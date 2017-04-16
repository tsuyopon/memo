# 概要
Javaでのサーバ間SSLを行う場合の手順について整理

# 用語
- keystore
  - サーバーに送信するクライアントの証明書を格納するファイル
- truststore
  - クライアント側が認証するサーバー側の証明書を格納するファイル


# サーバ間SSLのイメージ
全体像はこのあたりの画像が非常に参考になる。
- https://codezine.jp/article/detail/105

SSLクライアントに配置されるもの
- トラストストア
  - その会社のルート証明書
- キーストア
  - ベリサインルート証明書
  - ベリサインサーバ証明書
- SSLサーバに含まれるもの
  - トラストストア
    - ベリサインルート証明書
  - キーストア
    - その会社のルート証明書
    - その会社の中間証明書
    - その会社のサーバ証明書

認証シーケンスは次の通りとなる。
- 1. SSL接続を開始する
- 2. サーバ側がクライアント側にキーストア情報を送る。クライアントが受け取ると、クライアント側のトラストストアで認証する。
- 3. クライアント側がキーストア情報を送る。サーバが受け取ると、サーバ側のトラストストアで認証する。

### keystore発行手順(概要)
以下のドキュメントを参考にして
- http://qiita.com/rsooo/items/9119456285db1fe14b6d

- (1). キーストアの作成(申請者作業)
```
$ sudo keytool -genkey -keystore serverkeystore.jks -alias server
有効期限を設定する場合の例
	$ sudo keytool -genkey -keystore serverKeystore.jks -alias server -validity 3650       // 10年

その他にも色々指定する場合
	$ sudo keytool -genkeypair -alias testkeystore -keysize 2048 -keyalg RSA -sigalg SHA256withRSA -keystore serverkeystore.jks -storetype JKS -validity 3650 -keypass hogekey -storepass hogestore

NOTE: 最新版はgenkeyではなくgenkeypairらしい
      aliasというのは、証明書・鍵をKeyStore内で識別する名前
```
- (2). CAの作成(CA作業)
```
DebianやUbuntuの場合(/usr/local/ssl/bin/CA.plの場合もあるらしい)
	$ sudo /usr/local/ssl/bin/CA.sh -newca
RedHat, CentOSの場合
	$ sudo /etc/pki/tls/misc/CA -newca

NOTE: 実はCAはスクリプトでopensslを叩いているだけなので中を見てみると良い。
```
- (3). CSR(証明書要求)の作成(申請者作業)
  - CAにCRTファイルを生成してもらう必要があるのですが、これを生成するときにはCSRファイルと言うものが必要になります。
```
$ sudo keytool -certreq -alias testkeystore -sigalg SHA256withRSA -file test.csr -keypass hogekey -keystore serverkeystore.jks -storepass hogestore -storetype JKS
```
- (4). CAでの署名(CA作業)
```
DebianやUbuntuの場合
	$ sudo openssl ca -md sha256 -keyfile /usr/local/ssl/CA/private/cakey.pem -cert /usr/local/ssl/CA/cacert.pem -in test.csr -out testservercert.crt -days 1460 -policy policy_anything

RedHatやCentの場合
	$ sudo openssl ca -md sha256 -keyfile /etc/pki/CA/private/cakey.pem -cert /etc/pki/CA/cacert.pem -in test.csr -out testservercert.crt -days 1460 -policy policy_anything

上記で作成したtestservercert.crtを、-----BEGIN CERTIFICATE-----と-----END CERTIFICATE-----とその中身だけになるように、ほかを削除しておく。
```
- (5). jksに証明書をインポートする。つまりjksへの登録作業(申請者作業)
  - 次のコマンドでjksにcrtやcerなどの証明書ファイルをインポートする事ができます。(仕様上はRoot証明書cacert.pemは登録不要ですが、必要あれば以下と同じ手順で登録が必要です。順番はルート証明書->中間証明書->証明書となります。)
```
DebianやUbuntuの場合
	$ sudo keytool -importcert -alias testkeystore -file testservercert.crt -keystore serverkeystore.jks -trustcacerts -storepass hogestore

RedHatやCentの場合
	$ sudo keytool -importcert -alias testkeystore -file testservercert.crt -keystore serverkeystore.jks -trustcacerts -storepass hogestore

NOTE:
	※ 昔はimportcertではなくimportと言ったコマンドだったようです。
	この作業はルート証明書、中間証明書などもimportできるようです。
		https://codezine.jp/article/detail/105
	証明書をインポートする際に、-trustcacerts オプションを使用して証明書連鎖を構築することと、秘密鍵を生成した際のalias名と同一の名前を指定するのがポイントです。
	証明書連鎖を構築すると、証明書をクライアントに送信する際に連鎖している証明書も送信されます
```
- (6). 証明書の確認(申請者作業)
```
$ sudo keytool -list -v -keystore serverkeystore.jks -storepass hogestore
```

### truststore発行手順(概要)
たった1工程のみ
- (1) 先程の(4)で作成したcrtをserverTruststore.jksにインポートして作成する。
```
$ keytool -import -keystore serverTruststore.jks -alias serverTruststore -file testservercert.crt 
```

### client側のkeystoreとtruststore作成手順について
基本的にはserver側と同じことを実施するだけ。

### keystore発行手順(詳細)
- (1)
  - serverkeystore.jksが生成される。
```
$ keytool -genkeypair -alias testkeystore -keysize 2048 -keyalg RSA -sigalg SHA256withRSA -keystore serverkeystore.jks -storetype JKS -validity 3650 -keypass hogekey -storepass hogestore
What is your first and last name?
  [Unknown]:  www.example.com
What is the name of your organizational unit?
  [Unknown]:  BaseTechnology
What is the name of your organization?
  [Unknown]:  Core
What is the name of your City or Locality?
  [Unknown]:  Saitama
What is the name of your State or Province?
  [Unknown]:  Kawaguchi
What is the two-letter country code for this unit?
  [Unknown]:  JP
Is CN=www.example.com, OU=BaseTechnology, O=Core, L=Saitama, ST=Kawaguchi, C=JP correct?
  [no]:  yes
```
- (2) 
```
$ sudo /etc/pki/tls/misc/CA -newca
CA certificate filename (or enter to create)
                                                   ###### デフォルトでいいのでここでEnterを押下 #####
Making CA certificate ...
Generating a 2048 bit RSA private key
......................................+++
..+++
writing new private key to '/etc/pki/CA/private/./cakey.pem'
Enter PEM pass phrase:                             ###### 適当にここではhogepemとした #####
Verifying - Enter PEM pass phrase:
-----
You are about to be asked to enter information that will be incorporated
into your certificate request.
What you are about to enter is what is called a Distinguished Name or a DN.
There are quite a few fields but you can leave some blank
For some fields there will be a default value,
If you enter '.', the field will be left blank.
-----
Country Name (2 letter code) [XX]:JP
State or Province Name (full name) []:Tokyo
Locality Name (eg, city) [Default City]:Minatoku
Organization Name (eg, company) [Default Company Ltd]:TestCA
Organizational Unit Name (eg, section) []:Sign
Common Name (eg, your name or your server's hostname) []:www.testca.com
Email Address []:testca@example.com

Please enter the following 'extra' attributes
to be sent with your certificate request
A challenge password []:testchallenge　　　　　　　　　　　　###### 適当にここではtestchallengeとした #####
An optional company name []:
Using configuration from /etc/pki/tls/openssl.cnf
Enter pass phrase for /etc/pki/CA/private/./cakey.pem:　　###### 最初に聞かれたhogepemを入力した #####
Check that the request matches the signature
Signature ok
Certificate Details:
        Serial Number:
            80:74:6b:6d:b8:8c:75:af
        Validity
            Not Before: Apr 16 10:09:36 2017 GMT
            Not After : Apr 15 10:09:36 2020 GMT
        Subject:
            countryName               = JP
            stateOrProvinceName       = Tokyo
            organizationName          = TestCA
            organizationalUnitName    = Sign
            commonName                = www.testca.com
            emailAddress              = testca@example.com
        X509v3 extensions:
            X509v3 Subject Key Identifier: 
                B7:4C:C0:57:1C:1C:18:A9:01:53:6C:02:4D:E9:A6:EE:57:A3:BF:74
            X509v3 Authority Key Identifier: 
                keyid:B7:4C:C0:57:1C:1C:18:A9:01:53:6C:02:4D:E9:A6:EE:57:A3:BF:74

            X509v3 Basic Constraints: 
                CA:TRUE
Certificate is to be certified until Apr 15 10:09:36 2020 GMT (1095 days)

Write out database with 1 new entries
Data Base Updated
```
  - これでCA側が持つCA秘密鍵、CA証明書が発行される。この２ファイルは(4)のCA署名作業として必要となる。
```
	CA秘密鍵
		/etc/pki/CA/private/cakey.pem
	CA証明書
		/etc/pki/CA/cacert.pem 
			次のコマンドで確認できる。
				$ openssl x509 -in /etc/pki/CA/cacert.pem -text
```
- (3)
  - 以下のコマンドでtest.csrを生成する
```
$ sudo keytool -certreq -alias testkeystore -sigalg SHA256withRSA -file test.csr -keypass hogekey -keystore serverkeystore.jks -storepass hogestore -storetype JKS
```
- (4)
  - 以下のコマンドで入力としてcakey.pem, cacert.pem, test.csrを与えることにより、testservercert.crtを生成する
```
$ sudo openssl ca -md sha256 -keyfile /etc/pki/CA/private/cakey.pem -cert /etc/pki/CA/cacert.pem -in test.csr -out testservercert.crt -days 1460 -policy policy_anything
Using configuration from /etc/pki/tls/openssl.cnf
Enter pass phrase for /etc/pki/CA/private/cakey.pem:
Check that the request matches the signature
Signature ok
Certificate Details:
        Serial Number:
            80:74:6b:6d:b8:8c:75:b0
        Validity
            Not Before: Apr 16 10:20:56 2017 GMT
            Not After : Apr 15 10:20:56 2021 GMT
        Subject:
            countryName               = JP
            stateOrProvinceName       = Kawaguchi
            localityName              = Saitama
            organizationName          = Core
            organizationalUnitName    = BaseTechnology
            commonName                = www.example.com
        X509v3 extensions:
            X509v3 Basic Constraints: 
                CA:FALSE
            Netscape Comment: 
                OpenSSL Generated Certificate
            X509v3 Subject Key Identifier: 
                A5:AC:A3:4B:B1:85:70:5E:B2:51:05:F2:78:D0:31:86:B7:1F:E3:7A
            X509v3 Authority Key Identifier: 
                keyid:B7:4C:C0:57:1C:1C:18:A9:01:53:6C:02:4D:E9:A6:EE:57:A3:BF:74

Certificate is to be certified until Apr 15 10:20:56 2021 GMT (1460 days)
Sign the certificate? [y/n]:y


1 out of 1 certificate requests certified, commit? [y/n]y
Write out database with 1 new entries
Data Base Updated
```
- (5)
  - testservercert.crtをserverkeystore.jksに登録しています
```
$ sudo keytool -importcert -alias testRootCA -file testservercert.crt -keystore serverkeystore.jks -trustcacerts -storepass hogestore
Owner: CN=www.example.com, OU=BaseTechnology, O=Core, L=Saitama, ST=Kawaguchi, C=JP
Issuer: EMAILADDRESS=testca@example.com, CN=www.testca.com, OU=Sign, O=TestCA, ST=Tokyo, C=JP
Serial number: 80746b6db88c75b0
Valid from: Sun Apr 16 19:20:56 JST 2017 until: Thu Apr 15 19:20:56 JST 2021
Certificate fingerprints:
	 MD5:  22:19:D4:A4:2A:27:5A:45:2D:97:96:3B:44:44:55:44
	 SHA1: 8F:62:A0:21:32:2A:DE:06:C6:B3:EF:8B:2D:34:49:05:9D:8D:6F:D7
	 SHA256: 58:46:43:AC:FE:9D:F9:56:92:50:81:6D:21:C4:E0:FD:89:CA:5D:19:4D:2F:E7:76:BC:40:B7:34:01:97:9F:3E
	 Signature algorithm name: SHA256withRSA
	 Version: 3

Extensions: 

#1: ObjectId: 2.16.840.1.113730.1.13 Criticality=false
0000: 16 1D 4F 70 65 6E 53 53   4C 20 47 65 6E 65 72 61  ..OpenSSL Genera
0010: 74 65 64 20 43 65 72 74   69 66 69 63 61 74 65     ted Certificate


#2: ObjectId: 2.5.29.35 Criticality=false
AuthorityKeyIdentifier [
KeyIdentifier [
0000: B7 4C C0 57 1C 1C 18 A9   01 53 6C 02 4D E9 A6 EE  .L.W.....Sl.M...
0010: 57 A3 BF 74                                        W..t
]
]

#3: ObjectId: 2.5.29.19 Criticality=false
BasicConstraints:[
  CA:false
  PathLen: undefined
]

#4: ObjectId: 2.5.29.14 Criticality=false
SubjectKeyIdentifier [
KeyIdentifier [
0000: A5 AC A3 4B B1 85 70 5E   B2 51 05 F2 78 D0 31 86  ...K..p^.Q..x.1.
0010: B7 1F E3 7A                                        ...z
]
]

Trust this certificate? [no]:  yes
Certificate was added to keystore
```
- (6)
  - serverkeystore.jksに登録された内容を確認するためのコマンドです。
```
$ sudo keytool -list -v -keystore serverkeystore.jks -storepass hogestore

Keystore type: JKS
Keystore provider: SUN

Your keystore contains 2 entries

Alias name: testkeystore
Creation date: Apr 16, 2017
Entry type: PrivateKeyEntry
Certificate chain length: 1
Certificate[1]:
Owner: CN=www.example.com, OU=BaseTechnology, O=Core, L=Saitama, ST=Kawaguchi, C=JP
Issuer: CN=www.example.com, OU=BaseTechnology, O=Core, L=Saitama, ST=Kawaguchi, C=JP
Serial number: 75184547
Valid from: Sun Apr 16 18:57:13 JST 2017 until: Wed Apr 14 18:57:13 JST 2027
Certificate fingerprints:
	 MD5:  FD:80:17:B3:45:27:AF:87:67:6B:DF:D4:7B:6D:B5:BA
	 SHA1: 5A:16:9C:14:58:F5:F5:90:D7:0A:71:4B:EE:C3:37:F0:E5:6E:CC:F5
	 SHA256: 05:10:8E:B6:58:C9:5D:4B:4B:E8:51:72:D6:9B:FB:AD:48:F4:C8:3A:3A:41:3A:5C:D7:1B:41:93:FA:1A:69:CC
	 Signature algorithm name: SHA256withRSA
	 Version: 3

Extensions: 

#1: ObjectId: 2.5.29.14 Criticality=false
SubjectKeyIdentifier [
KeyIdentifier [
0000: A5 AC A3 4B B1 85 70 5E   B2 51 05 F2 78 D0 31 86  ...K..p^.Q..x.1.
0010: B7 1F E3 7A                                        ...z
]
]



*******************************************
*******************************************


Alias name: testrootca
Creation date: Apr 16, 2017
Entry type: trustedCertEntry

Owner: CN=www.example.com, OU=BaseTechnology, O=Core, L=Saitama, ST=Kawaguchi, C=JP
Issuer: EMAILADDRESS=testca@example.com, CN=www.testca.com, OU=Sign, O=TestCA, ST=Tokyo, C=JP
Serial number: 80746b6db88c75b0
Valid from: Sun Apr 16 19:20:56 JST 2017 until: Thu Apr 15 19:20:56 JST 2021
Certificate fingerprints:
	 MD5:  22:19:D4:A4:2A:27:5A:45:2D:97:96:3B:44:44:55:44
	 SHA1: 8F:62:A0:21:32:2A:DE:06:C6:B3:EF:8B:2D:34:49:05:9D:8D:6F:D7
	 SHA256: 58:46:43:AC:FE:9D:F9:56:92:50:81:6D:21:C4:E0:FD:89:CA:5D:19:4D:2F:E7:76:BC:40:B7:34:01:97:9F:3E
	 Signature algorithm name: SHA256withRSA
	 Version: 3

Extensions: 

#1: ObjectId: 2.16.840.1.113730.1.13 Criticality=false
0000: 16 1D 4F 70 65 6E 53 53   4C 20 47 65 6E 65 72 61  ..OpenSSL Genera
0010: 74 65 64 20 43 65 72 74   69 66 69 63 61 74 65     ted Certificate


#2: ObjectId: 2.5.29.35 Criticality=false
AuthorityKeyIdentifier [
KeyIdentifier [
0000: B7 4C C0 57 1C 1C 18 A9   01 53 6C 02 4D E9 A6 EE  .L.W.....Sl.M...
0010: 57 A3 BF 74                                        W..t
]
]

#3: ObjectId: 2.5.29.19 Criticality=false
BasicConstraints:[
  CA:false
  PathLen: undefined
]

#4: ObjectId: 2.5.29.14 Criticality=false
SubjectKeyIdentifier [
KeyIdentifier [
0000: A5 AC A3 4B B1 85 70 5E   B2 51 05 F2 78 D0 31 86  ...K..p^.Q..x.1.
0010: B7 1F E3 7A                                        ...z
]
]



*******************************************
*******************************************

```

### truststore発行手順(詳細)
先程のたった1工程しか存在しないtruststore発行手順ですが、コマンド結果を添付しておきます。
```
$ keytool -import -keystore serverTruststore.jks -alias serverTruststore -file testservercert.crt 
Enter keystore password:                   ##### 作成したhogekeyを入力 ##### 
Re-enter new password: 
Owner: CN=www.example.com, OU=BaseTechnology, O=Core, L=Saitama, ST=Kawaguchi, C=JP
Issuer: EMAILADDRESS=testca@example.com, CN=www.testca.com, OU=Sign, O=TestCA, ST=Tokyo, C=JP
Serial number: 80746b6db88c75b0
Valid from: Sun Apr 16 19:20:56 JST 2017 until: Thu Apr 15 19:20:56 JST 2021
Certificate fingerprints:
	 MD5:  22:19:D4:A4:2A:27:5A:45:2D:97:96:3B:44:44:55:44
	 SHA1: 8F:62:A0:21:32:2A:DE:06:C6:B3:EF:8B:2D:34:49:05:9D:8D:6F:D7
	 SHA256: 58:46:43:AC:FE:9D:F9:56:92:50:81:6D:21:C4:E0:FD:89:CA:5D:19:4D:2F:E7:76:BC:40:B7:34:01:97:9F:3E
	 Signature algorithm name: SHA256withRSA
	 Version: 3

Extensions: 

#1: ObjectId: 2.16.840.1.113730.1.13 Criticality=false
0000: 16 1D 4F 70 65 6E 53 53   4C 20 47 65 6E 65 72 61  ..OpenSSL Genera
0010: 74 65 64 20 43 65 72 74   69 66 69 63 61 74 65     ted Certificate


#2: ObjectId: 2.5.29.35 Criticality=false
AuthorityKeyIdentifier [
KeyIdentifier [
0000: B7 4C C0 57 1C 1C 18 A9   01 53 6C 02 4D E9 A6 EE  .L.W.....Sl.M...
0010: 57 A3 BF 74                                        W..t
]
]

#3: ObjectId: 2.5.29.19 Criticality=false
BasicConstraints:[
  CA:false
  PathLen: undefined
]

#4: ObjectId: 2.5.29.14 Criticality=false
SubjectKeyIdentifier [
KeyIdentifier [
0000: A5 AC A3 4B B1 85 70 5E   B2 51 05 F2 78 D0 31 86  ...K..p^.Q..x.1.
0010: B7 1F E3 7A                                        ...z
]
]

Trust this certificate? [no]:  yes
Certificate was added to keystore
```


# FAQなど

- 拡張子CRTとCERの違いは?
  - 拡張子CRTとCERの２つは内容が同じです。
  - CERはマイクロソフト系で呼ばれるようです。
    - http://qiita.com/kunichiko/items/12cbccaadcbf41c72735
- ディストリビューションで違いはあるのか?
  - 「Debian・Ubuntu」と「 Redhat・CentOS」でディレクトリなどに違いがあるので注意する
  - 各種ファイル名などのデフォルト値は以下に記載されている。
    - /etc/pki/tls/openssl.cnf(Redhat, CentOS)
    - /etc/ssl/openssl.cnf(Debian, Ubuntu)
- keytoolで指定されているaliasとは何か?
  - プログラム上から識別されるものであることがわかっている。
  - 最初に鍵を作って、あとでkeytoolコマンドの-trustcacerts オプションでこのaliasをあわせないと証明書連鎖の構築ができなさそう。。


# MEMO
- SSLがここまで混乱させるのはなぜか?
  - 仕様上はここまででOKみたいなことがあるので、パターンパターンで異なる。
    - たとえば、truststoreの構造などはパターンパターンで異なる
  - CAスクリプトをopensslで書いたりしている。ネット上では色々異なるパターンがある
  - ディストリビューションによってCAを作成する際に存在するパスが異なる。
  - 古いコマンドかどうかでkeygen, keygenpairの違いや、importとimportcertの違いなどがある

# TODO
- clientのkeystoreとtruststoreなども試したらのせておきたい。
- kafkaの場合も参考に載せておきたい
 - http://docs.confluent.io/2.0.0/kafka/ssl.html



