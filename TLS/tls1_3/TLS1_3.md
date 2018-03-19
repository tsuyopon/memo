# 概要
TLS1.3についての概要

現時点で最新はdraft26となる。
- https://tools.ietf.org/html/draft-ietf-tls-tls13-26

# TLS1.2未満とTLS1.3の違いについて
- 全般
  - CBCモードが廃止され、AEAD(AES-GCM, ChaCha20-Poly1305など)
    - CBCモードを狙ったBEAST攻撃、Lucky Thirteen攻撃などが頻発したことが背景にある。
- ClientHello
  - TLS1.2と互換性がある
  - サーババージョンはSupported Version拡張(必須)にその役割を移動し、固定で0x0303(TLS1.2)
  - session_idやcompression_methodsは廃止され、代わりにPSKが利用される。ミドルボックス問題のためにlegacy_としてその名残は残る。
  - extensionは必ず存在することになる
  - extensions中で暗号パラメータのやりとりが行われる
- ServerHello
  - 互換性がなくなった
- ClienKeyExchange
  - 廃止
  - ClientHello中のExtensionに移動する
- ServerKeyExchange
  - 廃止
  - ServerHello中のExtensionに移動する
- ChangeCipherSpec
  - 廃止
  - 鍵交換直後に暗号化が開始される

TODO: まだ整理していないので後で追記

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

### TLS1.3 draft23として公開されているサーバ
- https://enabled.tls13.com
- https://www.tls13.facebook.com
- https://tls13.crypto.mozilla.org

# 参考資料
- TLS 1.3 の標準化動向(IIJ: 山本和彦さん)
  - draftの歴史などについて。なぜ仕様が変わっていったのかを垣間見れて面白い
  - http://www.mew.org/~kazu/material/2018-tls13.pdf
- TLS 1.3 draft 23 ハンズオン(IIJ: 山本和彦さん)
  - Haskel用クライアントライブラリやpicotlsの説明
  - http://www.mew.org/~kazu/material/2018-handson.pdf
- TLS1.3とは何か? 大津さん資料
  - https://speakerdeck.com/shigeki/tls1-dot-3tohahe-ka
- あどけない話
  - 山本和彦さんによるTLS1.3について20回以上に分割して掲載している。すごい勉強になる記事
  - http://d.hatena.ne.jp/kazu-yamamoto/archive
- 今なぜHTTPS化なのか？インターネットの信頼性のために、技術者が知っておきたいTLSの歴史と技術背景
  - https://employment.en-japan.com/engineerhub/entry/2018/02/14/110000
- TLS1.3 Overview
  - https://qiita.com/sylph01/items/3bf7bc2d42da4e0efb37	
