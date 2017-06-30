@echo off

rem Add path to MakePri
set MAKEPRIEXE=()
if exist "%ProgramFiles(x86)%\Windows Kits\10\bin\x86\makepri.exe" (
    set MAKEPRIEXE="%ProgramFiles(x86)%\Windows Kits\10\bin\x86\makepri.exe"
    goto :FOUND_MAKEPRIEXE
)
if exist "%ProgramFiles(x86)%\Windows Kits\10\bin\x64\makepri.exe" (
    set MAKEPRIEXE="%ProgramFiles(x86)%\Windows Kits\10\bin\x64\makepri.exe"
    goto :FOUND_MAKEPRIEXE
)
if exist "%ProgramFiles%\Windows Kits\10\bin\x86\makepri.exe" (
    set MAKEPRIEXE="%ProgramFiles%\Windows Kits\10\bin\x86\makepri.exe"
    goto :FOUND_MAKEPRIEXE
)
if exist "%ProgramFiles%\Windows Kits\10\bin\x64\makepri.exe" (
    set MAKEPRIEXE="%ProgramFiles%\Windows Kits\10\bin\x64\makepri.exe"
    goto :FOUND_MAKEPRIEXE
)

if %MAKEPRIEXE%==() (
    echo "I couldn't find makepri.exe on your PC. Make sure it's installed somewhere, and if it's not in the above if statements (in buildpri.bat), add it."
    goto :EXIT
) 
:FOUND_MAKEPRIEXE

%MAKEPRIEXE% new /pr %~dp0\Resources /cf MyDistroResourcesConfig.xml /mn MyDistro.appxmanifest /of Resources.pri /o

:EXIT