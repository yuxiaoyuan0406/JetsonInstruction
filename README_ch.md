# Jetson使用说明

简要的Jetson Nano使用说明，包括安装环境等。

## 系统烧录和SSD启动

前往[英伟达开发者网站](https://developer.nvidia.com/embedded/downloads)下载系统镜像  
下载完成后使用[balenaEtcher](https://www.balena.io/etcher/)烧录到sd卡或者ssd

注意，Jetson Nano B01虽然有m.2接口但该接口并不支持硬盘，ssd只能从usb启动  
这一段参考[知乎文章-Nvidia Jetson Nano USB SSD Boot 配置](https://zhuanlan.zhihu.com/p/346736716)  
只需要将写好系统的ssd在一台linux机器上挂载APP分区，修改文件`/boot/extlinux/extlinux.conf`  

```
LABEL primary
      MENU LABEL primary kernel
      LINUX /boot/Image
      INITRD /boot/initrd
      APPEND ${cbootargs} quiet root=/dev/mmcblk0p1 rw rootwait rootfstype=ext4 console=ttyS0,115200n8 console=tty0 fbcon=map:0 net.ifnames=0
```

将`/dev/mmcblk0p1`修改为`/dev/sda1`即可

## conda

常用linux写代码的比较熟悉[Anaconda](https://www.anaconda.com/products/individual)  
Anaconda官方之前只提供了x86的版本  
最近刚更新了ARM64平台的支持，但本人没有尝试过，这里不推荐也不反对

笔者使用的是[Archiconda](https://github.com/Archiconda/build-tools)  
直接下载脚本安装  

## pytorch

## libtorch

## OpenCV

## 其他

