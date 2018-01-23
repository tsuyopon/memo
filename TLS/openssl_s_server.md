# 概要
opensslのs_serverサブオプションについて

# 詳細
### 即座に443ポートを起動する
次のコマンドを実行すれば即座に443のTLS待受サーバを動かすことができる。簡単なテストなどに便利です。
```
$ openssl genrsa -des3 -out server.key 2048                                        // ここで適当に「test」などとしてパスワードを設定
$ openssl req -new -key server.key -out server.csr
$ openssl x509 -req -days 365 -in server.csr -signkey server.key -out server.crt
$ sudo openssl s_server -accept 443 -cert server.crt -key server.key -www -debug   // wwwだとTLSハンドシェイクをbodyに返す
```

### 秘密鍵と公開鍵のペアが一致することを確認する
opensslでテスト起動できないような場合、秘密鍵と公開鍵のペアが一致していない場合には次のようなエラーがでます。
```
$ sudo openssl s_server -accept 443 -cert mid_server.crt -key mid_server.key -www -debug
Enter pass phrase for mid_server.key:
Using default temp DH parameters
Using default temp ECDH parameters
error setting private key
140421887227536:error:0B080074:x509 certificate routines:X509_check_private_key:key values mismatch:x509_cmp.c:330:
```

crtと対のkeyなのかは次のハッシュ値が一致しているかどうかで確認することができます。
次のように一致していれば問題無いことが確認できます。
```
$ openssl rsa -in mid_server.key -modulus -noout | openssl md5
Enter pass phrase for server.key:
(stdin)= c83dfb14665389f18d3c2b019bc8575b
$ openssl x509 -in mid_server.crt -modulus -noout | openssl md5
(stdin)= c83dfb14665389f18d3c2b019bc8575b
```


