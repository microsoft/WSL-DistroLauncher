# WSL DistroLauncher Sample 
## Introduction 
  This is the basic reference implementation for a Linux Distro Installer application.

  It provides the following functionality:
  (where `launcher` is replaced by the distro-specific name)

  * `launcher`
    - Launch the distro's default login shell.
    - If the instance has not yet been installed, this will unpack and install the instance.

  * `launcher run <command line>`
    - Run the given command line in that distro, using the default configuration.
    - Everything after `run ` is passed to the linux LaunchProcess call.

  * `launcher config [setting [value]]`
    - Configure certain settings for this distro.
    - Settings are any of the following (by default)
      - `--default-user <username>`: Set the default user for this distro to <username>

  * `launcher clean`
    - Uninstalls the distro. The appx remains on your machine. This can be useful for "factory resetting" your instance. This removes the linux filesystem from the disk, but not the app from your PC, so you don't need to redownload the entire tar.gz again.

  * `launcher help`
    - Print the usage.

## Launcher Outline
  This is the basic flow of how the launcher code is set up.

  1.  If the `clean` argument is specified, we unregister the distro from WSL, and clean up the filesystem.
  2.  Next we check if the distro is installed. If it's not, then we'll try try to install and register it with the Windows Subsystem for Linux. 
  3.  Once the distro is successfully installed, any other pre-launch setup is performed in `MyLinuxDistroLauncher::SetupDistro()` This is where distro-specific setup can be performed. As an example, the reference implementation calls `MyLinuxDistroLauncher::_CreateUserAccount()`, which prompts the user to input a user-name and password, and sets this user account as the default for the distro.
      - Note: This sample function is Ubuntu specific; change as necessary to match the needs of your distro.
  4.  Once the distro is configured, we parse any other command-line arguments. This calls into `DispatchCommandLine()`, which you extend if necessary. By default, `DispatchCommandLine()` looks for only one verb - `run`. The details of these arguments are described above, in the [Introduction](#Introduction).

## Getting Started
  Creating your own linux distro is simple!
  1. First of all, pick a _Name_ for your distro. WSL will use this as a key to identify this particular version of your distro - so please try to make it unique! **This name should not change from one version of your app to the next.**
  Set this _name_ in `MyLinuxDistroLauncher::Initialize`, by setting `this->_MyName`. By default, the value is `"MyDistro.1.0"`
  2.  Modify `MyLinuxDistroLauncher::SetupDistro` in `MyLinuxDistroLauncher.cpp` to set up the initial configuration of your distro.
      - This can include prompting the user for the first user and password, for example.
      - We have provided a sample for setting up a first user on an Ubuntu based system. This code should be modified to work appropriately on your distro.
      - Make sure that `MyLinuxDistroLauncher::_SetDefaultUser` works on your distro. This is used for changing the default user WSL starts processes as, and is called when the user runs `<launcher> config --default-user`
  3.  Possibly modify `MyLinuxDistroLauncher::LaunchDefault`, if you'd like to specify a different default experience. This is the function that is called when the user runs either `mydistro` or `mydistro run` from the commandline.
  4.  Add an icon (.ico) and logo (.png) to the `/images` directory. The logo will be used in the Start Menu and the taskbar for your launcher, and the icon will appear on the console window.
      - The icon should be named `icon.ico`. It is currently a bug that it is not loaded by the console window, this should be fixed in the future.
  5. Pick the name you'd like to make this distro callable by from the commandline. For the rest of the README I'll be using `mydistro` or `mydistro.exe`. **This is the name of your executable** and should be unique.
  6. Make sure to change the name of the project in the `DistroInstaller.vcxproj` file to the name of your executable we picked in step 5. By default the lines should look like:

  ``` xml
  <PropertyGroup Label="Globals">
    ...
    <ProjectName>mydistro</ProjectName>
  </PropertyGroup>
  ```

  So if I wanted to instead call my distro "TheBestDistroEver", I'd change this to:
  ``` xml
  <PropertyGroup Label="Globals">
    ...
    <ProjectName>TheBestDistroEver</ProjectName>
  </PropertyGroup>
  ```

  7.  Update `MyDistro.appxmanifest`. There are a number of properties that are in the manifest that will need to be updated with your specific values.
      - Make sure to note the `Identity Publisher` value (by default, `"CN=DistroOwner"`). We'll need that for testing the application.
      - Make sure that `<desktop:ExecutionAlias Alias="mydistro.exe" />` is set to something that ends in ".exe". This is the command that will be used to launch your distro from the commandline, and should match the executable name we picked in step 4.
      - Make sure each of the `Executable` values match the executable name we picked in step 4.
  8. Copy your tar.gz containing your distro into the root of the project, and rename it to `install.tar.gz`.
  9. Update the values in `filemap.txt` to point at your logo, icon, executable, and the tar.gz containing your distro.
      - The executable should by default be coming from the `x64/Release` directory in the project.
      - The tar.gz should be named `install.tar.gz`.

## Build and Test
  To help building and testing the DistroLauncher project, we've included the following scripts to automate some tasks:

### Building:
  To compile the project, you can simply type `build` in the root of the project
  to use MSBuild to build the solution. This is useful for verifying that your application compiles, though to test it you will need to create and sideload the packaged .appx on your test machine (see Packaging).
  
  `build.bat` assumes that MSBuild is installed at one of the following paths:
  `%ProgramFiles*%\MSBuild\14.0\bin\msbuild.exe` or
  `%ProgramFiles*%\Microsoft Visual Studio\2017\Enterprise\MSBuild\15.0\Bin\msbuild.exe` or
  `%ProgramFiles*%\Microsoft Visual Studio\2017\Community\MSBuild\15.0\Bin\msbuild.exe`.

  If that's not the case, then you will need to modify that script.

### Packaging
  To create an appx to test installing and running your launcher, you can use the included `pkg` script.
  However, you'll need to make some small changes to it first. You'll need to change the value of the `_OWNER` variable to be the same as the `Identity Publisher` value in the appxmanifest. 

  So if your appxmanifest has

  ``` xml
  <Identity Name="DistroName.1.0"
            Version="1.0"
            Publisher="CN=MyCompany"
            ProcessorArchitecture="x64" />
  ```

  Then you'd need to change the `pkg.bat` script to the following:

  ``` cmd
  set _OWNER=MyCompany
  ```

  Once that's set, you can call `pkg` from your command prompt in the root of the project to build the release version of your launcher, and pack it into an appx.

  This first time you do this, `pkg` will prompt you for a password (3 times) to create some test certs and private keys to sign the appx with. (Sideloading your appx won't work unless it's signed in this manner.)

  You will also need to add the generated cert to your test machine to be able to sideload the appx. 
  after running `pkg`, you can run `%_KITS%\CertMgr /add %_OWNER%.cer /s /r localMachine root` to add the test cert as a root cert on your machine. If you'd like to use another cert to sign the appx instead, you can modify `pkg.bat` as necessary, or use at as a reference for invoking `makeappx.exe` and `signtool`.

### Testing
  Once you have a signed appx, you can now install it on your machine to test it!

  But before you do that, make sure you've enabled Developer Mode in the Settings app (WSL won't work without it, and neither will sideloading). Then double click on the signed appx, and click "Install" to install it. Note that this only installed the appx on your system, but it doesn't unzip the tar.gz or register the distro yet. You can then begin the distro registration by launching the app from the Start Menu, or executing `mydistro` from the commandline. Unfortunately, the "Launch" button on the sideloading dialog does not work for Distro Launchers at the moment.

### Publishing
  Once you are ready to upload your appx to the store, you will need to change a few small things to prepare the appx for the store.

  1. In the appxmanifest, you will need to change the values of the Identity to match the value given to you by the store. This should look like the following:

  ``` xml
  <Identity Name="1234YourCompanyName.YourAppName"
          Version="1.0.1.0"
          Publisher="CN=12345678-045C-ABCD-1234-ABCDEF987654"
          ProcessorArchitecture="x64" />
  ```

  2. The appx that you upload to the store does not need to be signed. You can quickly do this with the following command:

  ``` cmd
  build clean rel && %_KITS%\makeappx.exe pack /m %_AppxName%.appxmanifest /f %_FilemapName% /p %_AppxName%.appx
  ```

  from a console window that you have previously run `pkg` in.

# Contributing

This project has adopted the [Microsoft Open Source Code of Conduct](https://opensource.microsoft.com/codeofconduct/). For more information see the [Code of Conduct FAQ](https://opensource.microsoft.com/codeofconduct/faq/) or contact [opencode@microsoft.com](mailto:opencode@microsoft.com) with any additional questions or comments.
