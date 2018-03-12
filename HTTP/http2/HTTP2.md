# 概要
HTTP/2は、HTTP1.1という非効率な通信プロトコルの仕様を改善するためにGoogleが「SPDY」をベースとして「HTTP/2」が誕生しました。
なお、2016/05/15にChromeのSPDYサポートは終了されました。

HTTP1.1による制限は次のような最適化手法を生み出していた。これらはHTTP/2移行により制限が取り払わえる
- ドメインシャーディング
- イメージスプライト
- CSS, Javascript, 画像のインライン化
- クッキーなしドメイン

HTTP/2の特徴
- 1つのコネクション内部で複数のリクエスト/レスポンスができるようになった
  - HTTP1.1では一般的なブラウザは1つのドメインあたり同時接続数が最大6という制限があった。何度もTCP接続していたが、HTTP/2では１度だけの接続となった。
  - HTTP1.1から存在するパイプライン機能では、クライアントからA, B, Cというリクエストがある場合、サーバ側もA, B, Cの順番で返す必要があった。このため、Aで処理がかかるような場合には後続を待たせることになって遅くなる
    - HTTP/2ではプライオリティ機能も存在し上記でクライアントからBを優先してくださいといったリクエストをサーバに送ることによって、サーバからBを受け取ることが可能となる。
- クライアントとサーバ間の通信がバイナリで行われるようになり、処理が高速となった。
- HPACKというヘッダー圧縮フォーマットを使用することによって、１度送信したヘッダを再送信せずに必要な差分ヘッダのみ送信することが可能になりました。
- サーバプッシュ機能と呼ばれる、リクエストされていないコンテンツをサーバがクライアントに送信される機能
- HTTP/2自体の仕様はTLS上でなくても可能だが、chromeやfirefoxのブラウザでもTLSを利用するものしか対応していないので実質TLSを利用するしかありません。

ほとんどすべてのブラウザでHTTP/2が利用可能となっている。
- http://caniuse.com/#feat=http2

HTTP/1.1とHTTP/2との画像出力における比較サイトも参考すると良い。
- https://http2.akamai.com/demo

# 仕様

### HTTP/2で開始するFRAMEフォーマット
次の9バイトで始まる
```
    +-----------------------------------------------+
    |                 Length (24)                   |
    +---------------+---------------+---------------+
    |   Type (8)    |   Flags (8)   |
    +-+-------------+---------------+-------------------------------+
    |R|                 Stream Identifier (31)                      |
    +=+=============================================================+
    |                   Frame Payload (0...)                      ...
    +---------------------------------------------------------------+
```

- Length: 2^14 (16,384) よりも大きな値は送ってはならない
- Type: frameのフォーマットやセマンティクスを決定する。知らないタイプは無視しなければならない
- Flags: frame typeに特化したboolean flagsのための予約フィールド
- R: Reservedを表す1bitの領域
- Stream Identifier: 
  - https://tools.ietf.org/html/rfc7540#section-5.1.1


### Stream Identifierについて
- クライアント主導のストリームは奇数番号を使わなければならない
- サーバ主導のストリームは偶数番号を使わなければならない
- 0x00はコネクション制御メッセージを表す。この値は新規ストリーム確立時に使われてはならない。


###
- ストリームはどちらからでも切断することが可能である


# TIPS
### TLSがALPNに対応していることを確認する
TLSがALPN拡張に対応していないと初期接続としてHTTP/2を確立できません。
次のopensslコマンドで確認することができます。なお、OpenSSLはALPNをサポートしていますが、サポートしているバージョンは OpenSSL 1.0.2 以降です。
```
$ echo | openssl s_client -alpn h2 -connect www.yahoo.co.jp:443 
```

対応している場合には次の行が表示されます
```
ALPN protocol: h2
```

対応していない場合には次のようが表示されます
```
No ALPN negotiated
```

### ブラウザの開発ツール

- chromeの場合にはプロトコルはデフォルトで表示されていません。
  - 「デベロッパーツール」の「Network」タブでプロトコルを確認できるがデフォルトでは表示されていない。
  - 「Network」タブでヘッダーカラムを右クリックして表示項目で「Protocol」やHTTP2で利用される「Priority」などを表示するようにしておくと良い。
  - 次のURLにアクセスすることで接続数なども確認することができます。IDをクリックするとさらに詳細なデータの双方向のやりとりを確認することができます。
    - chrome://net-internals/#http2
- Firefoxで確認する場合には特に設定不要で確認できます。



- 参考URL
  - http://knowledge.sakura.ad.jp/knowledge/7735/
  - https://blog.sakurasaku-labo.jp/http2-beginners/


### wiresharkでHTTP/2のパケット構造を確認する
wiresharkを開いて何も設定しない状態だとTLSで暗号化されているのでプロトコルがHTTP/2と表示されません。

これに対処するにはブラウザ側とwireshark側双方に設定を行います。

ブラウザ側では起動時に次のようにコンソールからSSLKEYLOGFILEを指定して実行します。自分が試した感じだとexportしてから起動だとうまく動作しなかったのですが、この方法であれば起動しました。
```
// firefoxの場合
$ SSLKEYLOGFILE=~/Desktop/tls_key.log "/Applications/Firefox.app/Contents/MacOS/firefox-bin"

// chromeの場合
$ SSLKEYLOGFILE=~/Desktop/tls_key.log "/Applications/Google Chrome.app/Contents/MacOS/Google Chrome"
```
- 参考
  - https://gist.github.com/summerwind/a482dd1f8e9887d26199

出力されるtls_key.logは次のようなフォーマットです。
- https://developer.mozilla.org/en-US/docs/Mozilla/Projects/NSS/Key_Log_Format

続いて、wiresharkの設定を行います。wiresharkを起動して「Preferences > Protocols > SSL」(※TLSは存在しないことに注意)として設定管理画面を開きます。  
「(Pre)-Master-Secret log filename」の箇所に先程SSLKEYLOGFILEで指定したファイルを指定します。

これでwiresharkからでもHTTP/2のプロトコルやその内部のヘッダ構造などが正しく表記されています。

### HTTP/2デバッグ方法や便利ツール
以下にデバッグや便利ツールを紹介する素晴らしい記事があった。
- Tools for debugging, testing and using HTTP/2
  - https://blog.cloudflare.com/tools-for-debugging-testing-and-using-http-2/

上記ではHTTP/2をデバッグするために次のようなツールや方法を紹介
- chrome用プラグイン「Extension HTTP/2 and SPDY indicator」の紹介
  - https://chrome.google.com/webstore/detail/http2-and-spdy-indicator/mpbpobfflnpcgagjijhmgnchggcjblin?hl=en
- onlinet test toolの紹介
  - https://tools.keycdn.com/http2-test
- chrome用プラグイン「Claire」の紹介
  - https://chrome.google.com/webstore/detail/claire/fgbpcgddpmjmamlibbaobboigaijnmkl
- curl(7.43.0以降)の紹介
  - https://nghttp2.org/  がリンクされているとのこと
- HTTP/2実装時に利用可能なライブラリnghttp2
  - https://nghttp2.org/
- h2loadベンチマーク(like ab)の紹介。nghttp2に含まれている
　- https://nghttp2.org/documentation/h2load-howto.html
- opensslコマンド
  - nextprotonegを付与するとどのプロトコルを使っているかを表示してくれる
  - openssl s_client -connect www.cloudflare.com:443 -nextprotoneg ''
- h2cの紹介
  - https://github.com/fstab/h2c
- h2iの紹介
  - https://github.com/golang/net/tree/master/http2/h2i
- h2specの紹介
  - https://github.com/jgrahamc/h2scan
- is-http2-cliの紹介
  - https://github.com/stefanjudis/is-http2-cli
- wiresharkでのHTTP/2デバッグ
- Chrome Developer ToolsにProtocolを表示


# 参考URL
- HTTP/2
  - https://http2.github.io/
- HTTP2 Advent Calendar 2014
  - http://qiita.com/advent-calendar/2014/http2
- HTTP2 Advent Calendar 2015
  - http://qiita.com/advent-calendar/2015/http2
- HTTP2 Advent Calendar 2016
  - http://qiita.com/advent-calendar/2016/http2
- HTTP1.1とHTTP/2の速さを比較するデモサイト
  - http://http2vs1.cybertrust.ne.jp/

# 参考
- RFC7540: Hypertext Transfer Protocol Version 2 (HTTP/2)
  - https://tools.ietf.org/html/rfc7540
- RFC7541: HPACK: Header Compression for HTTP/2
  - https://tools.ietf.org/html/rfc7541

