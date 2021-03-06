# 概要
この辺を参考にする。
- http://www.usupi.org/sysad/252.html

サポートバージョンなどについては次のRelease Strategy資料を参考にすること
- https://www.openssl.org/policies/releasestrat.html

# 詳細
### バージョンを表示する
単順なバージョンのみ表示する
```
$ openssl version
OpenSSL 1.0.1f 6 Jan 2014
```

すべての情報を表示する。 コンパイルオプションやOPENSSLDIRがわかるのでデフォルトでどこの証明書が利用されるのかがわかります。
```
$ openssl version -a
OpenSSL 1.0.1f 6 Jan 2014
built on: Fri Dec  4 13:26:29 UTC 2015
platform: debian-amd64
options:  bn(64,64) rc4(16x,int) des(idx,cisc,16,int) blowfish(idx) 
compiler: cc -fPIC -DOPENSSL_PIC -DOPENSSL_THREADS -D_REENTRANT -DDSO_DLFCN -DHAVE_DLFCN_H -m64 -DL_ENDIAN -DTERMIO -g -O2 -fstack-protector-strong -Wformat -Werror=format-security -D_FORTIFY_SOURCE=2 -Wl,-Bsymbolic-functions -Wl,-z,relro -Wa,--noexecstack -Wall -DMD32_REG_T=int -DOPENSSL_IA32_SSE2 -DOPENSSL_BN_ASM_MONT -DOPENSSL_BN_ASM_MONT5 -DOPENSSL_BN_ASM_GF2m -DSHA1_ASM -DSHA256_ASM -DSHA512_ASM -DMD5_ASM -DAES_ASM -DVPAES_ASM -DBSAES_ASM -DWHIRLPOOL_ASM -DGHASH_ASM
OPENSSLDIR: "/usr/lib/ssl"
```

### openssl Manpage
man opensslをすると次のようなSEE ALSOが表示される。
```
SEE ALSO
       asn1parse(1), ca(1), config(5), crl(1), crl2pkcs7(1), dgst(1), dhparam(1), dsa(1), dsaparam(1), enc(1), gendsa(1), genpkey(1), genrsa(1), nseq(1),
       openssl(1), sslpasswd(1), pkcs12(1), pkcs7(1), pkcs8(1), sslrand(1), req(1), rsa(1), rsautl(1), s_client(1), s_server(1), s_time(1), smime(1),
       spkac(1), verify(1), version(1), x509(1), crypto(3), ssl(3), x509v3_config(5)
```

つまり、s_serverオプションを知りたければ以下のコマンドでOK
```
man s_server
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

### AESに対応したCPU命令を出力するかどうかglibcを確認する
glibcで利用されるgasのバージョンでIntelの暗号化処理機能が制限されています。gasバージョンは次のようにして確認できます。
```
$ gcc -Wa,-v -c -o /dev/null -x assembler /dev/null
GNU assembler version 2.25.1 (x86_64-redhat-linux) using BFD version version 2.25.1-31.base.el7 
```

gasのバージョンでの違いは次の通りです。
- 2.22以上ならAVX2を利用する
- 2.21〜2.20ならAVXを利用する
- 2.20未満ならAVXサポートはなし

cpuinfoで対応しているかどうかは次のようにして確認することができます。openssl speedのオプションで-evpを付与するとAESありとして速度を測ってくれます。
```
$ grep -m1 -o aes /proc/cpuinfo 
aes
```

### opensslのバージョンポリシーについて
- https://stackoverflow.com/questions/42189880/how-to-determine-the-latest-openssl-version
- https://www.openssl.org/blog/blog/2014/12/23/the-new-release-strategy/

# 参考URL
- opensslコマンドの中ではもっともしっかりしたマニュアル
  - https://nona.to/fswiki/OpenSSL+Command-Line+HOWTO.html
  - 上記翻訳の元
    - https://www.madboa.com/geek/openssl/
- http://www.usupi.org/sysad/252.html
- http://d.hatena.ne.jp/blooper/20120910/1347285980
