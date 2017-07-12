//
//    Copyright (C) Microsoft.  All rights reserved.
// Licensed under the terms described in the LICENSE file in the root of this project.
//
#include "stdafx.h"
#include "MyLinuxDistroLauncher.hpp"

int wmain(int argc, wchar_t const *argv[])
{
    HRESULT hr = S_OK;

    MyLinuxDistroLauncher myDistro = MyLinuxDistroLauncher();
    hr = myDistro.Initialize();

    // Quick look to see if we're cleaning the distro.
    // We want this to be able to be done even if setup hasn't been completed.
    if (argc > 1 && _wcsicmp(argv[1], L"clean") == 0)
    {
        hr = myDistro.CleanDistro();
    }
    else if (SUCCEEDED(hr))
    {
        if (!myDistro.IsInstalled())
        {
            // Try installing the distro. If we successfully install, then also 
            //      perform setup.
            hr = myDistro.InstallDistro();

            if (SUCCEEDED(hr)) 
            {
                hr = myDistro.SetupDistro();
            }
        }

        if (SUCCEEDED(hr))
        {
            // Proccess the commandline args if there are any
            int remainingArgc = argc - 1;
            wchar_t const ** remainingArgv = argc > 1 ? argv + 1 : nullptr;
            hr = myDistro.DispatchCommandLine(remainingArgc, remainingArgv);
        }
    }
    
    // If it wasn't an invalid commandline, print the error message.
    if (!SUCCEEDED(hr) && hr != E_INVALIDARG)
    {
        Helpers::PrintMessage(MSG_ERROR_CODE, hr);

		// 0x80070003 is the HR corresponding to the optional component not being installed.
        if (hr == 0x80070003)
        {
            Helpers::PrintMessage(MSG_MISSING_OPTIONAL_COMPONENT);
        }   
        Helpers::PrintMessage(MSG_PRESS_A_KEY);
        _getwch();
    }

    return SUCCEEDED(hr)? 0 : 1;
}