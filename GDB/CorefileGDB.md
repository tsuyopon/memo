# 概要
コアファイルについて

## コア関連設定

#####  コアが生成されない場合
ulimitコマンド設定を見直す必要があります。
```
$ ulimit -c              // 確認コマンド
$ ulimit -c unlimited    // 無制限に変更
```

##### 起動中プロセスのコアを取得する。
gcoreコマンドにプロセスIDを指定すれば生成することができる
```
$ sudo gcore 2567
[sudo] password for tsuyoshi: 
[Thread debugging using libthread_db enabled]
Using host libthread_db library "/lib64/libthread_db.so.1".
0x00007f3325b03e47 in accept4 () from /lib64/libc.so.6
Saved corefile core.2567
$ ls core.2567
$ sudo gdb /usr/local/bin/httpd core.2567
```

#####  coreファイルが何処に作成されるか確認する
```
$ sysctl -a | grep core 
kern.corefile: /cores/core.%P
kern.coredump: 1
kern.sugid_coredump: 0
machdep.cpu.cores_per_package: 8
machdep.cpu.thermal.core_power_limits: 1
machdep.cpu.core_count: 2
```

## コアファイルを生成する
まずcoreファイルはどのように生成するかというと(apacheに限ったものではない)

(1) gcoreからpidを指定して生成する
```
$ gcore <pid>
```

(2) gdbから生成する
```
$ gdb
(gdb) attach <pid>
(gdb) gcore core
(gdb) detach
$ ls -alt ./core
```

これのcoreを利用すると以下のようにして原因箇所の特定ができるようです。
```
$ sudo gdb /usr/sbin/httpd core
(gdb) where
(gdb) bt
(gdb) bt full
```

またはこんな感じでもいけると思う(試していない)
```
$ sudo gdb
(gdb) file /usr/sbin/httpd
(gdb) core-file core
(gdb) bt
```


