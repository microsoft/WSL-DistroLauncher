---
name: WSL Error on Launch
about: Report errors like 0x800320306 on launch.

---

**Note**

These WSL error messages occur from time to time and can tricky to troubleshoot short of reinstalling WSL.

They are usually not an issue with WLinux itself but a glitch with the underlying Windows Subsystem for Linux in Windows 10.

You can help us help you and Microsoft improve WSL and address these if you can provide us some debugging information.

[ ] I have read the above statement.

**Basic Troubleshooting**

Please check:

[ ] I have confirmed WSL is enabled: https://docs.microsoft.com/en-us/windows/wsl/troubleshooting#confirm-wsl-is-enabled.
[ ] I have searched Google for the error message.
[ ] I have searched the official Microsoft WSL issues page: https://github.com/Microsoft/WSL/issues.
[ ] I have searched the WLinux issues page: https://github.com/WhitewaterFoundry/WLinux/issues.
[ ] I have reset WLinux: Settings->Apps->Apps & features->WLinux->Advanced Options->Reset. 
[ ] I have disabled and re-enabled WSL in Windows Features.
[ ] I have run Windows 10 updates and restarted.

What other troubleshooting have you attempted to date?

**Error Code**

Insert here:

Please check:

[ ] This error code is not one listed below.

Known Error Codes
0x80040306 Fix: https://docs.microsoft.com/en-us/windows/wsl/troubleshooting#error-0x80040306-on-installation
0x80040154 Fix: https://docs.microsoft.com/en-us/windows/wsl/troubleshooting#error-0x80040154-after-windows-update

**Version**

Find: Settings->Apps->Apps & features->WLinux->Advanced Options->Version.

Insert here:

**Screenshot**

Insert here:

**Windows Build**

Run 'systeminfo | findstr /C:"OS"' in Command Prompt and insert here:

For help on retrieving: https://docs.microsoft.com/en-us/windows/wsl/troubleshooting#check-your-build-number

**WSL Debug Data**

Please collect and attach .etl files by following this guide: https://docs.microsoft.com/en-us/windows/wsl/troubleshooting#starting-bash-gives-an-error-code
