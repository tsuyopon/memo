# 概要
traffic_xxx関連のツールについて
- traffic_logcat
- traffic_layout

# 詳細

### ログをわかりやすい形式で出力する

traffic_logcatの後にログを与えると全てのログをわかりやすい形式で出力します。
```
$ traffic_logcat /opt/trafficserver/var/log/trafficserver/squid.blog  
(snip)
1516311075.109 2 127.0.0.1 TCP_REFRESH_MISS/404 466 GET http://127.0.0.1:8080/admin/v1/combo?filepath1&dir1:filepath2&filepath3 - DIRECT/127.0.0.1 text/html
```

tailのようなことを行いたければfオプションを付与します。
```
$ traffic_logcat -f /opt/trafficserver/var/log/trafficserver/squid.blog  
1516311075.109 2 127.0.0.1 TCP_REFRESH_MISS/404 466 GET http://127.0.0.1:8080/admin/v1/combo?filepath1&dir1:filepath2&filepath3 - DIRECT/127.0.0.1 text/html
```

### インストールされたファイルレイアウトを確認する
```
$ traffic_layout 
PREFIX: /opt/trafficserver-7.1.x_log
BINDIR: /opt/trafficserver-7.1.x_log/bin
SYSCONFDIR: /opt/trafficserver-7.1.x_log/etc/trafficserver
LIBDIR: /opt/trafficserver-7.1.x_log/lib
LOGDIR: /opt/trafficserver-7.1.x_log/var/log/trafficserver
RUNTIMEDIR: /opt/trafficserver-7.1.x_log/var/trafficserver
PLUGINDIR: /opt/trafficserver-7.1.x_log/libexec/trafficserver
INCLUDEDIR: /opt/trafficserver-7.1.x_log/include
SNAPSHOTDIR: /opt/trafficserver-7.1.x_log/etc/trafficserver/snapshots
records.config: /opt/trafficserver-7.1.x_log/etc/trafficserver/records.config
remap.config: /opt/trafficserver-7.1.x_log/etc/trafficserver/remap.config
plugin.config: /opt/trafficserver-7.1.x_log/etc/trafficserver/plugin.config
ssl_multicert.config: /opt/trafficserver-7.1.x_log/etc/trafficserver/ssl_multicert.config
storage.config: /opt/trafficserver-7.1.x_log/etc/trafficserver/storage.config
hosting.config: /opt/trafficserver-7.1.x_log/etc/trafficserver/hosting.config
volume.config: /opt/trafficserver-7.1.x_log/etc/trafficserver/volume.config
ip_allow.config: /opt/trafficserver-7.1.x_log/etc/trafficserver/ip_allow.config
```

次のようにjオプションを付与するとJSON形式で出力することができます。
```
$ traffic_layout -j
```

### ビルド時のdefineを確認する
```
$ traffic_layout -f
#define BUILD_MACHINE "localhost.localdomain"
#define BUILD_PERSON "tsuyoshi"
#define BUILD_GROUP "tsuyoshi"
#define BUILD_NUMBER ""
#define TS_HAS_LIBZ 0
#define TS_HAS_LZMA 0
#define TS_HAS_JEMALLOC 0
#define TS_HAS_TCMALLOC 0
#define TS_HAS_IN6_IS_ADDR_UNSPECIFIED 1
#define TS_HAS_BACKTRACE 1
#define TS_HAS_PROFILER 0
#define TS_USE_FAST_SDK 0
#define TS_USE_DIAGS 1
#define TS_USE_EPOLL 1
#define TS_USE_KQUEUE 0
#define TS_USE_PORT 0
#define TS_USE_POSIX_CAP 0
#define TS_USE_TPROXY 0
#define TS_HAS_SO_MARK 1
#define TS_HAS_IP_TOS 1
#define TS_USE_HWLOC 0
#define TS_USE_TLS_NPN 1
#define TS_USE_TLS_ALPN 1
#define TS_USE_TLS_SNI 1
#define TS_USE_CERT_CB 1
#define TS_USE_SET_RBIO 0
#define TS_USE_TLS_ECKEY 1
#define TS_USE_LINUX_NATIVE_AIO 0
#define TS_HAS_SO_PEERCRED 1
#define TS_USE_REMOTE_UNWINDING 0
#define GETHOSTBYNAME_R_GLIBC2 1
#define SIZEOF_VOID_POINTER 8
#define TS_IP_TRANSPARENT 0
#define TS_HAS_128BIT_CAS 1
#define TS_HAS_TESTS 1
#define TS_HAS_WCCP 0
#define TS_MAX_THREADS_IN_EACH_THREAD_TYPE 3072
#define TS_MAX_NUMBER_EVENT_THREADS 4096
#define TS_MAX_HOST_NAME_LEN 256
#define TS_MAX_API_STATS 512
#define SPLIT_DNS 1
#define HTTP_CACHE 1
#define TS_PKGSYSUSER "nobody"
#define TS_PKGSYSGROUP "nobody"
```

