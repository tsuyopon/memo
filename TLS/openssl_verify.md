### ルート証明書であることを検証する
```
$ openssl verify <ルート証明書>
```

### ルート証明書で直接署名された証明書を検証する
```
$ openssl verify -CAfile <親証明書>  <子証明書>
```

### 中間CA証明書で署名された証明書(深さ2以上)を検証する
とりあえず簡単にできる方法としては、ルートCA証明書と必要な中間CA証明書をすべて含む一つの親証明書を作成して検証する方法

```
$ cat StartSSL_CA_Root.pem StartSSL_CA_Class1.pem > StartSSL_CA.pem  
$ openssl verify -CAfile StartSSL_CA.pem cert.pem 
 
 cert.pem: OK  
```
