# WLinux

The first Linux® distribution optimized for WSL. Based on Debian®.

From open-source software startup [Whitewater Foundry](https://whitewaterfoundry.com
).

WLinux can be downloaded from the [Microsoft Store](https://afflnk.microsoft.com/c/1291904/433017/7593?u=https%3A%2F%2Fwww.microsoft.com%2Fstore%2FproductId%2F9NV1GV1PXZ6P).

**Read in other languages: [简体中文](README.zh-hans.md) [繁體中文](README.zh-hant.md) [日本語](README.ja.md)**

## Features

- WLinux is a Linux environment for Windows 10 built on work by Microsoft Research and the Debian project.
- The first Linux distribution pre-configured and optimized to run specifically on [Windows® Subsystem for Linux](https://github.com/sirredbeard/Awesome-WSL), a Microsoft-supported feature of Windows 10 and Windows Server 2019.
- Includes [wslu](https://github.com/wslutilities/wslu), a set of useful open-source utilities for interacting between WSL and Windows 10.
- A custom wlinux-setup tool allows new WLinux users to get started on Linux immediately:
    - Language settings.
    - Choice of terminal shells: bash, csh, zsh (with [oh-my-zsh](https://ohmyz.sh/)), and [fish](https://fishshell.com/) (with [oh-my-fish](https://github.com/oh-my-fish/oh-my-fish)).
    - Choice of text editors: [emacs](https://www.gnu.org/software/emacs/), [neovim](https://neovim.io/), and [Visual Studio Code](https://code.visualstudio.com/).
    - Choice of development environments: [NodeJS](https://nodejs.org/) (with n, npm, and/or yarn), Python 3.7 (and pip), [Ruby](http://www.ruby-lang.org/) (via rbenv), and [Go](https://golang.org/).
    - Choice of cloud and administration tools: [PowerShell](https://github.com/PowerShell/PowerShell) and [azure-cli](https://github.com/Azure/azure-cli) tools for Azure.
    - Enable/disable Windows Explorer shell integration.
    - Configure experimental GUI settings, including HiDPI support and international input methods.
- Support for [many Linux graphical applications](https://github.com/ethanhs/WSL-Programs) with no need to configure display or libGL in Wlinux. (Requires a Windows-based X client, such as [X410](http://afflnk.microsoft.com/c/1291904/459838/7593?prodsku=9NLP712ZMN9Q&u=https%3A%2F%2Fwww.microsoft.com%2Fen-us%2Fstore%2Fp%2Fx410%2F9NLP712ZMN9Q).)
- Install over 25,353 open source packages via the apt package management system from the [expansive Debian repositories](https://packages.debian.org/stable/) and any third-party Debian-compatible repositories from outside projects.
- A handful of unnecessary packages, such as systemd, have been removed from the base image to reduce image size and increase stability.
- New features are [actively developed](https://github.com/WhitewaterFoundry/WLinux/pulls) based on [community input](https://github.com/WhitewaterFoundry/WLinux/issues).
- WLinux provides faster patching for WSL-specific bugs than any upstream Linux distro available on WSL.

Note: The features above refer to the version slated for release as 1.1.23 on the Microsoft Store in late October. Build WLinux yourself and help us test and debug new features. 

## Obtaining Support

- First, search for your issue on the WLinux Issues page [here](https://github.com/whitewaterfoundry/WLinux/issues).
- Next, search for your issue on the general WSL Issues page [here](https://github.com/Microsoft/WSL/issues).
- Then consult the official [Troubleshooting Windows Subsystem for Linux](https://docs.microsoft.com/en-us/windows/wsl/troubleshooting) documentation.
- Finally, if you are still unable to resolve your issue, please submit a bug report [here](https://github.com/WhitewaterFoundry/WLinux/issues/new?template=bug_report.md).

## Additional Documentation

- [LICENSE.md](LICENSE.md)
- [BUILDING.md](BUILDING.md)
- [PRIVACY.md](PRIVACY.md)
- [ROADMAP.md](ROADMAP.md)
- [CONTRIBUTING.md](CONTRIBUTING.md)

## Related Pages

- [Awesome Windows Subsystem for Linux](https://github.com/sirredbeard/Awesome-WSL)
- [Awesome UNIX](https://github.com/sirredbeard/Awesome-UNIX)
- [wslutilities](https://github.com/wslutilities/wslu)

## Credits

- [Hayden Barnes](https://github.com/sirredbeard)
- [Patrick Wu](https://github.com/patrick330602)
