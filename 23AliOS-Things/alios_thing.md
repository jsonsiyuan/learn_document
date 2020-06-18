# ALIOS-THING 使用笔记 （V2.1.0） #

## 一个环境搭建的demo ##
esp8266 阿里云测试
https://blog.csdn.net/lan120576664/article/details/80197396
https://blog.csdn.net/xh870189248/article/details/82692224
## API 参考文档 ##

> https://github.com/alibaba/AliOS-Things/wiki/AliOS-Things-API-YLOOP-Guide

（V3.1.0）
> https://help.aliyun.com/document_detail/161023.html?spm=a2c4g.11186623.6.542.7d6837e2syZfcU 

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

## alios mqtt 的做法##

- 对paho嵌入式c代码的分装
- 还是会使用一个线程进行异步使用。
- **使用list进行大量异步管理，使用消息id作为标识**

		void *thread_yield(void *pclient)
		{
		    while (g_thread_yield_running) {
		        IOT_MQTT_Yield(pclient, 200);
		
		        HAL_SleepMs(200);
		    }
		
		    return NULL;
		}

### 关键API ###

PATH：

	AliOS-Things\middleware\linkkit\sdk-c\src\protocol\mqtt\client
key function:
	IOT_MQTT_Yield
API:

	MQTTConnect
	MQTTPublish
	MQTTSubscribe
	MQTTUnsubscribe
	MQTTDisconnect
	MQTTPuback
	。。。
	iotx_mc_get_next_packetid


## 进入临界区 ##

	#include "k_api.h"
	CPSR_ALLOC();
	RHINO_CRITICAL_ENTER();
    /*内核临界区*/
	RHINO_CRITICAL_EXIT();

## Gateway 使用机制 ##
	https://code.aliyun.com/edward.yangx/public-docs/wikis/user-guide/linkkit/Archived/V230_Snapshot/programme/Gateway_Prog?spm=a2c4g.11186623.2.33.14831671HqOZU5
## 存在问题 ##

- ESP8266 在2.1版本上，配网成功后，进行通知时，有小小概率出现异常，芯片停止工作（1/80）。使用看门狗解决
- ESP8266 在3.0版本上，进行配网时，有小小概率出现，芯片停止工作（1/80）。使用看门狗解决


## 天猫平台的对接人 ##

	https://www.aligenie.com/doc/357554/fqn268