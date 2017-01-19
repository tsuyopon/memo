# 概要
Knockout.jsについて

基本的な動作概要
- viewにdata-bindをattributeに記述するdata-bind="text: hoge"
- this.hoge = ko.observable(true); などとして対象の監視をする
- this.hogeを使ってデータを書き出したい場合にはko.computedを使う。
- ko.computedは最初に実行された際に依存する変数を保存しておく。これによって対象が変更された場合にはその関数を実行することになる。



### チュートリアル
この辺にあるようです。
- http://learn.knockoutjs.com/#/?tutorial=intro

### ko.computedについて
- この辺の記事がわかりやすい。
- http://qiita.com/opengl-8080/items/2b0fb26be865bd5d1890

