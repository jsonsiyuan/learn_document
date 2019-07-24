# mqtt关键内容 #

## 控制报文格式 ##
### MQTT控制报文的结构 ###
| :---: |
|固定报文Fixed header|
|可变报文 Variable header|
|有效负载 Payload|
### 固定报文 ###
| :---: |:---:| :---:|
|Bit|7-4 |3-0|
| byte1 | 控制报文类型 |对应标志位|
| byte2 |剩余长度  |
####  MQTT控制报文的类型  ####

| 名字 |值|报文流动方向|描述|
| :---: |:---:| :---:| :---:|
| Reserved |0|禁止|保留 |
| CONNECT |1|客服端到服务器|客户端请求连接服务器|
| CONNACK|2|服务器到客户端|连接报文确认|
| PUBLISH|3|双向|发布消息|
| PUBACK|4|双向|Qos 1 消息发布收到确认|
| PUBREC|5|双向|发布收到|
| PUBREL|6|双向|发布释放|
| PUBCOMP|7|双向|Qos 2消息发布完成|
| SUBSCRIBE|8|客户端到服务器|客户端订阅请求|
| SUBACK|9|服务器到客户端|订阅请求报文确认|
| UNSUBSCRIBE|10|客户端到服务器|客户端取消订阅请求|
| UNSUBACK|11|服务器到客户端|取消订阅请求确认|
| PINGREQ|12|客户端到服务器|心跳请求|
| PINGRESP|13|服务器到客户端|心跳相应|
| DISCONNECT|14|客户端到服务端|客户端断开连接|
| RESERVED|15|禁止|保留|

#### 剩余长度 #### 
每个字节的低7位用于编码，最高位是标志位
最大是4字节

## 可变包头 ##

| 名字 |可变报头|
| :---: |:---:|
| CONNECT |N|
| CONNACK|N|
| PUBLISH|Y(Qos>0)|
| PUBACK|Y|
| PUBREC|Y|
| PUBREL|Y|
| PUBCOMP|Y|
| SUBSCRIBE|Y|
| SUBACK|Y|
| UNSUBSCRIBE|Y|
| UNSUBACK|Y|
| PINGREQ|N|
| PINGRESP|N|
| DISCONNECT|N|

## 负载 ##
| 名字 |有效负载|
| :---: |:---:|
| CONNECT |Y|
| CONNACK|N|
| PUBLISH|可选|
| PUBACK|N|
| PUBREC|N|
| PUBREL|N|
| PUBCOMP|N|
| SUBSCRIBE|Y|
| SUBACK|Y|
| UNSUBSCRIBE|N|
| UNSUBACK|N|
| PINGREQ|N|
| PINGRESP|N|
| DISCONNECT|N|



