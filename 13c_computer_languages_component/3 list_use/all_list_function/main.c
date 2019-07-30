
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "device_manager.h"
unsigned char array1[4]={1,2,3,4};
unsigned char array2[4]={2,2,3,4};
unsigned char array3[4]={3,2,3,4};
unsigned char array4[4]={4,2,3,4};
unsigned char array5[4]={5,2,3,4};





void main(void)
{
	int num_tmp;
	NDevice data_tmp;

	dev_man_init();
	num_tmp=dev_man_get_devices_num(0);
	printf("now list number is %d \r\n",num_tmp);
	/****/
	memset(data_tmp.id,0,sizeof(data_tmp.id));
	memcpy(data_tmp.id,array1,sizeof(data_tmp.id));
	dev_man_add(0, data_tmp);
	/****/
	memset(data_tmp.id,0,sizeof(data_tmp.id));
	memcpy(data_tmp.id,array2,sizeof(data_tmp.id));
	dev_man_add(0, data_tmp);
	/****/
	memset(data_tmp.id,0,sizeof(data_tmp.id));
	memcpy(data_tmp.id,array3,sizeof(data_tmp.id));
	dev_man_add(0, data_tmp);
	/****/
	num_tmp=dev_man_get_devices_num(0);
	printf("now list number is %d \r\n",num_tmp);
	/****/
	memset(data_tmp.id,0,sizeof(data_tmp.id));
	memcpy(data_tmp.id,array4,sizeof(data_tmp.id));
	dev_man_add(0, data_tmp);
	/****/
	memset(data_tmp.id,0,sizeof(data_tmp.id));
	memcpy(data_tmp.id,array5,sizeof(data_tmp.id));
	dev_man_add(0, data_tmp);
	/**/
	num_tmp=dev_man_get_devices_num(0);
	printf("now list number is %d \r\n",num_tmp);
	/**/
	memset(data_tmp.id,0,sizeof(data_tmp.id));
	memcpy(data_tmp.id,array5,sizeof(data_tmp.id));
	dev_man_add(0, data_tmp);
	/**/
	num_tmp=dev_man_get_devices_num(0);
	printf("now list number is %d \r\n",num_tmp);

	dev_man_del_by_id(0,array5);
	dev_man_del_by_id(0,array4);
	/**/
	num_tmp=dev_man_get_devices_num(0);
	printf("now list number is %d \r\n",num_tmp);
	
}
