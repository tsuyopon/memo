# 概要
status_request拡張はTLSハンドシェイク中にクライアント証明書のステータス情報(つまり、OCSP)をサーバからクライアント側に送付することを許可することを示しています。
これは制限されたネットワーク環境下でバンド幅を節約するためのCRL転送を避けるために望ましいとされています。

# 詳細

### 動作概要
ClientHello中にstatus_request拡張を埋め込むことによってクライアント側はOCSPに対応していることを明示することができます。

### データ構造 
```
struct {
    CertificateStatusType status_type;
    select (status_type) {
        case ocsp: OCSPStatusRequest;
    } request;
} CertificateStatusRequest;

enum { ocsp(1), (255) } CertificateStatusType;

struct {
    ResponderID responder_id_list<0..2^16-1>;
    Extensions  request_extensions;
} OCSPStatusRequest;

opaque ResponderID<1..2^16-1>;
opaque Extensions<0..2^16-1>;
```

上記から次のようなデータ構造になります
- CertificateStatusType: 固定で"ocsp"を表す1が入る
- ResponderID: クライアントが信用するOCSPレスポンダIDのリスト。ここが0の場合には特別な意味があり、暗にサーバ側によって知られているといった意味となる。
- Extensions: 


### データ構造サンプル
- ClientHelloサンプル
```
Extension: status_request
    Type: status_request (0x0005)
    Length: 5
    Certificate Status Type: OCSP (1)
    Responder ID list Length: 0
    Request Extensions Length: 0
```
- ServerHelloサンプル
```
Extension: status_request
    Type: status_request (0x0005)
    Length: 0
```

### opensslコマンドについて
opensslコマンドを利用して次に示すような情報を確認するには../openssl_ocsp.mdに記載していますのでそちらを参考のこと
- StatusRequestをClientHelloに含めて、OCSPレスポンスがあるかどうかを確認する方法
- OCSPサーバを起動する方法
- OCSPサーバに問い合わせるリクエスト内容を確認する方法

# SeeAlso
- RFC6066: Transport Layer Security (TLS) Extensions: Extension Definitions
  - https://tools.ietf.org/html/rfc6066#section-8
