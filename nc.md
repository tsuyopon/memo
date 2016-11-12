
# $B35MW(B
nc$B%3%^%s%I$K$D$$$F(B

# $B>\:Y(B

### HTTP$B%j%/%(%9%H$r=P$9(B

```
$ echo -en "GET / HTTP/1.1\n\n" | nc www.google.com 80
HTTP/1.1 302 Found
Cache-Control: private
Content-Type: text/html; charset=UTF-8
Location: http://www.google.co.jp/?gfe_rd=cr&ei=wsUgWOS0JaTK8gfCyZzgDA
Content-Length: 261
Date: Mon, 07 Nov 2016 18:19:46 GMT

<HTML><HEAD><meta http-equiv="content-type" content="text/html;charset=utf-8">
<TITLE>302 Moved</TITLE></HEAD><BODY>
<H1>302 Moved</H1>
The document has moved
<A HREF="http://www.google.co.jp/?gfe_rd=cr&amp;ei=wsUgWOS0JaTK8gfCyZzgDA">here</A>.
</BODY></HTML>
```

### $B%a!<%k$rAw$k(B
```
nc [-C] localhost 25 << EOF
HELO host.example.com
MAIL FROM:<user@host.example.com>
RCPT TO:<user2@host.example.com>
DATA
Body of email.
.
QUIT
EOF
```

### $B%]!<%H%9%-%c%s%K%s%0$r9T$&(B
$B%;%-%e%j%F%#%A%'%C%/$J$I$N$?$a$K%m!<%+%k%[%9%H$G<B;\$9$k$3$H!#(B
```
$ nc -zv localhost 1-65535
```

### Redis$B$X%"%/%;%9(B
```
$ (echo 'set KEY1 hoge'; sleep 1s; echo 'key *') | nc localhost 6379
```

### .ssh/config$B$K(BProxyCommand$B$r5-=R$9$k(B
passproxy.com$B$K%m%0%$%s$;$:$K0l5$$K(Bremoteserver.com$B$K(Bssh$B%m%0%$%s$d(Bscp$B$9$k$?$a$N@_Dj(B
```
Host remoteserver.com
  ProxyCommand ssh passproxy.com nc %h %p
```

# $B;29M(BURL
- nc $B%3%^%s%I(B $B;H$$J}%a%b(B: Qiita
 - http://qiita.com/yasuhiroki/items/d470829ab2e30ee6203f
- nc$B$N(BManpage
 - http://www.computerhope.com/unix/nc.htm
