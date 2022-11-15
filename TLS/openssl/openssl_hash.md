# 概要
opensslでハッシュ値を生成する方法

openssl -hで出力される下記のサブオプションを取る事ができる
```
blake2b512        blake2s256        md4               md5               
mdc2              rmd160            sha1              sha224            
sha256            sha3-224          sha3-256          sha3-384          
sha3-512          sha384            sha512            sha512-224        
sha512-256        shake128          shake256          sm3        
```

# 詳細

### MD5
```
$ echo "HogeFuga" | openssl md5 -binary | base64
Noy1O8KuOOGr0DpFkyHxyQ==
```

### SHA1
```
$ echo "HogeFuga" | openssl sha1 -binary | base64
A7zhvnCC56/YuBPbzWkByoG+8PM=
```

### SHA256
```
$ echo "HogeFuga" | openssl sha256 -binary | base64
xnnZOdLO1PO4kTbml99ZO1a6EVkvDHOpf6HQ8lav66Y=
```

### SHA512
```
$ echo "HogeFuga" | openssl sha512 -binary | base64
hVoxJITXXjnKGPolJGb079qMNAJyv1AOeFCRGd2JULx0+rE6tgeWsf9+ZhCbmUmD7Y9c4YjtaYuWXN8bvcevRA==
```
