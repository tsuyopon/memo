# 概要
HTTP Public Key Pinning(HPKP)ヘッダは、クライアントに特定の公開鍵をウェブサーバに関連付けさせる機能です。
これによって、偽造された不正な証明書を見分けることができ、中間者攻撃リスクを減少させるための機能です。

RFC7469によって規定されています。

HTTP Public Key Pinningには次の２種類の方法があります。
- Pre-loaded public key pinning
  - あらかじめブラウザのソースコードに公開鍵情報を埋め込む
- HTTP-based public key pinning (HPKP)
  - サーバからHTTPヘッダでブラウザに公開鍵情報を通知する

しかし、現在ではサイト運営者が誤ってサイト訪問者をブロックするような悪影響がある可能性が指摘されていてChrome67ではサポートが廃止されている。
代替としてはHPKPではなくて、Certificate TransparencyやExpect-CT HTTP拡張ヘッダを推奨しているとのこと。
- https://japan.cnet.com/article/35109624/

# 提供手段

例えば、HPKPヘッダは次のようなヘッダ書式となる。
```
Public-Key-Pins: pin-sha256="base64=="; max-age=expireTime [; includeSubDomains][; report-uri="reportURI"]
```

以下はmozillaに記載されている応答ヘッダのサンプルです。
```
Public-Key-Pins: 
  pin-sha256="cUPcTAZWKaASuYWhhneDttWpY3oBAkE3h2+soZS7sWs="; 
  pin-sha256="M8HztCzM3elUxkcjR2S5P4hhyBNf6lHkmjAHKhpGPWE="; 
  max-age=5184000; includeSubDomains; 
  report-uri="https://www.example.org/hpkp-report"
```
- pin-sha256はサーバの公開鍵です。以下の例では２つ指定されているが、本番用と及びバックアップ用途などで指定しているようです。
- max-ageはこのヘッダ情報を2ヶ月(5184000)の間、保存するように伝える
- includeSubDomainsは、xxx.comでこのヘッダを受けた場合、yyy.xxx.com, zzz.xxx.comなどのサブドメインにも提供される旨を示す。
- report-uriは、ピンの検証に失敗した場合に報告されるURLを示す。


report-uriを解析するためのテストサイトとして次のサイトがある
- https://report-uri.com/
- 利用方法に関する参考資料: https://rms-digicert.ne.jp/howto/basis/Scott_Helme_io.html

# HPKPを有効にする
- https://developer.mozilla.org/en-US/docs/Web/HTTP/Public_Key_Pinning

# 参考URL
- RFC7469: Public Key Pinning Extension for HTTP
  - https://tools.ietf.org/html/rfc7469
- mozilla: HTTP Public Key Pinning (HPKP)
  - https://developer.mozilla.org/ja/docs/Web/Security/Public_Key_Pinning
- 「Public Key Pinning Extension for HTTP（HPKP）」で証明書の不正利用を防止する
  - https://rms-digicert.ne.jp/howto/basis/pinning.html
- ぼちぼち日記(不正なSSL証明書を見破るPublic Key Pinningを試すAdd Starboyasanmkt)
  - http://d.hatena.ne.jp/jovi0608/20140902/1409635279
- 自堕落な技術者の日記
  - http://blog.livedoor.jp/k_urushima/archives/1811745.html

