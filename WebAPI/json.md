# 概要
JSONをWebAPIとして利用する場合についてのメモ

# JSON仕様について
以下に標準仕様が定義されています。
- https://www.rfc-editor.org/rfc/rfc8259.txt

JSONでは特定の標準レスポンスは存在しない。
中には $.dataに入れるような表記も存在するが、これが標準というわけではない。
- https://stackoverflow.com/questions/12806386/is-there-any-standard-for-json-api-response-format

RFC8259のExampleを参照するとJSONのサンプルレスポンス(1つの場合、複数の場合)が記載されています。

# エラーレスポンス
JSONのエラーレスポンスの標準はRFC7807で定義されています。
Content-Typeや各種要素が定義されていますので、参考にすることができます。

```
HTTP/1.1 403 Forbidden
Content-Type: application/problem+json
Content-Language: en

{
 // エラー詳細ドキュメントへのURL
 "type": "https://example.com/probs/out-of-credit",
 // 短いサマリー 
 "title": "You do not have enough credit.",
 // 説明文 
 "detail": "Your current balance is 30, but that costs 50.",
 // 問題発生箇所のURI
 "instance": "/account/12345/msgs/abc",
 // statuは省略

 // 口座の残高
 "balance": 30,
 // 扱うことのできる口座へのリンク
 "accounts": [
    "/account/12345",
    "/account/67890"
 ]
}
```
