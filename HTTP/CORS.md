# 概要
Cross-Origin Resource Sharing（CORS）は、HTML5 世代の仕様です。w3cにより勧告されています。
- https://www.w3.org/TR/cors/

クロスドメイン制約に対する異なるオリジンへのアクセスを許可するにはCORSを使用します。
クロスオリジンドメイン制約とは、Ajaxリクエスト(XMLHttpRequest)などでコンテンツが生成されたドメインとは別のドメインにアクセスした場合にはエラーとなる仕組みです。

例えば、ブラウザで表示される次のエラーはクロスドメイン制約に対するものです。
```
クロスオリジン要求をブロックしました: 同一生成元ポリシーにより、http://example.co.jp/test.html にあるリモートリソースの読み込みは拒否されます (理由: CORS ヘッダー ‘Access-Control-Allow-Origin’ が足りない)。
```

# 詳細

### クロスドメイン制約を受けない場合
以下の指定の場合にはクロスドメイン制約をうけない。
```
<link rel="stylesheet" href="...">
<script src="..."></script>
<img>
<video>
<audio>
<object>
<embed>
<applet>
@font-face で指定されたフォント
<frame>
<iframe>
```

- SeeAlso
  - https://developer.mozilla.org/ja/docs/Web/Security/Same-origin_policy


### CORSで必要なリクエストヘッダ
- Orign
  - Originはリクエストを最初に開始したサーバーを示す URI です。ここにパス情報は含めず、サーバー名だけにします。
  - Ajaxでリクエストされる別ドメインはこのヘッダを見て、Originがこのサーバであれば大丈夫かどうかを判断します。
```
Origin: http://origin.co.jp
```
- Access-Control-Request-Method
  - リクエストは POST リクエストメソッドで送られることを、プリフライトリクエストの一部でサーバーに通知します
```
Access-Control-Request-Method: POST
```
- Access-Control-Request-Headers
  - 実際のリクエストにここで指定されたヘッダが含まれることを通知します。例えば、「X-PINGOTHER, Content-Type」の値が含まれていればこれら２つのヘッダがリクエストに入ることを通知します。
  - 独自のヘッダX-PINGOTHERなどを含めたい場合にはここで含める必要があります
```
Access-Control-Request-Headers: X-PINGOTHER, Content-Type
```

### CORSで必要な　レスポンスヘッダ
- Access-Control-Allow-Origin
  - このヘッダにはクロスサイト方式でアクセスできるドメインを返します。リクエストへのOriginヘッダに含まれる値を含むべきです。「*」などを返すこともあります。
```
Access-Control-Allow-Origin: http://origin.co.jp
```
- Access-Control-Allow-Methods
  - 当該リソースへのアクセスに対して指定されたメソッドだけが可能であることを示します。
```
Access-Control-Allow-Methods: POST, GET, OPTIONS
```
- Access-Control-Allow-Headers
  - 実際に使用できるリクエストヘッダとして認めるものを表しています。
```
Access-Control-Allow-Headers: X-PINGOTHER, Content-Type
```
- Access-Control-Max-Age
  - プリフライトリクエスト(OPTIONS)を送付しなくてもいいようにこのレスポンスをキャッシュしてもよい時間を秒数で指定します。
```
Access-Control-Max-Age: 86400
```
- Access-Control-Allow-Credentials
  - クロスドメインからリクエストを送付されてきてもCookieが送られてこない場合には、このヘッダをtrueにする必要がある。
  - あと、Access-Control-Allow-Originヘッダーを*指定にして全許可にしたら、うまくいかなかったとの記事もあったりするので注意すること
```
Access-Control-Allow-Credentials: true
```
- Access-Control-Expose-Headers
  - ブラウザが使用できるヘッダのホワイトリストをサーバーが示すことができます。例えば以下の場合であれば、ブラウザに対して X-My-Custom-Header および X-Another-Custom-Header ヘッダを許可します。オープンに公開しています
```
Access-Control-Expose-Headers: X-My-Custom-Header, X-Another-Custom-Header
```

https://qiita.com/tomoyukilabs/items/81698edd5812ff6acb34

### プリフライトリクエスト
プリフライトリクエストとは、ブラウザがCORSに該当するときに別サーバに対して何が許可されているかを実際にリクエストする前にOPTIONSで確認する仕組みです。

CORS仕様では、次の場合には必ず確認するように求められています。
- GET, POST, HEAD以外のメソッドを利用している
- HTTPリクエストヘッダにAccept, Accept-Language, Content-Language以外のフィールドが含まれている。または、Content-Typeフィールドにapplication/x-www-form-urlencoded, multipart/form-data, text/plain以外の内容が指定されている。

- 1. サーバからクライアントにOPTIONSメソッドで次の条件でアクセスできるかどうかを確認します。
```
OPTIONS https://example.com/testapi.php HTTP/1.1
Accept: */*
Origin: http://example.com/
Access-Control-Request-Headers: X-PINGOTHER, Content-Type
Access-Control-Request-Method: POST
```
- 2. サーバ側は上記リクエストを受け取ってOriginサーバが問題無いことの確認、メソッドなどが問題無いことを確認します。確認できたら次のレスポンスを応答します。
```
HTTP/1.1 200 OK
Access-Control-Allow-Origin: http://example.com/
Access-Control-Allow-Headers: X-PINGOTHER, Content-Type
Access-Control-Allow-Method: POST, GET, OPTIONS
Access-Control-Max-Age: 86400
Content-Length: 0
```
- 3. クライアントからサーバ側にリクエストします。
```
Method: POST
X-PINGOTHER: pingpong
Content-Type: application/json
Origin: http://example.com/
Access-Control-Request-Method: POST
Access-Control-Request-Headers: X-PINGOTHER, Content-Type
{json1: param1, json2: param2, ...}
```
- 4. サーバからクライアントにレスポンスが応答されます。
```
HTTP/1.1 200 OK
Content-Type: application/json
```

### JSONPによる同一生成元回避方法
JSONPでは、CORSを避けるためにscriptタグのスクリプトソースには同一生成元ポリシーがないことを利用します。
```
<script type="text/javascript" src="http://www.example.com/foo.php?id=1"></script>
```

JSONPとしてはつぎのようなJSON 文字列によるオブジェクトリテラルの送信に加えて、関数呼び出しを付け足します。
```
func1( {"id":1, "firstname":"Taro", "lastname":"Yamada"} );
```

JSONPだと誰でも読み込むことができるのでアクセス時に認証情報をパラメータなどに付与するとよいでしょう。

### SSLサイトアクセスの注意点
IEではhttpsのサイトからhttpのサイトを呼び出すことはセキュリティ上許可されていません。

### Apacheの設定
.htaccessなどに次のような設定を配置します。
```
Header append Access-Control-Allow-Origin: *
```

この辺も参考のこと
- https://qiita.com/kawaz/items/6a22c2c970c8d932a3a1

# 参考URL
- Cross-Origin Resource Sharing(W3C)
  - https://www.w3.org/TR/cors/
- The Web Origin Concept
  - https://www.ietf.org/rfc/rfc6454.txt
- HTTP アクセス制御 (CORS)(Mozilla)
  - https://developer.mozilla.org/ja/docs/Web/HTTP/HTTP_access_control
  - 海外版のサイトの方はシーケンス図が含まれている
    - https://developer.mozilla.org/en-US/docs/Web/HTTP/CORS#Preflighted_requests
- Using CORS
  - https://www.html5rocks.com/en/tutorials/cors/
