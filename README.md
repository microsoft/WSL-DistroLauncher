# WLinux

The first Linux® distribution optimized for WSL. Based on Debian®.

From open-source software startup [Whitewater Foundry](https://whitewaterfoundry.com
).

WLinux can be downloaded from the [Microsoft Store](https://afflnk.microsoft.com/c/1291904/433017/7593?u=https%3A%2F%2Fwww.microsoft.com%2Fstore%2FproductId%2F9NV1GV1PXZ6P).

**Read in other languages: [简体中文](README.zh-hans.md) [繁體中文](README.zh-hant.md) [日本語](README.ja.md)**

## Features

- A fast Linux terminal and development environment for developers and pro-users built on [Windows® Subsystem for Linux](https://github.com/sirredbeard/Awesome-WSL) (WSL) on Windows 10.
- A new out-of-the-box experience for users to get started on the Linux terminal.
- Choice of terminal shells: bash, csh, zsh (with oh-my-zsh), and fish (with oh-my-fish).
- Choice of editors: emacs, neovim, nano, and Visual Studio Code.
- Choice of development environments: nodejs (with n, npm, and/or yarn), python 3.7 (and pip), ruby (via rbenv), and go.
- Choice of cloud and administration tools: PowerShell and Azure-CLI.
- Ships with [wslu](https://github.com/wslutilities/wslu), a set of useful open-source utilities for interacting between WSL and Windows 10.
- Optional Windows Explorer shell integration and support for HiDPI displays.
- Support for [many Linux graphical apps](https://github.com/ethanhs/WSL-Programs) with no need to configure display or libGL settings. Requires a Windows-based X client, such as [X410](http://afflnk.microsoft.com/c/1291904/459838/7593?prodsku=9NLP712ZMN9Q&u=https%3A%2F%2Fwww.microsoft.com%2Fen-us%2Fstore%2Fp%2Fx410%2F9NLP712ZMN9Q).
- Additional packages can be easily installed via the apt package management system from the [expansive Debian repos](https://packages.debian.org/stable/) and third-party apt-based repos.
- A handful of unnecessary packages, such as systemd, have been are removed from the base image to reduce size and increase stability.
- New features are [actively developed](https://github.com/WhitewaterFoundry/WLinux/pulls) based on [community interest](https://github.com/WhitewaterFoundry/WLinux/issues).
- WLinux features faster patching for WSL-specific bugs than any upstream Linux distro on WSL.
- WLinux users can run `$ wlinux-setup` at any time to get access to latest WLinux features and customizations for WSL.

Note: The features above refer to the current GitHub version slated for release as 1.1.21 on the Microsoft Store in October. Build WLinux yourself and help us test and debug new features. 

## Obtaining Support

- First, search for your issue [here](https://github.com/whitewaterfoundry/WLinux/issues).
- Next, search for your issue [here](https://github.com/Microsoft/WSL/issues).
- Then consult [Troubleshooting Windows Subsystem for Linux](https://docs.microsoft.com/en-us/windows/wsl/troubleshooting) - Microsoft official docs.
- Only then, if you are unable to find your answer, please open a new issue [here](https://github.com/sirredbeard/WLinux/issues/new).

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
