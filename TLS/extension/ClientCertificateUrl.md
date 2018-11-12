# 概要
制約があるような環境下においてクライアント認証が行われる場合、
URLでクライアント証明書のパスを指定できる方が望ましい。
これによりクライアントは証明書を持っていたり、専用のメモリを使わないようにすることができる。
これを可能にするのがRFC6066で定義されるclient_certificate_url拡張です。

# 仕様
- 1. 制約されたクライアントはClientHelloにclient_certificate_url拡張を含めます。値は空となります。
- 2. サーバもclient_certificate_urlに対応していたら、ServerHelloにこの拡張を含めます。値は空となります。
- 3. クライアントはCertificateメッセージを次で指定するURL情報に置き換えます。

url_and_hash_listにはURLとハッシュを含みます。
```
num {
    individual_certs(0), pkipath(1), (255)
} CertChainType;

struct {
    CertChainType type;
    URLAndHash url_and_hash_list<1..2^16-1>;
} CertificateURL;

struct {
    opaque url<1..2^16-1>;
    unint8 padding;
    opaque SHA1Hash[20];
} URLAndHash;
```

# 参考URL
- Transport Layer Security (TLS) Extensions: Extension Definitions
  - https://tools.ietf.org/html/rfc6066
