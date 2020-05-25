# プロセス管理
psコマンドや/proc/<pid>/statusなどプロセス関連のコマンド

- option
```
a   全ユーザのプロセスの状態を表示
u   ユーザ名と開始時刻を表示
x   制御端末を持たないデーモンなどのプロセスも合わせて表示
ww  表示結果を省略せずに行を折り返して全て表示
e   全プロセスの情報を表示
f   プロセスの親子関係をツリー状にして表示
L   スレッドを表示
```

# 詳細

### カーネルスレッドであることを確認
RSSが0となるのはカーネルスレッドとして生成されたプログラムのみです
```
$ ps auxww 
USER       PID %CPU %MEM    VSZ   RSS TTY      STAT START   TIME COMMAND
root         1  0.0  0.4  41556  4172 ?        Ss   Jan01   0:00 /usr/lib/systemd/systemd
root         2  0.0  0.0      0     0 ?        S    Jan01   0:00 [kthreadd]
root         3  0.0  0.0      0     0 ?        S    Jan01   0:00 [ksoftirqd/0]
root         6  0.0  0.0      0     0 ?        S    Jan01   0:00 [migration/0]
root         7  0.0  0.0      0     0 ?        S    Jan01   0:00 [watchdog/0]
root         8  0.0  0.0      0     0 ?        S<   Jan01   0:00 [cpuset]
root         9  0.0  0.0      0     0 ?        S<   Jan01   0:00 [khelper]
root        10  0.0  0.0      0     0 ?        S    Jan01   0:00 [kdevtmpfs]
...
```

### ps -lコマンド
```
$ ps -l
F S   UID   PID  PPID  C PRI  NI ADDR SZ WCHAN  TTY          TIME CMD
0 S  1000 12814 12813  0  80   0 - 29049 wait   pts/0    00:00:00 bash
0 R  1000 13610 12814  0  80   0 -  2757 -      pts/0    00:00:00 ps
```

左から２番目の状態には以下の種類がある
```
    S（State）
        状態。
    R (runnable)
        実行可能。CPU が空いていれば実行される。 
    U (uninterruptible), D (Disk),
        ディスク入出力などの完了を待っている。割り込み不可。 
    S (Sleep)、I (Idle)
        キーボードや他のプロセスからの入力を待っている。 
    Z (Zombie)
        既に終了していて、終了処理の完了を待ってる。 
    T (Traced)
        一時的に停止しているか、デバッグの対象になっている。 
```

その他の項目は以下の通り
```
PID	    Process ID。プロセス1つ1つに重複ないように(unique)割り当てた番号。
PPID    Parent PID。親プロセスのPID。
UID     User ID。プロセスを生成した利用者の識別子。
TTY     端末名。そのプロセスが結びつけられている端末の省略形。 たとえば、端末 /dev/ttys001は s001になる。 
TIME    CPU時間。 CPUがそのプロセスを実行するために費やした時間。 
COMMAND そのプロセスを起動した時のコマンド。 プログラムが含まれているファイルの名前の一部。 
```

### ps uコマンド(プロセスに割り当てられた資源を確認する)
psコマンドにuオプションを付けると、 プロセスに割り当てられたメモリ資源やCPU資源が表示する。 
```
$ ps u 
USER       PID %CPU %MEM    VSZ   RSS TTY      STAT START   TIME COMMAND
tsuyoshi 10628  0.0  0.6 116196  3452 pts/5    Ss   07:32   0:00 -bash
tsuyoshi 10801  0.0  0.4  50692  2516 pts/5    S+   07:34   0:00 vim syscall.c
tsuyoshi 10802  0.0  0.1  11488   628 pts/5    S+   07:34   0:00 /usr/bin/cscope -dl -f /home/tsuyoshi/UNIX_V6/xv6/cscope.out
```

各項目の意味については以下の通り
```
%CPU                    過去１分間に利用した CPU 時間の割合。 
%MEM                    実際に消費してるメイン・メモリの大きさの割合。 
VSZ (Virtual Size)      仮想記憶上のプロセスの大きさ。KB 単位。 
RSS (resident set size) 実際に消費してるメイン・メモリの大きさ。 
START                   プロセスが生成された時刻。 
```

### メモリ使用量でソートする

- メモリ使用率ベスト2を表示する。 
```
$ ps aux --sort=-%mem  | awk 'NR<=3 {print $0}'
USER       PID %CPU %MEM    VSZ   RSS TTY      STAT START   TIME COMMAND
root      2818  0.0  0.7 358640 29416 ?        Ssl  Mar28   0:01 /usr/bin/python -Es /usr/sbin/firewalld --nofork --nopid
root      3309  0.0  0.4 573932 19128 ?        Ssl  Mar28   1:05 /usr/bin/python2 -Es /usr/sbin/tuned -l -P
```

- CPUでソートする
```
$ ps auxww --sort -pcpu | head -4
USER       PID %CPU %MEM    VSZ   RSS TTY      STAT START   TIME COMMAND
gdm        987  0.2  7.8 1234372 79896 ?       Sl   08:25   0:08 gnome-shell --gdm-mode
tsuyoshi  1048  0.0  0.1 132360  1888 ?        S    08:25   0:02 sshd: tsuyoshi@pts/0
root      2970  0.0  0.0      0     0 ?        S    09:10   0:00 [kworker/0:2]
```
- Sizeでソートする
```
$ ps auxww --sort -size | head -4
USER       PID %CPU %MEM    VSZ   RSS TTY      STAT START   TIME COMMAND
gdm        987  0.2  7.8 1234372 79896 ?       Sl   08:25   0:08 gnome-shell --gdm-mode
gdm        836  0.0  1.7 793164 17816 ?        Sl   08:25   0:00 /usr/libexec/gnome-settings-daemon
gdm        911  0.0  0.4 366092  4156 ?        Sl   08:25   0:00 /usr/libexec/at-spi-bus-launcher
```
- RSSでソートする
```
$ ps aux --sort -rss | head -4
USER       PID %CPU %MEM    VSZ   RSS TTY      STAT START   TIME COMMAND
lightdm    728  1.5  3.8 816336 38916 ?        Sl   08:24   0:01 /usr/sbin/unity-greeter
root       697  2.0  3.8 216516 38772 tty7     Ss+  08:24   0:01 /usr/bin/X -core :0 -seat seat0 -auth /var/run/lightdm/root/:0 -nolisten tcp vt7 -novtswitch
lightdm    772  0.3  3.1 510644 32280 ?        Sl   08:24   0:00 nm-applet
```
- VSZでソートする
```
$ ps aux --sort -vsize | head -4
USER       PID %CPU %MEM    VSZ   RSS TTY      STAT START   TIME COMMAND
lightdm    728  1.2  3.8 816336 38916 ?        Sl   08:24   0:01 /usr/sbin/unity-greeter
lightdm    775  0.2  2.7 681924 28044 ?        Sl   08:24   0:00 /usr/lib/unity-settings-daemon/unity-settings-daemon
lightdm    772  0.2  3.1 510644 32280 ?        Sl   08:24   0:00 nm-applet
```

この他にもmanコマンドを見ると次のように定義されている。
```
KEY   LONG         DESCRIPTION
c     cmd          simple name of executable
C     pcpu         cpu utilization
f     flags        flags as in long format F field
g     pgrp         process group ID

G     tpgid        controlling tty process group ID
j     cutime       cumulative user time
J     cstime       cumulative system time
k     utime        user time
m     min_flt      number of minor page faults
M     maj_flt      number of major page faults
n     cmin_flt     cumulative minor page faults
N     cmaj_flt     cumulative major page faults
o     session      session ID
p     pid          process ID
P     ppid         parent process ID
r     rss          resident set size
R     resident     resident pages
s     size         memory size in kilobytes
S     share        amount of shared pages
t     tty          the device number of the controlling tty
T     start_time   time process was started
U     uid          user ID number
u     user         user name
v     vsize        total VM size in kB
y     priority     kernel scheduling priority
```

### 現状のプロセスの/proc/<PID>/statusを覗いてみる。
```
$ head -11 /proc/$$/status
Name:	bash
State:	S (sleeping)
Tgid:	12814
Pid:	12814
PPid:	12813
TracerPid:	0
Uid:	1000	1000	1000	1000
Gid:	1000	1000	1000	1000
Utrace:	0
FDSize:	256
Groups:	10 18 1000 
```

### プロセス強制終了

通常は^Cだが、coreファイルを生成する場合^¥で良い。  
これはstty -a で確認できる。
```
$ stty -a
speed 9600 baud; rows 45; columns 158; line = 0;
intr = ^C; quit = ^\; erase = ^?; kill = ^U; eof = ^D; eol = M-^?; eol2 = M-^?; swtch = <undef>; start = ^Q; stop = ^S; susp = ^Z; rprnt = ^R; werase = ^W;
lnext = ^V; flush = ^O; min = 1; time = 0;
-parenb -parodd cs8 -hupcl -cstopb cread -clocal -crtscts
-ignbrk -brkint -ignpar -parmrk -inpck -istrip -inlcr -igncr icrnl ixon -ixoff -iuclc ixany imaxbel -iutf8
opost -olcuc -ocrnl onlcr -onocr -onlret -ofill -ofdel nl0 cr0 tab0 bs0 vt0 ff0
isig icanon iexten echo echoe -echok -echonl -noflsh -xcase -tostop -echoprt echoctl echoke
```

### プロセス情報を木構造で表示する
```
$ pstree
systemd-+-NetworkManager-+-dhclient
        |                `-2*[{NetworkManager}]
        |-abrt-watch-log
        |-abrtd
        |-accounts-daemon---{accounts-daemon}
        |-at-spi-bus-laun---2*[{at-spi-bus-laun}]
        |-atd
        |-auditd-+-audispd-+-sedispatch
        |        |         `-{audispd}
        |        `-{auditd}
        |-avahi-daemon---avahi-daemon
        |-bluetoothd
        |-colord---{colord}
        |-colord-sane---{colord-sane}
        |-crond
        |-cupsd
        |-2*[dbus-daemon]
        |-dbus-launch
        |-dconf-service---2*[{dconf-service}]
        |-gconfd-2
        |-gdm-binary-+-gdm-simple-slav-+-Xorg
        |            |                 |-gdm-session-wor-+-gnome-session-+-abrt-applet
        |            |                 |                 |               |-deja-dup-monito---2*[{deja-dup-monito}]
        |            |                 |                 |               |-evolution-alarm---2*[{evolution-alarm}]
        |            |                 |                 |               |-gnome-screensav---2*[{gnome-screensav}]
        |            |                 |                 |               |-gnome-settings----2*[{gnome-settings-}]
        |            |                 |                 |               |-gnome-shell-+-firefox---19*[{firefox}]
        |            |                 |                 |               |             |-gnome-terminal-+-bash
        |            |                 |                 |               |             |                |-gnome-pty-helpe
        |            |                 |                 |               |             |                `-3*[{gnome-terminal}]
        |            |                 |                 |               |             `-6*[{gnome-shell}]
        |            |                 |                 |               |-nm-applet---{nm-applet}
        |            |                 |                 |               |-tracker-miner-f---3*[{tracker-miner-f}]
        |            |                 |                 |               |-tracker-store---6*[{tracker-store}]
        |            |                 |                 |               `-3*[{gnome-session}]
        |            |                 |                 `-2*[{gdm-session-wor}]
        |            |                 `-{gdm-simple-slav}
        |            `-{gdm-binary}
        |-gnome-keyring-d---7*[{gnome-keyring-d}]
(省略)
```


### psコマンドでもプロセスの木構造を確認することができます
```
$ ps x --forest
  PID TTY      STAT   TIME COMMAND
10370 ?        S      0:00 sshd: tsuyoshi@pts/1
10371 pts/1    Ss     0:00  \_ -bash
10440 pts/1    S      0:00      \_ scl enable devtoolset-8 rh-python36 bash
10441 pts/1    S      0:00          \_ /bin/bash /var/tmp/sclXM8AF8
10449 pts/1    S      0:00              \_ bash
10603 pts/1    R+     0:00                  \_ ps x --forest
 9352 ?        S      0:00 sshd: tsuyoshi@pts/0
 9353 pts/0    Ss+    0:00  \_ -bash
 7831 ?        S      0:01 sshd: tsuyoshi@pts/5
 7832 pts/5    Ss+    0:00  \_ -bash
 7705 ?        S      0:01 sshd: tsuyoshi@pts/2
 7706 pts/2    Ss+    0:00  \_ -bash
 5840 ?        S      0:02 sshd: tsuyoshi@pts/4
 5841 pts/4    Ss+    0:00  \_ -bash
 5788 ?        S      0:01 sshd: tsuyoshi@pts/3
 5789 pts/3    Ss+    0:00  \_ -bash
```

### プロセスが起動した時刻を調べたいとき
```
$ ps -eo pid,lstart,args | grep -ie apache -ie COMMAND
  PID                  STARTED COMMAND
 1174 Tue Jun 20 08:24:20 2017 /usr/sbin/apache2 -k start
 1176 Tue Jun 20 08:24:20 2017 /usr/sbin/apache2 -k start
 1177 Tue Jun 20 08:24:20 2017 /usr/sbin/apache2 -k start
```


### スレッドも含めて表示する
たとえば、psにLオプションを表示するとスレッドも含めて表示します。
```
$ ps -efL | grep -ie apache -ie PPID
UID        PID  PPID   LWP  C NLWP STIME TTY          TIME CMD
root      1174     1  1174  0    1 08:24 ?        00:00:00 /usr/sbin/apache2 -k start
www-data  1176  1174  1176  0   27 08:24 ?        00:00:00 /usr/sbin/apache2 -k start
www-data  1176  1174  1181  0   27 08:24 ?        00:00:00 /usr/sbin/apache2 -k start
www-data  1176  1174  1182  0   27 08:24 ?        00:00:00 /usr/sbin/apache2 -k start
www-data  1176  1174  1183  0   27 08:24 ?        00:00:00 /usr/sbin/apache2 -k start
www-data  1176  1174  1184  0   27 08:24 ?        00:00:00 /usr/sbin/apache2 -k start
www-data  1176  1174  1185  0   27 08:24 ?        00:00:00 /usr/sbin/apache2 -k start
www-data  1176  1174  1186  0   27 08:24 ?        00:00:00 /usr/sbin/apache2 -k start
www-data  1176  1174  1187  0   27 08:24 ?        00:00:00 /usr/sbin/apache2 -k start
www-data  1176  1174  1188  0   27 08:24 ?        00:00:00 /usr/sbin/apache2 -k start
www-data  1176  1174  1189  0   27 08:24 ?        00:00:00 /usr/sbin/apache2 -k start
www-data  1176  1174  1190  0   27 08:24 ?        00:00:00 /usr/sbin/apache2 -k start
www-data  1176  1174  1191  0   27 08:24 ?        00:00:00 /usr/sbin/apache2 -k start
www-data  1176  1174  1192  0   27 08:24 ?        00:00:00 /usr/sbin/apache2 -k start
www-data  1176  1174  1193  0   27 08:24 ?        00:00:00 /usr/sbin/apache2 -k start
www-data  1176  1174  1194  0   27 08:24 ?        00:00:00 /usr/sbin/apache2 -k start
www-data  1176  1174  1195  0   27 08:24 ?        00:00:00 /usr/sbin/apache2 -k start
www-data  1176  1174  1196  0   27 08:24 ?        00:00:00 /usr/sbin/apache2 -k start
www-data  1176  1174  1197  0   27 08:24 ?        00:00:00 /usr/sbin/apache2 -k start
www-data  1176  1174  1198  0   27 08:24 ?        00:00:00 /usr/sbin/apache2 -k start
www-data  1176  1174  1199  0   27 08:24 ?        00:00:00 /usr/sbin/apache2 -k start
www-data  1176  1174  1200  0   27 08:24 ?        00:00:00 /usr/sbin/apache2 -k start
www-data  1176  1174  1201  0   27 08:24 ?        00:00:00 /usr/sbin/apache2 -k start
www-data  1176  1174  1202  0   27 08:24 ?        00:00:00 /usr/sbin/apache2 -k start
www-data  1176  1174  1203  0   27 08:24 ?        00:00:00 /usr/sbin/apache2 -k start
www-data  1176  1174  1204  0   27 08:24 ?        00:00:00 /usr/sbin/apache2 -k start
www-data  1176  1174  1205  0   27 08:24 ?        00:00:00 /usr/sbin/apache2 -k start
www-data  1176  1174  1206  0   27 08:24 ?        00:00:00 /usr/sbin/apache2 -k start
www-data  1177  1174  1177  0   27 08:24 ?        00:00:00 /usr/sbin/apache2 -k start
www-data  1177  1174  1208  0   27 08:24 ?        00:00:00 /usr/sbin/apache2 -k start
www-data  1177  1174  1209  0   27 08:24 ?        00:00:00 /usr/sbin/apache2 -k start
www-data  1177  1174  1210  0   27 08:24 ?        00:00:00 /usr/sbin/apache2 -k start
www-data  1177  1174  1211  0   27 08:24 ?        00:00:00 /usr/sbin/apache2 -k start
www-data  1177  1174  1212  0   27 08:24 ?        00:00:00 /usr/sbin/apache2 -k start
www-data  1177  1174  1213  0   27 08:24 ?        00:00:00 /usr/sbin/apache2 -k start
www-data  1177  1174  1214  0   27 08:24 ?        00:00:00 /usr/sbin/apache2 -k start
www-data  1177  1174  1215  0   27 08:24 ?        00:00:00 /usr/sbin/apache2 -k start
www-data  1177  1174  1216  0   27 08:24 ?        00:00:00 /usr/sbin/apache2 -k start
www-data  1177  1174  1217  0   27 08:24 ?        00:00:00 /usr/sbin/apache2 -k start
www-data  1177  1174  1218  0   27 08:24 ?        00:00:00 /usr/sbin/apache2 -k start
www-data  1177  1174  1219  0   27 08:24 ?        00:00:00 /usr/sbin/apache2 -k start
www-data  1177  1174  1220  0   27 08:24 ?        00:00:00 /usr/sbin/apache2 -k start
www-data  1177  1174  1221  0   27 08:24 ?        00:00:00 /usr/sbin/apache2 -k start
www-data  1177  1174  1222  0   27 08:24 ?        00:00:00 /usr/sbin/apache2 -k start
www-data  1177  1174  1223  0   27 08:24 ?        00:00:00 /usr/sbin/apache2 -k start
www-data  1177  1174  1224  0   27 08:24 ?        00:00:00 /usr/sbin/apache2 -k start
www-data  1177  1174  1225  0   27 08:24 ?        00:00:00 /usr/sbin/apache2 -k start
www-data  1177  1174  1226  0   27 08:24 ?        00:00:00 /usr/sbin/apache2 -k start
www-data  1177  1174  1227  0   27 08:24 ?        00:00:00 /usr/sbin/apache2 -k start
www-data  1177  1174  1228  0   27 08:24 ?        00:00:00 /usr/sbin/apache2 -k start
www-data  1177  1174  1229  0   27 08:24 ?        00:00:00 /usr/sbin/apache2 -k start
www-data  1177  1174  1230  0   27 08:24 ?        00:00:00 /usr/sbin/apache2 -k start
www-data  1177  1174  1231  0   27 08:24 ?        00:00:00 /usr/sbin/apache2 -k start
www-data  1177  1174  1232  0   27 08:24 ?        00:00:00 /usr/sbin/apache2 -k start
www-data  1177  1174  1233  0   27 08:24 ?        00:00:00 /usr/sbin/apache2 -k start
```

### スレッド単位でCPU使用率も表示させる
```
$ ps auxww -L | grep -ie apache -ie COMMAND | head -10
USER       PID   LWP %CPU NLWP %MEM    VSZ   RSS TTY      STAT START   TIME COMMAND
root      1174  1174  0.0    1  0.4  71580  4292 ?        Ss   08:24   0:00 /usr/sbin/apache2 -k start
www-data  1176  1176  0.0   27  0.6 360744  6188 ?        Sl   08:24   0:00 /usr/sbin/apache2 -k start
www-data  1176  1181  0.0   27  0.6 360744  6188 ?        Sl   08:24   0:00 /usr/sbin/apache2 -k start
www-data  1176  1182  0.0   27  0.6 360744  6188 ?        Sl   08:24   0:00 /usr/sbin/apache2 -k start
www-data  1176  1183  0.0   27  0.6 360744  6188 ?        Sl   08:24   0:00 /usr/sbin/apache2 -k start
www-data  1176  1184  0.0   27  0.6 360744  6188 ?        Sl   08:24   0:00 /usr/sbin/apache2 -k start
www-data  1176  1185  0.0   27  0.6 360744  6188 ?        Sl   08:24   0:00 /usr/sbin/apache2 -k start
www-data  1176  1186  0.0   27  0.6 360744  6188 ?        Sl   08:24   0:00 /usr/sbin/apache2 -k start
www-data  1176  1187  0.0   27  0.6 360744  6188 ?        Sl   08:24   0:00 /usr/sbin/apache2 -k start
```

### プロセスツリーを表示する
fオプションを付与するとプロセスツリーを表示します。以下の例では27195の子に28529のPIDがあることがわかります。
```
$ ps afx
  PID TTY      STAT   TIME COMMAND
(snip)
 1139 ?        Ss     0:00 /usr/sbin/sshd -D
26248 ?        Ss     0:00  \_ sshd: tsuyoshi [priv]
26252 ?        S      0:02  |   \_ sshd: tsuyoshi@pts/3
26253 pts/3    Ss+    0:00  |       \_ -bash
27190 ?        Ss     0:00  \_ sshd: tsuyoshi [priv]
27194 ?        S      0:04      \_ sshd: tsuyoshi@pts/0
27195 pts/0    Ss     0:00          \_ -bash
28537 pts/0    R+     0:00              \_ ps afx
 1142 ?        Ssl    0:14 /usr/bin/python -Es /usr/sbin/tuned -l -P
 1242 ?        Ss     0:00 /usr/libexec/postfix/master -w
 1244 ?        S      0:00  \_ qmgr -l -t unix -u
28353 ?        S      0:00  \_ pickup -l -t unix -u
```
