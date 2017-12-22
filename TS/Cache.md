# 概要
cache方法についてまとめていきます

以下のドキュメントも参照してください。
- https://docs.trafficserver.apache.org/ja/latest/admin-guide/configuration/cache-basics.en.html

# 詳細

### ヘッダによるキャッシュ有無の制御設定
次の設定値によってキャッシュの動作を変更する
```
proxy.config.http.cache.required_headers
```

デフォルトの動作は2となっているようだ。
- 0: キャッシュさせるためにはどのヘッダも必要としない
- 1: Last-Modifiedまたは明示的な(Expires, Cache-Control: max-age)が必要となる
- 2: ExpiresヘッダやCache-Control: max-ageなどの明示的なlifetimeを必要とする

- https://docs.trafficserver.apache.org/ja/5.3.x/reference/configuration/records.config.en.html#proxy-config-http-cache-required-headers

### 全キャッシュを削除する
trafficserverを一時停止してからキャッシュクリアを行います。
```
$ sudo service trafficserver stop
$ traffic_server -Cclear
$ sudo service trafficserver start
```

- See
  - https://docs.trafficserver.apache.org/en/latest/admin-guide/storage/index.en.html#clearing-the-cache

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

### キャッシュのキーの持ち方を変更する
キャッシュはURL情報をkeyとして決定していますが、 CacheURL Pluginというプラグインを利用することでキャッシュするkeyを変更することができます。
ただし、trafficserverのドキュメントで見るとこのCacheURLプラグインは6.2でdeprecate扱いで、7.0で削除されている。7.0以降は次に示すcachekeyプラグインを利用することになっているようだ。
- https://docs.trafficserver.apache.org/en/6.2.x/admin-guide/plugins/cachekey.en.html#admin-plugins-cachekey

- See
  - https://docs.trafficserver.apache.org/en/6.2.x/admin-guide/plugins/cacheurl.en.html
