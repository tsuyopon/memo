# 概要
TLSのcipherについて

# 詳細

### cipher suiteの種類を確認したい
IANAのレジストリを参照すること
- https://www.iana.org/assignments/tls-parameters/tls-parameters.xhtml#tls-parameters-4

### TLS_NULL_WITH_NULL_NULLというのはどのような意味か
3つNULLがあるがそれぞれの位置では次のような意味を持ちます。
- 1番目NULL: 鍵交換と認証はしない
- 2番目NULL: 共通鍵暗号はしない
- 3番目NULL: MACアルゴリズムはない

TLS_NULL_WITH_NULL_NULL が指定されている場合、これはそのチャネルで最初にハンドシェイクする間の TLS 接続の初期状態を表します。
TLS_NULL_WITH_NULL_NULLはTLSコネクションが可能かどうかをチェックし、ハンドシェイクをシミュレートするもの。

- SeeAlso
  - https://security.stackexchange.com/questions/135998/ssl-tls-ciphersuite-tls-null-with-null-null

### TLS_DHE_RSA_WITH_AES_256_CBC_SHA
```
DHE: 鍵交換
RSA: 証明書の署名アルゴリズム(認証)
AES_256_CBC: 共通鍵暗号方式(暗号モードと鍵長) chacha20とかは鍵長さない
SHA: MACに使うためのハッシュアルゴリズム
```

### TLSCompressionMethodで指定できるみたい
IANAを参考にすること
- https://www.iana.org/assignments/comp-meth-ids/comp-meth-ids.xhtml

実際にはNULL, DEFLATE, LZSの３つが存在します。

### cipher suiteでECDHEを指定したら
必ず次の２つの拡張を含めなければならない
- supported_groups
- ec_point_formats

### RSA暗号について
RSAの場合だと、サーバ側の方がクライアントよりもループしなければならない数が多いので負荷が高い (TODO:ちゃんと深追いしたい)

### 鍵交換と認証が一緒の場合
たとえば、鍵交換と認証がそれぞれRSAを利用するのであれば、
```
TLS_RSA_RSA_WITH_XXXX
```
ではなくて
```
TLS_RSA_WITH_XXXX
```
で良い

### セキュリティパラメータについて
RFC5246のAppendix A.6で規定されている。
- https://tools.ietf.org/html/rfc5246#appendix-A.6

```
   struct {
       ConnectionEnd          entity;
       PRFAlgorithm           prf_algorithm;
       BulkCipherAlgorithm    bulk_cipher_algorithm;
       CipherType             cipher_type;
       uint8                  enc_key_length;
       uint8                  block_length;
       uint8                  fixed_iv_length;
       uint8                  record_iv_length;
       MACAlgorithm           mac_algorithm;
       uint8                  mac_length;
       uint8                  mac_key_length;
       CompressionMethod      compression_algorithm;
       opaque                 master_secret[48];
       opaque                 client_random[32];
       opaque                 server_random[32];
   } SecurityParameters;
```

- entity
- prf_algorithm
  - PRFと判断するのはGCM、CCM、Poly1305の３つを呼ぶ。これを総称してAEADと呼ぶ
  - なお、1.3ではPRFがなくなってHKDFに変わるとのこと
- bulk_cipher_algorithm
  - 共通鍵暗号方式
- cipher_type
- enc_key_length
- block_length
  - ブロック長の場合には資料を見る必要があります
    - http://nvlpubs.nist.gov/nistpubs/FIPS/NIST.FIPS.197.pdf
- fixed_iv_length
  - 固定なのでネットワークを介して見ることができない
- record_iv_length
  - レコードレイヤーに含まれているものなのでネットワークを介して見ることができる。
- mac_algorithm
  - GCMのアルゴリズム中にMACアルゴリズムが包括されているので、この場合にはnullとなる。
  - mac_lengthと同様にhmac_sha1, hmac_sha256などによって変化してくる
- mac_length
  - mac_algorithmと同様にhmac_sha1, hmac_sha256などによって変化してくる
- mac_key_length
- compression_algorithm
  - TLS1.2的にはnullしか存在しない。
  - IANAを見るとDEFLATE, LZSなども存在している
  - ClientHelloの構造体中に含まれている。
- master_secret
- client_random
- server_random

