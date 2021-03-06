# 概要
IETFについてまとめておくことにする
公式サイトは次の通り
- https://www.ietf.org/

# 詳細

### IETFに参加する場合
- 登録日程などに注意する
  - https://datatracker.ietf.org/meeting/important-dates/

### IETFエリアについて
2018/02現在としては次のとおりである。
- GEN: General(統括的技術分野)
- ART(3): Application and Real Time(応用・リアルタイム分野)
- INT(2): Internet(インターネット分野)
- OPS(2): Operation And Management(運用管理分野)
- RTG(3): Routing(ルーティング分野)
- SEC(2): Security(セキュリティ分野)
- TSV(2): Transport and Service (トランスポート分野)

合計15のエリアが存在するらしい。

上記の上位組織としてIESGとその上にIAB、ISOCが存在しています。
IESGが作成するRFCの取り扱い方法に関する決定を下す。つまり、InternetDraftがRFCになるかどうかの大きな影響力を持つ。

- SeeAlso
  - https://www.ietf.org/topics/areas/

### 各エリアの詳細について
- ARTエリアの主なWG
  - appsawg: 他のWGに入らない話題
  - httpbis: HTTP/2
  - core: CoAP
  - uta: アプリレベルでのTLSの活用
  - precis: 識別子の国際化
  - rtcweb: WebRTC
  - netvc: コーデック
  - webpush: 通知
  - cdni: CDN Interconnection

### IETFへ初めて参加する場合
次の資料を見ておくのが良い
- IETF会合に初めて参加して
  - https://www.nic.ad.jp/ja/newsletter/No62/0640.html
  - 第1回IETF勉強会
    - https://www.isoc.jp/wiki.cgi?page=PreIETF93
  - 第2回IETF勉強会
    - https://www.isoc.jp/wiki.cgi?page=PreIETF94

上記からの関連だが次の資料などにも目を通しておくこと
- PDF資料
  - IETFの歩き方(pdf)
    - http://www.isoc.jp/wiki.cgi?action=ATTACH&file=ietf94study%5F01%5Ftutorial%5Fnemoto%2Epdf&page=PreIETF94
    - https://www.isoc.jp/wiki.cgi?page=PreIETF93&action=ATTACH&file=20150701%5Fpre%2DIETF%2D01%5Fnemo%2Epdf
  - Working Group参加の心構えとInternet-Draftの読み方
    - https://www.isoc.jp/wiki.cgi?page=PreIETF94&file=ietf94study%5F02%5Ftutorial%5Fshimaoka%5Fr5%2Epdf&action=ATTACH
  - RFC/Internet-Draftの読み方
    - http://www.isoc.jp/wiki.cgi?page=PreIETF93&action=ATTACH&file=isocjp%2Dietf%2Dstudy%2D20150701%5Fhayashi%5Fnishizuka%2Epdf
  - RFC/Internet-Draftの書き方
    - https://www.isoc.jp/wiki.cgi?page=PreIETF93&file=isocjp%2Dietf%2Dstudy%2D20150701%2Dsakane%2Dfixed%2Epdf&action=ATTACH
- IETFのタオ
  - http://www6.ietf.org/tao-translated-ja.html


注意点としては
- ドレスコードは禁止なので天気にあった服が望ましい
- 日曜日から参加するとIETFで２時間かけてNewcomer's Orientationを行ってもらえる。


### 押さえておいた方がよさそうなサイトなど

たとえば、IETF101でのMeeting Agendaは以下(URLを見る限りでは時間がたてば最新のIETFに変わる)
- https://datatracker.ietf.org/meeting/agenda/

前回のアジェンダ
- https://datatracker.ietf.org/meeting/101/agenda
- https://datatracker.ietf.org/meeting/100/agenda

若干UI表示が違うがこちらも見ると良い
- https://tools.ietf.org/agenda/102/
- https://tools.ietf.org/agenda/101/
- https://tools.ietf.org/agenda/100/

### IETFに向けてのツール
- datatracker
  - https://datatracker.ietf.org/
- meetecho
  - ドメインの100, 99の部分を変更するとmeetechoが閲覧可能
    - IETF100
      - http://ietf100.conf.meetecho.com/index.php/
    - IETF99
      - http://ietf99.conf.meetecho.com/index.php/
- jabber
  - アカウントが必要らしい

### RFCやドラフトの探し方
- RFC効率的な探し方
  - http://www6.ietf.org/
  - から「RFC Pages」のタブをクリックして、その後「RFC Search Page」のリンクから次のリンクに飛ぶ
  - キーワードを入れるだけでそれに該当するRFCを表示してくれます。
    - https://www.rfc-editor.org/search/rfc_search.php
- RFCドラフトの効率的な探し方
  - http://www6.ietf.org/
  - から「Internet-Drafts」の「Search」リンクをクリックする
  - 次の箇所からキーワードを入れるだけで該当するRFCのドラフトを表示してくれます。
    - https://datatracker.ietf.org/doc/
- WGから探す場合
  - https://datatracker.ietf.org/wg/
  - 上記で表示され各種WGのリンクを辿ることでActiveなDraftやRFCを辿ることができる。
- 表示されるI-D Existsとは何のこと?
  - datatracker周りの規則についてはこの辺にまとめられている。
    - https://tools.ietf.org/html/rfc6174
  - 流れについてはこの辺のスライド(p8)が状態遷移をわかりやすく説明してくれているので参考にすること
    - https://www.slideshare.net/tanupoo/isocjp-ietfstudy20150701sakane-50034092
  - 参考slide
    - https://www.isoc.jp/wiki.cgi?page=PreIETF93&action=ATTACH&file=isocjp%2Dietf%2Dstudy%2D20150701%5Fhayashi%5Fnishizuka%2Epdf

# 必要メモ
- IETF参加登録
  - https://www.ietf.org/how/meetings/register/
  - IETFへの参加登録は「Acknowledge & Continue to Meeting Registration」などのリンクから行う。
  - 必要情報を入力後に、クレジットカードで支払いを済ませるので手元に準備しておくことになります。

# IETF102メモ
- httpbis
  - https://datatracker.ietf.org/wg/httpbis/documents/
  - https://tools.ietf.org/wg/httpbis/
- tls
  - https://datatracker.ietf.org/wg/tls/documents/
  - https://tools.ietf.org/wg/tls/
- doh
  - https://datatracker.ietf.org/wg/doh/documents/
    - https://datatracker.ietf.org/doc/draft-ietf-doh-dns-over-https/
  - https://tools.ietf.org/wg/doh/
- oauth
  - https://datatracker.ietf.org/wg/oauth/documents/
    - https://datatracker.ietf.org/doc/draft-ietf-oauth-discovery/
    - https://datatracker.ietf.org/doc/draft-ietf-oauth-jwsreq/
    - https://datatracker.ietf.org/doc/draft-ietf-oauth-device-flow/
    - https://datatracker.ietf.org/doc/draft-ietf-oauth-token-exchange/
  - https://tools.ietf.org/wg/oauth/
- quic
  - https://datatracker.ietf.org/wg/quic/documents/
  - https://tools.ietf.org/wg/quic/
- ace
  - https://datatracker.ietf.org/wg/ace/documents/
  - https://tools.ietf.org/wg/ace/


# 前回のアジェンダ
- https://tools.ietf.org/agenda/101/
- https://tools.ietf.org/agenda/100/

# 前回のスライドなど
- https://datatracker.ietf.org/meeting/101/proceedings
- https://datatracker.ietf.org/meeting/100/proceedings
- https://datatracker.ietf.org/meeting/99/proceedings

# 過去の資料など
- https://datatracker.ietf.org/meeting/99/agenda.html
- https://datatracker.ietf.org/meeting/100/agenda.html
- https://datatracker.ietf.org/meeting/101/agenda.html

「show meeting materials」を押下すると過去のスライドなどを閲覧することができます。

# 参考URL
- 公式サイト
  - https://www.ietf.org/
- RFC Editor
  - https://www.rfc-editor.org/
