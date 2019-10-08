# linux 驱动 #

## linux 驱动类型 ##

- 字符设备
- 快设备
- 网络设备

note：字符设备是以字节为单位的I/O传输。

## 一个简单的字符设备开始 my_demodrv.c##

### code ###

    #include <linux/module.h>
    #include <linux/fs.h>
    #include <linux/uaccess.h>
    #include <linux/init.h>
    #include <linux/cdev.h>

    #define DEMO_NAME "my_demo_dev"

    static dev_t dev;
    static struct cdev *demo_cdev;
    static signed count=1;
    
    static int demodrv_open(struct inode *inode,struct file *file)
    {
    	int major =MAJOR(inode->i_rdev);
    	int minor =MINOR(inode->i_rdev);
    	printk("%s: major =%d,minor=%d\n",__func__,major,minor);
    	return 0;
    }
    
    static int demodrv_release(struct inode *inode,struct file *file)
    {
    	return 0;
    }
    
    static ssize_t demodrv_read(struct file *file,char __user *buf,size_t lbuf,loff_t *ppos)
    {
    	printk("%s enter\n",__func__);
    	return 0;
    }
    
    static ssize_t demodrv_write(struct file *file,const char __user *buf ,size_t count,loff_t *f_pos)
    {
    	printk("%s enter\n",__func__);
    	return 0;
    }
    
    static const struct file_operations demodrv_fops=
    {
    	.owner=THIS_MODULE,
    	.open=demodrv_open,
    	.release=demodrv_release,
    	.read=demodrv_read,
    	.write=demodrv_write,
    };

	static int __init simple_char_init(void)
    {
    	int ret;
    	ret=alloc_chrdev_region(&dev,0,count,DEMO_NAME);
    	if(ret)
    	{
    		printk("failed to allocate char device region");
    		return ret;
    	}
    
    	demo_cdev=cdev_alloc();
    	if(!demo_cdev)
    	{
    		printk("cdev_alloc failed\n");
    		goto unregister_chrdev;
    
    	}
    	cdev_init(demo_cdev,&demodrv_fops);
    
    	ret=cdev_add(demo_cdev,dev,count);
    	if(ret)
    	{
    		printk("cdev_add failed\n");
    		goto cdev_fail;
    	}
    	printk("succeeded register char device:%s\n",DEMO_NAME);
    	printk("Major number =%d,minor number=%d\n",MAJOR(dev),MINOR(dev));
    	return 0;
    
    	cdev_fail:
    		cdev_del(demo_cdev);
    
		unregister_chrdev:
    		unregister_chrdev_region(dev,count);
    
    	return ret;
    }

    static void __exit simple_char_exit(void)
    {
    	printk("removing device\n");
    	if(demo_cdev)
    	{
    		cdev_del(demo_cdev);
    	}
    	unregister_chrdev_region(dev,count);
    }

    module_init(simple_char_init);
    module_exit(simple_char_exit);
    MODULE_AUTHOR("SUN");
    MODULE_LICENSE("GPL v2");
    MODULE_DESCRIPTION("simpe character device");


### Makefile: ###

    BASEINCLUDE ?= /lib/modules/`uname -r`/build
    mydemo-objs :=my_demodrv.o
    obj-m :=mydemo.o
    
    all:
    	$(MAKE) -C $(BASEINCLUDE) M=$(PWD) modules;
    clean:
    	$(MAKE) -C  $(BASEINCLUDE) SUBDIRS=$(PWD) clean;
    
    	rm -f *.ko;

### 后续步骤 ###

	sudo insmod mydemo.ko
	
	cat /proc/devices #这个proc虚拟文件系统中，可以找到相关设备

	生成的设备需要在/dev 目录下面生成对应的节点：
	根据具体的情况：
	mknod /dev/demo_drv c xx 0 #挂设备
	ls -l 查看/dev/目录

### 用户空间的测试程序 test.c  ###

    #include <stdio.h>
    #include<fcntl.h>
    #include<unistd.h>
    
    #define DEMO_DEV_NAME "/dev/demo_drv"
    int main ()
    {
    	char buffer[64];
    	int fd;
    	fd=open(DEMO_DEV_NAME,O_RDONLY);
    	if(fd<0)
    	{
    		printf("open device %s failed\n",DEMO_DEV_NAME);
    		return -1;
    	}
    	read(fd,buffer,64);
    	close(fd);
    	return 0;
    }

dmesg 进行内核信息查看

note：交叉编译时，加上 --static 把程序进行静态编译和连接






	



