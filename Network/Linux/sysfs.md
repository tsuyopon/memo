# 概要
enp0s3はeth0, eth1など適宜変更すること

# 詳細

### MACアドレスが欲しい
```
$ cat /sys/class/net/enp0s3/address 
08:00:27:ff:ff:ff
```

### Ethernetケーブルが抜けたかどうかを確認する
```
$ cat /sys/class/net/enp0s3/carrier
1
```

次の状態を見ることで、up、down、unknownを表示することもできるようです。
```
$ cat /sys/class/net/enp0s3/operstate 
up
```

### ケーブルの値を抜き差しした回数が知りたい
```
$ cat /sys/class/net/enp0s3/carrier_changes 
28
```

### 送信キューを確保できるパケット数を確認する
```
$ cat /sys/class/net/enp0s3/tx_queue_len 
1000
```

# 参考
- /sys/class/netのドキュメント
  - https://www.kernel.org/doc/Documentation/ABI/testing/sysfs-class-net
