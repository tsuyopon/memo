# 概要
TLS関連について
TLS1.3関連についてはtls1.3/README.mdを参照のこと

# TLSパケットの可視化
- The Illustrated TLS Connection
  - https://tls.ulfheim.net/
  - TLS1.3
    - https://tls13.ulfheim.net/

# ウェブサーバ
- Apache, Nginx, Lighttpd, HAProxy, AWS ELFなどのTLS設定を自動的に出力するgenerator
  - https://mozilla.github.io/server-side-tls/ssl-config-generator/

# ライブラリ実装
- TLS実装の比較
  - https://ja.wikipedia.org/wiki/TLS%E5%AE%9F%E8%A3%85%E3%81%AE%E6%AF%94%E8%BC%83

# RFC
- Transport Layer Security(wikipedia)
  - TLS各バージョンの暗号対応、クライアント対応状況、ライブラリ対応状況など様々な比較表が存在する
  - RFCなどもTLSバージョン毎に以下のページにまとまっているので参照すべし
  - https://en.wikipedia.org/wiki/Transport_Layer_Security

# IANA
- Transport Layer Security (TLS) Extensions
  - https://www.iana.org/assignments/tls-extensiontype-values/tls-extensiontype-values.xml

# 参考資料
- SSL and TLS Deployment Best Practices
  - https://github.com/ssllabs/research/wiki/SSL-and-TLS-Deployment-Best-Practices
- SSL Server Rating Guide
  - https://github.com/ssllabs/research/wiki/SSL-Server-Rating-Guide
- OpenSSL CookBook
  - https://www.feistyduck.com/library/openssl-cookbook/online/
- Mozilla wiki: Security/Server Side TLS
  - https://wiki.mozilla.org/Security/Server_Side_TLS
