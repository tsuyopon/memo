# Makefile
Makefileはtarget, prerequisites, commandの３つで構成されます。commandはタブの後に記載します。
これらの用語についてMakefile関連で検索したい時に覚えておくと便利です。
```
target: prerequisites
	command
```

Makefileを検索する際には次の公式マニュアルがおすすめです。
1ページ内に全てを表示してくれるので検索する際にも非常に便利です。
- Makefile公式マニュアル
  - http://www.gnu.org/software/make/manual/make.html


# 終了ステータス
makeの終了ステータスが決まっています。
```
0: makeが成功した場合
1: "-q"フラグを使ってファイルが最新でないと判断された場合
2: makeが実行中にいくつかのエラーに遭遇した場合
```

# 変数

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


## 変数への代入

#### "="(遅延評価)と":="(即時評価)の違いについて
次のことを覚えておきましょう。
- "="の場合には、遅延評価
- ":"の場合には、即時評価

この２つは以下の違いですぐにわかります。２つの違いはMakefileのCMDLINE変数の代入演算子が":"か":="かの違いだけです。

- "="による遅延評価
  - CMDLINEが定義ではなく実行された時点で評価されるのでLSOPT変数の内容が反映されます。
```
$ cat Makefile 
CMDLINE = ls $(LSOPT)
LSOPT = -al

all:
	$(CMDLINE)
$ gmake
ls -al
合計 12
drwxrwxr-x   2 tsuyoshi tsuyoshi   34  2月 28 07:09 .
drwx------. 36 tsuyoshi tsuyoshi 4096  2月 28 07:09 ..
-rw-rw-r--   1 tsuyoshi tsuyoshi   52  2月 28 07:09 Makefile
-rw-rw-r--   1 tsuyoshi tsuyoshi    0  2月 28 07:08 hoge
```

- ":="による即時評価
  - CMDLINEの定義された時点で評価されるのでLSOPT変数の内容が反映されていません。
```
$ cat Makefile 
CMDLINE := ls $(LSOPT)
LSOPT = -al

all:
	$(CMDLINE)
$ gmake
ls 
Makefile  hoge
```

### 代入演算子の意味
```
=
	遅延評価

:= または ::=
	2つは基本的には同じ意味です。このような代入は、変数値を一度だけ処理し、記憶します。簡潔かつ強力であるこのようなタイプの代入は、デフォルトとして選びましょう。

?=
	遅延評価
	?=は変数が定義されていないときのみ:=として機能します。定義されていたら何も起きません。

+=
	遅延評価か即時評価は元の定義に準ずる
	加算代入演算子です。変数があらかじめ:=もしくは::=に設定されている場合、右辺は即値とみなされます。そうでない場合は、遅延された値とみなされます。

!=
	即時評価
	シェルの代入演算子です。右辺は即座に評価されシェルに渡されます。結果は、左辺にある変数に記憶されます。
	(TODO): 試してみたがうまく動かなかったので再調査が必要
```

- 参考
  - https://www.gnu.org/software/make/manual/make.html#Reading-Makefiles

### マクロの参照方法
次のいずれかの方法で参照することができます。
```
$(マクロ名)
```
または
```
${マクロ名}
```

### ターゲット中で変数を定義したい
evalを使う必要があります。Makefile_function.mdに記載されています。

### VPATH変数、vpathディレクティブ

target や prerequisites の検索パスを追加したい時は、VPATH 変数にディレクトリのパスを設定します。 複数のパスを指定したい場合は、コロン (:) かスペースで区切って指定します
なお、カレントディレクトリはデフォルトで探索するので指定する必要はありません。
```
VPATH = src:../headers
```

また、vpathディレクティブを指定すると、ファイル名に応じて別々の検索パスを設定することができます。
```
vpath %.h   ../headers
vpath %.cpp src
vpath %     hoge
```

### .LIBPATTERNS変数について
prerequisites に -l<name> と指定した場合に、どんな名前のファイルを検索するかは、.LIBPATTERNS 変数に設定されたパターンによって決められます。 デフォルトでは次のような値に設定されています。
```
.LIBPATTERNS = lib%.so lib%.a
```

上記の変数への指定によって、-lcurses と指定したときにはlibcurses.so と libcurses.a ファイルが検索されることになります。

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

### ターゲットと同一のファイル名(ディレクトリ)が存在しない場合にのみターゲットに定義された内容を実行させる
次のようにMakefileに定義されたターゲット名前と同一のファイルやディレクトリが存在しない場合にのみ実行させる。
注意点としては、以下の場合にはそのターゲットの.PHONYは定義してはならない。
```
$ cat Makefile 
testfile:
	-echo "testfile does not exists"
$ make
echo "testfile does not exists"
testfile does not exists
$ touch testfile
$ make
make: `testfile' is up to date.
```

### ファイルが無いと実行させないようにするには
例えば、test.txtというファイルが存在しなければエラーにするにはMakefileがコマンド実行してエラーになる性質を利用します。
```
depfile: test.txt
    @cat test.txt
```

### 依存ファイルへの更新がない場合にはターゲットを実行しない
```
test: test.cc 
	gcc -o test test.cc
```
「ターゲット」(上記ではtest)が「依存するファイル」(test.cc)よりも新しいか新しくないかでターゲットを実行するかどうか判断する。
ターゲットが存在していて依存するファイルよりも更新時刻が新しい場合には次のように表示されます。
```
$ make test
make: `test' is up to date.
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

変数に登録された値を出力する例も記載しておきます。
```
LIST = one two three
all:
	for i in $(LIST); do \
         echo $$i; \
	done
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


### どんなターゲットにも一致する%について
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

実は「hoge-hoge/fuga」といったスラッシュがはいったターゲットだと%だけでは効かないことがある。この場合には「hoge-%/%:」と%を2度記述する必要がある。
- http://stackoverflow.com/questions/21182990/makefile-is-it-possible-to-have-stem-with-slash

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

実用的な例も記載しておく。
```
ifeq ($(CC),gcc)
        $(CC) -o foo $(objects) $(libs_for_gcc)
else
        $(CC) -o foo $(objects) $(normal_libs)
endif
```

```
ifeq ($(DEBUG), 1)
  LIBS = $(LIBS_FOR_DEBUG)
else
  LIBS = $(LIBS_FOR_RELEASE)
endif
```

### defineによって複数のコマンドを一括で定義する(Canned Command Sequences)
defineによって複数のコマンドを一括で定義できます。
```
define greet-and-print-target
	echo Hello.
	@echo Target is $@.
endef

all:
	$(greet-and-print-target)
```

Canned Command Sequencesの呼び出し時に@などのプレフィックスを付与すると全てのコマンド行にそれを付与した場合と同様の効果があります。
```
all:
	@($greet-and-print-target)

$ make
Hello.
Target is all.
```

### includeの前のハイフンについて
例えば、次のようにincludeの前にハイフン(-)が付与されている場合には、そのファイルが存在しなくてもエラーになりません。
```
-include optional.mk
```

### includeで別ファイルとして読み込むMakefileを指定する
ファイル名の中で変数 (variable) や関数 (function) を参照すると、展開されてからファイルを検索します。
```
HOGE = foo.mk bar.mk
include $(HOGE)
```

includeされるMakefileを相対パスで指定すると次の探索順となります。
- 1. カレントディレクトリ
- 2. -I または --include-dir オプションで指定したディレクトリ
- 3. <prefix>/include（通常は /usr/local/include）
- 4. /usr/gnu/include
- 5. /usr/local/include
- 6. /usr/include

### コマンド実行結果を変数に格納する
以下のバッククォートによるコマンド実行の場合だとその変数が実行されるまで、pwdの実行結果が処理されません。
```
MYPWD = `shell pwd`
```

Makefile中でコマンド展開してほしい場合にはshellを使うのが正しい記法であると思われます。
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

### 何階層目のMakefileかを調べる
次のように３つのファイルを用意します。 MAKELEVELによって何階層かわかります。
```
$ cat Makefile 
all:
	echo $(MAKELEVEL)
	$(MAKE) -f sub.mk
$ cat sub.mk 
all:
	@echo $(MAKELEVEL)
	$(MAKE) -f sub2.mk
$ cat sub2.mk 
all:
	@echo $(MAKELEVEL)
```

実行してみると親の場合には0、そこから深くなるにつれてレベルが1ずつ上がっていることが確認できます。
```
$ make
echo 0
0
make -f sub.mk
make[1]: Entering directory `/home/tsuyoshi/git/memo/Makefile/test'
1
make -f sub2.mk
make[2]: Entering directory `/home/tsuyoshi/git/memo/Makefile/test'
2
make[2]: Leaving directory `/home/tsuyoshi/git/memo/Makefile/test'
make[1]: Leaving directory `/home/tsuyoshi/git/memo/Makefile/test'
```

### 再帰make実行時に親側で定義された変数を、親側から実行されたMakefile内部でも参照したい
デフォルトでは、呼び出し側の Makefile で定義した変数の値は、sub-make 側に渡されません。
この場合にはexportディレクティブを使う必要があります。

次の2つのファイルを用意します。
```
$ cat Makefile 
export HOGE = 100
all:
	$(MAKE) -f sub.mk
```
```
$ cat sub.mk 
all:
	@echo $(HOGE)
```

ではmakeを実行してみます。
```
$ make
make -f sub.mk
make[1]: Entering directory `/home/tsuyoshi/git/memo/Makefile/test'
100
make[1]: Leaving directory `/home/tsuyoshi/git/memo/Makefile/test'
```

なお、Makefile中で定義された全ての変数をsub-make側に渡すには引数を指定せずにexportを記述します。
このとき、特定の変数だけ除外したい場合にはunexportで定義しておく必要があります。
```
export
unexport FOO BAR
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
Makefile2:2: \*\*\* ccccc.  Stop.
```

errorの場合には必ずその行で停止します。
参考: http://quruli.ivory.ne.jp/document/make_3.79.1/make-jp_7.html#Make-Control-Functions

- 3.デバッグ情報を出力したい
--debugオプションを付加すればよい。
```
   $ make --debug 
```

### 全てのコマンドエラーを無視させたい場合
すべてのコマンドのエラーを無視するようにするには、make を実行するときのパラメータに -i (--ignore-erros) を指定するか、スペシャルターゲットの .IGNOREを prerequisites を指定せずに Makefile の中に記述します。
なお、上記は一時的な対処であって、本来は"-"でコマンド毎の振る舞いにより判断することが推奨されています。

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

# 参考
- Makefile公式マニュアル
  - 1ページ内に全てを表示してくれるので検索する際にも非常に便利
  - http://www.gnu.org/software/make/manual/make.html
- 公式ドキュメント
  - 非常に豊富なドキュメント群
  - https://www.gnu.org/software/make/manual/html_node/index.html#Top
- もっとも豊富な日本語リファレンス(GNU Make GNU make Version 3.77)
  - http://www.ecoop.net/coop/translated/GNUMake3.77/make_toc.jp.html
- MakeとMakefileの説明
  - http://www.unixuser.org/~euske/doc/makefile/
- POSTD: Makeについて知っておくべき7つのこと
  - https://postd.cc/7-things-you-should-know-about-make/
- Makefileの書き方に関する備忘録 (第１回〜第４回)
 -　http://minus9d.hatenablog.com/entry/20140203/1391436293


