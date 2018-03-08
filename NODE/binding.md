# 概要
Node.jsのC++ Binding(Addon)に関するメモなど

# 詳細

### Nodejsのv0.12, v4の違いは?
以下の記事を参考にすると、
- JavaScriptのレイヤは互換性があります。ほとんどのモジュールはそのまま動くでしょう。
- C++バインディングを利用して作られるライブラリはV8がバージョンアップされたことに伴い、内部のABIが崩れて動かなくなります。

参考URL
- https://html5experts.jp/yosuke_furukawa/17791/
- https://github.com/nodejs/node/issues/2798

### Node.jsのサンプルモジュール
以下にサンプルが存在していてそれぞれにnan, node_0.10, node_0.12といった3つのディレクトリが存在する。  
基本的にはnanによるビルドができれば、おそらくNode4以降のV8エンジンの各種バージョンの差異を吸収してくれると思われる。
- https://github.com/nodejs/node-addon-examples

予めビルド用に必要となるnode-gypをインストールしておきます。
```
$ sudo npm install node-gyp -g
```

あとはnanディレクトリに移動したら、次のコマンドを実行するだけビルド、実行までができるはずです。
```
$ npm install
$ node-gyp rebuild
$ node ./
```

### NAN(Native Abstractions for Node.js)
Nodeのアドオン(Nativeのコードをnode.jsで利用するしくみ)はV8に依存しており、バージョンアップごとにV8の変更に大きく依存する。  
そのため、後方互換性が保たれないという問題が有ります。

NANというモジュールをかませることによって、NODEのアドオンがnode.jsのバージョンに依存しないようになります。

nodejs-0.12からnanのAPIを使った変更を行うためにはAPI周りを変更する必要があります。以下のREADME.mdに詳しく記載されています。
- https://github.com/nodejs/nan

# 参考URL
- C++ Addons
  - https://nodejs.org/dist/latest-v4.x/docs/api/addons.html
  - https://nodejs.org/dist/latest-v6.x/docs/api/addons.html
  - https://nodejs.org/dist/latest-v8.x/docs/api/addons.html
- nodeバージョン、V8バージョン、NPMバージョンなどの関係性は以下を参考のこと
  - https://nodejs.org/ja/download/releases/
- Nodeのバージョンにおける変更点について
  - https://github.com/nodejs/node/blob/master/CHANGEaLOG.md#2016-04-26-version-600-current-jasnell
- github
  - NodejsのC++バインディングをビルドするための仕組み
    - https://github.com/nodejs/node-gyp
  - Nodeのバージョンが上がってもV8依存を意識しないようにするための仕組み
    - https://github.com/nodejs/nan
  - NodejsのC++バインディングのサンプルモジュール
    - https://github.com/nodejs/node-addon-examples
  - node中にあるサンプル(nanは使われていない)
    - https://github.com/nodejs/node/tree/master/test/addons
