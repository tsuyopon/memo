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

# SeeAlso
- RFC5077: Transport Layer Security (TLS) Session Resumption without Server-Side State
  - https://www.ietf.org/rfc/rfc5077.txt
- サーバ側のSSL Session Cache状況を確認する「rfc5077」というツールが便利
  - https://github.com/vincentbernat/rfc5077

