# 概要
curlをインストールします。
curlでもnghttp2と組み合わせることでHTTP/2リクエストが可能になりますので、今回はその手順を記します。

# 詳細

### nghttp2のインストール
今回はgithubからv1.37.0をダウンロードします。
コンパイル手順についてはREADMEに記載されています。
- https://github.com/nghttp2/nghttp2
```
$ git clone -b v1.37.0 https://github.com/nghttp2/nghttp2.git
$ git submodule update --init
$ autoreconf -i
$ automake
$ autoconf
```

openssl-1.1.1があったのでついでにコンパイルオプションに指定します。なければOPENSSL_CFLAGS, OPENSSL_LIBSは指定しなくても問題ありません。
```
$ ./configure CFLAGS="-g3 -O0" OPENSSL_CFLAGS="-I/opt/openssl-1.1.1/include/" OPENSSL_LIBS="-L/opt/openssl-1.1.1/lib/ -lssl -lcrypto" --prefix=/opt/nghttp2
$ make
$ sudo make install
```


### curlのインストール
```
$ wget https://curl.haxx.se/download/curl-7.64.1.tar.gz
$ tar zxvf curl-7.64.1.tar.gz
$ cd curl-7.64.1/
$ ./configure CFLAGS="-g3 -O0" --prefix=/opt/curl-7.64.1 --with-nghttp2=/opt/nghttp2 --enable-debug
```


今回のconfigureの結果は次のような感じ(g3が有効になってなさそうなので、--enable-debugを付与した)
```
  Host setup:       x86_64-pc-linux-gnu
  Install prefix:   /opt/curl-7.64.1
  Compiler:         gcc
   CFLAGS:          -O0 -Werror-implicit-function-declaration -g -pedantic -Wall -W -Wpointer-arith -Wwrite-strings -Wunused -Wshadow -Winline -Wnested-externs -Wmissing-declarations -Wmissing-prototypes -Wno-long-long -Wbad-function-cast -Wfloat-equal -Wno-multichar -Wsign-compare -Wundef -Wno-format-nonliteral -Wendif-labels -Wstrict-prototypes -Wdeclaration-after-statement -Wold-style-definition -Wstrict-aliasing=3 -Wcast-align -Wtype-limits -Wold-style-declaration -Wmissing-parameter-type -Wempty-body -Wclobbered -Wignored-qualifiers -Wconversion -Wno-sign-conversion -Wvla -ftree-vrp -Wdouble-promotion -Wformat=2 -Wno-system-headers -pthread
   CPPFLAGS:        -I/opt/nghttp2/include
   LDFLAGS:         -L/opt/nghttp2/lib
   LIBS:            -lnghttp2 -lssl -lcrypto -lssl -lcrypto -lz

  curl version:     7.64.1
  SSL:              enabled (OpenSSL)
  SSH:              no      (--with-libssh2)
  zlib:             enabled
  brotli:           no      (--with-brotli)
  GSS-API:          no      (--with-gssapi)
  TLS-SRP:          no      (--enable-tls-srp)
  resolver:         POSIX threaded
  IPv6:             enabled
  Unix sockets:     enabled
  IDN:              no      (--with-{libidn2,winidn})
  Build libcurl:    Shared=yes, Static=yes
  Built-in manual:  enabled
  --libcurl option: enabled (--disable-libcurl-option)
  Verbose errors:   enabled (--disable-verbose)
  Code coverage:    disabled
  SSPI:             no      (--enable-sspi)
  ca cert bundle:   /etc/pki/tls/certs/ca-bundle.crt
  ca cert path:     no
  ca fallback:      no
  LDAP:             no      (--enable-ldap / --with-ldap-lib / --with-lber-lib)
  LDAPS:            no      (--enable-ldaps)
  RTSP:             enabled
  RTMP:             no      (--with-librtmp)
  Metalink:         no      (--with-libmetalink)
  PSL:              no      (libpsl not found)
  Alt-svc:          no      (--enable-alt-svc)
  HTTP2:            enabled (nghttp2)
  Protocols:        DICT FILE FTP FTPS GOPHER HTTP HTTPS IMAP IMAPS POP3 POP3S RTSP SMB SMBS SMTP SMTPS TELNET TFTP
  Features:         SSL IPv6 UnixSockets libz AsynchDNS NTLM NTLM_WB HTTP2 HTTPS-proxy
 ```

あとはコンパイルをしてインストールする。
 ```
 $ make
 $ sudo make install
 ```


### 動作確認
ヤフーのサーバにアクセスしてみます。

```
$ /opt/curl-7.64.1/bin/curl --http2 -v https://www.yahoo.co.jp/
```

```
$ /opt/curl-7.64.1/bin/curl --http2 -I https://www.yahoo.co.jp/
HTTP/2 200 
date: Thu, 04 Apr 2019 16:42:54 GMT
p3p: policyref="http://privacy.yahoo.co.jp/w3c/p3p_jp.xml", CP="CAO DSP COR CUR ADM DEV TAI PSA PSD IVAi IVDi CONi TELo OTPi OUR DELi SAMi OTRi UNRi PUBi IND PHY ONL UNI PUR FIN COM NAV INT DEM CNT STA POL HEA PRE GOV"
x-content-type-options: nosniff
x-xss-protection: 1; mode=block
x-frame-options: SAMEORIGIN
expires: -1
pragma: no-cache
cache-control: private, no-cache, no-store, must-revalidate
content-type: text/html; charset=UTF-8
age: 0
via: http/1.1 edge2627.img.djm.yahoo.co.jp (ApacheTrafficServer [c sSf ])
server: ATS
```

### HTTP/2通信をdecryptしたい場合
curlでもSSLKEYLOGFILE環境変数を使ってmaster secret情報を出力することができます。これはopensslなどで定義される環境変数仕様のようです。
```
$ SSLKEYLOGFILE=~/curl_ssl_keylog.keylog /opt/curl-7.64.1/bin/curl --http2 -v https://www.yahoo.co.jp/
```

wireshark側の設定についてはwireshak.mdを参考にしてください。


