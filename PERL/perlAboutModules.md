# 概要
perlに存在する各種モジュールの外観(overview)的なもの

# 詳細

## Getopt::Long

### 基本的な使い方
```
use Getopt::Long;

$name1 = "test1";
$name2 = "test2";
GetOptions('name=s' => \$name1, 'name2=s' => \$name2 );
print "$name1\t$name2\n";
```

上記を引数無しで実行すると、下記結果が出力されます。
```
(出力例)
test1   test2
```

## Smart::Comments
Smart::Commentsを利用するとソースコード中に下記コードを埋め込むことにより様々なでバッグ制御を行うことができます。

### 基本的な使い方
```
	 ###
```
このモジュールはデバッグとしての利用のため、useを書かずに、
```
$ perl -MSmart::Comments
```
として実行した方がソースがきれいになります。

## File::Basename
File::Basenameは、ファイルのベース名を取りだす場合に利用するモジュールです。

### 基本的な使い方
```
use File::Basename;
my $name = "/usr/local/bin/perl";
my $basename = basename $name;
```

これは$basenameとしてperlが返却されます。

## File::Basename
File::Copyは、ファイルをコピーしたり、移動したい場合に利用するモジュールです。 以下の２つの関数を提供します。
```
move()
copy()
```

### 基本的な使い方
```
use File::Copy;
copy("source","destination") or die "Can't copy 'source' to 'destination': $!";
move("oldname","newname") or die "Can't change name: $!";
```

## Sts::Hostname
Sts::Hostnameは、マシンのhostnameを知りたい場合に利用するモジュールです。
### 基本的な使い方
```
use Sys::Hostname;
my $host = hostname;
print "This machine name = '$host'.\n";
```

## Cwd
Cwdは、カレントディレクトリが知りたい場合に利用するモジュールです。
###  基本的な使い方
```
use Cwd;
my $directory = cwd;
```

## Net::Ping
### 基本的な使い方 
```
use Net::ping;
$timeout_sec = 10;  # タイムアウトの指定
$proto = 'icmp';    #icmp,tcp,udpの指定が可能
$ping = new Net::Ping($proto,$timeout_sec);
$result = $ping->('localhost');
if($ping){ 
	print "localhost alive\n";
}
$ping->close;
undef($ping);
```

## GD::Graph
GD::Graphモジュールはデータを素早く簡単にGraphicalに表現するPerl5モジュールです。
GD::Graphを利用する為には以下のパッケージが必要となります。
```
<必要なパッケージ>        
GD Graphics Library       線や多角形、円を描画するためのライブラリ
PNG graphics library      PNGグラフィックスフォーマット用ライブラリ
zlib compression library  zlib汎用圧縮ライブラリ
Free Type                 TrueTypeフォントをレンダリングするライブラリ
JPEG library              JPEGグラフィックスフォーマット用ライブラリ
GD Perl Module            GDライブラリをPerlで利用可能にするモジュール
GD::Text(GDTextUtil)      GDを利用してテキストを扱えるようにするモジュール
GD::Graph(GDGraph)        GDを利用してグラフを扱えるようにするモジュール
Jcode                     日本語文字コードを変換するモジュール
```

GD::Graphには以下のサブクラスが存在します。
```
GD::Graph::Colour         GD::Graphで使われる色操作ルーチン
GD::Graph::FAQ            よく聞かれる質問
GD::Graph::Data           GD::Graphのためのデータセットのカプセル化
GD::Graph::Error          GD::Graphクラスのためのエラーハンドリング
```

実際に表現できるグラフは以下の通りです。
```
GD::Graph::lines          折線グラフ
GD::Graph::bars           棒グラフ
GD::Graph::points         点グラフ
GD::Graph::linespoints    点付き折線グラフ
GD::Graph::area           面グラフ
GD::Graph::mixed          上記のグラフを組み合わせたグラフ
GD::Graph::pie            円グラフ
```

## Graph::Easy
Graph Easyは、データ形式のハコ図を作成したりすることができます。

以下の２つの機能を提供します。
- (1) コマンドとしての機能(入力はコマンドラインから)
  - /usr/bin/graph-easyというコマンドがあります。
- (2) Perlモジュールとしての機能
  - Graph::Easyとしての機能を提供します。

Graphvizと連携することも可能で、以下のデータを生成することができます。

### graph-easyコマンドについて
- 例1: 基本的な例
```
$ echo "[server1] -- Ethernet --> [ server2 ]" | graph-easy
+---------+  Ethernet   +---------+
| server1 | ----------> | server2 |
+---------+             +---------+
```

- 例2: 下矢印が含まれる場合の例 [#d979720f]
```
$ cat data.txt
[ Server1 ] == Cat5 Cable ==> [ Gateway ]
[ Gateway ] == Cat5 Cable ==>  [ Server2 ] { origin: Gateway; offset: 2,0; }
[ Gateway ] -- cable router-\>Gateway --> [ Special\nRouter ]
                                         { origin: Gateway; offset: 0,2; }
$ graph-easy < data.txt
+---------+  Cat5 Cable   +------------------------+  Cat5 Cable   +---------+
| Server1 | ============> |        Gateway         | ============> | Server2 |
+---------+               +------------------------+               +---------+
                            |
                            | cable router->Gateway
                            v
                          +------------------------+
                          |        Special         |
                          |         Router         |
                          +------------------------+
```

### 基本的な使い方 
```
$ cat prog.pl
#!/usr/bin/perl
use strict;
use warnings;
use utf8;
use Graph::Easy;

my $graph = Graph::Easy->new();
$graph->add_edge_once ('AAA', 'BBB');
$graph->add_edge_once ('test', 'test2');
$graph->add_edge_once ('BBB', 'test2');
print $graph->as_ascii();
#print $graph->as_svg();
```

上記プログラムを実行すると下記の結果が得られます。
```
$ perl prog.pl
+-----+     +-----+     +-------+     +------+
| AAA | --> | BBB | --> | test2 | <-- | test |
+-----+     +-----+     +-------+     +------+
```

## 基本的なモジュールメモ
覚えておいたほうがよさそうなモジュールメモ
```
DB_File
    DBMファイルを作成、使用する、空にする等
GDBM_File
    異なるDBMファイルに変換する
MLDBM
    永続的なデータを維持できるようにする
DBIx::Dump
    問い合わせ結果をExcelやCSVへ保存する
DBI
    RDBへの問い合わせを行う
DBD::CSV
    CSVファイルをSQLで問い合わせる
DBD::SQLite
	データベースサーバ無しでSQLを使用する
Getopt::Std
	1文字だけのオプションを解析する
Getopt::Long
	名前付き引数(--helpなど)を解析する
POSIX::Termios
	端末の出力速度を取得する
	端末の特性を直接設定する
POSIX
	値の切捨て(floor), 値の切り上げ(ceil)を行います
	日付の書式設定(strftime)
Date::Simple
	日付の妥当性チェックを行います。日付の差分を求める。
	前日、翌日の日付を取得します。曜日の取得を行います
Date::Range
	日付がある範囲内に存在するかどうかをチェックします
Math::Round
	四捨五入を行います
Math::Trig
	sin,cos,tanの値、円周率の値を取得します
Math::BigInt
	大きい数の演算を行います。最大公約数の取得を行います
Math::Stat
	中央値の取得を行います
Math::Complex
	複素数を利用します
Math::Matrix
	行列の計算を行います
Math::Fibonacci
	フィボナッチ数列の取得を行います
Math::BaseCalc
	N進数変換を行います
Statistics::Lite
	平均値の取得を行います。最大値や最小値の取得も行います
	最大値と最小値の差(範囲)を取得できます。合計値の取得を行います。中央値の取得を行います
List::Util
	最大値、最小値の取得を行います。合計値の取得を行います。
	配列のシャッフルを行います。
List::MoreUtils
	重複値の削除を行います
Array::Uniq
	重複値の削除を行います
Term::Cap
	適切な文字シーケンスを送信する
	端末のビープ音の制御をする
Term::ReadKey
	端末やウィンドウのサイズを判定する
	キーボードから1文字を読み取る
	パスワードを読み取る
	待機状態の入力を検査する
Term::ANSIColor
	テキストの色を変更する
Term::ReadLine
	ユーザーからの入力行をユーザ自身で編集できるようにする
Curses
	画面を制御する
Expect
	インタラクティブな処理の自動化(10秒間にパスワードが入力されないとエラー等)の処理を行う
Tk
	GUIの画面の作成処理を行う
Tk::DialogBox
	Tkでダイアログボックスを作成する
Carp::Confess
	スタックトレース付きのエラーを発生することができる
Devel::Trace
	トレース表示を行う
Devel::Size
	変数が利用しているメモリサイズの取得
Devel::DProf
	プロファイラを利用する
Readonly
	定数を利用する(use constantでも可能)
Time::HiRes
	1秒未満のsleepを行う(select undef, undef, undef, 0.5;  でも可能)
Class::Struct
	構造体の定義を行う
Switch
	switch文を利用する
Win32::OLE
	Excelを操作する(EXCELがインストールされている必要あり)
	iTunesの今聞いている曲の取得、再生と停止、トラック移動、曲一覧の取得等を行う
	Internet Explorerの履歴情報取得を行う
Win32::SystemInfo
	CPU、メモリ情報の取得を行います
Win32::Registry
	レジストリの値を取得します
Win32::Clipboard
	クリップボードを利用します
Win32::EventLog
	イベントログにメッセージを出力する
Perl::Tidy
	perlのソースコードを整形してくれる
Crypt::CBC
	暗号化を行う
Crypt::SSLeay
	httpsで始まるwebページを取得する。LWPで利用するURLが自動的にhttpsになる
Storable
	配列やハッシュの値を保存する場合に利用する
Text::Tabs
	タブとスペースの相互変換を行います
Text::Highlight
	ソースコードのハイライト表示を行います
Text::ASCIITable
	配列のデータをデータを表形式で出力することができます
Text::Template
	HTMLのテンプレート作成に便利(らしい)
JSON
	JSONデータの作成を行います
MP3::Info
	MP3情報の取得を行います
Image::MetaData::JPEG
	JPEGファイルの情報取得を行います
	JPEGファイルの撮影日時取得を行います
	JPEGファイルの生成機器取得を行います
Number::Phone::JP
	日本での電話番号の妥当性の確認を行います
Acme::Comment type => 'C++';
	/* --- */ もコメントの一部になります
File::Spec
	ファイルの絶対パス名を取得します
File::Copy
	ファイルのコピーを行います。ファイルの移動を行います。
File::Basename
	ベース名の取得を行います。ベース以外の部分(ディレクトリの取得)にも利用できます。
File::Path
	再帰的にディレクトリの作成を行います。再帰的なディレクトリの削除を行います。
File::HomeDir
	ホームディレクトリの取得を行います
File::Remove
	*や?のワイルドカードを使ってファイルを削除する
File::Find
	ディレクトリを再帰的にたどることができます
File::Compare
	2つのファイルが同じものであるかどうかの比較を行うことができます
Archive::Tar
	tarファイルの一覧を取得、展開、作成を行います
Archive::Zip
	zipファイルの一覧を取得、展開、作成を行います
FindBin
	スクリプトパスの取得を行います
Digest::MD5
	MD5の取得を行います
Digest::MD5::Reverse
	MD5から元の文字列の取得を行います
Digest::SHA1
	SHA-1の取得を行います
Digest::SHA
	SHA-2の取得を行います
Algorithm::Diff
	文章の差分の取得を行います
Data::UUID
	UUID(Universally Unique IDentifier)の取得を行います
String::Rondom
	ランダムな文字列の取得を行います
Module::CoreList
	標準でインストールされているモジュールの一覧を表示する
Pod::HtmlEasy
	PODをHTMLに変換する
Benchmark
	ベンチマークの取得を行います
Sys::Hostname
	ホスト名の取得を行います
Sys::Syslog
	syslogにメッセージを出力する
Parse:Syslog
	syslogファイルをパースする
English
	OS名前を$OSNAMEにより取得する
Jcode
	日本語へのエンコードを行います
HTML::Rainbow
	虹色文字列の出力を行います
HTML::LinkExtor
	HTMLファイルから全てのURLを抽出を行う
HTML::Parser
	HTMLのパース処理を行います
HTML::TokeParser
	HTMLを細かい要素にまでパース処理を行います
HTML::Entities
	HTMLのエンコード、デコード処理を行います
HTML::TableContentParser
	HTMLテーブル内のデータをPerlのデータ構造に変換したい
HTML::Mason
	テンプレートの作成を行う
Apache::Constants

Apache::Cookie
	レスポンスの一部としてcookieをクライアントに送りたい。
	クライアントから取得したクッキーの値にアクセスしたい。
Apache
	リダイレクト処理を行いたい
	ヘッダを調べたい
Apache::Request
	特定のパラメータにアクセスしたい。
	アップロードファイルを受信したい。
Apache::DBI
	データベース接続を透過的にキャッシュする(DBIよりも先にApache::DBIをロードする)
Apache::Table
	ハンドラ間で情報を共有する
Apache::Reload
Apache::StatINC
Apache::Timeit
	コンテンツハンドラの実行時間を計測する
Encode::Guess
	文字コードの推測を行います
Calendar::Simple
	カレンダーの表示を行います
Cwd
	カレントディレクトリの取得を行います
Lingua::JA::Numbers
	漢数字変換を行います
Lingua::EN::Numbers
	数字から英語にする
Lingua::EN::Words2Nums
	英語から数字にする
Lingua::JA::Hepburn::Passport
	ヘボン式ローマ字への変換を行います
MIME::Base64
	Base64のエンコード デーコードを行う
MIME::Lite
	添付ファイル付きのメールを送信する
MIME::Parser
	メールから添付ファイルの取り出しを行う
Business::ISBN
	ISBNの10桁13桁変換
Regexp::Assemble
	与えた文字列にマッチする正規表現を作成することができる
Config::Simple
	設定ファイルを読み込みを行います
CGI
	CGIパラメータ一覧を見やすい形で取得する(Dumpメソッド)。
	CGIのデータ量制限を行う。CGIのURLを取得する。別ページにリダイレクトさせる。
CGI::Carp
	CGIのデバッグを行います
URI
	リンク先を絶対パスで取得する。
	クエリ付きURIの作成する。
URI::Escape
	URIのエスケープを行う
URI::URL
	
URI::Heuristic
	
LWP
	HTTPヘッダの取得を行います
LWP::Simple
	WEBページの取得を行います
LWP::RobotUA
	自分自身でWEBを自動的に巡回するロボットを作成する
HTTP::Date
	HTTPで使用する形式の日時を取得できます
HTTP::Async
	HTTPリクエストを並列に実行します
HTTP::Request
	WEBページの取得を行います。
	BASIC認証しているページの取得を行います。
HTTP::BrowserDetect
	ブラウザ情報の取得を行います
HTTP::Parser
	Aタグのhrefの値を取得します
HTTP::Daemon
	仮のWEBサーバデーモン(HTTPのデバッグなどに利用)を記述できる
HTTP::Cookie
	Cookieを扱います
HTTP::Response
	
Parallel::ForkManager
	処理を並列に実行します
NetAddr::IP
	ネットワーク内の先頭アドレスの取得します。 ネットワーク内の末尾アドレスの取得します。
	ネットワークアドレスの取得を行います。 アドレス範囲の取得を行います。
	ブロードキャストアドレスの取得を行います。
WWW::Mixi
	mixiにアクセスする
WWW::Mechanize
	フォーム情報の取得を行います
Net::SMTP
	メールの送信を行います
Net::Ping
	マシンへのPingを行います
Net::Amazon
	Amazonから情報を取得します
Net::FTP
	FTPによるファイル転送、ファイルの取得を行います
Net::Telnet
	TELNETによるコマンド実行を行います
Net::DNS
	DNSレコードの取得を行います
Net::NNTP
	Usenetニュースサーバへの接続を行いメッセージの投稿および読み取りを行う
Net::POP3
	POP3でメールを読み取りを行う
Net::LDAP
	LDAPサーバへの接続を行います
IP::Country::Fast
	IPアドレスやドメインがどの国のものであるかを調べる
XML::RSS
	RSSをパースする
XML::Simple
	XMLのデータ構造を解析する。XMLの作成を行います。
XML::LibXML
	DOMを利用してXMLファイルのパースツリーにアクセスし、必要に応じて変更を加える
XML::SAX
	XMLパーサからSAXイベントを取得する
XML::Twig
	利用可能なメモリ量よりも大きなファイルを処理する
XMLRPC::Transport
	XML-RPCサーバを記述する
XMLRPC::Lite
	XML-RPCクライアントを記述する
SOAP::Transport
	SOAPサーバを記述する
SOAP::Lite
	SOAPクライアントを記述する
Smart::Comments
	###をコメントとして認識させ、変数や配列の出力、プログレスバーの出力を行う
Data::Dumper
	定数の内容を出力する(変数のキーのソートも可能)
Image::Magick
	画像の読み込み、リサイズ、書き出しを行います
GD::Image
	画像にテキストを追加する
GD::Graph
	データをグラフ化する
IPC::Open2
	別のプログラムに対して書き込みと読み取りを同時に行い、制御する
IPC::Open3
	コマンドの入力、出力、およびエラーの書くストリーム処理を完全に制御する
IO::Select
	どのファイルハンドルから読み取りを行うことができるか判断させる
IO::Socket
	ソケット通信を行います
IO::Handle
	
IO::Multiplex
	複数の入力ストリームを管理したい
Socket
	IO::Socketよりも更に低レベルでの定義を行ったソケット通信ができます
Fcntl
Tie::RefHash
threads
	OSのスレッドを利用して1つのプロセスの中から複数のクライアントを処理するサーバのコードを書きたい
POE::Component
	Perl5.8のスレッドや複雑な非ブロック型I/Oを使用せずに、1つのプロセスの中から複数のクライアントを処理するサーバのコードを書きたい
Mail::Mailer
	メールの送信を行います
Logfile::Apache
	apacheサーバのログを処理する
```
