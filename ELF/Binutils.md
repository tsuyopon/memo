# Binutils概要
Binutilsは、バイナリ操作や情報取得に必要な次のコマンドを含んでいます。
- addr2line,ar,as,c++filt,gprof,ld,nm,objcopy,objdump,ranlib,readelf,size,strings,strip

以下にコマンドの説明を載せます。
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
- objcopy
  - 一種のオブジェクトファイルを他の種類に翻訳するのに使われる。
- ranlib
  - アーカイブの内容の目録を作成し、それをアーカイブの茄かに保管します。
- size
  - 与えられたオブジェクトファイルについて、セクションと包括的な全体のサイズをリストします。
- strings
  - 与えられたそれぞれのファイルについて、少なくとも特定の長さ(デフォルトでは4)の表示可能な門司の一続きを出力する。
- strip
  - オブジェクトファイルからシンボルを捨てます。


以下のコマンドは別でまとめています
- od
  - ファイル情報を2、8、16進数などでダンプします
- hexdump
  - ファイル情報を16進数でダンプします
- ld
  - リンカです。これは数多くのオブジェクトとアーカイブファイルを一つのファイルに結合し、それらのデータを再配置し、シンボルへの参照を結びつける。
- nm
  - 与えられたオブジェクトファイルの茄かに存在するシンボルをリストします。
- objdump
  - 与えられたオブジェクトファイルについての情報を表示する。
- readelf
  - elfタイプのバイナリについての情報を表示します。

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


# 詳細
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

注意点としてはgprofは1度実行が必要で、経由したコードパスしか表示しない点に注意が必要である。

## sizeコマンド

### sizeコマンドを利用してみる
```
$ size ./a.out   <=バイナリファイルを引数に与えます。
text    data     bss     dec     hex filename
2268     244       4    2516     9d4 ./a.out
```

### バイナリがどのセクションにどれくらいのサイズで配置されているのかを確認する。
この出力結果は後でメモリを図にするのに非常に役に立つ。
```
$ size --format=SysV -x a.out
layout  :
section               size       addr
.interp               0x1c   0x400200
.note.ABI-tag         0x20   0x40021c
.note.gnu.build-id    0x24   0x40023c
.gnu.hash             0x1c   0x400260
.dynsym              0x108   0x400280
.dynstr               0x6d   0x400388
.gnu.version          0x16   0x4003f6
.gnu.version_r        0x20   0x400410
.rela.dyn             0x18   0x400430
.rela.plt             0xd8   0x400448
.init                  0xe   0x400520
.plt                  0xa0   0x400530
.text                0x4a4   0x4005d0
.fini                  0x9   0x400a74
.rodata               0x25   0x400a80
.eh_frame_hdr         0x3c   0x400aa8
.eh_frame             0xe4   0x400ae8
.init_array            0x8   0x600bd0
.fini_array            0x8   0x600bd8
.jcr                   0x8   0x600be0
.dynamic             0x1d0   0x600be8
.got                   0x8   0x600db8
.got.plt              0x60   0x600dc0
.data                 0xa0   0x600e20
.bss                  0xa0   0x600ec0
.comment              0x2c        0x0
Total                0xd73
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

## xxdコマンド
2進数表示する
```
$ echo hoge.txt > hoge
$ xxd hoge 
0000000: 686f 6765 2e74 7874 0a                   hoge.txt.
```

## tips

### rpathを変更する
binutilsにはrpathだけを変更する仕組みはないがchrpathパッケージを使うことで変更可能らしい
- 参考
  - https://stackoverflow.com/questions/13769141/can-i-change-rpath-in-an-already-compiled-binary

