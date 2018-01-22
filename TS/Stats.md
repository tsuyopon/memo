# 概要
traffic_logstatsコマンドについてまとめていきます

# 詳細

### ヘルプ
```
$ traffic_logstats  -h
Usage: traffic_logstats [--SWITCH [ARG]]
  switch__________________type__default___description
  -f, --log_file          str             Specific logfile to parse
  -o, --origin_list       str             Only show stats for listed Origins
  -O, --origin_file       str             File listing Origins to show
  -M, --max_orgins        int   0         Max number of Origins to show
  -u, --urls              int   0         Produce JSON stats for URLs, argument is LRU size
  -U, --show_urls         int   0         Only show max this number of URLs
  -A, --as_object         tog   false     Produce URL stats as a JSON object instead of array
  -C, --concise           tog   false     Eliminate metrics that can be inferred from other values
  -i, --incremental       tog   false     Incremental log parsing
  -S, --statetag          str             Name of the state file to use
  -t, --tail              int   0         Parse the last <sec> seconds of log
  -s, --summary           tog   false     Only produce the summary
  -j, --json              tog   false     Produce JSON formatted output
  -c, --cgi               tog   false     Produce HTTP headers suitable as a CGI
  -m, --min_hits          i64   0         Minimum total hits for an Origin
  -a, --max_age           int   0         Max age for log entries to be considered
  -l, --line_len          int   78        Output line length
  -T, --debug_tags        str             Colon-Separated Debug Tags
  -r, --report_per_user   tog   false     Report stats per user instead of host
  -h, --help                              Print usage information
  -V, --version                           Print version string
      --run-root                          using TS_RUNROOT as sandbox
```

### 様々な特型情報を出力する

```
$ traffic_logstats /opt/trafficserver/var/log/trafficserver/squid.blog   
                               Traffic summary

Origin Server                               Hits         Misses         Errors
------------------------------------------------------------------------------
127.0.0.1:8080                                34            116              2
==============================================================================



                        Totals (all Origins combined)

Request Result                         Count    Percent       Bytes    Percent
------------------------------------------------------------------------------
Cache hit                                  8      5.06%      3.28KB      2.24%
Cache hit RAM                             26     16.46%      9.40KB      6.41%
Cache hit IMS                              0      0.00%      0.00KB      0.00%
Cache hit refresh                          0      0.00%      0.00KB      0.00%
Cache hit other                            0      0.00%      0.00KB      0.00%
Cache hit total                           34     21.52%     12.68KB      8.65%

Cache miss                                92     58.23%    120.06KB     81.85%
Cache miss IMS                             0      0.00%      0.00KB      0.00%
Cache miss refresh                        26     16.46%     11.69KB      7.97%
Cache miss other                           0      0.00%      0.00KB      0.00%
Cache miss total                         118     74.68%    131.75KB     89.81%

Client aborted                             2      1.27%      0.00KB      0.00%
Connect failed                             3      1.90%      1.76KB      1.20%
Invalid request                            0      0.00%      0.00KB      0.00%
Unknown error(99)                          0      0.00%      0.00KB      0.00%
Other errors                               0      0.00%      0.00KB      0.00%
Errors total                               5      3.16%      1.76KB      1.20%
..............................................................................
Total requests                           158    100.00%    146.69KB    100.00%


HTTP return codes                      Count    Percent       Bytes    Percent
------------------------------------------------------------------------------
100 Continue                               0      0.00%      0.00KB      0.00%
200 OK                                    86     54.43%    111.03KB     75.69%
201 Created                                0      0.00%      0.00KB      0.00%
202 Accepted                               0      0.00%      0.00KB      0.00%
203 Non-Authoritative Info                 0      0.00%      0.00KB      0.00%
204 No content                             0      0.00%      0.00KB      0.00%
205 Reset Content                          0      0.00%      0.00KB      0.00%
206 Partial content                        0      0.00%      0.00KB      0.00%
2xx Total                                 86     54.43%    111.03KB     75.69%

300 Multiple Choices                       0      0.00%      0.00KB      0.00%
301 Moved permanently                      0      0.00%      0.00KB      0.00%
302 Found                                  0      0.00%      0.00KB      0.00%
303 See Other                              0      0.00%      0.00KB      0.00%
304 Not modified                           0      0.00%      0.00KB      0.00%
305 Use Proxy                              0      0.00%      0.00KB      0.00%
307 Temporary Redirect                     0      0.00%      0.00KB      0.00%
3xx Total                                  0      0.00%      0.00KB      0.00%

400 Bad request                            0      0.00%      0.00KB      0.00%
401 Unauthorized                           0      0.00%      0.00KB      0.00%
402 Payment Required                       0      0.00%      0.00KB      0.00%
403 Forbidden                              1      0.63%      5.12KB      3.49%
404 Not found                             66     41.77%     28.78KB     19.62%
405 Method Not Allowed                     0      0.00%      0.00KB      0.00%
406 Not Acceptable                         0      0.00%      0.00KB      0.00%
407 Proxy Auth Required                    0      0.00%      0.00KB      0.00%
408 Request Timeout                        0      0.00%      0.00KB      0.00%
409 Conflict                               0      0.00%      0.00KB      0.00%
410 Gone                                   0      0.00%      0.00KB      0.00%
411 Length Required                        0      0.00%      0.00KB      0.00%
412 Precondition Failed                    0      0.00%      0.00KB      0.00%
413 Request Entity Too Large               0      0.00%      0.00KB      0.00%
414 Request-URI Too Long                   0      0.00%      0.00KB      0.00%
415 Unsupported Media Type                 0      0.00%      0.00KB      0.00%
416 Req Range Not Satisfiable              0      0.00%      0.00KB      0.00%
417 Expectation Failed                     0      0.00%      0.00KB      0.00%
4xx Total                                 67     42.41%     33.90KB     23.11%

500 Internal Server Error                  0      0.00%      0.00KB      0.00%
501 Not implemented                        0      0.00%      0.00KB      0.00%
502 Bad gateway                            3      1.90%      1.76KB      1.20%
503 Service unavailable                    0      0.00%      0.00KB      0.00%
504 Gateway Timeout                        0      0.00%      0.00KB      0.00%
505 HTTP Ver. Not Supported                0      0.00%      0.00KB      0.00%
5xx Total                                  3      1.90%      1.76KB      1.20%

000 Unknown                                2      1.27%      0.00KB      0.00%


Origin hierarchies                     Count    Percent       Bytes    Percent
------------------------------------------------------------------------------
NONE                                      38     24.05%     14.94KB     10.19%
DIRECT                                   118     74.68%    131.75KB     89.81%
SIBLING                                    0      0.00%      0.00KB      0.00%
PARENT                                     0      0.00%      0.00KB      0.00%
EMPTY                                      2      1.27%      0.00KB      0.00%
invalid                                    0      0.00%      0.00KB      0.00%
other                                      0      0.00%      0.00KB      0.00%


HTTP Methods                           Count    Percent       Bytes    Percent
------------------------------------------------------------------------------
OPTIONS                                    0      0.00%      0.00KB      0.00%
GET                                      158    100.00%    146.69KB    100.00%
HEAD                                       0      0.00%      0.00KB      0.00%
POST                                       0      0.00%      0.00KB      0.00%
PUT                                        0      0.00%      0.00KB      0.00%
DELETE                                     0      0.00%      0.00KB      0.00%
TRACE                                      0      0.00%      0.00KB      0.00%
CONNECT                                    0      0.00%      0.00KB      0.00%
PURGE                                      0      0.00%      0.00KB      0.00%
none (-)                                   0      0.00%      0.00KB      0.00%
other                                      0      0.00%      0.00KB      0.00%


URL Schemes                            Count    Percent       Bytes    Percent
------------------------------------------------------------------------------
HTTP (port 80)                           158    100.00%    146.69KB    100.00%
HTTPS (port 443)                           0      0.00%      0.00KB      0.00%
none                                       0      0.00%      0.00KB      0.00%
other                                      0      0.00%      0.00KB      0.00%


Protocols                              Count    Percent       Bytes    Percent
------------------------------------------------------------------------------
IPv4                                     158    100.00%    146.69KB    100.00%
IPv6                                       0      0.00%      0.00KB      0.00%


Content Types                          Count    Percent       Bytes    Percent
------------------------------------------------------------------------------
text/javascript                            2      1.27%     83.98KB     57.25%
text/css                                   0      0.00%      0.00KB      0.00%
text/html                                154     97.47%     62.71KB     42.75%
text/xml                                   0      0.00%      0.00KB      0.00%
text/plain                                 0      0.00%      0.00KB      0.00%
text/ other                                0      0.00%      0.00KB      0.00%
text/ total                              156     98.73%    146.69KB    100.00%

image/jpeg                                 0      0.00%      0.00KB      0.00%
image/gif                                  0      0.00%      0.00KB      0.00%
image/png                                  0      0.00%      0.00KB      0.00%
image/bmp                                  0      0.00%      0.00KB      0.00%
image/ other                               0      0.00%      0.00KB      0.00%
image/ total                               0      0.00%      0.00KB      0.00%

audio/x-wav                                0      0.00%      0.00KB      0.00%
audio/x-mpeg                               0      0.00%      0.00KB      0.00%
audio/ other                               0      0.00%      0.00KB      0.00%
audio/ total                               0      0.00%      0.00KB      0.00%

application/x-shockwave                    0      0.00%      0.00KB      0.00%
application/[x-]javascript                 0      0.00%      0.00KB      0.00%
application/x-quicktime                    0      0.00%      0.00KB      0.00%
application/zip                            0      0.00%      0.00KB      0.00%
application/rss+xml                        0      0.00%      0.00KB      0.00%
application/rss+atom                       0      0.00%      0.00KB      0.00%
application/ other                         0      0.00%      0.00KB      0.00%
application/ total                         0      0.00%      0.00KB      0.00%

none                                       2      1.27%      0.00KB      0.00%
other                                      0      0.00%      0.00KB      0.00%


Elapsed time stats          Min          Max              Avg    Std Deviation
------------------------------------------------------------------------------
Cache hit                     2        6,598           825.10          2181.95
Cache hit RAM             3,431      164,002         14839.04         41538.47
Cache hit IMS                 0            0             0.00             0.00
Cache hit refresh             0            0             0.00             0.00
Cache hit other               0            0             0.00             0.00
Cache hit total               2      164,002         11541.63         36822.75
Cache miss                    1      303,352         11710.48         51434.00
Cache miss IMS                0            0             0.00             0.00
Cache miss refresh            2      209,451         42947.96         66280.48
Cache miss other              0            0             0.00             0.00
Cache miss total              1      303,352         18593.31         56552.29

______________________________________________________________________________



                                127.0.0.1:8080

Request Result                         Count    Percent       Bytes    Percent
------------------------------------------------------------------------------
Cache hit                                  8      5.26%      3.28KB      5.43%
Cache hit RAM                             26     17.11%      9.40KB     15.55%
Cache hit IMS                              0      0.00%      0.00KB      0.00%
Cache hit refresh                          0      0.00%      0.00KB      0.00%
Cache hit other                            0      0.00%      0.00KB      0.00%
Cache hit total                           34     22.37%     12.68KB     20.98%

Cache miss                                90     59.21%     36.08KB     59.69%
Cache miss IMS                             0      0.00%      0.00KB      0.00%
Cache miss refresh                        26     17.11%     11.69KB     19.33%
Cache miss other                           0      0.00%      0.00KB      0.00%
Cache miss total                         116     76.32%     47.77KB     79.02%

Client aborted                             2      1.32%      0.00KB      0.00%
Connect failed                             0      0.00%      0.00KB      0.00%
Invalid request                            0      0.00%      0.00KB      0.00%
Unknown error(99)                          0      0.00%      0.00KB      0.00%
Other errors                               0      0.00%      0.00KB      0.00%
Errors total                               2      1.32%      0.00KB      0.00%
..............................................................................
Total requests                           152    100.00%     60.45KB    100.00%


HTTP return codes                      Count    Percent       Bytes    Percent
------------------------------------------------------------------------------
100 Continue                               0      0.00%      0.00KB      0.00%
200 OK                                    84     55.26%     27.06KB     44.76%
201 Created                                0      0.00%      0.00KB      0.00%
202 Accepted                               0      0.00%      0.00KB      0.00%
203 Non-Authoritative Info                 0      0.00%      0.00KB      0.00%
204 No content                             0      0.00%      0.00KB      0.00%
205 Reset Content                          0      0.00%      0.00KB      0.00%
206 Partial content                        0      0.00%      0.00KB      0.00%
2xx Total                                 84     55.26%     27.06KB     44.76%

300 Multiple Choices                       0      0.00%      0.00KB      0.00%
301 Moved permanently                      0      0.00%      0.00KB      0.00%
302 Found                                  0      0.00%      0.00KB      0.00%
303 See Other                              0      0.00%      0.00KB      0.00%
304 Not modified                           0      0.00%      0.00KB      0.00%
305 Use Proxy                              0      0.00%      0.00KB      0.00%
307 Temporary Redirect                     0      0.00%      0.00KB      0.00%
3xx Total                                  0      0.00%      0.00KB      0.00%

400 Bad request                            0      0.00%      0.00KB      0.00%
401 Unauthorized                           0      0.00%      0.00KB      0.00%
402 Payment Required                       0      0.00%      0.00KB      0.00%
403 Forbidden                              1      0.66%      5.12KB      8.47%
404 Not found                             65     42.76%     28.28KB     46.77%
405 Method Not Allowed                     0      0.00%      0.00KB      0.00%
406 Not Acceptable                         0      0.00%      0.00KB      0.00%
407 Proxy Auth Required                    0      0.00%      0.00KB      0.00%
408 Request Timeout                        0      0.00%      0.00KB      0.00%
409 Conflict                               0      0.00%      0.00KB      0.00%
410 Gone                                   0      0.00%      0.00KB      0.00%
411 Length Required                        0      0.00%      0.00KB      0.00%
412 Precondition Failed                    0      0.00%      0.00KB      0.00%
413 Request Entity Too Large               0      0.00%      0.00KB      0.00%
414 Request-URI Too Long                   0      0.00%      0.00KB      0.00%
415 Unsupported Media Type                 0      0.00%      0.00KB      0.00%
416 Req Range Not Satisfiable              0      0.00%      0.00KB      0.00%
417 Expectation Failed                     0      0.00%      0.00KB      0.00%
4xx Total                                 66     43.42%     33.40KB     55.24%

500 Internal Server Error                  0      0.00%      0.00KB      0.00%
501 Not implemented                        0      0.00%      0.00KB      0.00%
502 Bad gateway                            0      0.00%      0.00KB      0.00%
503 Service unavailable                    0      0.00%      0.00KB      0.00%
504 Gateway Timeout                        0      0.00%      0.00KB      0.00%
505 HTTP Ver. Not Supported                0      0.00%      0.00KB      0.00%
5xx Total                                  0      0.00%      0.00KB      0.00%

000 Unknown                                2      1.32%      0.00KB      0.00%


Origin hierarchies                     Count    Percent       Bytes    Percent
------------------------------------------------------------------------------
NONE                                      34     22.37%     12.68KB     20.98%
DIRECT                                   116     76.32%     47.77KB     79.02%
SIBLING                                    0      0.00%      0.00KB      0.00%
PARENT                                     0      0.00%      0.00KB      0.00%
EMPTY                                      2      1.32%      0.00KB      0.00%
invalid                                    0      0.00%      0.00KB      0.00%
other                                      0      0.00%      0.00KB      0.00%


HTTP Methods                           Count    Percent       Bytes    Percent
------------------------------------------------------------------------------
OPTIONS                                    0      0.00%      0.00KB      0.00%
GET                                      152    100.00%     60.45KB    100.00%
HEAD                                       0      0.00%      0.00KB      0.00%
POST                                       0      0.00%      0.00KB      0.00%
PUT                                        0      0.00%      0.00KB      0.00%
DELETE                                     0      0.00%      0.00KB      0.00%
TRACE                                      0      0.00%      0.00KB      0.00%
CONNECT                                    0      0.00%      0.00KB      0.00%
PURGE                                      0      0.00%      0.00KB      0.00%
none (-)                                   0      0.00%      0.00KB      0.00%
other                                      0      0.00%      0.00KB      0.00%


URL Schemes                            Count    Percent       Bytes    Percent
------------------------------------------------------------------------------
HTTP (port 80)                           152    100.00%     60.45KB    100.00%
HTTPS (port 443)                           0      0.00%      0.00KB      0.00%
none                                       0      0.00%      0.00KB      0.00%
other                                      0      0.00%      0.00KB      0.00%


Protocols                              Count    Percent       Bytes    Percent
------------------------------------------------------------------------------
IPv4                                     152    100.00%     60.45KB    100.00%
IPv6                                       0      0.00%      0.00KB      0.00%


Content Types                          Count    Percent       Bytes    Percent
------------------------------------------------------------------------------
text/javascript                            0      0.00%      0.00KB      0.00%
text/css                                   0      0.00%      0.00KB      0.00%
text/html                                150     98.68%     60.45KB    100.00%
text/xml                                   0      0.00%      0.00KB      0.00%
text/plain                                 0      0.00%      0.00KB      0.00%
text/ other                                0      0.00%      0.00KB      0.00%
text/ total                              150     98.68%     60.45KB    100.00%

image/jpeg                                 0      0.00%      0.00KB      0.00%
image/gif                                  0      0.00%      0.00KB      0.00%
image/png                                  0      0.00%      0.00KB      0.00%
image/bmp                                  0      0.00%      0.00KB      0.00%
image/ other                               0      0.00%      0.00KB      0.00%
image/ total                               0      0.00%      0.00KB      0.00%

audio/x-wav                                0      0.00%      0.00KB      0.00%
audio/x-mpeg                               0      0.00%      0.00KB      0.00%
audio/ other                               0      0.00%      0.00KB      0.00%
audio/ total                               0      0.00%      0.00KB      0.00%

application/x-shockwave                    0      0.00%      0.00KB      0.00%
application/[x-]javascript                 0      0.00%      0.00KB      0.00%
application/x-quicktime                    0      0.00%      0.00KB      0.00%
application/zip                            0      0.00%      0.00KB      0.00%
application/rss+xml                        0      0.00%      0.00KB      0.00%
application/rss+atom                       0      0.00%      0.00KB      0.00%
application/ other                         0      0.00%      0.00KB      0.00%
application/ total                         0      0.00%      0.00KB      0.00%

none                                       2      1.32%      0.00KB      0.00%
other                                      0      0.00%      0.00KB      0.00%


Elapsed time stats          Min          Max              Avg    Std Deviation
------------------------------------------------------------------------------
Cache hit                     2        6,598           825.10          2181.95
Cache hit RAM             3,431      164,002         14839.04         41538.47
Cache hit IMS                 0            0             0.00             0.00
Cache hit refresh             0            0             0.00             0.00
Cache hit other               0            0             0.00             0.00
Cache hit total               2      164,002         11541.63         36822.75
Cache miss                    1      303,352         11970.54         51972.42
Cache miss IMS                0            0             0.00             0.00
Cache miss refresh            2      209,451         42947.96         66280.48
Cache miss other              0            0             0.00             0.00
Cache miss total              1      303,352         18913.76         56984.59

______________________________________________________________________________

```

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
$ traffic_logstats -j /opt/trafficserver/var/log/trafficserver/squid.blog  
{ "total": {
    "hit.direct" : { "req": "8", "req_pct": "5.06", "bytes": "3363", "bytes_pct": "2.24" },
    "hit.ram" : { "req": "26", "req_pct": "16.46", "bytes": "9626", "bytes_pct": "6.41" },
    "hit.ims" : { "req": "0", "req_pct": "0.00", "bytes": "0", "bytes_pct": "0.00" },
    "hit.refresh" : { "req": "0", "req_pct": "0.00", "bytes": "0", "bytes_pct": "0.00" },
    "hit.other" : { "req": "0", "req_pct": "0.00", "bytes": "0", "bytes_pct": "0.00" },
    "hit.total" : { "req": "34", "req_pct": "21.52", "bytes": "12989", "bytes_pct": "8.65" },
    "miss.direct" : { "req": "92", "req_pct": "58.23", "bytes": "122942", "bytes_pct": "81.85" },

(snip)
```

### オリジンサーバ関連の統計情報を取得する
- https://docs.trafficserver.apache.org/en/latest/admin-guide/monitoring/statistics/core/origin.en.html

### TLS関連の統計情報を取得する
- https://docs.trafficserver.apache.org/en/latest/admin-guide/monitoring/statistics/core/ssl-cipher.en.html
