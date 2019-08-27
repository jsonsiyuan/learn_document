# OPENSSL USE #

## 对称加密实践 ##

**对称加密主要使用enc 子命令**

	openssl list -cipher-algorithms 显示系统支持的加密算法

	openssl enc-aes-128-cbc -in e.txt -out m.txt -iv E9EDACA1BD7090C6 -K 89D4B1678D604FAA3DBFFD030A314B29

	openssl enc -ase-128-cbc -in m.txt -d -iv E9EDACA1BD7090C6 -K 89D4B1678D604FAA3DBFFD030A314B29

	openssl enc --help enc 查看帮助

## MAC(Message Authentication Code) 实践##

**MAC使用最多是HMAC**
	
	openssl dgst 主要用于数据摘要
	
	1openssl dgst -sha1 file.txt 对file.txt 通过SHA-1 算法计算摘要值。

	openssl sha1 -out digest.txt file.txt

	openssl dgst -sha1 -hmac "mykey" file.txt

