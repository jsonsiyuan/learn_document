# Simple doubly linked list implementation. #

    include/linux/list.h

## test ##
gcc main.c device_manager.c -o test
## 初始化 ##

- 静态初始化
- 
	#define LIST_HEAD_INIT(name) { &(name), &(name) }

	#define LIST_HEAD(name) \
	struct list_head name = LIST_HEAD_INIT(name)

- 动态初始化
- 
    static inline void INIT_LIST_HEAD(struct list_head *list)
    {
    	list->next = list;
    	list->prev = list;
    }

## 添加 ##

    static inline void list_add(struct list_head *new, struct list_head *head)

## 遍历节点 ##

    #define list_for_each(pos, head) \
    	for (pos = (head)->next; pos != (head); pos = pos->next)

## 获得节点的数据 ##

    #define list_entry(ptr, type, member) \
    	container_of(ptr, type, member)


    #define container_of(ptr, type, member) ({			\
    	const typeof( ((type *)0)->member ) *__mptr = (ptr);	\
    	(type *)( (char *)__mptr - offsetof(type,member) );})



    



