# Linux fcntl函数详解 #

## 功能描述： ##
根据文件描述词来操作文件的特性。

## 文件控制函数 ##          
fcntl -- file control

## 头文件： ##
	#include <unistd.h>
	#include <fcntl.h>

## 函数原型： ##
	int fcntl(int fd, int cmd);
	int fcntl(int fd, int cmd, long arg);         
	int fcntl(int fd, int cmd, struct flock *lock);

## fcntl函数有5种功能 ##

- 复制一个现有的描述符（cmd=F_DUPFD
- 获得／设置文件描述符标记(cmd=F_GETFD或F_SETFD)
- 获得／设置文件状态标记(cmd=F_GETFL或F_SETFL)
- 获得／设置异步I/O所有权(cmd=F_GETOWN或F_SETOWN)
- 获得／设置记录锁(cmd=F_GETLK,F_SETLK或F_SETLKW)

## cmd 选项分析##

### F_DUPFD###
第一种类似于dup操作，在这里不做举例。（fcnlt(oldfd, F_DUPFD, 0) <==>dup2(oldfd, newfd)）

返回一个如下描述的(文件)描述符：

- 最小的大于或等于arg的一个可用的描述符 
- 与原始操作符一样的某对象的引用 
- 如果对象是文件(file)的话,返回一个新的描述符,这个描述符与arg共享相同的偏移量(offset)                    
- 相同的访问模式(读,写或读/写) 
- 相同的文件状态标志(如:两个文件描述符共享相同的状态标志) 
- 与新的文件描述符结合在一起的close-on-exec标志被设置成交叉式访问execve(2)的系统调用


### F_GETFD      ###

取得与文件描述符fd联合close-on-exec标志

note：
**close_on_exec 是一个进程所有文件描述符（文件句柄）的位图标志，每个比特位代表一个打开的文件描述符，用于确定在调用系统调用execve()时需要关闭的文件句柄（参见include/fcntl.h）**

### F_SETFD      ###

设置close-on-exec旗标。该旗标以参数arg的FD_CLOEXEC位决定

### F_GETFL ###

取得fd的文件状态标志

###  F_SETFL ###

设置给arg描述符状态标志,可以更改的几个标志是：O_APPEND， O_NONBLOCK，O_SYNC和O_ASYNC。

O_NONBLOCK   非阻塞I/O;
O_APPEND     强制每次写(write)操作都添加在文件大的末尾
O_DIRECT     最小化或去掉reading和writing的缓存影响.系统将企图避免缓存你的读或写的数据.
O_ASYNC      当I/O可用的时候,允许SIGIO信号发送到进程组

###  F_GETOWN ###

取得当前正在接收SIGIO或者SIGURG信号的进程id或进程组id,进程组id返回成负值

### F_SETOWN ###

设置将接收SIGIO和SIGURG信号的进程id或进程组id,进程组id通过提供负值的arg来说明,否则,arg将被认为是进程id


### F_GETLK,F_SETLK，F_SETLKW ###
设置获取记录锁

code demo：

	struct flcok
	
	{
	
	　　 short int l_type; /* 锁定的状态*/
	
	　　　　//这三个参数用于分段对文件加锁，若对整个文件加锁，则：l_whence=SEEK_SET,l_start=0,l_len=0;
	
	　　 short int l_whence;/*决定l_start位置*/
	
	　　 off_t l_start; /*锁定区域的开头位置*/
	
	　　 off_t l_len; /*锁定区域的大小*/
	
	　　 pid_t l_pid; /*锁定动作的进程*/
	
	};
	
	l_type 有三种状态:
	
	　　 F_RDLCK 建立一个供读取用的锁定
	
	　　 F_WRLCK 建立一个供写入用的锁定
	
	       F_UNLCK 删除之前建立的锁定
	
	l_whence 也有三种方式:
	
	　　SEEK_SET 以文件开头为锁定的起始位置。
	
	     SEEK_CUR 以目前文件读写位置为锁定的起始位置
	
	     SEEK_END 以文件结尾为锁定的起始位置。


	#include "filelock.h"
	
	/* 设置一把读锁 */
	int readLock(int fd, short start, short whence, short len) 
	{
	    struct flock lock;
	    lock.l_type = F_RDLCK;
	    lock.l_start = start;
	    lock.l_whence = whence;//SEEK_CUR,SEEK_SET,SEEK_END
	    lock.l_len = len;
	    lock.l_pid = getpid();
	//  阻塞方式加锁
	    if(fcntl(fd, F_SETLKW, &lock) == 0)
	        return 1;
	    
	    return 0;
	}
	
	/* 设置一把读锁 , 不等待 */
	int readLocknw(int fd, short start, short whence, short len) 
	{
	    struct flock lock;
	    lock.l_type = F_RDLCK;
	    lock.l_start = start;
	    lock.l_whence = whence;//SEEK_CUR,SEEK_SET,SEEK_END
	    lock.l_len = len;
	    lock.l_pid = getpid();
	//  非阻塞方式加锁
	    if(fcntl(fd, F_SETLK, &lock) == 0)
	        return 1;
	    
	    return 0;
	}
	/* 设置一把写锁 */
	int writeLock(int fd, short start, short whence, short len) 
	{
	    struct flock lock;
	    lock.l_type = F_WRLCK;
	    lock.l_start = start;
	    lock.l_whence = whence;
	    lock.l_len = len;
	    lock.l_pid = getpid();
	
	    //阻塞方式加锁
	    if(fcntl(fd, F_SETLKW, &lock) == 0)
	        return 1;
	    
	    return 0;
	}
	
	/* 设置一把写锁 */
	int writeLocknw(int fd, short start, short whence, short len) 
	{
	    struct flock lock;
	    lock.l_type = F_WRLCK;
	    lock.l_start = start;
	    lock.l_whence = whence;
	    lock.l_len = len;
	    lock.l_pid = getpid();
	
	    //非阻塞方式加锁
	    if(fcntl(fd, F_SETLK, &lock) == 0)
	        return 1;
	    
	    return 0;
	}
	
	/* 解锁 */
	int unlock(int fd, short start, short whence, short len) 
	{
	    struct flock lock;
	    lock.l_type = F_UNLCK;
	    lock.l_start = start;
	    lock.l_whence = whence;
	    lock.l_len = len;
	    lock.l_pid = getpid();
	
	    if(fcntl(fd, F_SETLKW, &lock) == 0)
	        return 1;
	
	    return 0;
	}