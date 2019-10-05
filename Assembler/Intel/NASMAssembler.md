# 概要
NASM(Netwide Assembler)とはx86用アセンブラの１つで、GASと同様にAT&T記法です。
ここではインストール方法やアセンブル方法などについて簡単に説明します。

特徴
- クロスプラットフォームである。GASと同様にNASMはほとんどのプラットフォームで動作する。
- オープンソースである

NASMのユーザーマニュアルは以下にあります。
- http://www.nasm.us/doc/

# 詳細
### インストール方法
```
$ wget "http://sourceforge.net/projects/nasm/files/nasm%20sources/2.07/nasm-2.07.tar.gz/download"
$ tar xvfz download
$ cd nasm-2.07
$ ./configure
$ make
$ su
# make install
```

- 参考
  -  http://dqn.sakusakutto.jp/2011/05/hello-world.html

### helloworldプログラム
helloworldプログラムを準備します。
```
$ vim hello.asm
section .text

global main

main:
  push dword len
  push dword msg
  push dword 1

  mov eax, 0x4
  sub esp, 4
  int 0x80

  add esp, 16

  push dword 0

  mov eax, 0x1
  sub esp, 4
  int 0x80

section .data
  msg db "Hello, World", 0xa
  len equ $-msg
```

アセンブルとリンカは次のコマンドで行います。
```
$ nasm -f macho hello.asm
$ ld -o hello -e main hello.o
$ ./hello
```

- 参考
  - http://ravelll.hatenadiary.jp/entry/2014/10/09/142134


<<<<<<< Updated upstream:Assembler/Intel/NASMAssembler.md
### 32bitアセンブル、64bitアセンブル
64bitシステムで32bit用のELFを作成する場合にはelf_i386が必要となります。
```
$ nasm -f elf helloworld.asm
$ ld -m elf_i386 helloworld.o -o helloworld
```

```
$ nasm -f elf64 helloworld_int.s
$ ld -s -o helloworld_int helloworld_int.o
```


# 参考URL
- NASM公式マニュアル
  - https://www.nasm.us/doc/
=======
###

```
helloworld_int:
    nasm -f elf64 helloworld_int.s
    ld -s -o helloworld_int helloworld_int.o
    ./helloworld_int
```


### オブジェクトファイルの出力フォーマットを指定する(fオプション)
hfオプションでどの形式を指定することができるのかを確認することができます。
よく指定するelf32, elf64, elf(elf32と同じ)などは以下で確認することができます。
```
$ nasm -hf
(snip)
valid output formats for -f are (`*' denotes default):
  * bin       flat-form binary files (e.g. DOS .COM, .SYS)
    ith       Intel hex
    srec      Motorola S-records
    aout      Linux a.out object files
    aoutb     NetBSD/FreeBSD a.out object files
    coff      COFF (i386) object files (e.g. DJGPP for DOS)
    elf32     ELF32 (i386) object files (e.g. Linux)
    elf64     ELF64 (x86_64) object files (e.g. Linux)
    elfx32    ELFX32 (x86_64) object files (e.g. Linux)
    as86      Linux as86 (bin86 version 0.3) object files
    obj       MS-DOS 16-bit/32-bit OMF object files
    win32     Microsoft Win32 (i386) object files
    win64     Microsoft Win64 (x86-64) object files
    rdf       Relocatable Dynamic Object File Format v2.0
    ieee      IEEE-695 (LADsoft variant) object file format
    macho32   NeXTstep/OpenStep/Rhapsody/Darwin/MacOS X (i386) object files
    macho64   NeXTstep/OpenStep/Rhapsody/Darwin/MacOS X (x86_64) object files
    dbg       Trace of all info passed to output stage
    elf       ELF (short name for ELF32)
    macho     MACHO (short name for MACHO32)
    win       WIN (short name for WIN32)
```

### nasmのfオプションとldのmオプションで指定する値の違い
以下にまとめています。
- https://github.com/tsuyopon/assembler/tree/master/nasm/helloworld

nasmではオブジェクトファイルの形式を指定して、ldでは実行プログラムのファイル形式を指定します。
上記リンクを見るとわかるようにオブジェクトファイルの形式に、ldで生成する実行プログラムのファイル形式は大きく依存します。

# 参考
- NASMユーザーマニュアル
  - http://www.nasm.us/doc/




