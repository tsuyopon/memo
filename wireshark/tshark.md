# 概要
tsharkコマンドについてまとめておく
各種プロトコル別操作についてはtsharkディレクトリの方で説明する。

# 詳細

## tsharkコマンドのインストール
wiresharkパッケージに包括されているのでインストールします。
```
$ sudo yum install wireshark
```

## パケットの詳細
```
$ sudo tshark -i lo -O mysql -Y 'tcp.dstport==3306' -V
```
- i: インターフェースの指定
- O: Verbose結果を表示したいアプリケーションレイヤのプロトコルを指定
- Y: wiresharkのパケットをフィルタするための条件
- V: パケットの詳細な解析結果を表示する。(Oオプションと合わせて使うのが良い)

## 指定できるinterfaceを確認する
```
$ sudo tshark -D
1. enp0s3
2. nflog
3. nfqueue
4. usbmon1
5. any
6. lo (Loopback)
```

iオプションの後にこの番号を指定することもできます。


## フィルタリング
fオプションはYオプションと似ているが、libpcapフィルタsyntaxによるフィルタを指定することができる。
fオプションについてはlibpcapのオプションなどを参考にすると良いかも
- http://dog.tele.jp/winpcap/html/group__language.html

本来はiオプションでinterfaceを指定するがここでは使い方のために省略している

### TCP, UDP, ICMPパケットを抽出する
```
$ sudo tshark -f "tcp"
$ sudo tshark -f "udp"
$ sudo tshark -f "icmp"
```

### ポート番号を指定する
```
$ sudo tshark -f "port 80"
```

### プロトコル + ポート番号でフィルタ指定する
```
$ sudo tshark -f "tcp and port 80"
```

### 特定のIPアドレスのパケットを取得する
以下は127.0.0.1だが、他の宛先などに変更すると良い
```
$ sudo tshark -f 'host 127.0.0.1'
```

### ネットワークアドレスで指定する
```
$ sudo tshark -f 'net 172.16.0.0 mask 255.255.0.0'
```

### 特定の範囲のポート番号を取得する
```
$ sudo tshark -f 'tcp portrange 16000-16100'
```

### ポート番号を指定する

## N秒間だけキャプチャーする
以下は10秒間の場合
```
$ tshark -a duration:10
```

## キャプチャファイルのローテートを指定する
ファイルサイズが10キロバイトに達すると次のファイルに記録。ファイル数が3つになったら停止する
```
$tshark -i lo -f 'port 53' -w packet filesize:10 -a files:3
```

## 受信するパケット数を指定しておく
cオプションで指定することができます。指定した数だけ受信するとパケットキャプチャを終了します。
```
$ sudo tshark -c 10
Running as user "root" and group "root". This could be dangerous.
Capturing on 'enp0s3'
  1 0.000000000    10.0.2.15 -> 139.162.66.25 NTP 90 NTP Version 4, client
  2 0.037561784 139.162.66.25 -> 10.0.2.15    NTP 90 NTP Version 4, server
  3 0.558225897    10.0.2.15 -> 10.0.2.2     SSH 254 Encrypted response packet len=200
  4 0.558552063     10.0.2.2 -> 10.0.2.15    TCP 60 61798 > ssh [ACK] Seq=1 Ack=201 Win=65535 Len=0
  5 1.066609284    10.0.2.15 -> 10.0.2.2     SSH 286 Encrypted response packet len=232
  6 1.066975387     10.0.2.2 -> 10.0.2.15    TCP 60 61798 > ssh [ACK] Seq=1 Ack=433 Win=65535 Len=0
  7 1.569065062    10.0.2.15 -> 10.0.2.2     SSH 286 Encrypted response packet len=232
  8 1.569556966     10.0.2.2 -> 10.0.2.15    TCP 60 61798 > ssh [ACK] Seq=1 Ack=665 Win=65535 Len=0
  9 2.070801561    10.0.2.15 -> 10.0.2.2     SSH 286 Encrypted response packet len=232
 10 2.071348159     10.0.2.2 -> 10.0.2.15    TCP 60 61798 > ssh [ACK] Seq=1 Ack=897 Win=65535 Len=0
10 packets captured
```

## hex, ASCIIダンプを取得する
```
$ sudo tshark  -x -c 3
Running as user "root" and group "root". This could be dangerous.
Capturing on 'enp0s3'
0000  08 00 27 af c9 96 52 54 00 12 35 02 08 00 45 00   ..'...RT..5...E.
0010  00 28 08 81 00 00 40 06 5a 3f 0a 00 02 02 0a 00   .(....@.Z?......
0020  02 0f f7 78 00 16 04 a9 74 5f cd 20 bf 24 50 10   ...x....t_. .$P.
0030  ff ff 9a e7 00 00 00 00 00 00 00 00               ............

0000  52 54 00 12 35 02 08 00 27 af c9 96 08 00 45 10   RT..5...'.....E.
0010  00 70 40 97 40 00 40 06 e1 d0 0a 00 02 0f 0a 00   .p@.@.@.........
0020  02 02 00 16 f7 78 cd 20 bf 24 04 a9 74 5f 50 18   .....x. .$..t_P.
0030  b6 80 18 73 00 00 00 00 00 30 9c 82 23 65 74 15   ...s.....0..#et.
0040  25 7d ca 25 f0 f2 79 f1 50 f0 b4 33 f7 af 36 fc   %}.%..y.P..3..6.
0050  e9 71 9a 2f 4f e2 8d b9 e0 80 3b 62 25 5d fd 52   .q./O.....;b%].R
0060  da cc 1d af 9b 42 19 20 d0 d5 6d 1c 5b 56 14 a5   .....B. ..m.[V..
0070  7e ca de af 2c c6 11 c4 4e f7 39 d0 6c 83         ~...,...N.9.l.

0000  08 00 27 af c9 96 52 54 00 12 35 02 08 00 45 00   ..'...RT..5...E.
0010  00 28 08 82 00 00 40 06 5a 3e 0a 00 02 02 0a 00   .(....@.Z>......
0020  02 0f f7 78 00 16 04 a9 74 5f cd 20 bf 6c 50 10   ...x....t_. .lP.
0030  ff ff 9a 9f 00 00 00 00 00 00 00 00               ............

3 packets captured
```


# 参考URL
- https://qiita.com/hana_shin/items/0d997d9d9dd435727edf
