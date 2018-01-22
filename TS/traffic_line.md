# 概要
traffic_lineコマンドについて

このコマンドは近いうちにdeprecatedが予定されている。移行先はtraffic_ctlコマンドとなります。
- https://issues.apache.org/jira/browse/TS-3368

# 詳細

### 統計情報を取得する
```
$ sudo traffic_line -r proxy.node.cache.percent_free
1.000000
```

どのような値を取得できるのかについては「Core Statistics」配下のドキュメントを参考にすること
- https://docs.trafficserver.apache.org/ja/latest/admin-guide/monitoring/statistics/core-statistics.en.html

次のように取れない場合もあるので、他の値も確認してみること
```
$ sudo traffic_line -r proxy.node.cahce_hit_ratio
traffic_line: [12] Generic Fail message (ie. CoreAPI call).
```

### 設定を変更する
```
$ traffic_line -s proxy.config.alarm_email -v root@downtown.jp
```

次の設定反映のxオプションも合わせて必要です。

### 設定を変更したものを反映する
```
$ sudo traffic_line -x
```
メモリのサイズなどの変更の場合にはrestartが必要な場合もあるので注意が必要です。　

### ヘルプを表示する
```
$ traffic_line -h
Usage: traffic_line [--SWITCH [ARG]]
  switch__________________type__default___description
  -q, --query_deadhosts   on    false     Query congested sites
  -r, --read_var          str   (null)    Read Variable
  -s, --set_var           str   (null)    Set Variable (requires -v option)
  -v, --value             str   (null)    Set Value (used with -s option)
  -h, --help                              Help
  -x, --reread_config     on    false     Reread Config Files
  -M, --restart_cluster   on    false     Restart traffic_manager (cluster wide)
  -L, --restart_local     on    false     Restart traffic_manager (local node)
  -S, --shutdown          on    false     Shutdown traffic_server (local node)
  -U, --startup           on    false     Start traffic_server (local node)
  -B, --bounce_cluster    on    false     Bounce traffic_server (cluster wide)
  -b, --bounce_local      on    false     Bounce local traffic_server
  -C, --clear_cluster     on    false     Clear Statistics (cluster wide)
  -c, --clear_node        on    false     Clear Statistics (local node)
  -V, --version           tog   false     Print Version Id
```

# TODO
いろいろオプションがあるので、時間があればもっと使ってみるといいかも

