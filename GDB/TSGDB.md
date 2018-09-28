# 概要
trafficserverでgdbを利用するにあたってよく使うTIPS

# 詳細

### コアファイルを確認する
コアファイルをcoreとして次のようにします。
```
$ sudo gdb traffic_server core
```

### 起動時から確認する
コアファイルをcoreとして次のようにします。
runの後には引数を指定します。
```
$ sudo gdb traffic_server
(gdb) 予め起動時にしかけたいブレークポイントがあればここで設定する。
(gdb) run start
```

### 特定のスレッドを無視する
以下は複数のスレッドを無視する場合である。

注意するのは||ではなく、&&条件で指定しているところである。
```
(gdb) b Continuation::handleEvent if ( ($_thread != 2) && ($_thread != 4) )
Breakpoint 1 at 0x51ce05: file /home/tsuyoshi/trafficserver/iocore/eventsystem/I_Continuation.h, line 153.
(gdb) c
Continuing.
```

### SIGPIPEを無視する
SIGPIPEを受け取ると、次のような出力を表示して再度ブレークポイントに入ってしまう
```
Program received signal SIGPIPE, Broken pipe.
[Switching to Thread 0x7f42450ff700 (LWP 14497)]
0x00007f424789d6ad in write () from /lib64/libpthread.so.0
```

次のコマンドを実行するとSIGPIPEを無視します。
```
(gdb)  handle SIGPIPE nostop
Signal        Stop	Print	Pass to program	Description
SIGPIPE       No	Yes	Yes		Broken pipe
(gdb) c
Continuing.
```

### 他のプロセスからの
traffic_serverをデバッグする際にtraffic_copやtraffic_managerプロセスが邪魔となります。
それは次のような操作を行っているからです。
- 他のプロセスからヘルスチェックのためにリクエストされるエントリポイント、
- 応答しなくなったプロセスを再起動する

gdbを開始する前に次の操作を行っておきましょう。
```
$ sudo kill -STOP `pidof /opt/trafficserver-7.1.x/bin/traffic_manager` `pidof /opt/trafficserver-7.1.x/bin/traffic_cop`
```

終わったらプロセスを再開します。
```
$ sudo kill -CONT `pidof /opt/trafficserver-7.1.x/bin/traffic_manager` `pidof /opt/trafficserver-7.1.x/bin/traffic_cop`
```

### directoryもまるごと指定する。
手元にソースコードがある場合には、次のようにしてデバッグすると便利です。
以下はtrafficserverディレクトリ直下で実行していることを想定したコマンドです。(パスは適宜変更してください)
```
$ sudo gdb `find iocore proxy -type d -printf '-d %p '`  -p `pidof /opt/trafficserver-7.1.x/bin/traffic_server`
```

上記でgdbが起動したら次のコマンドを実行することで、シングルキーモードでソースコードを表示しながらデバッグをするとかなりはかどります。
```
Ctrl +x, u
```

