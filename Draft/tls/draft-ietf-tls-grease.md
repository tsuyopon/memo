# Applying GREASE to TLS Extensibility
GREASE (Generate Random Extensions And Sustain Extensibility)仕様について規定しています。
これはTLSエコシステムにおいて拡張上の失敗を防ぐためのメカニズムです。

# 解決する課題
- 拡張などに未知の値が含まれる場合には、本来無視しなければならないが、拒絶する実装が存在する。

# 解決方法
- ランダムで未知の値を埋め込むことによって各種実装はこれらの本来無視されるべき値を無視して相互運用性が高まります。それらの実装が広められる前に回避することができる。


# 仕様

### 規定しているGREASE値
この仕様書では次のランダム値を複数決定している
- cipher suitesに指定する値
- extensions, named groups, signature algorithms, versionsに指定する値
- PskKeyExchangeModesに指定する値
- ALPN identifiersに指定する値


### 規定している振る舞い
- クライアント主導でのGREASE値決定の流れとそれを受け取ったサーバの振る舞い
- サーバ主導で値を決定しなければならないような場合のサーバの振る舞いとそれを受け取ったクライアントの振る舞い

# 参考URL
- https://tools.ietf.org/html/draft-ietf-tls-grease-01
