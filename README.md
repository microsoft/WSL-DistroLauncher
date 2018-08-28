# WLinux

A Linux® distribution optimized for WSL based on Debian® stable from Whitewater Foundry, Ltd. Co.

## Features

- Optimized for use with Windows® Subsystem for Linux (WSL) on Windows 10 Version 1709+.
- Out-of-the-box support for external Windows-based X clients, such as [X410](https://www.microsoft.com/store/productId/9NLP712ZMN9Q).
- Popular programming tools, including git and python3, are pre-installed. Additional packages can be easily installed via the apt package management system from the expansive Debian repos.
- Ships with useful utilities for running Linux on WSL installable with one command.
- A handful of unnecessary packages, such as systemd, have been removed to improve stability and security.
- Scripts to easily install the following popular applications:
    - Visual Studio Code `$ sudo /opt/installcode.sh`
    - Google Chrome `$ sudo /opt/installchrome.sh`
    - [wslu](https://github.com/patrick330602/wslu) `$ sudo /opt/installwslu.sh`
    
## Background

WLinux is a Linux distribution ("distro") optimized for use on Windows Subsystem for Linux ("WSL"). While other distros are available for WSL, this is the first Linux distro specifically designed for use on WSL. A number of enhancements are enabled by default and additional improvements are planned. WLinux is open-source and based on the stable Debian GNU/Linux distro. Development occurs on GitHub. Pull requests, forks, and issues are welcome. A paid version is planned for the Microsoft Store to fund future development.

Note: There are no .iso or .img files available for WLinux.

## Support

### General

See [Awesome WSL](https://github.com/sirredbeard/Awesome-WSL) for a comprehensive overview of the Windows Subsystem for Linux feature in Windows 10.

### Help

Support is handled via the GitHub project issues page. First search for your issue [here](https://github.com/sirredbeard/WLinux/issues). If you are unable to find your answer, please open a new issue [here](https://github.com/sirredbeard/WLinux/issues/new).

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



# Related Pages

- [Awesome WSL](https://github.com/sirredbeard/Awesome-WSL)
- [Awesome UNIX](https://github.com/sirredbeard/Awesome-UNIX)

# Intellectual Property

See [LICENSE.md](https://github.com/sirredbeard/WLinux/blob/master/LICENSE.md).
