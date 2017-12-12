# 概要
アラートプロトコルについてRFC5246のセクション7.2について

# 詳細

## 7.2 Alert Protocol
alertメッセージはメッセージの重大性をfatal, warningの２種類、またメッセージ詳細を伝えるためのものです。
fatalレベルのメッセージは、即座にコネクションを終了させることを意味しています。
このケースの場合には、そのセッションで利用する他のコネクションが続くかもしれないが、sessionIDを無効にしなければなりません。

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



Dierks & Rescorla           Standards Track                    [Page 28]
 
RFC 5246                          TLS                        August 2008


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
クライアントとサーバは「truncate attackを避けるためにコネクションを終了した」ということを伝えなければなりません(未調査: trncate attack)
いずれもclosingメッセージを交換するかもしれません。

```
close_notify
   このメッセージは、senderはこのコネクションではもうメッセージを送らないよということをrecipient側に伝えます。
   TLS1.1現在において、XXX
   これは、TLS1.0からの変更です。
```

どちらの側にとっても、close_notifyアラートを送ることによってcloseを送るかもしれません。
closure alertのあとに受け取ったデータは無視されるようになります。

いずれかのfatalアラートが送信されない限り、どちらの側


### 7.2.2 Error Alerts
TLSハンドシェイク中のエラーハンドリングはとても単純です。
エラーを検知したら、受信側は送信側にメッセージを送ります。
fatalアラートメッセージを送信したり、受け取るとすぐに、どちらの側でも即座にコネクションをクローズします。
serverとclientはSessionID, 鍵情報, 失敗したコネクションに基づくsecret情報を破棄しなければなりません。
fatalアラートにより終了したどんなコネクションもresumeとして使われてはいけません。

実装においてfatalアラートで定義した状態になったときには、コネクションを閉じることよりも優先して適切なアラートを送付しなければなりません。

すべてのエラーは明示的にアラートレベルが明記されていません。送信側がポリシーなどに応じてfatalエラーかそうじゃないかといったことを決定するかもしれません。

もし実装として、アラートを送るように選択し、それがすぐにコネクションのクローズを意図したものであるならば、fatalレベルを送らなければなりません。








