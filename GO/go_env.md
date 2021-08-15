# 概要
goの環境変数について

# 詳細

### http2通信のデバッグを出力する
GODEBUG環境変数を設定すれば良い
```
export GODEBUG=http2debug=2
```

標準出力に次のようなログが表示されます。
```
2021/08/15 11:20:02 http: TLS handshake error from [::1]:62514: remote error: tls: unknown certificate
2021/08/15 11:20:02 http2: server connection from [::1]:62515 on 0xc0003900e0
2021/08/15 11:20:02 http2: Framer 0xc0000f00e0: wrote SETTINGS len=24, settings: MAX_FRAME_SIZE=1048576, MAX_CONCURRENT_STREAMS=250, MAX_HEADER_LIST_SIZE=1048896, INITIAL_WINDOW_SIZE=1048576
2021/08/15 11:20:02 http2: server: client [::1]:62515 said hello
2021/08/15 11:20:02 http2: Framer 0xc0000f00e0: wrote WINDOW_UPDATE len=4 (conn) incr=983041
2021/08/15 11:20:02 http2: Framer 0xc0000f00e0: read SETTINGS len=30, settings: HEADER_TABLE_SIZE=65536, MAX_CONCURRENT_STREAMS=1000, INITIAL_WINDOW_SIZE=6291456, MAX_HEADER_LIST_SIZE=262144, UNKNOWN_SETTING_43546=2808745131
2021/08/15 11:20:02 http2: server read frame SETTINGS len=30, settings: HEADER_TABLE_SIZE=65536, MAX_CONCURRENT_STREAMS=1000, INITIAL_WINDOW_SIZE=6291456, MAX_HEADER_LIST_SIZE=262144, UNKNOWN_SETTING_43546=2808745131
2021/08/15 11:20:02 http2: server processing setting [HEADER_TABLE_SIZE = 65536]
2021/08/15 11:20:02 http2: server processing setting [MAX_CONCURRENT_STREAMS = 1000]
2021/08/15 11:20:02 http2: server processing setting [INITIAL_WINDOW_SIZE = 6291456]
2021/08/15 11:20:02 http2: server processing setting [MAX_HEADER_LIST_SIZE = 262144]
2021/08/15 11:20:02 http2: server processing setting [UNKNOWN_SETTING_43546 = 2808745131]
2021/08/15 11:20:02 http2: server ignoring unknown setting [UNKNOWN_SETTING_43546 = 2808745131]
(snip)
```
