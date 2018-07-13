# Encrypted Server Name Indication for TLS 1.3

# 解決したい課題
TLS1.3では大抵のハンドシェイクを暗号化しますが、経路上に存在するアタッカーには次の情報を提供することになります。
- DNSクエリは平文
- サーバIPアドレスが見える。サーバはドメインベースのバーチャルホストを使っていないことが推測されることになる。
- SNI(RFC6066)が見えるClientHelloメッセージが平文で流れる。


# 解決方法

ENSIをサポートするプロバイダーがencrypted_server_name拡張を持ったClientHello中のserver_nameを置き換える。
encrypted_server_name拡張はプロバイダーの公開鍵の元で暗号化された値を持つ。

プロバイダーは拡張を解読して、コネクションを終了させたり(SHARED MODE)、バックエンドサーバにそれを送ったり(SPLIT MODE)することができる。　


### SHARED MODE
プロバイダとオリジンサーバが同居する方式をSHARED MODEという。
```
                   +---------------------+
                   |                     |
                   |   2001:DB8::1111    |
                   |                     |
   Client <----->  | private.example.org |
                   |                     |
                   | public.example.com  |
                   |                     |
                   +---------------------+
                           Server

                      Figure 1: Shared Mode Topology
```


### SPLIT MODE
プロバイダとオリジンサーバが同居しない方式をSHARED MODEという。
```
                   +--------------------+       +---------------------+
                   |                    |       |                     |
                   |   2001:DB8::1111   |       |   2001:DB8::EEEE    |
   Client <------------------------------------>|                     |
                   | public.example.com |       | private.example.com |
                   |                    |       |                     |
                   +--------------------+       +---------------------+
                     Client-Facing Server            Backend Server

                       Figure 2: Split Mode Topology
```


# 仕様詳細
SNI Encryption keysは、下記に述べるESNIKeys鍵構造を使うことによってDNSで発行することができる。
```
       // Copied from TLS 1.3
       struct {
           NamedGroup group;
           opaque key_exchange<1..2^16-1>;
       } KeyShareEntry;

       struct {
           uint8 checksum[4];
           KeyShareEntry keys<4..2^16-1>;
           CipherSuite cipher_suites<2..2^16-2>;
           uint16 padded_length;
           uint64 not_before;
           uint64 not_after;
           Extension extensions<0..2^16-1>;
       } ESNIKeys;
```


### encrypted_server_name拡張
```
      struct {
          CipherSuite suite;
          opaque record_digest<0..2^16-1>;
          opaque encrypted_sni<0..2^16-1>;   // server_name拡張からのオリジナルのサーバ名のリスト
      } EncryptedSNI;
```

# 参考URL
- https://tools.ietf.org/html/draft-rescorla-tls-esni-00
