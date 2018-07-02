# 概要
elliptic_curves(supported_groups)とec_point_formatsの２つのエクステンションによってECDHEの鍵交換が決定されます。
ECC証明書の場合にはこん２つのエクステンションが付与される(??: 要確認)

- elliptic_curves(supported_groups)
  - 試験するための曲線の種別を表す
  - クライアントがサポートする楕円曲線の種別を表しています
  - ServerKeyExchangeのパケットにはこの中で選択される値を含みます
- ec_point_formats
  - クライアントがパース可能な点のフォーマットを示す


楕円曲線についてはmath/ECC.mdを確認のこと

# 詳細

## 拡張データ構造
ExtensionTypeは次の番号を利用します。
```
enum { elliptic_curves(10), ec_point_formats(11) } ExtensionType;
```

上記２つのタイプそれぞれについて説明します。
### 1) elliptic_curves (Supported Elliptic Curves Extension):   
- クライアントによってサポートされる楕円曲線(elliptic curves)のセットを示しています。 
- opaque型のextension_dataにはEllipticCurveListを含んでいます。

```
struct {
     NamedCurve elliptic_curve_list<1..2^16-1>
} EllipticCurveList;
```

NamedCurveについては次に示すような値が入ります。
```
enum {
    sect163k1 (1), sect163r1 (2), sect163r2 (3),
    sect193r1 (4), sect193r2 (5), sect233k1 (6),
    sect233r1 (7), sect239k1 (8), sect283k1 (9),
    sect283r1 (10), sect409k1 (11), sect409r1 (12),
    sect571k1 (13), sect571r1 (14), secp160k1 (15),
    secp160r1 (16), secp160r2 (17), secp192k1 (18),
    secp192r1 (19), secp224k1 (20), secp224r1 (21),
    secp256k1 (22), secp256r1 (23), secp384r1 (24),
    secp521r1 (25),
    reserved (0xFE00..0xFEFF),
    arbitrary_explicit_prime_curves(0xFF01),
    arbitrary_explicit_char2_curves(0xFF02),
    (0xFFFF)
} NamedCurve;
```

- データ型については以下を参照のこと
  - https://tools.ietf.org/html/rfc4492#section-5.1.1

### 2) ec_point_formats (Supported Point Formats Extension):
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
- ClientHelloサンプル
```
Extension: ec_point_formats
    Type: ec_point_formats (0x000b)
    Length: 2
    EC point formats Length: 1
    Elliptic curves point formats (1)
        EC point format: uncompressed (0)
```
```
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

### データ構造サンプル(TLS1.3 draft18)
- ClientHelloサンプル(TLS1.3からはelliptic_curvesはsupported_groupsという名称に変更になりました)
```
Extension: supported_groups (len=10)
    Type: supported_groups (10)
    Length: 10
    Supported Groups List Length: 8
    Supported Groups (4 groups)
        Supported Group: Reserved (GREASE) (0x3a3a)
        Supported Group: x25519 (0x001d)
        Supported Group: secp256r1 (0x0017)
        Supported Group: secp384r1 (0x0018)
Extension: ec_point_formats (len=2)
    Type: ec_point_formats (11)
    Length: 2
    EC point formats Length: 1
    Elliptic curves point formats (1)
        EC point format: uncompressed (0)
```

# SeeAlso
- RFC4492: Elliptic Curve Cryptography (ECC) Cipher Suites for Transport Layer Security (TLS)
  - https://www.ietf.org/rfc/rfc4492.txt
    - elliptic_curves
      - https://tools.ietf.org/html/rfc4492#section-5.1.1
    - ec_point_formats
      - https://tools.ietf.org/html/rfc4492#section-5.1.2
- IANA:
  - TLS Supported Groups Registry
    - https://www.iana.org/assignments/tls-parameters/tls-parameters.xhtml#tls-parameters-8
  - TLS EC Point Format Registry
    - https://www.iana.org/assignments/tls-parameters/tls-parameters.xhtml#tls-parameters-9
  - TLS EC Curve Type Registry
    - https://www.iana.org/assignments/tls-parameters/tls-parameters.xhtml#tls-parameters-10
