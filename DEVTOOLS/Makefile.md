

# Makefileコマンドライン

### Makefile以外のファイルを読み込ませたい。
デフォルトではmakeはMakefileという名前のファイルを読み込む。   
たとえば、Makefile.linuxというファイルを読み込ませたい場合には   
以下の様にする。   
```
   $ make -f Makefile.linux
```

*** Makefileのテストをしたい。 [#n272f3c9]
実際にテストを行いたい場合には、実行するコマンドだけ出力させることができる。
-nオプションを付加するだけでよい。
```
   $ make -n 
```

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

### デバッグ情報を出力したい
--debugオプションを付加すればよい。
```
   $ make --debug 
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



# 基本的な使い方
### プログラムsub1.c,sub2.cがheader.hを必要とする場合の例 [#yd2eb789]
生成コマンドの前には必ず行頭に「タブ」を入れることがルールである。
```
	 a.out: sub1.o sub2.o         # ターゲット a.out の依存ファイルは sub1.o, sub2.o 
	 	cc -o a.out sub1.o sub2.o # a.out の生成コマンド
	 
	 sub1.o: sub1.c               # sub1.o の依存ファイルは sub1.c
	         cc -c sub1.c         # sub1.o の生成コマンド
	 sub2.o: sub2.c               # sub2.o の依存ファイルは sub2.c
	         cc -c sub2.c         # sub2.o の生成コマンド
 
 # header.h はコンパイル時に include されるので、実際には何もしなくてよい
	 sub1.c: header.h             # sub1.c の依存ファイルは header.h
	 sub2.c: header.h             # sub2.c の依存ファイルは header.h
```


# Makefileマクロ
### 各種マクロについて(基本編)
```
- ${マクロ名} あるいは $(マクロ名) 
	 例: $(CC) → gcc
```
これはmakefile内でこの変数が定義されていれば、それを使用する。定義されていなければ、環境変数から取得する。

```
- $@ 
今、実行しようとしている生成コマンドの中で、「それが生成しようとしているターゲット名」に展開される。
	 例: a.out: sub1.o
	               cc -o $@ sub1.o
```
上記の場合には「$@」は「a.out」に展開される。

```
- $<
今、実行しようとしている生成コマンドの中で、そのターゲットが依存しているファイルのひとつに展開される。
	 例: .c.o:
	         cc -c $<
```
ここでmakeがsub1.cからsub1.oを生成するためにこのコマンドを実行するならば、「$<」は「sub1.c」へと展開される。

```
- $*
ターゲット名からサフィックスを除いたものに展開される。
	 例: paper.ps: paper.dvi
	             dvips $*
```
上記の例では「$*」は「paper」に展開される。

```
- $?
依存ファイルで更新されたもののリストに展開される。
	 例: a.out: sub1.c sub2.c
	             echo "$? are modified."
```
上記でもしも、sub1.cだけがa.outよりも新しければ「$?」→「sub1.c」に展開される。

```
$($(マクロ名)) 
マクロを2段階に展開する。
	 例: VAR = CC
	     CC = gcc
```
ここで$($(VAR)) → $(CC) → gcc に展開されることになる。

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

### その他のマクロたち
```
	 $% : ターゲットがアーカイブメンバだったときのターゲットメンバ名
	 $^ : すべての依存するファイルの名前
	 $+ : Makefileと同じ順番の依存するファイルの名前
```

### シェルを実行した結果を変数に格納したい
以下の様にしてshellストリングを利用すれば、whoamiの結果がUNAMEに格納されることになる。
```
   UNAME = $(shell whoami)
```

# Makefileサンプル事例
###  (1)何かしらのコマンドを実行する。
```
 clean: 
 	touch testfile
```
make cleanを実行すれば、testfileが作成されます。   
画面に実行したコマンド結果が出力されていると思います。   
   
また、「make」だけで「make clean」を実行させたい場合もあると思います。   
そのような場合には以下のように「all: clean」を定義します。   
```
 all: clean
 clean: 
 	touch testfile
```

### (2)画面に実行した結果を非表示にしたい。
Makefileに記述したコマンドは画面上に表示されてしまうので、非表示にしたい場合があるかと思います。   
このような場合は「@」をコマンドの先頭につけます。(1)の例で「touch testfile」を画面上に表示させないようにします。
```
 clean: 
 	@touch testfile
```

### (3)ターゲットをコマンドの一部に利用したい
```
 touch:
 	$@ testfile
```
上記では「make touch」とすると、「touch testfile」が実行されます。

### (4)途中で実行エラーとなっても、最後まで処理を行わせたい。
```
 touch:
 	@echo "test1"
 	-@rm zzzzz
 	@echo "test2"
```

例えば、上記のMakefileを実行すると
```
 $ make touch
 test1
 rm: cannot remove zzzzz: No such file or directory
 make: *** [touch] Error 1
```
上記の様にrmで失敗しているので、その後のコマンド「echo "test2"」は実行されません。   
  
そこで、rmで失敗してもその後のコマンドを実行させたい場合には以下の様にします。
```
 touch:
	@echo "test1"
	-@rm zzzzz               <=ここに先頭に"-"が付いた。(但し、先頭は必ずTABであること)
	@echo "test2"
 $ make touch
 test1
```

上記の様に"[TAB]-"という形式で無いとコマンドは無視されないので注意してください。   
上記に変更してからコマンドを実行すると「test2」が出力されているのが確認できます。
```
 test1
 rm: cannot remove zzzzz: No such file or directory
 make: [touch] Error 1 (ignored)
 test2
```

*** (5)別のファイルもMakefileとしてincludeさせたい。 [#h6d92ed8]
例えば、Makefile2として、makeするディレクトリから1つ階層が下のincludeというディレクトリ中に設置した場合には以下の様にします。

```
 (Makefileの例)
 include include/Makefile2
 
 (include/Makefile2の例)
 test:
    echo "TEST"
```

上記の様にすれば「make test」とするとMakefile2のターゲットが読み込まれます。
ここで、以下の様な出力の場合
```
 $ make test
 make: test is up to date.
```
この場合には、同じディレクトリ中に「test」というファイル名が存在していることがあります。   
このような場合にはMakefileを以下の様に修正する必要があります。
```
 .PHONY: test                     <=この1行を追加
 include include/Makefile2
```
.PHONYはターゲット名と同じファイル名が存在した場合に記述する必要があります。

### (6)入力されたターゲットやターゲットの一部を利用したい。
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

### (7)あるファイルが存在しないとターゲットを実行させない。(依存) 
```
 readfile: inputfile.txt
    @cat inputfile.txt
```

上記はinputfile.txtというファイルが存在しない場合には、「make readfile」としても以下の様にターゲットが実行されません。
```
 $ make
 make: *** No rule to make target inputfile.txt, needed by readfile.  Stop.
```
以下の様にinputfile.txtを用意すれば、「cat inputfile.txt」が実行されます。
```
 $ echo "test" > inputfile.txt
 $ make
 test
```

### (8)依存ファイルのリストを表示したい。
```
 all: testfile testfil2
 	@echo $^
```
上記の様に「$^」により依存関係のリストを表示させることができます。
出力例を以下に示します。
```
 $ make
 testfile testfile2
```

### (9)変数の一部を変更したい。(拡張子の一部を変更する) 
```
 TEST= test1.c test2.c
 all:
     @echo $(TEST:.c=.o)
```

上記ではtest1.cとtest2.cの「.c」を「.o」へと変更します。   
出力は以下の様になります。
```
 $ make
 test1.o test2.o
```

### (10) for文等で利用する変数「$i」を解釈させたい。
for文を利用する際には変数を「$i」等と記述しても動作しません。   
このような場合には「$$i」と記述します。
```
 for i in *.sh; do echo $$i;done
```

# 参考URL
- Make と Makefile の説明
 - http://www.unixuser.org/~euske/doc/makefile/
- GNU Make
 - http://www.ecoop.net/coop/translated/GNUMake3.77/make_toc.jp.html
- GNU `make'
 - http://www.gnu.org/software/make/manual/make.html
- GNU make
 - http://www.ecoop.net/coop/translated/GNUMake3.77/make_8.jp.html

