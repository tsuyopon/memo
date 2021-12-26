# 概要
証明書を圧縮するための方法をサーバに伝える仕組みのが拡張として定義されています。
この仕組みはTLS1.3以上で機能し、TLS1.2以下では無視されます。
- https://datatracker.ietf.org/doc/html/rfc8879

# 解決したい課題
証明書は送付されるTLSデータの大部分を占めています。これらの問題によるレイテンシやパフォーマンス悪化の問題がもたらされています。
RFC7924のCachedInfo拡張を使うことによってクライアントとサーバ間で初期段階で共有した証明書情報の送付を避けることができますが、接続時初回のハンドシェイクではこの問題は回避できていません。

# 解決方法
フルハンドシェイク中にクライアント側からサーバ側に証明書を圧縮してほしい旨を伝える仕組みを提供します。
以下の拡張を新規で定義します。
- compress_certificate(27)

具体的にはClientHello, CertificateRequewst拡張でこの新規拡張を付与することができます。
拡張経由でCertificateメッセージを圧縮可能なアルゴリズムによって圧縮して欲しい旨をpeerに伝えます。
これを受け取ったpeer側は、Certificateメッセージは圧縮して送付しても良いことを知り、その圧縮アルゴリズムで何が利用可能かを理解します。
この拡張は一方通行なのでpeerからの対応したecho backレスポンスは不要です。

注意点として、この拡張は「Middlebox Compatibility」(section6)で定義されているように、ミドルボックスが意図しないメッセージをドロップする可能性があるので、TLS1.3以上のバージョンのみで有効な拡張としての扱いとなります。TLS1.2以下では無視されます。

# データ構造

### ClientHelloへの拡張
CertificateCompressionAlgorithmsという構造体を定義しています。
その中にalgorithmsと呼ばれるリストを定義しています。この仕様ではzlibとbrotliのみ定義されています。
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

### CompressedCertificateメッセージ
もしpeerが圧縮をサポートしているということを示してきて、サーバとクライアントは一致するCertificateメッセージを圧縮しても良い。
以下に示すCompressedCertificateメッセージはCertificateメッセージを置き換えます。
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
    - 下記それぞれのアルゴリズムに従って圧縮しなければならない(MUST)
      - zlibならば https://tools.ietf.org/html/rfc1950 に従う
      - brotliならば https://tools.ietf.org/html/rfc7932 に従う
      - zstdならば https://datatracker.ietf.org/doc/html/rfc8478 に従う

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
  - https://datatracker.ietf.org/doc/html/rfc8879
