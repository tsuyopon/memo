# TLS Ticket Requests

# 解決したい課題
TLS1.3で導入されたNewSessionTicketメッセージには次の２つの制約が存在する。
- サーバ上で発行枚数がハードコードされている。
- クライアントからチケットが何枚必要かといったことをサーバに伝える仕組みが存在しない。

チケット枚数を指定する要望としては次のようなものがあります。
- 並列のHTTPコネクション: 複数のコネクションがある場合など
- コネクション競合の場合: 複数のインターフェースやプロトコル(IPv4, IPv6)などによる競合がある場合など
- 中央集権的に管理されているようなシステム: サーバが代替してチケットを受け取りクライアントに渡すような場合(?)
- いくつかのチケットは接続のたびに発行されるという無駄を少なくしたい。
- リザンプションの拒否: チケット枚数が0であることを送付して、リザンプションの意思がないことを通知する場合

# 解決方法
クライアントはサーバ側にticket_request拡張を付与することで何枚のチケットを発行してほしいか伝えることができる。
ClientHelloの拡張情報には次のデータを追加して、countには発行してほしいチケット枚数を指定します。
```
struct {
    uint8 count;
} TicketRequestContents;
```

サーバ側はTicketRequestContents.countで指定された枚数よりも多くの枚数をクライアント側に送付すべきではない(SHOULD NOT)
ticket_request拡張をサポートするサーバはEncryptedExtensions中にticket_requestをechoとして返してはならない(MUST NOT)
クライアントはEncryptedExtensionsメッセージ中にticket_requestが存在していたらillegal_parameterでアボートしなければならない(MUST)
クライアントはHRRへの応答の２度目のClientHelloでTicketRequestContents.countを変更してはならない(MUST NOT)

# 参考URL
- https://tools.ietf.org/rfcdiff?url2=draft-ietf-tls-ticketrequests-04.txt
- IETF102スライド
  - https://datatracker.ietf.org/meeting/102/materials/slides-102-tls-ticket-requests-00
