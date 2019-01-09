# 概要
dockerについてのメモ

基本コマンドについては以下を参考にすること
- https://gist.github.com/tcnksm/7700047

# 詳細

### インストール
dockerコマンドを使うには次のpackageをインストールするだけ
```
$ sudo apt-get install docker.io
```

dockerコマンドを実行する際にはsudoコマンドを付与する必要があります。
- - https://qiita.com/DQNEO/items/da5df074c48b012152ee

### dockerコマンドのコマンドライン
以下を参考にするとよさそう
- https://gist.github.com/hotta/69b476ae6662c5ff67f0/

### dockerイメージを取得する
docker pullコマンドを取得する
```
$ sudo docker pull centos
latest: Pulling from centos

6c5159923047: Downloading [=========================>                         ] 37.85 MB/73.39 MB
acec82331181: Download complete 
1c1b67b33c28: Download complete 
```

### 取得したイメージを確認する
取得したイメージは次のようにして確認することができます。
```
$ sudo docker images
REPOSITORY          TAG                 IMAGE ID            CREATED             VIRTUAL SIZE
ubuntu              latest              4c8b3daeb158        2 weeks ago         121.6 MB
ubuntu              14.04               b44ce450cb60        3 weeks ago         188 MB
```
上記のubuntuは以下の公式レポジトリから確認することができます。
- https://hub.docker.com/_/ubuntu/

digestsを引数に追加すればDIGEST値も表示してくれるようです。
```
$ docker images --digests

REPOSITORY          TAG                 DIGEST                                                                    IMAGE ID            CREATED
alpine              3.2                 sha256:21e69d5899e4865b647f6a7aeaba3ddf0d0f17c0016b03ed716322c855533ccd   7bed0150ea37        4 weeks ago         5.265 MB
```

### レポジトリを検索する
- https://hub.docker.com/explore/

### dockerを起動する
次のようにして
- iオプションはそのdocker内でシェルを続行したい場合に付与します。以下にオプションを記します。
- hオプションは名前を付与します。
- tにはイメージを指定します。「docer images」などで指定した「<REPOSITORY>:<IMAGE ID>」を指定します。
```
$ sudo docker run -h spam -i -t ubuntu:b44ce450cb60 /bin/bash
```

起動時に環境変数を指定するeオプションもある。実行時の初期ディレクトリを変更するにはwオプションがある。詳しくは以下を参照のこと
- https://qiita.com/shimo_yama/items/d0c42394689132fcb4b6

### dockerの停止後に破棄する
rmオプションを付与するとコンテナ停止後にコンテナが破棄されます。
```
$ docker run -rm -t -i tsuyopon/hello /bin/bash
```

### dockerのstartとattach
停止しているコンテナを起動するには次のようにします。
```
%  sudo docker start fdb376b21eaf
fdb376b21eaf
%  sudo docker attach fdb376b21eaf
[root@fdb376b21eaf /]# 
```

### 稼働しているコンテナに関するプロセスを表示する
```
$ docker ps -a
CONTAINER ID        IMAGE               COMMAND              CREATED             STATUS                           PORTS               NAMES
b3d815c72f6f        library/node        "sleep 20"           6 minutes ago       Exited (0) 6 minutes ago                             awesome_brattain
52932027642a        library/node        "/bin/bash"          6 minutes ago       Exited (0) 6 minutes ago                             amazing_newton
07398e077972        library/node        "/bin/bash"          56 minutes ago      Exited (127) About an hour ago                       trusting_nash
47490b2b0efc        busybox             "echo hello world"   About an hour ago   Exited (0) About an hour ago                         pensive_elion
```

### 不要なコンテナのプロセスを削除する
先でプロセスを表示していましたが、「47490b2b0efc」のプロセスを削除してみます。
```
$ docker rm 47490b2b0efc
47490b2b0efc
$ docker ps -a
CONTAINER ID        IMAGE               COMMAND             CREATED             STATUS                           PORTS               NAMES
b3d815c72f6f        library/node        "sleep 20"          9 minutes ago       Exited (0) 9 minutes ago                             awesome_brattain
52932027642a        library/node        "/bin/bash"         10 minutes ago      Exited (0) 10 minutes ago                            amazing_newton
07398e077972        library/node        "/bin/bash"         59 minutes ago      Exited (127) About an hour ago                       trusting_nash
```

### 不要なイメージを削除する
"docker ps -a"などで該当のイメージを使っているプロセスが存在しないことを確認してからイメージを削除します。
```
$ docker rmi busybox
Untagged: busybox:latest
Untagged: busybox@sha256:7964ad52e396a6e045c39b5a44438424ac52e12e4d5a25d94895f2058cb863a0
Deleted: sha256:3a093384ac306cbac30b67f1585e12b30ab1a899374dabc3170b9bca246f1444
Deleted: sha256:683f499823be212bf04cb9540407d8353803c25d0d9eb5f2fdb62786d8b95ead
```

### dockerに関する情報を表示する
```
$ docker info
Containers: 4
 Running: 0
 Paused: 0
 Stopped: 4
Images: 2
Server Version: 18.09.0
Storage Driver: overlay2
 Backing Filesystem: extfs
 Supports d_type: true
 Native Overlay Diff: true
Execution Driver: <not supported>
Logging Driver: json-file
Cgroup Driver: cgroupfs
Plugins: 
 Volume: local
 Network: bridge host macvlan null overlay
Kernel Version: 4.14.79-boot2docker
Operating System: Boot2Docker 18.09.0 (TCL 8.2.1)
OSType: linux
Architecture: x86_64
CPUs: 1
Total Memory: 989.4 MiB
Name: default
ID: YNSI:VNJ5:ZCXL:IHRC:TE22:326U:ZPT7:A75H:7HCO:V7VQ:EISA:LAYP
Docker Root Dir: /mnt/sda1/var/lib/docker
Debug mode (client): false
Debug mode (server): false
Registry: https://index.docker.io/v1/
Labels:
 provider=virtualbox
```

### Dockerfileからイメージを作成する
```
$ echo -e "FROM base\nRUN apt-get install hello\nCMD hello" > Dockerfile
$ docker build tsuyopon/hello .
```

### 利用可能なリモートにあるdocker image一覧


### docker hubにpushする
- https://qiita.com/umi/items/d4b5a68263ad0444693b#docker-hub-%E3%81%ABpush-%E3%81%97%E3%81%A6%E3%81%BF%E3%82%8B


試したわけではないが流れだけ記載しておく
- 1. 以下のdocker hubからアカウントを作成します。
  - https://hub.docker.com/explore/
- 2. ログインする
```
$ sudo docker login
```
- 3. タグ付けをする
```
$ sudo docker tag 18247f8cdbc4 ubuntu/mysql:latest
$ sudo docker images
```
- 4.リモートレポジトリにプッシュする
```
$ sudo docker push ubuntu/mysql:latest
```
- 5. docker hubを確認してレポジトリが作成されたことを確認する。

# 参考URL
- docker公式資料
  - https://docs.docker.com/
- docker hub
  - https://hub.docker.com/


### TODO
- dockerレジストリ設定方法
- この辺もまとめる
  - https://qiita.com/bungoume/items/b8911fd243d9c084bd63 
- https://qiita.com/nimusukeroku/items/72bc48a8569a954c7aa2
