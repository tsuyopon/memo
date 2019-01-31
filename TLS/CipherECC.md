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


# RFC8422の構成は次のようになっています。
- Section2: ECC鍵交換のOverview
- Section3: クライアント認証のためのECC認証の使用
- Section4: 特定の曲線やポイントフォーマット利用するためのネゴシエーションを行うためのTLS拡張
- Section5: ECCが基盤となるハンドシェイク、TLSメッセージ中のエンコーディング、いくつかのメッセージを処理するために必要となる様々なデータ構造
- Section6: ECCがベースとなるCipherSuitesを定義し、この仕様の中のすべての実装で推奨される小さなサブセットの識別
- Section8:
- Section9: IANA規定
- Appendix B: RFC4492とRFC8422の相違点

# RFC4492とRFC8422の相違点について
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



# 公式URL
- Elliptic Curve Cryptography (ECC) Cipher Suites for Transport Layer Security (TLS) Versions 1.2 and Earlier
  - https://tools.ietf.org/html/rfc8422
- Elliptic Curve Cryptography (ECC) Cipher Suites for Transport Layer Security (TLS)
  - RFC8422によってObsoleteされています。
  - https://tools.ietf.org/html/rfc4492
