# 概要
IPv4について

# 詳細

## IPv4データフォーマット

- Refer from: https://tools.ietf.org/html/rfc791#section-3.1
```
    0                   1                   2                   3
    0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
   |Version|  IHL  |Type of Service|          Total Length         |
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
   |         Identification        |Flags|      Fragment Offset    |
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
   |  Time to Live |    Protocol   |         Header Checksum       |
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
   |                       Source Address                          |
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
   |                    Destination Address                        |
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
   |                    Options                    |    Padding    |
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

                    Example Internet Datagram Header
```

- Version(4bit)
  - IPv4の場合には常に4が格納されます
- IHL(Ip Header Length)(4bit)
  - IPヘッダの流され32bit単位で表される。この値によりデータの開始位置を知ることができる。最小値は5で表され、データ開始位置はのように計算される。
    - 5 * 32 = 160bits = 20bytes
  - 最大値は15となる。この場合データ開始位置は次の通り
    - 15 * 32 = 480bits = 60bytes.
- Type of Service!(8bit)
  - サービス種別(TOS)を表す。現在このフィールドは使われていないらしい。
- Total Length(16bit)
  - IPヘッダを含むパケットの全長をオクテット単位で表したもの。最大は65,535オクテット
- Identification(16bit)
  - It is used as packet identifier.
  - If packet divided into some packets, we can ackowledge the original packet.
- Flags(3bit)
  - 0: Not used
  - 1: forbid divide(1), allow divide(0)
  - 2: continue fragment(1), last fragment(0)
- Fragment Offset(13bit)
  - ルータなどがパケットを断片化した際に、その位置を8オクテット単位で格納する。断片化したパケットの復元に用いられる。
  - Identification, FlagsとこのFragment Offsetの３つの値からフラグメントを行うことができます。
- Time to Live(8bit)
  - ルーターはパケットを転送するたびにこの値を1つ減らします。パケットがネットワーク上で無限に巡回する問題を防ぐ効果があります。
- Protocol(8bit)
  - TCPなどの上位プロトコルを表す番号が設定されます。たとえば、ICMP、TCP、UDP、IPv6、EIGRP、OSPFなどです。
- Header Checksum(16bit)
  - IPヘッダの誤り検査に用いられる。転送毎に生存時間の値が変わるため、ルータはチェックサムも転送毎に再計算する必要がある。
- Source Addrress(32bit)
  - パケットの送信元IPアドレス
- Destination Addrress(32bit)
  - パケットの送信先IPアドレス
- Options(variable length)
  - It is added as optional function. There are a lot of Options not only below.
    - Security
    - Loose Source Routing
    - Record Route
    - Internet Timestamp
- Padding
  - Optionsが可変長のために32bit単位とするために必要であれば0をパディングとしてパケットに追加する。


Type Of Services(8bit) is re-designed to this. But, still not used at all.
- Differentiated Services Code Point (DSCP) (6bits)
- Explicit Congestion Notification (ECN) Field (2 bits) 

These three parameters(Identification, Flagment Offset, Flags) are used as packet divide purpose.

**TODO**
- check sequence using Identification, Flags, Flagment Offset 
- Check caliculating Header Checksum 

### Flags(3bit)について
実際に利用されているのは3bit中の2bitのみである。
次のような情報として利用される。
- MF(More Fragment)ビット
  - フラグメントがさらに続くかどうかを表すビットである。
  - 1つのIPパケットを複数に分割した場合に、最後のパケットではこのビットを0にして、それ以外のパケットではこのビットを1にすることで、後続のパケットが存在するかどうかを伝えることができる。
- DF(Donot Fragment)ビット
  - ICMPを利用した経路MTU探索でMTUを算出する場合に用いられるフラグである。
  - このビットが有効なパケットはフラグメントしてはならない仕組みとなっています。断片化されたパケットの再構築(Reassembly)は宛先である装置が行う。

## How to culculate IPv4 Checksum?
Try it later!
- http://qiita.com/h-sh/items/9e16b55adec787b82f52
- http://www.erg.abdn.ac.uk/users/gorry/course/inet-pages/ip-cksum.html

### ヘッダチェックサムの計算方法

- 1. ヘッダの一連を ヘッダの一連を16bit単位に分割する。
- 2. 1の補数演算を用いてワードを合計する。
- 3. 桁上げをすべて加算して最後の結果の桁上げをすべて加算して最後の結果の1の補数を取る。
- 4. 受信ホストで同様の計算を行い、チェックサムと照らし合わせて破損がないことを確認する。

### I want to know more about "Options" fileds.
See 
- http://www.wata-lab.meijo-u.ac.jp/file/seminar/2003/2003-Semi1-Naoki_Kato.pdf

## Preparation Address List
- https://ja.wikipedia.org/wiki/IPv4

### MTU


### IP Packet Processing Diagram
See
- http://www.erg.abdn.ac.uk/users/gorry/course/inet-pages/ip-processing.html


### Operation of a Router
See
- http://www.erg.abdn.ac.uk/users/gorry/course/inet-pages/router-opn.html

# MEMO
- What are SRE and SLE?
  - https://ask.wireshark.org/questions/1389/what-are-sre-and-sle
- TCP Selective Acknowledgment Options
  - https://tools.ietf.org/html/rfc2018

# Diagrams 
- https://en.wikipedia.org/wiki/Transmission_Control_Protocol
- http://www.medianet.kent.edu/techreports/TR2005-07-22-tcp-EFSM.pdf
