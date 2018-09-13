# Datagram Transport Layer Securityについて

DTLSはUDP上で動作するTLSを似せたプロトコルであり、次の特徴があります。
- DTLSではUDP上で信頼性がないので鍵を共有できない可能性があるので、TLSにTCPのような信頼性を付与したプロトコルであると言えます。
- DTLSではカーネル修正する必要なく利用できるように設計されています

DTLSは次のような場面で利用されています
- WebRTC
- SIP (TCP/UDP双方で利用)
- 遅延が重要となる双方向ゲーム処理
- インターネット電話

TCPでないことによる問題点には次の２つがあります。
- TLSでは整合性チェックをシーケンス番号に依存しています。もしレコード番号Nを受け取ってなかったら、レコード番号N+1における整合性チェックは失敗します。
- TLSハンドシェイクはハンドシェイクメッセージが信頼して届けられ、これらのメッセージが失ったときにブレークします。

上記を解決する課題としてDTLSでは次のアプローチを利用しています。
- 損失を気にしないメッセージング処理
- ハンドシェイクのために信頼性の提供
  - パケットロス
  - Reordering
  - メッセージサイズ
  - リプレイ検知

TLSとDTLSとの違いについての差分が規定されています。たとえば、RFC6347ではTLS1.2とDTLS1.2との差分が規定されています。DTLSではこの差分情報がRFC(RFC4347, RFC6347)の大部分を占めています。
- RFC6347の場合Section4に記載されている
  - https://tools.ietf.org/html/rfc6347#section-4


# 詳細

### フルハンドシェイク

```
   Client                                          Server
   ------                                          ------

   ClientHello             -------->                           Flight 1

                           <-------    HelloVerifyRequest      Flight 2

   ClientHello             -------->                           Flight 3

                                              ServerHello    \
                                             Certificate*     \
                                       ServerKeyExchange*      Flight 4
                                      CertificateRequest*     /
                           <--------      ServerHelloDone    /

   Certificate*                                              \
   ClientKeyExchange                                          \
   CertificateVerify*                                          Flight 5
   [ChangeCipherSpec]                                         /
   Finished                -------->                         /

                                       [ChangeCipherSpec]    \ Flight 6
                           <--------             Finished    /

               Figure 1. Message Flights for Full Handshake
```


### セッションレジュームハンドシェイク
```
   Client                                           Server
   ------                                           ------

   ClientHello             -------->                          Flight 1

                                              ServerHello    \
                                       [ChangeCipherSpec]     Flight 2
                            <--------             Finished    /

   [ChangeCipherSpec]                                         \Flight 3
   Finished                 -------->                         /

         Figure 2. Message Flights for Session-Resuming Handshake
                           (No Cookie Exchange)
```

###  Timeout and Retransmission状態マシン

```
                      +-----------+
                      | PREPARING |
                +---> |           | <--------------------+
                |     |           |                      |
                |     +-----------+                      |
                |           |                            |
                |           | Buffer next flight         |
                |           |                            |
                |          \|/                           |
                |     +-----------+                      |
                |     |           |                      |
                |     |  SENDING  |<------------------+  |
                |     |           |                   |  | Send
                |     +-----------+                   |  | HelloRequest
        Receive |           |                         |  |
           next |           | Send flight             |  | or
         flight |  +--------+                         |  |
                |  |        | Set retransmit timer    |  | Receive
                |  |       \|/                        |  | HelloRequest
                |  |  +-----------+                   |  | Send
                |  |  |           |                   |  | ClientHello
                +--)--|  WAITING  |-------------------+  |
                |  |  |           |   Timer expires   |  |
                |  |  +-----------+                   |  |
                |  |         |                        |  |
                |  |         |                        |  |
                |  |         +------------------------+  |
                |  |                Read retransmit      |
        Receive |  |                                     |
           last |  |                                     |
         flight |  |                                     |
                |  |                                     |
               \|/\|/                                    |
                                                         |
            +-----------+                                |
            |           |                                |
            | FINISHED  | -------------------------------+
            |           |
            +-----------+
                 |  /|\
                 |   |
                 |   |
                 +---+

              Read retransmit
           Retransmit last flight

          Figure 3. DTLS Timeout and Retransmission State Machine
```


# 参考URL
- RFC4347: Datagram Transport Layer Security
  - https://tools.ietf.org/html/rfc4347
- RFC6347: Datagram Transport Layer Security Version 1.2
  - https://tools.ietf.org/html/rfc6347


# 参考リンク
- RFC 4347 (DTLS) について調べてみた
  - https://mdgw.hateblo.jp/entry/20080217/1203273902
