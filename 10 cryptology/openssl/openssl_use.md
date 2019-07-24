# openssl 使用 #


## Key and Certificate Management ##

1. generate a strong private key
2. create a Certificate Signing Request (CSR) and send it to a CA, and
3. install the CA-provided certificate in your web server

### Key Generation ###

**RSA**
To generate an RSA key, use the genrsa command:

		openssl genrsa -aes128 -out fd.key 2048

You can see a key’s structure using the following rsa command:

	openssl rsa -text -in fd.key

you need to have just the public part of a key separately

	openssl rsa -in fd.key -pubout -out fd-public.key

**DSA**
DSA key generation

	openssl dsaparam -genkey 2048 | openssl dsa -out dsa.key -aes128


**椭圆积分曲线**

	openssl ecparam -genkey -name secp256r1 | openssl ec -out ec.key -aes128


### Creating Certificate Signing Requests ###


- Creating Certificate Signing Requests 

	openssl req -new -key fd.key -out fd.csr

- double-check that the CSR is correct
	
	openssl req -text -in fd.csr -noout

- Creating CSRs from Existing Certificates
	
	openssl x509 -x509toreq -in fd.crt -out fd.csr -signkey fd.key

- Unattended CSR Generation

**We would start by creating a file fd.cnf**

	openssl req -new -config fd.cnf -key fd.key -out fd.csr

- Signing Your Own Certificates

**If you’re installing a TLS server for your own use, you probably don’t want to go to a CA for
a publicly trusted certificate**
**If you already have a CSR, create a certificate using the following command**

	openssl x509 -req -days 365 -in fd.csr -signkey fd.key -out fd.crt

**You don’t actually have to create a CSR in a separate step. The following command creates a
self-signed certificate starting with a key alone**

	openssl req -new -x509 -days 365 -key fd.key -out fd.crt

- Examining Certificates

	openssl x509 -text -in fd.crt -noout

### Key and Certificate Conversion ###

- PEM and DER Conversion

**To convert a certificate from PEM to DER format**

	openssl x509 -inform PEM -in fd.pem -outform DER -out fd.der

**To convert a certificate from DER to PEM format**

	openssl x509 -inform DER -in fd.der -outform PEM -out fd.pem

**PKCS#12 (PFX) Conversion**

	openssl pkcs12 -export -name "My Certificate" -out fd.p12 -inkey fd.key \
	-in fd.crt \
	-certfile fd-chain.crt

	openssl pkcs12 -in fd.p12 -out fd.pem -nodes
	
**PKCS#7 Conversion**

	openssl crl2pkcs7 -nocrl -out fd.p7b -certfile fd.crt -certfile fd-chain.crt

	openssl pkcs7 -in fd.p7b -print_certs -out fd.pem

### Cipher Suite Selection ###

	openssl ciphers -v 'ALL:COMPLEMENTOFALL'

**For example, you can ask it to list only
cipher suites that are based on RC4, as follows**

	openssl ciphers -v 'RC4'


	