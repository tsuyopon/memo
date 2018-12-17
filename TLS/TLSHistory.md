# TLSに関する歴史などについてまとめる

とりあえずSSLに関する説明や役に立ちそうなリンク集など
SSL(Secure Socket Layer)の開発元はNetscape、TLS(Transport Layer Security)の開発元はIETFとなっている。SSLとTLSのバージョンは次の通り。
```
SSL1.0    ✕    最初のSSLとして設計したが、設計レビューの時点でプロトコルの脆弱性が発見されたため破棄されている。
SSL2.0    ✕    SSL1.0の問題を修正して設計後、1994年にSSL2.0として発表。その後、いくつか脆弱性が発見されてSSL3.0が登場するが、未使用でもSSL2.0が有効な状態の場合に提示する最弱のアルゴリズムを使用させるダウングレード攻撃などを受ける可能性があるので、明示的に無効にする必要がある。
SSL3.0    ✕    SSL2.0の問題を修正して機能追加も行い1995年にSSL3.0として発表。ただ、古くなってきている。CVE-2014-3566で脆弱性が発生したため明示的に無効にする必要がある。
TLS1.0    △   SSL3.0とTLS1.0の両者間には正確な互換性はないがほぼ同じ。CVE-2011-3389(BEAST)による一部脆弱性を含む。
TLS1.1    ◯   TLS 1.0からの変更点は、新しく発見された攻撃手法に対する耐性の強化が中心である。
TLS1.2    ◎   ハッシュのアルゴリズムにSHA-256が追加されたほか、ブロック暗号について、従来のCBCモードだけではなく、GCM、CCMといった認証付き暗号が利用可能となった。
TLS1.3    ?    [ドラフト]インターネット環境の変化とTLS1.2までの暗号化強度不足を改善するため2016年中に仕様化完了を目指している(らしい)
```

# TLS歴史概略
以下、概略
- SSL1.0
  - 最初SSLとして設計したが、設計レビューの時点でプロトコルに脆弱性が発見されたためにリリースされていない。
- SSL2.0
  - 数年使われたが実用上欠陥があった。
- SSL3.0
  - 大きな変更があった。pooldleがSSL3.0にトドメを指した。
  - ガラケーのサポートはたいていここまでとなっている。
- TLS1.0
  - 非常にマイナーな修正(SSL3.1相当の修正)
- TLS1.1
  - セキュリティに関する修正が行われた。
- TLS1.2
  - AEAD + ハンドシェイクが追加された

概念図などは以下を参考のこと
- http://qiita.com/kuni-nakaji/items/5118b23bf2ea44fed96e#comment-456cb90d89c71c924782
