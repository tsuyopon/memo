# Inkscape
SVGを描くための便利なツールを探していたらInkscapeというdrawingツールがあった。
使い方で困った点などに関するメモ

# インストール
### MAC OSでのインストール
MAC上でinkscapeを動かすためにはあらかじめxquartzをインストールしておく必要があります。
共にdmgファイルで提供されていますのでインストールはそれぞれをインストールするだけです。

xquartzはMAC上でXを動作させるための仕組みです。
- xquartz
  - https://www.xquartz.org/

downloadタブから最新版を入れてください。
- inkscape
  - https://inkscape.org/ja/

一度再起動したほうがいいかもしれません。
初回起動時にはアプリケーションが起動までに数分かかるので注意が必要です。


# 基本操作
### 直線の作成
- Draw Bezie curves and straight linesのアイコン画像をクリック
- 直線の先端をクリック -> 直線の末端でクリック　-> Enterを押下
- ( 画面左下のangleが0度になるようにする必要がある。でないと矢印をつけるとおかしくなる
- https://www.youtube.com/watch?v=FwqJcYGcnBw

### 矢印の作成
- strokeの部分をダブルクリックする　-> 画面右側にwindowが現れる。 -> strokeタブを選択
- https://www.youtube.com/watch?v=JUmjbi3jS_8&t=40s

### サイズを現状作成したものに合わせる
- file -> document properties -> Pageタブ -> Resize page to drawing or selectionを指定すると画面描画領域にのみリサイズされる。
- https://www.youtube.com/watch?v=TICNUF6uiOg


# SVGパーツの探し方
- Inkscapeと連携しているのは次のサイトなのでここから検索で探しても良い
  - https://openclipart.org/
- もしくはGoogle画像検索から"名前 svg"と入力するとたくさん引っかかる

# 参考URL
- http://wiki.inkscape.org/wiki/index.php/FAQ_(Japanese)#Inkscape.E3.81.A3.E3.81.A6.E4.BD.95.E3.81.A7.E3.81.99.E3.81.8B.3F
- 上記の英語版
  - http://wiki.inkscape.org/wiki/index.php/Frequently_asked_questions
