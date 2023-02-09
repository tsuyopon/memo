# 概要
docker-composeコマンドを利用した作業・開発業務などのTIPSについて記載します。

# 詳細

### docker-composeを試してみる
以下の内容でdocker-compose.ymlファイルを用意します。
```
$ cat docker-compose.yml
version: '3.7'

services:
  app:
    image: php:7-apache
    depends_on:
      - db
  db:
    image: mysql:8
    volumes:
      - mysqldata:/var/lib/mysql
    environment:
      MYSQL_ROOT_PASSWORD: root

volumes:
  mysqldata:
    driver: local
```

では、起動してみます。イメージ取得まで自動的にやって、コンテナも起動してくれました。
```
$ docker-compose up -d
Docker Compose is now in the Docker CLI, try `docker compose up`

Creating network "docker_default" with the default driver
Creating volume "docker_mysqldata" with local driver
Pulling db (mysql:8)...
8: Pulling from library/mysql
f003217c5aae: Pull complete
65d94f01a09f: Pull complete
43d78aaa6078: Pull complete
a0f91ffbdf69: Pull complete
59ee9e07e12f: Pull complete
04d82978082c: Pull complete
70f46ebb971a: Pull complete
db6ea71d471d: Pull complete
c2920c795b25: Pull complete
26c3bdf75ff5: Pull complete
9ec1f1f78b0e: Pull complete
4607fa685ac6: Pull complete
Digest: sha256:1c75ba7716c6f73fc106dacedfdcf13f934ea8c161c8b3b3e4618bcd5fbcf195
Status: Downloaded newer image for mysql:8
Pulling app (php:7-apache)...
7-apache: Pulling from library/php
c229119241af: Pull complete
47e86af584f1: Pull complete
e1bd55b3ae5f: Pull complete
1f3a70af964a: Pull complete
0f5086159710: Pull complete
7d9c764dc190: Pull complete
ec2bb7a6eead: Pull complete
9d9132470f34: Pull complete
fb23ab197126: Pull complete
cbdd566be443: Pull complete
be224cc1ae0f: Pull complete
629912c3cae4: Pull complete
f1bae9b2bf5b: Pull complete
Digest: sha256:ef46a8784e3f71cd19fa3833850a91e80aa592e7d8339194defd8adb17ed3fa1
Status: Downloaded newer image for php:7-apache
Creating docker_db_1 ... done
Creating docker_app_1 ... done
```

docker-composeで起動した対象のイメージが起動していることも確認します。
```
$ docker-compose images
 Container     Repository     Tag        Image Id       Size  
--------------------------------------------------------------
docker_app_1   php          7-apache   eca4459c9842   452.3 MB
docker_db_1    mysql        8          667ee8fb158e   520.7 MB
```

終了するにはdownオプションを指定します。
```
$ docker-compose down
```

### docker-composeで立ち上げたコンテナで稼働するプロセスを確認する
```
$ docker-compose top
docker_app_1
  UID       PID    PPID    C   STIME   TTY     TIME             CMD         
----------------------------------------------------------------------------
www-data   305     99716   0   00:10   ?     00:00:00   apache2 -DFOREGROUND
www-data   306     99716   0   00:10   ?     00:00:00   apache2 -DFOREGROUND
www-data   307     99716   0   00:10   ?     00:00:00   apache2 -DFOREGROUND
www-data   308     99716   0   00:10   ?     00:00:00   apache2 -DFOREGROUND
www-data   309     99716   0   00:10   ?     00:00:00   apache2 -DFOREGROUND
root       99716   99694   0   00:10   ?     00:00:00   apache2 -DFOREGROUND

docker_db_1
UID    PID    PPID    C   STIME   TTY     TIME      CMD  
---------------------------------------------------------
999   99509   99482   1   00:10   ?     00:00:03   mysqld
```

### psコマンドを実行する
```
$ docker-compose -f ./docker-compose.yml ps
            Name                           Command                  State                                                                Ports                                                         
-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
cdn-in-a-box_db_1               docker-entrypoint.sh /run- ...   Up             0.0.0.0:5432->5432/tcp                                                                                                 
cdn-in-a-box_dns_1              /sbin/entrypoint.sh /usr/s ...   Up             0.0.0.0:9353->53/tcp, 0.0.0.0:9353->53/udp                                                                             
cdn-in-a-box_edge_1             /bin/sh -c /run.sh               Up             0.0.0.0:2347->2347/tcp, 0.0.0.0:9000->80/tcp                                                                           
cdn-in-a-box_enroller_1         /bin/sh -c /run.sh               Up             0.0.0.0:2343->2343/tcp                                                                                                 
```

### docker-composeで立ち上げたコンテナのログを見る
docker-compose.ymlが存在するディレクトリで実施してください。
各種コンテナのログがわかるようになっています。以下ではdb_1やapp_1のログがわかります。
```
$ docker-compose logs
(snip)
db_1   | 2022-03-31T00:10:32.712382Z 0 [Warning] [MY-011810] [Server] Insecure configuration for --pid-file: Location '/var/run/mysqld' in the path is accessible to all OS users. Consider choosing a different directory.
db_1   | 2022-03-31T00:10:32.784608Z 0 [System] [MY-010931] [Server] /usr/sbin/mysqld: ready for connections. Version: '8.0.28'  socket: '/var/run/mysqld/mysqld.sock'  port: 3306  MySQL Community Server - GPL.
db_1   | 2022-03-31T00:10:32.785094Z 0 [System] [MY-011323] [Server] X Plugin ready for connections. Bind-address: '::' port: 33060, socket: /var/run/mysqld/mysqlx.sock
app_1  | AH00558: apache2: Could not reliably determine the server's fully qualified domain name, using 172.22.0.3. Set the 'ServerName' directive globally to suppress this message
app_1  | AH00558: apache2: Could not reliably determine the server's fully qualified domain name, using 172.22.0.3. Set the 'ServerName' directive globally to suppress this message
app_1  | [Thu Mar 31 00:10:19.693476 2022] [mpm_prefork:notice] [pid 1] AH00163: Apache/2.4.53 (Debian) PHP/7.4.28 configured -- resuming normal operations
app_1  | [Thu Mar 31 00:10:19.693544 2022] [core:notice] [pid 1] AH00094: Command line: 'apache2 -D FOREGROUND'
```


デフォルトではカレンとディレクトリにdocker-compose.ymlが配置されているかどうかで、
ymlに記載されているサービスのログを取得するかどうかを決定します。 ymlファイルを明示的に指定する場合にはfオプションで指定してください。
```
$ docker-compose -f option/docker-compose.yml
```

### 各種ファイルを変更した場合に反映するために必要なコマンドについて
docker-compose.yml, Dockerfile, ソースコード変更などに従って何のコマンドが必要かについて整理してくれています。
- https://qiita.com/subretu/items/5857628534b53f29f5a3

### コンテナをリビルドして
Dockerfileやdocker-compose.ymlの内容を更新した場合には
```
$ docker-compose build --no-cache
$ docker-compose up -d --build --force-recreate
```

上記だけだとボリュームなどが反映されないケースがあるみたいです。


### 滅びのコマンドを実行する
docker-composeで以下の処理を一括で実施したい場合
- コンテナ止める
- ネットワーク削除する
- ボリューム削除する
- イメージ削除する

```
$ docker-compose down --rmi all --volumes
```
