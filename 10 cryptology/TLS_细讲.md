# TLS（ssl） 细讲#

TLS/SSL 分为两层协议。握手协议和记录层协议。
其中握手协议由4个子协议构成：

- 握手协议
- 警告协议
- 应用层协议 
- 密码切换协议（Change Cipher Spec）


## 记录层协议 ##
密码的状态和内容记录

## 握手协议 ##

- 互相换hello 子消息
- 交换证书和密码学信息
- 交换必要的密码学参数
- 通过预备主密钥和服务器、客户端的随机值生成主密钥
- 握手协议提供加密参数给TLS记录层协议
- 客户端和服务端校验对方的finished子消息，避免握手协议的消息被篡改

具体内容：
Client Hello 子消息
Server Hello 子消息
Server Certificate 子消息
Server Key Exchange  子消息
Server Hello Done 子消息
Client Key Exchange 子消息
计算主密钥和密码块
Change Cipher Spec 协议
finished 子消息

### 握手协议（sub） ###

握手协议主要工作就是客户端和服务端协商出双方都认可的密码套件。一般要经历过两个来回才能完成沟通和协商。

### 应用层协议 ###

TLS/SSL 可以无缝的处理应用层数据。

## 异常处理 ##

### 基于session ID 的会话恢复 ###
### 基于session Ticke ###





