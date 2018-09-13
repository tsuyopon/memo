# Exported Authenticators in TLS

# 解決したい課題
アプリケーションレイヤープロトコルでは、同一コネクション上で複数の証明書に対する認証がしたい
このケースの最初の利用パターンがHTTP/2の追加証明書を予定している。
- 1つのストリーム上でHTTP/2のクライアント認証を実現すること
- サーバ証明書の追加(Requested or Spontaneous)

なお、多重化接続のHTTP/2上のクライアント認証を実現するSecondary Certificateが検討されていますが、これをヒントとしてTLSレイヤで同様の機能を実現するようにしたいといった課題から Exported Authenticatorsは生まれました。

# 解決方法
Exported Authenticatorsという仕組みによって、通常のハンドシェイクから別のSNIの認証及びマスターシークレットの再生性のしくみを提供します。
- CertificateRequest(servername含む)を渡して、Certificate, CertificateVerify, Finishedなどの一連のメッセージを渡す。拡張マスターシークレットは再計算
  - 2つの方法があり、自発的であればCertificateRequestを渡さずに処理する方法も可能です。

Exported Authenticatorsには次の特徴があります。
- ハンドシェイク後(Post-handshake)の認証メカニズムの提供
- TLS1.2再ネゴシエーションに対する置き換えを行う
- TLS1.3ハンドシェイク後のクライアント認証よりも多目的である
- クライアントとサーバ共に複数のidentityを持つことを許容する

この機能によって、クライアント認証だけでなくサーバ・クライアント間で、一度TLS接続した後に追加で別の証明書でサーバ認証が行えるようになります。
この仕組は、TLSのハンドシェイクとは独立して認証のやり取りを行うので、サーバ・クライアントのTLS状態を変えることもありません。

次の２つのフローが存在します。

Request-Response EA
- 1. InitiatorがResponderにCertificateRequestを送る
  - 上記のCertificateRequestが"Authenticator Request"に該当する
  - CertificateRequestにはserver_name拡張などを含みます。
- 2. ResponderがCertificate, CertificateVerify, Finishedメッセージを送付する。
  - 上記の処理がAuthenticatorが行う処理に該当する
- 3. 受け取ったがわは証明書の検証を行い、拡張マスターシークレットを再計算します。

Spontaneous EA
- 1. SerevrからClientに対してCertificate, CertificateVerify, Finishedメッセージを送付する。
  - 上記の処理がAuthenticatorが行う処理に該当する
- 2. このメッセージを受け取ったクライアントはルート証明書の検証を行い、拡張マスターシークレットが再計算されます。


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

- certificate_request_context: certificate requestの身元を特定するための文字列であり、この値には同一パーティーで生成された複数のauthenticator requestを含んではならない。Authenticator側の応答ではechoされる。
- extensions: TLS1.3のSecion4.2で定義される拡張やserver_name拡張が含まれます。


### Authenticatorについて
AuthenticatorはどちらかのTLS通信からエクスポートされた構造体メッセージです。このメッセージはアプリケーションレイヤーでTLS通信の他のパーティーに送信されます。
Authenticatorに送るために使われるアプリケーションプロトコルは、証明書を機密にしておくためにトランスポートに基づいてTLSが使われるべきです。
AuthenticatorメッセージはTLS通信を確立したクライアントかサーバのどちらかによって構築されます。
クライアントは前のauthenticator requestなしではAuthenticatorを送付してはなりません。サーバにとってはauthenticator requestはオプションです。


### Authenticator Keys
それぞれのauthenticatorはTLSセッションから派生したハッシュコンテキストやFinished MACキーを使って計算される。
これらの値は、TLS1.2ではRFC5705に基づいたexporterを使っている(TLS1.3ではドラフトに基づく)

これらの値は送信元の役割に基づいて異なったラベルが使われています。
- Handshake Context:
- Finished MAC Key: 

もし、コネクションがTLS1.2であるならば、マスターシークレットは同期攻撃を防ぐために拡張マスターシークレット(RFC7627)として計算されなければならない。

AuthenticatorはTLS1.3のCertificate, CertificateVerify, Finishedの３つのメッセージの連結で形成される。
もし、Authenticatorリクエストがなければ、拡張はTLSハンドシェイクから選択されることになる。
サーバだけが一致するリクエスト(Authenticator Request)なくAuthenticatorを送付することができる。
そのようなケースにおいては、ClientHello拡張はCertificateメッセージの中で許容される拡張を決定する。


### APIについて
- See: https://tools.ietf.org/html/draft-ietf-tls-exported-authenticator-07#section-6

TLSライブラリで次のような実装を規定しています。これはアプリケーションレイヤーで実装できたとしてもTLSライブラリで実装すべきと規定しています。
- The "request" API
  - 引数: 「certificate_request_context」、「含むべきextensionのセット」
  - 戻り値: authenticator request
- The "get context" API
  - 引数: 「authenticator」
  - 戻り値: certificate_request_context
- The "authenticate" API
  - 引数: 「証明書チェーンのセットと関連拡張」、「各種チェーンへの署名」、「an optional authenticator request or certificate_request_context」
  - 戻り値: exported authenticatorか空のauthenticator
- The "validate" API
  - 引数: 「an optional authenticator request」と「an authenticator」の２つ
  - 戻り値: 証明書チェーン、拡張、authenticatorステータス

# 参考URL
- https://tools.ietf.org/html/draft-ietf-tls-exported-authenticator-07
- IETF 101スライド
  - https://datatracker.ietf.org/meeting/101/materials/slides-101-tls-sessa-exported-authenticators-security-analysis-00
- IETF 100s裏井戸
  - https://datatracker.ietf.org/meeting/100/materials/slides-100-tls-sessa-tls-exporters-00
- IETF 97スライド
  - https://datatracker.ietf.org/meeting/97/materials/slides-97-tls-sessa-exported-authenticators-in-tls-00
