- [Clone须知](#clone须知)
- [iOS编译报错请看](#iOS编译报错请看)
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
安装git-lfs:
```objc
// brew 命令安装
$ brew install git-lfs
// git 命令安装
$ git lfs install
```
安装完成后再执行clone，即可完整的将项目clone下来。

> 使用sourceTree来clone的开发者会在clone完毕后提示安装git-lfs，按照提示安装即可。


# iOS编译报错请看：
由于github无法上传超过100MB的大文件，iOS SDK文件使用git-lfs管理。这将导致直接download的项目的开发者在编译iOS项目时报错。

**解决方式**：进入[SDK下载链接](https://storage.zego.im/downloads/ZegoLiveRoom-MediaPlayer-iOS.zip)，下载SDK后将项目中libs/ZegoLiveRoom-all/下的iphoneos、iphone_simulator两个文件夹内的framework替换为下载的SDK即可正常编译运行。

# ZEGO Support
Please visit [ZEGO Developer Center](https://www.zego.im/html/document/#Application_Scenes/Video_Live)
