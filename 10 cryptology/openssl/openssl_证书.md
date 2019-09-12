# openssl_证书 #

## PEM ##
privacy enhanced electronic mail

## OPENSSL 相关证书操作 ##

	openssl x509 -in cert.pem -out cert.der -outform DER #PEM转DER

	openssl x509 -in certr.der -inform DER -out cert.prm -outform PEM #DER 转PEM

	openssl ↓09 -text-in cert.pem -noout#查看证书完整信息


	