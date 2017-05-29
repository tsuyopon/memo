

## Binutils超概要
Binutilsは、バイナリ操作や情報取得に必要な次のコマンドを含んでいます。
- addr2line,ar,as,c++filt,gprof,ld,nm,objcopy,objdump,ranlib,readelf,size,strings,strip


- addr2line
  - プログラムアドレスをファイル名と行番号に翻訳する。
- ar
  - アーカイブを作り、修整し、またそこからファイルを引き出す。
- as
  - アセンブラです。gccからの出力をオブジェクトファイルにアセンブルします。
- c++filt
  - リンかによって使われており、関数名の衝突を避けるために台なし(mangle)にされたC++とJavaのシンボル芽衣を元に戻す(demangle)為に使われます。
- gprof
  - グラフ呼び出しプロファイル情報を表示する。
- ld
  - リンカです。これは数多くのオブジェクトとアーカイブファイルを一つのファイルに結合し、それらのデータを再配置し、シンボルへの参照を結びつける。
- nm
  - 与えられたオブジェクトファイルの茄かに存在するシンボルをリストします。
- objcopy
  - 一種のオブジェクトファイルを他の種類に翻訳するのに使われる。
- objdump
  - 与えられたオブジェクトファイルについての情報を表示する。
- ranlib
  - アーカイブの内容の目録を作成し、それをアーカイブの茄かに保管します。
- readelf
  - elfタイプのバイナリについての情報を表示します。
- size
  - 与えられたオブジェクトファイルについて、セクションと包括的な全体のサイズをリストします。
- strings
  - 与えられたそれぞれのファイルについて、少なくとも特定の長さ(デフォルトでは4)の表示可能な門司の一続きを出力する。
- strip
  - オブジェクトファイルからシンボルを捨てます。

その他のBinutilsに含まれるライブラリに関する説明
- libiberty
  - 様々なGNUプログラムに使用されるgetoptやobstack,strerror,strtol,strtoulなどのルーチンを含む。
- libbfd
  - バイナリファイルデスクリプタのライブラリです。
- libopcodes
  - opcodeをあつかう為のライブラリ。これはobjdumpなどのユーティリティを構築する為に使用される。Opcodeは人に読める文章版のプロセッサへの説明。

- 参考URL
  - GNU Binary Utils
    - http://www.geocities.jp/fut_nis/html/binutils-ja/index.html#Top
  - The Linux ELF HOWTO
    - http://www.linux.or.jp/JF/JFdocs/archive/ELF-HOWTO.html
  - 組み込みLinux開発の手引き
    - http://www26.atwiki.jp/funa_tk/pages/22.html

## addr2lineコマンド
アドレスからエラーが起こった行番号を特定する。
- http://qiita.com/masayuki_oguni/items/580e0d576a683949ebcc

以下のような感じで求めることができる。
```
$ addr2line -e vmlinux -a ffffffff81525fc0
0xffffffff81525fc0
/home/tsuyoshi/linux/net/core/dev.c:2464
```

## arコマンド
### スタティックライブラリを作成したり、ばらばらにする方法
arコマンドを使用する。  
arコマンドは書庫の作成、変更、及び書庫からのファイルの取りだしを行なうコマンド  
例えば、liblapack.aをバラバラに各々のオブジェクトファイルに分割する時は次の様にする。
```
$ar -x liblapack.a
```

次に例えば、/home/tsuyoshi/objectfilesディレクトリにある全てのオブジェクトファイルから、自分で/libcustomize.aというスタティックライブラリを作成したい時は次の様にする。
```
$ar -r libcustomize.a  /home/tsuyoshi/objectfiles/*.o
```

中の各種ファイルを見たい場合には以下の様にする
```
$ ar -tv /usr/lib/libc.a
rw-r--r-- 0/0   1580 Mar  6 07:17 2007 init-first.o
rw-r--r-- 0/0   3200 Mar  6 07:17 2007 libc-start.o
rw-r--r-- 0/0    792 Mar  6 07:17 2007 sysdep.o
rw-r--r-- 0/0   2060 Mar  6 07:17 2007 version.o
rw-r--r-- 0/0   1268 Mar  6 07:17 2007 check_fds.o
rw-r--r-- 0/0    856 Mar  6 07:17 2007 libc-tls.o
rw-r--r-- 0/0   1480 Mar  6 07:17 2007 elf-init.o
(以下略)
```

arコマンドで生成されるものが.oファイルの塊ということはその中にもシンボルやデバッグシンボルが含まれるということを意味しています。

## gprofコマンド
### プロファイリングをしたい(gcc)
例えば、test.cというプログラムが何の関数を主に呼んでいるかを調べたいとする。
この時、次のようにする。
```
$gcc -g -pg -o test test.c
$./test
$ls
  test.c   test   gmon.out   <=プログラムを実行するとgmon.outが出来る。
$gprof -b test
```
gmon.outはプロファイルの為のファイルである。

## ldコマンド
### ld(GNUのリンカ)を使用する
例えば次の例を見てみることとする。
```
$ld -o output /lib/crt0.o hello.o -lc  <=一番良く使用される例
```
この例では、ldにoutputという名前のファイルを作成するように命令している。  
リンクするファイルは/lib/crt0.oとhello.o及び標準的な検索ディレクトリ(/usr/lib,/libなど)にあるライブラリlibc.aであるという亊を意味している。

## nmコマンド

### 共有ライブラリの作成方法と確認方法
- 共有ライブラリの作成方法
  - 次のようにすると、test1.oとtest2.oの静的共有ライブラリ(libcustomize.so)が作成される。
```
$gcc -shared -o libcustomize.so  test1.o test2.o
※一般的には、拡張子がso(shared object)ファイルは慣用的にlibname.so.x.yと書かれる。xは共有ライブラリのmajor番号、yはminor番号表す。
soファイルはcygwinなどにおけるdllと同じ働きをする。
```

- 共有ライブラリの確認方法
次のようにすればよい
```
$nm libname.so
```

なお、C++の場合にはマングリングされていて読みにくいのでdemangleオプションを付与するとよい。
```
$ nm --demangle libname.so
```

または以下のようにc++filtコマンドを利用することも可能
```
$nm -o libname.so | c++filt
```

シンボルがあるかどうかはfileコマンドで確認することができる「not stripped」や「stripped」といった情報が表示される。

### オブジェクトファイルのシンボルを確認する
以下のようなhello.cをオブジェクトファイルにします。
```
#include
int main(){ printf("Hello World\n"); }
```
上記を保存してオブジェクトファイルにします。
```
$ gcc -c hello.c
$ ls 
 hello.c    hello.o
```
上記の様にgccに-cオプションを行うと.o(オブジェクトファイル)が作成される  

上記のシンボルを以下のようにして確認する。
```
$ nm hello.o
00000000 T main
         U printf
```

### 記号の意味について
小文字はそのシンボルがローカルであることを意味し、大文字はそのシンボルがグローバル (外部定義) であることを意味します。  
典型的なシンボルタイプについては以下のとおりです
- T コードセクション内の定義
- D 初期化されたデータセクション
- B 初期化されないデータセクション
- U 未定義。シンボルはライブラリによって使われているが、ライブラリ内では定義されていない
- W weak. 他のライブラリも同じシンボルを定義している場合、その定義によりオーバーライドされる

## sizeコマンド

### sizeコマンドを利用してみる
```
$ size ./a.out   <=バイナリファイルを引数に与えます。
text    data     bss     dec     hex filename
2268     244       4    2516     9d4 ./a.out
```

## stringsコマンド
### バイナリファイル中の可読部分の文字列の取得を行う
```
$ strings /bin/ls | head -n 10
/lib/ld-linux.so.2
libtermcap.so.2
_DYNAMIC
_init
tgetent
_fini 
_GLOBAL_OFFSET_TABLE_
_Jv_RegisterClasses
tgetstr
__gmon_start__
```

### シンボルの削除を行う
```
$ nm a.out
100008c0 t call___do_global_ctors_aux
100003f4 t call___do_global_dtors_aux
10000454 t call_frame_dummy
(中略)
10000470 T main
10010988 d p.0
U printf@@GLIBC_2.0
U scanf@@GLIBC_2.0
$ strip a.out
$ nm a.out
nm: a.out: no symbols
```

## stripコマンド
### 実行ファイルのサイズを減少させる
オブジェクトファイルからリロケート情報とシンボルテーブルのデバッグ用の情報を削除することで実行ファイルを減少させる事が出来る。
```
$ ls -l a.out
-rwxr-xr-x    1 tsuyoshi tsuyoshi      5671 Dec 24 14:32 a.out*
$ file a.out
a.out:          ELF 32-bit MSB executable SPARC Version 1, dynamically linked, not stripped
$ strip a.out
$ file a.out
a.out:          ELF 32-bit MSB executable SPARC Version 1, dynamically linked, stripped
$ ls -l a.out
-rwxr-xr-x    1 tsuyoshi tsuyoshi      3172 Dec 24 14:33 a.out*
```

## odコマンド

### メモリ内部を直接読む
```
# od -x /dev/mem
```

### odでバイナリファイルのダンプを行う
- odはデフォルトで8進数の出力を行う。
```
$ od a.out  | head -3
0000000 042577 043114 000401 000001 000000 000000 000000 000000
0000020 000002 000003 000001 000000 101170 004004 000064 000000
0000040 016464 000000 000000 000000 000064 000040 000006 000050
```

- -xオプションで16進数を表示することができる。
```
$ od -x a.out | head -3
0000000 457f 464c 0101 0001 0000 0000 0000 0000
0000020 0002 0003 0001 0000 8278 0804 0034 0000
0000040 1d34 0000 0000 0000 0034 0020 0006 0028
```

- -dオプションで10進数表示をすることができる。
```
$ od -d a.out | head -3
0000000 17791 17996   257     1     0     0     0     0
0000020     2     3     1     0 33400  2052    52     0
0000040  7476     0     0     0    52    32     6    40
```

- ASCII文字列表示も調べたい場合には -t x1zとzを付ける。
```
$ od -t x1z -A x a.out  | more
000000 7f 45 4c 46 01 01 01 00 00 00 00 00 00 00 00 00  >.ELF............<
000010 02 00 03 00 01 00 00 00 78 82 04 08 34 00 00 00  >........x...4...<
(中略)
0001a0 00 6c 69 62 63 2e 73 6f 2e 36 00 70 72 69 6e 74  >.libc.so.6.print<
0001b0 66 00 5f 49 4f 5f 73 74 64 69 6e 5f 75 73 65 64  >f._IO_stdin_used<
0001c0 00 5f 5f 6c 69 62 63 5f 73 74 61 72 74 5f 6d 61  >.__libc_start_ma<
(以下略)
```

## xxdコマンド
2進数表示する
```
$ echo hoge.txt > hoge
$ xxd hoge 
0000000: 686f 6765 2e74 7874 0a                   hoge.txt.
```

## hexdumpコマンド
-Cオプションを付加すると16進数+文字列を表示して埋め込まれた文字などを探すことができる
```
$ hexdump -C /usr/lib/libcurl.dylib  | head -4
00000000  ca fe ba be 00 00 00 02  01 00 00 07 00 00 00 03  |................|
00000010  00 00 10 00 00 05 d4 00  00 00 00 0c 00 00 00 07  |................|
00000020  00 00 00 03 00 05 f0 00  00 05 b6 00 00 00 00 0c  |................|
00000030  00 00 00 00 00 00 00 00  00 00 00 00 00 00 00 00  |................|
```

