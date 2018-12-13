# 概要
TLS1.3ではSessionID + Ticketは廃止され、PSK(Pre-Shared Key)と呼ばれる仕組みが利用されるようになります。
PSKは共通鍵を交換するための仕組みであり、PFS(前方秘匿性)を提供します。


# 詳細

### データ書式
```
struct {
    opaque identity<1..2^16-1>;
    uint32 obfuscated_ticket_age;
} PskIdentity;

opaque PskBinderEntry<32..255>;

struct {
    PskIdentity identities<7..2^16-1>;
    PskBinderEntry binders<33..2^16-1>;
} OfferedPsks;

struct {
    select (Handshake.msg_type) {
        case client_hello: OfferedPsks;
        case server_hello: uint16 selected_identity;
    };
} PreSharedKeyExtension;
```

### サンプルデータ
- ClientHello
```
Extension: pre_shared_key (len=171)
    Type: pre_shared_key (41)
    Length: 171
    Pre-Shared Key extension
        Identities Length: 134
        PSK Identity (length: 128)
            Identity Length: 128
            Identity: 7e4d5c84009f1b189b613883991eaa6bc2f23633bae6cbdc...
            Obfuscated Ticket Age: 1766424038
        PSK Binders length: 33
        PSK Binders
```
- ServerHello
```
Extension: pre_shared_key (len=2)
    Type: pre_shared_key (41)
    Length: 2
    Pre-Shared Key extension
        Selected Identity: 0
```

# 参考URL
- TLS 1.3 開発日記 その6 Pre Shared
  - http://d.hatena.ne.jp/kazu-yamamoto/20161213/1481681466

# SeeAlso
- RFC4279: Pre-Shared Key Ciphersuites for Transport Layer Security (TLS)
  - https://tools.ietf.org/html/rfc4279
- RFC8446: The Transport Layer Security (TLS) Protocol Version 1.3
  - https://tools.ietf.org/html/rfc8446#section-2.2
  - https://tools.ietf.org/html/rfc8446#section-4.2.11

# TODO
- 上記のSeeAlso以外にもPSKで関連するRFCがいくつか存在しているので概要を確認したい
  - https://en.wikipedia.org/wiki/TLS-PSK
