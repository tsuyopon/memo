# 概要
docker imageを作成する際のコマンドやDockerfileについてまとめる

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
