# 概要
webpackとはweb提供に必要となる配布物(アセット)を生成するためのビルドツールです。これはつまりコンパイラのようなものと思って問題ありません。

インストール
```
$ npm install webpack -g 
```

# 詳細

### 使ってみる

```
$ cat cats.js
var cats = ['tama', 'kuro', 'tora']
module.exports = cats;
```

```
$ cat app.js
var cats = require('./cats.js');
console.log(cats);
```

上記２つをwebpackでビルドしましょう。

### 設定ファイル(webpack.config.js)
先ほどの例ではwebpackに引数を指定しましたが、設定ファイルに設定を記述しておけばwebpackコマンドだけで生成してくれます。

### json-loaderを使う
以下のようにhoge.jsonを用意する
```
["hoge", "fuga", "piyo"]
```

ソースコードでは次のように記述できる。
```
var cats = require('json-loader!./hoge.json');
or
var cats = require('json!./hoge.json');          // -loaderは省略可能
```

### 


# 参考URL
- 公式チュートリアル
 - http://webpack.github.io/docs/tutorials/getting-started/
- step by stepではじめるwebpack
 - http://qiita.com/howdy39/items/48d85c430f90a21075cd
- json-loader
 - https://github.com/webpack/json-loader/blob/master/index.js
