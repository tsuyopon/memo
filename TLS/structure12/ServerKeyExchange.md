# Server Key Exchange
ClientKeyExchangeでも公開鍵が32バイト、64バイトの違いがあった。
Server Key Exchangeでもx25519かsecp256r1でその違いがあったのでこれらに応答する鍵サイズとなっていると思われます。

- x25519が選択されている場合
  - 公開鍵は32バイト
```
TLSv1.2 Record Layer: Handshake Protocol: Server Key Exchange
    Content Type: Handshake (22)
    Version: TLS 1.2 (0x0303)
    Length: 300
    Handshake Protocol: Server Key Exchange
        Handshake Type: Server Key Exchange (12)
        Length: 296
        EC Diffie-Hellman Server Params
            Curve Type: named_curve (0x03)
            Named Curve: x25519 (0x001d)
            Pubkey Length: 32
            Pubkey: dd797a68121b8a1027cb2a557f3d0e82ef2adaa818577115...
            Signature Algorithm: rsa_pkcs1_sha512 (0x0601)
                Signature Hash Algorithm Hash: SHA512 (6)
                Signature Hash Algorithm Signature: RSA (1)
            Signature Length: 256
            Signature: 844128ae245f86806fc40e29777ce7c07b57c7e802c1e76a...
```


- secp256r1が選択されている場合
  - 公開鍵は65バイト
```
    TLSv1.2 Record Layer: Handshake Protocol: Server Key Exchange
        Content Type: Handshake (22)
        Version: TLS 1.2 (0x0303)
        Length: 333
        Handshake Protocol: Server Key Exchange
            Handshake Type: Server Key Exchange (12)
            Length: 329
            EC Diffie-Hellman Server Params
                Curve Type: named_curve (0x03)
                Named Curve: secp256r1 (0x0017)
                Pubkey Length: 65
                Pubkey: 04a84290f83abc17b68d35f2042ab6f1867ec01a93696859...
                Signature Algorithm: rsa_pkcs1_sha512 (0x0601)
                    Signature Hash Algorithm Hash: SHA512 (6)
                    Signature Hash Algorithm Signature: RSA (1)
                Signature Length: 256
                Signature: 92860f2e067e0a54a9a8193fd9f98d957e715dbf1215a921...
```
