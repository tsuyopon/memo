# 概要
tc(Traffic Control)コマンドを使ってOS側で強制的にネットワーク遅延やパケットロスなどを発生させることができます。
Linuxカーネル2.6以降からこの機能を利用できるとのこと

# 詳細

### tcの設定を確認する
```
$ tc qdisc show
qdisc noqueue 0: dev lo root refcnt 2 
qdisc pfifo_fast 0: dev eth0 root refcnt 2 bands 3 priomap  1 2 2 2 1 2 0 0 1 1 1 1 1 1 1 1
```

### ネットワーク遅延を引き起こす
まず、www.yahoo.co.jpにpingした結果を載せておきます。15~19ms程度で応答しています。
```
$ ping www.yahoo.co.jp
PING edge.g.yimg.jp (183.79.249.252) 56(84) bytes of data.
64 bytes from 183.79.249.252 (183.79.249.252): icmp_seq=1 ttl=63 time=15.9 ms
64 bytes from 183.79.249.252 (183.79.249.252): icmp_seq=2 ttl=63 time=17.8 ms
64 bytes from 183.79.249.252 (183.79.249.252): icmp_seq=3 ttl=63 time=19.4 ms
64 bytes from 183.79.249.252 (183.79.249.252): icmp_seq=4 ttl=63 time=17.2 ms
^C
--- edge.g.yimg.jp ping statistics ---
4 packets transmitted, 4 received, 0% packet loss, time 3003ms
rtt min/avg/max/mdev = 15.980/17.639/19.448/1.243 ms
```

200ms遅延させるネットワーク設定を入れます。
```
$ sudo tc qdisc add dev eth0 root netem delay 200ms
```

そして、再度www.yahoo.co.jpにpingすると先程の値+200ms以上であることが確認できます。
```
$ ping www.yahoo.co.jp
PING edge.g.yimg.jp (182.22.25.252) 56(84) bytes of data.
64 bytes from 182.22.25.252 (182.22.25.252): icmp_seq=1 ttl=63 time=209 ms
64 bytes from 182.22.25.252 (182.22.25.252): icmp_seq=2 ttl=63 time=216 ms
64 bytes from 182.22.25.252 (182.22.25.252): icmp_seq=3 ttl=63 time=235 ms
64 bytes from 182.22.25.252 (182.22.25.252): icmp_seq=4 ttl=63 time=215 ms
^C
--- edge.g.yimg.jp ping statistics ---
4 packets transmitted, 4 received, 0% packet loss, time 3003ms
rtt min/avg/max/mdev = 209.096/219.206/235.113/9.658 ms
```

設定を確認します
```
$ sudo tc qdisc show dev eth0
qdisc netem 8001: root refcnt 2 limit 1000 delay 200.0ms
```

設定を削除すると、通常の設定に戻ります。
```
$ sudo tc qdisc del dev eth0 root
$ sudo tc qdisc show dev eth0
qdisc pfifo_fast 0: root refcnt 2 bands 3 priomap  1 2 2 2 1 2 0 0 1 1 1 1 1 1 1 1
```

### 帯域制限を行う 
TBF(Token Buffer Filter)と呼ばれる仕組みを用いる。
```
$ sudo tc qdisc add dev eth0 root tbf limit 200Kb buffer 100Kb rate 200Kbps
```

- limit 200Kb
  - データキューのサイズを 200KByte に設定
- buffer 100Kb
  - パケットのサイズを 100KByte に設定
  - 「100Kb/8」 のようなオプションを設定している場合もあるが、付与してもしなくても変わらない
- rate 200Kbps
  - 帯域幅を 200KBps に設定

なお、tcでのbは「ビット」ではなく「バイト」であることに注意すること


なお、設定を解除するには次の通り
```
$ sudo tc qdisc del dev eth0 root
```

### ネットワーク遅延と同時にパケットロスを引き起こす
```
$ sudo tc qdisc add dev eth0 root netem delay 100ms 10ms loss 10%
$ sudo tc qdisc show dev eth0
qdisc netem 8005: root refcnt 2 limit 1000 delay 100.0ms  10.0ms loss 10%
```

pingを投げてみる。20%packet lossなので完全に一致するわけではない?
```
$ ping www.yahoo.co.jp -c 10
PING edge.g.yimg.jp (183.79.249.252) 56(84) bytes of data.
64 bytes from 183.79.249.252 (183.79.249.252): icmp_seq=1 ttl=63 time=121 ms
64 bytes from 183.79.249.252 (183.79.249.252): icmp_seq=2 ttl=63 time=119 ms
64 bytes from 183.79.249.252 (183.79.249.252): icmp_seq=3 ttl=63 time=104 ms
64 bytes from 183.79.249.252 (183.79.249.252): icmp_seq=4 ttl=63 time=168 ms
64 bytes from 183.79.249.252 (183.79.249.252): icmp_seq=5 ttl=63 time=143 ms
64 bytes from 183.79.249.252 (183.79.249.252): icmp_seq=6 ttl=63 time=116 ms
64 bytes from 183.79.249.252 (183.79.249.252): icmp_seq=7 ttl=63 time=109 ms
64 bytes from 183.79.249.252 (183.79.249.252): icmp_seq=10 ttl=63 time=202 ms

--- edge.g.yimg.jp ping statistics ---
10 packets transmitted, 8 received, 20% packet loss, time 9010ms
rtt min/avg/max/mdev = 104.977/135.764/202.602/31.752 ms
```

設定を元に戻します。
```
$ sudo tc qdisc del dev eth0 root
$ sudo tc qdisc show dev eth0
qdisc pfifo_fast 0: root refcnt 2 bands 3 priomap  1 2 2 2 1 2 0 0 1 1 1 1 1 1 1 1
```

### 不正なパケットを送る
次の設定で10%分のパケットを不正なパケットにすることができます。
あまり大きくすると輻輳の影響で応答がほとんど返ってこなくなるようですので、とりあえず試してみるといった場合には10%程度にしておくといいかもしれません。
```
$ tc qdisc add dev eth0 root netem corrupt 10%
```

設定を削除するには次のようにします。
```
$ tc qdisc del dev eth0 root netem corrupt 10%
```

# TODO
- tc機能の概要部分しかまとめていないが、まだまだ奥が深いコマンドなのでまとめる。
- 次のあたりの記事内容についてはここには記していないので調査したい
  - http://labs.gree.jp/blog/2014/10/11288/

# SeeAlso
- GREE Engineers Blog: よくわかるLinux帯域制限
  - http://labs.gree.jp/blog/2014/10/11266/
