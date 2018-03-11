# 概要
nodejsについての歴史や基本事項について

# 詳細
## nodejsに関する歴史 

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

## 起動する

### nodeをコマンドラインから直接実行する
プログラムをコマンドライン経由で実行したい場合には次のようにすれば良い
```
$ node -e "console.log('hello world');"
```

### オプションを確認する
以下のコマンドを実行します。ただし、オプションがありすぎて出力が多いです。
```
$ node --v8-options
```

たとえば、logでgrepしただけでもこれだけものオプションがあります。
```
$ node --v8-options | grep log
  --log (Minimal logging (no API, code, GC, suspect, or handles samples).)
  --log_all (Log all events to the log file.)
  --log_runtime (Activate runtime system %Log call.)
  --log_api (Log API events to the log file.)
  --log_code (Log code events to the log file without profiling.)
  --log_gc (Log heap samples on garbage collection for the hp2ps tool.)
  --log_handles (Log global handle events.)
  --log_snapshot_positions (log positions of (de)serialized objects in the snapshot.)
  --log_suspect (Log suspect operations.)
  --prof (Log statistical profiling information (implies --log-code).)
  --prof_lazy (Used with --prof, only does sampling and logging when profiler is active (implies --noprof_auto).)
  --log_regexp (Log regular expression execution.)
  --logfile (Specify the name of the log file.)
        type: string  default: v8.log
```

### 簡単に起動する(package.jsonを利用)
package.jsonを利用した方法で次のような内容を記述しておけば、NODE_ENV, NODE_PATHなども指定して実行できます。
```
"scripts": {
  "start": "NODE_ENV=production NODE_PATH=lib node --harmony_typeof --harmony"
}
```

次のコマンドでnodeを起動することができるようになります。
```
$ npm run start
```


## 便利な環境変数

### NODE_PATH環境変数
jsファイルに次のように<path_to>を毎回書くのは面倒なので、これはNODE_PATHにライブラリなどを追加することで解決します。
```
require('<path_to>/my_util');
```

たとえば、<path_to>/my_util.jsの<path_to>をlibと仮定すると次のように記述すると
```
NODE_PATH=lib node server.js
```

この場合にはserver.jsのrequireは次のように記述すればよくなり、相対パスなどで汚くならなくてすみます。
```
require('my_util');
```

### Node.jsがモジュールを探しにいくパスを表示する。
```
$ node -e "console.log(global.module.paths)"
[ '/home/vagrant/node_modules',
  '/home/node_modules',
  '/node_modules' ]
```
上記に不足しているようで「Cannot find module xxxx」などと表示されるようであればNODE_PATHに追加するとよい。

### NODE_DEBUG環境変数
以下の例ではhttpとnetモジュールを指定して作成したサーバを起動してデバッグ出力を見ています。
```
$ NODE_DEBUG=http,net node server.js
NET: bind to 0.0.0.0
NET: onconnection
HTTP: SERVER new http connection
NET: onconnection
HTTP: SERVER new http connection
HTTP: server response shouldKeepAlive: true
HTTP: outgoing message end.
HTTP: server response shouldKeepAlive: true
HTTP: outgoing message end.
```

NODE_DEBUG環境変数には次のような値を指定することができるようです。上記ではカンマがセパレータとして指定されていますが、なんでもいいようです。
- cluster
- net
- http
- fs
- tls
- module
- timers

- 参考
  - http://www.juliengilli.com/2013/05/26/Using-Node.js-NODE_DEBUG-for-fun-and-profit/

### NODE_XXX環境変数を使ってスクリプトからその値を利用できるようにする。
基本は起動時に使います。
xxx=yyy という変数をつけて実行すると、ランタイムからはprocess.env.xxx で yyy の値を文字列値として受け取れるようになります。
```
$ NODE_MY_FLG=true node server.js
```

### Node.jsのバインディング(C++ Native拡張)の作り方
この辺を参考にすること
- https://qiita.com/castaneai/items/f82b2523bcb603e42ea7

手順としては
- 1.ソースコードやbinding.gypを準備する。
- 2.以下のコマンドを実行する
```
$ node-gyp configure
$ node-gyp build
```
- 3. build/フォルダが作成されて、build/Release/xxxx.nodeといった拡張子のバイナリが生成される。
- 4. 次のようにして利用することができる
```
var hoge = requre('./hoge');
console.log(hoge);
```

なお、nodeはバージョンの進化が激しく微妙にバージョンごとに差異を吸収してくれる仕組みとしてNANというものがあります。
```
$ npm install --save nan
```

そして、binding.gypで次のinclude_dirsの1行を加える必要があります。プログラム側もNANに合わせて書き換えます(詳細は上のURLを参考のこと)
```
 {
   "targets": [
     {
       "target_name": "my_extension",
       "sources": ["my_extension.cc"],
+      "include_dirs": ["<!(node -e \"require('nan')\")"]
     }
   ]
 }
```

余談: binding.gypのgypはGenerate Your Projectsの略称です。

以下は参考資料
- node_gyp
  - https://github.com/nodejs/node-gyp
- nan
  - https://github.com/nodejs/nan

gypの仕様書?
- https://gyp.gsrc.io/docs/LanguageSpecification.md

スライドシェアもあります
- https://www.slideshare.net/shigeki_ohtsu/nodegakuen5-ohtsu

### UbuntuにNodeの最新バージョンを入れる + nodeバージョンの切り替えもできるようにする。
自前のVirtualBoxにすごい簡単にVirtualBoxを入れる方法があったのでそのメモとなります。以下を参考にします。
- https://qiita.com/seibe/items/36cef7df85fe2cefa3ea

まずは最初にnodejsとnpmをインストールしておきます。
```
$ sudo apt-get install -y nodejs npm
```

次のnという一文字の名前のnpmパッケージをインストールします。
- https://github.com/tj/n

次のコマンドでインストールすることができます。
```
$ sudo npm cache clean
$ sudo npm install n -g
/usr/local/bin/n -> /usr/local/lib/node_modules/n/bin/n
n@2.1.8 /usr/local/lib/node_modules/n
```

npackageを使ってnodeをインストールします。
```
$ sudo n stable

     install : node-v8.6.0
       mkdir : /usr/local/n/versions/node/8.6.0
       fetch : https://nodejs.org/dist/v8.6.0/node-v8.6.0-linux-x64.tar.gz
######################################################################## 100.0%
   installed : v8.6.0

$ sudo ln -sf /usr/local/bin/node /usr/bin/node
```

バージョンを確認してみます。
```
$node -v
v8.6.0
```

nのnpmパッケージをインストールするために入れた不要なパッケージは混乱のもととなるので削除します。
```
$sudo apt-get purge -y nodejs npm 
```

以上で最新バージョンを入れることができました。  

ちなみに、バージョンを切り替えることも可能です。たとえば、v4.2.3に切り替える場合には次のようになります。
git fetchで取得してくれるようになります。
```
$sudo n 4.2.3

     install : node-v4.2.3
       mkdir : /usr/local/n/versions/node/4.2.3
       fetch : https://nodejs.org/dist/v4.2.3/node-v4.2.3-linux-x64.tar.gz
######################################################################## 100.0%
   installed : v4.2.3

$node -v
v4.2.3
```

- 参考URL
  - https://qiita.com/seibe/items/36cef7df85fe2cefa3ea

# 参考URL
- http://jxck.hatenablog.com/entry/20120410/1334071898

