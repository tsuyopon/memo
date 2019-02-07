# 概要
TLS1.3から存在するsupported_group拡張は、実はTLS1.2以前ではelliptic_curves拡張として存在していました。
このような名前になったのはTLS1.2以前ではElliptic Curve Groupsのみ対応していましたが、Finite Field Groupが追加されました。
- Elliptic Curve Groups (ECDHE)
- Finite Field Groups (DHE)

TLS1.2ではelliptic_curvesはec_point_formatsとセットで曲線のグループとフォーマットを決定していました。
しかし、TLS1.3ではec_point_formatsは廃止され、supported_groupsで表されたそれぞれの曲線に対して1つのフォーマットが固定で決まってくることになります。
- (参考) https://tools.ietf.org/html/rfc8446#section-4.2.7

# 詳細

### 解決したい課題
TLS1.2ではelliptic_curvesとec_point_formatsを指定することで曲線とその書記を指定していました。

冒頭でのべたようにTLS1.3ではElliptic Curve Groupsの他にも、Finite Field Groupsがサポートされるようになりましたので拡張名がelliptic_curvesなのは適切ではなくなりました。
また、TLS1.2で存在していたec_point_formats拡張ではcompressedやuncompressedといった書式を指定していましたが、これも複雑にする元となっていました。

### 解決方法
- elliptic_curves拡張からsupported_group拡張に名称が変更され、Finite Field Groupsも含まれる様になりました。
- ec_point_formats拡張を廃止して、選択された曲線(x25519, secp256r1等)に応じてcompressedやuncompressedかは一意に決定する様になりました。

### 仕様
- 1. ClientHelloのsupproted_groupにて対応している曲線情報が指定されてきます。優先度順で指定されています。
  - supported_groupに入っているグループで1つ以上がKeyShare拡張として公開鍵も含めて送付されます。
- 2. サーバ側はsupported_group拡張とkey_share拡張を確認して、鍵グループを確認して公開鍵を生成します。この公開鍵はServerHelloのKeyShareとして応答します。

### データ構造
```
      enum {

          /* Elliptic Curve Groups (ECDHE) */
          secp256r1(0x0017), secp384r1(0x0018), secp521r1(0x0019),
          x25519(0x001D), x448(0x001E),

          /* Finite Field Groups (DHE) */
          ffdhe2048(0x0100), ffdhe3072(0x0101), ffdhe4096(0x0102),
          ffdhe6144(0x0103), ffdhe8192(0x0104),

          /* Reserved Code Points */
          ffdhe_private_use(0x01FC..0x01FF),
          ecdhe_private_use(0xFE00..0xFEFF),
          (0xFFFF)
      } NamedGroup;

      struct {
          NamedGroup named_group_list<2..2^16-1>;
      } NamedGroupList;
```

### データサンプル
- ClientHello
  - supported_gropusに対応している全ての曲線情報を表示します。なお、supported_gropusでのグループがkey_shareの公開鍵に1つ以上指定されないとなりません。(合わせてデータサンプルを記載しておきます)
```
Extension: supported_groups (len=10)
    Type: supported_groups (10)
    Length: 10
    Supported Groups List Length: 8
    Supported Groups (4 groups)
        Supported Group: Reserved (GREASE) (0xfafa)
        Supported Group: x25519 (0x001d)
        Supported Group: secp256r1 (0x0017)
        Supported Group: secp384r1 (0x0018)
Extension: key_share (len=43)
    Type: key_share (51)
    Length: 43
    Key Share extension
        Client Key Share Length: 41
        Key Share Entry: Group: Reserved (GREASE), Key Exchange length: 1
            Group: Reserved (GREASE) (64250)
            Key Exchange Length: 1
            Key Exchange: 00
        Key Share Entry: Group: x25519, Key Exchange length: 32
            Group: x25519 (29)
            Key Exchange Length: 32
            Key Exchange: 32ca2b0d8c366bdec7fc50aabb39fc1474c5c43e9d4e14e3...
```

# 参考URL
- 4.2.7.  Supported Groups
  - https://tools.ietf.org/html/rfc8446#section-4.2.7
