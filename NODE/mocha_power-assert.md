# 概要
mochaとpower-assertについて
- mochaはNode.js上で動作するフレームワークです。
- power-assertは、mochaフレームワークを用いたテストで用いるassertライブラリ
となります。


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
