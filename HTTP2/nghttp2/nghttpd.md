# 概要
nghttpdコマンドを使うことでHTTP/2サーバとして稼働させることができます。

# 詳細

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
nghttpdでサーバを受け付けているとクライアントからのボディが正しく届いているかを確認したい場合があります。
この場合にはhexdumpオプションを利用します。

以下でリクエストを発行します。
```
$ nghttp -v https://localhost:8080/ --hexdump -H ':method: POST' -d -
helloworld                          // 入力後にCtrl+Dを２度押してリクエストを発行する
```

この時サーバ側ではボディ情報も含めて次のように出力されます。
recv DATAの直下に「helloworld」とは表示されていないのでもう少しうまい方法がないか模索中です。
```
$ nghttpd -v -n 5 -d ./var/html/ 8080 server.key server.crt --hexdump
The negotiated protocol: h2
[id=1] [370.880] send SETTINGS frame <length=6, flags=0x00, stream_id=0>
          (niv=1)
          [SETTINGS_MAX_CONCURRENT_STREAMS(0x03):100]
00000000  50 52 49 20 2a 20 48 54  54 50 2f 32 2e 30 0d 0a  |PRI * HTTP/2.0..|
00000010  0d 0a 53 4d 0d 0a 0d 0a  00 00 0c 04 00 00 00 00  |..SM............|
00000020  00 00 03 00 00 00 64 00  04 00 00 ff ff 00 00 00  |......d.........|
00000030  04 01 00 00 00 00 00 00  05 02 00 00 00 00 03 00  |................|
00000040  00 00 00 c8 00 00 05 02  00 00 00 00 05 00 00 00  |................|
00000050  00 64 00 00 05 02 00 00  00 00 07 00 00 00 00 00  |.d..............|
00000060  00 00 05 02 00 00 00 00  09 00 00 00 07 00 00 00  |................|
00000070  05 02 00 00 00 00 0b 00  00 00 03 00 00 00 2b 01  |..............+.|
00000080  24 00 00 00 0d 00 00 00  0b 0f 83 84 87 41 8a a0  |$............A..|
00000090  e4 1d 13 9d 09 b8 f0 1e  07 53 03 2a 2f 2a 90 7a  |.........S.*/*.z|
000000a0  8a aa 69 d2 9a c4 c0 57  65 f5 c5 0f 0d 02 31 30  |..i....We.....10|
000000b0  00 00 0a 00 01 00 00 00  0d 68 65 6c 6c 6f 77 6f  |.........hellowo|
000000c0  72 6c 64                                          |rld|
000000c3
[id=1] [370.880] recv SETTINGS frame <length=12, flags=0x00, stream_id=0>
          (niv=2)
          [SETTINGS_MAX_CONCURRENT_STREAMS(0x03):100]
          [SETTINGS_INITIAL_WINDOW_SIZE(0x04):65535]
[id=1] [370.880] recv SETTINGS frame <length=0, flags=0x01, stream_id=0>
          ; ACK
          (niv=0)
[id=1] [370.880] recv PRIORITY frame <length=5, flags=0x00, stream_id=3>
          (dep_stream_id=0, weight=201, exclusive=0)
[id=1] [370.880] recv PRIORITY frame <length=5, flags=0x00, stream_id=5>
          (dep_stream_id=0, weight=101, exclusive=0)
[id=1] [370.880] recv PRIORITY frame <length=5, flags=0x00, stream_id=7>
          (dep_stream_id=0, weight=1, exclusive=0)
[id=1] [370.880] recv PRIORITY frame <length=5, flags=0x00, stream_id=9>
          (dep_stream_id=7, weight=1, exclusive=0)
[id=1] [370.880] recv PRIORITY frame <length=5, flags=0x00, stream_id=11>
          (dep_stream_id=3, weight=1, exclusive=0)
[id=1] [370.880] recv (stream_id=13) :method: POST
[id=1] [370.880] recv (stream_id=13) :path: /
[id=1] [370.880] recv (stream_id=13) :scheme: https
[id=1] [370.880] recv (stream_id=13) :authority: localhost:8080
[id=1] [370.880] recv (stream_id=13) accept: */*
[id=1] [370.880] recv (stream_id=13) accept-encoding: gzip, deflate
[id=1] [370.880] recv (stream_id=13) user-agent: nghttp2/1.39.2
[id=1] [370.880] recv (stream_id=13) content-length: 10
[id=1] [370.880] recv HEADERS frame <length=43, flags=0x24, stream_id=13>
          ; END_HEADERS | PRIORITY
          (padlen=0, dep_stream_id=11, weight=16, exclusive=0)
          ; Open new stream
[id=1] [370.880] recv DATA frame <length=10, flags=0x01, stream_id=13>
          ; END_STREAM
[id=1] [370.881] send SETTINGS frame <length=0, flags=0x01, stream_id=0>
          ; ACK
          (niv=0)
[id=1] [370.881] send HEADERS frame <length=69, flags=0x04, stream_id=13>
          ; END_HEADERS
          (padlen=0)
          ; First response header
          :status: 404
          server: nghttpd nghttp2/1.39.2
          date: Sat, 14 Sep 2019 01:36:54 GMT
          content-type: text/html; charset=UTF-8
          content-length: 147
[id=1] [370.881] send DATA frame <length=147, flags=0x01, stream_id=13>
          ; END_STREAM
[id=1] [370.881] stream_id=13 closed
00000000  00 00 08 07 00 00 00 00  00 00 00 00 00 00 00 00  |................|
00000010  00                                                |.|
00000011
[id=1] [370.881] recv GOAWAY frame <length=8, flags=0x00, stream_id=0>
          (last_stream_id=0, error_code=NO_ERROR(0x00), opaque_data(0)=[])
[id=1] [370.881] closed
```

### デーモンとして起動させたい
-Dオプションがある
```
$ nghttpd -n 5 -d ./var/html/ 8080 server.key server.crt -D
```

# 参考URL
オプションなどについては以下のマニュアルを参照のこと
- https://nghttp2.org/documentation/nghttpd.1.html
