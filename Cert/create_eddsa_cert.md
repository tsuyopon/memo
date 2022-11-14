# 概要
opensslコマンドでEdDSAの証明書を発行します。

# 

```
$ openssl genpkey -algorithm ED25519 -out key.pem
```

生成された秘密鍵をcatします
```
$ cat key.pem 
-----BEGIN PRIVATE KEY-----
MC4CAQAwBQYDK2VwBCIEIKtyYUrd39N6LNOWo26gJ2O0q2f96KSZy5jZ6DJBM+u3
-----END PRIVATE KEY-----
```

秘密鍵情報を確認します(※1)
```
$ openssl pkey -text -noout -in key.pem 
ED25519 Private-Key:
priv:
    ab:72:61:4a:dd:df:d3:7a:2c:d3:96:a3:6e:a0:27:
    63:b4:ab:67:fd:e8:a4:99:cb:98:d9:e8:32:41:33:
    eb:b7
pub:
    4d:6b:0c:4a:d3:08:7f:5e:48:8d:ac:45:d5:2e:55:
    a8:84:c9:36:a9:31:de:38:ed:e9:c4:10:8d:e6:f5:
    f5:a8
```

秘密鍵から公開鍵を生成します
```
$ openssl pkey -in key.pem -pubout -out pubkey.pem
```

生成された公開鍵pubkey.pemを確認します。
```
$ cat pubkey.pem 
-----BEGIN PUBLIC KEY-----
MCowBQYDK2VwAyEATWsMStMIf15IjaxF1S5VqITJNqkx3jjt6cQQjeb19ag=
-----END PUBLIC KEY-----
```

公開鍵の確認時は(※1)に「-pubin」を付与します。
```
$ openssl pkey -text -noout -pubin -in pubkey.pem 
ED25519 Public-Key:
pub:
    4d:6b:0c:4a:d3:08:7f:5e:48:8d:ac:45:d5:2e:55:
    a8:84:c9:36:a9:31:de:38:ed:e9:c4:10:8d:e6:f5:
    f5:a8
```

CSRを生成します。テスト用途なので入力している内容は適当です。
```
$ openssl req -new -sha256 -key key.pem > localhost.csr
You are about to be asked to enter information that will be incorporated
into your certificate request.
What you are about to enter is what is called a Distinguished Name or a DN.
There are quite a few fields but you can leave some blank
For some fields there will be a default value,
If you enter '.', the field will be left blank.
-----
Country Name (2 letter code) [AU]:JP
State or Province Name (full name) [Some-State]:Saitama Pref
Locality Name (eg, city) []:Kawaguchi
Organization Name (eg, company) [Internet Widgits Pty Ltd]:Test Company 
Organizational Unit Name (eg, section) []:
Common Name (e.g. server FQDN or YOUR name) []:example.co.jp
Email Address []:

Please enter the following 'extra' attributes
to be sent with your certificate request
A challenge password []:
An optional company name []:
```

生成されたCSRをcatします。
```
$ cat localhost.csr
-----BEGIN CERTIFICATE REQUEST-----
MIHnMIGaAgEAMGcxCzAJBgNVBAYTAkpQMRUwEwYDVQQIDAxTYWl0YW1hIFByZWYx
EjAQBgNVBAcMCUthd2FndWNoaTEVMBMGA1UECgwMVGVzdCBDb21wYW55MRYwFAYD
VQQDDA1leGFtcGxlLmNvLmpwMCowBQYDK2VwAyEATWsMStMIf15IjaxF1S5VqITJ
Nqkx3jjt6cQQjeb19aigADAFBgMrZXADQQDiMc+qS4swn/SQzFVzD7gD0wS1Qpl/
a37ULr0zkzKNBetQoMurv/8rZwB27Zse8nOZVO2tl+Lp96Sv9i/NWmcI
-----END CERTIFICATE REQUEST-----
```

可視化して確認してみます。
```
$ openssl req -text -noout -in localhost.csr
Certificate Request:
    Data:
        Version: 1 (0x0)
        Subject: C = JP, ST = Saitama Pref, L = Kawaguchi, O = Test Company, CN = example.co.jp
        Subject Public Key Info:
            Public Key Algorithm: ED25519
                ED25519 Public-Key:
                pub:
                    4d:6b:0c:4a:d3:08:7f:5e:48:8d:ac:45:d5:2e:55:
                    a8:84:c9:36:a9:31:de:38:ed:e9:c4:10:8d:e6:f5:
                    f5:a8
        Attributes:
            (none)
            Requested Extensions:
    Signature Algorithm: ED25519
    Signature Value:
        e2:31:cf:aa:4b:8b:30:9f:f4:90:cc:55:73:0f:b8:03:d3:04:
        b5:42:99:7f:6b:7e:d4:2e:bd:33:93:32:8d:05:eb:50:a0:cb:
        ab:bf:ff:2b:67:00:76:ed:9b:1e:f2:73:99:54:ed:ad:97:e2:
        e9:f7:a4:af:f6:2f:cd:5a:67:08
```

```
$ openssl x509 -req -signkey key.pem < localhost.csr > localhost.crt
Certificate request self-signature ok
subject=C = JP, ST = Saitama Pref, L = Kawaguchi, O = Test Company, CN = example.co.jp
```

生成されたサーバ証明書をcatします
```
$ cat localhost.crt
-----BEGIN CERTIFICATE-----
MIIBiTCCATsCFH0jCR166BQYabA4T+uI1qsVsKNuMAUGAytlcDBnMQswCQYDVQQG
EwJKUDEVMBMGA1UECAwMU2FpdGFtYSBQcmVmMRIwEAYDVQQHDAlLYXdhZ3VjaGkx
FTATBgNVBAoMDFRlc3QgQ29tcGFueTEWMBQGA1UEAwwNZXhhbXBsZS5jby5qcDAe
Fw0yMjExMTQwMDEwMDhaFw0yMjEyMTQwMDEwMDhaMGcxCzAJBgNVBAYTAkpQMRUw
EwYDVQQIDAxTYWl0YW1hIFByZWYxEjAQBgNVBAcMCUthd2FndWNoaTEVMBMGA1UE
CgwMVGVzdCBDb21wYW55MRYwFAYDVQQDDA1leGFtcGxlLmNvLmpwMCowBQYDK2Vw
AyEATWsMStMIf15IjaxF1S5VqITJNqkx3jjt6cQQjeb19agwBQYDK2VwA0EArnUY
5vgUivejD9yQnTixMLXbQ1FVXy6XvLGEoA+7WjBK15nylTNNfWjuqPjUDpSA7W28
YZOsISedcjrogoHDAQ==
-----END CERTIFICATE-----
```

生成したサーバ証明書確認します。以下の情報が表示されている事が確認できます。
- Signature Algorithm: ED25519 
- Public Key Algorithm: ED25519

CSRと比較してSerial Number, Validityなどの他の情報が付与されていて署名値も変わっている事が確認できます。
```
$ openssl x509 -text -noout -in localhost.crt
Certificate:
    Data:
        Version: 1 (0x0)
        Serial Number:
            7d:23:09:1d:7a:e8:14:18:69:b0:38:4f:eb:88:d6:ab:15:b0:a3:6e
        Signature Algorithm: ED25519
        Issuer: C = JP, ST = Saitama Pref, L = Kawaguchi, O = Test Company, CN = example.co.jp
        Validity
            Not Before: Nov 14 00:10:08 2022 GMT
            Not After : Dec 14 00:10:08 2022 GMT
        Subject: C = JP, ST = Saitama Pref, L = Kawaguchi, O = Test Company, CN = example.co.jp
        Subject Public Key Info:
            Public Key Algorithm: ED25519
                ED25519 Public-Key:
                pub:
                    4d:6b:0c:4a:d3:08:7f:5e:48:8d:ac:45:d5:2e:55:
                    a8:84:c9:36:a9:31:de:38:ed:e9:c4:10:8d:e6:f5:
                    f5:a8
    Signature Algorithm: ED25519
    Signature Value:
        ae:75:18:e6:f8:14:8a:f7:a3:0f:dc:90:9d:38:b1:30:b5:db:
        43:51:55:5f:2e:97:bc:b1:84:a0:0f:bb:5a:30:4a:d7:99:f2:
        95:33:4d:7d:68:ee:a8:f8:d4:0e:94:80:ed:6d:bc:61:93:ac:
        21:27:9d:72:3a:e8:82:81:c3:01
```

# 公式情報
- /docs/man1.1.1/man1/openssl-genpkey.html
- /docs/man1.1.1/man1/openssl-pkey.html
