# HTTP Alternative Services
Alternative Servicesはオリジンを別のプロトコル、別のエンドポイント、別のポート(protocol/host/port)で提供できることをクライアントに通知する仕組みです。RFC7838で規定されています。

次の２つ方法で提供されています
- (1). Alt-Svcレスポンスヘッダの定義
- (2). HTTP/2において「The ALTSVC HTTP/2 Frame Type」という新しいフレームタイプを定義する方法

そして、Alt-Svcで指定された情報が利用された場合には次のヘッダがレスポンスとして応答されます。
- Alt-Used

また、上記がうまくさばけなかった場合に次のレスポンスコードを規定しています。
- The 421 (Misdirected Request) HTTP Status Code

# 詳細

### ALSTSVCの利用用途
利用用途などについては以下の資料に記載されているので参考にすること。
- http://syucream.hatenablog.jp/entry/2014/12/20/160552

### Alt-Svcの簡単な使い方
例えば、(1)の方法でクライアントが次のレスポンスヘッダを受信したのであれば、
現在のリクエストがHTTP/2(h2)でホスト名がnew.example.org、ポートが80で提供できる。またmax-age(ma)が3600秒であるといったことを意図しています(デフォルトだと24時間となっている)。
```
HTTP/1.1 200 OK
Content-Type: text/html
Cache-Control: max-age=600
Age: 30
Alt-Svc: h2="new.example.org:80"; ma=3600
```

上記Alt-Svcを受信したクライアントは、その情報を使ってリクエストを投げる場合にはAlt-Usedヘッダフィールドを付与する必要があります。ループを回避するためにこのヘッダの付与はMUSTです。
```
Alt-Used: new.example.org
```

Alt-Svcがうまくさばけなかった場合にはステータスコード421を応答します。

# 参考URL
- HTTP Alternative Services
  - https://tools.ietf.org/html/rfc7838
- ブログのしゅーくりーむ(HTTP Alternative Services について)
  - http://syucream.hatenablog.jp/entry/2014/12/20/160552

