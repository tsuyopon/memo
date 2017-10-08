# 概要
Node.jsのC++ Binding(Addon)に関するメモなど

# 詳細
### node.jsバージョンに関する歴史
下記を参考にすることが出来ます。
- https://nodejs.org/ja/download/releases/

io.jsとはNode.jsのフォークで、v0.12をフォークしています。
- https://nodejs.org/ja/download/releases/

io.jsができた経緯としては、次のような理由でした。
- アクティブじゃなくて、新しいコントリビュータがいなくて、リリースが滞っているNodeプロジェクトの現体制を動かそうって試みていたんだよ。
- "Node.js"っていう商標権はJoyentが持っていて、そこの問題がクリアになるまで新しいNode.jsはリリースできないから、名前を"io.js"に変えることにしたんだ。

つまり、
Node.jsは現時点でリリーススケジュールがちゃんとworkしていません。issueが登録されてもそれがさばかれずに放置されたり、pull-reqが滞ることが多く、この一年くらいそういう感じになってしまっていました。io.jsはこの体制を変えようという活動です。

この辺の記事もio.jsとnode.jsの理解に役立ちます。
- https://mag.osdn.jp/15/09/11/070600

1.xから3.xはio.jsのフォークによって「io.js」と呼ばれていました。その後、Node.jsとio.jsはNode.jsは4.0.0で合流しました。
- Node.js
  - 0.1.x, 0.2.x, 0.3.x, 0.4.x, 0.6.x, 0.7.x, 0.8.x, 0.9.x, 0.10.x, 0.11.x, 0.12.x
- io.js
  - 1.0.x, 1.1.x, 1.2.x, 1.3.x, 1.4.x, 1.5.x, 1.6.x, 1.7.x, 1.8.x, 2.0.x, 2.1.x, 2.2.x, 2.3.x, 2.4.x, 2.5.x, 3.0.x, 3.1.x, 3.2.x, 3.3.x
- Node.js
  - 4.x.x, 5.x.x, 6.x.x, 7.x.x, 8.x.x

### バージョンにごとの差異など

奇数バージョンと偶数バージョンでLTMサポート方針が異なるようだ。
変更点については以下の
- https://github.com/nodejs/node/blob/master/CHANGEaLOG.md#2016-04-26-version-600-current-jasnell

以下に各バージョンの違いの概要だけを記す
- Node.js V4.0.0(LTS)
  - io.jsのv1からv3で含まれる機能が全て利用可能となりました。
  - 「V8エンジン v4.5」を採用により以下の機能をサポート
    - ES2015サポート範囲拡大
	- StrongScript等のJavaScriptの新機能対応
	- Intlオブジェクトのサポートによる国際化対応
  - 参考URL
    - https://html5experts.jp/yosuke_furukawa/17791/
- Node.js V6.0.0(LTS)
  - 「V8エンジン v5.0」を採用によりES2015サポートの改善(58%から96%まで改善した)
  - module_load性能の改善で、requireしたときの性能が初期ロードで3倍高速に、2回目以降のcache付きロードでは5倍高速となった。
  - 参考URL
    - http://yosuke-furukawa.hatenablog.com/entry/2016/04/27/110027
- Node.js v8.0.0(LTS)
  - v7.0.xの安定版
  - 「V8エンジン 5.4を採用」、ES6カバー率98%、信頼性とパフォーマンス向上の実現 
  - async/awaitをサポートする最初のLTSバージョン
  - npm5.0も含む
  - 参考URL
    - http://abouthiroppy.hatenablog.jp/entry/2017/05/30/090015

nodeバージョン、V8バージョン、NPMバージョンなどの関係性は以下を参考のこと
- https://nodejs.org/ja/download/releases/

以下の記事なども参考のこと
- 2年ぶりの最新版となる「Node 0.12」がリリース
  - https://mag.osdn.jp/15/02/10/092000
- Node.jsからフォークした「io.js」バージョン1.0系がリリースされる
  - https://mag.osdn.jp/15/01/16/160000
- Node.jsからフォークした「io.js」の最新版、「io.js 3.0」リリース。最後のリリースとなるか
  - https://mag.osdn.jp/15/08/08/053900

### v0.12, v4の違いは?
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
