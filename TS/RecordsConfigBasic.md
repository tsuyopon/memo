# 概要
records.configに関する基本的な設定についてをまとめておく
基本的にはこの辺に記載されています。
- https://docs.trafficserver.apache.org/en/7.1.x/admin-guide/files/records.config.en.html

# 詳細


### リバースプロキシを有効にする
```
proxy.config.reverse_proxy.enabled
```
- https://docs.trafficserver.apache.org/ja/5.3.x/reference/configuration/records.config.en.html#proxy-config-reverse-proxy-enabled

### URLのremapが必要かどうかの設定
もしマッチしなければ、ブラウザはエラーを返す
```
proxy.config.url_remap.remap_required
```
- https://docs.trafficserver.apache.org/en/7.1.x/admin-guide/files/records.config.en.html#proxy-config-url-remap-remap-required

### URL remapした後にHostヘッダを維持したい場合
```
proxy.config.url_remap.pristine_host_hdr
```
- https://docs.trafficserver.apache.org/en/7.1.x/admin-guide/files/records.config.en.html#proxy-config-url-remap-pristine-host-hdr

### ATSサーバポートを変更する
デフォルトでは8080になっています。
```
proxy.config.http.server_ports
```
- https://docs.trafficserver.apache.org/ja/5.3.x/reference/configuration/records.config.en.html#proxy-config-http-server-ports
