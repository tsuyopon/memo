TODO: TBDを記述する。RFCをもう一回ちゃんと読む

# Transport Layer Security (TLS) and Datagram Transport Layer Security (DTLS) Heartbeat Extension
2012年リリースのOpenSSL1.0.1よりHeartbeat拡張機能がサポートされています。  
この拡張機能は多くのプロトコルやアプリケーションで自身が正常に稼動していることを相手先に伝えるために利用されます。  
具体的には接続されている機器同士でセッションの維持のためのデータのやり取りを行います。  

2014年4月7日にOpenSSLのHeartbeat拡張を利用した場合の脆弱性(CVE-2014-0160)であるHeartbeatが発表されました(詳細はTLS/attach/Heartbleed.mdを参照のこと)
この脆弱性を悪用された場合、秘密鍵、Cookie など、メモリに格納されている重要なデータを読み出されてしまう可能性があります。
次のバージョンについては脆弱性が存在しますので、これ以降のバージョンでは脆弱性が回避された版となっています(Heartbeat自体が無効となっているわけではない)。
```
OpenSSL 1.0.1から1.0.1f
OpenSSL 1.0.2-beta から 1.0.2-beta1
```

# 詳細

## 解決したい課題
プロトコルやアプリケーションで自身が正常に稼動していることを相手先に伝えたい。
これによって、接続されている機器間でセッション維持を行いたい。

HeartbeatはTLS(TCP)とDTLS(UDP)で規定されていて、通常のTCPではその仕組みを使ってkeep-aliveすることができるが、UDPの場合にはその仕組みを利用できないのでUDPで利用される方が多いとのこと


## 解決方法
HeartbeatRequestメッセージを送付して接続先に届き、接続先が稼動しているかどうかのチェックを行うようにする。
TLS/TCPではこの処理はTCP Keep-Alive機能でも可能とする。


## 詳細

### ClientHello, ServerHelloに指定するTLS拡張の値
お互いで次のような情報をHelloメッセージ中のTLS拡張に入れます。
```
enum {
   peer_allowed_to_send(1),
   peer_not_allowed_to_send(2),
   (255)
} HeartbeatMode;

struct {
   HeartbeatMode mode;
} HeartbeatExtension;
```

HeartbeatRequest は接続相手がpeer_not_allowed_to_sendを示しているのであれば送付してはならない(MUST NOT)。
もし、peer_not_allowed_to_sendを示しているエンドポイントがHeartbeatRequestを受け取った場合には、エンドポイントは何もせずにそのメッセージをドロップすべき(SHOULD)で、unexpected_messageを送付するかもしれません。

### Heartbeatメッセージ
Heartbeatはレコードレイヤ上の直下のTLS Content-Type(Alert, ApplicationData, Handshake, CCSなど)上で動作します。
次の２つのheartbeat_requestとheartbeat_responseがあります。
```
enum {
   heartbeat_request(1),
   heartbeat_response(2),
   (255)
} HeartbeatMessageType;
```

HeartbeatRequestメッセージを受け取ったら、HeartbeatResponseを応答すべき(SHOULD)。
HeartbeatMessageは次の構造体で表されます。このメッセージ全体は2^14を超過してはなりません(MUST NOT)
```
struct {
   HeartbeatMessageType type;
   uint16 payload_length;
   opaque payload[HeartbeatMessage.payload_length];
   opaque padding[padding_length];
} HeartbeatMessage;
```

- type: heartbeat_requestかheartbeat_responseのいずれかが入ります。
- payload_length: ペイロードの長さ
- payload: 
- padding: 受け取り側によって無視されるべきランダムなパディングが入ります。

HeartbeatMessageの送信側は少なくとも16byteのランダムパティングをしなければなりません。受け取ったpaddingは無視されなければなりません。
もし、payload_lengthがあまりに長いものであったら、受け取ったHeartbeatMessageは何もせずにそのまま捨てられなければなりません。



## IANA規定項目
TLS Content-Typeにて24番としてIANAに規定されています。
- https://www.iana.org/assignments/tls-parameters/tls-parameters.xhtml#tls-parameters-5

拡張番号15番としてIANAに規定されています
- https://www.iana.org/assignments/tls-extensiontype-values/tls-extensiontype-values.xhtml#tls-extensiontype-values-1

TLS Heartbeat Message TypesとTLS Heartbeat ModesがIANAに規定されています。
- https://www.iana.org/assignments/tls-parameters/tls-parameters.xhtml#heartbeat-message-types

## サーバ側(Openssl)でHeartbeatを無効にする
openssl-1.0.1g以降ではHeartbleedの脆弱性対応されていて、デフォルトでHeartbleedが有効となります。
もし、デフォルトで無効としておきたい場合には、コンパイル時に次のオプションの指定が必要となります。
```
-DOPENSSL_NO_HEARTBEATS
```

## opensslによるheartbeat確認方法
- HeartBeat未対応のサーバの場合
```
$ openssl s_client -connect xxx.co.jp:443 
(snip)
B               // "B"を入力してエンターを押下
HEARTBEATING
140188478379936:error:1413B16D:SSL routines:tls1_heartbeat:peer does not accept heartbeats:t1_lib.c:4039:
```

- HeartBeat対応のサーバの場合
```
$ openssl s_client -connect xxx.co.jp:443 
(snip)
B               // "B"を入力してエンターを押下
HEARTBEATING
read R BLOCK
```

# 参考URL
- Transport Layer Security (TLS) and Datagram Transport Layer Security (DTLS) Heartbeat Extension
  - https://tools.ietf.org/html/rfc6520
- Why does TLS need an explicit heartbeat protocol?
  - https://security.stackexchange.com/questions/55215/why-does-tls-need-an-explicit-heartbeat-protocol
