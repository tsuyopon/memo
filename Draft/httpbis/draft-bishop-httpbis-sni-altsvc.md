# The "SNI" Alt-Svc Parameter

- https://tools.ietf.org/html/draft-bishop-httpbis-sni-altsvc-02

# 解決したい課題
- コミューニケーション間の機密性と認証はTLSでインターネットをセキュアにするための最初のゴールですが、TLSではホスト名と証明書は暗号化されずに送付されてきます。

# 解決方法
Alt-Svcにsniパラメータを設けます。このHTTPヘッダを受取った後にヘッダで指定された該当のホストに対して接続の切り替えを行います。
なお、この仕様はsni接続先の切り替えを行いますのでSecondary Certificateとのコンビネーションで動きます。
```
h2="innocence.org:443";ma=2635200;persist=true;sni=innocence.org
```
上記のクエリ例だと
- 次の30日間において(ma)、どんなネットワーク上でも(persist)、innocence.org:443でソケットを開き(h2=xxx)、sniとしてinnocence.orgを使う(sni)、HTTP2を使う(h2)

上記の代替へと処理を行う際には、クライアントはTLSハンドシェイク中においてSNI拡張にホスト名を指定しなければなりません。
もし、ホスト名が空文字列である場合には、クライアントはTLSハンドシェイクからSNI拡張を省略(付与しない)すべきです。
この場合、サーバは次のいずれか１つを満たす妥当な証明書を応答しなければなりません。
- SNI拡張で指定されたホスト名
- 代替として発行されたオリジンのホスト名
- 代替へと接続するために使われたホスト名

# サンプル
section3ではいくつかのサンプルが規定されていますので、そちらについて添付します。
- https://tools.ietf.org/html/draft-bishop-httpbis-sni-altsvc-02#section-3

### 通常の利用
https://sensitive.example.com/privateにアクセスして次のAltSvcを受け取った場合
```
h2="innocence.org:443";ma=2635200;persist=true;sni=innocence.org
```

- 1. h2で指定されたinnocence.orgドメインのDNSを解決する
- 2. 1で取得したIPアドレスに対してTCPコネクションとTLSハンドシェイクを開始する
- 3. クライアントはTLSハンドシェイクにおいて、sniに指定された「innocence.org」をSNI拡張に指定します。
- 4. クライアントは「sensitive.example.com」で証明書を検証します
- 5. バリデーションが失敗したら、クライアントは「innocence.org」で証明書を検証します。これは成功します。
- 6. バリデーションが成功したら、クライアントはCERTIFICATE_REQUESTフレームを送ります。
- 7. 「sensitive.example.com」を所有する旨のCERTIFICATEフレームを受け取った後、クライアントはその証明書を検証します。
- 8. クライアントはhttps://sensitive.example.com/privateに対してHTTP/2リクエスト送信を進めます。

### ワイルドカードサブドメインの場合
https://sensitive.example.com/privateにアクセスして次のAltSvcを受け取った場合
```
h2="www.example.com:443";ma=2635200;persist=true;sni=www.example.com
```

- 1. h2で指定されたwww.example.comドメインのDNSを解決する
- 2. 1で取得したIPアドレスに対してTCPコネクションとTLSハンドシェイクを開始する
- 3. クライアントはTLSハンドシェイクにおいて、sniに指定された「www.example.com」をSNI拡張に指定します
- 4. クライアントは「sensitive.example.com」で証明書を検証しますが、証明書はSubject Alternative Nameに「*.example.com」が指定されているので検証が通ります。
- 5. 証明書が信頼されるものであれば、クライアントはHTTP/2リクエストを送信してhttps://sensitive.example.com/privateのデータ取得を行います。

### SNIが省略された場合
https://sensitive.example.com/privateにアクセスして次のAltSvcを受け取った場合
```
h2="alternative.example.com:443";ma=2635200;persist=true;sni=""
```

- 1. h2で指定されたalternative.example.comドメインのDNSを解決する
- 2. 1で取得したIPアドレスに対してTCPコネクションとTLSハンドシェイクを開始する
- 3. クライアントはTLSハンドシェイクにおいて、sniは省略されているので、SNI拡張をClientHelloに含めないで送ります。TLSサーバはデフォルト設定に基づいたサーバ証明書を返却します。
- 4. サーバは「sensitive.example.com」をカバーした証明書(ワイルドドメイン含む)であれば妥当かの検証を行う、そうでなければ不正であるとして即終了します。
- 5. 証明書が信頼されるものであれば、クライアントはHTTP/2リクエストを送信してhttps://sensitive.example.com/privateのデータ取得を行います。

### sniパラメータにリクエスト時と関係ないドメインがある場合
https://sensitive.example.com/privateにアクセスして次のAltSvcを受け取った場合
```
h2=":443";ma=2635200;persist=true;sni=other.example
```

- 1. h2で指定されたsensitive.example.comドメインのDNSを解決する
- 2. 1で取得したIPアドレスに対してTCPコネクションとTLSハンドシェイクを開始する
- 3. クライアントはTLSハンドシェイクにおいて、sniに指定された「other.example」をSNI拡張に指定します。
- 4. TLSサーバはこのホスト名に対する証明書は持っていませんが、証明書としては「sensitive.example.com」のものを応答します。
- 5. クライアントは正しくsensitive.example.comの証明書を検証できます。

# セキュリティについて
現状このAlt-Svcを利用するためには最低1度はOriginと接続する必要があるが、これはDNS over HTTPS(DoH)を使うことにより緩和される予定ではある。


# 参考URL
- https://tools.ietf.org/html/draft-bishop-httpbis-sni-altsvc-02
