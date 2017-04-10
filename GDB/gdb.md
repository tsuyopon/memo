# 概要
GDB基本事項についてまとめておくページです
以下の日本語ドキュメントも参考にすること
- [http://www.asahi-net.or.jp/~wg5k-ickw/html/online/gdb-5.0/gdb-ja_toc.html]

以下の２つも読んでまとめておく
- [http://www.keshi.org/blog/2006/03/gdb_hacks_hardware.html]
- [http://d.hatena.ne.jp/hayamiz/20090930/1254323169]

## 基本操作

### ビルドについて
ファイル名、行番号などの情報は-gオプションを付与します。
マクロはgdbでは使えないのであらかじめ展開しておきたい場合には-gの代わりに-g3を付与します。
コンパイラによる最適化を抑制したいのであれば-O0を付与しましょう。

-gや-g3が付与されるとデバッグ情報が付与されます。この情報はfileコマンドで確認できます。
バイナリを計量にするためにこの情報を除去したければstripコマンドを使うことができます。

### 起動中のプロセスにgdbからアタッチする
```
$ ps auxww | grep -i httpd
$ sudo gdb /usr/local/apache2/bin/httpd
(gdb) attach <pid>
// 何かをする
(gdb) detach          // デバッグ終了したらデタッチします。
```

attachした状態にてrunやquitを実行するとプロセスが停止してしまうらしいので注意が必要とのことです。  
  
(参考)実行中のmemcachedプロセスをGDBでdebugする方法   
- http://kotakanbe.blogspot.jp/2011/02/memcachedgdbdebug.html

### gdb基本オプション
```
	 コマンド	省略形	効果
	 run        r       デバッグ対象プログラムを実行する
	 backtrace  bt	    バックトレースを表示する(where, info stackはbacktraceの別名です)
	 frame N    f	    フレームNに移動する
	 list       l       現在の関数のソースコードを表示する
	 print EXPR p       式EXPRの値を表示する
	 continue   c       続きを実行する
	 quit       q       gdbを終了する
```

### 起動
```
$ gdb
(gdb) file /usr/local/apache2/bin/httpd
(gdb) run -X                              // apacheの場合は-Xオプションでシングルプロセスとして起動するのでデバッグで便利
```

引数を指定する例
```
(gdb) run -s -1 -c -5
```

### ブレークポイントを設定する
```
(gdb) b 行番号              // 例: b 16
(gdb) b 関数名              // 例: b log4cpp::StringUtil::vform
(gdb) b ファイル名:行番号   // 例: b test.cc:207
(gdb) b ファイル名:関数名   // 例: b http_request.c:ap_internal_request
(gdb) b +オフセット         // 例: b *main+100
(gdb) b -オフセット         
(gdb) b *アドレス           // 例: b *0x00007ffff7dc0a0e
```

もしC++でオーバーライドされた関数のうち１つを特定したブレークポイントを貼りたい場合には型を指定する
```
(gdb) break TestClass::testFunc(int) 
```

条件付きのbreakポイントも設定できる。
```
(gdb) b 19 if i == j           // 19行目でiとjが等しかったらbreakする
```

上記は以下と等価です。
```
(gdb) break 19                 // 19行目にbreakポイントを設定する
(gdb) condition <Bnum> i == j  // <Bnum>はinfo bで表示される番号です
```

breakポイントに到達しても何回か飛ばしたい場合
```
(gdb) break 19                 // 19行目にbreakポイントを設定する
(gdb) ignore <Bnum> <num>      // <Bnum>はinfo bで表示される番号。<num>は無視する回数を表します。
```

### 設定してあるブレークポイントを取得する
info breakpoints(省略形はinfo b)で設定してあるブレークポイント一覧を表示します
```
(gdb) info breakpoints
Num     Type           Disp Enb Address            What
1       breakpoint     keep y   0x000000000043989d in ap_process_request_internal at request.c:104
	breakpoint already hit 1 time
```

### breakポイントを削除する。
全てのbreakポイントを削除する場合には引数を指定しない
```
(gdb) delete
```

info breakで表示される番号を指定してbreakポイントを削除する場合
```
(gdb) info break
(gdb) delete <num>
```

### breakするたびにコマンドを設定する場合
例えばループして毎回特定の変数の値を表示する場合などに便利
```
(gdb) commands <Bnum>
> print i
> end
```

### 特定の値が変化するたびにbreakする
```
(gdb) p &(foo->bar)
$100 = (MyData *)0x80cc978
(gdb) watch *((MyData*)0x80cc978)
Hardware watchpoint 7: *(MyData *) 135051400
```

watchコマンドでは書き込みしか監視できませんが、rwatchを使うと変数の読み込みに対して監視できます。
以下はwatchvarが読み込まれた際にプログラムが一時停止します。
```
(gdb) rwatch watchvar
```

読み込みと書き込み両方を監視したい場合にはawatchを使います。
これを使うと変数が読み込まれた、変数が変化したことを監視できます。
```
(gdb) awatch watchvar
```

### breakポイントの一時的な無効化を行う

info bすると「Enb」という項目でEnable状態かどうか確認することができます。
```
(gdb) b ap_process_request
Breakpoint 1 at 0x7f9b5c1e1510: file /usr/src/debug/httpd-2.2.23/modules/http/http_request.c, line 259.
(gdb) info b
Num     Type           Disp Enb Address            What
1       breakpoint     keep y   0x00007f9b5c1e1510 in ap_process_request at /usr/src/debug/httpd-2.2.23/modules/http/http_request.c:259
(gdb) disable 1
(gdb) info b
Num     Type           Disp Enb Address            What
1       breakpoint     keep n   0x00007f9b5c1e1510 in ap_process_request at /usr/src/debug/httpd-2.2.23/modules/http/http_request.c:259
(gdb) enable 1
(gdb) info b
Num     Type           Disp Enb Address            What
1       breakpoint     keep y   0x00007f9b5c1e1510 in ap_process_request at /usr/src/debug/httpd-2.2.23/modules/http/http_request.c:259
```

### 一度だけ有効なテンポラリのブレークポイントを設定する
tbreak(Temporary Break)を利用する。使い方はbreakと同じです。

#### 特定のアドレスに到達するまで処理を続ける
以下、サンプル
```
(gdb) until *main+43
(gdb) u *main+43
```

### プログラムを進める
```
continue:   breakポイントを設定したが実行継続する場合
next:       次の関数を実行する
step:       次の関数を実行する。nextと異なり関数の中にも入っていく
nexti(ni):  サブルーチンがコールされた場合、サブルーチンからリターンするまで実行を継続します。
stepi(si):  アセンブリレベルで１つずつ実行を行う
finish:     関数を抜けるまで処理を続ける
```

nextやstepを一気に100回実行したいと行った場合には
```
n 100
s 100
```
とすればよい

untilコマンドというのもあるがここでは紹介しない

### リンクされた関数を実行する
プログラムからリンクされた関数を呼び出すことができます。
```
(gdb) call hogehoge()
```

coreを吐くために終了させることなども可能です
```
(gdb) call abort()
```

### いじっている周辺のソースコードを取得
```
(gdb) list
109	        core_dir_config *d;
110	        d = ap_get_module_config(r->per_dir_config, &core_module);
111	        if (d->allow_encoded_slashes) {
112	            access_status = ap_unescape_url_keep2f_ex(r->parsed_uri.path, d->decode_encoded_slashes);
113	        }
114	        else {
115	            access_status = ap_unescape_url(r->parsed_uri.path);
116	        }
117	        if (access_status) {
118	            if (access_status == HTTP_NOT_FOUND) {
```

### 変数の型を取得する

```
(gdb) whatis *d
type = int

(gdb) whatis myfile
type = char [4097]
```

### シェルを実行する
```
(gdb) shell ls
```

### print書式
```
(gdb) p 変数            // (例): p str
(gdb) p *ポインタ変数   // (例): p *r
(gdb) p &アドレス変数   // (例): p &r
```

> o: 8進数、 x: 16進数、 t: 2進数、 f: 浮動小数点表示
> d: 符号付き10進表示、 u: 符号なし10進表示、 c: 文字表示、 a:アドレス

上記の書式を使って変数の値を調べてみるサンプル
```
(gdb) p counter        // 10進数
$1 = 1024
(gdb) p/o counter      // 8進数(octal)
$2 = 02000
(gdb) p/x counter      // 16進数(hex)
$3 = 0x400
(gdb) p/t counter      // 2進数(binary)
$4 = 10000000000
(gdb) p/a counter      // アドレス(address)
$5 = 0x400
(gdb) p/c counter      // 文字表示(char)
$6 = 0 '¥000'
(gdb) p/d counter      // 符号付き10進数(decimal)
$7 = 1024
(gdb) p/u counter      // 符号無し10真数(unsigned decimal)
$8 = 1024
(gdb) p &counter
$9 = (int *) 0x7fffffffe218
(gdb) p *counter
Cannot access memory at address 0x400
```

### 配列
```
(gdb) p myIntArray
$46 = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}
(gdb) pt myIntArray
type = int [10]
(gdb) pt myIntArray[3]
type = int
(gdb) p myIntArray[3]
$48 = 3
(gdb) p myIntArray[3]@5
$49 = {3, 4, 5, 6, 7}
(gdb) p myIntArray[3]@11
$54 = {3, 4, 5, 6, 7, 8, 9, 10, 1107293224, 1079194419, -1947051841}
(gdb) p myStruct
$2 = {name = 0x40014978 "HogeFuga", EyeColour = 1}
(gdb) print myStruct.name
$6 = 0x40014978 "HogeFuga"
```

### 処理するたびに毎回特定の値を表示したい場合
displayコマンドにarrayという引数を与えるとarrayという変数を毎回nextやstep等の実行した後に実行してくれます。
```
(gdb) display array
1: array = {-8528, 32767, 0, 0}
(gdb) next
10     printarray(&array[0], 4);
1: array = {4, 1, 3, 2}
```

info displayで設定されているdisplayを表示して、解除する場合にはundisplayで解除できます。
```
(gdb) display a1
1: a1 = 10
(gdb) display a2
2: a2 = 10
(gdb) info display
Auto-display expressions now in effect:
Num Enb Expression
2:   y  a2
1:   y  a1
(gdb) undisplay 1
(gdb) info display
Auto-display expressions now in effect:
Num Enb Expression
2:   y  a2
(gdb) undisplay 2
(gdb) info display
There are no auto-display expressions now.
```

### setを使う
構造体を見やすくする
```
(gdb) set print pretty on
(gdb) set listsize 1000
```

printの表示文字数をセットする
```
(gdb) set print elements 300
```

今セットされているものをみる
```
(gdb) info set
```

セットできるもの一覧を表示する
```
(gdb) help set
```

特定の変数をセットする
```
(gdb) set $eax=42
```

なお、"set {書き込むデータの型}アドレス = 書き込むデータ"とコマンドを実行すると、任意アドレスのデータを変更することができます。
```
(gdb) set {int}0x280d36e8 = 0x000000b8
(gdb) set {char}0x280d36ec = 0x00
(gdb) set {short}0x280d36ed = 0x9090
(gdb) set {short}0x280d36ef = 0x9090 
```


構造体を表示する
```
(gdb) ptype   // ptとも略せる
type = int
```

変数の値を設定する
```
(gdb) p var=100
```

配列を空に書き換える
```
(gdb) p myary="\0" 
```


### スタック一覧を取得する
特定のbreakポイントに到達した際に「info stack」すると
```
(gdb) b ap_update_child_status
Breakpoint 2 at 0x7f9b5c1c4430: file /usr/src/debug/httpd-2.2.23/server/scoreboard.c, line 476.
// ここでrequesetしてbreakするまで待つ
(gdb) info stack
#0  0x00007f9b5a4fae47 in accept4 () from /lib64/libc.so.6
#1  0x00007f9b5abfda98 in apr_socket_accept (new=new@entry=0x7fff188c8508, sock=0x7f9b5ce9eaf8, connection_context=0x7f9b5d1a0c88)
    at network_io/unix/sockets.c:210
#2  0x00007f9b5c1e848d in unixd_accept (accepted=0x7fff188c8560, lr=<optimized out>, ptrans=<optimized out>)
    at /usr/src/debug/httpd-2.2.23/os/unix/unixd.c:523
#3  0x00007f9b5c1e621a in child_main (child_num_arg=child_num_arg@entry=0) at /usr/src/debug/httpd-2.2.23/server/mpm/prefork/prefork.c:648
#4  0x00007f9b5c1e6992 in make_child (slot=0, s=0x7f9b5cea5860) at /usr/src/debug/httpd-2.2.23/server/mpm/prefork/prefork.c:768
#5  make_child (s=0x7f9b5cea5860, slot=0) at /usr/src/debug/httpd-2.2.23/server/mpm/prefork/prefork.c:696
#6  0x00007f9b5c1e6a36 in startup_children (number_to_start=1) at /usr/src/debug/httpd-2.2.23/server/mpm/prefork/prefork.c:786
#7  0x00007f9b5c1e7395 in ap_mpm_run (_pconf=_pconf@entry=0x7f9b5cea0138, plog=<optimized out>, s=s@entry=0x7f9b5cea5860)
    at /usr/src/debug/httpd-2.2.23/server/mpm/prefork/prefork.c:1007
#8  0x00007f9b5c1be887 in main (argc=3, argv=0x7fff188c8968) at /usr/src/debug/httpd-2.2.23/server/main.c:753
```

なお、where, info stackというのは実はbacktraceにaliasとなっているようです


### ローカル変数を取得する
特にローカル変数が存在しない行だと以下のように表示される
```
(gdb) info locals
No symbol table info available.
```

ローカル変数が存在する行だと以下のように表示される
```
(gdb) info locals
s = <optimized out>
sa = {pool = 0x7f9b5d1aeeb0, hostname = 0x7f9b5d1a0ef0 "\210\f\032]\233\177", servname = 0x64 <Address 0x64 out of bounds>, port = 17982, 
  family = 32667, salen = 28, ipaddr_len = 32667, addr_str_len = 100, ipaddr_ptr = 0x7f9b5d1a0ef0, next = 0x7f9b5c1c6f58, sa = {sin = {
      sin_family = 10, sin_port = 25053, sin_addr = {s_addr = 0}, sin_zero = "\000\000\000\000\000\000\000"}, sin6 = {sin6_family = 10, 
      sin6_port = 25053, sin6_flowinfo = 0, sin6_addr = {__in6_u = {
          __u6_addr8 = "\000\000\000\000\000\000\000\000\000\000\377\377\n\000\002\002", __u6_addr16 = {0, 0, 0, 0, 0, 65535, 10, 514}, 
          __u6_addr32 = {0, 0, 4294901760, 33685514}}}, sin6_scope_id = 0}, sas = {ss_family = 10, __ss_align = 0, 
      __ss_padding = "\000\000\377\377\n\000\002\002\000\000\000\000\000\000\000\000\001\000\000\000\000\000\000\000\070\356\032]\233\177\000\000\000\r\032]\233\177\000\000\360\016\032]\233\177", '\000' <repeats 11 times>"\360, \177\263\006\213\031\271\070\356\032]\233\177\000\000\030\256\032]\233\177\000\000x\362?\\\233\177\000\000\020\024@\\\233\177\000\000\360\016\032]\233\177\000\000L\210\277Z\233\177\000"}}}
```

複数あれば以下のように出力されたりもする
```
(gdb) info locals
a1 = 10
a2 = 10
a3 = 10
a4 = 10
a5 = 10
a6 = 0
```
別の関数にcontinueしてinfo localsすると、次の関数のローカル変数を表示する。
```
(gdb) c
Continuing.

Breakpoint 2, sub () at stack.c:4
4		int b1 = 11;
(gdb) info locals
b1 = 0
b2 = 0
b3 = 32767
b4 = 1606417344
```
上記のように変数値がぐちゃぐちゃな値をとる場合には値が設定されていない状態であることがわかる

### 関数の引数を取得する
```
(gdb) info args
new = 0x7fff188c8508
sock = 0x7f9b5ce9eaf8
connection_context = 0x7f9b5d1a0c88
```

### 環境変数を設定する
```
(gdb) set environment LD_LIBRARY_PATH=/usr/lib/debug
```

## TIPS関連

### IntelやATT形式にシンタックスに変更する。

Intelの場合には以下のようにします。
```
(gdb) set disassembly-flavor intel          // set dis intelでもOK
(gdb) disas
Dump of assembler code for function main:
   0x00000000004004dc <+0>:	push   rbp
   0x00000000004004dd <+1>:	mov    rbp,rsp
=> 0x00000000004004e0 <+4>:	mov    edi,0x4005b0
   0x00000000004004e5 <+9>:	mov    eax,0x0
   0x00000000004004ea <+14>:	call   0x4003b0 <printf@plt>
   0x00000000004004ef <+19>:	pop    rbp
   0x00000000004004f0 <+20>:	ret    
End of assembler dump.
```

ATT形式の場合には以下で変更することができます。
```
(gdb) set disassembly-flavor att
(gdb) disas
Dump of assembler code for function main:
   0x00000000004004dc <+0>:	push   %rbp
   0x00000000004004dd <+1>:	mov    %rsp,%rbp
=> 0x00000000004004e0 <+4>:	mov    $0x4005b0,%edi
   0x00000000004004e5 <+9>:	mov    $0x0,%eax
   0x00000000004004ea <+14>:	callq  0x4003b0 <printf@plt>
   0x00000000004004ef <+19>:	pop    %rbp
   0x00000000004004f0 <+20>:	retq   
End of assembler dump.
```

### 特定のシステムコール呼び出し時にbreakする
```
(gdb) catch syscall write
```

### 逆アセンブラを行う

現在のステップで位置する関数のアセンブラを表示するには以下のようにします。
```
(gdb) disassemble
Dump of assembler code for function main:
   0x00000000004255de <+0>:	push   %rbp
   0x00000000004255df <+1>:	mov    %rsp,%rbp
   0x00000000004255e2 <+4>:	sub    $0xc0,%rsp
   0x00000000004255e9 <+11>:	mov    %edi,-0xa4(%rbp)
   0x00000000004255ef <+17>:	mov    %rsi,-0xb0(%rbp)
   0x00000000004255f6 <+24>:	movl   $0x0,-0x4(%rbp)
   0x00000000004255fd <+31>:	movq   $0x489da3,-0x10(%rbp)
   0x0000000000425605 <+39>:	movq   $0x489db3,-0x18(%rbp)
   0x000000000042560d <+47>:	movq   $0x0,-0x20(%rbp)
   0x0000000000425615 <+55>:	lea    -0xb0(%rbp),%rdx
   0x000000000042561c <+62>:	lea    -0xa4(%rbp),%rax
   0x0000000000425623 <+69>:	mov    %rdx,%rsi
   0x0000000000425626 <+72>:	mov    %rax,%rdi
   0x0000000000425629 <+75>:	callq  0x425038 <init_process>
   0x000000000042562e <+80>:	mov    %rax,-0x30(%rbp)
```

特定の関数を指定する場合にはdisassembleの後に関数名を指定します。
```
(gdb) disassemble main
Dump of assembler code for function main:
   0x00000000004255de <+0>:	push   %rbp
   0x00000000004255df <+1>:	mov    %rsp,%rbp
   0x00000000004255e2 <+4>:	sub    $0xc0,%rsp
   0x00000000004255e9 <+11>:	mov    %edi,-0xa4(%rbp)
   0x00000000004255ef <+17>:	mov    %rsi,-0xb0(%rbp)
   0x00000000004255f6 <+24>:	movl   $0x0,-0x4(%rbp)
   0x00000000004255fd <+31>:	movq   $0x489da3,-0x10(%rbp)
   0x0000000000425605 <+39>:	movq   $0x489db3,-0x18(%rbp)
   0x000000000042560d <+47>:	movq   $0x0,-0x20(%rbp)
   0x0000000000425615 <+55>:	lea    -0xb0(%rbp),%rdx
   0x000000000042561c <+62>:	lea    -0xa4(%rbp),%rax
   0x0000000000425623 <+69>:	mov    %rdx,%rsi
   0x0000000000425626 <+72>:	mov    %rax,%rdi
   0x0000000000425629 <+75>:	callq  0x425038 <init_process>
   0x000000000042562e <+80>:	mov    %rax,-0x30(%rbp)
```

他にも以下のに示すような指定が可能です
```
(gdb) disas プログラムカウンタ
(gdb) disas 開始アドレス 終了アドレス
(gdb) disas $pc
(gdb) disas $pc $pc+10
```

以下のように特定の場所でブレークポイントを設定などもできます。
```
   break *0x0000000000425629
```

## info関連

### info
引数無しでinfoを実行すればOKです。
```
(gdb) info
"info" must be followed by the name of an info command.
List of info subcommands:

info address -- Describe where symbol SYM is stored
info all-registers -- List of all registers and their contents
info args -- Argument variables of current stack frame
info auxv -- Display the inferior's auxiliary vector
info breakpoints -- Status of user-settable breakpoints
info catch -- Exceptions that can be caught in the current stack frame
info checkpoints -- Help
info classes -- All Objective-C classes
info common -- Print out the values contained in a Fortran COMMON block
info copying -- Conditions for redistributing copies of GDB
info dcache -- Print information on the dcache performance
info display -- Expressions to display when program stops
info extensions -- All filename extensions associated with a source language
info files -- Names of targets and files being debugged
info float -- Print the status of the floating point unit
info fork -- Help
info frame -- All about selected stack frame
info functions -- All function names
info gc-references -- List the garbage collectors references for a given address
info gc-roots -- List the garbage collector's shortest unique roots to a given address
info handle -- What debugger does when program gets various signals
info interpreters -- List the interpreters currently available in gdb
info line -- Core addresses of the code for a source line
info locals -- Local variables of current stack frame
info mach-port -- Get info on a specific port
info mach-ports -- Get list of ports in a task
info mach-region -- Get information on mach region at given address
info mach-regions -- Get information on all mach region for the current inferior
info mach-task -- Get info on a specific task
info mach-tasks -- Get list of tasks in system
info mach-thread -- Get info on a specific thread
info mach-threads -- Get list of threads in a task
info macro -- Show the definition of MACRO
info malloc-history -- List the stack(s) where malloc or free occurred for the address
info mem -- Memory region attributes
info pid -- Process ID of the program
info plugins -- Show current plug-ins state
info program -- Execution status of the program
info registers -- List of integer registers and their contents
info scope -- List the variables local to a scope
info selectors -- All Objective-C selectors
info set -- Show all GDB settings
info sharedlibrary -- Generic command for shlib information
info signals -- What debugger does when program gets various signals
info source -- Information about the current source file
info sources -- Source files in the program
info stack -- Backtrace of the stack
info symbol -- Describe what symbol is at location ADDR
info target -- Names of targets and files being debugged
info task -- Get information on task
info terminal -- Print inferior's saved terminal status
info thread -- Get information on thread
info threads -- IDs of currently known threads
info tracepoints -- Status of tracepoints
info trampoline -- Resolve function for DYLD trampoline stub and/or Objective-C call
info types -- All type names
info variables -- All global and static variable names
info vector -- Print the status of the vector unit
info warranty -- Various kinds of warranty you do not have
info watchpoints -- Synonym for ``info breakpoints''
```

### プロセス情報を取得する
```
(gdb) info proc
process 18060
cmdline = '/usr/local/apache2.2/bin/httpd'
cwd = '/usr/local/apache2.2/bin'
exe = '/usr/local/apache2.2/bin/httpd'
```

### SharedObjectのデバッグ情報を表示する
share <regex>という書式です。以下にサンプルを示します。
```
(gdb) share rewrite
Symbols already loaded for /etc/httpd/modules/mod_rewrite.so
```

### 共有ライブラリ一覧を表示する
```
(gdb) info sharedlibrary
From                To                  Syms Read   Shared Object Library
0x00007f9b5bc8f5f0  0x00007f9b5bcf6a0c  Yes (*)     /lib64/libm.so.6
0x00007f9b5ba31da0  0x00007f9b5ba72988  Yes         /lib64/libpcre.so.0
0x00007f9b5b814fc0  0x00007f9b5b825768  Yes         /lib64/libselinux.so.1
0x00007f9b5b5f3820  0x00007f9b5b6071bc  Yes         /lib64/libaprutil-1.so.0
0x00007f9b5b3b3dc0  0x00007f9b5b3b8cac  Yes (*)     /lib64/libcrypt.so.1
0x00007f9b5b18ddd0  0x00007f9b5b1a6ccc  Yes         /lib64/libexpat.so.1
0x00007f9b5ae32ae0  0x00007f9b5af54db8  Yes         /lib64/libdb-4.8.so
0x00007f9b5abeb340  0x00007f9b5ac051ac  Yes         /lib64/libapr-1.so.0
0x00007f9b5a9c8790  0x00007f9b5a9d3494  Yes (*)     /lib64/libpthread.so.0
0x00007f9b5a7bfea0  0x00007f9b5a7c09e0  Yes (*)     /lib64/libdl.so.2
```

### 関数一覧を取得する
ファイルごとに出力してくれるみたいです。
```
All defined functions:

File /home/tsuyoshi/httpd/httpd-2.2.27/server/buildmark.c:
const char *ap_get_server_built(void);

File vhost.c:
void ap_fini_vhost_config(apr_pool_t *, server_rec *);
void ap_init_vhost_config(apr_pool_t *);
int ap_matches_request_vhost(request_rec *, const char *, apr_port_t);
const char *ap_parse_vhost_addrs(apr_pool_t *, const char *, server_rec *);
const char *ap_set_name_virtual_host(cmd_parms *, void *, const char *);
void ap_update_vhost_from_headers(request_rec *);
void ap_update_vhost_given_ip(conn_rec *);
int ap_vhost_iterate_given_conn(conn_rec *, ap_vhost_iterate_conn_cb, void *);
static int add_name_vhost_config(apr_pool_t *, server_rec *, server_rec *, server_addr_rec *, ipaddr_chain *);
static void check_hostalias(request_rec *);
static void check_serverpath(request_rec *);
static void dump_a_vhost(apr_file_t *, ipaddr_chain *);
static void dump_vhost_config(apr_file_t *);
static ipaddr_chain *find_default_server(apr_port_t);
static ipaddr_chain *find_ipaddr(apr_sockaddr_t *);
static void fix_hostname(request_rec *);
static const char *get_addresses(apr_pool_t *, const char *, server_addr_rec ***, apr_port_t);
static unsigned int hash_addr(struct apr_sockaddr_t *);
static unsigned int hash_inaddr(unsigned int);
static int matches_aliases(server_rec *, const char *);
static ipaddr_chain *new_ipaddr_chain(apr_pool_t *, server_rec *, server_addr_rec *);
static name_chain *new_name_chain(apr_pool_t *, server_rec *, server_addr_rec *);
static void remove_unused_name_vhosts(server_rec *, ipaddr_chain **);

File util_pcre.c:
int ap_regcomp(ap_regex_t *, const char *, int);
apr_size_t ap_regerror(int, const ap_regex_t *, char *, apr_size_t);
int ap_regexec(const ap_regex_t *, const char *, apr_size_t, ap_regmatch_t *, int);
-- snip --
```


### バックトレース取得する
btとbt fullがあります。btの方が簡易版です。
```
(gdb) bt
#0  ap_process_request_internal (r=0x7afbf0) at request.c:104
#1  0x00000000004620d6 in ap_process_request (r=0x7afbf0) at http_request.c:280
#2  0x000000000045efd3 in ap_process_http_connection (c=0x7abdc0) at http_core.c:190
#3  0x0000000000449395 in ap_run_process_connection (c=0x7abdc0) at connection.c:43
#4  0x000000000044982b in ap_process_connection (c=0x7abdc0, csd=0x7abbd0) at connection.c:190
#5  0x000000000047d13e in child_main (child_num_arg=0) at prefork.c:667
#6  0x000000000047d235 in make_child (s=0x6be148, slot=0) at prefork.c:712
#7  0x000000000047d7ed in ap_mpm_run (_pconf=0x6b9138, plog=0x6fb348, s=0x6be148) at prefork.c:988
#8  0x00000000004260bf in main (argc=2, argv=0x7fffffffe4e8) at main.c:753
```

最初の10個、最後の10個を表示
```
(gdb) bt full 10     // 最初の10個
(gdb) bt full -10    // 最後の10個
```

もっと詳細を取得したい場合にはfullを付加します。
```
(gdb) bt full
#0  ap_process_request_internal (r=0x7afbf0) at request.c:104
        file_req = -1
        access_status = 32767
#1  0x00000000004620d6 in ap_process_request (r=0x7afbf0) at http_request.c:280
        access_status = -1
#2  0x000000000045efd3 in ap_process_http_connection (c=0x7abdc0) at http_core.c:190
        r = 0x7afbf0
        csd = 0x0
#3  0x0000000000449395 in ap_run_process_connection (c=0x7abdc0) at connection.c:43
        pHook = 0x6e6f08
        n = 0
        rv = -1
#4  0x000000000044982b in ap_process_connection (c=0x7abdc0, csd=0x7abbd0) at connection.c:190
        rc = -2
#5  0x000000000047d13e in child_main (child_num_arg=0) at prefork.c:667
        current_conn = 0x7abdc0
        csd = 0x7abbd0
        ptrans = 0x7abb58
        allocator = 0x7a9a50
        status = 0
        i = -1
        lr = 0x6b7b70
        pollset = 0x7a9bc8
        sbh = 0x7a9bc0
        bucket_alloc = 0x7adb68
        last_poll_idx = 0
#6  0x000000000047d235 in make_child (s=0x6be148, slot=0) at prefork.c:712
        pid = 0
#7  0x000000000047d7ed in ap_mpm_run (_pconf=0x6b9138, plog=0x6fb348, s=0x6be148) at prefork.c:988
        index = 0
        remaining_children_to_start = 0
        rv = 0
#8  0x00000000004260bf in main (argc=2, argv=0x7fffffffe4e8) at main.c:753
        c = 88 'X'
        configtestonly = 0
```

### レジスタ情報を取得する
レジスタ情報を閲覧するには以下のようにします。
```
(gdb) info registers
rax            0x7afbf0	8059888
rbx            0x0	0
rcx            0x0	0
rdx            0x0	0
rsi            0x0	0
rdi            0x7afbf0	8059888
rbp            0x7fffffffe400	0x7fffffffe400
rsp            0x7fffffffe340	0x7fffffffe340
r8             0x7afe70	8060528
r9             0x7afe80	8060544
r10            0x7afbf0	8059888
r11            0x7ffff7ba40f0	140737349566704
r12            0x424c90	4344976
r13            0x7fffffffe4e0	140737488348384
r14            0x0	0
r15            0x0	0
rip            0x4260bf	0x4260bf <main+2785>
eflags         0x202	[ IF ]
cs             0x33	51
ss             0x2b	43
ds             0x0	0
es             0x0	0
fs             0x0	0
gs             0x0	0
```

各レジスタの値は$を付加することでprintで閲覧することができるようです。
```
(gdb) print $rax
$1 = 140737488347680
```

## マルチスレッドのデバッグ
全スレッドの表示
```
(gdb) info threads
  3 Thread 0x7ffff75d2710 (LWP 4688)  thread3 (d=0x0) at three-threads.c:9
* 2 Thread 0x7ffff7fd3710 (LWP 4687)  thread2 (d=0x0) at three-threads.c:23
  1 Thread 0x7ffff7fd5720 (LWP 4620)  main () at three-threads.c:34
```

スレッド番号の切り替え
```
(gdb) thread <num>
```

スレッドの全てのバックトレースを表示する
```
(gdb) thread apply all bt
```

特定のスレッドに対してブレークポイントを設定する
```
(gdb) b xxxfunc thread <num>
or
(gdb) b xxxfunc thread <num>  if a > b
```

- 参考
 - https://sourceware.org/gdb/current/onlinedocs/gdb/Threads.html

## .gdbinit
以下はサンプル
```
# 履歴
set history save on
set history size 10000
set history filename ~/.gdb_history

# 出力形式
set print pretty on
set print static-members off
set print symbol-filename on   # シンボリック形式のアドレス表示の際に、シンボルのソース・ファイル名と行番号を表示する

# 言語設定
set charset UTF-8
#set charset ASCII

# for C++
set print demangle on
```

## その他
### フレーム関連の処理
```
(gdb) where
(gdb) frame
(gdb) up     // 関数呼び出しの側に戻る
(gdb) down   // 関数呼び出しの中に入る
```

### テキストユーザインターフェースモード
```
$ gdb -tui
```
とするとテキストユーザーインターフェースとしてソースコードを画面上部に表示してくれるます。
もしくは以下のように入力する
```
(gdb) <
```
これのトグルをするにはCtrl-X, Aを実行する

テキストユーザーインターフェース仕様については以下のURLが参考になります。
- [http://www.geocities.jp/harddiskdive/gdb/gdb_290.html]

### 実行ログを取得する
ロギングするファイルを指定します。以下設定をせずにset logging onするとカレントディレクトリのgdb.txtに吐かれます。
```
(gdb) set logging file <ログファイル名>
```

ログ取得を開始する場合には以下のコマンドを実行します。
```
(gdb) set logging on
```

ログ取得を終了させたければ以下のコマンドを実行します。
```
(gdb) set logging off
```

### メモリダンプする
書式は次の通り
```
[書式]
    x/(個数)(フォーマット)   (変数名)
```

```
(gdb) x/20x argv    // hex
0x7fffffffe3b8:	0xffffe5e4	0x00007fff	0x00000000	0x00000000
0x7fffffffe3c8:	0xffffe621	0x00007fff	0xffffe632	0x00007fff
0x7fffffffe3d8:	0xffffe651	0x00007fff	0xffffe661	0x00007fff
0x7fffffffe3e8:	0xffffe675	0x00007fff	0xffffe683	0x00007fff
0x7fffffffe3f8:	0xffffe6a0	0x00007fff	0xffffe6b3	0x00007fff

(gdb) x/20o argv    // octal
0x7fffffffe3b8:	037777762744	077777	0	0
0x7fffffffe3c8:	037777763041	077777	037777763062	077777
0x7fffffffe3d8:	037777763121	077777	037777763141	077777
0x7fffffffe3e8:	037777763165	077777	037777763203	077777
0x7fffffffe3f8:	037777763240	077777	037777763263	077777

(gdb) x/20d argv    // decimal
0x7fffffffe3b8:	-6684	32767	0	0
0x7fffffffe3c8:	-6623	32767	-6606	32767
0x7fffffffe3d8:	-6575	32767	-6559	32767
0x7fffffffe3e8:	-6539	32767	-6525	32767
0x7fffffffe3f8:	-6496	32767	-6477	32767

(gdb) x/20u argv   // unsigned decimal
0x7fffffffe3b8:	4294960612	32767	0	0
0x7fffffffe3c8:	4294960673	32767	4294960690	32767
0x7fffffffe3d8:	4294960721	32767	4294960737	32767
0x7fffffffe3e8:	4294960757	32767	4294960771	32767
0x7fffffffe3f8:	4294960800	32767	4294960819	32767

(gdb) x/20t argv   // binary
0x7fffffffe3b8:	11111111111111111110010111100100	00000000000000000111111111111111	00000000000000000000000000000000	00000000000000000000000000000000
0x7fffffffe3c8:	11111111111111111110011000100001	00000000000000000111111111111111	11111111111111111110011000110010	00000000000000000111111111111111
0x7fffffffe3d8:	11111111111111111110011001010001	00000000000000000111111111111111	11111111111111111110011001100001	00000000000000000111111111111111
0x7fffffffe3e8:	11111111111111111110011001110101	00000000000000000111111111111111	11111111111111111110011010000011	00000000000000000111111111111111
0x7fffffffe3f8:	11111111111111111110011010100000	00000000000000000111111111111111	11111111111111111110011010110011	00000000000000000111111111111111

(gdb) x/20f argv   // float
0x7fffffffe3b8:	-nan(0x7fe5e4)	4.59163468e-41	0	0
0x7fffffffe3c8:	-nan(0x7fe621)	4.59163468e-41	-nan(0x7fe632)	4.59163468e-41
0x7fffffffe3d8:	-nan(0x7fe651)	4.59163468e-41	-nan(0x7fe661)	4.59163468e-41
0x7fffffffe3e8:	-nan(0x7fe675)	4.59163468e-41	-nan(0x7fe683)	4.59163468e-41
0x7fffffffe3f8:	-nan(0x7fe6a0)	4.59163468e-41	-nan(0x7fe6b3)	4.59163468e-41

(gdb) x/20a argv   // addrss
0x7fffffffe3b8:	0x7fffffffe5e4	0x0
0x7fffffffe3c8:	0x7fffffffe621	0x7fffffffe632
0x7fffffffe3d8:	0x7fffffffe651	0x7fffffffe661
0x7fffffffe3e8:	0x7fffffffe675	0x7fffffffe683
0x7fffffffe3f8:	0x7fffffffe6a0	0x7fffffffe6b3
0x7fffffffe408:	0x7fffffffe6c1	0x7fffffffee12
0x7fffffffe418:	0x7fffffffee1e	0x7fffffffee82
0x7fffffffe428:	0x7fffffffeea0	0x7fffffffeeaf
0x7fffffffe438:	0x7fffffffeeea	0x7fffffffeef1
0x7fffffffe448:	0x7fffffffeefa	0x7fffffffef11

(gdb) x/20i argv   // instruction
   0x7fffffffe3b8:	in     $0xe5,%al
   0x7fffffffe3ba:	(bad)  
   0x7fffffffe3bb:	(bad)  
   0x7fffffffe3bc:	(bad)  
   0x7fffffffe3bd:	jg     0x7fffffffe3bf
   0x7fffffffe3bf:	add    %al,(%rax)
   0x7fffffffe3c1:	add    %al,(%rax)
   0x7fffffffe3c3:	add    %al,(%rax)
   0x7fffffffe3c5:	add    %al,(%rax)
   0x7fffffffe3c7:	add    %ah,(%rcx)
   0x7fffffffe3c9:	out    %al,$0xff
   0x7fffffffe3cb:	(bad)  
   0x7fffffffe3cc:	(bad)  
   0x7fffffffe3cd:	jg     0x7fffffffe3cf
   0x7fffffffe3cf:	add    %dh,(%rdx)
   0x7fffffffe3d1:	out    %al,$0xff
   0x7fffffffe3d3:	(bad)  
   0x7fffffffe3d4:	(bad)  
   0x7fffffffe3d5:	jg     0x7fffffffe3d7
   0x7fffffffe3d7:	add    %dl,-0x1a(%rcx)

(gdb) x/20c argv    // char
0x7fffffffe3b8:	-28 '\344'	-27 '\345'	-1 '\377'	-1 '\377'	-1 '\377'	127 '\177'	0 '\000'	0 '\000'
0x7fffffffe3c0:	0 '\000'	0 '\000'	0 '\000'	0 '\000'	0 '\000'	0 '\000'	0 '\000'	0 '\000'
0x7fffffffe3c8:	33 '!'	-26 '\346'	-1 '\377'	-1 '\377'

(gdb) x/20s argv    // string
0x7fffffffe3b8:	 "\344\345\377\377\377\177"
0x7fffffffe3bf:	 ""
0x7fffffffe3c0:	 ""
0x7fffffffe3c1:	 ""
0x7fffffffe3c2:	 ""
0x7fffffffe3c3:	 ""
0x7fffffffe3c4:	 ""
0x7fffffffe3c5:	 ""
0x7fffffffe3c6:	 ""
0x7fffffffe3c7:	 ""
0x7fffffffe3c8:	 "!\346\377\377\377\177"
0x7fffffffe3cf:	 ""
0x7fffffffe3d0:	 "2\346\377\377\377\177"
0x7fffffffe3d7:	 ""
0x7fffffffe3d8:	 "Q\346\377\377\377\177"
0x7fffffffe3df:	 ""
0x7fffffffe3e0:	 "a\346\377\377\377\177"
0x7fffffffe3e7:	 ""
0x7fffffffe3e8:	 "u\346\377\377\377\177"
0x7fffffffe3ef:	 ""
```

### 正規表現でブレークポイントを設定する

### リバースデバッギング
gdb7.0から逆方向にnext, nexti, step, stepiなどを実行することができる。
- reverse-continue ('rc') -- Continue program being debugged but run it in reverse
- reverse-finish -- Execute backward until just before the selected stack frame is called
- reverse-next ('rn') -- Step program backward, proceeding through subroutine calls.
- reverse-nexti ('rni') -- Step backward one instruction, but proceed through called subroutines.
- reverse-step ('rs') -- Step program backward until it reaches the beginning of a previous source line
- reverse-stepi -- Step backward exactly one instruction
- set exec-direction (forward/reverse) -- Set direction of execution.

- 参考
 - https://www.sourceware.org/gdb/news/reversible.html

### TODO
- ざっとながめてみて機能を見るのもいいかも
  - http://www.asahi-net.or.jp/~wg5k-ickw/html/online/gdb-5.0/gdb-ja_9.html

### 参考URL
- http://typea.info/tips/wiki.cgi?page=Linux+C+gdb%A4%CB%A4%E8%A4%EB%A5%C7%A5%D0%A5%C3%A5%B0
- http://b-rabbit-alice.blogspot.com/2011/05/gdb-pre.html

