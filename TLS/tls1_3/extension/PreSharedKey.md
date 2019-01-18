# 概要
TLS1.3ではSessionIDとSessionTicket拡張は廃止され、PSK(Pre-Shared Key)と呼ばれる仕組みが利用されるようになります。
TLS1.2ではWEPのように双方で事前に秘密鍵を保持する仕組みとしてPSKを定義していましたが、これもTLS1.3のPSKに含まれます。

psk_key_exchange_modes拡張にて次の２つがPSKモードとして規定されている(PSKExchangeKeyMode.mdを参照のこと)
- psk_ke: 事前に双方に登録しておいた秘密鍵を使って通信を行う。鍵が漏れると危殆化する。
- psk_dhe_ke: PSKとDHEの２つを使って秘密鍵を導出して通信を行う。この場合にはPFSとなる

なお、pre_shared_key拡張が付与される場合には、必ずpsk_key_exchange_modes拡張が付与されてきます。
TLS接続を初めて行う場合は、pre_shared_key拡張は送付されません。

# 詳細

### 仕様

概要ではpsk_key_exchange_modes拡張のモード(psk_ke, psk_dhe_ke)によって、pre_shared_key拡張は大きく影響するのでそれぞれについて説明する。

お互いに双方に登録しておいた秘密鍵のみを使ってTLS通信する場合(psk_ke)
- 1. あらかじめサーバ・クライアント双方に秘密鍵を設定しておく
- 2. ClientHelloにpsk_key_exchange_modesにpsk_keyを指定、pre_shared_keyで設定しておいたPSKを指定する。
- 3. サーバ側にて受信したpre_shared_keyを受け付ける場合には、サーバで応答するServerHello中にpre_shared_key拡張を含まなければならない。

前回のTLS接続にてNewSessionTicketを発行してもらっている場合(psk_dhe_ke)
- 1. 前回の接続にてNewSessionTicketを発行を受け取る。これをPSKとして保存しておく。
- 2. ClientHelloにpsk_key_exchange_modesにpsk_dhe_keを指定、pre_shared_keyで保存しておいたPSKを指定、key_shareにはDHEの公開鍵を指定する。
- 3. サーバ側にて受信したpre_shared_keyを受け付ける場合には、サーバで応答するServerHello中にpre_shared_key拡張を含まなければならない。

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
  - IdentityにはPSKの値が入ります。
  - Obfuscated Ticket Ageは実は曖昧な時刻として隠されている。
  - PSK Bindersというのは、セッションハッシュが指定されています。この値によって、前回接続を行ったものとPSKとの紐付けを行います。
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
  - ClientHelloから受けったpre_shared_keyを受け付ける場合には、ServerHelloにpre_shared_key拡張を含めます。
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
