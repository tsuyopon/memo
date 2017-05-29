# 概要
node-inspectorを利用すると、サーバサイドで動作しているJavascriptをブラウザでステップ実行したり、バックトレースを表示したりすることができます。  
以下のコマンドでインストールすることができます。
```
$ npm install -g node-inspector
```

なお、これに対応してるブラウザは CHROME だけですので注意が必要です。

# 使ってみる

サーバサイドではnodeを次のようにして起動します。
```
$ node --debug
```

たとえば、ファイルの先頭行(1行目)にブレークポイントを設定したいような場合には--debug-brkを利用します。
function()で囲まれたクロージャーのような場合などに便利です。
```
$ node --debug-brk path/to/hoge.js
```

実はデバッグモードにするには上記のように起動する他にもUSR1シグナルを送ることでも可能です。
```
$ kill -s USR1 `pgrep -l node`
```

nodeをdebugオプション付きで起動したらサーバ上でnode-inspectorも起動しておきます。
```
$ node-inspector

Node Inspector v0.5.0
   info  - socket.io started
   Visit http://127.0.0.1:8080/debug?port=5858 to start debugging.
```

これで**CHROME**ブラウザから以下のようにしてアクセスすることができます。
```
http://<hostname>:8080/debug?port=5858
```

以下のようなことを試して見てください。
- ブレークポイントを貼ってみる
- ブレークポイントからバックトレース関数を眺めてみる
- 変数の値などを動的に確認してみる
- next実行やstep実行などを行ってみる

### ブラウザ待ち受けやデバッグポートを変更する。
あまり使う機会などはないかもしれませんが、次のようにすると変更できるようです。
```
$ node-inspector --web-port 8081 --debug-port 5859
```

# TODO
- node6.3.0以降だと --inspectというオプションが出来たらしいので調査してもいいかも
  - http://qiita.com/y_fujieda/items/c190cbcc2fab6dd49809
- node-inspectorのオプションがgithubにいろいろ書かれているので試してみてもいいかも

# 参考URL
- github/node-inspector
  - https://github.com/node-inspector/node-inspector
