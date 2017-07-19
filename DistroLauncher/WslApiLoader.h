//
//    Copyright (C) Microsoft.  All rights reserved.
// Licensed under the terms described in the LICENSE file in the root of this project.
//
#pragma once
#include <wslapi.h>

class WslApiLoader
{
  public:
	WslApiLoader();
	~WslApiLoader();

    BOOL WslIsDistributionRegistered(PCWSTR distributionName);

    HRESULT WslRegisterDistribution(PCWSTR distributionName, PCWSTR tarGzFilename);

    HRESULT WslUnregisterDistribution(PCWSTR distributionName);

    HRESULT WslConfigureDistribution(PCWSTR distributionName,
                                     ULONG defaultUID,
                                     WSL_DISTRIBUTION_FLAGS wslDistributionFlags);

    HRESULT WslGetDistributionConfiguration(PCWSTR distributionName,
                                            ULONG *distributionVersion,
                                            ULONG *defaultUID,
                                            WSL_DISTRIBUTION_FLAGS *wslDistributionFlags,
                                            PSTR **defaultEnvironmentVariables,
                                            ULONG *defaultEnvironmentVariableCount);

    HRESULT WslLaunchInteractive(PCWSTR distributionName,
                                 PCWSTR command,
                                 BOOL useCurrentWorkingDirectory,
                                 DWORD *exitCode);

    HRESULT WslLaunch(PCWSTR distributionName,
                      PCWSTR command,
                      BOOL useCurrentWorkingDirectory,
                      HANDLE stdIn,
                      HANDLE stdOut,
                      HANDLE stdErr,
                      HANDLE *process);

    HRESULT EnsureWslApiDll();
  private:
    HMODULE _hWslApiDll;
};

extern WslApiLoader wslApi;
