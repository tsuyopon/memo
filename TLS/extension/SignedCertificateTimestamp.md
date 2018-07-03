# 概要
signed_certificate_timestamp拡張はCertificate Transparencyで利用される仕組みです。
この仕様の詳細についてはTLS/CertificateTransparency.mdを参照してください。

CTやSCTについて用語をあらかじめ抑えておきます。
- CT: Certificate Transparency。CTログサーバに発行した証明書を登録することで、証明書発行の「透明性」を確保する仕組み。
- SCT: Signed Certificate Timestamp、署名付き証明書タイムスタンプ。CTログサーバに証明書を登録した際に、発行してもらえるタイムスタンプ。

# 詳細

### データ構造サンプル
- ClientHelloサンプル
```
Extension: signed_certificate_timestamp
    Type: signed_certificate_timestamp (0x0012)
    Length: 0
    Data (0 bytes)
```

- ServerHelloのサンプル(応答だとサイズがある)
```
Extension: signed_certificate_timestamp (len=242)
    Type: signed_certificate_timestamp (18)
    Length: 242
    Serialized SCT List Length: 240
    Signed Certificate Timestamp (Google 'Pilot' log)
        Serialized SCT Length: 117
        SCT Version: 0
        Log ID: a4b90990b418581487bb13a2cc67700a3c359804f91bdfb8...
        Timestamp: Feb 20, 2018 15:39:16.793000000 UTC
        Extensions length: 0
        Signature Algorithm: ecdsa_secp256r1_sha256 (0x0403)
            Signature Hash Algorithm Hash: SHA256 (4)
            Signature Hash Algorithm Signature: ECDSA (3)
        Signature Length: 70
        Signature: 304402200579285ce75f49956041696438159862b6433733...
    Signed Certificate Timestamp (Symantec log)
        Serialized SCT Length: 119
        SCT Version: 0
        Log ID: ddeb1d2b7a0d4fa6208b81ad8168707e2e8e9d01d55c888d...
        Timestamp: Feb 20, 2018 15:39:16.520000000 UTC
        Extensions length: 0
        Signature Algorithm: ecdsa_secp256r1_sha256 (0x0403)
            Signature Hash Algorithm Hash: SHA256 (4)
            Signature Hash Algorithm Signature: ECDSA (3)
        Signature Length: 72
        Signature: 3046022100ddaae49cdbb285a0f0688fae0fe2d98eb6d48d...
```

### この拡張を有効にするための方法
TODO
- https://blog.pierky.com/certificate-transparency-manually-verify-sct-with-openssl/

# SeeAlso
- RFC6962: Certificate Transparency
  - https://tools.ietf.org/html/rfc6962
- How Certificate Transparency Works
  - http://www.certificate-transparency.org/how-ct-works
- Certificate Transparency: manually verify SCT with openssl
  - 手動でSCTを検証する方法
  - https://blog.pierky.com/certificate-transparency-manually-verify-sct-with-openssl/

