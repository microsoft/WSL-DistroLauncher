# WLinux

由[Whitewater Foundry](https://whitewaterfoundry.com)出品，基于Debian®, 专门为Windows 10 Linux® 子系统调整的 Linux® 发行版。

WLinux 可以从[微软商店](https://afflnk.microsoft.com/c/1291904/433017/7593?u=https%3A%2F%2Fwww.microsoft.com%2Fstore%2FproductId%2F9NV1GV1PXZ6P)下载.

*其他语言版本： [English](EADME.md)　[繁體中文](README.zh-hant.md) [日本語](README.ja.md)*

## 功能

- 一款专门为开发者和资深用户设计的在[Windows 10 Linux 子系统](https://github.com/sirredbeard/Awesome-WSL)(WSL)上运行的Linux开发环境。
- 开箱即用的GUI支持！注：需要安装Windows下的X服务器，如[X410](http://afflnk.microsoft.com/c/1291904/459838/7593?prodsku=9NLP712ZMN9Q&u=https%3A%2F%2Fwww.microsoft.com%2Fen-us%2Fstore%2Fp%2Fx410%2F9NLP712ZMN9Q)。
- 内置常用命令行和开发工具，如zsh，git，neovim，python可在第一次运行一键安装。其他的工具和包可以使用apt和我们内置的[扩展Debian包服务器](https://packages.debian.org/stable/)和第三方包服务器，例如用`$ sudo apt install nodejs`一键安装nodejs。`Debian backports`和`Debian Testing`包服务器也进行了内部配置。
- 预装[wslu](https://github.com/patrick330602/wslu)，一个为WSL而设计的工具包（我其实就是wslu开发者哈哈哈哈）。
- 一些不必要或者不支持的应用如`systemd`已被移除。
- 新功能会不断的添加，包括我们的[功能&Bug赏金计划](https://github.com/WhitewaterFoundry/WLinux/issues?q=is%3Aissue+is%3Aopen+label%3ABounty)。
- WLinux提供更快的Bug修复。
- WLinux用户可以随时运行/etc/setup获取最新功能。
    
## 背景

WLinux是一款基于Debian®, 专门为Windows 10 Linux 子系统调整的 Linux® 发行版。纵然其他发行版也有提供Linux® 子系统版本，这是第一款专门为Windows 10 Linux 子系统调整的 Linux® 发行版。 一些为WSL做出的调整已经启用，新功能也在计划中。WLinux是一款基于稳定版Debian GNU/Linux的开源系统，于GitHub开源。欢迎开PR，Issue或者fork本项目。欲了解更多，请看[此](https://whitewaterfoundry.com/)。

## 支持

**[Official WLinux Wiki](https://github.com/WhitewaterFoundry/WLinux/wiki)**

请首先查看官方Wiki一了解更多。

**Twitter**: [@WLinuxApp](https://twitter.com/WLinuxApp)

**Telegram**: [WSLinux](https://t.me/wslinux)

**GitHub**: 请先[在此](https://github.com/sirredbeard/WLinux/issues)搜索你的问题。如果你无法找到你的问题，请[开一个新的issue](https://github.com/sirredbeard/WLinux/issues/new)。

## 其他文档

- [LICENSE.md](https://github.com/sirredbeard/WLinux/blob/master/LICENSE.md)
- [BUILDING.md](https://github.com/WhitewaterFoundry/WLinux/blob/master/BUILDING.md)
- [PRIVACY.md](https://github.com/WhitewaterFoundry/WLinux/blob/master/PRIVACY.md)
- [ROADMAP.md](https://github.com/WhitewaterFoundry/WLinux/blob/master/ROADMAP.md)
- [CONTRIBUTING.md](https://github.com/WhitewaterFoundry/WLinux/blob/master/CONTRIBUTING.md)

## 相关界面

- [Awesome Windows Subsystem for Linux](https://github.com/sirredbeard/Awesome-WSL)
- [Awesome UNIX](https://github.com/sirredbeard/Awesome-UNIX)
