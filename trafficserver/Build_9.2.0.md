# 概要
trafficserver-9.2.0をgithubレポジトリ からcloneしてubuntu上でデバッグビルドします。

# 環境
Ubuntuが標準インストールされていることを想定しています。
```
$ lsb_release -a
No LSB modules are available.
Distributor ID:	Ubuntu
Description:	Ubuntu 22.04.1 LTS
Release:	22.04
Codename:	jammy
```

# 手順
/usr/local/src上に落としておきます
```
$ cd /usr/local/src
$ sudo git clone https://github.com/apache/trafficserver.git
$ sudo mv -iv trafficserver trafficserver-9.2.0
$ cd trafficserver-9.2.0
```

タグを変更します
```
$ sudo git checkout 9.2.0
```

configureファイルを生成します
```
$ sudo autoreconf -if
```

configure実行時にエラーにならないように依存パッケージをインストールします。
```
$ sudo apt-get install zlib1g-dev libpcre3-dev systemtap-sdt-dev
```

configureによりfficserverのビルド設定を行います。/opt/trafficserver-9.2.0に入るようにして、各種ビルド専用オプションを有効にしておきます。
下記の機能も入れるためにenable-event-trackerを有効にしてみます。
- https://github.com/apache/trafficserver/pull/8179/files
```
$ sudo ./configure --prefix=/opt/trafficserver-9.2.0 --enable-debug --enable-experimental-plugins --enable-event-tracker --enable-example-plugins --enable-systemtap

(snip)
configure: Build option summary:
    CC:                 cc
    CXX:                c++
    CPP:                cc -E
    CFLAGS:             
    CXXFLAGS:           
    CPPFLAGS:           -D_GNU_SOURCE -DOPENSSL_NO_SSL_INTERN -DOPENSSL_API_COMPAT=10002 -DOPENSSL_IS_OPENSSL3
    LDFLAGS:            
    AM_CFLAGS:      -std=gnu99 -ggdb3 -pipe -Wall -Wextra -Wno-ignored-qualifiers -Wno-unused-parameter -Wno-format-truncation -Wno-cast-function-type -Wno-stringop-overflow -mcx16
    AM_CXXFLAGS:    -std=c++17 -ggdb3 -pipe -Wall -Wextra -Wno-ignored-qualifiers -Wno-unused-parameter -Wno-format-truncation -Wno-cast-function-type -Wno-stringop-overflow -Wno-invalid-offsetof -Wno-noexcept-type -Wsuggest-override -mcx16
    AM_CPPFLAGS:    -Dlinux -DDEBUG -D_DEBUG -DENABLE_EVENT_TRACKER -D_LARGEFILE64_SOURCE=1 -D_COMPILE64BIT_SOURCE=1 -D_REENTRANT -D__STDC_LIMIT_MACROS=1 -D__STDC_FORMAT_MACROS=1
    AM_LDFLAGS:     -rdynamic -Wl,--as-needed
    TS_INCLUDES:        
    OPENSSL_LDFLAGS:    
    OPENSSL_INCLUDES:   
    YAMLCPP_LDFLAGS:    -L${abs_top_builddir}/lib/yamlcpp
    YAMLCPP_INCLUDES:   -I${abs_top_srcdir}/lib/yamlcpp/include
    NURAFT_LDFLAGS:     
    NURAFT_INCLUDES:   
```

以上によりビルドの準備が整いましたのでビルド、インストールを行います。
```
$ sudo make
$ sudo make install
```

ポート番号だけデフォルトで8080なので80で起動するように変更します。
```
$ vim /opt/trafficserver-9.2.0/etc/trafficserver/records.config
```

remap.configも設定を入れておく
```
$ vim /opt/trafficserver-9.2.0/etc/trafficserver/remap.config
map http://httpbin.org/ https://httpbin.org/get
```

```
$ sudo /opt/trafficserver-9.2.0/bin/trafficserver start
$ ps auxww | grep traffic
nobody    903332  1.2  0.1 182584 11744 ?        Sl   08:20   0:00 /opt/trafficserver-9.2.0/bin/traffic_manager
nobody    903340  3.0  0.6 479320 53128 ?        Sl   08:20   0:00 /opt/trafficserver-9.2.0/bin/traffic_server -M --httpport 80:fd=8,80:fd=9:ipv6
```

以上でtrafficserverが起動できているところまでが確認できました。
localhostにリクエストを投げて動作確認をするとちゃんとReverse Proxyとなっていることが確認できます。

```
$ curl -v -H "Host: httpbin.org" http://localhost/
*   Trying 127.0.0.1:80...
* Connected to localhost (127.0.0.1) port 80 (#0)
> GET / HTTP/1.1
> Host: httpbin.org
> User-Agent: curl/7.81.0
> Accept: */*
> 
* Mark bundle as not supporting multiuse
< HTTP/1.1 200 OK
< Date: Thu, 16 Mar 2023 23:24:19 GMT
< Content-Type: application/json
< Content-Length: 298
< Server: ATS/9.2.0
< Access-Control-Allow-Origin: *
< Access-Control-Allow-Credentials: true
< Age: 1
< Connection: keep-alive
< 
{
  "args": {}, 
  "headers": {
    "Accept": "*/*", 
    "Client-Ip": "127.0.0.1", 
    "Host": "httpbin.org", 
    "User-Agent": "curl/7.81.0", 
    "X-Amzn-Trace-Id": "Root=1-6413a523-2a9096ca4733ca3c5230ed1b"
  }, 
  "origin": "127.0.0.1, 60.101.238.212", 
  "url": "https://httpbin.org/get"
}
* Connection #0 to host localhost left intact
```

# 参考資料
- https://docs.trafficserver.apache.org/en/latest/getting-started/index.en.html#installation
