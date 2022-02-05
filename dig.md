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

### 特定のセクションだけ取得する
幾つか例を示す

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

- 最後の行
```
$ dig +noall +cmd www.yahoo.co.jp

; <<>> DiG 9.8.3-P1 <<>> +noall +cmd www.yahoo.co.jp
;; global options: +cmd
```

### 回答結果を短く得る
```
$ dig www.yahoo.co.jp +short
edge.g.yimg.jp.
183.79.249.124
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
通常はdigはUDPで問い合わせを行っているのだが、応答サイズが512を超える場合にはTCPでの問い合わせに変更するようになっている
```
$ dig www.yahoo.co.jp +vc
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

