# 概要
protocol-bufferを試してみる

# 詳細

### MACのbrewを使っての環境セットアップ
protocol bufferを使えるようにします。
```
$ brew install protobuf
$ protoc --version
libprotoc 3.12.4
```

今回はGO言語のパッケージを使って確認します。以下を入れておきます。
```
$ go get -u google.golang.org/grpc
$ go get -u github.com/golang/protobuf/protoc
$ go get -u github.com/golang/protobuf/protoc-gen-go
```
先に以下protocコマンドが裏側でprotoc-gen-goを使用しているみたいです。


以下のサンプルIDLを準備します。
```
$ ls
sample.proto
$ cat sample.proto
syntax = "proto3";
package sample;

message User {
    int32 id = 1;
    string name = 2;
}
```

作ったprotoファイルをコンパイルしてC++、JAVA、PYTHON、GO言語用のIDLを出力してみます。
```
$ $ protoc --cpp_out=. --java_out=. --python_out=. --go_out=. sample.proto
$ tree .
├── sample
│   └── Sample.java
├── sample.pb.cc
├── sample.pb.go
├── sample.pb.h
├── sample.proto
└── sample_pb2.py

1 directory, 6 files
```
