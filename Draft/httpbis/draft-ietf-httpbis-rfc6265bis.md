# Cookies: HTTP State Management Mechanism

# 解決したい課題
このRFC6265bisの前はもともとはそれぞれ別のドラフトとして扱われていました。
- (1). Cookie Prefixes
  - サーバ側はブラウザが保持しているCookieにどのような属性が付与されているのかを知る方法がありません。自分でSetしたCookieですが、Cookieを共有するサブドメインやJavaScriptに変更されている可能性などもあります。
  - https://tools.ietf.org/html/draft-ietf-httpbis-cookie-prefixes-00
- (2). Same-Site Cookies
  - クロスサイトなリクエストに対してCookieを送付しないようにしたい。
  - https://tools.ietf.org/html/draft-ietf-httpbis-cookie-same-site-00
- (3). Deprecate modification of 'secure' cookies from non-secure origins
  - 非セキュアなhttp://のオリジンサーバから、secure属性が付与されたCookieをセットできないようにしたい。
  - https://tools.ietf.org/html/draft-ietf-httpbis-cookie-alone-01

また、上記以外にも次の課題も対応された
- (4) Cookie2やSet-Cookie2はCookieやSet-Cookieよりも柔軟な設定が可能だが、現状ではほとんど使われていない

これ以外にも細かい修正は行われていますが、02までを確認した感じだと主要な修正は上記の(1)〜(4)の4つである。

# 解決方法
(1)〜(4)それぞれについて以下で述べます。


### (1) Cookie Prefixes
サーバ側でも識別できるように「__Secure-」と「__Host-」prefixを用意する。また、これによって、サーバ側はブラウザ側に対して属性を強制させる仕様であることを明示する。
- __Secure: Secure属性が付与されていないCookieは拒否される
- __Host: Secure属性が付与されていて、path属性が設定されている。Domain属性は指定されていない。


次の場合だとsecureフラグがセットされていないと拒否される。
```
Set-Cookie: __Secure-SID=12345; Domain=example.com
```

次の場合だとhttps接続で、secureフラグがセットされていないと拒否される
```
Set-Cookie: __Secure-SID=12345; Secure; Domain=example.com
```

次の場合だとPathを入れる場合には「__Host-」prefixのCookieを指定する。この場合にはDomainはいれてはならない。
```
Set-Cookie: __Host-SID=12345; Secure; Path=/
```

TODO: __Hostの役割がよくわかっていない。なぜPathを入れて、Domainを入れてはならないのか...

### (2) 

SameSiteという新しい属性を定義します。
この属性が付与されたCookieはクロスサイトなリクエストに対して付与されなくなります。これによってCSRF対策を緩和することができるようになります。
```
Set-Cookie: SID=31d4d96e407aad42; SameSite
```

TODO: そもそも、現状ってクロスサイトなドメインに対してもCookie送るんだっけ? 

### (3)
secure属性を付与されるとhttps属性のときにしかサーバにCookieが付与されない。しかし、http接続の場合でもSet-Cookieはできてしまうはず(TODO:要確認)である。
この仕様ではsecure属性が存在する場合にhttp://からのCookie書き込みをできないように仕様を明示する。

### (4)
Cookie2やSet-Cookie2は明示的に仕様から削除されることになった。

# 詳細
上記の(1)〜(3)については次にテスト用のページも存在しているようです。
- http://rfc6265.biz/tests/

# 参考URL
- https://tools.ietf.org/html/draft-ietf-httpbis-rfc6265bis-02
- Cookieの仕様改定版、RFC6265bisの議論
  - https://asnokaze.hatenablog.com/entry/2017/04/26/080916
- qiita
  - https://qiita.com/flano_yuki/items/b87b2c28db0b056665ef
