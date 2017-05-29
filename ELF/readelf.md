#  概要
このページでは、readelfコマンドについてまとめます。
- ELFヘッダの読み出し
```
 ELFファイルヘッダ              -h    
 プログラムヘッダ               -l
 セクションヘッダ               -S
 以上3つのヘッダ                -e
```
 
- ELF情報の読み出し
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
## ELFヘッダの読み出し

### ELF仕様書
- http://www.skyfree.org/linux/references/ELF_Format.pdf

### readelfコマンドを利用する
オプションは通常は-hを利用する。
```
$ readelf -h a.out
ELF ヘッダ:
  マジック:  7f 45 4c 46 01 01 01 00 00 00 00 00 00 00 00 00
  クラス:                            ELF32
  データ:                            2 の補数、リトルエンディアン
  バージョン:                        1 (current)
  OS/ABI:                            UNIX - System V
  ABI バージョン:                    0
  タイプ:                            EXEC (実行可能ファイル)
  マシン:                            Intel 80386
  バージョン:                        0x1
  エントリポイントアドレス:          0x8048278
  プログラムの開始ヘッダ:            52 (バイト)
  セクションヘッダ始点:              7476 (バイト)
  フラグ:                            0x0
  このヘッダのサイズ:                52 (バイト)
  プログラムヘッダサイズ:            32 (バイト)
  プログラムヘッダ数:                6
  セクションヘッダ:                  40 (バイト)
  Number of section headers:         34
  Section header string table index: 31
```

### -lオプションもよく利用される
```
$ readelf -l hellopecl.so

Elf file type is DYN (Shared object file)
Entry point 0x6f0
There are 4 program headers, starting at offset 52

Program Headers:
  Type           Offset   VirtAddr   PhysAddr   FileSiz MemSiz  Flg Align
  LOAD           0x000000 0x00000000 0x00000000 0x00b98 0x00b98 R E 0x1000
  LOAD           0x000b98 0x00001b98 0x00001b98 0x00200 0x00220 RW  0x1000
  DYNAMIC        0x000bb0 0x00001bb0 0x00001bb0 0x000c8 0x000c8 RW  0x4
  GNU_STACK      0x000000 0x00000000 0x00000000 0x00000 0x00000 RW  0x4

 Section to Segment mapping:
  Segment Sections...
   00     .gnu.hash .dynsym .dynstr .gnu.version .gnu.version_r .rel.dyn .rel.plt .init .plt .text .fini .rodata .eh_frame
   01     .ctors .dtors .jcr .data.rel.ro .dynamic .got .got.plt .data .bss
   02     .dynamic
   03
```

### -Sオプションを以下に載せる
```
$ readelf -S hellopecl.so
There are 35 section headers, starting at offset 0x51a0:

Section Headers:
  [Nr] Name              Type            Addr     Off    Size   ES Flg Lk Inf Al
  [ 0]                   NULL            00000000 000000 000000 00      0   0  0
  [ 1] .gnu.hash         GNU_HASH        000000b4 0000b4 000068 04   A  2   0  4
		(途中略)
  [32] .shstrtab         STRTAB          00000000 005064 00013a 00      0   0  1
  [33] .symtab           SYMTAB          00000000 005718 000510 10     34  54  4
  [34] .strtab           STRTAB          00000000 005c28 000319 00      0   0  1
Key to Flags:
  W (write), A (alloc), X (execute), M (merge), S (strings)
  I (info), L (link order), G (group), x (unknown)
  O (extra OS processing required) o (OS specific), p (processor specific)
```

### h, l, Sオプション３つを一括で実行する
```
$ readelf -e a.out
```

## ELF情報の読み出し

### シンボルテーブルを表示する
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

### リロケーション情報を表示する
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

### 共有ライブラリの依存関係を調べる
```
$ readelf -d /bin/ls
Dynamic segment at offset 0x14f00 contains 22 entries:
Tag        Type                         Name/Value
0x00000001 (NEEDED)                     Shared library: [librt.so.1]
0x00000001 (NEEDED)                     Shared library: [libacl.so.1]
0x00000001 (NEEDED)                     Shared library: [libc.so.6]
0x0000000c (INIT)                       0x10002698
0x0000000d (FINI)                       0x100114c4
0x00000004 (HASH)                       0x10000184
0x00000005 (STRTAB)                     0x100015a8
0x00000006 (SYMTAB)                     0x10000808
0x0000000a (STRSZ)                      2545 (bytes)
0x0000000b (SYMENT)                     16 (bytes)
0x00000015 (DEBUG)                      0x0
0x00000003 (PLTGOT)                     0x10025120
0x00000002 (PLTRELSZ)                   1116 (bytes)
0x00000014 (PLTREL)                     RELA
0x00000017 (JMPREL)                     0x1000223c
0x00000007 (RELA)                       0x10002200
0x00000008 (RELASZ)                     1176 (bytes)
0x00000009 (RELAENT)                    12 (bytes)
0x6ffffffe (VERNEED)                    0x10002150
0x6fffffff (VERNEEDNUM)                 3
0x6ffffff0 (VERSYM)                     0x10001f9a
0x00000000 (NULL)                       0x0
```
上記によりlsの実行に際しても、librt.so.1, libacl.so.1, libc.so.6が必要となることがわかる。

### バージョン情報を調べる
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
迷ったらとりあえずこれを実行すればreadelfで得られるほぼ全ての情報を得られるものと思われます。
```
$ readelf -a hellopecl.so
```

- readelf
  - http://sourceware.org/binutils/docs-2.16/binutils/readelf.html

