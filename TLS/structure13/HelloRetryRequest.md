### HelloRetryRequestサンプル
```
TLSv1.3 Record Layer: Handshake Protocol: Hello Retry Request
    Content Type: Handshake (22)
    Version: TLS 1.2 (0x0303)
    Length: 88
    Handshake Protocol: Hello Retry Request
        Handshake Type: Server Hello (2)
        Length: 84
        Version: TLS 1.2 (0x0303)
        Random: cf21ad74e59a6111be1d8c021e65b891c2a211167abb8c5e... (HelloRetryRequest magic)
        Session ID Length: 32
        Session ID: 6ed732a322914b575bfd7bc88dcca70daa638f5590a02f58...
        Cipher Suite: TLS_AES_256_GCM_SHA384 (0x1302)
        Compression Method: null (0)
        Extensions Length: 12
        Extension: supported_versions (len=2)
            Type: supported_versions (43)
            Length: 2
            Supported Version: TLS 1.3 (0x0304)
        Extension: key_share (len=2)
            Type: key_share (51)
            Length: 2
            Key Share extension
                Selected Group: secp256r1 (23)
```

HelloRetryRequestの後にはChange Cipher Specメッセージが送付されていた。一応、そのサンプルも添付しておく。
```
TLSv1.3 Record Layer: Change Cipher Spec Protocol: Change Cipher Spec
    Content Type: Change Cipher Spec (20)
    Version: TLS 1.2 (0x0303)
    Length: 1
    Change Cipher Spec Message
```

# 参考までに上記のHelloRetryRequestメッセージを送付する前後のClientHelloメッセージも以下に添付しておく
以下のサンプルでの前後の大きな違いとしては、次の２点です。
- Versionが1.2と1.0で違いがある。
- key_shareが前後でサポートされるグループがx25519からsecp256r1に変更になるので、内容が変更される。

### HelloRetryRequestを受け取る前のClientHello
```
TLSv1.3 Record Layer: Handshake Protocol: Client Hello
    Content Type: Handshake (22)
    Version: TLS 1.0 (0x0301)
    Length: 512
    Handshake Protocol: Client Hello
        Handshake Type: Client Hello (1)
        Length: 508
        Version: TLS 1.2 (0x0303)
        Random: fc238baf1eca92c3cf105dc78526bf546e0d313cc367e959...
        Session ID Length: 32
        Session ID: 6ed732a322914b575bfd7bc88dcca70daa638f5590a02f58...
        Cipher Suites Length: 34
        Cipher Suites (17 suites)
            Cipher Suite: Reserved (GREASE) (0x3a3a)
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
        Compression Methods Length: 1
        Compression Methods (1 method)
        Extensions Length: 401
        Extension: Reserved (GREASE) (len=0)
            Type: Reserved (GREASE) (35466)
            Length: 0
            Data: <MISSING>
        Extension: server_name (len=30)
            Type: server_name (0)
            Length: 30
            Server Name Indication extension
                Server Name list length: 28
                Server Name Type: host_name (0)
                Server Name length: 25
                Server Name: cdn.syndication.twimg.com
        Extension: extended_master_secret (len=0)
            Type: extended_master_secret (23)
            Length: 0
        Extension: renegotiation_info (len=1)
            Type: renegotiation_info (65281)
            Length: 1
            Renegotiation Info extension
                Renegotiation info extension length: 0
        Extension: supported_groups (len=10)
            Type: supported_groups (10)
            Length: 10
            Supported Groups List Length: 8
            Supported Groups (4 groups)
                Supported Group: Reserved (GREASE) (0xaaaa)
                Supported Group: x25519 (0x001d)
                Supported Group: secp256r1 (0x0017)
                Supported Group: secp384r1 (0x0018)
        Extension: ec_point_formats (len=2)
            Type: ec_point_formats (11)
            Length: 2
            EC point formats Length: 1
            Elliptic curves point formats (1)
                EC point format: uncompressed (0)
        Extension: SessionTicket TLS (len=0)
            Type: SessionTicket TLS (35)
            Length: 0
            Data (0 bytes)
        Extension: application_layer_protocol_negotiation (len=14)
            Type: application_layer_protocol_negotiation (16)
            Length: 14
            ALPN Extension Length: 12
            ALPN Protocol
                ALPN string length: 2
                ALPN Next Protocol: h2
                ALPN string length: 8
                ALPN Next Protocol: http/1.1
        Extension: status_request (len=5)
            Type: status_request (5)
            Length: 5
            Certificate Status Type: OCSP (1)
            Responder ID list Length: 0
            Request Extensions Length: 0
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
        Extension: signed_certificate_timestamp (len=0)
            Type: signed_certificate_timestamp (18)
            Length: 0
        Extension: key_share (len=43)
            Type: key_share (51)
            Length: 43
            Key Share extension
                Client Key Share Length: 41
                Key Share Entry: Group: Reserved (GREASE), Key Exchange length: 1
                    Group: Reserved (GREASE) (43690)
                    Key Exchange Length: 1
                    Key Exchange: 00
                Key Share Entry: Group: x25519, Key Exchange length: 32
                    Group: x25519 (29)
                    Key Exchange Length: 32
                    Key Exchange: bae028c4e9d1b9ca8246fe01214d7d085fc41ad45769f70e...
        Extension: psk_key_exchange_modes (len=2)
            Type: psk_key_exchange_modes (45)
            Length: 2
            PSK Key Exchange Modes Length: 1
            PSK Key Exchange Mode: PSK with (EC)DHE key establishment (psk_dhe_ke) (1)
        Extension: supported_versions (len=11)
            Type: supported_versions (43)
            Length: 11
            Supported Versions length: 10
            Supported Version: Unknown (0xdada)
            Supported Version: TLS 1.3 (0x0304)
            Supported Version: TLS 1.2 (0x0303)
            Supported Version: TLS 1.1 (0x0302)
            Supported Version: TLS 1.0 (0x0301)
        Extension: Unknown type 27 (len=3)
            Type: Unknown (27)
            Length: 3
            Data: 020002
        Extension: Reserved (GREASE) (len=1)
            Type: Reserved (GREASE) (31354)
            Length: 1
            Data: 00
        Extension: padding (len=191)
            Type: padding (21)
            Length: 191
            Padding Data: 000000000000000000000000000000000000000000000000...
```

### HelloRetryRequestを受け取った後のClientHello
```
TLSv1.3 Record Layer: Handshake Protocol: Client Hello
    Content Type: Handshake (22)
    Version: TLS 1.2 (0x0303)
    Length: 512
    Handshake Protocol: Client Hello
        Handshake Type: Client Hello (1)
        Length: 508
        Version: TLS 1.2 (0x0303)
        Random: fc238baf1eca92c3cf105dc78526bf546e0d313cc367e959...
        Session ID Length: 32
        Session ID: 6ed732a322914b575bfd7bc88dcca70daa638f5590a02f58...
        Cipher Suites Length: 34
        Cipher Suites (17 suites)
            Cipher Suite: Reserved (GREASE) (0x3a3a)
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
        Compression Methods Length: 1
        Compression Methods (1 method)
        Extensions Length: 401
        Extension: Reserved (GREASE) (len=0)
            Type: Reserved (GREASE) (35466)
            Length: 0
            Data: <MISSING>
        Extension: server_name (len=30)
            Type: server_name (0)
            Length: 30
            Server Name Indication extension
                Server Name list length: 28
                Server Name Type: host_name (0)
                Server Name length: 25
                Server Name: cdn.syndication.twimg.com
        Extension: extended_master_secret (len=0)
            Type: extended_master_secret (23)
            Length: 0
        Extension: renegotiation_info (len=1)
            Type: renegotiation_info (65281)
            Length: 1
            Renegotiation Info extension
                Renegotiation info extension length: 0
        Extension: supported_groups (len=10)
            Type: supported_groups (10)
            Length: 10
            Supported Groups List Length: 8
            Supported Groups (4 groups)
                Supported Group: Reserved (GREASE) (0xaaaa)
                Supported Group: x25519 (0x001d)
                Supported Group: secp256r1 (0x0017)
                Supported Group: secp384r1 (0x0018)
        Extension: ec_point_formats (len=2)
            Type: ec_point_formats (11)
            Length: 2
            EC point formats Length: 1
            Elliptic curves point formats (1)
                EC point format: uncompressed (0)
        Extension: SessionTicket TLS (len=0)
            Type: SessionTicket TLS (35)
            Length: 0
            Data (0 bytes)
        Extension: application_layer_protocol_negotiation (len=14)
            Type: application_layer_protocol_negotiation (16)
            Length: 14
            ALPN Extension Length: 12
            ALPN Protocol
                ALPN string length: 2
                ALPN Next Protocol: h2
                ALPN string length: 8
                ALPN Next Protocol: http/1.1
        Extension: status_request (len=5)
            Type: status_request (5)
            Length: 5
            Certificate Status Type: OCSP (1)
            Responder ID list Length: 0
            Request Extensions Length: 0
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
        Extension: signed_certificate_timestamp (len=0)
            Type: signed_certificate_timestamp (18)
            Length: 0
        Extension: key_share (len=71)
            Type: key_share (51)
            Length: 71
            Key Share extension
                Client Key Share Length: 69
                Key Share Entry: Group: secp256r1, Key Exchange length: 65
                    Group: secp256r1 (23)
                    Key Exchange Length: 65
                    Key Exchange: 04677ad2be6e5b5f4f2d98c212893f5bc06ff8634474677c...
        Extension: psk_key_exchange_modes (len=2)
            Type: psk_key_exchange_modes (45)
            Length: 2
            PSK Key Exchange Modes Length: 1
            PSK Key Exchange Mode: PSK with (EC)DHE key establishment (psk_dhe_ke) (1)
        Extension: supported_versions (len=11)
            Type: supported_versions (43)
            Length: 11
            Supported Versions length: 10
            Supported Version: Unknown (0xdada)
            Supported Version: TLS 1.3 (0x0304)
            Supported Version: TLS 1.2 (0x0303)
            Supported Version: TLS 1.1 (0x0302)
            Supported Version: TLS 1.0 (0x0301)
        Extension: Unknown type 27 (len=3)
            Type: Unknown (27)
            Length: 3
            Data: 020002
        Extension: Reserved (GREASE) (len=1)
            Type: Reserved (GREASE) (31354)
            Length: 1
            Data: 00
        Extension: padding (len=163)
            Type: padding (21)
            Length: 163
            Padding Data: 000000000000000000000000000000000000000000000000...
```

