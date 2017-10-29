# 概要
opensslのocspサブオプションについて

# 詳細

### OCSPレスポンス
- OCSPレスポンスが存在する場合
```
$ echo Q | openssl s_client -connect rdsig.yahoo.co.jp:443 -status 
CONNECTED(00000003)
depth=1 /C=BE/O=GlobalSign nv-sa/CN=GlobalSign Organization Validation CA - SHA256 - G2
verify error:num=20:unable to get local issuer certificate
verify return:0
OCSP response: 
======================================
OCSP Response Data:
    OCSP Response Status: successful (0x0)
    Response Type: Basic OCSP Response
    Version: 1 (0x0)
    Responder Id: 9C4D0099000E8BB0018175A1BAF0D025D7A01C47
    Produced At: Oct 28 10:51:28 2017 GMT
    Responses:
    Certificate ID:
      Hash Algorithm: sha1
      Issuer Name Hash: 0C9E4D9C3DEDEF84D891E972C7CF8406BC197B07
      Issuer Key Hash: 96DE61F1BD1C1629531CC0CC7D3B830040E61A7C
      Serial Number: 0FC63355EDFC043941B72C71
    Cert Status: good
    This Update: Oct 28 10:51:28 2017 GMT
    Next Update: Nov  1 10:51:28 2017 GMT

    Signature Algorithm: sha256WithRSAEncryption
        2a:0c:92:9f:9d:be:b2:9c:cb:6f:ca:62:b9:51:ad:f4:2e:c1:
        ae:0d:52:a8:ce:7e:da:6a:f0:50:fc:1e:91:7b:44:40:92:91:
        f1:cd:fc:e9:1f:ad:d2:88:c3:23:06:1c:00:d4:7c:d5:25:7e:
        68:bc:7d:d4:38:9a:10:15:11:04:ca:40:de:92:6e:cd:e3:fd:
        15:14:7d:d5:00:3b:15:8f:b8:29:be:b2:c7:7a:eb:ad:45:b7:
        be:90:3d:c2:51:7f:b1:cb:76:0f:3a:a6:39:20:25:d4:33:a6:
        44:3d:9c:48:74:a9:c0:25:e5:ac:59:ac:ee:8a:a8:01:bd:1f:
        fe:60:df:21:7f:f5:93:fa:da:d9:db:c8:16:2c:61:86:06:02:
        21:5e:08:ea:74:c1:eb:d5:a5:55:a8:9f:34:c6:03:b7:43:a0:
        90:8f:52:c6:d5:a3:d8:3a:26:88:a1:7a:69:eb:52:47:91:4c:
        9c:9d:82:91:1d:16:1e:76:a2:0f:07:22:e5:8b:96:38:7d:2a:
        a2:26:96:76:72:bc:61:55:2e:4d:2c:a4:ec:ff:e4:3c:95:0b:
        e5:7e:34:9c:c4:04:86:da:82:1c:c7:b1:3a:20:4f:06:d4:d5:
        3b:95:6a:bb:25:c7:e3:03:a4:51:fb:95:cf:a2:33:85:70:0a:
        d4:e8:fa:28
(snip)
```
