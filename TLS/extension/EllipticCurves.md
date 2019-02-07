# 概要
TLS1.2以前ではelliptic_curvesとec_point_formatsの２つのエクステンションによってECDHEの鍵交換が決定されます。
elliptic_curves拡張は次の情報を表しています。
- クライアントがサポートする楕円曲線の種別を表しています
- ServerKeyExchangeのパケットにはこの拡張で選択されるた曲線情報とその曲線に応じた公開鍵情報を含みます。

TLS1.3ではelliptic_curvesはsupported_groupsという拡張に名称が変更されます。TLS1.3ではec_point_formatsは廃止され、supported_groupsのみで表された曲線に対して1つのフォーマットが固定で決定されます。
- (参考) https://tools.ietf.org/html/rfc8446#section-4.2.7

TLS1.3のsupported_groupsについては以下で説明していますので、ここではelliptic_curvesについて説明します。
- ../tls1_3/extension/SupportedGroups.md 

# 解決したい課題
公開鍵暗号方式の楕円曲線暗号をネゴシエーションをする際に、クライアントがどの楕円曲線をサポートしているのかをサーバ側に伝えたい。

# 解決方法
elliptic_curvesによってサーバ側にクライアントがサポートしている楕円曲線を伝えます。
なお、TLS1.3ではelliptic_curvesではなくsupported_groups拡張となり、ec_point_formatsは廃止されます。

# 詳細
- クライアントによってサポートされる楕円曲線(elliptic curves)のセットを示しています。 
- opaque型のextension_dataにはEllipticCurveListを含んでいます。

### elliptic_curves
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

### データ構造サンプル(ec_point_formatsも合わせて記載)

- ClientHelloサンプル
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
    - elliptic_curves
      - https://tools.ietf.org/html/rfc4492#section-5.1.1
- IANA:
  - TLS Supported Groups Registry
    - https://www.iana.org/assignments/tls-parameters/tls-parameters.xhtml#tls-parameters-8
  - TLS EC Curve Type Registry
    - https://www.iana.org/assignments/tls-parameters/tls-parameters.xhtml#tls-parameters-10
