# linux time #
web：

> https://www.cnblogs.com/embedded-linux/p/7087558.html
> https://blog.csdn.net/luotuo44/article/details/39374759
> https://www.cnblogs.com/hushaojun/p/7990951.html
## struct  timeval ##

	struct timeval 
	{
	time_t tv_sec; // seconds 
	long tv_usec; // microseconds 
	};
	
	struct timezone{ 
	int tz_minuteswest; //miniutes west of Greenwich 
	int tz_dsttime; //type of DST correction 
	};
> struct timeval有两个成员，一个是秒，一个是微秒, 所以最高精确度是微秒。

### gettimeofday  ###

获取系统的时间：

	int gettimeofday(struct timeval *tv, struct timezone *tz)

常用：

	gettimeofday(&now, NULL);

### 相关操作函数 ###
	#include <sys/time.h>
	
	void timeradd(struct timeval *a, struct timeval *b,
	             struct timeval *res);
	
	void timersub(struct timeval *a, struct timeval *b,
	             struct timeval *res);
	
	void timerclear(struct timeval *tvp);
	
	int timerisset(struct timeval *tvp);
	
	int timercmp(struct timeval *a, struct timeval *b, CMP);

