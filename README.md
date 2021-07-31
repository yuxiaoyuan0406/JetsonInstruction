# JetsonInstruction

An instraction for coding and other shit on Jetson nano  

## System and boot from ssd

Go to [Nvidia](https://developer.nvidia.com/embedded/downloads) for the system image.  
Using [balenaEtcher](https://www.balena.io/etcher/) to flash the image to your sd card or ssd drive.  

Note: Jetson Nano B01 has a m.2 port but not does not support a hard drive. Using an ssd can only boot via usb.  
Ref: [Zhihu-Nvidia Jetson Nano USB SSD Boot Configuration](https://zhuanlan.zhihu.com/p/346736716)  
After flash the drive, mount the APP sector on a linux computer. Edit file `/boot/extlinux/extlinux.conf`.  

```
LABEL primary
      MENU LABEL primary kernel
      LINUX /boot/Image
      INITRD /boot/initrd
      APPEND ${cbootargs} quiet root=/dev/mmcblk0p1 rw rootwait rootfstype=ext4 console=ttyS0,115200n8 console=tty0 fbcon=map:0 net.ifnames=0
```

Change `/dev/mmcblk0p1` into `/dev/sda1`.  

## conda

[Anaconda](https://www.anaconda.com/products/individual) is useful.  
Anaconda.org used to only support some x86 version. Recently they updated a ARM64 version. I haven't try it yet, just note here. 

I'm using [Archiconda](https://github.com/Archiconda/build-tools).  
One can download the script and run it easily.  

## pytorch & torchvision

Nvidia has a compiled-for-jetson version of [PyTorch](https://forums.developer.nvidia.com/t/pytorch-for-jetson-version-1-9-0-now-available/72048).  
They offered an instruction as well. Check it on their website. 

To install torchvision, check this [instruction](https://qengineering.eu/install-pytorch-on-jetson-nano.html) from Qengineering.  

Verification  

```python
import torch
print(torch.__version__)
print(torch.cuda.is_available())
import torchvision
print(torchvision.__version__)
```

Might have some problems. 

```
Python 3.6.13 | packaged by conda-forge | (default, Feb 19 2021, 05:46:38)
[GCC 9.3.0] on linux
Type "help", "copyright", "credits" or "license" for more information.
>>> import torch
Illegal instruction (core dumped)
```

This is a numpy 1.19.5 [issue](https://github.com/numpy/numpy/issues/18131), run `pip install numpy==1.19.4` to fix this. 

## libtorch

If you used the wheel from Nvidia, you will get all the c++ libs aka libtorch.  
Use command `python -c 'import torch;print(torch.utils.cmake_prefix_path)'` to find the directory.  
Note: 
__Must run the command in the conda enviorment which already installed pytorch.__  
Then set the cmake argument `CMAKE_PREFIX_PATH` to it.  
A [demo](https://github.com/yuxiaoyuan0406/JetsonInstruction/tree/main/example/libtorch) is given in this repo.  

## OpenCV

For python, install via conda.  
For c++, follow the [instructions](https://github.com/Qengineering/Install-OpenCV-Jetson-Nano) given by Qengineering.  
A [demo](https://github.com/yuxiaoyuan0406/JetsonInstruction/tree/main/example/torchcv) for libtorch & OpenCV is given in this repo.  

Note: Using OpenCV from conda-forge may not be able to use a gstreamer camera(CSI camera like rpi camera). See [issue#1](https://github.com/yuxiaoyuan0406/JetsonInstruction/issues/1) for more details.  

## one more thing
__todo__
