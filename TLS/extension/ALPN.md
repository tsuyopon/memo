# Application Layer Protocol Negotiation(ALPN)
ALPNは次のような仕組みです。
- TLSハンドシェイク中においてアプリケーションレイヤーに対してプロトコル選択をネゴシエーションすることができるためのTLS拡張です。
- ALPNを用いることでClietnHelloメッセージの一部としてクライアントはサポートされるプロトコルリストを送ります。サーバ側はそのプロトコルリストの中から利用したいプロトコルを選択してServerHelloメッセージに含めて返答します。
- ユーザエクスペリエンスを損なわないように、サーバ、クライアント間のラウンドトリップがないようにすることができる。

# 背景
HTTP/2は平文の場合には次のように開始します。
- 1. 最初はHTTP/1.1で接続が始まる
  - クライアントはGETメソッドを発行して、そのリクエストヘッダーに「Upgrade: h2c」を入れる。(HTTP/2の平文だとh2ではなく、h2cとなる)
- 2. サーバ側がUpgradeヘッダーへのレスポンスとして「101 Switching Protocols」、「Connection: upgrade」、「Upgrade: h2c」を返却する。
- 3. HTTP/2での接続が始まる。

一方で、TLSを利用する場合にはALPNというTLS拡張の仕組みを使うことで上位レイヤーに対して利用したいプロトコルを伝えることができる。
これによって、、ラウンドトリップの無駄な時間を抑制することが可能になる。
- 1. TLSのClientHello時にTLS拡張としてALPNの中に利用可能なプロトコルリストを全て含める
- 2. サーバ側ではClientHelloの中から選択された唯一のプロトコルを応答として返却する。

現在ではHTTP/2を利用する場合にはTLSを使わないと受け付けない実装も多い。

# 詳細
### ALPNで指定することができるプロトコル一覧
IANAで定義されている。
- https://www.iana.org/assignments/tls-extensiontype-values/tls-extensiontype-values.xhtml#alpn-protocol-ids

### TLSがALPNに対応していることを確認する
次のopensslコマンドでALPN拡張としてHTTP/2(h2)をClientHelloから送付します。
なお、OpenSSLはALPNをサポートしていますが、サポートしているバージョンは OpenSSL 1.0.2 以降です。
```
// 1つ指定する場合
$ echo | openssl s_client -alpn h2 -connect www.yahoo.co.jp:443 

// 複数指定する場合
$ echo | openssl s_client -alpn h2,http/1.1 -connect www.yahoo.co.jp:443 
```

対応している場合には次の行が表示されます
```
ALPN protocol: h2
```

対応していない場合には次のようが表示されます
```
No ALPN negotiated
```

### データ構造
```
enum {
    application_layer_protocol_negotiation(16), (65535)
} ExtensionType;

opaque ProtocolName<1..2^8-1>;

struct {
    ProtocolName protocol_name_list<2..2^16-1>
} ProtocolNameList;
```

### データサンプル
- ClientHelloのサンプル
```
Extension: Application Layer Protocol Negotiation
    Type: Application Layer Protocol Negotiation (0x0010)
    Length: 14
    ALPN Extension Length: 12
    ALPN Protocol
        ALPN string length: 2
        ALPN Next Protocol: h2
        ALPN string length: 8
        ALPN Next Protocol: http/1.1
```
- ServerHelloのサンプル: 1つだけ選択されていることが確認できる
```
Extension: Application Layer Protocol Negotiation
    Type: Application Layer Protocol Negotiation (0x0010)
    Length: 11
    ALPN Extension Length: 9
    ALPN Protocol
        ALPN string length: 8
        ALPN Next Protocol: http/1.1
```

# SeeAlso
- RFC7301: Transport Layer Security (TLS) Application-Layer Protocol Negotiation Extension
  - https://tools.ietf.org/html/rfc7301
