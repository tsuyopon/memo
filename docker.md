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

### TODO
- dockerレジストリ設定方法
- この辺もまとめる
  - https://qiita.com/bungoume/items/b8911fd243d9c084bd63 

# 参考URL
- docker公式資料
  - https://docs.docker.com/
- docker hub
  - https://hub.docker.com/
