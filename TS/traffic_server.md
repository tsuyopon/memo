# 概要
traffic_serverコマンドについて

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
