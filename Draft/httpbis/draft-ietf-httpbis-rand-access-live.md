# HTTP Random Access and Live Content


# 解決する問題点
ライブコンテンツ、音声、ログデータ、ブロックチェーンデータベースなどをHTTPで取得する場合には次のような指定しかできなかった。

- 次の場合だと1000byteからデータの最後までを応答する
```
HEAD /resource HTTP/1.1
Range: bytes=1000-
...
```

- 次の場合だと1000byteから終わりはレスポンスデータがわからない場合に指定します。この場合だと、1000-2000バイトのデータしか帰ってきません。
```
HTTP/1.1 206 Partial Content
Content-Range: bytes 1000-2000/*
...
```

クライアントは増えた分のコンテンツを読み込むには再度指定しなければなりません。

このようにいくつかのアプリケーションではこれらの大量のデータのやりとりをもっと効率よくするためにこの仕様が追加されました。

# 解決方法
クライアントから最大指定が大きいとliveコンテンツへの仕様と判断します。
```
GET /resource HTTP/1.1
Range: bytes=1230000-999999999999
```

サーバ側はliveコンテンツとして解釈して次のようにchunkedにより応答します。
```
HTTP/1.1 206 Partial Content
Content-range: 1230000-9999999999999/*
Transfer-encoding: chunked
...
```


# 参考URL
- https://asnokaze.hatenablog.com/entry/2017/12/03/165022
