# Elliptic Curve Cryptography(ECC)
ECCは公開鍵暗号であり、特にモバイルやワイヤレスなどで利用されます。
RSAのような暗号と比較すると鍵のサイズは小さくなります。鍵が小さくなると電力、メモリ、バンド幅、計算コストなどを節約するので制約されたような環境でも利用できます。

```
 Symmetric  |   ECC   |  DH/DSA/RSA
------------+---------+-------------
     80     |   163   |     1024
    112     |   233   |     2048
    128     |   283   |     3072
    192     |   409   |     7680
    256     |   571   |    15360
```

ECCについてはRFC4492とRFC8422で定義されていますが、RFC4492はRFC8422でObsoletedされています。
RFC8422ではTLS1.2以前が対応していて、TLS1.3についてはここでは規定していません。


RFC8422では次のECCに基づいた鍵交換アルゴリズムについて説明しています。
- Ephemeral Elliptic Curve Diffie-Hellman鍵合意(ECDHE)
  - TLS premaster secretを確立するためのエフェメラルキーを用いたECDHE鍵合意スキーム
- Elliptic Curve Digital Signature Algorithm (ECDSA)
  - TLS通信相手の認証のためのECDSA署名
- Edwards-curve Digital Signature Algorithm (EdDSA)
  - TLS通信相手の認証のためのEdDSA署名

### RFC8422の構成は次のようになっています。
- Section2: ECC鍵交換のOverview
- Section3: クライアント認証のためのECC認証の使用
- Section4: 特定の曲線やポイントフォーマット利用するためのネゴシエーションを行うためのTLS拡張
- Section5: ECCが基盤となるハンドシェイク、TLSメッセージ中のエンコーディング、いくつかのメッセージを処理するために必要となる様々なデータ構造
- Section6: ECCがベースとなるCipherSuitesを定義し、この仕様の中のすべての実装で推奨される小さなサブセットの識別
- Section8: Security Consideration
- Section9: IANA規定
- Appendix B: RFC4492とRFC8422の相違点

### RFC4492とRFC8422の相違点について
RFC8422はRFC4492をObsoleteにしましたが、次の点で違いがあります。
これはRFC8422#Appendix Bに記載されているものです。

- EllipticCurveListをNamedCurveListへとリネームした
- TLS1.2について追加した
- ECDH鍵交換(ECDH_RSA,  ECDH_ECDSA)を除去した
- 次のcihpersuiteをdeprecatedとした
```
TLS_ECDH_ECDSA_WITH_NULL_SHA
TLS_ECDH_ECDSA_WITH_RC4_128_SHA
TLS_ECDH_ECDSA_WITH_3DES_EDE_CBC_SHA
TLS_ECDH_ECDSA_WITH_AES_128_CBC_SHA
TLS_ECDH_ECDSA_WITH_AES_256_CBC_SHA
TLS_ECDH_RSA_WITH_NULL_SHA
TLS_ECDH_RSA_WITH_RC4_128_SHA
TLS_ECDH_RSA_WITH_3DES_EDE_CBC_SHA
TLS_ECDH_RSA_WITH_AES_128_CBC_SHA
TLS_ECDH_RSA_WITH_AES_256_CBC_SHA
全RC4関連のciphersuite
```
- 未使用のcurveとuncompressedなポイントフォーマットを除いたすべてを削除した
- X25519とX448を追加した
- 明示的なcurveをdeprecatedとした
- 証明書中のsignature algorithm上の制約を削除した


# ECDSAとEdDSAの用語整理
ECDSAとEdDSAの違いを抑えておかないと混乱しますので予めちゃんと抑えておきます。
以下の資料を参考に整理
- https://kazu-yamamoto.hatenablog.jp/entry/20171114/1510635277

### ECDSA(Elliptic Curve Digital Signature Algorithm)
以下の３つがRFC中でNIST Curveという用語として定義されています。
- P256(secp256r1)
- P384(secp384r1)
- P521(secp521r1)

NIST Curveと定義されているセクション
- https://tools.ietf.org/html/rfc8422#section-5.1.1

NIST Curveについての参考資料は上記にリファレンスがありますが以下を参照します。
- http://www.secg.org/sec2-v2.pdf
- https://nvlpubs.nist.gov/nistpubs/FIPS/NIST.FIPS.186-4.pdf

ECDSAについてはソニーPlay Station3のソフトウェア署名に用いていたECDSA秘密鍵の解読に成功されてしまった事例がある。
これは本来乱数とすべき値を固定値としてしまったことによる実装ミスであり、アルゴリズムの脆弱性ではない。

### EdDSA(Edwards-curve Digital Signature Algorithm)
NISTが疑似乱数生成アルゴリズムにバックドアを仕込んでいたことが明るみになった。
これによってセキュリティの専門家がNISTを信用しなくなり、NISTのECDHEとECDSAに対する代替が必要とされるようになった。

DJBはCurve25519とCurve449を策定した。
この２つのcurveを使ってDHEを実現するつのが名前がXから始まる鍵交換である。
- Curve25519を利用したDHE: X25519
- Curve448を利用したDHE:   X448

上記実装については以下を参照のこと
- https://tools.ietf.org/html/rfc7748


ここでやっと登場するのが、上記の認証についてはDSAと異なる署名方式であるEdDSAを使うことになる。以下のRFCで定義されている。
- https://tools.ietf.org/html/rfc8032	

上記では次の２つが規定されている。
- Curve25519を利用して実現されるEdDSA:  Ed25519
- Curve448を利用して実現されるEdDSA:    Ed448


- 参考
  - https://ed25519.cr.yp.to/
    - 特徴、実装の紹介、論文へのリンクなど

# 詳細

### 鍵交換アルゴリズム ( https://tools.ietf.org/html/rfc8422#section-2 )
ECC基盤の鍵交換アルゴリズムについては次の3種類が存在しています。以下の３つはIANAのTLS_XXXX_WITH_YYYYで表されるXXXXの部分です。
３つはすべてpremaster secretの計算をEphemeral ECDH (ECDHE) を利用しますが、それぞれで認証メカニズムが異なります。
```
     +-------------+------------------------------------------------+
     | Algorithm   | Description                                    |
     +-------------+------------------------------------------------+
     | ECDHE_ECDSA | Ephemeral ECDH with ECDSA or EdDSA signatures. |
     | ECDHE_RSA   | Ephemeral ECDH with RSA signatures.            |
     | ECDH_anon   | Anonymous ephemeral ECDH, no signatures.       |
     +-------------+------------------------------------------------+
```

- ECDHE_ECDSA
  - サーバ証明書に"ECDSA-"か"EdDSA-"が可能な公開鍵を含めなければならない
  - サーバはServerKeyExchangeメッセージ中にエフェメラルなECDH公開鍵と対応したcurveの情報を含めて送付してきます。
    - これらのパラメータはサーバ証明書の中の公開鍵に対応した秘密鍵を使ってECDSAかEdDSAで署名されていなければなりません。
  - クライアントはEphemeralなECDH鍵として同一curve上のECDH鍵ペアを生成して、ClientKeyExchangeメッセージでその公開鍵を送付します。
- ECDHE_RSA
  - サーバ証明書中にRSA公開鍵を含めなければならないといった点を除いては、ECDHE_ECDSAと同じ鍵交換アルゴリズムです。
  - ServerKeyExchangeメッセージ中の署名は対応するRSA秘密鍵で計算しなければなりません。
- ECDH_anon
  - NOTE: Despite the name beginning with "ECDH_" (no E), the key used in ECDH_anon is ephemeral just like the key in ECDHE_RSA and ECDHE_ECDSA.  The naming follows the example of DH_anon, where the key is also ephemeral but the name does not reflect it.
  - サーバのCertificate、CertificateRequest、クライアントのCertificate、CertificateVerifyは送ってはいけません。
  - サーバはServerKeyExchangeメッセージ中にEphemeralな公開鍵や対応するcurve情報を送付しなければならない。しかし、これらのパラメータは署名されてはならない。
  - クライアント側も同一curveに対するECDH鍵ペアを生成して、ClientKeyExchangeメッセージで公開鍵を送付しなければならない。


### クライアント認証 ( https://tools.ietf.org/html/rfc8422#section-3 )
TBD


### ECCのためのTLS拡張 ( https://tools.ietf.org/html/rfc8422#section-4 )
TBD


### データ構造と計算 ( https://tools.ietf.org/html/rfc8422#section-5 )
TBD

# 公式URL
- RFC6090: Fundamental Elliptic Curve Cryptography Algorithms
  - https://tools.ietf.org/html/rfc6090
- RFC8422: Elliptic Curve Cryptography (ECC) Cipher Suites for Transport Layer Security (TLS) Versions 1.2 and Earlier
  - https://tools.ietf.org/html/rfc8422
- RFC4492: Elliptic Curve Cryptography (ECC) Cipher Suites for Transport Layer Security (TLS)
  - RFC8422によってObsoleteされています。
  - https://tools.ietf.org/html/rfc4492


# TODO
- RFC6090も確認しておくこと
