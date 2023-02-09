# 概要
Docker Composeとは、yaml形式の設定ファイルで複数のコンテナの管理ができるツールです。設定ファイルがあれば、コマンド1つでコンテナの実行ができます。

# 注意事項
docker-composeは「-f」オプションを指定しないと「-f docker-compose.yml」を指定したことと同義になります。
docker-comoposeはdocker-compose.ymlの存在するディレクトリで実行が必要です。

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
upは起動させるオプションで、-dによりバックグラウンド実行させることができます。
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

終了するにはdownオプションを指定します。コンテナを停止して、ネットワークも削除します。
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

### docker-composeのコンテナ内で実行されているイベントコマンドを取得する
下記でtailのようにdocker内で実行されているコマンドが出力されます。
```
$ sudo docker-compose events
2023-02-10 02:11:57.629502 container exec_create: /bin/sh -c bash -c 'source /to-access.sh && [[ "$(curl -s http://trafficmonitor.infra.ciab.test/api/traffic-ops-uri)" == "$TO_URL" ]]' 6c1477439b99b9f22022d69eecee5d84f80af5d3bae63d731570d523857cce1a (execID=71cf05c3818bd9ad08286ae68cb33dd1f69885ef3e1c51b6bca3f9cb753ccdbf, image=trafficmonitor-debug, name=cdn-in-a-box_trafficmonitor_1)
2023-02-10 02:11:57.631514 container exec_start: /bin/sh -c bash -c 'source /to-access.sh && [[ "$(curl -s http://trafficmonitor.infra.ciab.test/api/traffic-ops-uri)" == "$TO_URL" ]]' 6c1477439b99b9f22022d69eecee5d84f80af5d3bae63d731570d523857cce1a (execID=71cf05c3818bd9ad08286ae68cb33dd1f69885ef3e1c51b6bca3f9cb753ccdbf, image=trafficmonitor-debug, name=cdn-in-a-box_trafficmonitor_1)
2023-02-10 02:11:57.732582 container exec_die 6c1477439b99b9f22022d69eecee5d84f80af5d3bae63d731570d523857cce1a (execID=71cf05c3818bd9ad08286ae68cb33dd1f69885ef3e1c51b6bca3f9cb753ccdbf, exitCode=0, image=trafficmonitor-debug, name=cdn-in-a-box_trafficmonitor_1)
2023-02-10 02:12:03.181608 container exec_create: /bin/sh -c bash -c 'source /to-access.sh && [[ "$(curl -sk "https://${TO_FQDN}/api/${TO_API_VERSION}/ping" | jq .ping)" == \"pong\" ]]' 7ee3f6ebc1e1d59f615b3d934633e68a63acfd8a7b25424a4bba2b338772da8a (desktop.docker.io/binds/0/Source=/Users/tsuyoshi/trafficcontrol/infrastructure/cdn-in-a-box/traffic_ops/ca, desktop.docker.io/binds/0/SourceKind=hostFile, desktop.docker.io/binds/0/Target=/ca, execID=cba93524c2c57e1bc660e88df7664321ab107e5a496dae2ba9f99df66917a4a2, image=trafficops-debug, name=cdn-in-a-box_trafficops_1)
2023-02-10 02:12:03.182603 container exec_start: /bin/sh -c bash -c 'source /to-access.sh && [[ "$(curl -sk "https://${TO_FQDN}/api/${TO_API_VERSION}/ping" | jq .ping)" == \"pong\" ]]' 7ee3f6ebc1e1d59f615b3d934633e68a63acfd8a7b25424a4bba2b338772da8a (desktop.docker.io/binds/0/Source=/Users/tsuyoshi/trafficcontrol/infrastructure/cdn-in-a-box/traffic_ops/ca, desktop.docker.io/binds/0/SourceKind=hostFile, desktop.docker.io/binds/0/Target=/ca, execID=cba93524c2c57e1bc660e88df7664321ab107e5a496dae2ba9f99df66917a4a2, image=trafficops-debug, name=cdn-in-a-box_trafficops_1)
2023-02-10 02:12:03.322222 container exec_die 7ee3f6ebc1e1d59f615b3d934633e68a63acfd8a7b25424a4bba2b338772da8a (desktop.docker.io/binds/0/Source=/Users/tsuyoshi/trafficcontrol/infrastructure/cdn-in-a-box/traffic_ops/ca, desktop.docker.io/binds/0/SourceKind=hostFile, desktop.docker.io/binds/0/Target=/ca, execID=cba93524c2c57e1bc660e88df7664321ab107e5a496dae2ba9f99df66917a4a2, exitCode=0, image=trafficops-debug, name=cdn-in-a-box_trafficops_1)
2023-02-10 02:12:06.200529 container exec_create: /bin/sh -c bash -c 'source /to-access.sh && [[ "$(wget -qO- https://$SMTP_FQDN/healthz)" == true ]]' 1d96b30a6448b3ac84b62bb2ec42fbc1ae0b85c31fe4bda964be79a5c276a555 (execID=9f790b225963e889c0060c064d996ecd84ee1e84afd0fb62b668b837ccdefc27, image=cdn-in-a-box_smtp, name=cdn-in-a-box_smtp_1)
2023-02-10 02:12:06.201129 container exec_start: /bin/sh -c bash -c 'source /to-access.sh && [[ "$(wget -qO- https://$SMTP_FQDN/healthz)" == true ]]' 1d96b30a6448b3ac84b62bb2ec42fbc1ae0b85c31fe4bda964be79a5c276a555 (execID=9f790b225963e889c0060c064d996ecd84ee1e84afd0fb62b668b837ccdefc27, image=cdn-in-a-box_smtp, name=cdn-in-a-box_smtp_1)
2023-02-10 02:12:06.334995 container exec_die 1d96b30a6448b3ac84b62bb2ec42fbc1ae0b85c31fe4bda964be79a5c276a555 (execID=9f790b225963e889c0060c064d996ecd84ee1e84afd0fb62b668b837ccdefc27, exitCode=0, image=cdn-in-a-box_smtp, name=cdn-in-a-box_smtp_1)

```

### 対象のイメージを確認する
```
$ docker-compose -f ./docker-compose.yml images
          Container                     Repository            Tag       Image Id       Size  
---------------------------------------------------------------------------------------------
cdn-in-a-box_db_1               cdn-in-a-box_db              latest   69f09e5099b1   177.3 MB
cdn-in-a-box_dns_1              cdn-in-a-box_dns             latest   c0689fe37182   152.6 MB
cdn-in-a-box_edge_1             edge-debug                   latest   7efb9303af6a   900 MB  
cdn-in-a-box_enroller_1         enroller-debug               latest   c6c81aa0db66   228.6 MB
cdn-in-a-box_influxdb_1         cdn-in-a-box_influxdb        latest   7e13dd3ec4d6   290.8 MB
cdn-in-a-box_mid-01_1           mid-debug                    latest   7f56d7f2a949   900 MB  
cdn-in-a-box_mid-02_1           mid-debug                    latest   7f56d7f2a949   900 MB  
cdn-in-a-box_origin_1           cdn-in-a-box_origin          latest   55e8ecbc2fc9   32.15 MB
cdn-in-a-box_smtp_1             cdn-in-a-box_smtp            latest   f3e85572facf   112.2 MB
cdn-in-a-box_static_1           cdn-in-a-box_static          latest   9c6da911d0e6   62.71 MB
cdn-in-a-box_trafficmonitor_1   trafficmonitor-debug         latest   775cc164b8fb   342.3 MB
cdn-in-a-box_trafficops_1       trafficops-debug             latest   8a4864aaad5b   574.3 MB
cdn-in-a-box_trafficportal_1    trafficportal                latest   54514c3c8de8   468.5 MB
cdn-in-a-box_trafficrouter_1    cdn-in-a-box_trafficrouter   latest   0e997c146518   1.079 GB
cdn-in-a-box_trafficstats_1     trafficstats-debug           latest   0758f975e6ce   360.9 MB
```

### dockerのビルドから起動(バックグランド実行)までを実施する
```
$ docker-compose up -d --build
```

### docker-composeのイメージを作成する
```
$ docker-compose build
db uses an image, skipping
Building web ......
```

### docker-composeのコンテナを作成する
```
$ docker-compose create
```

### 1つのサービスを開始する
runは1つのサービスだけを開始します。まとめて開始する場合にはupを付与してください。
imageの構築、コンテナの構築、コンテナの起動までの一連を実行しますが、必ずコンテナ名を指定してください。
```
$ docker-compose run container1 /bin/bash
```

### コンテナを開始します
```
$ docker-compose start
```

### コンテナを停止します
```
$ docker-compose stop
```

### コンテナを再起動します
```
$ docker-compose restart
```

### コンテナを一時停止・一時停止から復帰する
サービスを一時停止します。
一時停止したサービスは強制削除、強制開始ができずunpauseをしてからでないと作業ができなくなるので注意してください。
```
$ docker-compose pause
```

なお、一時停止からの復帰はunpauseを使います。
```
$ docker-compose unpause
```

### コンテナを強制終了します
```
$ docker-compose kill
```

### 停止中のコンテナを削除します
なお、-fオプションを付与することで確認せずに削除してくれます。
```
$ docker-compose rm
```

### docker-compose.yamlに記述されたイメージをpullする
```
$ docker-compose pull
```

### イメージをpushする (docker loginを事前にしておく必要がある)
```
$ docker-compose push <サービス名>
```

### コンテナでプロセスを実行する
サービス名を指定することで特定のコンテナに入ることができます。
```
$ docker-compose exec container1 /bin/bash
```

### 各種ファイルを変更した場合に反映するために必要なコマンドについて
docker-compose.yml, Dockerfile, ソースコード変更などに従って何のコマンドが必要かについて整理してくれています。
- https://qiita.com/subretu/items/5857628534b53f29f5a3

### コンテナをリビルドする
Dockerfileやdocker-compose.ymlの内容を更新した場合にはno-cacheオプションを付与すると良いらしい。

以下は全てのリビルドをキャッシュを使わずに実施する
```
$ docker-compose build --no-cache
```

強制的に全コンテナを再作成し立ち上げする
```
$ docker-compose up -d --build --force-recreate
```

コンテナ名を指定することも可能です。
```
$ docker-compose up -d --build --force-recreate container1
```

上記だけだとボリュームなどが反映されないケースがあるみたいです。


### 滅びのコマンドを実行する
docker-composeで以下の処理を一括で実施したい場合
- コンテナ止める
- ネットワーク削除する
- ボリューム削除する
- イメージ削除する

up したコンテナ群を停止し ネットワーク、ボリューム、イメージを全て削除します。
```
$ docker-compose down --rmi all --volumes
```

### 設定ファイルdocker-compose.ymlに記述されている内容を表示する(変数がファイルで指定されているものは展開されている)

```
$ docker-compose config
services:
  db:
    build:
      context: /Users/tsuyoshi/trafficcontrol/infrastructure/cdn-in-a-box
      dockerfile: traffic_ops/Dockerfile-db
    depends_on:
      dns:
        condition: service_started
    domainname: infra.ciab.test
    environment:
      AUTO_SNAPQUEUE_ACTION_WAIT: '2'
      AUTO_SNAPQUEUE_ENABLED: "true"
      AUTO_SNAPQUEUE_POLL_INTERVAL: '2'
      AUTO_SNAPQUEUE_SERVERS: trafficops,trafficmonitor,trafficrouter,edge,mid-01,mid-02
      CDN_NAME: CDN-in-a-Box
      CDN_SUBDOMAIN: mycdn
      DBIC_TRACE: '0'
      DB_NAME: traffic_ops
      DB_PORT: '5432'
      DB_SERVER: db

(snip)
```

### バージョンを表示する
```
$ docker-compose version
docker-compose version 1.29.2, build 5becea4c
docker-py version: 5.0.0
CPython version: 3.9.0
OpenSSL version: OpenSSL 1.1.1h  22 Sep 2020
```

# ヘルプを表示する
### docker-composeのヘルプ
```
$ docker-compose -h
Define and run multi-container applications with Docker.

Usage:
  docker-compose [-f <arg>...] [--profile <name>...] [options] [--] [COMMAND] [ARGS...]
  docker-compose -h|--help

Options:
  -f, --file FILE             Specify an alternate compose file
                              (default: docker-compose.yml)
  -p, --project-name NAME     Specify an alternate project name
                              (default: directory name)
  --profile NAME              Specify a profile to enable
  -c, --context NAME          Specify a context name
  --verbose                   Show more output
  --log-level LEVEL           Set log level (DEBUG, INFO, WARNING, ERROR, CRITICAL)
  --ansi (never|always|auto)  Control when to print ANSI control characters
  --no-ansi                   Do not print ANSI control characters (DEPRECATED)
  -v, --version               Print version and exit
  -H, --host HOST             Daemon socket to connect to

  --tls                       Use TLS; implied by --tlsverify
  --tlscacert CA_PATH         Trust certs signed only by this CA
  --tlscert CLIENT_CERT_PATH  Path to TLS certificate file
  --tlskey TLS_KEY_PATH       Path to TLS key file
  --tlsverify                 Use TLS and verify the remote
  --skip-hostname-check       Don't check the daemon's hostname against the
                              name specified in the client certificate
  --project-directory PATH    Specify an alternate working directory
                              (default: the path of the Compose file)
  --compatibility             If set, Compose will attempt to convert keys
                              in v3 files to their non-Swarm equivalent (DEPRECATED)
  --env-file PATH             Specify an alternate environment file

Commands:
  build              Build or rebuild services
  config             Validate and view the Compose file
  create             Create services
  down               Stop and remove resources
  events             Receive real time events from containers
  exec               Execute a command in a running container
  help               Get help on a command
  images             List images
  kill               Kill containers
  logs               View output from containers
  pause              Pause services
  port               Print the public port for a port binding
  ps                 List containers
  pull               Pull service images
  push               Push service images
  restart            Restart services
  rm                 Remove stopped containers
  run                Run a one-off command
  scale              Set number of containers for a service
  start              Start services
  stop               Stop services
  top                Display the running processes
  unpause            Unpause services
  up                 Create and start containers
  version            Show version information and quit


Docker Compose is now in the Docker CLI, try `docker compose`
```

### docker-compose upのヘルプ

```
使い方: docker-compose up [オプション] [--scale サービス=数...] [サービス...]

オプション:
  -d, --detach               デタッチド・モード: バックグラウンドでコンテナを実行し、新しいコンテナ名を表示
                              --abort-on-container-exit と同時に使えない
   --no-color                 白黒で画面に表示
   --quiet-pull              進捗情報を表示しない
   --no-deps                  リンクしたサービスを起動しない
   --force-recreate           設定やイメージに変更がなくても、コンテナを再作成する
                             --no-recreate と同時に使えません
   --always-recreate-deps    依存関係のあるコンテナを再作成
                             --no-recreate と同時に使えません
   --no-recreate              コンテナが既に存在していれば、再作成しない
                              --force-recreate と同時に使えない
   --no-build                 イメージが見つからなくても構築しない
   --no-start                 作成してもサービスを起動しない
   --build                    コンテナを開始前にイメージを構築する
   --abort-on-container-exit  コンテナが１つでも停止したら全てのコンテナを停止
                              -d と同時に使えない
   --attach-dependencies      依存するコンテナにアタッチ
   -t, --timeout TIMEOUT      アタッチしている、あるいは既に実行中のコンテナを
                              停止する時のタイムアウト秒数を指定 (デフォルト:10 )
  -V, --renew-anon-volumes   以前のコンテナからデータを再利用せず、匿名ボリュームの再作成
   --remove-orphans           Compose ファイルで定義されていないサービス用のコンテナを削除
   --exit-code-from SERVICE   指定されたサービスコンテナの終了コードを返す
                              --abort-on-container-exit の指定を暗に含む
   --scale SERVICE=NUM        SERVICE のインスタンス数を NUM とする
                              Compose ファイルに scale の設定があっても上書きされる
```
- https://docs.docker.jp/compose/reference/up.html
