# Maximum Fragment Length Negotiation 拡張
max_fragment_lengthはRFC6066で定義されているTLS拡張で、TLSレコード長の最大サイズを変更することができます。
これは制約されたクライアントの環境ではメモリ制約によって更に小さなサイズを送付したい場合がありますが、このような課題を解決します。

この仕様はいくつかの課題があることから現在ではRecord Size Limit拡張(RFC8449)に置き換わっています。この課題についてはRecordSizeLimit.mdに記載しています。

# 詳細

データ仕様としては次の通りです。
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

# 参考URL
- Transport Layer Security (TLS) Extensions: Extension Definitions
  - https://tools.ietf.org/html/rfc6066
