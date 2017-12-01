# 概要
procpsには次のようなコマンドが含まれています
- free, kill, pgrep, pkill, pmap, ps, pwdx, skill, slabtop, snice, sysctl, tload, top, uptime, vmstat, w, watch

また、上記コマンドで利用しているlibprocというライブラリも提供しています。

### 特定のプロセスIDを取得する
次のようにプロセスが出力されると仮定して、
```
$ ps auxww | grep -i ssh
root      1139  0.0  0.1 105996  1836 ?        Ss   11月30   0:00 /usr/sbin/sshd -D
root     14695  0.0  0.3 145700  3964 ?        Ss   09:16   0:00 sshd: tsuyoshi [priv]
tsuyoshi 14699  0.0  0.2 145700  2048 ?        S    09:16   0:10 sshd: tsuyoshi@pts/2
root     26248  0.0  0.5 145700  5148 ?        Ss   17:24   0:00 sshd: tsuyoshi [priv]
tsuyoshi 26252  0.0  0.2 145700  2388 ?        S    17:24   0:02 sshd: tsuyoshi@pts/3
root     26295  0.0  0.5 145700  5144 ?        Ss   17:28   0:00 sshd: tsuyoshi [priv]
tsuyoshi 26299  0.0  0.2 145700  2240 ?        S    17:28   0:00 sshd: tsuyoshi@pts/4
```

特定のプロセスsshdを使っているtsuyoshiというユーザ以外のPIDも出力されます。
```
$ pidof sshd
26299 26295 26252 26248 14699 14695 1139
```

特定のプロセスIDだけを取得したい場合にはpgrepが利用できます。
```
$ pgrep -f "^sshd: tsuyoshi@pts/3"
26252
$ pgrep -f "^sshd: tsuyoshi@pts/"
14699
26252
26299
```

### 特定のプロセスIDだけを殺す

先程のpgrep -fの応用としてpkill -fがあります
```
$ pgrep -f "^sshd: tsuyoshi@pts/"
```

### 特定のプロセスIDが実行しているディレクトリを表示する
pwdxコマンドの後にPIDを指定すると良い。root権限のものを表示するためにはsudoが必要となります。
```
$ sudo pwdx 491
491: /
```

### リアルタイムにカーネルのスラブキャッシュを表示します。
実行にはsudoが必要かもしれません
```
$ sudo slabtop
 Active / Total Objects (% used)    : 721458 / 798177 (90.4%)
 Active / Total Slabs (% used)      : 17551 / 17551 (100.0%)
 Active / Total Caches (% used)     : 70 / 96 (72.9%)
 Active / Total Size (% used)       : 79942.05K / 91641.25K (87.2%)
 Minimum / Average / Maximum Object : 0.01K / 0.11K / 8.00K

  OBJS ACTIVE  USE OBJ SIZE  SLABS OBJ/SLAB CACHE SIZE NAME                   
128860 128860 100%    0.02K    758	170	 3032K scsi_data_buffer
127360 124918  98%    0.03K    995	128	 3980K kmalloc-32
119040  77960  65%    0.06K   1860	 64	 7440K kmalloc-64
 97923  97923 100%    0.19K   4663	 21     18652K dentry
 82432  82432 100%    0.01K    161	512	  644K kmalloc-8
 57344  57344 100%    0.02K    224	256	  896K kmalloc-16
 48246  34679  71%    0.04K    473	102	 1892K selinux_inode_security
```
