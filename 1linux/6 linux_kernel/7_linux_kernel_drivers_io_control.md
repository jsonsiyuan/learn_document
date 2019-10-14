# 特别的IO操作 #

## 非阻塞I/O ##

demo：

	if(file->f_flags&O_NONBLOCK)
		return EAGAIN//(可能是 -EAGAIN)


## 阻塞I/O和 ##

在linux 内核中，采用一个称为等待队列(wait queue )机制来实现进程的阻塞操作

### 等待队列头 ###

定义一个（wait_queue_head_t）的数据结构，定义在<linux/waiy.h>中。
	struct __wait_queue_head
	{
		spinlock_t lock;
		struct list_head task_list;

	}

	typedef struct __wait_queue_head wait_queue_head_t;
	
	使用下面的宏来静态初始化：
	DECLARE_WAIT_QUEUE_HEAD(name)
	
	使用动态初始
	
	wait_queue_head_t my_queue;
	init_waitqueue_head(&my_queue);

### 等待队列元素 wait_queue_t ###

	struct __wait_queue
	{
		unsigned int flags;
		void *private;
		wait_queue_func_t func;
		struct list_head task_list;
	};
	typedef struct __wait_queue wait_queue_t;
    
### 睡眠等待 ###
	linux 内核提供了简单的睡眠方式，并封装成wait_event()的宏及其他几个扩展宏。

	wait_event(wq,condition)
	wait_event_interruptible(wq,condition)
	wait_event_timeout(wq,condition,timeout)
	wait_event_interruptible_timeout(wq,condition,timeout)

	wq 表示等待队列
	condition 布什尔表达式
	timeout 表示timeout时间到达之后，进程会被唤醒
	wait_event_interruptible() 会让进程进入可中断睡眠状态。
	wait_event()会让进程进入不可，一般驱动程序不会采用这个睡眠模式

### 唤醒 ###

	wake_up(x)
	wake_up_interruptible(x)

### 使用总结 ###

wake_up()应该和wait_event()或者wait_event_timeout()配对使用
wake_up_interruptible()应该和wait_event_interruptible()和wait_event_interruptible_timeout()


### key code ###

#### 初始化队列 ####
	wait_waitqueue_t read_queue

#### read函数中 ####

	wait_event_interruptible()

#### write 中 ####
	wake_up_interruptible()






	 


