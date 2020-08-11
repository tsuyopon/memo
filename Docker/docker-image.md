# 概要
docker imageを作成する際のコマンドやDockerfileについてまとめる
主にimage作成に関する操作で必要なものについてはこちらでまとめる。その他についてはdocker.mdなども別途参照のこと

# 詳細

### 現在のサポートするストレージドライバを確認する
docker infoで確認することができます。
```
$ docker info | grep 'Storage Driver'
 Storage Driver: overlay2
```

なお、dockerでは以下のストレージドライバがサポートされていて、利用している環境や用途に応じてベストなドライバを選択できます。
```
overlay2, overlay
aufs
btrfs
devicemapper
vfs
zfs
```

### Dockerイメージ内部のレイヤ構造を確認する
以下の例ではdocker imageで出力されるnginxのイメージの履歴を表示しています。
以下の例では11個のレイヤが重なっていることが確認できます。
```
$ docker history nginx
IMAGE               CREATED             CREATED BY                                      SIZE                COMMENT
5a3221f0137b        11 months ago       /bin/sh -c #(nop)  CMD ["nginx" "-g" "daemon…   0B                  
<missing>           11 months ago       /bin/sh -c #(nop)  STOPSIGNAL SIGTERM           0B                  
<missing>           11 months ago       /bin/sh -c #(nop)  EXPOSE 80                    0B                  
<missing>           11 months ago       /bin/sh -c ln -sf /dev/stdout /var/log/nginx…   22B                 
<missing>           11 months ago       /bin/sh -c set -x     && addgroup --system -…   56.8MB              
<missing>           11 months ago       /bin/sh -c #(nop)  ENV PKG_RELEASE=1~buster     0B                  
<missing>           11 months ago       /bin/sh -c #(nop)  ENV NJS_VERSION=0.3.5        0B                  
<missing>           11 months ago       /bin/sh -c #(nop)  ENV NGINX_VERSION=1.17.3     0B                  
<missing>           11 months ago       /bin/sh -c #(nop)  LABEL maintainer=NGINX Do…   0B                  
<missing>           11 months ago       /bin/sh -c #(nop)  CMD ["bash"]                 0B                  
<missing>           11 months ago       /bin/sh -c #(nop) ADD file:330bfb91168adb4a9…   69.2MB   
```

### イメージレイヤのゴミ問題
RUNに1行でapt-get updateとcleanを一緒に書かないと実は削除の上書きをしているだけで、レイヤにゴミが残ってしまう問題。
詳細は以下を参考のこと

- 参考
  - https://www.techscore.com/blog/2018/12/10/docker-images-and-layers/

### コンテナからイメージを作成する

"docker ps -a"で閲覧できるコンテナからイメージを生成することができます。
```
書式
$ sudo docker commit [コンテナ名 or コンテナID]  [DockerHubユーザー名/任意のイメージ名]
```

statusがExitedで停止しているものからイメージを生成します。ここでの例としてamazing_jones(e0c1f3850bd7)のイメージを生成します。
```
$ docker ps -a
CONTAINER ID        IMAGE               COMMAND             CREATED             STATUS                      PORTS               NAMES
e0c1f3850bd7        a794da9351a3        "/bin/bash"         8 days ago          Exited (127) 8 days ago                         amazing_jones
42a1b2fed60f        a794da9351a3        "/bin/bash"         8 days ago          Exited (0) 8 days ago                           bold_keldysh
```

commitする場合には「CONTAINER ID」か「NAMES」をcommitの後に指定して、その後に「hoge:test」というのは「DockerHubユーザー名/任意のイメージ名」を指定します。
```
$ docker commit amazing_jones hoge:test
sha256:c8386525d3bdda9ac65b48788ff930f71eb3fe7446b4f386c3fd13af8618db6d
$ sudo docker images
REPOSITORY                              TAG                 IMAGE ID            CREATED             SIZE
hoge                                    test                c8386525d3bd        6 seconds ago       817MB
golang                                  latest              a794da9351a3        11 days ago         810MB
```


### Dockerfileからイメージを作成する(非常に簡単な例)
以下は非常に簡単な例です。
```
$ echo -e "FROM base\nRUN apt-get install hello\nCMD hello" > Dockerfile
$ docker build tsuyopon/hello .
```

### Dockerfileについて

- FROM: ベースイメージを指定する
- RUN: コマンドを実行する
- CMD:
- ENTRYPOINT: 
- MAINTAINER: 管理者の情報を指定する



CMDとENTRYPOINTは1つのDockerfileに1つしか指定されたものが実行されないようです。
- 参考: https://qiita.com/hihihiroro/items/d7ceaadc9340a4dbeb8f


### dockerイメージの履歴を表示する
dockerは1つ1つのコマンドの階層で表されています。
これらのログは階層を表すコマンド1つ１つを表しています。
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

### docker save+load とdocker export+importの違いについて

以下の記事が参考になります。
- https://qiita.com/leomaro7/items/e5474e67a8e41536f0ff

次の違いがあるようです。
- saveはイメージを保存
- exportはコンテナを保存

saveはレイヤの情報なども含めた状態で保存されます。しかし、exportではDockerとしての構造やメタ情報は保存されず、ファイルシステムだけが保存されます。


### docker hubにアップロードする
コンテナからImageIDをcommitによって生成して、その時生成されたImageIDからタグを生成する。
タグを使ってdocker hubにpushする
```
$ docker commit test_container                                   // test_containerの箇所はコンテナ名かコンテナIDを指定する
$ docker images -a                                               // 生成したImageIDを確認する
$ docker tag 057cb8323f88 tsuyopon1981/openssl111trace:latest    //  057cb8323f88はImage IDの例です。 
$ docker login                                                   // docker hubのIDとパスワードでログインする
$ docker push tsuyopon1981/openssl111trace:latest                // docker hubにpushする
```

以上によりdocker hubにアップロードされる。
- https://hub.docker.com/repository/docker/tsuyopon1981/openssl111trace

