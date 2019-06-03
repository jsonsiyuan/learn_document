# ALIOS-THING 使用笔记 （V2.1.0） #

## API 参考文档 ##

> https://github.com/alibaba/AliOS-Things/wiki/AliOS-Things-API-YLOOP-Guide

## alios-与智能生活平台（飞燕）使用文档 ##

> https://living.aliyun.com/doc?spm=a2c9o.12549863.0.0.4e9d7946zwCcCi#index.html
> 
> https://blog.csdn.net/qq_28877125/article/details/82887088

> https://blog.csdn.net/xh870189248/article/details/82692224

### 参考的demo ###

> 参考demo_wifi单品开发

### netmgr 介绍 ###
-----
**底层wifi API 再次抽象层**

## 一键配网 关键文件内容 ##

> AliOS-Things\middleware\linkkit\sdk-c\src\ref-impl\hal\os\alios 修改一键配网参数
> AliOS-Things\middleware\linkkit\sdk-c\src\services\awss 一键配网相关内容


## 版本号管理问题 ##
demo：

	app-1.0.0-20190523.1138

AliOS-Things\build\build_rules\aos_target_config.mk

	# Set APP_VERSION used by OTA
	CONFIG_SYSINFO_APP_VERSION = app-2.0.0-$(CURRENT_TIME)


### Alios Things的Flash划分规则 ###

	https://github.com/alibaba/AliOS-Things/wiki/OTA-Flash-Partitions-Overview.zh

## 取巧的方法 ##

**设备状态改变（例如从sta模式到配网模式）。通过重启，重新开始来避免一些逻辑**
