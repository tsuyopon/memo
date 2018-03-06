# 概要
SessionIDでは32byteしか許容せず、そのバイト数からはサーバ側にも状態を保持するための識別子にすぎません。
しかし、セッションチケット拡張を利用することによってサーバ側に状態を保持しなくてもチケットの中にセッション状態を保持することでサーバ側に保持する必要がなくなります。 
この仕組みを利用することで複数台のロードバランサ配下にあるサーバで接続先が異なった場合でも毎回ハンドシェイクを行うことを防ぐ効果があります。

# 詳細

## 古典的なSessionIDとセッションチケット拡張の違い
- Session IDの0～32バイトに対し、Session Ticketは最大64キロバイトまでいけます。この長さの違いがサーバ側で情報を保持するかどうかの違いに繋がります。
- セッションを発行するタイミングが古典的なSessionIDだとServerHello段階で発行しますが、Session TicketはChange Cipher Specの直前となります。これはセッションパラメータすべてをこの段階で詰め込むために発行タイミングが異なることになります。

## ハンドシェイクパターン
RFC5077の3.1 Overviewに記載されている４つのハンドシェイクパターンを押さえておく必要があります。
- (1). New Session Ticketを発行するフルハンドシェイク
- (2). 指定されたNew Session Ticketによる省略ハンドシェイク
- (3). クライアントからSessionTicketの値が指定されたが、New Session Ticketとしてサーバ側が処理したくない場合のハンドシェイク
- (4). クライアントからSessionTicketの値が指定されたが、New Session Ticketを新規発行したい場合のハンドシェイク

### (1). New Session Ticketを発行するフルハンドシェイク
- クライアントからClientHello中に空のSessionTicket拡張を含めて送付する。
- サーバ側はSessionTicket拡張に対応していることを示すためにServerHello中に空のSessionTicket拡張を含めて応答する。
- サーバ側はChangeCipherSpecを送付する直前にNewSessionTicketハンドシェイクを送付する
```
         Client                                               Server

         ClientHello
        (empty SessionTicket extension)-------->
                                                         ServerHello
                                     (empty SessionTicket extension)
                                                        Certificate*
                                                  ServerKeyExchange*
                                                 CertificateRequest*
                                      <--------      ServerHelloDone
         Certificate*
         ClientKeyExchange
         CertificateVerify*
         [ChangeCipherSpec]
         Finished                     -------->
                                                    NewSessionTicket
                                                  [ChangeCipherSpec]
                                      <--------             Finished
         Application Data             <------->     Application Data
```

### (2). 指定されたNew Session Ticketによる省略ハンドシェイク
- クライアントからClientHello中に以前指定された値をSessionTicket拡張を含めて送付する。
- サーバ側はSessionTicket拡張に対応していることを示すためにServerHello中に空のSessionTicket拡張を含めて応答する。
- ServerHelloの直後にNewSessionTicketを含めて発行する(TODO: この場合どのような値が入る?)
```
        Client                                                Server
         ClientHello
         (SessionTicket extension)      -------->
                                                          ServerHello
                                      (empty SessionTicket extension)
                                                     NewSessionTicket
                                                   [ChangeCipherSpec]
                                       <--------             Finished
         [ChangeCipherSpec]
         Finished                      -------->
         Application Data              <------->     Application Data
```

### (3). クライアントからSessionTicketの値が指定されたが、New Session Ticketとしてサーバ側が処理したくない場合のハンドシェイク
- クライアントからClientHello中に以前指定された値をSessionTicket拡張を含めて送付する。
- サーバ側はSessionTicket拡張に応答しないために、ServerHelloにはSessionTicket拡張を含めない。また、New Session Ticketパケットも送付しない。
  - 「指定されたセッションチケットがサーバ側でパースできない場合」、「セッションチケットの有効期限切れ」などの場合にも上記のような挙動となるようです。
- SessionTicket拡張は利用されることなくハンドシェイクが行われる。
```
         Client                                               Server

         ClientHello
         (SessionTicket extension)    -------->
                                                         ServerHello
                                                        Certificate*
                                                  ServerKeyExchange*
                                                 CertificateRequest*
                                      <--------      ServerHelloDone
         Certificate*
         ClientKeyExchange
         CertificateVerify*
         [ChangeCipherSpec]
         Finished                     -------->
                                                  [ChangeCipherSpec]
                                      <--------             Finished
         Application Data             <------->     Application Data
```

### (4). クライアントからSessionTicketの値が指定されたが、New Session Ticketを新規発行したい場合のハンドシェイク
- クライアントからClientHello中に以前指定された値をSessionTicket拡張を含めて送付する。
- サーバ側はSessionTicket拡張に対応していることを示すためにServerHello中に空のSessionTicket拡張を含めて応答する。
- 省略されたハンドシェイク(2)であればServerHelloの直後にNewSessionTicketが送付されるが、この場合だと新規発行したいので(1)ど同様にしてServer側がChangeCipherSpecを発行する直前にNewSessionTicketを発行する。
```
         Client                                               Server

         ClientHello
         (SessionTicket extension) -------->
                                                         ServerHello
                                     (empty SessionTicket extension)
                                                        Certificate*
                                                  ServerKeyExchange*
                                                 CertificateRequest*
                                  <--------          ServerHelloDone
         Certificate*
         ClientKeyExchange
         CertificateVerify*
         [ChangeCipherSpec]
         Finished                 -------->
                                                    NewSessionTicket
                                                  [ChangeCipherSpec]
                                  <--------                 Finished
         Application Data         <------->         Application Data
```

## サンプルデータ構造
以下の例では(1)のセッションチケットが新規発行される場合の例です。

- ClientHello
  - クライアントはSessionTicket TLS拡張に対応していることを伝えます
```
Extension: SessionTicket TLS
    Type: SessionTicket TLS (0x0023)
    Length: 0
    Data (0 bytes)
```
- ServerHello
  - サーバ側から空を返すことで後でNew Session Ticketハンドシェイクメッセージを送付することをクライアントに伝えています。
```
Extension: SessionTicket TLS
    Type: SessionTicket TLS (0x0023)
    Length: 0
    Data (0 bytes)
```
- New Session Ticket(Change Cipher Specの直前)
```
TLSv1.2 Record Layer: Handshake Protocol: New Session Ticket
    Content Type: Handshake (22)
    Version: TLS 1.2 (0x0303)
    Length: 218
    Handshake Protocol: New Session Ticket
        Handshake Type: New Session Ticket (4)
        Length: 214
        TLS Session Ticket
            Session Ticket Lifetime Hint: 7200
            Session Ticket Length: 208
            Session Ticket: 656467652e656467652e6174735f73734f397a7d1a6f66a7...
```

## セッションチケット拡張の確認方法

### セッションチケットを発行しているかどうかの確認を行う
次のようにアクセスして「TLS Session ticket」という項目が存在するかどうかを確認します。あればセッションチケット拡張に対応しています
```
$ echo Q | openssl s_client -connect www.yahoo.co.jp:443 -tls1 -debug -msg

(snip)

---
New, TLSv1/SSLv3, Cipher is AES128-SHA
Server public key is 2048 bit
Secure Renegotiation IS supported
Compression: NONE
Expansion: NONE
SSL-Session:
    Protocol  : TLSv1
    Cipher    : AES128-SHA
    Session-ID: 0FA970B68760F080A2CD369F1CA78BD3FDCF759E6DC7A1F0E9E6792667DF67DE
    Session-ID-ctx: 
    Master-Key: 1F60378AA1EEB3F301EE51F50DFD5571517EA8E563FD14909507370C46EF881C5588F86BB6FB264E854C52E3776FCC99
    Key-Arg   : None
    TLS session ticket lifetime hint: 7200 (seconds)
    TLS session ticket:
    0000 - 65 64 67 65 2e 65 64 67-65 2e 61 74 73 5f 73 73   edge.edge.ats_ss
    0010 - 8c a8 5c 7d ef c5 0b e6-5d ac 85 55 79 e3 14 7b   ..\}....]..Uy..{
    0020 - 83 bb c3 73 82 86 21 53-27 19 94 81 42 29 a1 e1   ...s..!S'...B)..
    0030 - b4 dc 5c ee 0e 7c d7 30-22 88 74 d4 8e 55 25 56   ..\..|.0".t..U%V
    0040 - 55 74 41 f5 a5 4c 53 48-fc e8 0e 56 f8 a1 76 ce   UtA..LSH...V..v.
    0050 - 07 1f 61 ef 0a f6 fb a1-09 39 dd 6f 07 99 94 40   ..a......9.o....
    0060 - 34 d2 be f5 73 b7 e4 53-a9 1f 95 e1 e3 88 12 c5   t...s..S........
    0070 - fd 05 33 74 1a 71 55 b2-10 f7 f5 1d 21 90 0d 34   ..3t.qU.....!..4
    0080 - b6 91 c7 58 cc 28 34 4d-58 8f 2e f4 29 01 4c df   ...X.(4MX...).L.
    0090 - 5a 45 3f 99 68 3a d4 24-1b d7 36 f0 bf 75 0e bc   ZE?.h:.$..6..u..
    00a0 - 92 17 79 74 66 7b ba db-1e 42 7a 42 88 b7 9d 2b   ..ytf{...BzB....
    00b0 - cf b9 cd f6 05 e0 e7 6a-b9 53 ze ae b5 87 91 41   .......j.S.....A

    Start Time: 1520376475
    Timeout   : 7200 (sec)
    Verify return code: 0 (ok)
---
```

対応していないような場合に次のように「TLS Session ticket」の項目が表示されません。
```
---
New, TLSv1/SSLv3, Cipher is DHE-RSA-AES128-SHA
Server public key is 2048 bit
Secure Renegotiation IS supported
Compression: NONE
Expansion: NONE
SSL-Session:
    Protocol  : TLSv1
    Cipher    : DHE-RSA-AES128-SHA
    Session-ID: 04D17FA33850584DE617AC11763211EA4EDF85F303BBBF527C8BEABE856BBA1A
    Session-ID-ctx: 
    Master-Key: B1BB85AC8B91A9BEC9567D36A6003F854BC9489D69BCCD32604F3D19922D698317A323853F98FC786D6D63551D5696D2
    Key-Arg   : None
    Start Time: 1520376709
    Timeout   : 7200 (sec)
    Verify return code: 0 (ok)
---
```

### セッションチケットを利用してハンドシェイクが省略されているかどうかを確認する
sess_outでセッションチケットを保存して、sess_inでセッションチケットを使ってハンドシェイクを行う
```
// 1回目
$ openssl s_client -connect example.com:443 -sess_out /tmp/ssl_s

// 2回目
$ openssl s_client -connect example.com:443 -sess_in /tmp/ssl_s
```

1回目の出力が次のようにNewで始まるとチケットが発行されている
```
New, TLSv1/SSLv3, Cipher is ECDHE-RSA-AES128-GCM-SHA256
```

2回目の出力が次のようにReusedで始まると省略ハンドシェイクとなる。２回目もNewだとセッションチケットの利用に失敗していることになります。
また、２回目の接続で証明書などで表示される大量の出力がなければ省略ハンドシェイクとなっていることを確認することができます。
```
Reused, TLSv1/SSLv3, Cipher is ECDHE-RSA-AES128-GCM-SHA256
```

- 参考
  - https://serverfault.com/questions/345891/how-should-i-check-if-ssl-session-resumption-is-working-or-not
 

# SeeAlso
- RFC5077: Transport Layer Security (TLS) Session Resumption without Server-Side State
  - https://www.ietf.org/rfc/rfc5077.txt
- サーバ側のSSL Session Cache状況を確認する「rfc5077」というツールが便利
  - https://github.com/vincentbernat/rfc5077

