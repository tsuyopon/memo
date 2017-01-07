# 概要
/proc/<pid>配下についてまとめる

```
$ uname -a
Linux localhost.localdomain 3.3.4-5.fc17.x86_64 #1 SMP Mon May 7 17:29:34 UTC 2012 x86_64 x86_64 x86_64 GNU/Linux
$ cat /proc/version 
Linux version 3.3.4-5.fc17.x86_64 (mockbuild@x86-14.phx2.fedoraproject.org) (gcc version 4.7.0 20120504 (Red Hat 4.7.0-4) (GCC) ) #1 SMP Mon May 7 17:29:34 UTC 2012
$ ps auxww | grep -i mysqld_safe
mysql     2190  0.0  0.1 114328  1408 ?        Ss   Jan01   0:00 /bin/sh /usr/bin/mysqld_safe --basedir=/usr
```

# 詳細

### 実行しているコマンド名を表示する
```
$ cat /proc/2190/comm 
mysqld_safe
```

### プロセスが実行されている環境変数を確認する
覗いてみると「@^」でセパレートされていることがわかる。
```
$ sudo cat /proc/2190/environ  | less
SYSFONT=True^@PATH=/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin^@PWD=/^@LANG=en_US.UTF-8^@KEYTABLE=jp106^@SHLVL=0^@BOOT_IMAGE=/vmlinuz-3.3.4-5.fc17.x86_64^@HOME=/var/lib/mysql^@LOGNAME=mysql^@USER=mysql^@
```


### コマンドラインで与えられた引数を確認する
```
$ ps auxww | grep -i mysqld_safe
mysql     2190  0.0  0.1 114328  1408 ?        Ss   Jan01   0:00 /bin/sh /usr/bin/mysqld_safe --basedir=/usr
$ cat /proc/2190/cmdline 
/bin/sh/usr/bin/mysqld_safe--basedir=/usr
```

### コマンドのcwdを表示する。
コマンドが実行されているカレントワーキングディレクトリ(cwd)を表示する。
```
$ sudo file /proc/2190/cwd 
/proc/2190/cwd: symbolic link to `/'
$ sudo ls -alt /proc/2190/cwd
lrwxrwxrwx 1 mysql mysql 0 Jan  2 19:02 /proc/2190/cwd -> /
```

### プロセス空間のメモリ構成を確認する
mapsで確認することができます。
```
$ sudo cat /proc/2190/maps 
00400000-004da000 r-xp 00000000 fd:01 138534                             /usr/bin/bash (deleted)
006d9000-006da000 r--p 000d9000 fd:01 138534                             /usr/bin/bash (deleted)
006da000-006e3000 rw-p 000da000 fd:01 138534                             /usr/bin/bash (deleted)
006e3000-006e9000 rw-p 00000000 00:00 0 
008e2000-008eb000 rw-p 000e2000 fd:01 138534                             /usr/bin/bash (deleted)
012dc000-0131e000 rw-p 00000000 00:00 0                                  [heap]
3897600000-3897620000 r-xp 00000000 fd:01 135298                         /usr/lib64/ld-2.15.so
389781f000-3897820000 r--p 0001f000 fd:01 135298                         /usr/lib64/ld-2.15.so
3897820000-3897821000 rw-p 00020000 fd:01 135298                         /usr/lib64/ld-2.15.so
3897821000-3897822000 rw-p 00000000 00:00 0 
3897a00000-3897bac000 r-xp 00000000 fd:01 135311                         /usr/lib64/libc-2.15.so
3897bac000-3897dac000 ---p 001ac000 fd:01 135311                         /usr/lib64/libc-2.15.so
3897dac000-3897db0000 r--p 001ac000 fd:01 135311                         /usr/lib64/libc-2.15.so
3897db0000-3897db2000 rw-p 001b0000 fd:01 135311                         /usr/lib64/libc-2.15.so
3897db2000-3897db7000 rw-p 00000000 00:00 0 
3898200000-3898203000 r-xp 00000000 fd:01 137178                         /usr/lib64/libdl-2.15.so
3898203000-3898402000 ---p 00003000 fd:01 137178                         /usr/lib64/libdl-2.15.so
3898402000-3898403000 r--p 00002000 fd:01 137178                         /usr/lib64/libdl-2.15.so
3898403000-3898404000 rw-p 00003000 fd:01 137178                         /usr/lib64/libdl-2.15.so
38a8e00000-38a8e25000 r-xp 00000000 fd:01 170142                         /usr/lib64/libtinfo.so.5.9.#prelink#.NAnR2s (deleted)
38a8e25000-38a9024000 ---p 00025000 fd:01 170142                         /usr/lib64/libtinfo.so.5.9.#prelink#.NAnR2s (deleted)
38a9024000-38a9028000 r--p 00024000 fd:01 170142                         /usr/lib64/libtinfo.so.5.9.#prelink#.NAnR2s (deleted)
38a9028000-38a9029000 rw-p 00028000 fd:01 170142                         /usr/lib64/libtinfo.so.5.9.#prelink#.NAnR2s (deleted)
7fb7a69ef000-7fb7a69fb000 r-xp 00000000 fd:01 136364                     /usr/lib64/libnss_files-2.15.so
7fb7a69fb000-7fb7a6bfa000 ---p 0000c000 fd:01 136364                     /usr/lib64/libnss_files-2.15.so
7fb7a6bfa000-7fb7a6bfb000 r--p 0000b000 fd:01 136364                     /usr/lib64/libnss_files-2.15.so
7fb7a6bfb000-7fb7a6bfc000 rw-p 0000c000 fd:01 136364                     /usr/lib64/libnss_files-2.15.so
7fb7a6c11000-7fb7ad03e000 r--p 00000000 fd:01 164960                     /usr/lib/locale/locale-archive
7fb7ad03e000-7fb7ad041000 rw-p 00000000 00:00 0 
7fb7ad04d000-7fb7ad04f000 rw-p 00000000 00:00 0 
7fb7ad04f000-7fb7ad056000 r--s 00000000 fd:01 3635                       /usr/lib64/gconv/gconv-modules.cache
7fb7ad056000-7fb7ad057000 rw-p 00000000 00:00 0 
7fffd6ddb000-7fffd6dfc000 rw-p 00000000 00:00 0                          [stack]
7fffd6dff000-7fffd6e00000 r-xp 00000000 00:00 0                          [vdso]
ffffffffff600000-ffffffffff601000 r-xp 00000000 00:00 0                  [vsyscall]
```

上記は次のように並んでいる。
```
address           perms offset  dev   inode       pathname
```

- address: そのフィールドが占めているプロセスのアドレス空間を表す。
- perms: パーミッションのセットを表す
```
r = read
w = write
x = execute
s = shared
p = private (copy on write)
```
- offset: ファイルへのオフセット値
- dev: デバイス番号(メジャーデバイス番号:マイナーデバイス番号)
- inode: そのデバイスのinode番号を表す。0の場合にはBSS(初期化されていないデータ領域)のようにどのinodeとも関連付けられていないことを表す。
- pathname: 通常そのマッピングに対応するファイルである。ELFの場合にはreadelf -lなどで簡単にoffsetと対応付けをすることができる。


### /proc/uptime
1つめのフィールドがOSが起動してからの合計時間(秒)、２つめのフィールドがアイドルだった際の合計時間(秒)
```
$ cat /proc/uptime 
114900.22 112903.48
```

1番目のフィールドをわかりやすい形式に次のようにして変換することができる。
```
$ cat /proc/uptime | awk '{print $1 / 60 /60 /24 "days (" $1 "sec)"}'
1.3068days (114904.66sec)
```

### AUXV
Auxiliary Vectorsを表示する。
VDSOなどの位置を特定するための
```
$ sudo cat /proc/2190/auxv | od -x
0000000 0021 0000 0000 0000 f000 d6df 7fff 0000
0000020 0010 0000 0000 0000 fbff 078b 0000 0000
0000040 0006 0000 0000 0000 1000 0000 0000 0000
0000060 0011 0000 0000 0000 0064 0000 0000 0000
0000100 0003 0000 0000 0000 0040 0040 0000 0000
0000120 0004 0000 0000 0000 0038 0000 0000 0000
0000140 0005 0000 0000 0000 000a 0000 0000 0000
0000160 0007 0000 0000 0000 0000 0000 0000 0000
0000200 0008 0000 0000 0000 0000 0000 0000 0000
0000220 0009 0000 0000 0000 d1a8 0041 0000 0000
0000240 000b 0000 0000 0000 001b 0000 0000 0000
0000260 000c 0000 0000 0000 001b 0000 0000 0000
0000300 000d 0000 0000 0000 001b 0000 0000 0000
0000320 000e 0000 0000 0000 001b 0000 0000 0000
0000340 0017 0000 0000 0000 0000 0000 0000 0000
0000360 0019 0000 0000 0000 b7b9 d6df 7fff 0000
0000400 001f 0000 0000 0000 bfe3 d6df 7fff 0000
0000420 000f 0000 0000 0000 b7c9 d6df 7fff 0000
0000440 0000 0000 0000 0000 0000 0000 0000 0000
0000460
```

### プロセスに設定された制限値を取得する
プロセス制限値を取得する
```
$ sudo cat /proc/2190/limits 
Limit                     Soft Limit           Hard Limit           Units     
Max cpu time              unlimited            unlimited            seconds   
Max file size             unlimited            unlimited            bytes     
Max data size             unlimited            unlimited            bytes     
Max stack size            8388608              unlimited            bytes     
Max core file size        0                    unlimited            bytes     
Max resident set          unlimited            unlimited            bytes     
Max processes             7815                 7815                 processes 
Max open files            1024                 4096                 files     
Max locked memory         65536                65536                bytes     
Max address space         unlimited            unlimited            bytes     
Max file locks            unlimited            unlimited            locks     
Max pending signals       7815                 7815                 signals   
Max msgqueue size         819200               819200               bytes     
Max nice priority         0                    0                    
Max realtime priority     0                    0                    
Max realtime timeout      unlimited            unlimited            us       
```

### mem
```
$ sudo cat /proc/2190/mem 
cat: /proc/2190/mem: Input/output error
$ file /proc/2190/mem 
/proc/2190/mem: empty
$ ls -alt /proc/2190/mem 
-rw------- 1 mysql mysql 0 Dec 30 20:03 /proc/2190/mem
```

このファイルにはopen, read, lseekなどのシステムコールを使ってアクセスするようです。

### /proc/self/, /proc/net, /proc/mounts
このディレクトリは現在実行中のプロセスへのリンクです。
即座にls -lでリンク先を変更してもリンク先が変わっていることが確認できます。
```
$ ls -l /proc/self
lrwxrwxrwx 1 root root 64 Dec 21 09:24 /proc/self -> 28140
$ ls -l /proc/self
lrwxrwxrwx 1 root root 64 Dec 21 09:24 /proc/self -> 28141
$ ls -l /proc/self
lrwxrwxrwx 1 root root 64 Dec 21 09:24 /proc/self -> 28142
$ ls -l /proc/self
lrwxrwxrwx 1 root root 64 Dec 21 09:24 /proc/self -> 28143
```

/proc/netと/proc/mountsは/proc/self配下を参照している。
```
$ ls -l /proc/net
lrwxrwxrwx 1 root root 8 Jan  2 19:38 /proc/net -> self/net
$ ls -l /proc/mounts 
lrwxrwxrwx 1 root root 11 Jan  2 19:38 /proc/mounts -> self/mounts
```

- 参考
 - http://unix.stackexchange.com/questions/6301/how-do-i-read-from-proc-pid-mem-under-linux
