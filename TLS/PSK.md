TLS1.2以下のPSKについての概略を記載しています。詳細は以下のRFCを参照のこと
- https://tools.ietf.org/html/rfc4279

# 概要
TLSは一般的に公開鍵証明書やKerberosを認証のために使っています。
このドキュメントではどのように共通鍵を使うかということについて述べています(これはpre-shared keyと呼ばれる)

なぜPSKを利用するかというのは、以下の2つの理由が存在する。
- cipher_suteに依存しているので、PSKを使うことで公開鍵操作の必要性を避けることができる。これは限られたCPUリソースの場合のパフォーマンス制約下の環境でTLSが使われる際に役に立ちます。
- PSKは鍵管理の観点から非常に便利である。例えば、閉じたような環境での使用など


```
      CipherSuite                        Key Exchange  Cipher       Hash

      TLS_PSK_WITH_RC4_128_SHA           PSK           RC4_128       SHA
      TLS_PSK_WITH_3DES_EDE_CBC_SHA      PSK           3DES_EDE_CBC  SHA
      TLS_PSK_WITH_AES_128_CBC_SHA       PSK           AES_128_CBC   SHA
      TLS_PSK_WITH_AES_256_CBC_SHA       PSK           AES_256_CBC   SHA
      TLS_DHE_PSK_WITH_RC4_128_SHA       DHE_PSK       RC4_128       SHA
      TLS_DHE_PSK_WITH_3DES_EDE_CBC_SHA  DHE_PSK       3DES_EDE_CBC  SHA
      TLS_DHE_PSK_WITH_AES_128_CBC_SHA   DHE_PSK       AES_128_CBC   SHA
      TLS_DHE_PSK_WITH_AES_256_CBC_SHA   DHE_PSK       AES_256_CBC   SHA
      TLS_RSA_PSK_WITH_RC4_128_SHA       RSA_PSK       RC4_128       SHA
      TLS_RSA_PSK_WITH_3DES_EDE_CBC_SHA  RSA_PSK       3DES_EDE_CBC  SHA
      TLS_RSA_PSK_WITH_AES_128_CBC_SHA   RSA_PSK       AES_128_CBC   SHA
      TLS_RSA_PSK_WITH_AES_256_CBC_SHA   RSA_PSK       AES_256_CBC   SHA
```


# PSKハンドシェイク全体像
もしサーバ側がPSKで接続したい場合には、PSKのcipherを選択します。
そして、選択したPSK cipher_suiteのためのサーバ側は適切なServerKeyExchangeメッセージを送付します。


もしサーバが認識できないPSK identityを受け取ったらunknown_psk_identityアラートを応答しても良い。もしくは、PSKを使っていると知られたくない場合にはdecrypt_errorを送付してもよい。

```

      Client                                               Server
      ------                                               ------

      ClientHello                  -------->
                                                      ServerHello
                                                    (Certificate)
                                               ServerKeyExchange*
                                             (CertificateRequest)
                                   <--------      ServerHelloDone
      (Certificate)
      ClientKeyExchange
      (CertificateVerify)
      ChangeCipherSpec
      Finished                     -------->
                                                 ChangeCipherSpec
                                   <--------             Finished
      Application Data             <------->     Application Data
```


# PSKアルゴリズムのServerKeyExchangeとClientKeyExchangeメッセージの変更点について

- PSK KeyExchange
```
      struct {
          select (KeyExchangeAlgorithm) {
              /* other cases for rsa, diffie_hellman, etc. */
              case psk:  /* NEW */
                  opaque psk_identity_hint<0..2^16-1>;
          };
      } ServerKeyExchange;

      struct {
          select (KeyExchangeAlgorithm) {
              /* other cases for rsa, diffie_hellman, etc. */
              case psk:   /* NEW */
                  opaque psk_identity<0..2^16-1>;
          } exchange_keys;
      } ClientKeyExchange;
```

- DHE_PSK
```
      struct {
          select (KeyExchangeAlgorithm) {
              /* other cases for rsa, diffie_hellman, etc. */
              case diffie_hellman_psk:  /* NEW */
                  opaque psk_identity_hint<0..2^16-1>;
                  ServerDHParams params;
          };
      } ServerKeyExchange;

      struct {
          select (KeyExchangeAlgorithm) {
              /* other cases for rsa, diffie_hellman, etc. */
              case diffie_hellman_psk:   /* NEW */
                  opaque psk_identity<0..2^16-1>;
                  ClientDiffieHellmanPublic public;
          } exchange_keys;
      } ClientKeyExchange;
```

- RSA_PSK
```
      struct {
          select (KeyExchangeAlgorithm) {
              /* other cases for rsa, diffie_hellman, etc. */
              case rsa_psk:  /* NEW */
                  opaque psk_identity_hint<0..2^16-1>;
          };
      } ServerKeyExchange;

      struct {
          select (KeyExchangeAlgorithm) {
              /* other cases for rsa, diffie_hellman, etc. */
              case rsa_psk:   /* NEW */
                  opaque psk_identity<0..2^16-1>;
                  EncryptedPreMasterSecret;
          } exchange_keys;
      } ClientKeyExchange;
```


