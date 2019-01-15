# 概要
3階層目としてサーバ証明書をOCSP付きで設定します。  
この資料では、1階層目のRootCAと2階層目の中間CAとしては[Create2TierCA.md]として予め構築されていることが前提です。

# 詳細

[Create2TierCA.md]で作成したca, conf, rootcaが存在するディレクトリと同じ階層にserverというサーバ証明書用のディレクトリを作ることにします。
```
$ ls 
ca/  conf/  rootca/
$ mkdir server/
$ cd server/
```

サーバ証明書生成のためのopenssl-ca.confを修正します。
```
$ vim ../conf/openssl-ca.conf
$ diff /usr/lib/ssl/openssl.cnf ../conf/openssl-ca.cnf  
42c42
< dir		= ./demoCA		# Where everything is kept  
---
> dir		= ../ca # Where everything is kept  [CA_default]
50c50
< certificate	= $dir/cacert.pem 	# The CA certificate
---
> certificate	= $dir/ca.crt 	# The CA certificate [CA_default]
55c55
< private_key	= $dir/private/cakey.pem# The private key
---
> private_key	= $dir/ca.key # The private key [CA_default]
164a165,166
> authorityInfoAccess = OCSP;URI:http://ocsptest.co.jp/  # [usr_cert]
> 
170c172
< basicConstraints=CA:TRUE
---
> basicConstraints=CA:FALSE  # [usr_cert]
176c178
< # nsCertType			= server
---
> nsCertType			= server #[usr_cert]
234c236
< authorityKeyIdentifier=keyid:always,issuer
---
> #authorityKeyIdentifier=keyid:always,issuer  #[usr_cert]
330c332
< dir		= ./demoCA		# TSA root directory
---
> dir		= ./ca # TSA root directory   #[tsa_config1] この修正だけ必要かわからない...
```

サーバ証明書のための公開鍵とCSR(公開鍵含む)を作成します。
```
$ openssl req -new -keyout server.key -out server.csr
Generating a 2048 bit RSA private key
.........+++
....+++
writing new private key to 'server.key'
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
State or Province Name (full name) [Some-State]:ThirdProvince
Locality Name (eg, city) []:ThirdCity
Organization Name (eg, company) [Internet Widgits Pty Ltd]:ThirdComapany
Organizational Unit Name (eg, section) []:ThirdDept
Common Name (e.g. server FQDN or YOUR name) []:third.co.jp
Email Address []:

Please enter the following 'extra' attributes
to be sent with your certificate request
A challenge password []:
An optional company name []:
$ ls
server.csr  server.key
```

続いて、次のコマンドで先程作成したopenssl-ca.cnfを指定してサーバ証明書(server.crt)を作成します。
```
$ openssl ca -policy policy_anything -config ../conf/openssl-ca.cnf -out server.crt -infiles server.csr
Using configuration from ../conf/openssl-ca.cnf
Enter pass phrase for ../ca/ca.key:
Check that the request matches the signature
Signature ok
Certificate Details:
        Serial Number: 1 (0x1)
        Validity
            Not Before: Oct 30 12:44:13 2017 GMT
            Not After : Oct 30 12:44:13 2018 GMT
        Subject:
            countryName               = JP
            stateOrProvinceName       = ThirdProvince
            localityName              = ThirdCity
            organizationName          = ThirdComapany
            organizationalUnitName    = ThirdDept
            commonName                = third.co.jp
        X509v3 extensions:
            Authority Information Access: 
                OCSP - URI:http://ocsptest.co.jp/

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

Certificate is to be certified until Oct 30 12:44:13 2018 GMT (365 days)
Sign the certificate? [y/n]:y


1 out of 1 certificate requests certified, commit? [y/n]y
Write out database with 1 new entries
Data Base Updated
$ ls
server.crt  server.csr	server.key
```

作成されたサーバ証明書を確認します。
注目すべきは「Issuer」には中間CA、「Subject」には今回登録された情報、及びX509v3拡張として「Authority Information Access」にOCSPのURLが設定され、「X509v3 Basic Constraints:」がCAとしての能力が無い(FALSE)となっていることです。
```
$ openssl x509 -in server.crt -noout -text
Certificate:
    Data:
        Version: 3 (0x2)
        Serial Number: 1 (0x1)
    Signature Algorithm: sha256WithRSAEncryption
        Issuer: C=JP, ST=SecondProvince, L=SecondCity, O=SecondCompany, OU=SecondDept, CN=second.co.jp
        Validity
            Not Before: Oct 30 12:44:13 2017 GMT
            Not After : Oct 30 12:44:13 2018 GMT
        Subject: C=JP, ST=ThirdProvince, L=ThirdCity, O=ThirdComapany, OU=ThirdDept, CN=third.co.jp
        Subject Public Key Info:
            Public Key Algorithm: rsaEncryption
                Public-Key: (2048 bit)
                Modulus:
                    00:da:7c:93:b3:84:a8:7e:df:ee:e0:d3:93:70:91:
                    (snip)
                Exponent: 65537 (0x10001)
        X509v3 extensions:
            Authority Information Access: 
                OCSP - URI:http://ocsptest.co.jp/

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

    Signature Algorithm: sha256WithRSAEncryption
         c0:dc:21:a6:56:b0:74:7e:4e:1c:91:41:c0:d0:50:d5:41:1e:
         (snip)
```

作成されたサーバ証明書のpurposeも確認しておきます。
```
$ openssl x509 -in server.crt -noout -purpose
Certificate purposes:
SSL client : No
SSL client CA : No
SSL server : Yes
SSL server CA : No
Netscape SSL server : Yes
Netscape SSL server CA : No
S/MIME signing : No
S/MIME signing CA : No
S/MIME encryption : No
S/MIME encryption CA : No
CRL signing : Yes
CRL signing CA : No
Any Purpose : Yes
Any Purpose CA : Yes
OCSP helper : Yes
OCSP helper CA : No
Time Stamp signing : No
Time Stamp signing CA : No
```

以上によりサーバ証明書にOCSP情報が付加されたことや、この証明書がCA能力を持っていないことを確認することができました。
一応、前回と同様にHTTPSサーバとして起動できることを確認しておきましょう。
```
$ openssl s_server -cert server.crt -key server.key -CAfile ../ca/ca.crt -www
Enter pass phrase for server.key:
Using default temp DH parameters
Using default temp ECDH parameters
ACCEPT
```

続いて、OCSPへ発行するリクエスト内容を作成してみます。リクエストはreq.derに含まれています。
```
$ sudo openssl ocsp -issuer ../ca/ca.crt -cert ./server.crt -reqout req.der
```

作成したreq.derの中身を見てみます。Serial Numberには01を入れていたのでちゃんとしたものであることが確認できます。
```
$ openssl ocsp -reqin req.der -text
OCSP Request Data:
    Version: 1 (0x0)
    Requestor List:
        Certificate ID:
          Hash Algorithm: sha1
          Issuer Name Hash: 900F39DA84A7D73294F8BD08896A41C3DF3E2D80
          Issuer Key Hash: 69B459343542C17D459E4AB3F69B4EAF606FDBE9
          Serial Number: 01
    Request Extensions:
        OCSP Nonce: 
            04101987EA5DB36F0A7EDC62C0DA0CE8D091
```

サーバ証明書の中のシリアル番号も確認しておきましょう。
```
$ openssl x509 -in server.crt -noout -serial
serial=01
```

あとは、OCSPレスポンダの確認をしておく必要がありますが、この前にOCSPレスポンダとしてサーバを起動しておく必要があります。
これには簡易コマンドがあります。

caディレクトリの中にindex.txtが含まれています。
```
$ cd ../ca
$ cat index.txt
V	181030124413Z		01	unknown	/C=JP/ST=ThirdProvince/L=ThirdCity/O=ThirdComapany/OU=ThirdDept/CN=third.co.jp
```

80番ポートが起動していないことを確認してから、次のOCSPレスポンダを起動することができます。
```
$ sudo openssl ocsp -index index.txt -CA ca.crt -rsigner ca.crt -rkey ca.key -port 80
Enter pass phrase for ca.key:
Waiting for OCSP client connections...
```

確認に必要なOCSPレスポンダのドメインを/etc/hostsに入れておきます。
```
$ cat /etc/hosts
127.0.0.1  ocsptest.co.jp
```

サーバ証明書やCA証明書を指定して以下のコマンドでOCSPクライアントとしてOCSPレスポンダにHTTPリクエストを投げることができます。
サーバ証明書からOCSP先を抽出して、リクエストを生成して、その後OCSPレスポンスに付与された署名を中間CA証明書(ca.crt)で照合していると考えられます。
```
$ sudo openssl ocsp -issuer ../ca/ca.crt -cert server.crt -url http://ocsptest.co.jp/ -resp_text -respout resp.der -CAfile ../ca/ca.crt -header 'host' 'ocsptest.co.jp'
OCSP Response Data:
    OCSP Response Status: successful (0x0)
    Response Type: Basic OCSP Response
    Version: 1 (0x0)
    Responder Id: C = JP, ST = SecondProvince, L = SecondCity, O = SecondCompany, OU = SecondDept, CN = second.co.jp
    Produced At: Oct 30 13:22:41 2017 GMT
    Responses:
    Certificate ID:
      Hash Algorithm: sha1
      Issuer Name Hash: 900F39DA84A7D73294F8BD08896A41C3DF3E2D80
      Issuer Key Hash: 69B459343542C17D459E4AB3F69B4EAF606FDBE9
      Serial Number: 01
    Cert Status: good
    This Update: Oct 30 13:22:41 2017 GMT

    Response Extensions:
        OCSP Nonce: 
            041052506DD85D8CE181AA15FD1675A4EC4D
    Signature Algorithm: sha256WithRSAEncryption
(snip)
Response verify OK
server.crt: good
	This Update: Oct 30 13:22:41 2017 GMT
```

MEMO: 上記で"Next Update"が出てこないのはなぜ?

# まとめ
CAからサーバ証明書を生成して、そのサーバ証明書はCAとしての能力がないこと、OCSPレスポンダの情報が入っていることを確認しました。
また、ocspサブオプションを利用してOCSPレスポンダの起動及びOCSPクライアントとしての接続確認をおこないました。

