
# 概要
TLS周りに関する詳細について

### Trasport Layer Security(TLS) Parameters
cipher suiteのマッピング表、Handshakeなどが置かれています。
- https://www.iana.org/assignments/tls-parameters/tls-parameters.xhtml

### トラストアンカーの仕組みについて
このあたりに非常によくまとまっていそう。
- https://blogs.cisco.com/security/where-is-my-intermediate-tls-certificate

検証手順としては次の流れとなるようだ。
- 1. HandshakeのCertificateで必要なサーバ証明書や中間証明書などを受け取ります。
- 2. 証明書には次のような情報が入っています。
```
Cert DN
Cert Public Key
Issue CA DN
Issuer Signature
```
- 3. サーバ証明書のIssue CA DNを確認。 サーバ証明書記載の情報がrevokeされていないか、期限切れでないかなどを確認する。
- 4. サーバ証明書の「Issuer CA DN」から中間証明書の「Cert DN」を決定し検証する中間証明書が決定します。
- 5. 中間証明書に含まれる「Cert Public Key」からサーバ証明書に含まれる「Issuer Signature」が検証できることを確認します。
- 6. 中間証明書に含まれる「Issuer CA DN」を確認。中間証明書記載の情報がrevokeされていないか、期限切れでないかなどを確認する。
- 7. 中間証明書に含まれる「Issuer CA DN」からルート証明書の「Root CA DN」を決定し検証するルート証明書が決定します。
- 8. ルート証明書に含まれる「Root CA Public Key」から中間証明書に含まれる「Issuer SIgnature」が検証できることを確認します。
-

TODO: 最初に入力されたアドレスがSANと一致するかを検証するか、最後にアドレスがSANと一致するかを検証するか?

もしサーバがハンドシェイクのCertificateのフェーズで、server certificateしか返さなかったら中間証明書設置ミスということでサーバサイドでエラーとなる。
