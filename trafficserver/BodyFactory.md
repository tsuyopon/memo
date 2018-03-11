# 概要
デフォルトでエラー時には表示されるHTMLテンプレートなどが格納される仕組みがあります。

# 詳細

### body_factoryのディレクトリについて
デフォルトは次のように定義されています。
```
PREFIX/body_factory/default
```

ただし、次の設定によって変更することができます。
```
proxy.config.body_factory.template_sets_dir
```

### body_factoryに含まれるテンプレートや対応するHTTPステータスコードについて
```
/etc/trafficserver/body_factory
/etc/trafficserver/body_factory/default
/etc/trafficserver/body_factory/default/README
/etc/trafficserver/body_factory/default/request#syntax_error
/etc/trafficserver/body_factory/default/timeout#activity
/etc/trafficserver/body_factory/default/access#proxy_auth_required
/etc/trafficserver/body_factory/default/connect#dns_failed
/etc/trafficserver/body_factory/default/request#no_content_length
/etc/trafficserver/body_factory/default/timeout#inactivity
/etc/trafficserver/body_factory/default/connect#hangup
/etc/trafficserver/body_factory/default/access#ssl_forbidden
/etc/trafficserver/body_factory/default/default
/etc/trafficserver/body_factory/default/response#bad_version
/etc/trafficserver/body_factory/default/request#no_host
/etc/trafficserver/body_factory/default/access#denied
/etc/trafficserver/body_factory/default/redirect#moved_temporarily
/etc/trafficserver/body_factory/default/access#redirect_url
/etc/trafficserver/body_factory/default/.body_factory_info
/etc/trafficserver/body_factory/default/urlrouting#no_mapping
/etc/trafficserver/body_factory/default/request#scheme_unsupported
/etc/trafficserver/body_factory/default/transcoding#unsupported
/etc/trafficserver/body_factory/default/request#cycle_detected
/etc/trafficserver/body_factory/default/congestion#retryAfter
/etc/trafficserver/body_factory/default/cache#not_in_cache
/etc/trafficserver/body_factory/default/cache#read_error
/etc/trafficserver/body_factory/default/connect#failed_connect
/etc/trafficserver/body_factory/default/interception#no_host
/etc/trafficserver/body_factory/default/response#bad_response
```

どのHTTPステータスコードの場合に何のテンプレートが返却されているのかについては以下を参考のこと
- https://docs.trafficserver.apache.org/en/latest/admin-guide/monitoring/error-messages.en.html#html-messages-sent-to-clients

### trafficserverで利用されるHTTPステータスコード
- https://docs.trafficserver.apache.org/en/latest/appendices/http-status-codes.en.html#appendix-http-status-codes
