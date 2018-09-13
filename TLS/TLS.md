# 概要
TLS/SSLについてまとめる。 RFCについては以下に定義されています。
- https://ja.wikipedia.org/wiki/Transport_Layer_Security

# 概念

### SSLハンドシェイク

* DNS Lookup
* Initial Connection(TCP SYN/ACK)
  * TCP SYNのリクエストとTCP SYN+ACKの応答レスポンス
* SSL Negotiation
  * Client Hello(クライアント=>サーバ)
  * Server Hello, Certificate(クライアント<=サーバ)
  * Certificate Verify(クライアント=>CRL配布orOCSPレスポンダサーバ)
  * OCSPレスポンダへのリクエスト(クライアント=>CRL配布orOCSPレスポンダサーバ)
  * ChangeCipherSpec(クライアント=>サーバ)
  * ChangeCipherSpec(クライアント<=サーバ)
* Time to First Byte
  * GET /index.html HTTP1.1
* Content Download
  * ウェブページコンテンツの取得
  
* 参考
  * 上記のフェーズに応じた高速化の手法について記述されている
  * https://www.jp.websecurity.symantec.com/welcome/pdf/wp_ssl_speedup.pdf


### SSL接続確立フロー(超概要)

次が準備段階の処理となる
- 1. 秘密鍵と署名要求(CSR)を生成する(サーバ)
- 2. 作成したCSRを送付する(サーバ->認証局)
- 3. 電子署名を付与してCRT(サーバ証明書)を発行する(認証局)
- 4. CRTを返送する(認証局->サーバ)
- 5. CRTを設置する(サーバ)

以下がSSLのフローとなる。
- 1. クライアントがSSLでアクセスする(クライアント->サーバ)
- 2. CRTと公開鍵を返送する(サーバ->クライアント)
- 3. 認証局の公開鍵(プリインストールされている)を使用してサーバ証明書から電子署名を取得する(クライアント->認証局)
- 4. 電子署名により取得した公開鍵が正しくサーバから送られてきたものであることを確認する(クライアント)
- 5. 公開鍵で共通鍵を暗号化する。(クライアント)
- 6. 暗号化された共通鍵を送る(クライアント->サーバ)
- 7. 秘密鍵で暗号化された共通鍵を複合化する。(サーバ)
- 8. 共通鍵を利用して暗号化通信を開始する(クライアント <==>  サーバ)


- https://www.google.co.jp/imgres?imgurl=https%3A%2F%2Fqiita-image-store.s3.amazonaws.com%2F0%2F8726%2F7badc3d2-d1da-8ee3-30da-48470a353d70.png&imgrefurl=http%3A%2F%2Fqiita.com%2Fkuni-nakaji%2Fitems%2F5118b23bf2ea44fed96e&docid=WfOgdWEIsh4rkM&tbnid=RHy36NUg7OLLVM%3A&vet=1&w=860&h=567&safe=off&bih=654&biw=1320&ved=0ahUKEwjg6_zLh8DQAhXIvLwKHbhEDMo4ZBAzCCsoKTAp&iact=mrc&uact=8

### SSL要点
- 対象暗号
- http://blog.shibayu36.org/entry/2015/10/26/120000

### SSL False Start
Google社が開発してChromeブラウザに搭載したHTTPSのウェブページの閲覧スピードを高速化するテクニックの１つである。
False Startは陸上競技における「フライング」にちなんで命名されたもので、
「相手からの応答を待ってから送信すべき暗号化された電文を先に送ってしまう」という仕組みです。

- https://tools.ietf.org/html/draft-bmoeller-tls-falsestart-00

chromeでこの機能を有効にするためには
```
about:config で詳細設定画面を開き
```
http://builder.japan.zdnet.com/off-topic/20393127/

```
security.ssl.enable_false_start
```
を有効にすればよい。

しかし、一部のロードバランサやSSLアクセラレータの製品バージョンによってSSL/TLS接続で問題が発覚しました。  
また、BEASTアタックなどが指摘されたとのことで、Googleは2012年4月にSSL False Startのサポートを終了するとのアナウンスを行いました。

### SSL技術要素の要点について

|方式|解決可能な問題|解決できない問題|
|:---:|:---|:---|
|対象暗号|平文の機密性|鍵配送問題|
|公開鍵暗号|鍵配送問題|アルゴリズム実行速度、正当な受信者の公開鍵であることの保証|
|一方向ハッシュ関数|改竄|なりすまし|
|メッセージ認証コード(MAC)|改竄、なりすまし|第三者に対する証明、否認|
|デジタル署名| 改竄、なりすまし、第三者に対する証明、否認|公開鍵が本物の送信者のものであるかどうかの確認|
|証明書|公開鍵を証明すること|認証局自体の信頼|

- 参考  
-- http://blog.shibayu36.org/entry/2015/10/26/120000

### CRL(Certificate Revocation List)とは
CRL(証明書執行リスト)とは有効期限よりも前に失効させたデジタル証明書の一覧です。  
万が一、証明書の秘密鍵が漏れてしまった場合などにはCRLに登録する必要があります。  
CRLを処理するのはクライアント側のソフトウェアの仕事です。

万が一証明書が漏れてしまった場合には以下の処理が必要となります。
- 1. 秘密鍵を持っていたアリスが盗まれたことを検知して、認証機関にrevocateするように申請する。
- 2. 認証機関はCRLリストに追加する
- 3. ボブはCRLを素早く更新する必要がある。

どれか１つでも遅延すると時間差攻撃で悪意のあるマロリーに攻撃される可能性があります。

このため、リアルタイムで検出するための手法としてOCSP(Online Certificate Status Protocol)というプロトコルが存在します。

DNS偽装やDoS攻撃を防ぐため、CRLには発行者のデジタル署名が付与されている。
CRLでの証明書の失効理由は以下の２つに大別することができる。
* Revoked(失効)
  * CAが不正に証明書を発行したことが判明した場合や秘密鍵を失効したと考えられる場合、証明書は不可逆で失効とされる。
* Hold(停止)
  * 有効な状態に戻すことができる。例えば、ユーザーが秘密鍵を紛失したような場合には一時的に証明書を停止させることができる。無事見つかれば後日復旧させることも可能。この場合、証明書のシリアル番号はCRLから削除されることがあります。

CRLはRFC5280で定義されています
- https://tools.ietf.org/html/rfc5280

* 参考
  * https://ja.wikipedia.org/wiki/%E8%A8%BC%E6%98%8E%E6%9B%B8%E5%A4%B1%E5%8A%B9%E3%83%AA%E3%82%B9%E3%83%88

### OCSP(Online Certificate Status Protocol)
先で説明したCRLの場合、証明書失効リストとしてCRLが利用されていたがだんだんとリストが肥大化し、ダウンロードに時間がかかるようになってきた。  
このため、単一レコード取得で済むOSCPが現在のX.509公開鍵証明書の失効を確認する通信プロトコルとして一般的になってきた。  
OSCPサーバのことをOCSPレスポンダと呼ぶ。OCSPレスポンダは要求の中で指定された証明書について「有効」、「失効」、「不明」のいずれかの応答を署名付きで返すか、要求を処理できない場合はエラーで返す。


以下に特徴を記す。
- 内部的にはクライアントがOSCPの応答をキャッシュすることによって、要求回数の増大によるレスポンス遅延を回避している。

* RFC6960: X.509 Internet Public Key Infrastructure Online Certificate Status Protocol - OCSP
  * https://tools.ietf.org/html/rfc6960
* RFC2560: X.509 Internet Public Key Infrastructure Online Certificate Status Protocol - OCSP
  * https://tools.ietf.org/html/rfc2560


* http://blog.mylibs.jp/archives/173
  * OCSPに関する図が載っていて非常にわかりやすいです。
* http://d.hatena.ne.jp/tkng/20130108/1357610340
  * 説明がわかりやすい

OCSPに関するブラウザでのサポート状況について(参考: https://ja.wikipedia.org/wiki/Online_Certificate_Status_Protocol)
- Firefoxは全バージョンでOSCPチェックをサポートしている。Firefox3では既定でチェックが有効となる。
- Mac OS XはSafariのOSCPチェックをサポートしている
- Google CHromeでは待ち時間やプライバシーの理由で2012年にOSCPチェックをデフォルトで無効にしている。
- IEではWindows Vista上のversion7でOSCPチェックのサポートを開始している

利用フローとプロトコル詳細については以下を確認すること
* 参考資料
  * https://ja.wikipedia.org/wiki/Online_Certificate_Status_Protocol


### OCSP Stapling
OCSPの場合にはリアルタイムでDNSで名前解決したり、サーバ(OCSPレスポンダ)にリクエストを飛ばすといった手順を踏むので遅い。特にサーバが海外だとすごい遅いらしい。  
このような問題があるため、OCSPレスポンダの返答をあらかじめサーバ側がキャッシュし、通信時に証明書と一緒にクライアントに送りつけることで、クライアントではOCSPのチェックを省略できるしくみが存在する。  
OCSP Stapingを有効にするためにはWebサーバ側の対応も必要となります。Apacheだと2.4以降が対応しています。

opensslコマンドで「OCSP Response Data」が存在していればOSCP Staplingが有効となっています。
```
$ openssl s_client -connect www.example.jp:443 -status -servername www.example.jp < /dev/null | head
depth=1 C = US, O = Let's Encrypt, CN = Let's Encrypt Authority X1
verify error:num=20:unable to get local issuer certificate
verify return:0
CONNECTED(00000003)
OCSP response: 
======================================
OCSP Response Data:
    OCSP Response Status: successful (0x0)
    Response Type: Basic OCSP Response
    Version: 1 (0x0)
    Responder Id: C = US, O = Let's Encrypt, CN = Let's Encrypt Authority X1
    Produced At: Dec 23 14:51:00 2015 GMT
    Responses:
DONE
```


### 中間CA証明書(Intermedate Certificate)の仕組みについて

サーバIDは4階層または3階層で証明書を検出する仕組みとなっているようです。
- https://knowledge.symantec.com/jp/support/ssl-certificates-support/index?vproductcat=V_C_S&vdomain=VERISIGN.JP&page=content&id=SO22877&actp=RSS&viewlocale=ja_JP&locale=ja_JP&redirected=true

ここでは３階層として話を進めます。  
SSL/TLS接続の際には下層から順に(3, 2, 1の順で)、最上位のルート証明書までを確認してサーバIDを検証しています。  
ブラウザが正しく証明書を検出できるように、取得したサーバIDと合わせて中間層の証明書もwebサーバにインストールしておく必要があります。
- 1. ルート証明書(ブラウザに標準で搭載されています)
- 2. 中間CA証明書(各製品専用の中間CA証明書をダウンロードして、webサーバにインストールする)
- 3. サーバID

* 参考
  * https://knowledge.symantec.com/jp/support/ssl-certificates-support/index?vproductcat=V_C_S&vdomain=VERISIGN.JP&page=content&id=SO22871&locale=ja_JP&redirected=true
  * https://jp.globalsign.com/support/faq/58.html


### SNI(Server Name Indication)
従来のSSLの仕組みでは1つのサーバに複数のドメイン名をVirtualHostなどで設定できても、SSLサーバ証明書は1枚しか設置できませんでした。  
ここで登場するのがSNIというRFC6066内で登場するSSL/TSLの拡張仕様で、複数枚のSSLサーバ証明書を配置できるようになりました。
- https://tools.ietf.org/html/rfc6066#section-3

注意点としてはクライアントとサーバ側双方で対応できている必要があり、フィーチャーフォンではほとんど利用できないとのことです。
また、Androidでは4.0以降では対応しているらしいですが、3.0未満だと以下の不具合があるようです。
* 参考
  * 標準ブラウザ、ネイティブアプリHTTPクライアント、ネイティブアプリwebviewに分けて詳細な説明やどのように表示されるかなどが確認できます。
  * http://knowledge.sakura.ad.jp/tech/1706/
  
* ブラウザのSNI対応状況などはwikipediaを参考のこと
  * https://ja.wikipedia.org/wiki/Server_Name_Indication


### SAN(異なるFQDNでアクセスしても1枚のSSL証明書で実現する仕組み)
GlobalSingが「マルチドメインオプション」として販売しているものがその代表例です。  

SSLサーバ証明書を発行するためには申請時に作成するCSRの電子証明書のフィールド内にFQDNをCN(Common Name)として指定します。
通常、CNには1つしか設定できません。CNとは別にSAN(Subject Alternative Name)と呼ばれるSSLサーバ証明書の拡張領域があり、このSANにCNと異なるFQDNを追加登録することによって1枚のSSLサーバ証明書で複数のFQDNに対応しています。(SANは複数設定するのでSANsと呼ばれることもある)

- https://www.gmo.jp/news/article/?id=3931

問題点としてはガラケー(フィーチャーフォン)や古いAndroid端末（確かver 2.x）とかだとサポートしていないことがあるらしい。


### TSLネゴシエーションの仕組み(NPNとALPNの違い)
現在ではサーバ側がプロトコルを決定できるALPNの方向に動いているようだ
* TLS-NPN(Next Protocol Negotiation)
  * 使用できるプロトコル(HTTP1, SPDY2, SPDY3など)はクライアントが決定できる
* TLS-ALPN(Application Layer Protocol Negotiation)
  * 使用できるプロトコル(HTTP1, SPDY2, SPDY3など)はサーバが決定できる
  * 使用できるプロトコルがクライアントに存在しない場合にはハンドシェイクアラートで切断される。
  * https://tools.ietf.org/html/rfc7301
  
* 以下のサイトで図付きで説明してくれている
  * http://d.hatena.ne.jp/ASnoKaze/20130207/1360249692


### クロスルート
- https://jp.globalsign.com/support/faq/431.html

#########################################################################

# コマンド編
### ncで443が空いているかを確認する 
```
$ nc -zv login.yahoo.co.jp 443
Connection to login.yahoo.co.jp 443 port [tcp/https] succeeded!
```

### curlでHTTPSにアクセスする
-kは危ない証明書でも通信してくれるオプションです。
危ないとはCNが違う、有効期限が切れている、中間証明書がおかしいなど。
```
$  curl -k -v https://login.yahoo.co.jp/config/login  > /dev/null
* About to connect() to login.yahoo.co.jp port 443 (#0)
*   Trying 182.22.71.247...
  % Total    % Received % Xferd  Average Speed   Time    Time     Time  Current
                                 Dload  Upload   Total   Spent    Left  Speed
  0     0    0     0    0     0      0      0 --:--:-- --:--:-- --:--:--     0* connected
* Connected to login.yahoo.co.jp (182.22.71.247) port 443 (#0)
* Initializing NSS with certpath: sql:/etc/pki/nssdb
* warning: ignoring value of ssl.verifyhost
* skipping SSL peer certificate verification
* SSL connection using TLS_RSA_WITH_AES_128_CBC_SHA
* Server certificate:
* 	subject: CN=login.yahoo.co.jp,O=Yahoo Japan Corporation,L=Minato-Ku,ST=Tokyo,C=JP
* 	start date: Nov 01 03:01:38 2016 GMT
* 	expire date: Nov 02 03:01:38 2017 GMT
* 	common name: login.yahoo.co.jp
* 	issuer: CN=GlobalSign Organization Validation CA - SHA256 - G2,O=GlobalSign nv-sa,C=BE
> GET /config/login HTTP/1.1
> User-Agent: curl/7.24.0 (x86_64-redhat-linux-gnu) libcurl/7.24.0 NSS/3.13.5.0 zlib/1.2.5 libidn/1.24 libssh2/1.4.1
> Host: login.yahoo.co.jp
> Accept: */*
> 
< HTTP/1.1 200 OK
< Date: Sat, 19 Nov 2016 10:12:38 GMT
< P3P: policyref="http://privacy.yahoo.co.jp/w3c/p3p_jp.xml", CP="CAO DSP COR CUR ADM DEV TAI PSA PSD IVAi IVDi CONi TELo OTPi OUR DELi SAMi OTRi UNRi PUBi IND PHY ONL UNI PUR FIN COM NAV INT DEM CNT STA POL HEA PRE GOV"
< X-Content-Type-Options: nosniff
< X-XSS-Protection: 1; mode=block
< Expires: Thu, 01 Jan 1970 00:00:00 GMT
< Cache-Control: private
< Pragma: no-cache
< Vary: Accept-Encoding
< Content-Type: text/html; charset=UTF-8
< Age: 0
< Transfer-Encoding: chunked
< Connection: close
< Server: ATS
< 
{ [data not shown]
100 16203    0 16203    0     0  51336      0 --:--:-- --:--:-- --:--:-- 55489
* Closing connection #0
```

### opensslコマンドを使ってHTTPSにアクセスする
s_clientは標準入力を受け取ろうとするので、そのまま表示するように < /dev/null としています。
opensslのオプションは次の通りです。
```
s_client 	SSL/TLSクライアントとして動作する
-showcerts 	全てのSSL証明書を表示する
-connect 	ドメインとポート番号を指定
```

以下にサンプルを示します。
```
$ openssl s_client -connect login.yahoo.co.jp:443 -showcerts < /dev/null 2>&1
CONNECTED(00000003)
depth=2 OU = GlobalSign Root CA - R3, O = GlobalSign, CN = GlobalSign
verify return:1
depth=1 C = BE, O = GlobalSign nv-sa, CN = GlobalSign Organization Validation CA - SHA256 - G2
verify return:1
depth=0 C = JP, ST = Tokyo, L = Minato-Ku, O = Yahoo Japan Corporation, CN = login.yahoo.co.jp
verify return:1
---
Certificate chain
 0 s:/C=JP/ST=Tokyo/L=Minato-Ku/O=Yahoo Japan Corporation/CN=login.yahoo.co.jp
   i:/C=BE/O=GlobalSign nv-sa/CN=GlobalSign Organization Validation CA - SHA256 - G2
-----BEGIN CERTIFICATE-----
MIIFPzCCBCegAwIBAgIMbxNJbrjFSThTVxEJMA0GCSqGSIb3DQEBCwUAMGYxCzAJ
BgNVBAYTAkJFMRkwFwYDVQQKExBHbG9iYWxTaWduIG52LXNhMTwwOgYDVQQDEzNH
bG9iYWxTaWduIE9yZ2FuaXphdGlvbiBWYWxpZGF0aW9uIENBIC0gU0hBMjU2IC0g
RzIwHhcNMTYxMTAxMDMwMTM4WhcNMTcxMTAyMDMwMTM4WjBvMQswCQYDVQQGEwJK
UDEOMAwGA1UECBMFVG9reW8xEjAQBgNVBAcTCU1pbmF0by1LdTEgMB4GA1UEChMX
WWFob28gSmFwYW4gQ29ycG9yYXRpb24xGjAYBgNVBAMTEWxvZ2luLnlhaG9vLmNv
LmpwMIIBIjANBgkqhkiG9w0BAQEFAAOCAQ8AMIIBCgKCAQEAvuM6T7HBYFc+6syU
sSpdbL+NjQr7K9g2w/SbykI0QloZBA4wImNf9wXwqsYWvNbAzKw/kqCwhtApB2Zi
ldBT/HjT17Q0jG4akNWNpRnsC0xqmWTAGuQdmyzpbt/FmvKYVnXtjk/iNlrsq0zG
7mF3YD+HbWs28S+4mp3Ett7I2tVr6ISgQSk/Hn+L5vcireIdG1AUEkwZUxsKs9Yr
BOX7iuFnSRfKxup6uoXp6gLNDmr2H7s5LGb5SA0fdbTvO7InSkUtz+IdMMUvZr8s
9QzF1MmtnjZqoSC/8DiymSSOsy1eOhI4h9SmYhPNtAsynYpCUIQb8JE1sDEBWZ4U
uhXTSQIDAQABo4IB4jCCAd4wDgYDVR0PAQH/BAQDAgWgMIGgBggrBgEFBQcBAQSB
kzCBkDBNBggrBgEFBQcwAoZBaHR0cDovL3NlY3VyZS5nbG9iYWxzaWduLmNvbS9j
YWNlcnQvZ3Nvcmdhbml6YXRpb252YWxzaGEyZzJyMS5jcnQwPwYIKwYBBQUHMAGG
M2h0dHA6Ly9vY3NwMi5nbG9iYWxzaWduLmNvbS9nc29yZ2FuaXphdGlvbnZhbHNo
YTJnMjBWBgNVHSAETzBNMEEGCSsGAQQBoDIBFDA0MDIGCCsGAQUFBwIBFiZodHRw
czovL3d3dy5nbG9iYWxzaWduLmNvbS9yZXBvc2l0b3J5LzAIBgZngQwBAgIwCQYD
VR0TBAIwADBJBgNVHR8EQjBAMD6gPKA6hjhodHRwOi8vY3JsLmdsb2JhbHNpZ24u
XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
HQYDVR0OBBYEFBDuxG+yJ/ubSG8FnXv3Ar7LMJ+cMB8GA1UdIwQYMBaAFJbeYfG9
HBYpUxzAzH07gwBA5hp8MA0GCSqGSIb3DQEBCwUAA4IBAQBhqDrSjLanhX2whHLo
V/baA0E98rQTYpFqlcuHowk6Qfse+Gux1DufaKHw6HG7rLztHFLignlSk0F03pGa
V0sTIUFLL4BGSpTTbgFOiSTF0lATeZEro5AYQ4ny+1IXT8alhlDnitAUltA3ujS1
4mPovDhlZ2ODrhu0N8fAoSqAJkwt4nW1y8AHiaIyzCSuw2NY00ceDtm+uYMg0IOR
n6no3GHK3aBFQnTl4YagVfhFQKTk1ZFYeXXTWayPY5gISO0IKSv/Ij8Edk+Q0+dC
XV1n6imTBXZZ2XeKGyzzcX+01JxSihscvLTMWGQZJg2vrNKRVzYLauH46uiSvaBv
drHs
-----END CERTIFICATE-----
 1 s:/C=BE/O=GlobalSign nv-sa/CN=GlobalSign Organization Validation CA - SHA256 - G2
   i:/OU=GlobalSign Root CA - R3/O=GlobalSign/CN=GlobalSign
-----BEGIN CERTIFICATE-----
MIIEYjCCA0qgAwIBAgILBAAAAAABMYnGRMkwDQYJKoZIhvcNAQELBQAwTDEgMB4G
XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
MTAwMDAwWjBmMQswCQYDVQQGEwJCRTEZMBcGA1UEChMQR2xvYmFsU2lnbiBudi1z
YTE8MDoGA1UEAxMzR2xvYmFsU2lnbiBPcmdhbml6YXRpb24gVmFsaWRhdGlvbiBD
QSAtIFNIQTI1NiAtIEcyMIIBIjANBgkqhkiG9w0BAQEFAAOCAQ8AMIIBCgKCAQEA
xw5sPyOTf8xwpZ0gww5TP37ATsKYScpH1SPvAzSFdMijAi5GXAt9yYidT4vw+Jxs
jFU127/ys+r741bnSkbZEyLKNtWbwajjlkOT8gy85vnm6JnIY0h4f1c2aRoZHVrR
1H3CnNR/4YASrnrqiOpX2MoKCjoSSaJiGXoNJPc367RzknsFI5sStc7rKd+kFAK5
AaXUppxDZIje+H7+4/Ue5f7co6jkZjHZTCXpGLmJWQmu6Z0cbTcPSh41ICjir9Qh
iwHERa1uK2OrkmthCk0g7XO6fM7+FrXbn4Dw1ots2Qh5Sk94ZdqSvL41+bPE+SeA
Tv+WUuYCIOEHc+ldK72y8QIDAQABo4IBKTCCASUwDgYDVR0PAQH/BAQDAgEGMBIG
A1UdEwEB/wQIMAYBAf8CAQAwHQYDVR0OBBYEFJbeYfG9HBYpUxzAzH07gwBA5hp8
MEcGA1UdIARAMD4wPAYEVR0gADA0MDIGCCsGAQUFBwIBFiZodHRwczovL3d3dy5n
bG9iYWxzaWduLmNvbS9yZXBvc2l0b3J5LzA2BgNVHR8ELzAtMCugKaAnhiVodHRw
Oi8vY3JsLmdsb2JhbHNpZ24ubmV0L3Jvb3QtcjMuY3JsMD4GCCsGAQUFBwEBBDIw
MDAuBggrBgEFBQcwAYYiaHR0cDovL29jc3AyLmdsb2JhbHNpZ24uY29tL3Jvb3Ry
MzAfBgNVHSMEGDAWgBSP8Et/qC5FJK5NUPpjmove4t0bvDANBgkqhkiG9w0BAQsF
AAOCAQEAugYpwLQZjCERwJQRnrs91NVDQPafuyULI2i1Gvf6VGTMKxP5IfBEreHo
FVjb7v3bok3MGI8Nmm3DawGhMfCNvABAzDlfh2FRbfSV6uoVNT5AhcBi1aE0/niq
qLJaOfM3Qfuc6D5xSlvr+GlYoeDGk3fpumeS62VYkHBzQn2v9CMmeReq+qS7meVE
b2WB58rrVcj0ticRIXSUvGu3dGIpxM2uR/LmQlt4hgVhy5CqeYnfBH6xJnBLjUAf
hHvA+wfmyLdOkfQ1A+3o60EQF0m0YsinLPLhTI8DLPMWN11n8aQ5eUmjwF3MVfkh
gA/7zuIpalhQ6abX6xwyNrVip8H65g==
-----END CERTIFICATE-----
---
Server certificate
subject=/C=JP/ST=Tokyo/L=Minato-Ku/O=Yahoo Japan Corporation/CN=login.yahoo.co.jp
issuer=/C=BE/O=GlobalSign nv-sa/CN=GlobalSign Organization Validation CA - SHA256 - G2
---
No client certificate CA names sent
---
SSL handshake has read 2824 bytes and written 438 bytes
---
New, TLSv1/SSLv3, Cipher is AES128-SHA
Server public key is 2048 bit
Secure Renegotiation IS supported
Compression: NONE
Expansion: NONE
SSL-Session:
    Protocol  : TLSv1
    Cipher    : AES128-SHA
    Session-ID: 708DA9776D8BBA29F7564A582CF3945DD2F2936A168XXXXXXXXXXXXXXXXXXXX
    Session-ID-ctx: 
    Master-Key: 1A9AC5DFE1AF2C25EDF355CB955B1D73738356CD1523DC912A2716E644B7BF8CD3C09378E84BC3D54FD6A468490XXXXX
    Key-Arg   : None
    Krb5 Principal: None
    PSK identity: None
    PSK identity hint: None
    TLS session ticket lifetime hint: 7200 (seconds)
    TLS session ticket:
    0000 - 38 b9 7c 99 bd e3 85 79-22 91 30 be f9 de d4 a7   8.|....y".0.....
    0010 - cb 55 cd d7 c7 c4 96 32-0e d1 4c 66 57 95 74 97   .U.....2..LfW.t.
    0020 - a3 9a 0b c7 2d b0 df 74-38 a3 ac 4e 1e 07 0d dd   ....-..t8..N....
    0030 - b5 55 52 be ff da c5 e9-ae b8 5a 96 2d f1 c6 79   .UR.......Z.-..y
    0040 - 9d 7b 5e b9 7b c8 49 a5-df 2f ec 9f 34 3a 44 3c   .{^.{.I../..4:D<
    0050 - cc 6d c8 d2 48 0a 77 63-7e bd 98 b8 29 26 24 fa   .m..H.wc~...)&$.
    0060 - a5 46 6f 8a ae c2 26 91-02 a5 a2 0f 80 ad 08 f7   .Fo...&.........
    0070 - f9 80 94 a6 1e 5a 89 b7-41 03 45 7c 2d 4c 98 b0   .....Z..A.E|-L..
    0080 - 13 f2 3a c1 c9 6f 0e c6-76 17 76 37 94 94 7d 96   ..:..o..v.v7..}.
    0090 - 44 fe af f1 a3 b1 4b 30-fd 51 87 6b a2 cd 56 xx   XXXXXXXXXXXXXXXX
    00a0 - a3 2e 21 08 cb 60 43 8a-f6 90 51 b3 62 58 80 56   XXXXXXXXXXXXXXXX
    00b0 - 66 eb fc dc de 1e 03 24-b7 6d 89 7b 62 08 3e 98   XXXXXXXXXXXXXXXX

    Start Time: 1478972838
    Timeout   : 300 (sec)
    Verify return code: 0 (ok)
---
DONE
```

### nmapで利用できるcipyersを表示する。
実際に試したわけではないが、ポートスキャンするので利用には十分注意すること
```
$ nmap --script ssl-enum-ciphers -p 443 example.com
Starting Nmap 6.47 ( http://nmap.org ) at 2016-11-07 16:50 JST
Nmap scan report for example.com (192.168.1.1)
Host is up (0.017s latency).
PORT    STATE SERVICE
443/tcp open  https
| ssl-enum-ciphers:
|   SSLv3: No supported ciphers found
|   TLSv1.0:
|     ciphers:
|       TLS_ECDHE_RSA_WITH_3DES_EDE_CBC_SHA - strong
|       TLS_ECDHE_RSA_WITH_AES_128_CBC_SHA - strong
|       TLS_ECDHE_RSA_WITH_AES_256_CBC_SHA - strong
|       TLS_RSA_WITH_3DES_EDE_CBC_SHA - strong
|       TLS_RSA_WITH_AES_128_CBC_SHA - strong
|       TLS_RSA_WITH_AES_256_CBC_SHA - strong
|       TLS_RSA_WITH_CAMELLIA_128_CBC_SHA - strong
|       TLS_RSA_WITH_CAMELLIA_256_CBC_SHA - strong
|       TLS_RSA_WITH_SEED_CBC_SHA - strong
|     compressors:
|       NULL
|   TLSv1.1:
|     ciphers:
|       TLS_ECDHE_RSA_WITH_3DES_EDE_CBC_SHA - strong
|       TLS_ECDHE_RSA_WITH_AES_128_CBC_SHA - strong
|       TLS_ECDHE_RSA_WITH_AES_256_CBC_SHA - strong
|       TLS_RSA_WITH_3DES_EDE_CBC_SHA - strong
|       TLS_RSA_WITH_AES_128_CBC_SHA - strong
|       TLS_RSA_WITH_AES_256_CBC_SHA - strong
|       TLS_RSA_WITH_CAMELLIA_128_CBC_SHA - strong
|       TLS_RSA_WITH_CAMELLIA_256_CBC_SHA - strong
|       TLS_RSA_WITH_SEED_CBC_SHA - strong
|     compressors:
|       NULL
|   TLSv1.2:
...
```

# スライド参考資料
* SSL/TLSの基礎と最新動向
  * わかりやすく説明している。実演などを兼ねた後半はまだよくわかっていない
  * http://www.slideshare.net/shigeki_ohtsu/security-camp2015-tls

# SSLの強度テストなどを実行したい場合
* QUALYS SSL LABS
  * https://www.ssllabs.com/ssltest/
* 上記はGlobalSign提供のものもある
  * https://globalsign.ssllabs.com/

# PKCS（Public-Key Cryptography Standards）とは
RSAセキュリティにより考案された公開鍵暗号標準のグループのこと
こう鍵暗号に

* 参考
  * http://qiita.com/kunichiko/items/7796ecfb88a62ce26b36

# 参考リンク
* SSL超概要
  * http://www.cpi.ad.jp/column/column08/
* SSL全体像の図が記載されている
  * http://www.ibm.com/developerworks/jp/websphere/library/web/web_security/2.html
* HSTS
  * https://ja.wikipedia.org/wiki/HTTP_Strict_Transport_Security
* 情報処理推進機構
  * 一度目を通しておいたほうがよさそう
  * http://www.ipa.go.jp/security/pki/
* 英語だけど目を通しておいたほうがよさそう
  * https://wiki.mozilla.org/Security/Server_Side_TLS
* SSL/TLS暗号設定ガイドライン
  * http://www.ipa.go.jp/security/vuln/ssl_crypt_config.html
  * https://www.ipa.go.jp/files/000045645.pdf
* https://www.jp.websecurity.symantec.com/welcome/pdf/wp_ssl_speedup.pdf
* https://www.jp.websecurity.symantec.com/welcome/pdf/wp_sslandroot-certificate.pdf


# RFC
- RFC768: Deprecating Secure Sockets Layer Version 3.0
  - https://tools.ietf.org/html/rfc7568
