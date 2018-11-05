# WLinux

專門為Windows 10 Linux® 子系統調整的 Linux® 發行版，基於Debian®，由[Whitewater Foundry](https://whitewaterfoundry.com)出品。

<a href='//www.microsoft.com/store/apps/9NV1GV1PXZ6P?ocid=badge'><img src='https://assets.windowsphone.com/e34f1ae1-fe0c-4fbc-afe6-3bd495fff1b9/Chinese-Traditional_get-it-from-MS_InvariantCulture_Default.png' alt='Chinese Traditional badge'/></a>

- [English](EADME.md)
- [簡體中文](README.zh-hans.md)
- [日本語](README.ja.md)

## 功能

- WLinux是第一款使用Microsoft Research開源技術基於Debian發行版的Windows 10上的發行版。
- WLinux是第一款專門為開發者和資深使用者設計的在[Windows 10 Linux 子系統](https://github.com/sirredbeard/Awesome-WSL)(WSL)上執行的Linux開發環境。
- 預裝[wslu](https://github.com/wslutilities/wslu)，一款專門為WSL而設計的工具組。
- `$ wlinux-setup`協助你配置你的Linux到你最喜歡的樣子：
    - 修改你的WLinux語言設定。
    - 可選的terminal shells: csh，zsh (帶[oh-my-zsh](https://ohmyz.sh/))或者[fish](https://fishshell.com/) (帶 [oh-my-fish](https://github.com/oh-my-fish/oh-my-fish))。
    - 可選的文字編輯器: [emacs](https://www.gnu.org/software/emacs/)，[neovim](https://neovim.io/)或者[Visual Studio Code](https://code.visualstudio.com/)。
    - 安裝你最喜愛的開發環境：[NodeJS](https://nodejs.org/) (n，npm和/或yarn), Python 3.7 (帶pip), [Ruby](http://www.ruby-lang.org/) (通過rbenv)與[Go](https://golang.org/)。
    - 用這些工具來管理你的Windows和Azure：[PowerShell](https://github.com/PowerShell/PowerShell)和[azure-cli](https://github.com/Azure/azure-cli)。
    - 開啟/關閉Windows檔案管理器右鍵選單支援。
    - 配置WSL的GUI設定，包括高解析度支援和CJK輸入法支援。
- 支援大部分的[GUI應用](https://github.com/ethanhs/WSL-Programs)! 注：需要安裝Windows下的X伺服器，如[X410](http://afflnk.microsoft.com/c/1291904/459838/7593?prodsku=9NLP712ZMN9Q&u=https%3A%2F%2Fwww.microsoft.com%2Fen-us%2Fstore%2Fp%2Fx410%2F9NLP712ZMN9Q)。
- WLinux提供與其他WSL支援的發行版相比更快的Bug修復。
- 一些不必要或者不支援的應用如`systemd`已被移除。
- 我們會基於[社羣反饋](https://github.com/WhitewaterFoundry/WLinux/issues)不斷的開發[新功能](https://github.com/WhitewaterFoundry/WLinux/pulls)。還有，[我們的WLinux賞金計劃](CONTRIBUTING.md)瞭解一下。

注：以上功能為最新的商店版本更新內容。你也可以自行編譯WLinux來幫我們測試新功能。

## 支援

WLinux在商店的購買可以是獨立的開源開發者們能夠持續的開發，測試和調整WLinux。我們嘗試為您提供最好的使用者服務。大部分問題可以通過以下方法解決。

- 請先[在此](https://github.com/sirredbeard/WLinux/issues)搜尋你的問題。
- 如果找不到，請在[WSL反饋頁](https://github.com/Microsoft/WSL/issues)搜尋你的問題。
- 你也可以檢視微軟官方的[WSL故障排除](https://docs.microsoft.com/en-us/windows/wsl/troubleshooting)檔案。
- 如果你無法找到你的問題，請[開一個新的issue](https://github.com/WhitewaterFoundry/WLinux/issues/new?template=bug_report.md)。我們通常會在幾個小時內回覆你，請您耐心等待。

## 其他文件

- [LICENSE.md](LICENSE.md)
- [BUILDING.md](BUILDING.md)
- [PRIVACY.md](PRIVACY.md)
- [ROADMAP.md](ROADMAP.md)
- [CONTRIBUTING.md](CONTRIBUTING.md)

## 相關介面

- [Awesome Windows Subsystem for Linux](https://github.com/sirredbeard/Awesome-WSL)
- [Awesome UNIX](https://github.com/sirredbeard/Awesome-UNIX)
- [wslu](https://github.com/wslutilities/wslu)

## 開發團體

### 核心團隊

- [Hayden Barnes](https://github.com/sirredbeard)
- [Patrick Wu](https://github.com/patrick330602)

### 測試/QA

- [Jack Mangano](https://thechipcollective.com/)
- [Nuno do Carmo](http://wslcorsair.blogspot.com/)

### 貢獻者

- [Carlos Rafael Ramirez](https://github.com/crramirez)
- [Andrew Fehr](https://github.com/ThatWeirdAndrew)