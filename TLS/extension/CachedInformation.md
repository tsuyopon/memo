# Transport Layer Security (TLS) Cached Information Extension
このTLS拡張はTLSクライアントがキャッシュされた証明書に関する情報を保持していることをサーバに伝えることによって、サーバ側から証明書の転送を省略ができる仕組みです。
近年、低バンド幅の環境などではこれらの情報量の削減がパフォーマンス改善に繋がってきています。


IANAではcached_info(25)として定義されています。
- https://www.iana.org/assignments/tls-extensiontype-values/tls-extensiontype-values.xhtml


# 詳細


## データ構造について
ClientHelloの場合にはCachedInformation構造を含めなければなりません。
```
enum {
     cert(1), cert_req(2) (255)
} CachedInformationType;

struct {
     select (type) {
       case client:
         CachedInformationType type;
         opaque hash_value<1..255>;
       case server:
         CachedInformationType type;
     } body;
} CachedObject;

struct {
     CachedObject cached_info<1..2^16-1>;
} CachedInformation;
```

### CachedInformationType = cert の場合
クライアントは同一のCachedInformationTypeである複数のCachedObjectsを送付するかもしれません。これは、サーバからの複数の証明書をキャッシュしているケースです。
certタイプの場合には、hash_valueをSHA-256で計算します。

### CachedInformationType = cert_req の場合


# 参考URL
- Transport Layer Security (TLS) Cached Information Extension
  - https://tools.ietf.org/html/rfc7924
