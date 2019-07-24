# MQTT 使用记录 #

## 服务器 ##

web：
	http://www.mosquitto.org/
tool:
	https://github.com/mqtt/mqtt.github.io/wiki/software?id=software
	
博客
	https://lanseyujie.com/post/mosquitto-installation-and-usage.html
	https://www.cnblogs.com/chen1-kerr/p/7258487.html
	https://www.cnblogs.com/yueli/category/1072998.html


# 自己的总结 #
## 下载 ##

**我使用官网下载**

	tar zxvf mosquitto-xx.tar.gz

## 编译和安装 ##

	cd mosquitto-xx
	make
	sudo make install

----

注意点：配置文件config.mk，其中包含了所有Mosquitto的安装选项

**个人介意不进行修改**

make 遇到问题，需要安装一些东西

	sudo apt install g++ libssl-dev libc-ares-dev uuid-dev xsltproc docbook-xsl

## 运行和配置 ##

切换到 /etc/mosquitto目录下 新建配置并修改

	sudo cp mosquitto.conf.example mosquitto.conf

运行新配置

	mosquitto -c /etc/mosquitto/mosquitto.conf

重启Mosquitto
	ps -A | grep mosquitto
	kill -9 21674

启动配置内容

	-c是指定一个配置文件
	-d作为守护进程
	-p是指定端口，默认1883
	-v详细日志输出

## mosquitto 自带client调测 ##

发布使用mosquitto_pub命令，订阅使用mosquitto_sub命令
	
	参数	描述
	-h	服务器主机，默认localhost
	-t	指定主题
	-u	用户名
	-P	密码
	-i	客户端id，唯一
	-m	发布的消息内容
---
demo:
	mosquitto_sub -v -t testtopic
	mosquitto_pub -t testtopic -m "Hello World"


调试问题：

**报错./mosquitto_sub: error while loading shared libraries: libmosquitto.so.1: cannot open shared object file: No such file or directory**

	sudo ln -s /usr/local/lib/libmosquitto.so.1 /usr/lib/libmosquitto.so.1
	ldconfig


##mosquitto.conf 详细讲解##
https://www.cnblogs.com/yueli/p/7486043.html

### 用户机制 ###
	sudo nano /etc/mosquitto/mosquitto.conf
	

	# 禁止匿名访问
	allow_anonymous false
	# 账号密码文件
	password_file /etc/mosquitto/pwfile
	
** 创建用户名和密码、打开命令窗口 键入如下命令**
加入admin **用户，提示连续两次输入密码**。
	mosquitto_passwd -c /etc/mosquitto/pwfile.example admin

### 用户权限管理 ###

	# 配置topic和用户关系
	acl_file /etc/mosquitto/aclfile
**配置topic**

	sudo /etc/mosquitto/aclfile
	
	user choi
	topic write testtopic/#
	
	user choi
	topic read testtopic/#
	
	# 订阅主题
	mosquitto_sub -h 127.0.0.1 -t testtopic -u choi -P lanseyujie
	
	# 发布消息
	mosquitto_pub -h 127.0.0.1 -t testtopic -u choi -P lanseyujie -m "Hello MQTT"

### Mosquitto 高级应用之SSL/TLS ###

准本工作： 一台 Linux 服务器、 安装好 openssl





## 代码使用 ##
**相关代码功能介绍**
**eclipse.paho**
http://www.eclipse.org/paho/downloads.php


## Desktop tools ##

MQTT.fx - MQTT.fx is a MQTT Client written in Java based on Eclipse Paho.
http://mqttfx.org/
教程
https://www.alibabacloud.com/help/zh/doc-detail/86706.htm












