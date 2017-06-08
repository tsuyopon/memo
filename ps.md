# プロセス管理
psコマンドや/proc/<pid>/statusなどプロセス関連のコマンド

#
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
$ ps aux --sort -rss
```
- VSZでソートする
```
$ ps aux --sort -vsize
```

次のように定義されている。
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

