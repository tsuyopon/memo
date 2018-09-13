# HTTP Representation Variants
- https://tools.ietf.org/html/draft-ietf-httpbis-variants-03

# 解決したい課題

例えば、クライアントからCDNに次のようにen優先でリクエストを投げた場合において、
```
GET /foo HTTP/1.1
Host: www.example.com
Accept-Language: en;q=1.0, fr;q=0.5
```

CDNから上記ヘッダをそのままバイパスされたOriginはenには対応しておらずfrに対応しているのでCDNに対してfrに対応したデータを応答します。
このデータはクライアントへの応答と同時に、CDN側でもキャッシュするものとします。
```
HTTP/1.1 200 OK
Content-Type: text/html;
Content-Language: fr
Vary: Accept-Language
```

そのまま同じリクエストだとCDNのキャッシュから応答される可能性がありますが、次のようにAccept-Languageが若干変わった場合はどうでしょうか?
この場合もOriginはjpに対応していないと仮定します。
```
GET /foo HTTP/1.1
Host: www.example.com
Accept-Language: jp;q=1.0, fr;q=0.6
```

上記のリクエストが来た場合、
CDNはfrのコンテンツを保持しているにもかかわらず、Originサーバにjpを持っていないかどうかを問い合わせることになります。
しかし、Originはjpのコンテンツしか持っていないので、結局frのコンテンツを応答することになります。
実はこれはCDNのキャッシュ中で持っているコンテンツなので、予めオリジンがどの言語に対応しているということがわかれば、CDNでOriginに問い合わせるかどうかを判定することができますが、現状はOriginに必ず問い合わせを行います。

これらの情報を返却してキャッシュフレンドリーな仕組みにしたいというのがこの仕様の目的です。


# 解決方法
第２のキャッシュキーとして「Variants」と「Variant-Key」ヘッダを定義します。
目的としては、キャッシュフレンドリーな先を見据えたコンテントネゴシエーションを実現するためのものです。

# 仕様

### 具体的な例
例えば、リクエスト時にAccept-Languageでen優先、次にfrとして指定した場合において。
その後、Variantsで適用される対象の言語とコンテンツとして応答した対象はfrであることを返却する。
```
GET /foo HTTP/1.1
Host: www.example.com
Accept-Language: en;q=1.0, fr;q=0.5


HTTP/1.1 200 OK
Content-Type: text/html
Content-Language: fr
Vary: Accept-Language
Variants: Accept-Language;fr;de;en;jp
Variant-Key: fr
Transfer-Encoding: chunked 
```

Variantsにはオリジンが利用可能なパラメータが入ります。上記の場合であればfr, de, en, jpが利用できます。
Variantsヘッダを送付する場合にはVariant-Keyヘッダもサーバ側は応答しなければなりません(MUST)。
Variant-Keyはレスポンスとして利用されたパラメータが入ります。例えば、上記の例ではレスポンスがfrで返されたことを意味しています。

### Variantsに複数記述する場合

Variantsには次のように複数記述することもできます。
```
Variants: Accept-Encoding;gzip;br, Accept-Language;en ;fr
Variant-Key: gzip, fr
```

次のように記述するとエンコーディングがgzipまたはidentityのいずれかであることを表します。これはfrの言語でgzip圧縮表現が存在しないことに由来する。
```
Variants: Accept-Encoding;gzip;br, Accept-Language;en ;fr
Variant-Key: gzip;identity, fr
```


# サンプルレスポンス
以下で規定される３つのサンプルレスポンスについて
- https://tools.ietf.org/html/draft-ietf-httpbis-variants-03#section-5.1

### Single Variant

```
   GET /clancy HTTP/1.1
   Host: www.example.com
   Accept-Language: en;q=1.0, fr;q=0.5


   HTTP/1.1 200 OK
   Content-Type: image/gif
   Content-Language: en
   Cache-Control: max-age=3600
   Variants: Accept-Language;en;de
   Variant-Key: en
   Vary: Accept-Language
   Transfer-Encoding: chunked
```

上記の場合にはVaryにAccept-Languageが指定されているので、次の2つの表現がOriginで提供されていることがわかる。
- en
- de

リクエストにはfrが指定されているが、Variantsを見るとわかるようにオリジン側でfrが返されることは無い。

### Multiple Variants

```
   GET /murray HTTP/1.1
   Host: www.example.net
   Accept-Language: en;q=1.0, fr;q=0.5
   Accept-Encoding: gzip, br


   HTTP/1.1 200 OK
   Content-Type: image/gif
   Content-Language: en
   Content-Encoding: br
   Variants: Accept-Language;en;jp;de
   Variants: Accept-Encoding;br;gzip
   Variant-Key: en, br
   Vary: Accept-Language, Accept-Encoding
   Transfer-Encoding: chunked
```

Varyヘッダの値にはAccept-Language, Accept-Encodingと２つのヘッダが指定されていますが、これらの値でキャッシュを分けることになります。
OriginはVariantsで対応しているパラメータを定義していて、組み合わせると次の9つのパターンのキャッシュを保持することが可能となります(ドラフトを見る感じではidentityは指定しなくても含まれているように思われる)
- en, br
- en, gzip
- en, identity
- jp, br
- jp, gzip
- jp, identity
- de, br
- de, gzip
- de, identity



### Partial Coverage

```
   GET /bar HTTP/1.1
   Host: www.example.net
   Accept-Language: en;q=1.0, fr;q=0.5
   Accept-Encoding: gzip, br


   HTTP/1.1 200 OK
   Content-Type: image/gif
   Content-Language: en
   Content-Encoding: br
   Variants: Accept-Encoding;br;gzip
   Variant-Key: br
   Vary: Accept-Language, Accept-Encoding
   Transfer-Encoding: chunked
```

上記の場合ではVaryにはAccept-Language, Accept-Encodingの２つが指定されているが、VariantsとしてはAccept-Encodingの１つしか指定されていない。


# 参考資料
- IETF101
  - https://datatracker.ietf.org/meeting/101/materials/slides-101-httpbis-variant-00
