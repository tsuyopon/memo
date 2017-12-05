# 概要
perlでプログラムを操作するために必要な次のような操作について説明する。
- 変数の代入, while, if-else, undef
- chomp, comment, @ARGV, ダイヤモンド演算子, =>, next, last, my, local, our, caller
- 配列, 無名配列, ハッシュ
- Pragma, strict, warning, constanc, diagnostics

# perl基礎知識
###  perlの基本的原則
-リテラル(値を表現する方法)の例を以下に示します。
```
6129[10進数] (61_29などリテラル間に_を挟みこんで、読みやすくする事が可能)
0377[8進数]  (0から始まるものは8進数)
0xff[16進数] (0xで始まるものは16進数)
0b11111111[2進数]  (0bで始まるものは2進数)
```
- 常にプログラム中に現われる整数の定数は浮動小数点として扱われる。
- 変数展開を行ないたい時はダブルクォーテーションで囲む。
```
$test = 5;
$file = "$test";          <== これは単独なので$file = $test;で良い
$file = "This is $test";  <== これは良い書き方
```
- 文字列の値は.(ピリオド)演算子によって連結することができる。
```
$test = "hello". " "  . "world"; <== $testはhello worldになる。
```
- 文字列繰り返し演算子(x)は左オペランドを右オペランドで指定した階数だけ繰りかえす。
```
$test = "tsuyoshi" x 3; <== $testはtsuyoshitsuyoshitsuyoshiになる。
$test2 = 5 x 3; <==$test2は555になる。
```
- スカラーの代入(以下に例を示します)
```
$test = 15;         <= $testに値15を代入する。
$test2 = 'hello';   <= $test2は5になる。
$test2 = $test + 3; <= $test2は18になる。
$test2 = $test * 2; <= $test2は30になる。
```
- 二項代入演算子
```
$test = $test + 5 ;   <===等価==>  $test += 5 ;
$test = $test . " ";  <==等価==>   $test .= " ";
```
- printによる出力
```
print "The answer is ";
print 6 * 7;
print ".\n";
上記の3行は以下の1行と等価です。
print "The answer is ", 6 * 7, ".\n";
```
- ブール値
  - 数値の0は偽で、1は真です。特別な値undefは偽です。
  - 空文字列('')は偽です。通常それ以外の全ての文字列は真になります。
  - ゼロを文字列で表した'0'は数値のゼロと同じ値(偽)になります。
- if-else文
  - if文はif(){〜}で表されます。以下ではif〜else文で例を示します。
```
if($test gt 0){
    print "'$test' is greater than 0";
  }else{
    print "'$test' is smaller than 0";
}
```
- while文
```
$count = 0;
while ($count < 10){
  $count += 1;
  print "count is now $count \n";
}
```
- 未定義値(Undefined value)
  - 変数は最初に値を設定されるまでは、特別な値undefを持っています。このundefを数値のように扱うと、0として振舞います。
  - undefを数値として使うと自動的に0として振舞うので、数値の和を求める変数を0で初期化せずに使うことができる。以下に例を示す。
```
$n = 1;
while($n < 1){
  $sum += $n;   <=== sumは0で初期化せずに使っている(undefの性質)
  $n += 2;
}
```

### ユーザーの入力とchomp演算子
スカラー値が期待される場所にを置くと、それを評価するたびに標準入力から、
次の1行(つまり、最初に現われる改行文字まで)が読みこまれて、それがになる。
chomp演算子はその文字列が改行文字で終っている場合に、その改行文字を削除します。
次の例を見てみます。
```
$line = ;
$line2 = chomp($line);
print $line2;
```
ここでSTDINでtest\n(改行)を入力したとすると、testが返される。

### コメントの追加について
複数行に渡るコメントを作成する場合には以下のようにする。
```
=comment
   ここの中は複数行にわたるコメント
   プログラムの動作には影響を与えない。
=cut
```

また、行の間に/* 〜 */で入れる場合にはAcme::Commentモジュールを利用すれば実現することができるらしい。

### @ARGV(起動引数リストが格納された特殊配列)について
一般的に入力では@ARGVが空リストであれば、標準入力ストリームを使い、そうでなければ@ARGVに入っているファイル名のリストを使用します。これはプログラムの実行を開始してから、ダイヤモンド演算子を初めて使用するまでの間に、@ARGVの内容をいじれるチャンス
があるという事を意味します。
例として次のようにすれば、ユーザーがコマンドラインで何を指定しようとも、常に3つの決まったファイルを処理することができます。

```
@ARGV =qw# test1 test2 test3 #;
while (<>){
  chomp;
  print "It was $_\n";
}
```

### デフォルト変数($_)
foreachとwhileで使用できる。以下に例を示す。
```
<例1>                     <例2>
while(){                  foreach(){
  print "I saw $_";                 print "I saw $_";  
}                                }
```
上記2つの違いはwhileの場合は1行1行読みこみ処理し、foreachは一気に全てを読み込み処理する。これはログファイルなどの厖大なファイルではwhileの方が良いだろう。

### ダイヤモンド演算子<>を使用して入力を引数として与えたい。
ダイヤモンド演算子は引数として入力を与えたいときに使用されます。
例えば、以下のようなperl.plファイルを作成したとします。
```
while(<>){
  chomp;                <== 引数を省略するとchompは$_に作用する
  print "It was $_\n";
}
```
ここで$perl perl.pl test1 test2として2つの引数(test1とtest2)を与えたとすると
```
It was test1
It was test2
```
と表示されます。

### ループの制御方法について(last, next)
ループとはwhile, until, for, foreachの4つで繰り返しを実行しているものをさします。
- next: ループをスキップする
- last: ループを終了する

###  =>について
これはカンマと同様みたいです。


## スコープについて
### localとmyの違いを理解する
- local: 宣言されたサブルーチンから呼び出されたサブルーチンからは参照が可能。
- my:    完全に局所化されるため、localのように、サブルーチンから呼び出されたサブルーチンからも参照することはできない。

以下のパターン1とパターン2を比較してみるとわかりやすいです。

```
<パターン1>
$word = "晴れ";
&today;

sub today {
    local $word = "雨";
    &yesterday;
    print "今日は$wordです。\n";
}

sub yesterday {
    print "昨日は$wordでした。\n";
}

[実行結果]
  昨日は雨でした。
  今日は雨です。 
```

```
<パターン2>
$word = "晴れ";
&today;

sub today {
    my $word = "雨";
    &yesterday;
    print "今日は$wordです。\n";
}

sub yesterday {
    print "昨日は$wordでした。\n";
}

<実行結果>
  昨日は晴れでした。
  今日は雨です。 
```

### ourについて
ourはパッケージ化された中の変数宣言として利用されます。
これにより、他のプログラムから呼び出された時に$Serverなどとして簡単に利用できます。


## サブルーチンについて
### サブルーチンを定義する。サブルーチンを呼び出す。
以下に簡単な例を示す。
```
&test-func;
&test-func;
&test-func;

sub test-func {
      $n += 1;
      print "number $n!\n";
}
```

上記を見ればわかるがサブルーチンはsubで定義し、呼び出すときは関数名にアンパーサンド(&)を付加する。
サブルーチンの中で行なわれた最後の結果が自動的に戻り値となる。
つまりtest-funcは一回目は「number 1」が戻り値、2回目は「number 2」が戻り値、3回目は「number 3」が戻り値となる。

### perlの引数は実は参照渡しである
```
$a = 100 ;
&sub_A ($a);
print $a ;

sub sub_A{
   # 引数の更新
   $_[0] = 10 ;
} 
```

既に参照渡しなのです。これはprint $aの出力結果は10になります。

### どこのファイルの何行目から、サブルーチンが呼ばれているのか知りたい
caller関数を利用します。
具体的にはサブルーチンの中で利用します。
```
#/usr/bin/perl 

package zzzz1;
&zzzz2::a();

package zzzz2;
sub a {
   my @call = caller;
      foreach(@call){
      print "$_\n";
   }
}
```

上記ファイルをa.plとして保存し、実行すると以下の出力となります。
```
zzzz1
a.pl
4
```


## 配列操作について
### 引数の最後の番号が知りたい
以下の様にして配列名に
```
$#
```
を付加すればよい

```
@test = ( "a", "b", "c", "d", "e");
print $#test."\n";                      <=4が出力される。
```

### 配列の最後の引数にアクセスする
```
@test = ( "aaa", "bbb", "ccc", "ddd", "eee" );
print $test[$#test];
```

### 配列の列挙
```
-----------その1-----------

@files = <*.txt>;#ワイルドカードに当てはまるファイル名を配列で取得

#配列の値を列挙
foreach ( @files ) {
 $file=$_;
 print $file,"\n";
}
```
 
```
-----------その2-----------

@files = <*.txt>;

$size=@files;#配列のサイズを求める

for($i=0;$i<$size;$i++){
 print $files[i];
}
```

### 無名配列コンストラクタの定義
角カッコにより無名配列であることを表すことができます。
```
$test1 = [ "test1", "test2", "test3", "test4" ];    <= 変数に入れていることに着目
```

リストと比較した場合の無名配列コンストラクタの利点は、中間変数を持っていないために理解しやすい点があります。

* 参考URL
- perldsc - Perl のデータ構造クックブック 
  - http://www.kt.rim.or.jp/~kbk/perl5.005/perldsc.html

## ハッシュ操作について
### 配列基本
```
while (($key, $val) = each (%fruit)) {
      print "キー: $key, 値: $val\n";
} 
```

### ハッシュのハッシュを宣言する。
以下に例を示します。
```
%HoH = (
flintstones => {
      lead      => "fred",
      pal       => "barney",
   },
      jetsons     => {
      lead      => "george", 
      wife      => "jane",
      "his boy" => "elroy",
   },
      simpsons    => {
      lead      => "homer",
      wife      => "marge",
      kid       => "bart",
   },
);
```

### ハッシュのハッシュで最下位層の値を全て取り出す。
以下に例を示します。ポイントは$HoH{$family}を %{ 〜 }で囲んでいるところです。
```
foreach $family ( keys %HoH ) {
   print "$family: { ";
      for $role ( keys %{ $HoH{$family} } ) {
         print "$role=$HoH{$family}{$role} ";
      }
   print "}\n";
}
```

### 無名ハッシュコンストラクタ
```
my $ref1 = (
 "name" => "tsuyoshi",
 "position" => "adult",
);

my $ref2 = (
 "name" => "yuta",
 "position" => "child",
);

my @family = ( $ref1, $ref2)
```

## Pragmaについて
Pragma(プラグマ)はコンパイル時にコンパイラに対して指示を与える特殊なモジュールです。

### strictプラグマ

use strictの利用により下記３機能が動作するみたいです。
```
use strict "vars"; // 変数宣言をしないまま使用するとエラーになる機能
use strict "refs"; // シンボリックリファレンスを禁止する機能
use strict "subs"; // ベア(裸の)ワードの詩的な最適化を禁止する機能
```

- 参考URL
  - とりあえずメモメモ。
  - http://d.hatena.ne.jp/hiront_at_nagoya/20090120/1232468705

### warningプラグマ
Perl が発する警告を制御します

### constantプラグマ
シンボル名のある定数を宣言します。
この定義はリストコンテキストとして評価されます。
```
use constant MAX => 100;
```

### diagnosticsプラグマ
警告やエラーで出力されるメッセージをより詳細なものに変更します。

### 参考URL
- Perl5編　第３８章　プラグマ
  - http://www.geocities.jp/ky_webid/perl5/038.html
