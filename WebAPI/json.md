# 概要
JSONをWebAPIとして利用する場合についてのメモ

JSONでのRFC変遷は次のようになっています。
- RFC 4627(2006.06)
- RFC 7158(2013.03)
- RFC 7159(2014.03)
- RFC 8259(2017.12)

もともとJSONの仕様は、IETFとは別にECMA Internationalが策定した「ECMA-404」が存在していましたがRFC8259公開に合わせてRFC 8259とECMA-404 2nd Editionは共通の仕様となりました。
- https://www.rfc-editor.org/rfc/rfc8259.txt

JSONに関する歴史については以下を参考にすること
- https://www.publickey1.jp/blog/17/jsonrfc_8259ecma-404_2nd_editonutf-8.html

# JSON標準レスポンス
JSONでは特定の標準レスポンスは存在しない。
中には $.dataに入れるような表記も存在するが、これが標準というわけではない。
- https://stackoverflow.com/questions/12806386/is-there-any-standard-for-json-api-response-format

RFC8259のExampleを参照するとJSONのサンプルレスポンス(1つの場合、複数の場合)が記載されています。
この仕様では文字エンコーディングは「UTF-8」が必須となっています。

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
