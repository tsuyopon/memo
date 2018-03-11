# 概要
traffic_viaやViaヘッダに関連する事項についてまとめる　

# 詳細

### traffic_viaコマンドによる状態解析をしたい
curlコマンドでリクエストするとViaヘッダが取得できます。　
```
$ curl -v http://localhost:80/hoge.html
* About to connect() to localhost port 80 (#0)
*   Trying ::1...
* 接続を拒否されました
*   Trying 127.0.0.1...
* Connected to localhost (127.0.0.1) port 80 (#0)
> GET /hoge.html HTTP/1.1
> User-Agent: curl/7.29.0
> Host: localhost
> Accept: */*
> 
< HTTP/1.1 200 OK
< Date: Fri, 19 Jan 2018 07:12:21 GMT
< Server: ATS/7.1.3
< Last-Modified: Tue, 02 Jan 2018 17:42:24 GMT
< Accept-Ranges: bytes
< Content-Length: 5
< Content-Type: text/html; charset=UTF-8
< Etag: "5-561ce9f272322"
< Age: 57842
< Connection: keep-alive
< Via: http/1.1 localhost.localdomain (ApacheTrafficServer/7.1.3 [cRs f ])
< 
hoge
* Connection #0 to host localhost left intact
```

上記ヘッダは次のようにして解析することができます。
```
$ /opt/trafficserver-7.1.x_log/bin/traffic_via "cRs f "
Via header is cRs f , Length is 6
Via Header Details:
Result of Traffic Server cache lookup for URL          :in cache, fresh Ram hit (a cache "HIT")
Response information received from origin server       :no server connection needed
Result of document write-to-cache:                     :no cache write performed
```

traffic_viaについては以下に公式ドキュメントが有ります
- https://docs.trafficserver.apache.org/ja/latest/appendices/command-line/traffic_via.en.html

### Viaの詳細なヘッダを解析する
proxy.config.http.insert_response_via_str=3のVia出力、またはxdebug.soのプラグインとX-Debugヘッダを指定して出力されるViaを取得する。
```
$ curl -v -H "X-Debug: Via" http://localhost:80/hoge.html
* About to connect() to localhost port 80 (#0)
*   Trying ::1...
* 接続を拒否されました
*   Trying 127.0.0.1...
* Connected to localhost (127.0.0.1) port 80 (#0)
> GET /hoge.html HTTP/1.1
> User-Agent: curl/7.29.0
> Host: localhost
> Accept: */*
> X-Debug: Via
> 
< HTTP/1.1 200 OK
< Date: Fri, 19 Jan 2018 07:12:21 GMT
< Server: ATS/7.1.3
< Last-Modified: Tue, 02 Jan 2018 17:42:24 GMT
< Accept-Ranges: bytes
< Content-Length: 5
< Content-Type: text/html; charset=UTF-8
< Etag: "5-561ce9f272322"
< Age: 57607
< Connection: keep-alive
< Via: http/1.1 localhost.localdomain (ApacheTrafficServer/7.1.3 [uScRs f p eN:t cCHi p s ])
< 
hoge
```

上記で取得するヘッダをtraffic_viaにかけると非常に詳細なtraffic_viaの内容を取得することができます。
```
$ /opt/trafficserver-7.1.x_log/bin/traffic_via "uScRs f p eN:t cCHi p s "
Via header is uScRs f p eN:t cCHi p s , Length is 24
Via Header Details:
Request headers received from client                   :simple request (not conditional)
Result of Traffic Server cache lookup for URL          :in cache, fresh Ram hit (a cache "HIT")
Response information received from origin server       :no server connection needed
Result of document write-to-cache:                     :no cache write performed
Proxy operation result                                 :unknown
Error codes (if any)                                   :no error
Tunnel info                                            :no tunneling
Cache Type                                             :cache
Cache Lookup Result                                    :cache hit
ICP status                                             :no icp
Parent proxy connection status                         :no parent proxy or unknown
Origin server connection status                        :no server connection needed
```

### Viaに表示される記号の説明ドキュメント
- https://docs.trafficserver.apache.org/en/latest/appendices/faq.en.html#how-do-i-interpret-the-via-header-code

### trafficserverサイトにViaヘッダを解析する簡単なツールがあります。
- http://trafficserver.apache.org/tools/via

### Viaヘッダのシンボルが定義されているソースコード箇所を確認したい
以下は7.1.xです。
- https://github.com/apache/trafficserver/blob/7.1.x/proxy/http/HttpTransact.h#L145-L228
