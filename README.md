# WLinux

A Linux distribution optimized for WSL based on Debian stable.

**Warning**: Project is incomplete. See [Project Progress](https://github.com/sirredbeard/WLinux#project-progress).

## Features Overview

- Optimized for use with Windows Subsystem for Linux on Windows 10.
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

WLinux is a Linux distro optimized for use on Windows Subsystem for Linux (WSL). While other distros are available for WSL, this is the first Linux distro specifically designed for use on WSL. A number of enhancements are enabled by default and additional improvements are planned. WLinux is open-source and based on the stable Debian release. Development occurs on GitHub. Pull requests, forks, and issue reports are welcomed.

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

To Do Before 1.0:

    - Complete Windows UWP app containerization/workout package build errors.
    - Add custom branding assets.

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

## Related Pages

- [Awesome WSL](https://github.com/sirredbeard/Awesome-WSL)
- [Awesome UNIX](https://github.com/sirredbeard/Awesome-UNIX)

## Intellectual Property Compliance

- [Licensed](https://github.com/sirredbeard/WLinux/blob/master/LICENSE) under the MIT license.
- UNIX® is a trademark of The Open Group.
- Debian® is a registered trademark of Software in the Public Interest, Inc.
- Microsoft®, Microsoft Store®, Windows 10®, Visual Studio®, and Xenix® are trademarks or registered trademarks of Microsoft Corporation.
- Linux® is a registered trademark of Linus Torvalds.
- Chrome™ is a registered trademarks of Alphabet, Inc.
