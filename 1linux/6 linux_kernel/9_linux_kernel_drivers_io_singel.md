# 异步通知 #

异步通知使用系统调用的signal函数和sigcation函数。signal函数让一个信号和一个函数对应，每当接收到这个信号时，会调用相应的函数处理。

## 在字符设备中添加异步通知 ##

### 1初始化一个struct fasync_struct 的链表头###

	demo:
	struct fasync_struct *fasync

### 异步通知在内核中使用struct fasync_struct 数据结构来描述。 ###

	demo:
	<include/linux/fs.h>
	struct fasync_struct 
	{
		spinlock_t fa_lock;
		int magic;
		struct fasync_struct *fa_next /*单列表*/
		struct file *fa_file;
		struct reu_head fa_rcu;
	}

### 设备驱动的file_operations 的操作方法中有一个fasync的方法，需要实现 ###

	demo：

	file_operations.fasync=demodrv_fasync

	static int demodrv_fasync(int fd,struct file *file ,int on)
	{
		struct mydemo_private_data *data =file->private_data;
		syruct mydemo_device *device =data-<device;
		return fasync_helper(fa,file,on,&device->fasync);//使用fasync_helper 函数来构造struct fasync_struct 类型的节点，并添加到系统的列表中。
	}

### 修改读和写的函数 ###

read 中

	kill_fasync(&device->fasync,SIGIO,POLL_IN);

### 应用层code编写 ###

	 void my_signal_fun(int signum,siginfo_t *siginfo,void *act)
	{
		int ret;
		char buf[64];
		if(signum==SIGIO)
		{
			if(siginfo->si_band&POLLIN)
			{
				printf("");
				if(ret=read(fd,buf,sizeof(buf))!=-1)
				{
					puts(buf);
				}
			}
		} 
		if(siginfo->si_band &POLLPUT)
		{
			printf("FIFO is not full\r\n");
		}
	}



	int main (int argc,char *argv[])
	{
		int ret;
		int flag;

		struct sigaction act,oldact;

		sigemptyset(&act.sa_mask);
		sigaddset(&act.sa_mask,SIGIO);
		act.sa_flags=SA_SIGINFO;
		act.sa_sigaction=my_signal_fun;
		if(sigaction(SIGIO,&act,&oldact)==-1)
		go to fail;


		/*设置异步I/O 所有权*/
		if(fcntl(fa,F_SETOWN,getpid())==-1)
		{}
		/*设置SIGIO信号*/
		if(fcntl(fd,F_SETSIG,SIGIO)==-1)
		{}

		/*获得文件flags*/
		if((flag=fcntl(fa,F_GETFL))==-1)
		{}

		/*设置文件flags ，设置FASYNC,支持异步通知*/
		if(fcntl(fa,F_SETFL,flag|FASYNC)==-1)
		{}
	}