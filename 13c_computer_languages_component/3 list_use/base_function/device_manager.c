
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "device_manager.h"
#include "list.h"
#define num_of_list 2
//�豸����ṹ
typedef struct{
	LHead head;
	int lock;
}DevManCtx;

//�豸�ڵ�
typedef struct{
	LHead node;
	NDevice dev;
}DeviceNode;


static DevManCtx _DevManCtx[num_of_list];
static int _DevManInited = 0;




void Lock_Init(int *lock)
{
	*lock=0;
}
void Lock_Lock(int *lock)
{
	*lock=1;
}
void Lock_ULock(int *lock)
{
	*lock=0;
}
int Lock_check(int *lock)
{
	return *lock;
}


int dev_man_add(int type, NDevice newdev)
{
	DeviceNode *pDevNode;
	LHead *pos;
	if (type >= num_of_list)return -1;
	if (!_DevManInited)return -1;

	Lock_Lock(&_DevManCtx[type].lock);
	list_for_each(pos,&_DevManCtx[type].head)//��������
	{

		pDevNode = (DeviceNode*)pos;
		//ͨ��mac�ж���ָ�����豸�������˳�����������豸
		if (0 == strncmp(pDevNode->dev.id,newdev.id,sizeof(pDevNode->dev.id)))
		{
			break;
		}
	}

	if (pos == &_DevManCtx[type].head){
		pDevNode = (DeviceNode*)malloc(sizeof(DeviceNode));//�����豸�ռ�
		if (NULL == pDevNode)
		{
			Lock_ULock(&_DevManCtx[type].lock);
			return -1;
		}
		memcpy(&pDevNode->dev,&newdev,sizeof(newdev));
		list_add(&pDevNode->node,&_DevManCtx[type].head);   //���豸���뵽������
	}
	Lock_ULock(&_DevManCtx[type].lock);

	return 0;
}

int dev_man_modify(int type,NDevice newdev)
{
	DeviceNode *pDevNode;
	LHead *pos;
	if (type >= num_of_list)return -1;
	if (!_DevManInited)return -1;
	Lock_Lock(&_DevManCtx[type].lock);
	list_for_each(pos,&_DevManCtx[type].head)//��������
	{

		pDevNode = (DeviceNode*)pos;
		if (0 == memcmp(pDevNode->dev.id,newdev.id,sizeof(pDevNode->dev.id)))
		{
			break;
		}
	}

	if (pos != &_DevManCtx[type].head)
	{
		memcpy(&pDevNode->dev,&newdev,sizeof(pDevNode->dev));
	}

	Lock_ULock(&_DevManCtx[type].lock);

	return 0;
}




int dev_man_get_device_by_id(int type,unsigned char *id,NDevice *outDev)
{
	DeviceNode *pDevNode = NULL;
	LHead *pos;
	
	if (type >= num_of_list)return -1;
	if (NULL == id || NULL == outDev)return -1;
	if (!_DevManInited)return -1;

	Lock_Lock(&_DevManCtx[type].lock);
	list_for_each(pos,&_DevManCtx[type].head)//�������������豸
	{
		pDevNode = (DeviceNode*)pos;
		//����ƥ���mac�豸
		if (0 == memcmp(pDevNode->dev.id,id,sizeof(pDevNode->dev.id)))
		{
			break;
		}
	}
	Lock_ULock(&_DevManCtx[type].lock);
	if (pos == &_DevManCtx[type].head)return -1;
	memcpy(outDev,&pDevNode->dev,sizeof(pDevNode->dev));

	return 0;
}

int dev_man_del_by_id(int type,unsigned char *id)
{
	DeviceNode *pDevNode = NULL;
	LHead *pos;
	int delFlag = 0;
	if (type >= num_of_list)return -1;
	if (NULL == id)return -1;
	if (!_DevManInited)return -1;

	Lock_Lock(&_DevManCtx[type].lock);
	list_for_each(pos,&_DevManCtx[type].head)//��������
	{
		pDevNode = (DeviceNode*)pos;
		//����ָ����mac���豸�����ڣ����������ɾ�������������ļ������ͷ��豸�ռ䣬�������ڣ����˳�
		if (0 == memcmp(&pDevNode->dev.id,id,sizeof(pDevNode->dev.id)))
		{
			list_del(pos);//��������ɾ���ýڵ�
			delFlag = 1;
			break;
		}
	}
	Lock_ULock(&_DevManCtx[type].lock);
	if (pos != &_DevManCtx[type].head){
		if (pDevNode && 1 == delFlag)
		{
			free(pDevNode);//�ͷſռ�
		}
	}



	return 0;
}


int dev_man_get_devices_num(int type)
{
	int num;
	if (type >= num_of_list)return -1;
	if (!_DevManInited)return -1;

	Lock_Lock(&_DevManCtx[type].lock);
	num = list_size(&_DevManCtx[type].head);
	Lock_ULock(&_DevManCtx[type].lock);

	return num;
}

int dev_man_init(void)
{
	if (_DevManInited)return 0;
	int i;
	for(i=0;i<num_of_list;i++)
	{
		INIT_LIST_HEAD(&_DevManCtx[i].head);//��ʼ������
		Lock_Init(&_DevManCtx[i].lock);//��ʼ����
	}
	_DevManInited = 1;

	return 0;
}



