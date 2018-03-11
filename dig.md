# $B35MW(B
dig(Domain Information Grouper)$B$K$D$$$F$^$H$a$k(B
dig$B%3%^%s%I$O(Bdig$B%Q%C%1!<%8!"(Bbind-utils(centos)$B!"(Bdnsutils(ubuntu)$B$J$I$GDs6!$5$l$F$$$k$h$&$G$9!#(B

$B%3%^%s%I$N;H$$J}$OC1=c$G0J2<$NDL$j$G$9(B
```
$ dig @server domain query-type
```

# $B>\:Y(B
### dig$B$H(Bnslookup$B$N0c$$(B
dig$B$O(BDNS$B$NLd$$9g$o$;$K6a$$7A<0$G=PNO$7!"(Bnslookup$B$OLd$$9g$o$;7k2L$r=PNO$9$k!#(B
$B%M%C%H%o!<%/%H%i%V%k%7%e!<%F%#%s%0$G$O!"(Bdig$B$r;H$C$?$[$&$,NI$$$H$N$3$H(B

nslookup$B$N;~$O<!$N$h$&$J=PNO$H$J$k(B
```
$ nslookup www.yahoo.co.jp
Server:		192.168.3.1
Address:	192.168.3.1#53

Non-authoritative answer:
www.yahoo.co.jp	canonical name = edge.g.yimg.jp.
Name:	edge.g.yimg.jp
Address: 182.22.31.252
```

dig$B$N>l9g$K$O<!$N$h$&$J=PNO$H$J$j!"<B:]$N(BDNS$B%5!<%P$N=PNO7k2L$H;w$?$h$&$J7A$K$J$k!#(B
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

- QUERY SECTION: $BLd$$9g$o$;$7$?FbMF$rI=<($9$k(B
- ANSWER SECTION: $BLd$$9g$o$;$KBP$9$k7k2L$rI=<($9$k(B
- AUTHORITY SECTION: $B1~Ez$7$?8"0R%5!<%P$r4^$`8"0R%5!<%P72(B($B8"0R%5!<%P$N(BNS$B%l%3!<%I(B)
- ADDITIONAL SECTION: $B8"0R%5!<%P$N(BA$B%l%3!<%I(B($B8"0R%5!<%P$N(BSOA$B%l%3!<%I$KEPO?$5$l$k%0%k!<%l%3!<%I(B)

### $BFCDj$N%;%/%7%g%s$@$1<hF@$9$k(B
$B4v$D$+Nc$r<($9(B

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

- $B:G8e$N9T(B
```
$ dig +noall +cmd www.yahoo.co.jp

; <<>> DiG 9.8.3-P1 <<>> +noall +cmd www.yahoo.co.jp
;; global options: +cmd
```

### $B2sEz7k2L$rC;$/F@$k(B
```
$ dig www.yahoo.co.jp +short
edge.g.yimg.jp.
183.79.249.124
```

### IP$B%"%I%l%9$N5U0z$-$r9T$&(B
x$B%*%W%7%g%s$r;XDj$7$?8e$K(BIP$B%"%I%l%9$r;XDj$9$l$P$h$$!#(B
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

### DNS$B%5!<%P$r;XDj$9$k(B
8.8.8.8$B$d(B4.4.4.4$B$J$I$O(BGoogle Public DNS$B$H$7$FDs6!$5$l$F$$$k$N$G$3$l$r;H$C$FLd$$9g$o$;$F8+$^$9!#(B
- https://developers.google.com/speed/public-dns/

$B$G$O(BDNS$B%5!<%P$r;XDj$7$F%"%/%;%9$7$^$9!#(B
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

### $B%l%3!<%I$r;XDj$7$F<hF@$9$k(B
$B0J2<$O(BNS$B$r;XDj$7$?Nc$G$9(B
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

$B0J2<$O(BSOA$B$r;XDj$7$?Nc$G$9!#(B
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

### $B8+$d$9$$7A<0$K$9$k(B
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

### $B%k!<%H(BDNS$B$+$iLd$$9g$o$;$r9T$$!"7k2L$r=gHV$K=PNO$9$k(B
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

### TCP$B$GLd$$9g$o$;$r9T$&(B
$BDL>o$O(Bdig$B$O(BUDP$B$GLd$$9g$o$;$r9T$C$F$$$k$N$@$,!"1~Ez%5%$%:$,(B512$B$rD6$($k>l9g$K$O(BTCP$B$G$NLd$$9g$o$;$KJQ99$9$k$h$&$K$J$C$F$$$k(B
```
$ dig www.yahoo.co.jp +vc
```

### DNSSEC$B$GLd$$9g$o$;$r9T$&(B
```
$ dig www.yahoo.co.jp +dnssec
```

### $B:F5/Ld$$9g$o$;$r9T$o$J$$(B
$BBP>]$H$J$k(BDNS$B%5!<%P$GJ];}$7$F$$$k%-%c%C%7%e$G$N$_Ld$$9g$o$;$r9T$&(B
```
$ dig www.yahoo.co.jp +norecurse
```

