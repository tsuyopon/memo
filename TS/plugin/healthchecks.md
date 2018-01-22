# 概要
ヘルスチェックプラグインはグローバルプラグインとして動作して、Interceptなプラグインとして機能します。

# 使い方
グローバルプラグインなのでplugin.configに次の1行を追加します。
```
/opt/trafficserver-7.1.x_log/libexec/trafficserver/healthchecks.so /opt/trafficserver-7.1.x_log/etc/trafficserver/healthchecks.conf
```

上記のプラグインの引数として指定されているファイルは設定ファイルです。
以下の設定はヘルスチェック用エントリポイントとして「/__hc」を提供して(ここは"/"であってはならない)、/tmp/statusが存在していれば200を、存在していなければ403をtext/plain形式のMIMEタイプで返却しなさいといった意味になります。
```
$ cat /opt/trafficserver-7.1.x_log/etc/trafficserver/healthchecks.conf
/__hc  /tmp/status  text/plain 200  403
```

```
$ touch /tmp/status
```

アクセスしてみます
```
$ curl -v http://localhost/__hc
* About to connect() to localhost port 80 (#0)
*   Trying ::1...
* 接続を拒否されました
*   Trying 127.0.0.1...
* Connected to localhost (127.0.0.1) port 80 (#0)
> GET /__hc HTTP/1.1
> User-Agent: curl/7.29.0
> Host: localhost
> Accept: */*
> 
< HTTP/1.1 200 OK
< Content-Type: text/plain
< Cache-Control: no-cache
< Content-Length: 0
< Date: Thu, 18 Jan 2018 22:55:36 GMT
< Age: 0
< Connection: keep-alive
< Via: http/1.1 localhost.localdomain (ApacheTrafficServer/7.1.3 [c sSf ])
< Server: ATS/7.1.3
< 
* Connection #0 to host localhost left intact
```

続いて、先程の/tmp/statusを削除してアクセスしてみると404の変化したことを確認できます。
```
$ rm /tmp/status
$ curl -v http://localhost/__hc
* About to connect() to localhost port 80 (#0)
*   Trying ::1...
* 接続を拒否されました
*   Trying 127.0.0.1...
* Connected to localhost (127.0.0.1) port 80 (#0)
> GET /__hc HTTP/1.1
> User-Agent: curl/7.29.0
> Host: localhost
> Accept: */*
> 
< HTTP/1.1 403 Forbidden
< Content-Type: text/plain
< Cache-Control: no-cache
< Content-Length: 0
< Date: Thu, 18 Jan 2018 22:55:43 GMT
< Age: 0
< Connection: keep-alive
< Via: http/1.1 localhost.localdomain (ApacheTrafficServer/7.1.3 [c s f ])
< Server: ATS/7.1.3
< 
* Connection #0 to host localhost left intact
```

# SeeAlso
- https://docs.trafficserver.apache.org/en/latest/admin-guide/plugins/healthchecks.en.html
