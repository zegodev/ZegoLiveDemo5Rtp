- [Clone须知](#clone须知)
- [Download须知](#Download须知)
- [ZEGO Support](#zego-support)

# Clone须知
由于github无法上传超过100MB的大文件，iOS SDK文件使用git-lfs管理。开发者在直接clone项目前需要确认本地安装了git-lfs:
```objc
// 终端运行
$ git lfs
// 显示正常则已安装lfs
git-lfs/2.6.0 (GitHub; darwin amd64; go 1.11.2)
...
```
如果未安装lfs，则需要先行安装。
安装git-lfs:
```objc
// 1.首先安装homebrew(已经安装的可以跳过)
$ /usr/bin/ruby -e "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/master/install)"

// 2.然后使用brew命令安装git-lfs
$ brew install git-lfs

// 3.最后set up git-lfs
$ git lfs install
```
安装完成后再执行clone，即可完整的将项目clone下来。

> 使用sourceTree来clone的开发者会在clone完毕后提示安装git-lfs，按照提示安装即可。


# Download须知
由于github无法上传超过100MB的大文件，iOS SDK文件使用git-lfs管理。这将导致直接download的项目的开发者在编译iOS项目时因为framework文件为空报错。

**解决方式**：进入[SDK下载链接](https://storage.zego.im/downloads/ZegoLiveRoom-MediaPlayer-iOS.zip)，下载SDK后将项目中libs/ZegoLiveRoom-all/下的iphoneos、iphone_simulator两个文件夹内的framework替换为下载的SDK即可正常编译运行。

> iOS会在编译前执行脚本拷贝对应版本的SDK到libs根目录，所以项目在第一次编译前Xcode中SDK文件是缺失的，正常编译即可。

> 如果iOS运行报错 `image not found` ，是由于framework未导入到项目。需要打开 Xcode，选择：项目 TARGET -> General -> Embedded Binaries以及Link Binary With Libraries，添加缺失的framework即可。

# ZEGO Support
Please visit [ZEGO Developer Center](https://www.zego.im/html/document/#Application_Scenes/Video_Live)
