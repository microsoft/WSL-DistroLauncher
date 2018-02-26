//
//    Copyright (C) Microsoft.  All rights reserved.
// Licensed under the terms described in the LICENSE file in the root of this project.
//
#include "stdafx.h"

#define DISTRO_NAME L"MyDistribution"

WslApiLoader g_wslApi;

static HRESULT InstallDistribution();
static HRESULT QueryUserInfo(const std::wstring& userName, unsigned long* uid);
static HRESULT SetDefaultUser(const std::wstring& userName);

HRESULT InstallDistribution()
{
    Helpers::PrintMessage(MSG_STATUS_INSTALLING);
    HRESULT hr = g_wslApi.WslRegisterDistribution(DISTRO_NAME, L"install.tar.gz");
    if (FAILED(hr)) {
        if (hr == HRESULT_FROM_WIN32(ERROR_ALREADY_EXISTS)) {
            Helpers::PrintMessage(INSTALL_ALREADY_EXISTS);
        }

        return hr;
    }

    // Delete /etc/resolv.conf to allow WSL to generate a version based on Windows networking information.
    DWORD exitCode;
    hr = g_wslApi.WslLaunchInteractive(DISTRO_NAME, L"/bin/rm /etc/resolv.conf", true, &exitCode);
    if (FAILED(hr)) {
        return hr;
    }

    // Prompt for a username, ensure the user does not already exist.
    Helpers::PrintMessage(MSG_CREATE_USER_PROMPT);
    std::wstring commandLine;
    std::wstring userName;
    do {
        userName = Helpers::GetUserInput(MSG_ENTER_USERNAME, 32);
        // Create the user account.
        commandLine = L"/usr/sbin/adduser --gecos '' " + userName;
        hr = g_wslApi.WslLaunchInteractive(DISTRO_NAME, commandLine.c_str(), true, &exitCode);
        if (FAILED(hr)) {
            return hr;
        }

    } while (exitCode != 0);

    // Add the user account to any relevant groups.
    commandLine = L"/usr/sbin/usermod -aG adm,cdrom,sudo,dip,plugdev " + userName;
    hr = g_wslApi.WslLaunchInteractive(DISTRO_NAME, commandLine.c_str(), true, &exitCode);
    if (FAILED(hr)) {
        return hr;
    }

    // Set this user account as the default.
    hr = SetDefaultUser(userName);
    if (FAILED(hr)) {
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
    if (CreatePipe(&readPipe, &writePipe, &sa, 0)) {
        // Query the UID of the supplied username.
        std::wstring bashCommand = L"/usr/bin/id -u " + userName;
        int returnValue = 0;
        HANDLE child;
        hr = g_wslApi.WslLaunch(DISTRO_NAME, bashCommand.c_str(), true, GetStdHandle(STD_INPUT_HANDLE), writePipe, GetStdHandle(STD_ERROR_HANDLE), &child);
        if (SUCCEEDED(hr)) {
            // Wait for the child to exit.
            WaitForSingleObject(child, INFINITE);
            DWORD exitCode;
            if ((GetExitCodeProcess(child, &exitCode) == 0) || (exitCode != 0)) {
                hr = E_INVALIDARG;
            }

            CloseHandle(child);
            if (SUCCEEDED(hr)) {
                char buffer[64];
                DWORD bytesRead;

                // Read the output of the command from the pipe and convert to a UID.
                if (ReadFile(readPipe, buffer, (sizeof(buffer) - 1), &bytesRead, NULL)) {
                    buffer[bytesRead] = ANSI_NULL;
                    try {
                        *uid = std::stoul(buffer, nullptr, 10);

                    } catch( ... ) {
                        hr = E_INVALIDARG;
                    }

                } else {
                    hr = HRESULT_FROM_WIN32(GetLastError()); 
                }
            }
        }

        CloseHandle(readPipe);
        CloseHandle(writePipe);
    }

    return hr;
}

HRESULT SetDefaultUser(const std::wstring& userName)
{
    // Query the UID of the created user account and configure the distribution
    // to use this UID as the default.
    ULONG uid;
    HRESULT hr = QueryUserInfo(userName, &uid);
    if (FAILED(hr)) {
        return hr;
    }

    hr = g_wslApi.WslConfigureDistribution(DISTRO_NAME, uid, WSL_DISTRIBUTION_FLAGS_DEFAULT);
    if (FAILED(hr)) {
        return hr;
    }

    return hr;
}

int wmain(int argc, wchar_t const *argv[])
{
    DWORD exitCode = 1;
    SetConsoleTitleW(DISTRO_NAME);

    // Verify that the Windows Subsystem for Linux optional component is installed.
    if (!g_wslApi.WslIsOptionalComponentInstalled()) {
        Helpers::PrintMessage(MSG_MISSING_OPTIONAL_COMPONENT);
        Helpers::PromptForInput();
        return exitCode;
    }

    // Register the distribution if it is not already.
    HRESULT hr = S_OK;
    if (!g_wslApi.WslIsDistributionRegistered(DISTRO_NAME)) {
        hr = InstallDistribution();
        Helpers::PrintMessage(SUCCEEDED(hr) ? MSG_INSTALL_SUCCESS : MSG_INSTALL_FAILURE);
    }

    // Parse the command line arguments.
    bool prompt = true;
    if (SUCCEEDED(hr)) {
        if (argc == 1) {
            hr = g_wslApi.WslLaunchInteractive(DISTRO_NAME, L"", false, &exitCode);

        } else if ((_wcsicmp(argv[1], L"run") == 0) ||
                   (_wcsicmp(argv[1], L"/c") == 0) ||
                   (_wcsicmp(argv[1], L"-c") == 0)) {

            std::wstring command;
            for (int i = 2; i < argc; ++i) {
                command += L" ";
                command += argv[i];
            }

            hr = g_wslApi.WslLaunchInteractive(DISTRO_NAME, command.c_str(), true, &exitCode);

        } else if (_wcsicmp(argv[1], L"config") == 0 ) {
            hr = E_INVALIDARG;
            prompt = false;
            if (argc == 4) {
                if (_wcsicmp(argv[2], L"--default-user") == 0) {
                    hr = SetDefaultUser(argv[3]);
                }
            }

        } else {
            Helpers::PrintMessage(MSG_USAGE);
            return exitCode;
        }
    }

    // If an error was encountered, print an error message.
    if (FAILED(hr)) {
        Helpers::PrintErrorMessage(hr);
        if (prompt) {
            Helpers::PromptForInput();
        }
    }

    return SUCCEEDED(hr) ? exitCode : 1;
}