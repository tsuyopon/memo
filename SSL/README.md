# 概要
SSLに関してのディレクトリ

特に混乱しやすいSSLの概念などについてはこのREADME.mdで説明する。

### 拡張子について
- der
  - 中間証明書（X.509証明書）です。DER(Distinguished Encoding Rules)で符号化された証明書。 中身は証明書のみ。バイナリ形式。
- pem
  - 中間証明書（X.509証明書）です。PEM(Privacy Enhanced Mail)。Base64 で符号化された証明書。秘密鍵や証明書、証明書要求の入れ物
- p12
  - 中間証明書（X.509証明書）です。Appを公開するために作成する公開用証明書です。
- csr(証明書署名要求)
  - CAに署名してもらうための形式csr。CAにはこのCSRを渡す事によってサーバ証明書を取得できる
- cer
  - サーバ証明書です。CERで符号化された証明書。 中身は証明書のみ。バイナリ形式。
- crt
  - サーバ証明書を表す。cerとcrtのファイルの中身は同一です。crtからpemに変換できる
- cert
  - サーバ証明書を表す
- ca
  - サーバ証明書を表す
- key
  - 秘密鍵です。keyがエンコーディングされたものがderまたはpemとなります。
- jks
  - JavaKeyStoreでJavaで利用される形式truststoreとkeystoreの２種類に分かれる。
    - truststore.jks: 信頼するCAのルート証明書や中間証明書を保存するファイルです。
    - keystore.jks: サーバ証明書が含まれます。サーバ証明書をインストールする前にその上位のルート証明書・中間証明書も共にインストールします。これによって証明書チェーンの連鎖を実現できます。


上記ではメジャーな拡張子だけ載せましたが、 サーバ証明書として扱う中間証明書(X509証明書)は
- https://en.wikipedia.org/wiki/X.509
  - pem, cer, crt, der, p7b, p7c, p12, pfxなどの拡張子が存在するようです。

ファイルの中を見るとなんのファイルを表しているかを確認できます。
- 秘密鍵(key, pem)
  - 「-----BEGIN RSA PRIVATE KEY-----」で始まり、「----END RSA PRIVATE KEY-----」で終わります
  - 場合によっては「RSA」が無いものもあるようです。
- CSRファイル(csr)
  - 「-----BEGIN CERTIFICATE REQUEST-----」で始まり、「-----END CERTIFICATE REQUEST-----」で終わります
  - もしくは、「-----BEGIN NEW CERTIFICATE REQUEST-----」で始まり、「-----END NEW CERTIFICATE REQUEST-----」で終わります
- 公開鍵
  - 「-----BEGIN CERTIFICATE-----」で始まり、「-----END CERTIFICATE-----」で終わります
- ルート証明書
  - 「-----BEGIN CERTIFICATE-----」で始まり、「-----END CERTIFICATE-----」で終わります。つまり、公開鍵と同じです。


次の記事にも目を通しておくとよいかもしれない
- http://qiita.com/kunichiko/items/12cbccaadcbf41c72735

### X509とはなんだろうか?
電子証明書のデータフォーマットはX.509という国際標準規格に準拠しています。

### なぜこんなにもSSL設定は混乱するのか?
- 拡張子がありすぎる。同じファイルなのに拡張子が違うといった場合もある。
- 仕様上はここまででOKみたいなことがあるので、パターンパターンで異なる。
  - たとえば、truststoreの構造などはパターンパターンで異なる
- CAスクリプトをopensslで書いたりしている。ネット上では色々異なるパターンがある
- ディストリビューションによってCAを作成する際に存在するパスが異なる。
- 古いコマンドかどうかでkeygen, keygenpairの違いや、importとimportcertの違いなどがある




