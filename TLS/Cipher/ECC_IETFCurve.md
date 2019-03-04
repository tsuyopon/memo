# 概要
curve25519やcurve448はエドワード曲線で、curve25519は128bitのセキュリティレベルを、curve448は224bitのセキュリティレベルを提供します。
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

### 推奨パラメータ(curve25519)
- curve25519
  - https://tools.ietf.org/html/rfc7748#section-4.1

次の楕円曲線がcurve25519である
```
v^2 = u^3 + A*u^2 + u

A = 486662

ベースポイント
u = 9, v = 14781619447589544791020593568409986887264606134616475288964881837755586237401
```

mod pのpはcurve25519を表す意味
```
p = 2^255 - 19
```


### 推奨パラメータ(curve448)
- curve448
  - https://tools.ietf.org/html/rfc7748#section-4.2

```

A = 156326

ベースポイント
u = 5, v = 355293926785568175264127502063783334808976399387714271831880898435169088786967410002932673765864550910142774147268105838985595290606362
```


mod p のpからcurve448を表す意味が確認できます。
```
p  2^448 - 2^224 - 1
```

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

