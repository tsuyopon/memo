# Makefileの関数について

自分の方でも手を使ってから記載しているが、ほとんどこちらを参考に記載したものとなっています。
- Qiita: Makefileの関数
  - https://qiita.com/chibi929/items/b8c5f36434d5d3fbfa4a

関数の呼び出しは次のいずれかの方法によって呼び出すことができます。
```
$(関数 引数)
または
${関数 引数}
```

以下の分類に則って自分の方でもまとめてみます。
- https://www.gnu.org/software/make/manual/html_node/Functions.html#Functions

# 各種関数
## filter

- 書式
  - TEXTの中からPATTERNの文字列に一致する要素を取得する。
```
$(filter PATTERN...,TEXT)
```
- 使い方
```
VAR := hoge.h hoge.cpp hogera.h hogera.cpp

.PHONY: all
all:
	@echo "$(filter %.cpp,$(VAR))"
```
- 実行結果
```
$ make
hoge.cpp hogera.cpp
```

## filter-out
- 書式
  - filterの逆を行う
  - TEXTの中からPATTERNの文字列に一致しない要素を取得する。
```
$(filter-out PATTERN...,TEXT)
```
- 使い方
```
VAR := hoge.h hoge.cpp hogera.h hogera.cpp

.PHONY: all
all:
	@echo "$(filter-out %.cpp,$(VAR))"
```
- 実行結果
```
$ make
hoge.h hogera.h
```

## findstring
- 書式
  - IN内にFINDの文字が含まれている要素を取得する。
```
$(findstring FIND,IN)
```
- 使い方
```
VAR := abc def ghi

.PHONY: all
all:
	@echo "$(findstring bc,$(VAR))"
```
- 実行結果
```
$ make
bc
```

## firstword
- 書式
  - NAMES内の最初の要素を取得する
```
$(firstword NAMES...)
```
- 使い方
```
VAR := abc def ghi

.PHONY: all
all:
	@echo "$(firstword $(VAR))"
```
- 実行結果
```
$ make
abc
```

## lastword
- 書式
  - NAMES内の最後の要素を取得する。
  - firstwordの逆の処理を行う
```
$(lastword NAMES...)
```
- 使い方
```
VAR := abc def ghi

.PHONY: all
all:
	@echo "$(lastword $(VAR))"
```
- 実行結果
```
$ make
ghi
```

## patsubst
- 書式
  - TEXT内からPATTERNにマッチした値をREPLACEMENTに置き換えを行う。
```
$(patsubst PATTERN,REPLACEMENT,TEXT)
```
- 使い方
```
VAR := hoge.cpp hogera.cpp .cppfile.o cpp.cpp cpp.x

.PHONY: all
all:
	@echo "$(patsubst %.cpp,%.o,$(VAR))"
```
- 実行結果
```
$ make 
hoge.o hogera.o .cppfile.o cpp.o cpp.x
```

## subst
- 書式
  - TEXT内からFROMにマッチした値をTOに置き換える。
  - patsubstのパターンマッチを利用しないバージョン 
```
$(subst FROM,TO,TEXT)
```
- 使い方
```
VAR := hoge.cpp hogera.cpp .cpp.x

.PHONY: all
all:
	@echo "$(subst .cpp,.o,$(VAR))"
```
- 実行結果
```
$ make
hoge.o hogera.o .o.x
```

公式ドキュメントからもう１つよく使われそうな例を載せておきます。

- 使い方2
```
VPATH = "aaa/bbb:ccc/ddd/eee:/home/test"

.PHONY: all
all:
	@echo $(subst :, ,$(VPATH))
	@echo $(patsubst %,-I%,$(subst :, ,$(VPATH)))
```
- 実行結果2
```
$ make
aaa/bbb ccc/ddd/eee /home/test
-Iaaa/bbb -Iccc/ddd/eee -I/home/test
```


## sort
- 書式
  - LISTの各種要素をソートする
```
$(sort LIST)
```
- 使い方
```
VAR := eee ddd bbb aa ddc aaa

.PHONY: all
all:
	@echo "$(sort $(VAR))"
```
- 実行結果
```
$ make
aa aaa bbb ddc ddd eee
```

## strip
- 書式
  - STRINGの無駄な空白部分を取り除く
```
$(strip STRING)
```
- 使い方
```
VAR := a b    c    d

.PHONY: all
all:
	@echo "$(strip $(VAR))"
```
- 実行結果
```
$ make
a b c d
```

## word
- 書式
  - TEXT内のN番目の要素を取得する
```
$(word N,TEXT)
```
- 使い方
```
VAR := abc def ghi jkl mno pqr

.PHONY: all
all:
	@echo "$(word 5,$(VAR))"
```
- 実行結果
```
$ make
mno
```

## wordlist
- 書式
  - TEXT内をSTART_NUMで指定された番号からEND_NUMで指定された番号までの要素を取得する
```
$(wordlist START_NUM,END_NUM,TEXT)
```
- 使い方
```
VAR := abc def ghi jkl mno pqr

.PHONY: all
all:
	@echo "$(wordlist 4,5,$(VAR))"
```
- 実行結果
```
$ make
jkl mno
```

## words
- 書式
  - TEXT内の要素数を取得する
```
$(words TEXT)
```
- 使い方
```
VAR := abc def ghi jkl mno pqr

.PHONY: all
all:
	@echo "$(words $(VAR))"
```
- 実行結果
```
$ make
6
```

# その他の関数

## abspath
- 書式
  - NAMESの各要素の絶対パスを取得する。ファイルやディレクトリが存在するかどうかはチェックしない。
```
$(abspath NAMES...)
```
- 使い方
```
VAR := ../ ./ ./notexist Makefile

.PHONY: all
all:
	@echo "$(abspath $(VAR))"
```
- 実行結果
```
$ make
/Users/tsuyoshi /Users/tsuyoshi/gomi /Users/tsuyoshi/gomi/notexist /Users/tsuyoshi/gomi/Makefile
```

## realpath
- 書式
  - NAMESの各要素の絶対パスを取得する。
  - abspath関数と異なり、ファイルやディレクトリが存在するかどうかはチェックし、存在するもののみ取得する。
```
$(realpath NAMES...)
```
- 使い方
```
VAR := ../ ./ ./notexist Makefile

.PHONY: all
all:
	@echo "$(realpath $(VAR))"
```
- 実行結果
```
$ make
/Users/tsuyoshi /Users/tsuyoshi/gomi /Users/tsuyoshi/gomi/Makefile
```


## addprefix
- 書式
  - NAMESの要素の接頭辞としてPREFIXを追加する。
  - 複数のinclude path(I)やライブラリパス(L)などで使えるオプション
```
$(addprefix PREFIX,NAMES...)
```
- 使い方
```
VAR := ./include ./dir/include

.PHONY: all
all:
	@echo "$(addprefix -I,$(VAR))"
```
- 実行結果
```
$ make
-I./include -I./dir/include
```

## addsuffix
- 書式
  - NAMESの各要素への末尾にSUFFIXを追加する。
  - フィアルをバックアップしたい場合などに使うことができそうか?
```
$(addsuffix SUFFIX,NAMES...)
```
- 使い方
```
VAR := hoge.cpp hogera.cpp

.PHONY: all
all:
	@echo "$(addsuffix .bak,$(VAR))"
```
- 実行結果
```
$ make
hoge.cpp.bak hogera.cpp.bak
```

## suffix
- 書式
  - NAMESの各要素の拡張子のみを取得する。
  - basename関数の逆バージョン
```
$(suffix NAMES...)
```
- 使い方
```
VAR := hoge.txt ./dir/hogera.txt test.c

.PHONY: all
all:
	@echo "$(suffix $(VAR))"
```
- 実行結果
```
$ make
.txt .txt .c
```


## basename
- 書式
  - ファイル名から拡張子を除去する。ファイルやディレクトリの存在はチェックしない。
  - suffix関数の逆バージョン
```
$(basename NAMES...)
```
- 使い方
```
VAR := hoge.txt ./dir/hogera.txt

.PHONY: all
all:
	@echo "$(basename $(VAR))"
```
- 実行結果
```
$ make
hoge ./dir/hogera
```

## dir
- 書式
  - NAMESの各要素のディレクトリ名を取得する
```
$(dir NAMES...)
```
- 使い方
```
VAR := hoge.txt ./dir/hogera.txt

.PHONY: all
all:
	@echo "$(dir $(VAR))"
```
- 実行結果
```
$ make
./ ./dir/
```

## notdir
- 書式
  - NAMESの各要素のファイル名を取得する
  - basenameの拡張子が付与される版と思えば良い。
```
$(notdir NAMES...)
```
- 使い方
```
VAR := hoge.txt ./dir/hogera.txt

.PHONY: all 
all:
	@echo "$(notdir $(VAR))"
```
- 実行結果
```
$ make
hoge.txt hogera.txt
```

## join
- 書式
  - LIST1とLIST2の結合を行う。要素が一致する対象同士を結合する。
```
$(join LIST1,LIST2)
```
- 使い方
```
VAR1 := a b c d
VAR2 := 1 2 3 4 5

.PHONY: all
all:
	@echo "$(join $(VAR1),$(VAR2))"
```
- 実行結果
```
$ make
a1 b2 c3 d4 5
```

## wildcard
- 書式
  - ワイルドカードを使って実在するファイルを取得する。PATTERNは複数記述できる。
  - 代替としてはshell関数も可能である。
```
$(wildcard PATTERN)
```
- 使い方
```
VAR := /tmp/* ./*

.PHONY: all
all:
	@echo "$(wildcard $(VAR))"
```
- 実行結果
```
$ make
/tmp/com.apple.launchd.77KhTemqSv /tmp/com.apple.launchd.MoOzx9Kjqg /tmp/com.apple.launchd.NqmptkTNvA ./Makefile
```

## shell
- 書式
  - シェルを叩く
```
$(shell COMMAND)
```
- 使い方
```
.PHONY: all
all:
    # shell関数を使うことで例えば"ls *.c"などワイルドカードの代用も可能です。
	@echo "$(shell date)"
```
- 実行結果
```
$ make
Wed Jan  9 08:55:51 JST 2019
```

## call
- 書式
  - 他の変数やマクロを呼び出すときに使用します。
```
$(call VARIABLE,PARAM,...)
```
- 使い方
```
VAR = "var $1 $2"
define MACRO
    @echo "macro $1 $2"
endef

.PHONY: all
all:
	@echo "$(call VAR,a,b)"
	$(call MACRO,a,b)
```
- 実行結果
```
$ make
var a b
macro a b
```

## foreach
- 書式
  - LISTの要素をVARに分解して、TEXTで展開して実行する。
```
$(foreach VAR,LIST,TEXT)
```
- 使い方
```
directories := /tmp /opt
files := $(foreach dir,$(directories),$(wildcard $(dir)/*))

.PHONY: all
all: 
	@echo ${files}
```
- 実行結果
```
$ make
/tmp/com.apple.launchd.77KhTemqSv /tmp/com.apple.launchd.MoOzx9Kjqg /tmp/com.apple.launchd.NqmptkTNvA /opt/X11 /opt/local
```

## flavor
- 書式
  - 変数の状態を表します。
  - flavor関数を使うと次の３つの状態のいずれであるかを判定することができます。
    - undefined: 変数が定義されていない場合
    - simple:    変数が単純に展開された値である場合 (単純展開変数(Simply expanded variables)は":="を使って定義されたもの)
    - recursive: 変数が最適的に展開された値である場合
```
$(flavor VARIABLE)
```
- 使い方
```
DEFINED := test
RECURSIVE = test

.PHONY: all
all:
	@echo $(flavor UNDEFINED)
	@echo $(flavor DEFINED)
	@echo $(flavor RECURSIVE)
```
- 実行結果
```
$ make
undefined
simple
recursive
```

## origin
- 書式
  - どこで定義された変数なのかを知る
  - 取得できる文字列は次の通り
    - undefined: 未定義
    - file:
    - environment:
    - environment override: 
    - override
    - automatic
    - default:
    - command line: 
```
$(origin VARIABLE)
```
- 使い方
```
DEFINED := test
OVERRIDE := test
override OVERRIDE := test

.PHONY: all
all:
	@echo $(origin UNDEFINED)
	@echo $(origin DEFINED)
	@echo $(origin PATH)
	@echo $(origin OVERRIDE)
	@echo $(origin @)
	@echo $(origin MAKE)
```
- 実行結果
```
$ make
undefined
file
environment
override
automatic
default
```
- See
  - https://www.gnu.org/software/make/manual/html_node/Origin-Function.html#Origin-Function

TODO: "environment override" と "command line" はどのような場合に出力させるのか確認。

## value
- 書式
  - VARIABLEを変数として解釈する
```
$(value VARIABLE)
```
- 使い方
```
FOO = $PATH

all:
	@echo $(FOO)
	@echo $(value FOO)
```
- 実行結果
  - 最初の行の結果は$Pが空の変数として扱われて意図しない"ATH"という値となってしまっているが、後者の行は意図した結果となっている。
```
$ make
ATH
/usr/local/bin:/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:/opt/X11/bin:
```

## eval
- 書式
  - 変数を展開した上で、Makefileの構文として定義される
```
$(eval TEXT)
```
- 使い方
  - 以下の例ではターゲット中でCC変数をgccとして定義する際にevalを用いてMakefileの構文であるとして定義している。
```
all:
	$(eval CC := gcc)
	@$(if $(CC:gcc=), \
		echo "$(CC) is not gcc", \
		echo "$(CC) is gcc" \
	)
```
- 実行結果
```
$ make
gcc is gcc
```

- 使い方2 (公式のサンプルを添付しておきます)
```
PROGRAMS    = server client

server_OBJS = server.o server_priv.o server_access.o
server_LIBS = priv protocol

client_OBJS = client.o client_api.o client_mem.o
client_LIBS = protocol

# Everything after this is generic

.PHONY: all
all: $(PROGRAMS)

# $(1)は$1と同じでcall時で指定された引数です
define PROGRAM_template =
 $(1): $$($(1)_OBJS) $$($(1)_LIBS:%=-l%)
 ALL_OBJS   += $$($(1)_OBJS)
endef

$(foreach prog,$(PROGRAMS),$(eval $(call PROGRAM_template,$(prog))))

$(PROGRAMS):
	$(LINK.o) $^ $(LDLIBS) -o $@

clean:
	rm -f $(ALL_OBJS) $(PROGRAMS)
```


# Conditional Function

## and
- 書式
  - 指定した全てのCONDITIONが空でない場合には、最後に指定したCONDTIONXを返す。
```
$(and CONDITION1[,CONDITION2[,CONDITION...]])
```
- 使い方
```
VAR1 := abc
VAR2 := def
VAR3 := ghi

.PHONY: all
all:
	@echo "$(and $(VAR1),$(EMPTY),$(VAR3))"
	@echo "$(and $(VAR1),$(VAR2),$(VAR3))"
	@echo "$(and $(VAR2),$(VAR3),$(VAR1))"
	@echo "$(and $(VAR3),$(VAR1),$(VAR2))"
```
- 実行結果
```
$ make

ghi
abc
def
```


## if
- 書式
  - CONDTIONが空文字でなければTHEN_PARTを返し、CONDITIONが空文字であればELSE_PARTを返す。 
```
$(if CONDITION,THEN_PART[,ELSE_PART])
```
- 使い方
```
VAR1 := abc
VAR2 := def
VAR3 := ghi

.PHONY: all
all:
	@echo "$(if $(VAR1),$(VAR2),$(VAR3))"
	@echo "$(if $(EMPTY),$(VAR2),$(VAR3))"
```
- 実行結果
```
$ make
def
ghi
```


## or
- 書式
  - CONDITION全てが空文字列の場合は空を返す。
  - 1つもで空でなければCONDITION1を返す。CONDITION1が空ならばその次のCONDTIONを返す(以下、繰り返し)
```
$(or CONDITION1[,CONDITION2[,CONDITION...]])
```
- 使い方
```
VAR1 := abc
VAR2 := def
VAR3 := ghi

.PHONY: all
all:
	@echo "$(or $(VAR1),$(VAR2),$(VAR3))"
	@echo "$(or $(VAR3),$(VAR2),$(VAR1))"
	@echo "$(or $(VAR1),$(EMPTY),$(VAR3))"
	@echo "$(or $(EMPTY),$(EMPTY),$(EMPTY))"
	@echo "$(or $(EMPTY),$(VAR2),$(VAR3))"
	@echo "$(or $(EMPTY),$(EMPTY),$(VAR3))"
```
- 実行結果
```
$ make
abc
ghi
abc

def
ghi
```



# Function That Controle Make

レベルとしてはerror>warning>infoとなる。

## error
- 書式
  - errorレベルとなり、処理がSTOPされる。
```
$(error TEXT...)
```
- 使い方
```
.PHONY: all
all:
	@echo "Hello"
	@echo "$(error this is error message!!!)"
	@echo "World"
```
- 実行結果
```
$ make
Makefile:3: *** this is error message!!!.  Stop.
```

## warning
- 書式
  - warningレベルとなり、指定したwarningのアラート情報は表示されるが処理は継続する
```
$(warning TEXT...)
```
- 使い方
```
.PHONY: all
all:
	@echo "Hello"
	@echo "$(warning this is warning message!!!)"
	@echo "World"
```
- 実行結果
```
$ make
Makefile:3: this is alert message!!!
Hello

World
```

## info
- 書式
  - infoレベルとなり、参考となるメッセージ情報が表示される。
```
$(info TEXT...)
```
- 使い方
```
.PHONY: all
all:
	@echo "Hello"
	@echo "$(info this is info message!!!)"
	@echo "World"
```
- 実行結果
```
$ make
this is info message!!!
Hello

World
```

# MEMO

## sample for added
- 書式
  - TBD
```
```
- 使い方
```
```
- 実行結果
```
```

# 参考URL
- Makefile公式マニュアル
  - https://www.gnu.org/software/make/manual/
- Qiita: Makefileの関数
  - https://qiita.com/chibi929/items/b8c5f36434d5d3fbfa4a
- GNU Make
  - http://www.ecoop.net/coop/translated/GNUMake3.77/make_8.jp.html
  - functionについては以下を参考のこと
    - https://www.gnu.org/software/make/manual/html_node/Functions.html#Functions


# TODO
- make 4系で追加されたfile, guileといったオプションは手元の環境が3.81だったのでまだ試せていません。
