# TLSの歴史
TLS周りの歴史やバージョンごとの差異についてまとめる

# 詳細
### TLS概略

とりあえずSSLに関する説明や役に立ちそうなリンク集など
SSL(Secure Socket Layer)の開発元はNetscape、TLS(Transport Layer Security)の開発元はIETFとなっている。SSLとTLSのバージョンは次の通り。
```
SSL1.0    最初のSSLとして設計したが、設計レビューの時点でプロトコルの脆弱性が発見されたため破棄されている。
SSL2.0    SSL1.0の問題を修正して設計後、1994年にSSL2.0として発表。その後、いくつか脆弱性が発見されてSSL3.0が登場するが、未使用でもSSL2.0が有効な状態の場合に提示する最弱のアルゴリズムを使用させるダウングレード攻撃などを受ける可能性があるので、明示的に無効にする必要がある。
SSL3.0    SSL2.0の問題を修正して機能追加も行い1995年にSSL3.0として発表。ただ、古くなってきている。CVE-2014-3566で脆弱性が発生したため明示的に無効にする必要がある。
TLS1.0    SSL3.0とTLS1.0の両者間には正確な互換性はないがほぼ同じ。CVE-2011-3389(BEAST)による一部脆弱性を含む。
TLS1.1    TLS 1.0からの変更点は、新しく発見された攻撃手法に対する耐性の強化が中心である。
TLS1.2    ハッシュのアルゴリズムにSHA-256が追加されたほか、ブロック暗号について、従来のCBCモードだけではなく、GCM、CCMといった認証付き暗号が利用可能となった。
TLS1.3    CipherSuiteを5つに絞り古いのは廃止AEADのみとなった。PFS。ハンドシェイク改善、1RTT追加、HKDFによる鍵派生関数再定義
```

SSL時代はNetscape社による開発だが、TLSになってIETFで標準化されるようになった。

### バージョン差異
- SSL1.0(Never Released)
  - 最初SSLとして設計したが、設計レビューの時点でプロトコルに脆弱性が発見されたためにリリースされていない。
- SSL2.0(1995)
  - 数年使われたが実用上欠陥があった。
  - 2011/3 RFC6176によって仕様を禁止
- SSL3.0(1996) RFC6101
  - SSL2.0からは名前は一緒であるが設計が根本から見直されています。
    - key materialはメッセージ認証や解読時に双方で再利用しなくなった。
    - MAC構成をより高めた。SHA1をサポートした。
    - ハンドシェイクの保護を追加した。サーバサイドではダウングレード攻撃が検出できるようになった。
    - closureアラートのサポートを追加
  - POODLEがSSL3.0にトドメを指した(2014/10) RFC7568によっても廃止された(2015/6)
  - ガラケーのサポートはたいていここまでとなっている。
- TLS1.0(1999) RFC2246
  - 非常にマイナーな修正(SSL3.1相当の修正)ではあるが、SSL3.0との互換性は無い。
    - 最初に交換したsecretの値から暗号鍵の拡張を行う機能が改善された。
    - MACを構成するアルゴリズムがHMACへと修正された。
    - DH鍵交換、DSS、3DESのサポートの義務化
  - PCI DSSという1つの規格の中で廃止が推奨されるようになった。
- TLS1.1(2006) RFC4346
  - セキュリティに関する修正が行われた。
    - CBC攻撃に対抗するためのimplicitなIVをexplicitなIVへと置き換える
    - CBC攻撃に対抗するためにpadding errorの扱いをdecryption_failedアラートからbad_record_macを使うように修正された
    - TLSでの新しい攻撃のためにinformationalなnoteが追加された
    - Premature closes no longer cause a session to be nonresumable. (TODO: よくわからなかったのでRFCからそのまま抜粋)
  - IANAレジストリにプロトコルパラメータの定義が行われた
    - https://tools.ietf.org/html/rfc4346#section-12
- TLS1.2(2008) RFC5246
  - TLS拡張が追加された
  - PRF関数において今まではMD5/SHA-1のコンビネーションで計算されていたが、cipher_suiteで指定されたPRFに置き換えられることになった。特に指定がなければP_SHA256が利用される。
  - cipher_suite関連の変更
    - TLS_RSA_WITH_AES_128_CBC_SHAがcipher_suiteとしての実装義務化とされる。
    - HMAC-SHA256が追加された。
    - IDEAとDESが削除され、これらはDeprecatedとなった。
    - AESが追加された
    - AEADが追加された
  - Alertがいくつかのケースで送るべき(MUST)となった。
  - certificate_requestメッセージの後に、もし利用可能な証明書がなかったとしても、空の証明書リストのメッセージを送付しなければならないように規定
- TLS1.3(2018) RFC8446
  - Cipher_Suite関連
    - PFSをサポート
      - 全ての鍵交換はEphemeral((EC)DHE)かPSKで行われなければならなくなった。
    - AEAD暗号のみをサポート
    - 古い脆弱な暗号の廃止(static RSA, DH, ECDH, RSA, RC4, MD5, SHA224, EXPORT)
    - CipherSuitesの形式の変更(鍵交換とサーバ認証を含まなくなった。MAC部分について変更されることになった)
    - Elliptic curve(supported_group)やSignatureAlgorithmsが基本仕様となる。TLS1.3では1つのpoint formatが望ましいとしてec_point_format拡張を廃止
  - 圧縮やリネゴシエーション廃止
  - 鍵派生関数(HKDF)が再設計された
  - 0-RTTの追加
  - 1-RTTハンドシェイクによるパフォーマンス改善等
    - ServerHelloDone, ClientKeyExchange, ServerKeyExchange, ChangeCipherSpecの廃止、EncryptedExtensionsの追加
      - StateMachineを定めることによってServerHelloDone, ChangeCipherSpecなどが不要になった。
    - ServerHelloの互換性はなく、TLS1.2のServerHelloはTLS1.3ではServerHelloとEncryptedExtensionsの２つのメッセージへと分割された
    - ServerHelloから後のメッセージは暗号化されて送付されるようになった。
  - MiddleBox介在を防ぐためにTLS1.2と同一のパケット構成にて、バージョンはsupported_version拡張にて実施

参考資料
- Strong SSL Configuration & Compatibility Report
  - SSLv2とSSLv3の違い、SSLv3とTLSv1の違いが記載されている重要な資料
  - http://www.g-sec.lu/ssl_recommendations.pdf
- RFC6101(Appendix E.  Version 2.0 Backward Compatibility)
  - https://tools.ietf.org/html/rfc6101#appendix-E
- RFC4346 (Differences from TLS 1.0)
  - https://tools.ietf.org/html/rfc4346#section-1.1
- RFC5246 (Major Differences from TLS 1.1)
  - https://tools.ietf.org/html/rfc5246#section-1.2
- RFC8446 (Major Differences from TLS 1.2)
  - https://tools.ietf.org/html/rfc8446#section-1.2
- wolfSSL: A Comparison of Differences in TLS 1.1 and TLS 1.2
  - https://www.wolfssl.com/a-comparison-of-differences-in-tls-1-1-and-tls-1-2/
- keycdn: TLS 1.2 vs TLS 1.1
  - https://www.keycdn.com/support/tls-1-2-vs-tls-1-1

概念図などは以下を参考のこと
- http://qiita.com/kuni-nakaji/items/5118b23bf2ea44fed96e#comment-456cb90d89c71c924782

