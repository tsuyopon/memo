# 概要
実行可能リンクフォーマットELFについて

### データ領域概要
- スタック領域(stack)
  - スタック領域とは、局所変数が格納される領域であり、関数が深く実行されるにつれてどんどん局所変数が積まれていく領域です。
  - 例えば、以下のように記述すると4byteの領域がスタックセグメントに割り当てられる
```
		main(){
		    auto int z;
		}
```
  - スタックセグメントは、普通、0xffffff (32ビットのアドレス空間の場合)からからアドレス が小さくなるほうに向かって伸びていく。この部分は、関数呼び出しが続くと 伸びていき、割り当てられたメモリよりも多くなると、カーネルが自動的に拡張する。 
- ヒープ領域(heap)
  - プログラマが実行時に欲しいサイズのメモリ領域を動的に確保する際に利用する領域で、
  - 画像やファイルなどの大きさがそのときそのときで変わるバッファ用に利用されます。
  - ヒープで確保できる領域はその大きさを自由に指定でき、さらに生成・破棄も自らが自由に行うことが出来ます。
  - 反面、生成した領域の破棄を忘れてしまうなどのミスを生む可能性を持ちます。

- データ領域(.data)
  - データ領域はプログラム実行時に自動生成される領域で、静的変数や大域変数のうち初期化が行われるものが入ります。
  - プログラム実行開始時にこれらの変数は初期値によって自動的に初期化されます。
  - 例えば、
```
	static int x = 100;
```
	や
```
	char *p ;
    p = malloc( 100 );
```
  - などを使って割り当てたりする場合が.dataに該当します。

- BSS領域(.bss)
  - BSS（Block Started by Symbol）領域はプログラム実行時に自動生成される領域で、静的変数や大域変数のうち初期化が行わていないものが入ります。
  - プログラム実行開始時にこれらの変数は値0（またはそれに該当するもの、NULLや+0.0など）によって自動的に初期化されます。
  - 例えば、以下のように記述するとbssに割り当てられる。これは実行時にカーネルが領域を割り当て内容を0に初期化します
```
static int x ;
```
  - なお、以下のように初期化すると.dataに割り当てらえる
```
static int x = 100;
```

- ReadOnlyData(.rodata)
  - リードオンリーデータ領域（Read Only DATA）はプログラム実行時に自動生成される領域で、
  - const修飾子のついた変数や文字列リテラルなどの定数化された変数が入り、その領域は本質的に読み取り専用と定義されています。  

これらの用語概念は非常に重要です。

### セクション詳細について
様々なセクションが存在するが、elfのmanドキュメントに詳細が記述されている
- http://linuxjm.sourceforge.jp/html/LDP_man-pages/man5/elf.5.html

- 名前
  - セクションの名前です。「.text」「.bss」「.data」「.stack」など、そのセクションを説明する名前がついています。
- 種別
```
	セクションの種別です。主なものを下に挙げます。 
		SHT_NULL	        無効なセクションです
		SHT_PROGBITS	    このセクションはデータ(機械語や初期値など)を持っています
		SHT_NOBITS	        このセクションはデータを持ちません
		SHT_RELA, SHT_REL	このセクションは再配置可能なデータ(メモリ位置に依存しないコード)を持ってます
		SHT_SYMTAB	        このセクションにはシンボル情報が詰まっています
```
- 属性フラグ
```
	SHF_ALLOC	このセクションをメモリにおくべし
				(実行に関係ない情報(デバッグ情報とか)を持つセクションにはSHF_ALLOCがない)
	SHF_WRITE	このセクションを書き込み可能な場所におくべし
	SHF_EXECINSTR	このセクションを実行可能な場所におくべし
```
- 開始アドレス [VMA/LMA]
  - セクションを読み出すべきメモリアドレスです。
  - VMA(Virtual Memory Address)は、リンカがアドレスを解決する際に利用するアドレスです。変数のアドレス(&value)と一緒です。
  - LMA(Load Memory Address)は、プログラムやデータが実際に配置されるアドレスです。
  - 多くの場合はVMA=LMAですが、初期値つきデータ(.data)の場合は異なります。
  - これは、変数のアドレス(VMA)はRAMにありますが、実際の初期値はROMに置かないと消えてしまうため、配置アドレス(LMA)は変数アドレス(VMA)と一致しません。
  - ただし、WindowsやLinuxのプログラムのように、プログラムローダによって直接RAM上に配置されるようなプログラムでは、初期値つきデータもVMA=LMAです。
- データ
  - セクションがデータを持っている場合、そのデータが格納されます。
- サイズ
  - セクションを読み出すのに必要なメモリのサイズです。
- アライメントサイズ
  - このセクションのアライメントサイズが格納されています。
  - この情報は、ふたつのファイルの同一セクションをくっつけるときや、セクションの読み出しアドレスを変えたい場合などに利用されます。


### 押さえておくべき特に重要なセクションについて
- .text   [SHT_PROGBITS, SHF_ALLOC+SHF_EXECINSTR]
  - プログラムのうち機械語部分を格納するセクション

- .data   [SHT_PROGBITS, SHF_ALLOC+SHF_WRITE]
  - プログラムのうち初期値を持たない変数を格納するセクションです。
  - C言語では、「0以外の初期値を持つ大域変数」「0以外の初期値を持つ静的局所変数」がここに置かれます。
  - データとして初期値を持ち、プログラムローダは書き込み可能なメモリを確保した後、初期値を書き込みます。

- .bss    [SHT_NOBITS, SHF_ALLOC+SHF_WRITE]
  - プログラムのうち、初期値を持たない変数を格納するためのセクションです。
  - C言語では、「初期値が指定されない大域変数」「初期値が0の大域変数」「初期値が指定されない静的局所変数」「初期値が0の静的局所変数」が格納されます。

- .rodata [SHT_PROGBITS, SHF_ALLOC]
  - プログラムのうち、定数(const)を格納するためのセクションです。
  - C言語の場合には、「プログラム中の文字列定数」「const宣言された定数」が格納される。


### セクション情報を表示してみる。
以下の単純なファイルをコンパイルしてみて、セクション情報を覗いてみます。
```
$ cat test.c
#include<stdio.h>

void main(){
	printf("hello");
}
```

sizeはtext, data, bssの３つに分類される
```
$ size a.out 
   text	   data	    bss	    dec	    hex	filename
   1148	    540	      4	   1692	    69c	a.out
```

以下のようになります。非常に多くのセクションが存在するようです。
```
$ objdump -h a.out 

a.out:     file format elf64-x86-64

Sections:
Idx Name          Size      VMA               LMA               File off  Algn
  0 .interp       0000001c  0000000000400200  0000000000400200  00000200  2**0
                  CONTENTS, ALLOC, LOAD, READONLY, DATA
  1 .note.ABI-tag 00000020  000000000040021c  000000000040021c  0000021c  2**2
                  CONTENTS, ALLOC, LOAD, READONLY, DATA
  2 .note.gnu.build-id 00000024  000000000040023c  000000000040023c  0000023c  2**2
                  CONTENTS, ALLOC, LOAD, READONLY, DATA
  3 .gnu.hash     0000001c  0000000000400260  0000000000400260  00000260  2**3
                  CONTENTS, ALLOC, LOAD, READONLY, DATA
  4 .dynsym       00000060  0000000000400280  0000000000400280  00000280  2**3
                  CONTENTS, ALLOC, LOAD, READONLY, DATA
  5 .dynstr       0000003f  00000000004002e0  00000000004002e0  000002e0  2**0
                  CONTENTS, ALLOC, LOAD, READONLY, DATA
  6 .gnu.version  00000008  0000000000400320  0000000000400320  00000320  2**1
                  CONTENTS, ALLOC, LOAD, READONLY, DATA
  7 .gnu.version_r 00000020  0000000000400328  0000000000400328  00000328  2**3
                  CONTENTS, ALLOC, LOAD, READONLY, DATA
  8 .rela.dyn     00000018  0000000000400348  0000000000400348  00000348  2**3
                  CONTENTS, ALLOC, LOAD, READONLY, DATA
  9 .rela.plt     00000030  0000000000400360  0000000000400360  00000360  2**3
                  CONTENTS, ALLOC, LOAD, READONLY, DATA
 10 .init         0000000e  0000000000400390  0000000000400390  00000390  2**2
                  CONTENTS, ALLOC, LOAD, READONLY, CODE
 11 .plt          00000030  00000000004003a0  00000000004003a0  000003a0  2**4
                  CONTENTS, ALLOC, LOAD, READONLY, CODE
 12 .text         000001c4  00000000004003d0  00000000004003d0  000003d0  2**4
                  CONTENTS, ALLOC, LOAD, READONLY, CODE
 13 .fini         00000009  0000000000400594  0000000000400594  00000594  2**2
                  CONTENTS, ALLOC, LOAD, READONLY, CODE
 14 .rodata       00000016  00000000004005a0  00000000004005a0  000005a0  2**3
                  CONTENTS, ALLOC, LOAD, READONLY, DATA
 15 .eh_frame_hdr 0000002c  00000000004005b8  00000000004005b8  000005b8  2**2
                  CONTENTS, ALLOC, LOAD, READONLY, DATA
 16 .eh_frame     000000a4  00000000004005e8  00000000004005e8  000005e8  2**3
                  CONTENTS, ALLOC, LOAD, READONLY, DATA
 17 .init_array   00000008  0000000000600690  0000000000600690  00000690  2**3
                  CONTENTS, ALLOC, LOAD, DATA
 18 .fini_array   00000008  0000000000600698  0000000000600698  00000698  2**3
                  CONTENTS, ALLOC, LOAD, DATA
 19 .jcr          00000008  00000000006006a0  00000000006006a0  000006a0  2**3
                  CONTENTS, ALLOC, LOAD, DATA
 20 .dynamic      000001d0  00000000006006a8  00000000006006a8  000006a8  2**3
                  CONTENTS, ALLOC, LOAD, DATA
 21 .got          00000008  0000000000600878  0000000000600878  00000878  2**3
                  CONTENTS, ALLOC, LOAD, DATA
 22 .got.plt      00000028  0000000000600880  0000000000600880  00000880  2**3
                  CONTENTS, ALLOC, LOAD, DATA
 23 .data         00000004  00000000006008a8  00000000006008a8  000008a8  2**2
                  CONTENTS, ALLOC, LOAD, DATA
 24 .bss          00000004  00000000006008ac  00000000006008ac  000008ac  2**2
                  ALLOC
 25 .comment      0000002c  0000000000000000  0000000000000000  000008ac  2**0
                  CONTENTS, READONLY
```

なお、オブジェクトファイルにするとだいぶ減る
```
$ gcc -c test.c 
$ objdump -h test.o 

test.o:     file format elf64-x86-64

Sections:
Idx Name          Size      VMA               LMA               File off  Algn
  0 .text         00000015  0000000000000000  0000000000000000  00000040  2**2
                  CONTENTS, ALLOC, LOAD, RELOC, READONLY, CODE
  1 .data         00000000  0000000000000000  0000000000000000  00000058  2**2
                  CONTENTS, ALLOC, LOAD, DATA
  2 .bss          00000000  0000000000000000  0000000000000000  00000058  2**2
                  ALLOC
  3 .rodata       00000006  0000000000000000  0000000000000000  00000058  2**0
                  CONTENTS, ALLOC, LOAD, READONLY, DATA
  4 .comment      0000002d  0000000000000000  0000000000000000  0000005e  2**0
                  CONTENTS, READONLY
  5 .note.GNU-stack 00000000  0000000000000000  0000000000000000  0000008b  2**0
                  CONTENTS, READONLY
  6 .eh_frame     00000038  0000000000000000  0000000000000000  00000090  2**3
                  CONTENTS, ALLOC, LOAD, RELOC, READONLY, DATA
```

.bssセクションはVMA, LMAが.oの時点では割り当てられないようだ(a.outと比較してみるとよい)  
.bssは最低4byte必要となるらしいvar1などを追加すると+4byteとなる

### データ割付について
メモリ割り当てなどは以下が参考になります。
- http://www.coins.tsukuba.ac.jp/~yas/coins/os2-2010/2011-01-25/


# 未整理リンク
- https://www.eecs.umich.edu/courses/eecs373/readings/Linker.pdf
- Symbol versioning extensions to ELF
  - ftp://ftp.kernel.org/pub/software/libs/glibc/hjl/compat/GNUvers.txt
- Version Script
  - https://ftp.gnu.org/old-gnu/Manuals/ld-2.9.1/html_node/ld_25.html
- 13.13 LD Version Scripts
  - https://www.gnu.org/software/gnulib/manual/html_node/LD-Version-Scripts.html
  - https://sourceware.org/binutils/docs/ld/VERSION.html
- ELFの各種セクションについて
  - http://refspecs.linuxbase.org/LSB_3.0.0/LSB-PDA/LSB-PDA/specialsections.html
- no version information avairable
  - ある特定のライブラリAを使ったプログラムを作成していて、ライブラリAを更新した際に上記エラーが出た。これはライブラリAでビルドし直すとうまくいく
  - http://stackoverflow.com/questions/18390833/no-version-information-available?noredirect=1&lq=1
- ELF executables: required version information for imported symbols
  - http://stackoverflow.com/questions/30053469/elf-executables-required-version-information-for-imported-symbols
- ライブラリのI/Fが変わってもメジャーバージョンをあげないで済ます方法
  - http://www.nslabs.jp/elf-versioning.rhtml
- ELF Symbol Versioning
  - https://www.akkadia.org/drepper/symbol-versioning
- Running new applications on old glibc
  - http://lightofdawn.org/wiki/wiki.cgi/-wiki/NewAppsOnOldGlibc
- ELF仕様書関連
  - http://www.cs.northwestern.edu/~pdinda/icsclass/doc/elf.pdf
  - https://www.uclibc.org/docs/psABI-x86_64.pdf
- The ELF Virus Writing HOWTO
  - http://www.linuxsecurity.com/resource_files/documentation/virus-writing-HOWTO/_html/index.html
- Linuxシステムコール徹底ガイド
  - https://postd.cc/the-definitive-guide-to-linux-system-calls/#kernelvsyscall-internals
