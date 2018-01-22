# Configuration Remap Plugin
このプラグインはremapプラグインとして機能します。
リマップルールに依存して設定の上書きすることを許可します。

# 使い方
使い方には次の２種類の方法があります。
- 1. インラインディレクティブ
  - remap.configなどに直接記述してしまう方法です。
```
map http://cdn.example.com/ http://origin.example.com/ @plugin=conf_remap.so @pparam=proxy.config.url_remap.pristine_host_hdr=1
```

- 2. 外部設定ファイル
```
map http://cdn.example.com/ http://some-server.example.com @plugin=conf_remap.so @pparam=/etc/trafficserver/cdn_conf_remap.config
```
```
$ cat /etc/trafficserver/cdn_conf_remap.config
CONFIG proxy.config.url_remap.pristine_host_hdr INT 1
```

# SeeAlso
- https://docs.trafficserver.apache.org/en/latest/admin-guide/plugins/conf_remap.en.html
