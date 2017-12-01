## パッケージ操作

###  パッケージ名宣言について
```
package Test1::Test2::pack;
```

上記の宣言のパッケージは
```
 <@INC内部に存在するディレクトリ>/Test1/Test2/pack.pm
```
に記述しなければならない。
package宣言によってpmファイルの場所も決定するので注意します。
「perldoc -m」などはこれによって決定されていると思われます。


### @EXPORT_OK, @EXPORT_FAIL, @EXPORTについて

- 以下の例ではEXPORT...配列について挙動を学ぶことができます。
  - @EXPORT指定されているsub1, sub2に関しては明示的にインポート指定する必要はありません。
  - @EXPORT_OK指定されているsub3に関しては明示的にインポート指定する必要があります。
  - @EXPORT_FAIL指定されているsub4に関してはインポートしないことを意味しています。
```
package Module;         // Module.pmを作成する場合に定義する
use Exporter;
@EXPORT = qw(sub1 sub2);
@EXPORT_OK = qw(sub3);
@EXPORT_FAIL = qa(sub4);
```

- 参考URL
  - http://www.rfs.jp/sb/perl/04/01.html


## リファレンス操作
### リファレンスを取得する
バックスラッシュ(\)を付加します。以下は例です。
```
変数:      \$test
配列:      \@test
ハッシュ:  \%test
```
 
### デリファレンスを取得する。
- 変数:
```
$ref = \$test;
print $$ref;    <=変数では$をつける
```

- 配列:
```
$ref = \@test;
print @$ref;    <=配列では@をつける
```

- ハッシュ:
```
$ref = \%test;
print %$ref;    <=ハッシュでは%をつける
```

## モジュール操作
### モジュールの読み込みを行う
requireは1度インクルードしたファイルを再度読み込まないように、どのファイルをインクルードしたのかを記憶する仕組みである。
例えば、sample.plを読み込む場合には以下の様にします。
```
 require "sample.pl";
```
requireでインクルードするファイルの最後の行には、通常は
```
 1;
```
を記述します。以下にsample.plの例を示します。
```
#!/usr/bin/perl -w
sub test {
   echo "test";
}
1;       <=必ず付加すること。尚、return 1でも問題ありません。
```

### 設定ファイルの作成について

```
package Test1::Config;
 
our $Server = "test1.co.jp";
```
上記のファイルをuseなどで呼び出せば、既にour宣言されているのでuseしたファイルでも$Serverとして呼び出すことができます。

### コンストラクタを作成したい。
phpの場合などはある特定のメソッド名の場合にはコンストラクタとなりますが、
perlの場合に自分でコンストラクタの名前から決定します。
一般的にはnew()いう名前にするのが作法の様です。パッケージ化したときに行います。
以下にコンストラクタ定義の例を示します。
```
package test;

sub new { 
	my $class = shift; 
	my $self  = {};
	bless $self, $class; 
	return $self;
}
```
尚、外部からnewを引数無しで呼ばれた場合にも第1引数には必ずクラス名が入ります

### デストラクタを作成したい
perlではデストラクタの名前は決まっています。
DESTORYという名前のメソッドを用意します。
```
# デストラクタ
sub DESTROY {
   print "destroy";
}
```
