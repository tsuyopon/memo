# 概要
Linux2.6からinotify APIが利用できます。  
これによってこのAPIを通してファイルやディクレトリのopen, close, rename, remove, create, chmodなどの変更検知が可能になります。

inotify-toolsというパッケージによって次の２つの機能を提供します。
- inotifywait
 - ファイルシステムイベントが変更された際に表示する
- inotifywatch
 - ファイルシステムイベントの統計を表示する

yumの場合には次のコマンドでインストールできます。
```
$ sudo yum install inotify-tools
```

### inotifywaitコマンドを使ってみる

ではファイルの変更検知を試してみましょう。
```
$ echo notifysample > wait.txt
$ inotifywait wait.txt &
[1] 15046
Setting up watches.
Watches established.
$ echo hoge >> wait.txt
$ wait.txt OPEN               // inotifywaitによって「wait.txt OPEN」と出力された。これが終わり次第1度だけ検知してデーモンが終了する。

[1]+  Done                    inotifywait wait.txt
```

変更は１度しか検知してくれません(しかもOPEN以外にもいろいろやっているはずなのに)。複数回検知させるためには-mオプションが必要とのことです。
-mをつけて実行してみると複数個のイベントが出力されるようになりました。
```
$ inotifywait -m wait.txt &
$ echo hoge >> wait.txt
wait.txt OPEN 
wait.txt MODIFY 
wait.txt CLOSE_WRITE,CLOSE 
```

inotifywaitのオプションについて
```
-r:           対象がディレクトリ時に対象を再帰的に掘っていく
-c:           通知結果をcsvで表示
-e <event>:   eventで指定したイベントのみを通知するようにフィルタリングする
-t <seconds>: -mオプションを付けない場合にseconds秒後に監視を終了する
-d:           デーモン化して動作する。結果は-oオプション指定ファイルか、-sオプションでsyslogに書き込む
```


### inotifywatchコマンドを使ってみる
inotifywatchに引数としてファイル名を指定することで簡単に利用できる。
```
$ inotifywatch wait.txt &
[2] 15152
$ echo "hoge" >> wait.txt 
$ touch wait.txt 
$ cat wait.txt
```

統計情報を出力させるためにはUSERシグナルを与えれば良い。killでも大丈夫。
```
$ kill 15152
total  access  modify  attrib  close_write  close_nowrite  open  filename
9      1       1       1       2            1              3     wait.txt
```

# 参考URL
- Manpage of inotify
 - http://linuxjm.osdn.jp/html/LDP_man-pages/man7/inotify.7.html
- inotify-toolsでファイルやディレクトリを監視する
 - http://qiita.com/stc1988/items/464410382f8425681c20
- inotify-tools(公式github)
 - https://github.com/rvoicilas/inotify-tools
