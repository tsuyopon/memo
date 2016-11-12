#lsofについて
lsofコマンドはプロセスを調査するときに非常に役立つコマンドです。
出力結果が表示されていない場合にはsudoで実行されていないことを疑ってください。

### lsofのオプション
主なオプションは次の通り
```
-P 	ポート番号をサービス名に変換しない
-c 	プロセス名を指定する
-i 	ネットワークソケットファイルを表示する
-n 	IPアドレスを表示する（名前解決しない）
-p 	プロセスIDを指定する
-u  ユーザーを指定する
```

- ほかにもいろいろオプションがあるので詳細はManpageを参考のこと
 - https://netadmintools.com/html/lsof.man.html


### lsofを引数なしで実行する
利用しているfd一覧が全て表示される。
```
# sudo lsof
COMMAND     PID  TID     USER   FD      TYPE             DEVICE  SIZE/OFF       NODE NAME
systemd       1          root   34u     unix 0xffff880036b28340       0t0      10333 /var/run/dbus/system_bus_socket
systemd       1          root   35u     unix 0xffff88003af69380       0t0      12052 socket
systemd       1          root   37u     unix 0xffff88003af69380       0t0      12052 socket
kthreadd      2          root  cwd       DIR              253,1      4096          2 /
kthreadd      2          root  rtd       DIR              253,1      4096          2 /
kthreadd      2          root  txt   unknown                                         /proc/2/exe
ksoftirqd     3          root  cwd       DIR              253,1      4096          2 /
ksoftirqd     3          root  rtd       DIR              253,1      4096          2 /
ksoftirqd     3          root  txt   unknown                                         /proc/3/exe
migration     6          root  cwd       DIR              253,1      4096          2 /
migration     6          root  rtd       DIR              253,1      4096          2 /
migration     6          root  txt   unknown                                         /proc/6/exe
...
```

各項目の説明は次の通り
```
    COMMAND … 実行されているコマンド
    PID … プロセスID
    TID … スレッドID
    USER … 実行ユーザ
    FD … ファイルディスクリプタ。主に見かけるものだけ抜粋。
        cwd … カレントディレクトリ
        txt … テキストファイル
        mem … メモリマッピングファイル
        mmap … メモリマッピングデバイス
        ◯ uなど … 実際のファイルディスクリプタを表す。数字以降のアルファベットの意味は、r→読み取り、w→書き込み、u→読み書き
    TYPE … ファイル種別。主に見かけるものだけ抜粋。
        REG … 通常ファイル
        DIR … ディレクトリ
        FIFO … FIFO
        CHR … デバイスファイル
        unix … UNIXドメインソケット
        IPv4 … IPv4ソケット
        IPv6 … IPv6ソケット
    DEVICE … デバイス番号
    SIZE/OFF … ファイルサイズ
    NODE … プロトコル
    NAME … ファイルまたはポート
```

### ネットワークコネクションを出力する
-iオプションを利用する
```
$ sudo lsof -i
COMMAND     PID     USER   FD   TYPE DEVICE SIZE/OFF NODE NAME
systemd       1     root   31u  IPv6  10328      0t0  TCP *:ipp (LISTEN)
systemd       1     root   32u  IPv4  10329      0t0  UDP *:ipp 
avahi-dae   515    avahi   12r  IPv4  12566      0t0  UDP *:mdns 
avahi-dae   515    avahi   13r  IPv4  12567      0t0  UDP *:35019 
sshd        952     root    3w  IPv4  14846      0t0  TCP *:ssh (LISTEN)
sshd        952     root    4u  IPv6  14856      0t0  TCP *:ssh (LISTEN)
sshd      22514     root    3r  IPv4  90864      0t0  TCP localhost.localdomain:ssh->10.0.2.2:64366 (ESTABLISHED)
sshd      22516 tsuyoshi    3u  IPv4  90864      0t0  TCP localhost.localdomain:ssh->10.0.2.2:64366 (ESTABLISHED)
sshd      23157     root    3r  IPv4  96257      0t0  TCP localhost.localdomain:ssh->10.0.2.2:50570 (ESTABLISHED)
sshd      23159 tsuyoshi    3u  IPv4  96257      0t0  TCP localhost.localdomain:ssh->10.0.2.2:50570 (ESTABLISHED)
dhclient  23816     root    6u  IPv4 100201      0t0  UDP *:bootpc 
dhclient  23816     root   20u  IPv4 100180      0t0  UDP *:33022 
dhclient  23816     root   21u  IPv6 100181      0t0  UDP *:8238 
sendmail  23841     root    4u  IPv4 100445      0t0  TCP localhost.localdomain:smtp (LISTEN)
sshd      24066     root    3r  IPv4 104701      0t0  TCP localhost.localdomain:ssh->10.0.2.2:52649 (ESTABLISHED)
sshd      24068 tsuyoshi    3u  IPv4 104701      0t0  TCP localhost.localdomain:ssh->10.0.2.2:52649 (ESTABLISHED)
...
```

ポートを指定して表示したい場合には次のようにする
```
$ sudo lsof -i:22
COMMAND   PID     USER   FD   TYPE DEVICE SIZE/OFF NODE NAME
sshd      952     root    3w  IPv4  14846      0t0  TCP *:ssh (LISTEN)
sshd      952     root    4u  IPv6  14856      0t0  TCP *:ssh (LISTEN)
sshd    22514     root    3r  IPv4  90864      0t0  TCP localhost.localdomain:ssh->10.0.2.2:64366 (ESTABLISHED)
sshd    22516 tsuyoshi    3u  IPv4  90864      0t0  TCP localhost.localdomain:ssh->10.0.2.2:64366 (ESTABLISHED)
sshd    23157     root    3r  IPv4  96257      0t0  TCP localhost.localdomain:ssh->10.0.2.2:50570 (ESTABLISHED)
sshd    23159 tsuyoshi    3u  IPv4  96257      0t0  TCP localhost.localdomain:ssh->10.0.2.2:50570 (ESTABLISHED)
sshd    24066     root    3r  IPv4 104701      0t0  TCP localhost.localdomain:ssh->10.0.2.2:52649 (ESTABLISHED)
sshd    24068 tsuyoshi    3u  IPv4 104701      0t0  TCP localhost.localdomain:ssh->10.0.2.2:52649 (ESTABLISHED)
...
```

このほかにも次のような指定が可能です。
```
$ sudo lsof -i:22,80                    # ssh or http
$ sudo lsof -i:http                     # 名前でもいける
$ sudo lsof -i@192.168.0.1              # interface指定
$ sudo lsof -i@192.168.0.1:80           # interfaceとポート指定
$ sudo lsof -i4                         # IPv4
$ sudo lsof -i6                         # IPv6
$ sudo lsof -itcp@192.168.0.1:ftp-data  # プロトコル、interface, ポート番号指定
```

tcpやudpで指定することも可能です
```
$ sudo lsof -i tcp
COMMAND    PID     USER   FD   TYPE DEVICE SIZE/OFF NODE NAME
systemd      1     root   31u  IPv6  10328      0t0  TCP *:ipp (LISTEN)
sshd       952     root    3w  IPv4  14846      0t0  TCP *:ssh (LISTEN)
sshd       952     root    4u  IPv6  14856      0t0  TCP *:ssh (LISTEN)
sshd     22514     root    3r  IPv4  90864      0t0  TCP localhost.localdomain:ssh->10.0.2.2:64366 (ESTABLISHED)
sshd     22516 tsuyoshi    3u  IPv4  90864      0t0  TCP localhost.localdomain:ssh->10.0.2.2:64366 (ESTABLISHED)
sshd     23157     root    3r  IPv4  96257      0t0  TCP localhost.localdomain:ssh->10.0.2.2:50570 (ESTABLISHED)
sshd     23159 tsuyoshi    3u  IPv4  96257      0t0  TCP localhost.localdomain:ssh->10.0.2.2:50570 (ESTABLISHED)
sendmail 23841     root    4u  IPv4 100445      0t0  TCP localhost.localdomain:smtp (LISTEN)
sshd     24066     root    3r  IPv4 104701      0t0  TCP localhost.localdomain:ssh->10.0.2.2:52649 (ESTABLISHED)
sshd     24068 tsuyoshi    3u  IPv4 104701      0t0  TCP localhost.localdomain:ssh->10.0.2.2:52649 (ESTABLISHED)
sshd     24066     root    3r  IPv4 104701      0t0  TCP localhost.localdomain:ssh->10.0.2.2:52649 (ESTABLISHED)
sshd     24068 tsuyoshi    3u  IPv4 104701      0t0  TCP localhost.localdomain:ssh->10.0.2.2:52649 (ESTABLISHED)
```

```
$ sudo lsof -i udp
COMMAND     PID  USER   FD   TYPE DEVICE SIZE/OFF NODE NAME
systemd       1  root   32u  IPv4  10329      0t0  UDP *:ipp 
avahi-dae   515 avahi   12r  IPv4  12566      0t0  UDP *:mdns 
avahi-dae   515 avahi   13r  IPv4  12567      0t0  UDP *:35019 
dhclient  23816  root    6u  IPv4 100201      0t0  UDP *:bootpc 
dhclient  23816  root   20u  IPv4 100180      0t0  UDP *:33022 
dhclient  23816  root   21u  IPv6 100181      0t0  UDP *:8238 
...
```

### 利用しているプロセス番号を知る
```
$ sudo lsof -i:22 -t
952
22514
22516
23157
23159
24066
24068
```

### ライブラリを利用しているプロセスを特定する
```
$ sudo lsof /usr/lib64/libssl.so
COMMAND    PID  USER  FD   TYPE DEVICE SIZE/OFF   NODE NAME
sendmail 23841  root mem    REG  253,1   382568 170151 /usr/lib64/libssl.so.1.0.0k
sendmail 23865 smmsp mem    REG  253,1   382568 170151 /usr/lib64/libssl.so.1.0.0k
```

### あるディレクトリを再帰的にチェックする
特定のディレクトリ配下を表示するDオプションの指定が「+D」であることに注意する。
```
$ sudo lsof +D /usr/lib64/ | tail -5
lsof      24368     root  mem    REG  253,1   128888 170125 /usr/lib64/libselinux.so.1
lsof      24369     root  mem    REG  253,1   158440 135298 /usr/lib64/ld-2.15.so
lsof      24369     root  mem    REG  253,1  2065552 135311 /usr/lib64/libc-2.15.so
lsof      24369     root  mem    REG  253,1    22480 137178 /usr/lib64/libdl-2.15.so
lsof      24369     root  mem    REG  253,1   128888 170125 /usr/lib64/libselinux.so.1
```


### プロセス名を指定して表示する
```
$ sudo lsof -c sshd | tail -5
sshd    24068 tsuyoshi    7r  FIFO                0,8      0t0 104777 pipe
sshd    24068 tsuyoshi    8w  FIFO                0,8      0t0 104777 pipe
sshd    24068 tsuyoshi    9u   CHR                5,2      0t0   6208 /dev/ptmx
sshd    24068 tsuyoshi   11u   CHR                5,2      0t0   6208 /dev/ptmx
sshd    24068 tsuyoshi   12u   CHR                5,2      0t0   6208 /dev/ptmx
```

次のように複数指定や特定のプロセス以外といった指定もできます。
これはプロセスに限らずユーザー指定(-u)などにも適応できます
```
$ sudo lsof -c python -c mysqld   // 複数指定
$ sudo lsof -c ^sshd              // それ以外指定
```

### ユーザーを指定して表示する
特定のユーザーのプロセスが使っているものを表示する。ユーザー名でなくユーザーIDでも大丈夫なようだ
```
$ sudo lsof -u tsuyoshi | tail -5
tail    24419 tsuyoshi  mem    REG              253,1    158440 135298 /usr/lib64/ld-2.15.so
tail    24419 tsuyoshi  mem    REG              253,1   2065552 135311 /usr/lib64/libc-2.15.so
tail    24419 tsuyoshi    0r  FIFO                0,8       0t0 107850 pipe
tail    24419 tsuyoshi    1u   CHR              136,2       0t0      5 /dev/pts/2
tail    24419 tsuyoshi    2u   CHR              136,2       0t0      5 /dev/pts/2
```

### グループを指定して表示する
```
$ sudo lsof -g12717
```


### プロセス番号を指定して表示する
```
$ sudo lsof -p 23816 | tail -5
dhclient 23816 root    4w   REG              253,1      782  31324 /var/lib/dhclient/dhclient-1bb6d412-9b66-4e9a-b125-617edfd08966-p2p1.lease
dhclient 23816 root    5u  pack             100200      0t0    ALL type=SOCK_RAW
dhclient 23816 root    6u  IPv4             100201      0t0    UDP *:bootpc 
dhclient 23816 root   20u  IPv4             100180      0t0    UDP *:33022 
dhclient 23816 root   21u  IPv6             100181      0t0    UDP *:8238 
```

### AND検索をおこなう
lsofでは、複数の検索条件を指定するとOR検索がデフォルトとなっています。
このためAND検索の場合には-aオプションを付与します。たとえば、ユーザー名とプロセス名をAND検索する場合には次のようにします。
```
$ sudo lsof -a -u hoge -c java
```

### 名前解決せず(-n)、ポート番号をサービスに変換しない(-P)指定をする
-nや-Pで名前解決せずに、そして、ポート番号からサービス変換せずに表示してくれます。
```
$ sudo lsof -i -n -P
```

### NFSのファイルも表示する
実際に使ったことはないが、
```
$ sudo lsof -N
```

# TODO
- この辺にまだlsofで知らないことが書いてありそうなので時間があれば見ておく
 - https://opensource.apple.com/source/lsof/lsof-41/lsof/00QUICKSTART

# 参考
- A Quick Start for Lsof
 - https://opensource.apple.com/source/lsof/lsof-41/lsof/00QUICKSTART
- Manpage of lsof
 - https://netadmintools.com/html/lsof.man.html
- Frequently Asked Questions about lsof
 - ftp://lsof.itap.purdue.edu/pub/tools/unix/lsof/FAQ
- Finding open files with lsof
 - http://www.ibm.com/developerworks/aix/library/au-lsof.html
- Vic Abell's Home Page
 - https://people.freebsd.org/~abe/
