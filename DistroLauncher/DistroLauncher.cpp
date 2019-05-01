//
//    Copyright (C) Microsoft.  All rights reserved.
// Licensed under the terms described in the LICENSE file in the root of this project.
//

#include "stdafx.h"
#include "resource.h"

// Commandline arguments: 
#define ARG_CONFIG              L"config"
#define ARG_CONFIG_DEFAULT_USER L"--default-user"
#define ARG_INSTALL             L"install"
#define ARG_INSTALL_ROOT        L"--root"
#define ARG_RUN                 L"run"
#define ARG_RUN_C               L"-c"

// Helper class for calling WSL Functions:
// https://msdn.microsoft.com/en-us/library/windows/desktop/mt826874(v=vs.85).aspx
WslApiLoader g_wslApi(DistributionInfo::Name);

static HRESULT InstallDistribution(bool createUser);
static HRESULT SetDefaultUser(std::wstring_view userName);

//bool GetInstallScript(LPSTR *lppstr)
//{
//	auto result = false;
//	WCHAR exePath[MAX_PATH];
//	Helpers::GetExePath(exePath, MAX_PATH);
//	std::wstring filePath = L"install.sh";
//	filePath = exePath + filePath;
//	const auto hFile = CreateFile2(filePath.c_str(), GENERIC_READ, FILE_SHARE_READ, OPEN_EXISTING, nullptr);
//	if (hFile == INVALID_HANDLE_VALUE) return result;
//	const auto fileSize = GetFileSize(hFile, nullptr);
//	if (fileSize != INVALID_FILE_SIZE) if (fileSize == 0) SetLastError(ERROR_FILE_INVALID); else
//	{
//		DWORD bytesRead;
//		*lppstr = static_cast<LPSTR>(malloc(static_cast<size_t>(fileSize) + sizeof CHAR));
//		if (*lppstr)
//		{
//			result = ReadFile(hFile, *lppstr, fileSize, &bytesRead, nullptr);
//			(*lppstr)[fileSize / sizeof CHAR] = '\0';
//			if (!result)
//			{
//				free(*lppstr);
//				*lppstr = nullptr;
//			}
//		}
//		else SetLastError(ERROR_OUTOFMEMORY);
//	}
//	CloseHandle(hFile);
//	return result;
//
//}

HRESULT InstallDistribution(bool createUser)
{
    Helpers::PrintMessage(MSG_STATUS_INSTALLING);

	//Read install.sh file.
	/*LPSTR lpInstallScriptStr;
	if (!GetInstallScript(&lpInstallScriptStr)) return HRESULT_FROM_WIN32(GetLastError());*/

	// Register the distribution.
    auto hr = g_wslApi.WslRegisterDistribution();
	if (FAILED(hr)) {
		return hr;
	}

    // Delete /etc/resolv.conf to allow WSL to generate a version based on Windows networking information.
    DWORD exitCode;
    hr = g_wslApi.WslLaunchInteractive(L"/bin/rm /etc/resolv.conf", true, &exitCode);
	if (FAILED(hr)) {
		return hr;
	}

	// Install and config Arch Linux.
	//hr = Helpers::RunScript(&g_wslApi, lpInstallScriptStr, &exitCode);
	hr = Helpers::RunScript(&g_wslApi, L"install.sh", &exitCode);
	if (FAILED(hr)) {
		return hr;
	}
	if (exitCode != 0) {
		return E_FAIL;
	}

    // Create a user account.
    if (createUser) {
        Helpers::PrintMessage(MSG_CREATE_USER_PROMPT);
        std::wstring userName;
        do {
            userName = Helpers::GetUserInput(MSG_ENTER_USERNAME, 32);

        } while (!DistributionInfo::CreateUser(userName));

        // Set this user account as the default.
        hr = SetDefaultUser(userName);
        if (FAILED(hr)) {
            return hr;
        }
    }

    return hr;
}

HRESULT SetDefaultUser(std::wstring_view userName)
{
    // Query the UID of the given user name and configure the distribution
    // to use this UID as the default.
    const auto uid = DistributionInfo::QueryUid(userName);
    if (uid == UID_INVALID) {
        return E_INVALIDARG;
    }

    const auto hr = g_wslApi.WslConfigureDistribution(uid, WSL_DISTRIBUTION_FLAGS_DEFAULT);
    if (FAILED(hr)) {
        return hr;
    }

    return hr;
}

int wmain(int argc, wchar_t const *argv[])
{
    // Update the title bar of the console window.
    SetConsoleTitleW(DistributionInfo::WindowTitle.c_str());

    // Initialize a vector of arguments.
    std::vector<std::wstring_view> arguments;
    for (auto index = 1; index < argc; index += 1) {
        arguments.emplace_back(argv[index]);
    }

    // Ensure that the Windows Subsystem for Linux optional component is installed.
    DWORD exitCode = 1;
    if (!g_wslApi.WslIsOptionalComponentInstalled()) {
        Helpers::PrintMessage(MSG_MISSING_OPTIONAL_COMPONENT);
        if (arguments.empty()) {
            Helpers::PromptForInput();
        }

        return exitCode;
    }

    // Install the distribution if it is not already.
	const auto installOnly = !arguments.empty() && arguments[0] == ARG_INSTALL;
	auto hr = S_OK;
    if (!g_wslApi.WslIsDistributionRegistered()) {

        // If the "--root" option is specified, do not create a user account.
        const auto useRoot = installOnly && arguments.size() > 1 && arguments[1] == ARG_INSTALL_ROOT;
        hr = InstallDistribution(!useRoot);
        if (FAILED(hr)) {
            if (hr == HRESULT_FROM_WIN32(ERROR_ALREADY_EXISTS)) {
                Helpers::PrintMessage(MSG_INSTALL_ALREADY_EXISTS);
            }

        } else {
            Helpers::PrintMessage(MSG_INSTALL_SUCCESS);
        }

        exitCode = SUCCEEDED(hr) ? 0 : 1;
    }

    // Parse the command line arguments.
    if ((SUCCEEDED(hr)) && (!installOnly)) {
        if (arguments.empty()) {
            hr = g_wslApi.WslLaunchInteractive(L"", false, &exitCode);

        } else if ((arguments[0] == ARG_RUN) ||
                   (arguments[0] == ARG_RUN_C)) {

            std::wstring command;
            for (size_t index = 1; index < arguments.size(); index += 1) {
                command += L" ";
                command += arguments[index];
            }

            hr = g_wslApi.WslLaunchInteractive(command.c_str(), true, &exitCode);

        } else if (arguments[0] == ARG_CONFIG) {
            hr = E_INVALIDARG;
            if (arguments.size() == 3) {
                if (arguments[1] == ARG_CONFIG_DEFAULT_USER) {
                    hr = SetDefaultUser(arguments[2]);
                }
            }

            if (SUCCEEDED(hr)) {
                exitCode = 0;
            }

        } else {
            Helpers::PrintMessage(MSG_USAGE);
            return exitCode;
        }
    }

    // If an error was encountered, print an error message.
    if (FAILED(hr)) {
        if (hr == HRESULT_FROM_WIN32(ERROR_LINUX_SUBSYSTEM_NOT_PRESENT)) {
            Helpers::PrintMessage(MSG_MISSING_OPTIONAL_COMPONENT);

        } else {
            Helpers::PrintErrorMessage(hr);
        }

        if (arguments.empty()) {
            Helpers::PromptForInput();
        }
    }

    return SUCCEEDED(hr) ? exitCode : 1;
}