# 概要
CRIME攻撃(Compression Ratio Info-leak Made Easy)についてまとめています。
現在、TLSでは圧縮機能を利用しないことが推奨されているが、その原因の一躍を担っているのがこの攻撃です。
CVE-2012-4929に該当します。


# 詳細
### どのような攻撃か
圧縮が利用された暗号化セッションにおいて、第三者によって暗号を解読せずにCookie情報を推測することが容易になります。

### 攻撃手法
圧縮機能を利用すると、重複したデータが圧縮されることになる。
文字列を埋め込んで送信される暗号化データ長が小さくなった場合には、以前送付した文字列であることを推測することができます。


具体例で見ていきます。
たとえば、次のようなリクエストをブラウザが送付する場合を仮定します。
```
POST / HTTP/1.1
Cookie: secret=129...
```

上記と同様のエントリポイント・メソッドに対して次のような(1)〜(3)のリクエストが送付された場合、  
すでに「POST / HTTP/1.1」で数字の"1"が送付されているので、(2)の場合だけ暗号された後の長さ(Encrypted-Length)が短いことが確認できます。
攻撃者はこのサイズが短くなったことを利用して攻撃を仕掛けてきます。
```
Cookie: secret=0        Encrypted-Length:920  /* (1) */
Cookie: secret=1        Encrypted-Length:919  /* (2) */
Cookie: secret=9        Encrypted-Length:920  /* (3) */
```

このようにすでに送付した文字は圧縮されることを利用することによって、Cookieに設定されている内容を攻撃者が推測しやすくなります。

たとえば、上記でsecretがセッションIDを意図したものであるのであれば、
ウェブサイトでのユーザ認証に使われているCookieの内容を回復されることで、セッションハイジャックが可能となります。

# 対処方法
- SPDYやTLSにおいてヘッダ圧縮機能を利用しないこと

# 参考URL
- wikipedia
  - https://en.wikipedia.org/wiki/CRIME
- CRIMEについて記載されているスライド(詳しい)
  - https://docs.google.com/presentation/d/11eBmGiHbYcHR9gL5nDyZChu_-lCa2GizeuOfaLU2HOU/edit?pli=1#slide=id.g1d134dff_1_222
- CRYPTREC 暗号技術ガイドライン(p78付近)
  - https://www.cryptrec.go.jp/report/c13_tech_guideline_TLSSSL_web.pdf
- http://niiconsulting.com/checkmate/2013/12/ssltls-attacks-part-2-crime-attack/
