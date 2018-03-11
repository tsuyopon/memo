# 概要
XDebugはグローバルプラグインとして機能します。plugin.configに「xdebug.so」を追加することですぐに利用できます。
X-Debugというヘッダを付与することでデバッグ情報を合わせて出力させることができます。

X-Debugという文字列を例えば、ATS-My-Dbugという文字列のヘッダ名称に変更したければplugin.configに次のように記述します。
```
xdebug.so –header=ATS-My-Debug
```

# 詳細

### キャッシュの現在の状況が知りたい
```
$ curl -I -H "X-Debug: X-Cache" http://localhost:80/hoge.html
HTTP/1.1 200 OK
Date: Fri, 19 Jan 2018 07:12:21 GMT
Server: ATS/7.1.3
Last-Modified: Tue, 02 Jan 2018 17:42:24 GMT
Accept-Ranges: bytes
Content-Length: 5
Content-Type: text/html; charset=UTF-8
Etag: "5-561ce9f272322"
Age: 46474
Connection: keep-alive
Via: http/1.1 localhost.localdomain (ApacheTrafficServer/7.1.3 [cRs f ])
X-Cache: hit-fresh
```

値の意味は次の通り、
- none: No cache lookup was attempted.
- miss: The object was not found in the cache.
- hit-stale: The object was found in the cache, but it was stale.
- hit-fresh: The object was fresh in the cache.
- skipped: The cache lookup was skipped.

### キャッシュされているキー情報を取得したい
```
$ curl -I -H "X-Debug: X-Cache-Key" http://localhost:80/hoge.html
HTTP/1.1 200 OK
Date: Fri, 19 Jan 2018 07:12:21 GMT
Server: ATS/7.1.3
Last-Modified: Tue, 02 Jan 2018 17:42:24 GMT
Accept-Ranges: bytes
Content-Length: 5
Content-Type: text/html; charset=UTF-8
Etag: "5-561ce9f272322"
Age: 46366
Connection: keep-alive
Via: http/1.1 localhost.localdomain (ApacheTrafficServer/7.1.3 [cRs f ])
X-Cache-Key: http://127.0.0.1:8080/hoge.html
```

### キャッシュの世代を取得する? (TODO: 要確認)
```
$ curl -I -H "X-Debug: X-Cache-Generation" http://localhost:80/hoge.html
HTTP/1.1 200 OK
Date: Fri, 19 Jan 2018 07:12:21 GMT
Server: ATS/7.1.3
Last-Modified: Tue, 02 Jan 2018 17:42:24 GMT
Accept-Ranges: bytes
Content-Length: 5
Content-Type: text/html; charset=UTF-8
Etag: "5-561ce9f272322"
Age: 46548
Connection: keep-alive
Via: http/1.1 localhost.localdomain (ApacheTrafficServer/7.1.3 [cRs f ])
X-Cache-Generation: -1
```

### トランザクションのUUIDを取得する
TSProcessUuidGet()の値を入れている。
```
$ curl -I -H "X-Debug: X-Transaction-id" http://localhost:80/hoge.html
HTTP/1.1 200 OK
Date: Fri, 19 Jan 2018 07:12:21 GMT
Server: ATS/7.1.3
Last-Modified: Tue, 02 Jan 2018 17:42:24 GMT
Accept-Ranges: bytes
Content-Length: 5
Content-Type: text/html; charset=UTF-8
Etag: "5-561ce9f272322"
Age: 46674
Connection: keep-alive
Via: http/1.1 localhost.localdomain (ApacheTrafficServer/7.1.3 [cRs f ])
X-Transaction-ID: 295b9260-abb3-445e-ab44-30c220c5a080-108
```

### 各フックのHTTPSMをたどるのにかかった時間を表す。
```
$ curl -I -H "X-Debug: X-Milestones" http://localhost:80/hoge.html
HTTP/1.1 200 OK
Date: Fri, 19 Jan 2018 07:12:21 GMT
Server: ATS/7.1.3
Last-Modified: Tue, 02 Jan 2018 17:42:24 GMT
Accept-Ranges: bytes
Content-Length: 5
Content-Type: text/html; charset=UTF-8
Etag: "5-561ce9f272322"
Age: 46818
Connection: keep-alive
Via: http/1.1 localhost.localdomain (ApacheTrafficServer/7.1.3 [cRs f ])
X-Milestones: PLUGIN-TOTAL=0.000016183, PLUGIN-ACTIVE=0.000016183, CACHE-OPEN-READ-END=0.000261598, CACHE-OPEN-READ-BEGIN=0.000261598, UA-BEGIN-WRITE=0.000261598, UA-READ-HEADER-DONE=0.000000000, UA-FIRST-READ=0.000000000, UA-BEGIN=0.000000000
```

### Viaの詳細を出力する
proxy.config.http.insert_response_via_str=3の設定としてViaを出力します。
```
$ curl -I -H "X-Debug: Via" http://localhost:80/hoge.html
HTTP/1.1 200 OK
Date: Fri, 19 Jan 2018 07:12:21 GMT
Server: ATS/7.1.3
Last-Modified: Tue, 02 Jan 2018 17:42:24 GMT
Accept-Ranges: bytes
Content-Length: 5
Content-Type: text/html; charset=UTF-8
Etag: "5-561ce9f272322"
Age: 47022
Connection: keep-alive
Via: http/1.1 localhost.localdomain (ApacheTrafficServer/7.1.3 [uScRs f p eN:t cCHi p s ])
```

### デバッグログへの出力を行う
TSHttpTxnDebugSet(txn, 1)が指定されたものとみなす。これはproxy.config.diags.debug.enabled=1も必要とします。
```
$ curl -I -H "X-Debug: Diags" http://localhost:80/hoge.html
```

### 複数のヘッダを一括で指定する
次のヘッダはX-DEbugの全部入り機能です。
```
$ curl -I -H "X-Debug: X-Cache, X-Cache-Key, X-Cache-Generation, X-Transaction-id, X-Milestones, Via, Diags" http://localhost:80/hoge.html
HTTP/1.1 200 OK
Date: Fri, 19 Jan 2018 07:12:21 GMT
Server: ATS/7.1.3
Last-Modified: Tue, 02 Jan 2018 17:42:24 GMT
Accept-Ranges: bytes
Content-Length: 5
Content-Type: text/html; charset=UTF-8
Etag: "5-561ce9f272322"
Age: 46330
Connection: keep-alive
Via: http/1.1 localhost.localdomain (ApacheTrafficServer/7.1.3 [uScRs f p eN:t cCHi p s ])
X-Cache-Key: http://127.0.0.1:8080/hoge.html
X-Cache: hit-fresh
X-Milestones: PLUGIN-TOTAL=0.000025839, PLUGIN-ACTIVE=0.000025839, CACHE-OPEN-READ-END=0.000272080, CACHE-OPEN-READ-BEGIN=0.000272080, UA-BEGIN-WRITE=0.000272080, UA-READ-HEADER-DONE=0.000000000, UA-FIRST-READ=0.000000000, UA-BEGIN=0.000000000
X-Cache-Generation: -1
X-Transaction-ID: 295b9260-abb3-445e-ab44-30c220c5a080-69
```

# TODO
- ドキュメント上には存在しないが、「X-Debug: log-headers」というのも存在するらしいので確認してみるとよさそう

# SeeAlso
- https://docs.trafficserver.apache.org/ja/6.2.x/admin-guide/plugins/xdebug.en.html
- ソースコード
  - https://github.com/apache/trafficserver/blob/master/plugins/xdebug/xdebug.cc
