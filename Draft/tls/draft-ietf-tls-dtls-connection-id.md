# The Datagram Transport Layer Security (DTLS) Connection Identifier

# 解決したい課題
現行のDTLSバージョンでは、IPアドレスとポート番号はDTLSへの関連を識別するために使われています。 不幸にもNAT再バインディングのような場合、これらの値だけでは不十分です。
上記のパラメータが変化すると鍵交換を含むハンドシェイクをはじめからやり直す必要があり、移動する端末や通信速度が低い端末などでは頻繁にこの問題が発生する可能性があります
これは特にIoT特有の問題であり、デバイスは待ち時間を発生しこの際にバッテリー消費を増加します。
NAT再バインディングはコネクション失敗をもたらし、新規ハンドシェイク接続のコストをもたらします。

# 解決方法
DTLSレコードレイヤーへConnection IDを追加するためのDTLS拡張を追加する。
また、TLSレコードレイヤにcidフィールドの追加、MAC値の計算方法の変更を行います。
このドラフトではTLS1.2及びTLS1.3共に対応します。

# 仕様詳細(TLS1.2)

### connection_id拡張の追加
TLS拡張としてconnection_idを定義します。この拡張はCientHello, ServerHelloに含まれます。
```
     struct {
         opaque cid<0..2^8-1>;
     } ConnectionId;
```

extension_dataの中にはCIDを含みます。 0byteの場合にはクライアントはConnectionIDを送付する準備ができたが、サーバ側にCIDを使ってほしくないような場合に指定します。
CIDを使おうとしているサーバはconnection_idで応答します。0byteの場合にはサーバはクライアントにCIDを使ってほしくない場合に指定します。
セッションがリジュームされた際に、connection_idが再びネゴシエートされたら、


### TLSレイヤーレコードの拡張

DTLS1.2以前では次のようにcidフィールドが新しく追加される。
```
      struct {
           ContentType type;
           ProtocolVersion version;
           uint16 epoch;
           uint48 sequence_number;
           opaque cid[cid_length];               // New field
           uint16 length;
           select (CipherSpec.cipher_type) {
               case block:  GenericBlockCipher;
               case aead:   GenericAEADCipher;
           } fragment;
      } DTLSCiphertext;
```

### レコードペイロードのプロテクション
cid_lengthとcidをMAC計算の際に指定する。
```
         MAC(MAC_write_key, DTLSCompressed.epoch +
                               DTLSCompressed.sequence_number +
                               DTLSCompressed.type +
                               DTLSCompressed.version +
                               connection_id + // New field
                               cid_length +        // New input
                               cid +               // New input
                               DTLSCompressed.length +
                               DTLSCompressed.fragment);
```

### サンプルフロー
```
   Client                                             Server
   ------                                             ------

   ClientHello
   (connection_id=empty)
                               -------->


                               <--------      HelloVerifyRequest
                                                        (cookie)

   ClientHello                 -------->
   (connection_id=empty)
     +cookie

                               <--------             ServerHello
                                             (connection_id=100)
                                                     Certificate
                                               ServerKeyExchange
                                              CertificateRequest
                                                 ServerHelloDone

   Certificate                 -------->
   ClientKeyExchange
   CertificateVerify
   [ChangeCipherSpec]
   Finished
   (cid=100)
                               <--------      [ChangeCipherSpec]
                                                        Finished

   Application Data           ========>
   (cid=100)
                              <========         Application Data

          Figure 2: Example DTLS 1.2 Exchange with Connection IDs
```

# 仕様詳細(TLS1.3)
- connection_id拡張
- RequestConnectionId：DTLS1.3で相手にコネクションIDを要求するメッセージ
- NewConnectionId：DTLS1.3で相手にコネクションIDを通知するメッセージ 

# 参考URL
- https://tools.ietf.org/html/draft-ietf-tls-dtls-connection-id-01
- ASnoKaze blog: DTLSにコネクションIDを導入する提案仕様
  - https://asnokaze.hatenablog.com/entry/2017/12/30/233032
