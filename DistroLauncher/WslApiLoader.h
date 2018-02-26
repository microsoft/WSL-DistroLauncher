//
//    Copyright (C) Microsoft.  All rights reserved.
// Licensed under the terms described in the LICENSE file in the root of this project.
//
#pragma once
#include <wslapi.h>

typedef BOOL    (STDAPICALLTYPE* WSL_IS_DISTRIBUTION_REGISTERED)(PCWSTR);
typedef HRESULT (STDAPICALLTYPE* WSL_REGISTER_DISTRIBUTION)(PCWSTR, PCWSTR);
typedef HRESULT (STDAPICALLTYPE* WSL_CONFIGURE_DISTRIBUTION)(PCWSTR, ULONG, WSL_DISTRIBUTION_FLAGS);
typedef HRESULT (STDAPICALLTYPE* WSL_GET_DISTRIBUTION_CONFIGURATION)(PCWSTR, ULONG *, ULONG *, WSL_DISTRIBUTION_FLAGS *, PSTR **, ULONG *);
typedef HRESULT (STDAPICALLTYPE* WSL_LAUNCH_INTERACTIVE)(PCWSTR, PCWSTR, BOOL, DWORD *);
typedef HRESULT (STDAPICALLTYPE* WSL_LAUNCH)(PCWSTR, PCWSTR, BOOL, HANDLE, HANDLE, HANDLE, HANDLE *);

class WslApiLoader
{
  public:
    WslApiLoader();
    ~WslApiLoader();

    BOOL WslIsOptionalComponentInstalled();

    BOOL WslIsDistributionRegistered(PCWSTR distributionName);

    HRESULT WslRegisterDistribution(PCWSTR distributionName, PCWSTR tarGzFilename);

    HRESULT WslConfigureDistribution(PCWSTR distributionName,
                                     ULONG defaultUID,
                                     WSL_DISTRIBUTION_FLAGS wslDistributionFlags);

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

  private:
    HMODULE _wslApiDll;
    WSL_IS_DISTRIBUTION_REGISTERED _isDistributionRegistered;
    WSL_REGISTER_DISTRIBUTION _registerDistribution;
    WSL_CONFIGURE_DISTRIBUTION _configureDistribution;
    WSL_LAUNCH_INTERACTIVE _launchInteractive;
    WSL_LAUNCH _launch;
};

extern WslApiLoader g_wslApi;
