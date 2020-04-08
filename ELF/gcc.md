# 概要
gcc周りについて

# 詳細

### 実行形式ファイルの生成にダイナミックリンクを使わない
```
$ gcc -static test.c
```

### sharedバイナリを作成する
```
$ gcc -shared -fPIC test.c
```

### rpathを埋め込む
以下はtest.cに/opt/と/tmp/をrpathとして埋め込む例です。
```
$ gcc -Wl,-rpath /opt/ -Wl,-rpath /tmp/ test.c 
$ objdump  -x a.out | grep -i rpath
  RPATH                /opt/:/tmp/
```

### デバッグオプションについて
デバッグはgオプションだけかと思っていたらg3というオプションがあることが判明
サイズやデバッグセクションなども変わってくるようだ。

- デバッグオプションを何も付与しない場合
```
$ gcc hello.c 
$ ls -alt a.out 
-rwxrwxr-x. 1 tsuyoshi tsuyoshi 8632 11月 23 12:25 a.out
$ nm --debug-syms a.out | grep " N "
$
```

- デバッグオプションgを付与する場合
```
$ gcc -g hello.c 
$ ls -alt a.out 
-rwxrwxr-x. 1 tsuyoshi tsuyoshi 9808 11月 23 12:21 a.out
$ nm --debug-syms a.out | grep " N "
0000000000000000 N .debug_abbrev
0000000000000000 N .debug_aranges
0000000000000000 N .debug_info
0000000000000000 N .debug_line
0000000000000000 N .debug_str
```

- デバッグオプションg3を付与する場合
```
$ gcc -g3 hello.c 
$ ls -alt a.out 
-rwxrwxr-x. 1 tsuyoshi tsuyoshi 29216 11月 23 12:21 a.out
$ nm --debug-syms a.out | grep " N "
0000000000000000 N .debug_abbrev
0000000000000000 N .debug_aranges
0000000000000000 N .debug_info
0000000000000000 N .debug_line
0000000000000000 N .debug_macro
0000000000000000 N .debug_str
```

g3を指定するとgdbを利用してマクロが認識されるようになるとのこと  
実は-g0, -g1, -g2, -g3などが存在しているようで-gだけだと-g2が指定されたのと同様の意味になるようだ。

### GDBデバッグ時について
次のようなオプションを付与しておくと良いでしょう。
```
-g3 -O0
```

他の資料なども参考にするとggdb, ggdb3といったオプションも付与するといいとのこと(自分は手元で付与してみたがサイズがg3と変わらなかった)
```
-g3 -ggdb -O0
or
-g3 -ggdb3 -O0
```

- 参考
  - https://stackoverflow.com/questions/10475040/gcc-g-vs-g3-gdb-flag-what-is-the-difference

### gccに関するパス情報を表示する
```
$ gcc -print-search-dirs
インストール: /usr/lib/gcc/x86_64-redhat-linux/4.8.5/
プログラム: =/usr/libexec/gcc/x86_64-redhat-linux/4.8.5/:/usr/libexec/gcc/x86_64-redhat-linux/4.8.5/:/usr/libexec/gcc/x86_64-redhat-linux/:/usr/lib/gcc/x86_64-redhat-linux/4.8.5/:/usr/lib/gcc/x86_64-redhat-linux/:/usr/lib/gcc/x86_64-redhat-linux/4.8.5/../../../../x86_64-redhat-linux/bin/x86_64-redhat-linux/4.8.5/:/usr/lib/gcc/x86_64-redhat-linux/4.8.5/../../../../x86_64-redhat-linux/bin/
ライブラリ: =/usr/lib/gcc/x86_64-redhat-linux/4.8.5/:/usr/lib/gcc/x86_64-redhat-linux/4.8.5/../../../../x86_64-redhat-linux/lib/x86_64-redhat-linux/4.8.5/:/usr/lib/gcc/x86_64-redhat-linux/4.8.5/../../../../x86_64-redhat-linux/lib/../lib64/:/usr/lib/gcc/x86_64-redhat-linux/4.8.5/../../../x86_64-redhat-linux/4.8.5/:/usr/lib/gcc/x86_64-redhat-linux/4.8.5/../../../../lib64/:/lib/x86_64-redhat-linux/4.8.5/:/lib/../lib64/:/usr/lib/x86_64-redhat-linux/4.8.5/:/usr/lib/../lib64/:/usr/lib/gcc/x86_64-redhat-linux/4.8.5/../../../../x86_64-redhat-linux/lib/:/usr/lib/gcc/x86_64-redhat-linux/4.8.5/../../../:/lib/:/usr/lib/
```

### 入力ファイルをldが処理するごとに、ファイル名を出力する
```
$ gcc -t test.c 
/usr/bin/ld: mode elf_x86_64
/usr/lib/gcc/x86_64-redhat-linux/4.8.5/../../../../lib64/crt1.o
/usr/lib/gcc/x86_64-redhat-linux/4.8.5/../../../../lib64/crti.o
/usr/lib/gcc/x86_64-redhat-linux/4.8.5/crtbegin.o
/tmp/cchsOWCp.o
-lgcc_s (/usr/lib/gcc/x86_64-redhat-linux/4.8.5/libgcc_s.so)
/lib64/libc.so.6
(/usr/lib64/libc_nonshared.a)elf-init.oS
/lib64/ld-linux-x86-64.so.2
/lib64/ld-linux-x86-64.so.2
-lgcc_s (/usr/lib/gcc/x86_64-redhat-linux/4.8.5/libgcc_s.so)
/usr/lib/gcc/x86_64-redhat-linux/4.8.5/crtend.o
/usr/lib/gcc/x86_64-redhat-linux/4.8.5/../../../../lib64/crtn.o
```

これは、ldコマンドのtオプションの機能だと思われる
- https://linuxjm.osdn.jp/html/GNU_binutils/man1/ld.1.html

