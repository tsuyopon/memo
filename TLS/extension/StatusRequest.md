# 概要
status_request拡張はOCSP Staplingを実現するための拡張です。
TLSハンドシェイク中にクライアント証明書のステータス情報をサーバからクライアント側に送付することを許可することを示しています。

OCSPだけだと3rdパーティのOCSPレスポンダに頼ることでレスポンスが悪化するなどがありましたが、OCSP Staplingとすることで独自のサーバから失効情報を配信できるようになりました。
RFC6066中においてCertificateStatusというメッセージが規定されていて、Certificateメッセージの後に送付するように規定されています。

# 詳細

## 動作概要
ClientHello中にstatus_request拡張を信頼するレスポンダリストも含めて埋め込むことによってクライアント側はOCSP Staplingに対応していることを明示します。
サーバ側がOCSP Staplingに対応していたらServerHelloでstatus_requestを応答します。
その後、ハンドシェイクのCertificateメッセージの後に送付されてくる、CertificateStatusというOCSP Stapling専用のメッセージをサーバから受け取ることでクライアントは送付されてくるメッセージをチェックします。

## データ構造 

### ClientHello
ClientHelloの拡張データには信頼できるOCSPレスポンダのリストresponder_id_listとX509の拡張情報を表すrequest_extensionsが含まれるようです。
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
- Extensions: 以下のRFC5280のExtensionsが参照される。
  - https://tools.ietf.org/html/rfc5280#section-4.1.2.9

### ServerHello
OCSP StaplingのCertificateStatusメッセージを応答する場合にはServerHelloにはstatus_request拡張を空データで含めなければならに。

### CertificateStatus
```
struct {
    CertificateStatusType status_type;
    select (status_type) {
        case ocsp: OCSPResponse;
    } response;
} CertificateStatus;

opaque OCSPResponse<1..2^24-1>;
```

注意点としては以下の通り
- サーバ側はstatus_requestに対応しているとServerHelloで応答したにも関わらずCertificateStatusメッセージを返さないかもしれない。
- サーバはクライアントとstatus_requestのネゴシエーションをしていない限りCertificateStatusメッセージを送付してはならない(MUST NOT)。
- クライアントはCertificateStatusメッセージのOCSPレスポンスをチェックしなければならない

## データ構造サンプル
### ClientHelloサンプル
```
Extension: status_request
    Type: status_request (0x0005)
    Length: 5
    Certificate Status Type: OCSP (1)
    Responder ID list Length: 0
    Request Extensions Length: 0
```

### ServerHelloサンプル
status_reuqestに対応している場合には空の応答が入ってくる。
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
