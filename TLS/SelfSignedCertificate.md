# 概要
自己証明書の作成方法について

opensslコマンドを駆使した自己証明書の作成方法についてまとめます。


# 詳細

秘密鍵を作成する。
```
$ openssl genrsa -aes128 2048 > server.key
Generating RSA private key, 2048 bit long modulus
.........+++
................................................................+++
e is 65537 (0x10001)
Enter pass phrase:
Verifying - Enter pass phrase:
```

公開鍵を作成する
```
$ openssl req -new -key server.key > server.csr
Enter pass phrase for server.key:
You are about to be asked to enter information that will be incorporated
into your certificate request.
What you are about to enter is what is called a Distinguished Name or a DN.
There are quite a few fields but you can leave some blank
For some fields there will be a default value,
If you enter '.', the field will be left blank.
-----
Country Name (2 letter code) [AU]:JP
State or Province Name (full name) [Some-State]:Saitama
Locality Name (eg, city) []:Kawaguchi
Organization Name (eg, company) [Internet Widgits Pty Ltd]:OreOre Company
Organizational Unit Name (eg, section) []:TestDept
Common Name (e.g. server FQDN or YOUR name) []:example.co.jp
Email Address []:

Please enter the following 'extra' attributes
to be sent with your certificate request
A challenge password []:
An optional company name []:
```

上記２つの秘密鍵、公開鍵は実は次のようなコマンド１回で作成することもできます。
```
$ openssl req -new -keyout server.key -out server.csr
```

続いて、サーバ証明書を作成する
```
$ openssl x509 -in server.csr -days 365000 -req -signkey server.key > server.crt
Signature ok
subject=/C=JP/ST=Saitama/L=Kawaguchi/O=OreOre Company/OU=TestDept/CN=example.co.jp
Getting Private key
Enter pass phrase for server.key:
```

以上により次の３つのファイルが生成されます。
```
$ ls
server.crt  server.csr	server.key
```

生成したサーバ証明書を確認する。
```
$ openssl x509 -text -noout -in server.crt 
Certificate:
    Data:
        Version: 1 (0x0)
        Serial Number: 11510764318465352677 (0x9fbe7329375e63e5)
    Signature Algorithm: sha256WithRSAEncryption
        Issuer: C=JP, ST=Saitama, L=Kawaguchi, O=OreOre Company, OU=TestDept, CN=example.co.jp
        Validity
            Not Before: Oct 28 14:09:38 2017 GMT
            Not After : Feb 28 14:09:38 3017 GMT
        Subject: C=JP, ST=Saitama, L=Kawaguchi, O=OreOre Company, OU=TestDept, CN=example.co.jp
        Subject Public Key Info:
            Public Key Algorithm: rsaEncryption
                Public-Key: (2048 bit)
                Modulus:
                    00:b6:b5:92:b2:26:5d:ab:74:c7:6b:23:b3:6a:5b:
                    b8:aa:dd:fa:de:c2:a0:d1:6b:3e:ba:67:17:2f:7b:
                    56:64:59:f5:0e:e0:44:79:79:d5:08:9a:3f:bf:43:
                    d0:5e:45:fc:69:1d:86:d5:9b:79:7a:61:2b:d9:0b:
                    07:31:b0:28:87:af:53:67:98:81:56:51:19:68:38:
                    a2:ad:75:cc:20:17:37:e5:63:37:92:50:a9:7e:bd:
                    d2:63:c5:27:ab:32:e6:9f:ad:da:92:95:4c:67:d7:
                    0d:55:23:f8:12:62:b1:59:9a:33:ac:08:63:b9:5f:
                    39:d7:9d:b3:49:67:02:73:5a:d8:ee:9f:8f:66:d3:
                    3b:3e:f8:e2:8e:1d:16:0d:9d:39:08:50:1d:e9:7d:
                    b3:f7:cf:16:ff:64:4d:21:1f:06:2f:64:55:cd:99:
                    b8:e0:9f:5d:3d:0b:cb:c1:f7:f8:77:f4:41:fc:3d:
                    1f:07:8b:13:03:c4:a0:70:3b:a9:cb:08:ff:6f:b2:
                    c2:74:c8:88:4f:23:71:b6:06:cd:62:ca:df:62:9b:
                    80:8c:76:7b:ef:16:05:bc:7c:4f:a6:c1:78:0f:27:
                    2e:51:93:a5:0f:0b:23:25:84:28:d6:9a:b7:8b:9e:
                    bf:a5:2b:9d:57:37:f5:0d:d0:03:e0:04:89:fd:e0:
                    c7:f5
                Exponent: 65537 (0x10001)
    Signature Algorithm: sha256WithRSAEncryption
         66:45:e7:60:e4:88:21:e0:25:08:77:db:fa:25:bf:ba:53:1c:
         de:88:21:bd:05:a3:94:31:a4:20:2f:2b:82:70:4e:fe:90:1d:
         99:db:a1:a9:18:5f:f9:10:0d:79:1e:2d:c6:10:08:44:93:99:
         94:4a:37:eb:38:49:1d:db:c3:64:b0:88:2c:49:f6:9a:9b:a9:
         ca:06:6f:a9:25:60:05:72:3c:7f:6f:1f:41:45:64:7a:66:a7:
         02:ef:95:57:cf:cd:b1:f3:7f:6d:e6:0f:a8:54:fd:56:03:6e:
         cd:68:1d:89:80:90:c4:3b:fb:09:fc:41:fb:95:b9:70:a2:f8:
         4e:24:5f:42:0c:bf:c9:5f:a8:7e:14:0e:9a:bc:20:13:78:5e:
         1f:0e:01:16:c7:7d:b4:00:2d:55:bc:61:64:ba:67:fe:e4:3d:
         af:19:5d:00:81:47:28:64:4a:06:43:62:20:eb:59:a9:3f:c4:
         2f:3c:af:10:69:4a:a8:70:b7:0f:4a:a9:a8:9f:49:d6:e5:67:
         37:32:da:1b:cf:b2:ce:81:47:ff:cf:b4:95:c5:fb:e6:37:34:
         14:b5:f1:71:04:a6:10:ea:84:26:4a:88:47:d6:5c:be:52:c8:
         dc:14:62:22:ea:7e:37:00:9e:fa:60:3f:31:5f:ff:2f:e8:79:
         bc:ae:46:c4
```


IssuerとSubjectが一致することで自己署名であることを確認する。これで明らかに一致してることが確認できる。
ルート証明書はこの作りとなっている。
```
$ openssl x509 -text -noout -in server.crt  | grep -e Issuer: -e Subject:
        Issuer: C=JP, ST=Saitama, L=Kawaguchi, O=OreOre Company, OU=TestDept, CN=example.co.jp
        Subject: C=JP, ST=Saitama, L=Kawaguchi, O=OreOre Company, OU=TestDept, CN=example.co.jp
```

念のためにserver.keyとserver.crtが一致していることを確認する。これを確認することによりkeyとcrtが確実にペアであることを保証することが出来ます。
```
$ openssl rsa -in server.key -modulus -noout | openssl md5
Enter pass phrase for server.key:
(stdin)= c83dfb14665389f18d3c2b019bc8575b
$ openssl x509 -in server.crt -modulus -noout | openssl md5
(stdin)= c83dfb14665389f18d3c2b019bc8575b
```

以上でSSLサーバ(HTTPS)が起動できます。今回は自己証明書で中間証明書などは存在しないので次のコマンドで起動することができます。
```
$ sudo openssl s_server -accept 443 -cert server.crt -key server.key -www -debug
Enter pass phrase for server.key:
Using default temp DH parameters
Using default temp ECDH parameters
ACCEPT

