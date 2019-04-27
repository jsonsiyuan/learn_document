# c和指针 #

---

## 常量配合指针 ##

有两样东西都有可能成为常量-指针变量和它所指向的实体。

	int const *pci; //指向整形常量的指针。你可以修改指针的值，但你不能修改它所指向的值。可以修改指向的内容，不能改指向内容的值

	int * const cpi ；//指向整形的常量指针。此时指针是常量，它的值无法修改，但你可以修改它所指向的整形的值。不可以修改指向的内容，能改指向内容的值

	int const *const cpi;都不能修改

 ## 指针常量 ##

	*（int*）100=25；

把25存储于位置100。这个方法只存在寄存器的使用

## 指针的运算 ##

- 指针是float类型的
- 当指针和一个整形量执行算术运算时，整数在执行运算前始终会根据合适的大小进行调整。这个合适的大小就是指向类型的大小。

## 可变参数列表 ##

stdarg 宏来确定使用.

	va_list var_arg;
	va_start(va_arg,n_values);
	.	
	.
	.
	va_end(var_arg,int);

## 数组在函数中的参数 ##

其实是一个指针

## 多维数组 ##

	
	matrix[3][10]

	matrix //指向包含10个整形元素的数组的指针
	*（matrix+1）//指向整形的指针
	*(*（matrix+1）+1) //==matrix[1][1]

## 多维数组在函数参数中 ##

	void fun2 (int (*mat)[10]);
	void fun2 (int mat[][10]);
	void fun2(int **mat);

## 内存函数 ##

    memset（）
    memcpy（）


## 结构体自引用 ##
	对的值：
	
	struct SELE_REF2{
		int a;
		struct SELE_REF2 *b;
		int c;
	}
## 结构的存储分配 ##

	offsetof（type，member）;

## 结构体的段位 ##

		struct CHAR
	{
		unsigned ch :7;
		unsigned font :6;
		unsigned size:19;
	}
	struct CHAR	 ch1;

## 函数指针 ##

	int （*f）(); 函数指针
	int (*f[])();函数指针数组

----- 
	int f (int);
	int (*pf)(int)=&f;//&可有可无，常见的编译器会自动搞定

	int ans；
	ans=f(25);
	ans=(*pf)(25);
	ans=pf(25);


## 预定义符号 ##

	__FILE__
	__LINE__
	__DATE__
	__TIME__
	__STDC__

## volatile ##

防止他以一种可能修改程序的方式 优化程序

## enum ##

	demo：
	// 灯状态枚举
	typedef  enum
	{
	    /// 红灯
	    red_led=0,  
	    /// 白灯
	    white_led=1,       
	}STATUS_LED_T;

## typedef ##

	// PFun是我们创建的一个类型别名
	typedef int *(*PFun)(int,char*);
	// 使用定义的新类型来声明对象，等价于int*(*a[5])(int,char*);
	PFun a[5];




	
	
	
	