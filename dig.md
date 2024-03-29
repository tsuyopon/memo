# 概要
dig(Domain Information Grouper)についてまとめる
digコマンドはdigパッケージ、bind-utils(centos)、dnsutils(ubuntu)などで提供されているようです。

コマンドの使い方は単純で以下の通りです
```
$ dig @server domain query-type
```

# 詳細
### digとnslookupの違い
digはDNSの問い合わせに近い形式で出力し、nslookupは問い合わせ結果を出力する。
ネットワークトラブルシューティングでは、digを使ったほうが良いとのこと

nslookupの時は次のような出力となる
```
$ nslookup www.yahoo.co.jp
Server:		192.168.3.1
Address:	192.168.3.1#53

Non-authoritative answer:
www.yahoo.co.jp	canonical name = edge.g.yimg.jp.
Name:	edge.g.yimg.jp
Address: 182.22.31.252
```

digの場合には次のような出力となり、実際のDNSサーバの出力結果と似たような形になる。
```
$ dig www.yahoo.co.jp

; <<>> DiG 9.8.3-P1 <<>> www.yahoo.co.jp
;; global options: +cmd
;; Got answer:
;; ->>HEADER<<- opcode: QUERY, status: NOERROR, id: 8526
;; flags: qr rd ra; QUERY: 1, ANSWER: 2, AUTHORITY: 2, ADDITIONAL: 2

;; QUESTION SECTION:
;www.yahoo.co.jp.		IN	A

;; ANSWER SECTION:
www.yahoo.co.jp.	834	IN	CNAME	edge.g.yimg.jp.
edge.g.yimg.jp.		20	IN	A	182.22.31.252

;; AUTHORITY SECTION:
g.yimg.jp.		860	IN	NS	gns02.yahoo.co.jp.
g.yimg.jp.		860	IN	NS	gns12.yahoo.co.jp.

;; ADDITIONAL SECTION:
gns02.yahoo.co.jp.	211	IN	A	118.151.254.148
gns12.yahoo.co.jp.	205	IN	A	124.83.255.100

;; Query time: 10 msec
;; SERVER: 192.168.3.1#53(192.168.3.1)
;; WHEN: Sat Jan 27 08:47:46 2018
;; MSG SIZE  rcvd: 147
```

- QUERY SECTION: 問い合わせした内容を表示する
- ANSWER SECTION: 問い合わせに対する結果を表示する
- AUTHORITY SECTION: 応答した権威サーバを含む権威サーバ群(権威サーバのNSレコード)
- ADDITIONAL SECTION: 権威サーバのAレコード(権威サーバのSOAレコードに登録されるグルーレコード)

### flagsに表示される意味について

```
$ dig www.yahoo.co.jp

; <<>> DiG 9.8.3-P1 <<>> www.yahoo.co.jp
;; global options: +cmd
;; Got answer:
;; ->>HEADER<<- opcode: QUERY, status: NOERROR, id: 8526
;; flags: qr rd ra; QUERY: 1, ANSWER: 2, AUTHORITY: 2, ADDITIONAL: 2
(snip)
```

DNSサーバからの応答内容を表しています。
RFC1036に以下が定義されています。
- QR:  specifies whether this message is a query (0), or a response (1)
  - メッセージがサーバからの回答 (response) の場合は QR が表示されます。 dig コマンド実行結果は「サーバからの回答」ですので QR は必ず表示されます。
- OPCODE A four bit field, only valid values: 0,1,2
- AA (Authoritative Answer)
  - 回答したネームサーバが、問い合わせたドメイン名について 権威を持っている場合は AA が表示されます。
- TC TrunCation (truncated due to length greater than that permitted on the transmission channel)
  - メッセージの切り詰めが行われた場合 (メッセージが UDP の 制限である 512byte 超過) TC が表示されます。
- RD (Recursion Desired)
  - 再帰的問い合わせを要求の場合に表示されますが、 RD は常に表示されるようです。
- RA (Recursion Available)
  - サーバが再帰的問い合わせをサポートしている場合は RA が表示されます。
- Z Reserved for future use. Must be zero

なお、RFC4036にはDNSSECに関連あるフラグも定義されています
- CD (Checking Disabled)
  - 署名のチェックを行なっていない
- AD (Authentic Data)
  - 署名が検証できた正しいデータである


参考: https://serverfault.com/questions/729025/what-are-all-the-flags-in-a-dig-response/729121


### digコマンドのレスポンスコードについて
RFC1035 4.1.1 Header section formatに下記内容で定義されています。
```
0 = NOERR, no error
1 = FORMERR, format error (unable to understand the query)
2 = SERVFAIL, name server problem
3 = NXDOMAIN, domain name does not exist
4 = NOTIMPL, not implemented
5 = REFUSED (e.g., refused zone transfer requests)
```

### 回答結果を短く得る
```
$ dig www.yahoo.co.jp +short
edge.g.yimg.jp.
183.79.249.124
```

### 指定したタイプを取得する
いくつか具体例を示します。ヤフーやgoogleの例です。 (出力を抑制するために+shortの簡易表示にしています)


```
$ dig -t A www.yahoo.co.jp +short
edge12.g.yimg.jp.
182.22.25.252

$ dig -t AAAA www.yahoo.co.jp +short
edge12.g.yimg.jp.

$ dig -t NS yahoo.co.jp +short
ns11.yahoo.co.jp.
ns02.yahoo.co.jp.
ns01.yahoo.co.jp.
ns12.yahoo.co.jp.

$ dig -t MX yahoo.co.jp +short
10 mx5.mail.yahoo.co.jp.
10 mx1.mail.yahoo.co.jp.
10 mx2.mail.yahoo.co.jp.
10 mx3.mail.yahoo.co.jp.

$ dig -t SOA yahoo.co.jp +short
yahoo.co.jp. postmaster.yahoo.co.jp. 2202100015 1800 900 86400 900

$ dig -t TXT google.com +short
"MS=E4A68B9AB2BB9670BCE15412F62916164C0B20BB"
"google-site-verification=TV9-DBe4R80X4v0M4U_bd_J9cpOJM0nikft0jAgjmsQ"
"google-site-verification=wD8N7i1JTNTkezJ49swvWW48f8_9xveREV4oB-0Hf5o"
"docusign=05958488-4752-4ef2-95eb-aa7ba8a3bd0e"
"globalsign-smime-dv=CDYX+XFHUw2wml6/Gb8+59BsH31KzUr6c1l2BPvqKX8="
"v=spf1 include:_spf.google.com ~all"
"apple-domain-verification=30afIBcvSuDV2PLX"
"facebook-domain-verification=22rm551cu4k0ab0bxsw536tlds4h95"
"docusign=1b0a6754-49b1-4db5-8540-d2c12664b289"
```

```
$ dig -t MX google.com +short
30 alt2.aspmx.l.google.com.
50 alt4.aspmx.l.google.com.
20 alt1.aspmx.l.google.com.
40 alt3.aspmx.l.google.com.
10 aspmx.l.google.com.
```

### 全てのリソースレコードを取得する(ANY)
```
$ dig -t ANY yahoo.co.jp +short
"v=spf1 include:spf.yahoo.co.jp ~all"
"google-site-verification=GvbYgNin-mY73VbS4IJK2D8nI3tHEf2NpRdy76VYqBU"
10 mx2.mail.yahoo.co.jp.
10 mx3.mail.yahoo.co.jp.
10 mx5.mail.yahoo.co.jp.
10 mx1.mail.yahoo.co.jp.
0 issue "globalsign.com"
0 issue "cybertrust.ne.jp"
0 issue "digicert.com;cansignhttpexchanges=yes"
0 iodef "mailto:nic-admin@mail.yahoo.co.jp"
yahoo.co.jp. postmaster.yahoo.co.jp. 2202100015 1800 900 86400 900
183.79.217.124
183.79.250.251
183.79.219.252
183.79.250.123
182.22.25.252
182.22.16.251
ns11.yahoo.co.jp.
ns01.yahoo.co.jp.
ns02.yahoo.co.jp.
ns12.yahoo.co.jp.
```

### 特定のセクションだけ取得する

DNSパケットはHEADER, QUESTION, ANSWER, AUTHORITY, ADDTIONALの5つのセクションから構成されます。
+noallをつけると全ての出力が抑制されます。そして +ansを同時に付与することでANSWERセクションだけ表示するなど表示したいセクションを絞ることが可能です。

- HEADER SECTION
```
$  dig +noall +comments www.yahoo.co.jp
;; Got answer:
;; ->>HEADER<<- opcode: QUERY, status: NOERROR, id: 9976
;; flags: qr rd ra; QUERY: 1, ANSWER: 2, AUTHORITY: 2, ADDITIONAL: 1

;; OPT PSEUDOSECTION:
; EDNS: version: 0, flags:; udp: 1232
```

- QUESTION SECTION
```
$ dig www.yahoo.co.jp +noall +question

; <<>> DiG 9.10.6 <<>> www.yahoo.co.jp +noall +question
;; global options: +cmd
;www.yahoo.co.jp.		IN	A
```

- ANSWER SECTION
```
$ dig +noall +ans www.yahoo.co.jp
www.yahoo.co.jp.	514	IN	CNAME	edge.g.yimg.jp.
edge.g.yimg.jp.		19	IN	A	183.79.249.252
```

- AUTHORITY SECTION
```
$ dig +noall +auth www.yahoo.co.jp
g.yimg.jp.		333	IN	NS	gns02.yahoo.co.jp.
g.yimg.jp.		333	IN	NS	gns12.yahoo.co.jp.
```

- ADDITIONAL SECTION
```
$ dig google.com +noall +additional

; <<>> DiG 9.10.6 <<>> google.com +noall +additional
;; global options: +cmd
ns1.google.com.		212267	IN	AAAA	2001:4860:4802:32::a
ns2.google.com.		275259	IN	AAAA	2001:4860:4802:34::a
ns3.google.com.		139681	IN	AAAA	2001:4860:4802:36::a
ns4.google.com.		305280	IN	AAAA	2001:4860:4802:38::a
ns1.google.com.		218218	IN	A	216.239.32.10
ns2.google.com.		219114	IN	A	216.239.34.10
ns3.google.com.		275187	IN	A	216.239.36.10
ns4.google.com.		157675	IN	A	216.239.38.10
```

- 実行コマンドの表示
```
$ dig +noall +cmd www.yahoo.co.jp

; <<>> DiG 9.8.3-P1 <<>> +noall +cmd www.yahoo.co.jp
;; global options: +cmd
```

- 統計情報の表示
```
$ dig www.yahoo.co.jp +noall +stats

; <<>> DiG 9.10.6 <<>> www.yahoo.co.jp +noall +stats
;; global options: +cmd
;; Query time: 19 msec
;; SERVER: 2400:2412:ec0:9d00:1111:1111:1111:1111#53(2400:2412:ec0:9d00:1111:1111:1111:1111)
;; WHEN: Sat Feb 12 20:52:50 JST 2022
;; MSG SIZE  rcvd: 128
```

### 対象ドメインの権威DNSサーバを取得する
```
$ dig yahoo.co.jp +nssearch
SOA yahoo.co.jp. postmaster.yahoo.co.jp. 2202100015 1800 900 86400 900 from server 118.151.254.149 in 7 ms.
SOA yahoo.co.jp. postmaster.yahoo.co.jp. 2202100015 1800 900 86400 900 from server 118.151.254.133 in 7 ms.
SOA yahoo.co.jp. postmaster.yahoo.co.jp. 2202100015 1800 900 86400 900 from server 124.83.255.37 in 17 ms.
SOA yahoo.co.jp. postmaster.yahoo.co.jp. 2202100015 1800 900 86400 900 from server 124.83.255.101 in 16 ms.
```

### IPアドレスの逆引きを行う
xオプションを指定した後にIPアドレスを指定すればよい。
```
$ dig -x 8.8.4.4

; <<>> DiG 9.8.3-P1 <<>> -x 8.8.4.4
;; global options: +cmd
;; Got answer:
;; ->>HEADER<<- opcode: QUERY, status: NOERROR, id: 7674
;; flags: qr rd ra; QUERY: 1, ANSWER: 1, AUTHORITY: 2, ADDITIONAL: 3

;; OPT PSEUDOSECTION:
; EDNS: version: 0, flags:; udp: 4096
;; QUESTION SECTION:
;4.4.8.8.in-addr.arpa.		IN	PTR

;; ANSWER SECTION:
4.4.8.8.in-addr.arpa.	39544	IN	PTR	google-public-dns-b.google.com.

;; AUTHORITY SECTION:
8.in-addr.arpa.		15656	IN	NS	ns1.level3.net.
8.in-addr.arpa.		15656	IN	NS	ns2.level3.net.

;; ADDITIONAL SECTION:
ns1.level3.net.		327	IN	A	209.244.0.1
ns2.level3.net.		327	IN	A	209.244.0.2

;; Query time: 10 msec
;; SERVER: 192.168.3.1#53(192.168.3.1)
;; WHEN: Sat Jan 27 09:29:59 2018
;; MSG SIZE  rcvd: 171
```

### DNSサーバを指定する
8.8.8.8や4.4.4.4などはGoogle Public DNSとして提供されているのでこれを使って問い合わせて見ます。
- https://developers.google.com/speed/public-dns/

ではDNSサーバを指定してアクセスします。
```
$ dig @8.8.8.8 www.google.com

; <<>> DiG 9.8.3-P1 <<>> @8.8.8.8 www.google.com
; (1 server found)
;; global options: +cmd
;; Got answer:
;; ->>HEADER<<- opcode: QUERY, status: NOERROR, id: 25778
;; flags: qr rd ra; QUERY: 1, ANSWER: 1, AUTHORITY: 0, ADDITIONAL: 0

;; QUESTION SECTION:
;www.google.com.			IN	A

;; ANSWER SECTION:
www.google.com.		109	IN	A	216.58.221.4

;; Query time: 13 msec
;; SERVER: 8.8.8.8#53(8.8.8.8)
;; WHEN: Sat Jan 27 08:57:41 2018
;; MSG SIZE  rcvd: 48
```

### ポート番号を指定する
```
$ dig xxx.co.jp -p 53
```

### レコードを指定して取得する
以下はNSを指定した例です
```
$ dig www.google.com NS

; <<>> DiG 9.8.3-P1 <<>> www.google.com NS
;; global options: +cmd
;; Got answer:
;; ->>HEADER<<- opcode: QUERY, status: NOERROR, id: 28199
;; flags: qr rd ra; QUERY: 1, ANSWER: 0, AUTHORITY: 1, ADDITIONAL: 1

;; OPT PSEUDOSECTION:
; EDNS: version: 0, flags:; udp: 4096
;; QUESTION SECTION:
;www.google.com.			IN	NS

;; AUTHORITY SECTION:
google.com.		60	IN	SOA	ns1.google.com. dns-admin.google.com. 183402538 900 900 1800 60

;; Query time: 53 msec
;; SERVER: 192.168.3.1#53(192.168.3.1)
;; WHEN: Sat Jan 27 09:31:20 2018
;; MSG SIZE  rcvd: 93
```

以下はSOAを指定した例です。
```
$ dig www.google.com SOA
; <<>> DiG 9.8.3-P1 <<>> www.google.com SOA
;; global options: +cmd
;; Got answer:
;; ->>HEADER<<- opcode: QUERY, status: NOERROR, id: 29165
;; flags: qr rd ra; QUERY: 1, ANSWER: 0, AUTHORITY: 1, ADDITIONAL: 1

;; OPT PSEUDOSECTION:
; EDNS: version: 0, flags:; udp: 4096
;; QUESTION SECTION:
;www.google.com.			IN	SOA

;; AUTHORITY SECTION:
google.com.		60	IN	SOA	ns1.google.com. dns-admin.google.com. 183448256 900 900 1800 60

;; Query time: 55 msec
;; SERVER: 192.168.3.1#53(192.168.3.1)
;; WHEN: Sat Jan 27 09:31:28 2018
;; MSG SIZE  rcvd: 93
```

### 見やすい形式にする
通常はSOAなどは1行出力ですが
```
$ dig google.com soa +noall +answer 

; <<>> DiG 9.10.6 <<>> google.com soa +noall +answer
;; global options: +cmd
google.com.		42	IN	SOA	ns1.google.com. dns-admin.google.com. 427960901 900 900 1800 60
```

+multilineを付与すると複数行として表示してくれます。
```
$ dig google.com soa +noall +answer +multiline

; <<>> DiG 9.8.3-P1 <<>> google.com soa +noall +answer +multiline
;; global options: +cmd
google.com.		60 IN SOA ns1.google.com. dns-admin.google.com. (
				183448256  ; serial
				900        ; refresh (15 minutes)
				900        ; retry (15 minutes)
				1800       ; expire (30 minutes)
				60         ; minimum (1 minute)
				)
```

### 応答を返すDNSキャッシュサーバを確認する
+identifyを付与することでDNSキャッシュサーバのIPアドレスが確認できます。

以下の例では192.168.3.1とローカルIPになっています。
```
$ dig -4 www.yahoo.co.jp +short +identify
edge12.g.yimg.jp. from server 192.168.3.1 in 14 ms.
182.22.25.252 from server 192.168.3.1 in 14 ms.

$ dig -6 www.yahoo.co.jp +short +identify
edge12.g.yimg.jp. from server 2400:2412:ec0:9d00:1111:1111:1111:1111 in 12 ms.
182.22.25.252 from server 2400:2412:ec0:9d00:1111:1111:1111:1111 in 12 ms.
```

8.8.8.8のサーバを指定してみると、次のように8.8.8.8であることがわかります。
```
$ dig @8.8.8.8 www.yahoo.co.jp +short +identify
edge12.g.yimg.jp. from server 8.8.8.8 in 14 ms.
183.79.250.251 from server 8.8.8.8 in 14 ms.
```

### ルートDNSから問い合わせを行い、結果を順番に出力する
```
$ dig www.google.com +trace

; <<>> DiG 9.8.3-P1 <<>> www.google.com +trace
;; global options: +cmd
.			191399	IN	NS	e.root-servers.net.
.			191399	IN	NS	d.root-servers.net.
.			191399	IN	NS	f.root-servers.net.
.			191399	IN	NS	i.root-servers.net.
.			191399	IN	NS	c.root-servers.net.
.			191399	IN	NS	a.root-servers.net.
.			191399	IN	NS	k.root-servers.net.
.			191399	IN	NS	l.root-servers.net.
.			191399	IN	NS	b.root-servers.net.
.			191399	IN	NS	j.root-servers.net.
.			191399	IN	NS	g.root-servers.net.
.			191399	IN	NS	h.root-servers.net.
.			191399	IN	NS	m.root-servers.net.
;; Received 811 bytes from 192.168.3.1#53(192.168.3.1) in 217 ms

com.			172800	IN	NS	g.gtld-servers.net.
com.			172800	IN	NS	f.gtld-servers.net.
com.			172800	IN	NS	i.gtld-servers.net.
com.			172800	IN	NS	j.gtld-servers.net.
com.			172800	IN	NS	l.gtld-servers.net.
com.			172800	IN	NS	m.gtld-servers.net.
com.			172800	IN	NS	b.gtld-servers.net.
com.			172800	IN	NS	k.gtld-servers.net.
com.			172800	IN	NS	a.gtld-servers.net.
com.			172800	IN	NS	d.gtld-servers.net.
com.			172800	IN	NS	e.gtld-servers.net.
com.			172800	IN	NS	h.gtld-servers.net.
com.			172800	IN	NS	c.gtld-servers.net.
;; Received 492 bytes from 199.9.14.201#53(199.9.14.201) in 344 ms

google.com.		172800	IN	NS	ns2.google.com.
google.com.		172800	IN	NS	ns1.google.com.
google.com.		172800	IN	NS	ns3.google.com.
google.com.		172800	IN	NS	ns4.google.com.
;; Received 168 bytes from 192.43.172.30#53(192.43.172.30) in 102 ms

www.google.com.		300	IN	A	216.58.199.228
;; Received 48 bytes from 216.239.36.10#53(216.239.36.10) in 48 ms
```

### TCPで問い合わせを行う
通常はdigはUDPで問い合わせを行っているのだが、応答サイズが512を超える場合にはTCPでの問い合わせに変更するようになっている。
これを最初からTCPで問合せするためには+vcオプションを付与します。このオプションは+tcpでも同じです。
```
$ dig www.yahoo.co.jp +vc
または
$ dig www.yahoo.co.jp +tcp
```

### TC=1ビットが帰ってきても、TCP問い合わせを行わずに終了する(つまり、TCPフォールバックしない)
```
$ dig google.com +ignore
```

### ENDS0を有効にする
デフォルトはEDNSは無効であり、BIND9.9付属からはデフォルトで有効。
```
$ dig www.yahoo.co.jp +edns=0
```

### DNSSECで問い合わせを行う
```
$ dig www.yahoo.co.jp +dnssec
```

### DNSSEC対応ゾーンを確認する
```
dig @127.0.0.1 +dnssec ホスト名 soa
```

### 署名の検証を行わない

cd(checking disabled)フラグをセットする
```
$ dig @127.0.0.1 +cd ホスト名 soa
```

### 再起問い合わせを行わない
対象となるDNSサーバで保持しているキャッシュでのみ問い合わせを行う
```
$ dig www.yahoo.co.jp +norecurse
```

### TLD DNSからトレースする
+traceオプションで表示してくれます。ServFailなどの時にルートゾーンから辿ってどこでコケているかなど探る時に便利です。
```
$ dig yahoo.co.jp +trace

; <<>> DiG 9.10.6 <<>> yahoo.co.jp +trace
;; global options: +cmd
.			317867	IN	NS	l.root-servers.net.
.			317867	IN	NS	d.root-servers.net.
.			317867	IN	NS	e.root-servers.net.
.			317867	IN	NS	m.root-servers.net.
.			317867	IN	NS	i.root-servers.net.
.			317867	IN	NS	k.root-servers.net.
.			317867	IN	NS	j.root-servers.net.
.			317867	IN	NS	h.root-servers.net.
.			317867	IN	NS	b.root-servers.net.
.			317867	IN	NS	c.root-servers.net.
.			317867	IN	NS	f.root-servers.net.
.			317867	IN	NS	a.root-servers.net.
.			317867	IN	NS	g.root-servers.net.
.			516109	IN	RRSIG	NS 8 0 518400 20220225050000 20220212040000 9799 . Utn1eft4h1tcM/snPYO6CoZm6p3kEdOnXOr3k8TAZnbmpRgiLvUBlH9Q VcizqoJLs402MVujO2wBOGQ/ONNn99POsqa4q16nXcHX0orzql9IFyjH /JtFlPMBsbgbN4CbpIptD7QG+JA9qPbzqZfGMPq9pAhWry3X01duw8cl UJQS2zHvQ+QvLKjFpMba6RMz9YaJ2WIaucUso5TPTN84JRg5I4q8Cjxn G9G9+YuvNZY2GnqUmTwEdRo70VDkOcQIxZxUCUwrwuPf+U/0VasY2HtB tmV3ha9KPhddRwl5JqVh4NZnXTCwLdDu8EXofzUBBhzqvqZaK64kfT44 ryKckQ==
;; Received 1097 bytes from 2400:2412:ec0:9d00:1111:1111:1111:1111#53(2400:2412:ec0:9d00:1111:1111:1111:1111) in 25 ms

jp.			172800	IN	NS	a.dns.jp.
jp.			172800	IN	NS	b.dns.jp.
jp.			172800	IN	NS	c.dns.jp.
jp.			172800	IN	NS	d.dns.jp.
jp.			172800	IN	NS	e.dns.jp.
jp.			172800	IN	NS	f.dns.jp.
jp.			172800	IN	NS	g.dns.jp.
jp.			172800	IN	NS	h.dns.jp.
jp.			86400	IN	DS	18100 8 2 C5242231AB0B249800926B3D700349CC76374B7505DD4101FEF8C54B BB464C6B
jp.			86400	IN	RRSIG	DS 8 1 86400 20220225050000 20220212040000 9799 . Pa6nh3O49Ptz/RaTC8Ft42+Ypkp0g5wO4bkZqGkD8sSZ+tqiuRtIrQkU x0wNUNGkSfJDtqdWtcO9arkxW4o1wU2aI/ruiqWD1+tab2+tq/wJPqYu tvb51fcXD0lWXlvVatnwgUQX+TfahjHicVJKno5M7AWy2P0aoxWroD3d 5dlF1amxDkDe+glXPs0+iw6zlF0z//6nk9s/E4rNYAyjN9hN1+EgCs2P 3Tu0soEyjh+Kutv6sKyeqJlmwVu4T6Ac0nKjoTYrFiDqV8r3+dRM0Gg0 +A4xH5MKwk5ETIG7XalHFWIQX3zNjTCUS1JBw3fss+NHQA0SZGGVumW7 dM6qQQ==
;; Received 831 bytes from 192.58.128.30#53(j.root-servers.net) in 83 ms

yahoo.co.jp.		86400	IN	NS	ns02.yahoo.co.jp.
yahoo.co.jp.		86400	IN	NS	ns11.yahoo.co.jp.
yahoo.co.jp.		86400	IN	NS	ns01.yahoo.co.jp.
yahoo.co.jp.		86400	IN	NS	ns12.yahoo.co.jp.
CC0SS2L0ICPPV6QD9MHOO3L2DT6M9D67.jp. 900 IN NSEC3 1 1 8 473CAF4BBE CC9KFOFEKFJSISR3DR99NAMQN4LIR6F8  TXT RRSIG
CC0SS2L0ICPPV6QD9MHOO3L2DT6M9D67.jp. 900 IN RRSIG NSEC3 8 2 900 20220307174509 20220205174509 38121 jp. p3oEqf04l3KAASweg0E+v1dOFliXdMVZZQR9Tdl8JqbQf7tvHmx5DRif yst556aqOXosb4lvQNb11Aqv96mx9WC4X7IV+yNoHXYEDAlR4sswgIVl HBlP9T4Mxu7rYuqfgvqtFDO2rP1VjRIMTE6EtGwPlJHTnzgSKNDI4HE1 WsY=
76S5LROE5MHM7FMTCHUPD8V3TR766SUB.jp. 900 IN NSEC3 1 1 8 473CAF4BBE 771CVVVEGRVOHO7M8H72GFMM5RI3DKU9  TXT RRSIG
76S5LROE5MHM7FMTCHUPD8V3TR766SUB.jp. 900 IN RRSIG NSEC3 8 2 900 20220307174509 20220205174509 38121 jp. TmUUjmL4FLXFlqG7jUd8mVrDyCMWdFzP4XNuPtZDI6P7F9irfPf6HGzZ FKjWFD0R7RWLN0PbENrj62U51AIUcwxxfiUHvmIWIf3KNjwhkbLx8/te aTxYwdoQIYT5pIbvfsstmaz0z7DDoH58mkZd4qGEcLgmF4bYNUusaNOy Kz4=
;; Received 672 bytes from 2a01:8840:1bc::25#53(h.dns.jp) in 107 ms

yahoo.co.jp.		300	IN	A	183.79.219.252
yahoo.co.jp.		300	IN	A	183.79.250.251
yahoo.co.jp.		300	IN	A	183.79.217.124
yahoo.co.jp.		300	IN	A	183.79.250.123
yahoo.co.jp.		300	IN	A	182.22.16.251
yahoo.co.jp.		300	IN	A	182.22.25.252
yahoo.co.jp.		900	IN	NS	ns02.yahoo.co.jp.
yahoo.co.jp.		900	IN	NS	ns12.yahoo.co.jp.
yahoo.co.jp.		900	IN	NS	ns01.yahoo.co.jp.
yahoo.co.jp.		900	IN	NS	ns11.yahoo.co.jp.
;; Received 276 bytes from 124.83.255.101#53(ns12.yahoo.co.jp) in 13 ms
```

### ルートから非再起問い合わせをしてみる。
まずはルートを確認します。
```
$ dig -t NS . +short
f.root-servers.net.
h.root-servers.net.
e.root-servers.net.
g.root-servers.net.
k.root-servers.net.
c.root-servers.net.
i.root-servers.net.
b.root-servers.net.
l.root-servers.net.
j.root-servers.net.
a.root-servers.net.
m.root-servers.net.
d.root-servers.net.
``` 

続いて、ルートサーバを1つ適当に選択して、www.yahoo.co.jpに非再起で問い合わせると以下の応答が返ってきます。
```
$ dig @d.root-servers.net www.yahoo.co.jp +norecurse 

(snip)

;; AUTHORITY SECTION:
jp.			172800	IN	NS	a.dns.jp.
jp.			172800	IN	NS	b.dns.jp.
jp.			172800	IN	NS	c.dns.jp.
jp.			172800	IN	NS	d.dns.jp.
jp.			172800	IN	NS	e.dns.jp.
jp.			172800	IN	NS	f.dns.jp.
jp.			172800	IN	NS	g.dns.jp.
jp.			172800	IN	NS	h.dns.jp.

;; ADDITIONAL SECTION:
a.dns.jp.		172800	IN	AAAA	2001:dc4::1
b.dns.jp.		172800	IN	AAAA	2001:dc2::1
c.dns.jp.		172800	IN	AAAA	2001:502:ad09::5
d.dns.jp.		172800	IN	AAAA	2001:240::53
e.dns.jp.		172800	IN	AAAA	2001:200:c000::35
f.dns.jp.		172800	IN	AAAA	2001:2f8:0:100::153
h.dns.jp.		172800	IN	AAAA	2a01:8840:1bc::25
a.dns.jp.		172800	IN	A	203.119.1.1
b.dns.jp.		172800	IN	A	202.12.30.131
c.dns.jp.		172800	IN	A	156.154.100.5
d.dns.jp.		172800	IN	A	210.138.175.244
e.dns.jp.		172800	IN	A	192.50.43.53
f.dns.jp.		172800	IN	A	150.100.6.8
g.dns.jp.		172800	IN	A	203.119.40.1
h.dns.jp.		172800	IN	A	161.232.72.25

(snip)
```

続いて、「jp」ゾーンのネームサーバは8つあることがわかりました。
どれか1つを選択して、再び非再起で問い合わせます。
```
$ dig @a.dns.jp www.yahoo.co.jp +norecurse 

(snip)

;; AUTHORITY SECTION:
yahoo.co.jp.		86400	IN	NS	ns02.yahoo.co.jp.
yahoo.co.jp.		86400	IN	NS	ns11.yahoo.co.jp.
yahoo.co.jp.		86400	IN	NS	ns12.yahoo.co.jp.
yahoo.co.jp.		86400	IN	NS	ns01.yahoo.co.jp.

;; ADDITIONAL SECTION:
ns12.yahoo.co.jp.	86400	IN	A	124.83.255.101
ns11.yahoo.co.jp.	86400	IN	A	124.83.255.37
ns02.yahoo.co.jp.	86400	IN	A	118.151.254.149
ns01.yahoo.co.jp.	86400	IN	A	118.151.254.133

(snip)
```

「jp」ゾーンに問い合わせを行うと、次に「yahoo.co.jp」ゾーンのネームサーバの応答が返ってきました。
yahoo.co.jpのネームサーバがnsXX.yahoo.co.jpの4台であることがわかります。
このうち1台を指定して試してみます。
www.yahoo.co.jpはedge12.g.yimg.jpのCNAMEとなっていることがわかりました。
AUTHORITY SECTIONには上記の権威サーバのNSが含まれています。
合わせてADDITIONAL SECTIONにはそのNSのIPがあります。
```
$ dig @ns02.yahoo.co.jp  www.yahoo.co.jp +norecurse 

; <<>> DiG 9.10.6 <<>> @ns02.yahoo.co.jp www.yahoo.co.jp +norecurse
; (1 server found)
;; global options: +cmd
;; Got answer:
;; ->>HEADER<<- opcode: QUERY, status: NOERROR, id: 37923
;; flags: qr aa; QUERY: 1, ANSWER: 1, AUTHORITY: 2, ADDITIONAL: 3

;; OPT PSEUDOSECTION:
; EDNS: version: 0, flags:; udp: 4096
;; QUESTION SECTION:
;www.yahoo.co.jp.		IN	A

;; ANSWER SECTION:
www.yahoo.co.jp.	900	IN	CNAME	edge12.g.yimg.jp.

;; AUTHORITY SECTION:
g.yimg.jp.		900	IN	NS	gns02.yahoo.co.jp.
g.yimg.jp.		900	IN	NS	gns12.yahoo.co.jp.

;; ADDITIONAL SECTION:
gns02.yahoo.co.jp.	900	IN	A	118.151.254.148
gns12.yahoo.co.jp.	900	IN	A	124.83.255.100

;; Query time: 6 msec
;; SERVER: 118.151.254.149#53(118.151.254.149)
;; WHEN: Sat Feb 12 20:32:19 JST 2022
;; MSG SIZE  rcvd: 144
```

以上によりAレコードがもとまります。
@gdn02.yahoo.co.jpとしてしてもいいですし、IPがわかっているので以下の例のようにIP指定でも問題ありません。

```
$ dig @118.151.254.148 edge12.g.yimg.jp  +norecurse 

; <<>> DiG 9.10.6 <<>> @118.151.254.148 edge12.g.yimg.jp +norecurse
; (1 server found)
;; global options: +cmd
;; Got answer:
;; ->>HEADER<<- opcode: QUERY, status: NOERROR, id: 45159
;; flags: qr aa ad; QUERY: 1, ANSWER: 1, AUTHORITY: 0, ADDITIONAL: 0

;; QUESTION SECTION:
;edge12.g.yimg.jp.		IN	A

;; ANSWER SECTION:
edge12.g.yimg.jp.	60	IN	A	183.79.217.124

;; Query time: 10 msec
;; SERVER: 118.151.254.148#53(118.151.254.148)
;; WHEN: Sat Feb 12 20:35:35 JST 2022
;; MSG SIZE  rcvd: 50
```


### ~/.digrcに毎回付与するオプションを定義する
毎回オプションを付与するのが面倒という場合には~/.digrcに記述することでタイプを省略することが可能です。
```
$ cat ~/.digrc 
+noedns
+noall
+answer
$ dig yahoo.co.jp
yahoo.co.jp.		92	IN	A	183.79.250.123
yahoo.co.jp.		92	IN	A	183.79.217.124
yahoo.co.jp.		92	IN	A	183.79.250.251
yahoo.co.jp.		92	IN	A	182.22.16.251
yahoo.co.jp.		92	IN	A	182.22.25.252
yahoo.co.jp.		92	IN	A	183.79.219.252
```

# 参考資料
- https://hana-shin.hatenablog.com/entry/2021/12/22/201022
