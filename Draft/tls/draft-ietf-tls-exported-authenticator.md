# Exported Authenticators in TLS

# 解決したい課題
セッションが確立された後に、証明書を使ってTLS通信した１つのパーティーから別のパーティーへの認証方法を提供したい。


# 解決方法
- 通常のTLSの性質に加えて、次の２つの利点を提供する
  - 複数の認証: 1つのコネクションで複数のエンドポイントに対しての認証を行いたいような場合(ただし、すべてのidentifyを持った1枚の証明書ではない)
  - 自発的認証: コネクションを確立した後にエンドポイントは認証をすることができる

これは次のメカニズムによって提供します。TLS1.2以降のみサポートし、クライアント認証でのみ利用することができます。
- ハンドシェイク後(Post-handshake)の認証メカニズム
- TLS1.2再ネゴシエーションに対する置き換え
- TLS1.3ハンドシェイク後のクライアント認証よりも多目的
- クライアントとサーバ共に複数のidentityを持つことを許容します。

次の２つのフローが存在します。

Request-Response EA
- 1. InitiatorがResponderにCertificateRequestを送る
  - 上記のCertificateRequestが"Authenticator Request"に該当する
- 2. ResponderがCertificate, CertificateVerify, Finishedメッセージを送付する。
  - 上記の処理がAuthenticatorが行う処理に該当する

Spontaneous EA
- 1. SerevrからClientに対してCertificate, CertificateVerify, Finishedメッセージを送付する。
  - 上記の処理がAuthenticatorが行う処理に該当する

つまり、上記は言い換えると次の２つのフローをサポートする。
- クライアントからAuthenticator Requestを送付して、サーバがAuthenticatorとして処理を行う
- サーバから直接Authenticatorとして認証を行わせる(自発的認証)


それぞれが送るメッセージは次のとおりです
Authenticator RequestはCertificateRequestを送ることでその中にserver_nameなどの拡張も含めます。

Authenticatorは次の連結した値をクライアントに送付します。
- Certificate, CertificateVerify, Finished

# 仕様詳細

### Authenticator Request (Authenticatorに依頼するためのリクエスト)

アプリケーションレイヤーにおいてTLSコネクションの別のパーティから送信されます。
Authenticator Requestはクライアントかサーバのいずれかによって構成されます。

このAuthenticator RequestはCertificateRequestメッセージ構造を利用します。
このメッセージはTLSレコードレイヤーを含んでおらず、ハンドシェイクキーで暗号化されていません。

CertificateRequestはauthenticatorに対してのリクエストの中に含めるパラメータを定義します。
TLS1.3での定義は次のようなものになります。
```
struct {
   opaque certificate_request_context<0..2^8-1>;
   Extension extensions<2..2^16-1>;
} CertificateRequest;
```

- certificate_request_context: Authenticator側の応答ではechoされる。
- extensions: TLS1.3で定義される拡張やserver_name拡張が含まれます。


### Authenticatorが行う処理
AuthenticatorはTLS1.3のCertificate, CertificateVerify, Finishedの３つのメッセージの連結で形成される。
もし、Authenticatorリクエストがなければ、拡張はTLSハンドシェイクから選択されることになる。
サーバだけが一致するリクエスト(Authenticator Request)なくAuthenticatorを送付することができる。
そのようなケースにおいては、ClientHello拡張はCertificateメッセージの中で許容される拡張を決定する。


# 参考URL
- https://tools.ietf.org/html/draft-ietf-tls-exported-authenticator-07
- IETF 101スライド
  - https://datatracker.ietf.org/meeting/101/materials/slides-101-tls-sessa-exported-authenticators-security-analysis-00
