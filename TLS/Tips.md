# 概要
TLS周りのtipsなど

### chromeでアドレスバーを押したらすぐに証明書がみれるようにする。

Chrome56からは、UI/UXポリシーによって、HTTPSで接続した際に使用しているSSLサーバ証明書の表示が鍵アイコンから簡単にできなくなってしまいました。

アドレスバーから次の画面にアクセスして、
- chrome://flags/#show-cert-link

次の箇所がデフォルトで無効なので、有効に変更して再起動します。
```
Show certificate link Mac, Windows, Linux, Chrome OS
```

詳細は以下の記事を参考にしてください。

- 参考
  - http://blog.livedoor.jp/k_urushima/


### 4階層構造(クロスルート方式)とは
クロスルート方式とは従来の証明書階層で使用するルート証明書に加えて、クロスルート用の中間証明書を設定することによって別のルートの証明書にも接続可能とする仕組みです。
つまり、1枚のサーバ証明書で別のルート証明書も許可する仕組みとなっています。 クロスルート方式は昔の端末などはサポートしないものも存在するようだ。

- 参考
  - https://knowledge.symantec.com/jp/support/ssl-certificates-support/index?page=content&actp=CROSSLINK&id=SO22884

### 中間証明書はなぜ必要となるのか? 必ず必要なのか?
SSL接続の際に、ブラウザは下層から順番に証明書を辿り、最上位のルート証明書までを確認してサーバIDを検証しています。  
中間CA証明書がWebサーバ側に設定されていないと正しい検証ができずに、無効な証明書と認識されます。つまり、必ず設定が必要となるようです。

- 参考
  - https://knowledge.symantec.com/jp/support/ssl-certificates-support/index?vproductcat=V_C_S&vdomain=VERISIGN.JP&page=content&id=SO22871&locale=ja_JP&redirected=true


### クロスルート方式の場合のサーバ設定方法はどうなっているのか? 2枚ともサーバに配置する必要があるのか?
次のようなクロスルート方式の証明書の場合
```
ルート証明書（ブラウザに標準搭載）
┗ クロスルート設定用証明書（Webサーバに設定）
┗ 中間CA証明書（Webサーバに設定）
┗ サーバ証明書（Webサーバに設定）
```

Apacheでは次のような設定を行うようだ。この場合、クロスルート証明書と中間CA証明書は同一ファイルで入れているようだ。
```
Apacheでの設定例
SSLEngine on
SSLCertificateKeyFile conf/hoge.jp.key # 秘密鍵
SSLCertificateFile conf/hoge.jp.crt    # サーバ証明書
SSLCertificateChainFile conf/inca.pem  # 中間CA証明書（クロスルート証明書も同一ファイルに続けて表記）
```

- 参考
  - https://cloudpack.media/630
