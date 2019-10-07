# linux kernel 编译和调试 #

## 内核配置 ##

### make config ###

一个传统的配置方式，输入y，编译进内核。输入 m，编译成模块。输入 n 不编译。

### make menuconfig ###

图形化配置

## .config ##

用于保存配置信息

### 使用版级的配置文件 ###

一些芯片公司提供一些demo，在 arch/arm/configs

### 使用系统的配置文件 ###

对应的内容使用系统的配置。在boot目录在config-xxx-generic


## QEMU 调试linux 内核 ##

### 安装 gdb-multiarch ###
	sudo apt-get install gdb-multiarch

### 内核编译，加入kernel kackong ###

--->compile-time checks--->[*]compile the kernel with debug info

	模拟demo:
    qemu-system-arm -M vexpress-a9  -m 1024M -kernel arch/arm/boot/zImage -append "rdinit=/linuxrc console=ttyAMA0 loglevel=8" -dtb arch/arm/boot/dts/vexpress-v2p-ca9.dtb  -S -s

	-S 直到GDB输入相关控制指令
	-s 表示在1234 端口接收GDB 的调试连接

### 在另一个窗口启动GDB： ###

	demo:

    gdb-multiarch --tui vmlinux
    
    set architecture arm
    target remote localhost:1234
    b start_kernel
    c 


## 使用Eclipse 调试比较方便 ##

## QEMU 在文件系统支持 ##




























