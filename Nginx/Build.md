# 概要
nginxのソースコードからのインストール+デバッグビルド

以下に記載されているstable版をインストールします。
- http://nginx.org/en/download.html

これを記載時点でstableの1.14.2をダウンロードします。
- http://nginx.org/download/

# 詳細
インストール
```
$ wget http://nginx.org/download/nginx-1.14.2.tar.gz
$ tar zxf nginx-1.14.2.tar.gz 
$ cd nginx-1.14.2
$ ./configure --prefix=/opt/nginx-1.14.2 --with-cc-opt='-g3 -O0'
$ make
$ sudo make install
```

確認
```
$ /opt/nginx-1.14.2/sbin/nginx -V
nginx version: nginx/1.14.2
built by gcc 4.8.5 20150623 (Red Hat 4.8.5-16) (GCC) 
configure arguments: --prefix=/opt/nginx-1.14.2 --with-cc-opt='-g3 -O0'
```

起動
```
$ sudo /opt/nginx-1.14.2/sbin/nginx 
$ sudo lsof -i:80
COMMAND   PID   USER   FD   TYPE  DEVICE SIZE/OFF NODE NAME
nginx   20605   root    6u  IPv4 1251354      0t0  TCP *:http (LISTEN)
nginx   20606 nobody    6u  IPv4 1251354      0t0  TCP *:http (LISTEN)
```

停止
```
$ sudo /opt/nginx-1.14.2/sbin/nginx -s stop
```

# 参考
- NGinx: Installation and Compile-Time Options
  - https://www.nginx.com/resources/wiki/start/topics/tutorials/installoptions/
