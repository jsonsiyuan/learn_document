**WEB:**

> http://blog.sina.com.cn/s/blog_587c016a0100nfeq.html

**信号**

> 信号值位于SIGRTMIN和SIGRTMAX之间的信号都是可靠信号，可靠信号克服了信号可能丢失的问题。
> 
> 不可靠信号是信号值小于SIGRTMIN的信号
> 
> Linux在支持新版本的信号安装函数sigation（）以及信号发送函数sigqueue()的同时，仍然支持早期的signal（）信号安装函数，支持信号发送函数kill()。

**进程对信号的响应**

1. 忽略信号，即对信号不做任何处理，其中，有两个信号不能忽略：SIGKILL及SIGSTOP
2. 捕捉信号。定义信号处理函数，当信号发生时，执行相应的处理函数
3. 执行缺省操作，Linux对每种信号都规定了默认操作

**信号的发送**

	1、kill() 
	#include <sys/types.h> 
	#include <signal.h> 
	int kill(pid_t pid,int signo)

Kill()最常用于pid>0时的信号发送，调用成功返回 0； 否则，返回 -1。

	2、raise（） 
	#include <signal.h> 
	int raise(int signo)

向进程本身发送信号，参数为即将发送的信号值。调用成功返回 0；否则，返回 -1。

	3、sigqueue（） 
	#include <sys/types.h> 
	#include <signal.h> 
	int sigqueue(pid_t pid, int sig, const union sigval val)  

	typedef union sigval {
	    int  sival_int;
	    void *sival_ptr;
	}sigval_t;

---
	4、alarm（） 
	#include <unistd.h> 
	unsigned int alarm(unsigned int seconds) 
1. 专门为SIGALRM信号而设，在指定的时间seconds秒后，将向进程本身发送SIGALRM信号，又称为闹钟时间。
2. 进程调用alarm后，任何以前的alarm()调用都将无效。如果参数seconds为零，那么进程内将不再包含任何闹钟时间。 
3. 返回值，如果调用alarm（）前，进程中已经设置了闹钟时间，则返回上一个闹钟时间的剩余时间，否则返回0。

------
	5、setitimer（） 
	#include <sys/time.h> 
	int setitimer(int which, const struct itimerval *value, struct itimerval *ovalue)); 
	setitimer()比alarm功能强大，支持3种类型的定时器：
	
1. ITIMER_REAL：	设定绝对时间；经过指定的时间后，内核将发送SIGALRM信号给本进程；
2. ITIMER_VIRTUAL 设定程序执行时间；经过指定的时间后，内核将发送SIGVTALRM信号给本进程；
3. ITIMER_PROF 设定进程执行以及内核因本进程而消耗的时间和，经过指定的时间后，内核将发送ITIMER_VIRTUAL信号给本进程；

------

	6、abort() 
	#include <stdlib.h> 
	void abort(void);

**信号的安装**


**signal()**

	#include <signal.h> 
	void (*signal(int signum, void (*handler))(int)))(int); 

1. 第一个参数指定信号的值，第二个参数指定针对前面信号值的处理，可以忽略该信号（参数设为SIG_IGN）；
2. 可以采用系统默认方式处理信号(参数设为SIG_DFL)；也可以自己实现处理方式(参数指定一个函数地址)。 
3. 如果signal()调用成功，返回最后一次为安装信号signum而调用signal()时的handler值；失败则返回SIG_ERR。

----
**sigaction()**

	#include <signal.h> 
	int sigaction(int signum,const struct sigaction *act,struct sigaction *oldact));

**note：比较新的，复杂的。**