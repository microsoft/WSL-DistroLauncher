@rem This script packages your installer into an appx, and signs it with the 
@rem    keys from deploy.bat.
@rem After the first deploy.bat, you can just run package.bat to repackage.

call build clean rel

set _OWNER=DistroOwner
set _AppxName=MyDistro
set _FilemapName=filemap.txt

set _KITS=()

if exist "C:\Program Files (x86)\Windows Kits\10\bin\10.0.16190.0\x64\makeappx.exe" (
    set _KITS="C:\Program Files (x86)\Windows Kits\10\bin\10.0.16190.0\x64"
    goto :FOUND_KITS
)
if exist "c:\Program Files (x86)\Windows Kits\10\bin\x64\makeappx.exe" (
    set _KITS="c:\Program Files (x86)\Windows Kits\10\bin\x64"
    goto :FOUND_KITS
)
if exist "C:\Program Files (x86)\Windows Kits\10\bin\10.0.15063.0\x64\makeappx.exe" (
    set _KITS="C:\Program Files (x86)\Windows Kits\10\bin\10.0.15063.0\x64"
    goto :FOUND_KITS
)

if %_KITS%==() (
    echo "I couldn't find The SDK on you machine. Make sure that it's installed, and if it's not in the above if statements (in pkg.bat), add it."
    goto :EXIT
) 
:FOUND_KITS

if not exist %_OWNER%.pfx (
    echo "Generating some test certs/keys to test sideloading with."
    echo "This is going to prompt you for a name and password, and then that password again, and then the password again."
    echo "You can enter whatever you want, these should only be used for local testing."
    @rem Creates keys for local testing.
    @rem Note that "CN=%_OWNER%" needs to match the Publisher in your appxmanifest
    %_KITS%\makecert -r -h 0 -n "CN=%_OWNER%" -eku "1.3.6.1.5.5.7.3.3,1.3.6.1.4.1.311.10.3.13" -pe -sv %_OWNER%.pvk %_OWNER%.cer
    %_KITS%\pvk2pfx -pvk %_OWNER%.pvk -spc %_OWNER%.cer -pfx %_OWNER%.pfx

    echo "You will need to install that cert before you can sideload the appx. "
    echo "You can install it with the following command (in an admin window)"
    echo
    echo %_KITS%\CertMgr /add %_OWNER%.cer /s /r localMachine root 
)

%_KITS%\makeappx.exe pack /m %_AppxName%.appxmanifest /f %_FilemapName% /p %_AppxName%.appx /l
%_KITS%\signtool sign /v /f %_OWNER%.pfx /fd SHA256 %_AppxName%.appx


@rem You will need to run this once before you can sideload your appx on a machine.
@rem %_KITS%\CertMgr /add %_OWNER%.cer /s /r localMachine root 