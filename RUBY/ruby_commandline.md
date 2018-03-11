# 概要
rubyのcommandline関連について

# 詳細
### rubyのバージョンが知りたい
```
$ ruby -v
ruby 1.8.6 (2007-09-24 patchlevel 111) [i486-linux]
```

### 実行するディレクトリを指定する
```
$ ruby -C/home/tsuyoshi/ sample.rb
```
この場合には/home/tsuyoshi/というディレクトリに移動してからsample.rbを実行する

### 構文チェックしたい
```
$ ruby -c example.rb
```
問題なければ「Syntax OK」と表示される。

### コマンドラインでrubyを実行したい
```
$ ruby -e "print('Hello, World')"
Hello, World
```

### ロードパスを指定して実行する
```
$ ruby -I /home/tsuyoshi/lib/ruby/ hoge.rb
```
この場合には、/home/tsuyoshi/lib/ruby/が$LOAD_PATHに追加されます。 これにより、

```
require "/home/tsuyoshi/lib/ruby/testtest'
```
と記述するのを

```
require "testtest"
```
と省略できます

### デバッグモードで実行する
$DEBUGというグローバル変数をTRUEにします。dオプションを付与します。
```
$ruby -d example.rb
```
これにより、 if $DEBUG then 〜〜 end とある箇所を実行してくれるようになります。

### 実行環境の文字コードを宣言する
```
UTF-8なら       「-Ku」
EUC-JPなら      「-Ke」
Shift-Jisなら   「-Ks」
```

### 標準のlib/以外の場所からもライブラリを検索できます
以下の環境変数があります
```
RUBYLIB=$RUBYLIB:/var/lib/gems/1.8/lib
```

### いちいちrubyのオプションを指定しなくても、デフォルトオプションとさせたい
以下の環境変数があります
```
RUBYOPT="-Ks -rkconv -rubygems"
```
