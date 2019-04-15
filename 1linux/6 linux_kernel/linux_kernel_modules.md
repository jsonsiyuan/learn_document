# 内核模块 #

- linux 可以通过内核模块实现动态添加和删除某个功能。

## 内核demo ##
	my_test.c

    #include <linux/init.h>
    #include <linux/module.h>
    static __init my_test_init(void)
    {
    	printk("my first kernel module init \n");
    	return 0;
    }
    
    static void __exit my_test_exit(void)
    {
    	printk("goodbye\n");
    }
    
    module_init(my_test_init);
    module_exit(my_test_exit);
    
    MODULE_LICENSE("GPL");
    MODULE_AUTHOR("SUN");
    MODULE_DESCRIPTION("MY TEST MODUEL");
    MODULE_ALIAS("MYTEST");

## MAKEFILE ##
    BASEINCLUDE ?= /lib/modules/`uname -r`/build
    mytest-objs :=my_test.o
    obj-m :=mytest.o
    
    all:
    	$(MAKE) -C $(BASEINCLUDE) M=$(PWD) modules;
    clean:
    	$(MAKE) -C  $(BASEINCLUDE) SUBDIRS=$(PWD) clean;
    
    	rm -f *.ko;

1. 当make的目标为all时，-C $(KDIR) 指明跳转到源码目录下读取那里的Makefile；M=$(PWD) 表明然后返回到当前目录继续读入
2. uname -r 查看系统内核
3. <模块名>-objs ：=<目标文件>.o
4. obj-m :=<模块名>.o
5. make
6. file mytest.ko
7. modinfo mytest.ko
7. sudo insmod mytest.ko
8. dmesg
9. lsmod
10. /sys/module/xx tree -a
11. rmmod

## 模块参数 ##

**linux提供了一个灵活性**

1. module_param(name,type,perm)
2. MODULE_PARM_DESC(_parm,desc)
3. <derver/misc/altera-stapl/altera.c> 一个例子
---
    name:参数名
    type:byte,short,ushort,int,uint,long,ulong,char,bool
    perm:权限，0 表示不会出现在sysfs文件系统中。S_IRUGO(0444),可以被所以人阅读。S_IRUGO|S_IWUSR(0644).

	insmod mymodule.ko mytest=200

## 符号共享 ##

    linux 提供两个宏
    EXPORT_SYMBOL()
    EXPORT_STMBOL_GPL()

    cat /proc/kallsyms
    1. 第一列是内核地址空间的地址
    2. 第2列是符号属性。T表示在TEXT。
    3. 第3列表示符号的字符串 EXPORT_SYMBOL 导出来的
    4. 那些内核模块在使用





