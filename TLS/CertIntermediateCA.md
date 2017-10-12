# 概要
中間証明書(別名: 中間CA証明書)について確認する
中間証明書はサーバ証明書などと同様にしてその中身をopensslコマンドで確認することができることをここでは確認します。

# 詳細
今回は例として以下のsymantecから適当に中間CA証明書をもってきます。
- https://www.jp.websecurity.symantec.com/repository/intermediate/server/ev_pro_ecc_hybrid.html

次の内容で上記から中間証明書データをコピーしてintermediate.certというファイル名で保存するものと仮定します。
```
$ cat intermediate.cert
-----BEGIN CERTIFICATE-----
MIIEYjCCA0qgAwIBAgIQcSI8pSIYXqxEzxdw0aiqXTANBgkqhkiG9w0BAQsFADCB
yjELMAkGA1UEBhMCVVMxFzAVBgNVBAoTDlZlcmlTaWduLCBJbmMuMR8wHQYDVQQL
ExZWZXJpU2lnbiBUcnVzdCBOZXR3b3JrMTowOAYDVQQLEzEoYykgMjAwNiBWZXJp
U2lnbiwgSW5jLiAtIEZvciBhdXRob3JpemVkIHVzZSBvbmx5MUUwQwYDVQQDEzxW
ZXJpU2lnbiBDbGFzcyAzIFB1YmxpYyBQcmltYXJ5IENlcnRpZmljYXRpb24gQXV0
aG9yaXR5IC0gRzUwHhcNMTUwNTEyMDAwMDAwWhcNMjUwNTExMjM1OTU5WjB/MQsw
CQYDVQQGEwJVUzEdMBsGA1UEChMUU3ltYW50ZWMgQ29ycG9yYXRpb24xHzAdBgNV
BAsTFlN5bWFudGVjIFRydXN0IE5ldHdvcmsxMDAuBgNVBAMTJ1N5bWFudGVjIENs
YXNzIDMgRUNDIDI1NiBiaXQgRVYgQ0EgLSBHMjBZMBMGByqGSM49AgEGCCqGSM49
AwEHA0IABC93+aAYNSQS+F5P39qxy3AhmkNBfnYME9lyISEJCvfrBSSiVc2ySA6v
e6GH2RRknqCtxX85cEyaQgABoxYHiL2jggFXMIIBUzASBgNVHRMBAf8ECDAGAQH/
AgEAMC8GA1UdHwQoMCYwJKAioCCGHmh0dHA6Ly9zLnN5bWNiLmNvbS9wY2EzLWc1
LmNybDAOBgNVHQ8BAf8EBAMCAQYwLgYIKwYBBQUHAQEEIjAgMB4GCCsGAQUFBzAB
hhJodHRwOi8vcy5zeW1jZC5jb20wXwYDVR0gBFgwVjBUBgRVHSAAMEwwIwYIKwYB
BQUHAgEWF2h0dHBzOi8vZC5zeW1jYi5jb20vY3BzMCUGCCsGAQUFBwICMBkaF2h0
dHBzOi8vZC5zeW1jYi5jb20vcnBhMCsGA1UdEQQkMCKkIDAeMRwwGgYDVQQDExNT
WU1DLUVDQy1DQS1wMjU2LTIzMB0GA1UdDgQWBBRycjbGpzGeh4nHMn3sOvWiZD94
ejAfBgNVHSMEGDAWgBR/02Wnwt3su/AwCfNDOfoCrzMxMzANBgkqhkiG9w0BAQsF
AAOCAQEAOiHdrJlwGYxgg+Zh8ePYDYqFuLbuom7+myENWaZ+NIsKAkHheANBJWJA
Ot6t8TKkGp7G+YeDQ/oEZRGwYyIrQgi7gyZqmpcojna6Wp1OxF1KHotIDEAh/LBk
73jOaJglZVeodRO40nhARoHHB0eJlIWoA8DybXAjVRMW0fxmAvFb3pjuKjokQtE9
muqFQfr8proZ8BdhmMv41d5IRATmkUU5jGJzAbph4EuypmgXSIES0IHsMxNxwJjU
ufpCh8h4dkv/pqkWH3sArdavhoK/NURrDkzPa+EwbIDVooWWBbLCBQ8LGbCyOeKp
Gov7Dys9bWC8vFML1cH+QDRfDwymdA==
-----END CERTIFICATE-----
```

### 証明書の有効期限を確認する
```
$ openssl x509 -noout -dates -in  intermediate.crt 
notBefore=May 12 00:00:00 2015 GMT
notAfter=May 11 23:59:59 2025 GMT
```

### 証明書の全内容を取得する
```
$ openssl x509 -text -noout -in intermediate.crt 
Certificate:
    Data:
        Version: 3 (0x2)
        Serial Number:
            71:22:3c:a5:22:18:5e:ac:44:cf:17:70:d1:a8:aa:5d
        Signature Algorithm: sha256WithRSAEncryption
        Issuer: C=US, O=VeriSign, Inc., OU=VeriSign Trust Network, OU=(c) 2006 VeriSign, Inc. - For authorized use only, CN=VeriSign Class 3 Public Primary Certification Authority - G5
        Validity
            Not Before: May 12 00:00:00 2015 GMT
            Not After : May 11 23:59:59 2025 GMT
        Subject: C=US, O=Symantec Corporation, OU=Symantec Trust Network, CN=Symantec Class 3 ECC 256 bit EV CA - G2
        Subject Public Key Info:
            Public Key Algorithm: id-ecPublicKey
            EC Public Key:
                pub: 
                    04:2f:77:f9:a0:18:35:24:12:f8:5e:4f:df:da:b1:
                    cb:70:21:9a:43:41:7e:76:0c:13:d9:72:21:21:09:
                    0a:f7:eb:05:24:a2:55:cd:b2:48:0e:af:7b:a1:87:
                    d9:14:64:9e:a0:ad:c5:7f:39:70:4c:9a:42:00:01:
                    a3:16:07:88:bd
                ASN1 OID: prime256v1
        X509v3 extensions:
            X509v3 Basic Constraints: critical
                CA:TRUE, pathlen:0
            X509v3 CRL Distribution Points: 
                URI:http://s.symcb.com/pca3-g5.crl

            X509v3 Key Usage: critical
                Certificate Sign, CRL Sign
            Authority Information Access: 
                OCSP - URI:http://s.symcd.com

            X509v3 Certificate Policies: 
                Policy: X509v3 Any Policy
                  CPS: https://d.symcb.com/cps
                  User Notice:
                    Explicit Text: https://d.symcb.com/rpa

            X509v3 Subject Alternative Name: 
                DirName:/CN=SYMC-ECC-CA-p256-23
            X509v3 Subject Key Identifier: 
                72:72:36:C6:A7:31:9E:87:89:C7:32:7D:EC:3A:F5:A2:64:3F:78:7A
            X509v3 Authority Key Identifier: 
                keyid:7F:D3:65:A7:C2:DD:EC:BB:F0:30:09:F3:43:39:FA:02:AF:33:31:33

    Signature Algorithm: sha256WithRSAEncryption
        3a:21:dd:ac:99:70:19:8c:60:83:e6:61:f1:e3:d8:0d:8a:85:
        b8:b6:ee:a2:6e:fe:9b:21:0d:59:a6:7e:34:8b:0a:02:41:e1:
        78:03:41:25:62:40:3a:de:ad:f1:32:a4:1a:9e:c6:f9:87:83:
        43:fa:04:65:11:b0:63:22:2b:42:08:bb:83:26:6a:9a:97:28:
        8e:76:ba:5a:9d:4e:c4:5d:4a:1e:8b:48:0c:40:21:fc:b0:64:
        ef:78:ce:68:98:25:65:57:a8:75:13:b8:d2:78:40:46:81:c7:
        07:47:89:94:85:a8:03:c0:f2:6d:70:23:55:13:16:d1:fc:66:
        02:f1:5b:de:98:ee:2a:3a:24:42:d1:3d:9a:ea:85:41:fa:fc:
        a6:ba:19:f0:17:61:98:cb:f8:d5:de:48:44:04:e6:91:45:39:
        8c:62:73:01:ba:61:e0:4b:b2:a6:68:17:48:81:12:d0:81:ec:
        33:13:71:c0:98:d4:b9:fa:42:87:c8:78:76:4b:ff:a6:a9:16:
        1f:7b:00:ad:d6:af:86:82:bf:35:44:6b:0e:4c:cf:6b:e1:30:
        6c:80:d5:a2:85:96:05:b2:c2:05:0f:0b:19:b0:b2:39:e2:a9:
        1a:8b:fb:0f:2b:3d:6d:60:bc:bc:53:0b:d5:c1:fe:40:34:5f:
        0f:0c:a6:74

```

### サーバ証明書と中間証明書の整合性を確認するには
それぞれで同じ値が取得できればOKです。
以下では、中間証明書の主体元とサーバ証明書の発行元が一致しているのかをハッシュを用いて確認しているだけです。
```
$ openssl x509 -subject_hash -noout -in intermediate.crt 
a434c1c2
```

```
$ openssl x509 -issuer_hash -noout -in server.crt
a434c1c2
```


