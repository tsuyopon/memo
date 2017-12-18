
*** Apacheモジュール概要
core以外のモジュールについて
    IPアドレスやネットワーク、ドメインによりアクセス制限を行う
        mod_access
    ログのカスタマイズを行う
        mod_log_config
    Basic認証、Digest認証を利用する
        mod_auth
    WebDAVを利用する
        mod_dav
    rewriteを実現したい
        mod_rewrite
    各ユーザでpublic_htmlとしてウェブページを実現したい
        mod_userdir
    エイリアスを設定する
        mod_alias
    拡張子と関連ファイル付けを行う
        mod_mime
    perlを利用してapacheハンドラを作成する
        mod_perl
    SSLを使用したい場合
        mod_ssl

##################################################################
mod_core
##################################################################
* 概要 [#pbd41e03]
mod_core関連についてまとめます。

* 詳細 [#k64b3b72]
*** エラーログのレベルを変更したい。 [#k3e9d9fa]
LogLevelのデフォルト値がwarnとなっている。
	 LogLevel warn

以下のレベルが指定できる。
	 emerg       緊急事態で、Webサーバを使用できない状態
	 alert       直ちに処置が必要
	 crit        致命的な状態
	 error       エラー状態
	 warn        警告
	 notice      正常だが重要な情報
	 info        追加情報
	 debug       デバッグレベルのメッセージ

*** httpd.conf以外にもローカル設定ファイルの場所を定義したい。 [#d4f22ad2]
Includeを利用すればよい。
例えば、以下の様にhttpd.confを記述すると、/etc/apache/conf.d
ディレクトリ以下のファイルがapacheの再起動時に読み込まれることになる。
	 Include /etc/apache/conf.d

*** Apacheでsyslogを利用したい。 [#cab6e44b]
以下の1行を追記すればいい。
	 Errorlog syslog

*** LocationディレクティブとDirectoryディレクティブの違い [#j3f5a906]
 Directory: 指定のファイルシステムのディレクトリとサブディレクトリとのみに 適用されるディレクティブを囲む
 Location:  ファイルシステム外のコンテンツにディレクティブを適用するときに 使用してください

*** IPアドレスが1つのWebサーバで、1台のシステム上で複数のドメインをサポートしたい。 [#b6599174]
例えば、以下の様にhttpd.confに記述するとします。
	 ServerName  127.0.0.1
	 NameVirtualHost *
	 <VirtualHost *>
	     ServerName 192.168.1.9
	     DocumentRoot /var/www/html
	 </VirtualHost> 
	 
	 <VirtualHost *>
	     ServerName test.itbdns.com
	     DocumentRoot /var/www/html/secret-digest/it
	 </VirtualHost>
上記は、192.168.1.9でアクセスが来た場合には/var/www/htmlをドキュメントルートとし、test.itbdn.comでアクセスが来た場合には/var/www/html/secret-digest/itをドキュメントルートとしています。
VirtualHost後の*は正規表現ではないということを覚えておいてください。

*** 1台のシステムに複数のIPアドレスが割り当てられていて、各IPアドレスでWebサイトをサポートしたい場合 [#xdeebb77]
例えば、以下の様にhttpd.confに記述するとします。
	 ServerName  127.0.0.1
	 <VirtualHost 192.168.1.9>
	     ServerName part1.itbdns.com
	     DocumentRoot /var/www/html_1
	 </VirtualHost>
	 
	 <VirtualHost 192.168.1.10>
	     ServerName part2.itbdns.com
	     DocumentRoot /var/www/html_2
	 </VirtualHost>
上記は、192.168.1.9のIPアドレスに対してアクセスが来て、part1.itbdns.comというアクセスで来ているのであれば/var/www/html_1をドキュメントルートとする設定である。
また、192.168.1.10のIPアドレスに対してアクセスが来て、part2.itbdns.comというアクセスで来ているのであれば/var/www/html_2をドキュメントルートとする設定である。

*** どのアドレスベースのバーチャルホストにもマップできないリクエストを処理したい [#p600cc13]
	 ServerName  127.0.0.1
	 <VirtualHost 192.168.1.9>
	     ServerName part1.itbdns.com
	     DocumentRoot /var/www/html_1
	 </VirtualHost>
	 
	 <VirtualHost 192.168.1.10>
	     ServerName part2.itbdns.com
	     DocumentRoot /var/www/html_2
	 </VirtualHost>
	 
	 <VirtualHost _default_>
	     DocumentRoot /var/www/html_3
	 </VirtualHost>
_default_に対してはバーチャルホストとして設定されていない「アドレス：ポート」宛の全てのリクエストを受け付ける
例えば、443ポートに対しての全てのマッピングできなかったものを処理したい場合には
	 <VirtualHost _default_:443>
とすればよい。

*** VirtualHostで設定したServerNameドメイン以外のドメインでもアクセスしたい [#w83f2e64]
VirtualHostで設定したドメインでアクセスしないと、VirtualHost内部で
設定を行った内容が反映されないことがあります。
そのような場合には、ServerAliasを利用します。
	 <VirtualHost 192.168.1.200>
	    ServerName  production.co.jp
	    ServerAlias test.co.jp
	    DocumentRoot /var/www/html_2
	 </VirtualHost>

* 参考URL [#z627ca66]
- apache v2.0 mod_core
-- http://httpd.apache.org/docs/2.0/ja/mod/core.html



##################################################################
SSIについて
##################################################################

* 概要 [#z42b74fa]
httpd.confでSSIを使うと定義する必要があります。(INCLUDEが定義されていればよい)
以下に特徴を記します。
- shtmlというファイル名を持ちます。
- 環境変数やファイル情報などの様々なデータを挿入することが可能になります
- すべてのファイルに同じヘッダやフッタを表示することが容易になります
- ファイルの最終更新時刻やサイズを自動的に表示できるようになります
- カウンタを容易に作れます

尚、SSIには以下のデメリットも存在することを覚えておいてください。
- パフォーマンスが下がる
- セキュリティが弱まる

SSIを利用する倍、Apacheの設定は下記記述がhttpd.confか.htaccessに記載されている必要があります。
 AddType text/x-server-parsed-html .shtml
 Options Includes

* 詳細 [#we30fefe]
*** 拡張子がhtmlでもSSIを利用したい [#r46aabae]
SSIは通常shtmlという拡張子になります。
ですが、htmlでもこれを利用したい場合にはconfに以下のAddType設定を追加します。
 AddType text/x-server-parsed-html .shtml .html

*** SSIページで利用できる追加変数 [#j74d26b0]
一般的にperlで%ENVで出力可能なものの他にも利用可能な追加変数を以下に挙げる。
 DOCUMENT_NAME           現在のファイル名
 DOCUMENT_URI            ファイルへの仮想パス
 QUERY_STRING_UNESCAPED  シェルでのメタ文字が全て"\"でエスケープシーケンスされ
                         たデコードされた文字列
 DATE_LOCAL              ローカルタイムゾーンでの現在日時 
 DATE_GMT                GMTでの現在日時
 LAST_MODIFIED           ブラウザがリクエストしたファイルの最終更新日時

*** 環境変数を出力 [#s53b0428]
 <!--#echo var="LAST_MODIFIED" -->

また、環境変数一覧を表示させるには以下の様にします。
 <!--#printenv -->

*** 変数に値を格納する [#h9acfe02]
以下の例ではmsgという変数に値を格納して、それを出力させる例です。
 <!--#set var="msg" value="Hello!!" -->
 <!--#echo var="msg" -->

*** 最終更新時刻を表示させる。 [#a7f3f6c9]
 <!--#config timefmt="%Y/%m/%d %X" -->     <=　時刻表示形式を指定できる
 <!--#echo var="LAST_MODIFIED" -->

*** ファイルの読み込み処理を行う [#madf284c]
 <!--#include file="header.html" -->

*** ファイルサイズを表示させる [#nd7918f2]
 <!--#config sizefmt="abbrev" -->
 <a href="xxx.zip">ダウンロード</a>（サイズ：<!--#fsize file="xxx.zip" -->）

*** コマンドを実行する [#g6ff8440]
実際のUNIXコマンドおよびcgiコマンドを実行させる例になります。
CGIの時にはパラメータ(?以降)は渡すことができないので注意が必要です。
 <!--#exec cmd="/bin/ls" -->
 <!--#exec cgi="./cgi-bin/test.cgi" -->

*** エラーメッセージを指定する [#n2b4d5ea]
文書処理中にエラーが発生した場合のメッセージを指定できる。これはエラーログにも記載されます。
 <!--#config errmsg="〜" -->

*** 制御構文を利用する [#b8468833]
 <!--#if expr="〜" -->
 <!--#elif expr="〜" -->
 <!--#else -->
 <!--#endif -->


* 参考URL [#z75d04ae]
- とほほのSSI入門
-- http://www.tohoho-web.com/wwwssi.htm
- Apache チュートリアル: Server Side Includes 入門
-- http://httpd.apache.org/docs/2.0/ja/howto/ssi.html


##################################################################
mod_access
##################################################################
* mod_accessとは [#wc1975c1]
IPアドレス、ネットワーク、ドメインにより制限をかけることができます。
mod_accessの各ディレクティブは以下に対して記述することができます。
- <Directory> 
- <Location> 
- <Files> 
- .htaccess 

* 技術詳細 [#f21a5401]
*** 基本アクセス許可する [#m29662de]
	 Order Deny,Allow
全ての接続をDenyしてから、全ての接続をAllowしますので全許可となります。

*** 基本アクセス拒否する [#p697c653]
	 Order Allow,Deny
全ての接続をAllowしてから、全ての接続をDenyしますので全許可となります。

*** 192.168.0.1のIPと、192.168.10.0/24, 172.10, test.co.jpのネットワーク以外全ての接続を許可 [#yb42dda5]
	 Order Deny,Allow
	 deny from 192.168.0.1
	 deny from 192.168.10.0/24
	 deny from 172.10
	 deny from test.co.jp
尚、/24の行は以下のサブネットマスク記載でも問題ありません。
	 deny from 192.168.10.0/255.255.255.0

* 参考URL [#x78d4149]
- Apache2.0
-- http://httpd.apache.org/docs/2.0/ja/mod/mod_access.html

##################################################################
mod_log_config
##################################################################
*** LogFormatでログをカスタマイズしたい [#kc7a5500]
mod_log_configを利用していますので、このページを見ると一番早いです。
	 フォーマット文字列 説明 
	 %% パーセント記号 (Apache 2.0.44 以降) 
	 %...a           リモート IP アドレス 
	 %...A           ローカル IP アドレス 
	 %...B           HTTP ヘッダ以外の送られたバイト数 
	 %...b           HTTP ヘッダ以外の送られたバイト数。CLF 書式。 すなわち、1 バイトも送られなかったときは 0 ではなく、 '-' になる 
	 %...{Foobar}C   サーバに送られたリクエスト中のクッキー Foobar の値 
	 %...D           リクエストを処理するのにかかった時間、ミリ秒単位 
	 %...{FOOBAR}e   環境変数 FOOBAR の内容 
	 %...f           ファイル名 
	 %...h           リモートホスト 
	 %...H           リクエストプロトコル 
	 %...{Foobar}i   サーバに送られたリクエストの Foobar: ヘッダの内容 
	 %...l           (identd からもし提供されていれば) リモートログ名。 これは IdentityCheck ディレクティブが On に設定されていない限り、 - になります。 
	 %...m           リクエストメソッド 
	 %...{Foobar}n   他のモジュールからのメモ Foobar の内容 
	 %...{Foobar}o   応答の Foobar: ヘッダの内容 
	 %...p           リクエストを扱っているサーバの正式なポート 
	 %...P           リクエストを扱った子プロセスのプロセス ID 
	 %...{format}P   リクエストを扱ったワーカーのプロセス ID かスレッド ID。 format として有効な値は pid と tid (Apache 2.0.46 以降)  
	 %...q           問い合せ文字列 (存在する場合は前に ? が追加される。 そうでない場合は空文字列) 
	 %...r           リクエストの最初の行 
	 %...s           ステータス。内部でリダイレクトされたリクエストは、元々の リクエストのステータス --- 最後のステータスは  %...>s  
	 %...t           時刻。CLF の時刻の書式 (標準の英語の書式) 
	 %...{format}t   format で与えられた書式による時刻。format は strftime (3) の 書式である必要がある。(地域化されている可能性がある) 
	 %...T           リクエストを扱うのにかかった時間、秒単位 
	 %...u           リモートユーザ (認証によるもの。ステータス (%s) が 401 のときは意味がないものである可能性がある)  
	 %...U           リクエストされた URL パス。クエリ文字列は含まない 
	 %...v           リクエストを扱っているサーバの正式な ServerName 
	 %...V           UseCanonicalName の設定によるサーバ名 
	 %...X           応答が完了したときの接続ステータス: 
	                 X = 応答が完了する前に接続が異常終了 
	                 + = 応答が送られた後に接続を持続することが可能 
	                 - =  応答が送られた後に接続が切られる 
	    (このディレクティブは Apache 1.3 の後期のバージョンでは %...c に割り当てられて いましたが、これは歴史的に ssl が使用している %...{var}c 構文と衝突していました。)
	 %...I           リクエストとヘッダを含む、受け取ったバイト数。 0 にはならない。 これを使用するためには mod_logio が必要 
	 %...O           ヘッダを含む、送信したバイト数。0 にはならない。 これを使用するためには mod_logio が必要

*** accessログをカスタマイズする [#v6b7ab12]
httpd.confには以下の様な複数の記述がある。
	 LogFormat "%h %l %u %t \"%r\" %>s %b \"%{Referer}i\" \"%{User-Agent}i\" \"%{forensic-id}n\" %T %v" full
	 LogFormat "%h %l %u %t \"%r\" %>s %b \"%{Referer}i\" \"%{User-Agent}i\" \"%{forensic-id}n\" %P %T" debug
	 LogFormat "%h %l %u %t \"%r\" %>s %b \"%{Referer}i\" \"%{User-Agent}i\" \"%{forensic-id}n\"" combined
	 LogFormat "%h %l %u %t \"%r\" %>s %b" common

また、上記の設定値を呼び出すことによって以下の様にして呼び出すことができる。
ログとして記述したいフォーマットを選びCustomLogを記述すればよい
CustomLogは複数行あっても問題なく、ログに複数のログが1リクエストで記述されることになる。

	 CustomLog /var/log/apache/access1.log combined
	 CustomLog /var/log/apache/access1.log common
	 CustomLog /var/log/apache/access1.log full
	 CustomLog /var/log/apache/access1.log debug

	 [full]
	 222.7.50.112 - - [29/Sep/2007:06:06:03 +0900] "GET / HTTP/1.1" 200 122 "-" "Mozilla/4.0 (compatible; MSIE 6.0; Windows NT 5.1; .NET CLR 1.1.4322)" "-" 0 test@test.itbdns.com
	 
	 [debug]
	 222.7.50.112 - - [29/Sep/2007:06:06:32 +0900] "GET / HTTP/1.1" 200 122 "-" "Mozilla/4.0 (compatible; MSIE 6.0; Windows NT 5.1; .NET CLR 1.1.4322)" "-" 6473 0
	 
	 [combined]
	 222.7.50.112 - - [29/Sep/2007:06:02:36 +0900] "GET / HTTP/1.1" 200 122 "-" "Mozilla/4.0 (compatible; MSIE 6.0; Windows NT 5.1; .NET CLR 1.1.4322)" "-"
	 
	 [common]
	 222.7.50.112 - - [29/Sep/2007:06:04:10 +0900] "GET / HTTP/1.1" 200 122

*** 日、または時間ごとにログファイルを循環したい [#q84d7406]
	 /usr/sbin/rotatelogs
プログラムを利用すればよい。
httpd.confに以下の1行を加えればよい。
	 CustomLog "| /usr/sbin/rotatelogs /var/log/apache/access_log.%Y-%m-%d 86400" combined

*** 各バーチャルホストごとに別々のログファイルに記録したい [#a5f5faa9]
	 split-logfile
プログラムを利用すればよい。
httpd.confに以下の様に記述する。
	 CustomLog "| /usr/sbin/split-logfile /var/log/apache" combined

*** accessログでIPアドレスではなく、ホスト名を記録したい [#gb5a1f8e]
デフォルトではおそらく
    HostnameLookups Off
となっているのでこれを以下に変更する。
    HostnameLookups On
これによりログが以下の様に変更される
	 (変更前) 222.7.50.112 - - [29/Sep/2007:17:00:46 +0900]
	 (変更後) test.itbdns.com - - [29/Sep/2007:17:00:46 +0900]

*** POSTで送られてきたデータをログに記録したい [#f50f844a]
- apache1.3では、POST処理モジュールで明示的にデータを記録しない限り不可である。
- apache2.0では、入力フィルタの機能を介してPOST方式を記録でるが、現在そのようなフィルタは存在しない

* 参考URL [#i3b4aa13]
- ApacheV2.0 モジュール mod_log_config
-- http://httpd.apache.org/docs/2.0/ja/mod/mod_log_config.html


##################################################################
mod_auth
##################################################################
*** Basic認証を行うpart1。(暗号化を行わない認証) [#v8a6a920]
認証をかけるディレクトリを/var/www/html/secretとする。
	 #mkdir -p /var/www/html/secret
次にパスワードのデータベースを作成する。これにはhtpasswdコマンドを使用する。
今回、認証をかけるパスワードデータベースを/etc/httpd/.htpasswdとする。
このパスワードデータベースを新規作成する場合には
	 #htpasswd -c /etc/httpd/.htpasswd tsuyoshi
	 New password:
	 Re-type new password:
	 Adding password for user secret
また、追加作成をする場合には-cオプションを付加しない。
	 #htpasswd -c /etc/httpd/.htpasswd yuuta
 ※.htpasswdは644である必要がある。

次に、以下の様にしてhttpd.confに以下のディレクティブを追加する。
	   AuthType Basic
	   AuthName "Enter your password underline!!"
	   AuthUserFile /etc/httpd/.htpasswd
	   AuthGroupFile /dev/null
	   Require valid-user   (<=ここにユーザー指定するにはRequire user yuutaの様に書く)

設定ファイルに追加した後はApacheを再起動してあげればよい。

*** Basic認証を行うpart2。(暗号化を行わない認証) [#c52a6ab5]
httpd.confにあるディレクティブがあれば、認証を行なうディレクトリに.htaccessファイルを置くだけで済む方法を紹介する。
以下のディレクティブがhttpd.confに書かれている事を確認する。

	 AccessFileName .htaccess 
	  
	 Order allow,deny
	 Deny from all

↑上記の他にも勿論、アクセスコントロールをしたいディレクトリの〜
が必要である。
次にBasic認証を行ないたいディレクトリに置く.htaccessファイルをに記載の内容を以下に示します。
下記の設定が記されたファイルは、/home/tsuyoshi/public_htmlに置くと仮定します。
	 AuthType Basic
	 AuthName "Password Verify"
	 AuthUserFile /home/tsuyoshi/public_html/.htpasswd
	 require valid-user

あとは/home/tsuyoshi/public_htmlに.htpasswdを作っておく必要がある[par1参照]
また、httpd.confは変更したらhttpdを再起動するが.htaccessは再起動する必要がない。

*** Digest認証を行う。 [#d82ee43a]
認証をかけるディレクトリを/var/www/html/secret-digestとする。
	 #mkdir -p /var/www/html/secret-digest
次にパスワードのデータベースを作成する。これにはhtdigestコマンドを使用する。
認証をかけるパスワードのデータベースを/etc/httpd/.htdigestとする。

新規作成の場合には
	 #htdigest -c /etc/httpd/.htdigest 'server.phys.test.ac.jp' tsuyoshi
	 Adding password for secret in realm Secret Zone.
	 New password:
	 Re-type new password:
上記でBasic認証とは違いserver.phys.test.ac.jpを指定したが、これはhttpd.confでのAuthNameで指定した文字と同じものでなければならない。

追加作成の場合には次のように-cオプションを付加しない。
	 #htdigest /etc/httpd/.htdigest 'server.phys.aoyama.ac.jp' yuuta

次にhttpd.confに以下のディレクティブを追加する。

	 AuthType Digest
	 AuthName "server.phys.test.ac.jp"
	 AuthDigestDomain /secret-digest/
	 AuthDigestFile /etc/httpd/.htdigest
	 Require valid-user

あとはhttpdを再起動してあげればよい。



##################################################################
mod_dav
##################################################################

*** WebDAVでSSLとBasic認証を使用する。 [#ldc44c1a]
Basic認証の基本は上記を見て欲しい。
すでに/etc/httpdディレクトリに.htpasswdファイルが作成されているものとします。
httpd.confに以下の設定を追加すればよい。
	 Alias /webdav/ "/var/www/html/webdav/"
	 
	   DAV on
	   SSLRequireSSL
	   AuthType        Basic
	   AuthName        "My Server's webDAV"
	   AuthUserFile    "/etc/httpd/.htpasswd"
	   Require valid-user

上記の設定を加えたらApacheを再起動すればよい。
windowsではネットワークプレイスの追加でDAVサーバーを加えることができる。

もしもできない場合は以下のApacheディレクティブがあることを確認します。
	 Addmodule mod_dav.c
	 Addmodule mod_dav_fs.c
	 DAVLockDB /var/lib/dav/lockdb


##################################################################
mod_rewrite
##################################################################

*** 動的ページを静的ページに見せる [#qb6670a8]
以下の様な方法で静的ページと見せかけることができます。
以下では.cgi&〜で始まっているような場合に利用することが可能です。
このようにすると検索サイトのロボットに引っかかりやすいそうです。
	 RewriteEngine on
	 RewriteRule ^/cgi-bin/sample/([0-9A-Za-z]+)/([0-9A-Za-z)]+)\.html$ /cgi-bin/sample/sample.cgi?a=$1&b=$2 [L]
尚、上記のRewriteEngineやRewriteRuleはDirectoryディレクティブの中では効かないので注意すること.

*** GETで付与されたパラメータを自動付与する(query string append[QSA]) [#u2c55098]
 RewriteRule ^test/(.*)$ /test.php?no=$1 [QSA] 
上記の様なrewriteが設定されている場合を想定します。

以下のURLにアクセスすると
	 http://tsuyoshi.com/test/123?s=45&e=678&q=hoge

以下の様なURLとしてrewriteされます。(つまり、余分なパラメータもしっかりと付与してくれるわけです)
	 http://tsuyoshi.com/test.php?no=123&s=45&e=678&q=hoge

*** %2F(スラッシュ)が含まれるものはmod_rewriteのパターンにマッチしない [#cbee5dd9]
使っているapacheのバージョンが1.3系の場合には対処不可能です。
バージョンが2.0系以降に存在する以下のディレクティブを有効にする必要があります。
	 AllowEncodedSlashes On

*** rewrite前に存在するファイルやディレクトリに対してはrewriteを適用させたくない場合 [#o1807f55]

- ファイルの場合には、以下の様に記述します。
	 RewriteCond %{REQUEST_FILENAME} !-f
	 !-f は存在するファイル名にはルールを適用しない
- ディレクトリの場合には、以下の様に記述します。
	 RewriteCond %{REQUEST_FILENAME} !-d
	 !-d は存在するディレクトリ名にはルールを適用しない

*** rewriteのログを取得する
以下の様な行をconfに設定する
	 RewriteLog logs/rewrite_log
	 RewriteLogLevel 4


*** 参考URL
- ＵＲＬを書き換えろ！Apache Rewrite 機能の応用
-- http://www.nurs.or.jp/~sug/homep/rewrite/rewrite1.htm
- mod_rewrite モジュール URL 書き換えエンジン
-- http://net-newbie.com/trans/mod_rewrite.html

##################################################################
mod_userdir
##################################################################

*** 全てのユーザーでwwwを利用できるようにしたい。 [#r6589f65]
たとえば$HOMEの直下のpublic_html以下のファイルにアクセスする場合、httpd.conf
に以下を指定すればよい。
	 UserDir public_html
これにはmod_userdirモジュールが必要である。

*** ユーザーのディレクトリでの認証を行なう場合 [#qe5b2d28]
httpd.confから以下が記述されている行を探して以下のようにコメントアウトを外す。
	 <Directory /home/*/public_html>
	   AllowOverride FileInfo AuthConfig Limit
	   Options MultiViews Indexes SymLinksIfOwnerMatch IncludeNoExec
	   <Limit GET POST OPTIONS PROPFIND>
	      Order allow,deny
	      Allow from all
	   </Limit>
	   <LimitExcept GET POST OPTIONS PROPFIND>
	      Order deny,allow
	      Deny from all
	   </LimitExcept>
	 </Directory>

これはプログラムの実行を許可せずに、読みだし系のメソッドのみ許可する制限のある設定となります。
(注)ディレクトリでの認証にはhttpd.confでUserDir public_html」が必要です。
「UserDir none」とするとユーザーディレクトリでの認証を拒否します。


##################################################################
mod_alias
##################################################################
*** 仮想ディレクトリのマッピング [#s7371488]
/home/www/imagesディレクトリを/images/にマッピングしたければhttpd.confに
	 Alias /images/ "home/www/images/"
を指定すればよい。(mod_aliasモジュールが必要)

*** CGIプログラムを配置するディレクトリのマッピング [#rc09f905]
/home/www/cgi-binディレクトリを/cgi-bin/にマッピングしたければhttpd.confに
	 ScriptAlias /cgi-bin/ "/home/www/cgi-bin"
を追加指定すればよい。
これはCGIだけが利用するものであって、PHPなどはApache本体が実行するものでは
ない。あくまでも、拡張モジュールなどを必要としないCGIプログラムだけに使用す
ることを忘れないでほしい。

*** 全てのユーザーでのCGIプログラムの実行 [#ocdd3c7a]
これは仮想的なディレクトリの設定位置(<IfModule mod_alias.c>〜<IfModule>の間)
に以下を記述するだけでよい。
	 ScriptAliasMatch /~(..*)/cgi-bin/(.*) /home/$1/public_html/cgi-bin/$2


##################################################################
mod_mime
##################################################################
*** MIME(Multipart Internet Mail Extension)typeについて [#jd6556d2]
以下のようにMIMEtypeの原則がある。それぞれ解釈させなくてはならない。
以下は簡単な例である。
 ブラウザで開く　　　　　　text/html
 リアルプレイヤーで開く    audio/x-pn-realaudio
 エクセルで開く　　　　　　application/vnd.ms-excel

##################################################################
mod_perl
##################################################################
* 概要 [#v03ba8d0]
mod_perlは、ApacheにPerlインタプリタを組み込んだものです。
以下の特徴があります。
- CGIを使用せずに済む
- パフォーマンスを向上させることができる。
- mod_perlを組み込んだApache環境では、以下の2つのモジュール用命令を利用することができます。
-- Apache::Registry
--- Perlで作成したモジュールを実行する際に１度だけモジュールがコンパイルされ、メモリに常駐する。
-- Apache::PerlRun
--- Perlで作成したモジュールが呼び出されるたびにコンパイルされる。

*** 拡張子が.cgiのものはmod_perlで実行するように設定する。 [#e6fc5f1c]
こんな感じ
	  <IfModule mod_perl.c>
	    <Files *.cgi>
	      SetHandler perl-script
	      PerlHandler Apache::Registry
	      PerlSendHeader On
	    </Files>
	  </IfModule> 


*** PERL5LIBの設定 [#g21468ed]
	 PerlSetEnv PERL5LIB /usr/local/apache2/site_perl


*** 参考URL
- mod_perl公式サイト
-- http://perl.apache.org/

##################################################################
mod_ssl
##################################################################

* 概要 [#g8cfcac7]
ApacheでSSLを利用するためのモジュールmod_sslについてまとめます。
SSLによる認証機能はブラウザ側がサポートしています。
ブラウザ毎に登録済みの認証期間はブラウザ毎によって対応、非対応と分かれるので確認が必要です。
尚、SSLは、アクセスしてくるサーバ名前と認証用の名前が同一でないと駄目みたいです。

* 詳細 [#w742f31f]
** mod_sslを使用する。(RedHat9) [#j440e5aa]
今回はOpen-SSL＋mod_sslを使用して行います。(これがデファクトスタンダードです。)
この場合にはソースからmod_sslがモジュールとして組み込まれている必要があります。
尚、SSLはポート443/TCPでトランスポート層で動作します。

- 1.httpd.confに以下の記述があるかどうか確認する。
	 <IfModule mod_ssl.c>
	    Include conf/ssl.conf   <= $(ServerRoot)/confにssl.confがある亊を確認する
	 </IfModule>
と記述されていればOKです。

- 2.ssl.confの設定
	 #mkdir /var/www/html/sslsite  <= SSLのDocumentRootとするディレクトリ
	 #vi /var/www/html/sslsite/index.html
 (test用に簡単なHTMLを作っておく)
	 #vi /etc/httpd/conf.d/ssl.conf
以下の記述があること確認する。省略している部分もある。
	 Listen 443 
	 
	 <VirtualHost test.itbdns.com:443>
	   DocumentRoot "/var/www/html/sslsite"
	   ServerName test.itbdns.com:443
	   ServerAdmin test@test.com
	   SSLEngine on
	   SSLCertificateFile /etc/httpd/conf/ssl.crt/server.crt
	   SSLCertificateKeyFile /etc/httpd/conf/ssl.key/server.key
	 </VirtualHost>

- 3.Apacheの起動
	  #/usr/sbin/apachectl start
SSLも起動したい場合には次のようにする。
	  #/usr/sbin/apachectl startssl

以上がデフォルトでRedHatなどに含まれるパッケージでの設定である。
以下にソースからインストールした場合に必要なサーバー鍵作成、証明書作成の手順を述べる。

** サーバー鍵作成、サーバー証明書の作成、ssl.confの作成(sourceインストール時) [#v1650ce6]
以下では/usr/local/apacheにapacheがインストールされたものとして仮定する。ただ
しパッケージとしてapacheがrpmでインストールされているものと仮定する。
1.サーバーの鍵を作成する
	 # cd /etc/httpd/conf
	 # rm ssl.key/server.key  <=デフォルトで入っている鍵を削除
	 # rm ssl.crt/server.crt  <=デフォルトで入っている鍵を削除
	 # cd /usr/share/ssl/certs
	 # make genkey
 ここでパスワード入力を求められる。
 (注)
 サーバーを起動する度にパスワードを入力しないようにするにはmake genkeyではなく 以下の2つのコマンドを使用する。
	 # /usr/bin/openssl genrsa 1024 > /etc/httpd/conf/ssl.key/server.key
	 # chmod 400 /etc/httpd/conf/ssl.key/server.key

2.サーバー証明書の作成
	 # make testcert
対話形式で聞かれるので、以下のように入力する。
	 Country Name(2 letter Code)[GB]:JP
	 State or Province Name(full Name)[Berkshire]:Saitama
	 Locality Name(eg,city)[Newnury]:Kawaguchi-City
	 Organization Name(eg,company)[My Company Ltd]:Univercity
	 Organization Unit Name(eg,section)[]:science and technology
	 Common Name ()[]:www.test.itbdns.com
	 Email Address[]:test@test.com
	 (注)ぶっちゃけ適当でも構わない。
	 # mkdir /usr/local/apache/conf/ssl.crt
	 # mkdir /usr/local/apache/conf/ssl.key
	 # cd /etc/httpd/conf
	 # cp ssl.crt/server.crt /usr/local/apache/conf/ssl.crt/server.crt
	 # cp ssl.key/server.key /usr/local/apache/conf/ssl.key/server.key

3.後は先ほどと同じようにssl.confを設定して、apacheを再起動すれば良い。


* 参考URL [#a3b07315]
- mod_ssl(Apache)
-- SSL鍵交換の仕組みが図で記載されてて非常に直感的に理解しやすい
-- http://www007.upp.so-net.ne.jp/kcannex/pn/mod_ssl/
- SSL/TLSの仕組み
-- http://www.soumu.go.jp/main_sosiki/joho_tsusin/security/kiso/k01_ssl.htm
- @IT 身近なPKI〜SSLを理解する
-- http://www.atmarkit.co.jp/fnetwork/rensai/pki03/pki01.html
- ssl.confの設定
-- http://www.nina.jp/server/slackware/httpd/ssl.conf.html
