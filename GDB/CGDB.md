# 概要
CGDBを使うとvimライクなUIでGDBでアタッチすることができるようになします。

## うまくアタッチできない場合
以下を確認しましょう
- バイナリはstrippedされていないか?
- gdbコマンドでdirectory登録したか?もしくはdebuginfoパッケージを入れたか?
- breakポイントを設定したか?
- breakポイントを本当に通過しているのか?
- continueしているか?

## CGDBインストール From YUM
```
$ uname -a
Linux localhost.localdomain 3.3.4-5.fc17.x86_64 #1 SMP Mon May 7 17:29:34 UTC 2012 x86_64 x86_64 x86_64 GNU/Linux
$ sudo yum install cgdb cgdb-debuginfo
```

## インストール From ソースコード
```
$ sudo yum instlal textinfo help2man -n
$ git clone https://github.com/cgdb/cgdb.git
$ cd cgdb
$ ./autogen.sh
$ ./configure
$ make
$ sudo make install
$ which cgdb
/usr/local/bin/cgdb
```


##  apacheのソースコードに当てはめてみる(debuginfoが入っている場合)
debuginfoが入っている場合にはdirectoryを指定する必要はなさそうです
```
$ sudo vim /etc/httpd/conf/httpd.conf
// IfModule prefork.cの中のMaxClientsを1に設定してください。
$ sudo apachectl stop
$ sudo apachectl start
$ ps auxww | grep -i apache
```

続いてcgdbをあててみます。
```
$ sudo cgdb /usr/sbin/httpd `pgrep -fu apache`
(gdb) b	ap_update_child_status
(gdb) continue
```

あとはリクエストを出すと画面上部にはソースコードが表示されるようになります。

## apacheのソースコードに当てはめてみる(ソースコードからのインストール)
```
$ sudo vim /etc/httpd/conf/httpd.conf
// IfModule prefork.cの中のMaxClientsを1に設定してください。
$ sudo apachectl stop
$ sudo apachectl start
$ ps auxww | grep -i apache
```

続いてcgdbをあててみます。  
あらかじめソースコードを展開したトップディレクトリに移動してからcgdbコマンドを実行します。  
directoryは再帰的に面倒見てくれないので全て指定します。ここではpreforkと仮定してcoreソースの一部だけ指定します
```
$ cd <path_to_source>
$ sudo cgdb /usr/sbin/httpd `pgrep -fu apache`
(gdb) directory server/:server/mpm/prefork/:include/:modules/http/:modules/loggers/     # 必要に応じて:区切りでつなげてください
(gdb) b	ap_update_child_status
(gdb) continue
```
