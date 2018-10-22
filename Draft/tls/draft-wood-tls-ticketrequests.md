# TLS Ticket Requests

# 解決したい課題
- TLSではハンドシェイクを確立するためにNewSessionTicketがチケットとして1回発行されますが、実装によっては複数のチケットを取得したいといった要望があります。
  - 並列のHTTPコネクション: 複数のコネクションがある場合など
  - コネクション競合の場合: 複数のインターフェースやプロトコル(IPv4, IPv6)などによる競合がある場合など
  - 中央集権的に管理されているようなシステム: サーバが代替してチケットを受け取りクライアントに渡すような場合(?)
- いくつかのチケットは接続のたびに発行されるという無駄を少なくしたい。

# 解決方法
TicketRequestというpost-handshakeで行われるメッセージを新しく規定します。
今後はこのTicketRequestメッセージが送付されてきた場合だけ発行できるようにしたい。
```
  struct {
       opaque identifier<0..255>;   //  A unique value for this ticket request
       opaque context<0..2^16-1>;
   } TicketRequest;
```

TicketRequestメッセージを受け取るとすぐに、サーバはNewSessionTicketメッセージを応答する。次の拡張を規定する。
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
- IETF102スライド
  - https://datatracker.ietf.org/meeting/102/materials/slides-102-tls-ticket-requests-00
