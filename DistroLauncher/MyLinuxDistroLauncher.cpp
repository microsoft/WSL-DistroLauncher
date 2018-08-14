//
//    Copyright (C) Microsoft.  All rights reserved.
// Licensed under the terms described in the LICENSE file in the root of this project.
//
#include "stdafx.h"
#include "MyLinuxDistroLauncher.hpp"

static const size_t MAX_USERNAME_LENGTH = 32;
static const size_t UID_BUFFER_LENGTH = 64;
static const std::wstring DEFAULT_USER_GROUPS = L"adm,cdrom,sudo,dip,plugdev";

using namespace std;

MyLinuxDistroLauncher::MyLinuxDistroLauncher() : BaseLinuxDistroLauncher()
{
    // Place any actual initialization for the class in Initialize()
}

// Method Description:
// - Initializes the MyLinuxDistroLauncher object. Sets any internal state that 
//      might be needed.
// Arguments:
// - None
// Return Value:
// - An HRESULT with the failure code, or S_OK if it succeeded.
HRESULT MyLinuxDistroLauncher::Initialize()
{
    // LOAD BEARING CODE:
    // Set the name of your distro. This name will be used for registering your
    // distro with WSL, so make it unique to this version of your distro.
    // This name MUST remain constant across upgrades to your app.
    this->_myName= L"Debian";
    
    // Completely optional - Set the console window title.
    // For install, this will be the title of the window that appears, instead
    // of the full path to the app 
    //  ex C:\Program Files\WindowsApps\my.linuxdistro_1.0.0.0_x64__8b0vtwsf57ycy\DistroInstaller.exe
    // (bash will usually overwrite this when it starts)
    SetConsoleTitleW(L"Debian GNU/Linux");
    return S_OK;
}

// Method Description:
// - Performs post-install setup for this distro. This can include things such 
//      as creating a first user, or installing packages, etc. 
//   Add additional per-install configuration steps here if required.
// Arguments:
// - None
// Return Value:
// - An HRESULT with the failure code, or S_OK if it succeeded.
HRESULT MyLinuxDistroLauncher::SetupDistro()
{
    // Customize your setup here.
    // _SetupFirstUser() is a sample method that should create a user account
    //      on debian-based flavors. Modify that as necessary.
    HRESULT hr = _SetupFirstUser();

    return hr;
}

// Method Description:
// - Sets the default user of this distro to the username in argv.
//   Fails if there is not exactly one user specified, or if the user does not exist.
//   Uses MyLinuxDistroLauncher::_SetDefaultUser, so make sure that works for your distro.
// Arguments:
// - argc: Number of args in argv
// - argv: An array of arguments to parse. There should be exactly one, and it should be a username.
// Return Value:
// - An HRESULT with the failure code, or S_OK if it succeeded.
HRESULT MyLinuxDistroLauncher::SetDefaultUser(int argc, wchar_t const *argv[])
{
    HRESULT hr = S_OK;
    if (argc != 1)
    {
        Helpers::PrintMessage(MSG_INVALID_COMMANDLINE);
        hr = E_INVALIDARG;
    }
    else
    {
        wstring userName = argv[0];
        hr = this->_SetDefaultUser(userName);
    }
    return hr;
}

// Method Description:
// - This is an example function for prompting the user to create a first user.
//      This example is based on a Debian-based install, so modify as necessary.
//   Because this is launched before we've set a default UID for the distro,
//      all of the processes called during setup will be performed by UID 0 (root)
//      by default.
// Arguments:
// - None
// Return Value:
// - An HRESULT with the failure code, or S_OK if it succeeded.
HRESULT MyLinuxDistroLauncher::_SetupFirstUser()
{
    wstring userName = _PromptForUsername();
    HRESULT hr = S_OK;

    // Check if the user exists. If the user does not exist create the user, add
    // the user to the default groups (sudo, adm, etc...)
    if (!_DoesUserExist(userName))
    {
        hr = _CreateUserAccount(userName);
    }
    else
    {
        Helpers::PrintMessage(MSG_FOUND_USER, userName.c_str());
    }

    // Set the password for the user.
    if (SUCCEEDED(hr))
    {
        hr = _SetUserPassword(userName);
    }

    if (SUCCEEDED(hr))
    {
        hr = this->_SetDefaultUser(userName);      
    }
    
    return hr;
}

// Method Description:
// - Prompts the user to enter a username for the first user account.
//      Will continue to prompt the user until they enter a valid username, 
//      see `Helpers::IsValidUserName`
// Arguments:
// - None
// Return Value:
// - The user entered username
wstring MyLinuxDistroLauncher::_PromptForUsername()
{
    wstring userName;
    // Prompt the user to input a username
    Helpers::PrintMessage(MSG_CREATE_USER_PROMPT);
    bool printInvalidMessage = false;
    while (!Helpers::IsValidUserName(userName))
    {
        if (printInvalidMessage)
        {
            Helpers::PrintMessage(MSG_INVALID_USER_NAME);
        }

        userName = Helpers::GetUserInput(MSG_ENTER_USERNAME, MAX_USERNAME_LENGTH);

        printInvalidMessage = true;
    }

    return userName;
}

// Method Description:
// - Creates a new user on the distro withj the given userName, and add them to
//      some default groups.
//   Because this is launched before we've set a default UID for the distro,
//      all of the processes called during setup will be performed by UID 0 (root)
//      by default.
// Arguments:
// - None
// Return Value:
// - An HRESULT with the failure code, or S_OK if it succeeded.
HRESULT MyLinuxDistroLauncher::_CreateUserAccount(const std::wstring& userName)
{
    bool userCreated = false;
    bool userSetupComplete = false;
    HRESULT hr = _AddUser(userName);
    if (SUCCEEDED(hr))
    {
        userCreated = true;
        hr = _AddUserToGroups(userName, DEFAULT_USER_GROUPS);
        if (SUCCEEDED(hr))
        {
            userSetupComplete = true;
        }
    }

    if (userCreated && !userSetupComplete)
    {
        _DeleteUser(userName);
    }

    return hr;
}

// Method Description:
// - Checks if a given username exists already on the system.
// Arguments:
// - userName: The username to check the presence of.
// Return Value:
// - true iff the user already exists.
bool MyLinuxDistroLauncher::_DoesUserExist(const wstring & userName)
{
    wstring bashCommand = L"/usr/bin/id " + userName + L" > /dev/null 2>&1";

    bool userExists = false;
    DWORD returnValue = 0;
    HRESULT hr = wslApi.WslLaunchInteractive(_myName, bashCommand.c_str(), true, &returnValue);
    if (SUCCEEDED(hr) && returnValue == 0)
    {
        userExists = true;
    }
    return userExists;
}

// Method Description:
// - Adds a user to a set of groups.
// Arguments:
// - userName: The username to add to groups.
// - groups: A comma-seperated list of group names to add the user to.
//      see DEFAULT_USER_GROUPS
// Return Value:
// - An HRESULT with the failure code, or S_OK if it succeeded.
HRESULT MyLinuxDistroLauncher::_AddUserToGroups(const wstring& userName, const wstring& groups)
{
    wstring commandLine =  L"/usr/sbin/usermod -aG " + groups + L" " + userName;
    DWORD returnValue = 0;
    return wslApi.WslLaunchInteractive(_myName, commandLine.c_str(), true, &returnValue);
}

// Method Description:
// - Creates a user with the given name.
// Arguments:
// - userName: The username to create.
// Return Value:
// - An HRESULT with the failure code, or S_OK if it succeeded.
HRESULT MyLinuxDistroLauncher::_AddUser(const wstring& userName)
{
    wstring commandLine = L"/usr/sbin/adduser --quiet --force-badname --disabled-password --gecos '' ";
    commandLine += userName;

    DWORD returnValue = 0;
    return wslApi.WslLaunchInteractive(_myName, commandLine.c_str(), true, &returnValue);
}

// Method Description:
// - Uses `/usr/bin/passwd` to prompt the user to enter a password for the given 
//      username. It continues to prompt them until a valid password is entered.
// Arguments:
// - userName: The username to prompt for the password for.
// Return Value:
// - An HRESULT with the failure code, or S_OK if it succeeded.
HRESULT MyLinuxDistroLauncher::_SetUserPassword(const wstring& userName)
{
    wstring commandLine = L"/usr/bin/passwd " + userName;
    DWORD returnValue = 0;
    HRESULT hr = E_FAIL;
    do 
    {
        hr = wslApi.WslLaunchInteractive(_myName, commandLine.c_str(), true, &returnValue);

    } while (SUCCEEDED(hr) && returnValue != 0);

    return hr;
}

// Method Description:
// - Retrieves the UID for a given username.
// Arguments:
// - userName: The username to query the UID of.
// - uid: Recieves the UID of the user specified by userName
// Return Value:
// - An HRESULT with the failure code, or S_OK if it succeeded.
HRESULT MyLinuxDistroLauncher::_QueryUserInfo(const wstring& userName,
                                              unsigned long* uid)
{
    // Create an unnamed pipe to read the output of the launched commands.
    HANDLE readPipe;
    HANDLE writePipe;
    SECURITY_ATTRIBUTES sa = {0};
    sa.nLength = sizeof(sa);
    sa.bInheritHandle = TRUE;

    unsigned long uidLocal = 0;
    HRESULT hr = E_FAIL;
    if (CreatePipe(&readPipe, &writePipe, &sa, 0))
    {
        // Query the UID.
        wstring bashCommand = L"/usr/bin/id -u " + userName;
        int returnValue = 0;
        HANDLE child;
        hr = wslApi.WslLaunch(_myName, bashCommand.c_str(), true, GetStdHandle(STD_INPUT_HANDLE), writePipe, GetStdHandle(STD_ERROR_HANDLE), &child);
        if (SUCCEEDED(hr))
        {
            // Wait for the child to return
            WaitForSingleObject(child, INFINITE);
            CloseHandle(child);
            char buffer[UID_BUFFER_LENGTH];
            DWORD bytesRead;

            if (ReadFile(readPipe, buffer, (sizeof(buffer) - 1), &bytesRead, NULL))
            {
                buffer[bytesRead] = ANSI_NULL;
                try
                {
                    uidLocal = std::stoul(buffer, nullptr, 10);
                    // hr is successful here, last set by WslLaunch
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
    if (SUCCEEDED(hr))
    {
        *uid = uidLocal;
    }
    return hr;
}

// Method Description:
// - Configures this username as the default for this distro.
//      The default user is the one that WSL launches processes as by default.
//   This is called both on installation, and `launcher config --default-user`
// Arguments:
// - userName: The name of the user to set as default.
// Return Value:
// - An HRESULT with the failure code, or S_OK if it succeeded.
HRESULT MyLinuxDistroLauncher::_SetDefaultUser(const std::wstring& userName)
{

    // Query the uid of the user and set them as default for this distro
    unsigned long uid;
    HRESULT hr = _QueryUserInfo(userName, &uid);
    if (SUCCEEDED(hr))
    {
        hr = wslApi.WslConfigureDistribution(_myName, uid, (WSL_DISTRIBUTION_FLAGS) WSL_DISTRIBUTION_FLAGS_DEFAULT);
        if (SUCCEEDED(hr))
        {
            Helpers::PrintMessage(MSG_CREATE_USER_SUCCESS, userName.c_str());
        }
    }  
    if (!SUCCEEDED(hr))
    {
        Helpers::PrintMessage(MSG_SET_USER_FAILURE, userName.c_str());
    }
    return hr;
}

// Method Description:
// - Deletes a user from this system.
// Arguments:
// - userName: The name of the user to delete
// Return Value:
// - An HRESULT with the failure code, or S_OK if it succeeded.
HRESULT MyLinuxDistroLauncher::_DeleteUser(const std::wstring& userName)
{
    wstring bashCommand = L"/usr/sbin/deluser " + userName + L" &> /dev/null";
    wstring bashCommandFormatted = _FormatBashCommandLine(bashCommand);
    DWORD returnValue = 0;
    return wslApi.WslLaunchInteractive(_myName, bashCommandFormatted.c_str(), true, &returnValue);
}

// Function Description:
// - This function takes a commandline and wraps it up as a command to be run 
//      by /bin/bash. This can be useful for redirecting output, or using other
//      shell functionality.
// Arguments:
// - commandLine: A command to be run by bash.
// Return Value:
// - The formatted commandline, in the format:
//      `/bin/bash -c "<commandLine>"`
wstring MyLinuxDistroLauncher::_FormatBashCommandLine(const wstring& commandLine)
{
    wstring formattedCommandLine(_myName, L"/bin/bash -c \"");
    formattedCommandLine += commandLine + L"\"";
    return formattedCommandLine;
}
