# 概要
dockerのログ出力について

# 詳細

### 起動から全てのログをみる
ログを確認したいdockerコンテナID、またはコンテナ名を取得します。
```
$ sudo docker ps -a
```

下記で閲覧できます。ただし、起動時からのログが全て出力されると思います。
以下はコンテナIDを指定していますが、代わりにコンテナ名を指定することもできます。
```
$ sudo docker logs b53d7a03a024 --follow
or
$ sudo docker logs b53d7a03a024 -f
```

### 指定した時刻以降のログを取得する
```
# docker logs --since 2s cont1                   // 2秒前以降のログを表示

# docker logs --since 10m cont1                  // 10分前以降のログを表示

# docker logs --since 2019-09-01T00:00:00 cont1  // 指定時刻以降のログを表示
```
cont1はコンテナ名を表しています(以降同じ)

日時の指定は上記のRFC3339のフォーマットや、UNIX timestamp（1970/1/1からの経過時間（秒））などが使用可能です。

### 指定した時刻以前のログを取得する
```
# docker logs --until 10h cont1                  // 10時間より以前のログを表示

# docker logs --until 2019-09-01T00:00:00 cont1  // 指定時刻以前のログを表示
```
日時の指定は上記のRFC3339のフォーマットや、UNIX timestamp（1970/1/1からの経過時間（秒））などが使用可能です。

### ログの先頭にタイムスタンプを付与する。
ログの先頭にタイムスタンプのprefixが付与されるようになります。
```
2023-02-07T00:32:09.404291952Z INFO: enroller.go:1053: 2023-02-07T00:32:09.404068158Z: new file : /shared/enroller/servers/trafficops.json
```

### ログを最後のN行目から表示させる
-fオプションだけだとたくさんのログがあると最新のログが表示されるまでに非常に時間がかかります。それを解決してくれるのがtailオプションです。

下記は最後の100行だけを取得して終了します。
```
$ docker log --tail 100 test_container
or
$ docker logs -n 100 cont1
```

最後の100行からずっとそのまま出力させるには-fを付与すれば良いです。
```
$ docker log --tail 100 test_container -f
```

