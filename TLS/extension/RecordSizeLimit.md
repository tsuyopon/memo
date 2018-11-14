# Record Size Limit Extension for Transport Layer Security (TLS)

# 解決したい課題
RFC6066で定義されるmax_fragment_lengthでは次のような課題がありました。(See: https://tools.ietf.org/html/rfc8449#section-3)
- クライアントとサーバの両方が送信するサイズを同一にしなければならない。
- クライアントからの提案に対して、サーバはそれよりも低い値を提案することができない。
- 最大レコードサイズは2^14であるが、2^12までしか指定できない。2^13や2^14は指定できない。

AEADでは解読と認証を行うためにはすべてのレコード情報を必要とします。その他のサイファースイートも同様です。
これらはIoTなどのようにOS資源が限られた環境下のデバイスにおいては難しい問題です。

# 解決方法
record_size_limitという新しい拡張をRFC8449で定義しています。この拡張はすべてのTLSバージョンで有効となります。
この仕様はMaxFragmentLength.mdで記述したRFC6066で定義されるmax_fragment_lengthを置き換える仕様です。


# 詳細


### 仕様
エンドポイントが受信できるサイズをオクテットで指定することができます。
```
uint16 RecordSizeLimit;
```

record_size_limit拡張がネゴシエーションされてきたら、エンドポイントはRecordSizeLimitで指定された値よりも大きなprotected recordを生成してはならない(MUST NOT)

### 特記事項
record_size_limitとmax_fragment_lengthの２つが両方ともClientHelloに表れた場合、サーバはmax_fragment_lengthを無視しなければならない(MUST)。
クライアントはrecord_size_limitとmax_fragment_lengthの両方を受信した場合にはfatal errorとして扱わなければならない(MUST)。


# 参考URL
- Record Size Limit Extension for TLS
  - https://datatracker.ietf.org/doc/rfc8449/
- https://tools.ietf.org/html/draft-ietf-tls-record-limit-03
- ASnoKaze blog
  - https://asnokaze.hatenablog.com/entry/2017/09/04/233741
