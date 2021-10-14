# 概要
CRLについてのメモ


# 詳細

### CRLの中身を確認する方法
以下でサンプルのCRLを取得する
```
$ curl http://crl.identrust.com/DSTROOTCAX3CRL.crl
```

opensslのcrlオプションで確認することができます。
```
$ openssl crl -in DSTROOTCAX3CRL.crl -inform DER -noout -text
Certificate Revocation List (CRL):
        Version 2 (0x1)
    Signature Algorithm: sha256WithRSAEncryption
        Issuer: /O=Digital Signature Trust Co./CN=DST Root CA X3
        Last Update: Oct 13 21:20:42 2021 GMT
        Next Update: Nov 12 21:20:42 2021 GMT
        CRL extensions:
            X509v3 Authority Key Identifier: 
                keyid:C4:A7:B1:A4:7B:2C:71:FA:DB:E1:4B:90:75:FF:C4:15:60:85:89:10

            X509v3 CRL Number: 
                233
Revoked Certificates:
    Serial Number: 0A014142000001415C7FF11500000002
        Revocation Date: Sep 16 16:49:21 2015 GMT
        CRL entry extensions:
            X509v3 CRL Reason Code: 
                Cessation Of Operation
    Serial Number: 0A01414200000148ADA40EF900000002
        Revocation Date: Nov 13 17:20:16 2019 GMT
        CRL entry extensions:
            X509v3 CRL Reason Code: 
                Superseded
    Serial Number: 165DD295B3518FFBB967895D8F23228A
        Revocation Date: Aug 28 21:27:49 2020 GMT
        CRL entry extensions:
            X509v3 CRL Reason Code: 
                Cessation Of Operation
    Serial Number: 723D92B8809A2A457B3451014010F726
        Revocation Date: Jun 28 19:40:00 2016 GMT
        CRL entry extensions:
            X509v3 CRL Reason Code: 
                Cessation Of Operation
    Serial Number: 6789BDF9DFDA422E210D52F3F0405C22
        Revocation Date: Aug 28 21:27:18 2020 GMT
        CRL entry extensions:
            X509v3 CRL Reason Code: 
                Cessation Of Operation
    Serial Number: 0A0141420000012BD040B46700000002
        Revocation Date: Sep 16 16:48:47 2015 GMT
        CRL entry extensions:
            X509v3 CRL Reason Code: 
                Cessation Of Operation
    Serial Number: 905048FAAB12F0C4D87CFCC47DFD2E8C
        Revocation Date: Oct 19 22:44:16 2015 GMT
        CRL entry extensions:
            X509v3 CRL Reason Code: 
                Superseded
    Serial Number: FB798B9AECE1D20840FC19764F7F2127
        Revocation Date: Sep 30 15:58:39 2016 GMT
        CRL entry extensions:
            X509v3 CRL Reason Code: 
                Superseded
    Serial Number: 400174E0927439B8ED0BAE830EE07F48
        Revocation Date: Oct  7 19:24:52 2020 GMT
        CRL entry extensions:
            X509v3 CRL Reason Code: 
                Superseded
    Serial Number: 400174E092652FC60BA981DF7F4D9298
        Revocation Date: Oct  7 19:24:33 2020 GMT
        CRL entry extensions:
            X509v3 CRL Reason Code: 
                Superseded
    Serial Number: 0A01414100000138E4381D6C00000002
        Revocation Date: Jun 28 18:34:53 2017 GMT
        CRL entry extensions:
            X509v3 CRL Reason Code: 
                Cessation Of Operation
    Serial Number: 0A01414100000138ED74F63900000002
        Revocation Date: Jun  7 17:11:40 2017 GMT
        CRL entry extensions:
            X509v3 CRL Reason Code: 
                Cessation Of Operation
    Serial Number: D50036F55837BC6A008480F6BBC93F34
        Revocation Date: Jun  7 17:10:38 2017 GMT
        CRL entry extensions:
            X509v3 CRL Reason Code: 
                Cessation Of Operation
    Serial Number: 9894F9BA5687651CE311517FC18CF720
        Revocation Date: Oct 19 22:43:36 2015 GMT
        CRL entry extensions:
            X509v3 CRL Reason Code: 
                Superseded
    Serial Number: 0A01414200000148C76FF42100000002
        Revocation Date: Nov 13 17:19:34 2019 GMT
        CRL entry extensions:
            X509v3 CRL Reason Code: 
                Superseded
    Signature Algorithm: sha256WithRSAEncryption
         b6:3c:f7:81:1b:be:6d:78:9c:37:6d:12:6c:a5:42:85:f5:f9:
         1b:0d:df:15:1b:fa:d4:25:44:a9:55:0c:39:fd:1d:ba:72:c6:
         05:de:59:75:d2:fe:63:19:94:5e:2e:54:e6:4a:2d:11:97:98:
         1a:43:a4:3d:e6:b9:2e:15:f8:f1:b0:d5:c3:d6:e0:5f:a3:f3:
         c7:cb:4f:c5:7b:d2:19:ac:3b:5b:95:a3:5a:37:0a:2d:4b:ac:
         ca:64:9f:7b:c7:28:79:88:37:de:d7:1f:61:fa:35:89:ab:1a:
         4e:38:8e:0d:f0:67:88:6c:ae:34:2b:45:8f:25:85:4b:a3:1f:
         bb:e1:ba:f1:66:1e:68:9d:09:c0:56:f3:30:38:dd:f8:95:56:
         4e:b4:2c:c8:5f:7e:67:f1:d9:a3:5a:2f:6d:d8:c1:8f:21:90:
         21:a4:c6:a5:35:5b:31:c0:95:f3:ae:af:fa:fb:ce:0c:7e:15:
         5c:b5:cd:a2:d1:8e:c5:e6:01:8c:98:1b:d8:27:57:29:36:e6:
         f9:17:b0:b4:b7:4e:33:ec:32:bb:9a:13:8f:2f:6c:83:91:50:
         4b:a4:bf:cd:d9:48:38:95:3a:32:35:74:77:02:11:11:0f:86:
         e6:a7:57:23:bf:21:59:fc:1a:0a:f6:cb:d9:71:2f:18:2e:86:
         82:f2:bb:ed
```
