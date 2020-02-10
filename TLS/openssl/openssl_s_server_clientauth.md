# 概要
opensslコマンドを利用したクライアント認証のテスト方法について

# 詳細

まずはサーバ証明書とその秘密鍵を作成します。
genrsaでパスフレーズ設定を求められますが以下ではtestを指定しています。そして、req, x509サブオプションではパスフレーズの入力を求められるのでtestを入力しています。
```
$ openssl genrsa -des3 -out server.key -passout pass:test 2048
$ openssl req -new -days 365 -key server.key -out server.csr -subj "/C=JP/ST=Saitama/L=city/O=server/OU=organizationunit/CN=server.co.jp" -passin pass:test 
$ openssl x509 -req -days 365 -in server.csr -signkey server.key -out server.crt -passin pass:test
```

続いて、クライアント証明書を発行します(本来は上位CAも作って、その秘密鍵で署名するのが望ましいですが、自己署名とします)
```
$ openssl genrsa -out CLIENT_CERT.key -passout pass:test 2048
$ openssl req -sha256 -new -days 365 -key CLIENT_CERT.key -out CLIENT_CERT.csr -subj "/C=JP/ST=Saitama/L=city/O=client/OU=organizationunit/CN=client.co.jp" -passin pass:test 
$ openssl x509 -sha256 -req -days 3650 -in CLIENT_CERT.csr -signkey CLIENT_CERT.key -out CLIENT_CERT-ca.crt -passin pass:test
```

クライアント認証に対応させるサーバとしては次のように起動します。
ポイントとしてはverifyを指定します。これがないとCertificateRequestがクライアントに送付されません。そして、CAfileでは、先で作成したクライアント証明書ファイルを指定します。　
```
$ sudo openssl s_server -accept 443 -cert server.crt -key server.key -CAfile CLIENT_CERT-ca.crt -verify 10 -msg -state
```

クライアント側は次のようにします。
ポイントはcertにはクライアント証明書を指定し、keyにはクライアント証明書に対応する秘密鍵を指定します。
CAfileには本来クライアント認証を許可する上位トラストアンカーが設定されますが、ここではクライアント認証のテストようでcertとCAfileはおなじなので自己署名扱いとなります。
```
$ openssl s_client -connect localhost:443 -cert CLIENT_CERT-ca.crt -key CLIENT_CERT.key -CAfile CLIENT_CERT-ca.crt -msg -state
```

s_serverでもs_clientでもmsgやstateオプションを付与することでどのようなメッセージが来ているかを確認することができます。

# 参考URL
- http://blog.808inorganic.com/2017/01/using-openssl-sserver-and-openssl.html
