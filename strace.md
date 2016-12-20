# strace
システムコールを追跡するコマンドです。


# 詳細

### 一般的な使い方
コマンドを直接指定する方法かpidを指定して現在のプロセスにアタッチする方法が一般的です。
```
$ sudo strace <command>
or
$ sudo strace <pid>
```

スレッドもトレースするには-fオプションを付与します。


### 特定のプロセス名のpidを取得する。
複数のプロセスを同時にstraceするには以下のコマンドを実行します。
```
$ sudo sudo strace -tt -T -p <pid1つめ> -p <pid２つめ>
```

マルチスレッドなプログラムあるいは当該プロセスが今後作成する子プロセスを含めて対象にする場合には
-f というオプションを指定します。rsyslogdはマルチスレッドで動作するので以下のように指定します。
```
# strace -tt -T -f -p `pidof rsyslogd`
```

### 実行されたコマンドのシステムコールの統計値を表示する(アタッチする場合も含めて)
```
$ sudo strace -c ls
2nd	    Desktop    Downloads  Music  Pictures  SOURCE   asm        dumpssl	httpd  packet_00001_20161203094801  yatos
BuildTools  Documents  MEMO.sh	  NODE	 Public    UNIX_V6  buildroot  git	key    work
% time     seconds  usecs/call     calls    errors syscall
------ ----------- ----------- --------- --------- ----------------
  -nan    0.000000           0        10           read
  -nan    0.000000           0         2           write
  -nan    0.000000           0        10           open
  -nan    0.000000           0        13           close
  -nan    0.000000           0        11           fstat
  -nan    0.000000           0        27           mmap
  -nan    0.000000           0        17           mprotect
  -nan    0.000000           0         3           munmap
  -nan    0.000000           0         3           brk
  -nan    0.000000           0         2           rt_sigaction
  -nan    0.000000           0         1           rt_sigprocmask
  -nan    0.000000           0         2           ioctl
  -nan    0.000000           0         1         1 access
  -nan    0.000000           0         1           execve
  -nan    0.000000           0         2           getdents
  -nan    0.000000           0         1           getrlimit
  -nan    0.000000           0         2         2 statfs
  -nan    0.000000           0         1           arch_prctl
  -nan    0.000000           0         1           set_tid_address
  -nan    0.000000           0         1           openat
  -nan    0.000000           0         1           set_robust_list
------ ----------- ----------- --------- --------- ----------------
100.00    0.000000                   112         3 total
```

なお、稼働中のプロセスのpidを指定して統計情報を取得する方法もあります。
測定したい時間たったらCtrl + Cなどを押下すると統計情報が出ます。何も統計情報が出力されない場合にはsleep状態の可能性が高いです。
```
$ sudo strace -c -p <pid>
```

-pと-cオプションを入れ替えると自分は使えなかったので注意が必要かもしれません。

### 表示される文字数を増やす
デフォルトだと引数が32文字しか表示されないので、もっとたくさんを表示させるには次のようにする
```
$ strace -s 1024 command
```

### ファイルを指定して出力する
oオプションとファイルを指定すればOK
```
$ strace -o output.log command
```

### 生成されたスレッド情報も合わせて表示する
```
$ strace -f command
```

### システムコール情報を絞って表示する
たとえば、statのみに絞る場合には次のようにする。
```
$ strace command -e trace=stat
```

### 不審なプロセスを監視する
```
$ strace -f -e execve -p <pid>
```

### どのファイルを開いているのかの順番を調べる
たとえば、mysqlだと次のようにして調べられるようです。
```
$ strace mysql 2>&1  | grep 'open' | grep '.cnf'
```

# 参考URL
- http://blog.livedoor.jp/sonots/archives/18193659.html
- http://www.intellilink.co.jp/article/column/oss11.html
