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

### 生成された別プロセスや別スレッド情報も合わせて表示する
```
$ strace -f command
```

### システムコール情報を絞って表示する
たとえば、statのみに絞る場合には次のようにする。
```
$ strace command -e trace=stat
```

traceは関連するシステムコールを絞って取得できる。
デフォルトだと"-e trace=all"が指定されている。
- all: デフォルト
- file: "open,stat,chmod,unlink,... "などのファイルに関連するシステムコール
- process: プロセス管理に関わるfork, wait, execなどのシステムコール
- network: ネットワークに関連するシステムコール
- signal: シグナルに関連するシステムコール
- ipc: IPCに関連するシステムコール
- desc: ファイルディスクリプタに関連したシステムコール


-writeや-readは"-e trace=write", "-e trace=read"と同じ

### 複数のシステムコールを監視する
```
$ sudo strace -e open,read,write cat /etc/hosts
open("/etc/ld.so.cache", O_RDONLY|O_CLOEXEC) = 3
open("/lib64/libc.so.6", O_RDONLY|O_CLOEXEC) = 3
read(3, "\177ELF\2\1\1\3\0\0\0\0\0\0\0\0\3\0>\0\1\0\0\0@\30\242\2278\0\0\0"..., 832) = 832
open("/etc/hosts", O_RDONLY)            = 3
read(3, "127.0.0.1\t\tlocalhost.localdomain"..., 32768) = 110
write(1, "127.0.0.1\t\tlocalhost.localdomain"..., 110127.0.0.1		localhost.localdomain localhost
::1		localhost6.localdomain6 localhost6

192.30.253.113 github.com
) = 110
read(3, "", 32768)                      = 0
+++ exited with 0 +++
```

### 不審なプロセスを監視する
```
$ strace -f -e execve -p <pid>
```

### より多くのシステムコールに関する情報を出力する。
たとえば、次のように出力してさらに多くの情報をみたい場合
```
$ sudo strace -e execve hostname
execve("/bin/hostname", ["hostname"], [/* 16 vars */]) = 0
localhost.localdomain
+++ exited with 0 +++
```

-vオプションを付与するとより多くの情報を出力する
```
$ sudo strace -v -e execve hostname
execve("/bin/hostname", ["hostname"], ["HOSTNAME=localhost.localdomain", "TERM=xterm-256color", "HISTSIZE=1000", "LS_COLORS=rs=0:di=38;5;27:ln=38;"..., "MAIL=/var/spool/mail/tsuyoshi", "LANG=C", "SHELL=/bin/bash", "LOGNAME=root", "USER=root", "USERNAME=root", "PATH=/sbin:/bin:/usr/sbin:/usr/b"..., "HOME=/root", "SUDO_COMMAND=/bin/strace -v -e e"..., "SUDO_USER=tsuyoshi", "SUDO_UID=1000", "SUDO_GID=1000"]) = 0
localhost.localdomain
+++ exited with 0 +++

```

### どのファイルを開いているのかの順番を調べる
たとえば、mysqlだと次のようにして調べられるようです。
```
$ strace mysql 2>&1  | grep 'open' | grep '.cnf'
```

### それぞれのシステムコールにかかった時間を表示する
-Tオプションを付与すると、行の右側の<>の中にかかった時間を表示するようだ
```
$ sudo strace -T -e open cat /etc/hosts
open("/etc/ld.so.cache", O_RDONLY|O_CLOEXEC) = 3 <0.000026>
open("/lib64/libc.so.6", O_RDONLY|O_CLOEXEC) = 3 <0.000028>
open("/etc/hosts", O_RDONLY)            = 3 <0.000023>
127.0.0.1		localhost.localdomain localhost
::1		localhost6.localdomain6 localhost6

192.30.253.113 github.com
+++ exited with 0 +++
```

### 時刻を表示する
-t, -tt, -tttなどのオプションがある。

```
$ sudo strace -t -e open cat /etc/hosts
21:11:55 open("/etc/ld.so.cache", O_RDONLY|O_CLOEXEC) = 3
21:11:55 open("/lib64/libc.so.6", O_RDONLY|O_CLOEXEC) = 3
21:11:55 open("/etc/hosts", O_RDONLY)   = 3
127.0.0.1		localhost.localdomain localhost
::1		localhost6.localdomain6 localhost6

192.30.253.113 github.com
21:11:55 +++ exited with 0 +++


$ sudo strace -tt -e open cat /etc/hosts
21:11:59.507854 open("/etc/ld.so.cache", O_RDONLY|O_CLOEXEC) = 3
21:11:59.509157 open("/lib64/libc.so.6", O_RDONLY|O_CLOEXEC) = 3
21:11:59.510537 open("/etc/hosts", O_RDONLY) = 3
127.0.0.1		localhost.localdomain localhost
::1		localhost6.localdomain6 localhost6

192.30.253.113 github.com
21:11:59.515186 +++ exited with 0 +++


$ sudo strace -ttt -e open cat /etc/hosts
1482495122.409597 open("/etc/ld.so.cache", O_RDONLY|O_CLOEXEC) = 3
1482495122.410633 open("/lib64/libc.so.6", O_RDONLY|O_CLOEXEC) = 3
1482495122.411786 open("/etc/hosts", O_RDONLY) = 3
127.0.0.1		localhost.localdomain localhost
::1		localhost6.localdomain6 localhost6

192.30.253.113 github.com
1482495122.416348 +++ exited with 0 +++
```

次のようにすると時・分・秒はわかりやすく表示してくれるようだ。
```
$ sudo strace -ttT -e open cat /etc/hosts
21:12:23.155430 open("/etc/ld.so.cache", O_RDONLY|O_CLOEXEC) = 3 <0.000025>
21:12:23.156842 open("/lib64/libc.so.6", O_RDONLY|O_CLOEXEC) = 3 <0.000164>
21:12:23.160478 open("/etc/hosts", O_RDONLY) = 3 <0.000177>
127.0.0.1		localhost.localdomain localhost
::1		localhost6.localdomain6 localhost6

192.30.253.113 github.com
21:12:23.165304 +++ exited with 0 +++
```

プログラム開始からかかった時刻(相対時間)を表示する場合には-rオプションを付与する。
```
$ sudo strace -r -e open cat /etc/hosts
     0.000000 open("/etc/ld.so.cache", O_RDONLY|O_CLOEXEC) = 3
     0.001404 open("/lib64/libc.so.6", O_RDONLY|O_CLOEXEC) = 3
     0.001915 open("/etc/hosts", O_RDONLY) = 3
127.0.0.1		localhost.localdomain localhost
::1		localhost6.localdomain6 localhost6

192.30.253.113 github.com
     0.004673 +++ exited with 0 +++
```

### IP(Instruction Pointer)を表示する
```
$ sudo strace -i cat /etc/hosts
[      3897abaa57] execve("/bin/cat", ["cat", "/etc/hosts"], [/* 16 vars */]) = 0
[      38976163fa] brk(0)               = 0xf81000
[      38976178ca] mmap(NULL, 4096, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0) = 0x7f3de778e000
[      3897617807] access("/etc/ld.so.preload", R_OK) = -1 ENOENT (No such file or directory)
[      3897617747] open("/etc/ld.so.cache", O_RDONLY|O_CLOEXEC) = 3
[      38976176d4] fstat(3, {st_mode=S_IFREG|0644, st_size=82850, ...}) = 0
[      38976178ca] mmap(NULL, 82850, PROT_READ, MAP_PRIVATE, 3, 0) = 0x7f3de7779000
[      3897617777] close(3)             = 0
[      3897617747] open("/lib64/libc.so.6", O_RDONLY|O_CLOEXEC) = 3
[      38976177a7] read(3, "\177ELF\2\1\1\3\0\0\0\0\0\0\0\0\3\0>\0\1\0\0\0@\30\242\2278\0\0\0"..., 832) = 832
[      38976176d4] fstat(3, {st_mode=S_IFREG|0755, st_size=2065552, ...}) = 0
[      38976178ca] mmap(0x3897a00000, 3892376, PROT_READ|PROT_EXEC, MAP_PRIVATE|MAP_DENYWRITE, 3, 0) = 0x3897a00000
[      3897617927] mprotect(0x3897bac000, 2097152, PROT_NONE) = 0
[      38976178ca] mmap(0x3897dac000, 24576, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0x1ac000) = 0x3897dac000
[      38976178ca] mmap(0x3897db2000, 17560, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_FIXED|MAP_ANONYMOUS, -1, 0) = 0x3897db2000
[      3897617777] close(3)             = 0
[      38976178ca] mmap(NULL, 4096, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0) = 0x7f3de7778000
[      38976178ca] mmap(NULL, 8192, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0) = 0x7f3de7776000
[      3897600fe0] arch_prctl(ARCH_SET_FS, 0x7f3de7776740) = 0
[      3897617927] mprotect(0x60a000, 4096, PROT_READ) = 0
[      3897617927] mprotect(0x3897dac000, 16384, PROT_READ) = 0
[      3897617927] mprotect(0x389781f000, 4096, PROT_READ) = 0
[      38976178f7] munmap(0x7f3de7779000, 82850) = 0
[      3897aea1da] brk(0)               = 0xf81000
[      3897aea1da] brk(0xfa2000)        = 0xfa2000
[      3897aea1da] brk(0)               = 0xfa2000
[      3897ae4274] fstat(1, {st_mode=S_IFCHR|0620, st_rdev=makedev(136, 4), ...}) = 0
[      3897ae4700] open("/etc/hosts", O_RDONLY) = 3
[      3897ae4274] fstat(3, {st_mode=S_IFREG|0644, st_size=110, ...}) = 0
[      3897ae8ced] fadvise64(3, 0, 0, POSIX_FADV_SEQUENTIAL) = 0
[      3897ae48f0] read(3, "127.0.0.1\t\tlocalhost.localdomain"..., 32768) = 110
[      3897ae4950] write(1, "127.0.0.1\t\tlocalhost.localdomain"..., 110127.0.0.1		localhost.localdomain localhost
::1		localhost6.localdomain6 localhost6

192.30.253.113 github.com
) = 110
[      3897ae48f0] read(3, "", 32768)   = 0
[      3897ae4890] close(3)             = 0
[      3897ae4890] close(1)             = 0
[      3897ae4890] close(2)             = 0
[      3897abaa29] exit_group(0)        = ?
[????????????????] +++ exited with 0 +++
```

### strace自身のデバッグログを出力する
-dオプションを付与する。

# 参考URL
- http://blog.livedoor.jp/sonots/archives/18193659.html
- http://www.intellilink.co.jp/article/column/oss11.html
