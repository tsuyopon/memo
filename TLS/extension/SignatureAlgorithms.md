# 概要
TLS拡張としてRFC5246に唯一定義されています。TLS1.2から加わった仕様であり、それ以前ではこのパラメータが付与されても無視されます。
- https://tools.ietf.org/html/rfc5246#section-7.4.1.4.1

このTLS拡張はデジタル署名においてどの署名/ハッシュアルゴリズムのペアを証明書検証として使用するかということをサーバ側に指示するために利用します。
この拡張はServerCertificate, ServerKeyExchange, ClientKeyExchange, ClientVerifyに影響します。

# 概要

### Signature Algorithmsの構造体について

次のように構造体が定義されています。
```
enum {
    none(0), md5(1), sha1(2), sha224(3), sha256(4), sha384(5),
    sha512(6), (255)
} HashAlgorithm;

enum { anonymous(0), rsa(1), dsa(2), ecdsa(3), (255) }
  SignatureAlgorithm;

struct {
      HashAlgorithm hash;
      SignatureAlgorithm signature;
} SignatureAndHashAlgorithm;
```

たとえば、TLS_RSA_WITH_AES_128_GCM_SHA256 といったcipherが選択される場合にはサーバから送付されてくるサーバ証明書や鍵交換でRSAを利用するということはわかりますが、どのハッシュ関数を利用するかまではわかりません。

RFC5246にはクライアントがsignature_algorithms拡張を送ってこない場合には、どのハッシュ関数が指定されたのかのデフォルト値を規定しています。もし、このルールに合致しないハッシュ関数を利用したい場合にはSignature Algorithms拡張を送付する必要があります。
- 鍵交換アルゴリズムが (RSA, DHE_RSA, DH_RSA, RSA_PSK, ECDH_RSA, ECDHE_RSA)のいずれかならば、クライアントが{sha1,rsa}を送ってきたものとして振舞う
- 鍵交換アルゴリズムが (DHE_DSS, DH_DSS)のいずれかならば、クライアントが{sha1,dsa}を送ってきたものとして振舞う
- 鍵交換アルゴリズムが (ECDH_ECDSA, ECDHE_ECDSA)のいずれかならば、クライアントが{sha1,ecdsa}を送ってきたものとして振舞う

上記はTLS1.1からの変更点です。TLS1.1では上記の明示的なルールはありませんでした。
TLSサーバはこの拡張を送信してはならない。TLSサーバはこの拡張は受信時に必ずサポートしなければなりません。

セッションリザンプションとして振舞う際には、この拡張はServer Hello中には含まれていません。もし存在していたとしても、サーバはこの拡張を無視します。

### 証明書出し分けについて

たとえば、Apacheの場合だと次のようにRSAとECCで署名された鍵をディレクティブとして記述するだけでRSAとECCで出し分けができるようになります。
```
SSLCertificateFile    /path/to/rsa.crt
SSLCertificateKeyFile /path/to/rsa.key
SSLCertificateFile    /path/to/ecc.crt
SSLCertificateKeyFile /path/to/ecc.key
```

また、新しめのopensslではs_clientでSignature Algorithms extensionextension を指定することができます。
これを使用して、証明書出し分けられている事を確認することが可能です。
```
// RSA証明書を表示するために「RSA+SHA256」をClientHelloに含める
$ openssl s_client  -connect localhost:443 -sigalgs RSA+SHA256

// ECC証明書を表示させるために「ECDSA+SHA256」をClientHelloに含める
$ openssl s_client  -connect localhost:443 -sigalgs ECDSA+SHA256 

// 複数指定することも可能です。
$ openssl s_client  -connect localhost:443 -sigalgs RSA+SHA256:ECDSA+SHA256

```

### SHA-1証明書の危殆化について
GoogleやMicrosoftが将来的にはSHA-1を使用した署名の証明書を安全でないものとして扱う旨のアナウンスを表明しています。
- Google Security Blog: Gradually sunsetting SHA-1
  - https://security.googleblog.com/2014/09/gradually-sunsetting-sha-1.html
- SHA1 Deprecation Policy
  - https://blogs.technet.microsoft.com/pki/2015/10/19/sha1-deprecation-policy/

このアナウンスを受けて認証局はSHA-2への移行を勧めている。
しかし、SHA-2を利用するためにはTLS1.2以上でSignature Algorithm拡張を扱うことができるクライアントである必要があります。

### データ構造サンプル
- ClientHelloに添付されるサンプル
```
Extension: signature_algorithms
    Type: signature_algorithms (0x000d)
    Length: 20
    Signature Hash Algorithms Length: 18
    Signature Hash Algorithms (9 algorithms)
        Signature Hash Algorithm: 0x0403
            Signature Hash Algorithm Hash: SHA256 (4)
            Signature Hash Algorithm Signature: ECDSA (3)
        Signature Hash Algorithm: 0x0804
            Signature Hash Algorithm Hash: Unknown (8)
            Signature Hash Algorithm Signature: Unknown (4)
        Signature Hash Algorithm: 0x0401
            Signature Hash Algorithm Hash: SHA256 (4)
            Signature Hash Algorithm Signature: RSA (1)
        Signature Hash Algorithm: 0x0503
            Signature Hash Algorithm Hash: SHA384 (5)
            Signature Hash Algorithm Signature: ECDSA (3)
        Signature Hash Algorithm: 0x0805
            Signature Hash Algorithm Hash: Unknown (8)
            Signature Hash Algorithm Signature: Unknown (5)
        Signature Hash Algorithm: 0x0501
            Signature Hash Algorithm Hash: SHA384 (5)
            Signature Hash Algorithm Signature: RSA (1)
        Signature Hash Algorithm: 0x0806
            Signature Hash Algorithm Hash: Unknown (8)
            Signature Hash Algorithm Signature: Unknown (6)
        Signature Hash Algorithm: 0x0601
            Signature Hash Algorithm Hash: SHA512 (6)
            Signature Hash Algorithm Signature: RSA (1)
        Signature Hash Algorithm: 0x0201
            Signature Hash Algorithm Hash: SHA1 (2)
            Signature Hash Algorithm Signature: RSA (1)
```

### TLS1.3データ構造サンプル(Chrome Canary: TLS1.3 draft18で取得したもの)
- TLS1.3のClientHello中のCipher Suites
```
Cipher Suites (17 suites)
    Cipher Suite: Reserved (GREASE) (0x5a5a)
    Cipher Suite: TLS_AES_128_GCM_SHA256 (0x1301)
    Cipher Suite: TLS_AES_256_GCM_SHA384 (0x1302)
    Cipher Suite: TLS_CHACHA20_POLY1305_SHA256 (0x1303)
    Cipher Suite: TLS_ECDHE_ECDSA_WITH_AES_128_GCM_SHA256 (0xc02b)
    Cipher Suite: TLS_ECDHE_RSA_WITH_AES_128_GCM_SHA256 (0xc02f)
    Cipher Suite: TLS_ECDHE_ECDSA_WITH_AES_256_GCM_SHA384 (0xc02c)
    Cipher Suite: TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384 (0xc030)
    Cipher Suite: TLS_ECDHE_ECDSA_WITH_CHACHA20_POLY1305_SHA256 (0xcca9)
    Cipher Suite: TLS_ECDHE_RSA_WITH_CHACHA20_POLY1305_SHA256 (0xcca8)
    Cipher Suite: TLS_ECDHE_RSA_WITH_AES_128_CBC_SHA (0xc013)
    Cipher Suite: TLS_ECDHE_RSA_WITH_AES_256_CBC_SHA (0xc014)
    Cipher Suite: TLS_RSA_WITH_AES_128_GCM_SHA256 (0x009c)
    Cipher Suite: TLS_RSA_WITH_AES_256_GCM_SHA384 (0x009d)
    Cipher Suite: TLS_RSA_WITH_AES_128_CBC_SHA (0x002f)
    Cipher Suite: TLS_RSA_WITH_AES_256_CBC_SHA (0x0035)
    Cipher Suite: TLS_RSA_WITH_3DES_EDE_CBC_SHA (0x000a)
```

- TLS1.3のClientHello (chrome canary draft18)
```
Extension: signature_algorithms (len=20)
    Type: signature_algorithms (13)
    Length: 20
    Signature Hash Algorithms Length: 18
    Signature Hash Algorithms (9 algorithms)
        Signature Algorithm: ecdsa_secp256r1_sha256 (0x0403)
            Signature Hash Algorithm Hash: SHA256 (4)
            Signature Hash Algorithm Signature: ECDSA (3)
        Signature Algorithm: rsa_pss_rsae_sha256 (0x0804)
            Signature Hash Algorithm Hash: Unknown (8)
            Signature Hash Algorithm Signature: Unknown (4)
        Signature Algorithm: rsa_pkcs1_sha256 (0x0401)
            Signature Hash Algorithm Hash: SHA256 (4)
            Signature Hash Algorithm Signature: RSA (1)
        Signature Algorithm: ecdsa_secp384r1_sha384 (0x0503)
            Signature Hash Algorithm Hash: SHA384 (5)
            Signature Hash Algorithm Signature: ECDSA (3)
        Signature Algorithm: rsa_pss_rsae_sha384 (0x0805)
            Signature Hash Algorithm Hash: Unknown (8)
            Signature Hash Algorithm Signature: Unknown (5)
        Signature Algorithm: rsa_pkcs1_sha384 (0x0501)
            Signature Hash Algorithm Hash: SHA384 (5)
            Signature Hash Algorithm Signature: RSA (1)
        Signature Algorithm: rsa_pss_rsae_sha512 (0x0806)
            Signature Hash Algorithm Hash: Unknown (8)
            Signature Hash Algorithm Signature: Unknown (6)
        Signature Algorithm: rsa_pkcs1_sha512 (0x0601)
            Signature Hash Algorithm Hash: SHA512 (6)
            Signature Hash Algorithm Signature: RSA (1)
        Signature Algorithm: rsa_pkcs1_sha1 (0x0201)
            Signature Hash Algorithm Hash: SHA1 (2)
            Signature Hash Algorithm Signature: RSA (1)
```

# SeeAlso
- RFC5246(secition 7.4.1.4.1)
  - https://tools.ietf.org/html/rfc5246#section-7.4.1.4.1
