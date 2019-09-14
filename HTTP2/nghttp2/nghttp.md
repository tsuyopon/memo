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

# 参考URL
オプションなどについては以下のマニュアルを参照のこと
- https://nghttp2.org/documentation/nghttp.1.html
