# 概要
GOのWebフレームワークで最もgithubのstart数が多くて利用されているのがginです。

公式ドキュメントは以下を参考のこと
- https://pkg.go.dev/github.com/gin-gonic/gin

関数の引数に引き渡されるcontextは以下のコードを参照すると良い
- https://github.com/gin-gonic/gin/blob/v1.7.3/context.go#L46

# 実装する際に参考にすべきサンプル情報
実装する上で参考になりそうなサンプルは以下です。
- 公式github(gin-gonic/gin)
   - gin利用方法はREADME.mdが非常に充実しているので公式のドキュメントを参考にするとよいでしょう。また、ginを利用している有名なソフトウェアについてもREADME.mdに記載されています。
   - https://github.com/gin-gonic/gin
- gin-gonic/examples
  - 公式レポジトリgin-gonic/ginから分離したレポジトリです。各種ディレクトリ直下に様々なサンプルが配置されています。
  - https://github.com/gin-gonic/examples
- 最も有名そうなginを使ったAPIサンプル集です。中国人の方による実装のようです。
  - redisとmysqlのセットアップが必要です。swaggerはありますが、使い方がいまいちよくわかっていません。
  - https://github.com/eddycjy/go-gin-example
- ドキュメントですが様々なAPIの実装サンプルがあります
  - https://chenyitian.gitbooks.io/gin-web-framework/content/

# その他参考
- Qiita: ginを最速でマスターしよう
  - https://qiita.com/Syoitu/items/8e7e3215fb7ac9dabc3a

# 関連お役立ち資料
- Standard Go Project Layout
  - https://github.com/golang-standards/project-layout/blob/master/README_ja.md
- Gin Web Framework
  - 参考になるドキュメント
  - https://chenyitian.gitbooks.io/gin-web-framework/content/
