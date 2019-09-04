# OPENSSL USE #

## 对称加密实践 ##

**对称加密主要使用enc 子命令**

	openssl list -cipher-algorithms 显示系统支持的加密算法

	openssl enc-aes-128-cbc -in e.txt -out m.txt -iv E9EDACA1BD7090C6 -K 89D4B1678D604FAA3DBFFD030A314B29

	openssl enc -ase-128-cbc -in m.txt -d -iv E9EDACA1BD7090C6 -K 89D4B1678D604FAA3DBFFD030A314B29

	openssl enc --help enc 查看帮助

NOTE:aes的填充标准是PKCS#7/5

## MAC(Message Authentication Code) 实践##

**MAC简单说是加密后的hash**
**MAC使用最多是HMAC**
	
	openssl dgst 主要用于数据摘要
	
	1openssl dgst -sha1 file.txt 对file.txt 通过SHA-1 算法计算摘要值。

	openssl sha1 -out digest.txt file.txt

	openssl dgst -sha1 -hmac "mykey" file.txt

## 公开密钥算法（Public Key Cryptography）&&（Asymmetrical Cryptography） ##

使用最广泛的是RSA算法.主要进行密钥协商和签名，很少进行加密。

### RSA加密实践 ###
1.RSA 加密算法的实践 使用genrsa子命令生成密钥对。

	openssl genrsa -out mykey.pem 2048 #生成密钥长度是2048 比特
	openssl genras -des3 -out mykey2.pem 2048 口令结合，需要输入密码

2.从密钥中分离出公钥

	openssl rsa -in mykey.pem -pubout -out mypubkey.pem
	openssl rsa -in mykey2.pem -pubout -out mypubkey2.pem
3.校验密码对文件是否正确
	
	openssl ras -in mykey.pem -check -noout
4.显示公钥信息
	
	openssl rsa -pubin -in mypubkey.pem -text
5.RSA加密

	echo "hello">>plain.txt
	openssl rsautl -encrypt -inkey mykey.pem -in plain.txt -out cipher.txt #使用密钥对加密
	openssl rsautl encrypt -pubin -inkey mypubkey.pem -in plain.txt -out cipher.txt# 使用公钥加密

	openssl rsautl -decrypt -inkey mykey.pem -in cipher.txt #解密
	openssl rsautl -decrypt -inkey mykey.pem -in cipher.txt -oaep #解密，使用OAEP机制

## 密钥协商 ##

### 椭圆曲线密码学（ECC）###

	openssl ecparam -list_curves #查看系统有多少曲线
	openssl ecparam -name secp256k1 -out secp256k1.pem #生成一个参数文件，通过-name 指定命名曲线

	openssl ecparam -in escp256k1.pem -text -param_enc explicit -nout #显示参数文件里的具体参数

#### ECDH 协商密钥####

ECC 和DH算法进行结合。
	demo：

	openssl ecparam -name secp256k1 -out secp256k1.pem #生成参数
	
	#A和B 各自生成一个ECDH 私钥文件
	openssl genpkey -paramfile secp256k1.pem -out akey.pem
	openssl genpkey -paramfile secp256k1.pem -out bkey.pem

	#A 和B 分解出公钥，并把公钥发送给对方

	openssl pkey -in akey.pem -pubout -out akey_pub.pem
	openssl pkey -in bkey.pem -pubout -out bkey_pub.pem

	#A 和B 计算出同样的会话密钥

	openssl pkeyutl -derive -inkey akey.pem -peerkey bkey_pub.pem -out data_a.txt
	openssl pkeyutl -derive -inkey bkey.pem -peerkey bkey_pub.pem -out data_b.txt

## 数字签名 ##
作用：
- 防止篡改
- 防止抵赖
- 防伪造

流程：
- 发送者对消息计算摘要值
- 发送者用私钥对摘要值进行签名得到签名值
- 发送者把原始消息和签名一同发给接受者

### RSA 数字签名 ###
### DSA 数字签名 ###
### ECDSA 数字签名 ###

	openssl ecparam -name secp256kl -genkey -out ecdsa_priv.pem #直接生产私钥

	openssl ec -in ecdsa_priv.pem -text -noout #显示私钥

	openssl ec -in ecdsa_priv.pem -pubout -out ecdsa_pub.pem #生成私钥对应的公钥

	openssl ec -in ecdsa_pub.pem -pubbin -text -noout #显示公钥
	
	echo "hello" >>plain.txt

	openssl dgst -sha256 -sign ecdsa_priv.pem -out signature.txt plain.txt #HASH 算法使用sha256

	openssl dgst -sha256 -verify ecdsa_pub.pem -signature signature.txt plain.txt #签名验证




	



