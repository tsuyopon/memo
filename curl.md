# 概要
curlについて

最近ではWebAPIのレスポンスがjsonが流行っているので次のようなコマンドを用いて出力データを見やすくすることができる
```
| jq .
| python -m json.tool
```

# 一般的な利用方法

### HTTP/2での指定を行う(SNIも含めて)
Hostヘッダの指定だけではSNI指定がうまくいかなかったのですが、次のようにresolveを使うことで回避できました。
```
$ curl -vik --resolve test.co.jp:443:127.0.0.1 https://test.co.jp --http2
```

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
or
$ curl --include http://www.yahoo.co.jp
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

### Rangeリクエストを送付したい
大容量のファイルなどを取得する際に使われているRangeリクエストを送る場合には次のようにします。
```
$ curl -v -r 0-100 "http://www.example.com/test.mp4"
```
上記では次のヘッダを合わせて送付しています。レスポンスはRangeリクエストに対応していないとそのまま200が返ってきます。
```
Range: bytes=0-100
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

### HTTPバージョンを指定する

```
$ curl -I --http2 https://www.yahoo.co.jp/
HTTP/2 200 
date: Wed, 14 Aug 2019 19:34:24 GMT
p3p: policyref="http://privacy.yahoo.co.jp/w3c/p3p_jp.xml", CP="CAO DSP COR CUR ADM DEV TAI PSA PSD IVAi IVDi CONi TELo OTPi OUR DELi SAMi OTRi UNRi PUBi IND PHY ONL UNI PUR FIN COM NAV INT DEM CNT STA POL HEA PRE GOV"
x-content-type-options: nosniff
x-xss-protection: 1; mode=block
x-frame-options: SAMEORIGIN
expires: -1
pragma: no-cache
cache-control: private, no-cache, no-store, must-revalidate
content-type: text/html; charset=UTF-8
age: 0
via: http/1.1 edge2626.img.djm.yahoo.co.jp (ApacheTrafficServer [c sSf ])
server: ATS

$ curl -I --http1.1 https://www.yahoo.co.jp/
HTTP/1.1 200 OK
Date: Wed, 14 Aug 2019 19:35:31 GMT
P3P: policyref="http://privacy.yahoo.co.jp/w3c/p3p_jp.xml", CP="CAO DSP COR CUR ADM DEV TAI PSA PSD IVAi IVDi CONi TELo OTPi OUR DELi SAMi OTRi UNRi PUBi IND PHY ONL UNI PUR FIN COM NAV INT DEM CNT STA POL HEA PRE GOV"
X-Content-Type-Options: nosniff
X-XSS-Protection: 1; mode=block
X-Frame-Options: SAMEORIGIN
Expires: -1
Pragma: no-cache
Cache-Control: private, no-cache, no-store, must-revalidate
Content-Type: text/html; charset=UTF-8
Age: 0
Connection: keep-alive
Via: http/1.1 edge2640.img.djm.yahoo.co.jp (ApacheTrafficServer [c sSf ])
Server: ATS

$ curl -I --http1.0 https://www.yahoo.co.jp/
HTTP/1.0 200 OK
Date: Wed, 14 Aug 2019 19:35:38 GMT
P3P: policyref="http://privacy.yahoo.co.jp/w3c/p3p_jp.xml", CP="CAO DSP COR CUR ADM DEV TAI PSA PSD IVAi IVDi CONi TELo OTPi OUR DELi SAMi OTRi UNRi PUBi IND PHY ONL UNI PUR FIN COM NAV INT DEM CNT STA POL HEA PRE GOV"
X-Content-Type-Options: nosniff
X-XSS-Protection: 1; mode=block
X-Frame-Options: SAMEORIGIN
Expires: -1
Pragma: no-cache
Cache-Control: private, no-cache, no-store, must-revalidate
Content-Type: text/html; charset=UTF-8
Age: 0
Via: http/1.1 edge2637.img.djm.yahoo.co.jp (ApacheTrafficServer [c sSf ])
Server: ATS
```

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

### curlを使ってボトルネックを調査する

次のコマンドを実行してtemplate.txtを準備します。
```
cat <<'EOF' > template.txt
url_effective\t\t: %{url_effective}\n
url_effective\t\t: %{url_effective}\n
http_code\t\t: %{http_code}\n
http_connect\t\t: %{http_connect}\n
time_total\t\t: %{time_total}\n
time_namelookup\t\t: %{time_namelookup}\n
time_connect\t\t: %{time_connect}\n
time_appconnect\t\t: %{time_appconnect}\n
time_pretransfer\t\t: %{time_pretransfer}\n
time_redirect\t\t: %{time_redirect}\n
time_starttransfer\t\t: %{time_starttransfer}\n
size_download\t\t: %{size_download}\n
size_upload\t\t: %{size_upload}\n
size_header\t\t: %{size_header}\n
size_request\t\t: %{size_request}\n
speed_download\t\t: %{speed_download}\n
speed_upload\t\t: %{speed_upload}
EOF
```

コマンド実行の際にテンプレートを実行すると指定した値を表示してくれます
```
$ curl -o /dev/null http://www.example.com -w @template -s
url_effective		: http://www.example.com/
url_effective		: http://www.example.com/
http_code		: 200
http_connect		: 000
time_total		: 0.404
time_namelookup		: 0.013
time_connect		: 0.222
time_appconnect		: 0.000
time_pretransfer		: 0.222
time_redirect		: 0.000
time_starttransfer		: 0.403
size_download		: 1270
size_upload		: 0
size_header		: 322
size_request		: 79
speed_download		: 3146.000
speed_upload		: 0.000
```

man curlなどとすると次のような値も指定することができます。
```
content_type, filename_effective, ftp_entry_path, http_code, http_connect, local_ip, local_port, num_connects, num_redirects, redirect_url, remote_ip, remote_port, size_download, size_header, size_request, size_upload, speed_download, speed_upload, ssl_verify_result, time_appconnect, time_connect, time_namelookup, time_pretransfer, time_redirect, time_starttransfer, time_total, url_effective
```

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

### C言語のソースコードを出力する
libcurlオプションを付与してソースコード名を指定します。
```
$ curl 'https://www.yahoo.co.jp/' --libcurl source.c
```

C言語形式のソースコードを吐き出してくれます。
```
$ ls source.c 
source.c
$ head -20 source.c 
/********* Sample code generated by the curl command line tool **********
 * All curl_easy_setopt() options are documented at:
 * https://curl.haxx.se/libcurl/c/curl_easy_setopt.html
 ************************************************************************/
#include <curl/curl.h>

int main(int argc, char *argv[])
{
  CURLcode ret;
  CURL *hnd;

  hnd = curl_easy_init();
  curl_easy_setopt(hnd, CURLOPT_BUFFERSIZE, 102400L);
  curl_easy_setopt(hnd, CURLOPT_URL, "https://www.yahoo.co.jp/");
  curl_easy_setopt(hnd, CURLOPT_NOPROGRESS, 1L);
  curl_easy_setopt(hnd, CURLOPT_USERAGENT, "curl/7.61.1");
  curl_easy_setopt(hnd, CURLOPT_MAXREDIRS, 50L);
  curl_easy_setopt(hnd, CURLOPT_HTTP_VERSION, (long)CURL_HTTP_VERSION_2TLS);
  curl_easy_setopt(hnd, CURLOPT_TCP_KEEPALIVE, 1L);
```

# curlコマンド
- https://hydrocul.github.io/wiki/commands/curl.html
- http://blog.wagavulin.jp/entry/2015/10/18/060938
- http://qiita.com/yasuhiroki/items/a569d3371a66e365316f
