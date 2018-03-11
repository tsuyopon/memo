# 概要
nmapコマンドについてまとめる

# 詳細

### nmapで対象のホストで起動しているポートをスキャンする
nmapの後にIPアドレスやドメインを指定します。複数指定することも可能です。
```
$ nmap localhost

Starting Nmap 6.40 ( http://nmap.org ) at 2018-01-21 20:29 JST
Nmap scan report for localhost (127.0.0.1)
Host is up (0.00030s latency).
Other addresses for localhost (not scanned): 127.0.0.1
Not shown: 994 closed ports
PORT     STATE SERVICE
22/tcp   open  ssh
25/tcp   open  smtp
80/tcp   open  http
443/tcp  open  https
8080/tcp open  http-proxy
8083/tcp open  us-srv

Nmap done: 1 IP address (1 host up) scanned in 0.06 seconds
```

指定方法は次のようにさまざまな方法が存在する
```
$ nmap 192.168.0.1 192.168.0.100   // 複数指定する
$ nmap 192.168.0.100-110           // 連続のIPを指定する
$ nmap 192.168.0.0/24 --exclude 192.168.0.1 192.168.1.5   // 幾つかのIPを除外する
$ nmap 192.168.1.0/24 --excludefile exclude.txt           // 幾つかの除外するものをファイルで指定する
$ nmap -iL リストファイルPATH      // ファイルで指定する
$ nmap 192.168.0.100/24            // ネットワークで指定する
```

### 詳細なスキャン情報を出力する
```
$ nmap -v localhost

Starting Nmap 6.40 ( http://nmap.org ) at 2018-01-21 20:32 JST
Initiating Ping Scan at 20:32
Scanning localhost (127.0.0.1) [2 ports]
Completed Ping Scan at 20:32, 0.00s elapsed (1 total hosts)
Initiating Connect Scan at 20:32
Scanning localhost (127.0.0.1) [1000 ports]
Discovered open port 22/tcp on 127.0.0.1
Discovered open port 25/tcp on 127.0.0.1
Discovered open port 8080/tcp on 127.0.0.1
Discovered open port 80/tcp on 127.0.0.1
Discovered open port 443/tcp on 127.0.0.1
Discovered open port 8083/tcp on 127.0.0.1
Completed Connect Scan at 20:32, 0.04s elapsed (1000 total ports)
Nmap scan report for localhost (127.0.0.1)
Host is up (0.00032s latency).
Other addresses for localhost (not scanned): 127.0.0.1
Not shown: 994 closed ports
PORT     STATE SERVICE
22/tcp   open  ssh
25/tcp   open  smtp
80/tcp   open  http
443/tcp  open  https
8080/tcp open  http-proxy
8083/tcp open  us-srv

Read data files from: /usr/bin/../share/nmap
Nmap done: 1 IP address (1 host up) scanned in 0.08 seconds
```

### pingを利用してそのネットワークで現在稼働中のマシン一覧を取得する
「-sP」オプションを実行することでpingを利用する
```
$ nmap -sP 10.0.2.0/24

Starting Nmap 6.40 ( http://nmap.org ) at 2018-01-21 20:33 JST
Nmap scan report for 10.0.2.2
Host is up (0.0078s latency).
Nmap scan report for 10.0.2.3
Host is up (0.0080s latency).
Nmap scan report for 10.0.2.4
Host is up (0.0080s latency).
Nmap scan report for 10.0.2.15
Host is up (0.00013s latency).
Nmap done: 256 IP addresses (4 hosts up) scanned in 3.24 seconds
```

### スキャンを行う対象としてIPプロトコルを指定する(sO)
```
$ sudo nmap -sO localhost

Starting Nmap 6.40 ( http://nmap.org ) at 2018-01-21 20:38 JST
Nmap scan report for localhost (127.0.0.1)
Host is up (0.000053s latency).
Other addresses for localhost (not scanned): 127.0.0.1
Not shown: 249 closed protocols
PROTOCOL STATE         SERVICE
1        open          icmp
2        open|filtered igmp
6        open          tcp
17       open          udp
103      open|filtered pim
136      open|filtered udplite
255      open|filtered unknown

Nmap done: 1 IP address (1 host up) scanned in 4.49 seconds
```

### スキャンを行う対象としてUDPプロトコルを指定する(sU)
```
$ sudo nmap -sU localhost

Starting Nmap 6.40 ( http://nmap.org ) at 2018-01-21 20:39 JST
Nmap scan report for localhost (127.0.0.1)
Host is up (0.000058s latency).
Other addresses for localhost (not scanned): 127.0.0.1
Not shown: 999 closed ports
PORT   STATE         SERVICE
68/udp open|filtered dhcpc

Nmap done: 1 IP address (1 host up) scanned in 50.48 seconds
```

ポート番号も指定する場合には次のようなコマンドになります
```
$ sudo nmap -sU -p 68 localhost

Starting Nmap 6.40 ( http://nmap.org ) at 2018-01-21 20:41 JST
Nmap scan report for localhost (127.0.0.1)
Host is up.
Other addresses for localhost (not scanned): 127.0.0.1
PORT   STATE         SERVICE
68/udp open|filtered dhcpc

Nmap done: 1 IP address (1 host up) scanned in 2.05 seconds
```

### OSを推定する
Oオプションを付与することによりOSを推定することが可能です。この場合にはsudoを必要とします。
上記では、Linuxが3.7-3.9であるだろうと判定されています。
```
$ sudo nmap -O localhost

Starting Nmap 6.40 ( http://nmap.org ) at 2018-01-21 20:36 JST
Nmap scan report for localhost (127.0.0.1)
Host is up (0.000045s latency).
Other addresses for localhost (not scanned): 127.0.0.1
Not shown: 994 closed ports
PORT     STATE SERVICE
22/tcp   open  ssh
25/tcp   open  smtp
80/tcp   open  http
443/tcp  open  https
8080/tcp open  http-proxy
8083/tcp open  us-srv
Device type: general purpose
Running: Linux 3.X
OS CPE: cpe:/o:linux:linux_kernel:3
OS details: Linux 3.7 - 3.9
Network Distance: 0 hops

OS detection performed. Please report any incorrect results at http://nmap.org/submit/ .
Nmap done: 1 IP address (1 host up) scanned in 1.84 seconds
```

上記を実行したマシンが次の通りなので
```
$ uname -a
Linux localhost.localdomain 3.10.0-693.el7.x86_64 #1 SMP Tue Aug 22 21:09:27 UTC 2017 x86_64 x86_64 x86_64 GNU/Linux
```

### OSとバージョンを検知しようとする
```
$ nmap -A localhost

Starting Nmap 6.40 ( http://nmap.org ) at 2018-01-21 20:43 JST
Nmap scan report for localhost (127.0.0.1)
Host is up (0.00032s latency).
Other addresses for localhost (not scanned): 127.0.0.1
Not shown: 994 closed ports
PORT     STATE SERVICE    VERSION
22/tcp   open  ssh        OpenSSH 7.4 (protocol 2.0)
| ssh-hostkey: 2048 59:2c:57:71:fa:6a:b2:c0:df:8f:b1:72:e3:b7:19:05 (RSA)
|_256 f3:cc:b9:70:fa:19:59:bd:35:f6:da:86:fe:e5:36:7a (ECDSA)
25/tcp   open  smtp       Postfix smtpd
|_smtp-commands: localhost.localdomain, PIPELINING, SIZE 10240000, VRFY, ETRN, ENHANCEDSTATUSCODES, 8BITMIME, DSN, 
80/tcp   open  http?
443/tcp  open  ssl/https?
|_http-title: Site doesn't have a title (text/html).
| ssl-cert: Subject: organizationName=Internet Widgits Pty Ltd/stateOrProvinceName=Some-State/countryName=AU
| Not valid before: 2018-02-25T08:29:53+00:00
|_Not valid after:  2019-02-25T08:29:53+00:00
|_ssl-date: 2028-01-09T03:16:07+00:00; +9y352d15h30m21s from local time.
8080/tcp open  http       Apache httpd 2.4.6 ((CentOS))
| http-methods: Potentially risky methods: TRACE
|_See http://nmap.org/nsedoc/scripts/http-methods.html
|_http-title: Apache HTTP Server Test Page powered by CentOS
8083/tcp open  us-srv?
1 service unrecognized despite returning data. If you know the service/version, please submit the following fingerprint at http://www.insecure.org/cgi-bin/servicefp-submit.cgi :
SF-Port443-TCP:V=6.40%T=SSL%I=7%D=1/21%Time=5A647CF3%P=x86_64-redhat-linux
SF:-gnu%r(GetRequest,1FE3,"HTTP/1\.0\x20200\x20ok\r\nContent-type:\x20text
SF:/html\r\n\r\n<HTML><BODY\x20BGCOLOR=\"#ffffff\">\n<pre>\n\ns_server\x20
SF:-accept\x20443\x20-cert\x20server\.crt\x20-key\x20server\.key\x20-www\x
SF:20-debug\x20\nSecure\x20Renegotiation\x20IS\x20supported\nCiphers\x20su
SF:pported\x20in\x20s_server\x20binary\nTLSv1/SSLv3:ECDHE-RSA-AES256-GCM-S
SF:HA384TLSv1/SSLv3:ECDHE-ECDSA-AES256-GCM-SHA384\nTLSv1/SSLv3:ECDHE-RSA-A
SF:ES256-SHA384\x20\x20TLSv1/SSLv3:ECDHE-ECDSA-AES256-SHA384\nTLSv1/SSLv3:
SF:ECDHE-RSA-AES256-SHA\x20\x20\x20\x20\x20TLSv1/SSLv3:ECDHE-ECDSA-AES256-
SF:SHA\x20\x20\x20\nTLSv1/SSLv3:DH-DSS-AES256-GCM-SHA384\x20TLSv1/SSLv3:DH
SF:E-DSS-AES256-GCM-SHA384\nTLSv1/SSLv3:DH-RSA-AES256-GCM-SHA384\x20TLSv1/
SF:SSLv3:DHE-RSA-AES256-GCM-SHA384\nTLSv1/SSLv3:DHE-RSA-AES256-SHA256\x20\
SF:x20\x20\x20TLSv1/SSLv3:DHE-DSS-AES256-SHA256\x20\x20\x20\x20\nTLSv1/SSL
SF:v3:DH-RSA-AES256-SHA256\x20\x20\x20\x20\x20TLSv1/SSLv3:DH-DSS-AES256-SH
SF:A256\x20\x20\x20\x20\x20\nTLSv1/SSLv3:DHE-RSA-AES256-SHA\x20\x20\x20\x2
SF:0\x20\x20\x20TLSv1/SSLv3:DHE-DSS-AES256-SHA\x20\x20\x20\x20\x20\x20\x20
SF:\nTLSv1/SSLv3:DH-RSA-AES256-SHA\x20\x20\x20\x20\x20\x20\x20\x20TLSv1/SS
SF:Lv3:DH-DSS-AES256-SHA\x20\x20\x20\x20\x20\x20\x20\x20")%r(FourOhFourReq
SF:uest,135D,"HTTP/1\.0\x20200\x20ok\r\nContent-type:\x20text/html\r\n\r\n
SF:<HTML><BODY\x20BGCOLOR=\"#ffffff\">\n<pre>\n\ns_server\x20-accept\x2044
SF:3\x20-cert\x20server\.crt\x20-key\x20server\.key\x20-www\x20-debug\x20\
SF:nSecure\x20Renegotiation\x20IS\x20supported\nCiphers\x20supported\x20in
SF:\x20s_server\x20binary\nTLSv1/SSLv3:ECDHE-RSA-AES256-GCM-SHA384TLSv1/SS
SF:Lv3:ECDHE-ECDSA-AES256-GCM-SHA384\nTLSv1/SSLv3:ECDHE-RSA-AES256-SHA384\
SF:x20\x20TLSv1/SSLv3:ECDHE-ECDSA-AES256-SHA384\nTLSv1/SSLv3:ECDHE-RSA-AES
SF:256-SHA\x20\x20\x20\x20\x20TLSv1/SSLv3:ECDHE-ECDSA-AES256-SHA\x20\x20\x
SF:20\nTLSv1/SSLv3:DH-DSS-AES256-GCM-SHA384\x20TLSv1/SSLv3:DHE-DSS-AES256-
SF:GCM-SHA384\nTLSv1/SSLv3:DH-RSA-AES256-GCM-SHA384\x20TLSv1/SSLv3:DHE-RSA
SF:-AES256-GCM-SHA384\nTLSv1/SSLv3:DHE-RSA-AES256-SHA256\x20\x20\x20\x20TL
SF:Sv1/SSLv3:DHE-DSS-AES256-SHA256\x20\x20\x20\x20\nTLSv1/SSLv3:DH-RSA-AES
SF:256-SHA256\x20\x20\x20\x20\x20TLSv1/SSLv3:DH-DSS-AES256-SHA256\x20\x20\
SF:x20\x20\x20\nTLSv1/SSLv3:DHE-RSA-AES256-SHA\x20\x20\x20\x20\x20\x20\x20
SF:TLSv1/SSLv3:DHE-DSS-AES256-SHA\x20\x20\x20\x20\x20\x20\x20\nTLSv1/SSLv3
SF::DH-RSA-AES256-SHA\x20\x20\x20\x20\x20\x20\x20\x20TLSv1/SSLv3:DH-DSS-AE
SF:S256-SHA\x20\x20\x20\x20\x20\x20\x20\x20");
Service Info: Host:  localhost.localdomain

Service detection performed. Please report any incorrect results at http://nmap.org/submit/ .
Nmap done: 1 IP address (1 host up) scanned in 276.36 seconds
```

### Cypherを確認する
```
$ nmap -v --script ssl-enum-ciphers -p 443 localhost

Starting Nmap 6.40 ( http://nmap.org ) at 2018-01-21 20:22 JST
NSE: Loaded 1 scripts for scanning.
NSE: Script Pre-scanning.
Initiating Ping Scan at 20:22
Scanning localhost (127.0.0.1) [2 ports]
Completed Ping Scan at 20:22, 0.00s elapsed (1 total hosts)
Initiating Connect Scan at 20:22
Scanning localhost (127.0.0.1) [1 port]
Discovered open port 443/tcp on 127.0.0.1
Completed Connect Scan at 20:22, 0.00s elapsed (1 total ports)
NSE: Script scanning 127.0.0.1.
Initiating NSE at 20:22
Completed NSE at 20:22, 3.60s elapsed
Nmap scan report for localhost (127.0.0.1)
Host is up (0.000066s latency).
Other addresses for localhost (not scanned): 127.0.0.1
PORT    STATE SERVICE
443/tcp open  https
| ssl-enum-ciphers: 
|   SSLv3: 
|     ciphers: 
|       TLS_DHE_RSA_WITH_3DES_EDE_CBC_SHA - strong
|       TLS_DHE_RSA_WITH_AES_128_CBC_SHA - strong
|       TLS_DHE_RSA_WITH_AES_256_CBC_SHA - strong
|       TLS_DHE_RSA_WITH_CAMELLIA_128_CBC_SHA - strong
|       TLS_DHE_RSA_WITH_CAMELLIA_256_CBC_SHA - strong
|       TLS_DHE_RSA_WITH_SEED_CBC_SHA - strong
|       TLS_ECDHE_RSA_WITH_3DES_EDE_CBC_SHA - strong
|       TLS_ECDHE_RSA_WITH_AES_128_CBC_SHA - strong
|       TLS_ECDHE_RSA_WITH_AES_256_CBC_SHA - strong
|       TLS_ECDHE_RSA_WITH_RC4_128_SHA - strong
|       TLS_RSA_WITH_3DES_EDE_CBC_SHA - strong
|       TLS_RSA_WITH_AES_128_CBC_SHA - strong
|       TLS_RSA_WITH_AES_256_CBC_SHA - strong
|       TLS_RSA_WITH_CAMELLIA_128_CBC_SHA - strong
|       TLS_RSA_WITH_CAMELLIA_256_CBC_SHA - strong
|       TLS_RSA_WITH_IDEA_CBC_SHA - weak
|       TLS_RSA_WITH_RC4_128_MD5 - strong
|       TLS_RSA_WITH_RC4_128_SHA - strong
|       TLS_RSA_WITH_SEED_CBC_SHA - strong
|     compressors: 
|       NULL
|   TLSv1.0: 
|     ciphers: 
|       TLS_DHE_RSA_WITH_3DES_EDE_CBC_SHA - strong
|       TLS_DHE_RSA_WITH_AES_128_CBC_SHA - strong
|       TLS_DHE_RSA_WITH_AES_256_CBC_SHA - strong
|       TLS_DHE_RSA_WITH_CAMELLIA_128_CBC_SHA - strong
|       TLS_DHE_RSA_WITH_CAMELLIA_256_CBC_SHA - strong
|       TLS_DHE_RSA_WITH_SEED_CBC_SHA - strong
|       TLS_ECDHE_RSA_WITH_3DES_EDE_CBC_SHA - strong
|       TLS_ECDHE_RSA_WITH_AES_128_CBC_SHA - strong
|       TLS_ECDHE_RSA_WITH_AES_256_CBC_SHA - strong
|       TLS_ECDHE_RSA_WITH_RC4_128_SHA - strong
|       TLS_RSA_WITH_3DES_EDE_CBC_SHA - strong
|       TLS_RSA_WITH_AES_128_CBC_SHA - strong
|       TLS_RSA_WITH_AES_256_CBC_SHA - strong
|       TLS_RSA_WITH_CAMELLIA_128_CBC_SHA - strong
|       TLS_RSA_WITH_CAMELLIA_256_CBC_SHA - strong
|       TLS_RSA_WITH_IDEA_CBC_SHA - weak
|       TLS_RSA_WITH_RC4_128_MD5 - strong
|       TLS_RSA_WITH_RC4_128_SHA - strong
|       TLS_RSA_WITH_SEED_CBC_SHA - strong
|     compressors: 
|       NULL
|   TLSv1.1: 
|     ciphers: 
|       TLS_DHE_RSA_WITH_3DES_EDE_CBC_SHA - strong
|       TLS_DHE_RSA_WITH_AES_128_CBC_SHA - strong
|       TLS_DHE_RSA_WITH_AES_256_CBC_SHA - strong
|       TLS_DHE_RSA_WITH_CAMELLIA_128_CBC_SHA - strong
|       TLS_DHE_RSA_WITH_CAMELLIA_256_CBC_SHA - strong
|       TLS_DHE_RSA_WITH_SEED_CBC_SHA - strong
|       TLS_ECDHE_RSA_WITH_3DES_EDE_CBC_SHA - strong
|       TLS_ECDHE_RSA_WITH_AES_128_CBC_SHA - strong
|       TLS_ECDHE_RSA_WITH_AES_256_CBC_SHA - strong
|       TLS_ECDHE_RSA_WITH_RC4_128_SHA - strong
|       TLS_RSA_WITH_3DES_EDE_CBC_SHA - strong
|       TLS_RSA_WITH_AES_128_CBC_SHA - strong
|       TLS_RSA_WITH_AES_256_CBC_SHA - strong
|       TLS_RSA_WITH_CAMELLIA_128_CBC_SHA - strong
|       TLS_RSA_WITH_CAMELLIA_256_CBC_SHA - strong
|       TLS_RSA_WITH_IDEA_CBC_SHA - weak
|       TLS_RSA_WITH_RC4_128_MD5 - strong
|       TLS_RSA_WITH_RC4_128_SHA - strong
|       TLS_RSA_WITH_SEED_CBC_SHA - strong
|     compressors: 
|       NULL
|   TLSv1.2: 
|     ciphers: 
|       TLS_DHE_RSA_WITH_3DES_EDE_CBC_SHA - strong
|       TLS_DHE_RSA_WITH_AES_128_CBC_SHA - strong
|       TLS_DHE_RSA_WITH_AES_128_CBC_SHA256 - strong
|       TLS_DHE_RSA_WITH_AES_128_GCM_SHA256 - strong
|       TLS_DHE_RSA_WITH_AES_256_CBC_SHA - strong
|       TLS_DHE_RSA_WITH_AES_256_CBC_SHA256 - strong
|       TLS_DHE_RSA_WITH_AES_256_GCM_SHA384 - strong
|       TLS_DHE_RSA_WITH_CAMELLIA_128_CBC_SHA - strong
|       TLS_DHE_RSA_WITH_CAMELLIA_256_CBC_SHA - strong
|       TLS_DHE_RSA_WITH_SEED_CBC_SHA - strong
|       TLS_ECDHE_RSA_WITH_3DES_EDE_CBC_SHA - strong
|       TLS_ECDHE_RSA_WITH_AES_128_CBC_SHA - strong
|       TLS_ECDHE_RSA_WITH_AES_128_CBC_SHA256 - strong
|       TLS_ECDHE_RSA_WITH_AES_128_GCM_SHA256 - strong
|       TLS_ECDHE_RSA_WITH_AES_256_CBC_SHA - strong
|       TLS_ECDHE_RSA_WITH_AES_256_CBC_SHA384 - strong
|       TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384 - strong
|       TLS_ECDHE_RSA_WITH_RC4_128_SHA - strong
|       TLS_RSA_WITH_3DES_EDE_CBC_SHA - strong
|       TLS_RSA_WITH_AES_128_CBC_SHA - strong
|       TLS_RSA_WITH_AES_128_CBC_SHA256 - strong
|       TLS_RSA_WITH_AES_128_GCM_SHA256 - strong
|       TLS_RSA_WITH_AES_256_CBC_SHA - strong
|       TLS_RSA_WITH_AES_256_CBC_SHA256 - strong
|       TLS_RSA_WITH_AES_256_GCM_SHA384 - strong
|       TLS_RSA_WITH_CAMELLIA_128_CBC_SHA - strong
|       TLS_RSA_WITH_CAMELLIA_256_CBC_SHA - strong
|       TLS_RSA_WITH_IDEA_CBC_SHA - weak
|       TLS_RSA_WITH_RC4_128_MD5 - strong
|       TLS_RSA_WITH_RC4_128_SHA - strong
|       TLS_RSA_WITH_SEED_CBC_SHA - strong
|     compressors: 
|       NULL
|_  least strength: weak

NSE: Script Post-scanning.
Read data files from: /usr/bin/../share/nmap
Nmap done: 1 IP address (1 host up) scanned in 3.66 seconds
```
