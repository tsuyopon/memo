# 概要
opensslコマンドのdgstサブオプションについてまとめる

# 詳細

### dgstサブオプション
```
-sign 秘密鍵を使ってファイルに署名する。
-verify 公開鍵を使ってファイルの署名を検証する。
-prverify 秘密鍵を使ってファイルの署名を検証する。
-keyform 鍵のフォーマットを指定する。 (PEM | ENGINE)
-out 出力ファイルを指定する。
-signature 署名ファイルを指定する。
-sigopt nm:v 署名パラメータを指定する。
-hmac 鍵からhash MAC 作成する。
-mac 指定のアルゴリズムからMAC(HMACでない)を作成する。
-macopt nm:v MACアルゴリズムのパラメータもしくは鍵を指定する。
-md4, -md5, -mdc2 -ripemd160, -sha, -sha1 ... -sha512, -whirlpool 使用するアルゴリズムを指定する。
-c 16進数出力時に2桁ごとに:で区切る。
-hex 出力を16進数にする。
-r ハッシュ値の出力を coreutil形式(md5sumのような)にする。
```

### 利用例
アルゴリズムをMD5に指定してkey.pem秘密鍵で fileに署名。署名ファイルはsigfile。
```
$ openssl dgst -md5 -sign key.pem -out sigfile file
```

アルゴリズムをMD5に指定してpub.pem公開鍵で fileを検証。署名ファイルはsigfile。
```
$ openssl dgst -md5 -verify pub.pem -signature sigfile file
```

アルゴリズムをMD5に指定してkey.pem秘密鍵で fileを検証。署名ファイルはsigfile。
```
$ openssl dgst -md5 -prverify key.pem -signature sigfile file
```

アルゴリズムをMD5に指定してkey.pem秘密鍵で fileに署名。出力は16進数、署名ファイルはsigfile。
```
$ openssl dgst -md5 -sign key.pem -out sigfile -hex file
```

アルゴリズムをMD5に指定してkey.pem秘密鍵で fileに署名。出力は16進数md5sum形式、署名ファイルはsigfile。
```
$ openssl dgst -md5 -sign key.pem -out sigfile -hex -r file
```

アルゴリズムをMD5に指定してkey.pem秘密鍵で fileに署名。出力は16進数2桁ごとに:で区切る、署名ファイルはsigfile。
```
$ openssl dgst -md5 -sign key.pem -out sigfile -hex -c file
```

fileのMD5ハッシュ値を出力
```
$ openssl dgst -md5 file
```

fileのMD5ハッシュ値を出力。(2桁ごとに区切って)
```
$ openssl dgst -md5 -c file
```

fileのMD5ハッシュ値を出力。(md5sumと同じ形式で)
```
$ openssl dgst -md5 -r file
```

file1, file2 のSHAハッシュ値を出力
```
$ openssl dgst -sha file1 file2
```
