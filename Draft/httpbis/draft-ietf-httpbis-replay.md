# Using Early Data in HTTP
- https://datatracker.ietf.org/doc/draft-ietf-httpbis-replay/

# 解決する課題
TLS Early Data(0-RTT)を利用することは、replay攻撃への可能性を晒すことになってしまいます。
このドキュメントでは、Early Dataが送信される際のHTTPリクエストについてサーバがクライアントを許容するメカニズムについて説明しています。

(具体的にはプロキシを間に挟む場合の提案になっているきがする)


# 解決方法
この仕様書では「Early-Data」ヘッダと425ステータスコードを規定しています。使い方は次の通りです。
- 1. クライアントはTLS1.3 Early DataでHTTPリクエストを行います。
- 2. リクエストを受け取った中間サーバはTLSを終端して、バックエンドへプロキシします。この際に「Early-Data: 1」ヘッダをOriginへのリクエストに付与します。
- 3. 受け取ったオリジンサーバは0-RTTであることをヘッダ情報から識別できるようになります。
- 4. 


# 詳細仕様

### クライアントが仕様する場合
クライアントは次の安全なHTTPメソッドを送付することを許可する(MAY)
- https://tools.ietf.org/html/rfc7231#section-4.2.1


# 参考資料
- https://asnokaze.hatenablog.com/entry/2017/06/22/164937
