# kfifo #

kfifo是Linux内核一个通用的队列实现。
它采用了前面提到的环形缓冲区来实现，提供一个无边界的字节流服务。

## web ##
	https://blog.csdn.net/alice_ice/article/details/14104889
	https://www.linuxidc.com/Linux/2016-12/137936.htm

## key API ##

	#defien DEFINE_KFIFO(fifo,type,size)
	#define kfifo_from_user(fifo,from,len,copied)
	#define kfifo_to_user(fifo,to,len,copied)