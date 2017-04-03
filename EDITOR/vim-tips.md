# 概要
vimに関する便利なTIPS的なことをまとめておく

### gfコマンド

たとえば、javascriptで
```
import 'path/xxxx'
```
などと記述されたpath/xxxxにカーソルを載せて、そのファイルを瞬時に開きたい場合には、

たとえば、上記ではxxxx.jsの想定だが拡張子は付与されていない。このような場合には次のvimをセットするとgfコマンド実行の際に自動的に読み込んでくれる。  
次の例ではjsの他にphpとincも含んだサンプルとなっている。
```
:set suffixesadd=.js,.php,.inc
```

またデフォルトだとgfはカレントディレクトリを元にして探すが、上記については/home/tsuyoshi配下も調べて欲しい場合には次を追加する。
```
:set path+=/home/tsuyoshi
```

新しいタブで開きたい場合には、
```
Ctrl - w, gf
```

元のファイルに戻る場合には
```
Ctrl - ^  
or
Ctrl - o
```

### プログラマが知っておくべき100のVimコマンド 
良記事
- http://loumo.jp/wp/archive/20080701175525/
