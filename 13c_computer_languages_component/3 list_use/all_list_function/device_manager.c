
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "device_manager.h"
#include "list.h"

typedef struct{
	struct list_head head;
	int lock;
}DevManCtx;

typedef struct{
	struct list_head node;
	NDevice dev;
}DeviceNode;


#define num_of_list 2




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


int dev_man_add(int index, NDevice newdev)
{
	DeviceNode *pDevNode;
	struct list_head *pos;
	if (index >= num_of_list)return -1;
	if (!_DevManInited)return -1;

	Lock_Lock(&_DevManCtx[index].lock);
	list_for_each(pos,&_DevManCtx[index].head)
	{

		pDevNode = (DeviceNode*)pos;
		if (0 == memcmp(pDevNode->dev.id,newdev.id,sizeof(pDevNode->dev.id)))
		{
			break;
		}
	}

	if (pos == &_DevManCtx[index].head)/*全部搜索完成后*/
	{
		pDevNode = (DeviceNode*)malloc(sizeof(DeviceNode));
		if (NULL == pDevNode)
		{
			Lock_ULock(&_DevManCtx[index].lock);
			return -1;
		}
		memcpy(&pDevNode->dev,&newdev,sizeof(newdev));
		list_add(&pDevNode->node,&_DevManCtx[index].head);  
	}
	Lock_ULock(&_DevManCtx[index].lock);

	return 0;
}

int dev_man_modify(int index,NDevice newdev)
{
	DeviceNode *pDevNode;
	struct list_head *pos;
	if (index >= num_of_list)return -1;
	if (!_DevManInited)return -1;
	Lock_Lock(&_DevManCtx[index].lock);
	list_for_each(pos,&_DevManCtx[index].head)
	{

		pDevNode = (DeviceNode*)pos;
		if (0 == memcmp(pDevNode->dev.id,newdev.id,sizeof(pDevNode->dev.id)))
		{
			break;
		}
	}

	if (pos != &_DevManCtx[index].head)/*没有搜索完成后*/
	{
		memcpy(&pDevNode->dev,&newdev,sizeof(pDevNode->dev));
	}

	Lock_ULock(&_DevManCtx[index].lock);

	return 0;
}




int dev_man_get_device_by_id(int index,unsigned char *id,NDevice *outDev)
{
	DeviceNode *pDevNode = NULL;
	struct list_head *pos;
	
	if (index >= num_of_list)return -1;
	if (NULL == id || NULL == outDev)return -1;
	if (!_DevManInited)return -1;

	Lock_Lock(&_DevManCtx[index].lock);
	list_for_each(pos,&_DevManCtx[index].head)
	{
		pDevNode = (DeviceNode*)pos;
		if (0 == memcmp(pDevNode->dev.id,id,sizeof(pDevNode->dev.id)))
		{
			break;
		}
	}
	Lock_ULock(&_DevManCtx[index].lock);
	if (pos == &_DevManCtx[index].head)return -1;
	memcpy(outDev,&pDevNode->dev,sizeof(pDevNode->dev));

	return 0;
}

int dev_man_del_by_id(int index,unsigned char *id)
{
	DeviceNode *pDevNode = NULL;
	struct list_head *pos;
	int delFlag = 0;
	if (index >= num_of_list)return -1;
	if (NULL == id)return -1;
	if (!_DevManInited)return -1;

	Lock_Lock(&_DevManCtx[index].lock);
	list_for_each(pos,&_DevManCtx[index].head)
	{
		pDevNode = (DeviceNode*)pos;
		
		if (0 == memcmp(&pDevNode->dev.id,id,sizeof(pDevNode->dev.id)))
		{
			list_del(pos);
			delFlag = 1;
			break;
		}
	}
	Lock_ULock(&_DevManCtx[index].lock);
	if (pos != &_DevManCtx[index].head){
		if (pDevNode && 1 == delFlag)
		{
			free(pDevNode);
		}
	}



	return 0;
}


int dev_man_get_devices_num(int index)
{
	int num=0;
	struct list_head *pos;
	if (index >= num_of_list)return -1;
	if (!_DevManInited)return -1;

	Lock_Lock(&_DevManCtx[index].lock);
	list_for_each(pos,&_DevManCtx[index].head)
	{
		num++;
	}
	Lock_ULock(&_DevManCtx[index].lock);

	return num;
}

int dev_man_init(void)
{
	if (_DevManInited)return 0;
	int i;
	for(i=0;i<num_of_list;i++)
	{
		INIT_LIST_HEAD(&_DevManCtx[i].head);
		Lock_Init(&_DevManCtx[i].lock);
	}
	_DevManInited = 1;

	return 0;
}



