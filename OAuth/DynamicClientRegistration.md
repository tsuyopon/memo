# 概要
RFC7591: OAuth 2.0 Dynamic Client Registration Protocol
について

# 解決したい課題
RFC6749で定義されるOAuth2.0のAUthorizationサーバを利用するため、クライアントはサーバと連携するためのクライアント識別子の情報が必要となります。
このクライアント識別子の情報を動的にやり取りしたいといった課題があります。

# 解決方法
AuthorzationサーバにOAuth2.0を動的に登録するためのメカニズムを定義する。
この仕様では登録中に使用するための共通のクライアントのメタデータフィールドと値を規定する。

# 詳細

### プロトコルフロー
```
        +--------(A)- Initial Access Token (OPTIONAL)
        |
        |   +----(B)- Software Statement (OPTIONAL)
        |   |
        v   v
    +-----------+                                      +---------------+
    |           |--(C)- Client Registration Request -->|    Client     |
    | Client or |                                      | Registration  |
    | Developer |<-(D)- Client Information Response ---|   Endpoint    |
    |           |        or Client Error Response      +---------------+
    +-----------+
```


### クライアント登録エンドポイント

以下のエンドポイントでAuthorizationサーバはクライアントにユニークな識別子を割り当てることになります。

クライアント登録エンドポイントは以下の要件が規定されています。
- POSTメソッド
- application/jsonメッセージ
- TLS利用

以下のエンドポイントはOAuth2.0のアクセストークンで受け付けても良い(この仕様は本書の対象外)。ただし、基本的にはアクセストークン無しで受け付けられるようにするべきである。

以下にアクセストークンなしで初回リクエストのサンプルです。
```
POST /register HTTP/1.1
Content-Type: application/json
Accept: application/json
Host: server.example.com

{
 "redirect_uris": [
   "https://client.example.org/callback",
   "https://client.example.org/callback2"],
 "client_name": "My Example Client",
 "client_name#ja-Jpan-JP":
    "\u30AF\u30E9\u30A4\u30A2\u30F3\u30C8\u540D",
 "token_endpoint_auth_method": "client_secret_basic",
 "logo_uri": "https://client.example.org/logo.png",
 "jwks_uri": "https://client.example.org/my_public_keys.jwks",
 "example_extension_parameter": "example_value"
}
```

登録成功した場合には、Authorizationサーバはクライアントに対してクライアント識別子を応答します。
サーバは「201 Created」のステータスコードかつ「application/json」のボディタイプで応答します。


続いて、以下はレスポンスのサンプルです。
client_idやclient_secretなどのクライアント識別子が発行されたことを確認することができます。
```
HTTP/1.1 201 Created
Content-Type: application/json
Cache-Control: no-store
Pragma: no-cache

{
 "client_id": "s6BhdRkqt3",
 "client_secret": "cf136dc3c1fc93f31185e5885805d",
 "client_id_issued_at": 2893256800,
 "client_secret_expires_at": 2893276800,
 "redirect_uris": [
   "https://client.example.org/callback",
   "https://client.example.org/callback2"],
 "grant_types": ["authorization_code", "refresh_token"],
 "client_name": "My Example Client",
 "client_name#ja-Jpan-JP":
    "\u30AF\u30E9\u30A4\u30A2\u30F3\u30C8\u540D",
 "token_endpoint_auth_method": "client_secret_basic",
 "logo_uri": "https://client.example.org/logo.png",
 "jwks_uri": "https://client.example.org/my_public_keys.jwks",
 "example_extension_parameter": "example_value"
}
```


# 参考URL
- https://datatracker.ietf.org/doc/html/rfc7591
