# 概要
goコマンドについて

公式ドキュメントについては以下を参考にすること
- https://pkg.go.dev/cmd/go

# 詳細

### GO環境変数の確認を行う
```
$ go env
GO111MODULE="on"
GOARCH="amd64"
GOBIN=""
GOCACHE="/Users/tsuyoshi/Library/Caches/go-build"
GOENV="/Users/tsuyoshi/Library/Application Support/go/env"
GOEXE=""
GOFLAGS=""
GOHOSTARCH="amd64"
GOHOSTOS="darwin"
GOINSECURE=""
GONOPROXY=""
GONOSUMDB=""
GOOS="darwin"
GOPATH="/Users/tsuyoshi/go"
GOPRIVATE=""
GOPROXY="https://proxy.golang.org,direct"
GOROOT="/usr/local/Cellar/go/1.14.7/libexec"
GOSUMDB="sum.golang.org"
GOTMPDIR=""
GOTOOLDIR="/usr/local/Cellar/go/1.14.7/libexec/pkg/tool/darwin_amd64"
GCCGO="gccgo"
AR="ar"
CC="clang"
CXX="clang++"
CGO_ENABLED="1"
GOMOD="/Users/tsuyoshi/git/gowebapi/go.mod"
CGO_CFLAGS="-g -O2"
CGO_CPPFLAGS=""
CGO_CXXFLAGS="-g -O2"
CGO_FFLAGS="-g -O2"
CGO_LDFLAGS="-g -O2"
PKG_CONFIG="pkg-config"
GOGCCFLAGS="-fPIC -m64 -pthread -fno-caret-diagnostics -Qunused-arguments -fmessage-length=0 -fdebug-prefix-map=/var/folders/f7/q7tp90ld44v9dw8y61t3h0gh0000gn/T/go-build362513466=/tmp/go-build -gno-record-gcc-switches -fno-common"
```

なお、設定変更は以下のようにして行います。
```
$ go env -w GO111MODULE=on
```

### 指定したパッケージのインストールを行う

```
// 一般的な指定
$ go get github.com/hoge/fuga@latest

// latestを指定
$ go get github.com/hoge/fuga@latest
```

### パッケージのインストールや不要なパッケージの削除を行う
```
$ go mod tidy -v
```
vオプションを付与すると不要なパッケージも表示するらしい(なくても可能)

上記コマンドを実行するとgo.sumが生成される。


### Goモジュールの初期化を行う
```
$ go mod init go-example
go: creating new go.mod: module go-example
$ ls
go.mod
$ cat go.mod 
module go-example

go 1.14
```

### モジュールが依存するパッケージ一覧を表示する

```
$ go list -m all
gin_test
github.com/creack/pty v1.1.9
github.com/davecgh/go-spew v1.1.1
github.com/gin-contrib/sse v0.1.0
github.com/gin-gonic/gin v1.7.3
github.com/go-playground/assert/v2 v2.0.1
github.com/go-playground/locales v0.14.0
github.com/go-playground/universal-translator v0.18.0
github.com/go-playground/validator/v10 v10.9.0
github.com/golang/protobuf v1.5.2
github.com/google/go-cmp v0.5.5
github.com/google/gofuzz v1.0.0
github.com/json-iterator/go v1.1.11
github.com/kr/pretty v0.3.0
github.com/kr/pty v1.1.1
github.com/kr/text v0.2.0
github.com/leodido/go-urn v1.2.1
github.com/mattn/go-isatty v0.0.13
github.com/modern-go/concurrent v0.0.0-20180306012644-bacd9c7ef1dd
github.com/modern-go/reflect2 v1.0.1
....
```

### コンパイルしてバイナリファイルを作成する

一時的に実行するのであれば、以下で実行できますが、
```
$ go run main.go
```

バイナリを生成して実行する場合には次のようにします。
```
$ go build main.go
$ ./main
```

go run はgo buildと異なり、importされたパッケージしか読み込まないので注意が必要です。

# 公式資料
- goコマンドの公式ドキュメント
  - https://pkg.go.dev/cmd/go
