# Makefileについて
Makefileの不明点などに関するリンクメモ

# 詳細

### makeコマンド
- どんなコマンドが実行されるのかしりたい場合には-nオプションを用いる
```
$ make -n
```

### 自動変数
記法
```
$@ : ターゲットファイル名
$% : ターゲットがアーカイブメンバだったときのターゲットメンバ名
$< : 最初の依存するファイルの名前
$? : ターゲットより新しいすべての依存するファイル名
$^ : すべての依存するファイルの名前
$+ : Makefileと同じ順番の依存するファイルの名前
$* : サフィックスを除いたターゲットの名前
```

- $@, $^は自動変数。ここでは$@はprog, $^は*.cを指している。
```
prog: *.c
	$(CC) -o $@ $^
```

- 参考
 -　http://minus9d.hatenablog.com/entry/20140203/1391436293

### 複数のターゲットを1つの箇所に記述する
次のように記述するとtargetA, targetBを一気に定義できます
```
targetA targetB: targetC
	[コマンド行]
```

### 複数行に分けてオブジェクトファイルを記述したい場合
バックスラッシュが必要です。
```
object_files = \
   foo.o \
   bar.o \
   baz.o
```

### ターゲットを複数の箇所で記述する
":"だとエラーがでるので、"::"を利用します。
```
targetA:: targetB
	[コマンド行1]

(他の処理)

targetA:: targetC
	[コマンド行2]
```

### 何もしないターゲットを作成する
これだけ
```
all: ;
```

### PHONY
Makefile中にcleanというターゲットが存在していてcleanファイルが存在していると以下のエラーになる。
```
$ touch clean
$ make clean
make: `clean' is up to date.
```

これを回避できるのが.PHONYである。
cleanファイルを作りたいのではなくてcleanというターゲットを実行したいということを明示する。
```
.PHONY: clean
clean:
	rm -f *.o lexer.c
```

### %のみのターゲットについて
例えば、以下のように記述されているとします。 
```
foo:
        frobnicate > foo

%: force
        @$(MAKE) -f Makefile $@
force: ;
```
この場合にはmake fooとfooターゲットを実行した場合には「frobnicate > foo」が実行されます。
make barとfoo以外のターゲットを実行した場合には「make -f Makefile bar」を実行します。

### %.oなどのターゲット
```
OFILES = main.o sub.o

all: a.out

a.out: $(OFILES)
        gcc $(OFILES) -o a.out

main.o: main.c		←生成に使用するファイルは指定するが、生成方法は書かない
sub.o: sub.c

%.o: %.c
        gcc -O -c $< -o $@
```


# FAQ

### Makefile: is it possible to have stem with slash? 
http://stackoverflow.com/questions/21182990/makefile-is-it-possible-to-have-stem-with-slash
以下のターゲットは「hoge-hoge/fuga」といったスラッシュがはいったのだと効かない。この場合には「hoge-%/%:」とする必要がある。
```
hoge-%:
	:
```

以下のドキュメントも合わせて参考のこと
- https://www.gnu.org/software/make/manual/html_node/Pattern-Match.html#Pattern-Match

# 参考
- 公式ドキュメント
 - 非常に豊富なドキュメント群
 - https://www.gnu.org/software/make/manual/html_node/index.html#Top
- もっとも豊富な日本語リファレンス
 - http://www.ecoop.net/coop/translated/GNUMake3.77/make_toc.jp.html
- MakeとMakefileの説明
 - http://www.unixuser.org/~euske/doc/makefile/


