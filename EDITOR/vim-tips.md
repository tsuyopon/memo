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

### 検索関連
```
/word                上から下へ "word" を検索する。
?word                下から上へ "word" を検索する。
/jo[ha]n             "john" もしくは "joan" を検索する。
/\<the               "the", "theatre" , "then" のいずれかを検索する。(theから始まる単語という事)
/the\>               "the" もしくは "breathe" を検索する。(theで終わる単語という事)
/\<the\>             "the" を検索する。
/\<....\>            4文字の単語を検索する。
/\<fred\>            "fred"を検索する。 "alfred" や "frederick" は当てはまらない。(原文のコマンドは // だったがミスかな？)
/fred\|joe           "fred" と "joe" を検索する。
/\<\d\d\d\d\>        4 桁の数字を検索する。
/^n{3}               空の3行を検索する。
:bufdo /searchstr/   全ての開いてるファイルから "searchstr" を検索する。
```

### 置換
```
%s/old/new/g            ファイル内の全ての "old" を "new" に置換する。
:%s/old/new/gc 	        ファイル内の全ての "old" を "new" に置換する。置換時に確認有り(コメント欄で間違い指摘有)
:2,35s/old/new/g        2行目から35行目までの "old" を "new" に置換する。
:5,$s/old/new/g         5行目からファイルの最後までの "old" を "new" に置換する。
:%s/^/hello/g           全ての行の先頭に "hello" を追加する。
:%s/$/Harry/g           全ての行の末尾に "Harry" を追加する。
:%s/onward/forward/gi   ファイル内の全ての "onward" を "forward" に置換する。"onward" は大文字小文字関係ない。(case unsensitive ってなんだ？)
:%s/ *$//g              全ての行末にある空白を削除する。(原文は "Delete all white space" で "全ての空白を削除する。"になるのだが・・・)
:g/string/d             "string" を含んでる行を削除する。
:v/string/d             "string" を含まない行を削除する。
:s/Bill/Steve/          現在の行で最初の "Bill" のみ "Steve" に置換する。
:s/Bill/Steve/g         現在の行の "Bill" を "Steve" に置換する。
:%s/Bill/Steve/g        このファイルの全ての "Bill" を "Steve" に置換する。
:%s/\r//g               改行コード "CR"(^M) を削除する。
:%s/\r/\r/g             Transform DOS carriage returns in returns (わかんなかった。)CRを現在vimで設定されている改行コードへ置換する。
:%s#<[^>]+>##g          タグに囲まれたテキストは残しつつ、HTMLタグを全て削除する。
:%s/^(.*)n1$/1/         同じ行が2回続いたら片方削除する。
Ctrl+a                  カーソル下の数字をインクリメントする。
Ctrl+x                  カーソル下の数字をデクリメントする。
ggVGg?                  テキストを Rot13 にする。
```

### Case
```
Vu                      現在の行の文字を小文字にする。
VU                      現在の行の文字を大文字にする。
g~~                     現在の行の文字の大文字小文字を反転させる。
vEU                     単語単位で大文字にする。
vE~                     単語単位で大文字小文字を反転させる。
ggguG                   全てのテキストを小文字にする。(原文では "uppercase" だがコマンド通りだと "lowercase"だろう。)
:set ignorecase         大文字小文字を区別しない。
:set smartcase          大文字を入力しない限り、大文字小文字を区別しない。
:%s/\<./\u&/g           全ての単語の先頭を大文字にする。
:%s/\<./\l&/g           全ての単語の先頭を小文字にする。
:%s/.*/\u&              全ての行の先頭を大文字にする。
:%s/.*/\l&              全ての行の先頭を小文字にする。
```

# 参考
- http://loumo.jp/wp/archive/20080701175525/
