# 概要
Multiple TCPとは、複数のインタフェースを用いることによってTCPコネクションを貼ることができるTCP拡張です。MPTCP自体はRFC6824で規定されています。
たとえば、スマートフォンの場合だと、LTEとWi-Fiといった２つのインタフェースを用いてコネクションを貼り、両方の経路を併用してデータ通信を行います。それにより利用者側からは１つのコネクションのように見せる仕組みです。
iOSに搭載されているSiriではこのMPTCPの仕組みを利用しています。

802.3adリンクアグリゲーション(Bonding)に対して、MPTCPは複数のインターフェイスに対して1つのTCPコネクションでバランスし、とても高いスループットを出すことができることで注目されています。

# 仕様
TCPオプションを用いてネゴシエーションを行う。MP_CAPABLEというオプションが使われる。

つまり、次のようなハンドシェイクとなり、これらが複数のインターフェースに対して行われるイメージでである。
- 1. 通信開始側がSYN+MP_CAPABLEを送信する
- 2. 相手側もMPTCPに対応している場合、SYN+ACK, MP_CAPABLEを送信することで相互にMPTCPで対応していることがわかる
- 3. 通信側が送るACKにもMP_CAPABLEが付与される

英語版wikipediaの「Multipath TCP」のページがわかりやすいシーケンシャル図を添付している
- https://en.wikipedia.org/wiki/Multipath_TCP#/media/File:MPTCP-session-en.png

# 対応状況
クライアントとサーバが双方で対応していれば使うことができます。
- iphone(iOS7以降)で利用可能
  - http://blog.multipath-tcp.org/blog/html/2017/07/05/mptcp_experiments_on_ios_11_beta.html
- Linux
  - 以下が1であれば有効らしい
```
$ sysctl net.mptcp.mptcp_enabled
```
  - 参考: https://www.multipath-tcp.org/
- Android(Galaxy S6, S6 edge, S7などのSamsung製スマホ)

# 仕様詳細

### MPTCPパケット構造
MPTCPはTCP拡張番号30として規定されています。
- https://www.iana.org/assignments/tcp-parameters/tcp-parameters.xhtml

RFC6824にも次の記載があります。
```
+------+--------+-----------------------+-----------+
| Kind | Length |        Meaning        | Reference |
+------+--------+-----------------------+-----------+
|  30  |    N   | Multipath TCP (MPTCP) |  RFC 6824 |
+------+--------+-----------------------+-----------+
        Table 1: TCP Option Kind Numbers
```

TCP拡張は最初の1バイトが種別、その次の1バイトが長さ、その後は種別ごとに異なることが多いです。
今回のMPTCPではその後に4bitのサブタイプ、サブタイプごとの可変長データでパケット構造が構成されています。
```
 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
+---------------+---------------+-------+-----------------------+
|     Kind      |    Length     |Subtype|                       |
+---------------+---------------+-------+                       |
|                     Subtype-specific data                     |
|                       (variable length)                       |
+---------------------------------------------------------------+
        Figure 3: MPTCP Option Format
```

上記で4bitのSubtypeに入る値は次のように規定されています。
```
+-------+--------------+----------------------------+---------------+
| Value |    Symbol    |            Name            |   Reference   |
+-------+--------------+----------------------------+---------------+
|  0x0  |  MP_CAPABLE  |      Multipath Capable     |  Section 3.1  |
|  0x1  |    MP_JOIN   |       Join Connection      |  Section 3.2  |
|  0x2  |      DSS     | Data Sequence Signal (Data |  Section 3.3  |
|       |              |    ACK and data sequence   |               |
|       |              |          mapping)          |               |
|  0x3  |   ADD_ADDR   |         Add Address        | Section 3.4.1 |
|  0x4  |  REMOVE_ADDR |       Remove Address       | Section 3.4.2 |
|  0x5  |    MP_PRIO   |   Change Subflow Priority  | Section 3.3.8 |
|  0x6  |    MP_FAIL   |          Fallback          |  Section 3.6  |
|  0x7  | MP_FASTCLOSE |         Fast Close         |  Section 3.5  |
+-------+--------------+----------------------------+---------------+
            Table 2: MPTCP Option Subtypes
```

### SubtypeがMP_CAPABLEの場合のパケット構造について
SubtypeがMP_CAPABLE(0x0)のときのMPTCP Option Formatは次のようなパケット構造になります。
```
                     1                   2                   3
 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
+---------------+---------------+-------+-------+---------------+
|     Kind      |    Length     |Subtype|Version|A|B|C|D|E|F|G|H|
+---------------+---------------+-------+-------+---------------+
|                   Option Sender's Key (64 bits)               |
|                                                               |
|                                                               |
+---------------------------------------------------------------+
|                  Option Receiver's Key (64 bits)              |
|                     (if option Length == 20)                  |
|                                                               |
+---------------------------------------------------------------+
        Figure 4: Multipath Capable (MP_CAPABLE) Option
```

# 問題点
- 複数経路があるとロードバランサによりIPが異なると判定されて別々のオリジンに飛ばされないか?

# 参考URL
- RFC6824:TCP Extensions for Multipath Operation with Multiple Addresses
  - https://tools.ietf.org/html/rfc6824
- Linux KenerlのMPTCP実装
  - https://github.com/multipath-tcp/mptcp
- MultiPath TCP - Linux Kernel implementation
  - http://multipath-tcp.org/
- PDFスライドでわかりやすい
  - http://ew2017.european-wireless.org/wp-uploads/2017/05/keynotes-Raiciu-EW2017.pdf
