# 字节设备驱动详解 #

## 字符设备驱动的抽象 ##

    linux 内核有一个数据结构对其进行抽象和描述：
    
    <include/linux/cdev.h>
    
    struct cdev
    {
    	struct kobject kobj;
    	struct module *owner;
    	const struct file_oprations *ops;
    	struct list_head list;
    	dev_t dev;
    	unsigned int count;
    }


- kobj：用于linux设备驱动模型
- owner：字符设备驱动程序所在的内核模块对象指针。
- ops：一些关键的操作
- list：用来将字符设备串成一个链表
- dev：字符设备的设备号，由主设备和次设备号组成
- count：同一个主设备号的次设备号的个数

## 主设备和次设备号获得：  ##
	
	设备号通过如下宏获得，就是高12比特是主设备号，低20比特是次设备号
	#define MAJOR(dev)
	#define MINOR(dev)
	#define MKDEV(ma，mi)


## struct cdev 产生  ##
	两种产生方法，一种是全局静态变量，一种是内核提供的cdev_alloc()

    static struct cdev mydemo_cdev;
    struct mydemo_cdev=cdev_alloc();

## 内核和cdev 相关的API函数  ##

### cdev_init()函数： ###
初始化cdev数据结构，并且建立设备与驱动操作方法集file_operations 之间的连接关系
	
	void cdev_init(struct cdev *cdev,const struct file_operatopns *fops);

### cdev_add()函数 ###
把一个字符设备添加到系统中

	int cdev_add(struct cdev *p,dev_t dev,unsigned count);

- p 表示一个设备的cdev 数据结构
- dev 表示设备的设备号
- count 表示可以有多少个次设备号

### cdev_del()函数 ###
	
从系统中删除一个cdev设备

	void cdev_del(struct cdev *p);



## 设备号管理 ##

### 需要指定主设备号，可以连续分配多个，避免使用已经分配的主设备号。 ###
	
register_chrdev_region 需要指定主设备，可以连续分配多个。使用该函数必须要保证要分配的主设备在系统中没有人使用，内核文档documentation/devices.txt 有介绍
 
	int register_chrdev_region(dev_t from,unsigned count,const char *name);
	
### 另一个接口 ###

自动分配一个主设备号

	int alloc_chrdev_region(dev_t *dev,unsigned baseminor,unsigned count,const char *name);

### 释放 ###

	void unregister_chrdev_region(dev_t from,unsigned count);

## 设备节点 ##

### 查看 ###
按照Linux 的习惯，系统中所有的设备节点都放在/dev/目录中。dev目录是一个动态生成的，使用devtmpfs虚拟文件系统挂载的。基于RAM的虚拟文件系统。
	ls -l /dev/ #查看

### 生成 ###

	mknod filename type major minor #使用mknod 命令手工生成
	使用udev机制动态生成。

## 字符设备操作方法集 ##

    static const struct file_operations #定义在 <include/linux/fs.h>

    struct file_operations { 
    　　struct module *owner;//拥有该结构的模块的指针，一般为THIS_MODULES  
       loff_t (*llseek) (struct file *, loff_t, int);//用来修改文件当前的读写位置  
       ssize_t (*read) (struct file *, char __user *, size_t, loff_t *);//从设备中同步读取数据   
       ssize_t (*write) (struct file *, const char __user *, size_t, loff_t *);//向设备发送数据  
       ssize_t (*aio_read) (struct kiocb *, const struct iovec *, unsigned long, loff_t);//初始化一个异步的读取操作   
       ssize_t (*aio_write) (struct kiocb *, const struct iovec *, unsigned long, loff_t);//初始化一个异步的写入操作   
    　　int (*readdir) (struct file *, void *, filldir_t);//仅用于读取目录，对于设备文件，该字段为NULL   
       unsigned int (*poll) (struct file *, struct poll_table_struct *); //轮询函数，判断目前是否可以进行非阻塞的读写或写入   
    　　int (*ioctl) (struct inode *, struct file *, unsigned int, unsigned long); //执行设备I/O控制命令   
    　　long (*unlocked_ioctl) (struct file *, unsigned int, unsigned long); //不使用BLK文件系统，将使用此种函数指针代替ioctl  
    　　long (*compat_ioctl) (struct file *, unsigned int, unsigned long); //在64位系统上，32位的ioctl调用将使用此函数指针代替   
    　　int (*mmap) (struct file *, struct vm_area_struct *); //用于请求将设备内存映射到进程地址空间  
    　　int (*open) (struct inode *, struct file *); //打开   
    　　int (*flush) (struct file *, fl_owner_t id);   
    　　int (*release) (struct inode *, struct file *); //关闭   
    　　int (*fsync) (struct file *, struct dentry *, int datasync); //刷新待处理的数据   
    　　int (*aio_fsync) (struct kiocb *, int datasync); //异步刷新待处理的数据   
    　　int (*fasync) (int, struct file *, int); //通知设备FASYNC标志发生变化   
    　　int (*lock) (struct file *, int, struct file_lock *);   
    　　ssize_t (*sendpage) (struct file *, struct page *, int, size_t, loff_t *, int);   
    　　unsigned long (*get_unmapped_area)(struct file *, unsigned long, unsigned long, unsigned long, unsigned long);   
    　　int (*check_flags)(int);   
    　　int (*flock) (struct file *, int, struct file_lock *);  
    　　ssize_t (*splice_write)(struct pipe_inode_info *, struct file *, loff_t *, size_t, unsigned int);  
    　　ssize_t (*splice_read)(struct file *, loff_t *, struct pipe_inode_info *, size_t, unsigned int);   
    　　int (*setlease)(struct file *, long, struct file_lock **);   
    };


## 使用MISC机制来创建设备 ##
 linux内核吧一些不符合预先确定的字符设备划分为杂散设备，这类设备主设备号是10. 使用struct miscdevice数据结构体描述这类设备。

使用两个API来进行管理
	int misc_register（struct miscdevice*misc）;
	int misc_deregister(struct miscdevice *misc);

## demo ##
	#include <linux/miscdevice.h>
	#define DEMO_NAME "my_demo_dev"

	static struct device *mydemodrv_device;

	static struct miscdevice mydemodrv_misc_device={
		.minor=MISC_DYNAMIC_MINOR,
		.name-DEMO_NAME,
		.fops=&demodrv_fops,
	}

	static int __init simple_char_init(void)
	{
		int ret;
		ret=misc_register(&mydemodrv_misc_device);
		if(ret)
		{
			return ret;
		}
		return 0;
	}

	static void __exit simple_char_exit(void)
	{
		misc_deregister(&mydemodrv_misc_device);
	}

**不需要挂载**
