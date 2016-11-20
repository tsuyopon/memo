# 概要
この辺を参考にする。
- http://www.usupi.org/sysad/252.html


# 詳細

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



# 参考URL
- http://www.usupi.org/sysad/252.html
- http://d.hatena.ne.jp/blooper/20120910/1347285980
