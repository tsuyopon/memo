# 概要
post_handshake_auth拡張(Post Handshake Client Authentication)は
この拡張はクライアントがpost-handshake authenticationをしようとしているといったことを示しています。
サーバ側はこの拡張を提示していないクライアントに対してpost-handshakeでCertificateRequestを送付してはならず、またサーバがこの拡張を送付することも禁止している。


# 詳細

### 仕様
Post Handshake Messageの1つとして Post-Handshake Authenticationが定義されています。
クライアントがこの拡張を送付した時、サーバ側はCertificateRequestメッセージを送ることによってハンドシェイクを完了した後にいつでもクライアント認証を要求するかもしれません。
クライアントは適切なAuthentication messagesを応答しなければなりません。
- https://tools.ietf.org/html/draft-ietf-tls-tls13-27#section-4.4

もしクライアントが認証することを選択したら、Certificate, CertificateVerify, Finishedを送付しなければなりません。
もし認証を拒否した場合、Certificateメッセージには証明書を含まずに、続いてFinishedが送られなければなりません。


### データ構造
データフィールドは空となっています。
```
struct {} PostHandshakeAuth;
```

# SeeAlso
- RFC draft: The Transport Layer Security (TLS) Protocol Version 1.3 
  - https://tools.ietf.org/html/draft-ietf-tls-tls13-27#section-4.2.6
  - https://tools.ietf.org/html/draft-ietf-tls-tls13-27#section-4.6.2
