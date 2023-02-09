# 概要
GO言語のdebugについて
 
# 詳細

### コアダンプ
下記環境変数を設定しておくだけでcrash時にコアダンプを出力してくれるようになります。
```
export GOTRACEBACK=crash
```

あとはOS側の設定も確認しておきましょう。
```
$ ulimit -c unlimited
$ ulimit -c
unlimited
```

プログラムにコアを吐かせたければSIGABRTを送りましょう。
```
$ ps auxww
$ kill -ABRT <プロセス番号>
```

### HTTP/2のデバッグで利用可能な環境変数
GODEBUG環境変数に次のように指定することでHTTP/2に関するデバッグログが取得できるらしい
```
$ export GODEBUG=http2debug=2
```

試しにGRPCのgreeter_server、greeter_clientの２つのclient helloサンプルで試してみた ( 参考: https://github.com/grpc/grpc-go.git ) 。

- サーバ側
```
$ export GODEBUG=http2debug=2
[~/git/grpc-go/examples/helloworld]$ go run greeter_server/main.go 
2020/08/09 06:00:27 http2: Framer 0xc0001a4000: wrote SETTINGS len=6, settings: MAX_FRAME_SIZE=16384
2020/08/09 06:00:27 http2: Framer 0xc0001a4000: read SETTINGS len=0
2020/08/09 06:00:27 http2: Framer 0xc0001a4000: read SETTINGS flags=ACK len=0
2020/08/09 06:00:27 http2: Framer 0xc0001a4000: wrote SETTINGS flags=ACK len=0
2020/08/09 06:00:27 http2: Framer 0xc0001a4000: read HEADERS flags=END_HEADERS stream=1 len=92
2020/08/09 06:00:27 http2: decoded hpack field header field ":method" = "POST"
2020/08/09 06:00:27 http2: decoded hpack field header field ":scheme" = "http"
2020/08/09 06:00:27 http2: decoded hpack field header field ":path" = "/helloworld.Greeter/SayHello"
2020/08/09 06:00:27 http2: decoded hpack field header field ":authority" = "localhost:50051"
2020/08/09 06:00:27 http2: decoded hpack field header field "content-type" = "application/grpc"
2020/08/09 06:00:27 http2: decoded hpack field header field "user-agent" = "grpc-go/1.30.0"
2020/08/09 06:00:27 http2: decoded hpack field header field "te" = "trailers"
2020/08/09 06:00:27 http2: decoded hpack field header field "grpc-timeout" = "999963u"
2020/08/09 06:00:27 http2: Framer 0xc0001a4000: read DATA flags=END_STREAM stream=1 len=12 data="\x00\x00\x00\x00\a\n\x05world"
2020/08/09 06:00:27 http2: Framer 0xc0001a4000: wrote WINDOW_UPDATE len=4 (conn) incr=12
2020/08/09 06:00:27 http2: Framer 0xc0001a4000: wrote PING len=8 ping="\x02\x04\x10\x10\t\x0e\a\a"
2020/08/09 06:00:27 http2: Framer 0xc0001a4000: read PING flags=ACK len=8 ping="\x02\x04\x10\x10\t\x0e\a\a"
2020/08/09 06:00:27 Received: world
2020/08/09 06:00:27 http2: Framer 0xc0001a4000: wrote HEADERS flags=END_HEADERS stream=1 len=14
2020/08/09 06:00:27 http2: Framer 0xc0001a4000: wrote DATA stream=1 len=18 data="\x00\x00\x00\x00\r\n\vHello world"
2020/08/09 06:00:27 http2: Framer 0xc0001a4000: wrote HEADERS flags=END_STREAM|END_HEADERS stream=1 len=24
2020/08/09 06:00:27 http2: Framer 0xc0001a4000: read WINDOW_UPDATE len=4 (conn) incr=18
2020/08/09 06:00:27 http2: Framer 0xc0001a4000: read PING len=8 ping="\x02\x04\x10\x10\t\x0e\a\a"
2020/08/09 06:00:27 http2: Framer 0xc0001a4000: wrote PING flags=ACK len=8 ping="\x02\x04\x10\x10\t\x0e\a\a"
```

- クライアント側
```
$ go run greeter_client/main.go 
2020/08/09 06:00:27 http2: Framer 0xc000318000: wrote SETTINGS len=0
2020/08/09 06:00:27 http2: Framer 0xc000318000: read SETTINGS len=6, settings: MAX_FRAME_SIZE=16384
2020/08/09 06:00:27 http2: Framer 0xc000318000: wrote SETTINGS flags=ACK len=0
2020/08/09 06:00:27 http2: Framer 0xc000318000: wrote HEADERS flags=END_HEADERS stream=1 len=92
2020/08/09 06:00:27 http2: Framer 0xc000318000: wrote DATA flags=END_STREAM stream=1 len=12 data="\x00\x00\x00\x00\a\n\x05world"
2020/08/09 06:00:27 http2: Framer 0xc000318000: read SETTINGS flags=ACK len=0
2020/08/09 06:00:27 http2: Framer 0xc000318000: read WINDOW_UPDATE len=4 (conn) incr=12
2020/08/09 06:00:27 http2: Framer 0xc000318000: read PING len=8 ping="\x02\x04\x10\x10\t\x0e\a\a"
2020/08/09 06:00:27 http2: Framer 0xc000318000: wrote PING flags=ACK len=8 ping="\x02\x04\x10\x10\t\x0e\a\a"
2020/08/09 06:00:27 http2: Framer 0xc000318000: read HEADERS flags=END_HEADERS stream=1 len=14
2020/08/09 06:00:27 http2: decoded hpack field header field ":status" = "200"
2020/08/09 06:00:27 http2: decoded hpack field header field "content-type" = "application/grpc"
2020/08/09 06:00:27 http2: Framer 0xc000318000: read DATA stream=1 len=18 data="\x00\x00\x00\x00\r\n\vHello world"
2020/08/09 06:00:27 http2: Framer 0xc000318000: read HEADERS flags=END_STREAM|END_HEADERS stream=1 len=24
2020/08/09 06:00:27 http2: decoded hpack field header field "grpc-status" = "0"
2020/08/09 06:00:27 http2: decoded hpack field header field "grpc-message" = ""
2020/08/09 06:00:27 http2: Framer 0xc000318000: wrote WINDOW_UPDATE len=4 (conn) incr=18
2020/08/09 06:00:27 http2: Framer 0xc000318000: wrote PING len=8 ping="\x02\x04\x10\x10\t\x0e\a\a"
2020/08/09 06:00:27 Greeting: Hello world
```

