# 概要
Node.jsのデバッグ方法について

### ブレークポイントとして停止させたい
chromeなどのブラウザと同様にnodeも次の構文を入れるとその箇所で停止させることができます。
```
debugger;
```

あとは実行時にdebugオプションを付与します。
```
$ node debug xxx.js
```

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
