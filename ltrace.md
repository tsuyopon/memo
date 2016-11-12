# ltrace
straceはシステムコールのトレースですが、ltraceはライブラリコールのトレースを行う事が可能です。
設定ファイルとして/etc/ltrace.confや$HOME/.ltrace.confがあります。

### ライブラリトレースをしてみる
引数に実行コマンドを与えるだけです。通常はこの使い方だけで事足ります。
```
$ ltrace hostname
__libc_start_main(0x401150, 1, 0x7fffda688098, 0x401d70 <unfinished ...>
rindex("hostname", '/')                                                                          = nil
strcmp("hostname", "domainname")                                                                 = 4
strcmp("hostname", "ypdomainname")                                                               = -17
strcmp("hostname", "nisdomainname")                                                              = -6
getopt_long(1, 0x7fffda688098, "aAdfbF:h?iIsVvy", 0x4027e0, nil)                                 = -1
__errno_location()                                                                               = 0x7fb2d24516c0
malloc(128)                                                                                      = 0x1342010
gethostname("localhost.localdomain", 128)                                                        = 0
memchr("localhost.localdomain", '\0', 128)                                                       = 0x1342025
puts("localhost.localdomain"localhost.localdomain
)                                                                    = 22
+++ exited (status 0) +++
```


### システムコールも一緒にトレースする
-Sオプションを付加すればstrace情報も表示します。
先ほどの情報の他にSYS_xxxxといったシステムコール情報も付加されていることがわかります。
```
$ ltrace -S hostname 
SYS_brk(0)                                                                                       = 0x1142000
SYS_mmap(0, 4096, 3, 34)                                                                         = 0x7f1cd61eb000
SYS_access("/etc/ld.so.preload", 04)                                                             = -2
SYS_open("/etc/ld.so.cache", 524288, 01)                                                         = 3
SYS_fstat(3, 0x7fffde3a3bb0)                                                                     = 0
SYS_mmap(0, 0x14107, 1, 2)                                                                       = 0x7f1cd61d6000
...
```

### 呼び出し関係を階層構造で表示する
-nオプションの後に数を指定すると関数呼び出しの関係を階層構造で出力します
ここで指定される数は階層があった場合にどれだけの感覚を開けるかのスペース数を表します。
-n 5とした場合は5つ分のスペースが空いていることがわかります。
```
$ ltrace -n 5 hostname 
__libc_start_main(0x401150, 1, 0x7fff71717378, 0x401d70 <unfinished ...>
     rindex("hostname", '/')                                                                     = nil
     strcmp("hostname", "domainname")                                                            = 4
     strcmp("hostname", "ypdomainname")                                                          = -17
     strcmp("hostname", "nisdomainname")                                                         = -6
     getopt_long(1, 0x7fff71717378, "aAdfbF:h?iIsVvy", 0x4027e0, nil)                            = -1
     __errno_location()                                                                          = 0x7fe853d706c0
     malloc(128)                                                                                 = 0xa85010
     gethostname("localhost.localdomain", 128)                                                   = 0
     memchr("localhost.localdomain", '\0', 128)                                                  = 0xa85025
     puts("localhost.localdomain"localhost.localdomain
)                                                               = 22
+++ exited (status 0) +++
```

### プログラム経過時間を出力する
-tや-tt, -tttのオプションがあります。画面左側に時刻の経過時間を付与します。

tの場合には次の通り
```
$ ltrace -t ls
...
21:57:56 fflush(0x3897db1180)                                                                    = 0
21:57:56 fclose(0x3897db1180)                                                                    = 0
21:57:56 +++ exited (status 0) +++
```

ttの場合には次の通り。μs単位で表示してくれるようでパフォーマンスチューニング用途などに利用できそうだ
```
$ ltrace -tt ls
...
21:56:41.063297 __freading(0x3897db1180, 0, 4, 0xfbad000c)                                       = 0
21:56:41.064225 fflush(0x3897db1180)                                                             = 0
21:56:41.064910 fclose(0x3897db1180)                                                             = 0
21:56:41.066930 +++ exited (status 0) +++
```

tttの場合の出力は次の通り
```
$ ltrace -ttt ls
...
1478956653.617763 fflush(0x3897db1180)                                                           = 0
1478956653.618234 fclose(0x3897db1180)                                                           = 0
1478956653.620122 +++ exited (status 0) +++
```

### 統計情報を表示する
```
$ ltrace -c ls
APACHE	DB	  GDB		 LINUX	MYSQL.md     OTHERS.md	SSL.md		     WANTTODO	curl.md    iOSAppli   nc.md	  shellscript.md  top.md
CPP	DEVTOOLS  Javascript.md  LOG	Makefile.md  PERL	TreeStructAlgorithm  XV6kernel	git.md	   lsof.md    netstat.md  tcpdump.md	  yum.md
CPU	EDITOR	  Kernel	 MISC	OS	     README.md	VirtualBox	     autotools	golang.md  ltrace.md  sed.md	  tmux.md
% time     seconds  usecs/call     calls      function
------ ----------- ----------- --------- --------------------
 20.18    0.020081          73       274 __errno_location
 19.63    0.019534         217        90 __overflow
 18.87    0.018779          82       228 __ctype_get_mb_cur_max
 12.69    0.012625          80       157 strcoll
  8.15    0.008115          71       114 __ctype_b_loc
  4.19    0.004165          69        60 memcpy
  3.96    0.003940          91        43 readdir
  3.13    0.003116          79        39 strlen
  3.07    0.003050          67        45 malloc
  2.77    0.002756          72        38 fwrite_unlocked
  0.66    0.000658         658         1 isatty
  0.51    0.000503          62         8 getenv
  0.35    0.000350          87         4 free
  0.32    0.000316          79         4 __freading
  0.19    0.000189          94         2 fclose
  0.15    0.000150          75         2 fileno
  0.15    0.000148          74         2 fflush
  0.15    0.000147          73         2 __fpending
  0.10    0.000096          96         1 setlocale
  0.09    0.000087          87         1 opendir
  0.09    0.000087          87         1 ioctl
  0.09    0.000085          85         1 closedir
  0.08    0.000083          83         1 strrchr
  0.08    0.000080          80         1 bindtextdomain
  0.08    0.000079          79         1 textdomain
  0.08    0.000079          79         1 getopt_long
  0.08    0.000075          75         1 __cxa_atexit
  0.07    0.000069          69         1 realloc
  0.07    0.000068          68         1 _setjmp
------ ----------- ----------- --------- --------------------
100.00    0.099510                  1124 total
```


### ファイルを指定して保存する
-oオプションを指定すると出力先を指定することができます。
```
$  ltrace -o stracelog.txt ls
```

ここから下は実際に試せていない。。。
### シグナルで呼ばれたトレースコールの表示をdisabledにする
```
$  ltrace -b cmd
```

### C++でマングリングされている表示のような場合にでマングリングする
```
$  ltrace -C cmd
```

# TODO
この辺を全体的に使ってみるといいかも
- http://latrace.sourceforge.net/latrace.html


# 参考URL
- Manpage of ltrace
 - https://linux.die.net/man/1/ltrace
- ltrace(1) Manpage
 - http://latrace.sourceforge.net/latrace.html
- ltrace公式サイト
 - http://www.ltrace.org/
 - https://anonscm.debian.org/gitweb/?p=collab-maint/ltrace.git
