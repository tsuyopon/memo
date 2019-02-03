# 概要
証明書を圧縮するための方法をサーバに伝える仕組みのドラフトがあります。compress_certificate拡張を以下のドラフトで定義しています。
- https://tools.ietf.org/html/draft-ietf-tls-certificate-compression-04

# 解決したい課題
証明書は送付されるTLSデータの大部分を占めています。これらの問題によるレイテンシやパフォーマンス悪化の問題がもたらされています。
RFC7924のCachedInfo拡張を使うことによってクライアントとサーバ間で初期段階で共有した証明書情報の送付を避けることができますが、接続時初回のハンドシェイクではこの問題は回避できていません。

# 解決方法
フルハンドシェイク中にクライアント側からサーバ側に証明書を圧縮してほしい旨を伝える仕組みを提供します。
具体的にはClientHelloの拡張を定義します。拡張経由でCertificateメッセージを圧縮可能なアルゴリズムをサーバ側に明示します。これを受け取ったサーバ側は、クライアント側はCertificateメッセージが圧縮可能であり、その圧縮アルゴリズムで何が利用できるのかを理解します。サーバ側によるServerHelloによるecho backは不要です。

注意点として、この拡張は「Middlebox Compatibility」(section5)で定義されているように、ミドルボックスが意図しないメッセージをドロップする可能性があるので、TLS1.3以上のバージョンのみで有効な拡張としての扱いとなります。TLS1.2以下では無視されます。

# データ構造

### ClientHelloへの拡張
CertificateCompressionAlgorithmsという構造体を定義しています。
その中にalgorithmsと呼ばれるリストを定義しています。この仕様ではzlibとbrotliのみ定義されています。
```
enum {
    zlib(1),
    brotli(2),
    (65535)
} CertificateCompressionAlgorithm;

struct {
    CertificateCompressionAlgorithm algorithms<1..2^8-1>;
} CertificateCompressionAlgorithms;
```


### CompressedCertificateメッセージ
CompressedCertificateメッセージはCertificateメッセージを置き換えます。
```
struct {
     CertificateCompressionAlgorithm algorithm;
     uint24 uncompressed_length;
     opaque compressed_certificate_message<1..2^24-1>;
} CompressedCertificate;
```

- algoritm: 
  - 証明書を圧縮するアルゴリズムが含まれています。これはcompress_certificate拡張中に含まれるアルゴリズムのうちの１つが指定されていなければなりません(MUST)
- uncompressed_length:
  - uncompressedなCertificateメッセージの長さを表します。圧縮後にこの値と一致しなければ、bad_certificateアラートで中断しなければならない(MUST)
- compressed_certificate_message:
  - Certificateメッセージの圧縮されたボディが入ります。
    - zlibならば https://tools.ietf.org/html/rfc1950 に従って圧縮し、brotliならば https://tools.ietf.org/html/rfc7932 に従って圧縮しなければならない(MUST)

受信したCompressedCertificateメッセージが解答できなければ、bad_certificateアラートで中断しなければならない(MUST)

# パケットサンプル
ClientHelloに次に示すようなデータが付与されます。
```
Extension: compress_certificate (len=3)
    Type: compress_certificate (27)
    Length: 3
    Algorithms Length: 2
    Algorithm: broli (2)
```

# SeeAlso
- TLS Certificate Compression
  - https://tools.ietf.org/html/draft-ietf-tls-certificate-compression-04
