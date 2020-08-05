# 概要
docker volumeについての概要について
ボリュームとは、Docker コンテナーにおいて生成され利用されるデータを、永続的に保持する目的で利用される仕組みです。

volumeについては以下の概要を確認してください。
- https://matsuand.github.io/docs.docker.jp.onthefly/storage/volumes/

volumeについてのオプションは少し複雑で以下のqiitaの記事が理解に役立ちます。
- https://qiita.com/gounx2/items/23b0dc8b8b95cc629f32

# 詳細


### ボリューム

dockerでは通常のファイルシステムをマウントすることもできますが、docker volume createで生成したボリュームをマウントすることもできます。

docker volume createで生成した場合には以下の利点が存在するようです。
- ボリュームはバインドマウントよりも、バックアップや移行が容易です。
- ボリュームは Docker CLI コマンドや Docker API を利用して管理することができます。
- ボリュームは Linux と Windows 上のコンテナーにおいて動作します。
- ボリュームは複数コンテナー間にて安全に共有できます。
- ボリュームドライバーを用いると、リモートホスト上、あるいはクラウドプロバイダー上のボリュームに保存できるようになります。保存の際にはボリューム内データを暗号化することができ、その他にも種々の機能を利用することができます。
- ボリュームを新たに生成すると、その内容はコンテナーがあらかじめ用意していた内容になります。

- 参考
  - https://matsuand.github.io/docs.docker.jp.onthefly/storage/volumes/


## volumeコマンドの実行

### ボリューム作成する
```
$ docker volume create myvol
myvol
```

### ボリューム一覧を表示する
```
$ docker volume ls
DRIVER              VOLUME NAME
local               myvol
```

### ボリュームの情報を確認する
```
$ docker volume inspect myvol
[
    {
        "CreatedAt": "2020-08-03T18:08:55Z",
        "Driver": "local",
        "Labels": {},
        "Mountpoint": "/var/lib/docker/volumes/myvol/_data",
        "Name": "myvol",
        "Options": {},
        "Scope": "local"
    }
]
```

### 作成したボリュームを削除する
```
$ docker volume rm myvol
myvol
$  docker volume ls
DRIVER              VOLUME NAME
```

# TODO
以下の資料を読み込む
- https://matsuand.github.io/docs.docker.jp.onthefly/storage/volumes/
