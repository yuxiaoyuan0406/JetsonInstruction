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
Anaconda官方之前只提供了x86的版本，最近刚更新了ARM64平台的支持，但本人没有尝试过，这里不推荐也不反对

笔者使用的是[Archiconda](https://github.com/Archiconda/build-tools)  
直接下载脚本安装  

## pytorch和torchvision

英伟达很良心得为大家准备了官方编译的[PyTorch](https://forums.developer.nvidia.com/t/pytorch-for-jetson-version-1-9-0-now-available/72048)  
也提供了官方的安装说明，直接去官网查看

torchvision安装参考Qengineering的[教程](https://qengineering.eu/install-pytorch-on-jetson-nano.html)

验证安装

```python
import torch
print(torch.__version__)
print(torch.cuda.is_available())
import torchvision
print(torchvision.__version__)
```

可能会报错

```
Python 3.6.13 | packaged by conda-forge | (default, Feb 19 2021, 05:46:38)
[GCC 9.3.0] on linux
Type "help", "copyright", "credits" or "license" for more information.
>>> import torch
Illegal instruction (core dumped)
```

这是numpy 1.19.5 的[issue](https://github.com/numpy/numpy/issues/18131)，使用指令`pip install numpy==1.19.4`降级可以解决

## libtorch

上一步安装的torch包含了C++的库文件即libtorch  
使用指令`python -c 'import torch;print(torch.utils.cmake_prefix_path)'`可以查看目录  
__注意要在安装了torch的conda环境中执行这个指令__  
然后将输出的结果设置为CMake脚本的参数`CMAKE_PREFIX_PATH`  
这里给出一个[示例工程](https://github.com/yuxiaoyuan0406/JetsonInstruction/tree/main/example/libtorch)作为参考  

## OpenCV

OpenCV如果只需要在python上使用可以用conda安装  
如果要用C++而且需要最新版本，只能从源码编译  
直接参考Qengineering给出的[教程](https://github.com/Qengineering/Install-OpenCV-Jetson-Nano)  
这里给出一个libtorch+OpenCV的[示例工程](https://github.com/yuxiaoyuan0406/JetsonInstruction/tree/main/example/torchcv)作为参考  

## 其他
__todo__
