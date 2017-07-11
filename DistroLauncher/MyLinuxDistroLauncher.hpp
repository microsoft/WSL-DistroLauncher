//
//    Copyright (C) Microsoft.  All rights reserved.
// Licensed under the terms described in the LICENSE file in the root of this project.
//
#pragma once
#include "BaseLinuxDistroLauncher.hpp"

class MyLinuxDistroLauncher : public BaseLinuxDistroLauncher
{
public:
    MyLinuxDistroLauncher();
    HRESULT Initialize();
    HRESULT SetupDistro();

    HRESULT SetDefaultUser(int argc, wchar_t const *argv[]);

private:
    HRESULT _SetupFirstUser();
    std::wstring _PromptForUsername();
    HRESULT _CreateUserAccount(const std::wstring& userName);

    std::wstring _FormatBashCommandLine(const std::wstring& commandLine);
    bool _DoesUserExist(const std::wstring & userName);

    HRESULT _AddUserToGroups(const std::wstring& userName, const std::wstring& groups);
    HRESULT _AddUser(const std::wstring& userName);
    HRESULT _DeleteUser(const std::wstring& userName);
    HRESULT _SetUserPassword(const std::wstring& userName);
    HRESULT _QueryUserInfo(const std::wstring& userName, unsigned long* uid);
    HRESULT _SetDefaultUser(const std::wstring& userName);
};
