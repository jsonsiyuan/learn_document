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
    
    MODULE_LICENSE("GPL"); //哪个许可
    MODULE_AUTHOR("SUN");  //作者
    MODULE_DESCRIPTION("MY TEST MODUEL");//模块描述
    MODULE_ALIAS("MYTEST");//模块别名

## Makefile ##

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
2. module_param_array(name, type, num, perm);
3. MODULE_PARM_DESC(_parm,desc)

note：
    name:参数名
    type:byte,short,ushort,int,uint,long,ulong,char,bool
    perm:权限，0 表示不会出现在sysfs文件系统中。S_IRUGO(0444),可以被所以人阅读。S_IRUGO|S_IWUSR(0644).

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
	
demo：

1. insmod mymodule.ko mytest=200
2. <derver/misc/altera-stapl/altera.c> 一个例子
3. code：
	MODULE_LICENSE("Dual BSD/GPL");
	static int num=10;
	module_param(num,int,S_IRUGO);
	static int hello_init(void)
	{
	    printk("Hello module init./n");
	    printk("num=%d/n",num);
	    return 0;
	}
	static void   hello_exit(void)
	{
	    printk("Goodbye module exit./n");
	}
	module_init(hello_init);
	module_exit(hello_exit);
	MODULE_DESCRIPTION("a simple module");
	MODULE_ALIAS("hello");

	上面的num=10,则10是参数num的默认值。
	
	保存为源文件hello.c, 编译生成hello.ko , 当我们使用insmod进行载入时, 使用
	
	insmod hello.ko num=20
	
	则可以 cat /sys/module/hello/parameters/num ，看到为 20

## 符号共享 ##

    linux 提供两个宏
    EXPORT_SYMBOL()
    EXPORT_STMBOL_GPL()

    cat /proc/kallsyms
    1. 第一列是内核地址空间的地址
    2. 第2列是符号属性。T表示在TEXT。
    3. 第3列表示符号的字符串 EXPORT_SYMBOL 导出来的
    4. 那些内核模块在使用


**使用方法**

- 在模块函数定义之后使用“EXPORT_SYMBOL（函数名）”来声明
- 在调用该函数的另外一个模块中使用extern对之声明
- 先加载定义该函数的模块，然后再加载调用该函数的模块，请注意这个先后顺序。


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

------

使用的代码
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









