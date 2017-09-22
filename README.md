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

## Project Structure
  The distro launcher is comprised of two Visual Studio projects - `launcher` and `DistroLauncher-Appx`. The first builds the actual launcher .exe that's executed when a user launches your app. The second is the project that actually builds the appx with all of the correctly scaled resources and other dependencies for the Windows Store. All of your code changes will happen in the `launcher` project (under `DistroLauncher/`). Any manifest changes are going to happen in the `DistroLauncher-Appx` project (under `DistroLauncher-Appx/`). 

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
  6. Make sure to change the name of the project in the `DistroLauncher-Appx/DistroLauncher-Appx.vcxproj` file to the name of your executable we picked in step 5. By default the lines should look like:

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

  **DO NOT** change the ProjectName of the `DistroLauncher/DistroLauncher.vcxproj` from the value `launcher`. Doing so will break the build, as the DistroLauncher-Appx project is looking for the output of this project as `launcher.exe`.

  7.  Update `MyDistro.appxmanifest`. There are a number of properties that are in the manifest that will need to be updated with your specific values.
      - Make sure to note the `Identity Publisher` value (by default, `"CN=DistroOwner"`). We'll need that for testing the application.
      - Make sure that `<desktop:ExecutionAlias Alias="mydistro.exe" />` is set to something that ends in ".exe". This is the command that will be used to launch your distro from the commandline, and should match the executable name we picked in step 4.
      - Make sure each of the `Executable` values match the executable name we picked in step 4.
  8. Copy your tar.gz containing your distro into the root of the project, and rename it to `install.tar.gz`.

## Build and Test
  To help building and testing the DistroLauncher project, we've included the following scripts to automate some tasks. You can either choose to use these scripts from the commandline, or work directly in Visual Studio, whatever your preference is. 

  **Please Note** some sideloading/deployment steps don't work if you mix and match Visual Studio and the commandline for development. If you run into errors while trying to deploy your app after already deploying it once, the easiest step is usually just to uninstall the previously sideloaded version and try again. 

### Building Project (Commandline):
  To compile the project, you can simply type `build` in the root of the project
  to use MSBuild to build the solution. This is useful for verifying that your application compiles. It will also build an appx for you to sideload on your dev machine for testing.
  
  `build.bat` assumes that MSBuild is installed at one of the following paths:
  `%ProgramFiles*%\MSBuild\14.0\bin\msbuild.exe` or
  `%ProgramFiles*%\Microsoft Visual Studio\2017\Enterprise\MSBuild\15.0\Bin\msbuild.exe` or
  `%ProgramFiles*%\Microsoft Visual Studio\2017\Community\MSBuild\15.0\Bin\msbuild.exe`.

  If that's not the case, then you will need to modify that script.

  Once you've completed the build, the packaged appx should be placed in a directory like `...WSL-DistroLauncher\x64\Release\DistroLauncher-Appx` and should be named something like `DistroLauncher-Appx_1.0.0.0_x64.appx`. Simply double click that appx file to open the sideloading dialog. 

  You can also use the powershell cmdlet `Add-AppxPackage` to register your appx. that can be invoked in a fashion similar to the following:
  ``` powershell
  powershell Add-AppxPackage x64\Debug\DistroLauncher-Appx\DistroLauncher-Appx_1.0.0.0_x64_Debug.appx
  ```

### Building Project (Visual Studio):

  You can also easily build and deploy the distro launcher from Visual Studio. To sideload your appx on your machine for testing, all you need to do is right-click on the "Solution (DistroLauncher)" in the Solution Explorer and click "Deploy Solution". This should build the project and sideload it automatically for testing.

  Note that the "Big Green Button" for running your project will likely not work. If you've previously registered your distro with WSL once, you might be able to use that to rebuild and launch your exe, but in most cases it won't work.

### Testing
  You should now have a finished appx sideloaded on your machine for testing.

  But before you do that, make sure you've enabled Developer Mode in the Settings app (WSL won't work without it, and neither will sideloading). Then double click on the signed appx, and click "Install" to install it. Note that this only installed the appx on your system, but it doesn't unzip the tar.gz or register the distro yet. 

  You can then begin the distro registration by launching the app from the Start Menu, or executing `mydistro` from the commandline. 

### Publishing
  Once you are ready to upload your appx to the store, you will need to change a few small things to prepare the appx for the store.  

  1. In the appxmanifest, you will need to change the values of the Identity to match the value given to you by the store. This should look like the following:

  ``` xml
  <Identity Name="1234YourCompanyName.YourAppName"
          Version="1.0.1.0"
          Publisher="CN=12345678-045C-ABCD-1234-ABCDEF987654"
          ProcessorArchitecture="x64" />
  ```

  **NOTE**: Visual Studio can update this for you. You can do that by right-clicking on "DistroLauncher-Appx (Universal Windows)" in the solution explorer, and clicking on "Store... Associate App with the Store..." and following the wizard. 

  2. You will either need to run `build rel` from the commandline to generate the Release version of your appx, or use Visual Studio directly to upload your package to the store. You can do this by right-clicking on "DistroLauncher-Appx (Universal Windows)" in the solution explorer, and clicking on "Store... Create App Packages..." and following the wizard. 

  Also maker sure to check out the [Notes for uploading to the Store](https://github.com/Microsoft/WSL-DistroLauncher/wiki/Notes-for-uploading-to-the-Store) page on our wiki for more information.

# Issues
Any bugs or problems discovered with the Launcher should be filed in this project's Issues list. The team will be notified and will respond to the reported issue within 3 (US) working days.

# Contributing
This project has adopted the [Microsoft Open Source Code of Conduct](https://opensource.microsoft.com/codeofconduct/). For more information see the [Code of Conduct FAQ](https://opensource.microsoft.com/codeofconduct/faq/) or contact [opencode@microsoft.com](mailto:opencode@microsoft.com) with any additional questions or comments.
