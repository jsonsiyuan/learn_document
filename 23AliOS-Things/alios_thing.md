# ALIOS-THING 指导 #

## API 参考文档 ##

> https://github.com/alibaba/AliOS-Things/wiki/AliOS-Things-API-YLOOP-Guide

## alios-与智能生活平台（飞燕）使用文档 ##

> https://living.aliyun.com/doc?spm=a2c9o.12549863.0.0.4e9d7946zwCcCi#index.html
> 
> https://blog.csdn.net/qq_28877125/article/details/82887088

> https://blog.csdn.net/xh870189248/article/details/82692224

### netmgr 介绍 ###
-----
**底层wifiAPI 再次抽象层**

## 关键文件内容 ##

> AliOS-Things\middleware\linkkit\sdk-c\src\ref-impl\hal\os\alios 修改配网参数
> AliOS-Things\middleware\linkkit\sdk-c\src\services\awss 一键配网相关内容

## 存在的问题 ##

- 一键配网必须从起。没有找到断网后，内部重连未找到

## 版本号管理 ##
demo：

	app-1.0.0-20190523.1138

AliOS-Things\build\build_rules\aos_target_config.mk

	# Set APP_VERSION used by OTA
	CONFIG_SYSINFO_APP_VERSION = app-2.0.0-$(CURRENT_TIME)

