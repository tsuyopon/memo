# 概要
「extended master secret」TLS拡張を利用するとmaster_secretの算出方式が変更されます。この拡張はTLS1.0〜TLS1.2までであり、TLS1.3は関係ありません。
次のRFCで規定されています。
- https://tools.ietf.org/html/rfc7627

# 背景
通常master_secretはClientHello.Random, ServerHello.Random, pre_master_secret, labelから算出されます。
この拡張が有効となる場合には、ハンドシェイクのClientHelloからClientKeyExchangeまでの平文をハッシュとして、それとpre_master_secretを元にしてmaster secretを生成します。

この算出方法の違いが意味することとしては、Triple Handshakeに対する驚異への対策となるようです。(詳細はSeeAlsoを参考のこと)


# 詳細
# データ構造サンプル
- ClientHelloのサンプル
```
Extension: Extended Master Secret
    Type: Extended Master Secret (0x0017)
    Length: 0
```
- ServerHelloの応答サンプル
```
Extension: Extended Master Secret
    Type: Extended Master Secret (0x0017)
    Length: 0
```

# TODO
- 攻撃に対してどのように有効なのかを全く理解していないので、ちゃんと理解する必要がある
- RFCと参考リンクも読んでいない

# SeeAlso
- RFC7627
  - https://tools.ietf.org/html/rfc7627
- TLS「extended master secret」拡張 (RFC7627)
  - https://qiita.com/n-i-e/items/f842a6b40cbacb007494
- Triple Handshakes Considered Harmful: Breaking and Fixing Authentication over TLS
  - シーケンス図つきの図解
  - https://mitls.org/pages/attacks/3SHAKE
