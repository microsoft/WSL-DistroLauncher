# WLinux

由[Whitewater Foundry](https://whitewaterfoundry.com)出品，基於Debian®, 專門爲Windows 10 Linux® 子系統調整的 Linux® 發行版。

WLinux 可以從[微軟商店](https://afflnk.microsoft.com/c/1291904/433017/7593?u=https%3A%2F%2Fwww.microsoft.com%2Fstore%2FproductId%2F9NV1GV1PXZ6P)下載.

**其他語言版本： [English](EADME.md) [简体中文](README.zh-hans.md) [日本語](README.ja.md)**

## 功能

- 一款專門為開發者和資深使用者設計的在[Windows 10 Linux 子系統](https://github.com/sirredbeard/Awesome-WSL)(WSL)上使用的Linux開發環境。
- 開箱即用的GUI支援！注：需要安裝Windows下的X伺服器，如[X410](http://afflnk.microsoft.com/c/1291904/459838/7593?prodsku=9NLP712ZMN9Q&u=https%3A%2F%2Fwww.microsoft.com%2Fen-us%2Fstore%2Fp%2Fx410%2F9NLP712ZMN9Q)。
- 內建常用命令列和開發工具，如zsh，git，neovim，python可在第一次執行一鍵安裝。其他的工具和包可以使用apt和我們內建的[擴充套件Debian包伺服器](https://packages.debian.org/stable/)和第三方包伺服器，例如用`$ sudo apt install nodejs`一鍵安裝nodejs。`Debian backports`和`Debian Testing`包伺服器也進行了內部配置。
- 預裝[wslu](https://github.com/patrick330602/wslu)，一個為WSL而設計的工具包（我其實就是wslu開發者哈哈哈哈）。
- 預裝[n](https://github.com/tj/n)，一款nodejs版本管理器。
- 一些不必要或者不支援的應用如`systemd`已被移除。
- 新功能會不斷的新增，包括我們的[功能&Bug賞金計劃](https://github.com/WhitewaterFoundry/WLinux/issues?q=is%3Aissue+is%3Aopen+label%3ABounty)。
- WLinux提供更快的Bug修復。
- WLinux使用者可以隨時執行/etc/setup獲取最新功能。
    
## 背景

WLinux是一款基於Debian®, 專門爲Windows 10 Linux 子系統調整的 Linux® 發行版。縱然其他發行版也有提供Linux® 子系統版本，這是第一款專門爲Windows 10 Linux 子系統調整的 Linux® 發行版。 一些爲WSL做出的調整已經啓用，新功能也在計劃中。WLinux是一款基於穩定版Debian GNU/Linux的開源系統，於GitHub開源。歡迎開PR，Issue或者fork本項目。欲瞭解更多，請看[此](https://whitewaterfoundry.com/)。

## 支持

**[Official WLinux Wiki](https://github.com/WhitewaterFoundry/WLinux/wiki)**

請首先查看官方Wiki瞭解更多。

**Twitter**: [@WLinuxApp](https://twitter.com/WLinuxApp)

**Telegram**: [WSLinux](https://t.me/wslinux)

**GitHub**: 請先[在此](https://github.com/sirredbeard/WLinux/issues)搜索你的問題。如果你無法找到你的問題，請[開一個新的issue](https://github.com/sirredbeard/WLinux/issues/new)。

## 其他文檔

- [LICENSE.md](https://github.com/sirredbeard/WLinux/blob/master/LICENSE.md)
- [BUILDING.md](https://github.com/WhitewaterFoundry/WLinux/blob/master/BUILDING.md)
- [PRIVACY.md](https://github.com/WhitewaterFoundry/WLinux/blob/master/PRIVACY.md)
- [ROADMAP.md](https://github.com/WhitewaterFoundry/WLinux/blob/master/ROADMAP.md)
- [CONTRIBUTING.md](https://github.com/WhitewaterFoundry/WLinux/blob/master/CONTRIBUTING.md)

## 相關界面

- [Awesome Windows Subsystem for Linux](https://github.com/sirredbeard/Awesome-WSL)
- [Awesome UNIX](https://github.com/sirredbeard/Awesome-UNIX)
