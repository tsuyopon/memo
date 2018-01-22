# 概要
TLS周りについて

# 詳細

### クライアントとtrafficserverのTLS通信設定
- https://docs.trafficserver.apache.org/en/latest/admin-guide/security/index.en.html#client-and-traffic-server-connections

### trafficserverとoriginサーバのTLS通信設定
- https://docs.trafficserver.apache.org/en/latest/admin-guide/security/index.en.html#traffic-server-and-origin-server-connections

### TLSセッションチケット拡張
- https://docs.trafficserver.apache.org/en/latest/admin-guide/security/index.en.html#rotating-tls-session-ticket-keys

### OCSP設定
- https://docs.trafficserver.apache.org/en/latest/admin-guide/security/index.en.html#ocsp-stapling

OCSP関連設定は以下の通りです
```
proxy.config.ssl.ocsp.enabled
proxy.config.ssl.ocsp.cache_timeout
proxy.config.ssl.ocsp.request_timeout
proxy.config.ssl.ocsp.update_period
```
