# Online Certificate Status Protocol(OCSP)について
OCSPはX509公開鍵証明書の失効状態を取得するための通信プロトコルです。
サーバに接続する際に失効状態を取得する方法としては証明書失効リスト(CRL)、OSCPの２つが存在するが、サーバ証明書の正当性を確認する必要がある。  
CRLはリストが巨大化しダウンロードにも時間がかかる。それに比べてOSCPは非常に軽量で単一レコードのみを取得します。

# 詳細

### OCSPとOCSP Stapling
OCSPとOCSP Staplingの違いについて抑えておきます。

- OCSP
  - OCSP要求をサードパーティのOSCP Responderに対して行う必要があり、レイテンシ増加と失敗する可能性が加わる。
  - 認証局が運用しているOCSP Responderはしばしばレスポンスが得られずに信頼性が低いといった問題点からOSCP Staplingが生まれた
- OCSP Stapling
  - TLSハンドシェイク中にキャッシュされたOCSPレコードをサーバが送信することを可能にします。これによってOCSP Responderをバイパスすることとなる。
  - これによってOCSP Responder間のラウンドトリップ時間を削減することができます。つまり、SSL/TLS通信の開始を早めることが可能とができます。

上記２つについては以下に図があるのでそちらを参照すること
- https://qiita.com/harukasan/items/fe37f3bab8a5ca3f4f92

### OCSP Staplingの情報を確認する
opensslコマンドを利用して簡単にサーバがOCSP Stapling対応しているかどうかを確認することができます。  
OCSP Stapling設定が存在しないサーバの場合には「OCSP response: no response sent」が出力されます。
```
$ openssl s_client -connect www.yahoo.co.jp:443 -status </dev/null
...
OCSP response: no response sent
...
```

OCSP Stapling設定が存在するサーバの場合には「OCSP Response Data:」が出力されます。
```
$ openssl s_client -connect sslanalyzer.comodoca.com:443 -status </dev/null
CONNECTED(00000003)
depth=2 /C=GB/ST=Greater Manchester/L=Salford/O=COMODO CA Limited/CN=COMODO RSA Certification Authority
verify error:num=20:unable to get local issuer certificate
verify return:0
OCSP response: 
======================================
OCSP Response Data:
    OCSP Response Status: successful (0x0)
    Response Type: Basic OCSP Response
    Version: 1 (0x0)
    Responder Id: 39DAFFCA28148AA8741308B9E40EA9D2FA7E9D69
    Produced At: Sep 19 18:39:25 2017 GMT
    Responses:
    Certificate ID:
      Hash Algorithm: sha1
      Issuer Name Hash: F4317077AEF7881259DD9E5D23F2FE267766D046
      Issuer Key Hash: 39DAFFCA28148AA8741308B9E40EA9D2FA7E9D69
      Serial Number: ACB22B496E8A98D905527E005D66AAF5
    Cert Status: good
    This Update: Sep 19 18:39:25 2017 GMT
    Next Update: Sep 26 18:39:25 2017 GMT

    Signature Algorithm: sha256WithRSAEncryption
        81:5d:2f:c8:79:cc:14:fc:86:4e:f0:21:80:be:c2:b2:33:ee:
        48:68:9a:bf:63:ea:78:ce:81:a5:33:2d:fc:de:08:fd:a4:ba:
        ab:c5:a3:d4:47:85:02:6d:a8:41:a6:69:82:a4:3c:c9:9a:c5:
        d7:e3:6a:60:bb:ca:0c:09:d7:c5:51:22:83:c8:85:59:65:aa:
        27:45:b4:a1:f2:d0:2d:ae:1f:4b:86:f5:4c:35:96:bf:28:3c:
        47:bc:c6:28:e7:2a:2c:09:c3:90:fe:e3:41:23:61:d4:e8:2b:
        49:c9:a3:12:c1:1d:46:67:4c:75:af:1b:9e:60:29:d5:ae:41:
        37:53:b9:8b:14:1d:e0:03:8e:5b:4a:db:37:54:13:90:e8:65:
        0b:60:76:a2:9e:1a:4a:9e:91:84:a0:b0:a9:a8:5f:c6:77:01:
        5f:e2:d4:41:4c:1a:1f:9f:42:de:35:17:f6:4f:ac:1a:5c:46:
        ef:bf:a0:e8:d0:51:7d:01:c3:2c:09:32:42:8b:2c:6e:4f:3d:
        83:03:ca:53:52:14:64:4d:27:b3:5b:00:63:12:4c:83:f0:75:
        18:ad:31:00:c8:e9:53:2a:e5:62:59:1d:fb:87:f3:f2:76:a7:
        fa:75:be:1c:52:9c:de:73:18:21:87:3d:be:c4:1e:e1:41:37:
        1b:9c:7d:01
======================================
...
```

### OCSPリクエスト
OCSPリクエストはHTTPベース(POST)で行われる。クライアント側からは次のContent-Typeが付与される。
```
Content-Type: application/ocsp-request
```

Body中のリクエストには次のような情報が入る。
```
CertID ::= SEQUENCE {
    hashAlgorithm            AlgorithmIdentifier,
    issuerNameHash     OCTET STRING, -- Hash of Issuer's DN
    issuerKeyHash      OCTET STRING, -- Hash of Issuers public key
    serialNumber       CertificateSerialNumber }
```

以下にOCSPサンプルリクエストを表示する。
```
Hypertext Transfer Protocol
    POST / HTTP/1.1\r\n
        [Expert Info (Chat/Sequence): POST / HTTP/1.1\r\n]
        Request Method: POST
        Request URI: /
        Request Version: HTTP/1.1
    Host: ocsp.comodoca.com\r\n
    User-Agent: Mozilla/5.0 (Macintosh; Intel Mac OS X 10.10; rv:55.0) Gecko/20100101 Firefox/55.0\r\n
    Accept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8\r\n
    Accept-Language: ja,en-US;q=0.7,en;q=0.3\r\n
    Accept-Encoding: gzip, deflate\r\n
    Content-Length: 83\r\n
    Content-Type: application/ocsp-request\r\n
    Connection: keep-alive\r\n
    \r\n
    [Full request URI: http://ocsp.comodoca.com/]
    [HTTP request 1/1]
    [Response in frame: 4409]
    File Data: 83 bytes
Online Certificate Status Protocol
    tbsRequest
        requestList: 1 item
            Request
                reqCert
                    hashAlgorithm (SHA-1)
                        Algorithm Id: 1.3.14.3.2.26 (SHA-1)
                    issuerNameHash: 7ae13ee8a0c42a2cb428cbe7a605461940e2a1e9
                    issuerKeyHash: 90af6a3a945a0bd890ea125673df43b43a28dae7
                    serialNumber: 0x06133d2a17cf9d28ed58eae3a5107b13
```

- 参考
  - https://www.ietf.org/rfc/rfc2560.txt
    - A.1.1 Requestを参照のこと
    - 4.1.1  Request Syntax

### OCSPレスポンス
次のようなサンプルレスポンスを返します。
```
Hypertext Transfer Protocol
    HTTP/1.1 200 OK\r\n
        [Expert Info (Chat/Sequence): HTTP/1.1 200 OK\r\n]
            [HTTP/1.1 200 OK\r\n]
            [Severity level: Chat]
            [Group: Sequence]
        Request Version: HTTP/1.1
        Status Code: 200
        Response Phrase: OK
    Date: Fri, 22 Sep 2017 08:25:34 GMT\r\n
    Server: Apache\r\n
    Last-Modified: Thu, 21 Sep 2017 02:10:06 GMT\r\n
    Expires: Thu, 28 Sep 2017 02:10:06 GMT\r\n
    ETag: 4A931A0BEA14CC25FD804AD7B3BC9EA50B85E6A4\r\n
    Cache-Control: max-age=495271,public,no-transform,must-revalidate\r\n
    X-OCSP-Reponder-ID: fsedcaocsp5\r\n
    Content-Length: 471\r\n
    Connection: close\r\n
    Content-Type: application/ocsp-response\r\n
    \r\n
    [HTTP response 1/1]
    [Time since request: 0.182933000 seconds]
    [Request in frame: 4330]
    File Data: 471 bytes
Online Certificate Status Protocol
    responseStatus: successful (0)
    responseBytes
        ResponseType Id: 1.3.6.1.5.5.7.48.1.1 (id-pkix-ocsp-basic)
        BasicOCSPResponse
            tbsResponseData
                responderID: byKey (2)
                    byKey: 90af6a3a945a0bd890ea125673df43b43a28dae7
                producedAt: 2017-09-20 18:10:06 (UTC)
                responses: 1 item
                    SingleResponse
            signatureAlgorithm (sha256WithRSAEncryption)
                Algorithm Id: 1.2.840.113549.1.1.11 (sha256WithRSAEncryption)
            Padding: 0
            signature: 1b8b7011003e4c3d18f861f220fead673b729e95fab49302...
```

上記で特筆すべきはレスポンスが「Content-Type: application/ocsp-response」となっていること。レスポンス仕様はRFC2560の「4.2 Response Syntax」を参照のこと

- 参考
  - https://www.ietf.org/rfc/rfc2560.txt
    - 4.2  Response Syntax

### サーバのOCSP Stapling設定方法
- Apache(2.3.3以上)
  - https://tech.nosuz.jp/2015/12/enable-ocsp-stapling/
- Nginx
  - http://blog.mylibs.jp/archives/173

### クライアント側の対応状況など
- From Wikipedia
  - IE, Firefox, Mac OS X(safari), OperaなどはOSCPをサポートしている。GoogleChromeのみは2012年にOCSPチェックをデフォルトで無効にしている。
  - https://ja.wikipedia.org/wiki/Online_Certificate_Status_Protocol
- iOS11よりOCSP Stapling対応
  - https://devstreaming-cdn.apple.com/videos/wwdc/2017/204kty9amomlmk222/204/204_updating_your_app_for_ios_11.pdf

# TODO
- どのタイミングでどのようなリクエスト・レスポンスを受け取っているか?
- CRTとの住み分けはどのようになっているのか?
- キャッシュはどのようになっている?
  - Cache-ControlあたりがOCSPレスポンスに含まれているので
- RFCを確認する

# 参考URL
- RFC2560: X.509 Internet Public Key Infrastructure Online Certificate Status Protocol - OCSP
  - https://tools.ietf.org/html/rfc2560
- RFC6960: X.509 Internet Public Key Infrastructure Online Certificate Status Protocol - OCSP
  - https://tools.ietf.org/html/rfc6960
- RFC6066: Transport Layer Security (TLS) Extensions: Extension Definitions
  - https://tools.ietf.org/html/rfc6066
