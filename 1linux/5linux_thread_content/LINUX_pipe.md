**WEB:**

> http://blog.sina.com.cn/s/blog_587c016a0100nfeq.html

## 管道 ##

管道是半双工的，数据只能向一个方向流动；需要双方通信时，需要建立起两个管道.

	#include <unistd.h>
	int pipe(int fd[2])

> 在实际应用中没有太大意义，因此，一个进程在由pipe()创建管道后，一般再fork一个子进程，然后通过管道实现父子进程间的通信
即一端只能用于读，由描述字fd[0]表示，称其为管道读端；另一端则只能用于写，由描述字fd[1]来表示，称其为管道写端

**NOTE:**
> 如果请求的字节数目大于PIPE_BUF
> PIPE_BUF在include/linux/limits.h中定义
> 
> linux将不保证写入的原子性，管道缓冲区一有空闲区域，写进程就会试图向管道写入数据。如果读进程不读走管道缓冲区中的数据，那么写操作将一直阻塞

**有名管道**

	#include <sys/types.h>
	#include <sys/stat.h>
	int mkfifo(const char * pathname, mode_t mode)

> 该函数的第一个参数是一个普通的路径名，也就是创建后FIFO的名字。第二个参数与打开普通文件的open()函数中的mode 参数相同。 
> 
> 如果mkfifo的第一个参数是一个已经存在的路径名时，会返回EEXIST错误，所以一般典型的调用代码首先会检查是否返回该错误，如果确实返回该错误，那么只要调用打开FIFO的函数就可以了。
> 
> 一般文件的I/O函数都可以用于FIFO，如close、read、write等等。



如果FIFO中有数据，则设置了阻塞标志的读操作不会因为FIFO中的字节数小于请求读的字节数而阻塞，此时，读操作会返回FIFO中现有的数据量。

当要写入的数据量不大于PIPE_BUF时，linux将保证写入的原子性

当要写入的数据量大于PIPE_BUF时，linux将不再保证写入的原子性

## NOTE ##

> 附1：kill -l 的运行结果，显示了当前系统支持的所有信号



