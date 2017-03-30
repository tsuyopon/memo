# 概要
go言語について

### macでの設定 
もともとの目的としては以下のパッケージを実行したかったのでgoを入れてみた。
https://github.com/demouth/mario-go

brewでインストールする
```
$ sudo brew install go
```

PATHでgoコマンドへのパスを、GOPATHe
```
$ export PATH=$PATH:/usr/local/opt/go/libexec/bin/
$ export GOPATH=/Users/tsuyoshi
```

以下を実行すると$GOPATH/src/配下にセットアップされるようだ。
```
$ go get github.com/demouth/mario-go
$ cd $GOPATH/src/github.com/demouth/mario-go
```

makeを実行してみる。色々と依存関係については"go get github.com/xxxx/yyyy"で解決すると最終的には以下のエラーとなった。
```
$ make
rm -f release/mario-go
rm -f release/mario-go.exe 
rm -f release/windows_386_mario-go.zip
rm -f release/darwin_amd64_mario-go.tar.gz
rm -f release/linux_amd64_mario-go.tar.gz
GOOS=windows GOARCH=386 go build -o release/mario-go.exe cmd/main.go
go build runtime: windows/386 must be bootstrapped using make.bash
make: *** [build-win] Error 1
```

GOARCHが386となっているようだが、環境変数を確認するとamd64となっている。
```
$  go env GOARCH
amd64
```

なぜかamd64だけど、makeを実行するとGOARCHが386になっている??
とりあえず以下のようにすれば実行できる。(後で調べる)
```
$ GOARCH=amd64 go run cmd/main.go 
```

### vimでのsyntaxを有効にする
```
filetype off
filetype plugin indent off
set runtimepath+=$GOROOT/misc/vim
filetype plugin indent on
syntax on
autocmd FileType go autocmd BufWritePre  Fmt
set rtp+=$GOPATH/src/github.com/nsf/gocode/vim
set rtp+=$GOPATH/src/github.com/golang/lint/misc/vim
set completeopt=menu,preview
```
syntaxだけで言えば、1行目と4行目だけでいけるようだ

- 参考
  - https://www.seeds-std.co.jp/seedsblog/2494.html


# 参考URL
- http://aibou.hateblo.jp/entry/2014/07/11/115920
- SlideShare(Go言語によるWebアプリの作り方)
  - http://www.slideshare.net/yasi_life/goweb-16448500
- VimでGo言語を書く環境を設定する 
  - https://www.seeds-std.co.jp/seedsblog/2494.html
