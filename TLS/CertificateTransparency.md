# Certificate Transparency(RFC6962)
次のような記事を読みCertificate Transparency(CT)について調べてみることにする。
```
2016年6月1日以降にSymantecが発行する証明書に関して、Certificate Transparencyのポリシーに準拠したものだけを信頼する仕組みを、Chromeのバージョン53に実装した。 
だが、同ブラウザーには、CTの情報を信頼する期間を10週間に限定する仕組みが別途実装されていた。古くなった情報への信頼を防ぐために行われた。
```
CTは日本語で「透かし入り証明書」「証明書の透明性」などと呼ばれています。    
Google Chromeでは今後EVSSL証明書は緑のインジケータを表示するためにはCT対応が必要としています。

SSL/TLSの信頼性を高めるための新たな技術で、Google社により提唱されました。RFC6962としてRFC化されています。
証明書の誤発行を防ぐための新しい技術として注目されています。

CTは認証局が発行する証明書を都度、すべての証明書の発行の証跡を第三者の監査ログに残すための仕組みです。防ぐわけではなく、いち早く発見するための仕組みです。

# なぜこのような仕組みが生まれたか?
SymantecがBaseline Requirementに準拠しない事案が２件発生させてしまったことによって、Googleを怒らせてしまったことが原因です。

歴史から見ていくとCT必須化の流れがわかります。
- 2013/06
  - 認証局がハッカーによって不正アクセスを受けて偽の証明書を発行したり、認証局が誤って不適切な証明書が発行される自体を受けてRFC6962としてCertificate Transparencyが策定されました。
    - https://tools.ietf.org/html/rfc6962
- 2015/09/14
  - google.com, www.google.comのEV SSLの証明書をGoogleの許可なく不正に発行していたことがCertificate Transparencyによりわかった。発行していたのはSymantec傘下のブランドであるThawteであった。
    - https://boingboing.net/2015/09/19/symantec-caught-issuing-rogue.html
- 2015/12/11
  - GoogleはSymantecのルート証明書を無効にすると発表します。
    - https://security.googleblog.com/2015/12/proactive-measures-in-digital.html
- 2016/10/24
  - Chromeチームは新たに公開されたすべての信頼できる証明書に対してCTを要求したいと発表しました。
  - この発表は以下のサイトページとCAブラウザフォーラムで行われました。
    - https://groups.google.com/a/chromium.org/forum/#!msg/ct-policy/78N3SMcqUGw/ykIwHXuqAQAJ
- 2017/01/19
  - Symantecが自身が所有していないexample.comのドメインに勝手に証明書を発行しているのがCTのログから見つかった。
    - https://groups.google.com/d/msg/mozilla.dev.security.policy/fyJ3EK2YOP8/yvjS5leYCAAJ
- 2017/09/11
  - GoogleからSymantecから発行された証明書を無効にする旨とそのリリーススケジュールが発表された。
    - https://security.googleblog.com/2017/09/chromes-plan-to-distrust-symantec.html
- 2017/10/31
  - DigiCertがSymantecのウェブサイトのセキュリティ事業、関連するPKIソリューションの買収を完了した。
    - https://www.websecurity.symantec.com/ja/jp/digicert-and-symantec-faq
- 2018/04/30
  - この日以降に発行されたサーバ証明書はCTに対応していないと警告が表示されるようになる。
    - https://groups.google.com/a/chromium.org/forum/#!topic/ct-policy/wHILiYf31DE
- 2018/10/23
  - 提示されたリリーススケジュールどおりにChrome70からSymantecから発行された証明書を無効にした。

削除されてしまったウェブページもあるので、以下のサイトにまとまっています。
- https://notchained.hatenablog.com/entry/2017/03/27/090554

# CTの流れ
以下を参考にしたところ
- https://www.cybertrust.ne.jp/sureserver/productinfo/ct.html

次の３つの方法があるようです。
- X.509v3 Extension
- TLS Extension
- OCSP Stapling

2015年現在、SCTは証明書に埋め込むパターン(X.509v3 Extension)でしか使われていません。これには次の理由があるようです。
- 証明書に埋め込むだけならばフィールドが1つ増えるだけなのでアプリも対応しやすい
- X.509v3 Extension以外ではWebサーバにも拡張が必要となったりする

TLS Extensionについては実験的なコード(Apache2.5のmod_ssl_ct, nginxのnginx-ctモジュール)など実験的に提供され始めているとのことです、OSCP Staplingについては全く実装すら存在しないようです。

以下で登場するSCTというのは監査ログサーバが特定の時間内に発行されたことを保証するタイムスタンプ情報です。

### X.509v3 Extension
- 0. サービス利用者がCAにCSR送付
- 1. 認証局(CA)が第三者の監査ログサーバにプレ証明書を登録する
- 2. 監査ログサーバがプレ証明書にSCT(Signed Certificate Timestamp)を付与して返却する
- 3. CAはサービス提供者にサーバ証明書(プレ証明書+SCT付きから発行)を提供します。
- 4. サービス提供者がWebサーバにサーバ証明書SCT付きを配置します。
- 5. サービス利用者がサーバ証明書SCT付きを取得します。
- 6. サービス利用者が監査ログサーバのサーバ証明書SCT付きを照合します。

### TLS Extension
- 1. CAはサービス提供者(Webサーバ)にサーバ証明書を送信します。
- 2. サービス提供者(Webサーバ)にサービス利用者からの通信があると、SSL接続時にTLS拡張を利用してWebサーバから監査ログサーバにサーバ証明書を送信します。
- 3. 監査ログサーバはSCTをWebサーバに送信します。

### OCSP Stapling
- 1. CAがサービス提供者にサーバ証明書を発行し、同時に第三者の監査ログサーバにも同様にサーバ証明書を送信します。
- 2. 監査ログサーバはサーバ証明書を受け取ると、CAにSCTを送信します。
- 3. サービス提供者(Webサーバ)はSSL接続時にCAにOCSPリクエストをします。
- 4. CAはSCT付きのOCSPレスポンスをサービス提供者(Webサーバ)に返します。
- 5. サービス利用者からの通信にはサーバ証明書とOCSPレスポンスで受け取ったSCTを利用して通信します。

# SCT確認方法
OpenSSLでも、現在最新の1.0.2aでx509サブコマンドの-textオプションを使えば、次のように証明書内のSCTを直接見ることができます。
```
$ openssl s_client -connect www.example.com:443 | openssl x509 -text -noout
```


# 対応状況確認
Chromeブラウザから確認すると「公開監査記録がありません」と表示されるような場合にはCT未対応です。「公開監査が可能です」と表示される場合にはCT対応しています。  
Chromeでは、2015年2月1日以降、Chromeは、ホワイトリストに登録されておらず、かつCTに適応していないEV SSL証明書については、EV SSL証明書固有の表示をしない（グリーンバーや組織名が表示されない）としています。

# CTのログを見る
CT とは、どのようなドメインや組織に対して認証事業者が証明書を発行したのか、誰でも確認できる仕組みです。
CT を使えば、ドメイン所有者や企業は、自分が申し込んだ覚えのない、あるいは許可したことのない証明書がないか、確認することができます。
- https://www.google.com/transparencyreport/https/ct/?hl=ja
- https://crt.sh/?q=yahoo.co.jp

# CTのデメリット
- 認証局は、SCT取得時にpre-certificateというものを作らなければならない。
- サーバ管理者は、関係者のみにしか漏らしたくないFQDNが見えてしまう
- 一般ユーザは、ログサーバ管理者から「いつ、どのIPから、どのFQDNにアクセスがあったのか」が見れてしまう。

# 参考URL
- RFC
  - https://tools.ietf.org/html/rfc6962
- Certificate Transparency
  - http://www.certificate-transparency.org/
- 画像
  - https://www.cybertrust.ne.jp/sureserver/productinfo/ct.html
- IETF Public Notary Transparency (trans) 
  - https://datatracker.ietf.org/wg/trans/documents/

