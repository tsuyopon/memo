# HTTP/2リバースプロキシ(nghttpx)

### HTTP/2リバースプロキシのサーバを起動する。
たとえば、以下のコマンドではHTTP/2リバースプロキシサーバとして起動します。
リクエストを行うと裏側ではwww.yahoo.co.jp:80へとリクエストを取得します。
```
$ sudo nghttpx server.key server.crt --backend="www.yahoo.co.jp,80" 
2018-10-02T10:10:51.940+09:00 24274 24274 0966062a NOTICE (shrpx.cc:859) Listening on 0.0.0.0:3000, tls
2018-10-02T10:10:51.940+09:00 24274 24274 0966062a NOTICE (shrpx.cc:859) Listening on [::]:3000, tls
2018-10-02T10:10:51.941+09:00 24274 24274 0966062a NOTICE (shrpx.cc:1302) Worker process [24275] spawned
2018-10-02T10:10:51.942+09:00 24274 24274 0966062a NOTICE (shrpx_worker_process.cc:211) Renew new ticket keys
2018-10-02T10:10:51.983+09:00 24274 24274 0966062a NOTICE (shrpx_connection_handler.cc:311) [LISTEN:0x7ffff24395c0] Created worker thread #0
fetch-ocsp-response (using OpenSSL 1.0.2k-fips  26 Jan 2017)
failed to extract ocsp URI from server.crt
2018-10-02T10:10:52.165+09:00 24274 24274 0966062a WARN (shrpx_connection_handler.cc:612) ocsp query command for server.crt failed: error=0, rstatus=ff00, status=255
```

上記だとデフォルトで3000番ポートが起動していますので
```
$ nghttp https://localhost:3000/
```
