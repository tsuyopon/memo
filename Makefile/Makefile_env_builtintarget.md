# Makefileで利用可能な環境変数について

Makefileで重要となる次のような情報についてまとめています。
- 環境変数
- マクロ変数
- .PHONYなどの特別なターゲット

公式資料

- .PHONY, .SUFFIXESなどについては以下の「Special Built-in Target Names」を参考のこと
  - https://www.gnu.org/software/make/manual/html_node/Special-Targets.html

# 詳細
### GNU MAKEの定義済みマクロ変数
```
マクロ名    文字列     説明
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
CTANGLE     ctangle    知らね
RM          rm -f      ファイルの削除
```

引数用マクロ変数
```
マクロ名    文字列 説明
ARFLAGS     rv ARの引数
ASFLAGS     ASの引数
CFLAGS      CCの引数
CXXFLAGS    CXXの引数   // C++プリプロセッサ用なので-std=c++11 などを入れるのは誤り
COFLAGS     COの引数
CPPFLAGS    CPPの引数   // C++コンパイラ用
FFLAGS      FCの引数
GFLAGS      GETの引数
LDFLAGS     リンカldの引数
LFLAGS      LEXの引数
PFLAGS      PCの引数
RFLAGS      知らね
YFLAGS      YACCの引数
```

"make -p"と実行すればどの拡張子でどのような環境変数を使って実行しているのかがわかります。
```
LINK.c = $(CC) $(CFLAGS) $(CPPFLAGS) $(LDFLAGS) $(TARGET_ARCH)
LINK.cc = $(CXX) $(CXXFLAGS) $(CPPFLAGS) $(LDFLAGS) $(TARGET_ARCH)
```

### .PHONY
Makefile中にcleanというターゲットが存在していて、万が一そのディレクトリにcleanファイルが存在していると以下のエラーになる。
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
サフィックスルール適用対象の拡張子の定義です。左のほうが優先度が高いです。
.c.oは.SUFFIXESで指定された拡張子でないと有効になりません。

xxxx.cやxxxx.oが存在する場合にはmake xxxxとするだけで実行されるターゲットを生成することができます。この場合には.SUFFIXESに対象の拡張子を指定する必要があります。
次のようなにMakefileを準備してカレントディレクトリにxxxx.cが存在していればmake xxxxのみでコンパイルすることができます。
```
.SUFFIXES: .c .o
.c.o:
	$(CC) $(CFLAGS) -c $<
```


### .DEFAULT
.DEFAULTを定義するとルールやエントリが見つからなかった場合に実行するターゲットを定義します。
ターゲットを指定しなくても実行できるようにするには"default: all"もかいておくと良い。
```
default: all

.DEFAULT:
	cd src && $(MAKE) $@
```

### .PRECIOUS


### .DEFAULT_GOAL
デフォルトターゲット(all)からの変更する場合には.DEFAULT_GOALを利用します。(3.8.1より利用可能) 
以下の例の場合には、デフォルトで2ndというターゲットが実行されます。
```
.DEFAULT_GOAL := 2nd 
```

