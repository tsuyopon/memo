# HTTP Representation Variants
- https://tools.ietf.org/html/draft-ietf-httpbis-variants-02

# 解決したい課題

# 解決方法
第２のキャッシュキーとして「Variants」と「Variant-Key」ヘッダを定義します。
目的としては、キャッシュフレンドリーな先を見据えたコンテントネゴシエーションを実現するためのものです。

# 
サンプルリクエスト及びレスポンス
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

# 参考資料
- IETF101
  - https://datatracker.ietf.org/meeting/101/materials/slides-101-httpbis-variant-00
