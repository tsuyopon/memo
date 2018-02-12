# Overview
SNIでは、HTTP1.1の名前ベースバーチャルホストをHTTPSに対応されるために利用する仕組みです。
次の特徴があります。
- ClientHelloでSNIによるservernameを指定することによって、サーバ側では適切に証明書の出し分けを行います。
  - 1枚のサーバ証明書に複数ホスト名を入れるためにX.509 v3の証明書で導入されたsubjectAltName拡張で、追加のホスト名を指定できる。
- SNIを利用するためにはクライアント及びサーバ側双方が対応している必要があります。

# Detail

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

# SeeAlso
- RFC6066:
  - https://tools.ietf.org/html/rfc6066#section-3
- wikipedia: Server Name Indication
  - 各種ソフトウェアの対応状況についてまとめられています
  - https://ja.wikipedia.org/wiki/Server_Name_Indication
