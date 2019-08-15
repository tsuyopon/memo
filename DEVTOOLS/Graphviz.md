# 概要
graphvizについて

サンプルについてはgraphvizで示します。

# 詳細

### dotファイルを変換したい
```
$ dot -T pdf sample.dot -o sample.pdf 
$ dot -T png sample.dot -o sample.png
$ dot -T jpg sample.dot -o sample.jpg
$ dot -T svg sample.dot -o sample.svg
```

### dotファイルを修正しながら画像を確認したい
gveditというアプリケーションがあるらしいです。


# 詳細

### ファイル間のincludeの依存関係を取得したい
この辺のperlスクリプトを使うと良い
- https://www.flourish.org/cinclude2dot/

# 参考URL
- Graphvizとdot言語でグラフを描く方法のまとめ
  - 画像付きでサンプルがあるので非常にいい
  - https://qiita.com/rubytomato@github/items/51779135bc4b77c8c20d
- WebUI上で定義ファイルを入力して画像を出力してくれるツール。ちょっとした確認に便利
  - http://www.webgraphviz.com/

# 公式サイト
- Graphviz
  - http://www.graphviz.org/
- Sphinxによるドキュメント
  - https://graphviz.readthedocs.io/en/stable/index.html
