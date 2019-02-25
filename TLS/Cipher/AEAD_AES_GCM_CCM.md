# 概要
AESについてまとめる
- RFC5116: An Interface and Algorithms for Authenticated Encryption
  - AEADについて
  - https://tools.ietf.org/html/rfc5116
- RFC5288: AES Galois Counter Mode (GCM) Cipher Suites for TLS
  - GCMについて
  - https://tools.ietf.org/html/rfc5288
- RFC6655: AES-CCM Cipher Suites for Transport Layer Security (TLS)
  - TLS1.2におけるCCMについて規定している
  - https://tools.ietf.org/html/rfc6655


# RFC5116(AEAD)


# RFC5288(AES-GCM)


# RFC6655(AES-CCM)
TLS1.2におけるAES-CCMについて規定しています。

### RSAベースのAES-CCM Ciphersuiteの定義
RFC5116でAEAD_AES_128_CCM、AEAD_AES_256_CCMの２つが定義されている。
```
CipherSuite TLS_RSA_WITH_AES_128_CCM       = {0xC0,0x9C}
CipherSuite TLS_RSA_WITH_AES_256_CCM       = {0xC0,0x9D)
CipherSuite TLS_DHE_RSA_WITH_AES_128_CCM   = {0xC0,0x9E}
CipherSuite TLS_DHE_RSA_WITH_AES_256_CCM   = {0xC0,0x9F}
CipherSuite TLS_RSA_WITH_AES_128_CCM_8     = {0xC0,0xA0}
CipherSuite TLS_RSA_WITH_AES_256_CCM_8     = {0xC0,0xA1)
CipherSuite TLS_DHE_RSA_WITH_AES_128_CCM_8 = {0xC0,0xA2}
CipherSuite TLS_DHE_RSA_WITH_AES_256_CCM_8 = {0xC0,0xA3}
```


saltはimplicitな部分でパケットとして送信されないclient_write_IVかserver_write_IVの4byteからなります。
nonce_explicitはGenericAEADCipher.nonce_explicitが利用されます。
```
struct {
      opaque salt[4];
      opaque nonce_explicit[8];
} CCMNonce;
```

CCMNonce.nonce_explicitには以下のRFC5246で規定されるGenericAEADCipher.nonce_explicitとして送付されてくる値を指定します。
- https://tools.ietf.org/html/rfc5246#section-6.2.3.3

### PSKベースのAES-CCM Ciphersuiteの定義
PSKベースのAES-CCMのCiphersuiteを次のように規定しています。
なお、PSKやDHE_PSKはRFC4279の鍵交換に準じます。
```
CipherSuite TLS_PSK_WITH_AES_128_CCM       = {0xC0,0xA4}
CipherSuite TLS_PSK_WITH_AES_256_CCM       = {0xC0,0xA5)
CipherSuite TLS_DHE_PSK_WITH_AES_128_CCM   = {0xC0,0xA6}
CipherSuite TLS_DHE_PSK_WITH_AES_256_CCM   = {0xC0,0xA7}
CipherSuite TLS_PSK_WITH_AES_128_CCM_8     = {0xC0,0xA8}
CipherSuite TLS_PSK_WITH_AES_256_CCM_8     = {0xC0,0xA9)
CipherSuite TLS_PSK_DHE_WITH_AES_128_CCM_8 = {0xC0,0xAA}
CipherSuite TLS_PSK_DHE_WITH_AES_256_CCM_8 = {0xC0,0xAB}
```

### AES-128-CCM with an 8-Octet Integrity Check Value (ICV)
The AEAD_AES_128_CCM_8認証アルゴリズムは、認証用に16オクテットのフルサイズから8オクテットを使用するという変更点を除いてはAEAD_AES_128_CCMと同様です。


### AES-256-CCM with a 8-Octet Integrity Check Value (ICV)
The AEAD_AES_256_CCM_8認証アルゴリズムは、認証用に16オクテットのフルサイズから8オクテットを使用するという変更点を除いてはAEAD_AES_256_CCMと同様です。

### その他規定事項
- AEADは1.2以上でサポートされているので、TLSバージョンは1.2でなければならない
- カウンタは再利用してはならない 



# Normative URL
- RFC5116: An Interface and Algorithms for Authenticated Encryption
  - AEADについて
  - https://tools.ietf.org/html/rfc5116
- RFC5288: AES Galois Counter Mode (GCM) Cipher Suites for TLS
  - GCMについて
  - https://tools.ietf.org/html/rfc5288
- RFC6655: AES-CCM Cipher Suites for Transport Layer Security (TLS)
  - TLS1.2におけるCCMについて規定している
  - https://tools.ietf.org/html/rfc6655
