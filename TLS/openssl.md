# 概要
この辺を参考にする。
- http://www.usupi.org/sysad/252.html

# 詳細

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

### opensslのバージョンポリシーについて
- https://stackoverflow.com/questions/42189880/how-to-determine-the-latest-openssl-version
- https://www.openssl.org/blog/blog/2014/12/23/the-new-release-strategy/

### ベンチマークについて
opensslにはspeedというオプションが存在する。これによりベンチマークを測定できる。  
以下は代表的なものだけ
```
$ openssl speed -evp aes-128-gcm
$ openssl speed rsa2048
$ openssl speed ecdhp256
```

### お手軽にHTTPSサーバを立てて証明書確認を行う
opensslコマンドにはお手軽にHTTPSサーバを立てる機能が存在します。次のような感じで指定します。
```
$ openssl s_server -accept 10443 -cert cert.pem -key keynp.pem -CAfile rapidssl.pem -WWW
Using default temp DH parameters
Using default temp ECDH parameters
ACCEPT
```
- accept: HTTPS待受portがデフォルトで4433とややわかりにくいので指定するといいかもしれません。
- cert: サーバ証明書のファイル名
- key: 秘密鍵のファイル名
- CAfile: 中間証明書のファイル名
- WWW: 単順なWEBサーバをエミュレートする。URL のパス部分をカレントディレクトリからの相対パスで解決して、対応するファイルを返す。

リクエストを確認するのも次のコマンドで可能なのですごい便利
```
$ openssl s_client -connect localhost:10433
```

- 参考
  - https://bacchi.me/linux/openssl-tips/

### CRLの中身を確認してみる
以下からpca1.1.1.crlを取得する
- https://www.jp.websecurity.symantec.com/repository/crl.html

次のような書式で可能らしい。
```
$ openssl crl -inform der -in crl.der -text
$ openssl crl -in crl.pem -text
```

crl拡張子はderファイルとのことだったので、指定してみたらCRLの内容が表示された。
```
$  openssl crl -inform der -in pca1.1.1.crl -text
Certificate Revocation List (CRL):
        Version 1 (0x0)
        Signature Algorithm: sha1WithRSAEncryption
        Issuer: /C=US/O=VeriSign, Inc./OU=Class 1 Public Primary Certification Authority
        Last Update: Dec 15 00:00:00 2016 GMT
        Next Update: Dec 31 23:59:59 2017 GMT
Revoked Certificates:
    Serial Number: 2CD24B62C497A417CD6EA3C89C7A2DC8
        Revocation Date: Apr  1 17:56:15 2004 GMT
    Serial Number: 3A45DE56CB02CDDCDC4E7763221BD4D5
        Revocation Date: May  8 19:22:34 2001 GMT
    Serial Number: 415D8836811520D5808346A85992782C
        Revocation Date: Jul  6 16:57:23 2001 GMT
    Serial Number: 473981FFFD8481F195F9EB18C27C0DF1
        Revocation Date: Jan  9 18:06:12 2003 GMT
    Serial Number: 70547E6AE2BAD8767F47A99910415E67
        Revocation Date: Sep 23 17:00:08 2002 GMT
    Serial Number: 7E0B5DDE18F2396682A68F65223823C8
        Revocation Date: May  8 19:08:21 2001 GMT
    Serial Number: D05448601867D3AD35CA2F0D4A27955E
        Revocation Date: Dec 11 18:26:21 2001 GMT
    Signature Algorithm: sha1WithRSAEncryption
        c3:4b:60:3b:0d:72:df:46:09:c7:50:d1:b7:9b:28:93:68:d9:
        f0:01:c0:2a:49:33:9b:22:9a:db:ea:5d:a5:40:62:5b:69:b6:
        38:73:75:a6:eb:11:fd:fc:6a:9b:fc:2e:dd:d0:86:a6:ef:9f:
        a4:16:86:3f:89:4e:a2:c6:e2:7a:5f:00:08:3a:cc:97:86:91:
        e1:2f:ff:37:5a:c0:1c:61:a0:0b:d1:6a:29:31:e5:de:ad:dc:
        a4:70:0e:59:d4:52:e7:18:f8:2d:1f:57:a9:a4:18:93:6c:f3:
        cc:dd:dc:2b:d6:61:12:e5:6f:0d:cf:21:cd:65:c0:ea:b4:a3:
        35:c5
-----BEGIN X509 CRL-----
MIICHjCCAYcwDQYJKoZIhvcNAQEFBQAwXzELMAkGA1UEBhMCVVMxFzAVBgNVBAoT
DlZlcmlTaWduLCBJbmMuMTcwNQYDVQQLEy5DbGFzcyAxIFB1YmxpYyBQcmltYXJ5
IENlcnRpZmljYXRpb24gQXV0aG9yaXR5Fw0xNjEyMTUwMDAwMDBaFw0xNzEyMzEy
MzU5NTlaMIH2MCECECzSS2LEl6QXzW6jyJx6LcgXDTA0MDQwMTE3NTYxNVowIQIQ
OkXeVssCzdzcTndjIhvU1RcNMDEwNTA4MTkyMjM0WjAhAhBBXYg2gRUg1YCDRqhZ
kngsFw0wMTA3MDYxNjU3MjNaMCECEEc5gf/9hIHxlfnrGMJ8DfEXDTAzMDEwOTE4
MDYxMlowIQIQcFR+auK62HZ/R6mZEEFeZxcNMDIwOTIzMTcwMDA4WjAhAhB+C13e
GPI5ZoKmj2UiOCPIFw0wMTA1MDgxOTA4MjFaMCICEQDQVEhgGGfTrTXKLw1KJ5Ve
Fw0wMTEyMTExODI2MjFaMA0GCSqGSIb3DQEBBQUAA4GBAMNLYDsNct9GCcdQ0beb
KJNo2fABwCpJM5simtvqXaVAYltptjhzdabrEf38apv8Lt3Qhqbvn6QWhj+JTqLG
4npfAAg6zJeGkeEv/zdawBxhoAvRaikx5d6t3KRwDlnUUucY+C0fV6mkGJNs88zd
3CvWYRLlbw3PIc1lwOq0ozXF
-----END X509 CRL-----
```

# TODO
- https://nona.to/fswiki/OpenSSL+Command-Line+HOWTO.html

# 参考URL
- http://www.usupi.org/sysad/252.html
- http://d.hatena.ne.jp/blooper/20120910/1347285980
