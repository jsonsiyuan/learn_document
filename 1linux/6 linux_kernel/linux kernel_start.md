# linux 学习 #

## linux 内核 ##
下载地址 使用4.16.3 

- https://git.kernel.org/pub/scm/linux/kernel/git/stable/linux.git/tag/?h=v4.16.3


### 宏内核和微内核 ###

- linux 是宏内核的。现在也加入的一些模块，参考了微内核。

## linux 内核概貌 ##

- 系统调用成：内核态和用户态之间的切换设置了软件抽象层。
- 处理器体系结构抽象层：内存管理放在 arch/xx/mm 不相干放在mm
- 进程管理：进程创建和销毁，线程组管理，内核线程管理，队列等待内容
- 内存管理：物理内存和虚拟内存。
- 中断管理：处理器的异常处理和中断处理
- 设备管理：
- 文件系统：VFS 软件层

linux code is 抽象和分层。

## 编译安装新的内核 ##

先下载一些软件包：

    
- sudo apt-get install libncurses5-dev libssl-dev build-essential openssl

- 	下载内核文件 
- 	内核配置     make menuconfig 
- 	编译内核     make -jn
- 	安装内核模块  sudo make modules_install
- 	安装到系统中  make install

## 编译一个ARM镜像，并运行在QEMU ##

	sudo apt-get install qemu libncurses5-dev gcc-arm-linux-gnueabi build-essential gcc-5-arm-linux-gnueabi git 

### update-alternatives ###

**软连接的变换使用**

    update-alternatives --install <link> <name> <path> <priority>

- link 指向etc/alternatives/<name> 符合应用
- name 连接名
- path 实际路径
- priority 优先级

使用update-alternative 选择一个配置

	sudo update-alternatives --config <link>

**demo：加入一些编译软件**

	ls /usr/bin |grep gcc

	sudo update-alternatives --install /usr/bin/arm-linux-gnueabi-gcc arm-linux-gnueabi-gcc /usr/bin/arm-linux-gnueabi-gcc-5 5

	


**在内核中加入设备**

	mknod DEVNAME {b | c} MAJOR MINOR



- b表示系统从块设备中读取数据的时候，直接从内存的buffer中读取数据，而不经过磁盘；
- c表示字符设备文件与设备传送数据的时候是以字符的形式传送，一次传送一个字符，比如打印机、终端都是以字符的形式传送数据；


------


### busybox  ###

**BusyBox 是一个集成了三百多个最常用Linux命令和工具的软件。主要用在嵌入式中**

	export ARCH=arm
    export CROSS_COMPILE=arm-linux-gnueabi-

- make menuconfig &&make &&make install生成一个_install 目录。
- busybox setting -->built..--->built busy static 编译成静态
- 把该目录放到linux-4.0（内核文件中）


---

### _install 内核中文件添加 ###

- 建立一些文件夹
- 
    mkdir etc
    mkdir dev
    mkdir mnt
    mkdir -p etc/init.d/

- 在init.d 中创建文件rcS，并修改为可执行 chomd+x。
- 
    mkdir -p /proc
    mkdir -p /tmp
    mkdir -p /sys
    mkdie -p /mnt
    /bin/mount -a
    mkdir -p /dev/pts
    mount -t devpts devpts /dev/pts
    echo /sbin/mdev >/proc/sys/kernel/hotplug
    mdev -s


- 在_install /etc 建立一个fstab（自动挂载文件） 并写入
-  

    proc /proc proc defaults 0 0
    tmpfs /tmp tmpfs defaults 0 0
    sysfs /sys sysfs defaults 0 0
    tmpfs /dev tmpfs defaults 0 0
    debugfs /sys/kernel/debug debugfs defaults 0 0

- 在_install/etc 新建一个inittab(init初始化程序用到的配置文件) 文件
- 
	::sysinit:/etc/init.d/rcS
	::respawn:~/bin/sh
	::askfirst:~/bin/sh
	::ctrlaltdel:/bin/umount -a -r
	
- 在_install/dev 加入设备节点
- 
	cd _install/dev/
	sudo mknod console c 5 1
	sudo mknod null c 1 3


### 内核编译 ###

    export ARCH=arm
    export CROSS_COMPILE=arm-linux-gnueabi-
    make vexpress_defconfig
    make menuconfig
-------
    GENERAL SETUP [*]Inital RAM filesystem ....(_install)...
    
    boot options--()default kernel ....
    
    kernel features-->memory split 3g/1g
	[*]high memory ...
-------
    make bzImage -j4 ARCH=arm CROSS_COMPILE=arm-linux-gnueabi-
    make dtbs   #制作设备树


### 运行QEMU ###
    
demo：

    qemu-system-arm -M vexpress-a9 -smp 4 -m 200M -kernel arch/arm/boot/zImage -dtb arch/arm/boot/dts/vexpress-v2p-ca9.dtb -nographic -append "rdinit=/linuxrc console=ttyAMA0 loglevel=8 " 


## note： ##
- inittab
- 
    respawn： 表示init应该监视这个进程，即使其结束后也应该被重新启动。
    wait：    init应该运行这个进程一次，并等待其结束后再进行下一步操作。
    once：    init需要运行这个进程一次。
    boot：    随系统启动运行，所以runlevel值对其无效。
    bootwait：随系统启动运行，并且init应该等待其结束。
    off：     没有任何意义。
    initdefault：系统启动后的默认运行级别；由于进入相应的运行级别会激活对应级别的进程，所以对其指定process字段没有任何意义。如果inittab文件内不存在这一条记录，系统启动时在控制台上询问进入的运行级。
    sysinit：    系统启动时准备运行的命令。比如说，这个命令将清除/tmp.可以查看/etc/rc.d/rc.sysinit脚本了解其运行了那些操作。
    powerwait：  允许init在电源被切断时，关闭系统。当然前提是有U P S和监视U P S并通知init电源已被切断的软件。RH linux默认没有列出该选项。
    powerfail：  同powerwait，但init不会等待正在运行的进程结束。RH linux默认没有列出该选项。
    powerokwait：当电源监视软件报告“电源恢复”时，init要执行的操作。
    powerfailnow：检测到ups电源即将耗尽时，init要执行的操作，和powerwait/powerfail不同的哟。
    ctrlaltdel：允许init在用户于控制台键盘上按下C t r l + A l t + D e l组合键时，重新启动系统。注意，如果该系统放在一个公共场所，系统管理员可将C t r l + A l t + D e l组合键配置为别的行为，比如忽略等。我是设置成打印一句骂人的话了^o^. kbrequest：监视到特定的键盘组合键被按下时采取的动作，现在还不完善。
    ondemand：  A process marked with an ondemand runlevel will be executed whenever the specified ondemand runlevel is called.  However， no runlevel change will occur （ondemand runlevels are ‘a’， ‘b’，and ‘c’）


- 























