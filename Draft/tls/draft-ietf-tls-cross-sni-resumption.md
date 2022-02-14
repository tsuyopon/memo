# 概要
Transport Layer Security (TLS) Resumption across Server Names
- https://datatracker.ietf.org/doc/html/draft-ietf-tls-cross-sni-resumption-02

# 課題
### 解決したい課題
TLSセッションチケットは新規コネクションのServerNameがオリジナルのSNIにマッチしている必要がある。
RFC8446 Section4.6.1には「もし明示的な外的手段があれば、クライアントは異なったSNIの値で再開しても良い」とされている。
```
If such an indication is provided (externally or by any other means), clients MAY resume with a different SNI value.”
```

よって、外的手段を提示することで、本来のオリジナル接続で利用したSNIと異なった値を使ってもセッションチケットで接続できるようにしたいという課題への対応である。


### 解決方法
TLSフラグ拡張を利用して、リザンプション時にオリジナルで利用されたSNIからまたがっても良いかを通知する。
サーバはNewSessionTicketメッセージ中にresumption_across_names(8)フラグを送ることができるようになる。
なおNewSessionTicketを使うのでTLS1.3以前では利用できません。


# 詳細
ServerNameがまたがるリザンプションは、 TLSフラグ拡張を通じてネゴシエートされます。
サーバはNewSessionTicketメッセージ中にresumption_across_names(8)フラグを送ってきても良い(MAY)
そのフラグは、その証明書中に提示されたどんなidentityに対するどのようなサーバでもチケットを受け取ることができるというサーバによってassert処理される。
このフラグを持ったチケットを受け付けたクライアントは、たとえ新しいServerNameがオリジナルセッション中の証明書とマッチしなかったとしても、サーバ証明書中のidentityに一致したServerNameに対してリザンプションを試みても良い(MAY) これはクライアントに対してオリジナルなサーバ証明書中に示された名前のリストを保持しておくことまでは要求しないという点に注意すること

そのフラグはTLS1.3以前ではNewSessionTicketメッセージが存在しないので使うことができません。

# 参考資料
- https://datatracker.ietf.org/doc/html/draft-ietf-tls-cross-sni-resumption-02
- スライド
  - https://datatracker.ietf.org/meeting/108/materials/slides-108-tls-cross-sni-resumption-00
