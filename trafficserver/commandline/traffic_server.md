# 概要
traffic_serverコマンドについて

# 詳細

### ヘルプを見る
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

### Cオプションのヘルプを表示する
```
$ sudo /opt/trafficserver-7.1.x/bin/traffic_server -Chelp
traffic_server: using root directory '/opt/trafficserver-7.1.x'
HELP

           list  List cache configuration
          check  Check the cache (do not make any changes)
          clear  Clear the entire cache
    clear_cache  Clear the document cache
   clear_hostdb  Clear the hostdb cache
  verify_config  Verify the config
           help  Obtain a short description of a command (e.g. 'help clear')
```


### 設定ファイルに問題がないことを確認する
```
$ sudo /opt/trafficserver-7.1.x/bin/traffic_server -Cverify_config
traffic_server: using root directory '/opt/trafficserver-7.1.x'
NOTE: VERIFY

INFO:Successfully loaded remap.config

INFO: Successfully loaded records.config

INFO: Successfully loaded plugin.config

INFO: Successfully loaded ssl multicert.config

INFO: Successfully initialized SSL client context
```


### cache.dbの確認を行う
```
$ sudo /opt/trafficserver-7.1.x/bin/traffic_server -Ccheck
traffic_server: using root directory '/opt/trafficserver-7.1.x'
CHECK

Stripe '[/opt/trafficserver-7.1.x/var/trafficserver/cache.db 16384:32766]'
  Directory Bytes: 83660
  Segments:  1
  Buckets per segment:   8366
  Entries:   33464
  - Segment-0 | Entries: used=0 stale=0 free=25098 disk-bytes=0 Buckets: used=0 empty=8366 max=0 avg=0.00 dups=0
  - Stripe | Entries: in-use=0 stale=0 free=25098 Buckets: empty=8366 max=0 avg=0.00
    Chain lengths:   0=8366  1=0  2=0  3=0  4=0  5=0  6=0  7=0  8=0  9=0  10=0  11=0  12=0  13=0  14=0  15=0  16>=0
    Total Size:      268419072
    Bytes in Use:    0 [0.00%]
    Objects:         0
    Average Size:    0
    Average Frags:   0.00
    Write Position:  0
    Wrap Count:      0
    Phase:           false
    Sync Serial:     0
    Write Serial:    0
    Create Time:     Tue May 29 11:17:48 2018

  Fragment size demographics
      512[ 0:0]:000000     1024[ 1:0]:000000     1536[ 2:0]:000000     2048[ 3:0]:000000     2560[ 4:0]:000000     3072[ 5:0]:000000     3584[ 6:0]:000000     4096[ 7:0]:000000

(snip)
CHECK succeeded
```


### hostdbの中を表示する
自分が試してみた限りでは正しく出力されてなさそうだった。やり方が間違えているのかも。
```
$ sudo /opt/trafficserver-7.1.x/bin/traffic_server -Clist
traffic_server: using root directory '/opt/trafficserver-7.1.x'
LIST

Host Database size:	0
/opt/trafficserver-7.1.x/var/trafficserver 268435456
```
