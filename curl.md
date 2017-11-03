# 概要
curlについて

最近ではWebAPIのレスポンスがjsonが流行っているので次のようなコマンドを用いて出力データを見やすくすることができる
```
| jq .
| python -m json.tool
```

# 一般的な利用方法

### OAuth関連
OAuth2.0のbearerでの確認は次のようにして流し込みすると確認が簡単となる。
```
// 通常
$ echo -n 'xxx' | xargs -I{} curl -v -H "Authorization: Bearer {}" "https://example.co.jp/"

// jsonを扱うような場合
$ echo -n 'xxx' | xargs -I{} curl -v -H "Authorization: Bearer {}" -H "Accept: application/json" -H "Content-type: application/json" "https://example.co.jp/"
```

または環境変数などを使うとtokenを頻繁に変更してリクエストするような場合に非常に便利である。
```
$ export BTOKEN="XXXXXXXXXXXX"
$ curl -v -H "Authorization: Bearer ${BTOKEN}" -H "Accept: application/json" -H "Content-type: application/json" "https://example.co.jp/"
```

- 参考
  - https://openid-foundation-japan.github.io/draft-ietf-oauth-v2-bearer-draft11.ja.html

### HEADメソッド
Iオプションを実行するとHEADメソッドで取得してヘッダのみを表示する
```
$ curl -I http://www.yahoo.co.jp/
HTTP/1.1 301 Redirect
Date: Sun, 16 Apr 2017 03:37:22 GMT
Connection: keep-alive
Via: http/1.1 edge2128.img.djm.yahoo.co.jp (ApacheTrafficServer [c s f ])
Server: ATS
Cache-Control: no-store
Location: https://www.yahoo.co.jp:443/
Content-Type: text/html
Content-Language: en
Content-Length: 6794
```

### レスポンスと一緒にレスポンスヘッダも表示する。
iオプション(include)を含めればレスポンスヘッダも表示する。
```
$ curl -i http://www.yahoo.co.jp
```

### POSTメソッド
```
$ curl http://example/test -X POST -d "age=1" -d "hoge=10"
or
$ curl http://example/test -X POST -d "age=1&hoge=test"
```

JSONを送る場合
```
$ curl -v -H "Accept: application/json" -H "Content-type: application/json" -X POST -d '{"user":{"first_name":"firstname","last_name":"lastname","email":"email@email.com","password":"app123","password_confirmation":"app123"}}'  http://example/test
```

### DELETE
以下はヘッダと値も付加しているサンプルです。
```
$ curl -X "DELETE" http://example.com/test -H "Content-Type:application/json" -d "{\"user\" :{\"first_name\":\"firstname\",\"last_name\":\"lastname\",\"email\":\"email@email.com\",\"password\":\"app123\",\"password_confirmation\":\"app123\"}}"
```

### ファイルをデータとして指定する
```
$ cat data.txt
{"key":"val","key2":",val2"}
$ curl -X "DELETE" http://example.com/test -H "Content-Type:application/json" -d '@data.txt'
```

### curlでリクエストした時のHeaderも見たい

```
$ curl -v http://www.example.com/test
```

### リソースを保存する
ウェブ上に存在するファイル名で保存する場合
```
$ curl -O  http://www.example.com/top.jpg
```

ファイル名を指定して保存する場合
```
$ curl -o my.jpg  http://www.example.com/top.jpg
```

### BASIC認証をさせたい場合
```
$ curl --basic --user user:password -X PUT -d 'example[foo]=bar' -d 'example[jane]=doe' http://example.com/test
```

### URLエンコードしたい場合
```
$ curl --data-urlencode "text1=a&b" --data-urlencode "text2=あ" http://example/test
```

### リダイレクト先も追跡して取得する場合
次のように301 Moved Parmanentlyしか帰ってこないがリダイレクト先も追跡したい場合、
```
$ curl -I http://yahoo.co.jp
HTTP/1.1 301 Moved Permanently
Server: nginx
Date: Sun, 16 Apr 2017 03:34:00 GMT
Content-Type: text/html
Connection: close
P3P: policyref="http://privacy.yahoo.co.jp/w3c/p3p_jp.xml", CP="CAO DSP COR CUR ADM DEV TAI PSA PSD IVAi IVDi CONi TELo OTPi OUR DELi SAMi OTRi UNRi PUBi IND PHY ONL UNI PUR FIN COM NAV INT DEM CNT STA POL HEA PRE GOV"
X-Content-Type-Options: nosniff
X-XSS-Protection: 1; mode=block
X-Frame-Options: SAMEORIGIN
Location: http://www.yahoo.co.jp/
Cache-Control: private
X-Frame-Options: SAMEORIGIN
```

この場合にはLオプションを用いると良い
```
$ curl -I -L http://yahoo.co.jp
HTTP/1.1 301 Moved Permanently
Server: nginx
Date: Sun, 16 Apr 2017 03:34:05 GMT
Content-Type: text/html
Connection: close
P3P: policyref="http://privacy.yahoo.co.jp/w3c/p3p_jp.xml", CP="CAO DSP COR CUR ADM DEV TAI PSA PSD IVAi IVDi CONi TELo OTPi OUR DELi SAMi OTRi UNRi PUBi IND PHY ONL UNI PUR FIN COM NAV INT DEM CNT STA POL HEA PRE GOV"
X-Content-Type-Options: nosniff
X-XSS-Protection: 1; mode=block
X-Frame-Options: SAMEORIGIN
Location: http://www.yahoo.co.jp/
Cache-Control: private
X-Frame-Options: SAMEORIGIN

HTTP/1.1 301 Redirect
Date: Sun, 16 Apr 2017 03:34:05 GMT
Connection: keep-alive
Via: http/1.1 edge1437.img.bbt.yahoo.co.jp (ApacheTrafficServer [c s f ])
Server: ATS
Cache-Control: no-store
Location: https://www.yahoo.co.jp:443/
Content-Type: text/html
Content-Language: en
Content-Length: 6794

HTTP/1.1 200 OK
Server: ATS
Date: Sun, 16 Apr 2017 03:34:05 GMT
Content-Type: text/html; charset=UTF-8
P3P: policyref="http://privacy.yahoo.co.jp/w3c/p3p_jp.xml", CP="CAO DSP COR CUR ADM DEV TAI PSA PSD IVAi IVDi CONi TELo OTPi OUR DELi SAMi OTRi UNRi PUBi IND PHY ONL UNI PUR FIN COM NAV INT DEM CNT STA POL HEA PRE GOV"
X-Content-Type-Options: nosniff
X-XSS-Protection: 1; mode=block
X-Frame-Options: SAMEORIGIN
Expires: -1
Pragma: no-cache
Cache-Control: private, no-cache, no-store, must-revalidate
X-XRDS-Location: https://open.login.yahooapis.jp/openid20/www.yahoo.co.jp/xrds
X-Frame-Options: SAMEORIGIN
Age: 0
Connection: keep-alive
Via: http/1.1 edge1123.img.bbt.yahoo.co.jp (ApacheTrafficServer [c sSf ])
```

# HTTPSに関する利用
### 接続方法を指定する
```
$ curl --tlsv1 https://www.yahoo.co.jp/         # 最新版のtlsで接続する。例えば、tlsv1.2ならtlsv1.2として接続する

$ curl --tlsv1.0 -I https://www.yahoo.co.jp/
$ curl --tlsv1.1 -I https://www.yahoo.co.jp/
$ curl --tlsv1.2 -I https://www.yahoo.co.jp/

$ curl --sslv2 https://www.yahoo.co.jp/
$ curl --sslv3 https://www.yahoo.co.jp/
$ curl --ssl https://www.yahoo.co.jp/  
```

### アクセス先サーバ証明書の検証を行わない。
```
$ curl -k https://www.yahoo.co.jp/
or
$ curl --insecure https://www.yahoo.co.jp/
```


### Linuxのca-certはどこにあるのか?
自分の試したUbuntuだと以下の箇所にルート証明書が配置されていた。
```
$ ls /etc/pki/tls/certs/
Makefile  ca-bundle.crt  ca-bundle.trust.crt  make-dummy-cert
```

次のパッケージに含まれている。
```
$ rpm -qf /etc/pki/tls/certs/*
openssl-1.0.0k-1.fc17.x86_64
ca-certificates-2012.81-1.fc17.noarch
ca-certificates-2012.81-1.fc17.noarch
openssl-1.0.0k-1.fc17.x86_64
```

### ルート証明書を指定させる
ルート証明書をcacertオプションで指定することもできる。
```
$ curl --cacert /etc/pki/tls/certs/ca-bundle.crt https://www.yahoo.co.jp/
```

ちなみに環境変数でも指定させることができる。
```
$ export CURL_CA_BUNDLE=cacert.pem
$ curl https://ssl.example.com/
```

- 参考
  - https://serverfault.com/questions/151157/ubuntu-10-04-curl-how-do-i-fix-update-the-ca-bundle?rq=1

# その他

### ヘッダ情報を変更したり、追加する
```
$ curl -H "Authorization: Bearer <ACCESS_TOKEN>" http://www.example.com
```

### IPv4, IPv6を指定する
IPv4でアクセスする
```
$ curl -4 https://www.yahoo.co.jp/
```

IPv6でアクセスする
```
$ curl -6 https://www.yahoo.co.jp/
```

### User-Agentを変更する
AオプションでUser-Agentを指定することができる。
```
$ curl -A "Mozilla/5.0 (Linux; U; Android 2.2.1; en-us; Nexus One Build/FRG83) AppleWebKit/533.1 (KHTML, like Gecko) Version/4.0 Mobile Safari/533.1" https://auctions.yahoo.co.jp/
```

### curlのルート証明書が古いので最新のに置き換えたい場合
既存の証明書をリネームしておく
```
$ cd /etc/pki/tls/certs/
$ sudo mv ca-bundle.crt ca-bundle.crt.org
```

新しい証明書を取得して置き換える。ca-bundle.crtはcacert.pemといった名称が使われることも多い
```
$ sudo wget http://curl.haxx.se/ca/cacert.pem
$ sudo mv ./cacert.pem ./ca-bundle.crt
```

### エラーを表示しない
sオプション(silent)を使うとエラーなども表示しない。。
```
$  curl https://www.yahoo.co.jps
curl: (6) Could not resolve host: www.yahoo.co.jps; Name or service not known
$  curl -s https://www.yahoo.co.jps
$ 
```

### アクセスした時にSet-Cookieされた情報を保存したい
cオプションの後にそのCookie情報を保存するファイル名を指定することにより保存することができる。
```
$ curl -c savecookie.txt https://auctions.yahoo.co.jp
$ cat savecookie.txt 
# Netscape HTTP Cookie File
# http://curl.haxx.se/docs/http-cookies.html
# This file was generated by libcurl! Edit at your own risk.

.auctions.yahoo.co.jp	TRUE	/	FALSE	1492502597	RD	T6qVdgD25tdbQn1BG8IXAhqyP1a4ml15ZL8-
```

そのCookieを使ってアクセスするにはbオプションでファイルを指定するとその時の情報がCookieヘッダに載せられることになる。
```
$ curl -b savecookie.txt https://auctions.yahoo.co.jp
```

### 自分のホストでNICに直接グローバルIPが割り当てられていないような場合のグローバルIPを取得する。
httpbin, inet-ip.info, ifconfig.meなどを使って取得可能です。ここではifconfig.meを使った方法を紹介します。
```
$ curl ifconfig.me      // http://ifconfig.meにアクセスしています。
133.215.11.38
```

サーバから出ていく際にアクセスするには次のようにifconfig.me/allで確認することが出来ます。
```
$ curl ifconfig.me/all
ip_addr: 133.215.11.38
remote_host: hogehoge.panda-world.ne.jp
user_agent: curl/7.38.0
port: 39450
lang: 
connection: 
keep_alive: 
encoding: 
mime: */*
charset: 
via: 
forwarded: 
```

その他にも次のようなものがあります。
```
$ curl ifconfig.me
$ curl ifconfig.me/host
$ curl ifconfig.me/all.json
```

次のページにアクセスするとどのようなエントリポイントで何を表示してくれるかといったことも確認することができます。
- http://ifconfig.me/

### curlコマンドの設定を取得する
curl-configというcurl設定情報を取得するコマンドが存在する。
```
$ curl-config 
Usage: curl-config [OPTION]

Available values for OPTION include:

  --built-shared says 'yes' if libcurl was built shared
  --ca        ca bundle install path
  --cc        compiler
  --cflags    pre-processor and compiler flags
  --checkfor [version] check for (lib)curl of the specified version
  --configure the arguments given to configure when building curl
  --features  newline separated list of enabled features
  --help      display this help and exit
  --libs      library linking information
  --prefix    curl install prefix
  --protocols newline separated list of enabled protocols
  --static-libs static libcurl library linking information
  --version   output version information
  --vernum    output the version information as a number (hexadecimal)
```

上記設定は次のようにして取得できる。何も表示されていない場合は設定が存在していないと思われる。
```
$ curl-config --ca

$ curl-config --cc
cc
$ curl-config --cflags

$ curl-config --built-shared
yes
$ curl-config --checkfor
(standard_in) 1: parse error
(standard_in) 1: parse error
/usr/bin/curl-config: line 113: test: : integer expression expected
requested version  is newer than existing 7.43.0
$ curl-config --configure
--disable-static --enable-hidden-symbols --enable-threaded-resolver --with-gssapi --with-darwinssl --without-libssh2
$ curl-config --features
SSL
IPv6
UnixSockets
libz
AsynchDNS
GSS-API
SPNEGO
Kerberos
NTLM
NTLM_WB
$ curl-config --libs
-lcurl
$ curl-config --prefix
/usr
$ curl-config --static-libs

$ curl-config --protocols
DICT
FILE
FTP
FTPS
GOPHER
HTTP
HTTPS
IMAP
IMAPS
LDAP
LDAPS
POP3
POP3S
RTSP
SMB
SMBS
SMTP
SMTPS
TELNET
TFTP
```

# curlコマンド
- https://hydrocul.github.io/wiki/commands/curl.html
- http://blog.wagavulin.jp/entry/2015/10/18/060938
- http://qiita.com/yasuhiroki/items/a569d3371a66e365316f
