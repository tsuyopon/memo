# 概要
Node.jsのデバッグ方法について

# 詳細

### 該当箇所を通った際にスタックトレースを表示したい
通った場合にスタックトレースを表示したい箇所に以下を仕込みます。
```
console.trace();
```

または次のようにします。
```
var stack = new Error().stack
console.log( stack )
```

### exceptionを受け取った場合にスタックトレースを表示したい
```
try {  
  // if something unexpected
  throw new Error("Something unexpected has occurred.");     

} catch (e) {
  console.error(e);
}
```

ログには次のように表示されます。
```
Error: Something unexpected has occurred.
    at main (c:\Users\Me\Documents\MyApp\app.js:9:15)
    at Object. (c:\Users\Me\Documents\MyApp\app.js:17:1)
    at Module._compile (module.js:460:26)
    at Object.Module._extensions..js (module.js:478:10)
    at Module.load (module.js:355:32)
    at Function.Module._load (module.js:310:12)
    at Function.Module.runMain (module.js:501:10)
    at startup (node.js:129:16)
    at node.js:814:3
```

- 参考
  - https://stackoverflow.com/questions/2923858/how-to-print-a-stack-trace-in-node-js

### node.jsのconsole対応状況を知りたい
consoleについては色々種類があるのでJAVASCRIPT/debug.mdを参考にすること

以下の記事によると、、
- https://qiita.com/ysm001/items/9abcacf74ead8a871540

node v4.1.1では次のメソッドに対応しているとのこと
```
log
info
warn
error
dir
time
timeEnd
trace
assert
```

### ブレークポイントとして停止させたい
chromeなどのブラウザと同様にnodeも次の構文を入れるとその箇所で停止させることができます。
```
debugger;
```

あとは実行時にdebugオプションを付与します。
```
$ node debug xxx.js
```


### Node.jsデバッガについて(v6.3.0未満)
node-inspectorというパッケージがあるのでこちらを利用してデバッグします(0.10, 0.12などでも利用できるはず)
詳細はnode-inspector.mdを参考にしてください。
- https://www.npmjs.com/package/node-inspector

node4やnode6ではdebugオプションがあるのでそちらで利用することも可能

### Node.jsデバッガについて
Node.jsデバッガの歴史やinspectオプションについては本家を参照のこと
- https://nodejs.org/en/docs/guides/debugging-getting-started/

以前まではnode-inspectorでした(使い方はnode-inspector.mdを参照のこと)
- https://www.npmjs.com/package/node-inspector

その後、node4やnode6系ではdebugオプションが利用できるようになりました。しかしv7.7.0からdeprecated扱いとなっています。
- https://nodejs.org/dist/latest-v6.x/docs/api/debugger.html
```
$ node debug myscript.js
< Debugger listening on [::]:5858
connecting to 127.0.0.1:5858 ... ok
break in /home/indutny/Code/git/indutny/myscript.js:1
> 1 global.x = 5;
  2 setTimeout(() => {
  3   debugger;
  debug>
```

### Node.jsデバッガについて(v6.3.0以降)
Nodejs v6.3.0以降では「--inspect」フラグを付けることでデバッグが可能です。
実行時に最初の行で止めたい場合は、「--debug-brk」フラグを付けると止まります
```
$ node --inspect --debug-brk app.js
Debugger listening on 127.0.0.1:9229.
To start debugging, open the following URL in Chrome:
    chrome-devtools://devtools/bundled/inspector.html?experiments=true&v8only=true&ws=127.0.0.1:9229/dc9010dd-f8b8-4ac5-a510-c1a114ec7d29
```

上記を実行するとchromeのURLが表示されるので、これをchromeブラウザから開くとデバッグすることができます。


- 参考URL
  - https://qiita.com/y_fujieda/items/c190cbcc2fab6dd49809
  - https://qiita.com/onionmk2/items/de8a22d70e2be0b0ff92
  - https://medium.com/@paul_irish/debugging-node-js-nightlies-with-chrome-devtools-7c4a1b95ae27
