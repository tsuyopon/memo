# 概要
traffic_ctlコマンドは様々なことができます。
サブコマンドがいくつか存在していますが、--debugオプションで確認することができます。
```
$ sudo /opt/trafficserver-7.1.x_log/bin/traffic_ctl --debug
Usage: traffic_ctl [OPTIONS] CMD [ARGS ...]

Subcommands:
    alarm           Manipulate alarms
    cluster         Stop, restart and examine the cluster
    config          Manipulate configuration records
    metric          Manipulate performance metrics
    server          Stop, restart and examine the server
    storage         Manipulate cache storage
    plugin          Interact with plugins

Options:
  switch__________________type__default___description
      --debug             on    true      Enable debugging output
  -h, --help                              Print usage information
  -V, --version                           Print version string
      --run-root                          using TS_RUNROOT as sandbox
```

例えば、上記でconfigのオプションがわからなければその先を指定して、hオプションを指定すると中を確認できます。
```
$ sudo /opt/trafficserver-7.1.x_log/bin/traffic_ctl config -h
Usage: traffic_ctl config CMD [ARGS ...]

Subcommands:
    defaults        Show default information configuration values
    describe        Show detailed information about configuration values
    diff            Show non-default configuration values
    get             Get one or more configuration values
    match           Get configuration matching a regular expression
    reload          Request a configuration reload
    set             Set a configuration value
    status          Check the configuration status
```

また、さらにその先も同様です。以下はgetの場合のヘルプを表示しています。
```
$ sudo /opt/trafficserver-7.1.x_log/bin/traffic_ctl config get -h
Usage: traffic_ctl config get [OPTIONS] RECORD [RECORD ...]

Options:
  switch__________________type__default___description
      --records           on    false     Emit output in records.config format
```


# 詳細
## configサブコマンド

### 設定に関するデフォルト値、現在設定、データ型等の各種情報を表示する
```
$ /opt/trafficserver-7.1.x/bin/traffic_ctl config describe proxy.config.http.enable_http_info
Name            : proxy.config.http.enable_http_info
Current Value   : 1
Default Value   : 0
Record Type     : standard config
Data Type       : INT
Access Control  : default
Update Type     : dynamic, no restart
Update Status   : 0x0
Source          : administratively set
Syntax Check    : none
Version         : 0
Order           : 404
Raw Stat Block  : 0
```

### 正規表現にマッチする設定値を取得する
```
$ sudo /opt/trafficserver-7.1.x_log/bin/traffic_ctl config match "proxy.config.http.keep*"
proxy.config.http.keep_alive_no_activity_timeout_in: 120
proxy.config.http.keep_alive_no_activity_timeout_out: 120
proxy.config.http.keep_alive_enabled_in: 1
proxy.config.http.keep_alive_enabled_out: 1
proxy.config.http.keep_alive_post_out: 1
proxy.config.http.keepalive_internal_vc: 0
```

### 設定値を取得する
```
$ /opt/trafficserver-7.1.x/bin/traffic_ctl config get --records proxy.config.alarm_email
CONFIG proxy.config.alarm_email STRING nobody
```

### 設定値を変更する
設定値によって再起動が必要なものと、必要でないものにわかれる。

次の出力の場合には再起動は不要で変更される。
```
$ sudo /opt/trafficserver-7.1.x_log/bin/traffic_ctl config set proxy.config.http.insert_response_via_str 2
set proxy.config.http.insert_response_via_str, please wait 10 seconds for traffic server to sync configuration, restart is not required
```

次の出力の場合には設定反映には再起動が必要となります。
```
$ sudo /opt/trafficserver-7.1.x_log/bin/traffic_ctl config set proxy.config.http.server_ports 80
set proxy.config.http.server_ports, restart required
```

### 設定を再読込する
```
$ sudo /opt/trafficserver-7.1.x/bin/traffic_ctl config reload
```

### 設定の前回読み込み時刻を表示する
```
$ sudo /opt/trafficserver-7.1.x_log/bin/traffic_ctl config status
Apache Traffic Server - traffic_server - 7.1.3 - (build # 010302 on Jan  3 2018 at 02:25:35)
Started at Fri Jan 19 06:53:33 2018
Last reconfiguration at Fri Jan 19 06:28:52 2018
Configuration is current
```

### デフォルトではない設定値を取得する
```
$ /opt/trafficserver-7.1.x_log/bin/traffic_ctl config diff
proxy.config.http.server_ports has changed
	Current Value   : 80
	Default Value   : 8080 8080:ipv6
proxy.config.http.insert_request_via_str has changed
	Current Value   : 4
	Default Value   : 1
proxy.config.http.insert_response_via_str has changed
	Current Value   : 2
	Default Value   : 0
proxy.config.http.negative_caching_enabled has changed
	Current Value   : 1
	Default Value   : 0
proxy.config.http.negative_caching_lifetime has changed
	Current Value   : 10
	Default Value   : 1800
proxy.config.http.cache.required_headers has changed
	Current Value   : 0
	Default Value   : 2
proxy.config.diags.debug.enabled has changed
	Current Value   : 1
	Default Value   : 0
proxy.config.diags.debug.tags has changed
	Current Value   : http.*|cache.*|dns.*
	Default Value   : http.*|dns.*
proxy.config.http_ui_enabled has changed
	Current Value   : 3
	Default Value   : 0
proxy.config.http.enable_http_info has changed
	Current Value   : 1
	Default Value   : 0
proxy.config.http.cache.max_stale_age has changed
	Current Value   : 30
	Default Value   : 604800
```

## metricサブコマンド

### 特定のメトリクス値を取得する
```
$ sudo /opt/trafficserver-7.1.x_log/bin/traffic_ctl metric get proxy.process.http.total_client_connections_ipv4
proxy.process.http.total_client_connections_ipv4 111
```

### 正規表現を指定してマッチしたメトリクスを表示したい
```
$ sudo /opt/trafficserver-7.1.x_log/bin/traffic_ctl metric match "proxy.process.http.total_*"
proxy.process.http.total_incoming_connections 102
proxy.process.http.total_client_connections 102
proxy.process.http.total_client_connections_ipv4 102
proxy.process.http.total_client_connections_ipv6 0
proxy.process.http.total_server_connections 102
proxy.process.http.total_parent_proxy_connections 0
proxy.process.http.total_parent_retries 0
proxy.process.http.total_parent_switches 0
proxy.process.http.total_parent_retries_exhausted 0
proxy.process.http.total_parent_marked_down_count 0
proxy.process.http.total_transactions_time 0
proxy.process.http.total_x_redirect_count 0
```

## serverサブコマンド

### traffic_managerのstop, status確認, startを行なう
stopやstartによってtraffic_managerを制御することができるようになります。
```
$ sudo /opt/trafficserver-7.1.x_log/bin/traffic_ctl server stop
$ sudo /opt/trafficserver-7.1.x_log/bin/traffic_ctl server status
Proxy -- off
$ ps auxww | grep -i traffic
root       552  0.0  0.3 130844  3792 ?        Ssl  06:28   0:00 /opt/trafficserver-7.1.x_log/bin/traffic_cop
nobody     554  0.1  1.2 443840 12520 ?        Sl   06:28   0:02 /opt/trafficserver-7.1.x_log/bin/traffic_manager --bind_stdout /opt/trafficserver-7.1.x_log/var/log/trafficserver/traffic.out --bind_stderr /opt/trafficserver-7.1.x_log/var/log/trafficserver/traffic.out
```

startするとtraffic_managerが起動していることが確認できます。
```
$ sudo /opt/trafficserver-7.1.x_log/bin/traffic_ctl server start
$ ps auxww | grep -i traffic
root       552  0.0  0.3 130844  3792 ?        Ssl  06:28   0:00 /opt/trafficserver-7.1.x_log/bin/traffic_cop
nobody     554  0.1  1.2 443600 12500 ?        Sl   06:28   0:02 /opt/trafficserver-7.1.x_log/bin/traffic_manager --bind_stdout /opt/trafficserver-7.1.x_log/var/log/trafficserver/traffic.out --bind_stderr /opt/trafficserver-7.1.x_log/var/log/trafficserver/traffic.out
nobody     896  2.2  3.9 381452 39840 ?        Sl   06:53   0:00 /opt/trafficserver-7.1.x_log/bin/traffic_server --bind_stdout /opt/trafficserver-7.1.x_log/var/log/trafficserver/traffic.out --bind_stderr /opt/trafficserver-7.1.x_log/var/log/trafficserver/traffic.out -M --httpport 80:fd=17
$ sudo /opt/trafficserver-7.1.x_log/bin/traffic_ctl server status
Proxy -- on
```


## pluginサブコマンド

### プラグインのタグにメッセージを送信する
```
$ sudo /opt/trafficserver-7.1.x_log/bin/traffic_ctl plugin msg testtag hoge
```

# TODO
以下のサブコマンドが現時点では使い方がよくわからなかったのでまとめていない。metricsは一部よく使い方がわからないのがあるのでまた必要な時にまとめる
- alarmサブコマンド
- clusterサブコマンド
- metricsサブコマンド
- storageサブコマンド

# 参考
- https://docs.trafficserver.apache.org/ja/latest/appendices/command-line/traffic_ctl.en.html
