# 概要
GREASE (Generate Random Extensions And Sustain Extensibility)は、TLS拡張にランダムな値を入れることによってサーバが意図せず落ちてしまったりするような挙動を防ぐための仕組みです。相互運用上の問題点を回避するための仕組みです。
RFC8701として最近規定されました。

# 解決する課題
- 拡張などに未知の値が含まれる場合には、本来無視しなければならないが、拒絶する実装が存在する。これは相互運用性に影響をもたらす。

# 解決方法
- ランダムで未知の値(このRFCで埋め込む値は規定している)を埋め込むことによって各種実装はこれらの本来無視されるべき値を無視して相互運用性が高まります。それらの実装が広められる前に回避することができる。

# 詳細

### 規定しているGREASE値
この仕様書では次のランダム値を複数決定している
- cipher suitesに指定する値
- ALPN(RFC7301) identifiersに指定する値
- extensions, named groups, signature algorithms, versionsに指定する値
- PskKeyExchangeModesに指定する値

### 規定している振る舞い
- クライアント主導でのGREASE値決定の流れとそれを受け取ったサーバの振る舞い
- サーバ主導で値を決定しなければならないような場合のサーバの振る舞いとそれを受け取ったクライアントの振る舞い
  - サーバ主導なのはTLS1.3でサーバからの応答に拡張を付与しているのでその影響である。

### サーバ仕様

# サンプルデータ構造
- ClientHello中に次のように複数含まれていることもあるようだ。
```
Extension: Reserved (GREASE) (len=0)
    Type: Reserved (GREASE) (10794)
    Length: 0
    Data: <MISSING>
Extension: Reserved (GREASE) (len=1)
    Type: Reserved (GREASE) (60138)
    Length: 1
    Data: 00
```

# Informative Revference
- chrome
  - https://groups.google.com/a/chromium.org/forum/#!topic/net-dev/wJIj6SS68C8


# Normative Reference
- RFC8701: Applying Generate Random Extensions And Sustain Extensibility (GREASE) to TLS Extensibility
  - https://tools.ietf.org/html/rfc8701
