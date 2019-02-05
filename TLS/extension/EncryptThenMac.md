# 概要
この仕様(RFC7366)はTLS, DTLSにおいて現行のMAC-Then-Encryptのメカニズムを置き換えてEncrypt-Then-MACの仕様をネゴシエーションするための手段についてTLS拡張機能として規定している。

つまり、MACを次のMAC-Then-Encryptから
```
encrypt( data || MAC || pad )
```

Encrypt-Then-MACへと変換するためのネゴシエーションを可能とするTLS拡張である。
```
encrypt( data || pad ) || MAC
```

上記の詳細は以下のwikipediaも参考のこと
- https://ja.wikipedia.org/wiki/%E8%AA%8D%E8%A8%BC%E4%BB%98%E3%81%8D%E6%9A%97%E5%8F%B7

# 詳細
### 解決したい課題
MAC-Then-Encryptは2000年以前までは安全であると考えられていたが、現在では脆弱性や攻撃対象となってしまっている。


### 利用方法
サーバとクライアント双方がTLS拡張に対応していたらMAC-Then-Encryptをネゴシエーションできるようにした。
- 1. Encrypt-Then-MACを利用したいクライアントはClientHello中にencrypt_then_mac拡張を含める
- 2. サーバは対応していたらServerHello中にencrypt_then_macを含めて応答する
- 3. 双方で対応していることがネゴシエーションされた場合には、encrypt_then_macで処理を行わなければならない。


### MACの計算方法

TLS1.0 (IV無し)の場合
```
   MAC(MAC_write_key, seq_num +
       TLSCipherText.type +
       TLSCipherText.version +
       TLSCipherText.length +
       ENC(content + padding + padding_length));
```


TLS1.1以上でIV有りの場合
```
   MAC(MAC_write_key, seq_num +
       TLSCipherText.type +
       TLSCipherText.version +
       TLSCipherText.length +
       IV +
       ENC(content + padding + padding_length));
```

### 再ハンドシェイク問題
最初の接続(Current Session)の後は、再ネゴシエーション後も同じ設定を保持すべきである。
しかし、状態を変更したい場合には次の表を参考にすると良い。
セキュリティ安全性の高いEncrypt-then-MACからセキュリティ安全性の低いEncrypt-then-MACに変更する場合にはエラーとなります。

```
   +------------------+---------------------+--------------------------+
   | Current Session  |     Renegotiated    |      Action to take      |
   |                  |       Session       |                          |
   +------------------+---------------------+--------------------------+
   | MAC-then-encrypt |   MAC-then-encrypt  |        No change         |
   |                  |                     |                          |
   | MAC-then-encrypt |   Encrypt-then-MAC  |        Upgrade to        |
   |                  |                     |     Encrypt-then-MAC     |
   |                  |                     |                          |
   | Encrypt-then-MAC |   MAC-then-encrypt  |          Error           |
   |                  |                     |                          |
   | Encrypt-then-MAC |   Encrypt-then-MAC  |        No change         |
   +------------------+---------------------+--------------------------+
```

# Encrypt-then-MACとMAC-then-Encryptの違い
 
- 参考
  - https://ja.wikipedia.org/wiki/%E8%AA%8D%E8%A8%BC%E4%BB%98%E3%81%8D%E6%9A%97%E5%8F%B7
  - https://crypto.stackexchange.com/questions/202/should-we-mac-then-encrypt-or-encrypt-then-mac


# SeeAlso
- Encrypt-then-MAC for Transport Layer Security (TLS) and Datagram Transport Layer Security (DTLS)
  - https://tools.ietf.org/html/rfc7366

