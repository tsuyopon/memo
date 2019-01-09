# Makefileのコマンドラインで指定可能なオプションについて

# makeコマンドやオプション

### 強制的に全実行したい
毎回make clean && makeと打つと実行時間ももったいないので次のコマンドで強制的に全実行させられるらしい
```
$ make -B
```

最新だよと言われたり、途中までビルドされてしまった状態でも、Bオプションを付与すると最初からすべてを実行してくれます。
```
$ make hello 
make: `hello' is up to date.
$ make hello -B
cc -Wall -I/usr/local/include  -march=native hello.c   -o hello
```

### ドライランを実行したい
nオプションでコマンドを実行しませんが、実行するコマンドを出力してくれます。
```
$ make -n hello
cc -Wall -I/usr/local/include  -march=native hello.c   -o hello
```

### Makefile内で-(ハイフン)を付加していなくても、コマンドがエラー時は処理を継続させたい
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

### 別のディレクトリへと移動してmakeを実行したい
Cオプションの後にディレクトリを指定するとそのディレクトリに移動してmakeを実行します。
```
$ make -C dir
```

例えば、このCオプションはMakefile中で次のように複数のディレクトリで実行したい場合に利用される。
```
SUBDIRS = lib bin util
$(SUBDIRS):
        $(MAKE) -C $@
```

### make であらかじめ定義されている規則・マクロをすべて展開し表示して確認したい
pオプションですべての規則やマクロを表示します。出力量が非常に多いので一部のみ表示しています。
```
$ make -p
...
# environment
PATH = /usr/local/bin:/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:/opt/X11/bin:/Applications/Wireshark.app/Contents/MacOS
# default
LD = ld
# default
TEXI2DVI = texi2dvi
# default
YACC = yacc
# default
COMPILE.mod = $(M2C) $(M2FLAGS) $(MODFLAGS) $(TARGET_ARCH)
# makefile (from `Makefile', line 1)
CFLAGS = -Wall
...
```

### 複数のプロセッサで並列実行する
並列実行したいジョブ数をjオプションで指定します。
```
$ make -j 2
```

### その他のオプション(未調査)
```
-t 
   生成コマンドを何も実行せず、指定されたターゲットを touch する。 
-e 
   make 内で定義されたマクロよりも環境変数の値を優先する。
```

### 一時的に変数を変更したい
以下の様にして、引数に変数を指定することもできる。   
たとえば、ccからgccにコンパイラを変更したい場合は以下の様にする。   
```
$ make CC=gcc
```
