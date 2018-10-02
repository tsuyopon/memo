# 概要
nghttp2パッケージを使うと
- HTTP/2クライアント(nghttp)
- HTTP/2サーバ(nghttpd)
- HTTP/2用ベンチマークの提供(h2load)
- HTTP/2プロキシ(nghttpx)

# nghttpセットアップ

### パッケージインストール
Linux
```
$ sudo sh -c 'yum -y install epel-release && yum -y install nghttp2'
```

# nghttp(HTTP/2クライアント)
オプションなどについては以下のマニュアルを参照のこと
- https://nghttp2.org/documentation/nghttp.1.html

### HTTP2でリクエストを行う
nghttpコマンドの引数としてURLを入れて上げるだけでHTTP/2でのリクエストが可能です。
```
$ nghttp https://google.co.jp/
<HTML><HEAD><meta http-equiv="content-type" content="text/html;charset=utf-8">
<TITLE>301 Moved</TITLE></HEAD><BODY>
<H1>301 Moved</H1>
The document has moved
<A HREF="https://www.google.co.jp/">here</A>.
</BODY></HTML>
```

送受信しているデータを表示するのであればnvオプションを付与することで確認できます。
```
$ nghttp -nv https://google.co.jp/
[  0.112] Connected
The negotiated protocol: h2
[  0.186] send SETTINGS frame <length=12, flags=0x00, stream_id=0>
          (niv=2)
          [SETTINGS_MAX_CONCURRENT_STREAMS(0x03):100]
          [SETTINGS_INITIAL_WINDOW_SIZE(0x04):65535]
[  0.186] send PRIORITY frame <length=5, flags=0x00, stream_id=3>
          (dep_stream_id=0, weight=201, exclusive=0)
[  0.186] send PRIORITY frame <length=5, flags=0x00, stream_id=5>
          (dep_stream_id=0, weight=101, exclusive=0)
[  0.186] send PRIORITY frame <length=5, flags=0x00, stream_id=7>
          (dep_stream_id=0, weight=1, exclusive=0)
[  0.186] send PRIORITY frame <length=5, flags=0x00, stream_id=9>
          (dep_stream_id=7, weight=1, exclusive=0)
[  0.186] send PRIORITY frame <length=5, flags=0x00, stream_id=11>
          (dep_stream_id=3, weight=1, exclusive=0)
[  0.186] send HEADERS frame <length=37, flags=0x25, stream_id=13>
          ; END_STREAM | END_HEADERS | PRIORITY
          (padlen=0, dep_stream_id=11, weight=16, exclusive=0)
          ; Open new stream
          :method: GET
          :path: /
          :scheme: https
          :authority: google.co.jp
          accept: */*
          accept-encoding: gzip, deflate
          user-agent: nghttp2/1.31.1
(snip)
```

### HTTPで接続してUpgradeリクエストを送る
```
$ nghttp -uv http://google.co.jp/
[  0.164] Connected
[  0.164] HTTP Upgrade request
GET / HTTP/1.1
host: google.co.jp
connection: Upgrade, HTTP2-Settings
upgrade: h2c
http2-settings: AAMAAABkAAQAAP__
accept: */*
user-agent: nghttp2/1.31.1


[  0.214] HTTP Upgrade response
HTTP/1.1 301 Moved Permanently
Location: http://www.google.co.jp/
Content-Type: text/html; charset=UTF-8
Date: Tue, 02 Oct 2018 20:38:24 GMT
Expires: Thu, 01 Nov 2018 20:38:24 GMT
Cache-Control: public, max-age=2592000
Server: gws
Content-Length: 221
X-XSS-Protection: 1; mode=block
X-Frame-Options: SAMEORIGIN

<HTML><HEAD><meta http-equiv="content-type" content="text/html;charset=utf-8">
<TITLE>301 Moved</TITLE></HEAD><BODY>
<H1>301 Moved</H1>
The document has moved
<A HREF="http://www.google.co.jp/">here</A>.
</BODY></HTML>

[ERROR] HTTP Upgrade failed
Some requests were not processed. total=1, processed=0

```


### HTTP/2でのレスポンスを計測する
```
$ nghttp -ns https://www.yahoo.co.jp
***** Statistics *****

Request timing:
  responseEnd: the  time  when  last  byte of  response  was  received
               relative to connectEnd
 requestStart: the time  just before  first byte  of request  was sent
               relative  to connectEnd.   If  '*' is  shown, this  was
               pushed by server.
      process: responseEnd - requestStart
         code: HTTP status code
         size: number  of  bytes  received as  response  body  without
               inflation.
          URI: request URI

see http://www.w3.org/TR/resource-timing/#processing-model

sorted by 'complete'

id  responseEnd requestStart  process code size request path
 13    +45.30ms       +196us  45.10ms  200   5K /
```

# nghttpd(HTTP/2サーバ)
オプションなどについては以下のマニュアルを参照のこと
- https://nghttp2.org/documentation/nghttpd.1.html

### nghttpdでHTTP/2のサーバを立てる
以下のコマンドを実行するこでHTTP/2サーバを試したい
```
$ mkdir server
$ cd server/
$ openssl genrsa 2048 > server.key
$ openssl x509 -days 3650 -req -signkey server.key < server.csr > server.crt
$ mkdir -p var/html
$ echo "hoge" > var/html/test.html
$ nghttpd -n 5 -d ./var/html/ 8080 server.key server.crt
```

HTTP/2での接続を確認するにはnghttpコマンドで行います。
```
$ nghttp  https://localhost:8080/test.html
[WARNING] Certificate verification failed: Hostname mismatch
hoge
```

### nghttpdでHTTP/2のサーバを立てる(TLSを利用しない)
```
$ nghttpd -n 5 -d ./var/html/ 8080 --no-tls
```


### nghttpdで接続時のデータを表示したい
```
$ nghttpd -v -n 5 -d ./var/html/ 8080 server.key server.crt
spawning thread #0
spawning thread #1
spawning thread #2
spawning thread #3
spawning thread #4
IPv4: listen 0.0.0.0:8080
IPv6: listen :::8080
[ALPN] client offers:
 * h2
 * h2-16
 * h2-14
SSL/TLS handshake completed
The negotiated protocol: h2
[id=1] [  3.516] send SETTINGS frame <length=6, flags=0x00, stream_id=0>
          (niv=1)
          [SETTINGS_MAX_CONCURRENT_STREAMS(0x03):100]
[id=1] [  3.518] recv SETTINGS frame <length=12, flags=0x00, stream_id=0>
          (niv=2)
          [SETTINGS_MAX_CONCURRENT_STREAMS(0x03):100]
          [SETTINGS_INITIAL_WINDOW_SIZE(0x04):65535]
[id=1] [  3.518] recv SETTINGS frame <length=0, flags=0x01, stream_id=0>
          ; ACK
          (niv=0)
[id=1] [  3.518] recv PRIORITY frame <length=5, flags=0x00, stream_id=3>
          (dep_stream_id=0, weight=201, exclusive=0)
[id=1] [  3.518] recv PRIORITY frame <length=5, flags=0x00, stream_id=5>
          (dep_stream_id=0, weight=101, exclusive=0)
[id=1] [  3.518] recv PRIORITY frame <length=5, flags=0x00, stream_id=7>
          (dep_stream_id=0, weight=1, exclusive=0)
[id=1] [  3.518] recv PRIORITY frame <length=5, flags=0x00, stream_id=9>
          (dep_stream_id=7, weight=1, exclusive=0)
[id=1] [  3.518] recv PRIORITY frame <length=5, flags=0x00, stream_id=11>
          (dep_stream_id=3, weight=1, exclusive=0)
[id=1] [  3.518] recv (stream_id=13) :method: GET
[id=1] [  3.518] recv (stream_id=13) :path: /
[id=1] [  3.518] recv (stream_id=13) :scheme: https
[id=1] [  3.518] recv (stream_id=13) :authority: localhost:8080
[id=1] [  3.518] recv (stream_id=13) accept: */*
[id=1] [  3.518] recv (stream_id=13) accept-encoding: gzip, deflate
[id=1] [  3.518] recv (stream_id=13) user-agent: nghttp2/1.31.1
[id=1] [  3.518] recv HEADERS frame <length=38, flags=0x25, stream_id=13>
```

### HTTP/2でクライアントから接続された際のバイナリデータをhexdumpで表示する
hexdumpオプションを付与すると、クライアントから接続があると次のようなダンプを表示します。
```
$ nghttpd -n 5 -d ./var/html/ 8080 --no-tls --hexdump
00000000  50 52 49 20 2a 20 48 54  54 50 2f 32 2e 30 0d 0a  |PRI * HTTP/2.0..|
00000010  0d 0a 53 4d 0d 0a 0d 0a  00 00 0c 04 00 00 00 00  |..SM............|
00000020  00 00 03 00 00 00 64 00  04 00 00 ff ff 00 00 05  |......d.........|
00000030  02 00 00 00 00 03 00 00  00 00 c8 00 00 05 02 00  |................|
00000040  00 00 00 05 00 00 00 00  64 00 00 05 02 00 00 00  |........d.......|
00000050  00 07 00 00 00 00 00 00  00 05 02 00 00 00 00 09  |................|
00000060  00 00 00 07 00 00 00 05  02 00 00 00 00 0b 00 00  |................|
00000070  00 03 00 00 00 2e 01 25  00 00 00 0d 00 00 00 0b  |.......%........|
00000080  0f 82 04 87 61 25 42 57  9d 34 d1 86 41 8a a0 e4  |....a%BW.4..A...|
00000090  1d 13 9d 09 b8 f0 1e 07  53 03 2a 2f 2a 90 7a 8a  |........S.*/*.z.|
000000a0  aa 69 d2 9a c4 c0 57 64  2b 87                    |.i....Wd+.|
000000aa
00000000  00 00 08 07 00 00 00 00  00 00 00 00 00 00 00 00  |................|
00000010  00                                                |.|
```

### デーモンとして起動させたい
-Dオプションがある
```
$ nghttpd -n 5 -d ./var/html/ 8080 server.key server.crt -D
```


# h2load

### HTTP/2サーバのベンチマークを測定する
次の例は8080で可動しているHTTP/2サーバに対して同時並列数10で、合計10000リクエストを送出するベンチマークです。
```
$ h2load -c 10 -n 10000 https://127.0.0.1:8080
starting benchmark...
spawning thread #0: 10 total client(s). 10000 total requests
TLS Protocol: TLSv1.2
Cipher: ECDHE-RSA-AES256-GCM-SHA384
Server Temp Key: ECDH P-256 256 bits
Application protocol: h2
progress: 10% done
progress: 20% done
progress: 30% done
progress: 40% done
progress: 50% done
progress: 60% done
progress: 70% done
progress: 80% done
progress: 90% done
progress: 100% done

finished in 2.65s, 3771.19 req/s, 645.05KB/s
requests: 10000 total, 10000 started, 10000 done, 0 succeeded, 10000 failed, 0 errored, 0 timeout
status codes: 0 2xx, 0 3xx, 10000 4xx, 0 5xx
traffic: 1.67MB (1751520) total, 98.91KB (101280) headers (space savings 91.83%), 1.40MB (1470000) data
                     min         max         mean         sd        +/- sd
time for request:      144us    104.30ms      2.49ms      4.01ms    92.92%
time for connect:    89.51ms     95.26ms     91.30ms      2.15ms    80.00%
time to 1st byte:    94.39ms     97.07ms     95.24ms       985us    80.00%
req/s           :     377.32      389.89      384.03        4.62    60.00%
```

### プロトコルを指定する

pオプションの後に「http/1.1」や「h2c」を指定することができます。
```
$ h2load -p http/1.1 -c 10 -n 10000 https://127.0.0.1:8080
starting benchmark...
spawning thread #0: 10 total client(s). 10000 total requests
TLS Protocol: TLSv1.2
Cipher: ECDHE-RSA-AES256-GCM-SHA384
Server Temp Key: ECDH P-256 256 bits
Application protocol: h2
progress: 10% done
progress: 20% done
progress: 30% done
progress: 40% done
progress: 50% done
progress: 60% done
progress: 70% done
progress: 80% done
progress: 90% done
progress: 100% done

finished in 3.12s, 3204.85 req/s, 548.18KB/s
requests: 10000 total, 10000 started, 10000 done, 0 succeeded, 10000 failed, 0 errored, 0 timeout
status codes: 0 2xx, 0 3xx, 10000 4xx, 0 5xx
traffic: 1.67MB (1751520) total, 98.91KB (101280) headers (space savings 91.83%), 1.40MB (1470000) data
                     min         max         mean         sd        +/- sd
time for request:      145us     94.16ms      2.95ms      4.99ms    91.85%
time for connect:   101.64ms    110.46ms    104.80ms      2.96ms    70.00%
time to 1st byte:   109.09ms    112.93ms    110.61ms      1.13ms    70.00%
req/s           :     320.63      333.88      325.14        4.94    80.00%
```

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
