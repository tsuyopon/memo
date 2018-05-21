# 概要
pingコマンドについて

# 詳細
### サイズを指定して、フラグメントを禁止する。
Dオプションでフラグメントを禁止(DFビット制御)し、sオプションでサイズを指定しています。
経路MTU探索する際にICMPを調整しますが、それと同様のことをpingで確認することができます。
```
$ ping -D -s 1472 -c 2 rakuten.co.jp
PING rakuten.co.jp (133.237.61.176): 1472 data bytes
556 bytes from softbank060101238212.bbtec.net (60.101.238.212): frag needed and DF set (MTU 1460)
Vr HL TOS  Len   ID Flg  off TTL Pro  cks      Src      Dst
 4  5  00 dc05 1ded   0 0000  3f  01 90ec 192.168.3.2  133.237.61.176 

Request timeout for icmp_seq 0
556 bytes from softbank060101238212.bbtec.net (60.101.238.212): frag needed and DF set (MTU 1460)
Vr HL TOS  Len   ID Flg  off TTL Pro  cks      Src      Dst
 4  5  00 dc05 b674   0 0000  3f  01 f864 192.168.3.2  133.237.61.176 
```
