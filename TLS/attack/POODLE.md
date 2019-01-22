TODO: 攻撃手法を埋める

# 概要
POODLE（Padding Oracle On Downgraded Legacy Encryption）攻撃は、SSL 3.0プロトコルの脆弱性を突く攻撃のことです。
2014年12月8日に発表された脆弱性で、CVE-2014-3566として番号が割り当てられています。

大元の論文は次の資料となります。
- https://www.openssl.org/~bodo/ssl-poodle.pdf

この攻撃によってSSL3.0は終焉を迎えることとなりました。

# 詳細
### どのような攻撃か
SSLv3プロトコルのパディングの問題点を突いて、効率的に暗号文を復号できしまうので、例えばセッションクッキーを復号して通信を盗聴することができる。
Webサイト利用時の認証情報（クッキー、トークンなど）を窃取することが可能になります(たとえば、Authorizationのbearerトークンなど)。

### 攻撃手法
- TBD

### 対処方法
- サーバ・クライアント側のいずれかでSSL3.0 を無効にすることで回避することができます。
- TLS_FALLBACK_SCSV仕様をサーバ・クライアントで実装すること
  - TLS_FALLBACK_SCSVはPOODLE脆弱性を受けて速やかにRFC策定されたものである。
- POODLE脆弱性はSSLv3とブロック暗号のCBCブロックモードを使用した場合に影響があるので、次のCiphersuiteを選択することで問題を緩和できます。
  - 認証付暗号化方式(AEAD)であるGCMブロックモードの暗号スイートを使用する
  - ストリーム暗号(RC4,ChaChaなど)を使用する

# 参考URL
- POODLE
  - https://www.openssl.org/~bodo/ssl-poodle.pdf
- 技術解説
  - https://www.imperialviolet.org/2014/10/14/poodle.html
- 自堕落な技術者の日記
  - http://blog.livedoor.jp/k_urushima/archives/1752935.html
