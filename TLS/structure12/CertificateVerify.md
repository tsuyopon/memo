# 概要
CertificateRequestメッセージが送付された場合にだけ送付されるCertificateVerifyメッセージは次の構造をしています。
```
TLSv1.2 Record Layer: Handshake Protocol: Certificate Verify
    Content Type: Handshake (22)
    Version: TLS 1.2 (0x0303)
    Length: 264
    Handshake Protocol: Certificate Verify
        Handshake Type: Certificate Verify (15)
        Length: 260
        Signature Algorithm: rsa_pkcs1_sha256 (0x0401)
            Signature Hash Algorithm Hash: SHA256 (4)
            Signature Hash Algorithm Signature: RSA (1)
        Signature length: 256
        Signature: d6018230ff806c85f609592aaafae21f5bcbe44f2fc61f57…
```
