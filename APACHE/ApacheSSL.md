# 概要
ApacheのSSL/TLS周りについて

# 詳細

### Apacheサーバで、RSAとECCで署名した証明書を出し分けをする
confファイルにRSAとECCで署名されたサーバ証明書と鍵をそれぞれ記述するだけで出し分けすることが可能になるようだ。
```
SSLCertificateFile    ./rsa.crt
SSLCertificateKeyFile ./rsa.key
SSLCertificateFile    ./ecc.crt
SSLCertificateKeyFile ./ecc.key
```

- SeeAlso
  - http://asnokaze.hatenablog.com/entry/20141013/1413194597
