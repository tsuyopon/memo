# 概要
TLS1.3についての全体像について記載します。

# TLS1.2未満とTLS1.3の違いについて
あらかじめRFCにTLS1.2とTLS1.3の違いがあるのでそちらを確認しておくこと
- https://tools.ietf.org/html/rfc8446#section-1.2


# 全体像
- 全般
  - RFC記載のGOALの変更
    - RFC8446: Authentication, Confidentiality, Integrity
    - RFC5246: Cryptographic security, Interoperability, Extensibility, Relative efficiency
  - CBCモードが廃止され、AEAD(AES-GCM, ChaCha20-Poly1305など)
    - CBCモードを狙ったBEAST攻撃、Lucky Thirteen攻撃などが頻発したことが背景にある。
    - Static RSAやDH cipher suiteは削除され、すべての鍵交換メカニズムはPerfect Forward Secrecyとなった。
  - CipherSuitesは5種類のみに変更
    - 共通鍵暗号(AES/CHACHA20)とそのメッセージ認証形式(GCM-SHA384等)を指定することになります。
    - サーバ証明書の確認や鍵交換方式は暗号スイートに含まれません。TLS\_<AEAD>\_<HKDFハッシュ> というcipherに変更になります。
  - コネクションのRoundTripTimeの削減。2RTTから1RTTへの変更
  - State Machineの定義
  - メッセージの変更
    - ServerHelloに含まれる拡張は鍵交換に必要な情報のみに変更
    - HelloRetryRequest、EncryptedExtensionsの追加
    - ChangeCipherSpecの削除(ミドルボックス互換性は残す)
    - ClientCertificate、ServerCertificateはCertificateへ統合
    - HelloRequest、ServerHelloDone、ClienKeyExchange、ServerKeyExchangeの削除
  - 0RTTモードの追加
  - 鍵交換モードの追加
    - ECDHE
    - PSK-only
    - SDK with ECDHE
  - PRFからHKDFへの変更
    - PRFのようにエントロピーの強さがよくわからないものからExpandさせるよりも、暗号学的により強いエントロピーを持ったランダムなキー生成が必要ということでHKDFが採用された。
  - SessionIDやSessionTicketを利用したSessionResumptionは全てPSKに置き換わることとなった
    - NewSessionTicketメッセージを新しく導入し、ハンドシェイク完了後にこのメッセージを受け取ることでPSKを取得することができます。
  - Renegotiationの廃止
    - 今までクライアント認証、鍵アップデートが発生するとRenegotiationしていたが、PostAuthentication Messageを定義することで同一ハンドシェイク中で行うことになった。
    - なお、シーケンス番号がオーバーフローした場合にもRenegotiationしていたが、これはTLS1.3ではカバーせず、切断を切ることがわかった。
  - EncryptedExtensionsメッセージ以降は暗号化されている。
  - TLS拡張に関するいくつかの変更
    - supported\_versions拡張でサポートするバージョンをリスト形式を受け付ける。
    - signature\_algorithms\_cert拡張を追加
    - ec\_point\_format拡張を廃止
    - key\_share拡張を追加
    - pre\_shared\_key拡張を追加
    - psk\_key\_exchange\_mode拡張を追加
    - early\_data拡張を追加
  

- 各種メッセージ詳細
  - ClientHello
    - TLS1.2と互換性がある
    - サーババージョンはSupported Version拡張(必須)にその役割を移動し、固定で0x0303(TLS1.2)
    - session\_idやcompression\_methodsは廃止され、代わりにPSKが利用される。ミドルボックス問題のためにlegacy\_としてその名残は残る。
      -  legacy_version、 legacy_session_id、 legacy_compression_methodsという変数となる
    - extensionは必ず存在することになる
    - extensions中で暗号パラメータのやりとりが行われる
  - ServerHello
    - 互換性がなくなった
    - ServerHelloに鍵交換に必要な拡張情報を含めて、それ以外は暗号化されたEncryptedExtensionに含まれるようになった


廃止されるがミドルボックスとしての互換性のために残されるメッセージ
- ChangeCipherSpec
  - 廃止
  - 鍵交換直後に暗号化が開始される

廃止されるメッセージ
- ServerHelloDone
  - 廃止
  - TLS1.2までは厳密にServerHelloの終了パケットはこれで判定していたが、StateMachineを定めることによって不要となった。
- ClienKeyExchange
  - 廃止
  - ClientHello中のExtensionに移動する
- ServerKeyExchange
  - 廃止
  - ServerHello中のExtensionに移動する

# 詳細

### ブラウザからどのTLSプロトコルを利用しているのかどうかを確認する
- chrome
  - Developer Toolsの「Security」タブから確認することができます。
- firefox
  - 開発ツールを開いたら「暗号化」タブでどのプロトコルを利用しているのかを確認することができます。

### 接続確認の方法など
- サーバとして起動する
```
$ /opt/openssl-1.1.1/bin/openssl s_server -accept 443 -cert server.crt -key server.key -www -debug -tls1_3
```

- クライアントとして接続する
```
$ /opt/openssl-1.1.1/bin/openssl s_client -connect localhost:443 --tls1_3
```

### TLS1.3として公開されているサーバ
- https://enabled.tls13.com
- https://www.tls13.facebook.com
- https://tls13.crypto.mozilla.org

### CipherSuiteの指定について
TLS1.3ではCipherSuiteの指定で共通鍵交換と証明書検証を含まないようになりました。

- TLS1.2
```
RSA_WITH_AES_128_CBC_SHA
ECDHE_ECDSA_WITH_AES_128_CBC_SHA256
```
- TLS1.3
```
共通鍵交換: secp256r1
証明書検証: rsa_pkcs1_sha256
暗号化: AES_128_GCM_SHA256
```

TLS1.3では共通鍵交換はKeyShare拡張、サーバ認証はSignatureAlgorithms拡張となりました。

### TLS1.3の実装リスト
- https://github.com/tlswg/tls13-spec/wiki/Implementations

# 全体像を理解するために参考になる資料
- 今なぜHTTPS化なのか？インターネットの信頼性のために、技術者が知っておきたいTLSの歴史と技術背景
  - https://employment.en-japan.com/engineerhub/entry/2018/02/14/110000
- TLS1.3とは何か? 大津さん資料
  - https://www.jnsa.org/seminar/pki-day/2016/data/1-3_ootsu_.pdf
- TLS 1.3 の標準化動向 山本和彦さん資料
  - draftの歴史などについて。なぜ仕様が変わっていったのかを垣間見れて面白い
  - http://www.mew.org/~kazu/material/2018-tls13.pdf
- TLS 1.3 draft 23 ハンズオン(IIJ: 山本和彦さん)
  - Haskel用クライアントライブラリやpicotlsの説明
  - http://www.mew.org/~kazu/material/2018-handson.pdf
- あどけない話
  - 山本和彦さんによるTLS1.3について20回以上に分割して掲載している。すごい勉強になる記事
  - http://d.hatena.ne.jp/kazu-yamamoto/archive
- TLSv1.3: Minor Version, Major Changes. F5
  - https://www.f5.com/pdf/agility2018/TLSv13-Minor-Version-Major-Changes.pdf
- TLS1.3 Overview
  - https://qiita.com/sylph01/items/3bf7bc2d42da4e0efb37	
- 祝RFC！Transport Layer Security (TLS) 1.3 発行の軌跡 ～熟成された4年間の安全性解析～  レピダム
  - https://lepidum.co.jp/blog/2018-10-01/tls1\_3security/

# 参考情報
- 実装時に参考となるwiki
  - https://wiki.openssl.org/index.php/TLS1.3
- TLS1.3で使える・使えない暗号アルゴリズム
  - https://qiita.com/s\_machida/items/0f6ef0466503c0f00839
- Traffic Analysis of an SSL/TLS Session
  - ASCIIアートのパケット構造が役に立つ
  - http://blog.fourthbit.com/2014/12/23/traffic-analysis-of-an-ssl-slash-tls-session
