# WSL DistroLauncher Sample 
## Introduction 
  This is the reference implementation for a Windows Subsystem for Linux (WSL) distribution installer application. You can use this sample project to create your own Linux distribution application that can be submitted to the Microsoft Store or sideloaded on your dev machine. 
  
  Note: This project is written in C++.

  ### Goals
  The goal of this project is to enable:
  * Linux distribution owners to package and submit an application that runs on top of WSL to the Microsoft Store
  * Developers to create custom Linux distributions that can be sideloaded onto their dev machine

### Project Status
This project is an active repo maintained by the WSL engineering team at Microsoft.

### Contents
  The sample provides the following functionality:
  (where `launcher` is replaced by the distro-specific name)

  * `launcher`
    - Launch the distro's default login shell.

  * `launcher run <command line>`
    - Run the given command line in that distro, using the default configuration.
    - Everything after `run ` is passed to the Linux LaunchProcess call.

  * `launcher config [setting [value]]`
    - Configure certain settings for this distro.
    - Settings are any of the following (by default)
      - `--default-user <username>`: Set the default user for this distro

  * `launcher help`
    - Print the usage.

## Launcher Outline
  This is the basic flow of how the launcher code is set up.

  1.  First check if the distribution is registered. If it's not, then it is registered it with the Windows Subsystem for Linux. Registration extracts the tar.gz file that is included in your distribution appx.
  2.  Once the distro is successfully registered, any other pre-launch setup is performed in `InstallDistribution()`. This is where distro-specific setup can be performed. As an example, the reference implementation creates a user account and sets this user account as the default for the distro.
      - Note: This commands used to query and create user accounts are Ubuntu-specific; change as necessary to match the needs of your distro.
  3.  Once the distro is configured, parse any other command-line arguments. The details of these arguments are described above, in the [Introduction](#Introduction).

## Project Structure
  The distro launcher is comprised of two Visual Studio projects - `launcher` and `DistroLauncher-Appx`. The `launcher` project builds the actual executable that is run when a user launches the app. The `DistroLauncher-Appx` builds the appx with all the correctly scaled resources and other dependencies for the Windows Store. Code changes will happen in the `launcher` project (under `DistroLauncher/`). Any manifest changes are going to happen in the `DistroLauncher-Appx` project (under `DistroLauncher-Appx/`). 

## Getting Started
  1. First, pick a _Name_ for your distro. WSL will use this as a key to identify this version of your distro - so please try to make it unique! **This name should not change from one version of your app to the next.**
  Set this _name_ in `DistroLauncher.cpp`, by modifying the `DISTRIBUTION_NAME` #define.
  2.  Modify `InstallDistribution` in `DistroLauncher.cpp` to set up the initial configuration of your distro.
      - We have provided a sample for setting up a default user on an Ubuntu based system. This code should be modified to work appropriately on your distro.
  3.  Add an icon (.ico) and logo (.png) to the `/images` directory. The logo will be used in the Start Menu and the taskbar for your launcher, and the icon will appear on the console window.
      - The icon must be named `icon.ico`.
  4. Pick the name you'd like to make this distro callable by from the command line. For the rest of the README I'll be using `mydistro` or `mydistro.exe`. **This is the name of your executable** and should be unique.
  5. Make sure to change the name of the project in the `DistroLauncher-Appx/DistroLauncher-Appx.vcxproj` file to the name of your executable we picked in step 5. By default, the lines should look like:

  ``` xml
  <PropertyGroup Label="Globals">
    ...
    <ProjectName>mydistro</ProjectName>
  </PropertyGroup>
  ```

  So, if I wanted to instead call my distro "TheBestDistroEver", I'd change this to:
  ``` xml
  <PropertyGroup Label="Globals">
    ...
    <ProjectName>TheBestDistroEver</ProjectName>
  </PropertyGroup>
  ```

  **DO NOT** change the ProjectName of the `DistroLauncher/DistroLauncher.vcxproj` from the value `launcher`. Doing so will break the build, as the DistroLauncher-Appx project is looking for the output of this project as `launcher.exe`.

  6.  Update `MyDistro.appxmanifest`. There are several properties that are in the manifest that will need to be updated with your specific values.
      - Make sure to note the `Identity Publisher` value (by default, `"CN=DistroOwner"`). We'll need that for testing the application.
      - Make sure that `<desktop:ExecutionAlias Alias="mydistro.exe" />` is set to something that ends in ".exe". This is the command that will be used to launch your distro from the command line and should match the executable name we picked in step 4.
      - Make sure each of the `Executable` values match the executable name we picked in step 4.
  7. Copy your tar.gz containing your distro into the root of the project and rename it to `install.tar.gz`.

## Build and Test
  To help building and testing the DistroLauncher project, we've included the following scripts to automate some tasks. You can either choose to use these scripts from the command line, or work directly in Visual Studio, whatever your preference is. 

  **Please Note** some sideloading/deployment steps don't work if you mix and match Visual Studio and the command line for development. If you run into errors while trying to deploy your app after already deploying it once, the easiest step is usually just to uninstall the previously sideloaded version and try again. 

### Setting up your Windows Environment
You will need a Windows environment to test that your app installs and works as expected. To set up a Windows environment for testing you can follow the steps from the [Windows Dev Center](https://developer.microsoft.com/en-us/windows/downloads/virtual-machines).

Note: If you are using Hyper-V you can use the new VM gallery to easily spin up a Windows instance.

### Building Project (Command line):
  To compile the project, you can simply type `build` in the root of the project
  to use MSBuild to build the solution. This is useful for verifying that your application compiles. It will also build an appx for you to sideload on your dev machine for testing.
  
  `build.bat` assumes that MSBuild is installed at one of the following paths:
  `%ProgramFiles*%\MSBuild\14.0\bin\msbuild.exe` or
  `%ProgramFiles*%\Microsoft Visual Studio\2017\Enterprise\MSBuild\15.0\Bin\msbuild.exe` or
  `%ProgramFiles*%\Microsoft Visual Studio\2017\Community\MSBuild\15.0\Bin\msbuild.exe`.

  If that's not the case, then you will need to modify that script.

  Once you've completed the build, the packaged appx should be placed in a directory like `...WSL-DistroLauncher\x64\Release\DistroLauncher-Appx` and should be named something like `DistroLauncher-Appx_1.0.0.0_x64.appx`. Simply double click that appx file to open the sideloading dialog. 

  You can also use the PowerShell cmdlet `Add-AppxPackage` to register your appx:
  ``` powershell
  powershell Add-AppxPackage x64\Debug\DistroLauncher-Appx\DistroLauncher-Appx_1.0.0.0_x64_Debug.appx
  ```

### Building Project (Visual Studio):

  You can also easily build and deploy the distro launcher from Visual Studio. To sideload your appx on your machine for testing, all you need to do is right-click on the "Solution (DistroLauncher)" in the Solution Explorer and click "Deploy Solution". This should build the project and sideload it automatically for testing.

  Note that the "Big Green Button" for running your project will likely not work. 

### Testing
  You should now have a finished appx sideloaded on your machine for testing.

  But before you do that, make sure you've enabled Developer Mode in the Settings app (sideloading won't work without it). Then double click on the signed appx and click "Install" to install it. Note that this only installed the appx on your system, but it doesn't unzip the tar.gz or register the distro yet. 

  You can then begin the distro registration by launching the app from the Start Menu or executing `mydistro` from the command line. 

### Publishing
  Once you are ready to upload your appx to the store, you will need to change a few small things to prepare the appx for the store.  

  1. In the appxmanifest, you will need to change the values of the Identity to match the value given to you by the store. This should look like the following:

  ``` xml
  <Identity Name="1234YourCompanyName.YourAppName"
            Version="1.0.1.0"
            Publisher="CN=12345678-045C-ABCD-1234-ABCDEF987654"
            ProcessorArchitecture="x64" />
  ```

  **NOTE**: Visual Studio can update this for you. You can do that by right-clicking on "DistroLauncher-Appx (Universal Windows)" in the solution explorer and clicking on "Store... Associate App with the Store..." and following the wizard. 

  2. You will either need to run `build rel` from the command line to generate the Release version of your appx or use Visual Studio directly to upload your package to the store. You can do this by right-clicking on "DistroLauncher-Appx (Universal Windows)" in the solution explorer and clicking on "Store... Create App Packages..." and following the wizard. 

  Also make sure to check out the [Notes for uploading to the Store](https://github.com/Microsoft/WSL-DistroLauncher/wiki/Notes-for-uploading-to-the-Store) page on our wiki for more information.

# Issues & Contact
Any bugs or problems discovered with the Launcher should be filed in this project's Issues list. The team will be notified and will respond to the reported issue within 3 (US) working days.

You may also reach out to our team alias at wslpartners@microsoft.com for questions related to submitting your app to the Microsoft Store.

# Contributing
This project has adopted the [Microsoft Open Source Code of Conduct](https://opensource.microsoft.com/codeofconduct/). For more information see the [Code of Conduct FAQ](https://opensource.microsoft.com/codeofconduct/faq/) or contact [opencode@microsoft.com](mailto:opencode@microsoft.com) with any additional questions or comments.

