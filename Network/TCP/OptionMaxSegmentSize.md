# 概要
MSS（Maximum Segment Size。最大セグメント・サイズ）は、受信可能なセグメントの最大サイズを通信相手に通知するためのオプションです。MSSは3way handshakeにて決定されます。

MSSが存在しない場合には次のような課題がありました。
- 通信効率の低下
- 通信に遅延が発生する
- 全く通信することができない

経路MTU探索(PathMTUDiscovery.md)でMTUが決定され、MSSも決定するのでそちらも合わせて参考にしてください。

# 詳細

### サンプルデータ
以下は特定の通信における送信元(SYN)と応答元(SYN+ACK)のデータサンプルです。
接続時に1460でMSSを指定していますが、応答時に1420を指定していることがわかります。
1460という数値は一般的にEthernetのMTUである1500からIPv4ヘッダ最小サイズ20byte+TCPv4ヘッダ最小サイズ20byteの合計40byteを除いた値となっていることに注意します。IPv6だと最小ヘッダサイズが40byteとなるので1440となるでしょう。


- 送信元(SYN)
```
        TCP Option - Maximum segment size: 1460 bytes
            Kind: Maximum Segment Size (2)
            Length: 4
            MSS Value: 1460
```
- 応答元(SYN+ACK)
```
        TCP Option - Maximum segment size: 1420 bytes
            Kind: Maximum Segment Size (2)
            Length: 4
            MSS Value: 1420
```

### 設定方法サンプル
- Linux
  - routeコマンドにmssというオプションがあります。たとえば次のように経路毎に設定することができます。
```
$ sudo route add -net 192.168.10.0 netmask 255.255.255.0 mss 1000 gw 192.168.0.1
```
- Cisco
  - MTUを設定するとMSSはそこから40差し引かれた値となります。
```
(config-if)# ip mtu 1480
```
  - 次のように直接MSSを変更する方法もあるようです。
```
(config-if)# ip tcp adjust-mss 1440
```

# SeeAlso
- RFC6691: TCP Options and Maximum Segment Size (MSS)
  - https://tools.ietf.org/html/rfc6691


# TODO
- RFC6691を読んでいないので読む
