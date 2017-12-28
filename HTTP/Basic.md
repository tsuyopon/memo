# 概要
HTTPに関して抑えておくべき基本的な知識

# 詳細

### 歴史を簡単に抑えておく
- HTTP/0.9
  - HTTPヘッダが存在しない(Content-Length、ステータスコード、エラーコードも存在しない)
  - GETメソッドのみサポート
- HTTP/1.0 (RFC1945)
  - HTTPヘッダの概念が追加
  - GET以外にもPOST等の概念がサポート
  - 0.9と区別するためにリクエストプロトコルにバージョンを含めるようになった(GET index.html HTTP/1.0など)
- HTTP/1.1 (RFC2068)
  - Keep-Alive, HTTP Pipiline, Chunked形式のレスポンスサポート
  - Hostヘッダの導入
- HTTP/2 (RFC7540)
  - バイナリプロトコル, 1つのコネクションで同一リクエストを扱う、ヘッダープッシュ、サーバープッシュ

- SeeAlso
  - https://developer.mozilla.org/ja/docs/Web/HTTP/Basics_of_HTTP/Evolution_of_HTTP


### 「Transfer-Encoding: chunked」について
mixiのトップページを見ていたら上記ヘッダがレスポンスに付与されていました。また、この際にContent-Lengthが付与されていませんでした。
- http://kiririmode.hatenablog.jp/entry/20100606/p1

上記によると、次のように書かれていました。
- RFC では、HTTP の特徴として「メッセージボディのサイズを決定することが難しいこと」があり、メッセージボディをチャンク(Chunk) に分け、チャンク毎のサイズとともに送信することで、受信側でそのサイズを確認できるというようなことが書かれています。

巨大なデータを動的に生成しているクライアントだとデータ全体をバッファリングしてContent-Lengthを生成しなければならないので、このような機能があるといったかんじでしょうか。

### X-Frame-Optionsヘッダについて
ヤフーのトップページやその他のサイトなどにアクセスするとよく「X-Frame-Options」ヘッダを見かけます。

このヘッダを含めておくことでブラウザがこの値を解釈し、 クリックジャッキングを防止する(iframe内の表示を制御)手法があります
- クリックジャッキングについては以下のサイトを参考のこと
  - http://www.techscore.com/blog/2015/03/05/%E3%82%AF%E3%83%AA%E3%83%83%E3%82%AF%E3%82%B8%E3%83%A3%E3%82%AE%E3%83%B3%E3%82%B0%E3%81%A3%E3%81%A6%EF%BC%9F/

ヘッダの値としては次の３つがあります。
- DENY: フレーム内のページ表示を全ドメインで禁止する
- SAMEORIGIN: フレーム内のページ表示を同一ドメイン内のみ許可する
- ALLOW-FROM uri: フレーム内のページ表示を指定されたドメインに限り許可する

### x-xss-protectionヘッダについて
次のようなヘッダが含まれる場合があります。
```
x-xss-protection: 1; mode=block
```

通常であればXSSフィルタはデフォルトで有効に設定されているはずですが、ユーザがこの設定を無効にした場合には、このHTTPヘッダがXSSの防止に役立ちます。IE8以降に導入されたXSSフィルターがX-XSS-Protectionヘッダによって活性化できます。

HTTPレスポンスヘッダに X-XSS-Protection: 0 があると、インターネットオプションの設定よりも優先されます。

検出可能なもの
- HTTPレスポンスの元となるHTTPリクエストにスクリプト注入(XSS)攻撃パターンとみなされるものが含まれていて、そのパターンと同じものがHTTPレスポンスにも出現している
- HTTPレスポンスの元となるHTTPリクエストを発生させたアクションやリンクが、HTTPレスポンスを返したサイトと異なるサイトから発生したものである
- 同一のサーバでも、ホスト名による参照とIPアドレスによる参照は、異なるサイトとみなす。

- 参考
  - http://kaworu.jpn.org/security/X-XSS-Protection

### X-Content-Type-Optionsについて
Webブラウザの中には、HTTPレスポンス全体を検査（sniffing）してコンテンツ タイプを判断し、「Content-Type」で指定されたファイルタイプを無視した動作を行うものも存在します。
このsniffingを防止するのが「X-Content-Type-Options」です。「X-Content-Type-Options: nosniff」とすることでsniffingをやめさせ、「Content-Type」に合致しない動作を回避できます。
```
X-Content-Type-Options: nosniff
```

主にIEで発生するコンテンツタイプSniffing対策などで付与されてきたようです。

