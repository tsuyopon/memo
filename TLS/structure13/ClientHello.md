### 単純なサンプル
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


### クライアントがクライアント認証に対するリクエストを出す(certificate_authorities拡張を含む)
これはopensslコマンドのrequestCAfileオプションを指定してcertificate_authoritiesを出力した例である。

```
Frame 4: 502 bytes on wire (4016 bits), 502 bytes captured (4016 bits)
Ethernet II, Src: 00:00:00_00:00:00 (00:00:00:00:00:00), Dst: 00:00:00_00:00:00 (00:00:00:00:00:00)
Internet Protocol Version 6, Src: ::1, Dst: ::1
Transmission Control Protocol, Src Port: 42780, Dst Port: 443, Seq: 1, Ack: 1, Len: 416
Transport Layer Security
    TLSv1.3 Record Layer: Handshake Protocol: Client Hello
        Content Type: Handshake (22)
        Version: TLS 1.0 (0x0301)
        Length: 411
        Handshake Protocol: Client Hello
            Handshake Type: Client Hello (1)
            Length: 407
            Version: TLS 1.2 (0x0303)
            Random: 337e8cd948e1591bb0f1e913c31bf8e229afd4f24bde2a2d…
            Session ID Length: 32
            Session ID: 45e36ce4675ede9ded5f0afe2a0c669e2a46474fc3b0b8aa…
            Cipher Suites Length: 62
            Cipher Suites (31 suites)
            Compression Methods Length: 1
            Compression Methods (1 method)
            Extensions Length: 272
            Extension: ec_point_formats (len=4)
            Extension: supported_groups (len=12)
            Extension: session_ticket (len=0)
            Extension: encrypt_then_mac (len=0)
            Extension: extended_master_secret (len=0)
            Extension: signature_algorithms (len=48)
            Extension: supported_versions (len=9)
            Extension: psk_key_exchange_modes (len=2)
            Extension: key_share (len=38)
            Extension: certificate_authorities (len=119)
                Type: certificate_authorities (47)
                Length: 119
                Distinguished Names Length: 117
                Distinguished Names (117 bytes)
                    Distinguished Name Length: 115
                    Distinguished Name: (id-at-commonName=client.co.jp,id-at-organizationalUnitName=organizationunit,id-at-organizationName=client,id-at-localityName=city,id-at-stateOrProvinceName=Saitama,id-at-countryName=JP)
                        RDNSequence item: 1 item (id-at-countryName=JP)
                            RelativeDistinguishedName item (id-at-countryName=JP)
                                Id: 2.5.4.6 (id-at-countryName)
                                CountryName: JP
                        RDNSequence item: 1 item (id-at-stateOrProvinceName=Saitama)
                            RelativeDistinguishedName item (id-at-stateOrProvinceName=Saitama)
                                Id: 2.5.4.8 (id-at-stateOrProvinceName)
                                DirectoryString: uTF8String (4)
                                    uTF8String: Saitama
                        RDNSequence item: 1 item (id-at-localityName=city)
                            RelativeDistinguishedName item (id-at-localityName=city)
                                Id: 2.5.4.7 (id-at-localityName)
                                DirectoryString: uTF8String (4)
                                    uTF8String: city
                        RDNSequence item: 1 item (id-at-organizationName=client)
                            RelativeDistinguishedName item (id-at-organizationName=client)
                                Id: 2.5.4.10 (id-at-organizationName)
                                DirectoryString: uTF8String (4)
                                    uTF8String: client
                        RDNSequence item: 1 item (id-at-organizationalUnitName=organizationunit)
                            RelativeDistinguishedName item (id-at-organizationalUnitName=organizationunit)
                                Id: 2.5.4.11 (id-at-organizationalUnitName)
                                DirectoryString: uTF8String (4)
                                    uTF8String: organizationunit
                        RDNSequence item: 1 item (id-at-commonName=client.co.jp)
                            RelativeDistinguishedName item (id-at-commonName=client.co.jp)
                                Id: 2.5.4.3 (id-at-commonName)
                                DirectoryString: uTF8String (4)
```

上記のcertificate_authorities拡張が含まれたClientHelloを発行する際にopensslコマンドへのrequestCAfileオプションとして指定したX509証明書は次の通り。
本来requestCAfileにはトラストアンカーを指定する。
```
$ openssl x509 -in CLIENT_CERT-ca.crt -text
Certificate:
    Data:
        Version: 1 (0x0)
        Serial Number:
            b7:9c:98:7d:3b:85:92:ab
    Signature Algorithm: sha256WithRSAEncryption
        Issuer: C=JP, ST=Saitama, L=city, O=client, OU=organizationunit, CN=client.co.jp
        Validity
            Not Before: Feb 10 16:03:59 2020 GMT
            Not After : Feb  7 16:03:59 2030 GMT
        Subject: C=JP, ST=Saitama, L=city, O=client, OU=organizationunit, CN=client.co.jp
        Subject Public Key Info:
            Public Key Algorithm: rsaEncryption
                Public-Key: (2048 bit)
                Modulus:
                    00:ea:ff:ad:4e:5d:b3:88:17:7d:96:4e:70:82:04:
                    6c:d5:1a:6e:b6:8a:7b:8c:a7:75:b8:cf:46:1d:f7:
(snip)
```
