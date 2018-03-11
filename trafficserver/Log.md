# 概要
logについてまとめていきます。

# 詳細

### 各種ファイルの役割について
- traffic.out
  - Debugレベルのメッセージがこのファイルに出力されます。
  - debug tagを指定するとこのファイルにログが出力されます。
- diags.log
  - DEBUGよりも優先度が高いログメッセージがこのファイルに出力されます。
- error.log
  - 運用上のエラーメッセージはここに出力されます。
  - このメッセージはtrafficserver自体ではなく

- 参考
  - https://docs.trafficserver.apache.org/en/latest/admin-guide/monitoring/diagnostic-files.en.html

### logging.configの記述方法について
logging.configの概要について
- https://docs.trafficserver.apache.org/en/latest/admin-guide/files/logging.config.en.html

cqh, pqh, chi等の各種意味やログのフォーマットを定義するlogging.configについて記載されています。
- https://docs.trafficserver.apache.org/en/latest/admin-guide/logging/formatting.en.html

以下のページにlogging.configのサンプルが記述されています。
- https://docs.trafficserver.apache.org/en/latest/admin-guide/logging/examples.en.html

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

### TCP_HIT, TCP_MISS, TCP_REFRESH_HITなどのログに出力される意味について
- https://docs.trafficserver.apache.org/en/latest/admin-guide/logging/cache-results.en.html#cache-result-codes

### イベントロギングフォーマットについて
どのようなフィールドをログに落とすのかについては以下を参照のこと
- https://docs.trafficserver.apache.org/ja/5.3.x/admin/event-logging-formats.en.html

### ログローテートに関して

# 参考URL
- Administrator’s Guide > Monitoring
  - https://docs.trafficserver.apache.org/en/latest/admin-guide/monitoring/index.en.html
- Administrator’s Guide > Logging
  - https://docs.trafficserver.apache.org/en/latest/admin-guide/logging/index.en.html
