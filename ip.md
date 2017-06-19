# 概要
ipコマンドの使い方について

# 詳細
### ルーティング表示
```
$ ip route
default via 10.0.2.2 dev eth0  proto static  metric 1024 
10.0.2.0/24 dev eth0  proto kernel  scope link  src 10.0.2.15 
169.254.0.0/16 dev eth0  scope link  metric 1000 
```

### IPアドレスを表示する
```
$ ip -f inet addr
1: lo: <LOOPBACK,UP,LOWER_UP> mtu 65536 qdisc noqueue state UNKNOWN group default 
    inet 127.0.0.1/8 scope host lo
       valid_lft forever preferred_lft forever
2: eth0: <BROADCAST,MULTICAST,UP,LOWER_UP> mtu 1500 qdisc pfifo_fast state UP group default qlen 1000
    inet 10.0.2.15/24 brd 10.0.2.255 scope global dynamic eth0
       valid_lft 84423sec preferred_lft 84423sec
```

```
$ ip addr show
1: lo: <LOOPBACK,UP,LOWER_UP> mtu 65536 qdisc noqueue state UNKNOWN group default 
    link/loopback 00:00:00:00:00:00 brd 00:00:00:00:00:00
    inet 127.0.0.1/8 scope host lo
       valid_lft forever preferred_lft forever
    inet6 ::1/128 scope host 
       valid_lft forever preferred_lft forever
2: eth0: <BROADCAST,MULTICAST,UP,LOWER_UP> mtu 1500 qdisc pfifo_fast state UP group default qlen 1000
    link/ether 08:00:27:9c:51:c6 brd ff:ff:ff:ff:ff:ff
    inet 10.0.2.15/24 brd 10.0.2.255 scope global dynamic eth0
       valid_lft 84535sec preferred_lft 84535sec
    inet6 fe80::a00:27ff:fe9c:51c6/64 scope link 
       valid_lft forever preferred_lft forever
```

### ARPテーブルを表示する
```
$ ip neigh
10.0.2.2 dev eth0 lladdr 52:54:00:12:35:02 REACHABLE
```

### コネクション先の履歴
```
$  ip tcp_metrics | sort | more
10.0.2.2 age 2067.176sec source 10.0.2.15
121.119.163.196 age 679.196sec rtt 1625us rttvar 2250us cwnd 10 metric_5 13647 metric_6 9726 source 10.0.2.15
160.26.2.187 age 679.196sec rtt 375us rttvar 250us cwnd 10 metric_5 3063 metric_6 1531 source 10.0.2.15
91.189.88.161 age 679.196sec rtt 26375us rttvar 48750us cwnd 10 metric_5 211042 metric_6 195473 source 10.0.2.15
91.189.95.15 age 2057.444sec rtt 462750us rttvar 462750us cwnd 10 metric_5 3702959 metric_6 1851479 source 10.0.2.15
::1 age 1791.732sec rtt 4500us rttvar 9000us cwnd 10 metric_5 36700 metric_6 36672 source ::1
```

# 参考
- ipコマンドチートシート for Redhat Enterprise Linux
  - https://access.redhat.com/sites/default/files/attachments/rh_ip_command_cheatsheet_1214_jcs_print_ja4.pdf
