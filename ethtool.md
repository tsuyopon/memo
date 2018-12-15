# 概要
ethtoolではデバイスドライバを経由してNICに対して設定変更などを行うことができるようだ。
TSOやGSOなどの設定もできるようだ

# 詳細

### イーサネットケーブルの接続状況や対応モードなどを確認したい
ethtoolにインターフェース識別子(eth0など)を引数として指定すると情報を出力します。
ケーブルが物理的に接続しているかどうかを表す"Link detected"を表示する場合にはsudoが必要です。
```
$ sudo ethtool p2p1
Settings for p2p1:
    Supported ports: [ TP ]
    Supported link modes:   10baseT/Half 10baseT/Full 
                            100baseT/Half 100baseT/Full 
                            1000baseT/Full 
    Supported pause frame use: No
    Supports auto-negotiation: Yes
    Advertised link modes:  10baseT/Half 10baseT/Full 
                            100baseT/Half 100baseT/Full 
                            1000baseT/Full 
    Advertised pause frame use: No
    Advertised auto-negotiation: Yes
    Speed: 1000Mb/s
    Duplex: Full
    Port: Twisted Pair
    PHYAD: 0
    Transceiver: internal
    Auto-negotiation: on
    MDI-X: Unknown
    Supports Wake-on: umbg
    Wake-on: d                                   // 
    Current message level: 0x00000007 (7)
                   drv probe link
    Link detected: yes                           // 物理的に接続されているかどうか
```

### ドライバに関する情報を表示する
iオプションを利用すれば良い
```
$ sudo ethtool -i p2p1
driver: e1000
version: 7.3.21-k8-NAPI
firmware-version: 
bus-info: 0000:00:03.0
supports-statistics: yes
supports-test: yes
supports-eeprom-access: yes
supports-register-dump: yes
supports-priv-flags: no
```

### キューサイズの確認
NICハードウェアの中にも受信キュー(rx queue)と送信キュー(tx queue)が存在します(**ハードウェアの中の話です**)。

このキューの値をいくつまで設定できるのか、現在いくつの値かを確認することができるのがgオプションです。
```
$ ethtool -g enp0s3
Ring parameters for enp0s3:
Pre-set maximums:
RX:     4096
RX Mini:    0
RX Jumbo:   0
TX:     4096
Current hardware settings:
RX:     256
RX Mini:    0
RX Jumbo:   0
TX:     256
```

設定値を変更するにはGオプションを使います。
```
$ sudo ethtool -G enp0s3 rx 512
$ ethtool -g enp0s3
Ring parameters for enp0s3:
Pre-set maximums:
RX:     4096
RX Mini:    0
RX Jumbo:   0
TX:     4096
Current hardware settings:
RX:     512
RX Mini:    0
RX Jumbo:   0
TX:     256
```

### イーサネットのデバッグレベルを変更する
以下はデバッグレベルが最大の場合の例です
```
$ ethtool -s eth0 msglvl 0xffff
```

デバッグフラグは次の通り
```
drv         0x0001     一般的なドライバーステータス
probe       0x0002     ハードウェアのプローブ
link        0x0004     リンクのステータス
timer       0x0008     定期的なステータスチェック
ifdown      0x0010     非アクティベートにしているインターフェース
ifup        0x0020     アクティベートにしているインターフェース
rx_err      0x0040     エラーを受信
tx_err      0x0080     エラー送信
intr        0x0200     割り込み処理
tx_done     0x0400     送信完了
rx_status   0x0800     受信完了
pktdata     0x1000     パケットコンテンツ
hw          0x2000     ハードウェアのステータス
wol         0x4000     Wake-on-LAN ステータス 
```

### 速度(Speed)を変更する。
例えば、100Mb/sに変更する場合には次のようにする。
```
# ethtool -s eth0 speed 100
```

### 全２重通信モード(duplex full)や半２重通信方式(duplex half)に切り替えたい
```
# ethtool -s eth0 duplex full

# ethtool -s eth0 duplex half
```

### デバイスのautonegotiationを切り返す。
on, offの引数で切り替えることができる。
```
$ ethtool -s eth0 autoneg off
```

### wol(Wakeup On Lan)のパケットを受け取れるようにする。
```
$ ethtool -s eth0 wol g 
```

### Offloadパラメータの出力と変更
```
$ sudo ethtool -k p2p1
Offload parameters for p2p1:
rx-checksumming: off
tx-checksumming: on
scatter-gather: on
tcp-segmentation-offload: on
udp-fragmentation-offload: off
generic-segmentation-offload: on
generic-receive-offload: on
large-receive-offload: off
rx-vlan-offload: on
tx-vlan-offload: on
ntuple-filters: off
receive-hashing: off
```

たとえば、以下でrx-checksummingやtx-checksummingを変更することができる。
```
# ethtool -K eth0 rx on
# ethtool -K eth0 tx on
```

scatter-gatherを変更する場合には次のようにする。この場合はsgとなるようだ。
```
$ target# ethtool -K eth0 sg on
```

### 統計情報を出力する
```
$ sudo ethtool -S p2p1
NIC statistics:
     rx_packets: 607365
     tx_packets: 446627
     rx_bytes: 259357794
     tx_bytes: 223155381
     rx_broadcast: 0
     tx_broadcast: 95
     rx_multicast: 0
     tx_multicast: 584
     rx_errors: 0
     tx_errors: 0
     tx_dropped: 0
     multicast: 0
     collisions: 0
     rx_length_errors: 0
     rx_over_errors: 0
     rx_crc_errors: 0
     rx_frame_errors: 0
     rx_no_buffer_count: 0
     rx_missed_errors: 0
     tx_aborted_errors: 0
     tx_carrier_errors: 0
     tx_fifo_errors: 0
     tx_heartbeat_errors: 0
     tx_window_errors: 0
     tx_abort_late_coll: 0
     tx_deferred_ok: 0
     tx_single_coll_ok: 0
     tx_multi_coll_ok: 0
     tx_timeout_count: 0
     tx_restart_queue: 0
     rx_long_length_errors: 0
     rx_short_length_errors: 0
     rx_align_errors: 0
     tx_tcp_seg_good: 28857
     tx_tcp_seg_failed: 0
     rx_flow_control_xon: 0
     rx_flow_control_xoff: 0
     tx_flow_control_xon: 0
     tx_flow_control_xoff: 0
     rx_long_byte_count: 259357794
     rx_csum_offload_good: 0
     rx_csum_offload_errors: 0
     alloc_rx_buff_failed: 0
     tx_smbus: 0
     rx_smbus: 0
     dropped_smbus: 0
```

### ARPを送ってみて統計情報を確認する
```
$ ethtool -S enp0s3 | grep tx_broad
     tx_broadcast: 10
$ arping -I enp0s3 10.0.2.2
ARPING 10.0.2.2 from 10.0.2.15 enp0s3
$ ethtool -S enp0s3 | grep tx_broad
     tx_broadcast: 11
```

### Register情報を出力する
```
$ sudo ethtool -d p2p1 
MAC Registers
-------------
0x00000: CTRL (Device control register)  0x08000249
      Endian mode (buffers):             little
      Link reset:                        reset
      Set link up:                       1
      Invert Loss-Of-Signal:             no
      Receive flow control:              enabled
      Transmit flow control:             disabled
      VLAN mode:                         disabled
      Auto speed detect:                 disabled
      Speed select:                      1000Mb/s
      Force speed:                       no
      Force duplex:                      no
0x00008: STATUS (Device status register) 0x00000083
      Duplex:                            full
      Link up:                           link config
      TBI mode:                          disabled
      Link speed:                        1000Mb/s
      Bus type:                          PCI
      Bus speed:                         33MHz
      Bus width:                         32-bit
0x00100: RCTL (Receive control register) 0x00008002
      Receiver:                          enabled
      Store bad packets:                 disabled
      Unicast promiscuous:               disabled
      Multicast promiscuous:             disabled
      Long packet:                       disabled
      Descriptor minimum threshold size: 1/2
      Broadcast accept mode:             accept
      VLAN filter:                       disabled
      Canonical form indicator:          disabled
      Discard pause frames:              filtered
      Pass MAC control frames:           don't pass
      Receive buffer size:               2048
0x02808: RDLEN (Receive desc length)     0x00001000
0x02810: RDH   (Receive desc head)       0x000000EE
0x02818: RDT   (Receive desc tail)       0x000000EC
0x02820: RDTR  (Receive delay timer)     0x00000000
0x00400: TCTL (Transmit ctrl register)   0x0103F0FA
      Transmitter:                       enabled
      Pad short packets:                 enabled
      Software XOFF Transmission:        disabled
      Re-transmit on late collision:     enabled
0x03808: TDLEN (Transmit desc length)    0x00001000
0x03810: TDH   (Transmit desc head)      0x00000062
0x03818: TDT   (Transmit desc tail)      0x00000062
0x03820: TIDV  (Transmit delay timer)    0x00000008
PHY type:                                M88
M88 PHY STATUS REGISTER:                 0x0000BC08
      Jabber:                            no
      Polarity:                          normal
      Downshifted:                       no
      MDI/MDIX:                          MDI
      Cable Length Estimate:             0-50 meters
      Link State:                        Up
      Speed & Duplex Resolved:           Yes
      Page Received:                     Yes
      Duplex:                            Full
      Speed:                             1000 mbps
M88 PHY CONTROL REGISTER:                0x00000868
      Jabber funtion:                    enabled
      Auto-polarity:                     disabled
      SQE Test:                          disabled
      CLK125:                            enabled
      Auto-MDIX:                         auto
      Extended 10Base-T Distance:        disabled
      100Base-TX Interface:              MII
      Scrambler:                         enabled
      Force Link Good:                   disabled
      Assert CRS on Transmit:            enabled
```

### ヘルプを見る
```
$ ethtool -h
ethtool version 3.2
Usage:
        ethtool DEVNAME Display standard information about device
        ethtool -s|--change DEVNAME Change generic options
        [ speed %d ]
        [ duplex half|full ]
        [ port tp|aui|bnc|mii|fibre ]
        [ autoneg on|off ]
        [ advertise %x ]
        [ phyad %d ]
        [ xcvr internal|external ]
        [ wol p|u|m|b|a|g|s|d... ]
        [ sopass %x:%x:%x:%x:%x:%x ]
        [ msglvl %d | msglvl type on|off ... ]
        ethtool -a|--show-pause DEVNAME Show pause options
        ethtool -A|--pause DEVNAME  Set pause options
        [ autoneg on|off ]
        [ rx on|off ]
        [ tx on|off ]
        ethtool -c|--show-coalesce DEVNAME  Show coalesce options
        ethtool -C|--coalesce DEVNAME   Set coalesce options
        [adaptive-rx on|off]
        [adaptive-tx on|off]
        [rx-usecs N]
        [rx-frames N]
        [rx-usecs-irq N]
        [rx-frames-irq N]
        [tx-usecs N]
        [tx-frames N]
        [tx-usecs-irq N]
        [tx-frames-irq N]
        [stats-block-usecs N]
        [pkt-rate-low N]
        [rx-usecs-low N]
        [rx-frames-low N]
        [tx-usecs-low N]
        [tx-frames-low N]
        [pkt-rate-high N]
        [rx-usecs-high N]
        [rx-frames-high N]
        [tx-usecs-high N]
        [tx-frames-high N]
        [sample-interval N]
        ethtool -g|--show-ring DEVNAME  Query RX/TX ring parameters
        ethtool -G|--set-ring DEVNAME   Set RX/TX ring parameters
        [ rx N ]
        [ rx-mini N ]
        [ rx-jumbo N ]
        [ tx N ]
        ethtool -k|--show-offload DEVNAME   Get protocol offload information
        ethtool -K|--offload DEVNAME    Set protocol offload
        [ rx on|off ]
        [ tx on|off ]
        [ sg on|off ]
        [ tso on|off ]
        [ ufo on|off ]
        [ gso on|off ]
        [ gro on|off ]
        [ lro on|off ]
        [ rxvlan on|off ]
        [ txvlan on|off ]
        [ ntuple on|off ]
        [ rxhash on|off ]
        ethtool -i|--driver DEVNAME Show driver information
        ethtool -d|--register-dump DEVNAME  Do a register dump
        [ raw on|off ]
        [ file FILENAME ]
        ethtool -e|--eeprom-dump DEVNAME    Do a EEPROM dump
        [ raw on|off ]
        [ offset N ]
        [ length N ]
        ethtool -E|--change-eeprom DEVNAME  Change bytes in device EEPROM
        [ magic N ]
        [ offset N ]
        [ length N ]
        [ value N ]
        ethtool -r|--negotiate DEVNAME  Restart N-WAY negotiation
        ethtool -p|--identify DEVNAME   Show visible port identification (e.g. blinking)
               [ TIME-IN-SECONDS ]
        ethtool -t|--test DEVNAME   Execute adapter self test
               [ online | offline | external_lb ]
        ethtool -S|--statistics DEVNAME Show adapter statistics
        ethtool -n|--show-nfc DEVNAME   Show Rx network flow classification options
        [ rx-flow-hash tcp4|udp4|ah4|esp4|sctp4|tcp6|udp6|ah6|esp6|sctp6 ]
        ethtool -f|--flash DEVNAME  Flash firmware image from the specified file to a region on the device
               FILENAME [ REGION-NUMBER-TO-FLASH ]
        ethtool -N|--config-nfc DEVNAME Configure Rx network flow classification options
        [ rx-flow-hash tcp4|udp4|ah4|esp4|sctp4|tcp6|udp6|ah6|esp6|sctp6 m|v|t|s|d|f|n|r... ]
        ethtool -x|--show-rxfh-indir DEVNAME    Show Rx flow hash indirection
        ethtool -X|--set-rxfh-indir DEVNAME Set Rx flow hash indirection
        equal N | weight W0 W1 ...
        ethtool -U|--config-ntuple DEVNAME  Configure Rx ntuple filters and actions
        [ delete %d ] |
        [ flow-type ether|ip4|tcp4|udp4|sctp4|ah4|esp4
            [ src %x:%x:%x:%x:%x:%x [m %x:%x:%x:%x:%x:%x] ]
            [ dst %x:%x:%x:%x:%x:%x [m %x:%x:%x:%x:%x:%x] ]
            [ proto %d [m %x] ]
            [ src-ip %d.%d.%d.%d [m %d.%d.%d.%d] ]
            [ dst-ip %d.%d.%d.%d [m %d.%d.%d.%d] ]
            [ tos %d [m %x] ]
            [ l4proto %d [m %x] ]
            [ src-port %d [m %x] ]
            [ dst-port %d [m %x] ]
            [ spi %d [m %x] ]
            [ vlan-etype %x [m %x] ]
            [ vlan %x [m %x] ]
            [ user-def %x [m %x] ]
            [ action %d ]
            [ loc %d]]
        ethtool -u|--show-ntuple DEVNAME    Get Rx ntuple filters and actions
        [ rule %d ]
        ethtool -P|--show-permaddr DEVNAME  Show permanent hardware address
        ethtool -w|--get-dump DEVNAME   Get dump flag, data
        [ data FILENAME ]
        ethtool -W|--set-dump DEVNAME   Set dump flag of the device
        N
        ethtool -l|--show-channels DEVNAME  Query Channels
        ethtool -L|--set-channels DEVNAME   Set Channels
               [ rx N ]
               [ tx N ]
               [ other N ]
               [ combined N ]
        ethtool --show-priv-flags DEVNAME   Query private flags
        ethtool --set-priv-flags DEVNAME    Set private flags
        FLAG on|off ...
        ethtool -h|--help       Show this help
        ethtool --version       Show version number
```

# TODO
- 超概要レベルのことしか書いていないので、今後ネットワーク関連をもっとしっかりやるときには一度深くひとめぐりするとイーサネット周りの知識がつきそうだ

# 参考URL
- https://access.redhat.com/documentation/ja-JP/Red_Hat_Enterprise_Linux/6/html/Deployment_Guide/s2-ethtool.html
