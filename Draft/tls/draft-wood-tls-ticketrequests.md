# TLS Ticket Requests


# 解決したい課題
- TLSではNewSessionTicketがチケットとして1回発行されますが、実装によっては複数回のチケットを取得したい要望が存在します。たとえば、
  - 1つのTLSチケットでそのサーバに並列のTLSコネクションを処理したい際の境界を示したい場合
  - 異なったネットワークI/F間でのTLSコネクション競合してしまう場合

# 解決方法
TicketRequestというpost-handshakeで行われるメッセージを新しく規定する
```
  struct {
       opaque identifier<0..255>;   //  A unique value for this ticket request
       opaque context<0..2^16-1>;
   } TicketRequest;
```

TicketRequestメッセージを受け取るとすぐに、サーバはNewSessionTicketメッセージを応答する。

また、次の拡張を規定する。
- ticket_identifier: TicketRequestのidentiferフィールドに応答しなければならない
- ticket_context: クライアントにticket contexを伝えるためのもの。
```
   enum {
       ...
       ticket_identifier(TBD),
       ticket_context(TBD+1),
       (65535)
   } ExtensionType;
```

ticket_requestというTLS拡張を新しく定義する。
ClientHelloでこれを空データで送り、対応していたらEncryptedExtensionsでechoする。
サーバから拡張がechoされてこなかったら、TicketRequestを送ってはならない。

サーバは255を超えたチケットをクライアントに送付してはならない。


# 参考URL
- https://www.ietf.org/id/draft-wood-tls-ticketrequests-00.txt
