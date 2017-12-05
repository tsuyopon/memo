# 概要
stats関連についてまとめます

# 詳細

### 様々な特型情報を出力する
```
$ traffic_logstats -s
                        Totals (all Origins combined)

Request Result                         Count    Percent       Bytes    Percent
------------------------------------------------------------------------------
Cache hit                                  0      0.00%      0.00KB      0.00%
Cache hit IMS                              0      0.00%      0.00KB      0.00%
Cache hit refresh                          0      0.00%      0.00KB      0.00%
Cache hit other                            0      0.00%      0.00KB      0.00%
Cache hit total                            0      0.00%      0.00KB      0.00%
(snip)

Client aborted                             0      0.00%      0.00KB      0.00%
Connect failed                             1    100.00%      0.44KB    100.00%
Invalid request                            0      0.00%      0.00KB      0.00%
Unknown error(99)                          0      0.00%      0.00KB      0.00%
Other errors                               0      0.00%      0.00KB      0.00%
Errors total                               1    100.00%      0.44KB    100.00%
..............................................................................
Total requests                             1    100.00%      0.44KB    100.00%


HTTP return codes                      Count    Percent       Bytes    Percent
------------------------------------------------------------------------------
100 Continue                               0      0.00%      0.00KB      0.00%
200 OK                                     0      0.00%      0.00KB      0.00%
201 Created                                0      0.00%      0.00KB      0.00%
(snip)

Origin hierarchies                     Count    Percent       Bytes    Percent
------------------------------------------------------------------------------
NONE                                       1    100.00%      0.44KB    100.00%
DIRECT                                     0      0.00%      0.00KB      0.00%
SIBLING                                    0      0.00%      0.00KB      0.00%
(snip)

HTTP Methods                           Count    Percent       Bytes    Percent
------------------------------------------------------------------------------
OPTIONS                                    0      0.00%      0.00KB      0.00%
GET                                        1    100.00%      0.44KB    100.00%
HEAD                                       0      0.00%      0.00KB      0.00%
(snip)

URL Schemes                            Count    Percent       Bytes    Percent
------------------------------------------------------------------------------
HTTP (port 80)                             1    100.00%      0.44KB    100.00%
HTTPS (port 443)                           0      0.00%      0.00KB      0.00%
none                                       0      0.00%      0.00KB      0.00%
other                                      0      0.00%      0.00KB      0.00%

Content Types                          Count    Percent       Bytes    Percent
------------------------------------------------------------------------------
text/javascript                            0      0.00%      0.00KB      0.00%
text/html                                  1    100.00%      0.44KB    100.00%
text/xml                                   0      0.00%      0.00KB      0.00%
(snip)

Elapsed time stats          Min          Max              Avg    Std Deviation
------------------------------------------------------------------------------
Cache hit                     0            0            0.000            0.000
Cache hit IMS                 0            0            0.000            0.000
Cache hit refresh             0            0            0.000            0.000
Cache hit other               0            0            0.000            0.000
Cache hit total               0            0            0.000            0.000
Cache miss                    0            0            0.000            0.000
Cache miss IMS                0            0            0.000            0.000
Cache miss refresh            0            0            0.000            0.000
Cache miss other              0            0            0.000            0.000
Cache miss total              0            0            0.000            0.000
______________________________________________________________________________
```


### json形式で取得する
```
$ traffic_logstats -j
{ "total": {
    "hit.direct" : { "req": "0", "req_pct": "0.00", "bytes": "0", "bytes_pct": "0.00" },
    "hit.ims" : { "req": "0", "req_pct": "0.00", "bytes": "0", "bytes_pct": "0.00" },
    "hit.refresh" : { "req": "0", "req_pct": "0.00", "bytes": "0", "bytes_pct": "0.00" },
    "hit.other" : { "req": "0", "req_pct": "0.00", "bytes": "0", "bytes_pct": "0.00" },
    "hit.total" : { "req": "0", "req_pct": "0.00", "bytes": "0", "bytes_pct": "0.00" },
    "miss.direct" : { "req": "0", "req_pct": "0.00", "bytes": "0", "bytes_pct": "0.00" },
    "miss.ims" : { "req": "0", "req_pct": "0.00", "bytes": "0", "bytes_pct": "0.00" },
    "miss.refresh" : { "req": "0", "req_pct": "0.00", "bytes": "0", "bytes_pct": "0.00" },
(snip)
```

### オリジンサーバ関連の統計情報を取得する
- https://docs.trafficserver.apache.org/en/latest/admin-guide/monitoring/statistics/core/origin.en.html

### TLS関連の統計情報を取得する
- https://docs.trafficserver.apache.org/en/latest/admin-guide/monitoring/statistics/core/ssl-cipher.en.html
