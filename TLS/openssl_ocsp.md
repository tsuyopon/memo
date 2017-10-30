# 概要
opensslのocspサブオプションについて

OCSPクライアント用オプションとOCSPサーバ用オプションに分かれています。
- https://wiki.openssl.org/index.php/Manual:Ocsp(1)

Create3TierWithOCSP.mdにはサーバ証明書及びOCSPレスポンダの情報の追加方法及びそれらの確認方法についても載せています。

# 詳細

### OCSPレスポンスが問題ないかどうかを確認する
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
- OCSPレスポンスが存在しない場合
```
$ openssl s_client -connect hoge.com:443 -tls1 -status 
(snip)
OCSP response: no response sent
```

### OCSPサーバを起動する
次のようなコマンドでOCSPサーバを起動する事ができます。
```
$ sudo openssl ocsp -index index.txt -CA ca.crt -rsigner ca.crt -rkey ca.key -port 80
Enter pass phrase for ca.key:
Waiting for OCSP client connections...
```

### OCSPリクエストを発行する
以下のような感じで発行します。
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

ポート番号を含む場合(例えば、8080と仮定)にはurlとHostヘッダの双方に含めないとならない
```
$ sudo openssl ocsp -issuer ../ca/ca.crt -cert server.crt -url http://ocsptest.co.jp:8080/ -resp_text -respout resp.der -CAfile ../ca/ca.crt -header 'host' 'ocsptest.co.jp:8080'
```

次のようにすればリクエストとレスポンスを両方共ファイルに記述します。
```
$ sudo openssl ocsp -index demoCA/index.txt -port 8888 -rsigner rcert.pem -CA demoCA/cacert.pem -text -out log.txt
```

### OCSPサーバに問い合わせるリクエスト内容を確認する

OCSPへのリクエストをreq.derとして作成してみます。req.derの情報は指定された証明書情報を元に生成されています。
```
$ openssl ocsp -issuer issuer.pem -cert c1.pem -cert c2.pem -reqout req.der
```

上記で作成したreq.derの内容を可視化して表示します。
```
$ openssl ocsp -reqin req.der -text
OCSP Request Data:
    Version: 1 (0x0)
    Requestor List:
        Certificate ID:
          Hash Algorithm: sha1
          Issuer Name Hash: 900F39DA84A7D73294F8BD08896A41C3DF3E2D80
          Issuer Key Hash: 69B459343542C17D459E4AB3F69B4EAF606FDBE9
          Serial Number: 11510764318465352677
    Request Extensions:
        OCSP Nonce: 
            04101987EA5DB36F0A7EDC62C0DA0CE8D091
```

サーバ証明書のシリアル番号を確認して、問い合わせを行います。
```
$ openssl x509 -in server.crt -text | grep -i serial
        Serial Number: 11510764318465352677 (0x9fbe7329375e63e5)
$ openssl ocsp -issuer server.crt -nonce -CAfile server.crt -url http://localhost:8081 -serial 115107643184653526 
```

### OCSPサーバに問い合わせたレスポンス内容を確認する
続いて、OCSPにリクエストを出してみてresp.derとして保存してみましょう
```
$ openssl ocsp -issuer issuer.pem -cert c1.pem -cert c2.pem -url http://ocsp.myhost.com/ -resp_text -respout resp.der
```

OCSPからのレスポンスをテキスト形式でわかりやすく表示します
```
$ openssl ocsp -respin resp.der -text
OCSP Response Data:
    OCSP Response Status: successful (0x0)
    Response Type: Basic OCSP Response
    Version: 1 (0x0)
    Responder Id: C = JP, ST = SecondProvince, L = SecondCity, O = SecondCompany, OU = SecondDept, CN = second.co.jp
    Produced At: Oct 30 13:56:08 2017 GMT
    Responses:
    Certificate ID:
      Hash Algorithm: sha1
      Issuer Name Hash: 900F39DA84A7D73294F8BD08896A41C3DF3E2D80
      Issuer Key Hash: 69B459343542C17D459E4AB3F69B4EAF606FDBE9
      Serial Number: 11510764318465352677
    Cert Status: good
    This Update: Oct 30 13:56:08 2017 GMT

    Response Extensions:
        OCSP Nonce: 
            04108B256853D64D9828C3512267790E354D
    Signature Algorithm: sha256WithRSAEncryption
         87:71:22:10:23:0c:bc:ba:4c:12:be:76:ca:20:cb:3b:90:68:
         6f:c1:70:9e:ed:dd:30:53:57:38:aa:4f:cc:1e:26:d7:1e:d9:
(snip)
-----END CERTIFICATE-----
Response verify OK
```




