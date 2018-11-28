# Using Early Data in HTTP
TLS1.3やHTTP over QUICでは0-RTTの仕組みが規定されていますが、リプレイ攻撃に対して脆弱です。
これに対応するために「Early-Data」ヘッダと425ステータスコードを規定しています。
- https://datatracker.ietf.org/doc/draft-ietf-httpbis-replay/

この仕様はRFC8470として規定されています。

# 解決する課題
TLS Early Data(0-RTT)を利用することは、replay攻撃への可能性を晒すことになってしまいます。
このドキュメントでは、Early Dataが送信される際のHTTPリクエストについてサーバがクライアントを許容するメカニズムについて説明しています。

このドキュメントはHTTP over QUICにおける0-RTTでも適用されています。

# 解決方法
この仕様書では「Early-Data」ヘッダと425ステータスコードを規定しています。使い方は次の通りです。
Early-Dataがオリジンサーバで0-RTTで来たかどうかを伝達するヘッダで、425ステータスコードは0-RTTを受け入れない(例えば、リプレイ攻撃が可能なエントリポイントに対してのリクエストなど)場合に使われます。

具体的には次のような形で利用されます。
- 1. クライアントはTLS1.3 Early DataでHTTPリクエストを行います。
- 2. リクエストを受け取った中間サーバはTLSを終端して、バックエンドへプロキシします。この際に「Early-Data: 1」ヘッダをOriginへのリクエストに付与します。
- 3. 受け取ったオリジンサーバは0-RTTであることをヘッダ情報から識別できるようになります。
- 4. Early-Dataを受け入れないことをオリジンサーバが決定した場合、それをクライアントに通達するために425ステータスコードを応答することができます。


# 詳細仕様

### クライアントが仕様する場合
クライアントは次の安全なHTTPメソッドを送付することを許可する(MAY)
- https://tools.ietf.org/html/rfc7231#section-4.2.1


# 参考資料
- RFC8446: Using Early Data in HTTP
  - https://tools.ietf.org/html/rfc8470
- https://asnokaze.hatenablog.com/entry/2017/06/22/164937
