# 概要
KeyShare拡張はTLS1.3のRFC中で定義されています。
- https://tools.ietf.org/html/draft-ietf-tls-tls13-26#section-4.2.8

例えば、DHEの場合には、KeyShareの中に「K = g^x mod p」のK値が含まれる。これはClientHello及びServerHello双方に含まれることになります。
pとgの値は有限群と呼びNamed Groupに含まれます。楕円曲線のパラメータはNamedCurveとして仕様上で決められている公開されている値です。

詳しくは以下を参考のこと
- https://qiita.com/sylph01/items/3bf7bc2d42da4e0efb37

# 詳細

### 仕様
クライアントはサーバからのグループ選択を要求するために追加のラウンドトリップを犠牲にしても、空のclient_sharesベクタ(データ書式参照)を送付してくるかもしれない(HelloRetryRequestを要求するために)。


### データ書式
```
struct {
    NamedGroup group;
    opaque key_exchange<1..2^16-1>;
} KeyShareEntry;
```
- group: 交換される鍵のグループ
- key_exchange: 鍵交換情報。このフィールドの内容は特定のグループや特定の定義によって決定される。
  - Finite Field Diffie-Hellmanパラメータ: https://tools.ietf.org/html/draft-ietf-tls-tls13-27#section-4.2.8.1
```

```
  - Elliptic Curve Diffie-Hellmanパラメータ: https://tools.ietf.org/html/draft-ietf-tls-tls13-27#section-4.2.8.2
```
      struct {
          uint8 legacy_form = 4;
          opaque X[coordinate_length];
          opaque Y[coordinate_length];
      } UncompressedPointRepresentation;
```

```
struct {
    KeyShareEntry client_shares<0..2^16-1>;
} KeyShareClientHello;
```

### データ構造サンプル(draft 23)
ClientHelloとその応答となるServerHlloのサンプル。同じ応答でのパケットだがClientHello, ServerHelloそれぞれKeyExchangeの値が異なる。
- ClientHello
```
Extension: key_share (len=43)
    Type: key_share (51)
    Length: 43
    Key Share extension
        Client Key Share Length: 41
        Key Share Entry: Group: Reserved (GREASE), Key Exchange length: 1
            Group: Reserved (GREASE) (35466)
            Key Exchange Length: 1
            Key Exchange: 00
        Key Share Entry: Group: x25519, Key Exchange length: 32
            Group: x25519 (29)
            Key Exchange Length: 32
            Key Exchange: 40b142e0e4c2863f2725a821b3f0fbbc3ba3e24b54b4b932...
```
- ServerHello
```
Extension: key_share (len=36)
    Type: key_share (51)
    Length: 36
    Key Share extension
        Key Share Entry: Group: x25519, Key Exchange length: 32
            Group: x25519 (29)
            Key Exchange Length: 32
            Key Exchange: 5f9a4d38c6470d7c9f66fb3943fd219d22a29e63d3c0ee95...
```


# SeeAlso
- https://tools.ietf.org/html/draft-ietf-tls-tls13-26#section-4.2.8
