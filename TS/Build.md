# 概要
trafficserverのビルドに関して


### ソースコードからインストールする
今回ソースコードをからビルドしたのは次の環境です。
```
$ uname -a
Linux localhost.localdomain 3.10.0-693.el7.x86_64 #1 SMP Tue Aug 22 21:09:27 UTC 2017 x86_64 x86_64 x86_64 GNU/Linux
$ cat /proc/version 
Linux version 3.10.0-693.el7.x86_64 (builder@kbuilder.dev.centos.org) (gcc version 4.8.5 20150623 (Red Hat 4.8.5-16) (GCC) ) #1 SMP Tue Aug 22 21:09:27 UTC 2017
$ gcc --version
gcc (GCC) 4.8.5 20150623 (Red Hat 4.8.5-16)
Copyright (C) 2015 Free Software Foundation, Inc.
This is free software; see the source for copying conditions.  There is NO
warranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
```

予め必要なpackageをインストールします。Requirementsを知りたければtrafficserverのgitレポジトリ直下のREADMEに記載されています。
```
$ sudo yum install openssl openssl-devel
$ sudo yum -y install tcl-devel libxml2-devel pcre-devel
```

githubを取得します。
```
$ git clone https://github.com/apache/trafficserver.git
$ cd trafficserver
$ git branch -a
$ git checkout remotes/origin/7.1.x
```

autoreconfを実行してconfigureを生成します。
```
$ autoreconf -if 
$ ls configure
configure
```

デバッグ用にしてビルドするためにenable-debugを付与しています。
```
$ ./configure --prefix=/opt/trafficserver-7.1.x --enable-debug
```

あとは次のようにしてmake, make installします。
```
$ make
$ sudo make install
```

以上により起動してみます。
```
$ sudo /opt/trafficserver-7.1.x/bin/trafficserver start
Starting Apache Traffic Server:                            [  OK  ]
$ ps auxww | grep -i traffic_
root     30753  0.0  0.3  57044  3552 ?        Ss   13:18   0:00 /opt/trafficserver-7.1.x/bin/traffic_cop
nobody   30755  0.5  0.6 297104  6748 ?        Sl   13:18   0:00 /opt/trafficserver-7.1.x/bin/traffic_manager --bind_stdout /opt/trafficserver-7.1.x/var/log/trafficserver/traffic.out --bind_stderr /opt/trafficserver-7.1.x/var/log/trafficserver/traffic.out
nobody   30762  1.5  3.8 310668 39508 ?        Sl   13:18   0:00 /opt/trafficserver-7.1.x/bin/traffic_server --bind_stdout /opt/trafficserver-7.1.x/var/log/trafficserver/traffic.out --bind_stderr /opt/trafficserver-7.1.x/var/log/trafficserver/traffic.out -M --httpport 8080:fd=9,8080:fd=10:ipv6
```

デフォルトだと8080ポートで稼働しています。
```
$ netstat -an | grep -w LISTEN
tcp        0      0 0.0.0.0:8080            0.0.0.0:*               LISTEN     
tcp        0      0 127.0.0.1:8083          0.0.0.0:*               LISTEN     
tcp        0      0 127.0.0.1:8084          0.0.0.0:*               LISTEN     
tcp        0      0 0.0.0.0:22              0.0.0.0:*               LISTEN     
tcp        0      0 127.0.0.1:25            0.0.0.0:*               LISTEN     
tcp6       0      0 :::8080                 :::*                    LISTEN     
tcp6       0      0 :::22                   :::*                    LISTEN     
tcp6       0      0 ::1:25                  :::*                    LISTEN    
```


