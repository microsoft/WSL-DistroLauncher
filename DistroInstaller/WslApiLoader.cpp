//
//    Copyright (C) Microsoft.  All rights reserved.
// Licensed under the terms described in the LICENSE file in the root of this project.
//
#include "stdafx.h"
#include "WslApiLoader.h"

WslApiLoader wslApi;

WslApiLoader::WslApiLoader() : _hWslApiDll(nullptr)
{
}

WslApiLoader::~WslApiLoader()
{
    if (_hWslApiDll != nullptr)
    {
        FreeLibrary(_hWslApiDll);
        _hWslApiDll = nullptr;
    }
}

// If wslapi.dll hasn't been loaded, load it.
HRESULT WslApiLoader::EnsureWslApiDll()
{
    HRESULT hr = S_OK;
    if (_hWslApiDll == nullptr)
    {
        _hWslApiDll = LoadLibraryEx(L"wslapi.dll", nullptr, LOAD_LIBRARY_SEARCH_SYSTEM32);
        if (_hWslApiDll == nullptr)
        {
            hr = HRESULT_FROM_WIN32(GetLastError());
        }
    }
    if (hr == HRESULT_FROM_WIN32(ERROR_MOD_NOT_FOUND))
    {
        Helpers::PrintMessage(MSG_MISSING_OPTIONAL_COMPONENT);
    }

    return hr;
}

typedef BOOL (STDAPICALLTYPE* PFNWSLISDISTRIBUTIONREGISTERED)(PCWSTR); // typedef for WslIsDistributionRegistered
BOOL WslApiLoader::WslIsDistributionRegistered(PCWSTR distributionName)
{
    if (SUCCEEDED(EnsureWslApiDll()))
    {
        // load function
        static PFNWSLISDISTRIBUTIONREGISTERED pfn = (PFNWSLISDISTRIBUTIONREGISTERED)GetProcAddress(_hWslApiDll, "WslIsDistributionRegistered");
        if (pfn != nullptr)
        {
            // call function
            return pfn(distributionName);
        }
    }

    return FALSE;
}

typedef HRESULT (STDAPICALLTYPE* PFNWSLREGISTERDISTRIBUTION)(PCWSTR, PCWSTR); // typedef for WslRegisterDistribution
HRESULT WslApiLoader::WslRegisterDistribution(PCWSTR distributionName, PCWSTR tarGzFilename)
{
    if (SUCCEEDED(EnsureWslApiDll()))
    {
        // load function
        static PFNWSLREGISTERDISTRIBUTION pfn = (PFNWSLREGISTERDISTRIBUTION)GetProcAddress(_hWslApiDll, "WslRegisterDistribution");
        if (pfn != nullptr)
        {
            // call function
            return pfn(distributionName, tarGzFilename);
        }
    }

    return HRESULT_FROM_WIN32(GetLastError());
}

typedef HRESULT (STDAPICALLTYPE* PFNWSLUNREGISTERDISTRIBUTION)(PCWSTR); // typedef for WslUnregisterDistribution
HRESULT WslApiLoader::WslUnregisterDistribution(PCWSTR distributionName)
{
    if (SUCCEEDED(EnsureWslApiDll()))
    {
        // load function
        static PFNWSLUNREGISTERDISTRIBUTION pfn = (PFNWSLUNREGISTERDISTRIBUTION)GetProcAddress(_hWslApiDll, "WslUnregisterDistribution");
        if (pfn != nullptr)
        {
            // call function
            return pfn(distributionName);
        }
    }

    return HRESULT_FROM_WIN32(GetLastError());
}

typedef HRESULT (STDAPICALLTYPE* PFNWSLCONFIGUREDISTRIBUTION)(PCWSTR, ULONG, WSL_DISTRIBUTION_FLAGS); // typedef for WslConfigureDistribution
HRESULT WslApiLoader::WslConfigureDistribution(PCWSTR distributionName, ULONG defaultUID, WSL_DISTRIBUTION_FLAGS wslDistributionFlags)
{
    if (SUCCEEDED(EnsureWslApiDll()))
    {
        // load function
        static PFNWSLCONFIGUREDISTRIBUTION pfn = (PFNWSLCONFIGUREDISTRIBUTION)GetProcAddress(_hWslApiDll, "WslConfigureDistribution");
        if (pfn != nullptr)
        {
            // call function
            return pfn(distributionName, defaultUID, wslDistributionFlags);
        }
    }

    return HRESULT_FROM_WIN32(GetLastError());
}

// typedef for WslGetDistributionConfiguration
typedef HRESULT (STDAPICALLTYPE* PFNWSLGETDISTRIBUTIONCONFIGURATION)(PCWSTR, ULONG *, ULONG *, WSL_DISTRIBUTION_FLAGS *, PSTR **, ULONG *);
HRESULT WslApiLoader::WslGetDistributionConfiguration(PCWSTR distributionName,
                                                      ULONG *distributionVersion,
                                                      ULONG *defaultUID,
                                                      WSL_DISTRIBUTION_FLAGS *wslDistributionFlags,
                                                      PSTR **defaultEnvironmentVariables,
                                                      ULONG *defaultEnvironmentVariableCount)
{
    if (SUCCEEDED(EnsureWslApiDll()))
    {
        // load function
        static PFNWSLGETDISTRIBUTIONCONFIGURATION pfn = (PFNWSLGETDISTRIBUTIONCONFIGURATION)GetProcAddress(_hWslApiDll, "WslGetDistributionConfiguration");
        if (pfn != nullptr)
        {
            // call function
            return pfn(distributionName,
                       distributionVersion,
                       defaultUID,
                       wslDistributionFlags,
                       defaultEnvironmentVariables,
                       defaultEnvironmentVariableCount);
        }
    }

    return HRESULT_FROM_WIN32(GetLastError());
}

typedef HRESULT (STDAPICALLTYPE* PFNWSLLAUNCHINTERACTIVE)(PCWSTR, PCWSTR, BOOL, DWORD *); // typedef for WslLaunchInteractive
HRESULT WslApiLoader::WslLaunchInteractive(PCWSTR distributionName, PCWSTR command, BOOL useCurrentWorkingDirectory, DWORD *exitCode)
{
    if (SUCCEEDED(EnsureWslApiDll()))
    {
        // load function
        static PFNWSLLAUNCHINTERACTIVE pfn = (PFNWSLLAUNCHINTERACTIVE)GetProcAddress(_hWslApiDll, "WslLaunchInteractive");
        if (pfn != nullptr)
        {
            // call function
            return pfn(distributionName, command, useCurrentWorkingDirectory, exitCode);
        }
    }

    return HRESULT_FROM_WIN32(GetLastError());
}

typedef HRESULT (STDAPICALLTYPE* PFNWSLLAUNCH)(PCWSTR, PCWSTR, BOOL, HANDLE, HANDLE, HANDLE, HANDLE *); // typedef for WslLaunch
HRESULT WslApiLoader::WslLaunch(PCWSTR distributionName,
                                PCWSTR command,
                                BOOL useCurrentWorkingDirectory,
                                HANDLE stdIn,
                                HANDLE stdOut,
                                HANDLE stdErr,
                                HANDLE *process)
{
    if (SUCCEEDED(EnsureWslApiDll()))
    {
        // load function
        static PFNWSLLAUNCH pfn = (PFNWSLLAUNCH)GetProcAddress(_hWslApiDll, "WslLaunch");
        if (pfn != nullptr)
        {
            // call function
            return pfn(distributionName, command, useCurrentWorkingDirectory, stdIn, stdOut, stdErr, process);
        }
    }
    return HRESULT_FROM_WIN32(GetLastError());
}
