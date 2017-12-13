# 概要
アラートプロトコルについてRFC5246のセクション7.2について

# 詳細

## 7.2 Alert Protocol
alertメッセージはメッセージの重大性をfatal, warningの２種類、またメッセージ詳細を伝えるためのものです。
fatalレベルのメッセージは、即座にコネクションを終了させることを意味しています。
このケースの場合には、そのセッションで利用する他のコネクションが続くかもしれないが、sessionIDを無効としなければなりません。それによって、Establishedされた新規コネクションから失敗するセッションを利用させることを回避させます。

他のメッセージと同様に、alertメッセージはcurrent connection stateによって述べられているように暗号化及び圧縮されています
```
     enum { warning(1), fatal(2), (255) } AlertLevel;

      enum {
          close_notify(0),
          unexpected_message(10),
          bad_record_mac(20),
          decryption_failed_RESERVED(21),
          record_overflow(22),
          decompression_failure(30),
          handshake_failure(40),
          no_certificate_RESERVED(41),
          bad_certificate(42),
          unsupported_certificate(43),
          certificate_revoked(44),
          certificate_expired(45),
          certificate_unknown(46),
          illegal_parameter(47),
          unknown_ca(48),
          access_denied(49),
          decode_error(50),
          decrypt_error(51),
          export_restriction_RESERVED(60),
          protocol_version(70),
          insufficient_security(71),
          internal_error(80),
          user_canceled(90),
          no_renegotiation(100),
          unsupported_extension(110),
          (255)
      } AlertDescription;

      struct {
          AlertLevel level;
          AlertDescription description;
      } Alert;
```

### 7.2.1 Closure Alerts
クライアントとサーバは「truncate attackを避けるためにコネクションを終了した」ということを伝えなければなりません(TODO: trncate attack)
いずれもclosingメッセージを交換するかもしれません。


(TODO: 送られることを確認しておきたい)
```
close_notify
   このメッセージは、senderはこのコネクションではもうメッセージを送らないよということをrecipient側に伝えます。
   TLS1.1現在において、コネクションを適切に閉じるための失敗は、セッションが再開されているかどうかといったことを要求していません。(英訳に自身なし)
   これは、広範囲の実装上の実践のためのTLS1.0からの変更点です。
```

どちらの側にとっても、close_notifyアラートを送ることによってcloseをinitiateするかもしれません。
closure alertのあとに受け取ったどんなデータでも無視されるようになります。

いずれかのfatalアラートが送信されない限り、コネクションの書き込み側をクローズする前にどちら側でもclose_notifyアラートを送信することが要求されています。
他の側(close_notifyを受け取った側)はclose_notfiyアラートに応答しなければなりません。そして、即座にコネクションをクローズし、書き込みしている情報を破棄します。(TODO: 何のことかをちゃんと確認すること)
クローズ処理のinitiator(プログラム開始側)には、コネクションの読み込みをクローズする前にclose_notifyアラートの応答を待つことを要求しません。

もし、TLSを利用するアプリケーションプロトコルを提供していたら、TLS実装はclose_notifyアラートを受け取らなければなりません。
TLS実装はTLSコネクションが終了したということをアプリケーション層に指示する前にclose_notifyアラートを受信しなければなりません。(TODO: 実装はどうやる?)

もし、アプリケーションプロトコルが追加データを転送しないのであれば、そのときは実装はclose_notifyアラートを待たずしてtransportコネクションをクローズすることになるかもしれません。

(TODO: lator)
No part of this standard should be taken to dictate the manner in which a usage profile for TLS manages its data transport, including when connections are opened or closed.

Note: It is assumed that closing a connection reliably delivers pending data before destroying the transport.

### 7.2.2 Error Alerts
TLSハンドシェイク中のエラーハンドリングはとても単純です。
エラーを検知したら、検知側は他方にメッセージを送ります。
fatalアラートメッセージを送信したり、受け取るとすぐに、どちらの側でも即座にコネクションをクローズします。
serverとclientはSessionID, 鍵情報, 失敗したコネクションに基づくsecret情報を破棄しなければなりません。(TODO: 厳密に確認)
fatalアラートにより終了したどんなコネクションもresumeとして使われてはなりません。

実装においてfatalアラートで定義した状態になったときにはいつでも、コネクションを閉じることよりも優先して適切なアラートを送付しなければなりません。

アラートレベルが明確に明記されていないすべてのエラーにとって、送信側がポリシーなどに応じてfatalエラーかそうじゃないかといったことを決定するかもしれません。

もし実装として、アラートを送るように選択し、それがすぐにコネクションのクローズを意図したものであるならば、fatalレベルを送らなければなりません。

もし、warningレベルのアラートが送信されたり、受信されたら、一般的にはコネクションは続きます。
もし、受信側がコネクション処理を続けたくないとした場合、コネクションを終了するためにfatalアラートを送るべきです。(e.g. acceptするつもりがないno_renegotiationアラートを受信した場合)
これを考慮すると(Given This)、一般的には送信側は受け取り側がどのような振る舞いをするのか知ることが出来ません。
warningアラートは送信側がコネクションを継続したいときにはあまりusefulではありません。そして、時々省略もされてしまいます。
例えば、相手側が期限切れの証明書を受け入れることを決め、コネクションを継続すると決定したら、一般的にはcertificate_expiredアラートは送られません。

次のエラーが規定されています。

- unexpected_message
  - 不適切なメッセージが送られてきた場合
-  bad_record_mac
  - 
- decryption_failed_RESERVED
- record_overflow
- decompression_failure
- handshake_failure
- no_certificate_RESERVED
- bad_certificate
- unsupported_certificate
- certificate_revoked
- certificate_expired
- certificate_unknown
- illegal_parameter
- unknown_ca
- access_denied
- decode_error
- decrypt_error
- export_restriction_RESERVED
- protocol_version
- insufficient_security
- internal_error
- user_canceled
- no_renegotiation
- unsupported_extension
  - クライアントによって送られる
  - メッセージはserver helloにはclient hello時に送っていない拡張が含まれているというものが送られる。常にfatalとなる

alert valueはIANAによって割り当てられる。(TODO: 確認しておく)
- https://tools.ietf.org/html/rfc5246#section-12

