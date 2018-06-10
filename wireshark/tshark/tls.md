# 概要
単純な次のTLSプログラムを稼働させて
- https://github.com/tsuyopon/cpp/blob/master/openssl/simple/server.c

以下を実行した際のパケットキャプチャーを添付する
```
$ openssl s_client -connect localhost:4433
```

# 詳細
### TLS主要パケットのみ表示する場合
```
$ sudo tshark  -i lo -d tcp.port==4433,ssl -Y ssl
Capturing on 'Loopback'
  6 0.000939231    127.0.0.1 -> 127.0.0.1    SSL 355 Client Hello
  8 0.073720363    127.0.0.1 -> 127.0.0.1    TLSv1.2 1271 Server Hello, Certificate, Server Key Exchange, Server Hello Done
 10 0.076197171    127.0.0.1 -> 127.0.0.1    TLSv1.2 192 Client Key Exchange, Change Cipher Spec, Encrypted Handshake Message
 12 0.082318453    127.0.0.1 -> 127.0.0.1    TLSv1.2 292 New Session Ticket, Change Cipher Spec, Encrypted Handshake Message
 13 0.082428470    127.0.0.1 -> 127.0.0.1    TLSv1.2 100 Application Data
 15 0.084265851    127.0.0.1 -> 127.0.0.1    TLSv1.2 97 Encrypted Alert
```

### TCPなどを含めてTLS主要パケットのみを表示する場合
```
$ sudo tshark  -i lo -d tcp.port==4433,ssl 
Capturing on 'Loopback'
  1 0.000000000          ::1 -> ::1          TCP 94 33492 > vop [SYN] Seq=0 Win=43690 Len=0 MSS=65476 SACK_PERM=1 TSval=6752698 TSecr=0 WS=128
  2 0.000022924          ::1 -> ::1          TCP 74 vop > 33492 [RST, ACK] Seq=1 Ack=1 Win=0 Len=0
  3 0.000150640    127.0.0.1 -> 127.0.0.1    TCP 74 45964 > vop [SYN] Seq=0 Win=43690 Len=0 MSS=65495 SACK_PERM=1 TSval=6752698 TSecr=0 WS=128
  4 -1482369608.783267898    127.0.0.1 -> 127.0.0.1    TCP 74 vop > 45964 [SYN, ACK] Seq=0 Ack=1 Win=43690 Len=0 MSS=65495 SACK_PERM=1 TSval=6752698 TSecr=6752698 WS=128
  5 0.000191406    127.0.0.1 -> 127.0.0.1    TCP 66 45964 > vop [ACK] Seq=1 Ack=1 Win=43776 Len=0 TSval=6752698 TSecr=6752698
  6 0.000927580    127.0.0.1 -> 127.0.0.1    SSL 355 Client Hello
  7 0.000984864    127.0.0.1 -> 127.0.0.1    TCP 66 vop > 45964 [ACK] Seq=1 Ack=290 Win=44800 Len=0 TSval=6752698 TSecr=6752698
  8 0.053686752    127.0.0.1 -> 127.0.0.1    TLSv1.2 1271 Server Hello, Certificate, Server Key Exchange, Server Hello Done
  9 0.053764314    127.0.0.1 -> 127.0.0.1    TCP 66 45964 > vop [ACK] Seq=290 Ack=1206 Win=174720 Len=0 TSval=6752752 TSecr=6752752
 10 0.055201353    127.0.0.1 -> 127.0.0.1    TLSv1.2 192 Client Key Exchange, Change Cipher Spec, Encrypted Handshake Message
 11 0.055512637    127.0.0.1 -> 127.0.0.1    TCP 66 vop > 45964 [ACK] Seq=1206 Ack=416 Win=44800 Len=0 TSval=6752755 TSecr=6752754
 12 0.059203914    127.0.0.1 -> 127.0.0.1    TLSv1.2 292 New Session Ticket, Change Cipher Spec, Encrypted Handshake Message
 13 0.059264491    127.0.0.1 -> 127.0.0.1    TLSv1.2 100 Application Data
 14 0.060353267    127.0.0.1 -> 127.0.0.1    TCP 66 45964 > vop [ACK] Seq=416 Ack=1467 Win=177152 Len=0 TSval=6752759 TSecr=6752756
 15 0.060408794    127.0.0.1 -> 127.0.0.1    TLSv1.2 97 Encrypted Alert
 16 0.060426631    127.0.0.1 -> 127.0.0.1    TCP 54 vop > 45964 [RST] Seq=1467 Win=0 Len=0
```

ダンプ情報を表示する
```
$ sudo tshark -i lo -x -d tcp.port==4433,ssl -Y ssl
Running as user "root" and group "root". This could be dangerous.
Capturing on 'Loopback'
0000  00 00 00 00 00 00 00 00 00 00 00 00 08 00 45 00   ..............E.
0010  01 55 d9 5d 40 00 40 06 62 43 7f 00 00 01 7f 00   .U.]@.@.bC......
0020  00 01 b3 ac 11 51 5a f7 fb 5d be 3d 3b bc 80 18   .....QZ..].=;...
0030  01 56 ff 49 00 00 01 01 08 0a 00 74 22 07 00 74   .V.I.......t"..t
0040  22 07 16 03 01 01 1c 01 00 01 18 03 03 fc b1 cb   "...............
0050  11 42 f2 bc 50 51 30 0e ee 05 f3 89 b5 de 3e 1f   .B..PQ0.......>.
0060  a9 2f 55 43 43 8a 57 7e 05 c7 f4 6d d4 00 00 ac   ./UCC.W~...m....
0070  c0 30 c0 2c c0 28 c0 24 c0 14 c0 0a 00 a5 00 a3   .0.,.(.$........
0080  00 a1 00 9f 00 6b 00 6a 00 69 00 68 00 39 00 38   .....k.j.i.h.9.8
(snip)
```

詳細情報を表示したものは以下
```
$ sudo tshark -i lo -V -d tcp.port==4433,ssl -Y ssl
Running as user "root" and group "root". This could be dangerous.
Capturing on 'Loopback'
Frame 6: 355 bytes on wire (2840 bits), 355 bytes captured (2840 bits) on interface 0
    Interface id: 0
    Encapsulation type: Ethernet (1)
    Arrival Time: Nov 23, 2017 02:47:29.380677469 JST
    [Time shift for this packet: 0.000000000 seconds]
    Epoch Time: 1511372849.380677469 seconds
    [Time delta from previous captured frame: 0.001724692 seconds]
    [Time delta from previous displayed frame: 0.000000000 seconds]
    [Time since reference or first frame: 0.002322070 seconds]
    Frame Number: 6
    Frame Length: 355 bytes (2840 bits)
    Capture Length: 355 bytes (2840 bits)
    [Frame is marked: False]
    [Frame is ignored: False]
    [Protocols in frame: eth:ip:tcp:ssl]
Ethernet II, Src: 00:00:00_00:00:00 (00:00:00:00:00:00), Dst: 00:00:00_00:00:00 (00:00:00:00:00:00)
    Destination: 00:00:00_00:00:00 (00:00:00:00:00:00)
        Address: 00:00:00_00:00:00 (00:00:00:00:00:00)
        .... ..0. .... .... .... .... = LG bit: Globally unique address (factory default)
        .... ...0 .... .... .... .... = IG bit: Individual address (unicast)
    Source: 00:00:00_00:00:00 (00:00:00:00:00:00)
        Address: 00:00:00_00:00:00 (00:00:00:00:00:00)
        .... ..0. .... .... .... .... = LG bit: Globally unique address (factory default)
        .... ...0 .... .... .... .... = IG bit: Individual address (unicast)
    Type: IP (0x0800)
Internet Protocol Version 4, Src: 127.0.0.1 (127.0.0.1), Dst: 127.0.0.1 (127.0.0.1)
    Version: 4
    Header length: 20 bytes
    Differentiated Services Field: 0x00 (DSCP 0x00: Default; ECN: 0x00: Not-ECT (Not ECN-Capable Transport))
        0000 00.. = Differentiated Services Codepoint: Default (0x00)
        .... ..00 = Explicit Congestion Notification: Not-ECT (Not ECN-Capable Transport) (0x00)
    Total Length: 341
    Identification: 0xa783 (42883)
    Flags: 0x02 (Don't Fragment)
        0... .... = Reserved bit: Not set
        .1.. .... = Don't fragment: Set
        ..0. .... = More fragments: Not set
    Fragment offset: 0
    Time to live: 64
    Protocol: TCP (6)
    Header checksum: 0x941d [validation disabled]
        [Good: False]
        [Bad: False]
    Source: 127.0.0.1 (127.0.0.1)
    Destination: 127.0.0.1 (127.0.0.1)
Transmission Control Protocol, Src Port: 45992 (45992), Dst Port: vop (4433), Seq: 1, Ack: 1, Len: 289
    Source port: 45992 (45992)
    Destination port: vop (4433)
    [Stream index: 1]
    Sequence number: 1    (relative sequence number)
    [Next sequence number: 290    (relative sequence number)]
    Acknowledgment number: 1    (relative ack number)
    Header length: 32 bytes
    Flags: 0x018 (PSH, ACK)
        000. .... .... = Reserved: Not set
        ...0 .... .... = Nonce: Not set
        .... 0... .... = Congestion Window Reduced (CWR): Not set
        .... .0.. .... = ECN-Echo: Not set
        .... ..0. .... = Urgent: Not set
        .... ...1 .... = Acknowledgment: Set
        .... .... 1... = Push: Set
        .... .... .0.. = Reset: Not set
        .... .... ..0. = Syn: Not set
        .... .... ...0 = Fin: Not set
    Window size value: 342
    [Calculated window size: 43776]
    [Window size scaling factor: 128]
    Checksum: 0xff49 [validation disabled]
        [Good Checksum: False]
        [Bad Checksum: False]
    Options: (12 bytes), No-Operation (NOP), No-Operation (NOP), Timestamps
        No-Operation (NOP)
            Type: 1
                0... .... = Copy on fragmentation: No
                .00. .... = Class: Control (0)
                ...0 0001 = Number: No-Operation (NOP) (1)
        No-Operation (NOP)
            Type: 1
                0... .... = Copy on fragmentation: No
                .00. .... = Class: Control (0)
                ...0 0001 = Number: No-Operation (NOP) (1)
        Timestamps: TSval 7373972, TSecr 7373971
            Kind: Timestamp (8)
            Length: 10
            Timestamp value: 7373972
            Timestamp echo reply: 7373971
    [SEQ/ACK analysis]
        [Bytes in flight: 289]
Secure Sockets Layer
    SSL Record Layer: Handshake Protocol: Client Hello
        Content Type: Handshake (22)
        Version: TLS 1.0 (0x0301)
        Length: 284
        Handshake Protocol: Client Hello
            Handshake Type: Client Hello (1)
            Length: 280
            Version: TLS 1.2 (0x0303)
            Random
                gmt_unix_time: Jul  7, 2021 00:23:39.000000000 JST
                random_bytes: 57962d9c3b93e913ae683a289b4d2c4e4476e59d284ddf59...
            Session ID Length: 0
            Cipher Suites Length: 172
            Cipher Suites (86 suites)
                Cipher Suite: TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384 (0xc030)
                Cipher Suite: TLS_ECDHE_ECDSA_WITH_AES_256_GCM_SHA384 (0xc02c)
                Cipher Suite: TLS_ECDHE_RSA_WITH_AES_256_CBC_SHA384 (0xc028)
                Cipher Suite: TLS_ECDHE_ECDSA_WITH_AES_256_CBC_SHA384 (0xc024)
                Cipher Suite: TLS_ECDHE_RSA_WITH_AES_256_CBC_SHA (0xc014)
                Cipher Suite: TLS_ECDHE_ECDSA_WITH_AES_256_CBC_SHA (0xc00a)
                Cipher Suite: TLS_DH_DSS_WITH_AES_256_GCM_SHA384 (0x00a5)
                Cipher Suite: TLS_DHE_DSS_WITH_AES_256_GCM_SHA384 (0x00a3)
                Cipher Suite: TLS_DH_RSA_WITH_AES_256_GCM_SHA384 (0x00a1)
                Cipher Suite: TLS_DHE_RSA_WITH_AES_256_GCM_SHA384 (0x009f)
                Cipher Suite: TLS_DHE_RSA_WITH_AES_256_CBC_SHA256 (0x006b)
                Cipher Suite: TLS_DHE_DSS_WITH_AES_256_CBC_SHA256 (0x006a)
                Cipher Suite: TLS_DH_RSA_WITH_AES_256_CBC_SHA256 (0x0069)
                Cipher Suite: TLS_DH_DSS_WITH_AES_256_CBC_SHA256 (0x0068)
                Cipher Suite: TLS_DHE_RSA_WITH_AES_256_CBC_SHA (0x0039)
                Cipher Suite: TLS_DHE_DSS_WITH_AES_256_CBC_SHA (0x0038)
                Cipher Suite: TLS_DH_RSA_WITH_AES_256_CBC_SHA (0x0037)
                Cipher Suite: TLS_DH_DSS_WITH_AES_256_CBC_SHA (0x0036)
                Cipher Suite: TLS_DHE_RSA_WITH_CAMELLIA_256_CBC_SHA (0x0088)
                Cipher Suite: TLS_DHE_DSS_WITH_CAMELLIA_256_CBC_SHA (0x0087)
                Cipher Suite: TLS_DH_RSA_WITH_CAMELLIA_256_CBC_SHA (0x0086)
                Cipher Suite: TLS_DH_DSS_WITH_CAMELLIA_256_CBC_SHA (0x0085)
                Cipher Suite: TLS_ECDH_RSA_WITH_AES_256_GCM_SHA384 (0xc032)
                Cipher Suite: TLS_ECDH_ECDSA_WITH_AES_256_GCM_SHA384 (0xc02e)
                Cipher Suite: TLS_ECDH_RSA_WITH_AES_256_CBC_SHA384 (0xc02a)
                Cipher Suite: TLS_ECDH_ECDSA_WITH_AES_256_CBC_SHA384 (0xc026)
                Cipher Suite: TLS_ECDH_RSA_WITH_AES_256_CBC_SHA (0xc00f)
                Cipher Suite: TLS_ECDH_ECDSA_WITH_AES_256_CBC_SHA (0xc005)
                Cipher Suite: TLS_RSA_WITH_AES_256_GCM_SHA384 (0x009d)
                Cipher Suite: TLS_RSA_WITH_AES_256_CBC_SHA256 (0x003d)
                Cipher Suite: TLS_RSA_WITH_AES_256_CBC_SHA (0x0035)
                Cipher Suite: TLS_RSA_WITH_CAMELLIA_256_CBC_SHA (0x0084)
                Cipher Suite: TLS_ECDHE_RSA_WITH_AES_128_GCM_SHA256 (0xc02f)
                Cipher Suite: TLS_ECDHE_ECDSA_WITH_AES_128_GCM_SHA256 (0xc02b)
                Cipher Suite: TLS_ECDHE_RSA_WITH_AES_128_CBC_SHA256 (0xc027)
                Cipher Suite: TLS_ECDHE_ECDSA_WITH_AES_128_CBC_SHA256 (0xc023)
                Cipher Suite: TLS_ECDHE_RSA_WITH_AES_128_CBC_SHA (0xc013)
                Cipher Suite: TLS_ECDHE_ECDSA_WITH_AES_128_CBC_SHA (0xc009)
                Cipher Suite: TLS_DH_DSS_WITH_AES_128_GCM_SHA256 (0x00a4)
                Cipher Suite: TLS_DHE_DSS_WITH_AES_128_GCM_SHA256 (0x00a2)
                Cipher Suite: TLS_DH_RSA_WITH_AES_128_GCM_SHA256 (0x00a0)
                Cipher Suite: TLS_DHE_RSA_WITH_AES_128_GCM_SHA256 (0x009e)
                Cipher Suite: TLS_DHE_RSA_WITH_AES_128_CBC_SHA256 (0x0067)
                Cipher Suite: TLS_DHE_DSS_WITH_AES_128_CBC_SHA256 (0x0040)
                Cipher Suite: TLS_DH_RSA_WITH_AES_128_CBC_SHA256 (0x003f)
                Cipher Suite: TLS_DH_DSS_WITH_AES_128_CBC_SHA256 (0x003e)
                Cipher Suite: TLS_DHE_RSA_WITH_AES_128_CBC_SHA (0x0033)
                Cipher Suite: TLS_DHE_DSS_WITH_AES_128_CBC_SHA (0x0032)
                Cipher Suite: TLS_DH_RSA_WITH_AES_128_CBC_SHA (0x0031)
                Cipher Suite: TLS_DH_DSS_WITH_AES_128_CBC_SHA (0x0030)
                Cipher Suite: TLS_DHE_RSA_WITH_SEED_CBC_SHA (0x009a)
                Cipher Suite: TLS_DHE_DSS_WITH_SEED_CBC_SHA (0x0099)
                Cipher Suite: TLS_DH_RSA_WITH_SEED_CBC_SHA (0x0098)
                Cipher Suite: TLS_DH_DSS_WITH_SEED_CBC_SHA (0x0097)
                Cipher Suite: TLS_DHE_RSA_WITH_CAMELLIA_128_CBC_SHA (0x0045)
                Cipher Suite: TLS_DHE_DSS_WITH_CAMELLIA_128_CBC_SHA (0x0044)
                Cipher Suite: TLS_DH_RSA_WITH_CAMELLIA_128_CBC_SHA (0x0043)
                Cipher Suite: TLS_DH_DSS_WITH_CAMELLIA_128_CBC_SHA (0x0042)
                Cipher Suite: TLS_ECDH_RSA_WITH_AES_128_GCM_SHA256 (0xc031)
                Cipher Suite: TLS_ECDH_ECDSA_WITH_AES_128_GCM_SHA256 (0xc02d)
                Cipher Suite: TLS_ECDH_RSA_WITH_AES_128_CBC_SHA256 (0xc029)
                Cipher Suite: TLS_ECDH_ECDSA_WITH_AES_128_CBC_SHA256 (0xc025)
                Cipher Suite: TLS_ECDH_RSA_WITH_AES_128_CBC_SHA (0xc00e)
                Cipher Suite: TLS_ECDH_ECDSA_WITH_AES_128_CBC_SHA (0xc004)
                Cipher Suite: TLS_RSA_WITH_AES_128_GCM_SHA256 (0x009c)
                Cipher Suite: TLS_RSA_WITH_AES_128_CBC_SHA256 (0x003c)
                Cipher Suite: TLS_RSA_WITH_AES_128_CBC_SHA (0x002f)
                Cipher Suite: TLS_RSA_WITH_SEED_CBC_SHA (0x0096)
                Cipher Suite: TLS_RSA_WITH_CAMELLIA_128_CBC_SHA (0x0041)
                Cipher Suite: TLS_ECDHE_RSA_WITH_3DES_EDE_CBC_SHA (0xc012)
                Cipher Suite: TLS_ECDHE_ECDSA_WITH_3DES_EDE_CBC_SHA (0xc008)
                Cipher Suite: TLS_DHE_RSA_WITH_3DES_EDE_CBC_SHA (0x0016)
                Cipher Suite: TLS_DHE_DSS_WITH_3DES_EDE_CBC_SHA (0x0013)
                Cipher Suite: TLS_DH_RSA_WITH_3DES_EDE_CBC_SHA (0x0010)
                Cipher Suite: TLS_DH_DSS_WITH_3DES_EDE_CBC_SHA (0x000d)
                Cipher Suite: TLS_ECDH_RSA_WITH_3DES_EDE_CBC_SHA (0xc00d)
                Cipher Suite: TLS_ECDH_ECDSA_WITH_3DES_EDE_CBC_SHA (0xc003)
                Cipher Suite: TLS_RSA_WITH_3DES_EDE_CBC_SHA (0x000a)
                Cipher Suite: TLS_RSA_WITH_IDEA_CBC_SHA (0x0007)
                Cipher Suite: TLS_ECDHE_RSA_WITH_RC4_128_SHA (0xc011)
                Cipher Suite: TLS_ECDHE_ECDSA_WITH_RC4_128_SHA (0xc007)
                Cipher Suite: TLS_ECDH_RSA_WITH_RC4_128_SHA (0xc00c)
                Cipher Suite: TLS_ECDH_ECDSA_WITH_RC4_128_SHA (0xc002)
                Cipher Suite: TLS_RSA_WITH_RC4_128_SHA (0x0005)
                Cipher Suite: TLS_RSA_WITH_RC4_128_MD5 (0x0004)
                Cipher Suite: TLS_EMPTY_RENEGOTIATION_INFO_SCSV (0x00ff)
            Compression Methods Length: 1
            Compression Methods (1 method)
                Compression Method: null (0)
            Extensions Length: 67
            Extension: ec_point_formats
                Type: ec_point_formats (0x000b)
                Length: 4
                EC point formats Length: 3
                Elliptic curves point formats (3)
                    EC point format: uncompressed (0)
                    EC point format: ansiX962_compressed_prime (1)
                    EC point format: ansiX962_compressed_char2 (2)
            Extension: elliptic_curves
                Type: elliptic_curves (0x000a)
                Length: 10
                Elliptic Curves Length: 8
                Elliptic curves (4 curves)
                    Elliptic curve: secp256r1 (0x0017)
                    Elliptic curve: secp521r1 (0x0019)
                    Elliptic curve: secp384r1 (0x0018)
                    Elliptic curve: secp256k1 (0x0016)
            Extension: SessionTicket TLS
                Type: SessionTicket TLS (0x0023)
                Length: 0
                Data (0 bytes)
            Extension: signature_algorithms
                Type: signature_algorithms (0x000d)
                Length: 32
                Signature Hash Algorithms Length: 30
                Signature Hash Algorithms (15 algorithms)
                    Signature Hash Algorithm: 0x0601
                        Signature Hash Algorithm Hash: SHA512 (6)
                        Signature Hash Algorithm Signature: RSA (1)
                    Signature Hash Algorithm: 0x0602
                        Signature Hash Algorithm Hash: SHA512 (6)
                        Signature Hash Algorithm Signature: DSA (2)
                    Signature Hash Algorithm: 0x0603
                        Signature Hash Algorithm Hash: SHA512 (6)
                        Signature Hash Algorithm Signature: ECDSA (3)
                    Signature Hash Algorithm: 0x0501
                        Signature Hash Algorithm Hash: SHA384 (5)
                        Signature Hash Algorithm Signature: RSA (1)
                    Signature Hash Algorithm: 0x0502
                        Signature Hash Algorithm Hash: SHA384 (5)
                        Signature Hash Algorithm Signature: DSA (2)
                    Signature Hash Algorithm: 0x0503
                        Signature Hash Algorithm Hash: SHA384 (5)
                        Signature Hash Algorithm Signature: ECDSA (3)
                    Signature Hash Algorithm: 0x0401
                        Signature Hash Algorithm Hash: SHA256 (4)
                        Signature Hash Algorithm Signature: RSA (1)
                    Signature Hash Algorithm: 0x0402
                        Signature Hash Algorithm Hash: SHA256 (4)
                        Signature Hash Algorithm Signature: DSA (2)
                    Signature Hash Algorithm: 0x0403
                        Signature Hash Algorithm Hash: SHA256 (4)
                        Signature Hash Algorithm Signature: ECDSA (3)
                    Signature Hash Algorithm: 0x0301
                        Signature Hash Algorithm Hash: SHA224 (3)
                        Signature Hash Algorithm Signature: RSA (1)
                    Signature Hash Algorithm: 0x0302
                        Signature Hash Algorithm Hash: SHA224 (3)
                        Signature Hash Algorithm Signature: DSA (2)
                    Signature Hash Algorithm: 0x0303
                        Signature Hash Algorithm Hash: SHA224 (3)
                        Signature Hash Algorithm Signature: ECDSA (3)
                    Signature Hash Algorithm: 0x0201
                        Signature Hash Algorithm Hash: SHA1 (2)
                        Signature Hash Algorithm Signature: RSA (1)
                    Signature Hash Algorithm: 0x0202
                        Signature Hash Algorithm Hash: SHA1 (2)
                        Signature Hash Algorithm Signature: DSA (2)
                    Signature Hash Algorithm: 0x0203
                        Signature Hash Algorithm Hash: SHA1 (2)
                        Signature Hash Algorithm Signature: ECDSA (3)
            Extension: Heartbeat
                Type: Heartbeat (0x000f)
                Length: 1
                Mode: Peer allowed to send requests (1)

Frame 8: 1271 bytes on wire (10168 bits), 1271 bytes captured (10168 bits) on interface 0
    Interface id: 0
    Encapsulation type: Ethernet (1)
    Arrival Time: Nov 23, 2017 02:47:29.440494267 JST
    [Time shift for this packet: 0.000000000 seconds]
    Epoch Time: 1511372849.440494267 seconds
    [Time delta from previous captured frame: 0.059737619 seconds]
    [Time delta from previous displayed frame: 0.059816798 seconds]
    [Time since reference or first frame: 0.062138868 seconds]
    Frame Number: 8
    Frame Length: 1271 bytes (10168 bits)
    Capture Length: 1271 bytes (10168 bits)
    [Frame is marked: False]
    [Frame is ignored: False]
    [Protocols in frame: eth:ip:tcp:ssl:pkcs-1:x509sat:x509sat:x509sat:x509sat:x509sat:x509sat:pkcs-1:pkcs-1]
Ethernet II, Src: 00:00:00_00:00:00 (00:00:00:00:00:00), Dst: 00:00:00_00:00:00 (00:00:00:00:00:00)
    Destination: 00:00:00_00:00:00 (00:00:00:00:00:00)
        Address: 00:00:00_00:00:00 (00:00:00:00:00:00)
        .... ..0. .... .... .... .... = LG bit: Globally unique address (factory default)
        .... ...0 .... .... .... .... = IG bit: Individual address (unicast)
    Source: 00:00:00_00:00:00 (00:00:00:00:00:00)
        Address: 00:00:00_00:00:00 (00:00:00:00:00:00)
        .... ..0. .... .... .... .... = LG bit: Globally unique address (factory default)
        .... ...0 .... .... .... .... = IG bit: Individual address (unicast)
    Type: IP (0x0800)
Internet Protocol Version 4, Src: 127.0.0.1 (127.0.0.1), Dst: 127.0.0.1 (127.0.0.1)
    Version: 4
    Header length: 20 bytes
    Differentiated Services Field: 0x00 (DSCP 0x00: Default; ECN: 0x00: Not-ECT (Not ECN-Capable Transport))
        0000 00.. = Differentiated Services Codepoint: Default (0x00)
        .... ..00 = Explicit Congestion Notification: Not-ECT (Not ECN-Capable Transport) (0x00)
    Total Length: 1257
    Identification: 0x71c0 (29120)
    Flags: 0x02 (Don't Fragment)
        0... .... = Reserved bit: Not set
        .1.. .... = Don't fragment: Set
        ..0. .... = More fragments: Not set
    Fragment offset: 0
    Time to live: 64
    Protocol: TCP (6)
    Header checksum: 0xc64c [validation disabled]
        [Good: False]
        [Bad: False]
    Source: 127.0.0.1 (127.0.0.1)
    Destination: 127.0.0.1 (127.0.0.1)
Transmission Control Protocol, Src Port: vop (4433), Dst Port: 45992 (45992), Seq: 1, Ack: 290, Len: 1205
    Source port: vop (4433)
    Destination port: 45992 (45992)
    [Stream index: 1]
    Sequence number: 1    (relative sequence number)
    [Next sequence number: 1206    (relative sequence number)]
    Acknowledgment number: 290    (relative ack number)
    Header length: 32 bytes
    Flags: 0x018 (PSH, ACK)
        000. .... .... = Reserved: Not set
        ...0 .... .... = Nonce: Not set
        .... 0... .... = Congestion Window Reduced (CWR): Not set
        .... .0.. .... = ECN-Echo: Not set
        .... ..0. .... = Urgent: Not set
        .... ...1 .... = Acknowledgment: Set
        .... .... 1... = Push: Set
        .... .... .0.. = Reset: Not set
        .... .... ..0. = Syn: Not set
        .... .... ...0 = Fin: Not set
    Window size value: 350
    [Calculated window size: 44800]
    [Window size scaling factor: 128]
    Checksum: 0x02de [validation disabled]
        [Good Checksum: False]
        [Bad Checksum: False]
    Options: (12 bytes), No-Operation (NOP), No-Operation (NOP), Timestamps
        No-Operation (NOP)
            Type: 1
                0... .... = Copy on fragmentation: No
                .00. .... = Class: Control (0)
                ...0 0001 = Number: No-Operation (NOP) (1)
        No-Operation (NOP)
            Type: 1
                0... .... = Copy on fragmentation: No
                .00. .... = Class: Control (0)
                ...0 0001 = Number: No-Operation (NOP) (1)
        Timestamps: TSval 7374032, TSecr 7373972
            Kind: Timestamp (8)
            Length: 10
            Timestamp value: 7374032
            Timestamp echo reply: 7373972
    [SEQ/ACK analysis]
        [Bytes in flight: 1205]
Secure Sockets Layer
    TLSv1.2 Record Layer: Handshake Protocol: Server Hello
        Content Type: Handshake (22)
        Version: TLS 1.2 (0x0303)
        Length: 66
        Handshake Protocol: Server Hello
            Handshake Type: Server Hello (2)
            Length: 62
            Version: TLS 1.2 (0x0303)
            Random
                gmt_unix_time: Mar  9, 1986 19:51:14.000000000 JST
                random_bytes: 715a37150c7058ab323b138a5d1e286a0b0f03c89ffcb5d4...
            Session ID Length: 0
            Cipher Suite: TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384 (0xc030)
            Compression Method: null (0)
            Extensions Length: 22
            Extension: renegotiation_info
                Type: renegotiation_info (0xff01)
                Length: 1
                Renegotiation Info extension
                    Renegotiation info extension length: 0
            Extension: ec_point_formats
                Type: ec_point_formats (0x000b)
                Length: 4
                EC point formats Length: 3
                Elliptic curves point formats (3)
                    EC point format: uncompressed (0)
                    EC point format: ansiX962_compressed_prime (1)
                    EC point format: ansiX962_compressed_char2 (2)
            Extension: SessionTicket TLS
                Type: SessionTicket TLS (0x0023)
                Length: 0
                Data (0 bytes)
            Extension: Heartbeat
                Type: Heartbeat (0x000f)
                Length: 1
                Mode: Peer allowed to send requests (1)
    TLSv1.2 Record Layer: Handshake Protocol: Certificate
        Content Type: Handshake (22)
        Version: TLS 1.2 (0x0303)
        Length: 782
        Handshake Protocol: Certificate
            Handshake Type: Certificate (11)
            Length: 778
            Certificates Length: 775
            Certificates (775 bytes)
                Certificate Length: 772
                Certificate (id-at-organizationName=Default Company Ltd,id-at-localityName=Default City,id-at-countryName=XX)
                    signedCertificate
                        serialNumber : 0x00db441c14d7b11e6c
                        signature (shaWithRSAEncryption)
                            Algorithm Id: 1.2.840.113549.1.1.5 (shaWithRSAEncryption)
                        issuer: rdnSequence (0)
                            rdnSequence: 3 items (id-at-organizationName=Default Company Ltd,id-at-localityName=Default City,id-at-countryName=XX)
                                RDNSequence item: 1 item (id-at-countryName=XX)
                                    RelativeDistinguishedName item (id-at-countryName=XX)
                                        Id: 2.5.4.6 (id-at-countryName)
                                        CountryName: XX
                                RDNSequence item: 1 item (id-at-localityName=Default City)
                                    RelativeDistinguishedName item (id-at-localityName=Default City)
                                        Id: 2.5.4.7 (id-at-localityName)
                                        DirectoryString: uTF8String (4)
                                            uTF8String: Default City
                                RDNSequence item: 1 item (id-at-organizationName=Default Company Ltd)
                                    RelativeDistinguishedName item (id-at-organizationName=Default Company Ltd)
                                        Id: 2.5.4.10 (id-at-organizationName)
                                        DirectoryString: uTF8String (4)
                                            uTF8String: Default Company Ltd
                        validity
                            notBefore: utcTime (0)
                                utcTime: 16-11-27 15:01:24 (UTC)
                            notAfter: utcTime (0)
                                utcTime: 26-11-25 15:01:24 (UTC)
                        subject: rdnSequence (0)
                            rdnSequence: 3 items (id-at-organizationName=Default Company Ltd,id-at-localityName=Default City,id-at-countryName=XX)
                                RDNSequence item: 1 item (id-at-countryName=XX)
                                    RelativeDistinguishedName item (id-at-countryName=XX)
                                        Id: 2.5.4.6 (id-at-countryName)
                                        CountryName: XX
                                RDNSequence item: 1 item (id-at-localityName=Default City)
                                    RelativeDistinguishedName item (id-at-localityName=Default City)
                                        Id: 2.5.4.7 (id-at-localityName)
                                        DirectoryString: uTF8String (4)
                                            uTF8String: Default City
                                RDNSequence item: 1 item (id-at-organizationName=Default Company Ltd)
                                    RelativeDistinguishedName item (id-at-organizationName=Default Company Ltd)
                                        Id: 2.5.4.10 (id-at-organizationName)
                                        DirectoryString: uTF8String (4)
                                            uTF8String: Default Company Ltd
                        subjectPublicKeyInfo
                            algorithm (rsaEncryption)
                                Algorithm Id: 1.2.840.113549.1.1.1 (rsaEncryption)
                            Padding: 0
                            subjectPublicKey: 3082010a0282010100d97f2fc0c17f5a41cd95b5651bbf0f...
                    algorithmIdentifier (shaWithRSAEncryption)
                        Algorithm Id: 1.2.840.113549.1.1.5 (shaWithRSAEncryption)
                    Padding: 0
                    encrypted: 5da0ee9d28d9a8740aff570dea2cb77e14cf63fa7bdada0d...
    TLSv1.2 Record Layer: Handshake Protocol: Server Key Exchange
        Content Type: Handshake (22)
        Version: TLS 1.2 (0x0303)
        Length: 333
        Handshake Protocol: Server Key Exchange
            Handshake Type: Server Key Exchange (12)
            Length: 329
            EC Diffie-Hellman Server Params
                curve_type: named_curve (0x03)
                named_curve: secp256r1 (0x0017)
                Pubkey Length: 65
                pubkey: 04fb9cf7ecd302437309429607a8104efa4c9eb4bb72a2ef...
                Signature Hash Algorithm: 0x0601
                    Signature Hash Algorithm Hash: SHA512 (6)
                    Signature Hash Algorithm Signature: RSA (1)
                Signature Length: 256
                signature: 12944e097b2a7d7896ae94ec276df67045c3e3ec08ef1e88...
    TLSv1.2 Record Layer: Handshake Protocol: Server Hello Done
        Content Type: Handshake (22)
        Version: TLS 1.2 (0x0303)
        Length: 4
        Handshake Protocol: Server Hello Done
            Handshake Type: Server Hello Done (14)
            Length: 0

Frame 10: 192 bytes on wire (1536 bits), 192 bytes captured (1536 bits) on interface 0
    Interface id: 0
    Encapsulation type: Ethernet (1)
    Arrival Time: Nov 23, 2017 02:47:29.441894244 JST
    [Time shift for this packet: 0.000000000 seconds]
    Epoch Time: 1511372849.441894244 seconds
    [Time delta from previous captured frame: 0.001322335 seconds]
    [Time delta from previous displayed frame: 0.001399977 seconds]
    [Time since reference or first frame: 0.063538845 seconds]
    Frame Number: 10
    Frame Length: 192 bytes (1536 bits)
    Capture Length: 192 bytes (1536 bits)
    [Frame is marked: False]
    [Frame is ignored: False]
    [Protocols in frame: eth:ip:tcp:ssl]
Ethernet II, Src: 00:00:00_00:00:00 (00:00:00:00:00:00), Dst: 00:00:00_00:00:00 (00:00:00:00:00:00)
    Destination: 00:00:00_00:00:00 (00:00:00:00:00:00)
        Address: 00:00:00_00:00:00 (00:00:00:00:00:00)
        .... ..0. .... .... .... .... = LG bit: Globally unique address (factory default)
        .... ...0 .... .... .... .... = IG bit: Individual address (unicast)
    Source: 00:00:00_00:00:00 (00:00:00:00:00:00)
        Address: 00:00:00_00:00:00 (00:00:00:00:00:00)
        .... ..0. .... .... .... .... = LG bit: Globally unique address (factory default)
        .... ...0 .... .... .... .... = IG bit: Individual address (unicast)
    Type: IP (0x0800)
Internet Protocol Version 4, Src: 127.0.0.1 (127.0.0.1), Dst: 127.0.0.1 (127.0.0.1)
    Version: 4
    Header length: 20 bytes
    Differentiated Services Field: 0x00 (DSCP 0x00: Default; ECN: 0x00: Not-ECT (Not ECN-Capable Transport))
        0000 00.. = Differentiated Services Codepoint: Default (0x00)
        .... ..00 = Explicit Congestion Notification: Not-ECT (Not ECN-Capable Transport) (0x00)
    Total Length: 178
    Identification: 0xa785 (42885)
    Flags: 0x02 (Don't Fragment)
        0... .... = Reserved bit: Not set
        .1.. .... = Don't fragment: Set
        ..0. .... = More fragments: Not set
    Fragment offset: 0
    Time to live: 64
    Protocol: TCP (6)
    Header checksum: 0x94be [validation disabled]
        [Good: False]
        [Bad: False]
    Source: 127.0.0.1 (127.0.0.1)
    Destination: 127.0.0.1 (127.0.0.1)
Transmission Control Protocol, Src Port: 45992 (45992), Dst Port: vop (4433), Seq: 290, Ack: 1206, Len: 126
    Source port: 45992 (45992)
    Destination port: vop (4433)
    [Stream index: 1]
    Sequence number: 290    (relative sequence number)
    [Next sequence number: 416    (relative sequence number)]
    Acknowledgment number: 1206    (relative ack number)
    Header length: 32 bytes
    Flags: 0x018 (PSH, ACK)
        000. .... .... = Reserved: Not set
        ...0 .... .... = Nonce: Not set
        .... 0... .... = Congestion Window Reduced (CWR): Not set
        .... .0.. .... = ECN-Echo: Not set
        .... ..0. .... = Urgent: Not set
        .... ...1 .... = Acknowledgment: Set
        .... .... 1... = Push: Set
        .... .... .0.. = Reset: Not set
        .... .... ..0. = Syn: Not set
        .... .... ...0 = Fin: Not set
    Window size value: 1365
    [Calculated window size: 174720]
    [Window size scaling factor: 128]
    Checksum: 0xfea6 [validation disabled]
        [Good Checksum: False]
        [Bad Checksum: False]
    Options: (12 bytes), No-Operation (NOP), No-Operation (NOP), Timestamps
        No-Operation (NOP)
            Type: 1
                0... .... = Copy on fragmentation: No
                .00. .... = Class: Control (0)
                ...0 0001 = Number: No-Operation (NOP) (1)
        No-Operation (NOP)
            Type: 1
                0... .... = Copy on fragmentation: No
                .00. .... = Class: Control (0)
                ...0 0001 = Number: No-Operation (NOP) (1)
        Timestamps: TSval 7374032, TSecr 7374032
            Kind: Timestamp (8)
            Length: 10
            Timestamp value: 7374032
            Timestamp echo reply: 7374032
    [SEQ/ACK analysis]
        [Bytes in flight: 126]
Secure Sockets Layer
    TLSv1.2 Record Layer: Handshake Protocol: Client Key Exchange
        Content Type: Handshake (22)
        Version: TLS 1.2 (0x0303)
        Length: 70
        Handshake Protocol: Client Key Exchange
            Handshake Type: Client Key Exchange (16)
            Length: 66
            EC Diffie-Hellman Client Params
                Pubkey Length: 65
                pubkey: 04c16700c65276b9a5f4dfa1d63c189e6933d7ea3764b8f8...
    TLSv1.2 Record Layer: Change Cipher Spec Protocol: Change Cipher Spec
        Content Type: Change Cipher Spec (20)
        Version: TLS 1.2 (0x0303)
        Length: 1
        Change Cipher Spec Message
    TLSv1.2 Record Layer: Handshake Protocol: Encrypted Handshake Message
        Content Type: Handshake (22)
        Version: TLS 1.2 (0x0303)
        Length: 40
        Handshake Protocol: Encrypted Handshake Message

Frame 12: 292 bytes on wire (2336 bits), 292 bytes captured (2336 bits) on interface 0
    Interface id: 0
    Encapsulation type: Ethernet (1)
    Arrival Time: Nov 23, 2017 02:47:29.446291888 JST
    [Time shift for this packet: 0.000000000 seconds]
    Epoch Time: 1511372849.446291888 seconds
    [Time delta from previous captured frame: 0.003709475 seconds]
    [Time delta from previous displayed frame: 0.004397644 seconds]
    [Time since reference or first frame: 0.067936489 seconds]
    Frame Number: 12
    Frame Length: 292 bytes (2336 bits)
    Capture Length: 292 bytes (2336 bits)
    [Frame is marked: False]
    [Frame is ignored: False]
    [Protocols in frame: eth:ip:tcp:ssl]
Ethernet II, Src: 00:00:00_00:00:00 (00:00:00:00:00:00), Dst: 00:00:00_00:00:00 (00:00:00:00:00:00)
    Destination: 00:00:00_00:00:00 (00:00:00:00:00:00)
        Address: 00:00:00_00:00:00 (00:00:00:00:00:00)
        .... ..0. .... .... .... .... = LG bit: Globally unique address (factory default)
        .... ...0 .... .... .... .... = IG bit: Individual address (unicast)
    Source: 00:00:00_00:00:00 (00:00:00:00:00:00)
        Address: 00:00:00_00:00:00 (00:00:00:00:00:00)
        .... ..0. .... .... .... .... = LG bit: Globally unique address (factory default)
        .... ...0 .... .... .... .... = IG bit: Individual address (unicast)
    Type: IP (0x0800)
Internet Protocol Version 4, Src: 127.0.0.1 (127.0.0.1), Dst: 127.0.0.1 (127.0.0.1)
    Version: 4
    Header length: 20 bytes
    Differentiated Services Field: 0x00 (DSCP 0x00: Default; ECN: 0x00: Not-ECT (Not ECN-Capable Transport))
        0000 00.. = Differentiated Services Codepoint: Default (0x00)
        .... ..00 = Explicit Congestion Notification: Not-ECT (Not ECN-Capable Transport) (0x00)
    Total Length: 278
    Identification: 0x71c2 (29122)
    Flags: 0x02 (Don't Fragment)
        0... .... = Reserved bit: Not set
        .1.. .... = Don't fragment: Set
        ..0. .... = More fragments: Not set
    Fragment offset: 0
    Time to live: 64
    Protocol: TCP (6)
    Header checksum: 0xca1d [validation disabled]
        [Good: False]
        [Bad: False]
    Source: 127.0.0.1 (127.0.0.1)
    Destination: 127.0.0.1 (127.0.0.1)
Transmission Control Protocol, Src Port: vop (4433), Dst Port: 45992 (45992), Seq: 1206, Ack: 416, Len: 226
    Source port: vop (4433)
    Destination port: 45992 (45992)
    [Stream index: 1]
    Sequence number: 1206    (relative sequence number)
    [Next sequence number: 1432    (relative sequence number)]
    Acknowledgment number: 416    (relative ack number)
    Header length: 32 bytes
    Flags: 0x018 (PSH, ACK)
        000. .... .... = Reserved: Not set
        ...0 .... .... = Nonce: Not set
        .... 0... .... = Congestion Window Reduced (CWR): Not set
        .... .0.. .... = ECN-Echo: Not set
        .... ..0. .... = Urgent: Not set
        .... ...1 .... = Acknowledgment: Set
        .... .... 1... = Push: Set
        .... .... .0.. = Reset: Not set
        .... .... ..0. = Syn: Not set
        .... .... ...0 = Fin: Not set
    Window size value: 350
    [Calculated window size: 44800]
    [Window size scaling factor: 128]
    Checksum: 0xff0a [validation disabled]
        [Good Checksum: False]
        [Bad Checksum: False]
    Options: (12 bytes), No-Operation (NOP), No-Operation (NOP), Timestamps
        No-Operation (NOP)
            Type: 1
                0... .... = Copy on fragmentation: No
                .00. .... = Class: Control (0)
                ...0 0001 = Number: No-Operation (NOP) (1)
        No-Operation (NOP)
            Type: 1
                0... .... = Copy on fragmentation: No
                .00. .... = Class: Control (0)
                ...0 0001 = Number: No-Operation (NOP) (1)
        Timestamps: TSval 7374035, TSecr 7374032
            Kind: Timestamp (8)
            Length: 10
            Timestamp value: 7374035
            Timestamp echo reply: 7374032
    [SEQ/ACK analysis]
        [Bytes in flight: 226]
Secure Sockets Layer
    TLSv1.2 Record Layer: Handshake Protocol: New Session Ticket
        Content Type: Handshake (22)
        Version: TLS 1.2 (0x0303)
        Length: 170
        Handshake Protocol: New Session Ticket
            Handshake Type: New Session Ticket (4)
            Length: 166
            TLS Session Ticket
                Session Ticket Lifetime Hint: 300
                Session Ticket Length: 160
                Session Ticket: 80cf708d161123437ef8fda3d59ef6b102353e3f4c513e07...
    TLSv1.2 Record Layer: Change Cipher Spec Protocol: Change Cipher Spec
        Content Type: Change Cipher Spec (20)
        Version: TLS 1.2 (0x0303)
        Length: 1
        Change Cipher Spec Message
    TLSv1.2 Record Layer: Handshake Protocol: Encrypted Handshake Message
        Content Type: Handshake (22)
        Version: TLS 1.2 (0x0303)
        Length: 40
        Handshake Protocol: Encrypted Handshake Message

Frame 13: 100 bytes on wire (800 bits), 100 bytes captured (800 bits) on interface 0
    Interface id: 0
    Encapsulation type: Ethernet (1)
    Arrival Time: Nov 23, 2017 02:47:29.446352528 JST
    [Time shift for this packet: 0.000000000 seconds]
    Epoch Time: 1511372849.446352528 seconds
    [Time delta from previous captured frame: 0.000060640 seconds]
    [Time delta from previous displayed frame: 0.000060640 seconds]
    [Time since reference or first frame: 0.067997129 seconds]
    Frame Number: 13
    Frame Length: 100 bytes (800 bits)
    Capture Length: 100 bytes (800 bits)
    [Frame is marked: False]
    [Frame is ignored: False]
    [Protocols in frame: eth:ip:tcp:ssl]
Ethernet II, Src: 00:00:00_00:00:00 (00:00:00:00:00:00), Dst: 00:00:00_00:00:00 (00:00:00:00:00:00)
    Destination: 00:00:00_00:00:00 (00:00:00:00:00:00)
        Address: 00:00:00_00:00:00 (00:00:00:00:00:00)
        .... ..0. .... .... .... .... = LG bit: Globally unique address (factory default)
        .... ...0 .... .... .... .... = IG bit: Individual address (unicast)
    Source: 00:00:00_00:00:00 (00:00:00:00:00:00)
        Address: 00:00:00_00:00:00 (00:00:00:00:00:00)
        .... ..0. .... .... .... .... = LG bit: Globally unique address (factory default)
        .... ...0 .... .... .... .... = IG bit: Individual address (unicast)
    Type: IP (0x0800)
Internet Protocol Version 4, Src: 127.0.0.1 (127.0.0.1), Dst: 127.0.0.1 (127.0.0.1)
    Version: 4
    Header length: 20 bytes
    Differentiated Services Field: 0x00 (DSCP 0x00: Default; ECN: 0x00: Not-ECT (Not ECN-Capable Transport))
        0000 00.. = Differentiated Services Codepoint: Default (0x00)
        .... ..00 = Explicit Congestion Notification: Not-ECT (Not ECN-Capable Transport) (0x00)
    Total Length: 86
    Identification: 0x71c3 (29123)
    Flags: 0x02 (Don't Fragment)
        0... .... = Reserved bit: Not set
        .1.. .... = Don't fragment: Set
        ..0. .... = More fragments: Not set
    Fragment offset: 0
    Time to live: 64
    Protocol: TCP (6)
    Header checksum: 0xcadc [validation disabled]
        [Good: False]
        [Bad: False]
    Source: 127.0.0.1 (127.0.0.1)
    Destination: 127.0.0.1 (127.0.0.1)
Transmission Control Protocol, Src Port: vop (4433), Dst Port: 45992 (45992), Seq: 1432, Ack: 416, Len: 34
    Source port: vop (4433)
    Destination port: 45992 (45992)
    [Stream index: 1]
    Sequence number: 1432    (relative sequence number)
    [Next sequence number: 1466    (relative sequence number)]
    Acknowledgment number: 416    (relative ack number)
    Header length: 32 bytes
    Flags: 0x019 (FIN, PSH, ACK)
        000. .... .... = Reserved: Not set
        ...0 .... .... = Nonce: Not set
        .... 0... .... = Congestion Window Reduced (CWR): Not set
        .... .0.. .... = ECN-Echo: Not set
        .... ..0. .... = Urgent: Not set
        .... ...1 .... = Acknowledgment: Set
        .... .... 1... = Push: Set
        .... .... .0.. = Reset: Not set
        .... .... ..0. = Syn: Not set
        .... .... ...1 = Fin: Set
            [Expert Info (Chat/Sequence): Connection finish (FIN)]
                [Message: Connection finish (FIN)]
                [Severity level: Chat]
                [Group: Sequence]
    Window size value: 350
    [Calculated window size: 44800]
    [Window size scaling factor: 128]
    Checksum: 0xfe4a [validation disabled]
        [Good Checksum: False]
        [Bad Checksum: False]
    Options: (12 bytes), No-Operation (NOP), No-Operation (NOP), Timestamps
        No-Operation (NOP)
            Type: 1
                0... .... = Copy on fragmentation: No
                .00. .... = Class: Control (0)
                ...0 0001 = Number: No-Operation (NOP) (1)
        No-Operation (NOP)
            Type: 1
                0... .... = Copy on fragmentation: No
                .00. .... = Class: Control (0)
                ...0 0001 = Number: No-Operation (NOP) (1)
        Timestamps: TSval 7374035, TSecr 7374032
            Kind: Timestamp (8)
            Length: 10
            Timestamp value: 7374035
            Timestamp echo reply: 7374032
    [SEQ/ACK analysis]
        [Bytes in flight: 261]
Secure Sockets Layer
    TLSv1.2 Record Layer: Application Data Protocol: Application Data
        Content Type: Application Data (23)
        Version: TLS 1.2 (0x0303)
        Length: 29
        Encrypted Application Data: 28e55c90589588c95e8f2a922ac6dc8551e1f4efc4d0d36b...

Frame 15: 97 bytes on wire (776 bits), 97 bytes captured (776 bits) on interface 0
    Interface id: 0
    Encapsulation type: Ethernet (1)
    Arrival Time: Nov 23, 2017 02:47:29.448074263 JST
    [Time shift for this packet: 0.000000000 seconds]
    Epoch Time: 1511372849.448074263 seconds
    [Time delta from previous captured frame: 0.000107619 seconds]
    [Time delta from previous displayed frame: 0.001721735 seconds]
    [Time since reference or first frame: 0.069718864 seconds]
    Frame Number: 15
    Frame Length: 97 bytes (776 bits)
    Capture Length: 97 bytes (776 bits)
    [Frame is marked: False]
    [Frame is ignored: False]
    [Protocols in frame: eth:ip:tcp:ssl]
Ethernet II, Src: 00:00:00_00:00:00 (00:00:00:00:00:00), Dst: 00:00:00_00:00:00 (00:00:00:00:00:00)
    Destination: 00:00:00_00:00:00 (00:00:00:00:00:00)
        Address: 00:00:00_00:00:00 (00:00:00:00:00:00)
        .... ..0. .... .... .... .... = LG bit: Globally unique address (factory default)
        .... ...0 .... .... .... .... = IG bit: Individual address (unicast)
    Source: 00:00:00_00:00:00 (00:00:00:00:00:00)
        Address: 00:00:00_00:00:00 (00:00:00:00:00:00)
        .... ..0. .... .... .... .... = LG bit: Globally unique address (factory default)
        .... ...0 .... .... .... .... = IG bit: Individual address (unicast)
    Type: IP (0x0800)
Internet Protocol Version 4, Src: 127.0.0.1 (127.0.0.1), Dst: 127.0.0.1 (127.0.0.1)
    Version: 4
    Header length: 20 bytes
    Differentiated Services Field: 0x00 (DSCP 0x00: Default; ECN: 0x00: Not-ECT (Not ECN-Capable Transport))
        0000 00.. = Differentiated Services Codepoint: Default (0x00)
        .... ..00 = Explicit Congestion Notification: Not-ECT (Not ECN-Capable Transport) (0x00)
    Total Length: 83
    Identification: 0xa787 (42887)
    Flags: 0x02 (Don't Fragment)
        0... .... = Reserved bit: Not set
        .1.. .... = Don't fragment: Set
        ..0. .... = More fragments: Not set
    Fragment offset: 0
    Time to live: 64
    Protocol: TCP (6)
    Header checksum: 0x951b [validation disabled]
        [Good: False]
        [Bad: False]
    Source: 127.0.0.1 (127.0.0.1)
    Destination: 127.0.0.1 (127.0.0.1)
Transmission Control Protocol, Src Port: 45992 (45992), Dst Port: vop (4433), Seq: 416, Ack: 1467, Len: 31
    Source port: 45992 (45992)
    Destination port: vop (4433)
    [Stream index: 1]
    Sequence number: 416    (relative sequence number)
    [Next sequence number: 447    (relative sequence number)]
    Acknowledgment number: 1467    (relative ack number)
    Header length: 32 bytes
    Flags: 0x018 (PSH, ACK)
        000. .... .... = Reserved: Not set
        ...0 .... .... = Nonce: Not set
        .... 0... .... = Congestion Window Reduced (CWR): Not set
        .... .0.. .... = ECN-Echo: Not set
        .... ..0. .... = Urgent: Not set
        .... ...1 .... = Acknowledgment: Set
        .... .... 1... = Push: Set
        .... .... .0.. = Reset: Not set
        .... .... ..0. = Syn: Not set
        .... .... ...0 = Fin: Not set
    Window size value: 1384
    [Calculated window size: 177152]
    [Window size scaling factor: 128]
    Checksum: 0xfe47 [validation disabled]
        [Good Checksum: False]
        [Bad Checksum: False]
    Options: (12 bytes), No-Operation (NOP), No-Operation (NOP), Timestamps
        No-Operation (NOP)
            Type: 1
                0... .... = Copy on fragmentation: No
                .00. .... = Class: Control (0)
                ...0 0001 = Number: No-Operation (NOP) (1)
        No-Operation (NOP)
            Type: 1
                0... .... = Copy on fragmentation: No
                .00. .... = Class: Control (0)
                ...0 0001 = Number: No-Operation (NOP) (1)
        Timestamps: TSval 7374039, TSecr 7374035
            Kind: Timestamp (8)
            Length: 10
            Timestamp value: 7374039
            Timestamp echo reply: 7374035
    [SEQ/ACK analysis]
        [Bytes in flight: 31]
Secure Sockets Layer
    TLSv1.2 Record Layer: Encrypted Alert
        Content Type: Alert (21)
        Version: TLS 1.2 (0x0303)
        Length: 26
        Alert Message: Encrypted Alert
```


