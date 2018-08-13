# Xebian

A Linux distro optimized for WSL based on Debian stable.

- Optimized for use with Windows Subsystem for Linux on Windows 10.
- Out-of-the-box support for external X clients, e.g. [X410](https://www.microsoft.com/store/productId/9NLP712ZMN9Q).
- Several useful packages pre-installed, including git and python3.
- Easily install:
    - Visual Studio Code `$ installcode.sh`
    - Google Chrome `$ installchrome.sh`

## Background

Xebian is a community Linux distro optimized for use on Windows Subsystem for Linux (WSL). While other distros are availablw for WSL, this is the first Linux distro specifically intended for use on WSL. A number of enhancements are enabled by default and additional suggestions are welcome.

Xebian is open-source. Development occurs on GitHub. Pull requests, forks, and issue reports are welcomed. A paid version of Xebian is planned for the Microsoft Store to support ongoing development.

Note: There are no .iso or .img files available for Xebian, only a tar.gz image for use on Windows Subsystem for Linux.

## Naming

Xebian is a portmanteau of [Xenix](https://en.wikipedia.org/wiki/Xenix), a version of UNIX® distributed by Microsoft, and [Debian](https://www.debian.org/)®, the Linux distro upon which Xebian is based.

NOTE: Xebian is not endorsed by the Debian Project or Microsoft.

## Components

- create-targz.sh - Builds custom Linux distro in a Debian environment.
- Launcher - Builds the actual executable that is run when a user launches the app.
- DistroLauncher-Appx - Builds the distro package with all the correctly scaled assets and other dependencies.

Read more about the components [here](https://github.com/Microsoft/WSL-DistroLauncher). 

----

- UNIX® is a trademark of The Open Group.
- Debian® is a registered trademark of Software in the Public Interest, Inc.
- Microsoft®, Microsoft Store®, Windows 10®, Visual Studio®, and Xenix® are trademarks or registered trademarks of Microsoft Corporation.
- Linux® is a registered trademark of Linus Torvalds.
- Chrome™ is a registered trademarks of Alphabet, Inc.