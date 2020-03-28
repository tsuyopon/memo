# readeld

ELFのフォーマットについてはELFFormat.mdでまとめています。

次の情報に分けて情報出力方法を記載しています。
- (1) ELFヘッダ(ELFファイルヘッダ、プログラムヘッダ、セクションヘッダ)
- (2) 各種section情報


- (1) ELFヘッダ
```
 ELFファイルヘッダ              -h    
 プログラムヘッダ               -l
 セクションヘッダ               -S
 3つのヘッダをまとめて出力      -e
```
 
- (2) section情報
```
 シンボルテーブル               -s
 リロケーション情報             -r
 ダイナミックセグメント         -d
 バージョンセクション           -V
 アーキテクチャ依存             -A
 パケットリスト長のヒストグラム	-I
 ヘッダすべてと以上の全て       -a
 コアノート                     -n
 unwind情報                     -u
```


# 詳細
## ELFヘッダ(ELFファイルヘッダ、プログラムヘッダ、セクションヘッダ)の読み出し

### ELFファイルヘッダを表示する
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
  Entry point address:               0x404b48
  Start of program headers:          64 (bytes into file)
  Start of section headers:          115736 (bytes into file)
  Flags:                             0x0
  Size of this header:               64 (bytes)
  Size of program headers:           56 (bytes)
  Number of program headers:         9
  Size of section headers:           64 (bytes)
  Number of section headers:         30
  Section header string table index: 29
```

### プログラムヘッダを出力する
```
$ readelf -l /bin/ls

Elf file type is EXEC (Executable file)
Entry point 0x404b48
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
                 0x00000000000193fc 0x00000000000193fc  R E    200000
  LOAD           0x000000000001a328 0x000000000061a328 0x000000000061a328
                 0x00000000000012d8 0x0000000000001ff8  RW     200000
  DYNAMIC        0x000000000001ada8 0x000000000061ada8 0x000000000061ada8
                 0x0000000000000200 0x0000000000000200  RW     8
  NOTE           0x0000000000000254 0x0000000000400254 0x0000000000400254
                 0x0000000000000044 0x0000000000000044  R      4
  GNU_EH_FRAME   0x0000000000016650 0x0000000000416650 0x0000000000416650
                 0x0000000000000744 0x0000000000000744  R      4
  GNU_STACK      0x0000000000000000 0x0000000000000000 0x0000000000000000
                 0x0000000000000000 0x0000000000000000  RW     10
  GNU_RELRO      0x000000000001a328 0x000000000061a328 0x000000000061a328
                 0x0000000000000cd8 0x0000000000000cd8  R      1

 Section to Segment mapping:
  Segment Sections...
   00     
   01     .interp 
   02     .interp .note.ABI-tag .note.gnu.build-id .gnu.hash .dynsym .dynstr .gnu.version .gnu.version_r .rela.dyn .rela.plt .init .plt .text .fini .rodata .eh_frame_hdr .eh_frame 
   03     .init_array .fini_array .jcr .data.rel.ro .dynamic .got .got.plt .data .bss 
   04     .dynamic 
   05     .note.ABI-tag .note.gnu.build-id 
   06     .eh_frame_hdr 
   07     
   08     .init_array .fini_array .jcr .data.rel.ro .dynamic .got 
```

### セクションヘッダ情報を表示する
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

### 特定のsection情報を確認する
「readelf -S /bin/ls」で各種セクションとその番号の情報が出力されていました。
前の例では15番セクションには.rodataがありましたが、このセクションをダンプするには次のようにします。
```
$ readelf -x15 /bin/ls

Hex dump of section '.rodata':
  0x00412980 01000200 00000000 00000000 00000000 ................
  0x00412990 00000000 00000000 00000000 00000000 ................
...
  0x00416610 e0b9ffff 0cbaffff 78737472 746f756d ........xstrtoum
  0x00416620 6178002f 7573722f 6c696236 34004153 ax./usr/lib64.AS
  0x00416630 43494900 43484152 53455441 4c494153 CII.CHARSETALIAS
  0x00416640 44495200 25353073 20253530 7300     DIR.%50s %50s.
```

### ELFヘッダ(ELFファイルヘッダ、プログラムヘッダ、セクションヘッダ)を全て出力する
ELFファイルヘッダ(hオプション)、プログラムヘッダ(lオプション)、セクションヘッダ(Sオプション)をまとめて出力してくれるのはeオプションです。
```
$ readelf -e /bin/ls
```

## section情報の取得

### .dynamicセクション
.dynamicセクションを参照することで共有ライブラリの情報を取得することができます。
```
$ readelf -d /bin/ls 

Dynamic section at offset 0x1ada8 contains 27 entries:
  Tag        Type                         Name/Value
 0x0000000000000001 (NEEDED)             Shared library: [libselinux.so.1]
 0x0000000000000001 (NEEDED)             Shared library: [libcap.so.2]
 0x0000000000000001 (NEEDED)             Shared library: [libacl.so.1]
 0x0000000000000001 (NEEDED)             Shared library: [libc.so.6]
 0x000000000000000c (INIT)               0x402228
 0x000000000000000d (FINI)               0x41295c
 0x0000000000000019 (INIT_ARRAY)         0x61a328
 0x000000000000001b (INIT_ARRAYSZ)       8 (bytes)
 0x000000000000001a (FINI_ARRAY)         0x61a330
 0x000000000000001c (FINI_ARRAYSZ)       8 (bytes)
 0x000000006ffffef5 (GNU_HASH)           0x400298
 0x0000000000000005 (STRTAB)             0x400f30
 0x0000000000000006 (SYMTAB)             0x4002d0
 0x000000000000000a (STRSZ)              1468 (bytes)
 0x000000000000000b (SYMENT)             24 (bytes)
 0x0000000000000015 (DEBUG)              0x0
 0x0000000000000003 (PLTGOT)             0x61b000
 0x0000000000000002 (PLTRELSZ)           2760 (bytes)
 0x0000000000000014 (PLTREL)             RELA
 0x0000000000000017 (JMPREL)             0x401760
 0x0000000000000007 (RELA)               0x401688
 0x0000000000000008 (RELASZ)             216 (bytes)
 0x0000000000000009 (RELAENT)            24 (bytes)
 0x000000006ffffffe (VERNEED)            0x4015f8
 0x000000006fffffff (VERNEEDNUM)         2
 0x000000006ffffff0 (VERSYM)             0x4014ec
 0x0000000000000000 (NULL)               0x0
```

### .dynsymを表示する(シンボル情報)
```
$ readelf -s hellopecl.so  | head -10

Symbol table '.dynsym' contains 28 entries:
  Num:    Value  Size Type    Bind   Vis      Ndx Name
    0: 00000000     0 NOTYPE  LOCAL  DEFAULT  UND
    1: 00000000     0 NOTYPE  WEAK   DEFAULT  UND __gmon_start__
    2: 00000000     0 NOTYPE  WEAK   DEFAULT  UND _Jv_RegisterClasses
    3: 00000000     0 NOTYPE  GLOBAL DEFAULT  UND zend_wrong_param_count
    4: 00000000   765 FUNC    GLOBAL DEFAULT  UND calloc@GLIBC_2.0 (2)
    5: 00000000     0 NOTYPE  GLOBAL DEFAULT  UND php_info_print_table_row
    6: 00000000     0 NOTYPE  GLOBAL DEFAULT  UND php_printf
```

### .rel.dyn, .rel.pltを表示する(リロケーション情報)
rオプションを付与することで.rel.dynと.rel.pltのセクション情報を表示します。
```
$ readelf -r hellopecl.so

Relocation section '.rel.dyn' at offset 0x52c contains 18 entries:
 Offset     Info    Type            Sym.Value  Sym. Name
00001bac  00000008 R_386_RELATIVE
00001ce0  00000008 R_386_RELATIVE
00001d00  00000008 R_386_RELATIVE
00001d54  00000008 R_386_RELATIVE
00001d70  00000008 R_386_RELATIVE
00001c78  00000106 R_386_GLOB_DAT    00000000   __gmon_start__
00001c7c  00000206 R_386_GLOB_DAT    00000000   _Jv_RegisterClasses
00001c80  00000d06 R_386_GLOB_DAT    00001d40   hellopecl_module_entry
00001c84  00001706 R_386_GLOB_DAT    00001d00   hellopecl_functions
00001d58  00001701 R_386_32          00001d00   hellopecl_functions
00001c88  00000c06 R_386_GLOB_DAT    00000000   __cxa_finalize
00001d04  00001301 R_386_32          00000810   zif_hello_pecl
00001d08  00001b01 R_386_32          00001d9c   hello_pecl_arg_info
00001d5c  00001001 R_386_32          00000930   zm_startup_hellopecl
00001d60  00001601 R_386_32          000007e0   zm_shutdown_hellopecl
00001d64  00001401 R_386_32          000007f0   zm_activate_hellopecl
00001d68  00000e01 R_386_32          00000800   zm_deactivate_hellopec
00001d6c  00001901 R_386_32          00000870   zm_info_hellopecl

Relocation section '.rel.plt' at offset 0x5bc contains 11 entries:
 Offset     Info    Type            Sym.Value  Sym. Name
00001c98  00000107 R_386_JUMP_SLOT   00000000   __gmon_start__
00001c9c  00000307 R_386_JUMP_SLOT   00000000   zend_wrong_param_count
00001ca0  00000407 R_386_JUMP_SLOT   00000000   calloc
00001ca4  00000507 R_386_JUMP_SLOT   00000000   php_info_print_table_r
00001ca8  00000607 R_386_JUMP_SLOT   00000000   php_printf
00001cac  00000707 R_386_JUMP_SLOT   00000000   php_info_print_table_e
00001cb0  00000807 R_386_JUMP_SLOT   00000000   php_info_print_table_s
00001cb4  00000907 R_386_JUMP_SLOT   00000000   _estrndup
00001cb8  00000a07 R_386_JUMP_SLOT   00000000   zend_register_internal
00001cbc  00000b07 R_386_JUMP_SLOT   00000000   malloc
00001cc0  00000c07 R_386_JUMP_SLOT   00000000   __cxa_finalize
```

### .gnu.versionと.gnu.version_rセクションを確認する
```
$ readelf -V hellopecl.so 

Version symbols section '.gnu.version' contains 28 entries:
 Addr: 00000000000004c4  Offset: 0x0004c4  Link: 2 (.dynsym)
  000:   0 (*local*)       0 (*local*)       0 (*local*)       0 (*local*)
  004:   2 (GLIBC_2.0)     0 (*local*)       0 (*local*)       0 (*local*)
  008:   0 (*local*)       0 (*local*)       0 (*local*)       2 (GLIBC_2.0)
  00c:   3 (GLIBC_2.1.3)   1 (*global*)      1 (*global*)      1 (*global*)
  010:   1 (*global*)      1 (*global*)      1 (*global*)      1 (*global*)
  014:   1 (*global*)      1 (*global*)      1 (*global*)      1 (*global*)
  018:   1 (*global*)      1 (*global*)      1 (*global*)      1 (*global*)

Version needs section '.gnu.version_r' contains 1 entries:
 Addr: 0x00000000000004fc  Offset: 0x0004fc  Link to section: 3 (.dynstr)
  000000: Version: 1  File: libc.so.6  Cnt: 2
  0x0010:   Name: GLIBC_2.1.3  Flags: none  Version: 3
  0x0020:   Name: GLIBC_2.0  Flags: none  Version: 2
```

### .shstrtabを表示する
.shstrtabセクションにはセクション名の文字列が格納されています。
```
$ readelf -p .shstrtab /bin/ls

String dump of section '.shstrtab':
  [     1]  .shstrtab
  [     b]  .interp
  [    13]  .note.ABI-tag
  [    21]  .note.gnu.build-id
  [    34]  .gnu.hash
  [    3e]  .dynsym
  [    46]  .dynstr
  [    4e]  .gnu.version
  [    5b]  .gnu.version_r
  [    6a]  .rela.dyn
  [    74]  .rela.plt
  [    7e]  .init
  [    84]  .text
  [    8a]  .fini
  [    90]  .rodata
  [    98]  .eh_frame_hdr
  [    a6]  .eh_frame
  [    b0]  .init_array
  [    bc]  .fini_array
  [    c8]  .jcr
  [    cd]  .data.rel.ro
  [    da]  .dynamic
  [    e3]  .got
  [    e8]  .got.plt
  [    f1]  .data
  [    f7]  .bss
  [    fc]  .gnu_debuglink
  [   10b]  .gnu_debugdata
```

### .interpセクションを表示する
動的リンクを行う外部プログラムが.interpに格納されている。
```
$ readelf -p .interp /bin/ls

String dump of section '.interp':
  [     0]  /lib64/ld-linux-x86-64.so.2
```

### バケットリスト(?)を表示する(不明)
何を表しているのか不明(要確認)
```
$ readelf -I hellopecl.so

Histogram for `.gnu.hash' bucket list length (total of 3 buckets):
 Length  Number     % of total  Coverage
      0  0          (  0.0%)
      1  0          (  0.0%)      0.0%
      2  0          (  0.0%)      0.0%
      3  1          ( 33.3%)     20.0%
      4  0          (  0.0%)     20.0%
      5  0          (  0.0%)     20.0%
      6  2          ( 66.7%)    100.0%
```

### 全情報を表示する
迷ったらとりあえずこれを実行すればreadelfで得られるほぼ全ての情報を得られます。
```
$ readelf -a hellopecl.so
```

### 1行80文字表示の制限を取っ払う

通常だと1行80文字制限で出力が打ち切られてしまいます。 コマンド実行例で比較してみます。

以下はWを付与しない場合の例です。
```
$  readelf -s  /usr/lib64/libcrypt.so | tail -5
   142: 0000000000000000     0 NOTYPE  WEAK   DEFAULT  UND _ITM_registerTMCloneTable
   143: 0000000000000000     0 FUNC    GLOBAL DEFAULT  UND __libc_alloca_cutoff@@GLI
   144: 0000000000000000     0 FUNC    WEAK   DEFAULT  UND __cxa_finalize@@GLIBC_2.2
   145: 0000000000001210   390 FUNC    WEAK   DEFAULT   14 fcrypt
   146: 0000000000000000     0 OBJECT  GLOBAL DEFAULT  ABS GLIBC_2.2.5
```

Wオプションを付与することでシンボルが途中で打ち切られていないことを確認できます。
```
$  readelf -Ws  /usr/lib64/libcrypt.so | tail -5
   142: 0000000000000000     0 NOTYPE  WEAK   DEFAULT  UND _ITM_registerTMCloneTable
   143: 0000000000000000     0 FUNC    GLOBAL DEFAULT  UND __libc_alloca_cutoff@@GLIBC_PRIVATE
   144: 0000000000000000     0 FUNC    WEAK   DEFAULT  UND __cxa_finalize@@GLIBC_2.2.5
   145: 0000000000001210   390 FUNC    WEAK   DEFAULT   14 fcrypt
   146: 0000000000000000     0 OBJECT  GLOBAL DEFAULT  ABS GLIBC_2.2.5
```


# 参考資料
- readelf manpage
  - http://sourceware.org/binutils/docs-2.16/binutils/readelf.html
- StackOverflow: How do I list the symbols in a .so file
  - https://stackoverflow.com/questions/34732/how-do-i-list-the-symbols-in-a-so-file?noredirect=1&lq=1

