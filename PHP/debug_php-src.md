# 概要
php-srcを使ったgdbデバッグの方法

# セットアップ
```
$ git clone --depth 1 https://github.com/php/php-src.git
$ cd php-src
$ ./buildconf 
$ ./configure --disable-all --enable-debug --prefix=/opt/php-src
$ make
```

インストールしなくても、これだけでもphpをgdbとして稼働させることができます。
```
$ gdb sapi/cli/php
```

prefixにインストールするにはmake installすればよい。
```
$ sudo make install
```

php-srcのルート直下には.gdbinitも存在します
```
$ ls .gdbinit 
.gdbinit
$ grep define .gdbinit | grep -v ____
define set_ts
define print_cvs
define dump_bt
define printzv
define print_const_table
define print_ht
define print_htptr
define print_htstr
define print_ft
define print_inh
define print_pi
define printzn
define printzops
define print_zstr
define zbacktrace
define lookup_root
```

# gdbを使う
abs関数の場合、zif_absという関数にブレークポイントを貼ります。
```
$ gdb sapi/cli/php
(gdb) b zif_abs
Breakpoint 1 at 0x5a0180: file /home/tsuyoshi/git/test/php-src/ext/standard/math.c, line 294.
(gdb) run -r 'echo abs("-123");'
Starting program: /home/tsuyoshi/git/test/php-src/sapi/cli/php -r 'echo abs("-123");'
[Thread debugging using libthread_db enabled]
Using host libthread_db library "/lib64/libthread_db.so.1".

Breakpoint 1, zif_abs (execute_data=0x7ffff661d090, return_value=0x7ffff661d080) at /home/tsuyoshi/git/test/php-src/ext/standard/math.c:294
294		ZEND_PARSE_PARAMETERS_START(1, 1)
Missing separate debuginfos, use: debuginfo-install glibc-2.17-196.el7.x86_64 nss-softokn-freebl-3.28.3-6.el7.x86_64
(gdb) bt
#0  zif_abs (execute_data=0x7ffff661d090, return_value=0x7ffff661d080) at /home/tsuyoshi/git/test/php-src/ext/standard/math.c:294
#1  0x00000000006f932a in ZEND_DO_ICALL_SPEC_RETVAL_USED_HANDLER () at /home/tsuyoshi/git/test/php-src/Zend/zend_vm_execute.h:618
#2  0x0000000000774cf4 in execute_ex (ex=0x7ffff661d030) at /home/tsuyoshi/git/test/php-src/Zend/zend_vm_execute.h:60024
#3  0x000000000077a0c2 in zend_execute (op_array=0x7ffff6680300, return_value=0x7fffffffcd90) at /home/tsuyoshi/git/test/php-src/Zend/zend_vm_execute.h:64050
#4  0x000000000068308b in zend_eval_stringl (str=0xc04d30 "echo abs(\"-123\");", str_len=17, retval_ptr=0x0, string_name=0x96f59c "Command line code")
    at /home/tsuyoshi/git/test/php-src/Zend/zend_execute_API.c:1054
#5  0x0000000000683234 in zend_eval_stringl_ex (str=0xc04d30 "echo abs(\"-123\");", str_len=17, retval_ptr=0x0, string_name=0x96f59c "Command line code", 
    handle_exceptions=1) at /home/tsuyoshi/git/test/php-src/Zend/zend_execute_API.c:1095
#6  0x00000000006832a9 in zend_eval_string_ex (str=0xc04d30 "echo abs(\"-123\");", retval_ptr=0x0, string_name=0x96f59c "Command line code", 
    handle_exceptions=1) at /home/tsuyoshi/git/test/php-src/Zend/zend_execute_API.c:1106
#7  0x000000000077c80c in do_cli (argc=3, argv=0xc04ca0) at /home/tsuyoshi/git/test/php-src/sapi/cli/php_cli.c:1042
#8  0x000000000077d598 in main (argc=3, argv=0xc04ca0) at /home/tsuyoshi/git/test/php-src/sapi/cli/php_cli.c:1404
(gdb) l
289	   Return the absolute value of the number */
290	PHP_FUNCTION(abs)
291	{
292		zval *value;
293	
294		ZEND_PARSE_PARAMETERS_START(1, 1)
295			Z_PARAM_ZVAL(value)
296		ZEND_PARSE_PARAMETERS_END();
297	
298		convert_scalar_to_number_ex(value);
(gdb) zbacktrace
Undefined command: "zbacktrace".  Try "help".
(gdb) source .gdbinit
(gdb) zbacktrace
[0x7ffff661d090] abs("-123") [internal function]
[0x7ffff661d030] (main) [internal function]
```

# 参考URL
- http://blog.anatoo.jp/entry/20111117/1321463886
  - こちらを参考にstrlen(zif_strlen)だとなぜかブレークポイントに引っかからなかった(要確認)
