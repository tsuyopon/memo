# 概要
perlコマンドのオプションについて

# 詳細
- w
  - 一度しか出現しない識別子や、初期化されずに参照される変数など、危険、無駄と思われる処理の警告を出力
- e
  - 指定したプログラムを実行してすぐにperlを終了するオプションである。これを指定するとプログラムファイルは引数として指定できないらしい。
- n
  - 与えたプログラムの外側に下のようなループがあるのと同じような動作をします
```
	 while(<>) {
	    ....
	 }
```
- p
  - ループブロックの内側の最後に print $_; があるように振舞います。
```
	 while(<>) {
	    ....
	   print $_;
	 } 
```
- i
  - 超便利!! 複数のファイルが存在していて一部のみ置換したい場合などに便利
  - (使用例: カレントディレクトリ中のhtml拡張子全てのファイルの「#ffffdd」を「#aaaacc」に変換し、予め.bakを 同ディレクトリ中にとっておく)
```
$  perl -i.bak -p -e 's/#ffffdd/#aaaacc/ig;' *.html
```
  - 以下の様に指定するとバックアップは作成されないので超危険です。
```
$ perl -i -p -e 's/#ffffdd/#aaaacc/ig;' *.html
```
- c
  - perlを実行せずに構文チェックのみ行います。但し、BEGIN, END, useは実行されてしまうようです。
- l
  - pやnオプションと同時に利用すると、ループブロック内の最初でchompを実行するそうです。以下と等価とのことです。
```
	  while(<>) {
	     chomp($_);
    	 ....
	  }
```

- a, F
  - a オプションを指定すると、入力行($_)が自動的に split され、結果が配列 @F にセットます。つまり、  
```
	 $ perl -a -n -e 'print join("," , @F), "\n";' /etc/services
```
  - 上記の文は以下と等価です。
```
	 while(<>) {
	    @F = split(' ');
	    print join("," , @F), "\n";
	 }
```
 - F オプションに続いて split の区切り文字を指定することもできます。
```
	$ perl -F':' -a -n -e 'print join("," , @F), "\n";' /etc/passwd
```


### デバッグしたい 
```
$ perl -d test.pl
```

使用法がわからなければ「h」を入力してエンターを押下します。 簡単に以下に説明します。
```
s   プログラムを1stepずつ実行できる。
x   変数内の値を表示する(わかりやすいフォーマットで表示)
    例: x \%test
```

### コマンドラインからモジュールを読み込み実行したい 
ちょっとした確認の時に便利です。
```
$ perl -MJcode 'print  Jcode->new("もげもげ")->euc'
```

参考までに、以下のたった1行のコードをデバッグしてみます。
```
for $test ( 1 .. 3 ){ print $test };

$ perl -d <script>
main::(test.pl:2):      for $test ( 1 .. 3 ){ print $test };
  DB<1> x $test
0  undef
  DB<2> s
main::(test.pl:2):      for $test ( 1 .. 3 ){ print $test };
  DB<2> x $test
0  1
  DB<3> s
main::(test.pl:2):      for $test ( 1 .. 3 ){ print $test };
  DB<3> 1x $test
0  2
  DB<4> s
main::(test.pl:2):      for $test ( 1 .. 3 ){ print $test };
  DB<4> 2x $test
0  3
  DB<5> s
Debugged program terminated.  Use q to quit or R to restart,
  use O inhibit_exit to avoid stopping after program termination,
  h q, h R or h O to get additional info.
```

### 1行perl(コマンドラインからのperlの実行について) 

(例1)1から100まで出力させたい
```
$ perl -e ' for($i = 0 ; $i <= 100 ; $i++) { print $i."\n" }'
```

上記のように'(シングルクォート)で囲めばよい。


### 型グロブを利用する

コマンドラインで実行してみた以下の出力例を見てください。
```
(パッケージ)::(変数名)
```
で出力されます。
```
$ perl -le 'package test; print *a;'
*test::a

$ perl -le 'print *a;'
*main::a
```

以下の様にして、サブルーチンに適用することが多いみたいです。
```
&func(*a);
```

# 参考URL
- 日本語 perl texinfo について
  - http://www.hariguchi.org/info/ja/perl4/perl-4.0.19.2-ja.html
- 第4回：PerlTips? Perlコマンドラインオプション(Stack)
  - http://www.stackasterisk.jp/tech/program/perl04_04.jsp
