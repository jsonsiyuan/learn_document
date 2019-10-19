# linux ioctl函数详解 #

## 应用层使用 ##
ioctl是设备驱动程序中对设备的I/O通道进行管理的函数。所谓对I/O通道进行管理，就是对设备的一些特性进行控制，例如串口的传输波特率、马达的转速等等

	int ioctl(int fd, ind cmd, …)
其中fd是用户程序打开设备时使用open函数返回的文件标示符，cmd是用户程序对设备的控制命令，至于后面的省略号，那是一些补充参数，一般最多一个，这个参数的有无和cmd的意义相关

## 驱动层使用 ##

主要为两个API
	long (*unlocked_ioctl) (struct file *, unsigned int, unsigned long);
	long (*compat_ioctl) (struct file *, unsigned int, unsigned long);

note： 因为在 vfs 层的代码是直接调用 unlocked_ioctl 函数


其中驱动的编写，内核提供了很多宏


demo：

	static const struct file_operations fops = {
	
	    .unlocked_ioctl = test_ioctl,
	}; 

	static long test_ioctl(struct file *file, unsigned int cmd, \
	                        unsigned long arg)
	{
	    //printk("[%s]\n", __func__);
	
	    int ret;
	    struct msg my_msg;
	
	    /* 检查设备类型 */
	    if (_IOC_TYPE(cmd) != IOC_MAGIC) {
	        pr_err("[%s] command type [%c] error!\n", \
	            __func__, _IOC_TYPE(cmd));
	        return -ENOTTY; 
	    }
	
	    /* 检查序数 */
	    if (_IOC_NR(cmd) > IOC_MAXNR) { 
	        pr_err("[%s] command numer [%d] exceeded!\n", 
	            __func__, _IOC_NR(cmd));
	        return -ENOTTY;
	    }    
	
	    /* 检查访问模式 */
	    if (_IOC_DIR(cmd) & _IOC_READ)
	        ret= !access_ok(VERIFY_WRITE, (void __user *)arg, \
	                _IOC_SIZE(cmd));
	    else if (_IOC_DIR(cmd) & _IOC_WRITE)
	        ret= !access_ok(VERIFY_READ, (void __user *)arg, \
	                _IOC_SIZE(cmd));
	    if (ret)
	        return -EFAULT;
	
	    switch(cmd) {
	    /* 初始化设备 */
	    case IOCINIT:
	        init();
	        break;
	
	    /* 读寄存器 */
	    case IOCGREG:
	        ret = copy_from_user(&msg, \
	            (struct msg __user *)arg, sizeof(my_msg));
	        if (ret) 
	            return -EFAULT;
	        msg->data = read_reg(msg->addr);
	        ret = copy_to_user((struct msg __user *)arg, \
	                &msg, sizeof(my_msg));
	        if (ret) 
	            return -EFAULT;
	        break;
	
	    /* 写寄存器 */
	    case IOCWREG:
	        ret = copy_from_user(&msg, \
	            (struct msg __user *)arg, sizeof(my_msg));
	        if (ret) 
	            return -EFAULT;
	        write_reg(msg->addr, msg->data);
	        break;
	
	    default:
	        return -ENOTTY;
	    }
	
	    return 0;
	}



