# 概要
opensslコマンドを利用してECDSAのX509証明書発行を試してみる

# 詳細
利用可能な楕円曲線一覧は下記コマンドで確認することができます。
```
$ openssl ecparam -list_curves
  secp112r1 : SECG/WTLS curve over a 112 bit prime field
  secp112r2 : SECG curve over a 112 bit prime field
  secp128r1 : SECG curve over a 128 bit prime field
  secp128r2 : SECG curve over a 128 bit prime field
  secp160k1 : SECG curve over a 160 bit prime field
  secp160r1 : SECG curve over a 160 bit prime field
  secp160r2 : SECG/WTLS curve over a 160 bit prime field
  secp192k1 : SECG curve over a 192 bit prime field
  secp224k1 : SECG curve over a 224 bit prime field
  secp224r1 : NIST/SECG curve over a 224 bit prime field
  secp256k1 : SECG curve over a 256 bit prime field
  secp384r1 : NIST/SECG curve over a 384 bit prime field
  secp521r1 : NIST/SECG curve over a 521 bit prime field
  prime192v1: NIST/X9.62/SECG curve over a 192 bit prime field
  prime192v2: X9.62 curve over a 192 bit prime field
  prime192v3: X9.62 curve over a 192 bit prime field
  prime239v1: X9.62 curve over a 239 bit prime field
  prime239v2: X9.62 curve over a 239 bit prime field
  prime239v3: X9.62 curve over a 239 bit prime field
  prime256v1: X9.62/SECG curve over a 256 bit prime field
  sect113r1 : SECG curve over a 113 bit binary field

(snip)
```

上記で表示された「prime256v1」を楕円曲線の種類として指定して、「-genkey」オプションを指定して秘密鍵を作成します。
```
$ openssl ecparam -name prime256v1 -genkey > localhost.key
```

発行された秘密鍵localhost.keyを確認します。
```
$ cat localhost.key 
-----BEGIN EC PARAMETERS-----
BggqhkjOPQMBBw==
-----END EC PARAMETERS-----
-----BEGIN EC PRIVATE KEY-----
MHcCAQEEIC+A7/yJ7fVbcym82A3oC/EQjSsbAVMSrkRhHj0LgjxmoAoGCCqGSM49
AwEHoUQDQgAEHD8Y0Owj7x2p3Cf4QgQM3bh7nvdPVUuVIwkyDLnfgjy3o0j+aUIF
i8PUcEagD+7ok7lmB7B7MY3fRjj5rwkyAQ==
-----END EC PRIVATE KEY-----
```

秘密鍵情報localhost.keyをデコードしてみます。
```
$ openssl ec -in localhost.key -text -noout
read EC key
Private-Key: (256 bit)
priv:
    2f:80:ef:fc:89:ed:f5:5b:73:29:bc:d8:0d:e8:0b:
    f1:10:8d:2b:1b:01:53:12:ae:44:61:1e:3d:0b:82:
    3c:66
pub:
    04:1c:3f:18:d0:ec:23:ef:1d:a9:dc:27:f8:42:04:
    0c:dd:b8:7b:9e:f7:4f:55:4b:95:23:09:32:0c:b9:
    df:82:3c:b7:a3:48:fe:69:42:05:8b:c3:d4:70:46:
    a0:0f:ee:e8:93:b9:66:07:b0:7b:31:8d:df:46:38:
    f9:af:09:32:01
ASN1 OID: prime256v1
NIST CURVE: P-256
```

続いて、作成した秘密鍵を元にしてCSRを発行します。 今回は手元で発行を試すだけのテスト用途なので適当な情報で入力をしてみます。
```
$ openssl req -new -sha256 -key localhost.key > localhost.csr
You are about to be asked to enter information that will be incorporated
into your certificate request.
What you are about to enter is what is called a Distinguished Name or a DN.
There are quite a few fields but you can leave some blank
For some fields there will be a default value,
If you enter '.', the field will be left blank.
-----
Country Name (2 letter code) [AU]:JP
State or Province Name (full name) [Some-State]:Saitama Pref
Locality Name (eg, city) []:Kawaguchi City
Organization Name (eg, company) [Internet Widgits Pty Ltd]:Test Company
Organizational Unit Name (eg, section) []:
Common Name (e.g. server FQDN or YOUR name) []:example.co.jp
Email Address []:

Please enter the following 'extra' attributes
to be sent with your certificate request
A challenge password []:
An optional company name []:
```


CSRを生成します。下記の値になっていることが確認できます。
- Public Key Algorithm: id-ecPublicKey
- Signature Algorithm: ecdsa-with-SHA256
```
$ openssl req -text -noout -in localhost.csr
Certificate Request:
    Data:
        Version: 1 (0x0)
        Subject: C = JP, ST = Saitama Pref, L = Kawaguchi City, O = Test Company, CN = example.co.jp
        Subject Public Key Info:
            Public Key Algorithm: id-ecPublicKey
                Public-Key: (256 bit)
                pub:
                    04:1c:3f:18:d0:ec:23:ef:1d:a9:dc:27:f8:42:04:
                    0c:dd:b8:7b:9e:f7:4f:55:4b:95:23:09:32:0c:b9:
                    df:82:3c:b7:a3:48:fe:69:42:05:8b:c3:d4:70:46:
                    a0:0f:ee:e8:93:b9:66:07:b0:7b:31:8d:df:46:38:
                    f9:af:09:32:01
                ASN1 OID: prime256v1
                NIST CURVE: P-256
        Attributes:
            (none)
            Requested Extensions:
    Signature Algorithm: ecdsa-with-SHA256
    Signature Value:
        30:44:02:20:14:fb:3b:4e:5f:16:33:88:5d:e2:1d:06:4d:8e:
        4a:07:38:6c:9b:a5:9c:c4:f9:5c:82:b2:1d:71:e7:00:09:a6:
        02:20:5a:7b:60:c3:f0:99:b1:b5:93:b3:75:0a:7d:e8:3b:51:
        c0:33:f1:50:5f:49:38:19:cc:40:27:71:36:bf:22:0f
```

作成した「秘密鍵」と「証明書署名要求」でCSRに署名することにより、「サーバ証明書」を作成します。
「-signkey」オプションを使用します。
```
$ openssl x509 -req -signkey localhost.key < localhost.csr > localhost.crt
Certificate request self-signature ok
subject=C = JP, ST = Saitama Pref, L = Kawaguchi City, O = Test Company, CN = example.co.jp
```

生成されたサーバ証明書を確認します
```
$ cat localhost.crt 
-----BEGIN CERTIFICATE-----
MIIB0zCCAXkCFDJZfiSVJYDSvDK4fnOa2m4MZXvxMAoGCCqGSM49BAMCMGwxCzAJ
BgNVBAYTAkpQMRUwEwYDVQQIDAxTYWl0YW1hIFByZWYxFzAVBgNVBAcMDkthd2Fn
dWNoaSBDaXR5MRUwEwYDVQQKDAxUZXN0IENvbXBhbnkxFjAUBgNVBAMMDWV4YW1w
bGUuY28uanAwHhcNMjIxMTEzMjMyNDI1WhcNMjIxMjEzMjMyNDI1WjBsMQswCQYD
VQQGEwJKUDEVMBMGA1UECAwMU2FpdGFtYSBQcmVmMRcwFQYDVQQHDA5LYXdhZ3Vj
aGkgQ2l0eTEVMBMGA1UECgwMVGVzdCBDb21wYW55MRYwFAYDVQQDDA1leGFtcGxl
LmNvLmpwMFkwEwYHKoZIzj0CAQYIKoZIzj0DAQcDQgAEHD8Y0Owj7x2p3Cf4QgQM
3bh7nvdPVUuVIwkyDLnfgjy3o0j+aUIFi8PUcEagD+7ok7lmB7B7MY3fRjj5rwky
ATAKBggqhkjOPQQDAgNIADBFAiEApPfLx9X0rbSZHvWZhQta/uM51swSz3cqDVON
BPP1KUoCIAzgD9U0xMS8M6Jv49HSWh0e3mJ45e0tIhF7N6R2SR8k
-----END CERTIFICATE-----
```

生成したサーバ証明書の情報を表示してみます。
```
$ openssl x509 -text -noout -in localhost.crt
Certificate:
    Data:
        Version: 1 (0x0)
        Serial Number:
            32:59:7e:24:95:25:80:d2:bc:32:b8:7e:73:9a:da:6e:0c:65:7b:f1
        Signature Algorithm: ecdsa-with-SHA256
        Issuer: C = JP, ST = Saitama Pref, L = Kawaguchi City, O = Test Company, CN = example.co.jp
        Validity
            Not Before: Nov 13 23:24:25 2022 GMT
            Not After : Dec 13 23:24:25 2022 GMT
        Subject: C = JP, ST = Saitama Pref, L = Kawaguchi City, O = Test Company, CN = example.co.jp
        Subject Public Key Info:
            Public Key Algorithm: id-ecPublicKey
                Public-Key: (256 bit)
                pub:
                    04:1c:3f:18:d0:ec:23:ef:1d:a9:dc:27:f8:42:04:
                    0c:dd:b8:7b:9e:f7:4f:55:4b:95:23:09:32:0c:b9:
                    df:82:3c:b7:a3:48:fe:69:42:05:8b:c3:d4:70:46:
                    a0:0f:ee:e8:93:b9:66:07:b0:7b:31:8d:df:46:38:
                    f9:af:09:32:01
                ASN1 OID: prime256v1
                NIST CURVE: P-256
    Signature Algorithm: ecdsa-with-SHA256
    Signature Value:
        30:45:02:21:00:a4:f7:cb:c7:d5:f4:ad:b4:99:1e:f5:99:85:
        0b:5a:fe:e3:39:d6:cc:12:cf:77:2a:0d:53:8d:04:f3:f5:29:
        4a:02:20:0c:e0:0f:d5:34:c4:c4:bc:33:a2:6f:e3:d1:d2:5a:
        1d:1e:de:62:78:e5:ed:2d:22:11:7b:37:a4:76:49:1f:24
```

# まとめ
opensslコマンドでECDSA証明書の発行を試しました

# 参考情報
- https://www.casleyconsulting.co.jp/blog/engineer/3014/
