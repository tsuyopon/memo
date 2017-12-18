
# analogのインストール(RedHat9の例) 
Analogはアクセスlog集計ソフトウェアで視覚的に教えてくれます。
以下ではソースからのインストールを説明します。
```
#cd /usr/local/src
http://www.analog.cx/donload.htmlのサイトから自分にあった物を取ってくる。
#wget http://www.iddl.vt.edu/~jackie/analog/analog-6.0-1.src.rpm
#rpmbuild --rebuild --target i686 analog-6.0-1.src.rpm
#cd /usr/src/redhat/RPMS/i686
#rpm -ivh analog-6.0-1.i686.rpm
#mkdir -p /usr/local/analog6/report
#cp -r /usr/local/analog6.0/images /usr/local/analog6.0/report
#vi /etc/analog.cfg (<=analog.cfgの設定については後ほど説明)
#vi /etc/httpd.conf
```

以下の行を追加する。
```
AddHandler cgi-script .cgi .pl  (<=コメントアウトを外し.plを追加)
Alias /analog/  /usr/local/analog6.0/report/
Directory /usr/local/analog6.0/report>
           Options ExecCGI
                       AllowOverride None
                       Order allow,deny
                       Allow from all
</Directory>
```

修正したらapacheの再起動を行います。
```
#/etc/init.d/httpd restart
```
※/etc/analog.cfgを編集してもhttpdを再起動する必要はない。
上記ではhttpd.confを編集したので再起動した。

以上で編集は終了である。

#/usr/bin/apacheでhtmlファイルが作成できたのが確認できる。
ブラウザなどで確認するといいだろう。
次のanalog.cfgの設定で出力先などは指定するのでそちらを参考にするとよい。
一般的に次のような警告が出るが[L]、[R]の警告は重要ではないらしいのであまり
気にしないほうが良い。
```
 analog: analog version 6.0/Unix
 analog: Warning R: Turning off empty Search Word Report
        (For help on all errors and warnings, see docs/errors.html)
        ----------------------------------------------------------------------------
        この時の警告の種類を以下に示す。
        C：不正な設定が行なわれた
        D：疑わしい設定が行なわれた
        E：ERRFILE コマンドが記述された
        F：ファイルが存在しないか壊れている
        G：corrupt lines in support files
        L：ログファイルに明らかな問題がある。
        M：ログファイルに多分問題がある。
        R：空のレポートの出力を止める。
        -----------------------------------------------------------------------------
```

最後に定期的にanalogが起動するようにcron.dailyディレクトリにshファイルを置く。
```
#vi analog.pl
-----------------------------------------------------------------------------
#!/bin/sh
       /usr/bin/analog
-----------------------------------------------------------------------------
#chmod u+x analog.pl
#mv analog.pl /etc/cron.daily
```

### /etc/analog.cfgの設定について
```
x  GENERAL      全体の概要
m  MONTHLY      月別レポート
W  WEEKLY       週別レポート
D  FULLDAILY    日別レポート
d  DAILY        曜日別概要
H  FULLHOURLY   時間別レポート
h  HOURLY       時間別概要
4  QUARTER      15分間隔レポート
5  FIVE         5分間隔レポート
S  HOST         ホストレポート
Z  ORGANISATION 組織レポート
o  DOMAIN       ドメインレポート
r  REQUEST      リクエストレポート
i  DIRECTORY    ディレクトリレポート
t  FILETYPE     ファイル種類別レポート
z  SIZE         ファイルサイズレポート
P  PROCTIME     処理時間レポート
E  REDIR        リダイレクションレポート
I  FAILURE      不成功レポート
f  REFERRER     リンク元レポート
s  REFSITE      リンク元サイトレポート
N  SEARCHQUERY  検索語句レポート
n  SEARCHWORD   検索語レポート
k  REDIRREF     リダイレクトされたリンク元レポート
K  FAILREF      不成功リンク元レポート
B  FULLBROWSER  ブラウザーレポート
b  BROWSER      ブラウザーの概要
p  OSREP        ＯＳレポート
v  VHOST        仮想ホストレポート
u  USER         ユーザレポート
J  FAILUSER     不成功ユーザレポート
c  STATUS       状態コードレポート
```


次のようなanalog.cfgを作成すれば良いだろう。
```
#
LANGFILE /usr/lib/analog/lang/jp.lng

#日本語だとJAPANESE-EUC,JAPANESE-SJIS,JAPANESE-UTFから選べる。
#LANGUAGE JAPANESE
LANGUAGE JAPANESE-EUC


#OUTPUT COMPUTER

#LOGFILEはログファイルの出力先としての指定先を示す。
#LOGFILE /var/log/httpd/*access*
                                                                                                LOGFILE /var/log/httpd/access_log

#OUTFILEはレポートの出力ファイルを絶対パスで指定します。これは必須項目
OUTFILE /usr/local/analog-6.0/report/Report.html
#CHARTDIR /analog/images/
CHARTDIR /usr/local/analog-6.0/images/
LOCALCHARTDIR /usr/lib/analog/web/images/

#HOSTNAMEは出力された統計レポートの先頭に出力され、HOSTURLはそのリンク先です。
HOSTNAME "WWW Server(test.itbdns.com)"
HOSTURL http://www.test.itbdns.com/

#DNS WRITEはDNS検索のモードを"WRITE"に設定する。
#DNS WRITE

#DNSFILE /var/analog-6.0.1/dnsfile.txt

#WARNINGS -LRはLとRに関する警告は表示しません。LとRは大したことのないエラー
#らしいです。デフォルト(WARNINGS ON)では全ての記号に対して警告を出します。
#WARNINGS -LR

#DNSGOODHOURSは失敗したDNS検索を再試行するまでの時間です。
#DNSGOODHOURS 168

#STYLESHEETはレポート出力で指定したいcssスタイルシートを指定する。
#STYLESHEET ./default.css
#HEADERFILE /var/www/httpd/analog-header
#FOOTERFILE /var/www/httpd/analog-footer

#SUBDOMAIN *.*.*はレポートの統計を取るときに3つの階層まで指定できる
#ことを意味する。
SUBDOMAIN *.*.*

GENERAL         ON  :全体の概要
YEARLY          ON　:年別レポート
QUARTERLY       OFF :4半期別レポート
MONTHLY         ON  :月別レポート
DAILYREP        ON　:週別レポート
DAILYSUM        ON  :日別レポート
WEEKLY          ON  :曜日別集計
HOURLYREP       OFF :時間別レポート
HOURLYSUM       ON　:時間別集計
QUARTERREP      OFF :15分間隔レポート
QUARTERSUM      OFF :15分間隔集計
FIVEREP         OFF :5分間隔レポート
FIVESUM         OFF :5分間隔集計
DOMAIN          ON  :ドメインレポート
ORGANIZATION    ON  :組織別レポート
DIRECTORY       ON　:ディレクトリレポート
FILETYPE        OFF :ファイル種類別レポート
REQUEST         OFF :リクエストレポート
REDIR           OFF :リダイレクトリポート
FAILURE         OFF :失敗したリクエストレポート
SIZE            OFF :ファイルサイズレポート
PROCTIME        OFF :プロセスタイムレポート
HOST            OFF :ホストレポート
REDIRHOST       OFF :ホストのリダイレクトレポート
FAILHOST        OFF :ホストの不成功レポート
REFERRER        OFF :リンク元URLレポート
FAILREF         OFF :リンク元サイトレポート
VHOST           OFF :バーチャルホストレポート
REDIRVHOST      OFF :バーチャルホストのリダイレクトレポート
FAILVHOST       OFF :バーチャルホストの不成功レポート
USER            OFF :ユーザーレポート
REDIRUSER       OFF :ユーザーのリダイレクトレポート
FAILUSER        OFF :ユーザーの不成功レポート
SEARCHQUERY     OFF :検索結果のレポート
SEARCHWORD      ON  :検索後レポート
INTSEARCHQUERY  OFF :インターナル検索結果レポート
INTSEARCHWORD   OFF :インターナル検索後レポート
BROWSERREP      OFF :ブラウザレポート
BROWSERSUM      OFF :ブラウザの概要
OSREP           OFF :OSレポート
STATUS          OFF :状態コードレポート

# REQINCLUDE pages
REQLINKINCLUDE pages
REFLINKINCLUDE *
REDIRREFLINKINCLUDE *
FAILREFLINKINCLUDE *
UNCOMPRESS *.gz,*.Z "gzip -cd"
BROWOUTPUTALIAS Mozilla Netscape
BROWOUTPUTALIAS "Mozilla (compatible)" "Netscape (compatible)"
BROWOUTPUTALIAS IWENG AOL
SUBBROW */*
                                               SUBTYPE *.gz,*.Z
# Add whichever of these types of pages you have on your server, or others.
# PAGEINCLUDE *.shtml
# PAGEINCLUDE *.asp
# PAGEINCLUDE *.jsp
# PAGEINCLUDE *.cfm
# PAGEINCLUDE *.pl
# PAGEINCLUDE *.php
SEARCHENGINE http://*altavista.*/* q
SEARCHENGINE http://*yahoo.*/* p
SEARCHENGINE http://*google.*/* q
SEARCHENGINE http://*lycos.*/* query
SEARCHENGINE http://*aol.*/* query
SEARCHENGINE http://*excite.*/* search
SEARCHENGINE http://*go2net.*/* general
SEARCHENGINE http://*metacrawler.*/* general
SEARCHENGINE http://*msn.*/* MT
SEARCHENGINE http://*hotbot.com/* MT
SEARCHENGINE http://*netscape.*/* search
SEARCHENGINE http://*looksmart.*/* key
SEARCHENGINE http://*infoseek.*/* qt
SEARCHENGINE http://*webcrawler.*/* search,searchText
SEARCHENGINE http://*goto.*/* Keywords
SEARCHENGINE http://*snap.*/* keyword
SEARCHENGINE http://*dogpile.*/* q
SEARCHENGINE http://*askjeeves.*/* ask
SEARCHENGINE http://*ask.*/* ask
SEARCHENGINE http://*aj.*/* ask
SEARCHENGINE http://*directhit.*/* qry
SEARCHENGINE http://*alltheweb.*/* query
SEARCHENGINE http://*northernlight.*/* qr
SEARCHENGINE http://*nlsearch.*/* qr
SEARCHENGINE http://*dmoz.*/* search
SEARCHENGINE http://*newhoo.*/* search
SEARCHENGINE http://*netfind.*/* query,search,s
SEARCHENGINE http://*/netfind* query
SEARCHENGINE http://*/pursuit query
SEARCHENGINE http://*goo.ne.jp/* MT
SEARCHENGINE http://*netplaza.biglobe.ne.jp/* key
SEARCHENGINE http://*search.biglobe.ne.jp/* q
SEARCHENGINE http://*infoweb.ne.jp/cgi-bin/asearch* QueryString
ROBOTINCLUDE REGEXPI:robot
ROBOTINCLUDE REGEXPI:spider
ROBOTINCLUDE REGEXPI:crawler
ROBOTINCLUDE Googlebot*
ROBOTINCLUDE Infoseek*
ROBOTINCLUDE Scooter*
ROBOTINCLUDE Slurp*
ROBOTINCLUDE Ultraseek*
TYPEOUTPUTALIAS .html    ".html [Hypertext Markup Language]"
TYPEOUTPUTALIAS .htm     ".htm  [Hypertext Markup Language]"
TYPEOUTPUTALIAS .shtml   ".shtml [Server-parsed HTML]"
TYPEOUTPUTALIAS .ps      ".ps   [PostScript]"
TYPEOUTPUTALIAS .gz      ".gz   [Gzip compressed files]"
TYPEOUTPUTALIAS .tar.gz  ".tar.gz [Compressed archives]"
TYPEOUTPUTALIAS .jpg     ".jpg  [JPEG graphics]"
TYPEOUTPUTALIAS .jpeg    ".jpeg  [JPEG graphics]"
TYPEOUTPUTALIAS .gif     ".gif  [GIF graphics]"
TYPEOUTPUTALIAS .png     ".png  [PNG graphics]"
TYPEOUTPUTALIAS .txt     ".txt  [Plain text]"
TYPEOUTPUTALIAS .cgi     ".cgi  [CGI scripts]"
TYPEOUTPUTALIAS .pl      ".pl  [Perl scripts]"
TYPEOUTPUTALIAS .css     ".css  [Cascading Style Sheets]"
TYPEOUTPUTALIAS .class   ".class [Java class files]"
TYPEOUTPUTALIAS .pdf     ".pdf  [Adobe Portable Document Format]"
TYPEOUTPUTALIAS .zip     ".zip  [Zip archives]"
TYPEOUTPUTALIAS .lzh     ".lzh  [Lha archives]"
TYPEOUTPUTALIAS .hqx     ".hqx  [Macintosh archives]"
TYPEOUTPUTALIAS .exe     ".exe  [PC ebxecutables]"
TYPEOUTPUTALIAS .wav     ".wav  [WAV sound files]"
TYPEOUTPUTALIAS .avi     ".avi  [AVI movies]"
TYPEOUTPUTALIAS .arc     ".arc  [Compressed archives]"
TYPEOUTPUTALIAS .mid     ".mid  [MIDI sound files]"
TYPEOUTPUTALIAS .mp3     ".mp3  [MP3 sound files]"
TYPEOUTPUTALIAS .doc     ".doc  [Microsoft Word document]"
TYPEOUTPUTALIAS .rtf     ".rtf  [Rich Text Format]"
TYPEOUTPUTALIAS .mov     ".mov  [Quick Time movie]"
TYPEOUTPUTALIAS .mpg     ".mpg  [MPEG movie]"
TYPEOUTPUTALIAS .mpeg    ".mpeg  [MPEG movie]"
TYPEOUTPUTALIAS .asp     ".asp  [Active Server Pages]"
TYPEOUTPUTALIAS .jsp     ".jsp  [Java Server Pages]"
TYPEOUTPUTALIAS .cfm     ".cfm  [Cold Fusion]"
TYPEOUTPUTALIAS .php     ".php  [PHP]"
TYPEOUTPUTALIAS .js      ".js  [JavaScript code]"
```

# 参考URL
- Analog公式ホームページ
  - http://www.analog.cx/
- Apache ログ解析 Analog の導入
  - http://www.miloweb.net/analog.html

