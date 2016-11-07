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

### バックトレースから探す方法

httpdを引数に与えてrun -Xで起動するか、
```
gdb /usr/local/apache/sbin/httpd
(gdb) run -X

ここでブラウザなどからアクセス

(gdb) bt
```

それか以下のようにコマンドラインの方法もある
```
gdb /home/user/dev/php-snaps/sapi/cli/php 
(gdb) run /path/to/script.php
(gdb) bt
```

ここでさらに詳細を取得したい場合、一番最小のフレーム番号のexecuteに着目してここに移動する。upやdown, frameによって移動することができます。
```
(gdb) bt
#0  0x080ca21b in _efree (ptr=0xbfffdb9b) at zend_alloc.c:240
#1  0x080d691a in _zval_dtor (zvalue=0x8186b94) at zend_variables.c:44
#2  0x080cfab3 in _zval_ptr_dtor (zval_ptr=0xbfffdbfc) at zend_execute_API.c:274
#3  0x080f1cc4 in execute (op_array=0x816c670) at ./zend_execute.c:1605
#4  0x080f1e06 in execute (op_array=0x816c530) at ./zend_execute.c:1638
#5  0x080f1e06 in execute (op_array=0x816c278) at ./zend_execute.c:1638
#6  0x080f1e06 in execute (op_array=0x8166eec) at ./zend_execute.c:1638
#7  0x080d7b93 in zend_execute_scripts (type=8, retval=0x0, file_count=3) at zend.c:810
#8  0x0805ea75 in php_execute_script (primary_file=0xbffff650) at main.c:1310
#9  0x0805cdb3 in main (argc=2, argv=0xbffff6fc) at cgi_main.c:753
#10 0x400c91be in __libc_start_main (main=0x805c580 
, argc=2, ubp_av=0xbffff6fc,
               init=0x805b080 <_init>, fini=0x80f67b4 <_fini>, rtld_fini=0x4000ddd0 <_dl_fini>,
               stack_end=0xbffff6ec) at ../sysdeps/generic/libc-start.c:129
(gdb) frame 3
#3  0x080f1cc4 in execute (op_array=0x816c670) at ./zend_execute.c:1605
(gdb) print (char *)(executor_globals.function_state_ptr->function)->common.function_name        // セグフォを起こした関数名
$14 = 0x80fa6fa "pg_result_error"
(gdb) print (char *)executor_globals.active_op_array->function_name                              // 
$15 = 0x816cfc4 "result_error"
(gdb) print (char *)executor_globals.active_op_array->filename
$16 = 0x816afbc "/home/yohgaki/php/DEV/segfault.php"
(gdb) 
```


# 参考URL
- PHP公式ドキュメントによるgdbの使い方(ためになる)
 - https://bugs.php.net/bugs-generating-backtrace.php
