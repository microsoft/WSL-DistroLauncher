# WLinux

<img src="https://github.com/sirredbeard/WLinux/blob/master/DistroLauncher-Appx/Assets/large%20logo.scale-100.png" height=15% width=15%>

A Linux distribution optimized for WSL based on Debian stable.

## Features Overview

- Optimized for use with Windows Subsystem for Linux (WSL) on Windows 10.
- Out-of-the-box support for external Windows X clients, such as [X410](https://www.microsoft.com/store/productId/9NLP712ZMN9Q).
- Popular programming tools, including git and python3, pre-installed. Additional packages can be easily installed via the apt package management system from expansive Debian repos.
- Ships with useful utilities for running Linux on WSL installable with one command.
- A handful of unnecessary packages, such as systemd, have been removed from WLinux to improve stability and security.
- Scripts to easily install the following popular applications:
    - Visual Studio Code `$ sudo /opt/installcode.sh`
    - Google Chrome `$ sudo /opt/installchrome.sh`
    - [wslu](https://github.com/patrick330602/wslu) `$ sudo /opt/installwslu.sh`

## User Support

### WSL Resources

See [Awesome WSL](https://github.com/sirredbeard/Awesome-WSL) for a comprehensive overview of WSL.

### Getting Help 

First search for your issue [here](https://github.com/sirredbeard/WLinux/issues). If you are unable to find help, please open an issue [here](https://github.com/sirredbeard/WLinux/issues/new).

## Background

WLinux is a Linux distro optimized for use on Windows Subsystem for Linux (WSL). While other distros are available for WSL, this is the first Linux distro specifically designed for use on WSL. A number of enhancements are enabled by default and additional improvements are planned. WLinux is open-source and based on the stable Debian Linux distro. Development occurs on GitHub. Pull requests, forks, and issues are welcome. A paid version is planned for the Microsoft Store to fund future development.

Note: There are no .iso or .img files available for WLinux.

## Project Progress

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
    - Add custom branding assets.
    - Complete Windows UWP app containerization/workout package build errors.

To Do Before 1.0:

    - Additional testing.

Planned For 1.1:

    - ARM64 support.
    - Additional third-party app install scripts:
        - Oracle Java
        - Anaconda Python Distribution

## Project Components

- create-targz.sh - Builds the WLinux custom Linux distro in a WLinux or Debian environment. **Status:** Working.
    - Sample [install.tar.gz](https://1drv.ms/u/s!AspPK83V8Sf2g5pWRkGIYRFmAN7bIQ) built on 8/14/18.
- Launcher project - Builds the actual executable that is run when a user launches the app. 
- DistroLauncher-Appx project - Builds the distro package with all the assets and other dependencies.

Read more about the components [here](https://github.com/Microsoft/WSL-DistroLauncher). 

## Requirements for building
This project can be built using Visual Studio Community 2017. The "Universal Windows Platform development" feature is required, along with the following subfeatures:

* C++ Universal Windows Platform tools
* Windows 10 SDK (10.0.16299.0) for UWP: C#, VB, JS

## Requirements for installing and running 
The system must be in Developer mode (found in Settings -> Update & Security -> For developers)

The Windows Subsystem for Linux is not enabled by default, and is required to run the app. You can add the feature to your Windows installation by running `C:\Windows\System32\OptionalFeatures.exe` and selecting it from the list.

## Building
- Open DistroLauncher.sln in Visual Studio.
- Generate a test certificate:
    - In the Solution Explorer, open `DistroLauncher-Appx\Gentoo.appxmanifest`
    - Select the Packaging tab
    - Select "Choose Certificate"
    - Click the Configure Certificate drop down and select Create test certificate.
- Build install.tar.gz by cloning the repo to an existing WLinux or Debian image, `$ chmod u+x create-targz.sh`, then ./create-targz.sh.
- Build the package:
    - Open a `Developer Command Prompt for VS 2017` and change directory to the project root.
    - Run `build.bat`
- If everything has gone right, you should find your app package in a subfolder under the `AppPackages\Gentoo-Appx` folder.
    1. First, install the certificate:
	    1. Double-click on the security certificate file.
		1. Click the Install Certificate button.
		1. Select Local Machine for the store location.
		1. Select "Automatically select the certificate store based on the type of certificate", then click Next.
		1. Proceed through the rest of the wizard, clicking Next, Finish, OK, and then OK.
	1. Once that's done, you should be able to double-click on the .appx package file and install it.

## Usage
The launcher provides the following functionality:

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

## Related Pages

- [Awesome WSL](https://github.com/sirredbeard/Awesome-WSL)
- [Awesome UNIX](https://github.com/sirredbeard/Awesome-UNIX)

## Intellectual Property Compliance

- [Licensed](https://github.com/sirredbeard/WLinux/blob/master/LICENSE) under the MIT license.
- [Icons](https://www.iconfinder.com/icons/652577/linux_os_penguin_platform_server_system_icon) by [Erik Ragnar Eliasson](http://www.erikeliasson.io/).
- UNIX® is a trademark of The Open Group.
- Debian® is a registered trademark of Software in the Public Interest, Inc.
- Microsoft®, Microsoft Store®, Windows 10®, Visual Studio®, and Xenix® are trademarks or registered trademarks of Microsoft Corporation.
- Linux® is a registered trademark of Linus Torvalds.
- Chrome™ is a registered trademark of Alphabet, Inc.
