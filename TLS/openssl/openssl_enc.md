# 概要
openssl encを利用する

# 詳細
### base64エンコード・デコードする
base64エンコードする
```
$ echo "hogefugapiyo" | openssl enc -e -base64
aG9nZWZ1Z2FwaXlvCg==
```

ase64デコードする
```
$ echo "aG9nZWZ1Z2FwaXlvCg==" | openssl enc -d -base64
hogefugapiyo
```
