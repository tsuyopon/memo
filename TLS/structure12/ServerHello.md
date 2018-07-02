# Server Hello

以下にサンプル1とサンプル2が添付されている。次の例では、Cipher Suite及びExtension情報が異なっています。

- サンプル1
```
TLSv1.2 Record Layer: Handshake Protocol: Server Hello
    Content Type: Handshake (22)
    Version: TLS 1.2 (0x0303)
    Length: 88
    Handshake Protocol: Server Hello
        Handshake Type: Server Hello (2)
        Length: 84
        Version: TLS 1.2 (0x0303)
        Random: 12e43dd777ea58ee0e59a689ca6a948b94a4a66c97a3ab12...
            GMT Unix Time: Jan 17, 1980 18:05:27.000000000 JST
            Random Bytes: 77ea58ee0e59a689ca6a948b94a4a66c97a3ab12e8618fca...
        Session ID Length: 0
        Cipher Suite: TLS_ECDHE_RSA_WITH_AES_128_GCM_SHA256 (0xc02f)
        Compression Method: null (0)
        Extensions Length: 44
        Extension: renegotiation_info (len=1)
            Type: renegotiation_info (65281)
            Length: 1
            Renegotiation Info extension
                Renegotiation info extension length: 0

```


- サンプル2
```
Secure Sockets Layer
    TLSv1.2 Record Layer: Handshake Protocol: Server Hello
        Content Type: Handshake (22)
        Version: TLS 1.2 (0x0303)
        Length: 80
        Handshake Protocol: Server Hello
            Handshake Type: Server Hello (2)
            Length: 76
            Version: TLS 1.2 (0x0303)
            Random: eec925a5e6386c936b26dc07a4f6c16daed0978f7b3f965d...
                GMT Unix Time: Dec 12, 2096 23:09:41.000000000 JST
                Random Bytes: e6386c936b26dc07a4f6c16daed0978f7b3f965d7b590702...
            Session ID Length: 0
            Cipher Suite: TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384 (0xc030)
            Compression Method: null (0)
            Extensions Length: 36
            Extension: renegotiation_info (len=1)
                Type: renegotiation_info (65281)
                Length: 1
                Renegotiation Info extension
                    Renegotiation info extension length: 0
            Extension: ec_point_formats (len=4)
                Type: ec_point_formats (11)
                Length: 4
                EC point formats Length: 3
                Elliptic curves point formats (3)
                    EC point format: uncompressed (0)
                    EC point format: ansiX962_compressed_prime (1)
                    EC point format: ansiX962_compressed_char2 (2)
            Extension: SessionTicket TLS (len=0)
                Type: SessionTicket TLS (35)
                Length: 0
                Data (0 bytes)
            Extension: status_request (len=0)
                Type: status_request (5)
                Length: 0
            Extension: application_layer_protocol_negotiation (len=11)
                Type: application_layer_protocol_negotiation (16)
                Length: 11
                ALPN Extension Length: 9
                ALPN Protocol
                    ALPN string length: 8
                    ALPN Next Protocol: http/1.1
```
