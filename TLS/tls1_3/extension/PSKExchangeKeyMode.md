# 概要
PSKを使用するために、クライアントはpsk_key_exchange_mode拡張を送らなければなりません。

この拡張では次の２モードのいずれかを指定することができます。
- psk_ke: PSK-only key establishment.
  - このモードではサーバはkey_shareの値を返してはならない
  - 共有している鍵だけを種に使って暗号路の鍵を生成します。
- psk_dhe_ke: PSK with (EC)DHE key establishment. 
  - このモードではクライアントとサーバはkey_share拡張(#section4.2.8)で定義される通りに値を提供しなければならない
  - 共有している鍵に加えて、新たに(EC)DHE で共有した鍵を種に使って暗号路の鍵を生成。このモードは前方秘匿性を持つ

なお、TLS1.3ではPSKはセッション再開(resumption)と統合されることになりました。
TLS1.2まではPSKというとExternal PSKのみを指しましたが、TLS1.3ではExternal PSKの他にResumption PSKを指すことになります。
- External PSK: 手作業で共有した鍵を使って、互いを認証すること
- Resumption PSK: 前のセッションで共有した鍵を使って、サーバ認証を省略すること
  - TLS1.2までのセッション再開はこちらに該当します。最初はフルハンドシェイクを行いNewSessionTicketによりPSKを取得することができます。

# 詳細

### 仕様
- クライアントはpre_shared_key拡張を提示する場合には、psk_key_exchange_modes拡張も提示しなければなりません。
  - クライアントがpsk_key_exchange_modes拡張を提示せず、pre_shared_keyを提示してきたら、サーバはハンドシェイクをアボートしなければなりません。
- サーバはpsk_key_exchange_modes拡張を送付してはなりません。


サーバはクライアントによって提示されたリストに存在しない鍵交換モードを選択してはいけません。
この拡張はPSK resumptionの使用を制限します。サーバは公告されてきたモードに準拠しないチケットにNewSessionTicketを送付すべきではありません(SHOULD NOT)。


### データ書式
```
enum { psk_ke(0), psk_dhe_ke(1), (255) } PskKeyExchangeMode;
```
上記の２モードの説明は概要に記載しています。

```
struct {
    PskKeyExchangeMode ke_modes<1..255>;
} PskKeyExchangeModes;
```

### データ構造サンプル(TLS1.3 draft23)
```
Extension: psk_key_exchange_modes (len=2)
    Type: psk_key_exchange_modes (45)
    Length: 2
    PSK Key Exchange Modes Length: 1
    PSK Key Exchange Mode: PSK with (EC)DHE key establishment (psk_dhe_ke) (1)
```

# 参考URL
- TLS 1.3 開発日記 その6 Pre Shared KeyAdd Star 
  - http://d.hatena.ne.jp/kazu-yamamoto/20161213/1481681466

# SeeAlso
- https://tools.ietf.org/html/rfc8446#section-4.2.9

