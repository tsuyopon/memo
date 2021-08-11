# 概要
go testで扱える内容について

主に以下についてまとめる
- テスト実行方法
- ベンチマーク実行方法

以下にサンプルを配置
- https://github.com/tsuyopon/golang/tree/master/basic_test/

ひとめぐりするには以下の資料がわかりやすかったです。
- https://qiita.com/taisa831/items/85fea8d970bcadd796b9
- https://future-architect.github.io/articles/20200601/

# 詳細

### テスト作成のルール
- xxx.goというテストファイルはxxxx_test.goというファイル名で作成します。こうすることで、ビルド時には\_test.goファイルは除外されます。
  - go testでは\_test.goのsuffixを持つテストファイルがビルド対象となります。
- xxxという関数名のテストはTestXxxとして定義します。定義するTestXxxはtestingパッケージを引数で受けります。
- テストファイルはテスト対象ファイルと同一パッケージとする(※テストだけ例外的にpackagename_testとすることも可能）

### テスト用に非公開スコープを使う方法
以下を参考にすると良い。go docのサンプルもある
- https://github.com/devlights/go-external-test-package-example

以下のコマンドで通常ファイル、test.goファイル、xxx\_test.goファイルなどを表示することができる。
```
$ go list -f={{.GoFiles}} ./pkg/hello/
[doc.go hello.go]
$ go list -f={{.TestGoFiles}} ./pkg/hello/
[hello_test.go]
$ go list -f={{.XTestGoFiles}} ./pkg/hello/
[hello_external_test.go]
```


### テストの実行(実際に試せていません)
```
# カレントディレクトリのみテスト
$ go test 

# testing パッケージ配下のみテスト
$ go test testing

# 指定したディレクトリ以下を再帰的にテスト
go test -v testing/...

# testing/subtest パッケージ配下のみテスト
$ go test testing/subtest

# 指定パッケージのみテスト
$ go test github.com/yoheiMune/MyGoProject/testtest

# 同じパッケージがテストが対象の場合のみテスト
$ go test testing_testing.go testing.go

# 関数名を指定してテスト
$ go test -run Square
```

### 特定の関数の特定のテストのみを実施する
以下のコードがある場合で、TestHello関数のhello-2のテストだけ実行したい場合
```
package hello

import (
    "testing"
)

func TestHello(t *testing.T) {
    t.Run("hello-1", func(t *testing.T) {
        t.Fatal("error")
    })
    t.Run("hello-2", func(t *testing.T) {
        t.Fatal("error")
    })
    t.Run("hello-3", func(t *testing.T) {
        t.Fatal("error")
    })
}
```

次のコマンドを実行します。
```
$ go test -run TestHello/hello-2
```


# 参考資料
- Go testing: Testingパッケージの説明
  - https://pkg.go.dev/testing
- The Go Blog: The cover story
  - https://blog.golang.org/cover
- How to Write Go Code
  - https://golang.org/doc/code#Testing
