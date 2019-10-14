# I/O多路复用 #

linux内核的file_operation 方法提供了poll方法的实现，当用户打开设备文件后，驱动程序的poll方法就会被调用。

## 设备驱动poll一般会执行步骤 ##

- 在一个或者多个等待队列中调用poll_wait()函数，把当前进程添加到指定的等待列表。当请求数据准备好了，会唤醒这些睡眠进程。
- 还回监听事件，也是POLLIN或者POLLOUT等掩码。

## DEMO ##

poll函数的使用

	static unsigned int demodrv_poll(struct file *file ,poll_table *wait)
	{
		int mask=0;
		struct mydemo_private_data *data =file->private_data;
		struct mydemo_device *device=dtat->device;
		poll_wait(file,&device->read_queue,wait);
		poll_wait(file.&device->write_queue,wait);
		if()
		{
			mask|=POLLIN|POLLRDNORM;
	
		}
	
		if()
		{
			mask|=POLLOUT|POLLWRNORM;
		}
		return mark;
	}


