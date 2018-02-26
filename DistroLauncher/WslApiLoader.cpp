//
//    Copyright (C) Microsoft.  All rights reserved.
// Licensed under the terms described in the LICENSE file in the root of this project.
//
#include "stdafx.h"
#include "WslApiLoader.h"

WslApiLoader::WslApiLoader()
{
    _hWslApiDll = LoadLibraryEx(L"wslapi.dll", nullptr, LOAD_LIBRARY_SEARCH_SYSTEM32);
    if (_hWslApiDll == nullptr)
    {
        // TODO: throw
    }

    _isDistributionRegistered = (WSL_IS_DISTRIBUTION_REGISTERED)GetProcAddress(_hWslApiDll, "WslIsDistributionRegistered");
    _registerDistribution = (WSL_REGISTER_DISTRIBUTION)GetProcAddress(_hWslApiDll, "WslRegisterDistribution");
    _getDistributionConfiguration = (WSL_GET_DISTRIBUTION_CONFIGURATION)GetProcAddress(_hWslApiDll, "WslGetDistributionConfiguration");
    _configureDistribution = (WSL_CONFIGURE_DISTRIBUTION)GetProcAddress(_hWslApiDll, "WslConfigureDistribution");
    _launchInteractive = (WSL_LAUNCH_INTERACTIVE)GetProcAddress(_hWslApiDll, "WslLaunchInteractive");
    _launch = (WSL_LAUNCH)GetProcAddress(_hWslApiDll, "WslLaunch");

    if ((_isDistributionRegistered  == nullptr) ||
        (_registerDistribution  == nullptr) ||
        (_getDistributionConfiguration  == nullptr) ||
        (_configureDistribution  == nullptr) ||
        (_launchInteractive  == nullptr) ||
        (_launch  == nullptr)) {

        // TODO: throw
    }
}

WslApiLoader::~WslApiLoader()
{
    if (_hWslApiDll != nullptr)
    {
        FreeLibrary(_hWslApiDll);
    }
}

BOOL WslApiLoader::WslIsDistributionRegistered(PCWSTR distributionName)
{
    return _isDistributionRegistered(distributionName);
}

HRESULT WslApiLoader::WslRegisterDistribution(PCWSTR distributionName, PCWSTR tarGzFilename)
{
    HRESULT hr = _registerDistribution(distributionName, tarGzFilename);
    if (FAILED(hr))
    {
        Helpers::PrintMessage(MSG_WSL_REGISTER_DISTRIBUTION_FAILED);
    }

    return hr;
}

HRESULT WslApiLoader::WslConfigureDistribution(PCWSTR distributionName, ULONG defaultUID, WSL_DISTRIBUTION_FLAGS wslDistributionFlags)
{
    HRESULT hr = _configureDistribution(distributionName, defaultUID, wslDistributionFlags);
    if (FAILED(hr))
    {
        Helpers::PrintMessage(MSG_WSL_CONFIGURE_DISTRIBUTION_FAILED);
    }

    return hr;
}

HRESULT WslApiLoader::WslGetDistributionConfiguration(PCWSTR distributionName,
                                                      ULONG *distributionVersion,
                                                      ULONG *defaultUID,
                                                      WSL_DISTRIBUTION_FLAGS *wslDistributionFlags,
                                                      PSTR **defaultEnvironmentVariables,
                                                      ULONG *defaultEnvironmentVariableCount)
{

    HRESULT hr = _getDistributionConfiguration(distributionName,
                                               distributionVersion,
                                               defaultUID,
                                               wslDistributionFlags,
                                               defaultEnvironmentVariables,
                                               defaultEnvironmentVariableCount);

    if (FAILED(hr))
    {
        Helpers::PrintMessage(MSG_WSL_GET_DISTRIBUTION_CONFIGURATION_FAILED);
    }

    return hr;
}

HRESULT WslApiLoader::WslLaunchInteractive(PCWSTR distributionName, PCWSTR command, BOOL useCurrentWorkingDirectory, DWORD *exitCode)
{
    HRESULT hr = _launchInteractive(distributionName, command, useCurrentWorkingDirectory, exitCode);
    if (FAILED(hr))
    {
        Helpers::PrintMessage(MSG_WSL_LAUNCH_INTERACTIVE_FAILED);
    }

    return hr;
}

HRESULT WslApiLoader::WslLaunch(PCWSTR distributionName,
                                PCWSTR command,
                                BOOL useCurrentWorkingDirectory,
                                HANDLE stdIn,
                                HANDLE stdOut,
                                HANDLE stdErr,
                                HANDLE *process)
{
    HRESULT hr = _launch(distributionName, command, useCurrentWorkingDirectory, stdIn, stdOut, stdErr, process);
    if (FAILED(hr))
    {
        Helpers::PrintMessage(MSG_WSL_LAUNCH_FAILED);
    }

    return hr;
}
