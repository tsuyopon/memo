# 概要
次にある資料の概要を把握する
- https://tools.ietf.org/wg/httpbis/


- agenda
  - https://datatracker.ietf.org/meeting/102/materials/agenda-102-httpbis-00

# 詳細

### 個人ドキュメント
- draft-bishop-httpbis-sni-altsvc
  - 

### Active
- draft-ietf-httpbis-bcp56bis
  - 
- draft-ietf-httpbis-cache
  - RFC7234(Hypertext Transfer Protocol (HTTP/1.1): Caching)ではHTTP/1.1固定だったが、このバージョン表記を削除して統一的な仕様としている。
- draft-ietf-httpbis-cache-digest
  - 
- draft-ietf-httpbis-client-hints
  - クライアントからデバイスピクセル値に関するヘッダを送付する仕組み。CH-DPRやCH-RWといったヘッダを規定している。
- draft-ietf-httpbis-expect-ct
  - CTに対応しているWebサーバがレスポンスヘッダとしてExpect-CTを応答することによって、それを受け取ったクライアント(ブラウザ)が公開CTログに現れるサイトすべての認証情報をチェックするように要求します。
- draft-ietf-httpbis-header-structure
  - 今後出てくるようなHTTPヘッダフィールドの構造も含めて規定してしまおうというRFCである。
- draft-ietf-httpbis-http2-secondary-certs
  - 
- draft-ietf-httpbis-messaging
  - 
- draft-ietf-httpbis-rand-access-live
  - 既存のHTTPでRangeリクエストを指定する場合には必ず範囲指定をする必要があるが、この仕様で「Content-Range: bytes 1230000-999999999999/\*」などと記述することによってライブストリーミングなどの大量のデータであると解釈してサーバ側が指定されたバイト列から一部だけ返却します。
- draft-ietf-httpbis-semantics
  - RFC7230, RFC7232, RFC7233, RFC7235などの散在するHTTP RFCを1つにまとめたいといった感じか?(TODO)
- draft-ietf-httpbis-variants
  - HTTPのための2番目のキャッシュキーの代替手段を提供する。これには、「Variants」、「Variant-Key」レスポンスヘッダを規定する。
  - この仕様の目的はHTTPの先を見据えたコンテンツの取得に関してキャッシュフレンドリーにするためのものである。
- draft-ietf-httpbis-rfc6265bis: Cookies: HTTP State Management Mechanism
  -

### IESG Processing
- draft-ietf-httpbis-replay
  -  TLS1.3の0-RTTへの対策のために「Early-Data」ヘッダと425ステータスコードを規定している。

### RFC-Editor's Queue
- draft-ietf-httpbis-h2-websockets
