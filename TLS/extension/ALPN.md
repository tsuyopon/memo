# Application Layer Protocol Negotiation(ALPN)
ALPNは次のような仕組みです。
- TLSハンドシェイク中においてアプリケーションレイヤーに対してプロトコル選択をネゴシエーションすることができるためのTLS拡張です。
- ALPNを用いることでClietnHelloメッセージの一部としてクライアントはサポートされるプロトコルリストを送ります。サーバ側はそのプロトコルリストの中から利用したいプロトコルを選択してServerHelloメッセージに含めて返答します。
- ユーザエクスペリエンスを損なわないように、サーバ、クライアント間のラウンドトリップがないようにすることができる。

# ALPNができた背景
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

# ALPNで指定することができるプロトコル一覧
IANAで定義されている。
- https://www.iana.org/assignments/tls-extensiontype-values/tls-extensiontype-values.xhtml#alpn-protocol-ids

# TLSがALPNに対応していることを確認する
次のopensslコマンドでALPN拡張としてHTTP/2(h2)をClientHelloから送付します。
なお、OpenSSLはALPNをサポートしていますが、サポートしているバージョンは OpenSSL 1.0.2 以降です。
```
$ echo | openssl s_client -alpn h2 -connect www.yahoo.co.jp:443 
```

対応している場合には次の行が表示されます
```
ALPN protocol: h2
```

対応していない場合には次のようが表示されます
```
No ALPN negotiated
```

# SeeAlso
- https://tools.ietf.org/html/rfc7301
