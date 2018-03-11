### LogFormatでログをカスタマイズしたい
mod_log_configを利用していますので、このページを見ると一番早いです。
```
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
```

### accessログをカスタマイズする
httpd.confには以下の様な複数の記述がある。
```
	 LogFormat "%h %l %u %t \"%r\" %>s %b \"%{Referer}i\" \"%{User-Agent}i\" \"%{forensic-id}n\" %T %v" full
	 LogFormat "%h %l %u %t \"%r\" %>s %b \"%{Referer}i\" \"%{User-Agent}i\" \"%{forensic-id}n\" %P %T" debug
	 LogFormat "%h %l %u %t \"%r\" %>s %b \"%{Referer}i\" \"%{User-Agent}i\" \"%{forensic-id}n\"" combined
	 LogFormat "%h %l %u %t \"%r\" %>s %b" common
```

また、上記の設定値を呼び出すことによって以下の様にして呼び出すことができる。
ログとして記述したいフォーマットを選びCustomLogを記述すればよい
CustomLogは複数行あっても問題なく、ログに複数のログが1リクエストで記述されることになる。

```
	 CustomLog /var/log/apache/access1.log combined
	 CustomLog /var/log/apache/access1.log common
	 CustomLog /var/log/apache/access1.log full
	 CustomLog /var/log/apache/access1.log debug
```

ログは次のような出力になります。
```
	 [full]
	 222.7.50.112 - - [29/Sep/2007:06:06:03 +0900] "GET / HTTP/1.1" 200 122 "-" "Mozilla/4.0 (compatible; MSIE 6.0; Windows NT 5.1; .NET CLR 1.1.4322)" "-" 0 test@test.itbdns.com
	 
	 [debug]
	 222.7.50.112 - - [29/Sep/2007:06:06:32 +0900] "GET / HTTP/1.1" 200 122 "-" "Mozilla/4.0 (compatible; MSIE 6.0; Windows NT 5.1; .NET CLR 1.1.4322)" "-" 6473 0
	 
	 [combined]
	 222.7.50.112 - - [29/Sep/2007:06:02:36 +0900] "GET / HTTP/1.1" 200 122 "-" "Mozilla/4.0 (compatible; MSIE 6.0; Windows NT 5.1; .NET CLR 1.1.4322)" "-"
	 
	 [common]
	 222.7.50.112 - - [29/Sep/2007:06:04:10 +0900] "GET / HTTP/1.1" 200 122
```

### 日、または時間ごとにログファイルを循環したい
```
/usr/sbin/rotatelogs
```
プログラムを利用すればよい。
httpd.confに以下の1行を加えればよい。
```
CustomLog "| /usr/sbin/rotatelogs /var/log/apache/access_log.%Y-%m-%d 86400" combined
```

### 各バーチャルホストごとに別々のログファイルに記録したい
```
split-logfile
```
プログラムを利用すればよい。
httpd.confに以下の様に記述する。
```
CustomLog "| /usr/sbin/split-logfile /var/log/apache" combined
```

### accessログでIPアドレスではなく、ホスト名を記録したい
デフォルトではおそらく
```
HostnameLookups Off
```
となっているのでこれを以下に変更する。
```
HostnameLookups On
```
これによりログが以下の様に変更される
```
(変更前) 222.7.50.112 - - [29/Sep/2007:17:00:46 +0900]
(変更後) test.itbdns.com - - [29/Sep/2007:17:00:46 +0900]
```

### POSTで送られてきたデータをログに記録したい
- apache1.3では、POST処理モジュールで明示的にデータを記録しない限り不可である。
- apache2.0では、入力フィルタの機能を介してPOST方式を記録でるが、現在そのようなフィルタは存在しない

# SeeAlso
- ApacheV2.0 モジュール mod_log_config
  - http://httpd.apache.org/docs/2.0/ja/mod/mod_log_config.html
