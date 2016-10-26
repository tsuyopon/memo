# 概要
PHPのGDBデバッグ方法についてまとめておくページ
phpでデバッグするためには./configureのオプションに「--enable-debug」が指定される必要があります。

# 詳細
### PHPコマンドラインでのデバッグ
```
$ gdb
(gdb) file /usr/bin/php     // 実行ファイルを指定する
(gdb) run /home/down.php    // 起動スクリプトを指定する
Program received signal SIGSEGV, Segmentation fault.
0x21c03c2d in zif_down_method (ht=0, return_value=0x9baccc, return_value_ptr=0x0, this_ptr=0x0, return_value_used=0)

    at Down.cc:32
```

落ちた関数は
```
(gdb) print (char *)(executor_globals.function_state_ptr->function)->common.function_name
$1 = 0x21c2314a "down_method"
```

落ちたファイル名は
```
(gdb) print (char *)executor_globals.active_op_array->filename
$3 = 0x9c7ccc "/home/down.php"
```

落ちた行数は
```
print executor_globals.current_execute_data.opline->lineno
$5 = 2
```

詳しくは以下のYahooJapanBlogの記事がすごい役に立つ
http://techblog.yahoo.co.jp/tips/php/

これによってPHPエクステンションで以下の箇所が特定できるらしい
- 何のファイルの
- 何の関数の
- 何行目で落ちたのか


### apache経由でセグフォを調査する
あらかじめ特定の画面にアクセスするとセグフォが起きることがわかっているのであれば、
次のようgdbで実行ファイルを指定してgdbのインタープリタを起動してrun -Xでシングルプロセスとして起動させるとデバッグしやすくなります。
```
$ gdb /usr/local/bin/apache
(gdb) run -X
```

ここでリクエストを出すとSIGSETVを検出する。
```
Program received signal SIGSEGV, Segmentation fault.
0x21d94c2d in zif_down_method (ht=0, return_value=0x81010c, return_value_ptr=0x0, this_ptr=0x0, return_value_used=0)
    at Down.cc:32
```

ここでbtやbt fullなどでバックトレースを取得したり、先ほどの手順で行数などを求めることができる
```
(gdb) bt
```

