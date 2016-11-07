
# 概要
ncコマンドについて

# 詳細

### HTTPリクエストを出す

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

### メールを送る
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

### ポートスキャンニングを行う
セキュリティチェックなどのためにローカルホストで実施すること。
```
$ nc -zv localhost 1-65535
```

### Redisへアクセス
```
$ (echo 'set KEY1 hoge'; sleep 1s; echo 'key *') | nc localhost 6379
```

### .ssh/configにProxyCommandを記述する
passproxy.comにログインせずに一気にremoteserver.comにsshログインやscpするための設定
```
Host remoteserver.com
  ProxyCommand ssh passproxy.com nc %h %p
```

# 参考URL
- nc コマンド 使い方メモ: Qiita
 - http://qiita.com/yasuhiroki/items/d470829ab2e30ee6203f
- ncのManpage
 - http://www.computerhope.com/unix/nc.htm
