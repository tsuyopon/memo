# 概要
NIST Curveはsecp256r1などで表される曲線グループの情報でありNISTによって定義されたものです。

TLSとして特に抑えておくべきなのが以下の３つのRFCです。
- RFC4492: Elliptic Curve Cryptography (ECC) Cipher Suites for Transport Layer Security (TLS)
  - https://tools.ietf.org/html/rfc4492
- RFC8422: Elliptic Curve Cryptography (ECC) Cipher Suites for Transport Layer Security (TLS) Versions 1.2 and Earlier
  - このRFCは4492をobsoleteしています。
  - https://tools.ietf.org/html/rfc8422
- RFC8446: The Transport Layer Security (TLS) Protocol Version 1.3
  - https://tools.ietf.org/html/rfc8446

上記では次のcurveが規定されています。

RFC4492はRFC5246(TLS1.2)をUpdateするRFCです。
次のように25種類の様々なグループが規定されていました。
- https://tools.ietf.org/html/rfc4492#section-5.1.1

RFC8422ではTLS1.2以前では次のようにしていこうという提案です。RFC4492をObsolteにして、25種類あった曲線を3つに絞っています。
- secp256r1, secp384r1, secp521r1 及び IETF Curve(curve25519, curve448)

RFC8466ではTLS1.3に対する規定ですが。RFC8422と同じ様になっています。
- secp256r1, secp384r1, secp521r1 及び IETF Curve(curve25519, curve448)

SECG、ANSI X9.62、NISTで呼び名が異なります。以下に表があるのでそちらを参考にできます。
- https://tools.ietf.org/html/rfc8422#appendix-A

# 詳細


- SEC 2: Recommended Elliptic Curve Domain Parameters
  - http://www.secg.org/sec2-v2.pdf
    - 例えば、secp256r1であれば「2.4.2 Recommended Parameters secp256r1」にパラメータが記載されています。
    - 以下のopensslのソースコードと対比させると良い。G: compressedについてはx、G: uncompressedについては前半はxと同じなので省略されていて、後半はyとなっている。(opensslのコードにGの先頭の03や04がなぜ省略されているのかは不明)
      - https://github.com/openssl/openssl/blob/a7f182b726956eb376a80d4a3e22c9465cf5e579/crypto/ec/ecp_nistp256.c#L65-L90



# 楕円曲線パラメータが定義されている箇所
- SEC 2: Recommended Elliptic Curve Domain Parameters
  - http://www.secg.org/sec2-v2.pdf
- openssl
  - https://github.com/openssl/openssl/blob/a7f182b726956eb376a80d4a3e22c9465cf5e579/crypto/ec/ecp_nistp256.c#L65-L90
  - https://github.com/openssl/openssl/blob/a7f182b726956eb376a80d4a3e22c9465cf5e579/crypto/ec/ecp_nistp521.c#L62-L112

# Normative URL
- SEC 2: Recommended Elliptic Curve Domain Parameters
  - http://www.secg.org/sec2-v2.pdf

