# ネットワークスタックにおけるスケール

これらの用語の意味や機能を正しく押さえておく必要があります。

- RSS: Receive Side Scaling
- RPS: Receive Packet Steering
- RFS: Receive Flow Steering
- Accelerated Receive Flow Steering
- XPS: Transmit Packet Steering

### Recieve Side Scaling(RSS)について
最近のNICにおいてはH/Wの中で送受信用のキューを保持しています。
この仕組みを利用することによって、通常は1つのCPUで行う受信制御を複数のCPUで行うことができます。
<img src="_svg/rss.png">

/proc/irq/<irq>/smp_affinityによって

### Receive Packet Steering
RSSの機能でNIC中のqueueから各CPUに分散されると、そのCPUからbacklogに登録されます。



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

### 


# 参考URL
- https://www.kernel.org/doc/Documentation/networking/scaling.txt
- Boost UDP Transaction Performance
  - http://events.linuxfoundation.jp/sites/events/files/slides/LinuxConJapan2016_makita_160714.pdf
