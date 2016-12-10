# ncコマンドについてまとめます。

### ncコマンドでできること
ncコマンドを使うことによってネットワークサーバにもクライアントとしても振舞うことができます。
- TCPおよびUDPの、任意のポートを対象とした読み書き
- ポートスキャン機能
- TCPサーバとしての起動
- telnetとして使う
- ローカルソースポートの指定
- ローカルソースアドレスの指定(詐称)

ncコマンドの基本的なオプションについて
```
-e コマンドを実行（コンパイル時の指定が必要)
-l リッスンモード
-u UDPモードにて通信を行う
-n 名前解決を行わない
-s ソースポートを指定
-z スキャンのみを行い、データを送らない。
```

* 参考URL:
	* ncチートシート: http://www.sans.org/security-resources/sec560/netcat_cheat_sheet_v1.pdf

### ファイル転送を行う
転送される側では適当なポート(ここでは10025ポートと仮定)でLISTENし、出力は全てfile.tgzとする。
```
$ nc -l 10025  > file.tgz
```

転送する側は以下のようにする。
```
$ nc host.example.com 10025 < func.php
```

正しくファイル内容が送付されたかどうかなどはmd5sumを使って調べておいたほうがよい。  
ncコマンドを使うとファイル転送を非常に高速に実現してくれるらしい

### 多段SSHをする場合
uchiからremoteに接続するするキワにotonari, genkanを経由する必要があるとした場合、
```
uchi -((-> otonari ----> genkan -))-> remote
```

.ssh configを以下のように記述します
```
$ cat ~/.ssh/config
Host  remote
  ProxyCommand  ssh genkan  nc -w 10 remote 22
Host  genkan
  ProxyCommand  ssh otonari nc -w 10 genkan  22
Host  otonari
  User          azarashi
  Port          22
```

以下のようにすれば一撃でアクセスすることができます。
```
$ ssh remote ls -al
```

もちろん接続やscpも可能です。
```
$ ssh remote
```

(参考) http://d.hatena.ne.jp/hirose31/20070419/1176968993

### .ssh/configにProxyCommandを記述する
(上と同じ??)
passproxy.comにログインせずに一気にremoteserver.comにsshログインやscpするための設定
```
Host remoteserver.com
  ProxyCommand ssh passproxy.com nc %h %p
```


### TCPサーバとしてLISTENする
サーバとしてTCP:12345ポートでLISTENモードにします。
```
$ nc -l 12345
```

ncサーバに接続するには以下のようにすればOK
```
$ nc localhost 12345
```

### UDPサーバとしてLISTENする。
サーバとしてUDP:12345ポートでLISTENモードにします。
```
$ nc -u -l 12345
```

ncサーバに接続するには以下のようにすればOK
```
$ nc -u localhost 10025
```

### TCPサーバに接続する
host.example.comの42番ポートに31337ポートを使って接続する。タイムアウトを5秒とする
```
$ nc -p 31337 -w 5 host.example.com 42
```

### IPアドレスを10.1.2.3に偽装してhost.example.com:42に接続する
```
$ nc -s 10.1.2.3 host.example.com 42
```

### 簡易HTTPサーバとして機能
```
$ ( echo "HTTP/1.0 200 Ok"; echo;  ) |  nc -l 12345
```

### HTTP GETリクエスト
```
$ echo -en "GET / HTTP/1.1\n\n" | nc localhost 80
```

### UDPモードで接続する
```
$ nc -u host.example.com 53
```

### 全ポートスキャン
セキュリティチェックなどのためにローカルホストで実施すること。
```
$ nc -zv localhost 1-65535
```

### プロキシ経由での利用
HTTP Proxyとして10.2.3.4:8080を経由して、host.example.com:42にアクセスする
```
$ nc -x10.2.3.4:8080 -Xconnect host.example.com 42
```

### 各種サーバへのアクセス例
- Redisサーバへアクセス
```
$ (echo 'set KEY1 hoge'; sleep 1s; echo 'key *') | nc localhost 6379
```

- メールを送信する
```
$ nc localhost 25 << EOF
HELO host.example.com
MAIL FROM:<user@host.example.com>
RCPT TO:<user2@host.example.com>
DATA
Body of email.
.
QUIT
EOF
```

memcachedにアクセス
```
$ echo flush_al | nc localhost 11211
```

# 参考URL
- nc コマンド 使い方メモ: Qiita
 - http://qiita.com/yasuhiroki/items/d470829ab2e30ee6203f
- ncのManpage
 - http://www.computerhope.com/unix/nc.htm
