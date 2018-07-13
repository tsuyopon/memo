# Layered Exported Authenticators in TLS

# 解決したい課題
Exported AuthenticatorsではTLS通信のあるパーティーから別のパーティーへの認証メソッドを提供します。
ここでの技術的課題として、同一チャネル上の複数のEAは共同での認証を行なわず、送信元が個別にそれぞれの証明書に対して認証を行っています。
同一チャネル上では送信元が一度で認証を行うことがこのドラフトでの目的です。

# 解決方法
このTLS拡張を含めることによって、送信元が共同で証明書の認証を行うことができるようになります。
この拡張はCertificateRequestかCertificate中に含まれています。

この手法としては次のとおりです
- クライアントがピンどめされたサーバ証明書を持ったサーバと通信し、サーバ側がピンどめされたサーバ証明書を送付する
- そして、クライアントは証明書が前回ピンどめされた証明書とバインドする。
- これによって、クライアント側ではサーバが共通の証明書を保持していて、共通の認証が必要であることがわかります。
- これによって共同認証を行うことができるようになります。

その他の潜在的な使用法としては次のとおりです。
- 証明書が受け入れられたかを証明する。
  - なぜならば、EAsはレスポンスメカニズムを保持していないので、EAの送信元は受信元の認証ステータスの状態を知らない
この拡張を利用することによって、一方のパーティは特有の証明書が受け入れられた通信相手かどうかを証明することができる。
(TODO: これで一体何がしたいのかはよくわかっていあに)


# 仕様詳細
- クライアントextension_dataフィールド(See: https://tools.ietf.org/html/draft-ietf-tls-tls13-28#section-4.2)に次の情報を入れる。これによってどの証明書及びそれに紐づくFinsihedでの認証が行われたのかを指定する。
  -  TLS拡張を定義して、前回のEA(Exported Authenticators)への参照を含ませる。このTLS拡張に含まれるEAは参照されたEAの認証を構成する。
  - (推測)おそらくこの拡張はCertificateRequestメッセージ中のフィールド中に含まれることになる?
```
   struct {
        opaque prev_certificate_request_context<0..2^8-1>;  // 参照しているEAに対するCertificate Request Context
        opaque binding[Hash.length];                        // 上記EAに対するFinishedメッセージ
   } LayeredEA;
```

このエクステンションを含んだCertificateRequestを受け取ったパーティーは、前回のEAから適切な証明書でFinishedメッセージとされるものが送付・受信されてきたものかどうかを検証しなければならない(MUST)

このリクエストを受取ったパーティーが認識できない証明書を受取ったり、ある理由で参照された証明書と結びつけたくなかったりするような場合であるが、EAに反応したい場合にはEAを省いた拡張を応答するかもしれない。


自発的証明書のために、サーバは独自のcertificate_request_contextを含まなければならない。
どちらのパーティーもcertificate_request_contextsやFinishedメッセージをバインドしようとした受け入れられたEAのリストを保持しなければならない。


# MEMO
- certificate_request_contextについては次のdraftで規定されている。
  - https://tools.ietf.org/html/draft-ietf-tls-exported-authenticator-04

# 参考URL
- https://datatracker.ietf.org/doc/draft-hoyland-tls-layered-exported-authenticator/

# 疑問点
- これはTLS1.3特有なの?
- クライアントやサーバ側の振る舞いがよくわからない
