# 概要
Javascriptのデバッグに関するテクニックについて
chromeツールが絶大な威力を発揮するので、下２つのページは見ておいた方がいいかもしれない。

- Chrome DevTools Overview
 - https://developer.chrome.com/devtools#debugging-JavaScript
- Chrome DevTools 
 - 各項目の詳細な説明がされている
 - https://developers.google.com/web/tools/chrome-devtools/

# 詳細

### alert
昔はよくアラート使っていたがいまではつかわないかな。。。
```
alert('hoge');
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

### HTML要素の位置が知りたい
Developer Toolsであれば画面をポインティングしているアイコンを押下して画面にoverlayすれば、その箇所のHTML要素をしることができる。
また、その要素の値をダブルクリックすればその値を変更することもできる。

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

# 詳細
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
