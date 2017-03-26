# 概要
karmaとはブラウザ上で単体テストを実行するためのテストランナーです。  
テストを実行する機能の他にもファイルの変更監視、結果レポート出力など単体テストに必要な機能が一式揃っています。

Node.jsやnpmが導入済みであれば次のコマンドでインストール可能です。
```
$ npm install --save-dev karma
$ npm install -g karma-cli
```

karmaでは様々なプラグインが提供されているようなので次の箇所もざっと見ておくといいのかも
- https://www.npmjs.com/browse/keyword/karma-launcher

# karmaサーバを起動する
```
$ karma start
```

これでhttp://<hostname>:9876/によりKarmaが起動します。

なお、ログレベルを指定するには--log-levelを付与します。
```
$ karma start --log-level debug

09 05 2016 12:31:49.435:DEBUG [plugin]: Loading karma-* from /Users/howdy/VscodeProjects/study-karma/node_modules
09 05 2016 12:31:49.464:DEBUG [karma]: List of files has changed, trying to execute
09 05 2016 12:31:49.465:WARN [karma]: No captured browser, open http://localhost:9876/
09 05 2016 12:31:49.470:INFO [karma]: Karma v0.13.22 server started at http://localhost:9876/
```

# karma起動時にデフォルトで読み込む設定ファイルを書く
karmaコマンド実行時にそのオプションとしてkarma.conf.jsを読み込みようになっています。

次のコマンドでインタラクティブな質問に答えるだけでサンプルファイルが作成されます。しかし、ここでは実際に手で作ってみます。
```
$ karma init
```

たとえばログレベルを最初からDEBUGレベルにしておきたければ次のようにします。
```
$ module.exports = function(config) {
    config.set({
        logLevel: config.LOG_DEBUG
    })
}
```

# karma.conf.jsについて

karmaコマンド実行時にデフォルトで読み込まれるファイルです。次のようなことができます。
- CI用に1度だけkarmaを起動したり
- 起動時のポート番号を制御したり
- 実行するテストファイルを指定したり、除外したり

あとは、
- preprocessorsなどを使えばテスト用ファイルをwebpackで固めるということもできます。

以下は簡単なサンプル
```
module.exports = function(config) {
  config.set({

    // ベースとなるパス
    basePath: '',

    // 使用するフレームワーク。ここから探せる https://npmjs.org/browse/keyword/karma-adapter
    frameworks: ['mocha'],

    // 読み込むファイル(テスト対象のファイルやテストファイルなど)。
    files: ['js/*.js'],

    // filesから除外したファイル
    exclude: [],

    // テストの実行前に差し込む処理。ここから探せる https://npmjs.org/browse/keyword/karma-preprocessor
    preprocessors: {}

    // テストの結果を出力する形式。ここから探せる https://npmjs.org/browse/keyword/karma-reporter
    // 'dots'と'progress'は最初から使える
    reporters: ['progress'],

    // 使用するport
    port: 9876,

    // 出力に色を付けるか
    colors: true,

    // ログレベル: config.LOG_DISABLE || config.LOG_ERROR || config.LOG_WARN || config.LOG_INFO || config.LOG_DEBUG
    logLevel: config.LOG_INFO,

    // ファイルの変更を監視してテストを自動的に実行するかどうか。filesで指定したファイルを監視して変更があったら再実行してくれます。
    autoWatch: true,

    // テストするブラウザ。ここから探せる https://npmjs.org/browse/keyword/karma-launcher
    browsers: ['Chrome'],

    // trueにすると一回テストを実行するとプロセスが終了する
    // CIのときに使ったり。
    singleRun: false
  });
};
```

# karmaブラウザ上でUnittestをデバッグしたい
chromeブラウザを使ってhttp://<hostname>:9876/などを開いて「debugger;」などを挿入することによってテストが実行できそうです。
- http://qiita.com/edwardkenfox/items/4fa997ae1e9d3aefba1a
- http://qiita.com/kazusa-qooq/items/adfc6070ccbc87563fec

手順としてはテストを次の通り
- breakしておきたい箇所にdebugger;を仕込んでおく
- karmaを実行する。single-runはfalseを指定する。
```
$ karma start ./karma.conf.js --browsers=PhantomJS_custom --single-run=false
- http://<hostname>:9876/でブラウザを開く。画面右上に「DEBUG」ボタンがあるのでこれを押下する
```
- 

# TODO
- karmaのプラグインを見る
- karmaブラウザでデバッグする方法について知りたい

