# 概要
Slow HTTP Dosとは、各セッションの接続時間を可能な限り引き延ばすことによってWebサーバのTCPセッションを占有します。
これはUDP FloodingやSYN Flooding等の攻撃とは異なり少量のパケットで攻撃が成立します。

Slow HTTP Dosといっても継続時間の引き伸ばしを試みる通信対象によって次の３つが存在します。
- (1) Slow HTTP Headers Attack
- (2) Slow HTTP POST Attack
- (3) Slow Read DoS Attack

これらについて説明します

# (1) Slow HTTP Headers Attack
### 攻撃方法

この脆弱性はApache1.x, Apache2.x, dhttpd, squidなどで確認されています。

slowlorisと呼ばれるツールを用いることにより簡単に再現することができる。
- https://github.com/llaera/slowloris.pl

上記のツールを確認するとわかるように
- https://github.com/llaera/slowloris.pl/blob/master/slowloris.pl#L295
```
HTTP/1.1\r\n
Host: $sendhost\r\n
User-Agent: Mozilla/4.0 (compatible; MSIE 7.0; Windows NT 5.1; Trident/4.0; .NET CLR 1.1.4322; .NET CLR 2.0.503l3; .NET CLR 3.0.4506.2152; .NET CLR 3.5.30729; MSOffice 12)\r\n
Content-Length: 42\r\n
X-a: b\r\n
X-a: b\r\n
X-a: b\r\n
```

次のヘッダを何度も送っていることがわかる。
```
X-a: b\r\n
```

その後、sleepして再度接続を張っていることが確認できる。  
これによってApacheが最大接続数に達することによって新規接続を受け付けなくするといった攻撃手法です。

### 対策方法
いくつか対策方法などが存在するので紹介しておく
- Apacheを利用している場合には、mod_reqtimeout(httpd-2.1.15以降)というモジュールを利用することによってHTTPヘッダとボディの受信にかかる時間(秒)を設定することができる。
```
設定例) RequestReadTimeout header=10 body=30
```
- nginxやpoundなどにslowlorisの影響を受けないリバースプロキシ・ロードバランサを前段に配置することによって防ぐことができる。
- iptablesなどを使って同一IPアドレスからの同時接続数を制限する
```
設定例) iptables -A INPUT -p tcp -m state --syn --state NEW --dport 80 -m connlimit --connlimit-above 100 -j DROP
```
- FreeBSDを利用しているのであればApacheのso_accept_filterを有効にすることにより、カーネルレベルでaccf_http(9)がHTTPリクエストをバッファリングしてリクエスト全体を受信完了するまでApacheにリクエスト渡さないようにすることができるのでDoSが成立しない(ただし、GETとHEADのみしか対応していない)
  - http://httpd.apache.org/docs/2.2/mod/core.html#acceptfilter

# (2) Slow HTTP POST Attack
TBD

HTTPのPOSTメソッドを悪用して、待機時間を挟みながら長いHTTPリクエストボディ(POSTペイロード)を送信することによってTCPセッションを占有する攻撃手法

# (3) Slow Read DoS Attack
TBD

WebサーバからのHTTPレスポンスを少しずつ受信することによって、セッション継続時間を引き延ばす攻撃方法

# 参考URL
- slowloris.pl
  - https://github.com/llaera/slowloris.pl
- slowlorisと類似のツールでPOSTリクエストでHTTPボディの送信をゆっくり行う攻撃が可能なツールがある
  - https://github.com/shekyan/slowhttptest 
  - https://github.com/shekyan/slowhttptest
