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

## 線の操作
### 直線の作成
- Draw Bezie curves and straight linesのアイコン画像をクリック
- 直線の先端をクリック -> 直線の末端でクリック　-> Enterを押下
- ( 画面左下のangleが0度になるようにする必要がある。でないと矢印をつけるとおかしくなる
- https://www.youtube.com/watch?v=FwqJcYGcnBw

### 矢印の作成
- 画面左下にあるstrokeの部分をダブルクリックする(Ctrl+Shift+F)　-> 画面右側にwindowが現れる。 -> strokeタブを選択
- https://www.youtube.com/watch?v=JUmjbi3jS_8&t=40s

- 参考
  - http://nahcew.com/arrow-inkscape/

### 線の色や太さやStyleを変更する
- 線の色を変更する
  - Fill and Strokeを開く(Ctrl+Shift+F) -> Stroke Paintタブを選択 -> RGBなどを選択して変更する
- 線の太さやStyle(線を点線など)を変更する
  - Fill and Strokeを開く(Ctrl+Shift+F) -> Stroke Styleタブを選択 -> Widthを変更する


### サイズを現状作成したものに合わせる
- file -> document properties -> Pageタブ -> Resize page to drawing or selectionを指定すると画面描画領域にのみリサイズされる。
- https://www.youtube.com/watch?v=TICNUF6uiOg

### 長方形を作成し、その中に文字をセットする
- 画面左側にあるアイコン「Create Rectangles and squres」から長方形を作成する。
- 長方形を作成したがら、画面上側にある「T」字のアイコンを選択して長方形と合わせる。
- あとは文字を入力するだけ

### グループ化して、グループ全体で拡大・縮小したい

Objectタブ -> Groupを指定して、その後範囲選択することによりグループ化できます。
これは、グループ全体で縮尺を変更したい場合などに便利です。


次のショートカット後に範囲選択することでもグループ化可能です。
```
Ctrl + G
```

### 特殊文字を作成する
文字のフォント部分だけ海の画像を使うといったことが可能です。
- http://logo.dollsent.jp/index.php?%E7%94%BB%E5%83%8F%E3%82%92%E4%BD%BF%E3%81%A3%E3%81%9F%E6%96%87%E5%AD%97

文字でアーチを書くといったことも可能です。
- http://logo.dollsent.jp/index.php?%E3%82%A2%E3%83%BC%E3%83%81%E3%82%92%E6%8F%8F%E3%81%8F

### アイコンを作成する
- http://kumacrow.blog111.fc2.com/blog-entry-431.html

### 他のSVGをインポートする
File -> Importから該当のsvgなどを選択することでインポートすることが可能  
もしくは  
Ctrl + Iのショートカットからも可能です。

### Google地図などを元にして独自の地図を作成する
- http://www.heisei-u.ac.jp/ba/blog/images/2011/text.pdf

### 店頭用の広告などを作成してみる
先ほどと同じ以下の資料を参考のこと
- http://www.heisei-u.ac.jp/ba/blog/images/2011/text.pdf

### 指定した形状(オブジェクト)にテキストを流し込む
- https://sites.google.com/site/book001inkscape/home/text/shapetext

### SVGパーツの探し方
- Inkscapeと連携しているのは次のサイトなのでここから検索で探しても良い
  - https://openclipart.org/
- もしくはGoogle画像検索から"名前 svg"と入力するとたくさん引っかかる

# TODO
- undoの方法
- オブジェクトのcopy&pasteがよくわからない

# 参考URL
- http://wiki.inkscape.org/wiki/index.php/FAQ_(Japanese)#Inkscape.E3.81.A3.E3.81.A6.E4.BD.95.E3.81.A7.E3.81.99.E3.81.8B.3F
- 上記の英語版
  - http://wiki.inkscape.org/wiki/index.php/Frequently_asked_questions
