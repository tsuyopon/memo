# 概要
RootCAと中間CA1の２つまでを作成します。

# 詳細
RootCA用ディレクトリを作成します。
```
$ mkdir rootca
$ cd rootca/
```

RootCAの秘密鍵と公開鍵を作成します。
```
$ openssl req -new -keyout rootca.key -out rootca.csr
Generating a 2048 bit RSA private key
...........................................................................................+++
...............................................+++
writing new private key to 'rootca.key'
Enter PEM pass phrase:
Verifying - Enter PEM pass phrase:
-----
You are about to be asked to enter information that will be incorporated
into your certificate request.
What you are about to enter is what is called a Distinguished Name or a DN.
There are quite a few fields but you can leave some blank
For some fields there will be a default value,
If you enter '.', the field will be left blank.
-----
Country Name (2 letter code) [AU]:JP
State or Province Name (full name) [Some-State]:FirstProvince
Locality Name (eg, city) []:FirstCity
Organization Name (eg, company) [Internet Widgits Pty Ltd]:FirstCompany
Organizational Unit Name (eg, section) []:FirstDept
Common Name (e.g. server FQDN or YOUR name) []:first.co.jp
Email Address []:

Please enter the following 'extra' attributes
to be sent with your certificate request
A challenge password []:
An optional company name []:
```

以上によりRootCAの秘密鍵と公開鍵が生成できます。
```
$ ls
rootca.csr  rootca.key
```

続いてRootCAのCRTファイルを生成します。
```
$ openssl x509 -req -signkey rootca.key -in rootca.csr -out rootca.crt
Signature ok
subject=/C=JP/ST=FirstProvince/L=FirstCity/O=FirstCompany/OU=FirstDept/CN=first.co.jp
Getting Private key
Enter pass phrase for rootca.key:
$ ls
rootca.crt  rootca.csr	rootca.key
```

server.crtが持つ制限などを確認してみます。すべてYesなので特権があることがわかります。
```
$  openssl x509 -in server.crt -noout -purpose
Certificate purposes:
SSL client : Yes
SSL client CA : Yes (WARNING code=3)
SSL server : Yes
SSL server CA : Yes (WARNING code=3)
Netscape SSL server : Yes
Netscape SSL server CA : Yes (WARNING code=3)
S/MIME signing : Yes
S/MIME signing CA : Yes (WARNING code=3)
S/MIME encryption : Yes
S/MIME encryption CA : Yes (WARNING code=3)
CRL signing : Yes
CRL signing CA : Yes (WARNING code=3)
Any Purpose : Yes
Any Purpose CA : Yes
OCSP helper : Yes
OCSP helper CA : Yes (WARNING code=3)
Time Stamp signing : No
Time Stamp signing CA : Yes (WARNING code=3)
```

続いて、CAを作成します。
```
$ cd ..
$ mkdir ca1
```

openssl設定ファイルをコピーしておきます。
```
$ mkdir conf
$ cp /etc/ssl/openssl.cnf conf/openssl.cnf
```

openssl.cnfの位置や内容は変わるので、参考までに今回のテストした環境を載せておきます。
```
$ cat /proc/version_signature 
Ubuntu 3.19.0-15.15-generic 3.19.3
$ cat /proc/version
Linux version 3.19.0-15-generic (buildd@komainu) (gcc version 4.9.2 (Ubuntu 4.9.2-10ubuntu13) ) #15-Ubuntu SMP Thu Apr 16 23:32:37 UTC 2015
$ dpkg -l | grep -w openssl
ii  openssl                                              1.0.1f-1ubuntu11                           amd64        Secure Sockets Layer toolkit - cryptographic utility
```

openssl.cnfファイルを今回の環境に合わせて修正します。
```
$ vim conf/openssl.cnf 
$ diff /etc/ssl/openssl.cnf conf/openssl.cnf 
42c42
< dir		= ./demoCA		# Where everything is kept
---
> dir		= ../rootca # Where everything is kept
50c50
< certificate	= $dir/cacert.pem 	# The CA certificate
---
> certificate	= $dir/rootca.crt # The CA certificate
55c55
< private_key	= $dir/private/cakey.pem# The private key
---
> private_key	= $dir/rootca.key # The private key
234c234
< authorityKeyIdentifier=keyid:always,issuer
---
> #authorityKeyIdentifier=keyid:always,issuer
330c330
< dir		= ./demoCA		# TSA root directory
---
> dir		= ./rootca # TSA root directory
```

CA用のCSRファイルを生成する。
```
$ cd ca1
$ openssl req -new -keyout ca.key -out ca.csr
Generating a 2048 bit RSA private key
.................+++
...............................................................................................+++
writing new private key to 'ca.key'
Enter PEM pass phrase:
Verifying - Enter PEM pass phrase:
-----
You are about to be asked to enter information that will be incorporated
into your certificate request.
What you are about to enter is what is called a Distinguished Name or a DN.
There are quite a few fields but you can leave some blank
For some fields there will be a default value,
If you enter '.', the field will be left blank.
-----
Country Name (2 letter code) [AU]:JP
State or Province Name (full name) [Some-State]:SecondProvince
Locality Name (eg, city) []:SecondCity
Organization Name (eg, company) [Internet Widgits Pty Ltd]:SecondCompany
Organizational Unit Name (eg, section) []:SecondDept
Common Name (e.g. server FQDN or YOUR name) []:second.co.jp
Email Address []:

Please enter the following 'extra' attributes
to be sent with your certificate request
A challenge password []:
An optional company name []:
```

以上により作成されるファイル全体として次のようなディレクトリ構成となります。
```
$ tree .
.
├── ca1
│   ├── ca.csr
│   └── ca.key
├── conf
│   └── openssl.cnf
└── rootca
    ├── rootca.crt
    ├── rootca.csr
    └── rootca.key

3 directories, 5 files
```

予め必要なディレクトリ、ファイルを作ります。index.txtとserialファイルはこの後の操作で上書きされます。
シリアル番号は最初は01などとしておくと良いでしょう。
```
$ mkdir -p rootca/newcerts
$ touch rootca/index.txt
$ echo 01 > rootca/serial
```

ではca.crtファイルを生成します。
```
$ cd ca1/
$ openssl ca -policy policy_anything -config ../conf/openssl.cnf -out ca.crt -infiles ca.csr
Using configuration from ../conf/openssl.cnf
Enter pass phrase for ../rootca/rootca.key:
Check that the request matches the signature
Signature ok
Certificate Details:
        Serial Number: 1 (0x1)
        Validity
            Not Before: Oct 29 00:29:36 2017 GMT
            Not After : Oct 29 00:29:36 2018 GMT
        Subject:
            countryName               = JP
            stateOrProvinceName       = SecondProvince
            localityName              = SecondCity
            organizationName          = SecondCompany
            organizationalUnitName    = SecondDept
            commonName                = second.co.jp
        X509v3 extensions:
            X509v3 Basic Constraints: 
                CA:TRUE
            Netscape Comment: 
                OpenSSL Generated Certificate
            X509v3 Subject Key Identifier: 
                C2:C6:5B:90:BE:19:4D:E2:3C:97:70:81:82:FA:4B:DE:B5:E8:03:A7
            X509v3 Authority Key Identifier: 
                DirName:/C=JP/ST=FirstProvince/L=FirstCity/O=FirstCompany/OU=FirstDept/CN=first.co.jp
                serial:8E:11:96:E3:FA:9B:8E:C6

Certificate is to be certified until Oct 29 00:29:36 2018 GMT (365 days)
Sign the certificate? [y/n]:y


1 out of 1 certificate requests certified, commit? [y/n]y
Write out database with 1 new entries
Data Base Updated
```

以上により次のディレクトリ構成になっています。
```
$ tree ..
..
├── ca1
│   ├── ca.crt
│   ├── ca.csr
│   └── ca.key
├── conf
│   └── openssl.cnf
└── rootca
    ├── index.txt
    ├── index.txt.attr
    ├── index.txt.old
    ├── newcerts
    │   └── 01.pem
    ├── rootca.crt
    ├── rootca.csr
    ├── rootca.key
    ├── serial
    └── serial.old

4 directories, 13 files
```

2つoldというファイルが作成されています。せっかくなのでこれを覗いてみるserialは1インクリメントされ、index.txtはRootCAに追加したCA1が含まれていることが確認できる。
```
$ ls ../rootca/*.old
../rootca/index.txt.old  ../rootca/serial.old
$ cat ../rootca/serial
02
$ cat ../rootca/index.txt
V	181029002936Z		01	unknown	/C=JP/ST=SecondProvince/L=SecondCity/O=SecondCompany/OU=SecondDept/CN=second.co.jp
```

Issuerが作成したRootCAで、Subjectが今回作成した中間CAのものであることを確認する。
```
$ openssl x509 -in ca.crt -text | grep -e Issuer: -e Subject: 
        Issuer: C=JP, ST=FirstProvince, L=FirstCity, O=FirstCompany, OU=FirstDept, CN=first.co.jp
        Subject: C=JP, ST=SecondProvince, L=SecondCity, O=SecondCompany, OU=SecondDept, CN=second.co.jp
```

今回作成したca.crtの情報からCAが中間CAとして署名できることを確認する。
```
$ openssl x509 -in ca.crt -text | grep -i "X509v3 Basic Constraints" -A 1
            X509v3 Basic Constraints: 
                CA:TRUE
```

ca.crtが持つ権限を確認しておきます。「Time Stamp signing」という項目以外はすべてYesであることがわかります。
```
$ openssl x509 -in ca.crt -noout -purpose
Certificate purposes:
SSL client : Yes
SSL client CA : Yes
SSL server : Yes
SSL server CA : Yes
Netscape SSL server : Yes
Netscape SSL server CA : Yes
S/MIME signing : Yes
S/MIME signing CA : Yes
S/MIME encryption : Yes
S/MIME encryption CA : Yes
CRL signing : Yes
CRL signing CA : Yes
Any Purpose : Yes
Any Purpose CA : Yes
OCSP helper : Yes
OCSP helper CA : Yes
Time Stamp signing : No
Time Stamp signing CA : Yes
```

念のためにca.key, ca.crtが秘密鍵、公開鍵ペアであることを確認する。
```
$ openssl rsa -in ca.key -modulus -noout | openssl md5
Enter pass phrase for ca.key:
(stdin)= 0e57232d865a0413d0f15beb2c9c1fcb
$ openssl x509 -in ca.crt -modulus -noout | openssl md5
(stdin)= 0e57232d865a0413d0f15beb2c9c1fcb
```

最後に作成したものがサーバとして起動できるかどうかを確認しておきます。
```
$ openssl s_server -cert ca.crt -key ca.key -CAfile ../rootca/rootca.crt -www 
Enter pass phrase for ca.key:
Using default temp DH parameters
Using default temp ECDH parameters
ACCEPT
(snip)
```

接続すると次のようになります。
```
$ openssl s_client -connect localhost:4433 
CONNECTED(00000003)
depth=1 C = JP, ST = FirstProvince, L = FirstCity, O = FirstCompany, OU = FirstDept, CN = first.co.jp
verify error:num=19:self signed certificate in certificate chain
verify return:0
---
Certificate chain
 0 s:/C=JP/ST=SecondProvince/L=SecondCity/O=SecondCompany/OU=SecondDept/CN=second.co.jp
   i:/C=JP/ST=FirstProvince/L=FirstCity/O=FirstCompany/OU=FirstDept/CN=first.co.jp
 1 s:/C=JP/ST=FirstProvince/L=FirstCity/O=FirstCompany/OU=FirstDept/CN=first.co.jp
   i:/C=JP/ST=FirstProvince/L=FirstCity/O=FirstCompany/OU=FirstDept/CN=first.co.jp
---
Server certificate
(snip)
    Start Time: 1509261939
    Timeout   : 300 (sec)
    Verify return code: 19 (self signed certificate in certificate chain)
---
```

なぜか「Verify return code: 19 (self signed certificate in certificate chain)」といったエラーが出てくる。
cafileなどをs_client時に指定してもうまくいかずで、さらなる調査が必要


TODO: 上記を解消しておくこと
MEMO: CA証明書の追加方法を次の手順で試してみるといいかも。/usr/lib/ssl/certsなど
- http://dsas.blog.klab.org/archives/50484787.html

# 参考URL
- 多段の中間CA証明書作成 -証明書作成編-
  - http://lab.hde.co.jp/2008/09/ca.html
