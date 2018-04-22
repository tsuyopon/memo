# 概要
OAuth2.0のBearerトークン仕様についてはRFC6750で規定されています。
この仕様では、TLSを使ったHTTP/1.1でのBearerトークン仕様について定義されています(TLSの利用は義務となっています)。


アクセストークンを使うことにより次のメリットがあります
- OAuthはクライアントに対してリソースオーナーの代わりに指定されたリソースにアクセスするための手段を提供します。
- アクセストークンは認証に必要な要素(username, password, assertion)などをリソースサーバによって理解できる１つのトークンに置き換えます。これによって、トークンの有効期限を設定することが可能になります。

# 詳細

## 抽象化されたフロー
以下はRFC6750のOverviewから抜粋した図である。
```
+--------+                               +---------------+
|        |--(A)- Authorization Request ->|   Resource    |
|        |                               |     Owner     |
|        |<-(B)-- Authorization Grant ---|               |
|        |                               +---------------+
|        |
|        |                               +---------------+
|        |--(C)-- Authorization Grant -->| Authorization |
| Client |                               |     Server    |
|        |<-(D)----- Access Token -------|               |
|        |                               +---------------+
|        |
|        |                               +---------------+
|        |--(E)----- Access Token ------>|    Resource   |
|        |                               |     Server    |
|        |<-(F)--- Protected Resource ---|               |
+--------+                               +---------------+
```
RFC6750では主にE, Fの部分に着目した話となります。


## アクセストークンを受け付ける方法について
アクセストークンを受け付けるための３つの方法として次の方法が規定されています。
- See: https://tools.ietf.org/html/rfc6750#section-2

### 1) Authorizationヘッダ
Authorizationヘッダを利用してBearer認証スキームでアクセストークンを送ります。
```
GET /resource HTTP/1.1
Host: server.example.com
Authorization: Bearer mF_9.B5f-4.1JqM
```

リソースサーバはこのメソッドをサポートしなければなりません(MUST)

### 2) リクエストボディにパラメータを指定する場合
次のようにリクエストボディにaccess_tokenパラメータを指定することができます。
```
POST /resource HTTP/1.1
Host: server.example.com
Content-Type: application/x-www-form-urlencoded

access_token=mF_9.B5f-4.1JqM
```

クライアントは次の条件を満たさなければこのメソッドを利用してはならない(MUST)。
- 「Content-Type: application/x-www-form-urlencoded」ヘッダが指定されていて、そのURLエンコード規約に従っていること
- HTTPリクエストがシングルパートであること
- ボディ中のエンコードされるべきコンテンツが完全にASCIIからのみ成り立っていること
- GETメソッドでないこと(MUST)

### 3) URIクエリパラメータとして指定する場合
次のようにリクエストURIにaccess_tokenパラメータを指定する場合は次のようなリクエストとなります。
```
GET /resource?access_token=mF_9.B5f-4.1JqM HTTP/1.1
Host: server.example.com
```

この方法を指定する場合には、クライアントはCache-Controlヘッダにno-storeオプションを含むべきである(SHOULD)。
サーバからの成功時のレスポンスにはCache-Controlヘッダにprivateオプションを含むべきである(SHOULD)。


## アクセストークンで返却するエラーコード種別
リクエストが失敗する場合、リソースサーバは適切なHTTPステータスコードを付与します(典型的には400, 401, 403, 405など)。
そして、レスポンス中に次のいずれか1つのコードを含むことが規定されています。
- invalid_request
  - リクエストに対して必須のパラメータが不足している場合です。サポートしていないパラメータや値、同一のパラメータの繰り返し、アクセストークンを含んで1つ以上のメソッドを仕様した場合、その他の改竄なども含みます。
  - このリクエストに対してはHTTP 400(Bad Request)を返すべきです(SHOULD)
- invalid_token
  - 指定されたアクセストークンは有効期限切れ、権限剥奪、改竄、またはその他の理由によって不正とみなされた場合
  - そのリソースはHTTP 401(Unauthorized)を返却すべきです(SHOULD)。クライアントは新しいアクセストークンをリクエストして、再度リソースへリクエストしてくるかもしれません。
- insufficient_scope
  - 指定されたアクセストークンよりも大きな権限を要求するリクエストであることを示しています。
  - リソースサーバはHTTP 403(Forbidden)を含むべき(SHOULD)で、アクセスするために必要となるscope属性を付与するかもしれない。

- See: https://tools.ietf.org/html/rfc6750#section-3.1


## アクセストークンのサンプルレスポンス
bearerトークンはOAuth2.0アクセストークンの一部としてクライアントに返却されます。以下はレスポンス例です。
```
HTTP/1.1 200 OK
Content-Type: application/json;charset=UTF-8
Cache-Control: no-store
Pragma: no-cache

{
  "access_token":"mF_9.B5f-4.1JqM",
  "token_type":"Bearer",
  "expires_in":3600,
  "refresh_token":"tGzv3JOkF0XG5Qx2TlKWIA"
}
```

- See: https://tools.ietf.org/html/rfc6750#section-4


## WWW-Authenticate レスポンスヘッダについて
リソースサーバのアクセスに必要なアクセストークンが付与されていない場合、リソースサーバはWWW-Authenticatをレスポンスヘッダを含めなければならない(MUST)。
また、このヘッダは他の状況に応じて含むことになるかもしれない。それはHTTP/1.1のRFC2617に含まれているからである。

このRFC仕様において定義される全てのチャレンジはBearerの認証スキームを使わなければなりません。

以下はYahooの注文検索APIでリクエストしたときのエラーレスポンスのようです(参考: https://qiita.com/rtssn/items/d2066e20be00ce02fac9 )
```
WWW-Authenticate: Bearer realm="yahooapis.jp", error="insufficient_scope", error_description="insufficient scope"
```


(TODO) WWW-Authenticateについてはまとめが不十分
- See: https://tools.ietf.org/html/rfc6750#section-3

# SeeAlso
- RFC6750: The OAuth 2.0 Authorization Framework: Bearer Token Usage
  - https://tools.ietf.org/html/rfc6750
- トークンを利用した認証・認可 API を実装するとき Authorization: Bearer ヘッダを使っていいのか調べた
  - https://qiita.com/uasi/items/cfb60588daa18c2ec6f5
