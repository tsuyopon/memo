# 概要
Makefileについての記述に関してのTIPSについて

# 詳細

### 以下の2つの違い
下記ファイルの違いにはまったのでメモ
- Makefile1: filterを使って、ifneqで判定する
- Makefile2: filterを使わずに、ifneqで判定する

Makefile1ではfilterを使って、ifneqで判定する
```
$ cat Makefile1
ifneq ($(filter debug,$(MAKECMDGOALS)),)
	HOGE="ifneq entered"
else
	HOGE="ifneq else entered"
endif

# 「make」で引数指定なしで解釈させるために「all」を、「make xxx」で解釈させるために「%」を指定しています。
all, %:
	echo ${HOGE}
```

では、ターゲットを変更して色々と実行してみます。
想像とは異なり、「debug」を指定するとifneqの中に入ってしまいました
```
$ make debug -f Makefile1
echo "ifneq entered"
ifneq entered
$ make debug2 -f Makefile1
echo "ifneq else entered"
ifneq else entered
$ make -f Makefile1
echo "ifneq else entered"
ifneq else entered
```

Makefile2ではfilterを使わずに、ifneqで判定します。
```
$ cat Makefile2
ifneq ($(MAKECMDGOALS),debug)
	HOGE="ifneq entered"
else
	HOGE="ifneq else entered"
endif

# 「make」で引数指定なしで解釈させるために「all」を、「make xxx」で解釈させるために「%」を指定しています。
all, %:
	echo ${HOGE}
```

では、ターゲットを変更して色々と実行してみます。
先ほどのMakefile1とは真逆の判定結果となっています。こちらは直感通りです。
```
$ make debug -f Makefile2
echo "no debug"
no debug
$ make debug2 -f Makefile2
echo "debug"
debug
$ make -f Makefile2
echo "debug"
debug
```

Makefile1とMakefile2で違いがありますが
filterを使った判定は直感で考えにくい部分があるので要注意です。
