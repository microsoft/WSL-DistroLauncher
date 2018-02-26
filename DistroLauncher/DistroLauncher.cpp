//
//    Copyright (C) Microsoft.  All rights reserved.
// Licensed under the terms described in the LICENSE file in the root of this project.
//
#include "stdafx.h"

#define DISTRO_NAME L"SampleDistribution"

WslApiLoader g_wslApi;

static
BOOL DoesUserExist(const std::wstring& userName);

static
HRESULT QueryUserInfo(const std::wstring& userName, unsigned long* uid);

BOOL DoesUserExist(const std::wstring& userName)
{
    std::wstring commandLine = L"/usr/bin/id -u " + userName + L" > /dev/null 2>&1";
    DWORD exitCode;
    HRESULT hr = g_wslApi.WslLaunchInteractive(DISTRO_NAME,
                                               commandLine.c_str(),
                                               true,
                                               &exitCode);

    if (FAILED(hr))
    {
        return hr;
    }

    return (exitCode == 0);
}

static
HRESULT InstallDistribution()
{
    Helpers::PrintMessage(MSG_STATUS_INSTALLING);
    HRESULT hr = g_wslApi.WslRegisterDistribution(DISTRO_NAME, L"install.tar.gz");
    if (FAILED(hr))
    {
        if (hr == HRESULT_FROM_WIN32(ERROR_ALREADY_EXISTS))
        {
            // We can get into this state if the registration for this distro was 
            //   removed from WSL after being registered, but without uninstalling
            //   the app or otherwise deleting the filesystem.
            Helpers::PrintMessage(INSTALL_ALREADY_EXISTS);
        }

        return hr;
    }

    // Delete /etc/resolv.conf to allow WSL to generate a version based on Windows networking information.
    DWORD exitCode;
    hr = g_wslApi.WslLaunchInteractive(DISTRO_NAME, L"/bin/rm /etc/resolv.conf", true, &exitCode);
    if (FAILED(hr) || (exitCode != 0))
    {

    }

    // Prompt for a username, ensure the user does not already exist.
    std::wstring userName;
    ULONG uid;
    do
    {
        userName = Helpers::GetUserInput(MSG_ENTER_USERNAME, 32);

    } while (DoesUserExist(userName));

    // Create the user account.
    std::wstring commandLine = L"/usr/sbin/adduser --gecos '' " + userName;
    do
    {
        hr = g_wslApi.WslLaunchInteractive(DISTRO_NAME, commandLine.c_str(), true, &exitCode);
        if (FAILED(hr))
        {
            return hr;
        }
    } while (exitCode != 0);

    // Add the user account to any relevant groups.
    commandLine = L"/usr/sbin/usermod -aG adm,cdrom,sudo,dip,plugdev " + userName;
    hr = g_wslApi.WslLaunchInteractive(DISTRO_NAME, commandLine.c_str(), true, &exitCode);
    if (FAILED(hr) || (exitCode != 0))
    {
        return hr;
    }

    // Query the UID of the created user account and configure the distribution
    // to use this UID as the default.
    hr = QueryUserInfo(userName, &uid);
    if (FAILED(hr))
    {
        return hr;
    }

    hr = g_wslApi.WslConfigureDistribution(DISTRO_NAME, uid, WSL_DISTRIBUTION_FLAGS_DEFAULT);
    if (FAILED(hr))
    {
        return hr;
    }

    return hr;
}

HRESULT QueryUserInfo(const std::wstring& userName, unsigned long* uid)
{
    // Create a pipe to read the output of the launched process.
    HANDLE readPipe;
    HANDLE writePipe;
    SECURITY_ATTRIBUTES sa{sizeof(sa), NULL, TRUE};
    HRESULT hr = E_FAIL;
    if (CreatePipe(&readPipe, &writePipe, &sa, 0))
    {
        // Query the UID of the supplied username.
        std::wstring bashCommand = L"/usr/bin/id -u " + userName;
        int returnValue = 0;
        HANDLE child;
        hr = g_wslApi.WslLaunch(DISTRO_NAME, bashCommand.c_str(), true, GetStdHandle(STD_INPUT_HANDLE), writePipe, GetStdHandle(STD_ERROR_HANDLE), &child);
        if (SUCCEEDED(hr))
        {
            // Wait for the child to exit.
            WaitForSingleObject(child, INFINITE);
            CloseHandle(child);
            char buffer[64];
            DWORD bytesRead;

            // Read the output of the command from the pipe and convert to a UID.
            if (ReadFile(readPipe, buffer, (sizeof(buffer) - 1), &bytesRead, NULL))
            {
                buffer[bytesRead] = ANSI_NULL;
                try
                {
                    *uid = std::stoul(buffer, nullptr, 10);
                }
                catch( ... )
                {
                    hr = E_INVALIDARG;
                }
            }
            else 
            {
                hr = HRESULT_FROM_WIN32(GetLastError()); 
            }
        }

        CloseHandle(readPipe);
        CloseHandle(writePipe);
    }
    return hr;
}

int wmain(int argc, wchar_t const *argv[])
{
    SetConsoleTitleW(DISTRO_NAME);

    // Register the distribution if it is not already.
    HRESULT hr = S_OK;
    if (!g_wslApi.WslIsDistributionRegistered(DISTRO_NAME))
    {
        hr = InstallDistribution();
        Helpers::PrintMessage(SUCCEEDED(hr) ? MSG_INSTALL_SUCCESS : MSG_INSTALL_FAILURE);
    }

    // Parse the command line.
    DWORD exitCode = 0;
    if (SUCCEEDED(hr))
    {
        if (argc == 1)
        {
            hr = g_wslApi.WslLaunchInteractive(DISTRO_NAME, L"", false, &exitCode);
        }
        else if ((_wcsicmp(argv[0], L"run") == 0) ||
                 (_wcsicmp(argv[0], L"/c") == 0) ||
                 (_wcsicmp(argv[0], L"-c") == 0))
        {
            std::wstring command;
            for (int i = 1; i < argc; ++i)
            {
                command += L" " + std::wstring(argv[i]);
            }

            hr = g_wslApi.WslLaunchInteractive(DISTRO_NAME, command.c_str(), true, &exitCode);
        }
        else if (_wcsicmp(argv[0], L"config") == 0 )
        {
            //hr = this->Configure(remainingArgc, remainingArgv);
        }
        else if ((_wcsicmp(argv[0], L"help") == 0) ||
                 (_wcsicmp(argv[0], L"/?") == 0) ||
                 (_wcsicmp(argv[0], L"-?") == 0))
        {
            Helpers::PrintMessage(MSG_USAGE);
        }
        else
        {
            Helpers::PrintMessage(MSG_INVALID_ARGS, argv[0]);
            Helpers::PrintMessage(MSG_USAGE);
            hr = E_INVALIDARG;
        }
    }

    // If it wasn't an invalid commandline, print the error message.
    if (FAILED(hr))
    {
        Helpers::PrintMessage(MSG_ERROR_CODE, hr);
        Helpers::PrintMessage(MSG_PRESS_A_KEY);
        _getwch();
    }

    return SUCCEEDED(hr) ? exitCode : 1;
}