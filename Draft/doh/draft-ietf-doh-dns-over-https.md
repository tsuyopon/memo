# 概要
HTTPS経由によるDNSクエリの発行及びレスポンスの取得を行うことについてまとめた仕様である。
この仕様はHTTP/2のみに規定されていて、DNS Queries over HTTPS(DoH)でRFC8484として規定される。

# 解決したい課題
- DNSのメッセージは平文であるために、HTTPS接続などを行っても接続先は第三者に明らかになってしまう問題がある。
- DNSメッセージが途中で書き換えられてしまい、本来とは異なるDNSサーバへと誘導されてしまう可能性がある

# 解決方法
- HTTP/2でDNSメッセージを運ぶ
  - このHTTPSで応答を返すDNSサーバのことをこのドラフトではDNSサーバではなくDoH(DNS over HTTPS)サーバと呼ぶことにする。

# 詳細

### 要求仕様
- DoHサーバはGETとPOSTを実装しなければならない(MUST)
- GETを使った実装の方がHTTPキャッシュフレンドリな実装となる。
- DNSサーバとDNSクライアントは相互運用性のために「application/dns-message」をサポートしなければならない


- DoHを使うminimumなおすすめバージョンはHTTP/2となっている
- GETを使ったクエリはbase64エンコード、POSTはエンコーディング不要

### HTTPリクエストサンプル
GETかPOSTメソッドを使います。 Acceptヘッダとして「application/dns-message」を含めます。
GETはbase64encodingしますが、POSTはしません。

- GETの場合の例
  - dnsクエリには「www.example.com」のbase64url_encodeした値が指定されています。
```
   :method = GET
   :scheme = https
   :authority = dnsserver.example.net
   :path = /dns-query?dns=AAABAAABAAAAAAAAA3d3dwdleGFtcGxlA2NvbQAAAQAB
   accept = application/dns-message
```

- POSTの場合の例
  - ボディには先程のdnsクエリがhex encodingされたものが指定されています。
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

### HTTPレスポンスサンプル
TTLがcache-controlから128秒であり、192.0.2.1のレスポンスを返却する
```
   :status = 200
   content-type = application/dns-message
   content-length = 64
   cache-control = max-age=128

   <64 bytes represented by the following hex encoding>
   00 00 81 80 00 01 00 01  00 00 00 00 03 77 77 77
   07 65 78 61 6d 70 6c 65  03 63 6f 6d 00 00 01 00
   01 03 77 77 77 07 65 78  61 6d 70 6c 65 03 63 6f
   6d 00 00 01 00 01 00 00  00 80 00 04 C0 00 02 01
```

# 対応状況
- Firefoxが対応
  - https://blog.nightly.mozilla.org/2018/06/01/improving-dns-privacy-in-firefox/
- Androidが対応
  - https://developers-jp.googleblog.com/2018/05/dns-over-tls-support-in-android-p.html

# TODO
- base64urlやレスポンスの変換方法をちゃんと検証できていない
- ENDS0拡張って何?

# 参考URL
- https://tools.ietf.org/html/rfc8484
