# Transport Layer Security (TLS) Certificate Compression
- https://tools.ietf.org/html/draft-ietf-tls-certificate-compression-03

# 解決したい課題
- TLSハンドシェイクの証明書チェーンは送信バイトの大部分を構成しているので、レイテンシやパフォーマンスに影響がある。
- RFC7924ではcached_info拡張により証明書をキャッシュするメカニズムが標準となったが、これだけでは初回接続時には問題となる。

# 解決方法
- 新しいTLS拡張としてcompress_certificateを定義することによって相手先に圧縮フォーマットのサポートを伝える。ClientHelloでこの拡張を送付することによってサーバ側に圧縮されたサーバ証明書を受け取ることを通知する。
- なお、この拡張はTLS1.3以上のみサポートして、それ以下のバージョンであればこの拡張を無視しなければならない


# 仕様

### ClientHello
拡張通知で圧縮アルゴリズムを指定することができます。
```
enum {
    zlib(1),
    brotli(2),
    zstd(3),
    (65535)
} CertificateCompressionAlgorithm;

struct {
    CertificateCompressionAlgorithm algorithms<2..2^8-2>;
} CertificateCompressionAlgorithms;
```

zlibやbrotilは次のRFC仕様に準ずるものがサーバから送られてきます。
- zlib
  - https://tools.ietf.org/html/rfc1950
- brotil
  - https://tools.ietf.org/html/rfc7932
- zstd
  - https://tools.ietf.org/html/rfc8478

### ServerHello
クライアント側へのエコーバックは不要

### Certificate
圧縮されたメッセージは次の構造で送付される。
```
struct {
     CertificateCompressionAlgorithm algorithm;
     uint24 uncompressed_length;
     opaque compressed_certificate_message<1..2^24-1>;
} CompressedCertificate;
```
- algorithm: ClientHelloのcompress_certificate拡張で指定したアルゴリズムのリストの中のものが利用されなければならない(MUST)
- uncompressed_length: 解凍後のサイズ
- compressed_certificate_message: 証明書の圧縮されたボディ


受信したメッセージが正しくdecompressedできなければ、bad_certificateアラートを通知しなければならない。


# 参考URL
- https://tools.ietf.org/html/draft-ietf-tls-certificate-compression-05


