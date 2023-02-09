# 概要
GDBに関するデバッグについて記載します。

なおgo言語の公式ドキュメント( https://go.dev/doc/gdb ) にはdelveが推奨となっています。
> Note that Delve is a better alternative to GDB when debugging Go programs built with the standard toolchain.

# デバッグしてみる
GO言語では基本的に最適化によるビルドが行われる。  
これによって実行された関数や変数などは適宜レジスタへ保存されるようになるため、最適化を無効化して値を得られるようにする必要がある。
```
$ cat hello.go 
package main

func main() {
    title := "Hello, World"
    println(title)
}
$ go build -gcflags '-N -l’ sample.go      // これで最適化を無効化して値を得られる
```

あとは通常通りgdbで実行する
```
$ gdb ./hoge.go 
GNU gdb (GDB) Fedora (7.4.50.20120120-54.fc17)
Copyright (C) 2012 Free Software Foundation, Inc.
License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>
This is free software: you are free to change and redistribute it.
There is NO WARRANTY, to the extent permitted by law.  Type "show copying"
and "show warranty" for details.
This GDB was configured as "x86_64-redhat-linux-gnu".
For bug reporting instructions, please see:
<http://www.gnu.org/software/gdb/bugs/>...
Reading symbols from /home/tsuyoshi/git/memo/GO/hoge.go...done.
warning: File "/usr/lib64/golang/src/pkg/runtime/runtime-gdb.py" auto-loading has been declined by your `auto-load safe-path' set to "$debugdir:$datadir/auto-load:/usr/bin/mono-gdb.py".
(gdb) b main.main
Breakpoint 1 at 0x400c00: file /home/tsuyoshi/git/memo/GO/hello.go, line 3.
(gdb) r
Starting program: /home/tsuyoshi/git/memo/GO/hoge.go 

Breakpoint 1, main.main () at /home/tsuyoshi/git/memo/GO/hello.go:3
3	func main() {
(gdb) n
4	    title := "Hello, World"
(gdb) list
1	package main
2	
3	func main() {
4	    title := "Hello, World"
5	    println(title)
6	}
(gdb) s
5	    println(title)
(gdb) s
runtime.printstring (v=void) at /usr/lib64/golang/src/pkg/runtime/print.c:351
351	runtime·printstring(String v)
(gdb) list
346	{
347		runtime·printhex((uint64)p);
348	}
349	
350	void
351	runtime·printstring(String v)
352	{
353		extern uint32 runtime·maxstring;
354	
355		if(v.len > runtime·maxstring) {
```

# TODO
- ブレークポイントに「info goroutines」という現在実行しているゴルーチンのリストを返すものがあります。

# 参考
- Debugging Go Code with GDB
 - https://golang.org/doc/gdb
- 11.2 GDBを使用してデバッグする
 - https://astaxie.gitbooks.io/build-web-application-with-golang/content/ja/11.2.html
