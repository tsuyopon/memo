# 概要
vimの折りたたみ関連に関する操作についてまとめておく


# 詳細

### 折りたたみのに関する設定を行いたい 
デフォルトの折り畳み方法は{{{ と }}}で囲まれた部分を折り畳みます。
```
set fdm=marker
```
とすると折り畳みが行われます。

### 折りたたみに関する操作 
```
zc/zC       折り畳みを閉じる。Cだと再帰的に閉じる
zo/zO       折り畳みを開く。Oだと再帰的に開く
zm/zM       全ての折り畳みを閉じる。mだと開いている一番下の折り畳みを閉じる
zR/zr       全ての折り畳みを開く。Rだと閉じている一番上の折り畳みが開く
za/zA       閉じている折り畳みは開く。開いている折り畳みは閉じる。
            Aだと全ての折りたたみに対してこの操作を行う。
zd/zD       カーソル位置の折り畳みを削除する。Dだと再帰的に削除する。
zE          そのファイルの全ての折り畳みを削除する。
zf          折り畳みを作成する
zi          折り畳みの有効、無効を切り替える
```

### 一般設定 
set foldmethodで指定できる折り畳み方法 
```
manual     手動でfold レベルをきめる
indent     インデントの数をfold レベルにする
expr       foldを定義する式を指定する
syntax     構文強調によりfoldを定義する
diff       変更されていないテキストをfoldとする
marker     テキスト中の印でfoldを定義する 
```


### sh などとしても折り畳みが適用されるようにしたい。 
以下のようなにシェルなどの場合でも折りたたみできるようにしたい
```
#{{{
#}}}
```

折り畳み設定はデフォルトでは// や /* */ などのC言語的なコメントにしか適用されない。 そこでシャープ(#)のみがコメントとするような言語では、以下の様にして設定を加える 必要がある。
```
set commentstring=;#%s        "HTML言語のコメント形式
set commentstring=/*%s*/      "C言語のコメント形式
set commentstring=\%%s        "texのコメント形式
set commentstring=            "コメントなし
```

以下の様にファイルにvimの設定を記述していると例えばPerlの様に#がコメントとなる記述で利用することができます。
```
# vim:tw=0:sw=4:ts=4:list:listchars=tab\:>-:foldmarker={{{,}}}:fdm=marker:commentstring=;#%s
```


フォルドレベルを指定する 
```
:set foldnestmax=3       fold のネストレベルを3にする
:set fdn=1               fold のネストレベルを1にする
```


# 言語別設定 
### PHPで折り畳みをするための設定 
いちいち以下の様にmarkerを記述しなくても、
```
// {{{
    .. この中に展開した際に表示される内容を記述
// }}}
```

下記設定を$HOME/.vimrc等に記述すればPHP構文を自動的に判定して折りたたみを行ってくれるようになります。
```
let php_folding=1
au Syntax php set fdm=syntax
```

### Perlの折り畳み関係の設定 
```
let perl_fold = 1
let perl_fold_blocks = 1
```

### Cなどで関数を開いたり閉じたりするための設定 
```
:syn region myFold start="{" end="}" transparent fold
:syn sync fromstart
:set foldmethod=syntax
```
