# 概要
KeyShare拡張はTLS1.3のRFC8446中で定義されていて、supported_group拡張中に記載したグループ情報とそれに紐づく公開鍵情報を送付します。
この拡張はClientHello及びServerHelloで送付されます。
- https://tools.ietf.org/html/rfc8446#section-4.2.8

TLS1.2までは次のメッセージでDHEが設定された場合に公開鍵情報を送付していました。
- ServerKeyExchange
- ClientKeyExchange 

TLS1.3では上記２つのメッセージはKeyShare拡張がその代替と置き換わることで廃止される。
冒頭にも述べた通りClientHello及びServerHelloのKeyShare拡張にて公開鍵の受け渡しを行います。

例えば、DHEの場合には、KeyShareの中に「K = g^x mod p」のKの公開鍵の値が含まれる。
クライアントで生成した公開鍵がClientHelloに、サーバで生成した公開鍵がServerHelloに含まれることになります。
pとgの値は有限群と呼びNamed Groupに含まれます。楕円曲線のパラメータはNamedCurveとして仕様上で決められている公開されている値です。

詳しくは以下を参考のこと
- https://qiita.com/sylph01/items/3bf7bc2d42da4e0efb37

ClientHelloで送付される公開鍵情報は1グループ送ろうが複数グループ送ろうといった仕様は決められていません。
そこで、もしClientHelloから指定されたkey_shareがサーバとして受け入れられないものであった場合には、HelloRetryRequestをサーバ側から送付して鍵グループの変更作業を行います。

# 詳細

### 仕様
- 1. ClientHelloのkey_share拡張には鍵グループとそれに紐づく公開鍵情報が送付されます。
  - pre_shared_key拡張にpsk_dhe_keが含まれています。
  - 鍵グループはsupported_group拡張に含まれるものでなければなりません。複数グループの公開鍵を送ることも可能です。
- 2. ClientHelloを受け取ったサーバ側はClientHelloのkey_share拡張から選択された鍵グループに応答する公開鍵情報を生成して、ServerHelloのkey_share拡張に含めて応答します。
  - もし、key_share拡張に存在する公開鍵情報が受け入れられない場合には、サーバ側はHelloRetryRequestをクライアント側に応答して鍵グループの変更を要求します。
- 3. 以降はKeySchedulingに応答してセッションのための鍵生成が行われて、暗号処理が行われます。


### データ書式
```
struct {
    NamedGroup group;
    opaque key_exchange<1..2^16-1>;
} KeyShareEntry;
```
- group: 交換される鍵のグループ
- key_exchange: 鍵交換情報。このフィールドの内容は特定のグループや特定の定義によって決定される。
  - Finite Field Diffie-Hellmanパラメータ: https://tools.ietf.org/html/rfc8446#section-4.2.8.1
  - Elliptic Curve Diffie-Hellmanパラメータ: https://tools.ietf.org/html/rfc8446#section-4.2.8.2
    - secp256r1, secp384r1, secp521r1の場合では次のような構造体にシリアライズされる
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
ClientHelloとその応答となるServerHlloのサンプル。同じ応答でのパケットだがClientHello, ServerHelloそれぞれKeyExchangeの値が公開鍵であるために異なる。
- ClientHello
  -KeyShare拡張は複数の
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
- https://tools.ietf.org/html/rfc8446#section-4.2.8
