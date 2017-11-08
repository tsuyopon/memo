# 概要
logについてまとめていきます。

# 詳細

### squid.blog(アクセスログに相当)を確認する
```
$ traffic_logcat /var/log/trafficserver/squid.blog 
1508887909.037 0 127.0.0.1 ERR_CONNECT_FAIL/404 449 GET http:/// - NONE/- text/html -
1508888166.331 0 127.0.0.1 ERR_CONNECT_FAIL/404 449 GET http:/// - NONE/- text/html -
```

### squid.blogのアクセス時刻を綺麗に変換する
```
$ traffic_logcat /var/log/trafficserver/squid.blog | perl -pe 's/\d+\.\d+/localtime $&/e'
Wed Oct 25 08:31:49 2017 0 127.0.0.1 ERR_CONNECT_FAIL/404 449 GET http:/// - NONE/- text/html -
Wed Oct 25 08:36:06 2017 0 127.0.0.1 ERR_CONNECT_FAIL/404 449 GET http:/// - NONE/- text/html -
```

### イベントロギングフォーマットについて
どのようなフィールドをログに落とすのかについては以下を参照のこと
- https://docs.trafficserver.apache.org/ja/5.3.x/admin/event-logging-formats.en.html
