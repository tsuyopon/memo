# 概要
HTTP1.1という非効率な通信プロトコルの仕様を改善するためにGoogleが「SPDY」をベースとして「HTTP/2」が誕生しました。
なお、前進となる2016/05/15にChromeのSPDYサポートは終了されました。

HTTP1.1による制限は次のようなHackとなる最適化手法を生み出していました。しかし、これらはHTTP/2移行により制限が取り払わえることで解決します。
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

### リクエスト仕様
HTTP1.1ではリクエスト時に次の３つの状態で指定していました。
- リクエスト(GET / HTTP/1.1など)
- リクエストヘッダ
- Body

HTTP/2ではバイナリプロトコルとなり次の２つになります。
- HEADERS frame
- DATA frame

### HTTP/2におけるコネクションとストリーム
HTTP/2に関する重要な仕様として次の仕様を覚えておいてください。
- コネクションの中にストリームがある
- ストリームはサーバ・クライアントの双方向でやりとりされている
- ストリームは複数同時に存在しても良い
- ストリームには番号が付与されていて、これをストリームIDと呼ぶ
  - クライアントからスタートしたら奇数、サーバからだと偶数となります。
  - ストリームID 0番は特別な番号で全体の制御に利用します。

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

- Length: ペイロードの長さを表します。2^14 (16,384) よりも大きな値は送ってはならない
- Type: フレームタイプであることを表します。frameのフォーマット(HEADERS, DATA)やセマンティクスを決定する。知らないタイプは無視しなければならない
- Flags: Type(フレームタイプ)ごとに決められた付加情報です。END_STREAM、END_HEADERSフラグなどが重要です。
- R: Reservedを表す1bitの領域
- Stream Identifier: 31ビットのストリームID
  - https://tools.ietf.org/html/rfc7540#section-5.1.1

フレームの種類についてはこちらを参照のこと
- https://tools.ietf.org/html/rfc7540#section-11.2
```
   +---------------+------+--------------+
   | Frame Type    | Code | Section      |
   +---------------+------+--------------+
   | DATA          | 0x0  | Section 6.1  |
   | HEADERS       | 0x1  | Section 6.2  |
   | PRIORITY      | 0x2  | Section 6.3  |
   | RST_STREAM    | 0x3  | Section 6.4  |
   | SETTINGS      | 0x4  | Section 6.5  |
   | PUSH_PROMISE  | 0x5  | Section 6.6  |
   | PING          | 0x6  | Section 6.7  |
   | GOAWAY        | 0x7  | Section 6.8  |
   | WINDOW_UPDATE | 0x8  | Section 6.9  |
   | CONTINUATION  | 0x9  | Section 6.10 |
   +---------------+------+--------------+
```
- IANAに上記以外も規定されているので確認すると良い
  - https://www.iana.org/assignments/http2-parameters/http2-parameters.xhtml

フレームタイプによってデータペイロードの構造が変わってきます。上記に仕様が記載されている各セクションがリスト表示されているので参考のこと。また、これらについてはHTTP2FramePacket.mdでまとめています。


### ストリームやストリームIDについて
- クライアント主導のストリームは奇数番号を使わなければならない
- サーバ主導のストリームは偶数番号を使わなければならない
- ストリームIDが0(0x00)は全体制御を行うコネクション制御メッセージを表す。この値は新規ストリーム確立時に使われてはならない。
- SETTINGSフレームのMAX_CONCURRENT_STREAMSよりも多くのストリームは同時に作ってはならない
- ストリームはどちらからでも切断することが可能である
- 番号を使い果たしたら、新シコネクションを作成する


以下の図は次の仕様書からの引用
- https://tools.ietf.org/html/rfc7540#section-6.1
```
                                +--------+
                        send PP |        | recv PP
                       ,--------|  idle  |--------.
                      /         |        |         \
                     v          +--------+          v
              +----------+          |           +----------+
              |          |          | send H /  |          |
       ,------| reserved |          | recv H    | reserved |------.
       |      | (local)  |          |           | (remote) |      |
       |      +----------+          v           +----------+      |
       |          |             +--------+             |          |
       |          |     recv ES |        | send ES     |          |
       |   send H |     ,-------|  open  |-------.     | recv H   |
       |          |    /        |        |        \    |          |
       |          v   v         +--------+         v   v          |
       |      +----------+          |           +----------+      |
       |      |   half   |          |           |   half   |      |
       |      |  closed  |          | send R /  |  closed  |      |
       |      | (remote) |          | recv R    | (local)  |      |
       |      +----------+          |           +----------+      |
       |           |                |                 |           |
       |           | send ES /      |       recv ES / |           |
       |           | send R /       v        send R / |           |
       |           | recv R     +--------+   recv R   |           |
       | send R /  `----------->|        |<-----------'  send R / |
       | recv R                 | closed |               recv R   |
       `----------------------->|        |<----------------------'
                                +--------+

          send:   endpoint sends this frame
          recv:   endpoint receives this frame

          H:  HEADERS frame (with implied CONTINUATIONs)
          PP: PUSH_PROMISE frame (with implied CONTINUATIONs)
          ES: END_STREAM flag
          R:  RST_STREAM frame

                          Figure 2: Stream States
```


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

