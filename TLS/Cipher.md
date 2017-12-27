# 概要
TLSのcipherについて

# 詳細

### cipher suiteの種類を確認したい
IANAのレジストリを参照すること
- https://www.iana.org/assignments/tls-parameters/tls-parameters.xhtml#tls-parameters-4

### TLS_NULL_WITH_NULL_NULLというのはどのような意味か
3つNULLがあるがそれぞれの位置では次のような意味を持ちます。
- 1番目NULL: 鍵交換と認証はしない
- 2番目NULL: 共通鍵暗号はしない
- 3番目NULL: MACアルゴリズムはない

TLS_NULL_WITH_NULL_NULL が指定されている場合、これはそのチャネルで最初にハンドシェイクする間の TLS 接続の初期状態を表します。
TLS_NULL_WITH_NULL_NULLはTLSコネクションが可能かどうかをチェックし、ハンドシェイクをシミュレートするもの。

- SeeAlso
  - https://security.stackexchange.com/questions/135998/ssl-tls-ciphersuite-tls-null-with-null-null

### TLS_DHE_RSA_WITH_AES_256_CBC_SHA
```
DHE: 鍵交換
RSA: 証明書の署名アルゴリズム(認証)
AES_256_CBC: 共通鍵暗号方式(暗号モードと鍵長) chacha20とかは鍵長さない
SHA: MACに使うためのハッシュアルゴリズム
```

### TLSCompressionMethodで指定できるあたい
IANAを参考にすること
- https://www.iana.org/assignments/comp-meth-ids/comp-meth-ids.xhtml

実際にはNULL, DEFLATE, LZSの３つが存在します。
