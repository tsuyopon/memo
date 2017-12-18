Apacheについて

*** 参考URL
	- Apache HTTP Server - wikipedia
	-- http://ja.wikipedia.org/wiki/Apache_HTTP_Server
	- apache v1.3
	-- http://httpd.apache.org/docs/1.3/
	- apache v2.3
	-- http://httpd.apache.org/docs/trunk/ja/sitemap.html


*** Apache起動モードについて

MPM ですが、Apache HTTP サーバではリクエストを処理する部分のことをさします。
MPM は、Apache HTTP サーバ 2.0 系から採用されています。MPMには以下の４種類が存在しているようです。
追記: apache 2.4系からはevent mpmが追加されているようですので５種類となります。


prefork
	Apache HTTPサーバ 1.3系以前のモデルです。
	1つのリクエストに対して1プロセスを割り当てています。
	負荷に応じてプロセスを増減させます。
	PHPで利用する際にはこのモードが推奨されている

worker
	スレッド対応型で、リクエスト処理はスレッドが対応する。
	負荷に応じて子プロセス数を増減させる
	1子プロセス数あたりのスレッド数は固定になっている

perchild
	スレッド対応型で、リクエスト処理はスレッドが対応する。
	負荷に応じてスレッド数を増減させる
	子プロセスの数は固定になっている

winnt
	スレッド対応型
	リクエスト処理は、スレッドが対応する
	Windows NT に特化したスレッドモデル

event
	KeepAlive問題に対応したworker。対応できるのはHTTPだけらしい
	マルチプロセス+マルチスレッドに対応したモデル

(参考)
	MPMについて
		http://unoh.github.io/2008/03/21/apache_mpm.html
	event mpmについて
		http://l-light-note.hatenablog.com/entry/2013/12/01/184352

*** Apacheの歴史

***** Apache1.x系 [#e45a8f4a]
| バージョン | 更新内容 |
| 1.0 | httpdへのpatchあてによる不具合修正や新機能の追加が行われた |
| 1.1 | HTTP/1.1サポート、外部スクリプト起動、その他モジュールの追加 |
| 1.2 | XSSI対応、正規表現でのパス記述、ブラウザ種別をUser-Agentにより取得、mod_rewrite対応 |
| 1.3 | dsoがサポートされた |

***** Apache2.x系 [#gbd3d60b]
- ハイブリッドにプロセスとスレッドを使用できるモードが新しく追加された
-- スレッドをサポートしているシステムでは、マルチプロセス・マルチスレッドのハイブリッドな形での運用が可能
- 新しいビルドシステム機能
-- ソースからのインストール時に、GNU の autoconf とlibtool が必要となりました。これらがないとうまくビルドできないので注意が必要となる。
- マルチプロトコルをサポートした
-- 今後追加モジュール使用することによって、様々なプロトコルを利用することが可能となる
- BeOS、OS/2、Windowsなどの非UNIXプラットフォームのサポート強化
-- 各プラットフォーム固有のＡＰＩを実装しているMPMsやAPRの導入によって、度々バグが発生し機能を低下させていたPOSIX エミュレーション層が削除されたことが大きな要因となっている
- IPv6のサポート
-- デフォルトで、IPv6上での動作が可能となっています。Listen・NameVirtualHost・といったディレクティブで IPv6での設定が可能となっている。
- フィルタリング機能
-- モジュールにフィルタリング機能を持たせることが可能となりました。例えば、mod_includeを使えば CGIの出力をSSIで解析することも可能です。  
- 多言語対応のエラーメッセージ
-- ブラウザへのエラーメッセージはSSIドキュメントを使用して、多言語で提供されています 
- ディレクティブ設定の簡素化
-- Port、BindAddresディレクティブが無くなり、Listenディレクティブだけで設定可能となっています。ServerNameディレクティブはリダイレクトやバーチャルホスト認証のためだけにサーバ名とポート番号を設定します
- Windows における Unicode のサポート
-- Apache2 は WindowsNT 上でのファイル名に関して、utf-8 を使用しています。これらのディレクトリは、Unicodeのファイルシステムに翻訳されます
- モジュールの機能強化
-- デフォルトのモジュールに関しても新しい機能が強化されたり、以前あったモジュールが削除されたりしています

*** Apache ソースコードからのインストール
	$tar zxvf apache_2.0.40.tar.gz
	$cd ./apache_2.0.40
	$./configure --prefix=/usr/local/apache2 --enable-module=so 
	        (ここで指定したモジュールがapxsコマンドでDSO(Dynamic Shared Object)として組み込み可能になる。)
	$make
	$su
	#make install


*** logresolveでアクセスログのIPアドレスの名前解決を行う。 [#o156e86d]
たとえば、access.logに以下の行が存在していたとする。
	 222.7.50.112 - - [18/Sep/2007:01:15:31 +0900] "GET /hello HTTP/1.1" 200 376 "-" "Mozilla/5.0 (Windows; U; Windows NT 5.1; ja; rv:1.8.0.12) Gecko/20070508 Firefox/1.5.0.12" "-"
	 127.0.0.1 - - [18/Sep/2007:01:32:24 +0900] "GET /server-status HTTP/1.0" 404 273 "-" "w3m/0.5.1" "-"

上記のIPアドレスに対して名前解決を行う場合には以下の様にする。
	 $ /usr/sbin/logresolve  /var/log/apache/access.log
	 ZL050112.ppp.dion.ne.jp - - [18/Sep/2007:01:15:31 +0900] "GET /hello HTTP/1.1" 200 376 "-" "Mozilla/5.0 (Windows; U; Windows NT 5.1; ja; rv:1.8.0.12) Gecko/20070508 Firefox/1.5.0.12" "-"
	 localhost - - [18/Sep/2007:01:32:24 +0900] "GET /server-status HTTP/1.0" 404 273 "-" "w3m/0.5.1" "-"

ファイルに出力したい場合には-sオプションが利用できる
	 $ /usr/sbin/logresolve -s outputfile /var/log/apache/access.log


