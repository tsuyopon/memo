# ssコマンド
ss(socket statistics)はネットワーク接続の統計情報を出力するプログラムです。
従来のnetstatコマンドを置き換えるためのコマンドとされています。

# 詳細

### 引数なしで実行する
引数なしでssコマンドを実行した場合には確立されている接続のみを表示します。
```
$ ss
Netid  State      Recv-Q Send-Q                             Local Address:Port                                              Peer Address:Port
u_str  ESTAB      0      0                                              * 18801                                                        * 18800
u_str  ESTAB      0      0                                              * 24052                                                        * 24051
...
u_str  ESTAB      0      0                                              * 18832                                                        * 18831
udp    ESTAB      0      0                                      10.0.2.15:56921                                              192.168.3.1:domain
tcp    ESTAB      0      0                                      10.0.2.15:ssh                                                   10.0.2.2:51654
tcp    ESTAB      0      0                                      10.0.2.15:ssh                                                   10.0.2.2:50396
tcp    ESTAB      0      0                                      10.0.2.15:ssh                                                   10.0.2.2:51731
...
```

上記の列の意味は次の通りです。
- Netid
  - u_strはTCP(Stream)、u_dgrはUDP(Diagram)、それ以外はnlとなる。ただし、u_strはtcp, u_dgrはtcpと表示されることもあるらしい。p_rawはRawソケット、
- State
  - 接続の状態を表す。ESTAB, LISTEN(接続要求待機待ち), UNCONN(接続されてない)が存在する。
- Recv-Q
  - ソケットからまだプロセスへと渡っていないデータのバイト数を表す
- Send-Q
  - プロセスから渡されたがまだ送信できていないデータのバイト数を表す

### 全ての接続を表示する
```
$ ss -a
Netid  State      Recv-Q Send-Q                             Local Address:Port                                              Peer Address:Port
nl     UNCONN     0      0                                           rtnl:kernel                                                        *    
nl     UNCONN     0      0                                           rtnl:1094714147                                                    *    
nl     UNCONN     0      0                                           rtnl:1094714147                                                    *    
nl     UNCONN     768    0                                        tcpdiag:kernel                                                        *    
nl     UNCONN     4352   0                                        tcpdiag:ss/10279                                                      *    
(snip)
```

あとは、TCPやUDPに出力を絞りたければオプションを付与すれば良い。
```
$ ss -a -t   // TCPのみ
$ ss -a -u   // UDPのみ
$ ss -a -x   // RawSocket
$ ss -u -a   // UnixDomainSocket
```

### ソケットのサマリーを表示する
```
$ ss -s
Total: 223 (kernel 0)
TCP:   24 (estab 3, closed 12, orphaned 0, synrecv 0, timewait 12/0), ports 0

Transport Total     IP        IPv6
*     0         -         -        
RAW   1         0         1        
UDP   6         4         2        
TCP   12        9         3        
INET      19        13        6        
FRAG      0         0         0        
```

### 開いているポート一覧
全ての開いているポートを出力します。pオプションがプロセス名を表示し、lオプションはlistening状態であるポートを表示します。
TCPはESTABLISHな状態しか表示してくれません。
```
$ ss -pl
Netid  State      Recv-Q Send-Q                             Local Address:Port                                              Peer Address:Port
nl     UNCONN     0      0                                           rtnl:kernel                                                        *    
nl     UNCONN     0      0                                           rtnl:1094714147                                                    *    
nl     UNCONN     0      0                                           rtnl:1094714147                                                    *    
nl     UNCONN     4352   0                                        tcpdiag:ss/10043                                                      *    

...

u_dgr  UNCONN     0      0                                              * 24334                                                        * 6948
u_dgr  UNCONN     0      0                                              * 15574                                                        * 6948
udp    UNCONN     0      0                                             :::ipv6-icmp                                                   :::*   
udp    UNCONN     0      0                                              *:bootpc                                                       *:*   
udp    UNCONN     0      0                                      127.0.0.1:323                                                          *:*   
udp    UNCONN     0      0                                              *:36225                                                        *:*   
udp    UNCONN     0      0                                            ::1:323                                                         :::*   
udp    UNCONN     0      0                                             :::36676                                                       :::*   
tcp    LISTEN     0      128                                            *:http                                                         *:*   
tcp    LISTEN     0      5                                      127.0.0.1:us-srv                                                       *:*   
tcp    LISTEN     0      128                                    127.0.0.1:8084                                                         *:*   
tcp    LISTEN     0      128                                            *:ssh                                                          *:*   
tcp    LISTEN     0      100                                    127.0.0.1:smtp                                                         *:*   
tcp    LISTEN     0      128                                            *:https                                                        *:*   
tcp    LISTEN     0      128                                           :::ssh                                                         :::*   
tcp    LISTEN     0      100                                          ::1:smtp                                                        :::*   
tcp    LISTEN     0      80                                            :::mysql                                                       :::*   
```

上記のうちTCPのみを表示する
```
$ ss -pl -t
State      Recv-Q Send-Q                                Local Address:Port                                                 Peer Address:Port
LISTEN     0      128                                               *:http                                                            *:*
LISTEN     0      5                                         127.0.0.1:us-srv                                                          *:*
LISTEN     0      128                                       127.0.0.1:8084                                                            *:*
LISTEN     0      128                                               *:ssh                                                             *:*
LISTEN     0      100                                       127.0.0.1:smtp                                                            *:*
LISTEN     0      128                                               *:https                                                           *:*
LISTEN     0      128                                              :::ssh                                                            :::*
LISTEN     0      100                                             ::1:smtp                                                           :::*
LISTEN     0      80                                               :::mysql                                                          :::*
```

上記のうちUDPのみを表示する
```
$ ss -pl -u
State      Recv-Q Send-Q                                Local Address:Port                                                 Peer Address:Port
UNCONN     0      0                                                 *:bootpc                                                          *:*
UNCONN     0      0                                         127.0.0.1:323                                                             *:*
UNCONN     0      0                                                 *:36225                                                           *:*
UNCONN     0      0                                               ::1:323                                                            :::*
UNCONN     0      0                                                :::36676                                                          :::*
```

### プロトコル名の名前解決を行わない
たとえば、オプションを付与しないと以下の22はsshと表示されてしまいますが、この自動解決をしたくない場合にはnオプションを付与します。
```
$ ss -n
State      Recv-Q Send-Q                                  Local Address:Port                                                 Peer Address:Port
ESTAB      0      0                                           10.0.2.15:22                                                       10.0.2.2:51654
ESTAB      0      0                                           10.0.2.15:22                                                       10.0.2.2:50396
ESTAB      0      0                                           10.0.2.15:22                                                       10.0.2.2:51731
(snip)
```

### IPv4, IPv6に限定する
```
$ ss -4
$ ss -6
```

### timer情報を表示する
```
$ ss -o
...
tcp    ESTAB      0      72        198.51.100.1:ssh          192.0.2.59:56741    timer:(on,314ms,0)
tcp    CLOSE-WAIT 1      0            127.0.0.1:35413         127.0.0.1:http-alt
```

### HTTPコネクション一覧
```
$ ss -io '( dport = :http or sport = :http )'
State      Recv-Q Send-Q      Local Address:Port          Peer Address:Port
ESTAB      0      0          127.0.0.1:http        219.136.105.93:40193
  ts sack cubic wscale:6,7 rto:224 rtt:24.875/2.75 ato:40 cwnd:10 send 4.5Mbps rcv_rtt:32 rcv_space:14480
ESTAB      0      0          127.0.0.1:http         49.99.133.91:39430
  sack cubic wscale:6,7 rto:271 rtt:71.75/17.25 ato:40 cwnd:10 send 1.6Mbps rcv_space:14600
ESTAB      0      0          127.0.0.1:http         39.28.158.70:1826
  ts sack cubic wscale:10,7 rto:218 rtt:18/6.75 ato:40 cwnd:10 send 6.4Mbps rcv_rtt:18 rcv_space:14480
...
```

### プロトコルと状態を指定する
```
$ ss -o state established '( dport = :ssh or sport = :ssh )'
Netid  Recv-Q Send-Q                                  Local Address:Port                                                   Peer Address:Port 
tcp    0      0                                           10.0.2.15:ssh                                                        10.0.2.2:51654
tcp    0      0                                           10.0.2.15:ssh                                                        10.0.2.2:50396
tcp    0      0                                           10.0.2.15:ssh                                                        10.0.2.2:51731
```

stateに指定できるのは次の値のようだ(man ss参照)
```
established, syn-sent, syn-recv, fin-wait-1, fin-wait-2, time-wait, closed, close-wait, last-ack, listen, closing
```

stateの条件の否定にすることも可能
```
$ ss -not state established
Recv-Q Send-Q                                       Local Address:Port                                                      Peer Address:Port              
0      0                                                10.0.2.15:22                                                            10.0.2.2:51654               timer:(keepalive,27min,0)
0      0                                                10.0.2.15:22                                                            10.0.2.2:50396               timer:(keepalive,43min,0)
0      0                                                10.0.2.15:22                                                            10.0.2.2:51731               timer:(keepalive,43min,0)
```

### 対象条件の変更
- 等しい(=でも==でもOK)
```
$  ss -lnt4 'sport = :80'
State      Recv-Q Send-Q                                  Local Address:Port                                                 Peer Address:Port
LISTEN     0      128                                                 *:80                                                              *:*
$  ss -lnt4 'sport == :80'
State      Recv-Q Send-Q                                  Local Address:Port                                                 Peer Address:Port
LISTEN     0      128                                                 *:80                                                              *:* 
```

- 未満
```
$  ss -lnt4 'sport < :1024'
State      Recv-Q Send-Q                                  Local Address:Port                                                 Peer Address:Port
LISTEN     0      128                                                 *:80                                                              *:*   
LISTEN     0      128                                                 *:22                                                              *:*   
LISTEN     0      100                                         127.0.0.1:25                                                              *:*   
LISTEN     0      128                                                 *:443                                                             *:*   
```

- 以上
```
$  ss -lnt4 'sport >= :1024'
State      Recv-Q Send-Q                                  Local Address:Port                                                 Peer Address:Port
LISTEN     0      5                                           127.0.0.1:8083                                                            *:*   
LISTEN     0      128                                         127.0.0.1:8084                                                            *:*   
```

- 否定
```
$  ss -lnt4 'sport != :80'
State      Recv-Q Send-Q                                  Local Address:Port                                                 Peer Address:Port
LISTEN     0      5                                           127.0.0.1:8083                                                            *:*   
LISTEN     0      128                                         127.0.0.1:8084                                                            *:*   
LISTEN     0      128                                                 *:22                                                              *:*   
LISTEN     0      100                                         127.0.0.1:25                                                              *:*   
LISTEN     0      128                                                 *:443                                                             *:*  
```

- or
```
$ ss -lnt4 'src 127.0.0.1 or sport = :25'
State      Recv-Q Send-Q                                  Local Address:Port                                                 Peer Address:Port
LISTEN     0      5                                           127.0.0.1:8083                                                            *:*   
LISTEN     0      128                                         127.0.0.1:8084                                                            *:*   
LISTEN     0      100                                         127.0.0.1:25                                                              *:*   
```

- and
```
$ ss -lnt4 'src 127.0.0.1 and sport = :25'   // "and"部分は抜いても実行可能
State      Recv-Q Send-Q                                  Local Address:Port                                                 Peer Address:Port
LISTEN     0      100                                         127.0.0.1:25                                                              *:*  
```

### メモリ利用状況も表示する

```
$ ss -m
State      Recv-Q Send-Q                                Local Address:Port                                                 Peer Address:Port                
ESTAB      0      0                                         10.0.2.15:ssh                                                      10.0.2.2:51654                
	 skmem:(r0,rb369280,t0,tb87040,f0,w0,o0,bl0)
ESTAB      0      0                                         10.0.2.15:ssh                                                      10.0.2.2:50396                
	 skmem:(r0,rb445148,t0,tb87040,f0,w0,o0,bl0)
ESTAB      0      0                                         10.0.2.15:ssh                                                      10.0.2.2:51731                
	 skmem:(r0,rb369280,t0,tb87040,f4096,w0,o0,bl0)
...
```

上記のskmem中にある()内の意味はカーネルの以下の変数や関数に該当するらしい。(TODO: 時間をとってちゃんとソースコードを読んで意味を記載したい)
- r
```
sk_rmem_alloc_get(sk)
受信バッファ(sk_receive_queue)に存在するパケットのサイズ（sk_buff構造体の管理領域も含む）を表す。
```
- rb
```
sk->sk_rcvbuf
受信バッファの上限値。上記結果は上限値が474,628(byte)であることを示している。tcp_rmem[1]の値です。
```
- t
```
sk_wmem_alloc_get(sk)
```
- tb
```
sk->sk_sndbuf
送信バッファの上限値。上記結果は上限値が139,264(byte)であることを示している。tcp_wmem[1]の値です。
```
- f
```
sk->sk_forward_alloc
```
- w
```
sk->sk_wmem_queued
```
- o
```
atomic_read(&sk->sk_omem_alloc)
```
- bl
```
sk->sk_backlog.len
```

- 素晴らしい参考資料
  - https://qiita.com/hana_shin/items/632b3a1eb44bf84e94f7

### TCPの場合に他の情報を合わせて表示する
iというオプションはTCPの場合に、さらに多くの情報を付与して表示してくれます。TCP以外ではこのオプションは効きません(あえてtオプションを付与する必要もないですが以下では付与しています)。
iを付与しない場合とiを付与した場合の出力を以下に載せておきます。

```
$ ss -t 
State      Recv-Q Send-Q                                Local Address:Port                                                 Peer Address:Port 
ESTAB      0      0                                         10.0.2.15:ssh                                                      10.0.2.2:51654
ESTAB      0      0                                         10.0.2.15:ssh                                                      10.0.2.2:50396
ESTAB      0      0                                         10.0.2.15:ssh                                                      10.0.2.2:51731
```

```
$ ss -t -i
State      Recv-Q Send-Q                                Local Address:Port                                                 Peer Address:Port                
ESTAB      0      0                                         10.0.2.15:ssh                                                      10.0.2.2:51654                
     cubic rto:201 rtt:0.331/0.032 ato:40 mss:1460 cwnd:10 bytes_acked:250901 bytes_received:23269 segs_out:1206 segs_in:1721 send 352.9Mbps lastsnd:445043 lastrcv:447311 lastack:445042 pacing_rate 705.2Mbps rcv_space:29200
ESTAB      0      0                                         10.0.2.15:ssh                                                      10.0.2.2:50396                
     cubic rto:201 rtt:0.39/0.1 ato:40 mss:1460 cwnd:10 bytes_acked:2642157 bytes_received:497597 segs_out:12798 segs_in:22988 send 299.5Mbps lastsnd:18817 lastrcv:18824 lastack:18817 pacing_rate 598.6Mbps rcv_rtt:359721 rcv_space:66928
ESTAB      0      0                                         10.0.2.15:ssh                                                      10.0.2.2:51731                
     cubic rto:201 rtt:0.339/0.098 ato:40 mss:1460 cwnd:10 bytes_acked:419005 bytes_received:24045 segs_out:809 segs_in:1252 send 344.5Mbps lastsnd:2 lastrcv:2 lastack:1 pacing_rate 688.1Mbps rcv_space:29200
```

### 上記の他に宛先も絞る
dstが利用できる。manに添付されているサンプル
```
$ ss -o state fin-wait-1 '( sport = :http or sport = :https )' dst 193.233.7/24
```

### 拡張情報を表示する
eオプションを付与することで多くの情報を表示する。iやoなどオプションも合わせて指定された感じだと思われる。
```
$ ss -e
Netid  State      Recv-Q Send-Q                             Local Address:Port                                              Peer Address:Port                
udp    ESTAB      0      0                                      10.0.2.15:56921                                              192.168.3.1:domain                uid:99 ino:24344 sk:ffff88003d529100 <->
tcp    ESTAB      0      0                                      10.0.2.15:ssh                                                   10.0.2.2:51654                 timer:(keepalive,51min,0) ino:23972 sk:ffff88003aae9f00 <->
tcp    ESTAB      0      0                                      10.0.2.15:ssh                                                   10.0.2.2:50396                 timer:(keepalive,66min,0) ino:19186 sk:ffff88003aae8f80 <->
tcp    ESTAB      0      0                                      10.0.2.15:ssh                                                   10.0.2.2:51731                 timer:(keepalive,66min,0) ino:28215 sk:ffff88000f17c7c0 <->
```

# ヘルプ
```
$ man ss
```

または
```
$ ss --help
Usage: ss [ OPTIONS ]
       ss [ OPTIONS ] [ FILTER ]
   -h, --help          this message
   -V, --version       output version information
   -n, --numeric       don't resolve service names
   -r, --resolve       resolve host names
   -a, --all           display all sockets
   -l, --listening     display listening sockets
   -o, --options       show timer information
   -e, --extended      show detailed socket information
   -m, --memory        show socket memory usage
   -p, --processes     show process using socket
   -i, --info          show internal TCP information
   -s, --summary       show socket usage summary
   -b, --bpf           show bpf filter socket information
   -Z, --context       display process SELinux security contexts
   -z, --contexts      display process and socket SELinux security contexts
   -N, --net           switch to the specified network namespace name

   -4, --ipv4          display only IP version 4 sockets
   -6, --ipv6          display only IP version 6 sockets
   -0, --packet        display PACKET sockets
   -t, --tcp           display only TCP sockets
   -S, --sctp          display only SCTP sockets
   -u, --udp           display only UDP sockets
   -d, --dccp          display only DCCP sockets
   -w, --raw           display only RAW sockets
   -x, --unix          display only Unix domain sockets
   -f, --family=FAMILY display sockets of type FAMILY

   -A, --query=QUERY, --socket=QUERY
       QUERY := {all|inet|tcp|udp|raw|unix|unix_dgram|unix_stream|unix_seqpacket|packet|netlink}[,QUERY]

   -D, --diag=FILE     Dump raw information about TCP sockets to FILE
   -F, --filter=FILE   read filter information from FILE
       FILTER := [ state STATE-FILTER ] [ EXPRESSION ]
       STATE-FILTER := {all|connected|synchronized|bucket|big|TCP-STATES}
         TCP-STATES := {established|syn-sent|syn-recv|fin-wait-{1,2}|time-wait|closed|close-wait|last-ack|listen|closing}
          connected := {established|syn-sent|syn-recv|fin-wait-{1,2}|time-wait|close-wait|last-ack|closing}
       synchronized := {established|syn-recv|fin-wait-{1,2}|time-wait|close-wait|last-ack|closing}
             bucket := {syn-recv|time-wait}
                big := {established|syn-sent|fin-wait-{1,2}|closed|close-wait|last-ack|listen|closing}
```


# 参考資料
- ssコマンドの使い方
  - https://qiita.com/hana_shin/items/632b3a1eb44bf84e94f7
