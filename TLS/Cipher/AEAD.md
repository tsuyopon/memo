# AEAD or AE
認証付き暗号(AE: Authentiated Encryption or AEAD: Authenticated Encryption with Associated Data)は、次の３つを同時に提供する暗号モードです。
- データの秘匿性
- 完全性
- 認証性

次の6種類の異なるモードが存在する。
- CCM
- GCM
- Encrypt Then MAC
- EAX
- Key Wrap
- OCB2.0

Ciphersuiteを表す文字列最後の要素SHA256, SHA384は、PRFのハッシュ関数をSHA256, SHA384に置き換えると以下で規定しています。
- https://tools.ietf.org/html/rfc5288#section-3

- TODO: CHACHA20-POLY1305は規定されていない?

# AEAD Algorthms
RFC5116では次の４つのAEADアルゴリズムが規定されています。
GCMもCCMもどちらも128bit
- AES GCM
  - 1. AEAD_AES_128_GCM
  - 2. AEAD_AES_256_GCM
- AES CCM
  - 3. AEAD_AES_128_CCM
  - 4. AEAD_AES_256_CCM

### 1. AEAD_AES_128_GCM

AEAD_AES_128_GCMはAEアルゴリズムはGCMが働き、ブロック暗号としてAES-128を利用される。
key, nonce, plaintext, associated dataの４つの情報を渡すことによって提供される。

認証タグは16オクテット(128bit)が利用される。
AEAD_AES_128_GCM のciphertextは、GCM暗号操作として生成された認証タグを付与することで形成されます。

以下にテストケースが提供されています。
- https://tools.ietf.org/html/rfc5116#ref-GCM

入力と出力の長さは次のようになります。
- K_LEN is 16 octets,
- P_MAX is 2^36 - 31 octets,
- A_MAX is 2^61 - 1 octets,
- N_MIN and N_MAX are both 12 octets, and
- C_MAX is 2^36 - 15 octets.

AEAD_AES_128_GCMのciphertextはきっちり16byte長である。

### 2. AEAD_AES_256_GCM
AEAD_AES_128_GCMとほとんど同じだが次の点で異なる。
- K_LEN is 32 octets, instead of 16 octets, and
- AES-256 GCM is used instead of AES-128 GCM.

### 3. AEAD_AES_128_CCM
AEAD_AES_128_GCMはAEアルゴリズムはCCMが働き、ブロック暗号としてAES-128を利用される。
key, nonce, associated data, plaintextを入力値として渡します。

認証タグとしては16オクテット長(128bit)が利用されます。
AEAD_AES_128_CCM  ciphertextはCCM暗号操作として生成された認証タグを付与することで形成されます。

以下にテストケースが提供されている。
- https://tools.ietf.org/html/rfc5116#ref-CCM

入力や出力の長さは次のとおりです。
- K_LEN is 16 octets,
- P_MAX is 2^24 - 1 octets,
- A_MAX is 2^64 - 1 octets,
- N_MIN and N_MAX are both 12 octets, and
- C_MAX is 2^24 + 15 octets.


### 4. AEAD_AES_256_CCM
AEAD_AES_128_CCMとほとんど同じだが次の点で異なる。
- K_LEN is 32 octets, instead of 16, and
- AES-256 CCM is used instead of AES-128 CCM.

# TLS1.2とTLS1.3の違い


- TLS1.2未満
  - 古いバージョンのTLSではクライアントはAEAD cipherは指定してはならず、またサーバ側もAEAD cipherを受け付けてはならない(MUST NOT)
  - クライアントはTLSバージョンをチェックして、不適切なバージョンであればillegal_parameterのfatalアラートを送らなければならない(MUST)
  - TLS1.2 (RFC5288より抜粋) のAEAD CipherSuite
```
CipherSuite TLS_RSA_WITH_AES_128_GCM_SHA256 = {0x00,0x9C}
CipherSuite TLS_RSA_WITH_AES_256_GCM_SHA384 = {0x00,0x9D}
CipherSuite TLS_DHE_RSA_WITH_AES_128_GCM_SHA256 = {0x00,0x9E}
CipherSuite TLS_DHE_RSA_WITH_AES_256_GCM_SHA384 = {0x00,0x9F}
CipherSuite TLS_DH_RSA_WITH_AES_128_GCM_SHA256 = {0x00,0xA0}
CipherSuite TLS_DH_RSA_WITH_AES_256_GCM_SHA384 = {0x00,0xA1}
CipherSuite TLS_DHE_DSS_WITH_AES_128_GCM_SHA256 = {0x00,0xA2}
CipherSuite TLS_DHE_DSS_WITH_AES_256_GCM_SHA384 = {0x00,0xA3}
CipherSuite TLS_DH_DSS_WITH_AES_128_GCM_SHA256 = {0x00,0xA4}
CipherSuite TLS_DH_DSS_WITH_AES_256_GCM_SHA384 = {0x00,0xA5}
CipherSuite TLS_DH_anon_WITH_AES_128_GCM_SHA256 = {0x00,0xA6}
CipherSuite TLS_DH_anon_WITH_AES_256_GCM_SHA384 = {0x00,0xA7}
```
  - CCMも追加する
- TLS1.3 (RFC8446より抜粋)
```
+------------------------------+-------------+
| Description                  | Value       |    TLS1.3での実装義務
+------------------------------+-------------+
| TLS_AES_128_GCM_SHA256       | {0x13,0x01} |    実装必須(MUST)
|                              |             |
| TLS_AES_256_GCM_SHA384       | {0x13,0x02} |    実装すべき(SHOULD)
|                              |             |
| TLS_CHACHA20_POLY1305_SHA256 | {0x13,0x03} |    実装すべき(SHOULD)
|                              |             |
| TLS_AES_128_CCM_SHA256       | {0x13,0x04} |
|                              |             |
| TLS_AES_128_CCM_8_SHA256     | {0x13,0x05} |
+------------------------------+-------------+
```

# 参考リンク
- あどけない話: TLS 1.3 開発日記 その17 AEAD
  - https://kazu-yamamoto.hatenablog.jp/entry/20170426/1493186127

# SeeAlso
- RFC5116: An Interface and Algorithms for Authenticated Encryption
  - https://tools.ietf.org/html/rfc5116
- RFC5288: AES Galois Counter Mode (GCM) Cipher Suites for TLS
  - https://tools.ietf.org/html/rfc5288
- NIST: Recommendation for Block Cipher Modes of Operation: Galois/Counter Mode (GCM) and GMAC
  - https://nvlpubs.nist.gov/nistpubs/Legacy/SP/nistspecialpublication800-38d.pdf

