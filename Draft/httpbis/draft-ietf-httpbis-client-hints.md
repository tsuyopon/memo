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

以下では例を見ていくことにします。

まずはクライアントがリクエストを行ってサーバ側から次の応答が帰ります。Accept-CHというヘッダでクライアントからサーバに送ってきてほしいヘッダ情報を指定します。
```
GET /index.html
...
HTTP/1.1 200 OK
Accept-CH: DPR, Viewport-Width, Width, Downlink, Save-Data
Accept-CH-Lifetime: 86400
```

クライアントがAccept-CHに対応している場合には、次回リクエストからは先程のAccept-CHで指定したヘッダが付与されてきます。
これはDPR(Device Pixel Rate)が2.0で、要求されたリソース幅が300CSS px(600/2.0)、そしてviewportの幅が320であることを意味します。
```
GET /ilovebroccoli.jpg

DPR: 2.0
Width: 600
Viewport-Width: 320
Save-Data: on
```

サーバ側はDPRとして次の値を選択したということをContent-DPRヘッダでクライアントに返答する。
```
200 OK
Content-Type: image/jpeg
...
Content-DPR: 0.5
Vary: DPR
Cache-Control: private, no-transform
```

TODO: Save-Dataヘッダの例について記載する。


