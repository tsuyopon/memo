# 概要
dockerについての基本的な内容についてのメモ

dockerのオプションおよび環境変数については以下を参考のこと
- https://docs.docker.jp/engine/reference/commandline/cli.html

基本コマンドについては以下を参考にすること
- https://gist.github.com/tcnksm/7700047

# 詳細

### dockerコマンドの環境変数
```
DOCKER_CONFIG クライアントの設定ファイルの場所。
DOCKER_CERT_PATH 認証鍵ファイルの場所。
DOCKER_DRIVER 使用するグラフドライバ。
DOCKER_HOST デーモンのソケット接続先。
DOCKER_NOWARN_KERNEL_VERSION Docker に対応していない Linux カーネルで警告を出さない。
DOCKER_RAMDISK 'pivot_root' を無効に設定。
DOCKER_TLS_VERIFY Docker で TLS とリモート認証を使う。
DOCKER_CONTENT_TRUST Docker でイメージの署名・確認用のために Notary 使用時に設定。これは、build、create、pull、push、run で --disable-content-trust=false を実行するのと同等
DOCKER_CONTENT_TRUST_SERVER Notary サーバが使う URL を指定。デフォルトはレジストリと同じ URL 。
DOCKER_TMPDIR 一時 Docker ファイルの場所。
```

「Go」ランタイムが利用する環境変数も使えます。特に次のものは便利です。
```
HTTP_PROXY
HTTPS_PROXY
NO_PROXY
```

- 参考: https://docs.docker.jp/engine/reference/commandline/cli.html

### とりあえずdockerを使ってみる
dockerコマンドを使うには次のpackageをインストールするだけ
```
$ sudo apt-get install docker.io
```

dockerコマンドを実行する際にはsudoコマンドを付与する必要があります。
- https://qiita.com/DQNEO/items/da5df074c48b012152ee


今回、適当にdevtoolsetで検索してみました。
```
$ docker search devtoolset
$ docker pull centos/devtoolset-6-toolchain-centos7
```

取得したイメージを確認する
```
$ sudo docker images
REPOSITORY                              TAG                 IMAGE ID            CREATED             SIZE
nginx                                   latest              5a3221f0137b        9 months ago        126MB
centos/devtoolset-6-toolchain-centos7   latest              f1b031cdb220        14 months ago       436MB
dockcross/windows-x64                   latest              ec59f2aa4229        14 months ago       2GB
```

コンテナの作成、起動、アタッチを以下のコマンドで実施する。
```
$ docker run -i -t f1b031cdb220 /bin/bash
bash-4.2$
```

### sudoを使わずにdockerコマンドを使う
この方法はグループに所属するユーザーが事実上のroot権限を持つことになるため、セキュリティには十分配慮が必要です。
```
$ sudo usermod -aG docker <ユーザー名前>
```

上記にしているのは、dockerクライアントは/var/run/docker.sockにアクセスし、docker.sockの所有者はrootでグループはdockerのためです。

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

検索時に特定のタグを指定することもできます。
```
$ docker search centos:latest | more
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

qオプションを付与するとIMAGE IDだけ抽出してくれるようです。
```
$ sudo docker images -q
4c8b3daeb158
b44ce450cb60
```

上記のubuntuは以下の公式レポジトリから確認することができます。
- https://hub.docker.com/\_/ubuntu/

digestsを引数に追加すればDIGEST値も表示してくれるようです。
```
$ docker images --digests

REPOSITORY          TAG                 DIGEST                                                                    IMAGE ID            CREATED
alpine              3.2                 sha256:21e69d5899e4865b647f6a7aeaba3ddf0d0f17c0016b03ed716322c855533ccd   7bed0150ea37        4 weeks ago         5.265 MB
```

### dockerコンテナの作成(runと違い起動はしない)

```
書式
$ sudo docker create -p ホスト(Ubuntu)側のポート:コンテナ側のポート --name 任意のコンテナ名 元にするイメージ名またはイメージID

例
$ sudo docker create -p 8080:3000 --name centos_container_test tera_shin/centos_test:latest
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

### コンテナの中に入る
attachコマンドをもちいる方法とexecコマンドをもちいる方法の２つが存在する。

- attach
  - attachはバックグラウンドで実行しているコンテナをフォアグラウンドにして、コンテナ中で/bin/bashを実行する。  
  - このコマンドでコンテナに入った場合、コンテナから抜けるとコンテナは停止する。
```
書式
$ sudo docker attach コンテナ名またはコンテナID

例
$ sudo docker attach centos_container_test
```

- exec
  - execを使うことで稼働中のコンテナにコマンドを実行させることができます。
  - execはbash以外にも任意のコマンドをコンテナ内で実行させることができる。  
  - このコマンドでコンテナに入った場合、コンテナから抜けてもコンテナは停止しない。
```
書式
$ sudo docker exec -i -t コンテナ名またはコンテナID bash

例
$ sudo docker exec -i -t centos_container_test bash  
```

### コンテナでちょっとした簡単なコマンドを実行する
例えばtestcontainerコンテナ中でtopコマンドを実行したいといった場合には以下のコマンドを実行します。
```
$ sudo docker exec -it testcontainer /bin/bash -c 'top'
```

### dockerの停止
```
$ docker stop dbb4bbe0f470
```

以下は２秒後に停止させる
```
$ docker stop -t 2 dbb4bbe0f470
```

### dockerの再起動
```
$ docker restart dbb4bbe0f470
```

### dockerの一時停止と再開
pauseオプションの引数にコンテナ名を指定すると一時停止できる。
```
$ docker pause dbb4bbe0f470
```

再開するにはunpauseオプションを指定する
```
$ docker unpause dbb4bbe0f470
```

### 動作中のコンテナの強制終了
killを使うことで動作中のコンテナを強制終了できるようです。(自分はまだこれを使う場面に遭遇したことない)
```
$ docker kill dbb4bbe0f470
```

なお、sオプションでシグナルを指定することができるようです。
```
-s, --signal="KILL": コンテナに送るシグナル
```

### docker psのオプションについて
色々なオプションがあります。
```
-a, --all=false: すべてのコンテナを表示する。デフォルトでは動作中のものだけが表示される。
--before="": IDまたは名前で指定されたコンテナより前に作られたコンテナだけを表示する。停止中のものも表示される。
-l, --latest=false: 最後に作られたコンテナだけを表示する。停止中のものも表示される。
-n=-1: 最後からｎ番目に作られたコンテナだけを表示する。停止中のものも表示される。
--no-trunc=false: 出力を切り詰めない
-q, --quiet=false: 数字のIDのみを表示する
-s, --size=false: サイズを表示する。-q といっしょには指定できない。
--since="": IDまたは名前で指定されたコンテナより後に作られたコンテナだけを表示する。停止中のものも表示される。
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

### dockerにディレクトリやファイルをコピーしたい
以下はtestdockerという名称で名前をつけたdockerに対するコピーです。
ディレクトリでもrなどのオプションは付与する必要はないようです。
```
$ docker cp directory testdocker:/home/tsuyoshi/directory
```

### 最後に起動したコンテナから数えてN個のコンテナを表示する。
以下は２つの場合の例です。
```
$ docker ps -n=2
```

### CONTAINERIDの情報を切り詰めずに表示する
```
$ docker ps --no-trunc
CONTAINER ID                                                       IMAGE               COMMAND             CREATED             STATUS              PORTS               NAMES
1fb337af7fce551181dcc8b4470bb76b45e3c9e69ecc7cb58d0625d74782c742   golang              "/bin/sh"           25 hours ago        Up 25 hours                             attack
```

### サイズを確認する
ps -sの出力は右側にSIZEが追加されていることを確認できます。
```
$ docker ps -s
CONTAINER ID        IMAGE               COMMAND             CREATED             STATUS              PORTS               NAMES               SIZE
1fb337af7fce        golang              "/bin/sh"           25 hours ago        Up 25 hours                             attack              0B (virtual 810MB)
```

### 最後に作られたコンテナのみを表示する
```
$ docker ps -l
CONTAINER ID        IMAGE               COMMAND             CREATED             STATUS              PORTS               NAMES
1fb337af7fce        golang              "/bin/sh"           25 hours ago        Up 25 hours                             attack
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

### コンテナが停止するまで待つ
引数にはコンテナを指定します。
```
$ docker wait e0c1f3850bd7
```

### コンテナとの差分を確認する
diffオプションにコンテナIDを指定することで既存のコンテナとの差分ファイルを表示してくれます。
```
$ docker diff e0c1f3850bd7
C /root
A /root/.vim
A /root/.vim/pack
A /root/.vim/pack/plugins
A /root/.vim/pack/plugins/start
A /root/.vim/pack/plugins/start/vim-go
A /root/.vim/pack/plugins/start/vim-go/.editorconfig
```

### 指定したコンテナIDの統計情報を表示する
CPUはコア数によるので100%を超えることがあることに注意です。コア数が2ならば最大200%となるようです。
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
docker inspectの引数はコンテナまたはIMAGEを指定することができます。
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

渡されている環境変数を調べる
```
$ docker inspect 6572058effff |jq '.[].Config.Env'
```

どのイメージが起動したかを調べる
```
$ docker inspect 6572058effff |jq '.[].Image'
```

### コンテナ内部からコンテナIDを取得する
/etc/hostnameをcatすればいけるらしい
```
$ cat /etc/hostname
7b9fc2c0bc4f
```

### コンテナなどの使用容量を調べる
```
$ docker system df
TYPE                TOTAL               ACTIVE              SIZE                RECLAIMABLE
Images              2                   0                   2.121GB             2.121GB (100%)
Containers          0                   0                   0B                  0B
Local Volumes       0                   0                   0B                  0B
Build Cache         0                   0                   0B                  0B
```

### 標準出力の内容をコンテナの外部から確認する

logという名称ですが、標準出力の内容をコンテナ外から確認するためのものです。

実行したコマンドやその出力結果が表示されます。
```
$ docker logs -f 73c79dda19b7 -t
2020-05-21T18:46:03.559197332Z bash-4.2$ cat /etc/host
2020-05-21T18:46:03.560659106Z cat: /etc/host: No such file or directory
2020-05-21T18:46:04.822444767Z bash-4.2$ cat /etc/hostname 
2020-05-21T18:46:04.823714199Z 73c79dda19b7
2020-05-21T18:46:40.879520861Z bash-4.2$ exit
```

他にもオプションがあります。
```
$ docker logs <containerID>
$ docker logs -f <containerID>
$ docker logs -tail 10 <containerID>
$ docker logs -tail 10 -f <containerID>
```

以下のオプションと意味を記載します。
```
-f, --follow=false: 表示が終わっても終了せず、ログファイルを開いたままにする
-t, --timestamps=false: タイムスタンプを表示する
```

### docker で Ctrl-p ２回押し問題

デフォルトでは Ctrl-p は、detachKeys の一部として認識されていて、コンテナにこのキーを送るには、 Ctrl-p を２度押しする必要がある。
docker v.1.10.0 から、 detachKeys を変更する機能が実装されたので、これを回避するには次の設定を配置すれば良い。
```
// ~/.docker/config.json
{
    "detachKeys": "ctrl-\\"
}
```

- 参考
  - https://qiita.com/Yuki-Inoue/items/60ec916383025160fbb8#_reference-a2d9244a6c4496f4df05

### ブラウザ上でdocker runを試すことができるサービス
- https://docker-run.com/

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
