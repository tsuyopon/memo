# 概要
perlでのデバッグ方法についてまとめておきます

デバッグしたい場合には-dオプションを付与するだけでインタプリタが起動します。
```
$ perl -d <programname>
```

### 基本コマンド
よく使うコマンドを表示するが、これ以外にもたくさんオプションがある。
詳しくは"h"コマンドのヘルプを参照すること
```
s             # ステップイン
n             # ステップオーバー
Enter         # s か n を繰り返す。
c 行番号      # 指定した行番号まで移動(行番号なしの場合は、ブレークポイントまで)
c 関数名      # 指定した関数まで移動
v 行番号      # 行番号付近のコードを見る
.             # 現在の行を見る
p 変数        # 変数を表示する
x 変数        # 配列、ハッシュを再帰的に表示する(便利)
b 行番号      # 指定した行番号にブレークポイントを設定
b 関数名      # 指定した関数にブレークポイントを設定
h             # ヘルプ
```

### ソースコード中でブレークポイントを指定する
以下のコードを入れておけば自動的にブレークポイントが設定されるようです。
$DBというのはデバッガの為のクラスです(データベースじゃありません)
```
$DB::single = 1;
```

### デバッガを使ってみる
以下をtest.plなどとして保存する。
```
#!/usr/local/bin/perl -w 
use strict;
use warnings;

#国に関する情報を表すハッシュのリファレンス
my $countries = {
  japan => {
    population => 100_000_000,
    language => 'Japanese'
  },
  usa => { 
    population => 200_000_000,
    language => 'English'
  },
  britain =>{
    population => 60_000_000,
    language => 'English'
  },
  china =>{
    population => 1_000_000_000,
    language => 'Chinese'
  }
};

my $population_total = get_population_total($countries);
print "Population Total: $population_total\n";

my $countries_use_english = get_country_from_lang($countries, 'English');

1;

#人口の合計を求める
sub get_population_total {
  my $countries = shift;
  my @names = keys %$countries;
  
  my $population_total = 0;
  for my $name (@names){
    $population_total += $countries->{$name}{population};
  }
  return $population_total;
}

#言語名から国名を求める。
sub get_country_from_lang {
  my ($countries, $one_language) = @_;
  
  my @names = keys %$countries;
  my $countries_use_one_lang = [];
  
  #引数で指定した言語を使う国々を求める
  for my $name (@names){
    push @$countries_use_one_lang, $name
      if $countries->{$name}{language} eq $one_language
  }
  return $countries_use_one_lang
}
```

使ってみる。操作方法などはgdbなどと同じなので使い易い
```
$ perl -d test.pl 
...
main::(test.pl:7):	my $countries = {
main::(test.pl:8):	  japan => {
main::(test.pl:9):	    population => 100_000_000,
main::(test.pl:10):	    language => 'Japanese'
  DB<1> n
main::(test.pl:26):	my $population_total = get_population_total($countries);
  DB<2> n
main::(test.pl:27):	print "Population Total: $population_total\n";
  DB<2> p $population_total
1360000000
  DB<3> b get_country_from_lang               // ブレークポイントを貼る

...
  DB<4> n
main::(test.pl:27):	print "Population Total: $population_total\n";
  DB<4> 
Population Total: 1360000000
main::(test.pl:29):	my $countries_use_english = get_country_from_lang($countries, 'English');
  DB<4> s                                     // ステップイン実行する
main::get_country_from_lang(test.pl:47):
47:	  my ($countries, $one_language) = @_;
  DB<4> x @_                                  // ハッシュなどはxを使うと便利
0  HASH(0x7fee0b8f9fc0)
   'britain' => HASH(0x7fee0b96f150)
      'language' => 'English'
      'population' => 60000000
   'china' => HASH(0x7fee0b82ee28)
      'language' => 'Chinese'
      'population' => 1000000000
   'japan' => HASH(0x7fee0b834648)
      'language' => 'Japanese'
      'population' => 100000000
   'usa' => HASH(0x7fee0b9706b8)
      'language' => 'English'
      'population' => 200000000
1  'English'
````

終わったらプログラムを再実行するにはRを、デバッガを終了するにはqを押下します。

### 次に移動する(next, step)
gdbと同様にnとsがあります。 nはnextと同様、sはstepと同様です。

### バックトレースを表示する
Tを使えばOK
```
  DB<5> T
@ = DB::DB called from file 'test.pl' line 49
$ = main::get_country_from_lang(ref(HASH), 'English') called from file 'test.pl' line 29
```

### ブレークポイントの設定
bコマンドでオプションを設定することができる。
```
  DB<10> b get_population_total
  DB<11> b get_country_from_lang
```

Lコマンドでブレークポイント、ウォッチ、アクションを閲覧できる。
```
  DB<12> L       
test.pl:
 35:	  my $countries = shift;
    break if (1)
 47:	  my ($countries, $one_language) = @_;
    break if (1)
```



### サブルーチンから戻る
gdbでのfinishと同じと思われるのがr(return)となります。  
rはサブルーチンの戻り値も表示してくれるようです。
```
  DB<5> T
@ = DB::DB called from file 'test.pl' line 50
$ = main::get_country_from_lang(ref(HASH), 'English') called from file 'test.pl' line 29
  DB<5> r
scalar context return from main::get_country_from_lang: 0  'usa'
1  'britain'
main::(test.pl:31):	1;
  DB<5> T
@ = DB::DB called from file 'test.pl' line 31
```

### プログラムを再実行する
runに相当するのがRです。大文字と小文字では役割が違うので注意が必要です。  
スクリプトの実行が終了すると以下のメッセージが表示されます。
```
Debugged program terminated.  Use q to quit or R to restart,
use o inhibit_exit to avoid stopping after program termination,
h q, h R or h o to get additional info.
```

Rコマンドで再度スクリプトを実行します。
```
  DB<15> R
```

### 現在いる行を表示する。
```
  DB<7> .
main::get_population_total(test.pl:40):
40:	    $population_total += $countries->{$name}{population};
```

### N行目付近のコードを取得する
vの後に行数を入力すると取得できる。
```
  DB<1> v 30
27:	print "Population Total: $population_total\n";
28 	
29:	my $countries_use_english = get_country_from_lang($countries, 'English');
30 	
31:	1;
32 	
33 	#人口の合計を求める
34 	sub get_population_total {
35:	  my $countries = shift;
36:	  my @names = keys %$countries;
```

### 特定の変数の値が変わったことを検知する
wのあとに変数名を指定すると、c, nやsなどで処理を実行していると値が変わった際に前後の値の状態を表示してくれます。
```
  DB<6> w $population_total
  DB<7> n
Watchpoint 0:	$population_total changed:
    old value:	''
    new value:	'0'
main::get_population_total(test.pl:39):
39:	  for my $name (@names){
  DB<7> 
main::get_population_total(test.pl:40):
40:	    $population_total += $countries->{$name}{population};
  DB<7> 
Watchpoint 0:	$population_total changed:
    old value:	'0'
    new value:	'200000000'
main::get_population_total(test.pl:40):
40:	    $population_total += $countries->{$name}{population};
  DB<7> 
Watchpoint 0:	$population_total changed:
    old value:	'200000000'
    new value:	'300000000'
main::get_population_total(test.pl:40):
40:	    $population_total += $countries->{$name}{population};
```

上記で設定したウォッチはLコマンドで見ることができます。
実はこのLはブレークポイント、ウォッチ、アクションそれぞれを表示するコマンドです。
```
  DB<7> L
Watch-expressions:
 $population_total
```

ウォッチを削除するには大文字のWのあとにその変数名を指定すればOK
```
  DB<7> W $population_total
  DB<8> L
  DB<8> 
```

全てのウォッチを削除する場合には引数にアスタリスクを指定すればOKとなる
```
  DB<7> W *
```

### スカラ値を表示する

### ハッシュを表示する
pだとHASH隣ってしまう場合にはxコマンドを利用して見ることができる
```
  DB<4> p $countries
HASH(0x7f93f28b5f68)
  DB<5> x $countries
0  HASH(0x7f93f28b5f68)
   'britain' => HASH(0x7f93f1a2def0)
      'language' => 'English'
      'population' => 60000000
   'china' => HASH(0x7f93f1808360)
      'language' => 'Chinese'
      'population' => 1000000000
   'japan' => HASH(0x7f93f180ca08)
      'language' => 'Japanese'
      'population' => 100000000
   'usa' => HASH(0x7f93f1a2df50)
      'language' => 'English'
      'population' => 200000000
```

### 正規表現でブレークポイントを設定する
//の中に検索したい表現を記述すれば良い。
```
  DB<3> /language/
55:	      if $countries->{$name}{language} eq $one_language
```

### ファイルを移動する
以下は同じファイルを操作している際の出力例で実際に試したわけではないがおそらくfコマンドでいけるはず...
```
  DB<2> f test.pl
Already in test.pl.
```

### モジュールバージョンを表示する
```
  DB<5> M
'Carp.pm' => '1.29 from /System/Library/Perl/5.18/Carp.pm'
'Config.pm' => '5.018002 from /System/Library/Perl/5.18/darwin-thread-multi-2level/Config.pm'
'Config_git.pl' => '/System/Library/Perl/5.18/darwin-thread-multi-2level/Config_git.pl'
'Config_heavy.pl' => '/System/Library/Perl/5.18/darwin-thread-multi-2level/Config_heavy.pl'
'Exporter.pm' => '5.68 from /System/Library/Perl/5.18/Exporter.pm'
'IO.pm' => '1.28 from /System/Library/Perl/5.18/darwin-thread-multi-2level/IO.pm'
'IO/Handle.pm' => '1.34 from /System/Library/Perl/5.18/darwin-thread-multi-2level/IO/Handle.pm'
'SelectSaver.pm' => '1.02 from /System/Library/Perl/5.18/SelectSaver.pm'
'Symbol.pm' => '1.07 from /System/Library/Perl/5.18/Symbol.pm'
'Term/Cap.pm' => '1.13 from /System/Library/Perl/5.18/Term/Cap.pm'
'Term/ReadLine.pm' => '1.12 from /System/Library/Perl/5.18/Term/ReadLine.pm'
'XSLoader.pm' => '0.16 from /System/Library/Perl/5.18/XSLoader.pm'
'arybase.pm' => '0.06 from /System/Library/Perl/5.18/darwin-thread-multi-2level/arybase.pm'
'dumpvar.pl' => '/System/Library/Perl/5.18/dumpvar.pl'
'feature.pm' => '1.32 from /System/Library/Perl/5.18/feature.pm'
'perl5db.pl' => '1.39_10 from /System/Library/Perl/5.18/perl5db.pl'
'strict.pm' => '1.07 from /System/Library/Perl/5.18/strict.pm'
'vars.pm' => '1.03 from /System/Library/Perl/5.18/vars.pm'
'warnings.pm' => '1.18 from /System/Library/Perl/5.18/warnings.pm'
'warnings/register.pm' => '1.02 from /System/Library/Perl/5.18/warnings/register.pm'
```

### ヘルプを表示する
```
  DB<1> h   
List/search source lines:               Control script execution:
  l [ln|sub]  List source code            T           Stack trace
  - or .      List previous/current line  s [expr]    Single step [in expr]
  v [line]    View around line            n [expr]    Next, steps over subs
  f filename  View source in file         <CR/Enter>  Repeat last n or s
  /pattern/ ?patt?   Search forw/backw    r           Return from subroutine
  M           Show module versions        c [ln|sub]  Continue until position
Debugger controls:                        L           List break/watch/actions
  o [...]     Set debugger options        t [n] [expr] Toggle trace [max depth] ][trace expr]
  <[<]|{[{]|>[>] [cmd] Do pre/post-prompt b [ln|event|sub] [cnd] Set breakpoint
  ! [N|pat]   Redo a previous command     B ln|*      Delete a/all breakpoints
  H [-num]    Display last num commands   a [ln] cmd  Do cmd before line
  = [a val]   Define/list an alias        A ln|*      Delete a/all actions
  h [db_cmd]  Get help on command         w expr      Add a watch expression
  h h         Complete help page          W expr|*    Delete a/all watch exprs
  |[|]db_cmd  Send output to pager        ![!] syscmd Run cmd in a subprocess
  q or ^D     Quit                        R           Attempt a restart
Data Examination:     expr     Execute perl code, also see: s,n,t expr
  x|m expr       Evals expr in list context, dumps the result or lists methods.
  p expr         Print expression (uses script's current package).
  S [[!]pat]     List subroutine names [not] matching pattern
  V [Pk [Vars]]  List Variables in Package.  Vars can be ~pattern or !pattern.
  X [Vars]       Same as "V current_package [Vars]".  i class inheritance tree.
  y [n [Vars]]   List lexicals in higher scope <n>.  Vars same as V.
  e     Display thread id     E Display all thread ids.
For more help, type h cmd_letter, or run man perldebug for all docs.
```

# TODO
全ヘルプオプションを試せていない...

# 参考URL
- http://d.hatena.ne.jp/perlcodesample/20080109/1199880506
- perldoc.jp(公式ドキュメント)
 - http://perldoc.jp/docs/perl/5.8.8/perldebug.pod
