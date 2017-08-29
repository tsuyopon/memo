# 概要
この辺を参考にする。
- http://www.usupi.org/sysad/252.html

# 詳細

### 秘密鍵とサーバ証明書を作成する(超簡易版)
実行結果については後で詳細を載せます。次のコマンドで秘密鍵server.keyを作成し、keyを元にCSRを作成し、CSRをCAに渡してサーバ証明書CRTを発行します。
```
$ openssl genrsa -des3 -out server.key 2048
$ openssl req -new -key server.key -out server.csr
$ openssl x509 -req -days 365 -in server.csr -signkey server.key -out server.crt
```
これらについての実行結果詳細は次の「鍵生成を行いopensslサーバを起動する」で載せています。

### 鍵生成を行いopensslサーバを起動する
公開鍵の改竄を防ぐため、認証局(Certification Authority, CA) というところで署名してもらいます。これが、サーバ証明書(Certificate, CRT)です。  

鍵を作成します。RSA(genrsa)とDSA(gendsa)の２つを指定できますがここではgenrsaを指定しています。(gendsaの場合には参考URLを参照のこと)
また、トリプルDESで2048bitの鍵をserver.keyとして出力するように指定している。
```
$ openssl genrsa -des3 -out server.key 2048
Generating RSA private key, 2048 bit long modulus
....................................+++
...中略...
e is 65537 (0x10001)
Enter pass phrase for server.key: (パスフレーズを入力)
Verifying - Enter pass phrase for server.key: (再度同じのを入力)
```

鍵(server.key)をそのまま配置しておくのは危険なために、上記では共通鍵で暗号化を行っています。  
このためのオプションが「-des」「-des3」、「-idea」としてます。

次に、公開鍵を CA で署名してもらって、CRTを作ります。  
CRTを作る際に署名をお願いするときに必要なファイルが、 証明書発行要求(Certificate Signing Request, CSR)です。 

```
$ openssl req -new -key server.key -out server.csr
Enter pass phrase for server.key: (先ほど入力したパスフレーズ)
...中略...
Country Name (2 letter code) [AU]:JP
State or Province Name (full name) [Some-State]:Aichi-ken
Locality Name (eg, city) []:Nagoya-shi
...後略...
```

ここで信頼ある機関に「server.csr」を署名してもらう必要がありますが、お金がかかるので自分で署名します。
server.csrを元にして、server.crtを生成します。
```
$ openssl x509 -req -days 365 -in server.csr -signkey server.key -out server.crt
Signature ok
subject=/C=JP/ST=Aichi-ken/L=Nagoya-shi/O=Hoge Company/OU=Dev/CN=usupi.org/emailAddress=usu@usupi.org
Getting Private key
Enter pass phrase for server.key: (先ほど入力したパスフレーズ)
```
「-req」オプションで、CRTの生成をお願いします。 「-days」オプションで、有効期限を日数で指定します。  
そして、「-in」オプションでCSR、「-signkey」オプションで署名に使う鍵、 「-out」オプションで出力ファイル名を指定しています。 

CSR が問題ないか確認するには、「-verify」オプションを使います。 
```
$ openssl req -in server.csr -verify -noout
verify OK
```

以上でSSLサーバに必要な鍵の準備は整いました。
opensslコマンドでサーバ起動やクライアント稼働として可能です。
```
$ openssl s_server -accept 14433 -cert server.crt -key server.key
Enter pass phrase for server.key:       // キーのパスフレーズを入力する
Using default temp DH parameters
ACCEPT
```

あらかじめダンプコマンドを実行します。
```
$ sudo ssldump -a -A -H -k server.key -i lo
```

SSLクライアントで14433ポートにリクエストする。
```
$  openssl s_client -connect localhost:14433 
CONNECTED(00000003)
depth=0 C = AA, ST = aa, L = aa, O = Default Company Ltd
verify error:num=18:self signed certificate
verify return:1
depth=0 C = AA, ST = aa, L = aa, O = Default Company Ltd
verify return:1
---
Certificate chain
 0 s:/C=AA/ST=aa/L=aa/O=Default Company Ltd
   i:/C=AA/ST=aa/L=aa/O=Default Company Ltd
---
Server certificate
-----BEGIN CERTIFICATE-----
MIIEaDCCBBACCQDacd1QWDhCATAJBgcqhkjOOAQDMEUxCzAJBgNVBAYTAkFBMQsw
(...)
-----END CERTIFICATE-----
subject=/C=AA/ST=aa/L=aa/O=Default Company Ltd
issuer=/C=AA/ST=aa/L=aa/O=Default Company Ltd
---
No client certificate CA names sent
---
SSL handshake has read 1664 bytes and written 246 bytes
---
New, TLSv1/SSLv3, Cipher is DHE-DSS-AES256-SHA
Server public key is 2048 bit
Secure Renegotiation IS supported
Compression: NONE
Expansion: NONE
SSL-Session:
    Protocol  : TLSv1
    Cipher    : DHE-DSS-AES256-SHA
    Session-ID: 7C9DB0C04B6566309D8779EFFB77D18EC695123DAF445200FCDE845A6FCA01F4
    Session-ID-ctx: 
    Master-Key: 789E1E8A9E29BB782FD87D00AB29D1A75B29ECD2F2B62B8007B160D8DE0296438503936D94F5B585369FEB21CCEBAC75
    Key-Arg   : None
    Krb5 Principal: None
    PSK identity: None
    PSK identity hint: None
    TLS session ticket:
    0000 - 69 25 c1 c6 99 d4 dc 76-4d 4a 19 46 eb db 79 ea   i%.....vMJ.F..y.
    0010 - 7a 92 56 af dc 25 d4 8c-be ba f0 95 ac 3f ec 73   z.V..%.......?.s
    0020 - d2 1f 53 01 43 f7 b5 f3-63 eb 05 86 e8 76 ce 65   ..S.C...c....v.e
    0030 - 56 b5 da c1 af 23 27 d3-dd 08 2f 97 8f ad 5a ba   V....#'.../...Z.
    0040 - 99 59 51 be d6 5a fc 7b-c5 1f da d2 68 61 97 49   .YQ..Z.{....ha.I
    0050 - e4 79 f4 c5 47 5a 47 f8-17 e1 50 27 a0 5e 10 25   .y..GZG...P'.^.%
    0060 - 79 95 8b 20 e7 4b 94 10-1e d6 ae 06 fd cb f6 08   y.. .K..........
    0070 - 19 3d b9 05 6c ca 6f 30-b1 20 da 53 f1 98 48 7f   .=..l.o0. .S..H.
    0080 - cc 4d dd 1d 86 0e 3e 6e-cd c8 ee 3c d8 14 69 b0   .M....>n...<..i.
    0090 - 6d e3 99 c5 e9 33 a4 3b-57 26 b3 e8 bb f7 f0      m....3.;W&.....
    00a0 - <SPACES/NULS>

    Start Time: 1478979164
    Timeout   : 300 (sec)
    Verify return code: 18 (self signed certificate)
---

```

先ほどダンプした結果には次のように出力されます。
```
$ sudo ssldump -a -A -H -k server.key -i lo
Enter PEM pass phrase:       //キーのパスフレーズを入力する
New TCP connection #1: localhost.localdomain(50423) <-> localhost.localdomain(14433)
1 1  0.0019 (0.0019)  C>S V3.1(107)  Handshake
      ClientHello
        Version 3.1 
        random[32]=
          58 27 6d e1 93 59 8f 8b e3 a3 c5 3b bc 62 77 e2 
          a1 02 c3 d5 e7 8a ce 43 23 47 4c 9e 00 9b fa 28 
        cipher suites
        TLS_DHE_RSA_WITH_AES_256_CBC_SHA
        TLS_DHE_DSS_WITH_AES_256_CBC_SHA
        Unknown value 0x88
        Unknown value 0x87
        TLS_RSA_WITH_AES_256_CBC_SHA
        Unknown value 0x84
        TLS_DHE_RSA_WITH_3DES_EDE_CBC_SHA
        TLS_DHE_DSS_WITH_3DES_EDE_CBC_SHA
        TLS_RSA_WITH_3DES_EDE_CBC_SHA
        TLS_DHE_RSA_WITH_AES_128_CBC_SHA
        TLS_DHE_DSS_WITH_AES_128_CBC_SHA
        Unknown value 0x9a
        Unknown value 0x99
        Unknown value 0x45
        Unknown value 0x44
        TLS_RSA_WITH_AES_128_CBC_SHA
        Unknown value 0x96
        Unknown value 0x41
        TLS_RSA_WITH_RC4_128_SHA
        TLS_RSA_WITH_RC4_128_MD5
        TLS_DHE_RSA_WITH_DES_CBC_SHA
        TLS_DHE_DSS_WITH_DES_CBC_SHA
        TLS_RSA_WITH_DES_CBC_SHA
        TLS_DHE_RSA_EXPORT_WITH_DES40_CBC_SHA
        TLS_DHE_DSS_EXPORT_WITH_DES40_CBC_SHA
        TLS_RSA_EXPORT_WITH_DES40_CBC_SHA
        TLS_RSA_EXPORT_WITH_RC2_CBC_40_MD5
        TLS_RSA_EXPORT_WITH_RC4_40_MD5
        Unknown value 0xff
        compression methods
                  NULL
1 2  0.0027 (0.0008)  S>C V3.1(53)  Handshake
      ServerHello
        Version 3.1 
        random[32]=
          58 27 6d e1 e5 b1 89 69 27 ff 0d ef ec ab 73 82 
          8b 04 ef bd 2b 11 9b 68 56 69 ee f2 03 6c d1 5a 
        session_id[0]=

        cipherSuite         TLS_DHE_DSS_WITH_AES_256_CBC_SHA
        compressionMethod                   NULL
1 3  0.0027 (0.0000)  S>C V3.1(1142)  Handshake
      Certificate
1 4  0.0027 (0.0000)  S>C V3.1(212)  Handshake
      ServerKeyExchange
        params
          DH_p[64]=
            da 58 3c 16 d9 85 22 89 d0 e4 af 75 6f 4c ca 92 
            dd 4b e5 33 b8 04 fb 0f ed 94 ef 9c 8a 44 03 ed 
            57 46 50 d3 69 99 db 29 d7 76 27 6b a2 d3 d4 12 
            e2 18 f4 dd 1e 08 4c f6 d8 00 3e 7c 47 74 e8 33 
          DH_g[1]=
            02 
          DH_Ys[64]=
            05 b4 65 49 1e e2 b8 34 c5 1d a6 0f 61 51 20 33 
            53 c3 b1 c8 05 c3 aa c4 f0 22 47 9b ee 72 3a b8 
            d9 a7 81 8a d9 2f f1 ae 26 35 dc 91 3d 78 26 08 
            34 d6 8f f2 1c 7c 95 2c 7f 57 02 d4 f8 02 1c b7 
        signature[71]=
          30 45 02 21 00 91 b2 8d b4 6c 6c ed b5 4d e9 8f 
          4b 76 f7 e5 42 7f ac e5 1d 2b a5 97 1c 0b 47 ab 
          24 6a 0d 7a 9b 02 20 3e 36 47 cb bc 69 f3 45 05 
          37 1f f8 67 cd 86 ba f0 c1 49 35 28 da 98 67 4d 
          33 c4 eb 34 d5 9d 66 
1 5  0.0027 (0.0000)  S>C V3.1(4)  Handshake
      ServerHelloDone
1 6  0.0174 (0.0146)  C>S V3.1(70)  Handshake
      ClientKeyExchange
        DiffieHellmanClientPublicValue[64]=
          60 72 03 89 82 8d ea b9 13 27 5c de d4 fc 05 44 
          13 f1 df f8 05 88 d7 8c 72 4c f8 8e a0 4d a3 d5 
          d0 9f 9e f7 de f8 7f 04 f9 80 2a b3 7d 81 1b 1f 
          26 a2 dc 9a c8 54 1e 80 a4 83 a6 da a9 a5 24 ec 
1 7  0.0174 (0.0000)  C>S V3.1(1)  ChangeCipherSpec
1 8  0.0174 (0.0000)  C>S V3.1(48)  Handshake
1 9  0.0179 (0.0005)  S>C V3.1(170)  Handshake
1 10 0.0179 (0.0000)  S>C V3.1(1)  ChangeCipherSpec
1 11 0.0179 (0.0000)  S>C V3.1(48)  Handshake
```


そのままだと CSR の中身も出力されますので、 「-noout」オプションを指定して阻止しています。
「-text」オプションを指定すると、CSR の中身をわかりやすく出力してくれます。 
```
$ openssl req -in server.csr -text -noout
Certificate Request:
    Data:
        Version: 0 (0x0)
        Subject: C=AA, ST=aa, L=aa, O=Default Company Ltd
        Subject Public Key Info:
            Public Key Algorithm: dsaEncryption
                pub: 
                    00:c4:09:42:3d:df:6e:b3:d3:00:9a:28:27:c5:f6:
                    (...)
                P:   
                    00:ee:75:4d:96:b7:b5:55:c8:f2:18:48:16:27:3a:
                    (...)
                Q:   
                    00:b1:75:5f:e1:37:a0:ed:22:11:8f:08:33:1d:83:
                    (...)
                G:   
                    00:bd:73:c1:5c:e1:e2:66:51:d3:58:5f:d2:0c:95:
                    (...)
        Attributes:
            a0:00
    Signature Algorithm: dsaWithSHA1
        30:44:02:20:4b:4e:c0:a3:de:bb:48:a7:84:f1:ae:df:b2:00:
        (...)
```

```
$ openssl x509 -in server.crt -text -noout
Certificate:
    Data:
        Version: 1 (0x0)
        Serial Number:
            da:71:dd:50:58:38:42:01
        Signature Algorithm: dsaWithSHA1
        Issuer: C=AA, ST=aa, L=aa, O=Default Company Ltd
        Validity
            Not Before: Nov 12 19:19:11 2016 GMT
            Not After : Nov 12 19:19:11 2017 GMT
        Subject: C=AA, ST=aa, L=aa, O=Default Company Ltd
        Subject Public Key Info:
            Public Key Algorithm: dsaEncryption
                pub: 
                    00:c4:09:42:3d:df:6e:b3:d3:00:9a:28:27:c5:f6:
                    (...)
                P:   
                    00:ee:75:4d:96:b7:b5:55:c8:f2:18:48:16:27:3a:
                    (...)
                Q:   
                    00:b1:75:5f:e1:37:a0:ed:22:11:8f:08:33:1d:83:
                    (...)
                G:   
                    00:bd:73:c1:5c:e1:e2:66:51:d3:58:5f:d2:0c:95:
                    (...)
    Signature Algorithm: dsaWithSHA1
        30:44:02:20:3d:ed:e8:06:22:8c:74:86:dc:9a:26:1e:63:37:
        (...)

```

### 証明書の内容を表示する
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


### パケット内容詳細も取得する
debugオプションを付与するとパケット内容の詳細も表示する。
```
$ openssl s_client -connect shopping.yahoo.co.jp:443  -debug
...
0000 - 0b 00 09 bf 00 09 bc 00-05 49 30 82 05 45 30 82   .........I0..E0.
0010 - 04 2d a0 03 02 01 02 02-0c 44 a4 0f 87 fe 4d dd   .-.......D....M.
...
```

### SSL/TLSバージョンを切り替える
```
$ openssl s_client -connect EXAMPLE.LOCAL:443 -ssl2
$ openssl s_client -connect EXAMPLE.LOCAL:443 -ssl3
$ openssl s_client -connect EXAMPLE.LOCAL:443 -tls1
$ openssl s_client -connect EXAMPLE.LOCAL:443 -tls1_1
$ openssl s_client -connect EXAMPLE.LOCAL:443 -tls1_2
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

### 秘密鍵の内容を確認する
```
$  openssl rsa -text -noout -in server.key 
Private-Key: (2048 bit)
modulus:
    00:dc:d4:78:45:af:ec:78:66:d7:6a:04:6f:58:7e:
    cc:3a:d2:a6:3b:37:78:62:02:bd:3c:80:cc:2d:8a:
    55:83:1c:10:43:3b:50:6e:6d:f2:69:c6:06:b7:fd:
    02:21:55:d4:e9:e4:ad:30:6e:f7:e6:7c:0d:71:89:
    92:a3:cc:73:e2:2f:c8:12:48:37:4c:f5:dc:3f:2e:
    28:3a:d5:41:45:19:80:6c:61:f7:2c:6b:d9:27:5b:
    a8:1d:a6:ee:5d:5d:fd:99:34:cf:1d:f8:ab:c5:12:
    52:0f:6b:72:70:37:a8:4c:d6:39:a0:b0:24:ca:07:
    c6:48:00:f2:b2:87:6d:fd:30:d8:59:c4:0a:7d:ae:
    29:00:30:e0:f5:d6:1a:59:6c:13:43:2a:96:e2:5c:
    cd:57:1c:42:3f:83:29:9d:5d:6d:b6:65:f9:fe:87:
    d1:51:49:83:57:3a:eb:31:7f:bd:8b:72:0f:84:3c:
    73:e3:f9:25:e3:af:45:2d:ef:40:03:77:d7:a2:af:
    2c:da:72:36:2d:ea:0c:d9:e7:40:55:8d:24:57:f9:
    54:6f:b2:16:63:75:61:b7:73:5a:b1:6d:5f:2e:2e:
    27:bd:74:7f:e8:30:2b:92:d3:9c:17:2f:d3:31:e9:
    b2:63:37:6c:8e:72:49:7d:e5:6b:a8:35:f1:72:88:
    99:4d
publicExponent: 65537 (0x10001)
privateExponent:

```

### 署名する
一般的に1をよく使うのでこれだけ覚えておけば十分かも。2や3はこんなこともできるんだ程度に見ておけば良い。

1. 自分の秘密鍵で自己署名した証明書を作成する
```
openssl x509 -in server.csr -out server.crt -req -signkey server.key -days 365
```

2. 秘密鍵作成,CSR作成,自己署名を一度にする(秘密鍵を暗号化しない)
```
$ openssl req -x509 -nodes -new -keyout server.key -out server.crt -days 365
```

3. 秘密鍵作成,CSR作成,自己署名を一度にする(秘密鍵を暗号化する)
```
$ openssl req -x509 -new -keyout server.key -out server.crt -days 365
```


### 証明書の内容を確認する

以下の３つはコマンドが似ているので一応整理も含めて載せておく。

証明書ファイルの内容を確認
```
$ sudo openssl x509 -text -noout -in <証明書>
```

秘密鍵ファイルの内容を確認
```
$ sudo openssl rsa -text -noout -in <秘密鍵>
```

CSRファイルの内容を確認
```
$ sudo  openssl req -text -noout -in <CSR>
```

### 証明書の使用目的を表示
```
$ openssl x509 -in server.crt -purpose
```

### ASN.1形式で表示
```
$ openssl asn1parse -in server.crt
```

### 証明書から公開鍵を取り出す
```
$ openssl x509 -in server.crt -pubkey -noout
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
```

sha1は次のように算出できる。
```
$ openssl sha1 server.key 
SHA1(server.key)= c5794c3d0c3b0edc8d5c07800f939dc86e939eac
```

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

### サーバがOCSP Stapling有効かどうかを確認する
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

### .crtから.pemに変換する
もちろん逆もできる
```
$ openssl x509 -in source.crt -out tmp.der -outform DER
$ openssl x509 -in tmp.der -inform DER -out dest.pem -outform pem
```

### 秘密鍵と公開鍵からp12形式を取得する
```
$ openssl pkcs12 -export -inkey server.key -in server.crt -out server.p12
```

### PKCS#12形式(pfx or p12)から証明書を取り出す
```
$ openssl pkcs12 -nokeys -in cert.der.pfx -out cert.crt.pem
or
$ openssl pkcs12 -nokeys -in cert.der.p12 -out cert.crt.pem
```

### PKCS#12形式(pfx or p12)から秘密鍵を取り出す
```
$ openssl pkcs12 -nocerts -in cert.der.pfx -out private.key.pem
or
$ openssl pkcs12 -nocerts -in cert.der.p12 -out private.key.pem
```

### 証明書の失効処理を行う
証明書の失効処理を行う
```
$ openssl ca -revoke newcerts/01.pem
```

CRLの生成を行う
```
$ openssl ca -gencrl -out CA.crl
```

CRLの内容を確認する
```
$ openssl crl -in CA.crl -text
```

### 証明書ファイルと秘密鍵ファイルの整合性を確認する
次の２つのコマンドの結果を確認することで一致すれば整合性があることを表しています。
```
$ sudo openssl x509 -noout -modulus -in 証明書ファイル | md5sum
$ sudo openssl rsa -noout -modulus -in 秘密鍵ファイル | md5sum
```

### opensslヘルプ
第１引数が間違っていると第１引数に指定するヘルプを表示する。
```
$ openssl -h
openssl:Error: '-h' is an invalid command.

Standard commands
asn1parse      ca             ciphers        crl            crl2pkcs7      
dgst           dh             dhparam        dsa            dsaparam       
ec             ecparam        enc            engine         errstr         
gendh          gendsa         genrsa         nseq           ocsp           
passwd         pkcs12         pkcs7          pkcs8          prime          
rand           req            rsa            rsautl         s_client       
s_server       s_time         sess_id        smime          speed          
spkac          verify         version        x509           

Message Digest commands (see the `dgst' command for more details)
md2            md4            md5            mdc2           rmd160         
sha            sha1           

Cipher commands (see the `enc' command for more details)
aes-128-cbc    aes-128-ecb    aes-192-cbc    aes-192-ecb    aes-256-cbc    
aes-256-ecb    base64         bf             bf-cbc         bf-cfb         
bf-ecb         bf-ofb         cast           cast-cbc       cast5-cbc      
cast5-cfb      cast5-ecb      cast5-ofb      des            des-cbc        
des-cfb        des-ecb        des-ede        des-ede-cbc    des-ede-cfb    
des-ede-ofb    des-ede3       des-ede3-cbc   des-ede3-cfb   des-ede3-ofb   
des-ofb        des3           desx           rc2            rc2-40-cbc     
rc2-64-cbc     rc2-cbc        rc2-cfb        rc2-ecb        rc2-ofb        
rc4            rc4-40         rc5            rc5-cbc        rc5-cfb        
rc5-ecb        rc5-ofb        seed           seed-cbc       seed-cfb       
seed-ecb       seed-ofb       
```

第２引数が間違っていると第２引数に指定できるヘルプを表示する。
```
$ openssl s_client -help
unknown option -help
usage: s_client args

 -host host     - use -connect instead
 -port port     - use -connect instead
 -connect host:port - who to connect to (default is localhost:4433)
 -verify depth - turn on peer certificate verification
 -cert arg     - certificate file to use, PEM format assumed
 -certform arg - certificate format (PEM or DER) PEM default
 -key arg      - Private key file to use, in cert file if
                 not specified but cert file is.
 -keyform arg  - key format (PEM or DER) PEM default
 -pass arg     - private key file pass phrase source
 -CApath arg   - PEM format directory of CA's
 -CAfile arg   - PEM format file of CA's
 -reconnect    - Drop and re-make the connection with the same Session-ID
 -pause        - sleep(1) after each read(2) and write(2) system call
 -showcerts    - show all certificates in the chain
 -debug        - extra output
 -msg          - Show protocol messages
 -nbio_test    - more ssl protocol testing
 -state        - print the 'ssl' states
 -nbio         - Run with non-blocking IO
 -crlf         - convert LF from terminal into CRLF
 -quiet        - no s_client output
 -ign_eof      - ignore input eof (default when -quiet)
 -no_ign_eof   - don't ignore input eof
 -ssl2         - just use SSLv2
 -ssl3         - just use SSLv3
 -tls1         - just use TLSv1
 -dtls1        - just use DTLSv1
 -mtu          - set the link layer MTU
 -no_tls1/-no_ssl3/-no_ssl2 - turn off that protocol
 -bugs         - Switch on all SSL implementation bug workarounds
 -serverpref   - Use server's cipher preferences (only SSLv2)
 -cipher       - preferred cipher to use, use the 'openssl ciphers'
                 command to see what is available
 -starttls prot - use the STARTTLS command before starting TLS
                 for those protocols that support it, where
                 'prot' defines which one to assume.  Currently,
                 only "smtp", "pop3", "imap", "ftp" and "xmpp"
                 are supported.
 -engine id    - Initialise and use the specified engine
 -rand file:file:...
 -sess_out arg - file to write SSL session to
 -sess_in arg  - file to read SSL session from
 -servername host  - Set TLS extension servername in ClientHello
 -tlsextdebug      - hex dump of all TLS extensions received
 -status           - request certificate status from server
 -no_ticket        - disable use of RFC4507bis session tickets
 -legacy_renegotiation - enable use of legacy renegotiation (dangerous)
```

# TODO
この辺にたくさんのopensslコマンドが乗っているのでまとめたい
- http://assimane.blog.so-net.ne.jp/2011-09-24
- http://qiita.com/takech9203/items/5206f8e2572e95209bbc

上記コマンドに実行例を載せておきたい

### opensslで利用可能なアルゴリズムを表示する
```
$ openssl ciphers -v
DHE-RSA-AES256-SHA      SSLv3 Kx=DH       Au=RSA  Enc=AES(256)  Mac=SHA1
DHE-DSS-AES256-SHA      SSLv3 Kx=DH       Au=DSS  Enc=AES(256)  Mac=SHA1
AES256-SHA              SSLv3 Kx=RSA      Au=RSA  Enc=AES(256)  Mac=SHA1
EDH-RSA-DES-CBC3-SHA    SSLv3 Kx=DH       Au=RSA  Enc=3DES(168) Mac=SHA1
EDH-DSS-DES-CBC3-SHA    SSLv3 Kx=DH       Au=DSS  Enc=3DES(168) Mac=SHA1
DES-CBC3-SHA            SSLv3 Kx=RSA      Au=RSA  Enc=3DES(168) Mac=SHA1
DES-CBC3-MD5            SSLv2 Kx=RSA      Au=RSA  Enc=3DES(168) Mac=MD5 
DHE-RSA-AES128-SHA      SSLv3 Kx=DH       Au=RSA  Enc=AES(128)  Mac=SHA1
DHE-DSS-AES128-SHA      SSLv3 Kx=DH       Au=DSS  Enc=AES(128)  Mac=SHA1
AES128-SHA              SSLv3 Kx=RSA      Au=RSA  Enc=AES(128)  Mac=SHA1
DHE-RSA-SEED-SHA        SSLv3 Kx=DH       Au=RSA  Enc=SEED(128) Mac=SHA1
DHE-DSS-SEED-SHA        SSLv3 Kx=DH       Au=DSS  Enc=SEED(128) Mac=SHA1
SEED-SHA                SSLv3 Kx=RSA      Au=RSA  Enc=SEED(128) Mac=SHA1
RC2-CBC-MD5             SSLv2 Kx=RSA      Au=RSA  Enc=RC2(128)  Mac=MD5 
RC4-SHA                 SSLv3 Kx=RSA      Au=RSA  Enc=RC4(128)  Mac=SHA1
RC4-MD5                 SSLv3 Kx=RSA      Au=RSA  Enc=RC4(128)  Mac=MD5 
RC4-MD5                 SSLv2 Kx=RSA      Au=RSA  Enc=RC4(128)  Mac=MD5 
EDH-RSA-DES-CBC-SHA     SSLv3 Kx=DH       Au=RSA  Enc=DES(56)   Mac=SHA1
EDH-DSS-DES-CBC-SHA     SSLv3 Kx=DH       Au=DSS  Enc=DES(56)   Mac=SHA1
DES-CBC-SHA             SSLv3 Kx=RSA      Au=RSA  Enc=DES(56)   Mac=SHA1
DES-CBC-MD5             SSLv2 Kx=RSA      Au=RSA  Enc=DES(56)   Mac=MD5 
EXP-EDH-RSA-DES-CBC-SHA SSLv3 Kx=DH(512)  Au=RSA  Enc=DES(40)   Mac=SHA1 export
EXP-EDH-DSS-DES-CBC-SHA SSLv3 Kx=DH(512)  Au=DSS  Enc=DES(40)   Mac=SHA1 export
EXP-DES-CBC-SHA         SSLv3 Kx=RSA(512) Au=RSA  Enc=DES(40)   Mac=SHA1 export
EXP-RC2-CBC-MD5         SSLv3 Kx=RSA(512) Au=RSA  Enc=RC2(40)   Mac=MD5  export
EXP-RC2-CBC-MD5         SSLv2 Kx=RSA(512) Au=RSA  Enc=RC2(40)   Mac=MD5  export
EXP-RC4-MD5             SSLv3 Kx=RSA(512) Au=RSA  Enc=RC4(40)   Mac=MD5  export
EXP-RC4-MD5             SSLv2 Kx=RSA(512) Au=RSA  Enc=RC4(40)   Mac=MD5  export
```

設定値などは次のように記述されることが多い
```
$ openssl ciphers -v 'aRSA+kRSA+AES:aRSA+kRSA+RC4:!EXP:!LOW:!SSLv2:!MD5'
AES256-SHA              SSLv3 Kx=RSA      Au=RSA  Enc=AES(256)  Mac=SHA1
AES128-SHA              SSLv3 Kx=RSA      Au=RSA  Enc=AES(128)  Mac=SHA1
RC4-SHA                 SSLv3 Kx=RSA      Au=RSA  Enc=RC4(128)  Mac=SHA1
```

強度の強い順番で表示する
```
$ openssl ciphers ALL:@STRENGTH -v
ADH-AES256-SHA          SSLv3 Kx=DH       Au=None Enc=AES(256)  Mac=SHA1
DHE-RSA-AES256-SHA      SSLv3 Kx=DH       Au=RSA  Enc=AES(256)  Mac=SHA1
DHE-DSS-AES256-SHA      SSLv3 Kx=DH       Au=DSS  Enc=AES(256)  Mac=SHA1
AES256-SHA              SSLv3 Kx=RSA      Au=RSA  Enc=AES(256)  Mac=SHA1
ADH-DES-CBC3-SHA        SSLv3 Kx=DH       Au=None Enc=3DES(168) Mac=SHA1
EDH-RSA-DES-CBC3-SHA    SSLv3 Kx=DH       Au=RSA  Enc=3DES(168) Mac=SHA1
EDH-DSS-DES-CBC3-SHA    SSLv3 Kx=DH       Au=DSS  Enc=3DES(168) Mac=SHA1
DES-CBC3-SHA            SSLv3 Kx=RSA      Au=RSA  Enc=3DES(168) Mac=SHA1
DES-CBC3-MD5            SSLv2 Kx=RSA      Au=RSA  Enc=3DES(168) Mac=MD5 
ADH-SEED-SHA            SSLv3 Kx=DH       Au=None Enc=SEED(128) Mac=SHA1
DHE-RSA-SEED-SHA        SSLv3 Kx=DH       Au=RSA  Enc=SEED(128) Mac=SHA1
DHE-DSS-SEED-SHA        SSLv3 Kx=DH       Au=DSS  Enc=SEED(128) Mac=SHA1
SEED-SHA                SSLv3 Kx=RSA      Au=RSA  Enc=SEED(128) Mac=SHA1
ADH-AES128-SHA          SSLv3 Kx=DH       Au=None Enc=AES(128)  Mac=SHA1
DHE-RSA-AES128-SHA      SSLv3 Kx=DH       Au=RSA  Enc=AES(128)  Mac=SHA1
DHE-DSS-AES128-SHA      SSLv3 Kx=DH       Au=DSS  Enc=AES(128)  Mac=SHA1
AES128-SHA              SSLv3 Kx=RSA      Au=RSA  Enc=AES(128)  Mac=SHA1
ADH-RC4-MD5             SSLv3 Kx=DH       Au=None Enc=RC4(128)  Mac=MD5 
RC4-SHA                 SSLv3 Kx=RSA      Au=RSA  Enc=RC4(128)  Mac=SHA1
RC4-MD5                 SSLv3 Kx=RSA      Au=RSA  Enc=RC4(128)  Mac=MD5 
RC2-CBC-MD5             SSLv2 Kx=RSA      Au=RSA  Enc=RC2(128)  Mac=MD5 
RC4-MD5                 SSLv2 Kx=RSA      Au=RSA  Enc=RC4(128)  Mac=MD5 
ADH-DES-CBC-SHA         SSLv3 Kx=DH       Au=None Enc=DES(56)   Mac=SHA1
EDH-RSA-DES-CBC-SHA     SSLv3 Kx=DH       Au=RSA  Enc=DES(56)   Mac=SHA1
EDH-DSS-DES-CBC-SHA     SSLv3 Kx=DH       Au=DSS  Enc=DES(56)   Mac=SHA1
DES-CBC-SHA             SSLv3 Kx=RSA      Au=RSA  Enc=DES(56)   Mac=SHA1
DES-CBC-MD5             SSLv2 Kx=RSA      Au=RSA  Enc=DES(56)   Mac=MD5 
EXP-ADH-DES-CBC-SHA     SSLv3 Kx=DH(512)  Au=None Enc=DES(40)   Mac=SHA1 export
EXP-ADH-RC4-MD5         SSLv3 Kx=DH(512)  Au=None Enc=RC4(40)   Mac=MD5  export
EXP-EDH-RSA-DES-CBC-SHA SSLv3 Kx=DH(512)  Au=RSA  Enc=DES(40)   Mac=SHA1 export
EXP-EDH-DSS-DES-CBC-SHA SSLv3 Kx=DH(512)  Au=DSS  Enc=DES(40)   Mac=SHA1 export
EXP-DES-CBC-SHA         SSLv3 Kx=RSA(512) Au=RSA  Enc=DES(40)   Mac=SHA1 export
EXP-RC2-CBC-MD5         SSLv3 Kx=RSA(512) Au=RSA  Enc=RC2(40)   Mac=MD5  export
EXP-RC4-MD5             SSLv3 Kx=RSA(512) Au=RSA  Enc=RC4(40)   Mac=MD5  export
EXP-RC2-CBC-MD5         SSLv2 Kx=RSA(512) Au=RSA  Enc=RC2(40)   Mac=MD5  export
EXP-RC4-MD5             SSLv2 Kx=RSA(512) Au=RSA  Enc=RC4(40)   Mac=MD5  export
```

# 参考URL
- http://www.usupi.org/sysad/252.html
- http://d.hatena.ne.jp/blooper/20120910/1347285980