# 概要
現在のHTTPではレスポンスを返却するとcssやjsを読み込んでレンダリングするまでは使用することができないといった問題点がある。
そこで、あらかじめサーバ側の方からクライアントに対して必要となる素材のリンクを通知する仕組みとして103 Early HintsがExperimentalのRFCで提示されている。
これによって、クライアントを利用するユーザーからの体感時間を早くさせる効果がある。

# 詳細

### 仕様
- Early Hintはあくまでもヒントであり、これによって生成される結果に影響があってはならない。
   - 最終的な処理の結果によって最後に応答される結果のフィールドと異なる場合がありえる。
- 同一ドメインに限りあらかじめ読み込みなどのヒントをクライアント側に通知する仕組みが必要となる。

### リクエストサンプル 例1
- クライアントからのリクエスト
```
GET / HTTP/1.1
Host: example.com
```
- サーバからのレスポンス
  - Early Hintsを送信する場合
```
HTTP/1.1 103 Early Hints
Link: </style.css>; rel=preload; as=style
Link: </script.js>; rel=preload; as=script
```
  - 200応答を返す場合
```
HTTP/1.1 200 OK
Date: Fri, 26 May 2017 10:02:11 GMT
Content-Length: 1234
Content-Type: text/html; charset=utf-8
Link: </style.css>; rel=preload; as=style
Link: </script.js>; rel=preload; as=script
```

### リクエストサンプル 例2  (複数回103をレスポンスし、最終的な結果として一部のassetしか使われない例)
- 2度のEarly Hintsが送付されてくる場合がある
```
HTTP/1.1 103 Early Hints
Link: </main.css>; rel=preload; as=style
```
```
HTTP/1.1 103 Early Hints
Link: </style.css>; rel=preload; as=style
Link: </script.js>; rel=preload; as=script
```
- 結果としてEarly Hintsで送付された３つのうち２つのみを使っている
```
HTTP/1.1 200 OK
Date: Fri, 26 May 2017 10:02:11 GMT
Content-Length: 1234
Content-Type: text/html; charset=utf-8
Link: </main.css>; rel=preload; as=style
Link: </newstyle.css>; rel=preload; as=style
Link: </script.js>; rel=preload; as=script
```

# SeeAlso
- RFC8297: An HTTP Status Code for Indicating Hints
  - https://tools.ietf.org/html/rfc8297
- スライド
  - https://www.ietf.org/proceedings/97/slides/slides-97-httpbis-sessb-early-hints-00.pdf
