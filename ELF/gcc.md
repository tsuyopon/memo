# 概要
gcc周りについて

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
[tsuyoshi@localhost ~]$ nm --debug-syms a.out | grep " N "
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


