# 概要
コマンドラインから画像を表示したいといった場合に利用できるソフトウェアです。

# 詳細
この場合にはcacautilsパッケージ内のcacaviewコマンドが便利である。
```
$ cacaview  <ファイルパス又はURL>
```
で画像を見ることができる。

このcacaviewのデモ用として以下のコマンドがあるので、引数無しで実行してみると 意外と面白い
```
cacaball  cacademo  cacafire  cacamoir  cacaplas
```

cacaviewとw3mで連携させることができる。つまりw3mで画像を見れる。 その場合には以下の設定が~/.w3m/mailcapというファイルを新しく作成して以下を記述する。
```
image/*;        cacaview %s ;needsterminal
```
