# coap  libcoap#

## 协议讲解 ##
	http://coap.technology/
	https://tools.ietf.org/html/rfc7252
	http://www.iana.org/assignments/core-parameters/core-parameters.xhtml
## libcoap  web: ##
	https://libcoap.net/
### libcoap 使用参考网站： ###

	https://segmentfault.com/a/1190000002511350
	http://blog.csdn.net/xukai871105/article/details/44980041
	https://datatracker.ietf.org/doc/rfc7252/?include_text=1

## 实践操作 ##

	https://www.cnblogs.com/tifnan2015/p/5363166.html
### 关键协议讲解 ###
#### Message Format ####

	    0                   1                   2                   3
	    0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
	   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
	   |Ver| T |  TKL  |      Code     |          Message ID           |
	   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
	   |   Token (if any, TKL bytes) ...
	   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
	   |   Options (if any) ...
	   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
	   |1 1 1 1 1 1 1 1|    Payload (if any) ...
	   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

                        
##### Option Format 

	     0   1   2   3   4   5   6   7
	   +---------------+---------------+
	   |               |               |
	   |  Option Delta | Option Length |   1 byte
	   |               |               |
	   +---------------+---------------+
	   \                               \
	   /         Option Delta          /   0-2 bytes
	   \          (extended)           \
	   +-------------------------------+
	   \                               \
	   /         Option Length         /   0-2 bytes
	   \          (extended)           \
	   +-------------------------------+
	   \                               \
	   /                               /
	   \                               \
	   /         Option Value          /   0 or more bytes
	   \                               \
	   /                               /
	   \                               \
	   +-------------------------------+	

####  Transmission Parameters ####
                   +-------------------+---------------+
                   | name              | default value |
                   +-------------------+---------------+
                   | ACK_TIMEOUT       | 2 seconds     |
                   | ACK_RANDOM_FACTOR | 1.5           |
                   | MAX_RETRANSMIT    | 4             |
                   | NSTART            | 1             |
                   | DEFAULT_LEISURE   | 5 seconds     |
                   | PROBING_RATE      | 1 byte/second |
                   +-------------------+---------------+

#### Time Values Derived from Transmission Parameters ####
                   +-------------------+---------------+
                   | name              | default value |
                   +-------------------+---------------+
                   | MAX_TRANSMIT_SPAN |          45 s |
                   | MAX_TRANSMIT_WAIT |          93 s |
                   | MAX_LATENCY       |         100 s |
                   | PROCESSING_DELAY  |           2 s |
                   | MAX_RTT           |         202 s |
                   | EXCHANGE_LIFETIME |         247 s |
                   | NON_LIFETIME      |         145 s |
                   +-------------------+---------------+
#### 负载可选内容 ####
	   o  Content-Format
	   o  ETag
	   o  Location-Path
	   o  Location-Query
	   o  Max-Age
	   o  Proxy-Uri
	   o  Proxy-Scheme
	   o  Uri-Host
	   o  Uri-Path
	   o  Uri-Port
	   o  Uri-Query
	   o  Accept
	   o  If-Match
	   o  If-None-Match
	   o  Size1

#### 多播地址注册 ####

> IPv4  - “所有CoAP节点”地址224.0.1.187，来自“IPv4 多播地址空间注册表”。

#### Constrained RESTful Environments (CoRE) Link Format ####

	https://tools.ietf.org/html/rfc6690#section-1

> 众所周知的相对URI  “/ .well-known/ core” 被定义为用于请求关于由服务器托管的资源的链接列表并因此执行CoRE资源发现的默认入口点。

###  CoAP (Constrained Application Protocol) over TCP, TLS, and WebSockets ###

	https://tools.ietf.org/html/rfc8323

** Capabilities and Settings Messages (CSMs)**


-----
### libcoap 安装 ###

- ./autogen.sh
- ./configure
- make
- sudo make install 
- ./coap-server
- ./coap-client -m get -o result.txt coap://localhost



**    安装完成之后，便会新建/usr/local/include/libcoap目录，并把coap.h config.h debug.h pdu.h等头文件复制到该目录中。另外，编译生成的libcoap.a该静态链接库被复制到了/usr/local/lib中。
    同时，在编译完成之后，在example目录中会增加两个重要文件——coap-client和coap-server。**

对于openssl的更新
	https://blog.csdn.net/weixin_42037232/article/details/88838959

### libcoap 使用 ###
	./coap-server
	./coap-client -m get coap://localhost

### libcoap code ###

	https://blog.csdn.net/yangkunhenry/article/details/80181294

