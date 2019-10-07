# linux 内核基础知识 #
## linux 常见的编译器 ##

### gcc ###
- 预处理（Pre-Process）
- 编译（Compile）
- 汇编(Assemble)
- 连接（Link）


### ARM GCC ###

**交叉工具链命名规则**

    [arch] [-os] [-(gnueabi)]
    arch 芯片架构 如ARM MIPS
    os 表示目标操作系统
    eabi 嵌入式应用二进制接口

- arm-linux-gnueabi-gcc ARM32
- aarch-linux-gnueabi-gcc ARM64
- arm-linux-gnueabihf-gcc Hard Float


# linux 内核常用的c语言技巧 #

## 零数组 ##

	struct line
	{
		int length;
		char contents[0];#不占用空间，
	}
	struct line *thisline =malloc(sizeof(struct line)+this_length);
	thisline->length=this_length;
## case 范围变大 ##

	like:case 1 ... 3

## 标号元素 ##

结构体初始化 不需要按一定顺序。


## 可变参数宏 ##

    "##__VA_ARGE__"

		#define pr_debug(fmt,...) \
		dynamic_pr_debug(fmt,##__VA_ARGE__)
## 函数属性 ##

    __attribute__((attribute-list))
    format,按某个函数格式进行检查
	noreturn,表示没有返回
	const :只调用一次，之后只要返回结果

## 变量属性 &类型属性##
	__attribute__((attribute-list))
	
	alignment
	packed :使用最小的对齐方式
	section


## 内建函数 ##
	以_builtin_ 作为函数名前
    __builtin_expect   --->exp==c 的概率很大
    __builtin_prefetch --->主动进行数据预取 把数据放到cache中

## UL ##

    unsigned long

## 内核代码git ##

	git://git.kernel.org/pub/scm/linux/kernel/git/torvalds/linux.git
	https://git.kernel.org/pub/scm/linux/kernel/git/torvalds/linux.git

	





