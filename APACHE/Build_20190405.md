# 概要
apacheをソースコードからインストールします。せっかくソースコードからインストールするのでデバッグビルド(-g3 -O0)で行います。

apacheのlatestバージョンは以下から確認します。
- https://httpd.apache.org/download.cgi

依存として必要なapr, apr-utilは以下から確認します。
- http://apr.apache.org/download.cgi

参考にしたドキュメントはこの辺です。
- https://qiita.com/ksugawara61/items/70f5d1faf192c4ba6ca0

# 詳細

### パッケージダウンロード
必要なパッケージをダウンロードする
```
$ wget https://github.com/libexpat/libexpat/releases/download/R_2_2_5/expat-2.2.5.tar.bz2
$ wget http://ftp.riken.jp/net/apache/apr/apr-1.6.5.tar.gz
$ wget http://ftp.riken.jp/net/apache/apr/apr-util-1.6.1.tar.gz
$ wget http://ftp.meisei-u.ac.jp/mirror/apache/dist//httpd/httpd-2.4.39.tar.gz
```

展開する
```
$ tar xvjf expat-2.2.5.tar.bz2
$ tar zxf apr-1.6.5.tar.gz 
$ tar zxf apr-util-1.6.1.tar.gz 
$ tar zxf httpd-2.4.39.tar.gz
```

### expatのインストール
```
$ cd expat-2.2.5
$ ./configure CFLAGS="-g3 -O0" --prefix=/opt/expat-2.2.5 
$ make
$ sudo make install
```

### aprインストール
```
$ cd apr-1.6.5
$ ./configure CFLAGS="-g3 -O0" --enable-debug --prefix=/opt/apr-1.6.5
$ make
$ sudo make install
```

### apr-utilインストール
apr-utilはaprのインストール先を指定するので、aprの後に必要です。
```
$ cd apr-util-1.6.1
$ ./configure CFLAGS="-g3 -O0" --enable-debug --prefix=/opt/apr-util-1.6.1 --with-apr=/opt/apr-1.6.5
$ make
$ sudo make install
```

### apr, apr-utilをhttpd-x.x.x/srclib/配下に移動します。
httpdをコンパイルする際にこれを実施しておかないと失敗します。
```
$ mv -iv apr-1.6.5 httpd-2.4.39/srclib/apr
$ mv -iv apr-util-1.6.1 httpd-2.4.39/srclib/apr-util
$ ls -F httpd-2.4.39/srclib/
Makefile  Makefile.in  apr/  apr-util/
```

### httpdインストール
今回は手元にローカルでビルドしたopenssl−1.1.1のデバッグビルドもあったので合わせて指定しておきます。
```
$ cd httpd-2.4.39/
$ ./configure CFLAGS="-g3 -O0" --prefix=/opt/httpd-2.4.39 --with-apr=/opt/apr-1.6.5 --with-apr-util=/opt/apr-util-1.6.1 --with-mpm=prefork --with-included-apr --with-included-apr-util --enable-so --enable-ssl --enable-mods-shared=all --with-ssl=/opt/openssl-1.1.1 --with-expat=/opt/expat-2.2.5/
$ make
$ sudo make install
```

### 起動
ServerNameだけ設定しておかないと起動はするがエラーメッセージが出るので設定しておく。
```
$ egrep "^ServerName" /opt/httpd-2.4.39/conf/httpd.conf 
ServerName 127.0.0.1:80
```

起動する
```
$ sudo /opt/httpd-2.4.39/bin/apachectl start
```

# エラーメモ

### httpdをmake時に出るXML関連のundefined referenceエラー
makeした際に次のようなエラーがでましたが、expatをソースから指定して--with-expat=/opt/expat-2.2.5/を付与して、
apr, apr-utilをsrclib配下に移動して--with-included-apr --with-included-apr-utilをconfigureに付与することでエラー回避できました。
```
/opt/apr-1.6.5/build-1/libtool --silent --mode=link gcc -std=gnu99  -g -Wall -pthread  -g3 -O0       -o htpasswd  htpasswd.lo passwd_common.lo       /opt/apr-util-1.6.1/lib/libaprutil-1.la /opt/apr-1.6.5/lib/libapr-1.la -lrt -lcrypt -lpthread -ldl -lcrypt
/opt/apr-util-1.6.1/lib/libaprutil-1.so: undefined reference to `XML_GetErrorCode'
/opt/apr-util-1.6.1/lib/libaprutil-1.so: undefined reference to `XML_SetEntityDeclHandler'
/opt/apr-util-1.6.1/lib/libaprutil-1.so: undefined reference to `XML_ParserCreate'
/opt/apr-util-1.6.1/lib/libaprutil-1.so: undefined reference to `XML_SetCharacterDataHandler'
/opt/apr-util-1.6.1/lib/libaprutil-1.so: undefined reference to `XML_ParserFree'
/opt/apr-util-1.6.1/lib/libaprutil-1.so: undefined reference to `XML_SetUserData'
/opt/apr-util-1.6.1/lib/libaprutil-1.so: undefined reference to `XML_StopParser'
/opt/apr-util-1.6.1/lib/libaprutil-1.so: undefined reference to `XML_Parse'
/opt/apr-util-1.6.1/lib/libaprutil-1.so: undefined reference to `XML_ErrorString'
/opt/apr-util-1.6.1/lib/libaprutil-1.so: undefined reference to `XML_SetElementHandler'
collect2: error: ld returned 1 exit status
make[2]: *** [htpasswd] Error 1
make[2]: Leaving directory `/home/tsuyoshi/apache/httpd-2.4.39/support'
make[1]: *** [all-recursive] Error 1
make[1]: Leaving directory `/home/tsuyoshi/apache/httpd-2.4.39/support'
make: *** [all-recursive] Error 1
```

