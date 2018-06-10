# 概要


# 詳細

### ICMP Echo Request(type: 8)を取得する方法

```
$ sudo tshark -i lo -Y 'icmp.type==8'
Running as user "root" and group "root". This could be dangerous.
Capturing on 'Loopback'
  1 0.000000000    127.0.0.1 -> 127.0.0.1    ICMP 98 Echo (ping) request  id=0x6666, seq=8/2048, ttl=64
  3 1.000000196    127.0.0.1 -> 127.0.0.1    ICMP 98 Echo (ping) request  id=0x6666, seq=9/2304, ttl=64
  5 2.000429905    127.0.0.1 -> 127.0.0.1    ICMP 98 Echo (ping) request  id=0x6666, seq=10/2560, ttl=64
  7 3.000718384    127.0.0.1 -> 127.0.0.1    ICMP 98 Echo (ping) request  id=0x6666, seq=11/2816, ttl=64
  9 4.000349650    127.0.0.1 -> 127.0.0.1    ICMP 98 Echo (ping) request  id=0x6666, seq=12/3072, ttl=64
 11 5.000266819    127.0.0.1 -> 127.0.0.1    ICMP 98 Echo (ping) request  id=0x6666, seq=13/3328, ttl=64
```
