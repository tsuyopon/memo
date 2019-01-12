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

特定のバージョンのイメージを取得する場合には次のようにします。
```
$ docker pull ubuntu:12.04
```

### dockerイメージの検索をする
```
$ docker search kernel
```

dockerhubからレポジトリを検索することもできます。
- https://hub.docker.com/explore/

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


### dockerを起動する
次のようにしてdockerを起動します。オプションは省略できるものもあります。
- hオプションは名前を付与します。以下では適当に「spam」という名称を付与します。指定しないとdockerが適当に決定します。
- iオプションはそのdocker内でシェルを続行したい場合に付与します。
- tにはイメージを指定します。「docer images」などで指定した「<REPOSITORY>:<IMAGE ID>」を指定します。
```
$ sudo docker run -h spam -i -t ubuntu:b44ce450cb60 /bin/bash 
```

起動時に環境変数を指定するeオプションもある。実行時の初期ディレクトリを変更するにはwオプションがある。詳しくは以下を参照のこと
- https://qiita.com/shimo_yama/items/d0c42394689132fcb4b6

### dockerをコンテナバックグラウンドで起動する
dオプションによってバックグラウンドで起動させることができます。
```
$ docker run -i -t -d ubuntu /bin/bash
```

### dockerの停止後に破棄する
rmオプションを付与するとコンテナ停止後にコンテナが破棄されます。
```
$ docker run -rm -t -i tsuyopon/hello /bin/bash
```

### dockerのstartとattach
停止しているコンテナを起動して、アタッチするには次のようにします。aオプションがアタッチを意味しています。
```
$ sudo docker start -a fdb376b21eaf
fdb376b21eaf
```

起動中のコンテナにアタッチする。
```
$ sudo docker attach fdb376b21eaf
[root@fdb376b21eaf /]# 
```

### dockerの停止
```
$ docker stop dbb4bbe0f470
```

以下は２秒後に停止させる
```
$ docker stop -t 2 dbb4bbe0f470
```

### 稼働しているコンテナに関するプロセスを表示する
aオプションを付与すると起動していないコンテナも合わせて表示してくれます。
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

### 不要なコンテナのプロセスを一気に削除する
```
$ docker rm `docker ps -aq`
```

### コンテナを全て強制的に削除する
```
$ docker rm -f `docker ps -aq`
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

### 指定したコンテナIDの統計情報を表示する
```
$ docker stats 52932027642a   // コンテナIDを指定する
CONTAINER           CPU %               MEM USAGE / LIMIT     MEM %               NET I/O             BLOCK I/O           PIDS
52932027642a        0.00%               921.6 kB / 1.037 GB   0.09%               1.256 kB / 0 B      0 B / 0 B           1
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

### dockerイメージの履歴を表示する
```
$ docker history node
IMAGE               CREATED             CREATED BY                                      SIZE                COMMENT
72ff1a4450d9        22 hours ago        /bin/sh -c #(nop)  CMD ["node"]                 0 B                 
<missing>           22 hours ago        /bin/sh -c set -ex   && for key in     6A010C   5.057 MB            
<missing>           22 hours ago        /bin/sh -c #(nop)  ENV YARN_VERSION=1.12.3      0 B                 
<missing>           22 hours ago        /bin/sh -c ARCH= && dpkgArch="$(dpkg --print-   59.17 MB            
<missing>           22 hours ago        /bin/sh -c #(nop)  ENV NODE_VERSION=11.6.0      0 B                 
<missing>           22 hours ago        /bin/sh -c groupadd --gid 1000 node   && user   333.4 kB            
<missing>           24 hours ago        /bin/sh -c set -ex;  apt-get update;  apt-get   560.2 MB            
<missing>           12 days ago         /bin/sh -c apt-get update && apt-get install    141.8 MB            
<missing>           12 days ago         /bin/sh -c set -ex;  if ! command -v gpg > /d   7.812 MB            
<missing>           12 days ago         /bin/sh -c apt-get update && apt-get install    23.23 MB            
<missing>           12 days ago         /bin/sh -c #(nop)  CMD ["bash"]                 0 B                 
<missing>           12 days ago         /bin/sh -c #(nop) ADD file:da71baf0d22cb2ede9   100.6 MB     
```

### dockerのバージョン
以下は、MacOS上のVirtualBoxのdocker-machineを利用したdocker versionの出力結果です。
```
$ docker version
Client:
 Version:      1.11.0
 API version:  1.23
 Go version:   go1.5.4
 Git commit:   4dc5990
 Built:        Wed Apr 13 18:13:28 2016
 OS/Arch:      darwin/amd64

Server:
 Version:      18.09.0
 API version:  1.39
 Go version:   go1.10.4
 Git commit:   4d60db4
 Built:        Wed Nov  7 00:52:55 2018
 OS/Arch:      linux/amd64
```

### イメージの詳細を確認する
```
$ docker inspect node
[
    {
        "Id": "sha256:72ff1a4450d95dfd454a2f11606390860e60b9346fc9e06bb3ff7ed333c92fdf",
        "RepoTags": [
            "node:latest"
        ],
        "RepoDigests": [
            "node@sha256:5ea9b2d04e1da959087d93289bdcfa5011c3a173bddf3eaf98553676d28b8f63"
        ],
        "Parent": "",
        "Comment": "",
        "Created": "2019-01-09T02:03:39.87092848Z",
        "Container": "3ee098da50e37eafbd462e8ab93c750bc571189796834277e0e701f848b4b8f9",
        "ContainerConfig": {
            "Hostname": "3ee098da50e3",
            "Domainname": "",
            "User": "",
            "AttachStdin": false,
            "AttachStdout": false,
            "AttachStderr": false,
            "Tty": false,
            "OpenStdin": false,
            "StdinOnce": false,
            "Env": [
                "PATH=/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin",
                "NODE_VERSION=11.6.0",
                "YARN_VERSION=1.12.3"
            ],
            "Cmd": [
                "/bin/sh",
                "-c",
                "#(nop) ",
                "CMD [\"node\"]"
            ],
            "ArgsEscaped": true,
            "Image": "sha256:79b59bf1743d783352b92609cee10a7b582b627d80516fefaeb01cd85139e955",
            "Volumes": null,
            "WorkingDir": "",
            "Entrypoint": null,
            "OnBuild": null,
            "Labels": {}
        },
        "DockerVersion": "18.06.1-ce",
        "Author": "",
        "Config": {
            "Hostname": "",
            "Domainname": "",
            "User": "",
            "AttachStdin": false,
            "AttachStdout": false,
            "AttachStderr": false,
            "Tty": false,
            "OpenStdin": false,
            "StdinOnce": false,
            "Env": [
                "PATH=/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin",
                "NODE_VERSION=11.6.0",
                "YARN_VERSION=1.12.3"
            ],
            "Cmd": [
                "node"
            ],
            "ArgsEscaped": true,
            "Image": "sha256:79b59bf1743d783352b92609cee10a7b582b627d80516fefaeb01cd85139e955",
            "Volumes": null,
            "WorkingDir": "",
            "Entrypoint": null,
            "OnBuild": null,
            "Labels": null
        },
        "Architecture": "amd64",
        "Os": "linux",
        "Size": 898116080,
        "VirtualSize": 898116080,
        "GraphDriver": {
            "Data": {
                "LowerDir": "/mnt/sda1/var/lib/docker/overlay2/2202d564f650eb0399f93a19c313d9f048dcde776fe4bafc5f600cfad1e54bfe/diff:/mnt/sda1/var/lib/docker/overlay2/0378fcce882fb007c2d4795ea792e6661fd69e199805fe1958aa1fa5626c417f/diff:/mnt/sda1/var/lib/docker/overlay2/357323a81613f0463197766ad73f7e9f1f0516795ad24cc609d97b61d72736d6/diff:/mnt/sda1/var/lib/docker/overlay2/dd98ae2f7cbf188743f0a333dd7ea260ab46a94fb1cd2ae76ddf83bf1b8e55fd/diff:/mnt/sda1/var/lib/docker/overlay2/ec591297b855d1fa1551ab28447f1370d6308d2433a0a88e90fc0ff5d71c0b2b/diff:/mnt/sda1/var/lib/docker/overlay2/215a3564416fcfe21730f2659d4daed6aca017c9f7e4cdfddf807a66414a9f3e/diff:/mnt/sda1/var/lib/docker/overlay2/cd91b3dff380959444cf350e1703460cba18886aa60e41dc104509bc58006647/diff",
                "MergedDir": "/mnt/sda1/var/lib/docker/overlay2/dbb935524710f9fb9fe8d2f767bff4c6e1f6c63b7c4b56eba18291af742bad3e/merged",
                "UpperDir": "/mnt/sda1/var/lib/docker/overlay2/dbb935524710f9fb9fe8d2f767bff4c6e1f6c63b7c4b56eba18291af742bad3e/diff",
                "WorkDir": "/mnt/sda1/var/lib/docker/overlay2/dbb935524710f9fb9fe8d2f767bff4c6e1f6c63b7c4b56eba18291af742bad3e/work"
            },
            "Name": "overlay2"
        },
        "RootFS": {
            "Type": "layers",
            "Layers": [
                "sha256:c581f4ede92df7272da388a45126ddd2944a4eeb27d3b0d80ee71cd633761394",
                "sha256:d2518892581f0448058b76313346f0c8a151e3f2b8c5586a9c41451ec31003fb",
                "sha256:b53b57a507464925b0fc2c0d44d2a068771ab1de032f9be70853fff6bcbcd583",
                "sha256:d2217ead3a1cf1853da370297650262868774966c9d5fedb361ceaad7f71dba9",
                "sha256:1a36262221c39a0c014b301801a73e2760cfa2bdad5f91d2e79d67727ab2f065",
                "sha256:8ed6596b2a0a8c4039c52252c89c52d86b14cf66d10f89f2d7ad104e33593c64",
                "sha256:1875c7f9d6595dc602bcc58df3a81206e32ffbbae98df4703d0b2a782808201e",
                "sha256:0ae0970278f47a833376912ca292971dffe3896c808683cd0fa586f512296f9c"
            ]
        },
        "Metadata": {
            "LastTagTime": "0001-01-01T00:00:00Z"
        }
    }
]
```

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
  - https://qiita.com/voluntas/items/68c1fd04dd3d507d4083
