# 概要
elliptic_curves(supported_groups)とec_point_formatsの２つのエクステンションによってECDHEの鍵交換が決定されます。RFC4492で規定されています。
ec_point_formats拡張はクライアントがパース可能な点のフォーマットを示します。

TLS1.3ではec_point_formats拡張は廃止されており、グループ中にec_point_formatsに関する情報も含まれています。


# 解決したい課題
クライアントがサーバ側にcompressed(X座標のみ)なECポイント形式をサポートしているかどうかを伝えるための拡張です。
なお、uncompressedは実装上はMUSTとなっています。

# 解決方法
elliptic_curves拡張と合わせて、ec_point_formats拡張を送付することでサポートする曲線(elliptic_curves)がどのECポイント形式をサポートしているかをサーバ側に伝えます。
この拡張によって、サーバ側はクライアントがcompressedに対応していることを知ることができます。uncompressed(X座標とY座標)は実装上として必須となっています。
なお、TLS1.3ではec_point_formatsは廃止されていて、曲線ごとにcompressedかuncompressedのいずれかがすでに決定しています。

一般的にはNIST Curve(secp256r, etc..)はuncompressedでX座標とY座標、IETFによるCurveはcompressedとなっています。

# 詳細

### データ書式
- クライアントがパースすることができるポイントフォーマットのセットを示します。 
- opaque型のextension_dataにはECPointFormatListを含んでいます。

```
enum { uncompressed (0), ansiX962_compressed_prime (1),
       ansiX962_compressed_char2 (2), reserved (248..255)
} ECPointFormat;
```

```
struct {
    ECPointFormat ec_point_format_list<1..2^8-1>
} ECPointFormatList;
```


- データ型については以下を参照のこと
  - https://tools.ietf.org/html/rfc4492#section-5.1.2

### データ構造サンプル

- ClientHelloサンプル(あわせてelliptic_curvesも記載しています)
```
Extension: ec_point_formats
    Type: ec_point_formats (0x000b)
    Length: 2
    EC point formats Length: 1
    Elliptic curves point formats (1)
        EC point format: uncompressed (0)
Extension: elliptic_curves
    Type: elliptic_curves (0x000a)
    Length: 10
    Elliptic Curves Length: 8
    Elliptic curves (4 curves)
        Elliptic curve: Unknown (0x5a5a)
        Elliptic curve: ecdh_x25519 (0x001d)
        Elliptic curve: secp256r1 (0x0017)
        Elliptic curve: secp384r1 (0x0018)
```
- ServerHello
```
Extension: ec_point_formats
    Type: ec_point_formats (0x000b)
    Length: 4
    EC point formats Length: 3
    Elliptic curves point formats (3)
        EC point format: uncompressed (0)
        EC point format: ansiX962_compressed_prime (1)
        EC point format: ansiX962_compressed_char2 (2)
```

# SeeAlso
- RFC4492: Elliptic Curve Cryptography (ECC) Cipher Suites for Transport Layer Security (TLS)
  - https://www.ietf.org/rfc/rfc4492.txt
    - ec_point_formats
      - https://tools.ietf.org/html/rfc4492#section-5.1.2
- IANA:
  - TLS EC Point Format Registry
    - https://www.iana.org/assignments/tls-parameters/tls-parameters.xhtml#tls-parameters-9
- StackExchange: What does the EC_POINT_FORMAT TLS extension protect against and what is the risk of not using it?
  - https://security.stackexchange.com/questions/165390/what-does-the-ec-point-format-tls-extension-protect-against-and-what-is-the-risk/165431
