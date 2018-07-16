# TCP Extensions for Multipath Operation with Multiple Addresses
RFC6824を更新するドラフト

# 問題点
- 1. Off path ADD_ADDRハイジャック攻撃というものがある
  - 解決すべきミディアムリスク
- 2. DoS攻撃
  - このプロトコル外で緩和することができる
- 3. 初期ハンドシェイクを盗み見ることができる
  - 今回の範疇外

このドラフトでは問題1について解決を行う

# 解決方法
- ADD_ADDRを再定義することでADD_ADDRハイジャック攻撃を防ぐ

# 仕様詳細

### フロー詳細(以下は、Network/TCP/MPTCP.mdより抜粋)
2台のmachine1とmachine2が存在していて、各々がI/Fを持っていて次のような略称を付与します。後で説明に使います。
```
[machine 1]
MA1 = First interface on machine 1
MA2 = Second Interface on machine 1

[machine 2]
MB1 = First interface on machine 2
MB2 = Second interface on machine 2
```

MPTCPによる3wayハンドシェイクは次の内容で行う。これでMPTCPを使うことが双方で合意できたことになる。(ここまでは先程と同じです)
- 1. Send SYN With MP_CAPABLE Flags        (MA1 -> MB1)
- 2. Reply SYN+ACK With MP_CAPABLE Flags   (MB1 -> MA1)
- 3. Reply ACK With MP_CAPABLE Flags       (MA1 -> MB1)

machine1からmachine2にMA2が存在することを通知しておく
- 4. Send SYN With ADD_ADDR(MA2) Flags **with HMAC**    (MA1 -> MB1)        // RFC6824との違い

必要になった時点でMB2から次のようにMP_JOINされる。
- 5. Send SYN With MP_JOIN Flags           (MB2 -> MA2)
- 6. Reply SYN+ACK With MP_JOIN With HMAC  (MA2 -> MB2)
- 7. Reply ACK With MP_JOIN With HMAC      (MB2 -> MA2)
- 8. Reply ACK                             (MA2 -> MB2)
```

### ADD_ADDRパケット構造
HMACが追加することでADD_ADDRの送信元が正しいことを検知することができるようになります。
```
                           1                   2                   3
       0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
      +---------------+---------------+-------+-------+---------------+
      |     Kind      |     Length    |Subtype|(rsv)|E|  Address ID   |
      +---------------+---------------+-------+-------+---------------+
      |          Address (IPv4 - 4 octets / IPv6 - 16 octets)         |
      +-------------------------------+-------------------------------+
      |   Port (2 octets, optional)   |                               |
      +-------------------------------+                               |
      |        Truncated HMAC (8 octets, if length > 10 octets)       |
      |                               +-------------------------------+
      |                               |
      +-------------------------------+

                 Figure 12: Add Address (ADD_ADDR) Option
```

# 詳細
- 公式資料
  - https://datatracker.ietf.org/doc/draft-ietf-mptcp-rfc6824bis/
- RFC6842との違い
  - https://tools.ietf.org/rfcdiff?url2=draft-ietf-mptcp-rfc6824bis-00.txt
