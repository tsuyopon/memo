# 概要
opensslのs_serverサブオプションについて

# 詳細
### 即座に443ポートを起動する
次のコマンドを実行すれば即座に443のTLS待受サーバを動かすことができる。簡単なテストなどに便利です。
```
$ openssl genrsa -des3 -out server.key 2048                                        // ここで適当に「test」などとしてパスワードを設定
$ openssl req -new -key server.key -out server.csr -subj "/CN=My Test CA"
$ openssl x509 -req -days 365 -in server.csr -signkey server.key -out server.crt
$ sudo openssl s_server -accept 443 -cert server.crt -key server.key -www -debug   // wwwだとTLSハンドシェイクをbodyに返す
```

apacheの起動時などで秘密鍵を取り除いておきたい場合には次のコマンドでパスフレーズを取り除いておくこと
```
$ openssl rsa -in server.key -out noserver.key
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

crtと対のkeyなのかは次のハッシュ値が一致しているかどうかでも確認することができます。
次のように一致していれば問題無いことが確認できます。
```
$ openssl rsa -in mid_server.key -modulus -noout | openssl md5
Enter pass phrase for server.key:
(stdin)= c83dfb14665389f18d3c2b019bc8575b
$ openssl x509 -in mid_server.crt -modulus -noout | openssl md5
(stdin)= c83dfb14665389f18d3c2b019bc8575b
```

### TLSサーバを立てる
次のコマンドでTLSサーバを立てます
```
$ openssl s_server -cert server.crt -key server.key
Using default temp DH parameters
Using default temp ECDH parameters
ACCEPT
```

server.crtやserver.keyは次の3つのコマンドですぐに作成できます。
```
$ openssl genrsa -des3 -out server.key 2048            // ここで適当に「test」などとしてパスワードを設定
$ openssl req -new -key server.key -out server.csr
$ openssl x509 -req -days 365 -in server.csr -signkey server.key -out server.crt
```

上記でデフォルトで4433ポートで起動するので、次のようにして接続確認ができます。
```
$ openssl s_client -connect localhost:4433 -quiet
```

msgオプションを付けると接続時にハンドシェイクの流れも表示してくれます。以下の例では中間証明書(-CAfile)を指定していませんが指定することも可能です。
```
$ openssl s_server -cert server.crt -key server.key -www -msg
Enter pass phrase for server.key:
Using default temp DH parameters
Using default temp ECDH parameters
ACCEPT
<<< TLS 1.2 Handshake [length 0122], ClientHello
    01 00 01 1e 03 03 8a a5 dc 11 ea 9c b7 48 76 3a
    (snip)
>>> TLS 1.2 Handshake [length 0042], ServerHello
    02 00 00 3e 03 03 c3 d8 52 27 17 bb 9f 6a 1d 90
    (snip)
>>> TLS 1.2 Handshake [length 0314], Certificate
    0b 00 03 10 00 03 0d 00 03 0a 30 82 03 06 30 82
    (snip)
>>> TLS 1.2 Handshake [length 014d], ServerKeyExchange
    0c 00 01 49 03 00 17 41 04 bb fe a5 3e 51 73 ad
    (snip)
>>> TLS 1.2 Handshake [length 0004], ServerHelloDone
    0e 00 00 00
<<< TLS 1.2 Handshake [length 0046], ClientKeyExchange
    10 00 00 42 41 04 df 41 1d 97 0f 92 86 73 7f 2e
    (snip)
<<< TLS 1.2 ChangeCipherSpec [length 0001]
    01
<<< TLS 1.2 Handshake [length 0010], Finished
    14 00 00 0c 73 70 b0 25 1a 79 82 78 eb 88 84 20
>>> TLS 1.2 Handshake [length 00aa]???
    04 00 00 a6 00 00 01 2c 00 a0 6a 7b ab d4 0c e8
    (snip)
>>> TLS 1.2 ChangeCipherSpec [length 0001]
    01
>>> TLS 1.2 Handshake [length 0010], Finished
    14 00 00 0c b3 31 cd e5 7e a9 c4 52 5c 71 5c 69
<<< TLS 1.2 Alert [length 0002], warning close_notify
    01 00
ACCEPT
```

debugオプションを付与するとパケット情報もダンプしてくれるようになります。
```
$ openssl s_server -cert server.crt -key server.key -www -debug
Enter pass phrase for server.key:
Using default temp DH parameters
Using default temp ECDH parameters
ACCEPT
read from 0x1c6aa50 [0x1c70140] (11 bytes => 11 (0xB))
0000 - 16 03 01 01 22 01 00 01-1e 03 03                  ...."......
read from 0x1c6aa50 [0x1c7014e] (284 bytes => 284 (0x11C))
0000 - 4a fd 40 ae 50 b2 2e 64-fa d1 9f fb 46 8d e9 f5   J.@.P..d....F...
0010 - 25 f2 59 c9 39 8e 0d 98-59 32 7c 00 cc 9c 2f 7a   %.Y.9...Y2|.../z
```

### お手軽にHTTPSサーバを立てて証明書確認を行う
opensslコマンドにはお手軽にHTTPSサーバを立てる機能が存在します。次のような感じで指定します。
以下の例ではCAfileで中間証明書も指定していますが、省略もできます(ブラウザによってはえらーになりますが)
```
$ openssl s_server -accept 10443 -cert cert.pem -key keynp.pem -CAfile rapidssl.pem -WWW
Using default temp DH parameters
Using default temp ECDH parameters
ACCEPT
```
- accept: HTTPS待受portがデフォルトで4433とややわかりにくいので指定するといいかもしれません。
- cert: サーバ証明書のファイル名
- key: 秘密鍵のファイル名
- CAfile: 中間証明書のファイル名
- WWW: 単順なWEBサーバをエミュレートする。URL のパス部分をカレントディレクトリからの相対パスで解決して、対応するファイルを返す。

リクエストを確認するのも次のコマンドで可能なのですごい便利
```
$ openssl s_client -connect localhost:10433
```

- 参考
  - https://bacchi.me/linux/openssl-tips/

### s_serverのwwwオプションとWWWオプションの違いについて
wwwだと、アクセス時にレスポンスとして証明書の情報などを出力します。
WWWだとコマンドを実行した関連とディレクトリをDocumentRootとして適当なファイルをURLで指定させることができます。
ファイルや動画などを置いていろいろ試したいといった場合にはWWWが良いでしょう。


