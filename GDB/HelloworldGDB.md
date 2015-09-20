#  GDBとは
GDBはGNUソフトウェア・システムで動く標準のデバッガです。  
C言語、C++言語、Fortran等の各言語にて対応しています。

## 参考URL
* gdb を用いたデバッグ方法
	* http://uguisu.skr.jp/Windows/gdb.html
* Manpage of GDB
	* http://www.linux.or.jp/JM/html/GNU_gdb/man1/gdb.1.html
* ファイヤープロジェクト
	* http://www.fireproject.jp/feature/gdb/
* Debugging with GDB
	* http://www.asahi-net.or.jp/~wg5k-ickw/html/online/gdb-5.0/gdb-ja_toc.html

## はじめに

GDBは以下のように複数のデバッグ方法を提供してくれています。
* coreファイルからattach
* 起動プロセスに対してattach
* これから実行するプロセスに対してattach

バイナリがGDBに対応しているかどうかはfileコマンドでわかります。
* 「stripped」だとGDBできない、「not stripped」だとGDBできます。
* GDBができるためにコンパイルされるにはgオプションを付加してビルドされています。

RPM系パッケージなどの場合にはxxxx-debuginfoという名称のパッケージをダウンロードするとgdbにあてることができます

## サンプルプログラムで使ってみる

#####  使ってみよう
まず、GDB用にバイナリファイルを作成する必要があります。  
  
以下のサンプルプログラムを保存してください。
```
	 #include 
	 
	 int main()
	 {
	     int i=0, n=0, fact=1;
	     printf("1からnまでの積を求めます。nの値: ");
	     scanf("%d", &n);
	     for (i = 1; i<=n; i++) {
	         fact = fact * n;
	     }
	     printf("積は%dです。\n", fact);
	     return 0;
	 }
```

続いて、gccに-gオプションを付加してa.outを作成しましょう。  
このオプションを付加しないとgdbからブレークポイントを設定しても認識されません(デバッグ情報が不足しているため)

以下に上記に対してgdbを使用したときのログを示します。
```
	 [test@kaeru c]$ gdb a.out
	 GNU gdb Red Hat Linux (5.3post-0.20021129.18rh)
	 Copyright 2003 Free Software Foundation, Inc.
	 GDB is free software, covered by the GNU General Public License, and you are
	 welcome to change it and/or distribute copies of it under certain conditions.
	 Type "show copying" to see the conditions.
	 There is absolutely no warranty for GDB.  Type "show warranty" for details.
	 This GDB was configured as "i386-redhat-linux-gnu"...
	 (gdb) run
	 Starting program: /home/tsuyoshi/prog/c/a.out
	 1からnまでの積を求めます。nの値: 3
	 積は27です。
	 
	 Program exited normally.
	 (gdb) run
	 Starting program: /home/tsuyoshi/prog/c/a.out
	 1からnまでの積を求めます。nの値: 4
	 積は256です。
	 
	 Program exited normally.
	 (gdb) b main
	 Breakpoint 1 at 0x804836c: file third.c, line 5.
	 (gdb) run
	 Starting program: /home/tsuyoshi/prog/c/a.out  
	 
	 Breakpoint 1, main () at third.c:5
	 warning: Source file is more recent than executable. 
	 
	 5           int i=0, n=0, fact=1;
	 (gdb) p i
	 $1 = 1073827872
	 (gdb) p n
	 $2 = 1108551892
	 (gdb) p fact
	 $3 = 134513646
	 (gdb) n
	 7           scanf("%d", &n);
	 (gdb) p i
	 $4 = 0
	 (gdb) p n
	 $5 = 0
	 (gdb) p fact
	 $6 = 1
	 (gdb) n
	 8           for (i = 1; i<=n; i++) {
	 (gdb) n
	 1からnまでの積を求めます。nの値: 3
	 10          }
	 (gdb) n
	 11          printf("積は%dです。\n", fact);
	 (gdb) p fact
	 $7 = 1
	 (gdb) n
	 10          }
	 (gdb) n
	 11          printf("積は%dです。\n", fact);
	 (gdb) n
	 10          }
	 (gdb) n
	 11          printf("積は%dです。\n", fact);
	 (gdb) n
	 10          }
	 (gdb) n
	 14
	 (gdb) n
	 積は27です。
	 Line number 16 out of range; third.c has 14 lines.
	 (gdb) h
	 List of classes of commands:
	 
	 aliases -- Aliases of other commands
	 breakpoints -- Making program stop at certain points
	 data -- Examining data
	 files -- Specifying and examining files
	 internals -- Maintenance commands
	 obscure -- Obscure features
	 running -- Running the program
	 stack -- Examining the stack
	 status -- Status inquiries
	 support -- Support facilities
	 tracepoints -- Tracing of program execution without stopping the program
	 user-defined -- User-defined commands
	 
	 Type "help" followed by a class name for a list of commands in that class.
	 Type "help" followed by command name for full documentation.
	 Command name abbreviations are allowed if unambiguous.
```

