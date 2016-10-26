
# トレースコマンドの種類
Linuxの場合、strace, ltrace, trace-cmd(ftrace)の３つが主にトレースとして利用されるようだ。
```
	starce:    システムコール
	ltrace:    ライブラリコール
	trace-cmd: カーネルコール
```

また、プロセスの関数スタックを表示するpstackについても説明する。

# ltraceコマンド

###  呼び出されているライブラリを確認する
```
$ ltrace /usr/bin/echo a
__libc_start_main(0x401290, 2, 0x7fff564d45f8, 0x403d50 <unfinished ...>
getenv("POSIXLY_CORRECT")                                                                        = nil
strrchr("/usr/bin/echo", '/')                                                                    = "/echo"
setlocale(LC_ALL, "")                                                                            = "C"
bindtextdomain("coreutils", "/usr/share/locale")                                                 = "/usr/share/locale"
textdomain("coreutils")                                                                          = "coreutils"
__cxa_atexit(0x401cb0, 0, 0, 0x736c6974756572)                                                   = 0
strcmp("a", "--help")                                                                            = 52
strcmp("a", "--version")                                                                         = 52
fputs_unlocked(0x7fff564d5687, 0x3d549b1260, 0, 45)                                              = 1
__overflow(0x3d549b1260, 10, 0x7fa264579001, 1024a
)                                               = 10
exit(0 <unfinished ...>
__fpending(0x3d549b1260, 0, 0x3d549b1f70, 4)                                                     = 0
fileno(0x3d549b1260)                                                                             = 1
__freading(0x3d549b1260, 0, 0x3d549b1f70, 4)                                                     = 0
__freading(0x3d549b1260, 0, 2052, 4)                                                             = 0
fflush(0x3d549b1260)                                                                             = 0
fclose(0x3d549b1260)                                                                             = 0
__fpending(0x3d549b1180, 0, 0x3d549b2a00, 0xfbad000c)                                            = 0
fileno(0x3d549b1180)                                                                             = 2
__freading(0x3d549b1180, 0, 0x3d549b2a00, 0xfbad000c)                                            = 0
__freading(0x3d549b1180, 0, 4, 0xfbad000c)                                                       = 0
fflush(0x3d549b1180)                                                                             = 0
fclose(0x3d549b1180)                                                                             = 0
+++ exited (status 0) +++
```

# trace-cmd(ftrace)の使い方

デフォルトではインストールされていないのでインストールが必要かもしれない。
```
$ yum install trace-cmd
```

例えば、wコマンドのカーネルコールを取得する場合
```
$ sudo trace-cmd record -p function_graph w
$ trace-cmd report | less
```
で木構造でカーネルコールを閲覧することができます。

# 特定のバイナリの関数スタックを調査する(pstack)

たとえば、特定のバイナリのスタックを見たい場合pidをまずは調べる
```
root     15985  0.0  0.5 402228  5924 ?        Sl   16:26   0:00 /usr/libexec/packagekitd
```

sudo権限でpidを引数としてpstackコマンドを実行する。
バックトレースを取得することができる。stripされている箇所は??と表示されるようだ。
```
$ sudo pstack 15985
Thread 3 (Thread 0x7fdd1b59b700 (LWP 15986)):
#0  0x0000003897ae8bdf in poll () from /lib64/libc.so.6
#1  0x0000003899a47984 in ?? () from /lib64/libglib-2.0.so.0
#2  0x0000003899a47aa4 in g_main_context_iteration () from /lib64/libglib-2.0.so.0
#3  0x0000003899a47af1 in ?? () from /lib64/libglib-2.0.so.0
#4  0x0000003899a6a315 in ?? () from /lib64/libglib-2.0.so.0
#5  0x0000003897e07d14 in start_thread () from /lib64/libpthread.so.0
#6  0x0000003897af168d in clone () from /lib64/libc.so.6
Thread 2 (Thread 0x7fdd1a599700 (LWP 15988)):
#0  0x0000003897ae8bdf in poll () from /lib64/libc.so.6
#1  0x0000003899a47984 in ?? () from /lib64/libglib-2.0.so.0
#2  0x0000003899a47de2 in g_main_loop_run () from /lib64/libglib-2.0.so.0
#3  0x000000389b6c9126 in ?? () from /lib64/libgio-2.0.so.0
#4  0x0000003899a6a315 in ?? () from /lib64/libglib-2.0.so.0
#5  0x0000003897e07d14 in start_thread () from /lib64/libpthread.so.0
#6  0x0000003897af168d in clone () from /lib64/libc.so.6
Thread 1 (Thread 0x7fdd1b59c800 (LWP 15985)):
#0  0x0000003897ae8bdf in poll () from /lib64/libc.so.6
#1  0x0000003899a47984 in ?? () from /lib64/libglib-2.0.so.0
#2  0x0000003899a47de2 in g_main_loop_run () from /lib64/libglib-2.0.so.0
#3  0x000000000040d2df in main ()
```
