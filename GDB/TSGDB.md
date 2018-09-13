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

