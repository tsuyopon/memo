# Makefileについて
Makefileはtarget, prerequisites, commandの３つで構成されます。commandはタブの後に記載します。
これはMakefile関連で検索したい時に覚えておくと便利です。
```
target: prerequisites
	command
```

# Makefile記法

## @と-の意味について
- "@"は実行するコマンドの出力を抑制します。
- "-"はエラーがあってもそのまま処理を続行します。

同時に指定することも可能です。
```
clean:
	-@rm *.o
```

## 自動変数(Automatic Variables)

自動変数については公式ドキュメントも参考のこと
- https://www.gnu.org/software/make/manual/html_node/Automatic-Variables.html

変数は次の意味を表します。少しわかりにくいので例を載せています。
```
$@ : target
$^ : prerequisites、ただし重複分は除く
$? : prerequisitesのうちターゲットより新しい全ての依存するファイル名
$< : prerequisitesのうち最初に書かれたもの1つのみ
$+ : prerequisites、重複分もそのまま表示する
$% : ターゲットがアーカイブメンバだったときのターゲットメンバ名(ターゲット名が"edajima.a(momo.o)"の場合、$@は"edajima.a"で、$%は"momo.o")
$* : suffixを除いたターゲットの名前
```

### 単純なサンプル
- サンプル1
```
mytarget.o: hello.c sub.c sub.c sub.c
	@printf "$$ @ = $@ \n"
	@printf "$$ ^ = $^ \n"
	@printf "$$ ? = $? \n"
	@printf "$$ < = $< \n"
	@printf "$$ + = $+ \n"
	@printf "$$ %% = $% \n"
	@printf "$$ * = $* \n"
```

上記を実行すると、次の結果となります。$%は出力されません。
```
$ touch hello.c sub.c sub.c sub.c
$ make
$ @ = mytarget.o 
$ ^ = hello.c sub.c 
$ ? = hello.c sub.c 
$ < = hello.c 
$ + = hello.c sub.c sub.c sub.c 
$ % =  
$ * = mytarget 
```


$%の例が上記では確認できなかったので、次にターゲットに()が含まれるパターンを見てみましょう。
- サンプル2
```
$ cat Makefile
mytarget(hack.o) : hello.c sub.c sub.c sub.c
	@printf "$$ @ = $@ \n"
	@printf "$$ ^ = $^ \n"
	@printf "$$ ? = $? \n"
	@printf "$$ < = $< \n"
	@printf "$$ + = $+ \n"
	@printf "$$ %% = $% \n"
	@printf "$$ * = $* \n"
```

makeでhelloターゲットを実行してみると$%には()内の値が出力されていることがわかります。
```
$ touch hello.c sub.c sub.c sub.c
$ make
$ @ = mytarget 
$ ^ = hello.c sub.c 
$ ? = hello.c sub.c 
$ < = hello.c 
$ + = hello.c sub.c sub.c sub.c 
$ % = hack.o 
$ * = hack 
```

### 自動変数詳細

- $@, $^は自動変数。ここでは$@はターゲット名なのでprogを, $^は全ての依存するファイルの名前なのでここでは*.cを指している。
```
prog: *.c
	$(CC) -o $@ $^
```

- $<
  - 今、実行しようとしている生成コマンドの中で、そのターゲットが依存しているファイルのひとつに展開される。
  - ここでmakeがsub1.cからsub1.oを生成するためにこのコマンドを実行するならば、「$<」は「sub1.c」へと展開される。
```
# 例
.c.o:
	cc -c $<
```

- $?
  - 依存ファイルで更新されたもののリストに展開される。
  - 下記でもしも、sub1.cだけがa.outよりも新しければ「$?」→「sub1.c」に展開される。
```
a.out: sub1.c sub2.c
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
paper.ps: paper.dvi
        dvips $*
```

- 参考
 -　http://minus9d.hatenablog.com/entry/20140203/1391436293


### 現在のディレクトリ直下のディレクトリのMakefileも実行したい
Cオプションを指定してその後にディレクトリが指定されるようにしておくのが一般的である。
```
SUBDIRS = foo bar baz

.PHONY: subdirs $(SUBDIRS)

subdirs: $(SUBDIRS)

$(SUBDIRS):
        $(MAKE) -C $@

foo: baz
```

### 要確認
```
::
:= または ::=
	2つは基本的には同じ意味です。このような代入は、変数値を一度だけ処理し、記憶します。簡潔かつ強力であるこのようなタイプの代入は、デフォルトとして選びましょう。
?=
	?=は、変数が定義されていないときのみ:=として機能します。定義されていたら何も起きません。
+=
	加算代入演算子です。変数があらかじめ:=もしくは::=に設定されている場合、右辺は即値とみなされます。そうでない場合は、遅延された値とみなされます。
!=
	シェルの代入演算子です。右辺は即座に評価されシェルに渡されます。結果は、左辺にある変数に記憶されます。
$$?
$$*
$$^
$$+
$(objects): %.o: %.c
vpath
```


### マクロの参照方法
次のいずれかの方法で参照することができます。
```
$(マクロ名)
```
または
```
${マクロ名}
```

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

### シェルスクリプトのforの中の変数「$i」を解釈させたい
for文を利用する際には変数を「$i」等と記述しても動作しません。   
このような場合には「$$i」と記述します。
```
 for i in *.sh; do echo $$i;done
```

サンプルMakefile
```
LENGTH := 3

all:
	@for i in {1..$(LENGTH)}; do \
		echo $$i; \
	done
```

実行結果
```
$ make
1
2
3
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
ifdefやifeqがあります。逆のifndef, ifneqなどもあります。ただし、elseはありませんので場合によってはifdefなどのネスト構造となります。

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

### コマンド実行結果を変数に格納する
```
MYPWD = $(shell pwd)

all:
	echo ${MYPWD}
```

### 関数について
深くは触れません。概要だけ記し、詳細はMakefile_function.mdに譲ります。
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


### Cコンパイルの暗黙的ルール
Makefileを次のように用意する。
```
$ cat Makefile
CFLAGS = -Wall
CPPFLAGS = -I/usr/local/include
TARGET_ARCH = -march=native

hello: hello.c
```

.cからのターゲット生成は次の暗黙的ルールに従う
```
$(CC) $(CFLAGS) $(CPPFLAGS) $(TARGET_ARCH) -c -o $@
```

helloターゲットを実行すると次のようになる。
```
$ make hello
cc -Wall -I/usr/local/include  -march=native hello.c   -o hello
```

- 参考
  - C++の場合なども載っています。
  - https://minus9d.hatenablog.com/entry/20140205/1391608946


### 暗黙でターゲットが生成されるルールが知りたい
makeのpオプションでLINKでgrepすれば暗黙ルールが確認できます。
```
$ make -p  | grep LINK
LINK.m = $(LINK.c)
LINK.o = $(CC) $(LDFLAGS) $(TARGET_ARCH)
LINK.p = $(PC) $(PFLAGS) $(CPPFLAGS) $(LDFLAGS) $(TARGET_ARCH)
LINK.cc = $(CXX) $(CXXFLAGS) $(CPPFLAGS) $(LDFLAGS) $(TARGET_ARCH)
LINK.r = $(FC) $(FFLAGS) $(RFLAGS) $(LDFLAGS) $(TARGET_ARCH)
LINK.C = $(LINK.cc)
LINK.S = $(CC) $(ASFLAGS) $(CPPFLAGS) $(LDFLAGS) $(TARGET_MACH)
LINK.c = $(CC) $(CFLAGS) $(CPPFLAGS) $(LDFLAGS) $(TARGET_ARCH)
LINK.s = $(CC) $(ASFLAGS) $(LDFLAGS) $(TARGET_MACH)
LINK.cpp = $(LINK.cc)
```


### デバッグ方法

- 1.どんなコマンドが実行されるか知りたい場合には-nオプションを用いる
```
$ make -n
```

- 2.ログレベルで分ける方法
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


### 依存ファイル(拡張子: .d)とその読み込み

-MMD -MPオプションで生成した.dファイルは、


ファイルの依存関係は、gccの -MMD -MPオプションで生成します。
```
CFLAGS = -g -MMD -MP
```

以下で読み込みます。
```
ifneq ($(MAKECMDGOALS),clean) 
	-include $(DEPENDS)
endif
```

MAKECMDGOALSにはコマンドラインで指定されたターゲットが入ります。
たとえば、make cleanとすると$(MAKECMDGOALS)にはcleanが入ることになります。
上記の例ではcleanでなかったら$(DEPENDS)を読み込みます。このifneqが存在しないとcleanを実行する前に.dファイルを作ってしまい無駄が生じます。


.dファイルには例えば次のような依存が記述されています。
```
$ cat hello.d 
hello.o: hello.c
```

- 参考
　　https://eng-notebook.com/post-2302



### TIPS
- カレントディレクトリ以下のcppファイルを全て変数に納める
```
SOURCES = $(notdir $(shell find . -name '*.cpp'))
```

- ソースファイル一覧をオブジェクトファイル一覧に変換する
```
OBJECTS = $(SOURCES:.cpp=.o)
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


