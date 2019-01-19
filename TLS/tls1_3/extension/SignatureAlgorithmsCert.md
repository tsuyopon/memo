# signature_algorithms_cert拡張について
TLS1.2から必須として規定されているsignature_algorithm拡張ですが、この拡張は証明書検証やハンドシェイクの署名などで使われていて仕様の理解を複雑にしていました。
そこでTLS1.3ではRFC8446中でsignature_algorithms_cert拡張が新設されました。
- https://tools.ietf.org/html/rfc8446#section-4.2.3

この拡張はsignature_algorithm拡張と大きく関係があります。
そのため、signature_algorithms拡張の仕様と合わせてsignature_algorithms_cert拡張の仕様について説明しています。

# 詳細

### 解決したい課題
TLS1.2ではsignature_algorithms拡張が必須で、この拡張は付与しなければならないとして規定されています。
signature_algorithms拡張が指定されることによって次の(1)、(2)の２つの処理を担当していましたが、これがTLS仕様理解を複雑にする元凶でもありました。
- (1) Certificateの選択・検証
- (2) ServerKeyExchangeで送付されてくる公開鍵の署名情報  (TLS1.3ではServerKeyExchangeは無くなりました)

### 解決方法
TLS1.3からはsignature_algorithm拡張の他に、signature_algorithms_cert拡張を新設することで２つの拡張が用意される。
この拡張が指定されてきた場合には「(1) Certificateの選択・検証」をするための情報として利用される。
なお、TLS1.2で指定されていたsignature_algorithm拡張はTLS1.3では「(2) ServerKeyExchangeで送付されてくる公開鍵の署名情報」の部分の処理をするための利用されるので少し役割が変わってくる。

なお、signature_algorithms_cert拡張が指定されてこない場合には、signature_algorithms拡張によって指定された値で(1)、(2)を代用します。

### 仕様
- signature_algorithms_cert拡張は証明書の選択や検証に影響する。signature_algorithm拡張はハンドシェイク
- signature_algorithms_cert拡張が存在しない場合には、signature_algorithms拡張によって代用される。
- もしサーバが証明書経由で認証し、クライアントがsignature_algorithms拡張を送付してこないのであれば、サーバはmissing_extensionアラートを送りハンドシェイクを中断する(MUST) 
- TLS1.2実装はsignature_algorithms_cert拡張を処理すべき(SHOULD)

### 利用方法
- 1. ClientHelloにsignature_algorithms拡張の他にsignature_algorithms_cert拡張も送付してくる。
- 2. サーバはsignature_algorithms_cert拡張を元に証明書を決定する。つまり、signature_algorithms_cert拡張の値に対応した証明書をサーバ側が選択しCertificateとして送付します。
- 3. サーバはCertificateVerifyメッセージで署名を送付します。
- 4. クライアントはCertificateを受け取ったらsignature_algorithms_cert拡張で送付した値を元にして検証を行います。
  - 通常はRoot証明書はクライアントにプリインストールされていて、中間証明書とサーバ証明書はサーバ側に配置されているので、これら３つの証明書に関して必要なsignature_algorithmはクライアントとサーバで知っているはずである。
- 5. クライアントはCertificateVerifyメッセージを受け取ったら、その中に含まれている証明書をsignature_algorithms拡張で指定された値で検証します。
  - TODO: もう少し確認

# 参考URL
- https://tools.ietf.org/html/rfc8446#section-4.2.3
- あどけない話: TLS 1.3 開発日記 その24 ID23
  - https://kazu-yamamoto.hatenablog.jp/entry/20180116/1516075029

# 要確認
TODO: ServerHelloから応答されるcipher_suiteはsignature_algoritmsの値によって影響しないか?
TODO: あどけない話のPSSとかの意味は何?
TODO: どこで署名が送られてくる?
TODO: 全部読んでまとめる
 https://tools.ietf.org/html/rfc8446#section-4.2.3
TODO: CertificateVerifyはRFC5246と8446で役割違うよね? 5246だとクライアント認証だけっぽい。要確認
