# 概要
ImageMagickは、画像を表示・操作するためのソフトウェアです。 以下に特徴を記します。
- GIF、JPEG、PNG等の100種類以上の画像ファイルフォーマットに対応している
- GPL互換によるライセンスが提供されており、ライセンス的に緩い

ImageMagickでは次のような方法を提供します。
- プログラムから利用する方法
- コマンドラインから利用する方法

# 詳細
### 画像から画像データを取得する
```
$ convert xxxxx.jpg xxxxx.txt  <=txt又はtextと拡張子を指定する
$ cat xxxxx.txt
0,0: 255,255,255  #ffffff
1,0: 255,255,255  #ffffff
2,0: 255,255,255  #ffffff
3,0: 255,255,255  #ffffff
4,0: 255,255,255  #ffffff
5,0: 255,255,255  #ffffff
6,0: 255,255,255  #ffffff
7,0: 255,255,255  #ffffff
8,0: 255,255,255  #ffffff
9,0: 255,255,255  #ffffff
```

### 画像を上下左右反転させる
以下の2つの方法がある
- gimpでGUI操作([水平反転]と[垂直反転])を使用する
- convertコマンドを使用する。
```
$ convert -flip hogehoge.jpg flip.jpg  <= 上下反転しflip.jpg作成
$ convert -flop hogehoge.jpg flop.jpg  <= 左右反転しflop.jpgを作成
```

### 画像の合成を行いたい
```
(例)$combine -compose difference test1.gif test2.gif L2.gif
```
上記ではtest1.gifとtest2.gifを結合し、L2.gifを作成している。 オプションのdifferenceは2つの画像の値の差分をとっている。

### 画面やウィンドウのスクリーンショットを取りたい
```
$ import xxxxx.png
```
とコマンドを入力して、キャプチャを取得したいウィンドウをマウスでクリックすると保存できる。

また、フレーム付きでウィンドウを保存する場合には
```
$ import -frame xxxxx.png
```

画面全体をキャプチャするには
```
$ import -window root xxxxx.png
```

さらに、白黒画像で保存したい様な場合には
```
$ import -monochrome xxxxx.png
```
xwdコマンドでも同様の操作を行うことができます

### 画像を表示したい
displayコマンドにより表示できる
```
$ display xxxx.jpg
```

又は、xvコマンドによっても表示できる
```
$ xv xxxxx.jpg
```

### 画像を複数枚スライドショーの様に表示したい
animateコマンドにより実現可能である。
delayオプションを指定しないと100分の1秒で切り替わるのですごい早い。 よって、以下の様に-delay 100とすると1秒ごとに画像が置き換わる
```
$ animate -delay 100 tmp0[1-3].png
```

また、xvコマンドでも同様の操作が可能である 例えば、カレントディレクトリ中のgifファイル全てを1秒間隔で表示したい場合
```
$ xv *.gif -wait 1 &
```

### 画像の種類を変換したい
どのフォーマットに変換するかは、指定した拡張子から自動的に判別してくれる。
```
$ convert sample.gif sample.jpg
```

### 画像の種類を"一括"変換したい
通常はconvertコマンドでも問題ないが、複数の画像を一括で行ってしまいたい ような場合がある。 例えば、jpgをpng形式に一括変換したい場合には
```
$ mogrify -format png *.jpg
```

画像サイズを100x75に変えて上書き保存したい場合には
```
$ mogrify -geometry 100x75 *.jpg 
```

また、以下の様に!を付与すると縦横比関係なくサイズを変更します。
```
$ mogrify -geometry 100x75! *.jpg 
```

### 画像から動画gifを生成する
adjoin オプションで、動画GIFを生成することができる。
```
$ convert -adjoin image01.gif image02.gif image03.gif sample.gif
```
image01〜03.gif からなる、動画GIF sample.gif を生成する

その逆、動画GIF sample.gif を分割し、image00,01,02...gif という画像ファイルを生成する
```
$ convert +adjoin sample.gif image%02d.gif
```

### 画像の表示サイズを変更したい(拡大、縮小)
```
$ convert   -geometry 100x75   orig1.jpg new1.jpg    <= 表示サイズを100x75にする
$ convert   -geometry 20%x20%  orig2.jpg new2.jpg    <= 縦と横を各々20%にして保存
$ convert   -geometry 20%      orig3.jpg new3.jpg    <= 縦、横の縮小比率が同じである方が良い
```

### その他の画像サイズ・スケール変換処理
```
$ convert -resize 120x120 sample.jpg sampleout.jpg
$ convert -scale 500 sample.jpg sampleout.jpg
```

### 画像を回転させたい
以下の様にして、時計回りに90度回転させる
```
$ convert -rotate 90 image_pre.png image_after.png
```

### 画像の切り出しを行いたい
画像を切り出したい
```
$ convert -crop 20x50+80+80 input.jpg output.jpg
```
これで、input.jpgの幅20・高さ50で横80・縦80からはじまる部分を切り取る事ができる。

### 画像一覧を作成する
例えば、test.jpg,test1.jpg,test2.jpgを縮小、まとめてall.jpgにしたい場合には以下のコマンドにより実現できる。
```
$ montage test.jpg test1.jpg test2.jpg all.jpg
```

### 画像の詳細な情報を取得する
fileやidentifyに画像を引数と与えて、簡単な情報を得ることもできるが、以下の様に identifyコマンドの-verboseオプションを利用して詳細を得ることもできる 以下に例を示す
```
$ identify -verbose sample.tif
TIFF Directory at offset 0x5b2008
Image Width: 1152 Image Length: 864
Bits/Sample: 16
Compression Scheme: None
Photometric Interpretation: RGB color
FillOrder: msb-to-lsb
Software: "@(#)ImageMagick 5.3.3 05/01/01 Q:16 http://www.imagemagick.org"
Document Name: "sample.tif"
Orientation: row 0 top, col 0 lhs
Samples/Pixel: 3
Rows/Strip: 1
Planar Configuration: single image plane
Image: sample.tif
Format: TIFF (Tagged Image File Format)
Geometry: 1152x864
Class: DirectClass
Type: true color
Depth: 8-bits
Colors: 66537
Filesize: 5839kb
Interlace: None
Background Color: white
Border Color: #dfdfdf
Matte Color: gray74
Compression: None
Software: @(#)ImageMagick 5.3.3 05/01/01 Q:16 http://www.imagemagick.org
Document: sample.tif
Signature: d104308db2ad6543b59e736975097d87
Tainted: False
User Time: 0.2u
Elapsed Time: 0:01
```
