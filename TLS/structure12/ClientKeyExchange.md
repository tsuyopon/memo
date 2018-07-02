# Client Key Exchange

- 公開鍵が65バイト
```
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
                Pubkey: 045d2fd6915ab6fd02467eda6a25e1274d31cbeb92a87f78...
```

- 公開鍵が32バイト
```
Secure Sockets Layer
    TLSv1.2 Record Layer: Handshake Protocol: Client Key Exchange
        Content Type: Handshake (22)
        Version: TLS 1.2 (0x0303)
        Length: 37
        Handshake Protocol: Client Key Exchange
            Handshake Type: Client Key Exchange (16)
            Length: 33
            EC Diffie-Hellman Client Params
                Pubkey Length: 32
                Pubkey: 17723d2090ed4ab42fd82468dbf609b303d7e43b5d57ce77...
```


# MEMO
- 公開鍵が65byteと32byteの違いは何?
  - おそらくx25519かsecp256r1などの曲線の種類によってこの公開鍵の長さがServerKeyExchangeでも同様に変化しているので、それに応答していると思われます。
