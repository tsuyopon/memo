# 概要
TimeStampオプションは次の２つのメカニズムで利用されています
- (1). Protection Against Wrapped Sequences (PAWS)
  - 最短で数十秒でseq番号が一巡する問題への対応としてこのタイムスタンプの値が利用されています。
- (2). Round-Trip Time Measurement (RTTM)
  - RTTを測定することができます。


# 背景
(2)については1Gbpsの速度においては、シーケンス番号が最短で30秒程度で一巡してしまいます。
この問題への対応としてPAWS (Protection Against Wrapped Sequence) という解決策が出てきました。これは、シーケンス番号をTime Stampオプションとセットにすることで、重複を避ける、というものです。 これにより、シーケンス番号が重複しても古いパケットと新しいパケットを識別することができます。
このような背景によりTimeStampオプションが登場しました。

ただし、このPAWSはDoS攻撃を受ける脆弱性があることがわかっていて、有効化する場合にはパケットが推測されない・FWを経由している等の環境にしていることが重要です。


# 詳細


### データ構造
```
   Length: 10 bytes

          +-------+-------+---------------------+---------------------+
          |Kind=8 |  10   |   TS Value (TSval)  |TS Echo Reply (TSecr)|
          +-------+-------+---------------------+---------------------+
              1       1              4                     4
```

- TSValには、タイムスタンプの現在の値が含まれる
- TSecrはACKフィールドが有効の場合だけ妥当と判断されます。送信元はTSecrに最近受け取ったTSValの値をechoしなければならない(MUST)

対応する送信側はTCPパケットには常に現在進行中のタイムスタンプを含んで送信するため、対応する受信側は、これを見て古いタイムスタンプを持つ古いパケットを破棄することができる。

### サンプルデータ
以下は対となる送信側と応答側のTimeStampのサンプルです。3way handshakeの最初のパケット中のTSecrは0となります。

- 送信側
```
        TCP Option - Timestamps: TSval 1773879829, TSecr 1046311534
            Kind: Time Stamp Option (8)
            Length: 10
            Timestamp value: 1773879829
            Timestamp echo reply: 1046311534
```
- 応答側
  - Timestamp echo replyには先ほどのTimestamp valueの値が含まれていることがわかる。
```
        TCP Option - Timestamps: TSval 1046311547, TSecr 1773879829
            Kind: Time Stamp Option (8)
            Length: 10
            Timestamp value: 1046311547
            Timestamp echo reply: 1773879829
```

# SeeAlso
- RFC7323: TCP Extensions for High Performance
  - Section3. TCP Timestamps Option
    - https://tools.ietf.org/html/rfc7323#section-3
  - Section4. The RTTM Mechanism
    - https://tools.ietf.org/html/rfc7323#section-4
  - Section5.  PAWS - Protection Against Wrapped Sequences
    - https://tools.ietf.org/html/rfc7323#section-5


# TODO
- RFC7323の概要が記載されているだけなので深読みしたい
