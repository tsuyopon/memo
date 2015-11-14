

### デバッグ方法
1. 実行コマンドを確認する方法
```
	make -n
```

2. ログレベルで分ける方法

例えば、以下のようなMakefileを実行すると
```
all:
	$(info aaaaa)
	$(warning bbbbb)
	$(error ccccc)
```

下記の出力となります。
```
aaaaa
Makefile2:2: bbbbb
Makefile2:2: *** ccccc.  Stop.
```

errorの場合には必ずその行で停止します。

### 要確認
```
::
:= または ::=
	2つは基本的には同じ意味です。このような代入は、変数値を一度だけ処理し、記憶します。簡潔かつ強力であるこのようなタイプの代入は、デフォルトとして選びましょう。
?=
	?=は、変数が定義されていないときのみ:=として機能します。そうでない場合は、何も起きません。
+=
	加算代入演算子です。変数があらかじめ:=もしくは::=に設定されている場合、右辺は即値とみなされます。そうでない場合は、遅延された値とみなされます。
!=
	シェルの代入演算子です。右辺は即座に評価されシェルに渡されます。結果は、左辺にある変数に記憶されます。
$$?
$$*
$$^
$$+
objects := $(wildcard *.o)
$(objects): %.o: %.c
vpath
SUBDIRS
先頭の@
先頭の-
@D
@F
@f
```

### マクロ変数
```
MYVAR = mogemoge
	hello: $(MYVAR) 
	または
	hello: ${MYVAR}
```

### GNU MAKEの定義済みマクロ変数
```
マクロ名 	文字列 	説明
AR 	ar 	アーカイブユーティリティ
AS 	as 	アセンブラ
CC 	cc 	Cコンパイラ
CXX 	g++ 	C++コンパイラ
CO 	co 	RCS ファイルからリビジョンをチェックアウトする
CPP 	$(CC) -E 	Cプリプロセッサ
FC 	f77 	Fortranコンパイラ
GET 	get 	知らね
LEX 	lex 	lex
PC 	pc 	Pascalコンパイラ
YACC 	yacc 	yacc
YACCR 	yacc -r 	知らね
MAKEINFO 	makeinfo 	Texinfo -> Info
TEX 	tex 	TeX
TEXI2DVI 	texi2dvi 	Texinfo -> DVI
WEAVE 	weave 	知らね
CWEAVE 	cweave 	知らね
TANGLE 	tangle 	知らね
CTANGLE 	ctangle 	知らね
RM 	rm -f 	ファイルの削除
```


引数用マクロ変数
```
マクロ名 	文字列 	説明
ARFLAGS 	rv 	ARの引数
ASFLAGS 		ASの引数
CFLAGS 		CCの引数
CXXFLAGS 		CXXの引数
COFLAGS 		COの引数
CPPFLAGS 		CPPの引数
FFLAGS 		FCの引数
GFLAGS 		GETの引数
LDFLAGS 		リンカldの引数
LFLAGS 		LEXの引数
PFLAGS 		PCの引数
RFLAGS 		知らね
YFLAGS 		YACCの引数
```

### 内部マクロ
```
$@ 	ターゲット名
$% 	ターゲットメンバ名(ターゲット名が“edajima.a(momo.o)”の場合、$@は“edajima.a”で、$%は“momo.o”
$< 	依存ファイルの先頭のファイル名
$? 	依存ファイルの内、ターゲットより新しいファイルのリスト
$^ 	すべての依存ファイルのリスト
$+ 	Makefileと同じ順番の依存するファイルの名前
$* 	suffixを除いたターゲットの名前
```

### 特別なビルドインターゲット名


- 参考
 - http://www.ecoop.net/coop/translated/GNUMake3.77/make_4.jp.html

### .SUFFIXES
サフィックスルール適用対象の拡張子の定義
```
.SUFFIXES: .c .o
```

拡張子が.oのファイルは拡張子を.cに変えたファイルに依存していることがわかっています
```
.c.o:
	$(CC) $(CFLAGS) -c $<
```


### cleanというファイルがローカルにあっても無視させる。
```
.PHONYに指定すればOK
	.PHONY: clean
	clean:
```

### 
```
OBJS    = $(SRCS:.cpp=.o)
		rm -f hello hello.o edajima.o raiden raiden.o
```

# 参考URL
- 公式マニュアル
 - http://www.gnu.org/software/make/manual/make.html
