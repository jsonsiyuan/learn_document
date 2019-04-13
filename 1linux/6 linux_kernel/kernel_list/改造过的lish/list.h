#ifndef _YC_LLIST_H
#define _YC_LLIST_H

#ifdef __cplusplus
extern "C"
{
#endif

//����ṹ
struct list_head {
	struct list_head *next;
	struct list_head *prev;
};

typedef struct list_head LHead;

//��ʼ������ͷ
#define INIT_LIST_HEAD(head) do {			\
		(head)->next = (head)->prev = head;	\
	} while (0)

#define list_entry(ptr, type, member)					\
	((type *)((char *)(ptr)-(unsigned long)(&((type *)0)->member)))

/*��������*/
#define list_for_each(pos, head)				     \
	for (pos = (head)->next; pos != (head); pos = pos->next)



//��ӽڵ㵽������ͷ���
void list_add (struct list_head *_new, struct list_head *head);

//��β������豸�ڵ㵽����
void list_add_tail (struct list_head *_new, struct list_head *head);

//��������ɾ���ڵ�
void list_del (struct list_head *old);

//�ж������Ƿ�Ϊ��
//return 1:�� ��0;��Ϊ��
int list_empty (struct list_head *head);

//��ȡ�����е��豸����
int list_size(struct list_head *head);


#ifdef __cplusplus
}
#endif
#endif /* _LLIST_H */


