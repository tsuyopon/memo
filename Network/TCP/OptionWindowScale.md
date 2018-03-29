# 概要
TCPv4ヘッダにはWindowと呼ばれる16bitのフィールドが存在します。
これによって2の16乗まで(64KByte)を表現することができますが、最近のホスト性能からするとこれだけでは不十分となっています。

ここでこのWindowフィールドを拡張するための仕組みとしてOptioフィールドにWindow Scaleという仕組みが導入されることになりました。

これを利用すると次のようにWindowフィールドの表現幅が広がります。
- たとえば、Window Scaleを1に指定した場合、ウィンドウFieldは2の17乗 = 128K Byteまで表現できる
- たとえば、Window Scaleを5に指定した場合、ウィンドウFieldは2の21乗 = 2M Byteまで表現できる

このオプションは、TCP 3wayハンドシェイクのsyn, syn/ackのタイミングで利用されます。
他と異なりネゴシエーションという訳ではなく、 お互いが別々の値を設定することができます。

# 詳細

### データ書式
```
   Length: 3 bytes

          +---------+---------+---------+
          | Kind=3  |Length=3 |shift.cnt|
          +---------+---------+---------+
               1         1         1
```

### サンプルデータ
```
        TCP Option - Window scale: 5 (multiply by 32)
            Kind: Window Scale (3)
            Length: 3
            Shift count: 5
            [Multiplier: 32]
```

# SeeAlso
- RFC7323: TCP Extensions for High Performance
  - https://tools.ietf.org/html/rfc7323#section-2

# TODO
- RFC7323を見る
