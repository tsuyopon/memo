# 概要
QUIC(Quick UDP Internet Connections)はTCPの代わりにUDP上でTLS1.3を使う仕組みである。

利点としては次の通り
- QUICでは前回の設定や交換した鍵を利用することで最短で0-RTTでの接続をサポートすることで通信の効率化を行う。なお、初回接続時は1-RTTかかる。
- UDPを改変するわけではなく、UDP上のユーザーランドでストリームの多重化通信をサポートする仕組みで、これによりTCPのTCPのHead Of Lineブロッキングを回避する。
  - QUICだと443/UDPへの接続を許可しなければならないので、セキュリティポリシー変更や機器の購入などを考慮しなければなりません。
- 輻輳制御とロスリカバリーのために多くのシグナリングを用意しており、精度が高い制御を行える。
  - また、ユーザーランドなので輻輳制御がプラッガブルである。
- 暗号化や認証を行うことで改ざんや不正なインジェクション攻撃を防ぎます。TLS1.3がQUICの動作要件です。
- QUICコネクションは64bitのコネクションIDによって識別されます。この仕組によってIPアドレスやポート番号元が変化してもコネクションが維持されます。
- 接続開始時にバージョンネゴシエーションを行うことによって複数のQUICバージョンを同時に利用できるようになります。

# 詳細

### 主要RFC
次の４つが主要なRFCとして定義されている。
- QUIC-TRANSPORT: draft-ietf-quic-transport
  - トランスポートプロトコルの仕様を定義する。
- QUIC-RECOVERY: draft-ietf-quic-recovery
  - ロスリカバリのための手順やタイミングを定義する。
- QUIC-TLS: draft-ietf-quic-tls
  - 暗号化層（TLS）のハンドシェイクおよびパケット暗号化のための鍵スケジューリングを定義する。
- QUIC-HTTP: draft-ietf-quic-http
  - QUIC 上に HTTP/2 をマッピングする仕様を定義する。

### 接続確認
- Chromeで次をURLを入力することによってアクティブなセッションを確認することができます。
  - chrome://net-internals/#quic
  - さらなる詳細はこの辺をみることでやりとりしている通信内容までを確認することができます。
    - chrome://net-internals/#events&q=type:QUIC_SESSION%20is:active

Chromeなどがインストールされていればコマンドラインから次のように実行するとブラウザが起動してQUICで接続します。たとえば、対応していないサイトwww.yahoo.co.jpに接続しようとするとQUICで接続できないエラー識別子が表示されます。
```
$ /Applications/Google\ Chrome.app/Contents/MacOS/Google\ Chrome   --user-data-dir=/tmp/chrome-profile   --no-proxy-server   --enable-quic   --origin-to-force-quic-on=www.youtube.com:443  https://www.youtube.com
```
- 参考: 
  - https://github.com/mholt/caddy/wiki/QUIC
  - https://stackoverflow.com/questions/37251357/how-to-send-data-over-quic

### 実装
Google提供によるもの
- クライアント
  - https://cs.chromium.org/chromium/src/net/tools/quic/?q=quic&sq=package:chromium
- サーバ
  - https://cs.chromium.org/chromium/src/net/quic/?q=quic&sq=package:chromium

QUICのWebサーバ実装は次のcaddyのみ
- https://github.com/mholt/caddy/wiki/QUIC

その他にもさまざまな実装が以下で詳細を確認することができます。
- https://github.com/quicwg/base-drafts/wiki/Implementations

QUICの相互接続試験についてはGoogle Spreadsheetsで確認することができます。
- https://docs.google.com/spreadsheets/d/1D0tW89vOoaScs3IY9RGC0UesWGAwE6xyLk0l4JtvTVg/edit#gid=1032646782

# 仕様書など
- draft-ietf-quic-transport(draft12)
  - https://tools.ietf.org/html/draft-ietf-quic-transport-12
- GoogleからQUIC実験を始めたことに伴うアナウンス
  - https://blog.chromium.org/2013/06/experimenting-with-quic.html
  - QUIC仕様書(上記からのリンク)
    - https://docs.google.com/document/d/1RNHkx_VvKWyWg6Lr8SZ-saqsQx7rFV-ev2jRFUoVD34/edit
  - QUIC FAQ(上記からのリンク)
    - https://docs.google.com/document/d/1lmL9EF6qKrk7gbazY8bIdvq3Pno2Xj_l_YShP40GLQE/edit
- QUIC仕様書
  - https://docs.google.com/document/d/1RNHkx_VvKWyWg6Lr8SZ-saqsQx7rFV-ev2jRFUoVD34/mobilebasic

# 参考URL
- QUIC公式サイト
  - https://quicwg.org/
- The Chromium Projects: QUIC, a multiplexed stream transport over UDP
  - https://www.chromium.org/quic
- Google QUICの論文(PDFリンクをクリックすると良い)
  - https://dl.acm.org/citation.cfm?id=3098842
- Google社のスライド
  - https://www.nanog.org/sites/default/files/meetings/NANOG64/1051/20150603_Rogan_Quic_Next_Generation_v1.pdf
  - https://www.ietf.org/proceedings/96/slides/slides-96-quic-3.pdf
- IETF草稿を管理するgithub
  - https://github.com/quicwg/base-drafts
- QUICの現状確認をしたい (2018/1)
  - 現時点での状況がしっかりと整理されている。参照ポインタへのリンクなども整理されている
  - https://qiita.com/flano_yuki/items/251a350b4f8a31de47f5
  - https://asnokaze.hatenablog.com/entry/2018/02/06/004539
- 総務省資料
  - http://www.soumu.go.jp/main_content/000485069.pdf

# TODO
- コマンドラインでアクセスする方法はあるのか?
- ietfで存在するドラフトを確認する(qiitaのリンクにある)
