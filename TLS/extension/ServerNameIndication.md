# 概要
Server Name Indcation(SNI)では、HTTP1.1の名前ベースバーチャルホストをHTTPSに対応されるために利用する仕組みです。
- https://www.iana.org/assignments/tls-extensiontype-values/tls-extensiontype-values.xhtml

次の特徴があります。
- ClientHelloでSNIによるservernameを指定することによって、サーバ側では適切に証明書の出し分けを行います。
  - 1枚のサーバ証明書に複数ホスト名を入れるためにX.509 v3の証明書で導入されたsubjectAltName拡張で、追加のホスト名を指定できる。
- SNIを利用するためにはクライアント及びサーバ側双方が対応している必要があります。

ただし、近年SNIで指定されたホスト名とHTTPのHOSTヘッダで指定されたホスト名は独立しているのでお互い異なるものを指定することが可能であり、これを「Virtual Host Confusion」や「Virtual Server Confusion」と呼びます。たとえば、SNIをsni.co.jpにして、HOSTをorigin.co.jpにすると、レスポンスはorigin.co.jpで返される。

# 詳細

### ブラウザ・サーバ対応状況
なお、SNIが動作するためにはウエブサーバとブラウザ両方の対応が必要となります。
このため、Android 3.0 (Honeycomb)以降の標準ブラウザであれば、SNIに対応しています。しかし、Android2.3のようにSNI非対応のブラウザでは対応しないといった状況が発生します。

- SeeAlso
  - https://ja.wikipedia.org/wiki/Server_Name_Indication

### SNIによる証明書の出し分けが行われていることを確認する

次の例はSNIでservername指定するかどうかによって、証明書が正しく出しわけられているかどうかを確認します。

- servernameが指定されない場合
```
$ openssl s_client -connect help.hipchat.com:443 -showcerts < /dev/null 2>&1 | grep subject
subject=/OU=GT20300774/OU=See www.rapidssl.com/resources/cps (c)15/OU=Domain Control Validated - RapidSSL(R)/CN=*.uservoice.com
```

- servernameが指定される場合(SNIとしてドメインが指定された場合) 
```
$ openssl s_client -connect help.hipchat.com:443 -servername help.hipchat.com -showcerts < /dev/null 2>&1 | grep subject
subject=/C=US/L=San Francisco/ST=California/O=Atlassian, Inc./OU=HipChat/CN=help.hipchat.com
```

### データ構造サンプル
- ClientHello
```
Extension: server_name
    Type: server_name (0x0000)
    Length: 21
    Server Name Indication extension
        Server Name list length: 19
        Server Name Type: host_name (0)
        Server Name length: 16
        Server Name: www.google.co.jp
```

# 詳細仕様
詳細仕様はこちらを参考にしています。
- https://tools.ietf.org/html/rfc6066#section-3

サーバはこの拡張を受け取ってそのserver_nameが識別できない場合には次の２つのうちどちらかのアクションを取るべき(SHOULD)
- unrecognized_name(112)によるfatalアラート。このアラートをwarningレベルのアラートで送付するのはすべきではない(NOT RECOMMENDED)
- ハンドシェイクの継続




ClientHelloではserver_name_listのリスト構造としてクライアントが送付してくる可能性がある。
IPv4やIPv6のアドレスが指定されるのは許可されていません。ホスト名は末尾のドットが付与されないASCIIエンコーディングの文字列とします。

# SeeAlso
- RFC6066:
  - https://tools.ietf.org/html/rfc6066#section-3
- wikipedia: Server Name Indication
  - 各種ソフトウェアの対応状況についてまとめられています
  - https://ja.wikipedia.org/wiki/Server_Name_Indication
- 日本語訳
  - http://www.ipa.go.jp/security/rfc/RFC6066JA.html#03
