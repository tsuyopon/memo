# 概要
ClientHello1 -> HelloRetryRequest -> ClientHello2 のサンプルを眺める。

# 詳細

最初にクライアントはサーバ側に次のClientHello1を送ります。
曲線グループ(supported_group)としてはx25519、 secp256r1、secp384r1の３つが対応していますが、key_shareにはx25519の公開鍵しか含めていないことに着目します。
```
TLSv1.3 Record Layer: Handshake Protocol: Client Hello
    Content Type: Handshake (22)
    Version: TLS 1.0 (0x0301)
    Length: 1488
    Handshake Protocol: Client Hello
        Handshake Type: Client Hello (1)
        Length: 1484
        Version: TLS 1.2 (0x0303)
        Random: 2de71a901584d0f7649a0fb3f4929a5685a8dd033ea07f86…
        Session ID Length: 32
        Session ID: 92e7d28ac26524c67e17631859698e804c1879e857628405…
        Cipher Suites Length: 34
        Cipher Suites (17 suites)
            Cipher Suite: Reserved (GREASE) (0x9a9a)
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
            Compression Method: null (0)
        Extensions Length: 1377
        Extension: Reserved (GREASE) (len=0)
            Type: Reserved (GREASE) (14906)
            Length: 0
            Data: <MISSING>
        Extension: server_name (len=25)
            Type: server_name (0)
            Length: 25
            Server Name Indication extension
                Server Name list length: 23
                Server Name Type: host_name (0)
                Server Name length: 20
                Server Name: platform.twitter.com
        Extension: extended_master_secret (len=0)
            Type: extended_master_secret (23)
            Length: 0
        Extension: renegotiation_info (len=1)
            Type: renegotiation_info (65281)
            Length: 1
            Renegotiation Info extension
                Renegotiation info extension length: 0
        Extension: supported_groups (len=12)
            Type: supported_groups (10)
            Length: 12
            Supported Groups List Length: 10
            Supported Groups (5 groups)
                Supported Group: Reserved (GREASE) (0xcaca)
                Supported Group: Unknown (0x4138)
                Supported Group: x25519 (0x001d)
                Supported Group: secp256r1 (0x0017)
                Supported Group: secp384r1 (0x0018)
        Extension: ec_point_formats (len=2)
            Type: ec_point_formats (11)
            Length: 2
            EC point formats Length: 1
            Elliptic curves point formats (1)
                EC point format: uncompressed (0)
        Extension: session_ticket (len=0)
            Type: session_ticket (35)
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
        Extension: key_share (len=1217)
            Type: key_share (51)
            Length: 1217
            Key Share extension
                Client Key Share Length: 1215
                Key Share Entry: Group: Reserved (GREASE), Key Exchange length: 1
                    Group: Reserved (GREASE) (51914)
                    Key Exchange Length: 1
                    Key Exchange: 00
                Key Share Entry: Group: Unknown (16696), Key Exchange length: 1170
                    Group: Unknown (16696)
                    Key Exchange Length: 1170
                    Key Exchange: 1e980f7f4600544346bc8b7f0e7c817e98bb0ce2986e5efa…
                Key Share Entry: Group: x25519, Key Exchange length: 32
                    Group: x25519 (29)
                    Key Exchange Length: 32
                    Key Exchange: 3ad6c0d217db24ff666af03980438dd7b0a589539cec0921…
        Extension: psk_key_exchange_modes (len=2)
            Type: psk_key_exchange_modes (45)
            Length: 2
            PSK Key Exchange Modes Length: 1
            PSK Key Exchange Mode: PSK with (EC)DHE key establishment (psk_dhe_ke) (1)
        Extension: supported_versions (len=11)
            Type: supported_versions (43)
            Length: 11
            Supported Versions length: 10
            Supported Version: Unknown (0xbaba)
            Supported Version: TLS 1.3 (0x0304)
            Supported Version: TLS 1.2 (0x0303)
            Supported Version: TLS 1.1 (0x0302)
            Supported Version: TLS 1.0 (0x0301)
        Extension: compress_certificate (len=3)
            Type: compress_certificate (27)
            Length: 3
            Algorithms Length: 2
            Algorithm: broli (2)
        Extension: Reserved (GREASE) (len=1)
            Type: Reserved (GREASE) (47802)
            Length: 1
            Data: 00
```

受け取ったサーバは別の曲線情報でやり取りしたいので曲線グループを変更するために、Hello Retry Requestを送ります。
この場合の例では、サーバからクライアントに対しては次の「Hello Retry Request」と「Change Cipher Spec」の２つのメッセージを送付しています。

ここで着目すべきはHRRのRandomには次の「HelloRetryRequest」をSHA256で変換したハッシュ値が入っています。
HelloRetryRequestメッセージはHandshakeTypeを見るとServerHelloタイプとなっていますが、クライアント側はRandom値が以下のハッシュと一致しているかどうかでServerHelloかHelloRetryRequestかを識別します。
```
$ echo -n "HelloRetryRequest" | sha256sum 
cf21ad74e59a6111be1d8c021e65b891c2a211167abb8c5e079e09e2c8a8339c  -
```

また、supported_veresionでTLS1.3が指定されていて、key_shareでsecp256r1が指定されています。secp256r1はkey_shareに公開鍵が含まれていませんでした。
```
TLSv1.3 Record Layer: Handshake Protocol: Hello Retry Request
    Content Type: Handshake (22)
    Version: TLS 1.2 (0x0303)
    Length: 88
    Handshake Protocol: Hello Retry Request
        Handshake Type: Server Hello (2)
        Length: 84
        Version: TLS 1.2 (0x0303)
        Random: cf21ad74e59a6111be1d8c021e65b891c2a211167abb8c5e… (HelloRetryRequest magic)
        Session ID Length: 32
        Session ID: 92e7d28ac26524c67e17631859698e804c1879e857628405…
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

```
TLSv1.3 Record Layer: Change Cipher Spec Protocol: Change Cipher Spec
    Content Type: Change Cipher Spec (20)
    Version: TLS 1.2 (0x0303)
    Length: 1
    Change Cipher Spec Message
```

Hello Retry Requestを受け取ったクライアントはsecp256r1の曲線で公開鍵を生成するために「Change Cipher Spec」と「Client Hello」を返します。
２度目に送付されてくるClientHello2のKeyShareエクステンションの中にはHelloRetryRequestで指定されたsecp256r1グループの公開鍵が含まれていることに着目してください。
```
TLSv1.3 Record Layer: Change Cipher Spec Protocol: Change Cipher Spec
    Content Type: Change Cipher Spec (20)
    Version: TLS 1.2 (0x0303)
    Length: 1
    Change Cipher Spec Message
```

```
Handshake Protocol: Client Hello
    Handshake Type: Client Hello (1)
    Length: 508
    Version: TLS 1.2 (0x0303)
    Random: 2de71a901584d0f7649a0fb3f4929a5685a8dd033ea07f86…
    Session ID Length: 32
    Session ID: 92e7d28ac26524c67e17631859698e804c1879e857628405…
    Cipher Suites Length: 34
    Cipher Suites (17 suites)
        Cipher Suite: Reserved (GREASE) (0x9a9a)
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
        Compression Method: null (0)
    Extensions Length: 401
    Extension: Reserved (GREASE) (len=0)
        Type: Reserved (GREASE) (14906)
        Length: 0
        Data: <MISSING>
    Extension: server_name (len=25)
        Type: server_name (0)
        Length: 25
        Server Name Indication extension
            Server Name list length: 23
            Server Name Type: host_name (0)
            Server Name length: 20
            Server Name: platform.twitter.com
    Extension: extended_master_secret (len=0)
        Type: extended_master_secret (23)
        Length: 0
    Extension: renegotiation_info (len=1)
        Type: renegotiation_info (65281)
        Length: 1
        Renegotiation Info extension
            Renegotiation info extension length: 0
    Extension: supported_groups (len=12)
        Type: supported_groups (10)
        Length: 12
        Supported Groups List Length: 10
        Supported Groups (5 groups)
            Supported Group: Reserved (GREASE) (0xcaca)
            Supported Group: Unknown (0x4138)
            Supported Group: x25519 (0x001d)
            Supported Group: secp256r1 (0x0017)
            Supported Group: secp384r1 (0x0018)
    Extension: ec_point_formats (len=2)
        Type: ec_point_formats (11)
        Length: 2
        EC point formats Length: 1
        Elliptic curves point formats (1)
            EC point format: uncompressed (0)
    Extension: session_ticket (len=0)
        Type: session_ticket (35)
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
                Key Exchange: 045dcf997e7e1a405cffc9d30cb65aaa7d070845ba4a248c…
    Extension: psk_key_exchange_modes (len=2)
        Type: psk_key_exchange_modes (45)
        Length: 2
        PSK Key Exchange Modes Length: 1
        PSK Key Exchange Mode: PSK with (EC)DHE key establishment (psk_dhe_ke) (1)
    Extension: supported_versions (len=11)
        Type: supported_versions (43)
        Length: 11
        Supported Versions length: 10
        Supported Version: Unknown (0xbaba)
        Supported Version: TLS 1.3 (0x0304)
        Supported Version: TLS 1.2 (0x0303)
        Supported Version: TLS 1.1 (0x0302)
        Supported Version: TLS 1.0 (0x0301)
    Extension: compress_certificate (len=3)
        Type: compress_certificate (27)
        Length: 3
        Algorithms Length: 2
        Algorithm: broli (2)
    Extension: Reserved (GREASE) (len=1)
        Type: Reserved (GREASE) (47802)
        Length: 1
        Data: 00
    Extension: padding (len=166)
        Type: padding (21)
        Length: 166
        Padding Data: 000000000000000000000000000000000000000000000000…
```

# まとめ
上記のサンプルでは ClientHello -> HelloRetryRequest -> ClientHello メッセージのやり取りを見ました。

ClientHello1では対応している曲線グループ(リスト)とそれに含まれる曲線グループの公開鍵を指定してきています。しかし、含まれる公開鍵は曲線グループ全てのものが含まれているわけではありません。
ClientHello1を受け取ったサーバ側では欲しい曲線グループの公開鍵が存在しなかったので、HelloRetryRequestメッセージにてsecp256r1の公開鍵を欲しい旨を指定します。
クライアント側はHelloRetryRequestを受け取るとハンドシェイクタイプはServerHelloと同一なのでRandom値がHelloRetryRequestのsha256値となっていることを確認するとでHelloRetryRequestと識別できるようになります。
クライアントからサーバに再度ClientHelloを送付する場合には、key_shareにHelloRetryRequestで指定された曲線グループの公開鍵を含めています。

