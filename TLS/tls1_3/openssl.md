# 概要
opensslコマンド関連で主にTLS1.3に関連する操作について

# 詳細

### 接続できることを確認する
```
$ echo q | /opt/openssl-1.1.1/bin/openssl s_client -connect localhost:443
CONNECTED(00000003)
depth=0 C = XX, L = Default City, O = Default Company Ltd
verify error:num=18:self signed certificate
verify return:1
depth=0 C = XX, L = Default City, O = Default Company Ltd
verify return:1
---
Certificate chain
 0 s:C = XX, L = Default City, O = Default Company Ltd
   i:C = XX, L = Default City, O = Default Company Ltd
---
Server certificate
-----BEGIN CERTIFICATE-----
MIIDADCCAegCCQCUVPJKARwj8TANBgkqhkiG9w0BAQsFADBCMQswCQYDVQQGEwJY
WDEVMBMGA1UEBwwMRGVmYXVsdCBDaXR5MRwwGgYDVQQKDBNEZWZhdWx0IENvbXBh
bnkgTHRkMB4XDTE5MDEyMzAwMTgzOFoXDTIwMDEyMzAwMTgzOFowQjELMAkGA1UE
BhMCWFgxFTATBgNVBAcMDERlZmF1bHQgQ2l0eTEcMBoGA1UECgwTRGVmYXVsdCBD
b21wYW55IEx0ZDCCASIwDQYJKoZIhvcNAQEBBQADggEPADCCAQoCggEBAMObpIhI
ZaekP20Ef4MBxwaI/LSo6J0ZxVrgapWoteAhrbbJ1TqhkkqK7qTqtfnQ/mp9xhWT
SaoVMCBJtULAEI+MAEiMDATTnlaePxu+3Preri3u4mAhlxtDgBbCxk+VKFQJmzoT
YE4qGNAB6lHn+NGKeUNrk4rojGEoFPDeEUX/Y/Rmrk6RR9eZWJoQfCwb2mRLcpj/
6x08QhxCQcj0sE0LQwmbT4FKucTjfIPQOj9gyvsBI8LUKj3ynf7kpMyd/dG9qTuE
k4CjeDdlR5jfzwixdS/zinj+DDlI9oaieoQp1J8WjsA3RtXCNWkZWNN7/2yX3p87
dkbwbfVe/vwJZ1ECAwEAATANBgkqhkiG9w0BAQsFAAOCAQEAGoagFZUxRVACctVe
zAVDMwxzphCOSS+PAJkEq4poLlqz7/ahg2vVgs4G2amin3pHNuuNDtu61i0bZpJ1
VaMFyfsBIZlHtGlHlk6JlWAgsQqTQ/4RlwGByQkn9XtIaafMbFkaVF28dtduR9yz
aVC29tueqQustaVbQDVCY3h7GNw3JOn//c0P2D+2dKGzJfXSMkeGcC7w7eV1jXOD
D2W+rFoOtAzl2K2KiCPlcNy2KSDi837sZeGjSCgqvbTLJOBot/z0DhOq/wkvT902
3YWuLOxfKjYbCEoWhc+ikZUrf6+f0jaz8zAEH5iXOe3BNJ5MF9+e0lNwAKPeUNKQ
bq4g5g==
-----END CERTIFICATE-----
subject=C = XX, L = Default City, O = Default Company Ltd

issuer=C = XX, L = Default City, O = Default Company Ltd

---
No client certificate CA names sent
Peer signing digest: SHA256
Peer signature type: RSA-PSS
Server Temp Key: X25519, 253 bits
---
SSL handshake has read 1328 bytes and written 391 bytes
Verification error: self signed certificate
---
New, TLSv1.3, Cipher is TLS_AES_256_GCM_SHA384
Server public key is 2048 bit
Secure Renegotiation IS NOT supported
Compression: NONE
Expansion: NONE
No ALPN negotiated
Early data was not sent
Verify return code: 18 (self signed certificate)
---
DONE
```

### Cipherを指定する
opensslでデフォルトで存在する３つのcipherです。
```
$ echo q | /opt/openssl-1.1.1/bin/openssl s_client -connect localhost:443 -ciphersuites 'TLS_CHACHA20_POLY1305_SHA256'
$ echo q | /opt/openssl-1.1.1/bin/openssl s_client -connect localhost:443 -ciphersuites 'TLS_AES_128_GCM_SHA256'
$ echo q | /opt/openssl-1.1.1/bin/openssl s_client -connect localhost:443 -ciphersuites 'TLS_AES_256_GCM_SHA384'
```

コロン区切りで複数のciphersuiteを指定することも可能です。
```
$ echo q | /opt/openssl-1.1.1/bin/openssl s_client -connect localhost:443 -ciphersuites 'TLS_AES_256_GCM_SHA384:TLS_CHACHA20_POLY1305_SHA256'
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

### openssl-1.1.1でearly_dataに対応する
nginxでearly_dataに対応させるための修正は次を参考のこと
- http://hg.nginx.org/nginx/rev/548a63b354a2

early_dataに関するAPI群は以下のリファレンスを山椒のこと
- https://www.openssl.org/docs/man1.1.1/man3/SSL_read_early_data.html

