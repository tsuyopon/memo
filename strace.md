# strace
システムコールを追跡するコマンドです。


# 詳細

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

### 実行されたコマンドのシステムコールの統計値を表示する
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

# 参考URL
- http://blog.livedoor.jp/sonots/archives/18193659.html
- http://www.intellilink.co.jp/article/column/oss11.html
