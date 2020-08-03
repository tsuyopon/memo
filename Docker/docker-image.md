# 概要
docker imageを作成する際のコマンドやDockerfileについてまとめる


# 詳細

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
