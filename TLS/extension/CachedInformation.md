# Transport Layer Security (TLS) Cached Information Extension
このTLS拡張はTLSクライアントがキャッシュされた証明書に関する情報を保持していることをサーバに伝えることによって、サーバ側から証明書の転送を省略ができる仕組みです。
近年、IoTのような環境において、低バンド幅環境ではこれらの情報量の削減がパフォーマンス改善に繋がっています。

IANAではcached_info(25)として定義されています。
- https://www.iana.org/assignments/tls-extensiontype-values/tls-extensiontype-values.xhtml


# 詳細

## 利用方法
- 1. クライアントとサーバでフルハンドシェイクでを行う
- 2. セッションリザンプションなしでTLSクライアントがサーバにその後つなぎに行った際に、キャッシュされた証明書を保持していることを明示するためにClientHelloにCachedInfo拡張を付与する。CachedInfoは証明書のフィンガープリントを提示します。
- 3. もしサーバ側の証明書が変化してなかったら、TLSサーバはCertificateを送付する必要無く、またクライアント側も証明書チェーンをたどる必要がない。
     クライアントによって提示されたフィンガープリントとサーバ側の証明書が一致しなければ、Clientにキャッシュを更新するためのCertificateメッセージを送付します。


まずは最初にフルハンドシェイクを行う。
クライアントは(1)で受け取った証明書をその後キャッシュして利用する。
```
   ClientHello            ->
                          <-  ServerHello
                              Certificate* // (1)
                              ServerKeyExchange*
                              CertificateRequest*
                              ServerHelloDone

   Certificate*
   ClientKeyExchange
   CertificateVerify*
   [ChangeCipherSpec]
   Finished               ->

                          <- [ChangeCipherSpec]
                             Finished

   Application Data <-------> Application Data
```

続いて、セッションリザンプションを利用しないという条件下においてcached_info(type=cert)をClientHelloで指定する。この時にcertには前回のハンドシェイクで取得した証明書のフィンガープリントを含む。
サーバ側もcached_infoに対応していたら同様に応答を行う(3)。
前回取得した証明書のフィンガープリントと一致していたら(4)のCertificateメッセージは省略することができる。
```
   ClientHello
   cached_info=(cert)     -> // (2)
                          <-  ServerHello
                              cached_info=(cert) (3)
                              Certificate (4)
                              ServerKeyExchange*
                              ServerHelloDone

   ClientKeyExchange
   CertificateVerify*
   [ChangeCipherSpec]
   Finished               ->

                          <- [ChangeCipherSpec]
                             Finished

   Application Data <-------> Application Data
```




## データ構造について
ClientHelloの場合にはCachedInformation構造を含めなければなりません。
クライアントは複数の証明書をキャッシュしている場合、同じCachedInformationTypeの複数のCachedObjectsを送付してくるかもしれません。
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
このタイプの場合には、クライアントはhash_valueフィールド中のCertificateメッセージのフィンガープリントを含めなければならない。
フィンガープリントはCertificateメッセージを入力値として算されなければならない。

### CachedInformationType = cert_req の場合
クライアントはhash_valueフィールド中のCertificateRequestメッセージのフィンガープリントを含めなければならない。
フィンガープリントはCertificateRequestメッセージを入力値として計算されなければならない。


## フィンガープリントの計算について
CachedInformationTypeがcertの場合も、cert_reqの場合も入力値が異なるだけで計算方法は同じである。
- 1. 入力データのSHA-256ハッシュを計算する
- 2. SHA-256ハッシュの出力結果を利用する


# 参考URL
- Transport Layer Security (TLS) Cached Information Extension
  - https://tools.ietf.org/html/rfc7924
