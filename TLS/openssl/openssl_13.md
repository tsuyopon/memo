# 概要
TLS1.3対応(openssl-1.1.1以降)でのopensslコマンドの取り扱いについて

# 詳細

### s_serverとs_clientを試してみる
以下でサーバを起動する。
```
$ sudo /usr/local/openssl-1.1.1a/bin/openssl s_server -accept 443 -cert server.crt -key server.key -4
```

サーバへリクエストをしてみると次のような出力となる
```
$ /usr/local/openssl-1.1.1a/bin/openssl s_client -connect localhost:443 -keylogfile /Users/tsuyoshi/sslkeylog.log -tls1_3 
CONNECTED(00000007)
depth=0 C = AU, ST = Some-State, O = Internet Widgits Pty Ltd
verify error:num=18:self signed certificate
verify return:1
depth=0 C = AU, ST = Some-State, O = Internet Widgits Pty Ltd
verify return:1
---
Certificate chain
 0 s:C = AU, ST = Some-State, O = Internet Widgits Pty Ltd
   i:C = AU, ST = Some-State, O = Internet Widgits Pty Ltd
---
Server certificate
-----BEGIN CERTIFICATE-----
MIIDETCCAfkCFFSBo254K0/KD0TJwmx4ggYTVk5NMA0GCSqGSIb3DQEBCwUAMEUx
CzAJBgNVBAYTAkFVMRMwEQYDVQQIDApTb21lLVN0YXRlMSEwHwYDVQQKDBhJbnRl
cm5ldCBXaWRnaXRzIFB0eSBMdGQwHhcNMTkwMjAzMDAwNTQ5WhcNMjAwMjAzMDAw
NTQ5WjBFMQswCQYDVQQGEwJBVTETMBEGA1UECAwKU29tZS1TdGF0ZTEhMB8GA1UE
CgwYSW50ZXJuZXQgV2lkZ2l0cyBQdHkgTHRkMIIBIjANBgkqhkiG9w0BAQEFAAOC
AQ8AMIIBCgKCAQEAvHv5fnF2OSU7bWlG//7snpU4MshDYZU9j5tVj763r9qNejsO
A9i87TsETY5gg6VObPwKbvtSsxgOML253i2sJtrK6G/fpLpnj4hbRTqpPYLv12nW
3V7LEe0eN0qxyrZHlwsYr2+zzMi1kkDPTw4b/v1R9kXg/gBlwB9Bst+xFl9ruN2p
hc8zWcVnhYG6MDoCJDOxKb7RkPAkS7Ys90/ikgvDSVVX6nbwzs4v7p2wTJdmO7Qh
gCY62cZgNLt0ExdcHAnHOP5em70aNzuIpMvF1zC9ALjpBBFytDKLgTmoTc69YFAH
8Qws8lW3qjLZrD2YxVBdbJx3l1Uf86V9aXF04wIDAQABMA0GCSqGSIb3DQEBCwUA
A4IBAQCe2q21PASCiqQn6WgKVYMmOULHDLRnnFyF81ByT2Peh3OdrKWDFoOdswb7
Ps8zbjnF1luhUnlqxueIRP6iH+aLG8MN0CD1E6U43P6LrD2RLyVMA04RcrQhgRd1
ei2JsibsegLnTZWwvpQqtEkW2r8u0M3NcreJScDoF87l+AAKW99+DKKxWJDKHhzN
qAzgiWzaZy6IvGU41hImZiaWqCAbqn56UeeyZpJQU2OZsuevDHhdxlbX5MaovXNg
tYAusG0CW5bjv87+4TNQzYytycfR0/L/+VYknJJZlr2Kp4/kk1z17BvzAzBdc/lU
aq0ABjyppSfC/E8P61hg37GK12mK
-----END CERTIFICATE-----
subject=C = AU, ST = Some-State, O = Internet Widgits Pty Ltd

issuer=C = AU, ST = Some-State, O = Internet Widgits Pty Ltd

---
No client certificate CA names sent
Peer signing digest: SHA256
Peer signature type: RSA-PSS
Server Temp Key: X25519, 253 bits
---
SSL handshake has read 1345 bytes and written 313 bytes
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
---
Post-Handshake New Session Ticket arrived:
SSL-Session:
    Protocol  : TLSv1.3
    Cipher    : TLS_AES_256_GCM_SHA384
    Session-ID: C721DB79D1321EEB9ABF6E9E64302C75BF1DD5ED4D7B28F28CACC801B67471FC
    Session-ID-ctx: 
    Resumption PSK: D7277796B0989B754BB0665C5540BD20EB37C6A0C026E75BA375D4492FEB47F8DD0E3E73C94853DA55EF3BD9AFB2EB54
    PSK identity: None
    PSK identity hint: None
    SRP username: None
    TLS session ticket lifetime hint: 7200 (seconds)
    TLS session ticket:
    0000 - c5 8b f0 fb 63 c3 a1 49-ee b5 cc 92 dd 36 df 35   ....c..I.....6.5
    0010 - 55 7e c1 41 64 ea 6e 20-58 c8 ff 3f 7c 6f d9 08   U~.Ad.n X..?|o..
    0020 - 45 a6 b9 4b 27 5c 22 9a-e7 ca 60 00 25 ec d4 09   E..K'\"...`.%...
    0030 - 26 16 05 df 21 ed 1b b8-48 4d 85 ad 14 66 0c 30   &...!...HM...f.0
    0040 - 43 d2 e5 15 50 e2 ad 13-99 96 cb 58 3c 6a 3b b7   C...P......X<j;.
    0050 - 0e 60 b8 be 19 ca ff d6-6f 24 e0 8c e3 04 0c 73   .`......o$.....s
    0060 - 0f ee ad ca c1 83 c6 bf-0b dc f2 e3 8b 05 70 dc   ..............p.
    0070 - c1 ca 03 e7 8a 3d 9b 57-e0 7e 15 ce 73 be fa 8f   .....=.W.~..s...
    0080 - 59 83 e8 82 73 44 9e 8a-64 e4 b9 57 e8 b7 ca ad   Y...sD..d..W....
    0090 - 10 13 52 e6 bc 94 3d 8e-2f d2 ee e1 22 46 64 bf   ..R...=./..."Fd.
    00a0 - 92 aa c8 6c 67 27 e5 bf-51 87 ac 9d 71 cd 27 ee   ...lg'..Q...q.'.
    00b0 - c9 5a 28 9d 82 ed 88 31-87 22 52 0a 3d 76 e6 01   .Z(....1."R.=v..
    00c0 - a5 4c c8 08 9e 70 73 28-d7 82 9d d1 d0 bd a9 ac   .L...ps(........

    Start Time: 1549154353
    Timeout   : 7200 (sec)
    Verify return code: 18 (self signed certificate)
    Extended master secret: no
    Max Early Data: 0
---
read R BLOCK
---
Post-Handshake New Session Ticket arrived:
SSL-Session:
    Protocol  : TLSv1.3
    Cipher    : TLS_AES_256_GCM_SHA384
    Session-ID: 6F95597D84A58C0265C645E7035EC223279DDBE90409B95245A55D01C758AF4E
    Session-ID-ctx: 
    Resumption PSK: 4B6DD146CBFEA2472BE6B51409597B0B92503582B08136CD878C9A4034823DD97950ED4583F638012018408048E30C14
    PSK identity: None
    PSK identity hint: None
    SRP username: None
    TLS session ticket lifetime hint: 7200 (seconds)
    TLS session ticket:
    0000 - c5 8b f0 fb 63 c3 a1 49-ee b5 cc 92 dd 36 df 35   ....c..I.....6.5
    0010 - 75 88 6c d6 4d 00 6a 52-d4 87 f6 13 4c 54 e2 b9   u.l.M.jR....LT..
    0020 - e5 e1 0f 64 66 8d b9 20-94 48 a1 49 22 8c a1 bf   ...df.. .H.I"...
    0030 - 79 4f 56 b3 7b 33 7e a8-e7 a4 b9 ae 72 89 64 eb   yOV.{3~.....r.d.
    0040 - 88 41 6e c0 c3 e7 c2 b6-5d 8c d6 67 f9 bb 4f 3d   .An.....]..g..O=
    0050 - e2 74 64 e2 4e b2 de 71-60 62 a4 bd d8 bc fa 95   .td.N..q`b......
    0060 - a6 c1 ec 05 34 4f 87 10-97 52 ca 69 22 65 fe f8   ....4O...R.i"e..
    0070 - ab f9 ce 06 94 15 93 eb-c7 86 d1 22 a5 2c 53 54   ...........".,ST
    0080 - 1f d1 67 1d 69 36 c6 e6-38 71 e0 31 02 41 3d bd   ..g.i6..8q.1.A=.
    0090 - c4 44 a3 61 6e ef 5f 50-4d fe 6f c4 45 88 55 25   .D.an._PM.o.E.U%
    00a0 - e8 6b 13 9a d4 06 29 ea-01 27 1f 65 0c a0 d2 b5   .k....)..'.e....
    00b0 - 8a 60 35 53 b2 77 0d 20-67 02 78 8c 09 e3 12 5c   .`5S.w. g.x....\
    00c0 - 52 fc fb 86 4f 31 14 cd-ab bb 96 0d 3d 71 e6 dc   R...O1......=q..

    Start Time: 1549154353
    Timeout   : 7200 (sec)
    Verify return code: 18 (self signed certificate)
    Extended master secret: no
    Max Early Data: 0
---
read R BLOCK
```

New Session Ticketが2枚送付されてきているのはIPv4とIPv6のデュアルスタックのために配布されてきている。

なお、opensslのs_clientは今まではQコマンドだけで終了していたが、終了させるには次のようになります。
```
Ctrl + D
```

鍵更新をしたい場合には
```
K
```

### wireshrkでdecryptするためのセッション鍵を出力したい
たとえば、s_clientでkeylogfileオプションを指定することでセッション鍵を
```
$ /usr/local/openssl-1.1.1a/bin/openssl s_client -connect localhost:443 -keylogfile /Users/tsuyoshi/sslkeylog.log -tls1_3 
```

### 利用可能なCipherを確認する
```
$  /usr/local/openssl-1.1.1a/bin/openssl ciphers 
TLS_AES_256_GCM_SHA384:TLS_CHACHA20_POLY1305_SHA256:TLS_AES_128_GCM_SHA256:ECDHE-ECDSA-AES256-GCM-SHA384:ECDHE-RSA-AES256-GCM-SHA384:DHE-RSA-AES256-GCM-SHA384:ECDHE-ECDSA-CHACHA20-POLY1305:ECDHE-RSA-CHACHA20-POLY1305:DHE-RSA-CHACHA20-POLY1305:ECDHE-ECDSA-AES128-GCM-SHA256:ECDHE-RSA-AES128-GCM-SHA256:DHE-RSA-AES128-GCM-SHA256:ECDHE-ECDSA-AES256-SHA384:ECDHE-RSA-AES256-SHA384:DHE-RSA-AES256-SHA256:ECDHE-ECDSA-AES128-SHA256:ECDHE-RSA-AES128-SHA256:DHE-RSA-AES128-SHA256:ECDHE-ECDSA-AES256-SHA:ECDHE-RSA-AES256-SHA:DHE-RSA-AES256-SHA:ECDHE-ECDSA-AES128-SHA:ECDHE-RSA-AES128-SHA:DHE-RSA-AES128-SHA:RSA-PSK-AES256-GCM-SHA384:DHE-PSK-AES256-GCM-SHA384:RSA-PSK-CHACHA20-POLY1305:DHE-PSK-CHACHA20-POLY1305:ECDHE-PSK-CHACHA20-POLY1305:AES256-GCM-SHA384:PSK-AES256-GCM-SHA384:PSK-CHACHA20-POLY1305:RSA-PSK-AES128-GCM-SHA256:DHE-PSK-AES128-GCM-SHA256:AES128-GCM-SHA256:PSK-AES128-GCM-SHA256:AES256-SHA256:AES128-SHA256:ECDHE-PSK-AES256-CBC-SHA384:ECDHE-PSK-AES256-CBC-SHA:SRP-RSA-AES-256-CBC-SHA:SRP-AES-256-CBC-SHA:RSA-PSK-AES256-CBC-SHA384:DHE-PSK-AES256-CBC-SHA384:RSA-PSK-AES256-CBC-SHA:DHE-PSK-AES256-CBC-SHA:AES256-SHA:PSK-AES256-CBC-SHA384:PSK-AES256-CBC-SHA:ECDHE-PSK-AES128-CBC-SHA256:ECDHE-PSK-AES128-CBC-SHA:SRP-RSA-AES-128-CBC-SHA:SRP-AES-128-CBC-SHA:RSA-PSK-AES128-CBC-SHA256:DHE-PSK-AES128-CBC-SHA256:RSA-PSK-AES128-CBC-SHA:DHE-PSK-AES128-CBC-SHA:AES128-SHA:PSK-AES128-CBC-SHA256:PSK-AES128-CBC-SHA
```


### cipherを指定する
TLS1.3ではcipherオプションではなくて、ciphersuitesオプションを利用します。
複数を指定する場合には":"をセパレータとして指定することができます。
```
$ /usr/local/openssl-1.1.1a/bin/openssl s_client -connect localhost:443 -ciphersuites TLS_CHACHA20_POLY1305_SHA256:TLS_AES_128_GCM_SHA256
```

### セッションリザンプションの確認について
reconnectだとうまくいかないので、sess_in, sess_outを利用します。


