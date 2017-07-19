//
//    Copyright (C) Microsoft.  All rights reserved.
// Licensed under the terms described in the LICENSE file in the root of this project.
//
#include "stdafx.h"
#include "BaseLinuxDistroLauncher.hpp"

#define REGISTRY_DISTRO_SETUP_COMPLETE_KEY (L"SetupComplete")

using namespace Helpers;


BaseLinuxDistroLauncher::BaseLinuxDistroLauncher() :
    _myName(nullptr)
{
}

BaseLinuxDistroLauncher::~BaseLinuxDistroLauncher()
{
}

////////////////////////////////////////////////////////////////////////////////
//  Installation
////////////////////////////////////////////////////////////////////////////////

// Method Description:
// - Determines if this distro is already installed on WSL.
// Arguments:
// - None
// Return Value:
// - true iff this distro has already been registered with WSL using `WslRegisterDistribution`
BOOL BaseLinuxDistroLauncher::IsInstalled()
{
    if (_myName == nullptr)
    {
        throw std::invalid_argument("You must set a name for your distro before"
            " calling any WSL API's. See MyLinuxDistroLauncher::Initialize()");
    }
    return wslApi.WslIsDistributionRegistered(_myName);
}

// Method Description:
// - Attempts to install and register the distro contained by this app with the 
//      linux subsystem.
// Arguments:
// - None
// Return Value:
// - An HRESULT with the failure code, or S_OK if it succeeded.
HRESULT BaseLinuxDistroLauncher::InstallDistro()
{
    HRESULT hr = S_OK;

    PrintMessage(MSG_STATUS_INSTALLING);
    hr = wslApi.WslRegisterDistribution(_myName, L"install.tar.gz");
    
    if (hr == HRESULT_FROM_WIN32(ERROR_ALREADY_EXISTS))
    {
        // We can get into this state if the registration for this distro was 
        //   removed from WSL after being registered, but without uninstalling
        //   the app or otherwise deleting the filesystem.
        PrintMessage(INSTALL_ALREADY_EXISTS);
    }

    PrintMessage(SUCCEEDED(hr) ? MSG_INSTALL_SUCCESS : MSG_INSTALL_FAILURE);

    return hr;
}

////////////////////////////////////////////////////////////////////////////////
//  Command Line Parsing
////////////////////////////////////////////////////////////////////////////////

// Method Description:
// - Parses the commandline args passed in, and dispatches the appropriate function.
// Arguments:
// - argc: Number of args in argv
// - argv: An array of arguments to parse.
// Return Value:
// - An HRESULT with the failure code, or S_OK if it succeeded.
HRESULT BaseLinuxDistroLauncher::DispatchCommandLine(int argc, wchar_t const *argv[])
{
    HRESULT hr = S_OK;
    if (argc <= 0 || argv == nullptr)
    {
        hr = this->LaunchDefault();
    }
    else 
    {
        wchar_t const * command = argv[0];
        int remainingArgc = argc - 1;
        wchar_t const ** remainingArgv = argc > 1 ? argv + 1 : nullptr;

        if (_wcsicmp(command, L"run") == 0 ||
            _wcsicmp(command, L"/c") == 0 ||
            _wcsicmp(command, L"-c") == 0 )
        {
            hr = this->LaunchProcess(remainingArgc, remainingArgv);
        }
        else if (_wcsicmp(command, L"config") == 0 )
        {
            hr = this->Configure(remainingArgc, remainingArgv);
        }
        else if (_wcsicmp(command, L"help") == 0 ||
                 _wcsicmp(command, L"/?") == 0 ||
                 _wcsicmp(command, L"-?") == 0)
        {
            hr = this->PrintHelp(remainingArgc, remainingArgv);
        }
        else
        {
            PrintMessage(MSG_INVALID_ARGS, command);
            hr = E_INVALIDARG;
        }
        
    }
    
    return hr;
}

// Method Description:
// - Unregisters this distro from the linux subsystem, and removes the distro's 
//      files. The app remains installed, so the user can re-install the distro
//      without re-downloading the entire appx again.
// Arguments:
// - None
// Return Value:
// - An HRESULT with the failure code, or S_OK if it succeeded.
HRESULT BaseLinuxDistroLauncher::CleanDistro()
{
    HRESULT hr = S_OK;

    PrintMessage(MSG_STATUS_UNINSTALL_PROMPT);
    hr = PromptAcceptance(MSG_AGREE_PROMPT_WORD, MSG_AGREE_PROMPT);
    if (SUCCEEDED(hr))
    {
        PrintMessage(MSG_STATUS_UNINSTALLING);
        hr = wslApi.WslUnregisterDistribution(_myName);

        if (SUCCEEDED(hr))
        {
            PrintMessage(MSG_UNINSTALL_SUCCESS);
        }
        else
        {
            PrintMessage(MSG_UNINSTALL_FAILED);
        }
    }
    else
    {
        PrintMessage(MSG_AGREE_REJECTED);
    }
    return hr;
}

// Method Description:
// - Launches a default process for this distro. This is what's launched when 
//      the user runs this application without any arguments.
//   By default, this launches the user's default shell, via wsl.exe. 
//      Make any changes to the subclass (MyLinuxDistroLauncher) if you'd like 
//      to modify this.
// Arguments:
// - None
// Return Value:
// - An HRESULT with the failure code, or S_OK if it succeeded.
HRESULT BaseLinuxDistroLauncher::LaunchDefault()
{
    HRESULT hr = S_OK;
    DWORD returnValue;
    hr = wslApi.WslLaunchInteractive(_myName, L"", false, &returnValue);

    return hr;
}

// Method Description:
// - Launches the commandline specified by the arguments in argv.
//      This will take the args in argv and join them with spaces, and pass that
//      command line to WslLaunchInteractive. This launches the process as the 
//      default user for the distro.
//   If no args are passed in (argc==0 && argv==nullptr), then this launches 
//      the default process for this distro (see LaunchDefault).
// Arguments:
// - argc: Number of args in argv
// - argv: An array of arguments to parse.
// Return Value:
// - An HRESULT with the failure code, or S_OK if it succeeded.
HRESULT BaseLinuxDistroLauncher::LaunchProcess(int argc, wchar_t const *argv[])
{

    HRESULT hr = S_OK;
    if (argc == 0)
    {
        // No args were passed in
        hr = this->LaunchDefault();
    }
    else
    {
        std::wstring command = argv[0];
        // Join args with spaces    
        for (int i = 1; i < argc; ++i)
        {
            command += L" " + std::wstring(argv[i]);
        }

        DWORD returnValue;
        hr = wslApi.WslLaunchInteractive(_myName, command.c_str(), true, &returnValue);
    }

    return hr;
}

////////////////////////////////////////////////////////////////////////////////
//  Configuration
////////////////////////////////////////////////////////////////////////////////

// Method Description:
// - Parses the commandline args passed in to perform certain configuration tasks.
//      With no args, it prints all of the state of this distro.
//      If you pass in one of the configuration flags, you can get 
//      specifically that value, or pass in more arguments to set that value.
//   By default, the only config flags supported are:
//      `--default-user <username>`: Set the default user for this distro to <username>
// Arguments:
// - argc: Number of args in argv
// - argv: An array of arguments to parse.
// Return Value:
// - An HRESULT with the failure code, or S_OK if it succeeded.
HRESULT BaseLinuxDistroLauncher::Configure(int argc, wchar_t const *argv[])
{
    HRESULT hr = S_OK;
    if (argc <= 0 || argv == nullptr)
    {
        PrintMessage(MSG_INVALID_COMMANDLINE);
        hr = E_INVALIDARG;
    }
    else
    {
        wchar_t const * token = argv[0];
        wchar_t const ** remainingArgv = argc > 1 ? argv + 1 : nullptr;
        int remainingArgc = argc-1;

        if ( _wcsicmp(token, L"--default-user") == 0 )
        {
            hr = this->SetDefaultUser(remainingArgc, remainingArgv);
        }
        else
        {
            PrintMessage(MSG_INVALID_ARGS, token);
            hr = E_INVALIDARG;
        }

    }
    return hr;
}

////////////////////////////////////////////////////////////////////////////////
//  Help
////////////////////////////////////////////////////////////////////////////////

// Method Description:
// - Prints the usage
// Arguments:
// - argc: Number of args in argv
// - argv: An array of arguments to parse.
// Return Value:
// - An HRESULT with the failure code, or S_OK if it succeeded.
HRESULT BaseLinuxDistroLauncher::PrintHelp(int argc, wchar_t const *argv[])
{
    PrintMessage(MSG_USAGE);
    return S_OK;
}