# 概要
役に立つopensslコマンドについてこちらに添付しておく

# 詳細

### メッセージの中身まで詳細に表示したい(-trace) TLS1.3
```
$ openssl s_client -connect www.yahoo.co.jp:443 -trace 
Connecting to 183.79.249.124
CONNECTED(00000005)
Sent TLS Record
Header:
  Version = TLS 1.0 (0x301)
  Content Type = Handshake (22)
  Length = 321
    ClientHello, Length=317
      client_version=0x303 (TLS 1.2)
      Random:
        gmt_unix_time=0x2DE64C11
        random_bytes (len=28): FA2094D4DEF7DDA1473F33D34A86CA026D9A019E019E5D1CC4D98EA8
      session_id (len=32): B156EB601A82AFF01313009BCCB8D5830771B90A036B04F5080E1ED8DDC2E4FD
      cipher_suites (len=60)
        {0x13, 0x02} TLS_AES_256_GCM_SHA384
        {0x13, 0x03} TLS_CHACHA20_POLY1305_SHA256
        {0x13, 0x01} TLS_AES_128_GCM_SHA256
        {0xC0, 0x2C} TLS_ECDHE_ECDSA_WITH_AES_256_GCM_SHA384
        {0xC0, 0x30} TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384
        {0x00, 0x9F} TLS_DHE_RSA_WITH_AES_256_GCM_SHA384
        {0xCC, 0xA9} TLS_ECDHE_ECDSA_WITH_CHACHA20_POLY1305_SHA256
        {0xCC, 0xA8} TLS_ECDHE_RSA_WITH_CHACHA20_POLY1305_SHA256
        {0xCC, 0xAA} TLS_DHE_RSA_WITH_CHACHA20_POLY1305_SHA256
        {0xC0, 0x2B} TLS_ECDHE_ECDSA_WITH_AES_128_GCM_SHA256
        {0xC0, 0x2F} TLS_ECDHE_RSA_WITH_AES_128_GCM_SHA256
        {0x00, 0x9E} TLS_DHE_RSA_WITH_AES_128_GCM_SHA256
        {0xC0, 0x24} TLS_ECDHE_ECDSA_WITH_AES_256_CBC_SHA384
        {0xC0, 0x28} TLS_ECDHE_RSA_WITH_AES_256_CBC_SHA384
        {0x00, 0x6B} TLS_DHE_RSA_WITH_AES_256_CBC_SHA256
        {0xC0, 0x23} TLS_ECDHE_ECDSA_WITH_AES_128_CBC_SHA256
        {0xC0, 0x27} TLS_ECDHE_RSA_WITH_AES_128_CBC_SHA256
        {0x00, 0x67} TLS_DHE_RSA_WITH_AES_128_CBC_SHA256
        {0xC0, 0x0A} TLS_ECDHE_ECDSA_WITH_AES_256_CBC_SHA
        {0xC0, 0x14} TLS_ECDHE_RSA_WITH_AES_256_CBC_SHA
        {0x00, 0x39} TLS_DHE_RSA_WITH_AES_256_CBC_SHA
        {0xC0, 0x09} TLS_ECDHE_ECDSA_WITH_AES_128_CBC_SHA
        {0xC0, 0x13} TLS_ECDHE_RSA_WITH_AES_128_CBC_SHA
        {0x00, 0x33} TLS_DHE_RSA_WITH_AES_128_CBC_SHA
        {0x00, 0x9D} TLS_RSA_WITH_AES_256_GCM_SHA384
        {0x00, 0x9C} TLS_RSA_WITH_AES_128_GCM_SHA256
        {0x00, 0x3D} TLS_RSA_WITH_AES_256_CBC_SHA256
        {0x00, 0x3C} TLS_RSA_WITH_AES_128_CBC_SHA256
        {0x00, 0x35} TLS_RSA_WITH_AES_256_CBC_SHA
        {0x00, 0x2F} TLS_RSA_WITH_AES_128_CBC_SHA
      compression_methods (len=1)
        No Compression (0x00)
      extensions, length = 184
        extension_type=renegotiate(65281), length=1
            <EMPTY>
        extension_type=server_name(0), length=20
          0000 - 00 12 00 00 0f 77 77 77-2e 79 61 68 6f 6f 2e   .....www.yahoo.
          000f - 63 6f 2e 6a 70                                 co.jp
        extension_type=ec_point_formats(11), length=4
          uncompressed (0)
          ansiX962_compressed_prime (1)
          ansiX962_compressed_char2 (2)
        extension_type=supported_groups(10), length=22
          ecdh_x25519 (29)
          secp256r1 (P-256) (23)
          ecdh_x448 (30)
          secp521r1 (P-521) (25)
          secp384r1 (P-384) (24)
          ffdhe2048 (256)
          ffdhe3072 (257)
          ffdhe4096 (258)
          ffdhe6144 (259)
          ffdhe8192 (260)
        extension_type=session_ticket(35), length=0
        extension_type=encrypt_then_mac(22), length=0
        extension_type=extended_master_secret(23), length=0
        extension_type=signature_algorithms(13), length=48
          ecdsa_secp256r1_sha256 (0x0403)
          ecdsa_secp384r1_sha384 (0x0503)
          ecdsa_secp521r1_sha512 (0x0603)
          ed25519 (0x0807)
          ed448 (0x0808)
          ecdsa_brainpoolP256r1_sha256 (0x081a)
          ecdsa_brainpoolP384r1_sha384 (0x081b)
          ecdsa_brainpoolP512r1_sha512 (0x081c)
          rsa_pss_pss_sha256 (0x0809)
          rsa_pss_pss_sha384 (0x080a)
          rsa_pss_pss_sha512 (0x080b)
          rsa_pss_rsae_sha256 (0x0804)
          rsa_pss_rsae_sha384 (0x0805)
          rsa_pss_rsae_sha512 (0x0806)
          rsa_pkcs1_sha256 (0x0401)
          rsa_pkcs1_sha384 (0x0501)
          rsa_pkcs1_sha512 (0x0601)
          ecdsa_sha224 (0x0303)
          rsa_pkcs1_sha224 (0x0301)
          dsa_sha224 (0x0302)
          dsa_sha256 (0x0402)
          dsa_sha384 (0x0502)
          dsa_sha512 (0x0602)
        extension_type=supported_versions(43), length=5
          TLS 1.3 (772)
          TLS 1.2 (771)
        extension_type=psk_key_exchange_modes(45), length=2
          psk_dhe_ke (1)
        extension_type=key_share(51), length=38
            NamedGroup: ecdh_x25519 (29)
            key_exchange:  (len=32): C250E935F6BC0992CE3CAB80D328D9823EDD8C63FF2AFBDB99A88DB946A6ED78

Received TLS Record
Header:
  Version = TLS 1.2 (0x303)
  Content Type = Handshake (22)
  Length = 122
    ServerHello, Length=118
      server_version=0x303 (TLS 1.2)
      Random:
        gmt_unix_time=0x6E2BD98F
        random_bytes (len=28): 80235214F9221EFEDCDF401C3591D84A30C742570B47C601F5A01155
      session_id (len=32): B156EB601A82AFF01313009BCCB8D5830771B90A036B04F5080E1ED8DDC2E4FD
      cipher_suite {0x13, 0x01} TLS_AES_128_GCM_SHA256
      compression_method: No Compression (0x00)
      extensions, length = 46
        extension_type=supported_versions(43), length=2
            TLS 1.3 (772)
        extension_type=key_share(51), length=36
            NamedGroup: ecdh_x25519 (29)
            key_exchange:  (len=32): C3AE6C9FA2C9731672A880FE56759230CCEB745BBEF6730624F29EC573CB375C

Received TLS Record
Header:
  Version = TLS 1.2 (0x303)
  Content Type = ChangeCipherSpec (20)
  Length = 1
    change_cipher_spec (1)

Received TLS Record
Header:
  Version = TLS 1.2 (0x303)
  Content Type = ApplicationData (23)
  Length = 27
  Inner Content Type = Handshake (22)
    EncryptedExtensions, Length=6
      extensions, length = 4
        extension_type=server_name(0), length=0

Received TLS Record
Header:
  Version = TLS 1.2 (0x303)
  Content Type = ApplicationData (23)
  Length = 5155
  Inner Content Type = Handshake (22)
    Certificate, Length=5134
      context (len=0): 
      certificate_list, length=5130
        ASN.1Cert, length=3837
------details-----
Certificate:
    Data:
        Version: 3 (0x2)
        Serial Number:
            57:1a:fe:8a:65:74:c4:af:2b:ce:69:77:e7:e9:8e:ad:0b:0c:9d:ae
        Signature Algorithm: sha256WithRSAEncryption
        Issuer: C = JP, O = "Cybertrust Japan Co., Ltd.", CN = Cybertrust Japan SureServer CA G4
        Validity
            Not Before: Apr 15 07:20:27 2025 GMT
            Not After : May 14 14:59:00 2026 GMT
        Subject: C = JP, ST = Tokyo, L = Chiyoda-ku, O = LY Corporation, CN = edge01.yahoo.co.jp
        Subject Public Key Info:
            Public Key Algorithm: rsaEncryption
                Public-Key: (2048 bit)
                Modulus:
                    00:d3:77:fe:92:fb:a1:ab:84:0d:dd:eb:ba:57:8d:
                    8c:b8:01:44:78:a5:6b:db:22:6f:d4:88:dd:70:13:
                    a6:26:d8:b9:9c:4b:55:d6:d1:f4:99:59:5b:70:6c:
                    00:02:86:c8:09:5b:4b:6a:13:64:8b:e4:83:21:c3:
                    de:62:2b:37:55:38:71:74:16:97:42:11:ba:87:03:
                    b4:80:56:4d:6c:2b:50:f6:ea:a9:39:1d:4b:0b:b3:
                    29:73:e7:0a:35:f4:1d:ba:bf:40:5c:77:59:2d:8f:
                    05:8b:2c:c3:35:59:dc:83:6c:28:85:21:89:cc:ef:
                    08:41:fd:85:9b:f5:b4:cb:79:a2:52:49:16:2b:52:
                    e9:73:e3:57:55:c8:c6:a5:ce:05:b7:c4:04:75:6a:
                    e8:da:78:b7:48:38:8e:bd:f6:18:d2:f1:27:78:b6:
                    8e:b2:db:87:99:66:6e:fc:65:b8:ec:65:ae:a1:9e:
                    25:3d:bd:65:d3:aa:5f:ba:2e:0a:2e:8b:d4:90:5a:
                    03:ec:3f:e1:a9:41:ea:36:ef:91:6b:1d:0f:9d:d1:
                    df:36:57:00:af:9e:9f:62:74:ed:8e:f2:f4:c5:9e:
                    dd:f4:35:b8:64:0d:f4:05:4b:e4:e7:da:5d:3f:c8:
                    3c:f3:5c:c1:c9:67:9a:69:2f:98:e5:88:7e:28:2c:
                    98:bf
                Exponent: 65537 (0x10001)
        X509v3 extensions:
            X509v3 Basic Constraints: critical
                CA:FALSE
            X509v3 Certificate Policies: 
                Policy: 2.23.140.1.2.2
                Policy: 1.2.392.200081.1.23.1
                  CPS: https://www.cybertrust.ne.jp/ssl/repository/index.html
            X509v3 Subject Alternative Name: 
                DNS:edge01.yahoo.co.jp, DNS:*.yahoo.co.jp, DNS:*.yahooapis.jp, DNS:*.ane.yahoo.co.jp, DNS:*.auctions.yahoo.co.jp, DNS:*.auctions.yahooapis.jp, DNS:*.box.yahooapis.jp, DNS:*.bspace.jp, DNS:*.bylines.news.yahoo.co.jp, DNS:*.c.yimg.jp, DNS:*.carnavi.yahooapis.jp, DNS:*.carview.co.jp, DNS:*.carview.yahoo.co.jp, DNS:*.chiebukuro.yahoo.co.jp, DNS:*.clorder.yahoo.co.jp, DNS:*.cvw.jp, DNS:*.digitalguide.jp, DNS:*.east.edge.storage-yahoo.jp, DNS:*.east.edge.storage-yahoobox.jp, DNS:*.edge.storage-yahoo.jp, DNS:*.edit.yahooapis.jp, DNS:*.finance.yahoo.co.jp, DNS:*.geocities.jp, DNS:*.global.edge.storage-yahoo.jp, DNS:*.gyao.yahoo.co.jp, DNS:*.jobcatalog.yahoo.co.jp, DNS:*.listing.yahoo.co.jp, DNS:*.loco.yahoo.co.jp, DNS:*.lycorp.co.jp, DNS:*.mail.yahoo.co.jp, DNS:*.marketing.yahoo.co.jp, DNS:*.mkcloud-api.carview.co.jp, DNS:*.mkimg.carview.co.jp, DNS:*.ms.yahoo.co.jp, DNS:*.lycorp-security.jp, DNS:*.news.yahoo.co.jp, DNS:*.news.yahooapis.jp, DNS:*.order.yahoo.co.jp, DNS:*.points.yahoo.co.jp, DNS:*.psi.yahoo.co.jp, DNS:*.push.yahooapis.jp, DNS:activity.travel.yahoo-net.jp, DNS:*.shopping.c.yimg.jp, DNS:*.shopping.srv.yimg.jp, DNS:*.shopping.yahoo.co.jp, DNS:*.shopping.yahooapis.jp, DNS:*.snsimg.carview.co.jp, DNS:*.store.yahoo.co.jp, DNS:*.travel.yahoo.co.jp, DNS:*.wallet.yahoo.co.jp, DNS:*.wallet.yahooapis.jp, DNS:*.webhosting.yahoo.co.jp, DNS:*.west.edge.storage-yahoo.jp, DNS:*.west.edge.storage-yahoobox.jp, DNS:*.xml.listing.yahoo.co.jp, DNS:*.yahoo-help.jp, DNS:*.yahoo-labs.jp, DNS:*.yahoo-net.jp, DNS:*.yahoo.jp, DNS:*.yahoobox.jp, DNS:*.yimg.jp, DNS:*.yjtag.jp, DNS:*.yjtag.yahoo.co.jp, DNS:*.ys-insurance.co.jp, DNS:*.search.yahooapis.jp, DNS:add.dir.yahoo.co.jp, DNS:api.y.clorder.yahoo.co.jp, DNS:arc.help.yahoo.co.jp, DNS:biztx.points.yahooapis.jp, DNS:carview.co.jp, DNS:cgi2.r-agent.yahoo.co.jp, DNS:cksync.pdsp.yahoo.co.jp, DNS:cm.froma.yahoo.co.jp, DNS:compass.ymobile.yahoo.co.jp, DNS:custom.search.yahoo.co.jp, DNS:e.developer.yahoo.co.jp, DNS:forms.business.yahoo.co.jp, DNS:frame.games.yahoo.co.jp, DNS:hrm.grmtrez.yahoo.co.jp, DNS:im.ov.yahoo.co.jp, DNS:info.hatalike.yahoo.co.jp, DNS:movie.chocotle.yahoo.co.jp, DNS:online.security.yahoo.co.jp, DNS:poiedit.map.yahoo.co.jp, DNS:portal.yadui.business.yahoo.co.jp, DNS:ssl-tools.kainavi.search.yahoo.co.jp, DNS:ssl.api.olp.yahooapis.jp, DNS:ssl.map.srv.yimg.jp, DNS:www.bosaiguide.jp, DNS:www.lohaco.yahoo.co.jp, DNS:www.search311.jp, DNS:www.sp-hinan.jp, DNS:www.techbasevn.com, DNS:yahoo.co.jp, DNS:yahoo.jp, DNS:yj.pn, DNS:yjtag.jp
            Authority Information Access: 
                OCSP - URI:http://ssocsp.cybertrust.ne.jp/OcspServer
                CA Issuers - URI:http://crl.cybertrust.ne.jp/SureServer/ovcag4/ovcag4.crt
            X509v3 Key Usage: critical
                Digital Signature, Key Encipherment
            X509v3 Extended Key Usage: 
                TLS Web Server Authentication, TLS Web Client Authentication
            X509v3 Authority Key Identifier: 
                62:A7:D2:DA:DE:85:B6:92:F1:85:BC:F6:E8:95:9D:75:A0:FA:4E:1F
            X509v3 CRL Distribution Points: 
                Full Name:
                  URI:http://crl.cybertrust.ne.jp/SureServer/ovcag4/cdp.crl

            X509v3 Subject Key Identifier: 
                7C:AA:2D:DA:E1:C6:26:CD:78:B6:B8:BC:50:E4:87:35:43:7E:D4:21
            CT Precertificate SCTs: 
                Signed Certificate Timestamp:
                    Version   : v1 (0x0)
                    Log ID    : 0E:57:94:BC:F3:AE:A9:3E:33:1B:2C:99:07:B3:F7:90:
                                DF:9B:C2:3D:71:32:25:DD:21:A9:25:AC:61:C5:4E:21
                    Timestamp : Apr 15 07:43:33.244 2025 GMT
                    Extensions: none
                    Signature : ecdsa-with-SHA256
                                30:45:02:21:00:A2:CB:CB:3D:8E:F1:12:A4:C5:6D:86:
                                8C:91:70:68:07:28:C0:33:07:0E:4A:7F:83:EF:27:97:
                                64:02:30:3E:A3:02:20:46:E8:82:A7:B5:B0:8E:1C:F4:
                                03:F4:3D:9C:90:5F:6F:45:CC:1F:50:56:35:20:B2:A6:
                                A0:5D:63:5A:CB:17:D6
                Signed Certificate Timestamp:
                    Version   : v1 (0x0)
                    Log ID    : 96:97:64:BF:55:58:97:AD:F7:43:87:68:37:08:42:77:
                                E9:F0:3A:D5:F6:A4:F3:36:6E:46:A4:3F:0F:CA:A9:C6
                    Timestamp : Apr 15 07:43:35.013 2025 GMT
                    Extensions: none
                    Signature : ecdsa-with-SHA256
                                30:44:02:20:4A:19:AA:29:CE:35:18:74:13:7F:47:1E:
                                2D:7B:68:7F:4D:34:DB:25:48:66:A4:33:8B:92:3B:CF:
                                6A:BD:54:84:02:20:14:30:38:DA:49:07:37:C3:8A:08:
                                1B:C5:22:94:A3:54:87:3A:FB:D8:94:2D:38:8F:4F:82:
                                01:1A:87:E2:7E:B8
                Signed Certificate Timestamp:
                    Version   : v1 (0x0)
                    Log ID    : 19:86:D4:C7:28:AA:6F:FE:BA:03:6F:78:2A:4D:01:91:
                                AA:CE:2D:72:31:0F:AE:CE:5D:70:41:2D:25:4C:C7:D4
                    Timestamp : Apr 15 07:43:36.309 2025 GMT
                    Extensions: none
                    Signature : ecdsa-with-SHA256
                                30:45:02:20:37:FB:B2:31:0E:0F:72:E1:D1:BA:25:AD:
                                68:F0:0B:E4:05:CB:1B:2E:DE:7D:52:13:84:05:9E:E6:
                                5D:BF:B1:07:02:21:00:DA:1E:E3:2A:19:4B:75:F4:44:
                                87:94:24:21:ED:C6:0B:F2:56:3E:77:07:1D:D4:F6:A7:
                                7C:52:D9:FA:21:2F:8A
    Signature Algorithm: sha256WithRSAEncryption
    Signature Value:
        7f:32:f1:c3:7a:d5:a6:7a:82:2a:73:e7:50:cc:4b:ab:b5:03:
        5d:e2:0f:c2:9e:0e:27:f9:87:fe:8f:df:94:9e:bb:0e:df:8a:
        47:3d:fc:be:e2:47:cc:6a:d3:da:02:e0:71:1a:ff:dc:2c:06:
        1e:01:61:3c:b5:92:51:ce:7e:bb:0e:10:4a:bc:69:9a:6a:a4:
        33:88:a8:93:d9:00:67:d2:18:bd:3e:22:de:b7:b1:68:30:ba:
        84:7c:3e:56:ee:6e:f2:1b:1f:21:52:5c:29:c7:0a:70:21:fd:
        b4:74:e7:70:8c:1c:cd:1e:5b:a4:65:57:f8:53:fc:8c:87:5b:
        7e:85:b1:df:05:00:08:5e:c6:26:84:cf:78:15:e1:3b:8f:61:
        0d:af:6c:73:7c:9c:a2:ca:fa:95:bd:5d:84:b9:41:17:ed:7f:
        9f:0d:5f:cb:d6:66:ea:75:b1:34:ea:74:aa:80:89:f2:8e:f6:
        e1:76:eb:d6:07:ff:9e:f4:75:ef:13:02:6f:1e:b5:61:eb:c5:
        a7:f3:cb:d8:31:e4:e4:ca:c6:79:a3:af:99:a3:cd:c1:27:4f:
        bf:8d:51:48:21:21:29:33:f4:33:76:a1:77:d7:ce:32:f4:81:
        f2:93:a4:0a:5b:21:b5:15:7b:f8:eb:2b:53:2d:aa:e0:1a:c5:
        0d:e1:35:82
-----BEGIN CERTIFICATE-----
MIIO+TCCDeGgAwIBAgIUVxr+imV0xK8rzml35+mOrQsMna4wDQYJKoZIhvcNAQEL
BQAwXjELMAkGA1UEBhMCSlAxIzAhBgNVBAoTGkN5YmVydHJ1c3QgSmFwYW4gQ28u
LCBMdGQuMSowKAYDVQQDEyFDeWJlcnRydXN0IEphcGFuIFN1cmVTZXJ2ZXIgQ0Eg
RzQwHhcNMjUwNDE1MDcyMDI3WhcNMjYwNTE0MTQ1OTAwWjBoMQswCQYDVQQGEwJK
UDEOMAwGA1UECBMFVG9reW8xEzARBgNVBAcTCkNoaXlvZGEta3UxFzAVBgNVBAoT
DkxZIENvcnBvcmF0aW9uMRswGQYDVQQDExJlZGdlMDEueWFob28uY28uanAwggEi
MA0GCSqGSIb3DQEBAQUAA4IBDwAwggEKAoIBAQDTd/6S+6GrhA3d67pXjYy4AUR4
pWvbIm/UiN1wE6Ym2LmcS1XW0fSZWVtwbAAChsgJW0tqE2SL5IMhw95iKzdVOHF0
FpdCEbqHA7SAVk1sK1D26qk5HUsLsylz5wo19B26v0Bcd1ktjwWLLMM1WdyDbCiF
IYnM7whB/YWb9bTLeaJSSRYrUulz41dVyMalzgW3xAR1aujaeLdIOI699hjS8Sd4
to6y24eZZm78ZbjsZa6hniU9vWXTql+6Lgoui9SQWgPsP+GpQeo275FrHQ+d0d82
VwCvnp9idO2O8vTFnt30NbhkDfQFS+Tn2l0/yDzzXMHJZ5ppL5jliH4oLJi/AgMB
AAGjggujMIILnzAMBgNVHRMBAf8EAjAAMGYGA1UdIARfMF0wCAYGZ4EMAQICMFEG
CSqDCIybEQEXATBEMEIGCCsGAQUFBwIBFjZodHRwczovL3d3dy5jeWJlcnRydXN0
Lm5lLmpwL3NzbC9yZXBvc2l0b3J5L2luZGV4Lmh0bWwwgghfBgNVHREEgghWMIII
UoISZWRnZTAxLnlhaG9vLmNvLmpwgg0qLnlhaG9vLmNvLmpwgg4qLnlhaG9vYXBp
cy5qcIIRKi5hbmUueWFob28uY28uanCCFiouYXVjdGlvbnMueWFob28uY28uanCC
FyouYXVjdGlvbnMueWFob29hcGlzLmpwghIqLmJveC55YWhvb2FwaXMuanCCCyou
YnNwYWNlLmpwghoqLmJ5bGluZXMubmV3cy55YWhvby5jby5qcIILKi5jLnlpbWcu
anCCFiouY2FybmF2aS55YWhvb2FwaXMuanCCDyouY2Fydmlldy5jby5qcIIVKi5j
YXJ2aWV3LnlhaG9vLmNvLmpwghgqLmNoaWVidWt1cm8ueWFob28uY28uanCCFSou
Y2xvcmRlci55YWhvby5jby5qcIIIKi5jdncuanCCESouZGlnaXRhbGd1aWRlLmpw
ghwqLmVhc3QuZWRnZS5zdG9yYWdlLXlhaG9vLmpwgh8qLmVhc3QuZWRnZS5zdG9y
YWdlLXlhaG9vYm94LmpwghcqLmVkZ2Uuc3RvcmFnZS15YWhvby5qcIITKi5lZGl0
LnlhaG9vYXBpcy5qcIIVKi5maW5hbmNlLnlhaG9vLmNvLmpwgg4qLmdlb2NpdGll
cy5qcIIeKi5nbG9iYWwuZWRnZS5zdG9yYWdlLXlhaG9vLmpwghIqLmd5YW8ueWFo
b28uY28uanCCGCouam9iY2F0YWxvZy55YWhvby5jby5qcIIVKi5saXN0aW5nLnlh
aG9vLmNvLmpwghIqLmxvY28ueWFob28uY28uanCCDioubHljb3JwLmNvLmpwghIq
Lm1haWwueWFob28uY28uanCCFyoubWFya2V0aW5nLnlhaG9vLmNvLmpwghsqLm1r
Y2xvdWQtYXBpLmNhcnZpZXcuY28uanCCFSoubWtpbWcuY2Fydmlldy5jby5qcIIQ
Ki5tcy55YWhvby5jby5qcIIUKi5seWNvcnAtc2VjdXJpdHkuanCCEioubmV3cy55
YWhvby5jby5qcIITKi5uZXdzLnlhaG9vYXBpcy5qcIITKi5vcmRlci55YWhvby5j
by5qcIIUKi5wb2ludHMueWFob28uY28uanCCESoucHNpLnlhaG9vLmNvLmpwghMq
LnB1c2gueWFob29hcGlzLmpwghxhY3Rpdml0eS50cmF2ZWwueWFob28tbmV0Lmpw
ghQqLnNob3BwaW5nLmMueWltZy5qcIIWKi5zaG9wcGluZy5zcnYueWltZy5qcIIW
Ki5zaG9wcGluZy55YWhvby5jby5qcIIXKi5zaG9wcGluZy55YWhvb2FwaXMuanCC
Fiouc25zaW1nLmNhcnZpZXcuY28uanCCEyouc3RvcmUueWFob28uY28uanCCFCou
dHJhdmVsLnlhaG9vLmNvLmpwghQqLndhbGxldC55YWhvby5jby5qcIIVKi53YWxs
ZXQueWFob29hcGlzLmpwghgqLndlYmhvc3RpbmcueWFob28uY28uanCCHCoud2Vz
dC5lZGdlLnN0b3JhZ2UteWFob28uanCCHyoud2VzdC5lZGdlLnN0b3JhZ2UteWFo
b29ib3guanCCGSoueG1sLmxpc3RpbmcueWFob28uY28uanCCDyoueWFob28taGVs
cC5qcIIPKi55YWhvby1sYWJzLmpwgg4qLnlhaG9vLW5ldC5qcIIKKi55YWhvby5q
cIINKi55YWhvb2JveC5qcIIJKi55aW1nLmpwggoqLnlqdGFnLmpwghMqLnlqdGFn
LnlhaG9vLmNvLmpwghQqLnlzLWluc3VyYW5jZS5jby5qcIIVKi5zZWFyY2gueWFo
b29hcGlzLmpwghNhZGQuZGlyLnlhaG9vLmNvLmpwghlhcGkueS5jbG9yZGVyLnlh
aG9vLmNvLmpwghRhcmMuaGVscC55YWhvby5jby5qcIIZYml6dHgucG9pbnRzLnlh
aG9vYXBpcy5qcIINY2Fydmlldy5jby5qcIIYY2dpMi5yLWFnZW50LnlhaG9vLmNv
Lmpwghdja3N5bmMucGRzcC55YWhvby5jby5qcIIUY20uZnJvbWEueWFob28uY28u
anCCG2NvbXBhc3MueW1vYmlsZS55YWhvby5jby5qcIIZY3VzdG9tLnNlYXJjaC55
YWhvby5jby5qcIIXZS5kZXZlbG9wZXIueWFob28uY28uanCCGmZvcm1zLmJ1c2lu
ZXNzLnlhaG9vLmNvLmpwghdmcmFtZS5nYW1lcy55YWhvby5jby5qcIIXaHJtLmdy
bXRyZXoueWFob28uY28uanCCEWltLm92LnlhaG9vLmNvLmpwghlpbmZvLmhhdGFs
aWtlLnlhaG9vLmNvLmpwghptb3ZpZS5jaG9jb3RsZS55YWhvby5jby5qcIIbb25s
aW5lLnNlY3VyaXR5LnlhaG9vLmNvLmpwghdwb2llZGl0Lm1hcC55YWhvby5jby5q
cIIhcG9ydGFsLnlhZHVpLmJ1c2luZXNzLnlhaG9vLmNvLmpwgiRzc2wtdG9vbHMu
a2FpbmF2aS5zZWFyY2gueWFob28uY28uanCCGHNzbC5hcGkub2xwLnlhaG9vYXBp
cy5qcIITc3NsLm1hcC5zcnYueWltZy5qcIIRd3d3LmJvc2FpZ3VpZGUuanCCFnd3
dy5sb2hhY28ueWFob28uY28uanCCEHd3dy5zZWFyY2gzMTEuanCCD3d3dy5zcC1o
aW5hbi5qcIISd3d3LnRlY2hiYXNldm4uY29tggt5YWhvby5jby5qcIIIeWFob28u
anCCBXlqLnBuggh5anRhZy5qcDCBiwYIKwYBBQUHAQEEfzB9MDUGCCsGAQUFBzAB
hilodHRwOi8vc3NvY3NwLmN5YmVydHJ1c3QubmUuanAvT2NzcFNlcnZlcjBEBggr
BgEFBQcwAoY4aHR0cDovL2NybC5jeWJlcnRydXN0Lm5lLmpwL1N1cmVTZXJ2ZXIv
b3ZjYWc0L292Y2FnNC5jcnQwDgYDVR0PAQH/BAQDAgWgMB0GA1UdJQQWMBQGCCsG
AQUFBwMBBggrBgEFBQcDAjAfBgNVHSMEGDAWgBRip9La3oW2kvGFvPbolZ11oPpO
HzBGBgNVHR8EPzA9MDugOaA3hjVodHRwOi8vY3JsLmN5YmVydHJ1c3QubmUuanAv
U3VyZVNlcnZlci9vdmNhZzQvY2RwLmNybDAdBgNVHQ4EFgQUfKot2uHGJs14tri8
UOSHNUN+1CEwggF9BgorBgEEAdZ5AgQCBIIBbQSCAWkBZwB2AA5XlLzzrqk+Mxss
mQez95Dfm8I9cTIl3SGpJaxhxU4hAAABljhnQXwAAAQDAEcwRQIhAKLLyz2O8RKk
xW2GjJFwaAcowDMHDkp/g+8nl2QCMD6jAiBG6IKntbCOHPQD9D2ckF9vRcwfUFY1
ILKmoF1jWssX1gB1AJaXZL9VWJet90OHaDcIQnfp8DrV9qTzNm5GpD8PyqnGAAAB
ljhnSGUAAAQDAEYwRAIgShmqKc41GHQTf0ceLXtof0002yVIZqQzi5I7z2q9VIQC
IBQwONpJBzfDiggbxSKUo1SHOvvYlC04j0+CARqH4n64AHYAGYbUxyiqb/66A294
Kk0BkarOLXIxD67OXXBBLSVMx9QAAAGWOGdNdQAABAMARzBFAiA3+7IxDg9y4dG6
Ja1o8AvkBcsbLt59UhOEBZ7mXb+xBwIhANoe4yoZS3X0RIeUJCHtxgvyVj53Bx3U
9qd8Utn6IS+KMA0GCSqGSIb3DQEBCwUAA4IBAQB/MvHDetWmeoIqc+dQzEurtQNd
4g/Cng4n+Yf+j9+UnrsO34pHPfy+4kfMatPaAuBxGv/cLAYeAWE8tZJRzn67DhBK
vGmaaqQziKiT2QBn0hi9PiLet7FoMLqEfD5W7m7yGx8hUlwpxwpwIf20dOdwjBzN
HlukZVf4U/yMh1t+hbHfBQAIXsYmhM94FeE7j2ENr2xzfJyiyvqVvV2EuUEX7X+f
DV/L1mbqdbE06nSqgInyjvbhduvWB/+e9HXvEwJvHrVh68Wn88vYMeTkysZ5o6+Z
o83BJ0+/jVFIISEpM/QzdqF3184y9IHyk6QKWyG1FXv46ytTLargGsUN4TWC
-----END CERTIFICATE-----
------------------
        No extensions
        ASN.1Cert, length=1283
------details-----
Certificate:
    Data:
        Version: 3 (0x2)
        Serial Number:
            22:b9:b1:a0:74:64:18:57:f7:a0:13:32:db:42:b9:ec
        Signature Algorithm: sha256WithRSAEncryption
        Issuer: C = JP, O = "SECOM Trust Systems CO.,LTD.", OU = Security Communication RootCA2
        Validity
            Not Before: Dec 13 05:57:30 2023 GMT
            Not After : May 29 05:00:39 2029 GMT
        Subject: C = JP, O = "Cybertrust Japan Co., Ltd.", CN = Cybertrust Japan SureServer CA G4
        Subject Public Key Info:
            Public Key Algorithm: rsaEncryption
                Public-Key: (2048 bit)
                Modulus:
                    00:cb:6e:9c:59:a8:b1:3f:08:c4:19:15:14:ff:8e:
                    9e:41:a4:71:59:9b:ba:2f:a1:75:50:65:19:98:67:
                    8a:78:95:96:e0:21:8a:09:b6:59:4c:71:a7:85:f9:
                    57:70:7f:40:a2:4b:66:67:80:b3:09:b3:c4:62:97:
                    68:30:b3:72:89:98:c5:74:f2:80:d5:dc:4c:b2:3e:
                    20:cc:91:8a:c1:0e:ed:5d:4d:5c:51:d4:8d:21:25:
                    29:a6:35:2f:30:80:f7:f7:a6:95:d9:e6:46:35:fa:
                    07:d6:6d:e7:15:ca:e6:ad:76:58:e2:16:90:91:02:
                    13:0c:0a:92:ee:fb:b6:fb:4a:64:f4:4a:68:23:42:
                    1a:c6:79:1e:36:bb:3c:1b:34:ee:32:e8:13:4a:cc:
                    b9:92:d0:64:d4:04:07:45:ba:dd:ab:6d:28:60:86:
                    cc:49:39:d2:50:e3:fb:04:34:52:55:1b:42:4d:f3:
                    00:4b:2f:74:4e:97:a3:5a:99:cb:d9:7b:f3:75:5a:
                    e3:4b:d2:c7:75:6a:84:66:1b:e2:35:90:ae:0d:82:
                    ac:0b:49:70:a4:0d:48:9d:26:f7:2c:49:55:54:03:
                    c2:94:10:c0:6c:47:3b:91:26:42:fd:4b:18:91:31:
                    01:27:a0:39:7c:e1:ce:a0:ab:e7:28:b0:10:27:d2:
                    ac:eb
                Exponent: 65537 (0x10001)
        X509v3 extensions:
            X509v3 Subject Key Identifier: 
                62:A7:D2:DA:DE:85:B6:92:F1:85:BC:F6:E8:95:9D:75:A0:FA:4E:1F
            X509v3 Authority Key Identifier: 
                0A:85:A9:77:65:05:98:7C:40:81:F8:0F:97:2C:38:F1:0A:EC:3C:CF
            X509v3 Basic Constraints: critical
                CA:TRUE, pathlen:0
            X509v3 Key Usage: critical
                Certificate Sign, CRL Sign
            X509v3 CRL Distribution Points: 
                Full Name:
                  URI:http://repository.secomtrust.net/SC-Root2/SCRoot2CRL.crl

            X509v3 Certificate Policies: 
                Policy: 2.23.140.1.2.2
                Policy: 1.2.392.200091.100.901.4
                  CPS: https://repository.secomtrust.net/SC-Root2/
            Authority Information Access: 
                OCSP - URI:http://scrootca2.ocsp.secomtrust.net
                CA Issuers - URI:http://repository.secomtrust.net/SC-Root2/SCRoot2ca.cer
            X509v3 Extended Key Usage: 
                TLS Web Server Authentication, TLS Web Client Authentication
    Signature Algorithm: sha256WithRSAEncryption
    Signature Value:
        3e:7f:43:75:49:3a:f1:b0:a3:44:41:05:ca:a2:a6:c6:a1:2e:
        70:05:4d:dd:7a:21:9c:d0:11:00:2d:71:12:5e:18:9a:30:18:
        71:5c:55:7b:eb:23:76:dc:cf:61:0c:10:4f:81:0f:f2:2d:f1:
        7f:9e:68:dd:50:de:c1:2b:f0:46:60:f8:77:86:9a:a0:56:8b:
        06:92:8a:f7:d1:e1:e1:f2:27:1a:c8:af:33:90:d1:3f:3b:ff:
        42:26:a5:f7:e5:82:9f:2e:b7:af:96:6b:f6:c6:a8:0d:0a:59:
        75:f8:a9:0f:74:81:03:6e:09:7e:d8:e3:3c:ab:27:e9:48:cc:
        bf:22:95:72:84:33:89:1a:83:31:06:1d:b8:ad:47:50:be:e8:
        17:c1:b6:3c:0e:9c:13:2a:15:7f:ad:11:a7:f2:e5:bd:ef:cb:
        33:74:e0:22:6d:7b:24:d1:4a:50:04:d2:81:c5:f0:e4:7a:f6:
        4a:86:e5:ea:de:80:d0:52:20:2d:20:2c:47:2f:29:99:50:e6:
        53:9b:d2:18:9a:e6:9d:06:fd:53:b6:9d:99:33:42:b5:82:aa:
        b5:96:e2:39:7d:86:db:6b:d2:97:d0:66:30:b9:f0:47:cd:a3:
        0d:5b:82:df:cb:a0:db:ea:57:09:86:11:c5:ff:77:c7:ea:a7:
        e8:5b:ef:cf
-----BEGIN CERTIFICATE-----
MIIE/zCCA+egAwIBAgIQIrmxoHRkGFf3oBMy20K57DANBgkqhkiG9w0BAQsFADBd
MQswCQYDVQQGEwJKUDElMCMGA1UEChMcU0VDT00gVHJ1c3QgU3lzdGVtcyBDTy4s
TFRELjEnMCUGA1UECxMeU2VjdXJpdHkgQ29tbXVuaWNhdGlvbiBSb290Q0EyMB4X
DTIzMTIxMzA1NTczMFoXDTI5MDUyOTA1MDAzOVowXjELMAkGA1UEBhMCSlAxIzAh
BgNVBAoTGkN5YmVydHJ1c3QgSmFwYW4gQ28uLCBMdGQuMSowKAYDVQQDEyFDeWJl
cnRydXN0IEphcGFuIFN1cmVTZXJ2ZXIgQ0EgRzQwggEiMA0GCSqGSIb3DQEBAQUA
A4IBDwAwggEKAoIBAQDLbpxZqLE/CMQZFRT/jp5BpHFZm7ovoXVQZRmYZ4p4lZbg
IYoJtllMcaeF+Vdwf0CiS2ZngLMJs8Ril2gws3KJmMV08oDV3EyyPiDMkYrBDu1d
TVxR1I0hJSmmNS8wgPf3ppXZ5kY1+gfWbecVyuatdljiFpCRAhMMCpLu+7b7SmT0
SmgjQhrGeR42uzwbNO4y6BNKzLmS0GTUBAdFut2rbShghsxJOdJQ4/sENFJVG0JN
8wBLL3ROl6NamcvZe/N1WuNL0sd1aoRmG+I1kK4NgqwLSXCkDUidJvcsSVVUA8KU
EMBsRzuRJkL9SxiRMQEnoDl84c6gq+cosBAn0qzrAgMBAAGjggG4MIIBtDAdBgNV
HQ4EFgQUYqfS2t6FtpLxhbz26JWddaD6Th8wHwYDVR0jBBgwFoAUCoWpd2UFmHxA
gfgPlyw48QrsPM8wEgYDVR0TAQH/BAgwBgEB/wIBADAOBgNVHQ8BAf8EBAMCAQYw
SQYDVR0fBEIwQDA+oDygOoY4aHR0cDovL3JlcG9zaXRvcnkuc2Vjb210cnVzdC5u
ZXQvU0MtUm9vdDIvU0NSb290MkNSTC5jcmwwXAYDVR0gBFUwUzAIBgZngQwBAgIw
RwYKKoMIjJsbZIcFBDA5MDcGCCsGAQUFBwIBFitodHRwczovL3JlcG9zaXRvcnku
c2Vjb210cnVzdC5uZXQvU0MtUm9vdDIvMIGFBggrBgEFBQcBAQR5MHcwMAYIKwYB
BQUHMAGGJGh0dHA6Ly9zY3Jvb3RjYTIub2NzcC5zZWNvbXRydXN0Lm5ldDBDBggr
BgEFBQcwAoY3aHR0cDovL3JlcG9zaXRvcnkuc2Vjb210cnVzdC5uZXQvU0MtUm9v
dDIvU0NSb290MmNhLmNlcjAdBgNVHSUEFjAUBggrBgEFBQcDAQYIKwYBBQUHAwIw
DQYJKoZIhvcNAQELBQADggEBAD5/Q3VJOvGwo0RBBcqipsahLnAFTd16IZzQEQAt
cRJeGJowGHFcVXvrI3bcz2EMEE+BD/It8X+eaN1Q3sEr8EZg+HeGmqBWiwaSivfR
4eHyJxrIrzOQ0T87/0Impfflgp8ut6+Wa/bGqA0KWXX4qQ90gQNuCX7Y4zyrJ+lI
zL8ilXKEM4kagzEGHbitR1C+6BfBtjwOnBMqFX+tEafy5b3vyzN04CJteyTRSlAE
0oHF8OR69kqG5eregNBSIC0gLEcvKZlQ5lOb0hia5p0G/VO2nZkzQrWCqrWW4jl9
httr0pfQZjC58EfNow1bgt/LoNvqVwmGEcX/d8fqp+hb788=
-----END CERTIFICATE-----
------------------
        No extensions

depth=2 C=JP, O=SECOM Trust Systems CO.,LTD., OU=Security Communication RootCA2
verify return:1
depth=1 C=JP, O=Cybertrust Japan Co., Ltd., CN=Cybertrust Japan SureServer CA G4
verify return:1
depth=0 C=JP, ST=Tokyo, L=Chiyoda-ku, O=LY Corporation, CN=edge01.yahoo.co.jp
verify return:1
Received TLS Record
Header:
  Version = TLS 1.2 (0x303)
  Content Type = ApplicationData (23)
  Length = 281
  Inner Content Type = Handshake (22)
    CertificateVerify, Length=260
      Signature Algorithm: rsa_pss_rsae_sha256 (0x0804)
      Signature (len=256): 12AA0BC5AB3E15A89E4E1FF93351464A2690B5DF2B9F03214220360714B2164FA5F5953265631346A83EEDC5EB6FFC957A1E34B55088C83134F187EC0ADDF27ED22583EC91446B0883FA610FFDD833AF89063FC6ABD8C0718CA0DCE1718FBBBE50518E2310BEEA9443AA551205BADB836B385AE2A431B083D809BEFC5A8336FDE1510C2EC4CEE4B50EA6C9C9E8AF4DFBBB8A6C33AC149C40A5CEED548E5F38E565E076B7DEA55D9266523D3A092E9FEC2A835477F88FFA18BA14C82B70435F25E524EA8D875384229422A3AE1778BAC56C41A950FBC7D802B45EC2FFA3C9D9D29ADEC368A74EC2DBE164A8744FEE2131AF48A4841F925AF13D2BF8265F311C20

Received TLS Record
Header:
  Version = TLS 1.2 (0x303)
  Content Type = ApplicationData (23)
  Length = 53
  Inner Content Type = Handshake (22)
    Finished, Length=32
      verify_data (len=32): 9DAA64E731EB5517CB371EA7CBBFDE6CD9A08AB68DEC288F798B127CD3A0A0CC

Sent TLS Record
Header:
  Version = TLS 1.2 (0x303)
  Content Type = ChangeCipherSpec (20)
  Length = 1
    change_cipher_spec (1)

Sent TLS Record
Header:
  Version = TLS 1.2 (0x303)
  Content Type = ApplicationData (23)
  Length = 53
  Inner Content Type = Handshake (22)
    Finished, Length=32
      verify_data (len=32): B324A8A7373DAA1292FA0005C5C49B2B675D270C372076F0A2BC77A5FC97EC29

---
Certificate chain
 0 s:C=JP, ST=Tokyo, L=Chiyoda-ku, O=LY Corporation, CN=edge01.yahoo.co.jp
   i:C=JP, O=Cybertrust Japan Co., Ltd., CN=Cybertrust Japan SureServer CA G4
   a:PKEY: rsaEncryption, 2048 (bit); sigalg: RSA-SHA256
   v:NotBefore: Apr 15 07:20:27 2025 GMT; NotAfter: May 14 14:59:00 2026 GMT
 1 s:C=JP, O=Cybertrust Japan Co., Ltd., CN=Cybertrust Japan SureServer CA G4
   i:C=JP, O=SECOM Trust Systems CO.,LTD., OU=Security Communication RootCA2
   a:PKEY: rsaEncryption, 2048 (bit); sigalg: RSA-SHA256
   v:NotBefore: Dec 13 05:57:30 2023 GMT; NotAfter: May 29 05:00:39 2029 GMT
---
Server certificate
-----BEGIN CERTIFICATE-----
MIIO+TCCDeGgAwIBAgIUVxr+imV0xK8rzml35+mOrQsMna4wDQYJKoZIhvcNAQEL
BQAwXjELMAkGA1UEBhMCSlAxIzAhBgNVBAoTGkN5YmVydHJ1c3QgSmFwYW4gQ28u
LCBMdGQuMSowKAYDVQQDEyFDeWJlcnRydXN0IEphcGFuIFN1cmVTZXJ2ZXIgQ0Eg
RzQwHhcNMjUwNDE1MDcyMDI3WhcNMjYwNTE0MTQ1OTAwWjBoMQswCQYDVQQGEwJK
UDEOMAwGA1UECBMFVG9reW8xEzARBgNVBAcTCkNoaXlvZGEta3UxFzAVBgNVBAoT
DkxZIENvcnBvcmF0aW9uMRswGQYDVQQDExJlZGdlMDEueWFob28uY28uanAwggEi
MA0GCSqGSIb3DQEBAQUAA4IBDwAwggEKAoIBAQDTd/6S+6GrhA3d67pXjYy4AUR4
pWvbIm/UiN1wE6Ym2LmcS1XW0fSZWVtwbAAChsgJW0tqE2SL5IMhw95iKzdVOHF0
FpdCEbqHA7SAVk1sK1D26qk5HUsLsylz5wo19B26v0Bcd1ktjwWLLMM1WdyDbCiF
IYnM7whB/YWb9bTLeaJSSRYrUulz41dVyMalzgW3xAR1aujaeLdIOI699hjS8Sd4
to6y24eZZm78ZbjsZa6hniU9vWXTql+6Lgoui9SQWgPsP+GpQeo275FrHQ+d0d82
VwCvnp9idO2O8vTFnt30NbhkDfQFS+Tn2l0/yDzzXMHJZ5ppL5jliH4oLJi/AgMB
AAGjggujMIILnzAMBgNVHRMBAf8EAjAAMGYGA1UdIARfMF0wCAYGZ4EMAQICMFEG
CSqDCIybEQEXATBEMEIGCCsGAQUFBwIBFjZodHRwczovL3d3dy5jeWJlcnRydXN0
Lm5lLmpwL3NzbC9yZXBvc2l0b3J5L2luZGV4Lmh0bWwwgghfBgNVHREEgghWMIII
UoISZWRnZTAxLnlhaG9vLmNvLmpwgg0qLnlhaG9vLmNvLmpwgg4qLnlhaG9vYXBp
cy5qcIIRKi5hbmUueWFob28uY28uanCCFiouYXVjdGlvbnMueWFob28uY28uanCC
FyouYXVjdGlvbnMueWFob29hcGlzLmpwghIqLmJveC55YWhvb2FwaXMuanCCCyou
YnNwYWNlLmpwghoqLmJ5bGluZXMubmV3cy55YWhvby5jby5qcIILKi5jLnlpbWcu
anCCFiouY2FybmF2aS55YWhvb2FwaXMuanCCDyouY2Fydmlldy5jby5qcIIVKi5j
YXJ2aWV3LnlhaG9vLmNvLmpwghgqLmNoaWVidWt1cm8ueWFob28uY28uanCCFSou
Y2xvcmRlci55YWhvby5jby5qcIIIKi5jdncuanCCESouZGlnaXRhbGd1aWRlLmpw
ghwqLmVhc3QuZWRnZS5zdG9yYWdlLXlhaG9vLmpwgh8qLmVhc3QuZWRnZS5zdG9y
YWdlLXlhaG9vYm94LmpwghcqLmVkZ2Uuc3RvcmFnZS15YWhvby5qcIITKi5lZGl0
LnlhaG9vYXBpcy5qcIIVKi5maW5hbmNlLnlhaG9vLmNvLmpwgg4qLmdlb2NpdGll
cy5qcIIeKi5nbG9iYWwuZWRnZS5zdG9yYWdlLXlhaG9vLmpwghIqLmd5YW8ueWFo
b28uY28uanCCGCouam9iY2F0YWxvZy55YWhvby5jby5qcIIVKi5saXN0aW5nLnlh
aG9vLmNvLmpwghIqLmxvY28ueWFob28uY28uanCCDioubHljb3JwLmNvLmpwghIq
Lm1haWwueWFob28uY28uanCCFyoubWFya2V0aW5nLnlhaG9vLmNvLmpwghsqLm1r
Y2xvdWQtYXBpLmNhcnZpZXcuY28uanCCFSoubWtpbWcuY2Fydmlldy5jby5qcIIQ
Ki5tcy55YWhvby5jby5qcIIUKi5seWNvcnAtc2VjdXJpdHkuanCCEioubmV3cy55
YWhvby5jby5qcIITKi5uZXdzLnlhaG9vYXBpcy5qcIITKi5vcmRlci55YWhvby5j
by5qcIIUKi5wb2ludHMueWFob28uY28uanCCESoucHNpLnlhaG9vLmNvLmpwghMq
LnB1c2gueWFob29hcGlzLmpwghxhY3Rpdml0eS50cmF2ZWwueWFob28tbmV0Lmpw
ghQqLnNob3BwaW5nLmMueWltZy5qcIIWKi5zaG9wcGluZy5zcnYueWltZy5qcIIW
Ki5zaG9wcGluZy55YWhvby5jby5qcIIXKi5zaG9wcGluZy55YWhvb2FwaXMuanCC
Fiouc25zaW1nLmNhcnZpZXcuY28uanCCEyouc3RvcmUueWFob28uY28uanCCFCou
dHJhdmVsLnlhaG9vLmNvLmpwghQqLndhbGxldC55YWhvby5jby5qcIIVKi53YWxs
ZXQueWFob29hcGlzLmpwghgqLndlYmhvc3RpbmcueWFob28uY28uanCCHCoud2Vz
dC5lZGdlLnN0b3JhZ2UteWFob28uanCCHyoud2VzdC5lZGdlLnN0b3JhZ2UteWFo
b29ib3guanCCGSoueG1sLmxpc3RpbmcueWFob28uY28uanCCDyoueWFob28taGVs
cC5qcIIPKi55YWhvby1sYWJzLmpwgg4qLnlhaG9vLW5ldC5qcIIKKi55YWhvby5q
cIINKi55YWhvb2JveC5qcIIJKi55aW1nLmpwggoqLnlqdGFnLmpwghMqLnlqdGFn
LnlhaG9vLmNvLmpwghQqLnlzLWluc3VyYW5jZS5jby5qcIIVKi5zZWFyY2gueWFo
b29hcGlzLmpwghNhZGQuZGlyLnlhaG9vLmNvLmpwghlhcGkueS5jbG9yZGVyLnlh
aG9vLmNvLmpwghRhcmMuaGVscC55YWhvby5jby5qcIIZYml6dHgucG9pbnRzLnlh
aG9vYXBpcy5qcIINY2Fydmlldy5jby5qcIIYY2dpMi5yLWFnZW50LnlhaG9vLmNv
Lmpwghdja3N5bmMucGRzcC55YWhvby5jby5qcIIUY20uZnJvbWEueWFob28uY28u
anCCG2NvbXBhc3MueW1vYmlsZS55YWhvby5jby5qcIIZY3VzdG9tLnNlYXJjaC55
YWhvby5jby5qcIIXZS5kZXZlbG9wZXIueWFob28uY28uanCCGmZvcm1zLmJ1c2lu
ZXNzLnlhaG9vLmNvLmpwghdmcmFtZS5nYW1lcy55YWhvby5jby5qcIIXaHJtLmdy
bXRyZXoueWFob28uY28uanCCEWltLm92LnlhaG9vLmNvLmpwghlpbmZvLmhhdGFs
aWtlLnlhaG9vLmNvLmpwghptb3ZpZS5jaG9jb3RsZS55YWhvby5jby5qcIIbb25s
aW5lLnNlY3VyaXR5LnlhaG9vLmNvLmpwghdwb2llZGl0Lm1hcC55YWhvby5jby5q
cIIhcG9ydGFsLnlhZHVpLmJ1c2luZXNzLnlhaG9vLmNvLmpwgiRzc2wtdG9vbHMu
a2FpbmF2aS5zZWFyY2gueWFob28uY28uanCCGHNzbC5hcGkub2xwLnlhaG9vYXBp
cy5qcIITc3NsLm1hcC5zcnYueWltZy5qcIIRd3d3LmJvc2FpZ3VpZGUuanCCFnd3
dy5sb2hhY28ueWFob28uY28uanCCEHd3dy5zZWFyY2gzMTEuanCCD3d3dy5zcC1o
aW5hbi5qcIISd3d3LnRlY2hiYXNldm4uY29tggt5YWhvby5jby5qcIIIeWFob28u
anCCBXlqLnBuggh5anRhZy5qcDCBiwYIKwYBBQUHAQEEfzB9MDUGCCsGAQUFBzAB
hilodHRwOi8vc3NvY3NwLmN5YmVydHJ1c3QubmUuanAvT2NzcFNlcnZlcjBEBggr
BgEFBQcwAoY4aHR0cDovL2NybC5jeWJlcnRydXN0Lm5lLmpwL1N1cmVTZXJ2ZXIv
b3ZjYWc0L292Y2FnNC5jcnQwDgYDVR0PAQH/BAQDAgWgMB0GA1UdJQQWMBQGCCsG
AQUFBwMBBggrBgEFBQcDAjAfBgNVHSMEGDAWgBRip9La3oW2kvGFvPbolZ11oPpO
HzBGBgNVHR8EPzA9MDugOaA3hjVodHRwOi8vY3JsLmN5YmVydHJ1c3QubmUuanAv
U3VyZVNlcnZlci9vdmNhZzQvY2RwLmNybDAdBgNVHQ4EFgQUfKot2uHGJs14tri8
UOSHNUN+1CEwggF9BgorBgEEAdZ5AgQCBIIBbQSCAWkBZwB2AA5XlLzzrqk+Mxss
mQez95Dfm8I9cTIl3SGpJaxhxU4hAAABljhnQXwAAAQDAEcwRQIhAKLLyz2O8RKk
xW2GjJFwaAcowDMHDkp/g+8nl2QCMD6jAiBG6IKntbCOHPQD9D2ckF9vRcwfUFY1
ILKmoF1jWssX1gB1AJaXZL9VWJet90OHaDcIQnfp8DrV9qTzNm5GpD8PyqnGAAAB
ljhnSGUAAAQDAEYwRAIgShmqKc41GHQTf0ceLXtof0002yVIZqQzi5I7z2q9VIQC
IBQwONpJBzfDiggbxSKUo1SHOvvYlC04j0+CARqH4n64AHYAGYbUxyiqb/66A294
Kk0BkarOLXIxD67OXXBBLSVMx9QAAAGWOGdNdQAABAMARzBFAiA3+7IxDg9y4dG6
Ja1o8AvkBcsbLt59UhOEBZ7mXb+xBwIhANoe4yoZS3X0RIeUJCHtxgvyVj53Bx3U
9qd8Utn6IS+KMA0GCSqGSIb3DQEBCwUAA4IBAQB/MvHDetWmeoIqc+dQzEurtQNd
4g/Cng4n+Yf+j9+UnrsO34pHPfy+4kfMatPaAuBxGv/cLAYeAWE8tZJRzn67DhBK
vGmaaqQziKiT2QBn0hi9PiLet7FoMLqEfD5W7m7yGx8hUlwpxwpwIf20dOdwjBzN
HlukZVf4U/yMh1t+hbHfBQAIXsYmhM94FeE7j2ENr2xzfJyiyvqVvV2EuUEX7X+f
DV/L1mbqdbE06nSqgInyjvbhduvWB/+e9HXvEwJvHrVh68Wn88vYMeTkysZ5o6+Z
o83BJ0+/jVFIISEpM/QzdqF3184y9IHyk6QKWyG1FXv46ytTLargGsUN4TWC
-----END CERTIFICATE-----
subject=C=JP, ST=Tokyo, L=Chiyoda-ku, O=LY Corporation, CN=edge01.yahoo.co.jp
issuer=C=JP, O=Cybertrust Japan Co., Ltd., CN=Cybertrust Japan SureServer CA G4
---
No client certificate CA names sent
Peer signing digest: SHA256
Peer signature type: RSA-PSS
Server Temp Key: X25519, 253 bits
---
SSL handshake has read 5669 bytes and written 390 bytes
Verification: OK
---
New, TLSv1.3, Cipher is TLS_AES_128_GCM_SHA256
Protocol: TLSv1.3
Server public key is 2048 bit
This TLS version forbids renegotiation.
Compression: NONE
Expansion: NONE
No ALPN negotiated
Early data was not sent
Verify return code: 0 (ok)
---
Received TLS Record
Header:
  Version = TLS 1.2 (0x303)
  Content Type = ApplicationData (23)
  Length = 282
  Inner Content Type = Handshake (22)
    NewSessionTicket, Length=261
        ticket_lifetime_hint=7200
        ticket_age_add=3002416440
        ticket_nonce (len=8): 0000000000000000
        ticket (len=240): 5961686F6F21204A4150414E00000000100B2B200B3512F192D760456D3B14B26A29C52BE4B32E3D0023E88E73468108304F74A74A6AC8CFDED0F55ECE6CAF6AB917D6AED6BD5D9B56D5A2628A627573B3B843BA1557050CC008978A3A8BCEF180B4BCBFBB286A07E0930E2F9C85C12661F85C3E7D1480ADC4E72EC96ECF777F4CD8394BF90D637BEE006EEB72A01AC8FA7CAFB94EBE8813D5A24435FF208B494F6074F21CE2D558CC9AB96DC3E935E3CC4E4C7B01A1B0396BEE8C1D796BF988345BA2E5B3C0AD803E9DA3726D9DF23FEB95BBD1B0D6D8E68AA490F604BFEDE0360A73CEF7ACE4CFB3F0665495D46F20
        No extensions

---
Post-Handshake New Session Ticket arrived:
SSL-Session:
    Protocol  : TLSv1.3
    Cipher    : TLS_AES_128_GCM_SHA256
    Session-ID: 9E44DE04A83F7D0296DFD8F3320C1294E93A86263A7E32D078616DFA5B6AD46B
    Session-ID-ctx: 
    Resumption PSK: 88ED977E99F85F193655B9488F21168B278BC56E8FACA61293303921B91CF1C4
    PSK identity: None
    PSK identity hint: None
    SRP username: None
    TLS session ticket lifetime hint: 7200 (seconds)
    TLS session ticket:
    0000 - 59 61 68 6f 6f 21 20 4a-41 50 41 4e 00 00 00 00   Yahoo! JAPAN....
    0010 - 10 0b 2b 20 0b 35 12 f1-92 d7 60 45 6d 3b 14 b2   ..+ .5....`Em;..
    0020 - 6a 29 c5 2b e4 b3 2e 3d-00 23 e8 8e 73 46 81 08   j).+...=.#..sF..
    0030 - 30 4f 74 a7 4a 6a c8 cf-de d0 f5 5e ce 6c af 6a   0Ot.Jj.....^.l.j
    0040 - b9 17 d6 ae d6 bd 5d 9b-56 d5 a2 62 8a 62 75 73   ......].V..b.bus
    0050 - b3 b8 43 ba 15 57 05 0c-c0 08 97 8a 3a 8b ce f1   ..C..W......:...
    0060 - 80 b4 bc bf bb 28 6a 07-e0 93 0e 2f 9c 85 c1 26   .....(j..../...&
    0070 - 61 f8 5c 3e 7d 14 80 ad-c4 e7 2e c9 6e cf 77 7f   a.\>}.......n.w.
    0080 - 4c d8 39 4b f9 0d 63 7b-ee 00 6e eb 72 a0 1a c8   L.9K..c{..n.r...
    0090 - fa 7c af b9 4e be 88 13-d5 a2 44 35 ff 20 8b 49   .|..N.....D5. .I
    00a0 - 4f 60 74 f2 1c e2 d5 58-cc 9a b9 6d c3 e9 35 e3   O`t....X...m..5.
    00b0 - cc 4e 4c 7b 01 a1 b0 39-6b ee 8c 1d 79 6b f9 88   .NL{...9k...yk..
    00c0 - 34 5b a2 e5 b3 c0 ad 80-3e 9d a3 72 6d 9d f2 3f   4[......>..rm..?
    00d0 - eb 95 bb d1 b0 d6 d8 e6-8a a4 90 f6 04 bf ed e0   ................
    00e0 - 36 0a 73 ce f7 ac e4 cf-b3 f0 66 54 95 d4 6f 20   6.s.......fT..o 

    Start Time: 1747181208
    Timeout   : 7200 (sec)
    Verify return code: 0 (ok)
    Extended master secret: no
    Max Early Data: 0
---
read R BLOCK
Received TLS Record
Header:
  Version = TLS 1.2 (0x303)
  Content Type = ApplicationData (23)
  Length = 282
  Inner Content Type = Handshake (22)
    NewSessionTicket, Length=261
        ticket_lifetime_hint=7200
        ticket_age_add=122127802
        ticket_nonce (len=8): 0000000000000001
        ticket (len=240): 5961686F6F21204A4150414E00000000E00A19EF9E08FC845DD76DD2DDBA6E9310DC503BB1130E7752B5353A2B47AD8A362162EB9A60788FD9560E04F2F8A7D4EB878CC24861ED437071E6743BABF8205A9108681D271A8FF574B5C4A0B5E44D8C43CF717C7EA264E274DADCFE1CD4C06DF8E05A06173A15178CDF19B0C866045BA7236DB198D09BAE118782A5004D0143E734FA6D737256BAFAE463C863499AFE80AEC4BBBD40456993F73E2F37C0337F41E86B3C26BD919330A697E5A928490FA084A002191D8EC46A4C015DF49642B1F65F2D9D0C7AA52BEDFCE0CB790B89AD183A7EC6E53B42853764CE1AA7CDA0
        No extensions

---
Post-Handshake New Session Ticket arrived:
SSL-Session:
    Protocol  : TLSv1.3
    Cipher    : TLS_AES_128_GCM_SHA256
    Session-ID: 10D13B3B58496CB32B0AEB96DD88A20584D51F8C40AD01EEE2D6D70EAAF07EB4
    Session-ID-ctx: 
    Resumption PSK: B353EBCCF3C9B25F1A4117F1E7A30A4E083B5FC928924B6E4CFBBAFB39F7A266
    PSK identity: None
    PSK identity hint: None
    SRP username: None
    TLS session ticket lifetime hint: 7200 (seconds)
    TLS session ticket:
    0000 - 59 61 68 6f 6f 21 20 4a-41 50 41 4e 00 00 00 00   Yahoo! JAPAN....
    0010 - e0 0a 19 ef 9e 08 fc 84-5d d7 6d d2 dd ba 6e 93   ........].m...n.
    0020 - 10 dc 50 3b b1 13 0e 77-52 b5 35 3a 2b 47 ad 8a   ..P;...wR.5:+G..
    0030 - 36 21 62 eb 9a 60 78 8f-d9 56 0e 04 f2 f8 a7 d4   6!b..`x..V......
    0040 - eb 87 8c c2 48 61 ed 43-70 71 e6 74 3b ab f8 20   ....Ha.Cpq.t;.. 
    0050 - 5a 91 08 68 1d 27 1a 8f-f5 74 b5 c4 a0 b5 e4 4d   Z..h.'...t.....M
    0060 - 8c 43 cf 71 7c 7e a2 64-e2 74 da dc fe 1c d4 c0   .C.q|~.d.t......
    0070 - 6d f8 e0 5a 06 17 3a 15-17 8c df 19 b0 c8 66 04   m..Z..:.......f.
    0080 - 5b a7 23 6d b1 98 d0 9b-ae 11 87 82 a5 00 4d 01   [.#m..........M.
    0090 - 43 e7 34 fa 6d 73 72 56-ba fa e4 63 c8 63 49 9a   C.4.msrV...c.cI.
    00a0 - fe 80 ae c4 bb bd 40 45-69 93 f7 3e 2f 37 c0 33   ......@Ei..>/7.3
    00b0 - 7f 41 e8 6b 3c 26 bd 91-93 30 a6 97 e5 a9 28 49   .A.k<&...0....(I
    00c0 - 0f a0 84 a0 02 19 1d 8e-c4 6a 4c 01 5d f4 96 42   .........jL.]..B
    00d0 - b1 f6 5f 2d 9d 0c 7a a5-2b ed fc e0 cb 79 0b 89   .._-..z.+....y..
    00e0 - ad 18 3a 7e c6 e5 3b 42-85 37 64 ce 1a a7 cd a0   ..:~..;B.7d.....

    Start Time: 1747181208
    Timeout   : 7200 (sec)
    Verify return code: 0 (ok)
    Extended master secret: no
    Max Early Data: 0
---
read R BLOCK
```

### メッセージの中身まで詳細に表示したい(-trace) TLS1.2
traceを付与
```
$ openssl s_client -connect www.yahoo.co.jp:443 -trace -tls1_2
Connecting to 182.22.28.252
CONNECTED(00000005)
Sent TLS Record
Header:
  Version = TLS 1.0 (0x301)
  Content Type = Handshake (22)
  Length = 216
    ClientHello, Length=212
      client_version=0x303 (TLS 1.2)
      Random:
        gmt_unix_time=0x594DF5F5
        random_bytes (len=28): 736628943D2737EA3BAC1A585E635A084DE514F95B1B4CC9EA535F49
      session_id (len=0): 
      cipher_suites (len=54)
        {0xC0, 0x2C} TLS_ECDHE_ECDSA_WITH_AES_256_GCM_SHA384
        {0xC0, 0x30} TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384
        {0x00, 0x9F} TLS_DHE_RSA_WITH_AES_256_GCM_SHA384
        {0xCC, 0xA9} TLS_ECDHE_ECDSA_WITH_CHACHA20_POLY1305_SHA256
        {0xCC, 0xA8} TLS_ECDHE_RSA_WITH_CHACHA20_POLY1305_SHA256
        {0xCC, 0xAA} TLS_DHE_RSA_WITH_CHACHA20_POLY1305_SHA256
        {0xC0, 0x2B} TLS_ECDHE_ECDSA_WITH_AES_128_GCM_SHA256
        {0xC0, 0x2F} TLS_ECDHE_RSA_WITH_AES_128_GCM_SHA256
        {0x00, 0x9E} TLS_DHE_RSA_WITH_AES_128_GCM_SHA256
        {0xC0, 0x24} TLS_ECDHE_ECDSA_WITH_AES_256_CBC_SHA384
        {0xC0, 0x28} TLS_ECDHE_RSA_WITH_AES_256_CBC_SHA384
        {0x00, 0x6B} TLS_DHE_RSA_WITH_AES_256_CBC_SHA256
        {0xC0, 0x23} TLS_ECDHE_ECDSA_WITH_AES_128_CBC_SHA256
        {0xC0, 0x27} TLS_ECDHE_RSA_WITH_AES_128_CBC_SHA256
        {0x00, 0x67} TLS_DHE_RSA_WITH_AES_128_CBC_SHA256
        {0xC0, 0x0A} TLS_ECDHE_ECDSA_WITH_AES_256_CBC_SHA
        {0xC0, 0x14} TLS_ECDHE_RSA_WITH_AES_256_CBC_SHA
        {0x00, 0x39} TLS_DHE_RSA_WITH_AES_256_CBC_SHA
        {0xC0, 0x09} TLS_ECDHE_ECDSA_WITH_AES_128_CBC_SHA
        {0xC0, 0x13} TLS_ECDHE_RSA_WITH_AES_128_CBC_SHA
        {0x00, 0x33} TLS_DHE_RSA_WITH_AES_128_CBC_SHA
        {0x00, 0x9D} TLS_RSA_WITH_AES_256_GCM_SHA384
        {0x00, 0x9C} TLS_RSA_WITH_AES_128_GCM_SHA256
        {0x00, 0x3D} TLS_RSA_WITH_AES_256_CBC_SHA256
        {0x00, 0x3C} TLS_RSA_WITH_AES_128_CBC_SHA256
        {0x00, 0x35} TLS_RSA_WITH_AES_256_CBC_SHA
        {0x00, 0x2F} TLS_RSA_WITH_AES_128_CBC_SHA
      compression_methods (len=1)
        No Compression (0x00)
      extensions, length = 117
        extension_type=renegotiate(65281), length=1
            <EMPTY>
        extension_type=server_name(0), length=20
          0000 - 00 12 00 00 0f 77 77 77-2e 79 61 68 6f 6f 2e   .....www.yahoo.
          000f - 63 6f 2e 6a 70                                 co.jp
        extension_type=ec_point_formats(11), length=4
          uncompressed (0)
          ansiX962_compressed_prime (1)
          ansiX962_compressed_char2 (2)
        extension_type=supported_groups(10), length=12
          ecdh_x25519 (29)
          secp256r1 (P-256) (23)
          ecdh_x448 (30)
          secp521r1 (P-521) (25)
          secp384r1 (P-384) (24)
        extension_type=session_ticket(35), length=0
        extension_type=encrypt_then_mac(22), length=0
        extension_type=extended_master_secret(23), length=0
        extension_type=signature_algorithms(13), length=48
          ecdsa_secp256r1_sha256 (0x0403)
          ecdsa_secp384r1_sha384 (0x0503)
          ecdsa_secp521r1_sha512 (0x0603)
          ed25519 (0x0807)
          ed448 (0x0808)
          ecdsa_brainpoolP256r1_sha256 (0x081a)
          ecdsa_brainpoolP384r1_sha384 (0x081b)
          ecdsa_brainpoolP512r1_sha512 (0x081c)
          rsa_pss_pss_sha256 (0x0809)
          rsa_pss_pss_sha384 (0x080a)
          rsa_pss_pss_sha512 (0x080b)
          rsa_pss_rsae_sha256 (0x0804)
          rsa_pss_rsae_sha384 (0x0805)
          rsa_pss_rsae_sha512 (0x0806)
          rsa_pkcs1_sha256 (0x0401)
          rsa_pkcs1_sha384 (0x0501)
          rsa_pkcs1_sha512 (0x0601)
          ecdsa_sha224 (0x0303)
          rsa_pkcs1_sha224 (0x0301)
          dsa_sha224 (0x0302)
          dsa_sha256 (0x0402)
          dsa_sha384 (0x0502)
          dsa_sha512 (0x0602)

Received TLS Record
Header:
  Version = TLS 1.2 (0x303)
  Content Type = Handshake (22)
  Length = 69
    ServerHello, Length=65
      server_version=0x303 (TLS 1.2)
      Random:
        gmt_unix_time=0x6F6DB67A
        random_bytes (len=28): 95182E23174ABCB1589B8C3AF1CB706B8205C0D7444F574E47524401
      session_id (len=0): 
      cipher_suite {0xC0, 0x2F} TLS_ECDHE_RSA_WITH_AES_128_GCM_SHA256
      compression_method: No Compression (0x00)
      extensions, length = 25
        extension_type=renegotiate(65281), length=1
            <EMPTY>
        extension_type=server_name(0), length=0
        extension_type=ec_point_formats(11), length=4
          uncompressed (0)
          ansiX962_compressed_prime (1)
          ansiX962_compressed_char2 (2)
        extension_type=session_ticket(35), length=0
        extension_type=extended_master_secret(23), length=0

Received TLS Record
Header:
  Version = TLS 1.2 (0x303)
  Content Type = Handshake (22)
  Length = 5133
    Certificate, Length=5129
      certificate_list, length=5126
        ASN.1Cert, length=3837
------details-----
Certificate:
    Data:
        Version: 3 (0x2)
        Serial Number:
            57:1a:fe:8a:65:74:c4:af:2b:ce:69:77:e7:e9:8e:ad:0b:0c:9d:ae
        Signature Algorithm: sha256WithRSAEncryption
        Issuer: C = JP, O = "Cybertrust Japan Co., Ltd.", CN = Cybertrust Japan SureServer CA G4
        Validity
            Not Before: Apr 15 07:20:27 2025 GMT
            Not After : May 14 14:59:00 2026 GMT
        Subject: C = JP, ST = Tokyo, L = Chiyoda-ku, O = LY Corporation, CN = edge01.yahoo.co.jp
        Subject Public Key Info:
            Public Key Algorithm: rsaEncryption
                Public-Key: (2048 bit)
                Modulus:
                    00:d3:77:fe:92:fb:a1:ab:84:0d:dd:eb:ba:57:8d:
                    8c:b8:01:44:78:a5:6b:db:22:6f:d4:88:dd:70:13:
                    a6:26:d8:b9:9c:4b:55:d6:d1:f4:99:59:5b:70:6c:
                    00:02:86:c8:09:5b:4b:6a:13:64:8b:e4:83:21:c3:
                    de:62:2b:37:55:38:71:74:16:97:42:11:ba:87:03:
                    b4:80:56:4d:6c:2b:50:f6:ea:a9:39:1d:4b:0b:b3:
                    29:73:e7:0a:35:f4:1d:ba:bf:40:5c:77:59:2d:8f:
                    05:8b:2c:c3:35:59:dc:83:6c:28:85:21:89:cc:ef:
                    08:41:fd:85:9b:f5:b4:cb:79:a2:52:49:16:2b:52:
                    e9:73:e3:57:55:c8:c6:a5:ce:05:b7:c4:04:75:6a:
                    e8:da:78:b7:48:38:8e:bd:f6:18:d2:f1:27:78:b6:
                    8e:b2:db:87:99:66:6e:fc:65:b8:ec:65:ae:a1:9e:
                    25:3d:bd:65:d3:aa:5f:ba:2e:0a:2e:8b:d4:90:5a:
                    03:ec:3f:e1:a9:41:ea:36:ef:91:6b:1d:0f:9d:d1:
                    df:36:57:00:af:9e:9f:62:74:ed:8e:f2:f4:c5:9e:
                    dd:f4:35:b8:64:0d:f4:05:4b:e4:e7:da:5d:3f:c8:
                    3c:f3:5c:c1:c9:67:9a:69:2f:98:e5:88:7e:28:2c:
                    98:bf
                Exponent: 65537 (0x10001)
        X509v3 extensions:
            X509v3 Basic Constraints: critical
                CA:FALSE
            X509v3 Certificate Policies: 
                Policy: 2.23.140.1.2.2
                Policy: 1.2.392.200081.1.23.1
                  CPS: https://www.cybertrust.ne.jp/ssl/repository/index.html
            X509v3 Subject Alternative Name: 
                DNS:edge01.yahoo.co.jp, DNS:*.yahoo.co.jp, DNS:*.yahooapis.jp, DNS:*.ane.yahoo.co.jp, DNS:*.auctions.yahoo.co.jp, DNS:*.auctions.yahooapis.jp, DNS:*.box.yahooapis.jp, DNS:*.bspace.jp, DNS:*.bylines.news.yahoo.co.jp, DNS:*.c.yimg.jp, DNS:*.carnavi.yahooapis.jp, DNS:*.carview.co.jp, DNS:*.carview.yahoo.co.jp, DNS:*.chiebukuro.yahoo.co.jp, DNS:*.clorder.yahoo.co.jp, DNS:*.cvw.jp, DNS:*.digitalguide.jp, DNS:*.east.edge.storage-yahoo.jp, DNS:*.east.edge.storage-yahoobox.jp, DNS:*.edge.storage-yahoo.jp, DNS:*.edit.yahooapis.jp, DNS:*.finance.yahoo.co.jp, DNS:*.geocities.jp, DNS:*.global.edge.storage-yahoo.jp, DNS:*.gyao.yahoo.co.jp, DNS:*.jobcatalog.yahoo.co.jp, DNS:*.listing.yahoo.co.jp, DNS:*.loco.yahoo.co.jp, DNS:*.lycorp.co.jp, DNS:*.mail.yahoo.co.jp, DNS:*.marketing.yahoo.co.jp, DNS:*.mkcloud-api.carview.co.jp, DNS:*.mkimg.carview.co.jp, DNS:*.ms.yahoo.co.jp, DNS:*.lycorp-security.jp, DNS:*.news.yahoo.co.jp, DNS:*.news.yahooapis.jp, DNS:*.order.yahoo.co.jp, DNS:*.points.yahoo.co.jp, DNS:*.psi.yahoo.co.jp, DNS:*.push.yahooapis.jp, DNS:activity.travel.yahoo-net.jp, DNS:*.shopping.c.yimg.jp, DNS:*.shopping.srv.yimg.jp, DNS:*.shopping.yahoo.co.jp, DNS:*.shopping.yahooapis.jp, DNS:*.snsimg.carview.co.jp, DNS:*.store.yahoo.co.jp, DNS:*.travel.yahoo.co.jp, DNS:*.wallet.yahoo.co.jp, DNS:*.wallet.yahooapis.jp, DNS:*.webhosting.yahoo.co.jp, DNS:*.west.edge.storage-yahoo.jp, DNS:*.west.edge.storage-yahoobox.jp, DNS:*.xml.listing.yahoo.co.jp, DNS:*.yahoo-help.jp, DNS:*.yahoo-labs.jp, DNS:*.yahoo-net.jp, DNS:*.yahoo.jp, DNS:*.yahoobox.jp, DNS:*.yimg.jp, DNS:*.yjtag.jp, DNS:*.yjtag.yahoo.co.jp, DNS:*.ys-insurance.co.jp, DNS:*.search.yahooapis.jp, DNS:add.dir.yahoo.co.jp, DNS:api.y.clorder.yahoo.co.jp, DNS:arc.help.yahoo.co.jp, DNS:biztx.points.yahooapis.jp, DNS:carview.co.jp, DNS:cgi2.r-agent.yahoo.co.jp, DNS:cksync.pdsp.yahoo.co.jp, DNS:cm.froma.yahoo.co.jp, DNS:compass.ymobile.yahoo.co.jp, DNS:custom.search.yahoo.co.jp, DNS:e.developer.yahoo.co.jp, DNS:forms.business.yahoo.co.jp, DNS:frame.games.yahoo.co.jp, DNS:hrm.grmtrez.yahoo.co.jp, DNS:im.ov.yahoo.co.jp, DNS:info.hatalike.yahoo.co.jp, DNS:movie.chocotle.yahoo.co.jp, DNS:online.security.yahoo.co.jp, DNS:poiedit.map.yahoo.co.jp, DNS:portal.yadui.business.yahoo.co.jp, DNS:ssl-tools.kainavi.search.yahoo.co.jp, DNS:ssl.api.olp.yahooapis.jp, DNS:ssl.map.srv.yimg.jp, DNS:www.bosaiguide.jp, DNS:www.lohaco.yahoo.co.jp, DNS:www.search311.jp, DNS:www.sp-hinan.jp, DNS:www.techbasevn.com, DNS:yahoo.co.jp, DNS:yahoo.jp, DNS:yj.pn, DNS:yjtag.jp
            Authority Information Access: 
                OCSP - URI:http://ssocsp.cybertrust.ne.jp/OcspServer
                CA Issuers - URI:http://crl.cybertrust.ne.jp/SureServer/ovcag4/ovcag4.crt
            X509v3 Key Usage: critical
                Digital Signature, Key Encipherment
            X509v3 Extended Key Usage: 
                TLS Web Server Authentication, TLS Web Client Authentication
            X509v3 Authority Key Identifier: 
                62:A7:D2:DA:DE:85:B6:92:F1:85:BC:F6:E8:95:9D:75:A0:FA:4E:1F
            X509v3 CRL Distribution Points: 
                Full Name:
                  URI:http://crl.cybertrust.ne.jp/SureServer/ovcag4/cdp.crl

            X509v3 Subject Key Identifier: 
                7C:AA:2D:DA:E1:C6:26:CD:78:B6:B8:BC:50:E4:87:35:43:7E:D4:21
            CT Precertificate SCTs: 
                Signed Certificate Timestamp:
                    Version   : v1 (0x0)
                    Log ID    : 0E:57:94:BC:F3:AE:A9:3E:33:1B:2C:99:07:B3:F7:90:
                                DF:9B:C2:3D:71:32:25:DD:21:A9:25:AC:61:C5:4E:21
                    Timestamp : Apr 15 07:43:33.244 2025 GMT
                    Extensions: none
                    Signature : ecdsa-with-SHA256
                                30:45:02:21:00:A2:CB:CB:3D:8E:F1:12:A4:C5:6D:86:
                                8C:91:70:68:07:28:C0:33:07:0E:4A:7F:83:EF:27:97:
                                64:02:30:3E:A3:02:20:46:E8:82:A7:B5:B0:8E:1C:F4:
                                03:F4:3D:9C:90:5F:6F:45:CC:1F:50:56:35:20:B2:A6:
                                A0:5D:63:5A:CB:17:D6
                Signed Certificate Timestamp:
                    Version   : v1 (0x0)
                    Log ID    : 96:97:64:BF:55:58:97:AD:F7:43:87:68:37:08:42:77:
                                E9:F0:3A:D5:F6:A4:F3:36:6E:46:A4:3F:0F:CA:A9:C6
                    Timestamp : Apr 15 07:43:35.013 2025 GMT
                    Extensions: none
                    Signature : ecdsa-with-SHA256
                                30:44:02:20:4A:19:AA:29:CE:35:18:74:13:7F:47:1E:
                                2D:7B:68:7F:4D:34:DB:25:48:66:A4:33:8B:92:3B:CF:
                                6A:BD:54:84:02:20:14:30:38:DA:49:07:37:C3:8A:08:
                                1B:C5:22:94:A3:54:87:3A:FB:D8:94:2D:38:8F:4F:82:
                                01:1A:87:E2:7E:B8
                Signed Certificate Timestamp:
                    Version   : v1 (0x0)
                    Log ID    : 19:86:D4:C7:28:AA:6F:FE:BA:03:6F:78:2A:4D:01:91:
                                AA:CE:2D:72:31:0F:AE:CE:5D:70:41:2D:25:4C:C7:D4
                    Timestamp : Apr 15 07:43:36.309 2025 GMT
                    Extensions: none
                    Signature : ecdsa-with-SHA256
                                30:45:02:20:37:FB:B2:31:0E:0F:72:E1:D1:BA:25:AD:
                                68:F0:0B:E4:05:CB:1B:2E:DE:7D:52:13:84:05:9E:E6:
                                5D:BF:B1:07:02:21:00:DA:1E:E3:2A:19:4B:75:F4:44:
                                87:94:24:21:ED:C6:0B:F2:56:3E:77:07:1D:D4:F6:A7:
                                7C:52:D9:FA:21:2F:8A
    Signature Algorithm: sha256WithRSAEncryption
    Signature Value:
        7f:32:f1:c3:7a:d5:a6:7a:82:2a:73:e7:50:cc:4b:ab:b5:03:
        5d:e2:0f:c2:9e:0e:27:f9:87:fe:8f:df:94:9e:bb:0e:df:8a:
        47:3d:fc:be:e2:47:cc:6a:d3:da:02:e0:71:1a:ff:dc:2c:06:
        1e:01:61:3c:b5:92:51:ce:7e:bb:0e:10:4a:bc:69:9a:6a:a4:
        33:88:a8:93:d9:00:67:d2:18:bd:3e:22:de:b7:b1:68:30:ba:
        84:7c:3e:56:ee:6e:f2:1b:1f:21:52:5c:29:c7:0a:70:21:fd:
        b4:74:e7:70:8c:1c:cd:1e:5b:a4:65:57:f8:53:fc:8c:87:5b:
        7e:85:b1:df:05:00:08:5e:c6:26:84:cf:78:15:e1:3b:8f:61:
        0d:af:6c:73:7c:9c:a2:ca:fa:95:bd:5d:84:b9:41:17:ed:7f:
        9f:0d:5f:cb:d6:66:ea:75:b1:34:ea:74:aa:80:89:f2:8e:f6:
        e1:76:eb:d6:07:ff:9e:f4:75:ef:13:02:6f:1e:b5:61:eb:c5:
        a7:f3:cb:d8:31:e4:e4:ca:c6:79:a3:af:99:a3:cd:c1:27:4f:
        bf:8d:51:48:21:21:29:33:f4:33:76:a1:77:d7:ce:32:f4:81:
        f2:93:a4:0a:5b:21:b5:15:7b:f8:eb:2b:53:2d:aa:e0:1a:c5:
        0d:e1:35:82
-----BEGIN CERTIFICATE-----
MIIO+TCCDeGgAwIBAgIUVxr+imV0xK8rzml35+mOrQsMna4wDQYJKoZIhvcNAQEL
BQAwXjELMAkGA1UEBhMCSlAxIzAhBgNVBAoTGkN5YmVydHJ1c3QgSmFwYW4gQ28u
LCBMdGQuMSowKAYDVQQDEyFDeWJlcnRydXN0IEphcGFuIFN1cmVTZXJ2ZXIgQ0Eg
RzQwHhcNMjUwNDE1MDcyMDI3WhcNMjYwNTE0MTQ1OTAwWjBoMQswCQYDVQQGEwJK
UDEOMAwGA1UECBMFVG9reW8xEzARBgNVBAcTCkNoaXlvZGEta3UxFzAVBgNVBAoT
DkxZIENvcnBvcmF0aW9uMRswGQYDVQQDExJlZGdlMDEueWFob28uY28uanAwggEi
MA0GCSqGSIb3DQEBAQUAA4IBDwAwggEKAoIBAQDTd/6S+6GrhA3d67pXjYy4AUR4
pWvbIm/UiN1wE6Ym2LmcS1XW0fSZWVtwbAAChsgJW0tqE2SL5IMhw95iKzdVOHF0
FpdCEbqHA7SAVk1sK1D26qk5HUsLsylz5wo19B26v0Bcd1ktjwWLLMM1WdyDbCiF
IYnM7whB/YWb9bTLeaJSSRYrUulz41dVyMalzgW3xAR1aujaeLdIOI699hjS8Sd4
to6y24eZZm78ZbjsZa6hniU9vWXTql+6Lgoui9SQWgPsP+GpQeo275FrHQ+d0d82
VwCvnp9idO2O8vTFnt30NbhkDfQFS+Tn2l0/yDzzXMHJZ5ppL5jliH4oLJi/AgMB
AAGjggujMIILnzAMBgNVHRMBAf8EAjAAMGYGA1UdIARfMF0wCAYGZ4EMAQICMFEG
CSqDCIybEQEXATBEMEIGCCsGAQUFBwIBFjZodHRwczovL3d3dy5jeWJlcnRydXN0
Lm5lLmpwL3NzbC9yZXBvc2l0b3J5L2luZGV4Lmh0bWwwgghfBgNVHREEgghWMIII
UoISZWRnZTAxLnlhaG9vLmNvLmpwgg0qLnlhaG9vLmNvLmpwgg4qLnlhaG9vYXBp
cy5qcIIRKi5hbmUueWFob28uY28uanCCFiouYXVjdGlvbnMueWFob28uY28uanCC
FyouYXVjdGlvbnMueWFob29hcGlzLmpwghIqLmJveC55YWhvb2FwaXMuanCCCyou
YnNwYWNlLmpwghoqLmJ5bGluZXMubmV3cy55YWhvby5jby5qcIILKi5jLnlpbWcu
anCCFiouY2FybmF2aS55YWhvb2FwaXMuanCCDyouY2Fydmlldy5jby5qcIIVKi5j
YXJ2aWV3LnlhaG9vLmNvLmpwghgqLmNoaWVidWt1cm8ueWFob28uY28uanCCFSou
Y2xvcmRlci55YWhvby5jby5qcIIIKi5jdncuanCCESouZGlnaXRhbGd1aWRlLmpw
ghwqLmVhc3QuZWRnZS5zdG9yYWdlLXlhaG9vLmpwgh8qLmVhc3QuZWRnZS5zdG9y
YWdlLXlhaG9vYm94LmpwghcqLmVkZ2Uuc3RvcmFnZS15YWhvby5qcIITKi5lZGl0
LnlhaG9vYXBpcy5qcIIVKi5maW5hbmNlLnlhaG9vLmNvLmpwgg4qLmdlb2NpdGll
cy5qcIIeKi5nbG9iYWwuZWRnZS5zdG9yYWdlLXlhaG9vLmpwghIqLmd5YW8ueWFo
b28uY28uanCCGCouam9iY2F0YWxvZy55YWhvby5jby5qcIIVKi5saXN0aW5nLnlh
aG9vLmNvLmpwghIqLmxvY28ueWFob28uY28uanCCDioubHljb3JwLmNvLmpwghIq
Lm1haWwueWFob28uY28uanCCFyoubWFya2V0aW5nLnlhaG9vLmNvLmpwghsqLm1r
Y2xvdWQtYXBpLmNhcnZpZXcuY28uanCCFSoubWtpbWcuY2Fydmlldy5jby5qcIIQ
Ki5tcy55YWhvby5jby5qcIIUKi5seWNvcnAtc2VjdXJpdHkuanCCEioubmV3cy55
YWhvby5jby5qcIITKi5uZXdzLnlhaG9vYXBpcy5qcIITKi5vcmRlci55YWhvby5j
by5qcIIUKi5wb2ludHMueWFob28uY28uanCCESoucHNpLnlhaG9vLmNvLmpwghMq
LnB1c2gueWFob29hcGlzLmpwghxhY3Rpdml0eS50cmF2ZWwueWFob28tbmV0Lmpw
ghQqLnNob3BwaW5nLmMueWltZy5qcIIWKi5zaG9wcGluZy5zcnYueWltZy5qcIIW
Ki5zaG9wcGluZy55YWhvby5jby5qcIIXKi5zaG9wcGluZy55YWhvb2FwaXMuanCC
Fiouc25zaW1nLmNhcnZpZXcuY28uanCCEyouc3RvcmUueWFob28uY28uanCCFCou
dHJhdmVsLnlhaG9vLmNvLmpwghQqLndhbGxldC55YWhvby5jby5qcIIVKi53YWxs
ZXQueWFob29hcGlzLmpwghgqLndlYmhvc3RpbmcueWFob28uY28uanCCHCoud2Vz
dC5lZGdlLnN0b3JhZ2UteWFob28uanCCHyoud2VzdC5lZGdlLnN0b3JhZ2UteWFo
b29ib3guanCCGSoueG1sLmxpc3RpbmcueWFob28uY28uanCCDyoueWFob28taGVs
cC5qcIIPKi55YWhvby1sYWJzLmpwgg4qLnlhaG9vLW5ldC5qcIIKKi55YWhvby5q
cIINKi55YWhvb2JveC5qcIIJKi55aW1nLmpwggoqLnlqdGFnLmpwghMqLnlqdGFn
LnlhaG9vLmNvLmpwghQqLnlzLWluc3VyYW5jZS5jby5qcIIVKi5zZWFyY2gueWFo
b29hcGlzLmpwghNhZGQuZGlyLnlhaG9vLmNvLmpwghlhcGkueS5jbG9yZGVyLnlh
aG9vLmNvLmpwghRhcmMuaGVscC55YWhvby5jby5qcIIZYml6dHgucG9pbnRzLnlh
aG9vYXBpcy5qcIINY2Fydmlldy5jby5qcIIYY2dpMi5yLWFnZW50LnlhaG9vLmNv
Lmpwghdja3N5bmMucGRzcC55YWhvby5jby5qcIIUY20uZnJvbWEueWFob28uY28u
anCCG2NvbXBhc3MueW1vYmlsZS55YWhvby5jby5qcIIZY3VzdG9tLnNlYXJjaC55
YWhvby5jby5qcIIXZS5kZXZlbG9wZXIueWFob28uY28uanCCGmZvcm1zLmJ1c2lu
ZXNzLnlhaG9vLmNvLmpwghdmcmFtZS5nYW1lcy55YWhvby5jby5qcIIXaHJtLmdy
bXRyZXoueWFob28uY28uanCCEWltLm92LnlhaG9vLmNvLmpwghlpbmZvLmhhdGFs
aWtlLnlhaG9vLmNvLmpwghptb3ZpZS5jaG9jb3RsZS55YWhvby5jby5qcIIbb25s
aW5lLnNlY3VyaXR5LnlhaG9vLmNvLmpwghdwb2llZGl0Lm1hcC55YWhvby5jby5q
cIIhcG9ydGFsLnlhZHVpLmJ1c2luZXNzLnlhaG9vLmNvLmpwgiRzc2wtdG9vbHMu
a2FpbmF2aS5zZWFyY2gueWFob28uY28uanCCGHNzbC5hcGkub2xwLnlhaG9vYXBp
cy5qcIITc3NsLm1hcC5zcnYueWltZy5qcIIRd3d3LmJvc2FpZ3VpZGUuanCCFnd3
dy5sb2hhY28ueWFob28uY28uanCCEHd3dy5zZWFyY2gzMTEuanCCD3d3dy5zcC1o
aW5hbi5qcIISd3d3LnRlY2hiYXNldm4uY29tggt5YWhvby5jby5qcIIIeWFob28u
anCCBXlqLnBuggh5anRhZy5qcDCBiwYIKwYBBQUHAQEEfzB9MDUGCCsGAQUFBzAB
hilodHRwOi8vc3NvY3NwLmN5YmVydHJ1c3QubmUuanAvT2NzcFNlcnZlcjBEBggr
BgEFBQcwAoY4aHR0cDovL2NybC5jeWJlcnRydXN0Lm5lLmpwL1N1cmVTZXJ2ZXIv
b3ZjYWc0L292Y2FnNC5jcnQwDgYDVR0PAQH/BAQDAgWgMB0GA1UdJQQWMBQGCCsG
AQUFBwMBBggrBgEFBQcDAjAfBgNVHSMEGDAWgBRip9La3oW2kvGFvPbolZ11oPpO
HzBGBgNVHR8EPzA9MDugOaA3hjVodHRwOi8vY3JsLmN5YmVydHJ1c3QubmUuanAv
U3VyZVNlcnZlci9vdmNhZzQvY2RwLmNybDAdBgNVHQ4EFgQUfKot2uHGJs14tri8
UOSHNUN+1CEwggF9BgorBgEEAdZ5AgQCBIIBbQSCAWkBZwB2AA5XlLzzrqk+Mxss
mQez95Dfm8I9cTIl3SGpJaxhxU4hAAABljhnQXwAAAQDAEcwRQIhAKLLyz2O8RKk
xW2GjJFwaAcowDMHDkp/g+8nl2QCMD6jAiBG6IKntbCOHPQD9D2ckF9vRcwfUFY1
ILKmoF1jWssX1gB1AJaXZL9VWJet90OHaDcIQnfp8DrV9qTzNm5GpD8PyqnGAAAB
ljhnSGUAAAQDAEYwRAIgShmqKc41GHQTf0ceLXtof0002yVIZqQzi5I7z2q9VIQC
IBQwONpJBzfDiggbxSKUo1SHOvvYlC04j0+CARqH4n64AHYAGYbUxyiqb/66A294
Kk0BkarOLXIxD67OXXBBLSVMx9QAAAGWOGdNdQAABAMARzBFAiA3+7IxDg9y4dG6
Ja1o8AvkBcsbLt59UhOEBZ7mXb+xBwIhANoe4yoZS3X0RIeUJCHtxgvyVj53Bx3U
9qd8Utn6IS+KMA0GCSqGSIb3DQEBCwUAA4IBAQB/MvHDetWmeoIqc+dQzEurtQNd
4g/Cng4n+Yf+j9+UnrsO34pHPfy+4kfMatPaAuBxGv/cLAYeAWE8tZJRzn67DhBK
vGmaaqQziKiT2QBn0hi9PiLet7FoMLqEfD5W7m7yGx8hUlwpxwpwIf20dOdwjBzN
HlukZVf4U/yMh1t+hbHfBQAIXsYmhM94FeE7j2ENr2xzfJyiyvqVvV2EuUEX7X+f
DV/L1mbqdbE06nSqgInyjvbhduvWB/+e9HXvEwJvHrVh68Wn88vYMeTkysZ5o6+Z
o83BJ0+/jVFIISEpM/QzdqF3184y9IHyk6QKWyG1FXv46ytTLargGsUN4TWC
-----END CERTIFICATE-----
------------------
        ASN.1Cert, length=1283
------details-----
Certificate:
    Data:
        Version: 3 (0x2)
        Serial Number:
            22:b9:b1:a0:74:64:18:57:f7:a0:13:32:db:42:b9:ec
        Signature Algorithm: sha256WithRSAEncryption
        Issuer: C = JP, O = "SECOM Trust Systems CO.,LTD.", OU = Security Communication RootCA2
        Validity
            Not Before: Dec 13 05:57:30 2023 GMT
            Not After : May 29 05:00:39 2029 GMT
        Subject: C = JP, O = "Cybertrust Japan Co., Ltd.", CN = Cybertrust Japan SureServer CA G4
        Subject Public Key Info:
            Public Key Algorithm: rsaEncryption
                Public-Key: (2048 bit)
                Modulus:
                    00:cb:6e:9c:59:a8:b1:3f:08:c4:19:15:14:ff:8e:
                    9e:41:a4:71:59:9b:ba:2f:a1:75:50:65:19:98:67:
                    8a:78:95:96:e0:21:8a:09:b6:59:4c:71:a7:85:f9:
                    57:70:7f:40:a2:4b:66:67:80:b3:09:b3:c4:62:97:
                    68:30:b3:72:89:98:c5:74:f2:80:d5:dc:4c:b2:3e:
                    20:cc:91:8a:c1:0e:ed:5d:4d:5c:51:d4:8d:21:25:
                    29:a6:35:2f:30:80:f7:f7:a6:95:d9:e6:46:35:fa:
                    07:d6:6d:e7:15:ca:e6:ad:76:58:e2:16:90:91:02:
                    13:0c:0a:92:ee:fb:b6:fb:4a:64:f4:4a:68:23:42:
                    1a:c6:79:1e:36:bb:3c:1b:34:ee:32:e8:13:4a:cc:
                    b9:92:d0:64:d4:04:07:45:ba:dd:ab:6d:28:60:86:
                    cc:49:39:d2:50:e3:fb:04:34:52:55:1b:42:4d:f3:
                    00:4b:2f:74:4e:97:a3:5a:99:cb:d9:7b:f3:75:5a:
                    e3:4b:d2:c7:75:6a:84:66:1b:e2:35:90:ae:0d:82:
                    ac:0b:49:70:a4:0d:48:9d:26:f7:2c:49:55:54:03:
                    c2:94:10:c0:6c:47:3b:91:26:42:fd:4b:18:91:31:
                    01:27:a0:39:7c:e1:ce:a0:ab:e7:28:b0:10:27:d2:
                    ac:eb
                Exponent: 65537 (0x10001)
        X509v3 extensions:
            X509v3 Subject Key Identifier: 
                62:A7:D2:DA:DE:85:B6:92:F1:85:BC:F6:E8:95:9D:75:A0:FA:4E:1F
            X509v3 Authority Key Identifier: 
                0A:85:A9:77:65:05:98:7C:40:81:F8:0F:97:2C:38:F1:0A:EC:3C:CF
            X509v3 Basic Constraints: critical
                CA:TRUE, pathlen:0
            X509v3 Key Usage: critical
                Certificate Sign, CRL Sign
            X509v3 CRL Distribution Points: 
                Full Name:
                  URI:http://repository.secomtrust.net/SC-Root2/SCRoot2CRL.crl

            X509v3 Certificate Policies: 
                Policy: 2.23.140.1.2.2
                Policy: 1.2.392.200091.100.901.4
                  CPS: https://repository.secomtrust.net/SC-Root2/
            Authority Information Access: 
                OCSP - URI:http://scrootca2.ocsp.secomtrust.net
                CA Issuers - URI:http://repository.secomtrust.net/SC-Root2/SCRoot2ca.cer
            X509v3 Extended Key Usage: 
                TLS Web Server Authentication, TLS Web Client Authentication
    Signature Algorithm: sha256WithRSAEncryption
    Signature Value:
        3e:7f:43:75:49:3a:f1:b0:a3:44:41:05:ca:a2:a6:c6:a1:2e:
        70:05:4d:dd:7a:21:9c:d0:11:00:2d:71:12:5e:18:9a:30:18:
        71:5c:55:7b:eb:23:76:dc:cf:61:0c:10:4f:81:0f:f2:2d:f1:
        7f:9e:68:dd:50:de:c1:2b:f0:46:60:f8:77:86:9a:a0:56:8b:
        06:92:8a:f7:d1:e1:e1:f2:27:1a:c8:af:33:90:d1:3f:3b:ff:
        42:26:a5:f7:e5:82:9f:2e:b7:af:96:6b:f6:c6:a8:0d:0a:59:
        75:f8:a9:0f:74:81:03:6e:09:7e:d8:e3:3c:ab:27:e9:48:cc:
        bf:22:95:72:84:33:89:1a:83:31:06:1d:b8:ad:47:50:be:e8:
        17:c1:b6:3c:0e:9c:13:2a:15:7f:ad:11:a7:f2:e5:bd:ef:cb:
        33:74:e0:22:6d:7b:24:d1:4a:50:04:d2:81:c5:f0:e4:7a:f6:
        4a:86:e5:ea:de:80:d0:52:20:2d:20:2c:47:2f:29:99:50:e6:
        53:9b:d2:18:9a:e6:9d:06:fd:53:b6:9d:99:33:42:b5:82:aa:
        b5:96:e2:39:7d:86:db:6b:d2:97:d0:66:30:b9:f0:47:cd:a3:
        0d:5b:82:df:cb:a0:db:ea:57:09:86:11:c5:ff:77:c7:ea:a7:
        e8:5b:ef:cf
-----BEGIN CERTIFICATE-----
MIIE/zCCA+egAwIBAgIQIrmxoHRkGFf3oBMy20K57DANBgkqhkiG9w0BAQsFADBd
MQswCQYDVQQGEwJKUDElMCMGA1UEChMcU0VDT00gVHJ1c3QgU3lzdGVtcyBDTy4s
TFRELjEnMCUGA1UECxMeU2VjdXJpdHkgQ29tbXVuaWNhdGlvbiBSb290Q0EyMB4X
DTIzMTIxMzA1NTczMFoXDTI5MDUyOTA1MDAzOVowXjELMAkGA1UEBhMCSlAxIzAh
BgNVBAoTGkN5YmVydHJ1c3QgSmFwYW4gQ28uLCBMdGQuMSowKAYDVQQDEyFDeWJl
cnRydXN0IEphcGFuIFN1cmVTZXJ2ZXIgQ0EgRzQwggEiMA0GCSqGSIb3DQEBAQUA
A4IBDwAwggEKAoIBAQDLbpxZqLE/CMQZFRT/jp5BpHFZm7ovoXVQZRmYZ4p4lZbg
IYoJtllMcaeF+Vdwf0CiS2ZngLMJs8Ril2gws3KJmMV08oDV3EyyPiDMkYrBDu1d
TVxR1I0hJSmmNS8wgPf3ppXZ5kY1+gfWbecVyuatdljiFpCRAhMMCpLu+7b7SmT0
SmgjQhrGeR42uzwbNO4y6BNKzLmS0GTUBAdFut2rbShghsxJOdJQ4/sENFJVG0JN
8wBLL3ROl6NamcvZe/N1WuNL0sd1aoRmG+I1kK4NgqwLSXCkDUidJvcsSVVUA8KU
EMBsRzuRJkL9SxiRMQEnoDl84c6gq+cosBAn0qzrAgMBAAGjggG4MIIBtDAdBgNV
HQ4EFgQUYqfS2t6FtpLxhbz26JWddaD6Th8wHwYDVR0jBBgwFoAUCoWpd2UFmHxA
gfgPlyw48QrsPM8wEgYDVR0TAQH/BAgwBgEB/wIBADAOBgNVHQ8BAf8EBAMCAQYw
SQYDVR0fBEIwQDA+oDygOoY4aHR0cDovL3JlcG9zaXRvcnkuc2Vjb210cnVzdC5u
ZXQvU0MtUm9vdDIvU0NSb290MkNSTC5jcmwwXAYDVR0gBFUwUzAIBgZngQwBAgIw
RwYKKoMIjJsbZIcFBDA5MDcGCCsGAQUFBwIBFitodHRwczovL3JlcG9zaXRvcnku
c2Vjb210cnVzdC5uZXQvU0MtUm9vdDIvMIGFBggrBgEFBQcBAQR5MHcwMAYIKwYB
BQUHMAGGJGh0dHA6Ly9zY3Jvb3RjYTIub2NzcC5zZWNvbXRydXN0Lm5ldDBDBggr
BgEFBQcwAoY3aHR0cDovL3JlcG9zaXRvcnkuc2Vjb210cnVzdC5uZXQvU0MtUm9v
dDIvU0NSb290MmNhLmNlcjAdBgNVHSUEFjAUBggrBgEFBQcDAQYIKwYBBQUHAwIw
DQYJKoZIhvcNAQELBQADggEBAD5/Q3VJOvGwo0RBBcqipsahLnAFTd16IZzQEQAt
cRJeGJowGHFcVXvrI3bcz2EMEE+BD/It8X+eaN1Q3sEr8EZg+HeGmqBWiwaSivfR
4eHyJxrIrzOQ0T87/0Impfflgp8ut6+Wa/bGqA0KWXX4qQ90gQNuCX7Y4zyrJ+lI
zL8ilXKEM4kagzEGHbitR1C+6BfBtjwOnBMqFX+tEafy5b3vyzN04CJteyTRSlAE
0oHF8OR69kqG5eregNBSIC0gLEcvKZlQ5lOb0hia5p0G/VO2nZkzQrWCqrWW4jl9
httr0pfQZjC58EfNow1bgt/LoNvqVwmGEcX/d8fqp+hb788=
-----END CERTIFICATE-----
------------------

depth=2 C=JP, O=SECOM Trust Systems CO.,LTD., OU=Security Communication RootCA2
verify return:1
depth=1 C=JP, O=Cybertrust Japan Co., Ltd., CN=Cybertrust Japan SureServer CA G4
verify return:1
depth=0 C=JP, ST=Tokyo, L=Chiyoda-ku, O=LY Corporation, CN=edge01.yahoo.co.jp
verify return:1
Received TLS Record
Header:
  Version = TLS 1.2 (0x303)
  Content Type = Handshake (22)
  Length = 300
    ServerKeyExchange, Length=296
      KeyExchangeAlgorithm=ECDHE
        named_curve: ecdh_x25519 (29)
        point (len=32): 69ED9E03C04D977BA93C4DEBE7D3142B927148CF78700F7A2185AAC6714B9F29
      Signature Algorithm: rsa_pss_rsae_sha256 (0x0804)
      Signature (len=256): BC832A6133A79C9B2C3A569923D3F6CCF4D409BC8A3448B54E28ED609588C8227814671B5D9BEE84A72E5D3520DB968BFF45BC0A330175FD68407B43AADEC418D92BD8ACFEDB6E9E2BE9D7D5BBF170588994931D5BBCA7E6AEF2375F6BE32D8210B2D4E4A1A8B5337310032DD5FDF576DDE360830F6A355B7010510FD17E1BCB831D150D07837B0B4ADBA7573D35A590D3AA6E6E112DDAED682DF2D611763520775BC2C4BFF17B145ACDB4C69AFB0D8A78CC7C118031D069596E519F99C719EEE1CA4B9121223E8E91098A694062AD1F074A035B5CE6198D8B2390D726E41CC5F32BE11CF0EE16D871E3CFAB6F41E8A2719F434AF09F6ED6C02E319C5D75D94B

Received TLS Record
Header:
  Version = TLS 1.2 (0x303)
  Content Type = Handshake (22)
  Length = 4
    ServerHelloDone, Length=0

Sent TLS Record
Header:
  Version = TLS 1.2 (0x303)
  Content Type = Handshake (22)
  Length = 37
    ClientKeyExchange, Length=33
      KeyExchangeAlgorithm=ECDHE
        ecdh_Yc (len=32): EA5BE43070BCEF31A590121374D8E4D6298DA6460A46184F564526A1FB8CA278

Sent TLS Record
Header:
  Version = TLS 1.2 (0x303)
  Content Type = ChangeCipherSpec (20)
  Length = 1
    change_cipher_spec (1)

Sent TLS Record
Header:
  Version = TLS 1.2 (0x303)
  Content Type = Handshake (22)
  Length = 40
    Finished, Length=12
      verify_data (len=12): 4E17379A86D1598737CAA78A

Received TLS Record
Header:
  Version = TLS 1.2 (0x303)
  Content Type = Handshake (22)
  Length = 234
    NewSessionTicket, Length=230
        ticket_lifetime_hint=7200
        ticket (len=224): 5961686F6F21204A4150414E00000000C3B4E4464BEBD3CF5AAC375AF1BA70F9A4A666D3C3DD5DE90BFA46FCB9D8F46E224762FA4515B5A895F04858D0101F97801F4B45AE34638CB2A021B5B091A3154EA4F16835B1D3EF2D37CFD39B25515DDF1DE6191F921C1E4C60E790D3F74CE47B51A1ECCAF8FE47A19B5EE4843862DB397B3913354DA952E9E0A5096EA23E3CB8A055E77B34DB706BBC56EFDBF140FCD2470771B3D917D096EFD00E3762E01F581475D32F3BA84AFF355CBF9E88FF35C5E6D55CD897793EF7335C3D194FA696F0C8D252B53EE2FE5610923B87370280

Received TLS Record
Header:
  Version = TLS 1.2 (0x303)
  Content Type = ChangeCipherSpec (20)
  Length = 1
Received TLS Record
Header:
  Version = TLS 1.2 (0x303)
  Content Type = Handshake (22)
  Length = 40
    Finished, Length=12
      verify_data (len=12): A3544983D9028B54907EBEF5

---
Certificate chain
 0 s:C=JP, ST=Tokyo, L=Chiyoda-ku, O=LY Corporation, CN=edge01.yahoo.co.jp
   i:C=JP, O=Cybertrust Japan Co., Ltd., CN=Cybertrust Japan SureServer CA G4
   a:PKEY: rsaEncryption, 2048 (bit); sigalg: RSA-SHA256
   v:NotBefore: Apr 15 07:20:27 2025 GMT; NotAfter: May 14 14:59:00 2026 GMT
 1 s:C=JP, O=Cybertrust Japan Co., Ltd., CN=Cybertrust Japan SureServer CA G4
   i:C=JP, O=SECOM Trust Systems CO.,LTD., OU=Security Communication RootCA2
   a:PKEY: rsaEncryption, 2048 (bit); sigalg: RSA-SHA256
   v:NotBefore: Dec 13 05:57:30 2023 GMT; NotAfter: May 29 05:00:39 2029 GMT
---
Server certificate
-----BEGIN CERTIFICATE-----
MIIO+TCCDeGgAwIBAgIUVxr+imV0xK8rzml35+mOrQsMna4wDQYJKoZIhvcNAQEL
BQAwXjELMAkGA1UEBhMCSlAxIzAhBgNVBAoTGkN5YmVydHJ1c3QgSmFwYW4gQ28u
LCBMdGQuMSowKAYDVQQDEyFDeWJlcnRydXN0IEphcGFuIFN1cmVTZXJ2ZXIgQ0Eg
RzQwHhcNMjUwNDE1MDcyMDI3WhcNMjYwNTE0MTQ1OTAwWjBoMQswCQYDVQQGEwJK
UDEOMAwGA1UECBMFVG9reW8xEzARBgNVBAcTCkNoaXlvZGEta3UxFzAVBgNVBAoT
DkxZIENvcnBvcmF0aW9uMRswGQYDVQQDExJlZGdlMDEueWFob28uY28uanAwggEi
MA0GCSqGSIb3DQEBAQUAA4IBDwAwggEKAoIBAQDTd/6S+6GrhA3d67pXjYy4AUR4
pWvbIm/UiN1wE6Ym2LmcS1XW0fSZWVtwbAAChsgJW0tqE2SL5IMhw95iKzdVOHF0
FpdCEbqHA7SAVk1sK1D26qk5HUsLsylz5wo19B26v0Bcd1ktjwWLLMM1WdyDbCiF
IYnM7whB/YWb9bTLeaJSSRYrUulz41dVyMalzgW3xAR1aujaeLdIOI699hjS8Sd4
to6y24eZZm78ZbjsZa6hniU9vWXTql+6Lgoui9SQWgPsP+GpQeo275FrHQ+d0d82
VwCvnp9idO2O8vTFnt30NbhkDfQFS+Tn2l0/yDzzXMHJZ5ppL5jliH4oLJi/AgMB
AAGjggujMIILnzAMBgNVHRMBAf8EAjAAMGYGA1UdIARfMF0wCAYGZ4EMAQICMFEG
CSqDCIybEQEXATBEMEIGCCsGAQUFBwIBFjZodHRwczovL3d3dy5jeWJlcnRydXN0
Lm5lLmpwL3NzbC9yZXBvc2l0b3J5L2luZGV4Lmh0bWwwgghfBgNVHREEgghWMIII
UoISZWRnZTAxLnlhaG9vLmNvLmpwgg0qLnlhaG9vLmNvLmpwgg4qLnlhaG9vYXBp
cy5qcIIRKi5hbmUueWFob28uY28uanCCFiouYXVjdGlvbnMueWFob28uY28uanCC
FyouYXVjdGlvbnMueWFob29hcGlzLmpwghIqLmJveC55YWhvb2FwaXMuanCCCyou
YnNwYWNlLmpwghoqLmJ5bGluZXMubmV3cy55YWhvby5jby5qcIILKi5jLnlpbWcu
anCCFiouY2FybmF2aS55YWhvb2FwaXMuanCCDyouY2Fydmlldy5jby5qcIIVKi5j
YXJ2aWV3LnlhaG9vLmNvLmpwghgqLmNoaWVidWt1cm8ueWFob28uY28uanCCFSou
Y2xvcmRlci55YWhvby5jby5qcIIIKi5jdncuanCCESouZGlnaXRhbGd1aWRlLmpw
ghwqLmVhc3QuZWRnZS5zdG9yYWdlLXlhaG9vLmpwgh8qLmVhc3QuZWRnZS5zdG9y
YWdlLXlhaG9vYm94LmpwghcqLmVkZ2Uuc3RvcmFnZS15YWhvby5qcIITKi5lZGl0
LnlhaG9vYXBpcy5qcIIVKi5maW5hbmNlLnlhaG9vLmNvLmpwgg4qLmdlb2NpdGll
cy5qcIIeKi5nbG9iYWwuZWRnZS5zdG9yYWdlLXlhaG9vLmpwghIqLmd5YW8ueWFo
b28uY28uanCCGCouam9iY2F0YWxvZy55YWhvby5jby5qcIIVKi5saXN0aW5nLnlh
aG9vLmNvLmpwghIqLmxvY28ueWFob28uY28uanCCDioubHljb3JwLmNvLmpwghIq
Lm1haWwueWFob28uY28uanCCFyoubWFya2V0aW5nLnlhaG9vLmNvLmpwghsqLm1r
Y2xvdWQtYXBpLmNhcnZpZXcuY28uanCCFSoubWtpbWcuY2Fydmlldy5jby5qcIIQ
Ki5tcy55YWhvby5jby5qcIIUKi5seWNvcnAtc2VjdXJpdHkuanCCEioubmV3cy55
YWhvby5jby5qcIITKi5uZXdzLnlhaG9vYXBpcy5qcIITKi5vcmRlci55YWhvby5j
by5qcIIUKi5wb2ludHMueWFob28uY28uanCCESoucHNpLnlhaG9vLmNvLmpwghMq
LnB1c2gueWFob29hcGlzLmpwghxhY3Rpdml0eS50cmF2ZWwueWFob28tbmV0Lmpw
ghQqLnNob3BwaW5nLmMueWltZy5qcIIWKi5zaG9wcGluZy5zcnYueWltZy5qcIIW
Ki5zaG9wcGluZy55YWhvby5jby5qcIIXKi5zaG9wcGluZy55YWhvb2FwaXMuanCC
Fiouc25zaW1nLmNhcnZpZXcuY28uanCCEyouc3RvcmUueWFob28uY28uanCCFCou
dHJhdmVsLnlhaG9vLmNvLmpwghQqLndhbGxldC55YWhvby5jby5qcIIVKi53YWxs
ZXQueWFob29hcGlzLmpwghgqLndlYmhvc3RpbmcueWFob28uY28uanCCHCoud2Vz
dC5lZGdlLnN0b3JhZ2UteWFob28uanCCHyoud2VzdC5lZGdlLnN0b3JhZ2UteWFo
b29ib3guanCCGSoueG1sLmxpc3RpbmcueWFob28uY28uanCCDyoueWFob28taGVs
cC5qcIIPKi55YWhvby1sYWJzLmpwgg4qLnlhaG9vLW5ldC5qcIIKKi55YWhvby5q
cIINKi55YWhvb2JveC5qcIIJKi55aW1nLmpwggoqLnlqdGFnLmpwghMqLnlqdGFn
LnlhaG9vLmNvLmpwghQqLnlzLWluc3VyYW5jZS5jby5qcIIVKi5zZWFyY2gueWFo
b29hcGlzLmpwghNhZGQuZGlyLnlhaG9vLmNvLmpwghlhcGkueS5jbG9yZGVyLnlh
aG9vLmNvLmpwghRhcmMuaGVscC55YWhvby5jby5qcIIZYml6dHgucG9pbnRzLnlh
aG9vYXBpcy5qcIINY2Fydmlldy5jby5qcIIYY2dpMi5yLWFnZW50LnlhaG9vLmNv
Lmpwghdja3N5bmMucGRzcC55YWhvby5jby5qcIIUY20uZnJvbWEueWFob28uY28u
anCCG2NvbXBhc3MueW1vYmlsZS55YWhvby5jby5qcIIZY3VzdG9tLnNlYXJjaC55
YWhvby5jby5qcIIXZS5kZXZlbG9wZXIueWFob28uY28uanCCGmZvcm1zLmJ1c2lu
ZXNzLnlhaG9vLmNvLmpwghdmcmFtZS5nYW1lcy55YWhvby5jby5qcIIXaHJtLmdy
bXRyZXoueWFob28uY28uanCCEWltLm92LnlhaG9vLmNvLmpwghlpbmZvLmhhdGFs
aWtlLnlhaG9vLmNvLmpwghptb3ZpZS5jaG9jb3RsZS55YWhvby5jby5qcIIbb25s
aW5lLnNlY3VyaXR5LnlhaG9vLmNvLmpwghdwb2llZGl0Lm1hcC55YWhvby5jby5q
cIIhcG9ydGFsLnlhZHVpLmJ1c2luZXNzLnlhaG9vLmNvLmpwgiRzc2wtdG9vbHMu
a2FpbmF2aS5zZWFyY2gueWFob28uY28uanCCGHNzbC5hcGkub2xwLnlhaG9vYXBp
cy5qcIITc3NsLm1hcC5zcnYueWltZy5qcIIRd3d3LmJvc2FpZ3VpZGUuanCCFnd3
dy5sb2hhY28ueWFob28uY28uanCCEHd3dy5zZWFyY2gzMTEuanCCD3d3dy5zcC1o
aW5hbi5qcIISd3d3LnRlY2hiYXNldm4uY29tggt5YWhvby5jby5qcIIIeWFob28u
anCCBXlqLnBuggh5anRhZy5qcDCBiwYIKwYBBQUHAQEEfzB9MDUGCCsGAQUFBzAB
hilodHRwOi8vc3NvY3NwLmN5YmVydHJ1c3QubmUuanAvT2NzcFNlcnZlcjBEBggr
BgEFBQcwAoY4aHR0cDovL2NybC5jeWJlcnRydXN0Lm5lLmpwL1N1cmVTZXJ2ZXIv
b3ZjYWc0L292Y2FnNC5jcnQwDgYDVR0PAQH/BAQDAgWgMB0GA1UdJQQWMBQGCCsG
AQUFBwMBBggrBgEFBQcDAjAfBgNVHSMEGDAWgBRip9La3oW2kvGFvPbolZ11oPpO
HzBGBgNVHR8EPzA9MDugOaA3hjVodHRwOi8vY3JsLmN5YmVydHJ1c3QubmUuanAv
U3VyZVNlcnZlci9vdmNhZzQvY2RwLmNybDAdBgNVHQ4EFgQUfKot2uHGJs14tri8
UOSHNUN+1CEwggF9BgorBgEEAdZ5AgQCBIIBbQSCAWkBZwB2AA5XlLzzrqk+Mxss
mQez95Dfm8I9cTIl3SGpJaxhxU4hAAABljhnQXwAAAQDAEcwRQIhAKLLyz2O8RKk
xW2GjJFwaAcowDMHDkp/g+8nl2QCMD6jAiBG6IKntbCOHPQD9D2ckF9vRcwfUFY1
ILKmoF1jWssX1gB1AJaXZL9VWJet90OHaDcIQnfp8DrV9qTzNm5GpD8PyqnGAAAB
ljhnSGUAAAQDAEYwRAIgShmqKc41GHQTf0ceLXtof0002yVIZqQzi5I7z2q9VIQC
IBQwONpJBzfDiggbxSKUo1SHOvvYlC04j0+CARqH4n64AHYAGYbUxyiqb/66A294
Kk0BkarOLXIxD67OXXBBLSVMx9QAAAGWOGdNdQAABAMARzBFAiA3+7IxDg9y4dG6
Ja1o8AvkBcsbLt59UhOEBZ7mXb+xBwIhANoe4yoZS3X0RIeUJCHtxgvyVj53Bx3U
9qd8Utn6IS+KMA0GCSqGSIb3DQEBCwUAA4IBAQB/MvHDetWmeoIqc+dQzEurtQNd
4g/Cng4n+Yf+j9+UnrsO34pHPfy+4kfMatPaAuBxGv/cLAYeAWE8tZJRzn67DhBK
vGmaaqQziKiT2QBn0hi9PiLet7FoMLqEfD5W7m7yGx8hUlwpxwpwIf20dOdwjBzN
HlukZVf4U/yMh1t+hbHfBQAIXsYmhM94FeE7j2ENr2xzfJyiyvqVvV2EuUEX7X+f
DV/L1mbqdbE06nSqgInyjvbhduvWB/+e9HXvEwJvHrVh68Wn88vYMeTkysZ5o6+Z
o83BJ0+/jVFIISEpM/QzdqF3184y9IHyk6QKWyG1FXv46ytTLargGsUN4TWC
-----END CERTIFICATE-----
subject=C=JP, ST=Tokyo, L=Chiyoda-ku, O=LY Corporation, CN=edge01.yahoo.co.jp
issuer=C=JP, O=Cybertrust Japan Co., Ltd., CN=Cybertrust Japan SureServer CA G4
---
No client certificate CA names sent
Peer signing digest: SHA256
Peer signature type: RSA-PSS
Server Temp Key: X25519, 253 bits
---
SSL handshake has read 5816 bytes and written 314 bytes
Verification: OK
---
New, TLSv1.2, Cipher is ECDHE-RSA-AES128-GCM-SHA256
Protocol: TLSv1.2
Server public key is 2048 bit
Secure Renegotiation IS supported
Compression: NONE
Expansion: NONE
No ALPN negotiated
SSL-Session:
    Protocol  : TLSv1.2
    Cipher    : ECDHE-RSA-AES128-GCM-SHA256
    Session-ID: DAE3843DC00466A59DF3B5DA281863322ABA75C03CB66D212DDCF69D3B8D17C8
    Session-ID-ctx: 
    Master-Key: 41CA44DE42EC4B2F65E9D3BD9F7D7C765474F4592A6AC048E62BF09F265A5E93E9E32422CC95CA0431C61D5BB01B373D
    PSK identity: None
    PSK identity hint: None
    SRP username: None
    TLS session ticket lifetime hint: 7200 (seconds)
    TLS session ticket:
    0000 - 59 61 68 6f 6f 21 20 4a-41 50 41 4e 00 00 00 00   Yahoo! JAPAN....
    0010 - c3 b4 e4 46 4b eb d3 cf-5a ac 37 5a f1 ba 70 f9   ...FK...Z.7Z..p.
    0020 - a4 a6 66 d3 c3 dd 5d e9-0b fa 46 fc b9 d8 f4 6e   ..f...]...F....n
    0030 - 22 47 62 fa 45 15 b5 a8-95 f0 48 58 d0 10 1f 97   "Gb.E.....HX....
    0040 - 80 1f 4b 45 ae 34 63 8c-b2 a0 21 b5 b0 91 a3 15   ..KE.4c...!.....
    0050 - 4e a4 f1 68 35 b1 d3 ef-2d 37 cf d3 9b 25 51 5d   N..h5...-7...%Q]
    0060 - df 1d e6 19 1f 92 1c 1e-4c 60 e7 90 d3 f7 4c e4   ........L`....L.
    0070 - 7b 51 a1 ec ca f8 fe 47-a1 9b 5e e4 84 38 62 db   {Q.....G..^..8b.
    0080 - 39 7b 39 13 35 4d a9 52-e9 e0 a5 09 6e a2 3e 3c   9{9.5M.R....n.><
    0090 - b8 a0 55 e7 7b 34 db 70-6b bc 56 ef db f1 40 fc   ..U.{4.pk.V...@.
    00a0 - d2 47 07 71 b3 d9 17 d0-96 ef d0 0e 37 62 e0 1f   .G.q........7b..
    00b0 - 58 14 75 d3 2f 3b a8 4a-ff 35 5c bf 9e 88 ff 35   X.u./;.J.5\....5
    00c0 - c5 e6 d5 5c d8 97 79 3e-f7 33 5c 3d 19 4f a6 96   ...\..y>.3\=.O..
    00d0 - f0 c8 d2 52 b5 3e e2 fe-56 10 92 3b 87 37 02 80   ...R.>..V..;.7..

    Start Time: 1747180991
    Timeout   : 7200 (sec)
    Verify return code: 0 (ok)
    Extended master secret: yes
---
Received TLS Record
Header:
  Version = TLS 1.2 (0x303)
  Content Type = Alert (21)
  Length = 26
    Level=warning(1), description=close notify(0)

closed
Sent TLS Record
Header:
  Version = TLS 1.2 (0x303)
  Content Type = Alert (21)
  Length = 26
    Level=warning(1), description=close notify(0)
```
