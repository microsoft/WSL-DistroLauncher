//
//    Copyright (C) Microsoft.  All rights reserved.
// Licensed under the terms described in the LICENSE file in the root of this project.
//
#pragma once

class BaseLinuxDistroLauncher
{
public:
    BaseLinuxDistroLauncher();
    ~BaseLinuxDistroLauncher();
    virtual HRESULT Initialize() = 0;

    HRESULT DispatchCommandLine(int argc, wchar_t const *argv[]);
    
    BOOL IsInstalled();
    HRESULT InstallDistro();

    virtual HRESULT SetupDistro() = 0;

    HRESULT CleanDistro();
    
    HRESULT LaunchDefault();
    HRESULT LaunchProcess(int argc, wchar_t const *argv[]);
    
    HRESULT Configure(int argc, wchar_t const *argv[]);
    virtual HRESULT SetDefaultUser(int argc, wchar_t const *argv[]) = 0;

    HRESULT PrintHelp(int argc, wchar_t const *argv[]);

protected:
    const wchar_t* _myName;
};
