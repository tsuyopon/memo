# 概要
環境セットアップ方法について

# 詳細

### yumでgo言語を入れる
以下のコマンドでインストールする
```
$ sudo yum install epel-release
$ sudo yum install -y golang
```

インストールされたことを確認する
```
$ go version
go version go1.13.6 linux/amd64
```

環境変数を設定する
```
$ echo export GOROOT=/usr/lib/golang >> ~/.bash_profile
$ echo export GOPATH=/usr/share/gocode >> ~/.bash_profile
$ echo export PATH=$PATH:$GOROOT/bin:$GOPATH/bin >> ~/.bash_profile
$ source ~/.bash_profile
```

動作確認のため、以下のhello worldプログラムをコンパイルしてみます。
```
$ cat hello.go 
package main

import "fmt"

func main() {
    fmt.Printf("hello, world\n")
}
```

では、簡単なhelloworldを実行してみましょう。
```
$ go build hello.go 
$ ls
hello  hello.go
$ ./hello 
hello, world
```

- 参考
  - https://qiita.com/okatai/items/4beaf74d284f5bdfae4b

### ソースコードからのインストール
以下の資料を参考にする
- https://golang.org/doc/install
