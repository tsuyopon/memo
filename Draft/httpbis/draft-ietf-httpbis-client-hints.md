# 概要
HTTP Client Hintsについて
- https://tools.ietf.org/html/draft-ietf-httpbis-client-hints-05

# 解決する課題
- クライアント側デバイスでは、デバイスに特化した情報にアクセスしたいが、サーバ上でそれを知る手段が無い。
  - 画像ごとのデバイスピクセル比などUser-Agentだとデバイスごとにその情報をサーバに配置しなければならないので、
- ここではUser-Agentの代替となるわけではないことに注意する。
  - なぜならUser-Agentを置き換えるわけではなく、サーバ上でそのデバイス情報に特化した情報をキャッシュフレンドリに扱いたいといった意図がある。なぜならば、User-Agentで扱うのであればサーバ側でそのデバイス固有の情報を保持していなければならない

# 解決方法

次のようなヘッダを新しく定義する
- DPR
- Width
- Viewport-Width
- Accept-CH
- Accept-CH-Lifetime
- Save-Data
- Content-DPR

以下では例を見ていくとする。

クライアントからは次のようなデバイス特化に関するヘッダがサーバ側に付与される。
これはDPR(Device Pixel Rate)が2.0で、要求されたリソース幅が160CSS px(320/2.0)、そしてviewportの幅が320であることを意味する。
```
DPR: 2.0
Width: 320
Viewport-Width: 320
```

サーバ側はDPRとして次の値を選択したということを次のヘッダでクライアントに返答する。以下の例では1.0を返却している。
```
Content-DPR: 1.0
```

また、サーバ側は次のようなヘッダをクライアント側に返却するかもしれない。
以下はAccept-CHヘッダで受け入れたヘッダ情報を記述して、その有効時間についてはAccept-CH-Lifetimeで明示している。
```
Accept-CH: DPR, Width
Accept-CH: Viewport-Width
Accept-CH-Lifetime: 86400
```

TODO: Save-Dataヘッダの例について記載する。


