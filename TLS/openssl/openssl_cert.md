# 概要
opensslコマンドの証明書・秘密鍵・CSR・CRLなどのファイルについて

# 詳細

## 証明書・秘密鍵・CSR・CRLの内容を確認する

### 各種証明書確認
以下の３つはコマンドが似ているので一応整理も含めて載せておく。

- 証明書ファイルの内容を確認
```
$ openssl rsa -text -noout -in server.key 
Private-Key: (2048 bit)
modulus:
    00:dc:d4:78:45:af:ec:78:66:d7:6a:04:6f:58:7e:
    cc:3a:d2:a6:3b:37:78:62:02:bd:3c:80:cc:2d:8a:
    55:83:1c:10:43:3b:50:6e:6d:f2:69:c6:06:b7:fd:
    02:21:55:d4:e9:e4:ad:30:6e:f7:e6:7c:0d:71:89:
    92:a3:cc:73:e2:2f:c8:12:48:37:4c:f5:dc:3f:2e:
    28:3a:d5:41:45:19:80:6c:61:f7:2c:6b:d9:27:5b:
    a8:1d:a6:ee:5d:5d:fd:99:34:cf:1d:f8:ab:c5:12:
    52:0f:6b:72:70:37:a8:4c:d6:39:a0:b0:24:ca:07:
    c6:48:00:f2:b2:87:6d:fd:30:d8:59:c4:0a:7d:ae:
    29:00:30:e0:f5:d6:1a:59:6c:13:43:2a:96:e2:5c:
    cd:57:1c:42:3f:83:29:9d:5d:6d:b6:65:f9:fe:87:
    d1:51:49:83:57:3a:eb:31:7f:bd:8b:72:0f:84:3c:
    73:e3:f9:25:e3:af:45:2d:ef:40:03:77:d7:a2:af:
    2c:da:72:36:2d:ea:0c:d9:e7:40:55:8d:24:57:f9:
    54:6f:b2:16:63:75:61:b7:73:5a:b1:6d:5f:2e:2e:
    27:bd:74:7f:e8:30:2b:92:d3:9c:17:2f:d3:31:e9:
    b2:63:37:6c:8e:72:49:7d:e5:6b:a8:35:f1:72:88:
    99:4d
publicExponent: 65537 (0x10001)
privateExponent:
```

- 秘密鍵ファイルの内容を確認
```
$ sudo openssl rsa -text -noout -in <秘密鍵>
```

- CSRファイルの内容を確認
```
$ sudo  openssl req -text -noout -in <CSR>
```

- CRLファイルの内容を確認
```
$ openssl crl -inform der -in crl.der -text
or
$ openssl crl -in crl.pem -text
```

例えば、以下で取得できるcrlを覗いてみると
- https://www.jp.websecurity.symantec.com/repository/crl.html
```
$  openssl crl -inform der -in pca1.1.1.crl -text
Certificate Revocation List (CRL):
        Version 1 (0x0)
        Signature Algorithm: sha1WithRSAEncryption
        Issuer: /C=US/O=VeriSign, Inc./OU=Class 1 Public Primary Certification Authority
        Last Update: Dec 15 00:00:00 2016 GMT
        Next Update: Dec 31 23:59:59 2017 GMT
Revoked Certificates:
    Serial Number: 2CD24B62C497A417CD6EA3C89C7A2DC8
        Revocation Date: Apr  1 17:56:15 2004 GMT
    Serial Number: 3A45DE56CB02CDDCDC4E7763221BD4D5
        Revocation Date: May  8 19:22:34 2001 GMT
    Serial Number: 415D8836811520D5808346A85992782C
        Revocation Date: Jul  6 16:57:23 2001 GMT
    Serial Number: 473981FFFD8481F195F9EB18C27C0DF1
        Revocation Date: Jan  9 18:06:12 2003 GMT
    Serial Number: 70547E6AE2BAD8767F47A99910415E67
        Revocation Date: Sep 23 17:00:08 2002 GMT
    Serial Number: 7E0B5DDE18F2396682A68F65223823C8
        Revocation Date: May  8 19:08:21 2001 GMT
    Serial Number: D05448601867D3AD35CA2F0D4A27955E
        Revocation Date: Dec 11 18:26:21 2001 GMT
    Signature Algorithm: sha1WithRSAEncryption
        c3:4b:60:3b:0d:72:df:46:09:c7:50:d1:b7:9b:28:93:68:d9:
        f0:01:c0:2a:49:33:9b:22:9a:db:ea:5d:a5:40:62:5b:69:b6:
        38:73:75:a6:eb:11:fd:fc:6a:9b:fc:2e:dd:d0:86:a6:ef:9f:
        a4:16:86:3f:89:4e:a2:c6:e2:7a:5f:00:08:3a:cc:97:86:91:
        e1:2f:ff:37:5a:c0:1c:61:a0:0b:d1:6a:29:31:e5:de:ad:dc:
        a4:70:0e:59:d4:52:e7:18:f8:2d:1f:57:a9:a4:18:93:6c:f3:
        cc:dd:dc:2b:d6:61:12:e5:6f:0d:cf:21:cd:65:c0:ea:b4:a3:
        35:c5
-----BEGIN X509 CRL-----
MIICHjCCAYcwDQYJKoZIhvcNAQEFBQAwXzELMAkGA1UEBhMCVVMxFzAVBgNVBAoT
DlZlcmlTaWduLCBJbmMuMTcwNQYDVQQLEy5DbGFzcyAxIFB1YmxpYyBQcmltYXJ5
IENlcnRpZmljYXRpb24gQXV0aG9yaXR5Fw0xNjEyMTUwMDAwMDBaFw0xNzEyMzEy
MzU5NTlaMIH2MCECECzSS2LEl6QXzW6jyJx6LcgXDTA0MDQwMTE3NTYxNVowIQIQ
OkXeVssCzdzcTndjIhvU1RcNMDEwNTA4MTkyMjM0WjAhAhBBXYg2gRUg1YCDRqhZ
kngsFw0wMTA3MDYxNjU3MjNaMCECEEc5gf/9hIHxlfnrGMJ8DfEXDTAzMDEwOTE4
MDYxMlowIQIQcFR+auK62HZ/R6mZEEFeZxcNMDIwOTIzMTcwMDA4WjAhAhB+C13e
GPI5ZoKmj2UiOCPIFw0wMTA1MDgxOTA4MjFaMCICEQDQVEhgGGfTrTXKLw1KJ5Ve
Fw0wMTEyMTExODI2MjFaMA0GCSqGSIb3DQEBBQUAA4GBAMNLYDsNct9GCcdQ0beb
KJNo2fABwCpJM5simtvqXaVAYltptjhzdabrEf38apv8Lt3Qhqbvn6QWhj+JTqLG
4npfAAg6zJeGkeEv/zdawBxhoAvRaikx5d6t3KRwDlnUUucY+C0fV6mkGJNs88zd
3CvWYRLlbw3PIc1lwOq0ozXF
-----END X509 CRL-----
```

### 証明書(crt)の内容を確認する
- text形式で表示(先に出たコマンドと重複)
```
$ openssl x509 -in server.crt -text
```

- 証明書の使用目的を表示
```
$ openssl x509 -in server.crt -purpose
```

- ASN.1形式で表示
```
$ openssl asn1parse -in server.crt
```

- 証明書から公開鍵を取り出す
```
$ openssl x509 -in server.crt -pubkey -noout
```

### 証明書の失効処理を行う
- 証明書の失効処理を行う
```
$ openssl ca -revoke newcerts/01.pem
```

- CRLの生成を行う
```
$ openssl ca -gencrl -out CA.crl
```

- CRLの内容を確認する
```
$ openssl crl -in CA.crl -text
```

## 変換
### .crtから.pemに変換する
もちろん逆もできる
```
$ openssl x509 -in source.crt -out tmp.der -outform DER
$ openssl x509 -in tmp.der -inform DER -out dest.pem -outform pem
```

### 秘密鍵と公開鍵からp12形式を取得する
```
$ openssl pkcs12 -export -inkey server.key -in server.crt -out server.p12
```

### PKCS#12形式(pfx or p12)から証明書を取り出す
```
$ openssl pkcs12 -nokeys -in cert.der.pfx -out cert.crt.pem
or
$ openssl pkcs12 -nokeys -in cert.der.p12 -out cert.crt.pem
```

### PKCS#12形式(pfx or p12)から秘密鍵を取り出す
```
$ openssl pkcs12 -nocerts -in cert.der.pfx -out private.key.pem
or
$ openssl pkcs12 -nocerts -in cert.der.p12 -out private.key.pem
```

### 証明書ファイルと秘密鍵ファイルの整合性を確認する
次の２つのコマンドの結果を確認することで一致すれば整合性があることを表しています。
```
$ sudo openssl x509 -noout -modulus -in 証明書ファイル | md5sum
$ sudo openssl rsa -noout -modulus -in 秘密鍵ファイル | md5sum
```

## 署名する
一般的に1をよく使うのでこれだけ覚えておけば十分かも。2や3はこんなこともできるんだ程度に見ておけば良い。

1. 自分の秘密鍵で自己署名した証明書を作成する
```
openssl x509 -in server.csr -out server.crt -req -signkey server.key -days 365
```

2. 秘密鍵作成,CSR作成,自己署名を一度にする(秘密鍵を暗号化しない)
```
$ openssl req -x509 -nodes -new -keyout server.key -out server.crt -days 365
```

3. 秘密鍵作成,CSR作成,自己署名を一度にする(秘密鍵を暗号化する)
```
$ openssl req -x509 -new -keyout server.key -out server.crt -days 365
```

# 参考URL
- OpenSSLコマンドの備忘録
  - https://qiita.com/takech9203/items/5206f8e2572e95209bbc
- opensslコマンド（まとめ）
  - http://assimane.blog.so-net.ne.jp/2011-09-24
