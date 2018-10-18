# 概要
HTTP拡張ヘッダであるExpect-CTレスポンスヘッダについて
- https://tools.ietf.org/html/draft-ietf-httpbis-expect-ct-07

# 解決する課題
- httpsで接続先のホストがSCT(Signed Certificate Timestamps)に対応した証明書がブラウザに送付されていることを明示する。
- 明示することによって不正なサーバ証明書などを検出することが可能になる。

# 解決方法
- CTに対応しているWebサーバがレスポンスヘッダとしてExpect-CTを応答することによって、それを受け取ったクライアント(ブラウザ)が公開CTログに現れるサイトすべての認証情報をチェックするように要求します。
```
// 送付されるExpect-CTヘッダの例
Expect-CT: max-age=3600, enforce, report-uri="https://{$subdomain}.report-uri.com/r/d/ct/reportOnly"
```
- クラインアント側ではCT対応のサーバ証明書が得られなかった場合には、何かがおかしいと判断してヘッダ中のreport-urlにレポートを送信します。


# 詳細
- max-ageは、policyに準拠すべき秒数を指定する。このヘッダの有効期間を意味している。
- enforceは、CTポリシーに違反した際、接続を拒否するように指示する。
- enforce指示とreport-uri指示の両方が存在する場合には、「強制と報告」の設定と呼ばれて証明書の透過性ポリシーへの準拠が強制され報告されるべきである。
- report-urlへ報告する内容は次のようなヘッダです。以下は報告されるサンプル。
```
{
    "expect-ct-report": {
        "date-time": "2018-05-10T07:00:00.000Z",
        "effective-expiration-date": "2018-05-10T07:00:00.000Z",
        "hostname": "example.com",
        "port": 443,
        "scts": [sct1, ... sctN],
        "served-certificate-chain": [pem1, ... pemN],
        "validated-certificate-chain": [pem1, ... pemN],
        "source": 
    }
}
```


# 参考
- CT対応を示すExpect-CTヘッダとは
  - https://asnokaze.hatenablog.com/entry/20161028/1477587599
- MDN web docs: Expect-CT
  - https://developer.mozilla.org/ja/docs/Web/HTTP/Headers/Expect-CT
- A new security header: Expect-CT
  - https://scotthelme.co.uk/a-new-security-header-expect-ct/
- CT is coming, are you ready?
  - https://scotthelme.co.uk/ct-is-coming/
