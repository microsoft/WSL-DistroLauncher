# WLinux

A Linux® distribution optimized for WSL based on Debian® stable from Whitewater Foundry.

## Features

- Optimized for use with [Windows® Subsystem for Linux](https://github.com/sirredbeard/Awesome-WSL) (WSL) on Windows 10 Version 1709+.
- Out-of-the-box support for external Windows-based X clients, such as [X410](http://afflnk.microsoft.com/c/1291904/459838/7593?prodsku=9NLP712ZMN9Q&u=https%3A%2F%2Fwww.microsoft.com%2Fen-us%2Fstore%2Fp%2Fx410%2F9NLP712ZMN9Q), no need to set DISPLAY or LIBGL settings.
- Popular programming tools, including git and python3, are pre-installed. Additional packages can be easily installed via the apt package management system from the [expansive Debian repos](https://packages.debian.org/stable/).
- A handful of unnecessary packages, such as systemd, have been removed to improve stability and security.
- Install [wslu](https://github.com/patrick330602/wslu), a set of useful utilities for running Linux on WSL, with one command.
- Additional scripts to easily install the following popular applications:
    - Visual Studio Code `$ sudo /opt/installcode.sh`
    - Google Chrome `$ sudo /opt/installchrome.sh`
    - Think another app needs to be here? File a [feature request](https://github.com/WhitewaterFoundry/WLinux/issues/new/choose).
- New features are actively added based on community demand, including [paid bug and feature bounties](https://github.com/WhitewaterFoundry/WLinux/issues?q=is%3Aissue+is%3Aopen+label%3ABounty).
- Faster patching than any upstream Linux distro for WSL-specific bugs.
    
## Background

WLinux is a Linux distribution optimized for use on Windows Subsystem for Linux. While other distros are available for WSL, this is the first distro specifically customized for use on WSL. A number of WSL-specific enhancements are enabled by default and additional features are planned. WLinux is open-source and based on the stable Debian GNU/Linux distro. Development occurs on GitHub. Pull requests, forks, and new issue reports are welcome. A paid version is planned for the Microsoft Store to fund future development, including bug/feature bounties.

## Support

**[Wiki](https://github.com/WhitewaterFoundry/WLinux/wiki)**

Please check the Wiki first. It has a guide for getting started, installing packages, and more.

**Twitter**: [@WhitewaterFndry](https://twitter.com/WhitewaterFndry)

**Telegram**: [WSLinux](https://t.me/wslinux)

**GitHub**: First search for your issue [here](https://github.com/sirredbeard/WLinux/issues). If you are unable to find your answer, please open a new issue [here](https://github.com/sirredbeard/WLinux/issues/new).

## Additional Documentation

- [LICENSE.md](https://github.com/sirredbeard/WLinux/blob/master/LICENSE.md)
- [BUILDING.md](https://github.com/WhitewaterFoundry/WLinux/blob/master/BUILDING.md)
- [PRIVACY.md](https://github.com/WhitewaterFoundry/WLinux/blob/master/PRIVACY.md)
- [CONTRIBUTING.md](https://github.com/WhitewaterFoundry/WLinux/blob/master/CONTRIBUTING.md)

## Related Pages

- [Awesome Windows Subsystem for Linux](https://github.com/sirredbeard/Awesome-WSL)
- [Awesome UNIX](https://github.com/sirredbeard/Awesome-UNIX)
