# SSL&TSL #

**核心就是 认证，密钥协商，数据加密**
## HTTPS ## 

> HTTPS 就是身披ssl外壳的HTTP
> HTTP +加密+认证+完整性保护=HTTPS

## 公开密钥加密本质 ##
> 公开密钥加密（Public-key cryptography）。
> 使用一对非对称的密钥
> 比较会使用RSA算法进行加密

## 证明公开密钥正确性的证书  CA##

> 数字证书认证机构颁发的公开密钥证书，来证明公开密钥的正确性。
> 数字证书认证机构颁发的公钥证书，叫做数字证书或直接叫证书。

### 自认证机构颁发的证书称为自签名证书 ###

> 使用openssl 构建一套属于自己的认证机构。，由自认证机构颁发的“无用”
> 证书也被称为自签名证书。

## 数据完整性保护 ##
> 应用层发送数据时会附加一种叫做MAC(Message Authentication Code)的报文摘要。MAC能够查知报文是否遭到篡改。
> mac 就是加了密的hash


## 非对称加密算法主要用途 ##

### 加密 很少用###
> 如果用公钥对数据进行加密，只有用对应的私钥才能解密
> 
> 例如：
> 
> 甲方生成一对密钥并将公钥公开，需要向甲方发送信息的其他角色(乙方)使用该密钥(甲方的公钥)对机密信息进行加密后再发送给甲方；甲方再用自己私钥对加密后的信息进行解密

### 签名 ###

> 甲方可以使用自己的私钥对机密信息进行签名后再发送给乙方；乙方再用甲方的公钥对甲方发送回来的数据进行验签。

### 密码协商 ###


## 建立ssl连接的大体过程 ##
- 1 建立SSL环境。
- 2 socket连接。
- 3 设置证书的等级模式。
- 4 ssl和socket对接。
- 5 发送和接收数据。

**协议主要分为为握手层+加密层**

## 密码套件 ##

- 身份验证算法
- 密码协商算法
- 加密算法或者加密模式
- HMAC算法的加密基元
- PRF算法的加密基元 伪随机

