# 概要
TLSのcipherについて

# 詳細

### TLSバージョンにおけるCipher対応状況について
- https://ja.wikipedia.org/wiki/Transport_Layer_Security#%E6%9A%97%E5%8F%B7%E3%82%B9%E3%82%A4%E3%83%BC%E3%83%88

### TLS_NULL_WITH_NULL_NULLというのはどのような意味か
3つNULLがあるがそれぞれの位置では次のような意味を持ちます。ただ、TLS_NULL_WITH_NULL_NULLというのは定義されているだけであり、実際に使用されることはありません。
- 1番目NULL: 鍵交換と認証はしない
- 2番目NULL: 共通鍵暗号はしない
- 3番目NULL: MACアルゴリズムはない

TLS_NULL_WITH_NULL_NULL が指定されている場合、これはそのチャネルで最初にハンドシェイクする間の TLS 接続の初期状態を表します。
TLS_NULL_WITH_NULL_NULLはTLSコネクションが可能かどうかをチェックし、ハンドシェイクをシミュレートするもの。

- SeeAlso
  - https://security.stackexchange.com/questions/135998/ssl-tls-ciphersuite-tls-null-with-null-null

### TLS_DHE_RSA_WITH_AES_256_CBC_SHA
上記はどのような意味を持っているのか?
```
DHE: 鍵交換
RSA: 証明書の署名アルゴリズム(認証)
AES_256_CBC: 共通鍵暗号方式(暗号モードと鍵長) chacha20とかは鍵長さない
SHA: MACに使うためのハッシュアルゴリズム
```

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

### TLSCompressionMethodとは　
IANAを参考にすること
- https://www.iana.org/assignments/comp-meth-ids/comp-meth-ids.xhtml

実際にはNULL, DEFLATE, LZSの３つが存在します。
しかし、TLSではCompressionが利用されることは実質存在しないのでNULLとなっているようです。

### opensslが対応しているcipher一覧について
次のコマンドでopensslが対応しているcipherを確認することができる。
```
$ openssl ciphers -v
DHE-RSA-AES256-SHA      SSLv3 Kx=DH       Au=RSA  Enc=AES(256)  Mac=SHA1
DHE-DSS-AES256-SHA      SSLv3 Kx=DH       Au=DSS  Enc=AES(256)  Mac=SHA1
AES256-SHA              SSLv3 Kx=RSA      Au=RSA  Enc=AES(256)  Mac=SHA1
EDH-RSA-DES-CBC3-SHA    SSLv3 Kx=DH       Au=RSA  Enc=3DES(168) Mac=SHA1
EDH-DSS-DES-CBC3-SHA    SSLv3 Kx=DH       Au=DSS  Enc=3DES(168) Mac=SHA1
DES-CBC3-SHA            SSLv3 Kx=RSA      Au=RSA  Enc=3DES(168) Mac=SHA1
DES-CBC3-MD5            SSLv2 Kx=RSA      Au=RSA  Enc=3DES(168) Mac=MD5 
DHE-RSA-AES128-SHA      SSLv3 Kx=DH       Au=RSA  Enc=AES(128)  Mac=SHA1
DHE-DSS-AES128-SHA      SSLv3 Kx=DH       Au=DSS  Enc=AES(128)  Mac=SHA1
AES128-SHA              SSLv3 Kx=RSA      Au=RSA  Enc=AES(128)  Mac=SHA1
DHE-RSA-SEED-SHA        SSLv3 Kx=DH       Au=RSA  Enc=SEED(128) Mac=SHA1
DHE-DSS-SEED-SHA        SSLv3 Kx=DH       Au=DSS  Enc=SEED(128) Mac=SHA1
SEED-SHA                SSLv3 Kx=RSA      Au=RSA  Enc=SEED(128) Mac=SHA1
RC2-CBC-MD5             SSLv2 Kx=RSA      Au=RSA  Enc=RC2(128)  Mac=MD5 
RC4-SHA                 SSLv3 Kx=RSA      Au=RSA  Enc=RC4(128)  Mac=SHA1
RC4-MD5                 SSLv3 Kx=RSA      Au=RSA  Enc=RC4(128)  Mac=MD5 
RC4-MD5                 SSLv2 Kx=RSA      Au=RSA  Enc=RC4(128)  Mac=MD5 
EDH-RSA-DES-CBC-SHA     SSLv3 Kx=DH       Au=RSA  Enc=DES(56)   Mac=SHA1
EDH-DSS-DES-CBC-SHA     SSLv3 Kx=DH       Au=DSS  Enc=DES(56)   Mac=SHA1
DES-CBC-SHA             SSLv3 Kx=RSA      Au=RSA  Enc=DES(56)   Mac=SHA1
DES-CBC-MD5             SSLv2 Kx=RSA      Au=RSA  Enc=DES(56)   Mac=MD5 
EXP-EDH-RSA-DES-CBC-SHA SSLv3 Kx=DH(512)  Au=RSA  Enc=DES(40)   Mac=SHA1 export
EXP-EDH-DSS-DES-CBC-SHA SSLv3 Kx=DH(512)  Au=DSS  Enc=DES(40)   Mac=SHA1 export
EXP-DES-CBC-SHA         SSLv3 Kx=RSA(512) Au=RSA  Enc=DES(40)   Mac=SHA1 export
EXP-RC2-CBC-MD5         SSLv3 Kx=RSA(512) Au=RSA  Enc=RC2(40)   Mac=MD5  export
EXP-RC2-CBC-MD5         SSLv2 Kx=RSA(512) Au=RSA  Enc=RC2(40)   Mac=MD5  export
EXP-RC4-MD5             SSLv3 Kx=RSA(512) Au=RSA  Enc=RC4(40)   Mac=MD5  export
EXP-RC4-MD5             SSLv2 Kx=RSA(512) Au=RSA  Enc=RC4(40)   Mac=MD5  export
```

上記出力結果からは次のようなことを確認することができます。
- SSLv2, SSLv3などはその暗号が対応しているバージョン
- Kx: Key Exchange (鍵交換アルゴリズム)
- Au: AUthorization (認証に使われる暗号化アルゴリズム)
- Enc: Encription (アプリケーション層の暗号化に使われるアルゴリズム)
- Mac: Message Authentication Code (メッセージ検証に利用されるハッシュアルゴリズム)

### cipher suiteの種類を確認したい
IANAのレジストリを参照すること
- https://www.iana.org/assignments/tls-parameters/tls-parameters.xhtml#tls-parameters-4

RFC5246でも規定されているので確認すること
- https://tools.ietf.org/html/rfc5246#appendix-C

### DH_DSS, DH_RSA, DH_anonの違いは何か
以下の鍵交換でDH_がprefixで始まるものとして上記３種類が存在するが何が違うのだろうか?
これ以外にも、DHE_DSS, DHE_RSAなど似たような違いがある。
- https://tools.ietf.org/html/rfc5246#appendix-C

KeyExchangeでは次のようにenumが定義されている。
```
enum { dhe_dss, dhe_rsa, dh_anon, rsa, dh_dss, dh_rsa
      /* 拡張される可能性がある。（例：ECDH について [TLSECC] 参照）*/
     } KeyExchangeAlgorithm;
```

KeyExchangeAlgorithmの種類によって構造体が変わってくる。dh_anonだとServerDHParamsのみだが、dhe_dss, dhe_rsaではその他にdigitally-signedな構造体が含まれている。
なお、dhe_dssとdhe_rsaの違いとしては、DHパラメータの署名にDSSを使うか、RSSを使うかの違いです。anonは署名なしということになります。
```
struct {
    select (KeyExchangeAlgorithm) {
        case dh_anon:
            ServerDHParams params;
        case dhe_dss:
        case dhe_rsa:
            ServerDHParams params;
            digitally-signed struct {
                opaque client_random[32];
                opaque server_random[32];
                ServerDHParams params;
            } signed_params;
        case rsa:
        case dh_dss:
        case dh_rsa:
            struct {} ;
           /* メッセージは、rsa、dh_dss について省略される。*/
        /* そして、dh_rsa は、拡張される可能性がある。（例：ECDH について [TLSECC] 参照） */
    };
} ServerKeyExchange;
```

ちなみにServerDHParamsには次のものが含まれています。
```
struct {
    opaque dh_p<1..2^16-1>;
    opaque dh_g<1..2^16-1>;
    opaque dh_Ys<1..2^16-1>;
} ServerDHParams;     /* Ephemeral DH parameters */
```

実は、RFC5246の7.4.2節と7.4.3節にその説明が存在しているようなので、こちらも合わせて参考にしたい。
- https://tools.ietf.org/html/rfc5246#section-7.4.2
- https://tools.ietf.org/html/rfc5246#section-7.4.3

### cipher suiteでECDHEを指定したら
必ず次の２つの拡張を含めなければならない
- supported_groups
- ec_point_formats

### DH, DHE, ECDH, ECDHEなどの違いについて
- DH(Diffie-Helman)
  - 公開値を元に送信者/受信者がそれぞれ生成した秘密値から同じ共通鍵を生成して、以後それを共通鍵暗号の鍵として利用します。
  - 公開鍵暗号の一種で、離散対数問題という問題を解くことが困難な性質を安全性の根拠にしています。DHの亜種がDHE, ECDH, ECDHEとなります。
- DHE(最後のEはEphemeral)
  - 一時的で短命な公開値をサーバー側で動的に生成してそれを利用する
- ECDH(Elliptic Curve)
  - オリジナルの DH について楕円曲線暗号を使うようにしたもの
- ECDHE(最後のEはEpemeral)
  - ECDHにおいて一時的で短命な公開鍵を使う場合(DHEとECDHを組み合わせたもの)


- SeeAlso
  - What key exchange mechanism should be used in TLS? (StackExchange)
    - https://security.stackexchange.com/questions/8343/what-key-exchange-mechanism-should-be-used-in-tls
  - 理解してるつもりの SSL/TLS でも、もっと理解したら面白かった話
    - http://tkengo.github.io/blog/2015/12/01/https-details/

### ECDHE_RSA, ECDHE_ECDSAなどの違いについて
次のような違いがあるようです。
- ECDHE_RSA:   DHE_RSA と同じですが、DH 鍵交換の部分に楕円曲線暗号が使われます。
- ECDHE_ECDSA: DHE_DSS と同じですが、DH 鍵交換と署名部分に楕円曲線暗号が使われます。

### セキュリティパラメータについて
RFC5246のAppendix A.6で規定されています。
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

上記構造体の各種値の意味は次の通りです。
- entity
  - serverかclientが入る
- prf_algorithm
  - PRFと判断するのはGCM(Galois/Counter Mode)、CCM(Counter with CBC-MAC)、Poly1305の３つの認証付き暗号を指す。これを総称してAEAD(認証付き暗号)と呼ぶ
  - なお、余談だが1.3ではPRFがなくなってHKDFに変わるとのこと
- bulk_cipher_algorithm
  - 共通鍵暗号方式が入ります。null、rc4、3des、aesなどが含まれます
- cipher_type
  - stream, block, aeadの３つが入ります。
  - RC4はストリーム暗号
  - 3DESとAESはブロック暗号
  - AES-GCM, CCM, Chacha20-Poly1305の３つはAEADです。
- enc_key_length
  - 共通鍵暗号アルゴリズムの長さ
  - 例えば、AESの場合には、~_WITH_AES_256_GCM_SHA256などとしてAES_のあとにある256がその長さを表す。他のはアルゴリズムによって決定されるのでAESだけ判断できるのは特別である。
  - 生成したkeyblockからこの長さで指定された部分だけclient_write_key、server_write_keyを取得する(RFC5246#6.3)
- block_length
  - ブロック長の場合には資料を見る必要があります
    - http://nvlpubs.nist.gov/nistpubs/FIPS/NIST.FIPS.197.pdf
- fixed_iv_length
  - 生成したkeyblockからこの長さで指定された部分だけclient_write_IVやserver_write_IVとする(RFC5246#6.3)
  - この値はネットワーク上を流れない
- record_iv_length
  - ブロック暗号(GenericBlockCipher)やAEAD暗号(GenericAEADCipher)の構造体中で表現されるIVやnonce_explicitの長さとして利用される。
  - この値はレコードレイヤーに含まれているものなのでネットワークを介して見ることができる。
- mac_algorithm
  - GCMのアルゴリズム中にMACアルゴリズムが包括されているので、この場合にはnullとなる。AEADの場合にはnullとなる。
  - mac_lengthと同様にhmac_sha1, hmac_sha256などによって変化してくる
- mac_length
  - mac_algorithmと同様にhmac_sha1, hmac_sha256などによって変化してくる
- mac_key_length
  - 生成されたkeyblockからclient_write_MAC_keyやserver_write_MAC_keyの長さを取得するために利用される(RFC5246#6.3)
- compression_algorithm
  - TLS1.2的にはnullしか存在しない。
  - IANAを見るとDEFLATE, LZSなども仕様上は存在している。
  - ClientHelloの構造体中に含まれている。
- master_secret
  - ServerRandom + ClientRandom + PremasterSecret + label("master secret")の4つの変数をPRFにかけることによって取得する
  - なお、上記で取得したmaster secretからkeyblockを作るのもServerRandom + ClientRandom + MasterSecret + label("key expansion")の４つの変数をPRFにかけて伸長して取得するので非常に似ているので注意すること
    - 余談だが、SSL3.0ではlabelが不要ので3つの変数となる
- client_random
  - クライアントが生成するランダム値。master_secret生成やkeyblock生成で利用される。
- server_random
  - サーバが生成するランダム値。master_secret生成やkeyblock生成で利用される。

# TODO
- RFC3268について(AES)
  - https://www.ietf.org/rfc/rfc3268.txt
- RFC4162
  - https://tools.ietf.org/html/rfc4162
- RSAの場合だと、サーバ側の方がクライアントよりもループしなければならない数が多いので負荷が高い (TODO:ちゃんと深追いしたい)
- Encrypt then MAC, Mac then Encryptなど
  - https://ja.wikipedia.org/wiki/%E8%AA%8D%E8%A8%BC%E4%BB%98%E3%81%8D%E6%9A%97%E5%8F%B7
- RFC7539: ChaCha20 and Poly1305 for IETF Protocols
  - https://tools.ietf.org/html/rfc7539
- RFC7905: ChaCha20-Poly1305 Cipher Suites for Transport Layer Security (TLS)
  - https://tools.ietf.org/html/rfc7905
- RFC5869: HMAC-based Extract-and-Expand Key Derivation Function (HKDF)
  - https://tools.ietf.org/html/rfc5869
