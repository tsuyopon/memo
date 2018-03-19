# 概要
opensslコマンド関連で主にTLS1.3に関連する操作について

# 詳細

### Cipherを指定する
opensslでデフォルトで存在する３つのcipherです。
```
$ echo Q | /opt/openssl-1.1.1/bin/openssl s_client -connect localhost:443 -cipher 'TLS13-CHACHA20-POLY1305-SHA256'
$ echo Q | /opt/openssl-1.1.1/bin/openssl s_client -connect localhost:443 -cipher 'TLS13-AES-256-GCM-SHA384'
$ echo Q | /opt/openssl-1.1.1/bin/openssl s_client -connect localhost:443 -cipher 'TLS13-AES-128-GCM-SHA256'
```

### グループを変更する
Signature Groupsで指定する値をgroupsオプションで指定することができます。
```
$ echo Q | /opt/openssl-1.1.1/bin/openssl s_client -connect localhost:443 -cipher 'TLS13-AES-256-GCM-SHA384' -groups prime256v1 | grep -i "Server Temp"
Server Temp Key: ECDH, P-256, 256 bits
$ echo Q | /opt/openssl-1.1.1/bin/openssl s_client -connect localhost:443 -cipher 'TLS13-AES-256-GCM-SHA384' -groups secp384r1 | grep -i "Server Temp"
Server Temp Key: ECDH, P-384, 384 bits
$ echo Q | /opt/openssl-1.1.1/bin/openssl s_client -connect localhost:443 -cipher 'TLS13-AES-256-GCM-SHA384' -groups secp521r1 | grep -i "Server Temp"
Server Temp Key: ECDH, P-521, 521 bits
```

次のようにして複数のグループ候補を指定することも可能です
```
$ echo Q | /opt/openssl-1.1.1/bin/openssl s_client -connect localhost:443 -cipher 'TLS13-AES-256-GCM-SHA384' -groups prime256v1:secp384r1:secp521r1
```

- 参考
  - https://support.citrix.com/article/CTX229287

### 指定できるグループをチェックする
```
$ echo Q | /opt/openssl-1.1.1/bin/openssl ecparam -list_curves | tail -10
  brainpoolP224r1: RFC 5639 curve over a 224 bit prime field
  brainpoolP224t1: RFC 5639 curve over a 224 bit prime field
  brainpoolP256r1: RFC 5639 curve over a 256 bit prime field
  brainpoolP256t1: RFC 5639 curve over a 256 bit prime field
  brainpoolP320r1: RFC 5639 curve over a 320 bit prime field
  brainpoolP320t1: RFC 5639 curve over a 320 bit prime field
  brainpoolP384r1: RFC 5639 curve over a 384 bit prime field
  brainpoolP384t1: RFC 5639 curve over a 384 bit prime field
  brainpoolP512r1: RFC 5639 curve over a 512 bit prime field
  brainpoolP512t1: RFC 5639 curve over a 512 bit prime field
```

### curvesを指定する
以下はP-256、P521の順番で優先度を指定する場合を表す。(TODO: groupとの違いは何か?)
```
$ echo Q | /opt/openssl-1.1.1/bin/openssl s_client -connect localhost:443 -cipher 'TLS13-AES-256-GCM-SHA384' -curves P-256:P-521 | grep -i "Server Temp"
Server Temp Key: ECDH, P-256, 256 bits
```

### セッション再利用を行う
まずはチケットを保存して、そのチケットを利用する。Newが出れば新規接続
```
$ echo Q | /opt/openssl-1.1.1/bin/openssl s_client -connect 127.0.0.1:443 -sess_out ticket | grep -ie reused -ie new
(snip)
New, TLSv1.3, Cipher is TLS13-AES-256-GCM-SHA384
```

Reusedが出力されれば再利用となります。
```
$ echo Q | /opt/openssl-1.1.1/bin/openssl s_client -connect 127.0.0.1:443 -sess_in ticket | grep -ie reused -ie new
DONE
Reused, TLSv1.3, Cipher is TLS13-AES-256-GCM-SHA384
```

試しにcipherやgroupなどを以前とは異なるものに変更するとReusedとならずにNewとなります。


### 0-RTTをコマンドライン

最初にセッション情報を保存します。
```
$ openssl s_client -connect nghttp2.org:13443 -sess_out session.dat
```

early_dataとして送付するデータを準備します。
```
$ cat http.txt
GET / HTTP/1.1
Host: nghttp2.org:13443
```

次のようにしてearly_data拡張として送付します。
```
$ openssl s_client -connect nghttp2.org:13443 -sess_out session.dat -sess_in session.dat -early_data http.txt
```

- 参考
  - https://nghttp2.org/blog/2017/03/20/tlsv1-3-endpoint-is-now-online/


