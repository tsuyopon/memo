# 概要
下記資料の内容を元に作成しています。
- https://datatracker.ietf.org/doc/html/draft-rescorla-tls-ctls-04


# 課題

### 解決したい課題
(RFCドキュメントに記載されていないので、自身の考えです)
現状のTLS1.3では以下の問題があります。
- 後方互換性を保つために不要なフィールドや不要なハンドシェイクメッセージを送付する
- N/W経路によるタッピングによるパケットが硬直化されている問題
- よりコンパクトにするためのエンコーディング

これらを解決するためにTLS1.3と直接的な互換性があるわけではないですが同型としてのCompact TLSを定義し、今後相互運用ができるように普及させていきたい。


### 解決方法
このドキュメントではTLS1.3のコンパクトなバージョンによる(以下、cTLSと呼ぶ)、ネットワークの最小バンド幅を目指して設計される。
cTLSはTLS1.3とは直接的に互換性があるわけではないが、最終的にはcTLSとTLS1.3が相互運用できるようになることを目指している。

以下の4つの方法を用いることでコンパクトにしようとしている。
- 以前のTLSバージョンの残骸となるような不要な変数の省略
- 初期バージョンのTLSとの後方互換性を保護するために必要とされるフィールドやハンドシェイクメッセージの省略
- 不要な値を省略することにより、さらにコンパクトなエンコーディング
- テンプレートを元にした特別なメカニズムによって、不要な値を省略したTLSのアプリケーションに特化したバージョンを作成することを許容する。


# 技術的詳細
## Common Primitives

### Varints
cTLSでは最小のエンコーディングで、幅広い整数を扱うために可変長整数を最大限に利用しようとします。
整数の幅は最初の2bitで以下のように決定される。

```
+----------------------------+----------------+
| Bit pattern                | Length (bytes) |
+----------------------------+----------------+
| 0xxxxxxx                   | 1              |
|                            |                |
|                            |                |
|                            |                |
| 10xxxxxx xxxxxxxx          | 2              |
|                            |                |
|                            |                |
|                            |                |
| 11xxxxxx xxxxxxxx xxxxxxxx | 3              |
+----------------------------+----------------+
```

1byteの場合には最大で127まで表現できる
TLSの可変長整数は「varints」であることを示す。そして、varintsのレンジを持ったVectorは以下のように示されます。
```
opaque foo<1..V>;
```

cTLSではTLS中の全ての整数をvarintsに置き換えることになります。下記が含まれます。
- Values of uint8, uint16, uint24, uint32, and uint64
- Vector length prefixes
-  Enum / code point values


### Record Layer
cTLSでは長さはUDPデータグラムに含まれることを想定しているのでTLSPlaintextからはlengthも不要となる。
```
struct {
    ContentType type;
    opaque fragment[TLSPlaintext.length];
} TLSPlaintext;
```

TLS1.3と比較して以下の2つは不要となる。
- legacy_record_version
- length


さらにTLSCiphertextからはdummyのcontent-typeが不要となる。
```
struct {
    opaque content[TLSPlaintext.length];
    ContentType type;
    uint8 zeros[length_of_padding];
} TLSInnerPlaintext;

struct {
    opaque encrypted_record[TLSCiphertext.length];
} TLSCiphertext;
```

TLS1.3と比較してTLSCiphertextからは下記フィールドが削除されます。
- opaque_type
- legacy_record_version
- length


### Handshake Layer
以下の２つを除いてはcTLSハンドシェイクはTLS1.3ハンドシェイクと同じです
- lengthフィールドの省略
- HelloRetryRequestはServerHelloに特化した形ではない本当のハンドシェイクメッセージとなる


## ハンドシェイクメッセージの変更

### ClientHello
```
opaque Random[RandomLength];      // variable length

struct {
    Random random;
    CipherSuite cipher_suites<1..V>;
    Extension extensions<1..V>;
} ClientHello;
```

TLS1.3と比較してcTLSでは以下のフィールドが削減されている。
- legacy_version
- legacy_session_id
- legacy_compression_methods

### ServerHello
```
struct {
    Random random;
    CipherSuite cipher_suite;
    Extension extensions<1..V>;
} ServerHello;
```

TLS1.3と比較してcTLSでは以下のフィールドが削減されている。
- legacy_version
- legacy_session_id_echo
- legacy_compression_method


### HelloRetryRequest
HelloRetryRequestはServerHelloと同じではあるが、不要なrandomが削減されている。
```
struct {
    CipherSuite cipher_suite;
    Extension extensions<2..V>;
} HelloRetryRequest;
```


## Template-Based Specialization
TBD



# 資料
- https://datatracker.ietf.org/doc/draft-rescorla-tls-ctls/
