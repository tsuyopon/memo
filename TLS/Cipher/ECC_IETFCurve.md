# 概要
curve25519やcurve448はエドワード曲線
secp256r1、secp384r1、secp521r1などのNIST Curveと対比してIETF Curveなどとも呼ばれたりします。

楕円曲線は次のように定義され
- x25519
- x448

x25519とx448については以下のRFC7748で定義されています。
- https://tools.ietf.org/html/rfc7748

上記それぞれに対応するエドワード曲線デジタル署名アルゴリズム(EdDSA)は次のように定義されています。
- ed25519
- ed448

ed25519とed448についてはRFC8032で定義されています。
- https://tools.ietf.org/html/rfc8032 

ed25519とed448についてはEdDSAなので以下の資料の方で説明します。
- ECC_EdDSA.md

# 詳細
TBD

# パラメータ定義箇所
- openssl
  - https://github.com/openssl/openssl/blob/a7f182b726956eb376a80d4a3e22c9465cf5e579/crypto/ec/curve25519.c

# Normative URL
- RFC7748: Elliptic Curves for Security
  - https://tools.ietf.org/html/rfc7748

# Informative URL
- wikipedia
  - https://en.wikipedia.org/wiki/Curve25519
  - https://en.wikipedia.org/wiki/Curve448

