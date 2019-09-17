# 概要
nghttpコマンドを使うことで、nghttp2ライブラリを利用してHTTP/2クライアントとしてリクエストを実行させることができます。

# 詳細

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

### 送受信している内容を詳細に表示する。ただし、レスポンスボディは出力のノイズになるので省略する。
送受信しているデータを表示するのであればnvオプションを付与することで確認できます。
nはボディを省略、vは詳細を表示します。
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

### methodを変更したり、ヘッダを変更、追加する
```
$ nghttp -v https://www.yahoo.co.jp -H ':method: HEAD' -H 'user-agent: hogeua' -H 'x-header: test'
(snip)
[  0.067] send HEADERS frame <length=52, flags=0x25, stream_id=13>
          ; END_STREAM | END_HEADERS | PRIORITY
          (padlen=0, dep_stream_id=11, weight=16, exclusive=0)
          ; Open new stream
          :method: HEAD
          :path: /
          :scheme: https
          :authority: www.yahoo.co.jp
          accept: */*
          accept-encoding: gzip, deflate
          user-agent: hogeua
          x-header: test
[  0.079] recv SETTINGS frame <length=0, flags=0x01, stream_id=0>
          ; ACK
          (niv=0)
[  0.116] recv (stream_id=13) :status: 200
[  0.116] recv (stream_id=13) date: Sat, 14 Sep 2019 00:42:30 GMT
[  0.116] recv (stream_id=13) p3p: policyref="http://privacy.yahoo.co.jp/w3c/p3p_jp.xml", CP="CAO DSP COR CUR ADM DEV TAI PSA PSD IVAi IVDi CONi TELo OTPi OUR DELi SAMi OTRi UNRi PUBi IND PHY ONL UNI PUR FIN COM NAV INT DEM CNT STA POL HEA PRE GOV"
[  0.116] recv (stream_id=13) x-content-type-options: nosniff
[  0.116] recv (stream_id=13) x-xss-protection: 1; mode=block
[  0.116] recv (stream_id=13) x-frame-options: SAMEORIGIN
[  0.116] recv (stream_id=13) expires: -1
[  0.116] recv (stream_id=13) pragma: no-cache
[  0.116] recv (stream_id=13) cache-control: private, no-cache, no-store, must-revalidate
[  0.116] recv (stream_id=13) content-type: text/html; charset=UTF-8
[  0.116] recv (stream_id=13) age: 0
[  0.116] recv (stream_id=13) via: http/1.1 edge2631.img.djm.yahoo.co.jp (ApacheTrafficServer [c sSf ])
[  0.116] recv (stream_id=13) server: ATS
[  0.116] recv HEADERS frame <length=411, flags=0x04, stream_id=13>
          ; END_HEADERS
          (padlen=0)
          ; First response header
[  0.116] recv DATA frame <length=0, flags=0x01, stream_id=13>
          ; END_STREAM
[  0.116] send GOAWAY frame <length=8, flags=0x00, stream_id=0>
          (last_stream_id=0, error_code=NO_ERROR(0x00), opaque_data(0)=[])
```

### POST時にデータを送付したい
dオプションの後に"-"を付与すると標準入力から読み込んでDATAとして扱ってくれるらしい。
以下の例では２行にわたって"test" "hoge"と入力した後にCtrl+Dを2度押下することでリクエストを発行できるようになる。

残念ながら以下のデバッグログでDATAフレーム送信時にその情報を出してくれなかった(やり方が間違っているかもしれない)

```
$ nghttp -v https://localhost:8080/ -H ':method: POST' --hexdump -d -
test2
hoge
[  4.704] Connected
[WARNING] Certificate verification failed: Hostname mismatch
The negotiated protocol: h2
00000000  00 00 06 04 00 00 00 00  00 00 03 00 00 00 64     |..............d|
0000000f
[  4.707] recv SETTINGS frame <length=6, flags=0x00, stream_id=0>
          (niv=1)
          [SETTINGS_MAX_CONCURRENT_STREAMS(0x03):100]
[  4.707] send SETTINGS frame <length=12, flags=0x00, stream_id=0>
          (niv=2)
          [SETTINGS_MAX_CONCURRENT_STREAMS(0x03):100]
          [SETTINGS_INITIAL_WINDOW_SIZE(0x04):65535]
[  4.708] send SETTINGS frame <length=0, flags=0x01, stream_id=0>
          ; ACK
          (niv=0)
[  4.708] send PRIORITY frame <length=5, flags=0x00, stream_id=3>
          (dep_stream_id=0, weight=201, exclusive=0)
[  4.708] send PRIORITY frame <length=5, flags=0x00, stream_id=5>
          (dep_stream_id=0, weight=101, exclusive=0)
[  4.708] send PRIORITY frame <length=5, flags=0x00, stream_id=7>
          (dep_stream_id=0, weight=1, exclusive=0)
[  4.708] send PRIORITY frame <length=5, flags=0x00, stream_id=9>
          (dep_stream_id=7, weight=1, exclusive=0)
[  4.708] send PRIORITY frame <length=5, flags=0x00, stream_id=11>
          (dep_stream_id=3, weight=1, exclusive=0)
[  4.708] send HEADERS frame <length=43, flags=0x24, stream_id=13>
          ; END_HEADERS | PRIORITY
          (padlen=0, dep_stream_id=11, weight=16, exclusive=0)
          ; Open new stream
          :method: POST
          :path: /
          :scheme: https
          :authority: localhost:8080
          accept: */*
          accept-encoding: gzip, deflate
          user-agent: nghttp2/1.39.2
          content-length: 11
[  4.708] send DATA frame <length=11, flags=0x01, stream_id=13>
          ; END_STREAM
00000000  00 00 00 04 01 00 00 00  00 00 00 45 01 04 00 00  |...........E....|
00000010  00 0d 8d 76 90 aa 69 d2  9a e4 52 a9 a7 4a 6b 13  |...v..i...R..Jk.|
00000020  01 5d 97 d7 17 61 96 dc  34 fd 28 16 94 dc 5a d4  |.]...a..4.(...Z.|
00000030  10 02 fa 80 0d c6 45 71  a7 54 c5 a3 7f 5f 92 49  |......Eq.T..._.I|
00000040  7c a5 89 d3 4d 1f 6a 12  71 d8 82 a6 0e 1b f0 ac  ||...M.j.q.......|
00000050  f7 0f 0d 03 31 34 37 00  00 93 00 01 00 00 00 0d  |....147.........|
00000060  3c 68 74 6d 6c 3e 3c 68  65 61 64 3e 3c 74 69 74  |<html><head><tit|
00000070  6c 65 3e 34 30 34 20 4e  6f 74 20 46 6f 75 6e 64  |le>404 Not Found|
00000080  3c 2f 74 69 74 6c 65 3e  3c 2f 68 65 61 64 3e 3c  |</title></head><|
00000090  62 6f 64 79 3e 3c 68 31  3e 34 30 34 20 4e 6f 74  |body><h1>404 Not|
000000a0  20 46 6f 75 6e 64 3c 2f  68 31 3e 3c 68 72 3e 3c  | Found</h1><hr><|
000000b0  61 64 64 72 65 73 73 3e  6e 67 68 74 74 70 64 20  |address>nghttpd |
000000c0  6e 67 68 74 74 70 32 2f  31 2e 33 39 2e 32 20 61  |nghttp2/1.39.2 a|
000000d0  74 20 70 6f 72 74 20 38  30 38 30 3c 2f 61 64 64  |t port 8080</add|
000000e0  72 65 73 73 3e 3c 2f 62  6f 64 79 3e 3c 2f 68 74  |ress></body></ht|
000000f0  6d 6c 3e                                          |ml>|
000000f3
[  4.708] recv SETTINGS frame <length=0, flags=0x01, stream_id=0>
          ; ACK
          (niv=0)
[  4.708] recv (stream_id=13) :status: 404
[  4.708] recv (stream_id=13) server: nghttpd nghttp2/1.39.2
[  4.708] recv (stream_id=13) date: Sat, 14 Sep 2019 01:32:47 GMT
[  4.708] recv (stream_id=13) content-type: text/html; charset=UTF-8
[  4.708] recv (stream_id=13) content-length: 147
[  4.708] recv HEADERS frame <length=69, flags=0x04, stream_id=13>
          ; END_HEADERS
          (padlen=0)
          ; First response header
<html><head><title>404 Not Found</title></head><body><h1>404 Not Found</h1><hr><address>nghttpd nghttp2/1.39.2 at port 8080</address></body></html>[  4.708] recv DATA frame <length=147, flags=0x01, stream_id=13>
          ; END_STREAM
[  4.708] send GOAWAY frame <length=8, flags=0x00, stream_id=0>
          (last_stream_id=0, error_code=NO_ERROR(0x00), opaque_data(0)=[])
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
sオプションを付与することで統計情報を出力することができる
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

# 参考URL
オプションなどについては以下のマニュアルを参照のこと
- https://nghttp2.org/documentation/nghttp.1.html
