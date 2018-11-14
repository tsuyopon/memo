# Maximum Fragment Length Negotiation 拡張
max_fragment_lengthはRFC6066で定義されているTLS拡張で、TLSレコード長の最大サイズを変更することができます。
これは制約されたクライアントの環境ではメモリ制約によって更に小さなサイズを送付したい場合がありますが、このような課題を解決します。

この仕様はいくつかの課題があることから現在ではRecord Size Limit拡張(RFC8449)に置き換わっています。この課題についてはRecordSizeLimit.mdに記載しています。

ただし、この仕様は現在RFC8449によって置き換えられています。
- https://tools.ietf.org/html/rfc8449

# 課題したい課題
この拡張が存在しない場合、レコードレイヤーにおいて最大固定長である2^14バイトが指定されてくる可能性があります。
これは、TLSPlaintext.lengthのサイズ数が入ることになります。
- https://tools.ietf.org/html/rfc5246#section-6.2.1

これは、2^14をそのまま利用すると制約されたクライアント環境などではメモリ制限やバンド幅制限に引っかかる可能性があり、2^14よりも小さな固定長サイズで送付してくるための仕組みが必要となります。

# 解決手段
max_fragment_length拡張を定義します。
小さな最小フラグメントサイズをネゴシエーションできるようにするために、クライアントがmax_fragment_length拡張をClientHelloで送付するようにします。
ClientHelloに含めるデータは次のようにいくつかの種類が固定で定められています。
```
enum{
    2^9(1), 2^10(2), 2^11(3), 2^12(4), (255)
} MaxFragmentLength;
```

データ仕様は次の通りです。
- ClientHelloはMaxFragmentLengthを指定する。
- ServerHelloはMaxFragmentLengthに応答するのであれば、その値を返却します。
- ServerHelloで返却するMaxFragmentLength拡張の値はClientHelloと同じでなければなりません。

次の場合にはエラーアラートを返します(MUST)
- ServerHelloで拡張応答が存在している場合に、ClientHelloと値が異なっている場合
- 拡張の値として指定されている値が許可されていない場合

# 特記事項
近年では次のような課題を解決したいという要望がありRFC8449が作成されることとなった。
- クライアントとサーバの両方が送信するサイズを同一にしなければならない。
- クライアントからの提案に対して、サーバはそれよりも低い値を提案することができない。
- 最大レコードサイズは2^14であるが、2^12までしか指定できない。2^13や2^14は指定できない。

# 参考URL
- RFC6066: Transport Layer Security (TLS) Extensions: Extension Definitions
  - https://tools.ietf.org/html/rfc6066
