# 概要
TCPのオプションで指定できるSACK(Selective ACKnowledge)について説明します。
SACKには次の２つのオプションタイプが存在します。
- SACK Permitted
  - 3way handshakeの過程で利用されるオプションです。これを送った側はSACKが利用可能であることを通知する意味を持ちます。
- SACK
  - 3way handshakeでSACK Permittedが示されたホスト同士の通信では送信側にかけているデータを送ることができるようになりました。
  - wiresharkで見るとこのパケットは再送要求なので黒い行となります。


この拡張が無い時代のTCPでは、たとえば1番から100番のパケットのうち1-30、35-90までを受け取ったとしても30番よりも後ろのパケットをすべて再送要求していました。
この拡張を利用すると1-30と35-90は受け取ったのでそれ以外を再送してくださいということを相手側に明示できるようになります。これにより31-34、91-100といった必要なパケットだけを再送してもらうことができるようになります。

# 詳細

### 仕様概要
SACKを利用するかどうかは3way handshakeでSACK Permittedが双方でやりとりできれば利用することになります。
SACKは再送時にのみ送付されるパケットで受信したACKの範囲を明示します。

### データ書式
- SACK Permitted
  - SYNフラグが立てられたパケット以外で送付してはならない(MUST)
```
       +---------+---------+
       | Kind=4  | Length=2|
       +---------+---------+
```
- SACK
```
                         +--------+--------+
                         | Kind=5 | Length |
       +--------+--------+--------+--------+
       |      Left Edge of 1st Block       |
       +--------+--------+--------+--------+
       |      Right Edge of 1st Block      |
       +--------+--------+--------+--------+
       |                                   |
       /            . . .                  /
       |                                   |
       +--------+--------+--------+--------+
       |      Left Edge of nth Block       |
       +--------+--------+--------+--------+
       |      Right Edge of nth Block      |
       +--------+--------+--------+--------+
```

### サンプルデータ
- SACK Permitted
  - 接続元からSYNを指定した場合、及び応答サーバからSYN+ACK双方からSACK Permittedオプションが指定された場合(以下のサンプル参照)には、SACKが利用可能となる。サンプルデータを見るとわかる通りこのパケットはSACKを利用できるかどうかのフラグである。
```
    Options: (20 bytes), Maximum segment size, SACK permitted, Timestamps, No-Operation (NOP), Window scale
        ...
        TCP Option - SACK permitted
            Kind: SACK Permitted (4)
            Length: 2
        ...
```
- SACK
  - 以下の例ではAck#1920270のパケットの再送を要求します。ただし、Ack#1923086からAck#2065294まではすでに受信しているから再送不要ですといったことを意味する。
```
Transmission Control Protocol, Src Port: 54131, Dst Port: 443, Seq: 14648, Ack: 1920270, Len: 0
    ...
    Acknowledgment number: 1920270    (relative ack number)
    ...
    Options: (24 bytes), No-Operation (NOP), No-Operation (NOP), Timestamps, No-Operation (NOP), No-Operation (NOP), SACK
    ...
        TCP Option - SACK 1923086-2065294
            Kind: SACK (5)
            Length: 10
            left edge = 1923086 (relative)
            right edge = 2065294 (relative)
            [TCP SACK Count: 1]
```

# SeeAlso
- RFC2018: TCP Selective Acknowledgment Options
  - https://tools.ietf.org/html/rfc2018

