# 概要
opensslコマンドのcipher周りについて

# 詳細

### cypherリストを表示する。
```
$ openssl list-cipher-commands
aes-128-cbc
aes-128-ecb
aes-192-cbc
aes-192-ecb
aes-256-cbc
aes-256-ecb
(...)
```

### opensslコマンドでハッシュ値を算出する
利用できるアルゴリズムは次の通りです。
```
$ openssl list-message-digest-commands
md2
md4
md5
rmd160
sha
sha1
```

md5は次のように算出できる。
```
$ openssl md5 server.key 
MD5(server.key)= dd2b93775f56ff19fd05891c1b1012d4

$ openssl dgst -md5 server.key
MD5(server.key)= dd2b93775f56ff19fd05891c1b1012d4
```

sha1は次のように算出できる。
```
$ openssl sha1 server.key 
SHA1(server.key)= c5794c3d0c3b0edc8d5c07800f939dc86e939eac

$ openssl dgst -sha1 server.key
SHA1(server.key)= c5794c3d0c3b0edc8d5c07800f939dc86e939eac
```

dgstのヘルプページを見ても様々なオプションが表示されます。
```
$  openssl dgst -h
unknown option '-h'
options are
-c              to output the digest with separating colons
-r              to output the digest in coreutils format
-d              to output debug info
-hex            output as hex dump
-binary         output in binary form
-hmac arg       set the HMAC key to arg
-non-fips-allow allow use of non FIPS digest
-sign   file    sign digest using private key in file
-verify file    verify a signature using public key in file
-prverify file  verify a signature using private key in file
-keyform arg    key file format (PEM or ENGINE)
-out filename   output to filename rather than stdout
-signature file signature to verify
-sigopt nm:v    signature parameter
-hmac key       create hashed MAC with key
-mac algorithm  create MAC (not neccessarily HMAC)
-macopt nm:v    MAC algorithm parameters or key
-engine e       use engine e, possibly a hardware device.
-md4            to use the md4 message digest algorithm
-md5            to use the md5 message digest algorithm
-ripemd160      to use the ripemd160 message digest algorithm
-sha            to use the sha message digest algorithm
-sha1           to use the sha1 message digest algorithm
-sha224         to use the sha224 message digest algorithm
-sha256         to use the sha256 message digest algorithm
-sha384         to use the sha384 message digest algorithm
-sha512         to use the sha512 message digest algorithm
-whirlpool      to use the whirlpool message digest algorithm
```

### opensslで利用可能なアルゴリズムを表示する
- 使用可能な暗号化方法の一覧
```
$ openssl ciphers -v | head -4 
DHE-RSA-AES256-SHA      SSLv3 Kx=DH       Au=RSA  Enc=AES(256)  Mac=SHA1
DHE-DSS-AES256-SHA      SSLv3 Kx=DH       Au=DSS  Enc=AES(256)  Mac=SHA1
AES256-SHA              SSLv3 Kx=RSA      Au=RSA  Enc=AES(256)  Mac=SHA1
EDH-RSA-DES-CBC3-SHA    SSLv3 Kx=DH       Au=RSA  Enc=3DES(168) Mac=SHA1
```

- 設定値などは次のように記述されることが多い
```
$ openssl ciphers -v 'aRSA+kRSA+AES:aRSA+kRSA+RC4:!EXP:!LOW:!SSLv2:!MD5' | head -3
AES256-SHA              SSLv3 Kx=RSA      Au=RSA  Enc=AES(256)  Mac=SHA1
AES128-SHA              SSLv3 Kx=RSA      Au=RSA  Enc=AES(128)  Mac=SHA1
RC4-SHA                 SSLv3 Kx=RSA      Au=RSA  Enc=RC4(128)  Mac=SHA1
```

- 強度の強い順番で表示する
```
$ openssl ciphers ALL:@STRENGTH -v | head -4
ADH-AES256-SHA          SSLv3 Kx=DH       Au=None Enc=AES(256)  Mac=SHA1
DHE-RSA-AES256-SHA      SSLv3 Kx=DH       Au=RSA  Enc=AES(256)  Mac=SHA1
DHE-DSS-AES256-SHA      SSLv3 Kx=DH       Au=DSS  Enc=AES(256)  Mac=SHA1
AES256-SHA              SSLv3 Kx=RSA      Au=RSA  Enc=AES(256)  Mac=SHA1
```

- TLSv1の暗号化方法一覧
```
$ openssl ciphers -v -tls1 | head -4
ECDHE-RSA-AES256-GCM-SHA384 TLSv1.2 Kx=ECDH     Au=RSA  Enc=AESGCM(256) Mac=AEAD
ECDHE-ECDSA-AES256-GCM-SHA384 TLSv1.2 Kx=ECDH     Au=ECDSA Enc=AESGCM(256) Mac=AEAD
ECDHE-RSA-AES256-SHA384 TLSv1.2 Kx=ECDH     Au=RSA  Enc=AES(256)  Mac=SHA384
ECDHE-ECDSA-AES256-SHA384 TLSv1.2 Kx=ECDH     Au=ECDSA Enc=AES(256)  Mac=SHA384
```

- 高度(128ビット以上)暗号化方法の一覧
```
$ openssl ciphers -v 'HIGH' | head -4
ECDHE-RSA-AES256-GCM-SHA384 TLSv1.2 Kx=ECDH     Au=RSA  Enc=AESGCM(256) Mac=AEAD
ECDHE-ECDSA-AES256-GCM-SHA384 TLSv1.2 Kx=ECDH     Au=ECDSA Enc=AESGCM(256) Mac=AEAD
ECDHE-RSA-AES256-SHA384 TLSv1.2 Kx=ECDH     Au=RSA  Enc=AES(256)  Mac=SHA384
ECDHE-ECDSA-AES256-SHA384 TLSv1.2 Kx=ECDH     Au=ECDSA Enc=AES(256)  Mac=SHA384
```

- 高度(128ビット以上)かつAES方式の暗号化方法の一覧
- openssl ciphers -v 'AES+HIGH' | head -4
```
$ openssl ciphers -v 'AES+HIGH' | head -4
ECDHE-RSA-AES256-GCM-SHA384 TLSv1.2 Kx=ECDH     Au=RSA  Enc=AESGCM(256) Mac=AEAD
ECDHE-ECDSA-AES256-GCM-SHA384 TLSv1.2 Kx=ECDH     Au=ECDSA Enc=AESGCM(256) Mac=AEAD
ECDHE-RSA-AES256-SHA384 TLSv1.2 Kx=ECDH     Au=RSA  Enc=AES(256)  Mac=SHA384
ECDHE-ECDSA-AES256-SHA384 TLSv1.2 Kx=ECDH     Au=ECDSA Enc=AES(256)  Mac=SHA384
```

上記のオプションで表示されるHIGHなどの定義は次の通り
```
eNULL   通信の暗号をしないもの (そういうのもあるのか!)
aNULL   認証をしないもの (そういうのもあるのか!)
ALL     eNULL を使ってない全て
DEFAULT ALL:!aNULL:!eNULL、つまり ALL から aNULL と eNULL を除いたもの。ALL の時点で eNULL は除かれてる気がする
MD5     MD5 を使ってるもの
3DES    Triple DES すな
TLSv1,SSLv3,SSLv2 そのままなんだけど、どうやらこのバージョンでは SSLv2 は一切無くなってて TLSv1 = SSLv3 みたい
EXP     米国の輸出規制にひっかかってなかったやつ、で 40bit と 56bit のが入ってるはずなんだけど 40bit しか出てこない
LOW     56bit とか 60bit のらしい
HIGH    暗号に 128bit 以上の鍵を使うものほぼ全て
```

### base64エンコードとデコード
エンコードとデコード
```
$ echo -n abcdefg | openssl enc -e -base64
YWJjZGVmZw==
$ echo YWJjZGVmZw== | openssl enc -d -base64
abcdefg
```

### テキストファイルをAES128bitで暗号化しcryptedにする。その後復号化する
適当なファイルをエンコードしてみます。
```
$ echo hoge > hoge.txt
$ openssl enc -e -aes128 -in hoge.txt -out crypted
enter aes-128-cbc encryption password:                 // 適当なパスワードを入力(複合時に必要となる)
Verifying - enter aes-128-cbc encryption password:
$ cat crypted; echo
Salted__xv?????5???S["t?t?^??|?
```

では、このファイルを戻してみましょう
```
$  openssl enc -d -aes128 -in crypted -out plain.txt
enter aes-128-cbc decryption password:
$ cat plain.txt 
hoge
```

