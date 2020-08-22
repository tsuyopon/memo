# 概要
grpcはマイクロサービス向けに最適化されたHTTP/2 + protocol_bufferを利用した仕組みです。


# 詳細

## hello worldを使ってみる
go言語の実装であるgrpc-goを利用してサーバとクライアントのサンプルを実行してみます。
```
$ git clone https://github.com/grpc/grpc-go.git
$ cd grpc-go/examples/helloworld
```

サーバを起動する
```
$ go run greeter_server/main.go
2020/08/09 06:16:05 Received: world       <= これはクライアントからのリクエストを受け取ったら表示される。
```

クライアントを起動する
```
$ go run greeter_client/main.go
2020/08/09 06:16:05 Greeting: Hello world
```


## 環境変数
環境変数周りについては以下のドキュメントを参考にすると良い
- https://github.com/grpc/grpc/blob/master/doc/environment_variables.md
- https://github.com/grpc/grpc/blob/master/TROUBLESHOOTING.md

### GRPC_VERBOSITY, GRPC_TRACE
Cをベースとした言語(C++, Python, Ruby, Objective-C, PHP, C#)の実装では以下のような環境変数を設定することで追加のログが出力できます。
```
$ export GRPC_VERBOSITY=DEBUG
$ export GRPC_TRACE=all
```

### GRPC_GO_LOG_SEVERITY_LEVEL, GRPC_GO_LOG_VERBOSITY_LEVEL
以下はgrpcのgo実装の場合に役に立つロギング環境変数設定らしい
```
$ export GRPC_GO_LOG_SEVERITY_LEVEL=info
$ export GRPC_GO_LOG_VERBOSITY_LEVEL=2
```

### GRPC_TRACE
```
$ export GRPC_TRACE=all
```

## CLI Tool

- grpcnode — CLI tool for quickly making servers and client, dynamically, in JavaScript.
- grpcc — REPL gRPC command-line client.
- grpc_cli — gRPC CLI tool.
- Evans — Expressive universal gRPC (CLI) client.
- grpcurl — Like cURL, but for gRPC: Command-line tool for interacting with gRPC servers.
- danby — A gRPC proxy for the browser.
- docker-protoc — Dockerized protoc, grpc-gateway, and grpc_cli commands bundled with Google API libraries.
- prototool Useful “Swiss Army Knife” for processing proto files.

- 参考: https://medium.com/@EdgePress/how-to-interact-with-and-debug-a-grpc-server-c4bc30ddeb0b


## example

- https://github.com/backstopmedia/gRPC-book-example
- 上記の使い方
  - https://medium.com/@EdgePress/how-to-interact-with-and-debug-a-grpc-server-c4bc30ddeb0b
