# 概要
tsharkコマンドについてまとめておく

# 詳細

### tsharkコマンドのインストール
wiresharkパッケージに包括されているのでインストールします。
```
$ sudo yum install wireshark
```

### パケットの詳細
```
$ sudo tshark -i lo -O mysql -Y 'tcp.dstport==3306' -V
```
- i: インターフェースの指定
- O: Verbose結果を表示したいアプリケーションレイヤのプロトコルを指定
- Y: wiresharkのパケットをフィルタするための条件
- V: パケットの詳細な解析結果を表示する。(Oオプションと合わせて使うのが良い)


# プロトコル別(MySQL)

### MySQL

Oオプションの後にmysqlを指定しているが、これはアプリケーションレイヤーとしてmysqlの結果だけ出力してくれとなる。
Vオプションを付与してOオプションを付与しないとデフォルトで全レイヤの情報が全て出力されるので必要な出力結果のみフィルタしたい場合に非常に便利です。
```
$ sudo tshark -i lo -O mysql -Y 'tcp.dstport==3306' -V
Running as user "root" and group "root". This could be dangerous.
Capturing on 'Loopback'
Frame 21: 86 bytes on wire (688 bits), 86 bytes captured (688 bits) on interface 0
Ethernet II, Src: 00:00:00_00:00:00 (00:00:00:00:00:00), Dst: 00:00:00_00:00:00 (00:00:00:00:00:00)
Internet Protocol Version 4, Src: 127.0.0.1 (127.0.0.1), Dst: 127.0.0.1 (127.0.0.1)
Transmission Control Protocol, Src Port: 37360 (37360), Dst Port: mysql (3306), Seq: 1, Ack: 1, Len: 20
MySQL Protocol
    Packet Length: 16
    Packet Number: 0
    Request Command Query
        Command: Query (3)
        Statement: show PROCEDURES

Frame 23: 66 bytes on wire (528 bits), 66 bytes captured (528 bits) on interface 0
Ethernet II, Src: 00:00:00_00:00:00 (00:00:00:00:00:00), Dst: 00:00:00_00:00:00 (00:00:00:00:00:00)
Internet Protocol Version 4, Src: 127.0.0.1 (127.0.0.1), Dst: 127.0.0.1 (127.0.0.1)
Transmission Control Protocol, Src Port: 37360 (37360), Dst Port: mysql (3306), Seq: 21, Ack: 170, Len: 0

Frame 44: 89 bytes on wire (712 bits), 89 bytes captured (712 bits) on interface 0
Ethernet II, Src: 00:00:00_00:00:00 (00:00:00:00:00:00), Dst: 00:00:00_00:00:00 (00:00:00:00:00:00)
Internet Protocol Version 4, Src: 127.0.0.1 (127.0.0.1), Dst: 127.0.0.1 (127.0.0.1)
Transmission Control Protocol, Src Port: 37360 (37360), Dst Port: mysql (3306), Seq: 21, Ack: 170, Len: 23
MySQL Protocol
    Packet Length: 19
    Packet Number: 0
    Request Command Query
        Command: Query (3)
        Statement: SELECT * FROM city
```
