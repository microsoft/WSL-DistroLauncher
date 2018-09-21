# WLinux

A Linux® distribution optimized for WSL based on Debian® stable from open-source software startup [Whitewater Foundry](https://whitewaterfoundry.com
).

WLinux can be downloaded from the [Microsoft Store](https://afflnk.microsoft.com/c/1291904/433017/7593?u=https%3A%2F%2Fwww.microsoft.com%2Fstore%2FproductId%2F9NV1GV1PXZ6P).

## Features

- A fast Linux terminal and development environment for developers and pro-users built on [Windows® Subsystem for Linux](https://github.com/sirredbeard/Awesome-WSL) (WSL) on Windows 10.
- Out-of-the-box support for most Linux graphical apps with no need to configure display or libGL settings. Note: Requires a Windows-based X client, such as [X410](http://afflnk.microsoft.com/c/1291904/459838/7593?prodsku=9NLP712ZMN9Q&u=https%3A%2F%2Fwww.microsoft.com%2Fen-us%2Fstore%2Fp%2Fx410%2F9NLP712ZMN9Q).
- Popular development tools, including zsh shell, git, and python 3.7, are pre-installed. Additional packages can be easily installed via the apt package management system (e.g. `$ sudo apt install nodejs`) from the [expansive Debian repos](https://packages.debian.org/stable/) and third-party Debian-compatible repos. The Debian backports repo is pre-configured.
- Pre-installed with [wslu](https://github.com/patrick330602/wslu), a set of useful open-source utilities for interacting between WSL and Windows 10.
- A handful of unnecessary packages, such as systemd, have been removed to improve stability and security.
- Additional scripts to easily install the following popular applications:
    - Visual Studio Code `$ sudo /opt/installcode.sh`
    - Google Chrome `$ sudo /opt/installchrome.sh`
    - Think another app needs to be here? File a [feature request](https://github.com/WhitewaterFoundry/WLinux/issues/new/choose) and state your case.
- New features are actively added based on community interest, including [paid bug and feature bounties](https://github.com/WhitewaterFoundry/WLinux/issues?q=is%3Aissue+is%3Aopen+label%3ABounty).
- WLinux offers faster patching than any upstream Linux distro for WSL-specific bugs.
    
## Background

WLinux is a Linux distribution optimized for use on Windows Subsystem for Linux. While other distros are available for WSL, this is the first distro specifically customized for use on WSL. A number of WSL-specific enhancements are enabled by default and additional features are planned. WLinux is open-source and based on the stable Debian GNU/Linux distro. Development occurs on GitHub. Pull requests, forks, and new issue reports are welcome. For more background, see [here](https://whitewaterfoundry.com/). 

## Support

**[Official WLinux Wiki](https://github.com/WhitewaterFoundry/WLinux/wiki)**

Please check the Wiki first. It has a guide for getting started, installing packages, and more.

**Twitter**: [@WLinuxApp](https://twitter.com/WLinuxApp)

**Telegram**: [WSLinux](https://t.me/wslinux)

**GitHub**: First search for your issue [here](https://github.com/sirredbeard/WLinux/issues). If you are unable to find your answer, please open a new issue [here](https://github.com/sirredbeard/WLinux/issues/new).

## Additional Documentation

- [LICENSE.md](https://github.com/sirredbeard/WLinux/blob/master/LICENSE.md)
- [BUILDING.md](https://github.com/WhitewaterFoundry/WLinux/blob/master/BUILDING.md)
- [PRIVACY.md](https://github.com/WhitewaterFoundry/WLinux/blob/master/PRIVACY.md)
- [ROADMAP.md](https://github.com/WhitewaterFoundry/WLinux/blob/master/ROADMAP.md)
- [CONTRIBUTING.md](https://github.com/WhitewaterFoundry/WLinux/blob/master/CONTRIBUTING.md)

## Related Pages

- [Awesome Windows Subsystem for Linux](https://github.com/sirredbeard/Awesome-WSL)
- [Awesome UNIX](https://github.com/sirredbeard/Awesome-UNIX)
