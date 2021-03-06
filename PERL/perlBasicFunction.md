# 概要
perlの基本的な関数の仕様について説明する

# 詳細

## 文字列操作

### printf, sprintfを利用する
```
コード 意味 
%c     文字 
%s     文字列 
%d     10進整数 
%e     浮動小数点数（指数形式） 
%f     浮動小数点数（固定小数点形式） 
%e     浮動小数点数（コンパクト形式） 
%o     8進整数 
%x     16進整数 
%X     16進整数（大文字使用） 
```
 
以下にsprintfの例を示す。
```
$time = sprintf("%02d:%02d:%02d", $hour,$min,$sec);
print "$time\n"; 
```

### perlの文字列比較に関して
文字列比較の場合には例えば、「==」ではなくて「eq」を利用する、大小の比較も文字列演算子で行う。
逆に数値の場合には「==」で行うべきです。

```
<意味>              <数値>         <文字列>       <意味>
より小さい          $a < $b        $a lt $b       $a が $b より小さければ真 
より大きい          $a > $b        $a gt $b       $a が $b より大きければ真 
より小さいか等しい  $a <= $b       $a le $b       $a が $b より小さいか等しければ真 
より大きいか等しい  $a >= $b       $a ge $b       $a が $b より大きいか等しければ真 
等しい              $a == $b       $a eq $b       $a と $b が等しければ真 
等しくない          $a != $b       $a ne $b       $a と $b が等しくなければ真 
比較                $a <=> $b      $a cmp $b      $a と $b が等しければ 0, $a が大きければ +1, $b が大さければ -1
```

### 区切り文字による文字の分割および結合
分割はsplit, 結合はjoin関数を利用すればよい。
```
$word = "apple:banana:orange";
@word = split(/:/, $word);
$word = join ":", @word;
```

### 部分文字列を探す
```
$wherefirst = index("Howdy world!","wor");      
$wherelast  = rindex("Yabba dabba doo!","abba");
```
$wherefirstにはindex関数で"Howdy world!"でworに一致しているのは前から何文字目かを調べる。これは上記の例では6が$wherefirstの値となる。
$wherelastにはrindex関数で"Yabba dabba doo!"でabbaに一致しているのは後から何文字目かを調べる。上記の例では7が$wherelastの値となる。


## ファイル操作
### ファイルの終りを知りたい(defined関数)
でファイルの行を次々と読み込み、読みこむ行がなくなると(改行文字ではなく)
undefを返します。値がundefであって、空文字列でないことを確かめるにはdefined関数を使用します。この関数は、引数がundefならば真を返し、それ以外ならば偽を返します。
```
$test = ;
if( defined($test)){
  print "The input was $test";
}else{
  print "No input available!\n";
}
```

明示的に未定義値を得るには、undef演算子を以下のように使用します。
```
$test = undef;
```

### ディレクトリ内の全てのファイルを処理する。
opendir関数でディレクトリをオープンし、readdir関数で各ファイル名を取りだす。
```
opendir(DIR,$dirname) or die "Can't opendir $dirname: $!";
while(defined($file = readdir(DIR))){
    #ここに$dirname/$fileに対する処理を書く。
}
closedir(DIR);
```

## システム操作
### ディレクトリを作成する。
```
mkdir("/usr/local/apache", 0755) or warn "Cannot make apachedir: $!";
```
成功時には 1 を返し、失敗時には 0 を返して、特殊変数$!を設定します。

### 空のディレクトリを削除する
```
rmdir("/home/tsuyoshi/test") or die "Cannot create directory $!\n";
```
成功時には 1 を返します。失敗時には 0 を返し、$!を設定します。

### パーミッションの変更をする
```
chmod(0755,"/home/tsuyoshi","/usr/local/test");
```
この場合2つの引数が指定されている

### カレントディレクトリからの移動
```
chdir("/etc/");
```

### ファイルを削除する
```
unlink("/etc/version"); 
```

### ファイルの名前を変更する
```
rename("/home/tsuyoshi/test1","/home/tsuyoshi/test2");
```
/home/tsuyoshiディレクトリにあるtest1をtest2という名前に変更する。

### あるプロセス番号のジョブを殺したい。(例として4201のジョブ番号をsignal9で殺す)
```
kill(9, 4201) or die "Cannot signal 4201: $!";
```

### ハードリンク(iノード番号が等しい)を作成する
```
link("/usr/lib/liblapack.a","/home/tsuyoshi/lapack");
```

### シンボリックリンクを作成する
```
symlink("/usr/lib/libblas.a","/home/tsuyoshi/blas");
```

### システムコマンドを実行したい
```
system `ls -l $HOME`;
system("ls -l \$HOME");
```
更に、戻り値まで取得したい場合には$?の特殊変数には戻り値(0〜255)が格納される。
正常終了の場合には$?には0が格納されるのでこれを利用して判定すればよい。


## 数値操作

### 数値比較の場合
数値の計算などで比較する場合
```
 if( $tmp lt  $now )
→ $tmpに10が入っていて、$nowに8が入っているとします。
```
とした場合にはこれは、真となってしまいます。これはltによる比較を行っているためです。
数値として正しく判定を行うのであれば、以下の様に判定を行う必要があります。
```
 if( $tmp < $now )
```

### 数学関数を使用してみる
```
$ans = int 10/3;    # $ansは3を返す
$ans = exp 1.0;     # $ansは自然対数のべき乗(左の例では1.0*2.7...)を返す
$ans = log (exp(1)) # $ansは1を返す
$ans = abs -1;      # $ansは-1の絶対値である1を返す
$ans = sqrt 4;      # $ansは4の平方根である2を返す
$ans = sin 0;       # $ansは0(ラジアン単位)のsinを求める
$ans = cos 0;       # $ansは0(ラジアン単位)のcosを求める
$ans = atan2 0;     # $ansは値0の逆正接を求める。$ansは−πからπまでを返す
```


## 時間操作
### localtimeとscalar
```
$ perl -le 'print localtime;'
3435231910832740
```

localtimeにscalar関数を適用するとdateの出力と同様になります。
```
$ perl -le 'print scalar(localtime);'
Wed Oct  1 23:35:35 2008
```

## シグナル操作
### シグナルにより制御を行う
dieやwarn時の動作を決めることができます。
%SIGハッシュに格納します。warnだと$SIG{__WARN__}, dieだと$SIG{__DIE__}に格納します
```
$SIG{__WARN__} = sub {
print STDERR '[IN_HOGE][WARN]';
print STDERR @_;
};

$SIG{__DIE__} = sub {
print STDERR '[IN_HOGE][DIE]';
print STDERR @_;
};
```


## CGI関連操作
###  一番簡単なCGIのサンプル
perlではオプションに汚染モードTとヘッダとしてhtmlタグなどの出力の前に
```
 Content-type: text/html\n\n
```
を出力させないとCGIだと解釈されません。
尚、ファイル名は.cgiにして、CGIが適用されるディレクトリに設置します。(/cgi-binなど)

以下に簡単な例を示します。
```
#!/usr/bin/perl -wT

use strict;

print "Content-type: text/html\n\n";
	 print <<EOD;
	 <html>
	 <head></head>
	 <body>
	 HELLO WORLD!
	 </body>
	 </html>
	 EOD
```

### エンコード、デコードを行う
- エンコード
```
sub url_encode{
   my $text = shift;
   $text =~ s/([^a-z0-9_.!~*'\(\) - -])/sprintf "%%%02X", ord($1)/egi;
   $text =~ tr/ /+/;
   return $text;
}
```

- デコード
```
sub url_decode{
   my $text = shift;
   $text =~tr/\+/ /;
   $text =~ s/%([a-f0-9][a-f0-9])/chr( hex( $1 ) )/egi;
   return $text;
}
```

# 参考資料
- Perl公式ホームページ(English)
  - http://www.perl.com/download.csp
- perldoc.jp
  - http://perldoc.jp/index/core
  - http://perldoc.jp/docs/
- Perl入門
  - http://wisdom.sakura.ne.jp/programming/perl/index.html
- とほほのperl入門
  - http://www.tohoho-web.com/wwwperl.htm
- Perl表技集
  - http://www2u.biglobe.ne.jp/~MAS/perl/waza/
- サンプルコードによるperl入門
  - http://d.hatena.ne.jp/perlcodesample/20100802/1278596435
