

##############################################################
Binutils超概要
##############################################################
* 概要
Binutilsは、バイナリ操作や情報取得に必要な次のコマンドを含んでいます。
- addr2line,ar,as,c++filt,gprof,ld,nm,objcopy,objdump,ranlib,readelf,size,strings,strip


* 詳細
*** [[addr2line]]
- プログラムアドレスをファイル名と行番号に翻訳する。

*** [[ar]]
- アーカイブを作り、修整し、またそこからファイルを引き出す。

*** [[as]]
- アセンブラです。gccからの出力をオブジェクトファイルにアセンブルします。

*** [[c++filt]]
- リンかによって使われており、関数名の衝突を避けるために台なし(mangle)にされたC++とJavaのシンボル芽衣を元に戻す(demangle)為に使われます。

*** [[gprof]]
- グラフ呼び出しプロファイル情報を表示する。

*** [[ld]]
- リンカです。これは数多くのオブジェクトとアーカイブファイルを一つのファイルに結合し、それらのデータを再配置し、シンボルへの参照を結びつける。

*** [[nm]]
- 与えられたオブジェクトファイルの茄かに存在するシンボルをリストします。

*** [[objcopy]]
- 一種のオブジェクトファイルを他の種類に翻訳するのに使われる。

*** [[objdump]]
- 与えられたオブジェクトファイルについての情報を表示する。

*** [[ranlib]]
- アーカイブの内容の目録を作成し、それをアーカイブの茄かに保管します。

*** [[readelf]]
- elfタイプのバイナリについての情報を表示します。

*** [[size]]
- 与えられたオブジェクトファイルについて、セクションと包括的な全体のサイズをリストします。

*** [[strings]]
- 与えられたそれぞれのファイルについて、少なくとも特定の長さ(デフォルトでは4)の表示可能な門司の一続きを出力する。

*** [[strip]]
- オブジェクトファイルからシンボルを捨てます。

*** その他のBinutilsに含まれるライブラリに関する説明
- libiberty
-- 様々なGNUプログラムに使用されるgetoptやobstack,strerror,strtol,strtoulなどのルーチンを含む。

- libbfd
-- バイナリファイルデスクリプタのライブラリです。

- libopcodes
-- opcodeをあつかう為のライブラリ。これはobjdumpなどのユーティリティを構築する為に使用される。Opcodeは人に読める文章版のプロセッサへの説明。

* 参考URL [#q536f7fa]
- GNU Binary Utils
-- http://www.geocities.jp/fut_nis/html/binutils-ja/index.html#Top
- The Linux ELF HOWTO
-- http://www.linux.or.jp/JF/JFdocs/archive/ELF-HOWTO.html
- 組み込みLinux開発の手引き
-- http://www26.atwiki.jp/funa_tk/pages/22.html


##############################################################
arコマンド
##############################################################
*** スタティックライブラリを作成したり、ばらばらにする方法 [#aba5f3c9]
arコマンドを使用する。
arコマンドは書庫の作成、変更、及び書庫からのファイルの取りだしを行なうコマンド
例えば、liblapack.aをバラバラに各々のオブジェクトファイルに分割する時は次の様にする。      
	 $ar -x liblapack.a

次に例えば、/home/tsuyoshi/objectfilesディレクトリにある全てのオブジェクトファ
イルから、自分で/libcustomize.aというスタティックライブラリを作成したい時は次の
様にする。
	 $ar -r libcustomize.a  /home/tsuyoshi/objectfiles/*.o

中の各種ファイルを見たい場合には以下の様にする
	 $ ar -tv /usr/lib/libc.a
	 rw-r--r-- 0/0   1580 Mar  6 07:17 2007 init-first.o
	 rw-r--r-- 0/0   3200 Mar  6 07:17 2007 libc-start.o
	 rw-r--r-- 0/0    792 Mar  6 07:17 2007 sysdep.o
	 rw-r--r-- 0/0   2060 Mar  6 07:17 2007 version.o
	 rw-r--r-- 0/0   1268 Mar  6 07:17 2007 check_fds.o
	 rw-r--r-- 0/0    856 Mar  6 07:17 2007 libc-tls.o
	 rw-r--r-- 0/0   1480 Mar  6 07:17 2007 elf-init.o
	 (以下略)

arコマンドで生成されるものが.oファイルの塊ということはその中にもシンボルやデバッグシンボルが含まれる
ということを意味しています。

##############################################################
gprofコマンド
##############################################################
*** プロファイリングをしたい(gcc) [#w917f87d]
例えば、test.cというプログラムが何の関数を主に呼んでいるかを調べたいとする。
この時、次のようにする。
	 $gcc -g -pg -o test test.c
	 $./test
	 $ls
	   test.c   test   gmon.out   <=プログラムを実行するとgmon.outが出来る。
	 $gprof -b test
gmon.outはプロファイルの為のファイルである。



##############################################################
ldコマンド
##############################################################
*** ld(GNUのリンカ)を使用する。 [#l1c1b7d1]
例えば次の例を見てみることとする。
	 $ld -o output /lib/crt0.o hello.o -lc  <=一番良く使用される例
この例では、ldにoutputという名前のファイルを作成するように命令している。
リンクするファイルは/lib/crt0.oとhello.o及び標準的な検索ディレクトリ(/usr/lib,/libなど)にあるライブラリlibc.aであるという亊を意味している。


##############################################################
nmコマンド
##############################################################
*** 共有ライブラリの作成方法と確認方法 [#u1cf2e3f]
[共有ライブラリの作成方法]
次のようにすると、test1.oとtest2.oの静的共有ライブラリ(libcustomize.so)が作成される。
	 $gcc -shared -o libcustomize.so  test1.o test2.o
※一般的には、拡張子がso(shared object)ファイルは慣用的にlibname.so.x.yと書かれる。xは共有ライブラリのmajor番号、yはminor番号表す。
soファイルはcygwinなどにおけるdllと同じ働きをする。

[共有ライブラリの確認方法]
次のようにすればよい
	 $nm libname.so

なお、C++の場合にはマングリングされていて読みにくいのでdemangleオプションを付与するとよい。
     $ nm --demangle libname.so
または以下のようにc++filtコマンドを利用することも可能
	 $nm -o libname.so | c++filt

シンボルがあるかどうかはfileコマンドで確認することができる「not stripped」や「stripped」といった情報が表示される。

*** オブジェクトファイルのシンボルを確認する [#k6531f5a]
以下のようなhello.cをオブジェクトファイルにします。
	 #include
	 int main(){ printf("Hello World\n"); }
上記を保存してオブジェクトファイルにします。
	 $ gcc -c hello.c
	 $ ls 
	  hello.c    hello.o
上記の様にgccに-cオプションを行うと.o(オブジェクトファイル)が作成される

上記のシンボルを以下のようにして確認する。
	 $ nm hello.o
	 00000000 T main
	          U printf

*** 記号の意味について [#ocecf516]
小文字はそのシンボルがローカルであることを意味し、大文字はそのシンボルがグローバル (外部定義) であることを意味します。
典型的なシンボルタイプについては以下のとおりです
	 T コードセクション内の定義
	 D 初期化されたデータセクション
	 B 初期化されないデータセクション
	 U 未定義。シンボルはライブラリによって使われているが、ライブラリ内では定義されていない
	 W weak. 他のライブラリも同じシンボルを定義している場合、その定義によりオーバーライドされる

##############################################################
objdumpコマンド
##############################################################
[[Binutils]]

* 概要 [#cda8b21e]
objdumpについてまとめます。オプションは下記のとおりです。
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

* 詳細 [#t941e799]
*** アーカイブヘッダ情報を表示する [#scbf158f]
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

*** ファイルヘッダ情報を表示する [#de3582ab]
	 $ objdump -f hellopecl.so
	 
	 hellopecl.so:     file format elf32-i386
	 architecture: i386, flags 0x00000150:
	 HAS_SYMS, DYNAMIC, D_PAGED
	 start address 0x000006f0

*** オブジェクトファイル特有のファイルヘッダ情報を表示する [#x78fe0f5]
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

*** セクションヘッダ情報を表示する [#n156672a]
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

*** 全ヘッダ情報を表示する [#l086cb33]
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


*** 実行セクション部をアセンブラに変換します。 [#lc69c710]
	 $ objdump -d hellopecl.so  | head -10
	 
	 hellopecl.so:     file format elf32-i386
	 
	 Disassembly of section .init:
	 
	 00000614 <_init>:
	  614:   55                      push   %ebp
	  615:   89 e5                   mov    %esp,%ebp
	  617:   83 ec 08                sub    $0x8,%esp
	  61a:   e8 d1 00 00 00          call   6f0 <call_gmon_start>


*** 全セクション部をアセンブラに変換します。 [#c8a0d508]
	 $ objdump -D hellopecl.so  | head -10
	 
	 hellopecl.so:     file format elf32-i386
	 
	 Disassembly of section .gnu.hash:
	 
	 000000b4 <.gnu.hash>:
	   b4:   03 00                   add    (%eax),%eax
	   b6:   00 00                   add    %al,(%eax)
	   b8:   0d 00 00 00 04          or     $0x4000000,%eax
	   bd:   00 00                   add    %al,(%eax)

mainからのアセンブラ情報を表示する場合には以下のようにgrepをかけます。
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

上記はATT形式ですが、intelの表記形式で出力するには-M intelオプションを付与します。
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


*** Intermix source code with disassembl [#o69a48f4]
COLOR(red): Sオプションについての出力結果だが、dオプションと何が違うんだろう??
	 $ objdump -S hellopecl.so   | head -10
	 
	 hellopecl.so:     file format elf32-i386
	 
	 Disassembly of section .init:
	 
	 00000614 <_init>:
	  614:   55                      push   %ebp
	  615:   89 e5                   mov    %esp,%ebp
	  617:   83 ec 08                sub    $0x8,%esp
	  61a:   e8 d1 00 00 00          call   6f0 <call_gmon_start>


*** 全セクション部のフルコンテンツ情報を表示します。 [#ga97a23e]
	 $ objdump -s hellopecl.so   | head -10
	 
	 hellopecl.so:     file format elf32-i386
	 
	 Contents of section .gnu.hash:
	  00b4 03000000 0d000000 04000000 07000000  ................
	  00c4 00006000 80810809 18452061 81048412  ..`......E a....
	  00d4 0d000000 13000000 19000000 323407eb  ............24..
	  00e4 fc6b093d bae3927c 144b308d ea9c0b70  .k.=...|.K0....p
	  00f4 4345d5ec 44a4f89d b287edc2 d871581c  CE..D........qX.
	  0104 5e24cfde 54e5a235 b98df10e cebe947f  ^$..T..5........

*** ファイル中のDWARFを表示する [#q9c3c878]
[[DWARF>http://ja.wikipedia.org/wiki/DWARF]]を表示します。
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

*** シンボルテーブルを表示します。 [#j1be41f2]
	 $ objdump -t hellopecl.so   | head -10
	 
	 hellopecl.so:     file format elf32-i386
	 
	 SYMBOL TABLE:
	 000000b4 l    d  .gnu.hash      00000000              .gnu.hash
	 0000011c l    d  .dynsym        00000000              .dynsym
	 000002dc l    d  .dynstr        00000000              .dynstr
	 000004c4 l    d  .gnu.version   00000000              .gnu.version
	 000004fc l    d  .gnu.version_r 00000000              .gnu.version_r
	 0000052c l    d  .rel.dyn       00000000              .rel.dyn

*** ダイナミックシンボルテーブルを表示します。 [#zb6441fd]
	 $ objdump -T hellopecl.so   | head -10
	 
	 hellopecl.so:     file format elf32-i386
	 
	 DYNAMIC SYMBOL TABLE:
	 00000000  w   D  *UND*  00000000              __gmon_start__
	 00000000  w   D  *UND*  00000000              _Jv_RegisterClasses
	 00000000      D  *UND*  00000000              zend_wrong_param_count
	 00000000      DF *UND*  000002fd  GLIBC_2.0   calloc
	 00000000      D  *UND*  00000000              php_info_print_table_row
	 00000000      D  *UND*  00000000              php_printf

*** ダイナミックリロケーションレコード [#x537ba9f]
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

*** オブジェクトフォーマットやアーキテクチャに関するサポート情報を表示する [#n04da828]
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


* 参考URL
- readelf
-- http://sourceware.org/binutils/docs-2.16/binutils/readelf.html



##############################################################
readelfコマンド
##############################################################

* 概要
このページでは、readelfコマンドについてまとめます。
 ■ELFヘッダの読み出し
	 ELFファイルヘッダ              -h    
	 プログラムヘッダ               -l
	 セクションヘッダ               -S
	 以上3つのヘッダ                -e
 
 ■ELF情報の読み出し
	 シンボルテーブル               -s
	 リロケーション情報             -r
	 ダイナミックセグメント         -d
	 バージョンセクション           -V
	 アーキテクチャ依存             -A
	 パケットリスト長のヒストグラム	-I
	 ヘッダすべてと以上の全て       -a
	 コアノート                     -n
	 unwind情報                     -u

* 詳細 [#t941e799]
** ELFヘッダの読み出し [#f359973e]

*** ELF仕様書
- http://www.skyfree.org/linux/references/ELF_Format.pdf

*** readelfコマンドを利用する。 [#pfb358f7]
オプションは通常は-hを利用する。
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

*** -lオプションもよく利用される。 [#h993205a]
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


*** -Sオプションを以下に載せる [#fd9fea80]
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


*** h, l, Sオプション３つを一括で実行する [#x38b2727]
	 $ readelf -e a.out

** ELF情報の読み出し [#w301c8f3]

*** シンボルテーブルを表示する [#d405f53a]
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

*** リロケーション情報を表示する [#aca13d91]
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


*** 共有ライブラリの依存関係を調べる [#wa6a12ad]
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
上記によりlsの実行に際しても、librt.so.1, libacl.so.1, libc.so.6が必要となることがわかる。


*** バージョン情報を調べる [#ae2008de]
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

*** バケットリスト(?)を表示する(不明) [#m3d86524]
COLOR(red): 何を表しているのか不明(要確認)
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


*** 全情報を表示する [#v62b07c2]
迷ったらとりあえずこれを実行すればreadelfで得られるほぼ全ての情報を得られるものと思われます。
	 $ readelf -a hellopecl.so

* 参考URL [#qb8fce15]
- readelf
-- http://sourceware.org/binutils/docs-2.16/binutils/readelf.html


##############################################################
sizeコマンド
##############################################################

*** sizeコマンドを利用してみる。 [#ocee4f70]
	 $ size ./a.out   <=バイナリファイルを引数に与えます。
	 text    data     bss     dec     hex filename
	 2268     244       4    2516     9d4 ./a.out


##############################################################
stringsコマンド
##############################################################
*** バイナリファイル中の可読部分の文字列の取得を行う [#nf5cef27]
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

*** シンボルの削除を行う [#f99e2be8]
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


##############################################################
stripコマンド
##############################################################
*** 実行ファイルのサイズを減少させる [#j1dc51bb]
オブジェクトファイルからリロケート情報とシンボルテーブルのデバッグ用の情報を削除することで実行ファイルを減少させる事が出来る。
	 $ ls -l a.out
	 -rwxr-xr-x    1 tsuyoshi tsuyoshi      5671 Dec 24 14:32 a.out*
	 $ file a.out
	 a.out:          ELF 32-bit MSB executable SPARC Version 1, dynamically linked, not stripped
	 $ strip a.out
	 $ file a.out
	 a.out:          ELF 32-bit MSB executable SPARC Version 1, dynamically linked, stripped
	 $ ls -l a.out
	 -rwxr-xr-x    1 tsuyoshi tsuyoshi      3172 Dec 24 14:33 a.out*


##############################################################
odコマンド
##############################################################

*** メモリ内部を直接読む [#eb9d3f33]
	 # od -x /dev/mem

*** odでバイナリファイルのダンプを行う [#he2ffb33]
☆odはデフォルトで8進数の出力を行う。
	 $ od a.out  | head -3
	 0000000 042577 043114 000401 000001 000000 000000 000000 000000
	 0000020 000002 000003 000001 000000 101170 004004 000064 000000
	 0000040 016464 000000 000000 000000 000064 000040 000006 000050

☆-xオプションで16進数を表示することができる。
	 $ od -x a.out | head -3
	 0000000 457f 464c 0101 0001 0000 0000 0000 0000
	 0000020 0002 0003 0001 0000 8278 0804 0034 0000
	 0000040 1d34 0000 0000 0000 0034 0020 0006 0028

☆-dオプションで10進数表示をすることができる。
	 $ od -d a.out | head -3
	 0000000 17791 17996   257     1     0     0     0     0
	 0000020     2     3     1     0 33400  2052    52     0
	 0000040  7476     0     0     0    52    32     6    40

☆ASCII文字列表示も調べたい場合には -t x1zとzを付ける。
	 $ od -t x1z -A x a.out  | more
	 000000 7f 45 4c 46 01 01 01 00 00 00 00 00 00 00 00 00  >.ELF............<
	 000010 02 00 03 00 01 00 00 00 78 82 04 08 34 00 00 00  >........x...4...<
	 (中略)
	 0001a0 00 6c 69 62 63 2e 73 6f 2e 36 00 70 72 69 6e 74  >.libc.so.6.print<
	 0001b0 66 00 5f 49 4f 5f 73 74 64 69 6e 5f 75 73 65 64  >f._IO_stdin_used<
	 0001c0 00 5f 5f 6c 69 62 63 5f 73 74 61 72 74 5f 6d 61  >.__libc_start_ma<
	 (以下略)


##############################################################
xxdコマンド
##############################################################
2進数表示する
	$ echo hoge.txt > hoge
	$ xxd hoge 
	0000000: 686f 6765 2e74 7874 0a                   hoge.txt.

##############################################################
hexdumpコマンド
##############################################################
-Cオプションを付加すると16進数+文字列を表示して埋め込まれた文字などを探すことができる
	$ hexdump -C /usr/lib/libcurl.dylib  | head -4
	00000000  ca fe ba be 00 00 00 02  01 00 00 07 00 00 00 03  |................|
	00000010  00 00 10 00 00 05 d4 00  00 00 00 0c 00 00 00 07  |................|
	00000020  00 00 00 03 00 05 f0 00  00 05 b6 00 00 00 00 0c  |................|
	00000030  00 00 00 00 00 00 00 00  00 00 00 00 00 00 00 00  |................|
