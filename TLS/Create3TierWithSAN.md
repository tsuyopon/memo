# 概要
サーバ証明書にSANオプションを追加する方法について
次の２つの流れは理解しておくのが望ましいです。
- Create2TierCA.md
- Create3TierWithOCSP.md

chrome58以降からはCommonNameではなくSAN(subjectAltName)を参照する仕組みになりました。
- https://qiita.com/cnloni/items/a8c9ae834a7d66f60d08
- https://www.cresco.co.jp/blog/entry/2704/

# 詳細
予め秘密鍵とCSR(公開鍵)は作成されていることを前提とします。
```
$ ls
server.csr	server.key
```

設定ファイルは次のような感じで準備します。
ここで着目すべきはusr_certセクションに「subjectAltName=@alt_names」を追加したことと、その指定に合わせて「alt_names」というセクションを追加したことです。
```
$ diff /usr/lib/ssl/openssl.cnf ../conf/openssl-ca1_san.cnf 
42c42
< dir		= ./demoCA		# Where everything is kept
---
> dir		= ../ca1 # Where everything is kept
50c50
< certificate	= $dir/cacert.pem 	# The CA certificate
---
> certificate	= $dir/ca1.crt 	# The CA certificate
55c55
< private_key	= $dir/private/cakey.pem# The private key
---
> private_key	= $dir/ca1.key # The private key
170c170
< basicConstraints=CA:TRUE
---
> basicConstraints=CA:FALSE
176c176
< # nsCertType			= server
---
> nsCertType			= server
202a203
> subjectAltName=@alt_names
234c235
< authorityKeyIdentifier=keyid:always,issuer
---
> #authorityKeyIdentifier=keyid:always,issuer
330c331
< dir		= ./demoCA		# TSA root directory
---
> dir		= ./ca1 # TSA root directory
350a352,359
> 
> [ alt_names ]
> DNS.1 = example1.com
> DNS.2 = example2.com
> DNS.3 = example3.com
> DNS.4 = example4.com
> DNS.5 = example5.com
> DNS.6 = hoge*.com
```

以上を元にして作成するとSAN(Subject Alternative Name)が新規で追加されています。
```
$ openssl ca -policy policy_anything -config ../conf/openssl-ca1_san.cnf -out server.crt  -infiles 

Using configuration from ../conf/openssl-ca1_san.cnf
Enter pass phrase for ../ca1/ca1.key:
Check that the request matches the signature
Signature ok
Certificate Details:
        Serial Number: 3 (0x3)
        Validity
            Not Before: Oct 30 18:08:41 2017 GMT
            Not After : Oct 30 18:08:41 2018 GMT
        Subject:
            countryName               = JP
            stateOrProvinceName       = ThirdProvince
            localityName              = ThirdCity
            organizationName          = ThirdComapany
            organizationalUnitName    = ThirdDept
            commonName                = third.co.jp
        X509v3 extensions:
            X509v3 Basic Constraints: 
                CA:FALSE
            Netscape Cert Type: 
                SSL Server
            Netscape Comment: 
                OpenSSL Generated Certificate
            X509v3 Subject Key Identifier: 
                F9:74:43:32:82:7C:70:59:89:5F:B8:A5:5F:0A:76:AB:40:03:F9:8D
            X509v3 Authority Key Identifier: 
                keyid:69:B4:59:34:35:42:C1:7D:45:9E:4A:B3:F6:9B:4E:AF:60:6F:DB:E9

            X509v3 Subject Alternative Name: 
                DNS:example1.com, DNS:example2.com, DNS:example3.com, DNS:example4.com, DNS:example5.com, DNS:hoge*.com
Certificate is to be certified until Oct 30 18:08:41 2018 GMT (365 days)
Sign the certificate? [y/n]:y


1 out of 1 certificate requests certified, commit? [y/n]y
Write out database with 1 new entries
Data Base Updated
```
