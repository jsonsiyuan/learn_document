# 内核模块 #

linux 可以通过内核模块实现动态添加和删除某个功能。

## 内核模块一个简单的demo ##

### my_test.c ###

    #include <linux/init.h>
    #include <linux/module.h>

    static int __init my_test_init(void)
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
    
    MODULE_LICENSE("GPL"); //哪个许可
    MODULE_AUTHOR("SUN");  //作者
    MODULE_DESCRIPTION("MY TEST MODUEL");//模块描述
    MODULE_ALIAS("MYTEST");//模块别名

### Makefile ###

    BASEINCLUDE ?= /lib/modules/`uname -r`/build ###一般来说，linux 系统的内核模块都会安装到/lib/modules 这个目录下，通过"uname -r "命令可以找到对应的内核版本号

    mytest-objs :=my_test.o ##<模块名>-objs ：=<目标文件>.o 内核模块需要哪些目标文件
	
    obj-m :=mytest.o ##表示要生成的模块。obj-m :=<模块名>.o
    
    all:
    	$(MAKE) -C $(BASEINCLUDE) M=$(PWD) modules; ###当make的目标为all时，-C $(KDIR) 指明跳转到源码目录下读取那里的Makefile；M=$(PWD) 表明然后返回到当前目录继续读入
    clean:
    	$(MAKE) -C  $(BASEINCLUDE) SUBDIRS=$(PWD) clean;
    
    	rm -f *.ko;

### 编译 ###

	make  #会生成*.ko文件
	
	file *.ko              ## 检查模块是否正确
	modinfo *.ko           ##进一步检查
	sudo insmod *.ko       #安装
	dmesg                  #查看内核打印信息
	lsmod                  #查看是否加载到内核中
	/sys/module/xx tree -a #内核会在/sys/modules 中新建一个文件
	sudo rmmod *#模块名称                 #删除模块

-------------------------------------


## 模块参数相关的简单介绍 ##

### linux提供了一个宏来实现模块参数传递: ###

	#define module_param(name,type,perm) \
		module_param_named(name,name,type,perm)
	#define MODULE_PARM_DESC(_parm,desc) \
		__MODULE_INFP(parm,_parm,#_parm ":" desc) 

### module_param 参数介绍 ###

    name:参数名
    type:byte,short,ushort,int,uint,long,ulong,char,bool
    perm:权限，0 表示不会出现在sysfs文件系统中。S_IRUGO(0444),可以被所以人阅读，但是不能修改。S_IRUGO|S_IWUSR(0644)，说明可以让root权限的用户修改这个参数

其中具体的权限类型：

	#define S_IRWXU 00700
	#define S_IRUSR 00400
	#define S_IWUSR 00200
	#define S_IXUSR 00100
	#define S_IRWXG 00070
	#define S_IRGRP 00040
	#define S_IWGRP 00020
	#define S_IXGRP 00010
	#define S_IRWXO 00007
	#define S_IROTH 00004
	#define S_IWOTH 00002
	#define S_IXOTH 00001
	
### 具体的demo ###

	1.<derver/misc/altera-stapl/altera.c> 一个例子

#### my_test.c 改良####

	#include <linux/init.h>
	#include <linux/module.h>
	
	static int debug=1;
	
	module_param(debug, int, 0644);
	
	MODULE_PARM_DESC(debug,"enable debugging information");
	
	
	#define dprintk(args...) \
		if(debug){ \
			printk(KERN_DEBUG args);\
			}
	
	static int mytest=1;
	module_param(mytest,int, 0644);
	MODULE_PARM_DESC(mytest,"test for module parameter");
	
	static int __init my_test_init(void)
	{
		printk("my first kernel module init \n");
		dprintk("my first kernel module init \n");
		dprintk("module parameter=%d \n",mytest);
		return 0;
	}
	
	static void __exit my_test_exit(void)
	{
		printk("goodbye\n");
	}
	
	module_init(my_test_init);
	module_exit(my_test_exit);
	
	MODULE_LICENSE("GPL"); //哪个许可
	MODULE_AUTHOR("SUN");  //作者
	MODULE_DESCRIPTION("MY TEST MODUEL");//模块描述
	MODULE_ALIAS("MYTEST");//模块别名

---------------------------

相关信息查看

- 编写Makefile
- sudo insmod my_test.ko mytest=20 debug=0
- dmesg #查看信息
- 则可以使用 cat /sys/module/xx/parameters ，看到为 一些参数20

## 符号共享 ##

    linux 提供两个宏
    EXPORT_SYMBOL() #把函数或者符号对全部内核代码公开，也是将一个函数以符号的方式导出给内核中的其他模块使用。

    EXPORT_STMBOL_GPL() 只能包含GPL许可的模块，内核核心的大部分模块导出来的符号都是使用GPL()这种形式的。

    cat /proc/kallsyms #内核导出的符号，通过该处查看。
    1. 第一列是内核地址空间的地址
    2. 第2列是符号属性。T表示在TEXT。
    3. 第3列表示符号的字符串 EXPORT_SYMBOL 导出来的
    4. 那些内核模块在使用


### 使用方法demo ###


- 在模块函数定义之后使用“EXPORT_SYMBOL（函数名）”来声明
- 在调用该函数的另外一个模块中使用extern对之声明
- 先加载定义该函数的模块，然后再加载调用该函数的模块，请注意这个先后顺序。


-----------------
	#include<linux/init.h>
	#include<linux/module.h>
	#include<linux/kernel.h>
	 
	static int function_one(void)
	{
	        printk("EXPORT_SYMBOL  In Func: %s...\n",__func__);
	        return 0;
	}
	 
	EXPORT_SYMBOL(function_one);
	 
	static int __init export_symbol_init(void)
	{
	        printk("EXPORT_SYMBOL  Module one,Init!\n");
	        return 0;
	}
	 
	static void __exit export_symbol_exit(void)
	{
	        printk("EXPORT_SYMBOL  Module one,Exit!\n");
	}
	 
	module_init(export_symbol_init);
	module_exit(export_symbol_exit);

---------------------------
	#include<linux/init.h>
	#include<linux/kernel.h>
	#include<linux/module.h>
	 
	static int function_two(void)
	{
	       extern int function_one(void);
	        function_one();
	        printk("EXPORT_SYMBOL In Func: %s...\n",__func__);
	        return 0;
	}
	 
	static int __init export_symbol_init(void)
	{
	        printk("EXPORT_SYMBOL  Module two,Init!\n");
	        function_two();
	        return 0;
	}
	 
	static void __exit export_symbol_exit(void)
	{
	        printk("EXPORT_SYMBOL  Module two,Exit!\n");
	}
	 
	module_init(export_symbol_init);
	module_exit(export_symbol_exit);



#note：使用其他平台，编译器需要适配
如果想编译在模拟开发板上运行的模块，就需要采用另一种方法，利用Linux 源文件根目录下Makefile 的 SUBDIRS 参数，下面来说明一下操作步骤：

1. 进入到已经编译生成Linux源文件根目录下 例如： linux-4.1.38，前提是已经利用这个目录编译生成过内核目标文件 ；
2. 执行 
export ARCH=arm
export CROSS_COMPILE=arm-linux-gnueabi-
make modules SUBDIRS= xxxx/hello_module    （xxxx为需要编译的模块所在目录）

**NOTE:**
在目标开发板上执行  rmmod 时会提示 rmmod: can't change directory to '/lib/modules': No such file or directory这个错误，是由于没有 /lib/modules/4.1.38(内核版本号) 这个目录导致的，在目标开发板上建立一下这个目录即可，是空目录，不需要任何文件。





