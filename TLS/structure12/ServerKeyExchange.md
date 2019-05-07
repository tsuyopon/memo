# Server Key Exchange
Server Key Exchangeはもっとも混乱しやすいメッセージである。
なぜ混乱しやすいかというとRFC2246、RFC4346、RFC4492、RFC5246、RFC8422の５つが複雑に絡み合っている。
バージョンごとに構造体の違いも多く、歴史的経緯による用語の混乱(dhe_dss, dhe_rsa)なども非常に多い。

ECCかどうかで構造体構造が変わってきたりするので注意が必要。例えば、TLS_DHEとTLS_ECDHEでは構造体が異なってくる。

- RFC2246 (TLS1.0)
  - https://www.ietf.org/rfc/rfc2246.txt
- RFC4346 (TLS1.1)
  - https://www.ietf.org/rfc/rfc4346.txt
- RFC5246 (TLS1.2)
  - https://tools.ietf.org/html/rfc5246#section-7.4.3
- RFC4492
  - ECCに関してはこちらを参考にする。
  - https://tools.ietf.org/html/rfc4492#section-5.4
- RFC8422
  - RFC4492をエフェメラルのみに限定し、EdDSAに関する記述も付与されている。
  - https://tools.ietf.org/html/rfc8422#section-5.4

なお、TLS1.3ではkey_shared拡張の登場によってこのメッセージは廃止されている。

# 詳細
ここでは一部のパケットしか載せていない

### TLS1.2でecdheの場合(RFC8422を参照のこと)

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
