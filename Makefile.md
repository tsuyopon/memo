# Makefileについて
Makefileの不明点などに関するリンクメモ

# 詳細

<!-- *****デバッグ方法***** -->
## デバッグ方法
- 1.どんなコマンドが実行されるのかしりたい場合には-nオプションを用いる
```
$ make -n
```

- 2. ログレベルで分ける方法
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

参考: http://quruli.ivory.ne.jp/document/make_3.79.1/make-jp_7.html#Make-Control-Functions

- 3.デバッグ情報を出力したい
--debugオプションを付加すればよい。
```
   $ make --debug 
```

<!-- *****make実行時***** -->
## makeコマンド実行時に関して
### Makefile内で-(ハイフン)を付加していなくても、コマンドがエラー時は継続させたい
-iオプションで全てのMakefile内のコマンドに-(ハイフン)が付与されているようにみせかけることができます。   
処理がエラーとなっても継続したい場合に便利です。   
```
   $ make -i 
```

### Makefile内で@を付加していなくても、コマンド出力をしないようにしたい。
-sオプションで全てのMakefile内のコマンドに@が付与されているようにみせかけることができます。   
```
   $ make -s 
```

### makeの一般的なオプションについて
```
	-p 
	   make であらかじめ定義されている規則・マクロをすべて展開し表示する。 
	-t 
	   生成コマンドを何も実行せず、指定されたターゲットを touch する。 
	-e 
	   make 内で定義されたマクロよりも環境変数の値を優先する。
	-n 
	   実行すべき生成コマンド列の表示のみを行い、実際には実行しない。 
	   これは、Makefile が何をするのか、前もって予想したいときに有効である。 
```

### 一時的に変数を変更したい
以下の様にして、引数に変数を指定することもできる。   
たとえば、ccからgccにコンパイラを変更したい場合は以下の様にする。   
```
	   $ make CC=gcc
```

### 参考URL
- makeのオプションについて
-- http://www.ecoop.net/coop/translated/GNUMake3.77/make_9.jp.html#SEC88


<!-- *****自動変数・マクロ変数***** -->
## 自動変数・マクロ環境変数など

### 自動変数
記法
```
$@ : ターゲットファイル名
$% : ターゲットがアーカイブメンバだったときのターゲットメンバ名(ターゲット名が“edajima.a(momo.o)”の場合、$@は“edajima.a”で、$%は“momo.o”)
$< : 最初の依存するファイルの名前
$? : ターゲットより新しいすべての依存するファイル名
$^ : すべての依存するファイルの名前
$+ : Makefileと同じ順番の依存するファイルの名前
$* : suffixを除いたターゲットの名前
```

- $@, $^は自動変数。ここでは$@はprog, $^は*.cを指している。
```
prog: *.c
	$(CC) -o $@ $^
```

- $<
 - 今、実行しようとしている生成コマンドの中で、そのターゲットが依存しているファイルのひとつに展開される。
 - ここでmakeがsub1.cからsub1.oを生成するためにこのコマンドを実行するならば、「$<」は「sub1.c」へと展開される。
```
	 例: .c.o:
	         cc -c $<
```

- $?
 - 依存ファイルで更新されたもののリストに展開される。
 - 下記でもしも、sub1.cだけがa.outよりも新しければ「$?」→「sub1.c」に展開される。
```
	 例: a.out: sub1.c sub2.c
	             echo "$? are modified."
```

- $^
 - 「$^」により依存関係のリストを表示させることができます。
```
 all: testfile testfil2
 	@echo $^
```
 - 上記に対する出力例を以下に示します。
```
 $ make
 testfile testfile2
```

- $*
 - ターゲット名からサフィックスを除いたものに展開される。
 - 下記の例では「$*」は「paper」に展開される。
```
	 例: paper.ps: paper.dvi
	             dvips $*
```

- 参考
 -　http://minus9d.hatenablog.com/entry/20140203/1391436293

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
先頭の@       画面上に実行するコマンドを表示したくない場合
先頭の-       実行エラーとなっても処理を行わせたいコマンドの先頭に付与する
@D
@F
@f
```

### GNU MAKEの定義済みマクロ変数
```
マクロ名 	文字列 	   説明
AR          ar         アーカイブユーティリティ
AS          as         アセンブラ
CC          cc         Cコンパイラ
CXX         g++        C++コンパイラ
CO          co         RCS ファイルからリビジョンをチェックアウトする
CPP         $(CC) -E   Cプリプロセッサ
FC          f77        Fortranコンパイラ
GET         get        知らね
LEX         lex        lex
PC          pc         Pascalコンパイラ
YACC        yacc       yacc
YACCR       yacc -r    知らね
MAKEINFO    makeinfo   Texinfo -> Info
TEX         tex        TeX
TEXI2DVI    texi2dvi   Texinfo -> DVI
WEAVE       weave      知らね
CWEAVE      cweave     知らね
TANGLE      tangle     知らね
CTANGLE 	ctangle    知らね
RM          rm -f      ファイルの削除
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

<!-- *****make記述***** -->
## make記述
### マクロ変数の利用
```
MYVAR = mogemoge
	hello: $(MYVAR) 
	または
	hello: ${MYVAR}
```

### 多段マクロ変数の展開
```
$($(マクロ名)) 
マクロを2段階に展開する。
	 例: VAR = CC
	     CC = gcc
```
ここで$($(VAR)) → $(CC) → gcc に展開されることになる。

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

### ファイルが無いと実行させないようにするには
例えば、test.txtというファイルが存在しなければエラーにするにはMakefileがコマンド実行してエラーになる性質を利用します。
```
depfile: test.txt
    @cat test.txt
```

### シェルを実行した結果を変数に格納したい
以下の様にしてshellストリングを利用すれば、whoamiの結果がUNAMEに格納されることになる。
```
   UNAME = $(shell whoami)
```


### シェルスクリプトのforの中の変数「$i」を解釈させたい
for文を利用する際には変数を「$i」等と記述しても動作しません。   
このような場合には「$$i」と記述します。
```
 for i in *.sh; do echo $$i;done
```

### 各種マクロについて(応用編)

```
- $(マクロ名:文字列1=文字列2) 
文字列置換つきマクロ。 マクロを展開するとき、文字列1 を 文字列2 に置換する。 これはよく以下のように用いられる : 
   例: OBJS = sub1.o sub2.o sub3.o
ここで $(OBJS:.o=.c) → sub1.c sub2.c sub3.c 
```

```
- $(マクロ名/*/文字列1&文字列2) 
文字列追加つきマクロ。 マクロを展開するとき、その展開結果に文字列1と 文字列2を追加する。 
   例: NAMES  = aaa bbb ccc

ここで、 $(NAMES/*/sub_&.c) → sub_aaa.c sub_bbb.c sub_ccc.c 
```

```
- $(マクロ名/^/文字列) 
文字列追加つきマクロ。 マクロを展開するとき、その先頭に文字列を追加する。
   例: NAMES  = aaa.c bbb.c ccc.c

ここで、 $(NAMES/^/sub_) → sub_aaa.c sub_bbb.c sub_ccc.c 
```

```
- $(マクロ名/$/文字列) 
文字列追加つきマクロ。 マクロを展開するとき、その末尾に文字列を追加する。
   例: NAMES  = sub_aaa sub_bbb sub_ccc

ここで、 $(NAMES/$/.c) → sub_aaa.c sub_bbb.c sub_ccc.c 
```

```
- $(マクロ名?文字列1:文字列2) 
条件分岐マクロ。 指定したマクロがすでに定義されていれば文字列1を、未定義ならば文字列 2 を展開する。 
```

- 参考資料
 - http://www.unixuser.org/~euske/doc/makefile/#cascade


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

### hoge-%などのターゲットで%を取得したい
```
 test-%:
    echo $*                         <=   $*により「test-%」の%部分を表示する。
    echo $@                         <=   $@によりターゲット名全てを表示する。
```

上記の様なMakefileで「make test-tsuyoshi」と実行すると
```
 $ make test-tsuyoshi
 tsuyoshi
 test-tsuyoshi
```
上記の様にtsuyoshiとして、ターゲット名の一部を利用することができます。

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

### 条件分岐したい
ifdefやifeqがあります。逆のifndef, ifneqなどもあります。

```
ifdef debug
 DEBUG_FLAG = -DDEBUG
else
 DEBUG_FLAG =
endif
```

ifeqの場合で変数と比較する場合は次のような例になる
```
ifeq "$(use_a)" "yes"
 a1 := a
else
 a1 := 1
endif
```

### includeの前のハイフンについて
例えば、次のようにincludeの前にハイフン(-)が付与されている場合には、そのファイルが存在しなくてもエラーになりません。
```
-include optional.mk
```

### 関数について
深くは触れません。概要だけ記しておきます。
- subst : 置換動作
- patsubst : 置換動作，ワイルドカードあり
- strip : 空白文字の削除
- findstring : 文字列を探す
- filter : 一致する単語の削除
- filter-out : 一致しない単語の削除
- sort : ソートする
- dir : ディレクトリ部分の抽出
- nodir : ファイル部分の抽出
- suffix : サフィックス（拡張子）部分
- basename : サフィックス以外
- addsuffix : サフィックスを加える
- addprefix : プレフィックスを加える
- join : 単語の連結
- word : n番目の単語を返す
- worldlist : 単語のリストを返す
- words : 単語数を返す
- firstword : 最初の名前を返す
- wildcard : ワイルドカードによりファイル名リストを返す
- foreach : 引数を複数回展開する

- 上記関数については以下のサイトに説明がありますので参考になります。
 - http://www.ecoop.net/coop/translated/GNUMake3.77/make_8.jp.html


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

# TODO
いかについてメモ
```
OBJS    = $(SRCS:.cpp=.o)
		rm -f hello hello.o edajima.o raiden raiden.o
```

# 参考
- 公式ドキュメント
 - 非常に豊富なドキュメント群
 - https://www.gnu.org/software/make/manual/html_node/index.html#Top
- 公式マニュアル
 - http://www.gnu.org/software/make/manual/make.html
- もっとも豊富な日本語リファレンス
 - http://www.ecoop.net/coop/translated/GNUMake3.77/make_toc.jp.html
- MakeとMakefileの説明
 - http://www.unixuser.org/~euske/doc/makefile/

