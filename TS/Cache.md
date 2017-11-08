# 概要
cache方法についてまとめていきます

以下のドキュメントも参照してください。
- https://docs.trafficserver.apache.org/ja/latest/admin-guide/configuration/cache-basics.en.html

# 詳細

### 全キャッシュを削除する
停止して次を実行してから再開するとよい
```
$ traffic_server -Cclear
```

### 特定のキャッシュをクリアする
URLのハッシュをキーとして持つのでPURGEリクエストを出せばよい。
```
$ curl -X PURGE -H 'Host: example.com' -v "http://localhost/remove_me.jpg"
* About to connect() to localhost port 80 (#0)
* Trying 127.0.0.1... connected
* Connected to localhost (127.0.0.1) port 80 (#0)

> PURGE /remove_me.jpg HTTP/1.1
> User-Agent: curl/7.19.7
> Host: example.com
> Accept: */*
>
< HTTP/1.1 200 Ok
< Date: Thu, 08 Jan 2010 20:32:07 GMT
< Connection: keep-alive
```
