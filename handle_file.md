# 概要
ファイル操作を行う際のtipsなどについて

# 詳細
次のA.txt, B.txtの２つのファイルがあることを仮定する。
```
$ cat A.txt 
aA 1
aa 2
Aa 3
AA 4
```

```
$ cat B.txt 
BBB 5
bB 4
bb 3
Bb 2
BB 1
```

### ２つのファイルを行で結合する。
pasteコマンドは行で結合する。垂直に結合するcatとは逆の操作となる。
```
$ paste  A.txt B.txt 
aA 1	BBB 5
aa 2	bB 4
Aa 3	bb 3
AA 4	Bb 2
	BB 1
```

なお、デリミタを指定して結合することもできます。
```
$ paste -d ':' A.txt B.txt
aA 1:BBB 5
aa 2:bB 4
Aa 3:bb 3
AA 4:Bb 2
:BB 1
```

# 参考URL
- https://eng-entrance.com/linux-command-join
