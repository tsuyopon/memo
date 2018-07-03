# 概要
HTTP/2経由でDNSクエリの発行及びレスポンスの取得を行うことについてまとめた仕様である。

次のDraft10の仕様書を元にまとめることとする。
- https://tools.ietf.org/html/draft-ietf-doh-dns-over-https-10


# 課題及び解決する課題
- 課題
  - DNSのメッセージは平文であるために、HTTPS接続などを行っても接続先は第三者に明らかになってしまう問題がある。
  - DNSメッセージが途中で書き換えられてしまい、本来とは異なるDNSサーバへと誘導されてしまう可能性がある

- 解決する課題
  - HTTP/2でDNSメッセージを運ぶ

# 詳細

### 要求仕様
- 最低バージョンはHTTP/2となっている
- GETを使ったクエリはbase64エンコード、POSTはエンコーディング不要
- DNSサーバとDNSクライアントは相互運用性のために「application/dns-message」をサポートしなければならない

### HTTPリクエストサンプル
GETかPOSTメソッドを使います。 Acceptヘッダとして「application/dns-message」を含めるようにします。

- GETの場合の例
```
   :method = GET
   :scheme = https
   :authority = dnsserver.example.net
   :path = /dns-query?dns=AAABAAABAAAAAAAAA3d3dwdleGFtcGxlA2NvbQAAAQAB
   accept = application/dns-message
```

- POSTの場合の例
```
   :method = POST
   :scheme = https
   :authority = dnsserver.example.net
   :path = /dns-query
   accept = application/dns-message
   content-type = application/dns-message
   content-length = 33

   <33 bytes represented by the following hex encoding>
   00 00 01 00 00 01 00 00  00 00 00 00 03 77 77 77
   07 65 78 61 6d 70 6c 65  03 63 6f 6d 00 00 01 00
   01
```

# TODO
- http://www.geekpage.jp/blog/?id=2017-12-20-1

- ENDS0拡張って何?
