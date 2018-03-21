# 概要
opensslクライアントのs_clientオプションについて
TLS接続先に対してXXしたいといった内容でまとめている

# 詳細

### 接続した先の証明書の内容を表示する
showcertsを付与する
```
$ openssl s_client -connect shopping.yahoo.co.jp:443 -showcerts 
CONNECTED(00000003)
depth=1 /C=BE/O=GlobalSign nv-sa/CN=GlobalSign Organization Validation CA - SHA256 - G2
verify error:num=20:unable to get local issuer certificate
verify return:0
---
Certificate chain
 0 s:/C=JP/ST=Tokyo/L=Minato-Ku/O=Yahoo Japan Corporation/CN=shopping.yahoo.co.jp
   i:/C=BE/O=GlobalSign nv-sa/CN=GlobalSign Organization Validation CA - SHA256 - G2
-----BEGIN CERTIFICATE-----
MIIFRTCCBC2gAwIBAgIMRKQPh/5N3WOv6VV9MA0GCSqGSIb3DQEBCwUAMGYxCzAJ
BgNVBAYTAkJFMRkwFwYDVQQKExBHbG9iYWxTaWduIG52LXNhMTwwOgYDVQQDEzNH
bG9iYWxTaWduIE9yZ2FuaXphdGlvbiBWYWxpZGF0aW9uIENBIC0gU0hBMjU2IC0g
RzIwHhcNMTYxMDE5MDAwMDAwWhcNMTcxMDE5MTQ1OTU5WjByMQswCQYDVQQGEwJK
UDEOMAwGA1UECBMFVG9reW8xEjAQBgNVBAcTCU1pbmF0by1LdTEgMB4GA1UEChMX
WWFob28gSmFwYW4gQ29ycG9yYXRpb24xHTAbBgNVBAMTFHNob3BwaW5nLnlhaG9v
LmNvLmpwMIIBIjANBgkqhkiG9w0BAQEFAAOCAQ8AMIIBCgKCAQEAzoZtY1E+ey6T
P4Cu4o3MI1555lAIJrpAlXy9YKp3fD0yHaw0YfCaZEuXObEib72iGpgw3P0TRW0S
zTeb/F9LYwTZD40DNclpttkZK0aHRJjgqve84xIsHoF7Mn3Ryyy2e/MemKJGNK99
mfm2PD9FgaGtcS5yXm1isLn6r2SRJoPXRO2fgGL/+aXjs+7uDNr7K8NE7+CtQxUI
48U+LvPdDtKdePBh54G/++OOpg6DOwM7prDIu7jCw4s5ntJBmJDqOIlyDvZnhk9A
iei7nQuQwgtXq+W1UUqNfUOKpAxdwwwMwwgno88Ls927YMiHm3TMDCu1Xvy+cwNO
4MHMbT7GjwIDAQABo4IB5TCCAeEwDgYDVR0PAQH/BAQDAgWgMIGgBggrBgEFBQcB
AQSBkzCBkDBNBggrBgEFBQcwAoZBaHR0cDovL3NlY3VyZS5nbG9iYWxzaWduLmNv
bS9jYWNlcnQvZ3Nvcmdhbml6YXRpb252YWxzaGEyZzJyMS5jcnQwPwYIKwYBBQUH
MAGGM2h0dHA6Ly9vY3NwMi5nbG9iYWxzaWduLmNvbS9nc29yZ2FuaXphdGlvbnZh
bHNoYTJnMjBWBgNVHSAETzBNMEEGCSsGAQQBoDIBFDA0MDIGCCsGAQUFBwIBFiZo
dHRwczovL3d3dy5nbG9iYWxzaWduLmNvbS9yZXBvc2l0b3J5LzAIBgZngQwBAgIw
CQYDVR0TBAIwADBJBgNVHR8EQjBAMD6gPKA6hjhodHRwOi8vY3JsLmdsb2JhbHNp
Z24uY29tL2dzL2dzb3JnYW5pemF0aW9udmFsc2hhMmcyLmNybDAfBgNVHREEGDAW
ghRzaG9wcGluZy55YWhvby5jby5qcDAdBgNVHSUEFjAUBggrBgEFBQcDAQYIKwYB
BQUHAwIwHQYDVR0OBBYEFGinxjbNBfcDmhTn7WYPBSRVFfvfMB8GA1UdIwQYMBaA
FJbeYfG9HBYpUxzAzH07gwBA5hp8MA0GCSqGSIb3DQEBCwUAA4IBAQAuqcnltNzH
u5HBKU+5dGcUB6+DKMIzKyQNeAweM1o9o9zIJOKi+gpL6DUtYfGPEPJnNjxrumf5
Xx0VBLRXybNGF40ZSCnezz216ma1YrY51zo78DRnjqs9ov77gtBNIlgMkV3/a0wM
Gwa67ESx2Jvso2nT1vYEOeGWIczR8UuPbJOSTSF5jJZzA18DecVcTL+3pG1/dZO6
SLDZF46wWTeJSk2MtfUh06A64JWs+i+tXDAuO/jpFz2iesrfEK4HMtXP6HkT8WSR
lx8DsGAoV64oEIZrTsz/I0Z/4yfNSEU0tdENuw6UOZ9gy/gtl1Pz7LcgRFEyaNO/
/5AU/w73tbpj
-----END CERTIFICATE-----
 1 s:/C=BE/O=GlobalSign nv-sa/CN=GlobalSign Organization Validation CA - SHA256 - G2
   i:/C=BE/O=GlobalSign nv-sa/OU=Root CA/CN=GlobalSign Root CA
-----BEGIN CERTIFICATE-----
MIIEaTCCA1GgAwIBAgILBAAAAAABRE7wQkcwDQYJKoZIhvcNAQELBQAwVzELMAkG
A1UEBhMCQkUxGTAXBgNVBAoTEEdsb2JhbFNpZ24gbnYtc2ExEDAOBgNVBAsTB1Jv
b3QgQ0ExGzAZBgNVBAMTEkdsb2JhbFNpZ24gUm9vdCBDQTAeFw0xNDAyMjAxMDAw
MDBaFw0yNDAyMjAxMDAwMDBaMGYxCzAJBgNVBAYTAkJFMRkwFwYDVQQKExBHbG9i
YWxTaWduIG52LXNhMTwwOgYDVQQDEzNHbG9iYWxTaWduIE9yZ2FuaXphdGlvbiBW
YWxpZGF0aW9uIENBIC0gU0hBMjU2IC0gRzIwggEiMA0GCSqGSIb3DQEBAQUAA4IB
DwAwggEKAoIBAQDHDmw/I5N/zHClnSDDDlM/fsBOwphJykfVI+8DNIV0yKMCLkZc
C33JiJ1Pi/D4nGyMVTXbv/Kz6vvjVudKRtkTIso21ZvBqOOWQ5PyDLzm+ebomchj
SHh/VzZpGhkdWtHUfcKc1H/hgBKueuqI6lfYygoKOhJJomIZeg0k9zfrtHOSewUj
mxK1zusp36QUArkBpdSmnENkiN74fv7j9R7l/tyjqORmMdlMJekYuYlZCa7pnRxt
Nw9KHjUgKOKv1CGLAcRFrW4rY6uSa2EKTSDtc7p8zv4WtdufgPDWi2zZCHlKT3hl
2pK8vjX5s8T5J4BO/5ZS5gIg4Qdz6V0rvbLxAgMBAAGjggElMIIBITAOBgNVHQ8B
Af8EBAMCAQYwEgYDVR0TAQH/BAgwBgEB/wIBADAdBgNVHQ4EFgQUlt5h8b0cFilT
HMDMfTuDAEDmGnwwRwYDVR0gBEAwPjA8BgRVHSAAMDQwMgYIKwYBBQUHAgEWJmh0
dHBzOi8vd3d3Lmdsb2JhbHNpZ24uY29tL3JlcG9zaXRvcnkvMDMGA1UdHwQsMCow
KKAmoCSGImh0dHA6Ly9jcmwuZ2xvYmFsc2lnbi5uZXQvcm9vdC5jcmwwPQYIKwYB
BQUHAQEEMTAvMC0GCCsGAQUFBzABhiFodHRwOi8vb2NzcC5nbG9iYWxzaWduLmNv
bS9yb290cjEwHwYDVR0jBBgwFoAUYHtmGkUNl8qJUC99BM00qP/8/UswDQYJKoZI
hvcNAQELBQADggEBAEYq7l69rgFgNzERhnF0tkZJyBAW/i9iIxerH4f4gu3K3w4s
32R1juUYcqeMOovJrKV3UPfvnqTgoI8UV6MqX+x+bRDmuo2wCId2Dkyy2VG7EQLy
XN0cvfNVlg/UBsD84iOKJHDTu/B5GqdhcIOKrwbFINihY9Bsrk8y1658GEV1BSl3
30JAZGSGvip2CTFvHST0mdCF/vIhCPnG9vHQWe3WVjwIKANnuvD58ZAWR65n5ryA
SOlCdjSXVWkkDoPWoC209fN5ikkodBpBocLTJIg1MGCUF7ThBCIxPTsvFwayuJ2G
K1pp74P1S8SqtCr4fKGxhZSM9AyHDPSsQPhZSZg=
-----END CERTIFICATE-----
---
Server certificate
subject=/C=JP/ST=Tokyo/L=Minato-Ku/O=Yahoo Japan Corporation/CN=shopping.yahoo.co.jp
issuer=/C=BE/O=GlobalSign nv-sa/CN=GlobalSign Organization Validation CA - SHA256 - G2
---
No client certificate CA names sent
---
SSL handshake has read 2646 bytes and written 444 bytes
---
New, TLSv1/SSLv3, Cipher is RC4-SHA
Server public key is 2048 bit
Secure Renegotiation IS supported
Compression: NONE
Expansion: NONE
SSL-Session:
    Protocol  : TLSv1
    Cipher    : RC4-SHA
    Session-ID: 26F3E5A1998B43623F39607045A84DE0D1085FEC392E62A796389124612E546A
    Session-ID-ctx: 
    Master-Key: A8084DD18F9FEE512B62F3858FB96A5BA8FC7161786586F6BA8FBCBFD07A6081F952695512D29F11AEC35D76ECA1390D
    Key-Arg   : None
    Start Time: 1478820987
    Timeout   : 300 (sec)
    Verify return code: 0 (ok)
---

<!DOCTYPE html>
<html lang="ja">
<head>
<meta charset="utf-8">
<title>Yahoo!ショッピング - Ｔポイントが貯まる！使える！ネット通販</title>
<meta name=”robots” content=”noindex”>
<link rel="stylesheet" href="https://s.yimg.jp/images/shp_front/pc/_library/css/_library1.15.css">
<link rel="stylesheet" href="https://s.yimg.jp/images/shp_front/pc/error/css/error1.2.css">
<link rel="canonical" href="http://shopping.yahoo.co.jp/">
</head>
<body>
</body>

(省略)

</html>
read:errno=0
```

### 接続時の証明書の詳細な情報を表示する
BEGIN CERTIFICATEからEND CERTIFICATEの部分をわかりやすい情報に変換して「Certificate:」以下を表示しています。
有効期限、Issuer, Subject, Serial Number, X509拡張, 署名などを表示してくれています。
```
$ openssl s_client -connect www.yahoo.jp:443 | openssl x509 -text
depth=1 C = JP, O = "Cybertrust Japan Co., Ltd.", CN = Cybertrust Japan Public CA G3
verify error:num=20:unable to get local issuer certificate
verify return:0
Certificate:
    Data:
        Version: 3 (0x2)
        Serial Number:
            4f:07:85:9d:ad:f7:a3:f5:5c:45:62:1e:33:91:80:bc:b7:5c:1d:a1
    Signature Algorithm: sha256WithRSAEncryption
        Issuer: C=JP, O=Cybertrust Japan Co., Ltd., CN=Cybertrust Japan Public CA G3
        Validity
            Not Before: Mar 14 05:43:41 2017 GMT
            Not After : Mar 14 14:59:00 2018 GMT
        Subject: C=JP, ST=Tokyo, L=Chiyoda-ku, O=Yahoo Japan Corporation, OU=EDGE_20170313, CN=*.yahoo.co.jp
        Subject Public Key Info:
            Public Key Algorithm: rsaEncryption
                Public-Key: (2048 bit)
                Modulus:
                    00:d5:aa:23:10:8a:92:4f:64:8b:64:49:70:75:65:
                    (snip)
                Exponent: 65537 (0x10001)
        X509v3 extensions:
            X509v3 Basic Constraints: critical
                CA:FALSE
            X509v3 Certificate Policies: 
                Policy: 1.2.392.200081.1.1
                  User Notice:
                    Explicit Text: For more details, please visit our website https://www.cybertrust.ne.jp .
                  CPS: https://www.cybertrust.ne.jp/ssl/repository/index.html
                Policy: 2.23.140.1.2.2

            X509v3 Subject Alternative Name: 
                DNS:*.yahoo.co.jp, DNS:*.yimg.jp, DNS:*.c.yimg.jp, DNS:*.yahooapis.jp, DNS:cgi2.r-agent.yahoo.co.jp, DNS:*.yoctfs.jp, DNS:*.edge.storage-yahoo.jp, DNS:*.east.edge.storage-yahoo.jp, DNS:*.west.edge.storage-yahoo.jp, DNS:*.global.edge.storage-yahoo.jp, DNS:*.listing.yahoo.co.jp, DNS:*.ane.yahoo.co.jp, DNS:*.chiebukuro.yahoo.co.jp, DNS:*.finance.yahoo.co.jp, DNS:*.auctions.yahoo.co.jp, DNS:*.shopping.yahoo.co.jp, DNS:*.travel.yahoo.co.jp, DNS:*.news.yahoo.co.jp, DNS:*.pmx.proatlas.net, DNS:add.dir.yahoo.co.jp, DNS:map.alpsmap.jp, DNS:ssl.map.srv.yimg.jp, DNS:ssl.api.olp.yahooapis.jp, DNS:subscription.push.yahooapis.jp, DNS:auth.carnavi.yahooapis.jp, DNS:vics.carnavi.yahooapis.jp, DNS:cm.froma.yahoo.co.jp, DNS:*.yahoobox.jp, DNS:info.hatalike.yahoo.co.jp, DNS:movie.chocotle.yahoo.co.jp, DNS:opetool.bylines.news.yahoo.co.jp, DNS:tool.bylines.news.yahoo.co.jp, DNS:poiedit.map.yahoo.co.jp, DNS:compass.ymobile.yahoo.co.jp, DNS:pf.carnavi.yahooapis.jp, DNS:rf.carnavi.yahooapis.jp, DNS:assist.search.yahooapis.jp, DNS:suggest.search.yahooapis.jp, DNS:arc.help.yahoo.co.jp, DNS:personalapp.news.yahooapis.jp, DNS:cksync.pdsp.yahoo.co.jp, DNS:suggest.auctions.yahooapis.jp, DNS:ssl-tools.kainavi.search.yahoo.co.jp, DNS:yoshimoto.gyao.yahoo.co.jp, DNS:lyrics.gyao.yahoo.co.jp, DNS:m.gyao.yahoo.co.jp, DNS:im.ov.yahoo.co.jp, DNS:xml.listing.yahoo.co.jp, DNS:app.news.yahooapis.jp, DNS:feedback.premiads.yahoo.co.jp, DNS:feedback.advertising.yahoo.co.jp, DNS:frame.games.yahoo.co.jp, DNS:sandbox.frame.games.yahoo.co.jp, DNS:*.yjtag.yahoo.co.jp, DNS:*.east.edge.storage-yahoobox.jp, DNS:*.shopping.c.yimg.jp, DNS:*.yjtag.jp, DNS:*.ys-insurance.co.jp, DNS:www.yjcard.co.jp, DNS:yahoo.co.jp
            Authority Information Access: 
                OCSP - URI:http://ocsp.cybertrust.ne.jp/OcspServer
                CA Issuers - URI:http://sureseries-crl.cybertrust.ne.jp/SureServer/ctjpubcag3/ctjpubcag3_sha256.crt

            X509v3 Key Usage: critical
                Digital Signature, Key Encipherment
            X509v3 Extended Key Usage: 
                TLS Web Server Authentication, TLS Web Client Authentication
            X509v3 Authority Key Identifier: 
                keyid:73:A8:08:53:29:B8:15:FB:99:80:E5:C5:37:D8:F8:39:7B:A4:13:06

            X509v3 CRL Distribution Points: 

                Full Name:
                  URI:http://sureseries-crl.cybertrust.ne.jp/SureServer/ctjpubcag3/cdp.crl

            X509v3 Subject Key Identifier: 
                77:8E:F7:67:6C:1C:B6:2E:BB:D8:71:BF:91:0E:DE:17:22:C1:02:E1
            1.3.6.1.4.1.11129.2.4.2: 
                (snip)
    Signature Algorithm: sha256WithRSAEncryption
         09:c4:3e:18:f5:13:38:53:22:eb:96:00:72:a2:7d:e4:da:21:
         (snip)
-----BEGIN CERTIFICATE-----
MIIM8DCCC9igAwIBAgIUTweFna33o/VcRWIeM5GAvLdcHaEwDQYJKoZIhvcNAQEL
(snip)
-----END CERTIFICATE-----
```

### 接続状態を表示する
クライアントとサーバとの接続状況を以下のコマンドで確認できます。
接続状況やサーバ証明書が表示されます。
```
$ openssl s_client -connect shopping.yahoo.co.jp:443 -state
CONNECTED(00000003)
SSL_connect:before/connect initialization
SSL_connect:SSLv2/v3 write client hello A
SSL_connect:SSLv3 read server hello A
depth=1 /C=JP/O=Cybertrust Japan Co., Ltd./CN=Cybertrust Japan Public CA G3
verify error:num=20:unable to get local issuer certificate
verify return:0
SSL_connect:SSLv3 read server certificate A
SSL_connect:SSLv3 read server done A
SSL_connect:SSLv3 write client key exchange A
SSL_connect:SSLv3 write change cipher spec A
SSL_connect:SSLv3 write finished A
SSL_connect:SSLv3 flush data
SSL_connect:SSLv3 read finished A
---
Certificate chain
 0 s:/C=JP/ST=Tokyo/L=Chiyoda-ku/O=Yahoo Japan Corporation/OU=EDGE_20170313/CN=*.yahoo.co.jp
   i:/C=JP/O=Cybertrust Japan Co., Ltd./CN=Cybertrust Japan Public CA G3
 1 s:/C=JP/O=Cybertrust Japan Co., Ltd./CN=Cybertrust Japan Public CA G3
   i:/C=IE/O=Baltimore/OU=CyberTrust/CN=Baltimore CyberTrust Root
---
Server certificate
-----BEGIN CERTIFICATE-----
(以下省略)
```

### 接続時にSSL/TLSバージョンを指定する
```
$ openssl s_client -connect www.yahoo.co.jp:443 -ssl2
$ openssl s_client -connect www.yahoo.co.jp:443 -ssl3
$ openssl s_client -connect www.yahoo.co.jp:443 -tls1
$ openssl s_client -connect www.yahoo.co.jp:443 -tls1_1
$ openssl s_client -connect www.yahoo.co.jp:443 -tls1_2
```

### TLS接続をして、そのままHTTPを要求してみる
以下の例ではTLS接続したあとに「GET / HTTP/1.1 + (改行2回)」をいれることでHTTPからコンテンツを取得しています。
```
$ openssl s_client -connect localhost:443 -debug
(snip)
GET / HTTP/1.1

```

### ハンドシェイクのTLSパケット情報も含めて確認する
msgオプションを付与すると、ClientHelloやServerHello等のパケット情報を確認することができる。
レコードレイヤーの5byteの情報などはこれで簡単に目GREPできる。
```
$ openssl s_client -connect shopping.yahoo.co.jp:443 -msg
CONNECTED(00000003)
>>> SSL 2.0 [length 0080], CLIENT-HELLO
    01 03 01 00 57 00 00 00 20 00 00 39 00 00 38 00
    00 35 00 00 16 00 00 13 00 00 0a 07 00 c0 00 00
    33 00 00 32 00 00 2f 00 00 9a 00 00 99 00 00 96
    03 00 80 00 00 05 00 00 04 01 00 80 00 00 15 00
    00 12 00 00 09 06 00 40 00 00 14 00 00 11 00 00
    08 00 00 06 04 00 80 00 00 03 02 00 80 00 00 ff
    36 2a 9f bb a9 17 ad 0e ec 3f df 97 cc 36 f1 ea
    67 ae 41 73 15 d7 10 6d 1a a8 e1 16 e5 9c 8b 0b
<<< TLS 1.0 Handshake [length 0051], ServerHello
    02 00 00 4d 03 01 82 9e 26 bc 02 75 e9 02 a7 53
    86 7c 70 bc cc 1e a9 ab dd 28 f6 a6 59 37 a9 63
    0e ca 77 bf 9d 69 20 7a 59 6c 72 cd 05 22 3e 7c
    cd 6f a9 5e 06 49 d7 74 4d 85 55 71 86 d5 b7 5b
    24 63 ef a3 3d 4e e7 00 2f 00 00 05 ff 01 00 01
    00
<<< TLS 1.0 Handshake [length 11ce], Certificate
    0b 00 11 ca 00 11 c7 00 0d 63 30 82 0d 5f 30 82
(snip)
```

### 接続時に暗号を指定する
たとえば、MD5関連の暗号だけ送るとすると、、、
```
$ openssl s_client -connect www.google.com:443 -cipher `openssl ciphers MD5`
```

### 接続時にCAファイルを指定する
```
$ openssl s_client -connect www.google.com:443 -CApath /etc/ssl/certs
```

### パケット内容詳細も取得する
debugオプションを付与するとパケット内容の詳細も表示する。
```
$ openssl s_client -connect shopping.yahoo.co.jp:443  -debug
...
0000 - 0b 00 09 bf 00 09 bc 00-05 49 30 82 05 45 30 82   .........I0..E0.
0010 - 04 2d a0 03 02 01 02 02-0c 44 a4 0f 87 fe 4d dd   .-.......D....M.
...
```

接続に失敗すると次のような出力となる。(-msgオプションを付けておいたほうがいいかもしれない)
```
$ openssl s_client -connect shopping.yahoo.co.jp:443 -ssl3 -debug -msg
CONNECTED(00000003)
write to 0x7fa113e00150 [0x7fa11500b000] (94 bytes => 94 (0x5E))
0000 - 16 03 00 00 59 01 00 00-55 03 00 59 3d 77 f6 9e   ....Y...U..Y=w..
0010 - ec f1 5d a5 6b aa fb 71-f7 ba fe 43 54 55 7b 78   ..].k..q...CTU{x
0020 - 53 c1 98 2d d2 ee 8a 25-57 6c a1 00 00 2e 00 39   S..-...%Wl.....9
0030 - 00 38 00 35 00 16 00 13-00 0a 00 33 00 32 00 2f   .8.5.......3.2./
0040 - 00 9a 00 99 00 96 00 05-00 04 00 15 00 12 00 09   ................
0050 - 00 14 00 11 00 08 00 06-00 03 00 ff 01            .............
005e - <SPACES/NULS>
>>> SSL 3.0 Handshake [length 0059], ClientHello
    01 00 00 55 03 00 59 3d 77 f6 9e ec f1 5d a5 6b
    aa fb 71 f7 ba fe 43 54 55 7b 78 53 c1 98 2d d2
    ee 8a 25 57 6c a1 00 00 2e 00 39 00 38 00 35 00
    16 00 13 00 0a 00 33 00 32 00 2f 00 9a 00 99 00
    96 00 05 00 04 00 15 00 12 00 09 00 14 00 11 00
    08 00 06 00 03 00 ff 01 00
read from 0x7fa113e00150 [0x7fa115006600] (5 bytes => 5 (0x5))
0000 - 15 03 00 00 02                                    .....
read from 0x7fa113e00150 [0x7fa115006605] (2 bytes => 2 (0x2))
0000 - 02 28                                             .(
<<< SSL 3.0 Alert [length 0002], fatal handshake_failure
    02 28
18704:error:14094410:SSL routines:SSL3_READ_BYTES:sslv3 alert handshake failure:/SourceCache/OpenSSL098/OpenSSL098-52/src/ssl/s3_pkt.c:1125:SSL alert number 40
18704:error:1409E0E5:SSL routines:SSL3_WRITE_BYTES:ssl handshake failure:/SourceCache/OpenSSL098/OpenSSL098-52/src/ssl/s3_pkt.c:546:
```

なお、opensslコマンドでの接続に失敗した場合の例についてはこちらを参照のこと
- http://sig9.hatenablog.com/entry/2016/07/03/230000

### ルート証明書を指定する(MACの場合)
認証された機関を表示したい場合には次のようにします。
/usr/local/etc/openssl/cert.pem と/usr/local/etc/openssl/osx_cert.pem で2種類あるようだが違いはよくわかっていない。。
```
$ openssl s_client -connect www.google.com:443 -quiet -CAfile 　
depth=3 /C=US/O=Equifax/OU=Equifax Secure Certificate Authority
verify return:1
depth=2 /C=US/O=GeoTrust Inc./CN=GeoTrust Global CA
verify return:1
depth=1 /C=US/O=Google Inc/CN=Google Internet Authority G2
verify return:1
depth=0 /C=US/ST=California/L=Mountain View/O=Google Inc/CN=www.google.com
verify return:1
```

### 接続先のサーバがOCSP Stapling有効かどうかを確認する
「OCSP Response Data」といった項目がいろいろと表示されたらOCSP Stapling有効のサーバです。
「OCSP response: no response sent」と表示される場合には有効でないサーバです。
```
$ openssl s_client -connect www.example.jp:443 -status -servername www.example.jp < /dev/null | head
depth=1 C = US, O = Let's Encrypt, CN = Let's Encrypt Authority X1
verify error:num=20:unable to get local issuer certificate
verify return:0
CONNECTED(00000003)
OCSP response: 
======================================
OCSP Response Data:
    OCSP Response Status: successful (0x0)
    Response Type: Basic OCSP Response
    Version: 1 (0x0)
    Responder Id: C = US, O = Let's Encrypt, CN = Let's Encrypt Authority X1
    Produced At: Dec 23 14:51:00 2015 GMT
    Responses:
DONE
```

- 参考
  - https://tech.nosuz.jp/2015/12/enable-ocsp-stapling/

### SNIの証明書を確認する
SNIという１つのIPアドレスで複数のSSL証明書を扱う技術を確認するためにはservernameを利用します。
これが指定されないと、サーバ側はデフォルトのSSL証明書を返します。

- servernameが指定されない場合
```
$ openssl s_client -connect help.hipchat.com:443 -showcerts < /dev/null 2>&1 | grep subject
subject=/OU=GT20300774/OU=See www.rapidssl.com/resources/cps (c)15/OU=Domain Control Validated - RapidSSL(R)/CN=*.uservoice.com
```

- servernameが指定される場合(SNIとしてドメインが指定された場合)
```
$ openssl s_client -connect help.hipchat.com:443 -servername help.hipchat.com -showcerts < /dev/null 2>&1 | grep subject
subject=/C=US/L=San Francisco/ST=California/O=Atlassian, Inc./OU=HipChat/CN=help.hipchat.com
```

- SeeAlso
  - https://qiita.com/greymd/items/5d2fc55430105620a550

### 有効期限情報を表示する
```
$ echo | openssl s_client -connect www.yahoo.co.jp:443 2> /dev/null |openssl x509 -dates -noout
notBefore=Oct 16 11:04:19 2017 GMT
notAfter=Nov 15 14:59:00 2018 GMT
```

### セッションがreuseできるかどうかを確認する方法
reconnectオプションで1回目は新規接続、2回目以降はsessionを再利用するといった使い方を確認することができます。
```
$ openssl s_client -reconnect -host www.yahoo.co.jp -port 443 |grep -e "\(Reuse\|New\)" 
depth=1 /C=JP/O=Cybertrust Japan Co., Ltd./CN=Cybertrust Japan Public CA G3
verify error:num=20:unable to get local issuer certificate
verify return:0
New, TLSv1/SSLv3, Cipher is AES128-SHA
depth=1 /C=JP/O=Cybertrust Japan Co., Ltd./CN=Cybertrust Japan Public CA G3
verify error:num=20:unable to get local issuer certificate
verify return:0
New, TLSv1/SSLv3, Cipher is AES128-SHA
Reused, TLSv1/SSLv3, Cipher is AES128-SHA
Reused, TLSv1/SSLv3, Cipher is AES128-SHA
Reused, TLSv1/SSLv3, Cipher is AES128-SHA
Reused, TLSv1/SSLv3, Cipher is AES128-SHA
```

上記だけだと新規接続と再接続時のパラメータの違いを見逃してしまうので出力を記載しておきます。
以下では新規接続(New)が1回、再接続(Reused)が1回呼び出されるところのみを表示しています。Protocol, Cipher, Session-ID, Master-Keyなどが何も変わっていないことが確認できます。
```
$ openssl s_client -reconnect -host www.yahoo.co.jp -port 443 
(snip)
---
SSL handshake has read 5239 bytes and written 415 bytes
---
New, TLSv1/SSLv3, Cipher is ECDHE-RSA-AES128-GCM-SHA256
Server public key is 2048 bit
Secure Renegotiation IS supported
Compression: NONE
Expansion: NONE
No ALPN negotiated
SSL-Session:
    Protocol  : TLSv1.2
    Cipher    : ECDHE-RSA-AES128-GCM-SHA256
    Session-ID: B21ED0649C2A821C9DD6AC9CC18F3ECF2F4AB1891BB4B5BE8AFEB44B39197E9D
    Session-ID-ctx: 
    Master-Key: E9D9697901AC45A5A41F69D890AC1C47279BF056160BA67916B09B53EAF84B961830089E5678D9EED2D185F991E06072
    Key-Arg   : None
    Krb5 Principal: None
    PSK identity: None
    PSK identity hint: None
    TLS session ticket lifetime hint: 7200 (seconds)
    TLS session ticket:
    0000 - 65 64 67 65 2e 65 64 67-65 2e 61 74 73 5f 73 73   edge.edge.ats_ss
    0010 - 39 e8 02 69 42 52 d6 2d-87 7c b8 da 5c db 85 7b   9..iBR.-.|..\..{
    0020 - e4 6b 73 b0 98 03 18 d4-3a 79 36 98 63 84 1b 72   .ks.....:y6.c..r
    0030 - d7 ee 18 b2 83 49 c9 c7-f7 6c a8 c0 03 ba 7c 6a   .....I...l....|j
    0040 - a2 7b 27 42 a7 30 e6 74-18 34 39 01 12 38 73 2c   .{'B.0.t.49..8s,
    0050 - 6b dd 14 99 1a 87 86 7c-99 cf 4a ca d1 cb 9a 1c   k......|..J.....
    0060 - 2e 94 98 de e3 9e 55 2f-16 b9 f8 68 00 17 e6 fb   ......U/...h....
    0070 - 31 7b 02 0d 64 03 92 85-3d 23 a0 29 bb 37 e8 a6   1{..d...=#.).7..
    0080 - b7 40 75 53 47 0b 87 4d-c6 f0 bf 2f 84 c1 8d 9b   .@uSG..M.../....
    0090 - bf c8 97 e3 11 c5 c0 53-66 77 6d 92 47 fe ec 08   .......Sfwm.G...
    00a0 - 1b 79 fb e7 d4 cc cd 75-7b 07 b8 22 cc da f7 eb   .y.....u{.."....
    00b0 - 47 65 52 f0 38 c6 45 9c-b3 51 25 43 67 66 92 58   GeR.8.E..Q%Cgf.X

    Start Time: 1516424835
    Timeout   : 300 (sec)
    Verify return code: 9 (certificate is not yet valid)
---
drop connection and then reconnect
CONNECTED(00000003)
---
Reused, TLSv1/SSLv3, Cipher is ECDHE-RSA-AES128-GCM-SHA256
Secure Renegotiation IS supported
Compression: NONE
Expansion: NONE
No ALPN negotiated
SSL-Session:
    Protocol  : TLSv1.2
    Cipher    : ECDHE-RSA-AES128-GCM-SHA256
    Session-ID: B21ED0649C2A821C9DD6AC9CC18F3ECF2F4AB1891BB4B5BE8AFEB44B39197E9D
    Session-ID-ctx: 
    Master-Key: E9D9697901AC45A5A41F69D890AC1C47279BF056160BA67916B09B53EAF84B961830089E5678D9EED2D185F991E06072
    Key-Arg   : None
    Krb5 Principal: None
    PSK identity: None
    PSK identity hint: None
    TLS session ticket lifetime hint: 7200 (seconds)
    TLS session ticket:
    0000 - 65 64 67 65 2e 65 64 67-65 2e 61 74 73 5f 73 73   edge.edge.ats_ss
    0010 - 39 e8 02 69 42 52 d6 2d-87 7c b8 da 5c db 85 7b   9..iBR.-.|..\..{
    0020 - e4 6b 73 b0 98 03 18 d4-3a 79 36 98 63 84 1b 72   .ks.....:y6.c..r
    0030 - d7 ee 18 b2 83 49 c9 c7-f7 6c a8 c0 03 ba 7c 6a   .....I...l....|j
    0040 - a2 7b 27 42 a7 30 e6 74-18 34 39 01 12 38 73 2c   .{'B.0.t.49..8s,
    0050 - 6b dd 14 99 1a 87 86 7c-99 cf 4a ca d1 cb 9a 1c   k......|..J.....
    0060 - 2e 94 98 de e3 9e 55 2f-16 b9 f8 68 00 17 e6 fb   ......U/...h....
    0070 - 31 7b 02 0d 64 03 92 85-3d 23 a0 29 bb 37 e8 a6   1{..d...=#.).7..
    0080 - b7 40 75 53 47 0b 87 4d-c6 f0 bf 2f 84 c1 8d 9b   .@uSG..M.../....
    0090 - bf c8 97 e3 11 c5 c0 53-66 77 6d 92 47 fe ec 08   .......Sfwm.G...
    00a0 - 1b 79 fb e7 d4 cc cd 75-7b 07 b8 22 cc da f7 eb   .y.....u{.."....
    00b0 - 47 65 52 f0 38 c6 45 9c-b3 51 25 43 67 66 92 58   GeR.8.E..Q%Cgf.X

    Start Time: 1516424835
    Timeout   : 300 (sec)
    Verify return code: 9 (certificate is not yet valid)
(残り4回ほどreusedが続くので省略)
```


