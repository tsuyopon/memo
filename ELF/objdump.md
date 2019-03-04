# 概要
objdumpについてまとめます。オプションは下記のとおりです。
```
$ objdump
Usage: objdump <option(s)> <file(s)>
 Display information from object <file(s)>.
 At least one of the following switches must be given:
  -a, --archive-headers    Display archive header information
  -f, --file-headers       Display the contents of the overall file header
  -p, --private-headers    Display object format specific file header contents
  -h, --[section-]headers  Display the contents of the section headers
  -x, --all-headers        Display the contents of all headers
  -d, --disassemble        Display assembler contents of executable sections
  -D, --disassemble-all    Display assembler contents of all sections
  -S, --source             Intermix source code with disassembly
  -s, --full-contents      Display the full contents of all sections requested
  -g, --debugging          Display debug information in object file
  -e, --debugging-tags     Display debug information using ctags style
  -G, --stabs              Display (in raw form) any STABS info in the file
  -W, --dwarf              Display DWARF info in the file
  -t, --syms               Display the contents of the symbol table(s)
  -T, --dynamic-syms       Display the contents of the dynamic symbol table
  -r, --reloc              Display the relocation entries in the file
  -R, --dynamic-reloc      Display the dynamic relocation entries in the file
  @<file>                  Read options from <file>
  -v, --version            Display this program's version number
  -i, --info               List object formats and architectures supported
  -H, --help               Display this information
```

# 詳細

### ライブラリ内で設定されているrpathを確認する
```
$ objdump -x n/grep | grep -i rpath
```

### ライブラリ内で依存しているライブラリのみを表示する
lddを使ってELFの依存ライブラリを参照することができますが、lddの場合だと依存しているライブラリまで取得してしまいます。
そこで
```
$ objdump -p /usr/bin/grep | grep -i needed
  NEEDED               libpcre.so.1
  NEEDED               libc.so.6
```


### アーカイブヘッダ情報を表示する
```
$ objdump -a /usr/lib/libcrypt.a
In archive /usr/lib/libcrypt.a:

crypt-entry.o:     file format elf32-i386
rw-r--r-- 100/500   1524 Mar 13 21:49 2007 crypt-entry.o

md5-crypt.o:     file format elf32-i386
rw-r--r-- 100/500   4236 Mar 13 21:49 2007 md5-crypt.o

md5.o:     file format elf32-i386
rw-r--r-- 100/500   4768 Mar 13 21:49 2007 md5.o

crypt.o:     file format elf32-i386
rw-r--r-- 100/500    957 Mar 13 21:49 2007 crypt.o

crypt_util.o:     file format elf32-i386
rw-r--r-- 100/500  11952 Mar 13 21:49 2007 crypt_util.o
```

### ファイルヘッダ情報を表示する
```
$ objdump -f hellopecl.so

hellopecl.so:     file format elf32-i386
architecture: i386, flags 0x00000150:
HAS_SYMS, DYNAMIC, D_PAGED
start address 0x000006f0
```

### オブジェクトファイル特有のファイルヘッダ情報を表示する
```
$ objdump -p hellopecl.so

hellopecl.so:     file format elf32-i386

Program Header:
    LOAD off    0x00000000 vaddr 0x00000000 paddr 0x00000000 align 2**12
         filesz 0x00000b98 memsz 0x00000b98 flags r-x
    LOAD off    0x00000b98 vaddr 0x00001b98 paddr 0x00001b98 align 2**12
         filesz 0x00000200 memsz 0x00000220 flags rw-
 DYNAMIC off    0x00000bb0 vaddr 0x00001bb0 paddr 0x00001bb0 align 2**2
         filesz 0x000000c8 memsz 0x000000c8 flags rw-
   STACK off    0x00000000 vaddr 0x00000000 paddr 0x00000000 align 2**2
         filesz 0x00000000 memsz 0x00000000 flags rw-

Dynamic Section:
  NEEDED      libc.so.6
  SONAME      hellopecl.so
  INIT        0x614
  FINI        0xaa4
  GNU_HASH    0xb4
  STRTAB      0x2dc
  SYMTAB      0x11c
  STRSZ       0x1e7
  SYMENT      0x10
  PLTGOT      0x1c8c
  PLTRELSZ    0x58
  PLTREL      0x11
  JMPREL      0x5bc
  REL         0x52c
  RELSZ       0x90
  RELENT      0x8
  VERNEED     0x4fc
  VERNEEDNUM  0x1
  VERSYM      0x4c4
  RELCOUNT    0x5

Version References:
  required from libc.so.6:
    0x09691f73 0x00 03 GLIBC_2.1.3
    0x0d696910 0x00 02 GLIBC_2.0
```

### セクションヘッダ情報を表示する
```
$ objdump -h hellopecl.so

hellopecl.so:     file format elf32-i386

Sections:
Idx Name          Size      VMA       LMA       File off  Algn
  0 .gnu.hash     00000068  000000b4  000000b4  000000b4  2**2
                  CONTENTS, ALLOC, LOAD, READONLY, DATA
  1 .dynsym       000001c0  0000011c  0000011c  0000011c  2**2
                  CONTENTS, ALLOC, LOAD, READONLY, DATA
  2 .dynstr       000001e7  000002dc  000002dc  000002dc  2**0
                  CONTENTS, ALLOC, LOAD, READONLY, DATA
  3 .gnu.version  00000038  000004c4  000004c4  000004c4  2**1
                  CONTENTS, ALLOC, LOAD, READONLY, DATA
  4 .gnu.version_r 00000030  000004fc  000004fc  000004fc  2**2
                  CONTENTS, ALLOC, LOAD, READONLY, DATA
 (以下略)
```

### 全ヘッダ情報を表示する
```
$ objdump -x hellopecl.so  | head -15

hellopecl.so:     file format elf32-i386
hellopecl.so
architecture: i386, flags 0x00000150:
HAS_SYMS, DYNAMIC, D_PAGED
start address 0x000006f0

Program Header:
    LOAD off    0x00000000 vaddr 0x00000000 paddr 0x00000000 align 2**12
         filesz 0x00000b98 memsz 0x00000b98 flags r-x
    LOAD off    0x00000b98 vaddr 0x00001b98 paddr 0x00001b98 align 2**12
         filesz 0x00000200 memsz 0x00000220 flags rw-
 DYNAMIC off    0x00000bb0 vaddr 0x00001bb0 paddr 0x00001bb0 align 2**2
         filesz 0x000000c8 memsz 0x000000c8 flags rw-
   STACK off    0x00000000 vaddr 0x00000000 paddr 0x00000000 align 2**2
```

### 実行セクション部をアセンブラに変換します
```
$ objdump -d hellopecl.so  | head -10

hellopecl.so:     file format elf32-i386

Disassembly of section .init:

00000614 <_init>:
 614:   55                      push   %ebp
 615:   89 e5                   mov    %esp,%ebp
 617:   83 ec 08                sub    $0x8,%esp
 61a:   e8 d1 00 00 00          call   6f0 <call_gmon_start>
```

### 全セクション部をアセンブラに変換します
```
$ objdump -D hellopecl.so  | head -10

hellopecl.so:     file format elf32-i386

Disassembly of section .gnu.hash:

000000b4 <.gnu.hash>:
  b4:   03 00                   add    (%eax),%eax
  b6:   00 00                   add    %al,(%eax)
  b8:   0d 00 00 00 04          or     $0x4000000,%eax
  bd:   00 00                   add    %al,(%eax)
```

mainからのアセンブラ情報を表示する場合には以下のようにgrepをかけます。
```
$ objdump -D ./a.out | grep -A 20 main.:
00000000004004dc <main>:
  4004dc:	55                   	push   %rbp
  4004dd:	48 89 e5             	mov    %rsp,%rbp
  4004e0:	48 83 ec 10          	sub    $0x10,%rsp
  4004e4:	c7 45 fc 00 00 00 00 	movl   $0x0,-0x4(%rbp)
  4004eb:	eb 0e                	jmp    4004fb <main+0x1f>
  4004ed:	bf c0 05 40 00       	mov    $0x4005c0,%edi
  4004f2:	e8 b9 fe ff ff       	callq  4003b0 <puts@plt>
  4004f7:	83 45 fc 01          	addl   $0x1,-0x4(%rbp)
  4004fb:	83 7d fc 09          	cmpl   $0x9,-0x4(%rbp)
  4004ff:	7e ec                	jle    4004ed <main+0x11>
  400501:	b8 00 00 00 00       	mov    $0x0,%eax
  400506:	c9                   	leaveq 
  400507:	c3                   	retq   
  400508:	0f 1f 84 00 00 00 00 	nopl   0x0(%rax,%rax,1)
  40050f:	00 

0000000000400510 <__libc_csu_init>:
  400510:	48 89 6c 24 d8       	mov    %rbp,-0x28(%rsp)
  400515:	4c 89 64 24 e0       	mov    %r12,-0x20(%rsp)
  40051a:	48 8d 2d 8f 01 20 00 	lea    0x20018f(%rip),%rbp        # 6006b0 <__init_array_end>
```

上記はATT形式ですが、intelの表記形式で出力するには-M intelオプションを付与します。
```
$ objdump -M intel -D ./a.out | grep -A 20 main.:
00000000004004dc <main>:
  4004dc:	55                   	push   rbp
  4004dd:	48 89 e5             	mov    rbp,rsp
  4004e0:	48 83 ec 10          	sub    rsp,0x10
  4004e4:	c7 45 fc 00 00 00 00 	mov    DWORD PTR [rbp-0x4],0x0
  4004eb:	eb 0e                	jmp    4004fb <main+0x1f>
  4004ed:	bf c0 05 40 00       	mov    edi,0x4005c0
  4004f2:	e8 b9 fe ff ff       	call   4003b0 <puts@plt>
  4004f7:	83 45 fc 01          	add    DWORD PTR [rbp-0x4],0x1
  4004fb:	83 7d fc 09          	cmp    DWORD PTR [rbp-0x4],0x9
  4004ff:	7e ec                	jle    4004ed <main+0x11>
  400501:	b8 00 00 00 00       	mov    eax,0x0
  400506:	c9                   	leave  
  400507:	c3                   	ret    
  400508:	0f 1f 84 00 00 00 00 	nop    DWORD PTR [rax+rax*1+0x0]
  40050f:	00 

0000000000400510 <__libc_csu_init>:
  400510:	48 89 6c 24 d8       	mov    QWORD PTR [rsp-0x28],rbp
  400515:	4c 89 64 24 e0       	mov    QWORD PTR [rsp-0x20],r12
  40051a:	48 8d 2d 8f 01 20 00 	lea    rbp,[rip+0x20018f]        # 6006b0 <__init_array_end>
```

### Intermix source code with disassemble
Sオプションについての出力結果だが、dオプションと何が違うんだろう??
```
$ objdump -S hellopecl.so   | head -10

hellopecl.so:     file format elf32-i386

Disassembly of section .init:

00000614 <_init>:
 614:   55                      push   %ebp
 615:   89 e5                   mov    %esp,%ebp
 617:   83 ec 08                sub    $0x8,%esp
 61a:   e8 d1 00 00 00          call   6f0 <call_gmon_start>
```

### 全セクション部のフルコンテンツ情報を表示します
```
$ objdump -s hellopecl.so   | head -10

hellopecl.so:     file format elf32-i386

Contents of section .gnu.hash:
 00b4 03000000 0d000000 04000000 07000000  ................
 00c4 00006000 80810809 18452061 81048412  ..`......E a....
 00d4 0d000000 13000000 19000000 323407eb  ............24..
 00e4 fc6b093d bae3927c 144b308d ea9c0b70  .k.=...|.K0....p
 00f4 4345d5ec 44a4f89d b287edc2 d871581c  CE..D........qX.
 0104 5e24cfde 54e5a235 b98df10e cebe947f  ^$..T..5........
```

### ファイル中のDWARFを表示する
http://ja.wikipedia.org/wiki/DWARF を表示します。
```
$ objdump -W hellopecl.so   | less

hellopecl.so:     file format elf32-i386

The section .debug_aranges contains:

  Length:                   28
  Version:                  2
  Offset into .debug_info:  0
  Pointer Size:             4
  Segment Size:             0

    Address    Length
    0x000007c0 0x2a1
    0x00000000 0x0

Contents of the .debug_pubnames section:

  Length:                              250
  Version:                             2
  Offset into .debug_info section:     0
  Size of area in .debug_info section: 9406

    Offset      Name
    8748                get_module
    8773                zm_shutdown_hellopecl
    8831                zm_activate_hellopecl
    8889                zm_deactivate_hellopecl
    8947                zif_hello_pecl
    9065                zm_info_hellopecl
    9105                zm_startup_hellopecl
    9319                hellopecl_module_entry
    9353                hello_pecl_arg_info
    9387                hellopecl_functions

The section .debug_info contains:

  Compilation Unit @ offset 0x0:
   Length:        9402
   Version:       2
   Abbrev Offset: 0
   Pointer Size:  4
 <0><b>: Abbrev Number: 1 (DW_TAG_compile_unit)
     DW_AT_stmt_list   : 0
     DW_AT_high_pc     : 0xa61
     DW_AT_low_pc      : 0x7c0
     DW_AT_producer    : (indirect string, offset: 0x9ac): GNU C 4.1.1 20070105 (Red Hat 4.1.1-52)
     DW_AT_language    : 1      (ANSI C)
     DW_AT_name        : (indirect string, offset: 0x6d9): /home/tsuyoshi/work/php-extension/test/hellopecl/hellopecl.c
```

### シンボルテーブルを表示します
```
$ objdump -t hellopecl.so   | head -10

hellopecl.so:     file format elf32-i386

SYMBOL TABLE:
000000b4 l    d  .gnu.hash      00000000              .gnu.hash
0000011c l    d  .dynsym        00000000              .dynsym
000002dc l    d  .dynstr        00000000              .dynstr
000004c4 l    d  .gnu.version   00000000              .gnu.version
000004fc l    d  .gnu.version_r 00000000              .gnu.version_r
0000052c l    d  .rel.dyn       00000000              .rel.dyn
```

### ダイナミックシンボルテーブルを表示します
```
$ objdump -T hellopecl.so   | head -10

hellopecl.so:     file format elf32-i386

DYNAMIC SYMBOL TABLE:
00000000  w   D  *UND*  00000000              __gmon_start__
00000000  w   D  *UND*  00000000              _Jv_RegisterClasses
00000000      D  *UND*  00000000              zend_wrong_param_count
00000000      DF *UND*  000002fd  GLIBC_2.0   calloc
00000000      D  *UND*  00000000              php_info_print_table_row
00000000      D  *UND*  00000000              php_printf
```

### ダイナミックリロケーションレコード
```
$ objdump -R hellopecl.so | head -15

hellopecl.so:     file format elf32-i386

DYNAMIC RELOCATION RECORDS
OFFSET   TYPE              VALUE
00001bac R_386_RELATIVE    *ABS*
00001ce0 R_386_RELATIVE    *ABS*
00001d00 R_386_RELATIVE    *ABS*
00001d54 R_386_RELATIVE    *ABS*
00001d70 R_386_RELATIVE    *ABS*
00001c78 R_386_GLOB_DAT    __gmon_start__
00001c7c R_386_GLOB_DAT    _Jv_RegisterClasses
00001c80 R_386_GLOB_DAT    hellopecl_module_entry
00001c84 R_386_GLOB_DAT    hellopecl_functions
00001d58 R_386_32          hellopecl_functions
```

### オブジェクトフォーマットやアーキテクチャに関するサポート情報を表示する
```
$ objdump -i
BFD header file version 2.17.50.0.6-2.el5 20061020
elf32-i386
 (header little endian, data little endian)
  i386
a.out-i386-linux
 (header little endian, data little endian)
  i386
efi-app-ia32
 (header little endian, data little endian)
  i386
elf32-little
 (header little endian, data little endian)
  i386
elf32-big
 (header big endian, data big endian)
  i386
srec
 (header endianness unknown, data endianness unknown)
  i386
symbolsrec
 (header endianness unknown, data endianness unknown)
  i386
tekhex
 (header endianness unknown, data endianness unknown)
  i386
binary
 (header endianness unknown, data endianness unknown)
  i386
ihex
 (header endianness unknown, data endianness unknown)
  i386
trad-core
 (header endianness unknown, data endianness unknown)

               elf32-i386 a.out-i386-linux efi-app-ia32 elf32-little elf32-big
          i386 elf32-i386 a.out-i386-linux efi-app-ia32 elf32-little elf32-big

               srec symbolsrec tekhex binary ihex trad-core
          i386 srec symbolsrec tekhex binary ihex ---------
```

