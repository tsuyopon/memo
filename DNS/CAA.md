# DNS Certification Authority Authorization (CAA)
CAAは意図しない認証局からの証明書の誤発行を防ごうといった趣旨です。RFC6844で規定されています。
簡単に言うと所有しているドメイン・サブドメインが指定した認証局以外で勝手に別の認証局から発行されることを防ぐための仕組みです。

CA/ブラウザフォーラムがCA（認証局）に、2017年9月8日からのCAAレコードチェックを義務付けました。
ドメイン所有者がDNSのCAA設定にどのドメインで発行してほしいかを指定することができます。
このCAAレコードが設定されていない場合にはどの証明書でも発行できることになります。


# CAAとTLSAレコード(DANE)の違い
CAAとDANE(TLSAレコード)の違いが非常にわかりにいですが、RFC6844に次のような記述があるようです。
```
Like the TLSA record defined in DNS-Based Authentication of Named Entities (DANE) [RFC6698], CAA records are used as a part of a mechanism for checking PKIX certificate data. The distinction between the two specifications is that CAA records specify an authorization control to be performed by a certificate issuer before	issue of a certificate and TLSA records specify a verification control to be performed by a relying party after the certificate is issued.

(訳)
RFC6698のDANEで定義されているTLSAレコードと同様に、CAAレコードも証明書データの検証メカニズムの一部として使用されます。両者の違いは、CAAレコードは証明書発行前に証明書発行者によって行われる審査コントロールとして定義されているのに対し、TLSAレコードは証明書発行後に信頼者によって行われる検証コントロールとして定義されていることです。
```

つまり次の違いが大きな違いとなっているようです。
- CAAレコードは証明書発行者によって行われる検証
- TLSAレコードはWebブラウザ(信頼者)によって行われる検証

また、ウェブブラウザなどではCAAレコードについては証明書検証の一部で使用してはならないとRFCで規定されています。

DANEの場合にはウェブブラウザへの実装が必要になりますが、CAAを使用するのは認証局だけとなります。
つまり、ウェブブラウザ側には実装は不要なのでクライアント側のアプリケーションには影響を及ぼさないといった利点があります。


# 仕様詳細

### CAA書式
以下はサンプルです。1つのFQDNに対して複数のCAAレコードを指定することが可能です。
MITMでCAAが書き換えられると困るので、DNSSECに対応していることが事実上前提となっているようです。
```
example1.jp.    IN  CAA 0 issue "letsencrypt.org"
example1.jp.    IN  CAA 0 issuewild ";"
example1.jp.    IN  CAA 0 iodef "mailto:xxxxxx@example1.jp"
```

上記サンプルでにある３つのパターンの意味は次の通りです。
- issue:     発行を許可するCA認証局のドメインを指定します。
- issuewild: ワイルドカード証明書の発行を拒否する場合には「;」を設定します。
- iodef:     認証局は発行が許可できなかった無効リクエストに関する情報をここで設定したアドレスに通知します。 URLを指定することもできるようです。

また、CAAの後に存在する0はflagを表します。

- 最初のビットが1（フラグ値＝128～255）の場合は、クリティカルで無視してはならないとして扱います。
- 7番目のビットが1(フラグ値=1)の場合は、クリティカルではありません。

- See: https://tools.ietf.org/html/rfc6844#section-5.1

### CAAレコードが利用される流れ
- 1. DNSドメイン名所有者は、CAAレコードにホスト名と証明書の発行を許可する認証局を登録します。
  - CAAレコードが登録されていない場合には
- 2. ドメイン名所有者はサーバ証明書の発行をCA事業者に依頼します。
- 3. CA事業者ではCAAレコードの記載内容を確認します。SubjectAltNameのDNS NameのCAAレコードを確認して、RFC6844で設定されている処理手順に従ってチェックします。
  - https://tools.ietf.org/html/rfc6844#section-4
  - (要確認) このCA事業者はおそらく上位のCA事業者がCAAを確認している認識だけどあってる?
- 4. CA事業者はチェックが問題なければ、サーバ証明書を発行します。

# 参考URL
- DNS Certification Authority Authorization (CAA) Resource Record
  - https://tools.ietf.org/html/rfc6844
- CAA利用に関する具体的な図については以下のサイトを確認するとよさそうです。
  - https://http2.try-and-test.net/dns_caa.html
- CAAが適切にチェックされているかを確認できる
  - https://caatest.co.uk/
