

#ifndef DEVICE_MANAGER_H_
#define DEVICE_MANAGER_H_




typedef struct{
	unsigned char  id[4];
}NDevice;



int dev_man_add(int index, NDevice newdev);
int dev_man_modify(int index,NDevice newdev);
int dev_man_get_device_by_id(int index,unsigned char *id,NDevice *outDev);
int dev_man_get_Yield(int index,NDevice *outDev);
int dev_man_del_by_id(int index,unsigned char *id);
int dev_man_get_devices_num(int index);
int dev_man_init(void);







#endif /* DEVICE_MANAGER_H_ */
