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

### 現在実行中のプロセスにアタッチしてライブラリトレースをする
```
$ ltrace -p <pid>
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

### fork()やclone()などで生成された子プロセスも表示する

たとえば、trafficserverの例で示すと
```
$ sudo ltrace -p <pid> -f
....
[pid 28042] ink_atomiclist_popall(0x1506eb00, 0, 0x1506eb20, 0xffffffff)                         = 0
[pid 28042] clock_gettime(0, 0x14e6bcc0, 1, 0)                                                   = 0
[pid 28042] pthread_mutex_lock(0x1506eb20, 0x17ee9784, 0x1b821e84, 1)                            = 0
[pid 28042] pthread_cond_timedwait(0x1506eb48, 0x1506eb20, 0x14e6bca0, 0x1506eb20 <unfinished ...>
[pid 28040] <... pthread_cond_timedwait resumed> )                                               = 110
[pid 28040] pthread_cond_timedwait(0x2c88348, 0x2c88320, 0x153f2c10, 0x2c88320)                  = 110
[pid 28040] pthread_cond_timedwait(0x2c88348, 0x2c88320, 0x153f2c10, 0x2c88320)                  = 110
[pid 28040] pthread_cond_timedwait(0x2c88348, 0x2c88320, 0x153f2c10, 0x2c88320)                  = 110
[pid 28043] <... pthread_cond_timedwait resumed> )                                               = 110
...
```

上記では、28042, 28040, 28043などのpidで稼働しているのがわかる。
プロセスを表示すると
```
$ ps auxww | grep -i traffic_server
root     28028  0.0  0.2 101072  2728 pts/1    S    22:21   0:00 sudo /usr/local/trafficserver/bin/traffic_server
nobody   28029  4.0  3.7 283532 38308 pts/1    Sl   22:21   0:58 /usr/local/trafficserver/bin/traffic_server
```

さらにスレッドもみると次のようになる。つまり、28040, 28042, 28043などはスレッドとして生成されたプロセスであるかわかる
```
$ ps -eL 28029 | grep -i traffic
28028 28028 pts/1    S      0:00 sudo /usr/local/trafficserver/bin/traffic_server
28029 28029 pts/1    Sl     0:06 /usr/local/trafficserver/bin/traffic_server
28029 28030 pts/1    Sl     0:00 /usr/local/trafficserver/bin/traffic_server
28029 28031 pts/1    Sl     0:00 /usr/local/trafficserver/bin/traffic_server
28029 28032 pts/1    Sl     0:00 /usr/local/trafficserver/bin/traffic_server
28029 28033 pts/1    Sl     0:06 /usr/local/trafficserver/bin/traffic_server
28029 28034 pts/1    Sl     0:06 /usr/local/trafficserver/bin/traffic_server
28029 28035 pts/1    Sl     0:06 /usr/local/trafficserver/bin/traffic_server
28029 28036 pts/1    Sl     0:06 /usr/local/trafficserver/bin/traffic_server
28029 28037 pts/1    Sl     0:06 /usr/local/trafficserver/bin/traffic_server
28029 28038 pts/1    Sl     0:06 /usr/local/trafficserver/bin/traffic_server
28029 28039 pts/1    Sl     0:06 /usr/local/trafficserver/bin/traffic_server
28029 28040 pts/1    Sl     0:06 /usr/local/trafficserver/bin/traffic_server
28029 28041 pts/1    Sl     0:00 /usr/local/trafficserver/bin/traffic_server
28029 28042 pts/1    Sl     0:00 /usr/local/trafficserver/bin/traffic_server
28029 28043 pts/1    Sl     0:00 /usr/local/trafficserver/bin/traffic_server
28029 28044 pts/1    Sl     0:00 /usr/local/trafficserver/bin/traffic_server
```

### フィルタリングオプションについて
x, e, lといった３種類のフィルタリングオプションがある。
```
-x is ´show me what calls these symbols (including local calls)´
-e is ´show me what calls these symbols (inter-library calls only)´
-l is ´show me what calls into this library´
```

xはローカルコール  
eは内部コールのみ  
lはライブラリ

### ライブラリで指定した情報だけ表示する

たとえば、hostnameでlddしてみて、/lib64/libnsl.so.1のライブラリ情報だけトレースしたいことがある。
```
$ ldd /usr/bin/hostname 
	linux-vdso.so.1 =>  (0x00007fff03dff000)
	libnsl.so.1 => /lib64/libnsl.so.1 (0x00000038aba00000)
	libc.so.6 => /lib64/libc.so.6 (0x0000003897a00000)
	/lib64/ld-linux-x86-64.so.2 (0x0000003897600000)
```

この場合には-lオプションの後にライブラリ名を指定する(ディレクトリのパスは指定すると正しく取得できないので指定しないこと)
```
$ sudo ltrace -l libnsl.so.1 hostname
localhost.localdomain
+++ exited (status 0) +++
[tsuyoshi@localhost memo]$ sudo ltrace -l libc.so.6 hostname
hostname->__libc_start_main(0x401150, 1, 0x7fff167fed98, 0x401d70 <unfinished ...>
hostname->getopt_long(1, 0x7fff167fed98, "aAdfbF:h?iIsVvy", 0x4027e0, nil)                       = -1
hostname->__errno_location()                                                                     = 0x7f5f3017d6c0
hostname->malloc(128)                                                                            = 0x1ca0010
hostname->gethostname("localhost.localdomain", 128)                                              = 0
hostname->memchr("localhost.localdomain", '\0', 128)                                             = 0x1ca0025
hostname->puts("localhost.localdomain"localhost.localdomain
)                                                          = 22
libnsl.so.1->__cxa_finalize(0x38abc15d50, 5, 0, 0)                                               = 0x3897db2b80
+++ exited (status 0) +++
```

### 特定の関数情報だけを取得する
```
$ ltrace -e "strcmp*" hostname
hostname->strcmp("hostname", "domainname")                                                       = 4
hostname->strcmp("hostname", "ypdomainname")                                                     = -17
hostname->strcmp("hostname", "nisdomainname")                                                    = -6
localhost.localdomain
+++ exited (status 0) +++
```

### ユーザー権限を指定する
-uオプションでその指定したユーザー権限でコマンドを実行した結果を出力します。
```
$ sudo ltrace -u tsuyoshi ls
```

### 引数に表示する長さを指定する
デフォルトで32となっているようだが、-sオプションで指定できる。
たとえば、3を指定した場合は引数が３文字表示され、その後３点リーダーになっていることが確認できる。
使う場面としてはもっと見たい場合に使うことが多そうだ
```
$ ltrace -s 3 hostname
__libc_start_main(0x401150, 1, 0x7fff0a8c32e8, 0x401d70 <unfinished ...>
rindex("hos"..., '/')                                                                            = nil
strcmp("hos"..., "dom"...)                                                                       = 4
strcmp("hos"..., "ypd"...)                                                                       = -17
strcmp("hos"..., "nis"...)                                                                       = -6
getopt_long(1, 0x7fff0a8c32e8, "aAd"..., 0x4027e0, nil)                                          = -1
__errno_location()                                                                               = 0x7f904de916c0
malloc(128)                                                                                      = 0x1b74010
gethostname("loc"..., 128)                                                                       = 0
memchr("loc"..., '\0', 128)                                                                      = 0x1b74025
puts("loc"...localhost.localdomain
)                                                                                   = 22
+++ exited (status 0) +++
```

### InstructionPointerのアドレスも表示する
左側にInstructionPointerへのアドレスも表示します。
```
$ sudo ltrace -i hostname
[0x4013d5] __libc_start_main(0x401150, 1, 0x7fffb7574088, 0x401d70 <unfinished ...>
[0x401173] rindex("hostname", '/')                                                               = nil
[0x4011ae] strcmp("hostname", "domainname")                                                      = 4
[0x401207] strcmp("hostname", "ypdomainname")                                                    = -17
[0x401218] strcmp("hostname", "nisdomainname")                                                   = -6
[0x4011cf] getopt_long(1, 0x7fffb7574088, "aAdfbF:h?iIsVvy", 0x4027e0, nil)                      = -1
[0x4015e3] __errno_location()                                                                    = 0x7fa0174726c0
[0x401648] malloc(128)                                                                           = 0x714010
[0x401611] gethostname("localhost.localdomain", 128)                                             = 0
[0x401625] memchr("localhost.localdomain", '\0', 128)                                            = 0x714025
[0x401987] puts("localhost.localdomain"localhost.localdomain
)                                                         = 22
[0xffffffffffffffff] +++ exited (status 0) +++
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

### 各トレースコールでの経過時間を表示する

```
$ ltrace -T hostname
__libc_start_main(0x401150, 1, 0x7fffebcd7f78, 0x401d70 <unfinished ...>
rindex("hostname", '/')                                                                          = nil <0.004076>
strcmp("hostname", "domainname")                                                                 = 4 <0.004934>
strcmp("hostname", "ypdomainname")                                                               = -17 <0.000455>
strcmp("hostname", "nisdomainname")                                                              = -6 <0.000652>
getopt_long(1, 0x7fffebcd7f78, "aAdfbF:h?iIsVvy", 0x4027e0, nil)                                 = -1 <0.000501>
__errno_location()                                                                               = 0x7fb4405316c0 <0.000117>
malloc(128)                                                                                      = 0x1f46010 <0.000236>
gethostname("localhost.localdomain", 128)                                                        = 0 <0.000147>
memchr("localhost.localdomain", '\0', 128)                                                       = 0x1f46025 <0.000965>
puts("localhost.localdomain"localhost.localdomain
)                                                                    = 22 <0.001108>
+++ exited (status 0) +++
```

### プログラム実行開始からの時間を表示する。
```
$ sudo ltrace -r hostname
  0.000000 __libc_start_main(0x401150, 1, 0x7ffff098c1f8, 0x401d70 <unfinished ...>
  0.003457 rindex("hostname", '/')                                                               = nil
  0.005304 strcmp("hostname", "domainname")                                                      = 4
  0.003444 strcmp("hostname", "ypdomainname")                                                    = -17
  0.001507 strcmp("hostname", "nisdomainname")                                                   = -6
  0.001140 getopt_long(1, 0x7ffff098c1f8, "aAdfbF:h?iIsVvy", 0x4027e0, nil)                      = -1
  0.001239 __errno_location()                                                                    = 0x7f85020ba6c0
  0.001845 malloc(128)                                                                           = 0xafc010
  0.000279 gethostname("localhost.localdomain", 128)                                             = 0
  0.000304 memchr("localhost.localdomain", '\0', 128)                                            = 0xafc025
  0.000134 puts("localhost.localdomain"localhost.localdomain
)                                                         = 22
  0.000254 +++ exited (status 0) +++
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

### ltraceプログラム自体のデバッグログを出力する
-Dの後にレベルを指定する。
```
$ ltrace -D 040 hostname
...
+++ exited (status 0) +++
DEBUG: proc.c:693: remove_proc(pid=28722)
DEBUG: proc.c:685: detach_task 28722 from leader 28722
DEBUG: handle_event.c:742: callstack_pop(pid=28722)
DEBUG: handle_event.c:742: callstack_pop(pid=28722)
DEBUG: dict.c:182: dict_apply_to_all()
DEBUG: dict.c:80: dict_clear()
DEBUG: events.c:144: next_event()
```

レベルに指定できる値は次の４つで040が最も出力量が多い
```
01     DEBUG_GENERAL.  Shows helpful progress information
010    DEBUG_EVENT.  Shows every event received by a traced program
020    DEBUG_PROCESS.  Shows every action ltrace carries upon a traced process
040    DEBUG_FUNCTION.  Shows every entry to internal functions
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

### ltrace.confをデフォルト以外のものに変更する
```
$  ltrace -F ltrace.conf hostname
```

# TODO
- manpageを元に調査したが、-L, -w, -x, -A <num>, -aなどのオプションについてはまだ未調査なので今後やりたい


# 参考URL
- Manpage of ltrace
  - https://linux.die.net/man/1/ltrace
- ltrace(1) Manpage
  - http://latrace.sourceforge.net/latrace.html
- ltrace公式サイト
  - http://www.ltrace.org/
  - https://anonscm.debian.org/gitweb/?p=collab-maint/ltrace.git
