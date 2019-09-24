# openssl_证书 #
X.509 的格式一般是BER(Basic Encoding Rules).

## PEM ##

privacy enhanced electronic mail

## OPENSSL 证书格式转换的操作 ##

	openssl x509 -in cert.pem -out cert.der -outform DER #PEM转DER

	openssl x509 -in certr.der -inform DER -out cert.prm -outform PEM #DER 转PEM

	-outform 表示输出文件编码方式


## OPENSSL 管理 CSR ##


	openssl req -new -sha256 -newkey rsa:2048 -nodes -subj '/cn=www.example.com,www.example2.com/O=Test,Inc./C=CN/ST=Beijing/L=Haidian' -keyout example_key.pem -out example_csr.pem  ### 生成CSR

	openssl req -in example_csr.pem -noout -text ### 查看CRS文件

	openssl req -in myreq.pem -noout -verify -key example_csr.pem  ### 验证CSR签名

## OPENSSL 生成证书 ##

	openssl x509 -req -days 365 -in example_csr.pem -signkey example_key.pem -out example_cert.pem -extfile certext.ext #-signkey 表示密码对的公钥 。生成自签的证书。

	openssl x509 -text -in cert.pem -noout #查看证书完整信息
	openssl x509 -in cert.pem -pubkey #查看证书包含的公钥
	openssl x509 -in cert.pem -issuer #查看CA机构
	openssl x509 -in cert.pem -enddate #查看证书的有效期
	openssl x509 -in cert.pem -text -noout #查看服务器实体证书

## 校验CRL ##
