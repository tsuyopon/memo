# 概要
Path MTU Discovery(経路MTU探索)とは、経路上のMTU最小値を調べることです。

次の3つの課題をクリアするMTUを決定する仕組みであると考えると良い
- MTUよりサイズが大きい場合は、分割される
- できれば分割されない方が良い（最初からMTUより小さいサイズで送るべし）
- 異なるMTUが設定された複数の機器を通る場合がある

# 詳細

### 仕組み
仕組みとしては次の通り
- 送信側は分割禁止(IPのDFビットが1)に設定したサイズの大きなICMPパケットを通信相手に送信します。
- サイズが大きいと途中のルーターから「分割しないと送れない」というエラーが返ってきます。
- 送信側はパケットサイズを少しずつ小さくしながら分割禁止のICMPパケットを送り、エラーがメッセージが返ってこないで相手から応答が来るまで繰り返す。その時の応答が最適なMTUサイズだとわかる。

### 試してみる
pingコマンドにはフラグメント禁止オプション(D)とサイズ指定オプション(s)があるので、それらを合わせて同様のことを実現できます。

- 正常に応答が返ってくる場合
```
$ ping -D -s 500 -c 2 xxx.co.jp
PING xxx.co.jp (133.237.61.176): 500 data bytes
508 bytes from 133.237.61.176: icmp_seq=0 ttl=248 time=8.735 ms
508 bytes from 133.237.61.176: icmp_seq=1 ttl=248 time=10.176 ms
```
- エラー応答が返ってくる場合 
```
$ ping -D -s 1450 -c 2 xxx.co.jp
PING xxx.co.jp (133.237.61.176): 1450 data bytes
556 bytes from softbank060101238212.bbtec.net (60.101.238.212): frag needed and DF set (MTU 1460)
Vr HL TOS  Len   ID Flg  off TTL Pro  cks      Src      Dst
 4  5  00 c605 eca0   0 0000  3f  01 c24e 192.168.3.2  133.237.61.176 

Request timeout for icmp_seq 0
556 bytes from softbank060101238212.bbtec.net (60.101.238.212): frag needed and DF set (MTU 1460)
Vr HL TOS  Len   ID Flg  off TTL Pro  cks      Src      Dst
 4  5  00 c605 4843   0 0000  3f  01 66ac 192.168.3.2  133.237.61.176
```
- サイズが大きすぎてパケット自体が破棄されている場合
```
$ ping -D -s 1500 -c 2 xxx.co.jp
PING xxx.co.jp (133.237.61.176): 1500 data bytes
ping: sendto: Message too long
ping: sendto: Message too long
Request timeout for icmp_seq 0
```

DFフラグ付きのIPパケットに対して、途中のルータやあて先コンピュータがエラーを返している場合の例であったが、ファイアウォールの設定によっては、エラーを返さずに、単にパケットを捨てている場合もある。
このような場合は、pingの応答は「Packet needs to be fragmented but DF set.」ではなく、単に「Request timed out.（応答がない）」となる。つまり、サイズが大きすぎる場合にはパケットが捨てられていることになる

# SeeAlso
- https://ja.wikipedia.org/wiki/Maximum_Transmission_Unit
