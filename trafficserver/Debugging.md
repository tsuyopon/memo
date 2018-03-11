# 概要
デバッグ方法についてまとめます。

## gdbを動かす
起動時と稼働時双方でgdbを動かしたい場合の方法を記述しておきます。
- 起動時などからgdbで確認したい場合には、 traffic_serverコマンドを直接動かす。
- 稼働中のtrafficserverを確認する場合には、traffic_serverプロセスのPIDを確認してgdb -pを利用する。

## デバッグタグを指定する

デバッグタグを指定するには２つの方法があります。
- (1) recoreds.configに設定値を入れる
- (2) traffic_serverコマンド起動時にTオプションで指定する

### (1) 
(1)を有効にするためには次の２つの設定を確認します。これでtraffic.outログに出力されます。
```
CONFIG proxy.config.diags.debug.enabled INT 1
CONFIG proxy.config.diags.debug.tags STRING debug-tag-name
```

debug-tag-nameには次のようなタグが入ります。これ以外にも各プラグイン用のタグなどもあるので、プラグインでつまったらソースコードを見てタグを取得しましょう。
debug-tag-nameの箇所には「http_tproxy|dns|hostdb」、「http.*|dns.*」などとして複数指定することもできます。
```
http_hdrs - traces all incoming and outgoing HTTP headers.
http_trans - traces actions in an HTTP transaction.
http_seq - traces the sequence of the HTTP state machine.
http_tproxy - transparency related HTTP events
dns - DNS operations
hostdb - Host name lookup
iocore_net - Socket and low level IO (very voluminous)
socket - socket operations
ssl - SSL related events
cache - Cache operations (many subtags, examine the output to narrow the tag set)
cache_update - Cache updates including writes
cache_read - Cache read events.
dir_probe - Cache searches.
sdk - gives some warning concerning API usage.
```

trafficserverのレポジトリ直下で次のコマンドを打てばタグを見つけることができるとのこと
- https://cwiki.apache.org/confluence/display/TS/FAQ#FAQ-debugtags
```
$ grep -orh 'Debug("[^"]*' * | sort | uniq | sed 's/Debug("//'
```

ソースコードには次のようにタグが埋め込まれています。
```
TSDebug ("my-plugin", "Starting my-plugin at %d\n", the_time);
```

### (2)
traffic_server起動時にTオプションでタグを指定する方法があります。これはコマンドライン上でちょっとした確認でデバッグログを標準出力させたい場合などに利用すると便利です。
```
$ sudo traffic_server -T"my-plugin"
```

Tオプションは--debug_tagsと等価です。次のようにして正規表現を指定することも可能です。
```
$ sudo traffic_server -T http.*
```

## コマンドラインからデバッグログを出力するように設定を上書きする
コマンドのみでrecords.configが読み込んだ設定を上書きすることができます　。タグは適宜修正してください。
```
$ sudo traffic_line -s proxy.config.diags.debug.enabled -v 1
$ sudo traffic_line -s proxy.config.diags.debug.tags -v http      # http.*|ssl.*  などのように正規表現で複数を記述することもできます。
```

ソースコードの行も表示するには次の設定も有効にします。
proxy.config.diags.show_locationはソースコード上の位置をログに出力します。値が1ならばDebug()メッセージのみ(これがデフォルト)、2ならばすべてのメッセージが対象となります
```
$ sudo traffic_line -s proxy.config.diags.show_location -v 1
```

## コアファイルを取得する
- records.config
```
CONFIG proxy.config.core_limit INT -1
```
- カーネルパラメータを変更する
```
$ sysctl -w kernel.core_pattern = /tmp/%e.core.%p
```

コアからデバッグするときには次のようにします。
```
$ sudo gdb traffic_server  <corefile>
```

## TIPS

### デバッグ時にスレッド数
traffic_serverにはスレッド数を減らすオプションが存在します。
```
$ traffic_server -h
[TrafficServer] using root directory '/usr'
Usage: traffic_server [--SWITCH [ARG]]
  switch__________________type__default___description
  -l, --lock_memory       int   0         Lock process in memory (must be root)
  -n, --net_threads       int   1         Number of Net Threads
  -Z, --cluster_threads   int   1         Number of Cluster Threads
  -U, --udp_threads       int   1         Number of UDP Threads
  -a, --accept_thread     tog   false     Use an Accept Thread
  -b, --accept_till_done  tog   true      Accept Till Done
  -p, --httpport          str   (null)    Port descriptor for HTTP Accept
  -P, --cluster_port      int   0         Cluster Port Number
  -o, --dprintf_level     int   0         Debug output level
  -V, --version           tog   false     Print Version String
  -T, --debug_tags        str   (null)    Vertical-bar-separated Debug Tags
  -B, --action_tags       str   (null)    Vertical-bar-separated Behavior Tags
  -i, --interval          int   0         Statistics Interval
  -M, --remote_management tog   false     Remote Management
  -d, --management_dir    str   /etc/tr.. Management Directory
  -C, --command           str   (null)    Maintenance Command to Execute
  -k, --clear_hostdb      on    false     Clear HostDB on Startup
  -K, --clear_cache       on    false     Clear Cache on Startup
  -v, --vingid            str   (null)    Vingid Flag
  -c, --read_core         str   (null)    Read Core file
  - , --accept_mss        int   0         MSS for client connections
  -t, --poll_timeout      int   10        poll timeout in milliseconds
  -h, --help                              HELP!
```

スレッド数がありすぎてgdbでデバッグしにくいときなどは次のようにして、スレッド数を減らすことができます。
n, Z, U, aなどでスレッド数を指定できるようです。
```
(gdb) run -n 1
```

### メモリリークを検知する
```
$ sudo traffic_line -s proxy.config.res_track_memory -v 1
```

### slow logを取得する
```
$ sudo traffic_line -s proxy.config.http.slow.log.threshold -v 100
```

### デバッグ関数
```
TSDebug() prints out a formatted statement if you are running Traffic Server in debug mode.
TSIsDebugTagSet() checks to see if a debug tag is set. If the debug tag is set, then Traffic Server prints out all debug statements associated with the tag.
TSError() prints error messages to Traffic Server’s error log
TSAssert() enables the use of assertion in a plugin.
TSReleaseAssert() enables the use of assertion in a plugin.
```

# 参考URL
- trafficserver公式ドキュメント(Debugging)
  - https://trafficserver.readthedocs.io/ja/latest/developer-guide/debugging/index.en.html
- Diagnostics&Debugging(PDF)
  - https://cwiki.apache.org/confluence/download/attachments/56066455/ATS%20Summit-%20Diagnostics%20%26%20Debugging-2.pdf?version=1&modificationDate=1447863198000&api=v2
- https://docs.google.com/presentation/d/1Qokjj5VuB3HvIPEi00ZTp_mJrhrIxraZPgIs4CMyoxM/edit?pli=1#slide=id.g430e3c44f_325
