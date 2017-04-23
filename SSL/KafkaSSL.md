# 概要
kafkaのSSLサーバ間認証とSSLクライアント認証する場合の鍵生成手順について

### SSLサーバ認証 
秘密鍵server.keystore.jksを作成する
```
$ sudo keytool -genkeypair -alias localhost -keysize 2048 -keyalg RSA -sigalg SHA256withRSA -keystore server.keystore.jks -storetype JKS -validity 3650 -keypass key1234 -storepass store1234
```

認証局(CA)作成してca-keyやca-certが生成される
```
$ openssl req -new -x509 -keyout ca-key -out ca-cert -days 3650
```

truststoreを作成する。ca-certをインポートしてserver.truststore.jksを新規作成する
```
$ keytool -keystore server.truststore.jks -alias CARoot -import -file ca-cert
```

server.keystore.jksからcert-fileを取り出してca-cert, ca-key, cert-fileなどで署名
```
$ keytool -keystore server.keystore.jks -alias localhost -certreq -file cert-file
$ openssl x509 -req -CA ca-cert -CAkey ca-key -in cert-file -out cert-signed -days 3650 -CAcreateserial
```

server.keystore.jksにインポート
```
$ sudo keytool -keystore server.keystore.jks -alias CARoot -import -file ca-cert
$ sudo keytool -keystore server.keystore.jks -alias localhost -import -file cert-signed
```

内容確認
```
$ keytool -list -keystore server.keystore.jks
$ keytool -list -keystore truststore.keystore.jks
```

設定についてはこの辺が参考になる
- http://kafka.apache.org/documentation.html#security_ssl

### SSLクライアント認証
秘密鍵consumer.keyとサーバ証明書consumer.crt作成
```
$ openssl genrsa -des3 -out consumer.key 2048
$ openssl req -new -key consumer.key -out consumer.csr     // crtを作るためにはcsrを作る
$ openssl x509 -req -days 3650 -in consumer.csr -signkey consumer.key -out consumer.crt
```

整合性確認
```
$ openssl  rsa -in consumer.key -modulus -noout | openssl md5
$ openssl x509 -in consumer.crt -modulus -noout | openssl md5
```

crtからpem変換
```
$ openssl x509 -in consumer.crt -out tmp.der -outform DER
$ openssl x509 -in tmp.der -inform DER -out consumer.pem -outform pem
```

ここで生成したconsumer.key, consumer.pem及び、先程のサーバ認証で生成したクライアント認証用のパスポートとしてca-certをproducer, consumerなどに配置する必要がある。

設定についてはこの辺が参考になる
- https://github.com/edenhill/librdkafka/wiki/Using-SSL-with-librdkafka

# 参考URL
- http://kafka.apache.org/documentation.html#security_ssl
