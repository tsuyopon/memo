# 概要
ssldumpコマンドについてまとめておく

# インストール
ssldumpの場合にはlibpcapを必要とする。
ハンドシェイクを確認したいだけであれば単純に以下のようにパッケージをインストールすることで可能です。
```
$ sudo yum install ssldump
```

ただし、ssldumpは古いので最新版のTLS1.1やTLS1.2では解読できないらしい。
おそらくこの辺の問題??
- https://sourceforge.net/p/ssldump/patches/8/

以下ではpatchがあたったレポジトリがあるのでこちらを使うと良い。
- https://github.com/adulau/ssldump

```
$ git clone https://github.com/adulau/ssldump.git
$ cd ssldump
$ ./configure
$ ./make
$ file ssldump     // ここにELFバイナリが生成されます。
```

# 詳細

### 利用パターン
```
$ sudo ssldump -i lo
$ sudo ssldump -i lo -k server.key          // 暗号化したい場合は鍵も指定する(-dオプションも必要だったかも)
$ sudo ssldump -i lo -x -d -k server.key    // 16進数のダンプデータを表示する
$ sudo ssldump -T -Ad -k ./server.key -p hoge -i lo host localhost     // TCPの接続状況を表示する(-T)、パスワードを指定(-p)
$ sudo ssldump -a -A -H -k server.key -i lo                            // HTTPヘッダなども表示する。
$ sudo ssldump -k server.key dst port 443                              // 443ポートを表示する。
$ sudo ssldump -k server.key dst port 443 or port 80                   // 80と443を表示する
```

pcapファイルがある場合には次のようにして解析することもできる。
```
$ ssldump -r <File_Name>.pcap -k <Key_File>.key -d host <IP_Address>
```
- 参考
  - https://support.citrix.com/article/CTX116978


# 出力を見る

### 通常出力を見る
```
$ sudo ssldump -T -Ad -k ./server.key -p hoge -i lo host localhost
TCP: localhost.localdomain(50440) -> localhost.localdomain(14433) Seq 3725356204.(0) ACK 1044070116 FIN 
TCP: localhost.localdomain(14433) -> localhost.localdomain(50440) Seq 1044070116.(0) ACK 3725356205 FIN 
TCP: localhost.localdomain(50440) -> localhost.localdomain(14433) Seq 3725356205.(0) ACK 1044070117 
TCP: localhost.localdomain(50441) -> localhost.localdomain(14433) Seq 1060606173.(0) SYN 
TCP: localhost.localdomain(14433) -> localhost.localdomain(50441) Seq 3277783720.(0) ACK 1060606174 SYN 
TCP: localhost.localdomain(50441) -> localhost.localdomain(14433) Seq 1060606174.(0) ACK 3277783721 
New TCP connection #1: localhost.localdomain(50441) <-> localhost.localdomain(14433)
TCP: localhost.localdomain(50441) -> localhost.localdomain(14433) Seq 1060606174.(112) ACK 3277783721 PUSH 
1 1  0.0018 (0.0018)  C>S V3.1(107)  Handshake
      ClientHello
        Version 3.1 
        random[32]=
          58 27 7f 47 2b 19 84 0f b2 5a 11 ab a2 3e 27 58 
          49 bc df d9 7b 41 06 bd 6d 71 03 60 42 f5 27 c9 
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
TCP: localhost.localdomain(14433) -> localhost.localdomain(50441) Seq 3277783721.(0) ACK 1060606286 
TCP: localhost.localdomain(14433) -> localhost.localdomain(50441) Seq 3277783721.(1430) ACK 1060606286 PUSH 
1 2  0.0029 (0.0010)  S>C V3.1(53)  Handshake
      ServerHello
        Version 3.1 
        random[32]=
          58 27 7f 47 2b 18 8b ca dc 0d cc 5a e7 47 77 43 
          f8 4c bb a6 a4 2b fc 21 b4 78 14 25 30 35 b2 fe 
        session_id[0]=

        cipherSuite         TLS_DHE_DSS_WITH_AES_256_CBC_SHA
        compressionMethod                   NULL
1 3  0.0029 (0.0000)  S>C V3.1(1142)  Handshake
      Certificate
1 4  0.0029 (0.0000)  S>C V3.1(211)  Handshake
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
            93 14 5e eb 0d 7c 05 d5 f6 60 80 bc ea d4 e1 92 
            20 9e 9d 39 cd b8 ae d3 48 d7 f7 4b ad ce ee a6 
            38 02 d6 b4 9d 88 da 08 57 6e 15 58 b9 05 fd 85 
            c1 29 41 4f 92 d7 50 03 bc 9f c6 38 31 2b 4d ab 
        signature[70]=
          30 44 02 20 1a c2 09 14 35 cc 16 1e 53 3a 36 04 
          72 26 60 ca 78 64 1a 0c 22 61 3b 56 66 12 a9 2a 
          3e 9b df d9 02 20 03 40 c9 33 ea c1 f4 31 e8 74 
          43 f4 40 4c a0 c8 4e df 45 94 cb 30 c2 3f 5d 1b 
          43 f4 9e 7e 18 c1 
1 5  0.0029 (0.0000)  S>C V3.1(4)  Handshake
      ServerHelloDone
TCP: localhost.localdomain(50441) -> localhost.localdomain(14433) Seq 1060606286.(0) ACK 3277785151 
TCP: localhost.localdomain(50441) -> localhost.localdomain(14433) Seq 1060606286.(134) ACK 3277785151 PUSH 
1 6  0.0164 (0.0135)  C>S V3.1(70)  Handshake
      ClientKeyExchange
        DiffieHellmanClientPublicValue[64]=
          31 65 15 33 d2 f3 64 8f 44 f8 47 57 ed a3 2f c9 
          6f 57 7d ff b8 33 2d 37 ba b0 e7 da 71 4f 99 0a 
          04 2d 6e f7 33 b6 ed 57 ff 9f 78 52 9e aa 9e c7 
          e4 f9 f5 1e e7 7c 60 6c 4b 11 1d 7e 29 50 c8 ab 
1 7  0.0164 (0.0000)  C>S V3.1(1)  ChangeCipherSpec
1 8  0.0164 (0.0000)  C>S V3.1(48)  Handshake
TCP: localhost.localdomain(14433) -> localhost.localdomain(50441) Seq 3277785151.(234) ACK 1060606420 PUSH 
1 9  0.0167 (0.0003)  S>C V3.1(170)  Handshake
1 10 0.0167 (0.0000)  S>C V3.1(1)  ChangeCipherSpec
1 11 0.0167 (0.0000)  S>C V3.1(48)  Handshake
TCP: localhost.localdomain(50441) -> localhost.localdomain(14433) Seq 1060606420.(0) ACK 3277785385 
```

### xオプション
16進数結果が出力される。
```
$ sudo ssldump -i lo -x -d -k server.key 
...

1 13 4.5956 (0.0000)  C>S  application_data
Packet data[37]=
  17 03 01 00 20 f5 25 51 b7 f4 11 f0 b2 70 ae e5 
  84 1a ba 22 8a f7 fa 69 e8 1e bb 7b 41 e6 e7 ac 
  1b 35 f7 33 e3 
```

### 失敗した場合のハンドシェイクの出力について

以下のソースコードを$gmakeでコンパイルするとserver, clientができる。
```
$ https://github.com/tsuyopon/cpp/tree/master/serverclient/https
```

SSLサーバを起動する。
```
$ ./server
$ sudo ssldump -n -H -i lo
```

クライアントから接続してdumpを覗いてみるとハンドシェイクエラーが起こっていることがわかる。
```
$ ./client
140261973305184:error:14094410:SSL routines:SSL3_READ_BYTES:sslv3 alert handshake failure:s3_pkt.c:1199:SSL alert number 40
$ sudo ssldump -n -H -i lo
New TCP connection #2: 127.0.0.1(37256) <-> 127.0.0.1(8765)
2 1  0.0031 (0.0031)  C>S  Handshake
      ClientHello
        Version 3.1 
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
2 2  0.0032 (0.0001)  S>C  Alert
    level           fatal
    value           handshake_failure
2    0.0033 (0.0000)  S>C  TCP FIN
2    0.0053 (0.0020)  C>S  TCP FIN
```


# 参考URL
- http://ssldump.sourceforge.net/
- http://ssldump.sourceforge.net/documentation.html
- http://prefetch.net/articles/debuggingssl.html
- http://d.hatena.ne.jp/blooper/20120910/1347285980
