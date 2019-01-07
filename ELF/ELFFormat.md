# ELF(Executable and Linkable Format) Formatについて
UNIXでは長い間a.outやCOFF形式が使われてきたが、クロスコンパイルや動的リンクなどに対応するためのより良い形式が必要としてELFが作成されました。

ELFオブジェクトファイルは次の2つの情報から成り立っています
- Header
- Section

ELFには次の３種類のHeaderが存在します。**上記Sectionとしてではなく、セクションHeaderとして別物ですので注意してください。 **
- ELF File Header
  - ELFファイルの先頭に位置していて、ELF識別子、アーキテクチャ情報、他の２つの情報に対するポインタ情報などを持つ
- Program Header
  - ELF Header直後に配置される。
- Section Header
  - Program HeaderとSection Headerの間には各種section情報(.text, rodata, .data)が存在します。Section HeaderはELFオブジェクトの最後尾に存在しています
  - プログラム実行にはSection Headerは使われておらず、リンクやデバッグ、objdumpなどのツールによってこのヘッダが参照されています。

静的バイナリ(static)、共有バイナリ(shared)、libdlライブラリを使ったバイナリ、coreなど、バイナリの種類によって含まれてくるSection情報(ヘッダではない)の数などが変化してきます。

なお、ヘッダ情報やセクション情報の意味は以下のELF公式資料に記載されていますので適宜参照してください。
- http://www.skyfree.org/linux/references/ELF_Format.pdf

# ヘッダの中身を覗いてみる
ELFには3種類のヘッダがあることを紹介しましたが、それぞれのヘッダの中身をreadelf, objdumpコマンドで見てみます。


### ELF File Headerの情報を表示する
```
$ readelf -h /bin/ls
ELF Header:
  Magic:   7f 45 4c 46 02 01 01 00 00 00 00 00 00 00 00 00 
  Class:                             ELF64
  Data:                              2's complement, little endian
  Version:                           1 (current)
  OS/ABI:                            UNIX - System V
  ABI Version:                       0
  Type:                              EXEC (Executable file)
  Machine:                           Advanced Micro Devices X86-64
  Version:                           0x1
  Entry point address:               0x404b6c
  Start of program headers:          64 (bytes into file)
  Start of section headers:          113024 (bytes into file)
  Flags:                             0x0
  Size of this header:               64 (bytes)
  Size of program headers:           56 (bytes)
  Number of program headers:         10
  Size of section headers:           64 (bytes)
  Number of section headers:         32
  Section header string table index: 31
```

### Program Headerの情報を表示する
lオプションでプログラムヘッダを表示することができます。
```
$ readelf -l /bin/ls

Elf file type is EXEC (Executable file)
Entry point 0x404b6c
There are 10 program headers, starting at offset 64

Program Headers:
  Type           Offset             VirtAddr           PhysAddr
                 FileSiz            MemSiz              Flags  Align
  PHDR           0x0000000000000040 0x0000000000400040 0x0000000000400040
                 0x0000000000000230 0x0000000000000230  R E    8
  INTERP         0x0000000000000270 0x0000000000400270 0x0000000000400270
                 0x000000000000001c 0x000000000000001c  R      1
      [Requesting program interpreter: /lib64/ld-linux-x86-64.so.2]
  LOAD           0x0000000000000000 0x0000000000400000 0x0000000000400000
                 0x0000000000018d88 0x0000000000018d88  R E    200000
  LOAD           0x00000000000192a8 0x00000000006192a8 0x00000000006192a8
                 0x00000000000012c8 0x0000000000001ff8  RW     200000
  LOAD           0x000000000001a570 0x000000000081a570 0x000000000081a570
                 0x0000000000000990 0x0000000000000990  RW     200000
  DYNAMIC        0x0000000000019d28 0x0000000000619d28 0x0000000000619d28
                 0x0000000000000210 0x0000000000000210  RW     8
  NOTE           0x000000000000028c 0x000000000040028c 0x000000000040028c
                 0x0000000000000044 0x0000000000000044  R      4
  GNU_EH_FRAME   0x0000000000016004 0x0000000000416004 0x0000000000416004
                 0x00000000000006f4 0x00000000000006f4  R      4
  GNU_STACK      0x0000000000000000 0x0000000000000000 0x0000000000000000
                 0x0000000000000000 0x0000000000000000  RW     8
  GNU_RELRO      0x00000000000192a8 0x00000000006192a8 0x00000000006192a8
                 0x0000000000000d58 0x0000000000000d58  R      1

 Section to Segment mapping:
  Segment Sections...
   00     
   01     .interp 
   02     .interp .note.ABI-tag .note.gnu.build-id .gnu.hash .dynsym .gnu.liblist .gnu.version .gnu.version_r .rela.dyn .rela.plt .init .plt .text .fini .rodata .eh_frame_hdr .eh_frame .dynstr 
   03     .init_array .fini_array .jcr .data.rel.ro .dynamic .got .got.plt .data .bss 
   04     .gnu.conflict 
   05     .dynamic 
   06     .note.ABI-tag .note.gnu.build-id 
   07     .eh_frame_hdr 
   08     
   09     .init_array .fini_array .jcr .data.rel.ro .dynamic .got
```

プログラム毎に出力内容の順番は異なっています。例えば、LOADが２つしか出力されない場合などもあります。

プログラムヘッダとSegment Sectionsは上から順番にマッピングさせることができます。上記出力の例だと次のようにマッピングされます。
- PHDRは00
- INTERPは01で.interpセクションが存在する
- 1番目のLOADは02で権限はRE(Read, Exec)であり、.interp .note.ABI-tag .note.gnu.build-id .gnu.hash .dynsym .gnu.liblist .gnu.version .gnu.version_r .rela.dyn .rela.plt .init .plt .text .fini .rodata .eh_frame_hdr .eh_frame .dynstrのセクションが存在する
- 2番目のLOADは03で.init_array .fini_array .jcr .data.rel.ro .dynamic .got .got.plt .data .bssのセクションが存在する
- 3番目のLOADは04で.gnu.conflictセクションが存在する
- DYNAMICは05で.dynamicセクションが存在する
- NOTEは06で.note.ABI-tag .note.gnu.build-idセクションが存在する
- GNU_EH_FRAMEは07で.eh_frame_hdr セクションが存在する
- GNU_STACKは08
- GNU_RELROは09で.init_array .fini_array .jcr .data.rel.ro .dynamic .gotセクションが存在する。


各種プログラムヘッダについての説明を行う (公式資料: http://www.skyfree.org/linux/references/ELF_Format.pdf を参考のこと)

- PT_PHDR
- PT_INTERP
  - インタープリターとしてinvokeするためのロケーション及びサイズを示す配列要素である。
- PT_LOAD
- PT_DYNAMIC
- GNU_EH_FRAME 
  - codeセグメントの一部である。
- GNU_STACK 
  - ELFがメモリにロードされた際にどのようにstackをコントロールするのかをシステムに伝えるためのものである。このため、FileSizもMemSizeも0である。
- GNU_RELRO
  - dataセグメントの一部である。



TODO: セグメントとは一体なにものか?
TODO: 2番目のLOADと3番目のLOADは権限も同じなのになぜ別セグメントとなるのか?


### Section Headerの情報を表示する
```
$ readelf -S /bin/ls
There are 30 section headers, starting at offset 0x1c418:

Section Headers:
  [Nr] Name              Type             Address           Offset
       Size              EntSize          Flags  Link  Info  Align
  [ 0]                   NULL             0000000000000000  00000000
       0000000000000000  0000000000000000           0     0     0
  [ 1] .interp           PROGBITS         0000000000400238  00000238
       000000000000001c  0000000000000000   A       0     0     1
  [ 2] .note.ABI-tag     NOTE             0000000000400254  00000254
       0000000000000020  0000000000000000   A       0     0     4
  [ 3] .note.gnu.build-i NOTE             0000000000400274  00000274
       0000000000000024  0000000000000000   A       0     0     4
  [ 4] .gnu.hash         GNU_HASH         0000000000400298  00000298
       0000000000000038  0000000000000000   A       5     0     8
  [ 5] .dynsym           DYNSYM           00000000004002d0  000002d0
       0000000000000c60  0000000000000018   A       6     1     8
  [ 6] .dynstr           STRTAB           0000000000400f30  00000f30
       00000000000005bc  0000000000000000   A       0     0     1
  [ 7] .gnu.version      VERSYM           00000000004014ec  000014ec
       0000000000000108  0000000000000002   A       5     0     2
  [ 8] .gnu.version_r    VERNEED          00000000004015f8  000015f8
       0000000000000090  0000000000000000   A       6     2     8
  [ 9] .rela.dyn         RELA             0000000000401688  00001688
       00000000000000d8  0000000000000018   A       5     0     8
  [10] .rela.plt         RELA             0000000000401760  00001760
       0000000000000ac8  0000000000000018  AI       5    12     8
  [11] .init             PROGBITS         0000000000402228  00002228
       000000000000001a  0000000000000000  AX       0     0     4
  [12] .plt              PROGBITS         0000000000402250  00002250
       0000000000000740  0000000000000010  AX       0     0     16
  [13] .text             PROGBITS         0000000000402990  00002990
       000000000000ffcc  0000000000000000  AX       0     0     16
  [14] .fini             PROGBITS         000000000041295c  0001295c
       0000000000000009  0000000000000000  AX       0     0     4
  [15] .rodata           PROGBITS         0000000000412980  00012980
       0000000000003cce  0000000000000000   A       0     0     32
  [16] .eh_frame_hdr     PROGBITS         0000000000416650  00016650
       0000000000000744  0000000000000000   A       0     0     4
  [17] .eh_frame         PROGBITS         0000000000416d98  00016d98
       0000000000002664  0000000000000000   A       0     0     8
  [18] .init_array       INIT_ARRAY       000000000061a328  0001a328
       0000000000000008  0000000000000000  WA       0     0     8
  [19] .fini_array       FINI_ARRAY       000000000061a330  0001a330
       0000000000000008  0000000000000000  WA       0     0     8
  [20] .jcr              PROGBITS         000000000061a338  0001a338
       0000000000000008  0000000000000000  WA       0     0     8
  [21] .data.rel.ro      PROGBITS         000000000061a340  0001a340
       0000000000000a68  0000000000000000  WA       0     0     32
  [22] .dynamic          DYNAMIC          000000000061ada8  0001ada8
       0000000000000200  0000000000000010  WA       6     0     8
  [23] .got              PROGBITS         000000000061afa8  0001afa8
       0000000000000048  0000000000000008  WA       0     0     8
  [24] .got.plt          PROGBITS         000000000061b000  0001b000
       00000000000003b0  0000000000000008  WA       0     0     8
  [25] .data             PROGBITS         000000000061b3c0  0001b3c0
       0000000000000240  0000000000000000  WA       0     0     32
  [26] .bss              NOBITS           000000000061b600  0001b600
       0000000000000d20  0000000000000000  WA       0     0     32
  [27] .gnu_debuglink    PROGBITS         0000000000000000  0001b600
       0000000000000010  0000000000000000           0     0     4
  [28] .gnu_debugdata    PROGBITS         0000000000000000  0001b610
       0000000000000cec  0000000000000000           0     0     1
  [29] .shstrtab         STRTAB           0000000000000000  0001c2fc
       000000000000011a  0000000000000000           0     0     1
Key to Flags:
  W (write), A (alloc), X (execute), M (merge), S (strings), l (large)
  I (info), L (link order), G (group), T (TLS), E (exclude), x (unknown)
  O (extra OS processing required) o (OS specific), p (processor specific)
```

elfのmanドキュメントに詳細が記述されている

- セクション番号(Nr)
  - セクションの番号です
- 名前(Name)
  - セクションの名前です。「.text」「.bss」「.data」「.stack」など、そのセクションを説明する名前がついています。
- 種別(Type)
  - セクションの種別です。主なものを下に挙げます。
```
SHT_NULL	        無効なセクションです
SHT_PROGBITS	    このセクションはデータ(機械語や初期値など)を持っています
SHT_NOBITS	        このセクションはデータを持ちません
SHT_RELA, SHT_REL	このセクションは再配置可能なデータ(メモリ位置に依存しないコード)を持ってます
SHT_SYMTAB	        このセクションにはシンボル情報が詰まっています
```
- 属性フラグ(Flag)
```
SHF_ALLOC       このセクションをメモリにおくべし
                (実行に関係ない情報(デバッグ情報とか)を持つセクションにはSHF_ALLOCがない)
SHF_WRITE       このセクションを書き込み可能な場所におくべし
SHF_EXECINSTR   このセクションを実行可能な場所におくべし
```
- データ
  - セクションがデータを持っている場合、そのデータが格納されます。
- サイズ
  - セクションを読み出すのに必要なメモリのサイズです。
- アライメントサイズ
  - このセクションのアライメントサイズが格納されています。
  - この情報は、ふたつのファイルの同一セクションをくっつけるときや、セクションの読み出しアドレスを変えたい場合などに利用されます。

- 参考資料
  - http://linuxjm.sourceforge.jp/html/LDP_man-pages/man5/elf.5.html


また、objdumpコマンドでもセクション情報を確認することができる。
```
$ objdump -h /bin/ls

/bin/ls:     file format elf64-x86-64

Sections:
Idx Name          Size      VMA               LMA               File off  Algn
  0 .interp       0000001c  0000000000400238  0000000000400238  00000238  2**0
                  CONTENTS, ALLOC, LOAD, READONLY, DATA
  1 .note.ABI-tag 00000020  0000000000400254  0000000000400254  00000254  2**2
                  CONTENTS, ALLOC, LOAD, READONLY, DATA
  2 .note.gnu.build-id 00000024  0000000000400274  0000000000400274  00000274  2**2
                  CONTENTS, ALLOC, LOAD, READONLY, DATA
  3 .gnu.hash     00000038  0000000000400298  0000000000400298  00000298  2**3
                  CONTENTS, ALLOC, LOAD, READONLY, DATA
  4 .dynsym       00000c60  00000000004002d0  00000000004002d0  000002d0  2**3
                  CONTENTS, ALLOC, LOAD, READONLY, DATA
...
 21 .dynamic      00000200  000000000061ada8  000000000061ada8  0001ada8  2**3
                  CONTENTS, ALLOC, LOAD, DATA
 22 .got          00000048  000000000061afa8  000000000061afa8  0001afa8  2**3
                  CONTENTS, ALLOC, LOAD, DATA
 23 .got.plt      000003b0  000000000061b000  000000000061b000  0001b000  2**3
                  CONTENTS, ALLOC, LOAD, DATA
 24 .data         00000240  000000000061b3c0  000000000061b3c0  0001b3c0  2**5
                  CONTENTS, ALLOC, LOAD, DATA
 25 .bss          00000d20  000000000061b600  000000000061b600  0001b600  2**5
                  ALLOC
 26 .gnu_debuglink 00000010  0000000000000000  0000000000000000  0001b600  2**2
                  CONTENTS, READONLY
 27 .gnu_debugdata 00000cec  0000000000000000  0000000000000000  0001b610  2**0
                  CONTENTS, READONLY
```

- 開始アドレス [VMA/LMA]
  - セクションを読み出すべきメモリアドレスです。
  - VMA(Virtual Memory Address)は、リンカがアドレスを解決する際に利用するアドレスです。変数のアドレス(&value)と一緒です。
  - LMA(Load Memory Address)は、プログラムやデータが実際に配置されるアドレスです。
  - 多くの場合はVMA=LMAですが、初期値つきデータ(.data)の場合は異なります。
  - これは、変数のアドレス(VMA)はRAMにありますが、実際の初期値はROMに置かないと消えてしまうため、配置アドレス(LMA)は変数アドレス(VMA)と一致しません。
  - ただし、WindowsやLinuxのプログラムのように、プログラムローダによって直接RAM上に配置されるようなプログラムでは、初期値つきデータもVMA=LMAです。



# sectionについて

### 特に重要なセクションについて
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


### セクション説明
- .interp
  - 動的リンクを実際に処理するインタプリタです。sharedなバイナリを生成するとINTERPが付与されます。
- .hash
  - シンボル名のハッシュテーブルであり、.dynsymでシンボルをサーチする時間を短縮する
- .commment
- .debug
  - デバッグ時に使用するシンボルが格納されます。
- .got
  - Global Offset Table
- .got.plt
  - 動的リンクされた関数などのアドレステーブル
- .hash
  - シンボル名の検索を高速化するためのハッシュテーブル
- .dynamic
  - 動的リンクに必要な情報を集めたテーブルである。セクション属性としては、SHF_ALLOC属性を含む。SHF_WRITE属性が立っているかどうかはプロセッサ特有である。
- .dynsym
  - 動的リンクに関連する情報が入っている。
- .dynstr
  - シンボル名の文字列テーブル
- .line
  - シンボルデバッグのための行番号情報が含まれる。
- .bss
  - 未初期化データが格納されるセクション
- .data
  - 初期化データが格納されるセクション
- .rodata, .rodata1
  - 
- .note
- .text
  - プログラムの実行命令が含まれたセクション
- .fini
  - 

- .plt
  - Procedure Linkage Tableのためのセクション
- .rel.<x>
  - 


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
や
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



### .dynamicセクション

## readelfコマンドでバイナリを確認する実験
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


### gオプションありとgオプションなしのバイナリを比較する
手元でgオプションありの場合とgオプションなしのバイナリで比較して

「readelf -S a.out」で比較をするとgオプションありには次のsectionが存在した。
これがデバッグ用に利用されるセクションであると考えられる。
- .debug_aranges
- .debug_info
- .debug_abbrev
- .debug_line
- .debug_str


### gオプションありでコンパイルしたものをstripして何が削除されたのかを確認する。
gオプションが付与された状態のデータを以下のコマンドによりstripして「readelf -S a.out」をして前後の差分を比較してみると、
```
$ strip a.out
$ readelf -S a.out
```
次のsectionが削除されていた
- .debug_aranges
- .debug_info
- .debug_abbrev
- .debug_line
- .debug_str
- .symtab
- .strtab


### staticとsharedのバイナリ比較してみる。

次のバイナリを用意する。
```
$ cat test.c 
#include<stdio.h>
int main(){
	printf("hoge");     // printfの行などが無いとコンパイルするとかなrずstaticバイナリとなってしまうので追加した。
	return 0;
}
```

staticのバイナリは次のように作成する
```
$ sudo yum install glibc-staticc   // コンパイル時にlcがないと言われる場合はこれが必要
$ gcc -static -lc test.c  -o static
$ readelf -l static
```

sharedのバイナリは次のように作成する
```
$ gcc -shared -fPIC test.c -o shared
$ readelf -l shared
```

あとはstaticとsharedのライブラリをreadelfコマンドで確認してみる。
主な違いとしては次の通り
- ELFファイルヘッダにおいて
  - 実行ファイルのタイプがstaticだとEXEC, sharedだとDYNとなる
- プログラムヘッダにおいて
  - staticのみTLSが存在する
  - sharedにのみDYNAMIC、GNU_EH_FRAMEが存在する
- sectionにおいて
  - staticにしか存在し無いTLSセグメントでは、.tdata .tbssが存在する
  - sharedにしか存在し無いDYNAMICセグメントでは、.dynamicが存在する
  - sharedにしか存在し無いGNU_EH_FRAMEセグメントでは、.eh_frame_hdrが存在する
  - NOTEのセグメントでは、staticの場合のみ.note.ABI-tagが存在する。
  - GNU_RELROのセグメントでは、staticだと.tdataが存在し,sharedだと.dynamicが存在する。

staticとsharedのreadelfコマンドの出力結果を以下に添付しておきます。

```
$ readelf -l static

Elf file type is EXEC (Executable file)
Entry point 0x400ecd
There are 6 program headers, starting at offset 64

Program Headers:
  Type           Offset             VirtAddr           PhysAddr
                 FileSiz            MemSiz              Flags  Align
  LOAD           0x0000000000000000 0x0000000000400000 0x0000000000400000
                 0x00000000000bb809 0x00000000000bb809  R E    200000
  LOAD           0x00000000000bbeb0 0x00000000006bbeb0 0x00000000006bbeb0
                 0x0000000000001860 0x00000000000039f8  RW     200000
  NOTE           0x0000000000000190 0x0000000000400190 0x0000000000400190
                 0x0000000000000044 0x0000000000000044  R      4
  TLS            0x00000000000bbeb0 0x00000000006bbeb0 0x00000000006bbeb0
                 0x0000000000000020 0x0000000000000058  R      10
  GNU_STACK      0x0000000000000000 0x0000000000000000 0x0000000000000000
                 0x0000000000000000 0x0000000000000000  RW     10
  GNU_RELRO      0x00000000000bbeb0 0x00000000006bbeb0 0x00000000006bbeb0
                 0x0000000000000150 0x0000000000000150  R      1

 Section to Segment mapping:
  Segment Sections...
   00     .note.ABI-tag .note.gnu.build-id .rela.plt .init .plt .text __libc_thread_freeres_fn __libc_freeres_fn .fini .rodata .stapsdt.base __libc_thread_subfreeres __libc_subfreeres __libc_IO_vtables __libc_atexit .eh_frame .gcc_except_table 
   01     .tdata .init_array .fini_array .jcr .data.rel.ro .got .got.plt .data .bss __libc_freeres_ptrs 
   02     .note.ABI-tag .note.gnu.build-id 
   03     .tdata .tbss 
   04     
   05     .tdata .init_array .fini_array .jcr .data.rel.ro .got 
```

```
$ readelf -l shared

Elf file type is DYN (Shared object file)
Entry point 0x5e0
There are 7 program headers, starting at offset 64

Program Headers:
  Type           Offset             VirtAddr           PhysAddr
                 FileSiz            MemSiz              Flags  Align
  LOAD           0x0000000000000000 0x0000000000000000 0x0000000000000000
                 0x0000000000000774 0x0000000000000774  R E    200000
  LOAD           0x0000000000000df8 0x0000000000200df8 0x0000000000200df8
                 0x0000000000000238 0x0000000000000240  RW     200000
  DYNAMIC        0x0000000000000e18 0x0000000000200e18 0x0000000000200e18
                 0x00000000000001c0 0x00000000000001c0  RW     8
  NOTE           0x00000000000001c8 0x00000000000001c8 0x00000000000001c8
                 0x0000000000000024 0x0000000000000024  R      4
  GNU_EH_FRAME   0x00000000000006f4 0x00000000000006f4 0x00000000000006f4
                 0x000000000000001c 0x000000000000001c  R      4
  GNU_STACK      0x0000000000000000 0x0000000000000000 0x0000000000000000
                 0x0000000000000000 0x0000000000000000  RW     10
  GNU_RELRO      0x0000000000000df8 0x0000000000200df8 0x0000000000200df8
                 0x0000000000000208 0x0000000000000208  R      1 
 Section to Segment mapping:
  Segment Sections...
   00     .note.gnu.build-id .gnu.hash .dynsym .dynstr .gnu.version .gnu.version_r .rela.dyn .rela.plt .init .plt .text .fini .rodata .eh_frame_hdr .eh_frame 
   01     .init_array .fini_array .jcr .data.rel.ro .dynamic .got .got.plt .bss 
   02     .dynamic 
   03     .note.gnu.build-id 
   04     .eh_frame_hdr 
   05     
   06     .init_array .fini_array .jcr .data.rel.ro .dynamic .got 
```


### dl, pthreadライブラリを使った場合のsecition情報を確認する
cpp/basic_linkage/dl/clang/sample1に存在するプログラムを使って共有ライブラリをdlopen(RTLD_LAZY指定)するプログラムのバイナリを作成する。
```
all: hello main

hello: hello.c
	gcc -shared hello.c -o hello.so -fPIC

main: main.c
	gcc main.c -o main -ldl
```

その時のreadelfは次のようになった。
- ELFファイルヘッダにおいて
  - sharedなファイルなのになぜかEXEC (なぜ??)
- プログラムヘッダにおいて
  - 単純なsharedなプログラムの時に加えてPHDR, INTERPが追加されている。

```
$ readelf -l main

Elf file type is EXEC (Executable file)
Entry point 0x400740
There are 9 program headers, starting at offset 64

Program Headers:
  Type           Offset             VirtAddr           PhysAddr
                 FileSiz            MemSiz              Flags  Align
  PHDR           0x0000000000000040 0x0000000000400040 0x0000000000400040
                 0x00000000000001f8 0x00000000000001f8  R E    8
  INTERP         0x0000000000000238 0x0000000000400238 0x0000000000400238
                 0x000000000000001c 0x000000000000001c  R      1
      [Requesting program interpreter: /lib64/ld-linux-x86-64.so.2]
  LOAD           0x0000000000000000 0x0000000000400000 0x0000000000400000
                 0x0000000000000ad4 0x0000000000000ad4  R E    200000
  LOAD           0x0000000000000e00 0x0000000000600e00 0x0000000000600e00
                 0x000000000000026c 0x0000000000000280  RW     200000
  DYNAMIC        0x0000000000000e18 0x0000000000600e18 0x0000000000600e18
                 0x00000000000001e0 0x00000000000001e0  RW     8
  NOTE           0x0000000000000254 0x0000000000400254 0x0000000000400254
                 0x0000000000000044 0x0000000000000044  R      4
  GNU_EH_FRAME   0x00000000000009ac 0x00000000004009ac 0x00000000004009ac
                 0x0000000000000034 0x0000000000000034  R      4
  GNU_STACK      0x0000000000000000 0x0000000000000000 0x0000000000000000
                 0x0000000000000000 0x0000000000000000  RW     10
  GNU_RELRO      0x0000000000000e00 0x0000000000600e00 0x0000000000600e00
                 0x0000000000000200 0x0000000000000200  R      1

 Section to Segment mapping:
  Segment Sections...
   00     
   01     .interp 
   02     .interp .note.ABI-tag .note.gnu.build-id .gnu.hash .dynsym .dynstr .gnu.version .gnu.version_r .rela.dyn .rela.plt .init .plt .text .fini .rodata .eh_frame_hdr .eh_frame 
   03     .init_array .fini_array .jcr .dynamic .got .got.plt .data .bss 
   04     .dynamic 
   05     .note.ABI-tag .note.gnu.build-id 
   06     .eh_frame_hdr 
   07     
   08     .init_array .fini_array .jcr .dynamic .got 
````

ちなみに、lpthreadでコンパイルするプログラムでも上記と同様の出力となった。


### データ割付について
メモリ割り当てなどは以下が参考になります。
- http://www.coins.tsukuba.ac.jp/~yas/coins/os2-2010/2011-01-25/


# 公式資料
- The GNU linker (PDF)
  - https://www.eecs.umich.edu/courses/eecs373/readings/Linker.pdf
- Executable and Linkable Format (ELF)  PDF
  - http://www.cs.northwestern.edu/~pdinda/icsclass/doc/elf.pdf
- System V Application Binary Interface AMD64 Architecture Processor Supplement
  - https://www.uclibc.org/docs/psABI-x86_64.pdf

# お役立ちリンク
- プログラムはどう動くのか? ～ ELFの黒魔術をかいまみる
  - http://ukai.jp/debuan/2002w/elf.html
- PLT, GOTについてわかりやすく説明してくれているスライド
   - http://ukai.jp/Slides/2006/1024-gree/binhacks.pdf
- https://www.slideshare.net/7shi/startprintf2-elf
  - 7shiさんの資料。各種セクションの説明、動的・静的ライブラリによるセクションの違いなどを説明している。
- ELF Hello World Tutorial
  - 英語の資料
  - http://www.cirosantilli.com/elf-hello-world/

# 未整理リンク
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
- The ELF Virus Writing HOWTO
  - http://www.linuxsecurity.com/resource_files/documentation/virus-writing-HOWTO/_html/index.html
- Linuxシステムコール徹底ガイド
  - https://postd.cc/the-definitive-guide-to-linux-system-calls/#kernelvsyscall-internals
- KernelのObject構造
  - http://caspar.hazymoon.jp/OpenBSD/lib/libsa/kernel_elf.html



