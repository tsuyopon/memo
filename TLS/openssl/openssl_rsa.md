### 秘密鍵と公開鍵のペアが一致することを確認する
crtと対のkeyなのかは次のハッシュ値が一致しているかどうかでも確認することができます。
次のように一致していれば問題無いことが確認できます。
```
$ openssl rsa -in mid_server.key -modulus -noout | openssl md5
Enter pass phrase for server.key:
(stdin)= c83dfb14665389f18d3c2b019bc8575b
$ openssl x509 -in mid_server.crt -modulus -noout | openssl md5
(stdin)= c83dfb14665389f18d3c2b019bc8575b
```

### 秘密鍵ファイルを確認する
```
$ openssl rsa -in server.key -noout -text 
Enter pass phrase for server.key:
Private-Key: (2048 bit)
modulus:
    (snip)
    9f:ed:b2:47:9f:80:1a:35:c4:3f:8a:1c:91:ab:69:
publicExponent: 65537 (0x10001)
privateExponent:
    (snip)
    a1:bb:96:07:0c:e8:06:7b:df:cd:d3:82:cd:86:5f:
prime1:
    (snip)
    a5:40:1e:c3:24:61:49:d1:07
prime2:
    (snip)
    d4:04:75:66:7b:06:12:ee:3d
exponent1:
    (snip)
    2d:f2:69:e9:0c:ef:60:1f:fd
exponent2:
    (snip)
    5a:b8:59:fa:81:1e:b5:e1
coefficient:
    (snip)
    a4:c5:d6:b1:b2:3f:f2:c9
```

### 秘密鍵からパスフレーズを取り除く
```
$ openssl rsa -in server.key -out nopass_server.key
```

### opensslコマンドでRSA鍵交換、暗号化、復号までを行う
以下のファイルを参照のこと
- Cipher/RSA.md
