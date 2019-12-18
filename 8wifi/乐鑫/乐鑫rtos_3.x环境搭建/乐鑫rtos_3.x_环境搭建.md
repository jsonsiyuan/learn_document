# 乐鑫 rtos 3.x 环境搭建 #

## 参考文档 ##

>https://docs.espressif.com/projects/esp8266-rtos-sdk/en/latest/

## linux 版本##
**使用Ubuntu 16的版本**

## 解决 Permission issues /dev/ttyUSB0 ## 

- sudo usermod -a -G dialout $USER
- sudo usermod -a -G uucp $USER

## IDF_PATH ##

- access `ESP8266_RTOS_SDK` using `IDF_PATH` environment variable.
- Set up IDF_PATH by adding the following line to `~/.profile` file

--------

    export IDF_PATH=~/esp/ESP8266_RTOS_SDK


- 测试code 
------

	printenv IDF_PATH



## 在linux 环境下 download ##

	make flash
	make erase_flash

- `Permission issues /dev/ttyUSB*` `[Errno 13] could not open port /dev/ttyUSB0`
---
	ls /dev |grep tty*
	sudo usermod -a -G dialout $USER
	sudo usermod -a -G uucp $USER 

## 3.0 flash 分布 ##
### Partition Tables ###

	# Name,   Type, SubType, Offset,   Size
	nvs,      data, nvs,     0x9000,   0x4000
	otadata,  data, ota,     0xd000,   0x2000
	phy_init, data, phy,     0xf000,   0x1000
	ota_0,    app,  ota_0,   0x10000,  0xF0000
	ota_1,    app,  ota_1,   0x110000, 0xF0000

	# Name,   Type, SubType, Offset,  Size
	nvs,      data, nvs,     0x9000,  0x6000
	phy_init, data, phy,     0xf000,  0x1000
	factory,  app,  factory, 0x10000, 0xF0000

flash 操作：
	ESP8266_RTOS_SDK\components\spi_flash
	
## 备注 ##

**环境的配置的改变，最简单的方法就是reboot**

#目前最好的版本3.1#








