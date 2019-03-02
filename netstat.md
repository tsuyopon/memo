# netstat, nstat
関連コマンドとしてnstat, ssなどもある。　nstatについてはここでも取り上げる。


## nstat
```
$ nstat 
#kernel
IpInReceives                    498                0.0
IpInDelivers                    498                0.0
IpOutRequests                   341                0.0
TcpActiveOpens                  16                 0.0
TcpPassiveOpens                 16                 0.0
TcpInSegs                       494                0.0
TcpOutSegs                      349                0.0
UdpInDatagrams                  4                  0.0
UdpOutDatagrams                 4                  0.0
TcpExtTW                        14                 0.0
TcpExtDelayedACKs               4                  0.0
TcpExtTCPHPHits                 97                 0.0
TcpExtTCPPureAcks               56                 0.0
TcpExtTCPHPAcks                 172                0.0
TcpExtTCPDeferAcceptDrop        8                  0.0
TcpExtTCPRcvCoalesce            16                 0.0
TcpExtTCPOrigDataSent           245                0.0
IpExtInOctets                   61576              0.0
IpExtOutOctets                  83104              0.0
IpExtInNoECTPkts                498                0.0
```

```
$ nstat -z -a 'Tcp*'
#kernel
TcpActiveOpens                  5621               0.0
TcpPassiveOpens                 2359               0.0
TcpAttemptFails                 3245               0.0
TcpEstabResets                  0                  0.0
TcpInSegs                       70475              0.0
TcpOutSegs                      53042              0.0
TcpRetransSegs                  8                  0.0
TcpInErrs                       0                  0.0
TcpOutRsts                      3283               0.0
TcpInCsumErrors                 0                  0.0
...
```

## netstat

### インターフェース情報をみる
```
$ netstat -i 
Kernel Interface table
Iface      MTU    RX-OK RX-ERR RX-DRP RX-OVR    TX-OK TX-ERR TX-DRP TX-OVR Flg
lo       16436       26      0      0 0            26      0      0      0 LRU
p2p1      1500   450454      0      0 0        343942      0      0      0 BMRU
```

### イーサネットの統計情報を表示する
```
$ netstat -e | head -10
Active Internet connections (w/o servers)
Proto Recv-Q Send-Q Local Address           Foreign Address         State       User       Inode     
tcp        0      0 localhost.localdoma:ssh 10.0.2.2:52649          ESTABLISHED root       104701    
tcp        0      0 localhost.localdoma:ssh 10.0.2.2:50570          ESTABLISHED root       96257     
tcp        0      0 localhost.localdoma:ssh 10.0.2.2:64366          ESTABLISHED root       90864     
Active UNIX domain sockets (w/o servers)
Proto RefCnt Flags       Type       State         I-Node   Path
unix  2      [ ]         DGRAM                    7572     /run/systemd/notify
unix  2      [ ]         DGRAM                    7632     /run/systemd/journal/syslog
unix  2      [ ]         DGRAM                    7635     /run/systemd/shutdownd
```

### リスニングしているソケット情報を表示する
```
$ netstat -l
Active Internet connections (only servers)
Proto Recv-Q Send-Q Local Address           Foreign Address         State      
tcp        0      0 *:ssh                   *:*                     LISTEN     
tcp        0      0 localhost.localdom:smtp *:*                     LISTEN     
tcp6       0      0 [::]:ssh                [::]:*                  LISTEN     
tcp6       0      0 [::]:ipp                [::]:*                  LISTEN     
udp        0      0 *:bootpc                *:*                                
udp        0      0 *:23116                 *:*                                
udp        0      0 *:ipp                   *:*                                
udp        0      0 *:35019                 *:*                                
udp        0      0 *:mdns                  *:*                                
udp6       0      0 [::]:37972              [::]:*                             
Active UNIX domain sockets (only servers)
Proto RefCnt Flags       Type       State         I-Node   Path
unix  2      [ ACC ]     STREAM     LISTENING     12288    /var/run/mcelog-client
unix  2      [ ACC ]     STREAM     LISTENING     13819    /tmp/.ICE-unix/764
unix  2      [ ACC ]     STREAM     LISTENING     14341    @/tmp/dbus-jCGUSs9Fx0
unix  2      [ ACC ]     STREAM     LISTENING     12904    /tmp/.X11-unix/X0
unix  2      [ ACC ]     STREAM     LISTENING     14510    /tmp/at-spi2/socket-830-1714502139
unix  2      [ ACC ]     STREAM     LISTENING     14348    /tmp/at-spi2/socket-764-1358959450
unix  2      [ ACC ]     STREAM     LISTENING     14465    /var/lib/gdm/.pulse/f703694c7ee7365150096ea800000005-runtime/native
unix  2      [ ACC ]     STREAM     LISTENING     15466    /tmp/at-spi2/socket-922-2035751608
unix  2      [ ACC ]     STREAM     LISTENING     13818    @/tmp/.ICE-unix/764
unix  2      [ ACC ]     STREAM     LISTENING     12350    /var/run/abrt/abrt.socket
unix  2      [ ACC ]     STREAM     LISTENING     12970    @/tmp/gdm-greeter-wsccjTJG
unix  2      [ ACC ]     STREAM     LISTENING     10326    /var/run/cups/cups.sock
unix  2      [ ACC ]     STREAM     LISTENING     10330    /var/run/avahi-daemon/socket
unix  2      [ ACC ]     STREAM     LISTENING     10333    /var/run/dbus/system_bus_socket
unix  2      [ ACC ]     STREAM     LISTENING     12903    @/tmp/.X11-unix/X0
unix  2      [ ACC ]     STREAM     LISTENING     13009    @/tmp/gdm-session-csSckSQp
unix  2      [ ACC ]     STREAM     LISTENING     34833    @/tmp/gdm-session-kNmUCcFC
unix  2      [ ACC ]     STREAM     LISTENING     7574     /run/systemd/private
unix  2      [ ACC ]     STREAM     LISTENING     13005    @/tmp/dbus-HRuyQoWNeb
unix  2      [ ACC ]     SEQPACKET  LISTENING     7643     /run/udev/control
unix  2      [ ACC ]     STREAM     LISTENING     7645     /run/systemd/journal/stdout
unix  2      [ ACC ]     STREAM     LISTENING     12798    /var/run/sdp
```

### netstatの状態について
manpageからの参照だが以下に載せておく。詳しくはManpageを参照のこと
```
ESTABLISHED
    ソケットは確立した接続状態にある。 
SYN_SENT
    ソケットは接続を確立しようと試みている。 
SYN_RECV
    接続要求をネットワークから受信している。 
FIN_WAIT1
    ソケットはクローズされており、接続は切断中である。 
FIN_WAIT2
    接続はクローズされ、ソケットはリモート側からの切断を待っている。 
TIME_WAIT
    ソケットは、クローズ後にリモートからの切断が再送されるのを待っている。 
CLOSED
    ソケットは使用されていない。 
CLOSE_WAIT
    リモート側は既に切断され、ソケットがクローズされるのを待っている。 
LAST_ACK
    リモート側は既に切断され、ソケットもクローズされている。 確認 (acknowledgement) を待っている。 
LISTEN
    ソケットは接続待ち (listen) である。 このようなソケットは、 --listening (-l) または --all (-a) オプションを指定しない限り、出力には含まれない。 
CLOSING
    両方のソケットが切断されているが、まだ全てのデータが送られていない。 
UNKNOWN
    ソケットの状態は不明である。 
```

### 各プロトコルの統計情報を表示する
```
$ netstat -s
Ip:
    448808 total packets received
    0 forwarded
    0 incoming packets discarded
    448356 incoming packets delivered
    313893 requests sent out
Icmp:
    13 ICMP messages received
    0 input ICMP message failed.
    ICMP input histogram:
        destination unreachable: 13
    60 ICMP messages sent
    0 ICMP messages failed
    ICMP output histogram:
        destination unreachable: 60
IcmpMsg:
        InType3: 13
        OutType3: 60
Tcp:
    126 active connections openings
    11 passive connection openings
    17 failed connection attempts
    9 connection resets received
    3 connections established
    448210 segments received
    341296 segments send out
    8 segments retransmited
    0 bad segments received.
    165 resets sent
Udp:
    133 packets received
    0 packets to unknown port received.
    0 packet receive errors
    1034 packets sent
    0 receive buffer errors
    0 send buffer errors
UdpLite:
TcpExt:
    20 TCP sockets finished time wait in fast timer
    1478 delayed acks sent
    343 delayed acks further delayed because of locked socket
    5180 packets directly queued to recvmsg prequeue.
    1845175 bytes directly in process context from backlog
    7735350 bytes directly received in process context from prequeue
    160093 packet headers predicted
    6840 packets header predicted and directly queued to user
    246 acknowledgments not containing data payload received
    255528 predicted acknowledgments
    3 congestion windows recovered without slow start after partial ack
    6 other TCP timeouts
    9 connections reset due to early user close
IpExt:
    InNoRoutes: 47
    InMcastPkts: 345
    OutMcastPkts: 462
    InOctets: 238351588
    OutOctets: 196291662
    InMcastOctets: 111051
    OutMcastOctets: 115731
```


### ルーティング情報を表示する
```
$ netstat -r
Kernel IP routing table
Destination     Gateway         Genmask         Flags   MSS Window  irtt Iface
default         10.0.2.2        0.0.0.0         UG        0 0          0 p2p1
10.0.2.0        *               255.255.255.0   U         0 0          0 p2p1
```

### マルチキャストグループを表示する
```
$ netstat -g
IPv6/IPv4 Group Memberships
Interface       RefCnt Group
--------------- ------ ---------------------
lo              1      all-systems.mcast.net
p2p1            1      224.0.0.251
p2p1            1      all-systems.mcast.net
lo              1      ff02::1
p2p1            1      ff02::1:ff7e:4b30
p2p1            1      ff02::1
```

### ヘルプをみる
```
$ netstat -h   
usage: netstat [-vWeenNcCF] [<Af>] -r         netstat {-V|--version|-h|--help}
       netstat [-vWnNcaeol] [<Socket> ...]
       netstat { [-vWeenNac] -I[<Iface>] | [-veenNac] -i | [-cnNe] -M | -s [-6tuw] } [delay]

        -r, --route              display routing table
        -I, --interfaces=<Iface> display interface table for <Iface>
        -i, --interfaces         display interface table
        -g, --groups             display multicast group memberships
        -s, --statistics         display networking statistics (like SNMP)
        -M, --masquerade         display masqueraded connections

        -v, --verbose            be verbose
        -W, --wide               don't truncate IP addresses
        -n, --numeric            don't resolve names
        --numeric-hosts          don't resolve host names
        --numeric-ports          don't resolve port names
        --numeric-users          don't resolve user names
        -N, --symbolic           resolve hardware names
        -e, --extend             display other/more information
        -p, --programs           display PID/Program name for sockets
        -c, --continuous         continuous listing

        -l, --listening          display listening server sockets
        -a, --all, --listening   display all sockets (default: connected)
        -o, --timers             display timers
        -F, --fib                display Forwarding Information Base (default)
        -C, --cache              display routing cache instead of FIB
        -Z, --context            display SELinux security context for sockets

  <Socket>={-t|--tcp} {-u|--udp} {-U|--udplite} {-w|--raw} {-x|--unix} --ax25 --ipx --netrom
  <AF>=Use '-6|-4' or '-A <af>' or '--<af>'; default: inet
  List of possible address families (which support routing):
    inet (DARPA Internet) inet6 (IPv6) ax25 (AMPR AX.25) 
    netrom (AMPR NET/ROM) ipx (Novell IPX) ddp (Appletalk DDP) 
    x25 (CCITT X.25) 
```

# TODO
- netstat -hなどで表示されたものをまだ色々試せていないので時間があるときにまた
