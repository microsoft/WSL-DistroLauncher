# WLinux

The first Linux® distribution optimized for WSL.

Based on Debian®.

From open-source software startup [Whitewater Foundry](https://whitewaterfoundry.com
).

WLinux can be downloaded from the [Microsoft Store](https://afflnk.microsoft.com/c/1291904/433017/7593?u=https%3A%2F%2Fwww.microsoft.com%2Fstore%2FproductId%2F9NV1GV1PXZ6P).

**Read in other languages: [简体中文](README.zh-hans.md) [繁體中文](README.zh-han.md) [日本語](README.ja.md)**

## Features

- A fast Linux terminal and development environment for developers and pro-users built on [Windows® Subsystem for Linux](https://github.com/sirredbeard/Awesome-WSL) (WSL) on Windows 10.
- Support for most Linux graphical apps with no need to configure display or libGL settings. Requires a Windows-based X client, such as [X410](http://afflnk.microsoft.com/c/1291904/459838/7593?prodsku=9NLP712ZMN9Q&u=https%3A%2F%2Fwww.microsoft.com%2Fen-us%2Fstore%2Fp%2Fx410%2F9NLP712ZMN9Q).
- Support for optional HiDPI configuration.
- Optional Windows Explorer shell integration.
- Choice of terminal shells: bash, csh, zsh (with oh-my-zsh), and fish (with oh-my-fish).
- Choice of editors: emacs, neovim, nano, and Visual Studio Code.
- Optional packages: PowerShell, Azure tools, and Google Chrome.
- Pre-installed with [wslu](https://github.com/patrick330602/wslu), a set of useful open-source utilities for interacting between WSL and Windows 10.
- Additional packages can be easily installed via the apt package management system (e.g. `$ sudo apt install nodejs`) from the [expansive Debian repos](https://packages.debian.org/stable/) and third-party Debian-compatible repos.
- A handful of unnecessary packages on WSL, such as systemd, have been removed to improve stability and security.
- New features are actively added based on community interest, including [bug bounties](https://github.com/WhitewaterFoundry/WLinux/issues?q=is%3Aissue+is%3Aopen+label%3ABounty).
- WLinux offers faster patching for WSL-specific bugs than any upstream Linux distro on WSL.
- WLinux users can re-run `$ bash /etc/setup` at any time to get access to latest WLinux features and customizations for WSL.

Note: The features above refer to the current GitHub version slated for release as 1.1.20 on the Store in early October. Build WLinux yourself and help us test and debug new features. 

## Obtaining Support

**[Official WLinux Wiki](https://github.com/WhitewaterFoundry/WLinux/wiki)**

Please check the Wiki first. It has a guide for getting started, guides for installing packages, and more.

**GitHub**: First search for your issue [here](https://github.com/sirredbeard/WLinux/issues). If you are unable to find your answer, please open a new issue [here](https://github.com/sirredbeard/WLinux/issues/new).

## Additional Documentation

- [LICENSE.md](LICENSE.md)
- [BUILDING.md](BUILDING.md)
- [PRIVACY.md](PRIVACY.md)
- [ROADMAP.md](ROADMAP.md)
- [CONTRIBUTING.md](CONTRIBUTING.md)

## Related Pages

- [Awesome Windows Subsystem for Linux](https://github.com/sirredbeard/Awesome-WSL)
- [Awesome UNIX](https://github.com/sirredbeard/Awesome-UNIX)
