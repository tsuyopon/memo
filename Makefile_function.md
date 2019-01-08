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

# Text-Functions
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

# value-Function

## value
- 書式
  - VARIABLEを変数として解釈する
```
$(value VARIABLE)
```
- 使い方
```
$ cat Makefile 
FOO = $PATH

all:
	@echo $(FOO)
	@echo $(value FOO)
```
- 実行結果
  - 最初の行の結果は意図しない"ATH"という値となってしまっているが、後者の行は意図した結果となっている。
```
$ make
ATH
/usr/local/bin:/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:/opt/X11/bin:
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
