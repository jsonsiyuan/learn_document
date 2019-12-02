# linux 学习 #

## linux 内核介绍 ##
下载地址 使用4.16.3 

- https://git.kernel.org/pub/scm/linux/kernel/git/stable/linux.git/tag/?h=v4.16.3


### 宏内核和微内核 ###
宏内核：相对比较集合，但是高效
微内核：操作系统分成多个独立的功能模块。
- linux 是宏内核的。现在也加入的一些模块，参考了微内核。

###  linux 内核概貌  ###

- 系统调用成：内核态和用户态之间的切换设置了软件抽象层。（借用了很多芯片自带的用户和非用户两个状态）
- 处理器体系结构抽象层：内存管理放在 arch/xx/mm 不相干放在mm
- 进程管理：进程创建和销毁，线程组管理，内核线程管理，队列等待内容
- 内存管理：物理内存和虚拟内存。
- 中断管理：处理器的异常处理和中断处理
- 设备管理：外设设备的管理
- 文件系统：VFS 软件层

note：大系统是 抽象和分层。

## 编译安装新的内核 ##

先下载一些软件包：

	sudo apt-get install libncurses5-dev libssl-dev build-essential openssl

- 	下载内核文件 
- 	内核配置     make menuconfig 
- 	编译内核     make -jn # 'n'代表使用多少个cpu核心来进行编译 
- 	安装内核模块  sudo make modules_install
- 	安装到系统中  make install

**note:在 /boot/ 里有参考的config配置文件**

## 编译一个ARM镜像，并运行在QEMU ##

### 安装一些必要的软件 ###

	sudo apt-get install qemu libncurses5-dev gcc-arm-linux-gnueabi build-essential gcc-5-arm-linux-gnueabi git 

### update-alternatives 介绍###

update-alternatives 命令用于处理linux系统中软件版本的切换

**软连接的变换使用**

    update-alternatives --install <link> <name> <path> <priority>

- link 指向etc/alternatives/<name> 符合应用
- name 连接名
- path 实际路径
- priority 优先级

使用update-alternative 选择一个配置

	sudo update-alternatives --config <link>

**demo：gcc更改**

	ls /usr/bin |grep gcc
	
	sudo update-alternatives --config arm-linux-gnueabi-gcc

	sudo update-alternatives --install /usr/bin/arm-linux-gnueabi-gcc arm-linux-gnueabi-gcc /usr/bin/arm-linux-gnueabi-gcc-5 5

	


### 在内核中加入设备 ###

	mknod DEVNAME {b | c} MAJOR MINOR

- b表示系统从块设备中读取数据的时候，直接从内存的buffer中读取数据，而不经过磁盘；
- c表示字符设备文件与设备传送数据的时候是以字符的形式传送，一次传送一个字符，比如打印机、终端都是以字符的形式传送数据；

### busybox  ###

**BusyBox 是一个集成了三百多个最常用Linux命令和工具的软件。主要用在嵌入式中。**

web：

	https://busybox.net/

#### 开始编译 ####

编译选项：

	export ARCH=arm
    export CROSS_COMPILE=arm-linux-gnueabi-

配置：
	make menuconfig

	note:
	Busybox Setting ---> Build Options --> [*]Build BusyBox as a static binary(no shared libs)

编译：
	make &&make install#生成一个_install 目录。_install复制到linux文件中

### linux 内核编译 ###

### _install 内核中文件添加 ###

先建立一些文件夹：
	cd _install
    mkdir etc
    mkdir dev
    mkdir mnt
    mkdir -p etc/init.d/

在_install/ect/init.d 中创建文件rcS文件，并写入下面内容：
	cd etc/init.d/
	gedit rcS
	
    mkdir -p /proc
    mkdir -p /tmp
    mkdir -p /sys
    mkdir -p /mnt
    /bin/mount -a
    mkdir -p /dev/pts
    mount -t devpts devpts /dev/pts
    echo /sbin/mdev >/proc/sys/kernel/hotplug
    mdev -s

修改为可执行:
	chmod +x rcS#并修改为可执行

在_install /etc 建立一个fstab文件（自动挂载文件）并修改为可执行 chomd+x。 并写入:
	cd ..
	gedit fstab

    proc /proc proc defaults 0 0
    tmpfs /tmp tmpfs defaults 0 0
    sysfs /sys sysfs defaults 0 0
    tmpfs /dev tmpfs defaults 0 0
    debugfs /sys/kernel/debug debugfs defaults 0 0

在_install/etc 新建一个inittab文件(init初始化程序用到的配置文件) 并修改为可执行 chomd+x:
	gedit inittab

	::sysinit:/etc/init.d/rcS
	::respawn:~/bin/sh
	::askfirst:~/bin/sh
	::ctrlaltdel:/bin/umount -a -r
	
在_install/dev 加入设备节点:
	cd ../dev/
	sudo mknod console c 5 1
	sudo mknod null c 1 3


### 内核编译 ###

	cd ../..
    export ARCH=arm
    export CROSS_COMPILE=arm-linux-gnueabi-
    make vexpress_defconfig
    make menuconfig

解决 make vexpress_defconfig error:

/bin/sh: 1: bison: not found:
	sudo apt-get install bison
/bin/sh: 1: flex: not found
	sudo apt-get install flex


#### 内核配置： ####

    GENERAL SETUP--->
	 [*]Inital RAM filesystem and RAM disk 
	(_install) Initramfs source file(s) 
    
    boot options-->
	()default kernel ....#清空 D额faultkernelcommand string
    
    kernel features-->
	memory split 3g/1g
	[*]high memory ...

#### 开始编译： ####

    make bzImage -j4 ARCH=arm CROSS_COMPILE=arm-linux-gnueabi-
    make dtbs   #制作设备树


### 运行QEMU ###
    
#### demo1： ####

    qemu-system-arm -M vexpress-a9 -smp 4 -m 200M -kernel arch/arm/boot/zImage -dtb arch/arm/boot/dts/vexpress-v2p-ca9.dtb -nographic -append "rdinit=/linuxrc console=ttyAMA0 loglevel=8 " 


### 在QEMU虚拟开发板与主机之间文件共享的方法 ###

NOTE:NFS 相关文件
	https://blog.csdn.net/jin970505/article/details/78847028
#### Linux中tun/tap ####
  tun/tap 驱动程序实现了虚拟网卡的功能，tun表示虚拟的是点对点设备，tap表示虚拟的是以太网设备

- sudo apt-get install uml-utilities    （User-Mode Linux，使用它创建TAP）
- sudo apt-get install bridge-utils    （如果需要创建bridge可以选择安装）
- 安装完成后，执行  sudo tunctl -u root -t tap30  就可以在主机上创建一个网络设备，这是使用 ifconfig -a 命令可以看到名字为tap30的网络设备。
- 执行 ifconfig tap30 192.168.111.1 promisc up 配置网卡IP地址，并且以混杂模式启用。
- 主机的网络配置已经完成，接下来开始配置虚拟机，QEMU通过 -net 参数指定网络配置 net nic  net tap  net user 一般nic必须有，tap和user选一个使用

demo：
	qemu-system-arm -M vexpress-a9 -smp 4 -m 200M -kernel arch/arm/boot/zImage -net nic,vlan=0 -net tap,vlan=0,ifname=tap30,script=no,downscript=no -dtb arch/arm/boot/dts/vexpress-v2p-ca9.dtb -nographic -append "rdinit=/linuxrc console=ttyAMA0 loglevel=8 "

启动后在目标开发板中执行  ifconfig -a 就能看到 eth0 的网络接口
在模拟开发板中执行  ifconfig eth0 192.168.111.2 promisc up

#### 开始配置并启用NFS服务 ####
**在主机中**
- 输入  sudo apt-get install nfs-kernel-server
- NFS服务的配置文件为 /etc/exports ，一个NFS服务可以共享多个NFS目录，在/etc/exports文件中，每个目录的设置独占一行，我要把 /share 目录共享给目标开发板，就在配置文件中加入一行：/share    192.168.111.2(rw,sync,no_root_squash,no_subtree_check)
- 保存配置文件并退出，执行 sudo service nfs-kernel-server start 启动NFS 服务
- 可以在主机上运行 showmount -e 来查看NFS服务和配置是否启动正常。

**模拟开发板**
 mkdir -p /mnt/nfs
 mount -t nfs -o nolock 192.168.111.1:/share /mnt/nfs

挂载成功后进入目标开发板的 /mnt/nfs 目录便可以将主机的 /share 文件夹作为本地文件夹来操作，这样会很大的提高应用程序的调试运行效率。























