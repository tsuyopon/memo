# ネットワークスケール

ネットワークをスケールするためには、 これらの用語の意味や機能を正しく押さえておく必要があります。

- RSS: Receive Side Scaling
- RPS: Receive Packet Steering
- RFS: Receive Flow Steering
- Accelerated Receive Flow Steering
- XPS: Transmit Packet Steering

上記用語の意味や機能については次でまとまっています。
- https://www.kernel.org/doc/Documentation/networking/scaling.txt

またこの他にも次の用語も押さえておく必要がある。
- TSO/GSO/LSO (これら3つは同じ意味らしい)
  - TSO: TCP Segmentation Offload (TSOはLSOやGSOと呼ばれることがある) 
  - GSO: Generic Segmentation Offload 
  - LSO: Large Segment Offload
- LSO/GRO (H/WかS/W側の処理によるかの違い)
  - LRO: Large Receive Offload
  - GRO: Generic Receive Offload
- TOE: TCP Offload Engine
- Interrupt Coalescing

これらの用語を正しく説明し、生まれた背景(問題点)、解決策、H/WやOSなどの制約事項についてまとめていきます。


### irqbalance
複数コアへの分散はirqbalanceデーモンにより10秒ごとに/proc配下のsmp_affinityが書き換えられています。


### Recieve Side Scaling(RSS)について
最近のNICにおいてはH/Wの中で送受信用のキューを保持しています。
この仕組みを利用することによって、通常は1つのCPUで行う受信制御を複数のCPUで行うことができます。
<img src="_svg/rss.png">

RSS登場前の問題点、解決策、解決方法を確認する
- 問題点
  - ソフトウェア割り込みはNICの割り込みがかかったCPUへスケジューリングされる
  - polling処理からデータのプロトコルスタックの処理の実行まではソフトウェア割り込み内で実行される。
  - NICの割り込みがかかっているCPUにのみ負荷がかかる。
  - ソフトウェア割り込みを実行しているCPUがボトルネックとなって性能がスケールしなくなる。
- 解決策
  - パケットを複数のCPUへ分散させてからプロトコルを処理する仕組みである必要がある。
  - ただし、TCPの順番保証を考えた場合にはパケットの並べ直しによるTCP Reorderingのコストが発生してパフォーマンスが低下する懸念はある。
- 解決方法
  - CPUごとに別々の受信キュー(RX-queue)を持つNIC(MultiQueue NIC)が存在する。
  - RX-queueごとに独立した割り込みを持つ
  - 同じフローに属するパケットは同じキューへ、異なるフローに属するパケットはなるべく別のキューへ分散(パケットヘッダのHash値計算により宛先キューを決定する)
- 制約事項
  - 現在、RSSはWindowsとLinux両方でサポートされているハードウェアでPCIバスのMSI-Xサポート、NICへのRSS実装対応サポートが必要となる。

### Receive Packet Steering(RPS)
RSSの機能でNIC中のqueueから各CPUに分散されると、そのCPUからbacklogに登録されます。

利用方法
```
# echo "f" > /sys/class/net/eth0/queues/rx-0/rps_cpus
# echo 4096 > /sys/class/net/eth0/queues/rx-0/rps_flow_cnt
```


### TCP Offload Engine(TOE)について
OSでプロトコル処理するのをやめてNICで処理させる仕組みで、TCP/IPの処理を全てハードウェア側で実施する(フルオフロード)仕組みである。
Linuxではサポート予定はない。

デメリットとしては、TOEにセキュリティホールが生じてもOS側から対応することができない。


### Transmit Packet Steering(XPS)
MultiQueue NICは送信キューも複数持っている。XPSはCPUと送信キューの割り当てを決めるI/F



### Interrupt Coalescing
NICがOS負荷を考慮して割り込みを間引く仕組みであり、パケット数個に１回の割り込み処理を行う。或いは一定時間待ってから割り込みする。

- 問題点
  - パケットが到達するごとにソフトウェア割り込みが発生するとコンテキストスイッチの負荷が非常に多くなる
- 解決策
  - 数個に1回でパケット割り込みするか、一定期間待ってからパケット割り込みする。
  - レイテンシが上がってしまう
- 制約事項
  - 



### TSO/GSO/LSO
TCPセグメントへの分割処理をハードウェア側で実施する仕組み。
CPUの処理速度よりもNICの処理速度の方が早いために処理を




### Large Receive Offload(LRO) 
セグメントの再構築をハードウェアで実施する仕組みです。つまり、NICが受信したTCPパケットを結合して大きなパケットにしてからOSへ渡します。
LinuxではソフトウェアによりLROが実装されています。これをGROというようです。


- 詳細
  - https://www.slideshare.net/syuu1228/ethernet-39611199



### メモ



```
$ 
ethtool
-
S ens1f0 | grep '
rx_queue
_.*_packets'
rx_queue_0_packets: 198005155
rx_queue_1_packets: 153339750
rx_queue_2_packets: 162870095
rx_queue_3_packets: 172303801
rx_queue_4_packets: 153728776
rx_queue_5_packets: 158138563
rx_queue_6_packets: 164411653
rx_queue_7_packets: 165924489
rx_queue_8_packets: 176545406
rx_queue_9_packets: 165340188
rx_queue_10_packets: 150279834
rx_queue_11_packets: 150983782
rx_queue_12_packets: 157623687
rx_queue_13_packets: 150743910
rx_queue_14_packets: 158634344
rx_queue_15_packets: 158497890
rx_queue_16_packets: 4
rx_queue_17_packets: 3
rx_queue_18_packets: 0
rx_queue_19_packets: 8
```



# TODO
- Direct Memory Access

# 参考URL
- https://www.kernel.org/doc/Documentation/networking/scaling.txt
- Boost UDP Transaction Performance
  - http://events.linuxfoundation.jp/sites/events/files/slides/LinuxConJapan2016_makita_160714.pdf
- 10GbE時代のネットワークI/O高速化
  - https://www.slideshare.net/syuu1228/10-gbeio
  - 非常に素晴らしい資料
- FreeBSD 10ギガビットネットワーク高速通信の秘密
  - http://news.mynavi.jp/articles/2008/10/29/bsdcon5/002.html
