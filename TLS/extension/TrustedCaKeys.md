# 概要
制約(メモリ制約、少数のCA Root鍵歯科持っていない)されたTLSクライアントでは、どのCA Rootに関する情報を持っているかということをサーバに示すために、trusted_ca_keys拡張が使われます。
これを受け取ったサーバはこの拡張に沿ってCA Rootを応答します。

# 仕様
処理の流れは次の通りです。
- 制約された環境下でのクライアントはClientHello中にtrusted_ca_keys拡張を含めます。
- サーバ側が拡張の情報に基づいて応答する場合trusted_ca_keysを含めて応答します。この時、拡張に指定される値は空になります。

ClientHello中に指定される拡張フィールドには次の値が入ります。
```
struct {
    TrustedAuthority trusted_authorities_list<0..2^16-1>;
} TrustedAuthorities;
```

上記はlist形式になっていて次のようなデータを保持します。
```
struct {
    IdentifierType identifier_type;
    select (identifier_type) {
        case pre_agreed: struct {};
        case key_sha1_hash: SHA1Hash;
        case x509_name: DistinguishedName;
        case cert_sha1_hash: SHA1Hash;
    } identifier;
} TrustedAuthority;

enum {
    pre_agreed(0), key_sha1_hash(1), x509_name(2),
    cert_sha1_hash(3), (255)
} IdentifierType;

opaque DistinguishedName<1..2^16-1>;
```

TrustedAuthoritiesはクライアントが所有するCA Root鍵を提供します。

identifier_typeに指定される値は次の通りです。
- pre_agreed: CA Root鍵の識別子は与えられない
- key_sha1_hash: CA Root KeyのSHA-1ハッシュを含む
- x509_name: CAのDER形式でエンコードされたX.509 DistinguishedNameを含む
- cert_sha1_hash: CA Root Keyを含むDERエンコードされた証明書のSHA-1ハッシュ値を含む

# 参考URL
- Transport Layer Security (TLS) Extensions: Extension Definitions
  - https://tools.ietf.org/html/rfc6066
