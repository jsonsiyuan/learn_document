# ARM GCC #
**命名规则**

    [arch] [-os] [-(gnueabi)]
    arch 芯片架构
    os 表示目标操作系统
    eabi 嵌入式应用二进制接口

- arm-linux-gnueabi-gcc ARM32
- aarch-linux-gnueabi-gcc ARM64
- arm-linux-gnueabihf-gcc Hard Float

# linux c #

- 语句表达式
- 
括号里的复合语句可以看做一个表达式。

- 零数组
- 

	struct line
	{
		int length;
		char contents[0];
	}

- case 范围变大
- 
case 1 ... 3

- 标号元素
- 
结构体初始化 不需要按一定顺序。

- 可变参数宏
- 
    "##__VA_ARGE__"

- 函数属性
- 
    __attribute__((attribute-list))
    format,noreturn

- 变量属性和类型属性
- 
alignment
packed
sections

- 内建函数
- 
    __builtin_expect   --->exp==c 的概率很大
    __builtin_prefetch --->主动进行数据预取

-UL
-
    unsigned long

# 实验 #

## demo1 ##

- arm-linux-gnueabi-gcc ...  --static

## demo2 ##

**内核链表**


	include/linux/list.h

## demo3 ##

**红黑树**

	lib/rbtree  include/linux/rbtree.h

**无锁环形缓冲**

	include/linux/kfifo.h
	kernel/kfifo.c

	





