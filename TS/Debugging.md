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
debug-tag-nameの箇所には「http_tproxy|dns|hostdb」、「http*」などとして複数指定することもできます。
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
$ traffic_server -T"my-plugin"
```

## デバッグ関数

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

