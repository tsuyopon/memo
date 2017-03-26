# 概要
mochaとpower-assertについて
- mochaはNode.js上で動作するフレームワークです。
- power-assertは、mochaフレームワークを用いたテストで用いるassertライブラリ
となります。

セットアップ方法としては次の通りです。karmaと連携させずに「mocha test/hoge.js」と実行するにはこれでも問題ありません。
```
$ npm install mocha --save-dev
$ npm install power-assert --save-dev
```

karmaと連携させる(karma.config.js)からも利用できるようにするには次のインストールをします。
```
$ npm install karma-mocha --save-dev
```

karma-mochaでmochaを実行した結果の表示色を変更するには次をインストールします。
- http://qiita.com/chihiro/items/f289ce458091e179e606
```
$ npm install karma-mocha-reporter --save-dev
```

assertのような感じでshouldやexpectを使いたければchaiもインストールしておきます。
- (参考) http://chaijs.com/guide/styles/
```
$ sudo npm install chai --save-dev
```


# mochaについて

### 特定のテストだけを実行する
```
$ mocha --require intelli-espower-loader  test/hogehoge.js
or
$  mocha test/hogehoge.js
```

### ファイルの変更を検知してテストを実行する
次のようにするとファイルに変更が入るたびにテストを実行し、結果を出力してくれます。
```
$ mocha -w --require intelli-espower-loader
or
$ mocha -w
```

### mochaが自動的に読み込むファイルに追加する
mochaが自動的に読み込んでオプションとして付加してくれる設定ファイルがあります。
それはテスト標準ディレクトリのtest/配下のmocha.optsにmochaのコマンドラインオプションを記述するとmochaコマンドを叩くだけで勝手に実行します。

たとえば、次のような設定を追加すると、テストファイルを読み込む時にbable-registerで前処理しテストコードもES-6で記述で、再帰的に記述できるようになる。
babel-polyfillによってブラウザでbabelで変換したものを利用する場合にはこのpolyfillが必要になります。これはES6の新しい機能などを利用するためのES5向けのライブラリです。
```
$ vim test/mocha.opts
--compilers js:babel-register
--recursive
--require babel-polyfill
```

# power-assertについて
各種assert関連関数一覧についてはこちらを参考のこと
- https://github.com/power-assert-js/power-assert

power-assertでは次のような関数を用意している
* `assert(value, [message])`
* `assert.ok(value, [message])`
* `assert.equal(actual, expected, [message])`
* `assert.notEqual(actual, expected, [message])`
* `assert.strictEqual(actual, expected, [message])`
* `assert.notStrictEqual(actual, expected, [message])`
* `assert.deepEqual(actual, expected, [message])`
* `assert.notDeepEqual(actual, expected, [message])`
* `assert.deepStrictEqual(actual, expected, [message])`
* `assert.notDeepStrictEqual(actual, expected, [message])`

https://nodejs.org/api/assert.html のassertと互換性があるので次の構文も使える
* `assert.fail(actual, expected, message, operator)`
* `assert.throws(block, [error], [message])`
* `assert.doesNotThrow(block, [message])`
* `assert.ifError(value)`


# 参考URL
- mocha + power-assert環境の構築
  - http://qiita.com/gitseitanaka/items/ea47d261284879a1d774
