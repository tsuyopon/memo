# 概要
Goのモジュールについてです。Goモジュールは1.13からサポートされました。
それ以前はGOPATHやGOVENDERといった環境変数を使用してパッケージ管理するのが一般的でした。

Go1.14からはすべての Go ユーザが GO111MODULE=onへ移行することが推奨されている
なおバージョン 1.16 から GO111MODULE 未指定時の既定値が on になった（1.15 までは auto）


# 公式サイトのGoモジュールの説明
Go 1.13には、Goモジュールのサポートが含まれています。
モジュール対応モードは、現在のディレクトリまたはその親にgo.modファイルが見つかった場合にデフォルトでアクティブになります。

モジュールサポートを利用する最も簡単な方法は、リポジトリをチェックアウトし、そこにgo.modファイル（次のセクションで説明）を作成し、そのファイルツリー内からgoコマンドを実行することです。

より細かく制御するために、Go 1.13は一時的な環境変数GO111MODULEを引き続き尊重します。
これは、off、on、またはauto（デフォルト）の3つの文字列値のいずれかに設定できます。

- GO111MODULE = onの場合、
  - goコマンドではモジュールを使用する必要があり、GOPATHを参照することはありません。 これを、モジュール対応または「モジュール対応モード」で実行されるコマンドと呼びます。
- GO111MODULE = offの場合、
  - goコマンドはモジュールサポートを使用しません。 代わりに、ベンダーのディレクトリとGOPATHを調べて依存関係を見つけます。これを「GOPATHモード」と呼びます。
- GO111MODULE = autoまたは未設定の場合、
  - goコマンドは現在のディレクトリに基づいてモジュールサポートを有効または無効にします。 モジュールのサポートは、現在のディレクトリにgo.modファイルが含まれる場合、またはgo.modファイルが含まれるディレクトリの下にある場合にのみ有効になります。

モジュール対応モード(GO111MODULE=on)では、GOPATHはビルド中のインポートの意味を定義しなくなりましたが、ダウンロードされた依存関係（GOPATH / pkg / mod）とインストールされたコマンド（GOBINが設定されていない場合はGOPATH / bin）を保存します。

# Goモジュールの設定を変更する
```
$ go env -w GO111MODULE=on
```

# 実際にGOMODULEを利用してみる。

以下を実行するとgo.modが生成されます。
```
$ go mod init gomodtest
$ cat go.mod
module gomodtest

go 1.14
```

以下でパッケージを取得します。
```
$ go get -u go.uber.org/zap
go: downloading go.uber.org/zap v1.19.0
go: go.uber.org/zap upgrade => v1.19.0
go: downloading go.uber.org/atomic v1.7.0
go: downloading go.uber.org/multierr v1.6.0
go: go.uber.org/atomic upgrade => v1.9.0
go: go.uber.org/multierr upgrade => v1.7.0
go: downloading go.uber.org/multierr v1.7.0
go: downloading go.uber.org/atomic v1.9.0
```

その後、go.sumが生成されていることがわかります。また、go.modファイルが変更されているのがわかります。
```
$ ls
go.mod go.sum
$ cat go.mod 
module gomodtest

go 1.14

require (
	go.uber.org/atomic v1.9.0 // indirect
	go.uber.org/multierr v1.7.0 // indirect
	go.uber.org/zap v1.19.0 // indirect
)
```

go.sumにはパッケージのバージョンとそのSHA256ハッシュ値が含まれています。

レポジトリから取得して以下のコマンドで一髪でインストールできます。
```
$ go mod tidy
```

### go.modに指定できるディレクティブ
```
ディレクティブ        記述例                                          内容
----------------------------------------------------------------------------------------------
module                module my/thing                                 モジュール名
go                    1.16                                            有効な Go バージョン
require               require other/thing v1.0.2                      インポート・モジュール
exclude               exclude old/thing v1.2.3                        除外モジュール
replace               replace bad/thing v1.4.5 => good/thing v1.4.5   モジュールの置換
retract               v1.0.5                                          撤回バージョン
```

### キャッシュについて
goではコンパイル結果の中間バイナリを環境変数 GOCACHE で指定したディレクトリにキャッシュし，可能な限り再利用しようとする。
インポートしたモジュールのキャッシュについては $GOPATH/pkg/mod ディレクトリに配置されているが Go 1.15 より環境変数 GOMODCACHE で変更できるようになった。

ビルドキャッシュのクリアは以下のコマンドで実行可能です。
```
$ go clean -cache
```

または
```
$ go clean -modcache
```




# 参考URL
詳しくは以下を参考にすると良い
- https://qiita.com/Syoitu/items/f221b52231703cebe8ff
- https://ren.nosuke.me/blog/202002/20200222/

まずは公式サイトに書かれている以下の注意書きをみること
- https://pkg.go.dev/cmd/go#hdr-Modules__module_versions__and_more

