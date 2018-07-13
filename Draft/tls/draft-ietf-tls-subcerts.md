# Delegated Credentials for TLS

# 解決したい課題
秘密鍵をサーバ側に保持せず集中管理できるようにするのは、特にマルチテナントのCDNプロバイダーなどが望んでいるアーキテクチャです。
そのままでは秘密鍵サーバへのRTT (Round Trip Time)の影響が大きいことから、サーバ認証を別の方法で短期的に委任できる、有効な方法を検討する仕様が必要とされています。

上記の他にも次のような問題があります
- サーバオペレータが新しい証明書を発行したい場合にはCAと連絡を取る必要がある
- サーバオペレータはCAが発行したクレデンシャルによるTLS認証スキームにもを利用することができる

上記については外部CA依存は実践上で次のような問題になる
- サーバオペレータはlow-trust zone(CDNやリモートデータセンター)に対して生存期間の短い証明書を発行したい場合

つまり、生存期間が短い証明書を独自で発行できるような委譲の仕組みが解決したい課題である。

# 解決手段
先に上げた問題点を解決するために、TLSサーバオペレータに対して外部CAによって発行された証明書のスコープ内で自身のクレデンシャルを持つことを許可するといった制限のある委譲メカニズムを提供する。
なぜならば、先に上げた問題というのはCAが検証している名前所有の検証とは無関係の問題だからである。

- 1. クライアントはClientHello中にdelegated_credential拡張を指定する
- 2. サーバはClintHello中にdelegated_credentialが存在していたら、ServerHello中に拡張を応答します。もし拡張が存在していなければ、クレデンシャルを送付してはいけません。 TLS1.2はDelegatedCredentialはServerHelloの拡張に含めて、TLS1.3ではCertificateEntryに含めなければなりません。
  - DelegatedCredentialの構造体は次のとおりです
```
   struct {
     uint32 valid_time;
     opaque public_key<0..2^16-1>;     // サーバ証明書中のSubjectPublicKeyInfoの値なので、サーバ証明書とcredentialが紐付いているのかをちぇっくする?
   } Credential;

   struct {
     Credential cred;
     SignatureScheme scheme;
     opaque signature<0..2^16-1>;
   } DelegatedCredential;
```
- 3. クライアントはクレデンシャルと証明書チェーンを受け取ると、クライアントは証明書チェーンの検証をする。
- 4. クライアントは引き続き次の検証を行う
  - クレデンシャルの時刻が有効期間内であるかと、クレデンシャルのTTLが7日を超過していないことを検証する。
  - サーバ証明書中にDelegationUsageが含まれているかを確認する。含まれていればDelegated credentialsの使用を許可する。
  - サーバ証明書中の公開鍵を使って、クレデンシャルの署名を検証する

# 参考URL
- https://tools.ietf.org/html/draft-ietf-tls-subcerts-01
- スライド
  - IETF98
    - https://datatracker.ietf.org/meeting/98/materials/slides-98-tls-delegated-credentials-00

# TODO
- RelatedWorkなどについて読めていない
- DelegatedCredentialの中にpublic_keyがあるのはなんでか?
- どのようにしてDelegated Certificateのsignatureを発行できるの? また、どのようにしてTLSサーバとしてセットアップが行われるのか?
