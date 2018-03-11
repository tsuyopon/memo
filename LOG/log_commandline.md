
### svtoolsを利用する
multitailを利用すれば複数のファイルをtailすることができる。
使い方はmultitailコマンドの後ろにファイル名を並べるだけでよい。
以下に例を示す。
```
$ sudo multitail /var/log/kern.log /var/log/faillog
```

### ログの取り出し方法など
例えば、秒毎、分毎にログをカウントしたい場合には以下を利用する。
コツはawkを使用し、そのセパレータとして何を利用するか。
また、uniq -cを利用することである。
```
(例)
$ cat /var/log/messages | awk -F"-" '{print $1}' | sort | uniq -c
```

### ログを生でチェックしたい
tail -f を利用する
例えばapacheのアクセスログをチェックしたい場合には以下のようにする。
```
# tail -f /var/log/httpd/access_log
```

実はlessでも「`F」によりtailと同様のことができるらしい

### ログを書き込みたい
例えば/var/log/messagesに書き込みたい場合には以下の様にすればよい。

以下はインタラクティブモードの例である。
```
$ logger -t /var/log/messages
fsskl
test
desu
```

次にある出力結果を/var/log/messagesに記述したい場合には以下の様にする。
```
$ echo "tsuyoshi" | logger -t /var/log/messages
```
すると以下の様に書き込みされている。
```
Sep  2 06:22:40 192 /var/log/messages: tsuyoshi
```
