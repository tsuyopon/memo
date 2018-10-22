# 概要
Multiple TCPとは、複数のインタフェースを用いることによってTCPコネクションを貼ることができるTCP拡張です。MPTCP自体はRFC6824で規定されています。
たとえば、スマートフォンの場合だと、LTEとWi-Fiといった２つのインタフェースを用いてコネクションを貼り、両方の経路を併用してデータ通信を行います。それにより利用者側からは１つのコネクションのように見せる仕組みです。
iOSに搭載されているSiriではこのMPTCPの仕組みを利用しています。

802.3adリンクアグリゲーション(Bonding)に対して、MPTCPは複数のインターフェイスに対して1つのTCPコネクションでバランスし、とても高いスループットを出すことができることで注目されています。

MultiPathTCPの特徴・利点は次のとおりです。
- 複数のpathを利用することでスループットを増加させる
- 1つの経路が利用できなくなっても、他の経路を利用することができる。
- コネクションを終了することなく、IPアドレスの追加と削除が可能である。
- MPTCP自体はアプリケーション層とTCP層の間に位置します。
- 輻輳制御も独自で行っている
- インタフェースを識別できるようにsubflowと呼ばれる識別子を定義している

# 疑問点: なぜ複数のTCPコネクション接続じゃだめなのか?

次の問題点が生じる
- 現行のアプリケーションの書き換えが必要となる
- 通常のTCP利用よりもかなりアグレッシブになりうる
- アプリケーションがどれだけの量をどのパスに送らなければならないとった、洗練されたデータ転送が難しい

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

## 利用方法
2台のmachine1とmachine2が存在していて、各々がI/Fを持っていて次のような略称を付与します。後で説明に使います。
```
[machine 1]
MA1 = First interface on machine 1
MA2 = Second Interface on machine 1

[machine 2]
MB1 = First interface on machine 2
MB2 = Second interface on machine 2
```

### 基本的な利用フロー
MPTCPによる3wayハンドシェイクは次の内容で行う。これでMPTCPを使うことが双方で合意できたことになる。
- 1. Send SYN With MP_CAPABLE Flags         (MA1 -> MB1)
- 2. Reply SYN+ACK With MP_CAPABLE Flags    (MB1 -> MA1)
- 3. Reply ACK With MP_CAPABLE Flags        (MA1 -> MB1)

続いて、今度はmachine1とmachine2でSecond Interfaceが存在するのでこの経路を追加する。
- 4. Send SYN With MP_JOIN Flags            (MA2 -> MB2)
- 5. Reply SYN+ACK With MP_JOIN Flags       (MB2 -> MA2)
- 6. Reply ACK With MP_JOIN Flags With HMAC (MA2 -> MB2)
- 7. Reply ACK                              (MB2 -> MA2)


### 相手側に自身が持つ別のI/Fを伝えておく方法
MPTCPによる3wayハンドシェイクは次の内容で行う。これでMPTCPを使うことが双方で合意できたことになる。(ここまでは先程と同じです)
- 1. Send SYN With MP_CAPABLE Flags        (MA1 -> MB1)
- 2. Reply SYN+ACK With MP_CAPABLE Flags   (MB1 -> MA1)
- 3. Reply ACK With MP_CAPABLE Flags       (MA1 -> MB1)

machine1からmachine2にMA2が存在することを通知しておく
- 4. Send SYN With ADD_ADDR(MA2) Flags     (MA1 -> MB1)

必要になった時点でMB2から次のようにMP_JOINされる。
- 5. Send SYN With MP_JOIN Flags           (MB2 -> MA2)
- 6. Reply SYN+ACK With MP_JOIN With HMAC  (MA2 -> MB2)
- 7. Reply ACK With MP_JOIN With HMAC      (MB2 -> MA2)
- 8. Reply ACK                             (MA2 -> MB2)

終了前にADD_ADDRしたアドレスを削除します。この場合REMOVE_ADDRが使われますがここでは割愛します。

## MPTCPパケット構造
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

### SubtypeがMP_CAPABLEの場合のパケット構造
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

- See: https://tools.ietf.org/html/rfc6824#section-3.1

### SubtypeがMP_JOINの場合のパケット構造
```
                           1                   2                   3
       0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
      +---------------+---------------+-------+-----+-+---------------+
      |     Kind      |  Length = 12  |Subtype|     |B|   Address ID  |
      +---------------+---------------+-------+-----+-+---------------+
      |                   Receiver's Token (32 bits)                  |
      +---------------------------------------------------------------+
      |                Sender's Random Number (32 bits)               |
      +---------------------------------------------------------------+
```
- Bフラグ
  - このコネクションがバックアップ回線かどうかを指定する
- Address ID
  - ADD_ADDRで通知されたAddressIDである
- Token
  - コネクションを識別するために使われるトークン
- Random Number
  - シーケンスナンバーはリプレイ攻撃のために付与されている


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
- Multipath TCPの紹介と最近の動向(PDF)
  - https://www.isoc.jp/materials/20131220/20131220_mptcp.pdf
