# 概要
PHPのGDBデバッグ方法についてまとめておくページ
phpでgdbデバッグするためには./configureのオプションに「--enable-debug」が指定される必要があります。

この辺の資料が素晴らしいクオリティで提供されているので読んでおくとよさそうです。
- https://net-newbie.com/phpext/b-gdb.html

# 詳細

### ブレークポイントを設定する
関数名でbreakpointを設定する方法がよくまだわかっていないので、ファイル名と行番号を指定することでbreakpointを設定することができます。
```
(gdb) b xxxxx.c:80
```

ネットからの情報によるとzif_をprefixに付与することでその関数に設定できるとのことです。(未確認)
```
(gdb) b zif_var_dump
Breakpoint 1 at 0x8429a4: file /usr/src/php/ext/standard/var.c, line 205.
```

例えば、次の様な感じでbreakポイントを設定して、直接runコマンドで呼び出す様なapache moduleを経由しない場合には次のようにデバッグできそうです。
```
(gdb) break zif_print_r
Breakpoint 1 at 0x8130d2e: file /home/dqneo/src/php-5.4.14/ext/standard/basic_functions.c, line 5495.

(gdb) run -r '$x = 123; print_r($x);'
Starting program: /home/dqneo/src/php-5.4.14/sapi/cli/php -r '$x = 123; print_r($x);'
[Thread debugging using libthread_db enabled]
[New Thread 0xb75436c0 (LWP 21957)]
[Switching to Thread 0xb75436c0 (LWP 21957)]

Breakpoint 1, zif_print_r (ht=1, return_value=0xb751ef48, return_value_ptr=0x0, this_ptr=0x0, return_value_used=0) at /home/dqneo/src/php-5.4.14/ext/standard/basic_functions.c:5495
5495            zend_bool do_return = 0;
```

- 参考URL
  - http://dqn.sakusakutto.jp/2013/04/php_gdb_zval_zvalue_value.html

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

### coreから調査を行う
```
$ gdb /usr/sbin/apache2 --core /var/tmp/core/core.<pid> --command /usr/local/src/php-5.5.5/.gdbinit
```

### 参照に便利そうなメモ
```
(gdb) set print pretty on
(gdb) zbacktrace
(gdb) print *executor_globals->active_op_array
(gdb) print sapi_globals->request_info
```

- sapi_globals
- executor_globals 	
- compiler_globals
- core_globals
- ps_globals

### .gdbinit
この辺にgdbinitが存在する。
- https://github.com/php/php-src/blob/master/.gdbinit
使い方はまた時間をとって抑えておきたい。

```
zbacktrace --- backtraceをみる
printzv    --- zvalの内容をみる
print_ht   --- HashTableの中身を見る。
```

実行中のグローバル変数をみる
```
(gdb) print_ht executor_globals->symbol_table->pListHead
```

セッションの中身をみる
```
(gdb) printzv ps_globals.http_session_vars
```


# 参考URL
- phpext 
  - https://net-newbie.com/phpext/b-gdb.html
- PHP公式ドキュメントによるgdbの使い方(ためになる)
  - https://bugs.php.net/bugs-generating-backtrace.php
- Debugging PHP segfault backtraces with `gdb`
  - http://www.robertames.com/blog.cgi/entries/debugging-php-segfault-backtraces-with-gdb.html
- How to set breakpoints in a php script using gdb
  - http://stackoverflow.com/questions/30664274/how-to-set-breakpoints-in-a-php-script-using-gdb
