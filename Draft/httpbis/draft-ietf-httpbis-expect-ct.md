# 概要

- https://tools.ietf.org/html/draft-ietf-httpbis-expect-ct-05


# 解決する課題
- httpsで接続先のホストがSCT(Signed Certificate Timestamps)に対応した証明書がブラウザに送付されていることを明示する。
- 明示することによって不正なサーバ証明書などを検出することが可能になる。


# 解決方法
- CTに対応しているWebサーバがレスポンスヘッダとしてExpect-CTを応答することによって、それを受け取ったクライアント(ブラウザ)が公開CTログに現れるサイトすべての認証情報をチェックするように要求します。
```
// 送付されるExpect-CTヘッダの例
expect-ct: enforce;max-age=3600;report-uri=https://example.com/report-uri
```
- クラインアント側ではCT対応のサーバ証明書が得られなかった場合には、何かがおかしいと判断してヘッダ中のreport-urlにレポートを送信します。



# 参考
- CT対応を示すExpect-CTヘッダとは
  - https://asnokaze.hatenablog.com/entry/20161028/1477587599

- MDN web docs: Expect-CT
  - https://developer.mozilla.org/ja/docs/Web/HTTP/Headers/Expect-CT
