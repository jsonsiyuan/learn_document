
# kfifo 使用方法 #

## 建立 ##

	#define kfifo_alloc(fifo, size, gfp_mask) 
	
	静态分配
	#define DECLARE_KFIFO(fifo, type, size)
	#define INIT_KFIFO(fifo) 

## 入列 ##
	#define	kfifo_in(fifo, buf, n)

## 出列 ##
	#define	kfifo_out(fifo, buf, n) 
## 获得大小 ##
	#define kfifo_size(fifo)	
	#define kfifo_len(fifo) 
	#define	kfifo_is_empty(fifo)
	#define	kfifo_is_full(fifo)


## 用户接口 ##
	#define	kfifo_from_user
	#define	kfifo_to_user