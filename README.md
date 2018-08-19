# WLinux

<img src="https://github.com/sirredbeard/WLinux/blob/master/DistroLauncher-Appx/Assets/large%20logo.scale-100.png" height=15% width=15%>

A Linux® distribution optimized for WSL based on Debian® stable.

## WLinux Features

- Optimized for use with Windows® Subsystem for Linux (WSL) on Windows 10.
- Out-of-the-box support for external Windows X clients, such as [X410](https://www.microsoft.com/store/productId/9NLP712ZMN9Q).
- Popular programming tools, including git and python3, are pre-installed. Additional packages can be easily installed via the apt package management system from the expansive Debian repos.
- Ships with useful utilities for running Linux on WSL installable with one command.
- A handful of unnecessary packages, such as systemd, have been removed to improve stability and security.
- Scripts to easily install the following popular applications:
    - Visual Studio Code `$ sudo /opt/installcode.sh`
    - Google Chrome `$ sudo /opt/installchrome.sh`
    - [wslu](https://github.com/patrick330602/wslu) `$ sudo /opt/installwslu.sh`

## WLinux User Support

### General WSL Resources

See [Awesome WSL](https://github.com/sirredbeard/Awesome-WSL) for a comprehensive overview of the Windows Subsystem for Linux feature in Windows 10.

### Getting Help For WLinux

Support is handled via the GitHub project issues page. First search for your issue [here](https://github.com/sirredbeard/WLinux/issues). If you are unable to find your answer, please open a new issue [here](https://github.com/sirredbeard/WLinux/issues/new).

## WLinux Background

WLinux is a Linux distribution ("distro") optimized for use on Windows Subsystem for Linux ("WSL"). While other distros are available for WSL, this is the first Linux distro specifically designed for use on WSL. A number of enhancements are enabled by default and additional improvements are planned. WLinux is open-source and based on the stable Debian GNU/Linux distro. Development occurs on GitHub. Pull requests, forks, and issues are welcome. A paid version is planned for the Microsoft Store to fund future development.

Note: There are no .iso or .img files available for WLinux.

## WLinux Project Progress

Completed:

    - Automated custom Linux distro image based on Debian stretch.
    - Custom /etc/os-release.
    - Custom /etc/profile optimized for WSL.
    - Custom /etc/apt/sources.list.
    - Scripts to install popular third-party software:
        - Google Chrome
        - Microsoft Virtual Studio Code
        - wslu
    - Support for Windows X clients and libGL enhancements.
    - Pre-install git, apt-https, and python3.
    - Remove systemd and iptables.
    - Windows UWP app containerization..
    - Add custom branding assets.

Ongoing:

    - Testing.

Planned:

    - ARM64 support.
    - Additional Linux and Windows 10 integration features.
    - Additional third-party app install scripts:
        - Oracle Java
        - Anaconda Python Distribution

# The Geeky Details

## WLinux Components

- /x64/create-targz.sh - Builds the WLinux custom Linux distro in a WLinux or Debian environment. **Status:** Working.
    - Sample [install.tar.gz](https://1drv.ms/u/s!AspPK83V8Sf2g5pWRkGIYRFmAN7bIQ) built on 8/14/18.
- Launcher project - Builds the actual executable that is run when a user launches the app. 
- DistroLauncher-Appx project - Builds the distro package with all the assets and other dependencies.

Read more about the components from the upstream template by Microsoft [here](https://github.com/Microsoft/WSL-DistroLauncher). 

## Building Requirements
This project can be built using Visual Studio Community 2017. The "Universal Windows Platform development" feature is required, along with the following subfeatures:

- C++ Universal Windows Platform tools
- Windows 10 SDK for UWP: C#, VB, JS

## Building Configuation 

1. Developer Mode
	- Windows 10 must be in Developer mode, which can be enabled in Start -> Settings -> Update & Security -> For developers.

2. Enable WSL
	- The Windows Subsystem for Linux is not enabled by default, and is required to run the app. You can add the feature to your Windows installation by running `C:\Windows\System32\OptionalFeatures.exe` and selecting it from the list.

## Build Process
1. Open DistroLauncher.sln in Visual Studio Community 2017.
2. Generate a test certificate:
    1. In the Solution Explorer, open `DistroLauncher-Appx\DistroLauncher.appxmanifest`
    1. Select the Packaging tab
    1. Select "Choose Certificate"
    1. Click the Configure Certificate drop down and select Create test certificate.
1. Build install.tar.gz
    1. You will need access to an existing WLinux or Debian-based distro for this step. If you do not already have WLinux installed, I recommend the following steps:
        - Enable WSL on Windows if you have not already.
        - Install the [Debian for WSL app](https://www.microsoft.com/en-us/p/debian-gnu-linux/9msvkqc78pk6?activetab=pivot%3Aoverviewtab) from the Microsoft Store.
        - Run, let it finish installing, configure your username and password.
        - Then you will need to update apt, upgrade existing packages, and then install git:
            - ` $ sudo apt-get update ; sudo apt-get upgrade -y ; sudo apt-get install git -y`
    1. With your WLinux (or configured/updated Debian) distro in place, execute the following:
        - ` $ git clone https://github.com/sirredbeard/WLinux.git `
        - ` $ cd WLinux`
        - ` $ chmod u+x create-targz.sh`
        - ` $ ./create-targz.sh`
    1. You should find an install.tar.gz in the /x64/ directory of your build directory. (When we get ARM64 support working there will also be an install.tar.gz in a /ARM64/ directory.)
1. Build the solution to make sure you have everything you need. Fix any build dependencies you are missing.
1. Build the Windows UWP package:
    1. Open a `Developer Command Prompt for VS 2017` and change directory to your build directory.
    1. Run `build.bat`

1. If everything has gone correctly, you should find your app package in a subfolder under the `AppPackages\DistroLauncher-Appx` folder.
    1. First, install the certificate:
	    1. Double-click on the security certificate file.
		1. Click the "Install Certificate" button.
		1. Select "Local Machine" for the store location.
		1. Select "Automatically select the certificate store based on the type of certificate", then click Next. (If you have any certificate issues, try specifying the Root Certificate Authority Trust here.)
		1. Proceed through the rest of the wizard, clicking Next, Finish, OK, and then OK.
    1. Once that's done, you should be able to double-click on the .appx package file and install it.

## Usage
The launcher app provides the following functionality:

* `wlinux.exe`
  - Launches the user's default shell in the user's home directory.

* `wlinux.exe install [--root]`
  - Install the distribution and do not launch the shell when complete.
    - `--root`: Do not create a user account and leave the default user set to root.

* `wlinux.exe run <command line>`
  - Run the provided command line in the current working directory. If no command line is provided, the default shell is launched.
  - Everything after `run` is passed to WslLaunchInteractive.

* `wlinux.exe config [setting [value]]`
  - Configure settings for this distribution.
  - Settings:
    - `--default-user <username>`: Sets the default user to <username>. This must be an existing user.

* `wlinux.exe help`
  - Print usage information.

# Related Pages

- [Awesome WSL](https://github.com/sirredbeard/Awesome-WSL)
- [Awesome UNIX](https://github.com/sirredbeard/Awesome-UNIX)

# Intellectual Property

See [LICENSE.md](https://github.com/sirredbeard/WLinux/blob/master/LICENSE.md).
