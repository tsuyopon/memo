# 概要
TLSはハンドシェイクがとても遅いのでこれを高速化する方法が存在します。  
2回目以降のハンドシェイクで1回目のハンドシェイク時に利用したmaster_secretをキャッシュしておいてそれを利用するという方法があります。

この２回目以降のハンドシェイク手順を「セッション再開(session resumption)」と呼びます。

これには次の２つの方法が存在します。
- (1) SessionIDを使う方法(古典的手法)
- (2) TLS Session Ticket拡張(RFC5077)を使う手法
  - https://tools.ietf.org/html/rfc5077


# (1) SessionIDを使う方法

1回目と2回目のハンドシェイク手順をそれぞれ見てみることにしましょう。
*については送信されない場合があるという意味になります。

参考資料
- http://qiita.com/n-i-e/items/bb0e582011a5b1f9c28d

### 1回目のフルハンドシェイク
ハンドシェイクは次の流れとなります。
```
                   ← HelloRequest*
       ClientHello → 
                   ← ServerHello
                   ← ServerCertificate
                   ← ServerKeyExchange*
                   ← CertificateRequest*
                   ← ServerHelloDone
ClientCertificate* → 
 ClientKeyExchange → 
CertificateVerify* → 
  ChangeCipherSpec → 
          Finished → 
                   ← ChangeCipherSpec 
                   ← Finished
  Application Data ⇔ Application Data
```

この時のServerHello.SessionIDがこのセッションのSessionIDとなります。
クライアントとサーバの双方でこのSessionIDとmaster_secretその他各種セッションパラメータをセットでセッションキャッシュ領域に保存します。

### 2回目のハンドシェイク(セッション再開を利用する場合)

ClientHelloとServerHelloの送受信まで進んだ段階で、ClientHello.SessionIDとServerHello.SessionIDを照合します。  
一致していたらセッション再開となります。

ハンドシェイクは次の流れとなります。

```
                   ← HelloRequest*
       ClientHello → 
                   ← ServerHello
                   ← ChangeCipherSpec 
                   ← Finished
  ChangeCipherSpec → 
          Finished → 
  Application Data ⇔ Application Data
```

# (2) TLS Session Ticket拡張(RFC5077)を使う手法

### 1回目のフルハンドシェイク
```
                   ← HelloRequest*
       ClientHello →                     # empty "session ticket" extension
                   ← ServerHello         # empty "session ticket" extension
                   ← ServerCertificate
                   ← ServerKeyExchange*
                   ← CertificateRequest*
                   ← ServerHelloDone
ClientCertificate* → 
 ClientKeyExchange → 
CertificateVerify* → 
  ChangeCipherSpec → 
          Finished → 
                   ← NewSessionTicket    # New!
                   ← ChangeCipherSpec 
                   ← Finished
  Application Data ⇔ Application Data
```

ClientHelloとServerHelloには「Session Ticket拡張」が付与されます。ただし、初期状態では何も情報がないので空となります。  
なお、Server Helloのパラメータは常に空となるようです。

新しくNewSessionTicketという項目が上記シーケンスで登場します。  
これがSessionTicket拡張を使う場合に限って登場するメッセージで、これがSessionIDの代替となります。
SessionIDとSessionTicketの違いについては後述します。

### 2回目のハンドシェイク(セッション再開を利用する場合)

```
                   ← HelloRequest*
       ClientHello →                     # "session ticket" extension
                   ← ServerHello         # empty "session ticket" extension
                   ← NewSessionTicket*
                   ← ChangeCipherSpec 
                   ← Finished
  ChangeCipherSpec → 
          Finished → 
  Application Data ⇔ Application Data
```
1回目のハンドシェイクのNewSessionTicketで送付されてきたNewSessionTicket.SessionTicketを今度はClientHelloに載せてクライアントからサーバへと送出されます。  
サーバ側ではこれを解読して有効な内容と認められれば、それを使って「セッション再開」手順によるハンドシェイクを行います。


# FAQ

### SessionIDとSessionTicketは何が違うのか?
それぞれ長さと発行タイミングが異なります。

- 長さ
  - SessionID: 0〜32Byte
  - SessionTicket: 最大64KByte
- 発行タイミング
  - SessionID: ServerHelloの段階で発行
  - SessionTicket: 鍵交換終了後に発行

SessionTicketはこの長さを利用することによって、サーバ側でセッションパラメータそのものを暗号化してSessionTicketに詰め込んで発行したりします。これによって、サーバ側ではセッションキャッシュ領域を保つ必要がなくなりますので、解読して利用すれば良いだけになります。
RFC5077のタイトルも「Transport Layer Security (TLS) Session Resumption without Server-Side State」なのでサーバが状態保持しなくても良いと明記されていることがわかります。

### 有効時間はどれくらいなのか?
SessionIDの場合だとクライアント・サーバ双方で状態を保持する必要があります。

Apacheだと次のような設定が可能です。
```
SSLSessionCache shm:/usr/local/apache/logs/ssl_gcache_data(512000)
SSLSessionCacheTimeout 300
```

### SessionID方式の他にTLS Session Ticket拡張方式が出来た理由は何か?
サーバが複数台でロードバランスしている場合、1つのクライアントに対して1回目のコネクションと2回目のコネクションを別のサーバで受け取るとセッション再開ではなく、フルハンドシェイクになるので効率が落ちる問題があります。

次のような方法でSessionIDをキャッシュする方法が一般的でしたが、
- スティッキーセッション機能を使う
- サーバ間でmemcached等を駆使してセッションキャッシュを共有する

SessionTicketに対応したことによって、対応方法が増えてきています。

以下の例ではLB単位でSessionIDを共有させたが、DNSで返却されるLBのIPアドレスが異なるとセッションIDの効果が薄れますといった話。問題点は理解しておいたほうがよい。
- https://techblog.yahoo.co.jp/infrastructure/ssl-session-resumption_2/

### TLS Session Ticket拡張のクライアント制限
TLS Session Ticket拡張は新しい方式なので、自分が調べた感じだと次の制限があるようです。
- iOSが非対応
- サーバに秘密鍵を持たせる必要があり、同じ鍵を使い続けるのはセキュアではないためこの鍵は定期的にローテートしなければならない。
といった制限があるようです。

# 参考資料
- TLSセッション再開 (session resumption) のしくみ  <= おすすめ
  - http://qiita.com/n-i-e/items/bb0e582011a5b1f9c28d
