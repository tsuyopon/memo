# 概要
SwagはGo言語(1.13 or newer)のアノテーションをSwaggerドキュメント(v2)ヘと変換する仕組みです。
以下のフレームワークをサポートしているようです。
- gin
- echo
- buffalo
- net/http
- flamingo
- fiber
- atreugo

# 導入方法
以下を参考にしてください。
- https://gavin-zhou.medium.com/go-gin%E3%83%81%E3%83%A5%E3%83%BC%E3%83%88%E3%83%AA%E3%82%A2%E3%83%AB-part7-db5a13795bf3

上記では以下のことを行なっています。
- モジュールへdocsのipmport (docsはswag initで生成されます)
- 以下の追加
```
r.GET("/swagger/*any", ginSwagger.WrapHandler(swaggerFiles.Handler))
```
- swaggerドキュメントのための関数へのアノテーションの追加

以上が完了したらswagコマンドを導入して、swagger用に必要なdocsディレクトリや関連ファイルを以下のコマンドで自動生成します。
```
$ go get -u github.com/swaggo/swag/cmd/swag
$ swag init
```

swag initコマンドによって、アノテーションを参照にdocsディレクトリとその中にyamlやjsonファイル、goのソースコードが生成されます。
あとは起動するだけです。


# 公式ドキュメント
Getting Startedや記述方法については以下を参考にすること
- https://github.com/swaggo/swag#general-api-info
- https://github.com/swaggo/swag#declarative-comments-format
- https://swaggo.github.io/swaggo.io/

swagger公式ドキュメント
- https://swagger.io/specification/

# 参考ドキュメント
- Swaggerの記法まとめ
  - https://qiita.com/rllllho/items/53a0023b32f4c0f8eabb
