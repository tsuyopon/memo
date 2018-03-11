# 概要
TLSのハンドシェイクに関しては、RFC5246で述べられている
- https://tools.ietf.org/html/rfc5246#section-7.3

# 詳細
図についてはハンドシェイク部分についてはRFC5246からの抜粋です。

### フルハンドシェイクの場合
```
Client                                               Server
------------------------------------------------------------------

ClientHello                  -------->
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

「*」は省略される可能性がある接続に対して記載されている。以下に省略される場合について記載しておきます。
- Server側のCertificate
  - anonymousやPSK、kerberos等だとCertificateを送付しませんので省略されることがあるようです。
- Server側のServerKeyExchange
  - RSAやDHだとCertificateに含まれているので省略されます。
  - RSA証明書やDHで使われるECC(楕円曲線暗号)証明書については、ClientHelloに応じてServer側のCertificateで出し分けできるのでこの項目は不要となる
- Server側のCertificateRequest
  - クライアント側の証明書の提示を要求する時に送信されるメッセージです。TLSクライアント認証で用いられます。
- Client側のCertificate
  - クライアントはServer側のCertificateRequestの要求を受け、自身が持つ証明書をサーバに送信します。TLSクライアント認証で用いられます。
- Client側のCertificateVerify
  - Client側のCertificateで送信した証明書が自身が保持する正当なものであることをサーバに示すため、それまでのハンドシェイクデータを秘密鍵で署名し、CertificateVerifyでサーバに送信します。TLSクライアント認証で用いられます。
  - サーバ側はCertificateで送付されてきた証明書とCertificateVerifyの値を検証し、クライアントが正当な鍵ペアを持つ通信相手であることを検証します。

なお、ChangeCipherSpecはブラケット([])で囲まれていますが、これはこのパケットのcontent typeがhandshake messageではなく独立した値を持っているためと思われます。

### 省略されたハンドシェイクの場合
```
Client                                                Server
------------------------------------------------------------------

ClientHello                   -------->
                                                 ServerHello
                                          [ChangeCipherSpec]
                              <--------             Finished
[ChangeCipherSpec]
Finished                      -------->
Application Data              <------->     Application Data
```

上記のハンドシェイクを見るとわかりますが、Session Resumptionと判断できるのはServer Helloの直後にChange Cipher Specがあればそのように判断することができます。
