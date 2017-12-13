# 概要
perlの特殊変数について

# 詳細
### 特殊リテラル
```
__LINE__     この文字列自体が置かれている行番号を値として持つ
__FILE__     この文字列自体が置かれているファイル名を値として持つ
__END__      この文字列の在る場所をファイルの尾張として認識して、以降のテキストは無視される。但し、特殊ファイルハンドルDATAによって__END__以降の行を読みこむ事が出来る。
__DATA__     __END__と同様の働きをするが、DATAというファイルハンドルをカレントパッケージ内でDATAファイルハンドルを使用してrequireされたファイル内の__DATA__トークン以降の部分を読み出す用途に使用される。
__PACKAGE__  コンパイル時のカレントパッケージ名を持つ。カレントパッケージがない場合、未定義値となる。
```

### 特殊変数
```
$_       # 入出力操作やパターンマッチ操作において対象を省略したときに使用されるデフォルト変数
$.       # ファイルから読み込み時の現在の行数
$/       # 入力時のレコード区切り文字。通常は改行。
$,       # 出力時の項目区切り文字。print @xx; の時に有効
$"       # 出力時の項目区切り文字。print "@xx"; の時に有効
$\       # 出力時の行末文字。print "$xx"; の後ろに付加される
$#       # 出力時の数値形式。通常は"%.20g"。詳細はprintfを参照
$%       # 出力時の現在のページ番号
$=       # 出力時の現在のライン数
$-       # 出力時の残り行数
$~       # 出力時のフォーマット名(デフォルトはハンドル名と同じ)
$^       # 出力時のヘッダフォーマット名
$|       # 0以外が代入されると出力をバッファリングしなくなる。
$$       # プロセスID
$?       # 最後に実行されたコマンドのステータス
$&       # パターンマッチにマッチした部分文字列
$`       # パターンマッチにマッチした部分の前側の文字列
$'       # パターンマッチにマッチした部分の後側の文字列
$+       # パターンマッチの最後の()に対応する文字列
$*       # 複数行マッチングの制御を行うが、perl5では使用が推奨されていない。
$0       # perlスクリプトのコマンド名
$1,$2,.. # パターンマッチの際の1番目の()に対応する文字列
$[       # 配列の最初の添え字。通常は0。
$]       # perlのバージョン情報
$:       # フォーマット出力において、フィールド内で改行動作に使用される文字列。
         # デフォルトは「\n-」つまり空白、改行文字、ハイフンのいずれか。
$;       # 高次元連想配列の添え字の区切り文字
$!       # 数値コンテキストではエラー番号、文字列コンテキストではエラー文字列
$@       # 直前のevalコマンドのエラーメッセージ
$<       # このプロセスの実ユーザーID
$>       # このプロセスの実効ユーザーID
$(       # このプロセスの実グループID
$)       # このプロセスの実効グループID
$^D      # デバッグフラグの値
$^F      # システムファイルディスクリプタの最大値
$^I      # -iオプションで指定した拡張子の名前
$^L
$^O      # 使用中のオペレーティングシステムの名前
$^P      # デバッガが使用する内部フラグ
$^T      # スクリプトを実行した時刻
$^W      # 警告スイッチの現在値
$^X      # perl自身の起動時の名前
@_       # サブルーチンへの引数
@INC     # perlライブラリ検索ディレクトリ
%INC     # 読み込まれたライブラリファイルの配列
%SIG     # シグナルとシグナルハンドラの情報が格納されているハッシュ
%ENV     # 環境変数の名前と値が格納されているハッシュ
$ARGV    # 現時点で行入力演算子<>から読み込まれているハッシュ名
@ARGV    # コマンドラインからスクリプトに渡される引数の配列
```

### ️環境変数
「-e」はコマンドラインからの処理で、「-l」は各配列の値ごとに改行を行う
```
$ perl -le 'print for @INC'
/etc/perl
/usr/local/lib/perl/5.8.4
/usr/local/share/perl/5.8.4
/usr/lib/perl5
/usr/share/perl5
/usr/lib/perl/5.8
/usr/share/perl/5.8
/usr/local/lib/site_perl
```
 

### ️-Iによる@INCの設定を行う。
例えば、test.plが/home/test/perl/libのディレクトリ中のライブラリを使用 する場合には以下のようにしてコマンドラインから@INCをセットすることができる。
	$ perl -I/home/test/perl/lib  ./test.pl


### ️PERL5LIBによって@INCの設定を行う
PERL5LIB環境変数を設定すればよい
```
$ export PERL5LIB="/home/tsuyoshi/perllib"
```


### 環境変数
```
$ export PERL5LIB=$PERL5LIB:$HOME/lib/perl
$ export PERLLIB=$PERLLIB:$HOME/lib/perl
$ export PERL_BADLANG=0
$ export PERLDOC_PAGER=${PAGER}
```


### 最短マッチ
```
*?         直前の文字を0回以上に最短マッチ 
+?         直前の文字を1回以上に最短マッチ 
??         直前の文字を0又は1回に最短マッチ 
{n}?       直前の文字をn回に最短マッチ 
{n,}?      直前の文字をn回以上に最短マッチ 
{n,m}?     直前の文字をn回以上、m回以下に最短マッチ
```

### パターンマッチで利用するショートカット
```
\w         ワード文字にマッチする。つまり[A-Za-z0-9_]にマッチ
\s         空白文字を表す
\d         数字にマッチする。つまり[0-9]にマッチ
\D         非数字にマッチ
\W         非ワード文字
\S         非空白文字
\b         ワード境界マッチ
```


### パターンマッチに利用される修飾子について
```
g          繰り返しマッチする 
i          大文字と小文字の区別をしない 
o          変数展開を1度だけ行う 
m          文字列を複数行として扱う 
s          文字列を単一行として扱う 
x          拡張正規表現を行う 
e          置換文字列を「式」と見なす(置換の時のみ有効)
```


### ダブルクォート文字列で使用できる逆スラッシュエスケープ 
```
\n         改行
\a         ベル
\t         タブ
\r         復帰
\f         改ページ
\b         バックスペース
\e         エスケープ、ASCIIのエスケープ文字
\007       8進数でASCIIコードを指定(この例は007=ベル)
\x7f       16進数でASCIIコードを指定(この例は7f=削除文字)
\cC        コントロール文字(この例はコントロールC)
\\         逆スラッシュそのもの
\l         次の1文字を小文字にする。
\L         これ以降、\Eまでを小文字にする
\u         次の1文字を大文字にする。
\U         これ以降、\Eまでを大文字にする
\Q         これ以降、\Eまでの全ての非単語構成文字の前に逆スラッシュを挿入する
\E         \L、\U、\Qの効果を終了させる
```


### 変換演算子
trやyは変換演算子である。
```
$word = 'apple';
$word =~ tr/a-z/A-Z/;
print "$word\n";
```

出力結果は次のようになる
```
APPLE 
```

変換演算子用の修飾子が存在します。
```
c           「変換対象の文字」を反転させる。（「変換対象の文字」に含まれない文字すべてをスキャンする） 
d           「変換対象の文字」に含まれるが、対応するものが「変換後の文字」にない文字を削除する 
s           変換の結果、同じ文字が連続したものを1文字とする
```


### ファイル演算子(UNIXのみ意味があるものが結構あるみたいです)
```
-r      # 読み込み可能であれば
-w      # 書き込み可能であれば
-x      # 実行可能であれば
-o      # 自分のものであれば
-R      # 実uid/gidで読み込み可能であれば
-W      # 実uid/gidで書き込み可能であれば
-X      # 実uid/gidで実行可能であれば
-O      # 実uidのものであれば
-e      # 存在すれば
-z      # サイズが0であれば
-s      # サイズが0でなければ(ファイルサイズを返す)
-f      # 通常ファイルであれば
-d      # ディレクトリであれば
-l      # シンボリックリンクであれば
-p      # 名前付きパイプであれば
-S      # ソケットであれば
-b      # ブロック型スペシャルファイルであれば
-c      # キャラクタ型スペシャルファイルであれば
-u      # setuidビットが立っていれば
-g      # setgifビットが立っていれば
-k      # stickyビットが立っていれば
-t      # ファイルハンドルが tty としてオープンされていれば
-T      # ファイルがテキストファイルであれば
-B      # ファイルがバイナリファイルであれば
-M      # perl起動時における、ファイルの更新時刻からの日数
-A      # perl起動時における、ファイルの参照時刻からの日数
-C      # perl起動時における、ファイルの作成時刻からの日数
```