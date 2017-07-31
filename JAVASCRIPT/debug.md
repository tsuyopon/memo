# 概要
Javascriptのデバッグに関するテクニックについて
chromeツールが絶大な威力を発揮するので、下２つのページは見ておいた方がいいかもしれない。

- Chrome DevTools Overview
  - https://developer.chrome.com/devtools#debugging-JavaScript
- Chrome DevTools 
  - 各項目の詳細な説明がされている
  - https://developers.google.com/web/tools/chrome-devtools/

Chromeの機能として以下のドキュメントが多くを紹介しているのでこれも目を通しておくとよさそう
- http://www.buildinsider.net/web/chromedevtools/01

# 詳細

### Objectを文字列として表示させたい。

console.log(obj)のようにObjectであるobj引数をそのまま指定すると次のようにHobbyが束ねられてしまうことがあります。
```
var obj = {"Name":"John","Hobby":[{"Hobby1":"Tennis"},{"Hobby2":"Golf"}]};
console.log(obj);

// 出力結果
Object{ Name="John", "Hobby"=[2] }
```

Objectとしてではなくjson文字列などどでconsole.log等に出したい場合には次のようにします。
```
var obj = {"Name":"John","Hobby":[{"Hobby1":"Tennis"},{"Hobby2":"Golf"}]};
console.log(obj.toSource());

// 出力結果としてはobjがそのまま表示される。
```

### 定番console
```
console.log("log");
console.error("error");
console.warn("warn");
console.info("info");
console.debug("debug");

// formatも可能
console.log("Hello %s", "Brian");

// CSSで表示できるらしい(大文字にして目立たせたいとか色つけたいとかに便利)
console.log("%choge","color:red;font-size:50px;");
```

formatは次のようになっています
```
%s 文字列
%d, %i 数値
%f 浮動小数点数
%o オブジェクトへのリンク
```

配列などを見るときにはconsole.logとconsole.tableがある。console.tableはテーブル形式となる。
```
var array=[{
  key1:'value1',
  key2:'value2',
  key3:'value3',
}];
console.log(array);
console.table(array);
```

HTMLタグが表示されるところが階層形式で詳細をみることができる

- (参考) http://kazefuku.net/archives/1265
```
var elm = document.getElementById('hoge');
console.log(elm);
console.dir(elm);
```
DOMエレメントのツリーを見やすくする
- http://qiita.com/kashira2339/items/874f95aaaa59f4a17d3d

例えば、aタグだけを表示したい場合には次のようにする。
```
console.dirxml(document.getElementsByTagName('a'));
```

以下のようにしてログをまとめることもできる。
```
console.groupCollapsed('hoge');
console.log('A');
console.log('B');
console.log('C');
console.groupEnd('hoge');
```

assertすることもできる。以下の例では第１引数に明示的にtrue, falseを入れてしまっているがあくまで例としてです。
```
console.assert( false, "falseなので実行されます");
console.assert( true, "trueなので実行されません");
```

consoleについては他にもいろいろあるので以下を参考に
- https://github.com/DeveloperToolsWG/console-object/blob/master/api.md

### プロファイリングする(これも実はconsole)
a間、b間、c間のプロファイリングを取得することができます。
```
console.profile('a');
 
console.profile('b');
hoge();
console.profileEnd('b');
 
console.profile('c');
fuga();
console.profileEnd('c');
 
console.profileEnd('a');
```

### エラーしたらサーバ側でクライアントのエラーを取得する
window.onerrorを使って収集することができるようです。
```
window.onerror = function(msg, url, line){
	// ここにAPIにリクエストする処理を記述する
}
```

詳しくは以下を参考のこと
- http://postd.cc/how-to-not-hate-javascript-tips-from-the-frontline/

### 時間計測
timeで指定したグループの時間計測で、timeStampでそのメソッドを実行したときの時間を表示します
```
console.timeStamp('start');
console.time('timer0');

console.time('timer1');
// 処理
console.timeEnd('timer1');

console.time('timer0');
console.timeStamp('stop');
```

### サーバ側にエラーを送る
エラーが見つかったらHTTP経由でサーバにエラーを送る方法です。  
サーバ側には1つエラーを取得するためのエントリポイントを準備する必要があります
- http://postd.cc/how-to-not-hate-javascript-tips-from-the-frontline/

### 関数のスタックトレースを表示する。
スタックトレースを表示したい箇所で以下を挿入します。
```
console.trace();
```

### ブレークポイントを使う
Developer Toolsであれば「Source」タブを開いて行番号を押下すればブレークポイントを設定できる。

Chromeのアイコンについては以下に公式説明があるので参考にすること
- https://developers.google.com/web/tools/chrome-devtools/javascript/step-code

条件式にマッチした変数の時にだけブレークするといったことも可能らしい。以下を参考のこと
- https://developers.google.com/web/tools/chrome-devtools/javascript/add-breakpoints

明示的に停止したければソースコードでブレークしたい箇所に以下を挿入すれば良い
```
debugger;
```

### 条件付きbreakする方法
ブレークポイントを右クリックして「Edit breakpoint」を選択します。
ブレーク条件を指定します。たとえば、次のような感じで指定します。
```
e !=  null
```

参考
- http://qiita.com/Shinji-Hashimoto/items/e6ab00be4f3dfbc20855

### どこで例外が発生したかを知る方法
(||)マークを押下します。詳細は以下のURLを参考のこと
参考
- http://qiita.com/Shinji-Hashimoto/items/e6ab00be4f3dfbc20855

### XHR Breakpoints
指定したURLへのAjax通信が発生した時にbreakする方法です。  
SourcesパネルのXHR Breakpointsのアコーディオンを開いて、右クリックまたは+ボタンで任意のURLを指定します。

URLを空で設定するとすべての通信時にブレイクする「Any HXR」として設定されます。


参考
- http://qiita.com/Shinji-Hashimoto/items/e6ab00be4f3dfbc20855

### Event Listender Breakpoints
どこかでイベントが発生したときにbreakする方法です。
たとえば、クリックイベントが発生した時などbreakするイベントは指定することができます。

SourcesパネルのEvent Listender Breakpointsのアコーディオンを開くと様々なイベントが表示されます。 
任意のイベントを選択状態にしておくとイベント発生時にbreakします。

参考
- http://qiita.com/Shinji-Hashimoto/items/e6ab00be4f3dfbc20855

### 要素の変更時にbreakする方法
Elementsパネルでbreakさせたい要素を右クリックして「Break on...」を選択して、次のいずれかを選択する。
* subtree modifications
** 子要素の変更時
* attribute modifications
** 該当要素の属性変更時
* node removal
** 要素削除時

参考
- http://qiita.com/Shinji-Hashimoto/items/e6ab00be4f3dfbc20855


### 実行している関数名を取得する

ES6であれば次のようなことが可能
```
function functionName(fun) {
  console.log(myFunction.name);         // xxxx.nameにより取得可能。xxxxは関数名となる
  var ret = fun.toString();
  ret = ret.substr('function '.length);
  ret = ret.substr(0, ret.indexOf('('));
  return ret;
}
```

ちなみに無名関数であればcallee.nameを使うと良い
```
var x = function x() {
    console.log( arguments.callee.name );
}
x();
```

この辺の詳細については以下を参照のこと
- https://stackoverflow.com/questions/2648293/javascript-get-function-name

### alert
昔はよくアラート使っていたがブラウザじゃないと利用できないのであまりもう利用しないかも
```
alert('hoge');
```


### HTML要素の位置が知りたい
Developer Toolsであれば画面をポインティングしているアイコンを押下して画面にoverlayすれば、その箇所のHTML要素をしることができる。
また、その要素の値をダブルクリックすればその値を変更することもできる。

### パフォーマンスに関するデバッグがしたい
chromeではパフォーマンス用のデバッグツールを提供している。
- http://qiita.com/y_fujieda/items/a0a69151cf7307039f74

### CSSをデバッグしたい
上記のテクニックでUIの特定の箇所を選択し、「Styles」タブを開くと指定したDOMの該当CSSが表示される。
特定の属性名にカーソルを乗せるとチェックボックスが表示されるのでこれでonにしたりoffにしたりすることができる。また、値を変更することもできる。

### chromeでできるデバッグについて
```
chrome://chrome-urls/
```
この辺にアクセスしてみると様々なデバッグに関する項目が表示される

### リクエストを投げてみる
- chrome
  - https://chrome.google.com/webstore/detail/dhc-restlet-client/aejoelaoggembcahagimdiliamlcdmfm

この辺を参考にするとよさそう
- http://qiita.com/snoguchi/items/8f6bb62a3166eca23ac3

### webpackのデバッグをChrome Developer Toolsで行う。
webpack.config.jsに以下の1行を加える
```
devtool: 'inline-source-map',
```
"debug: true"も必要と書かれている時もあったがちゃんと検証できていない。

inline-source-mapの他にもsource-map関連はいくつか設定がある。
- http://webpack.github.io/docs/configuration.html#devtool

あとは以下を実行するとwebpack.config.jsを読み込んでビルドします。
```
$ webpack
```

あとはChromeを開いて「Source」タブをクリックすると画面左側に「webpack://」という項目があれば、ブレークポイントを貼って調査することなどができる。

### Angularのデバッグ
試したわけではないがchromeで以下のプラグインがあるらしい
- https://chrome.google.com/webstore/detail/ng-inspector-for-angularj/aadgmnobpdmgmigaicncghmmoeflnamj

### knockout.jsのデバッグ方法
- http://qiita.com/MKGaru/items/4cf6fa1373357510b15e
- http://qiita.com/hiradimir/items/1934be2b55ea5a51f208
- http://stackoverflow.com/questions/9261296/how-to-debug-template-binding-errors-for-knockoutjs

# 参考URL
- http://postd.cc/how-to-not-hate-javascript-tips-from-the-frontline/
- JavascriptのChromeでのデバッグ方法個人的まとめ2016
  - http://qiita.com/snoguchi/items/8f6bb62a3166eca23ac3
- JavaScriptのデバッグ方法 – JSを嫌いにならないためのTips
  - http://postd.cc/how-to-not-hate-javascript-tips-from-the-frontline/
- Chromeが用意しているデバッグのためのページ
  - chromeでできるデバッグUA変更、位置情報、DOM変更、CSS変更、Network、Timeline、Profileなどについて載っている
  - https://developers.google.com/web/tools/chrome-devtools/
- How can I debug my JavaScript code?
  - http://stackoverflow.com/questions/988363/how-can-i-debug-my-javascript-code
