# 概要
暗号化通信のスピードを測定する

# 詳細

### openssl s_timeコマンドの出力結果の意味について
たとえば、下記の出力と仮定する。
```
8102 connections in 12.65s; 640.47 connections/user sec, bytes read 0
8102 connections in 31 real seconds, 0 bytes read per connection
```

- 12.65はCPUとしてのuser時間の合計値で、8102回のTLS接続が完了したので1秒あたり640.47connection/usersとなる。
- システム全体(system+user)としては31秒(1秒は丸め時間)かかったことになる

- 参考
  - https://mta.openssl.org/pipermail/openssl-users/2016-June/003951.html

### wwwオプションを指定した場合と指定しない場合などで顕著に差が出る場合
HTTPのユーザー時間にかかっている可能性がある
- 参考
  - https://groups.google.com/forum/#!topic/mailing.openssl.users/KIbj7n89cJ4

### テストを実施する
- 新規ハンドシェイク、再ハンドシェイク双方でテストを実施する
  - 後で登場するnewやreuseオプションを付与しない場合には、新規接続と再ハンドシェイク両方のテストを実施する
```
$  /opt/openssl-1.0.2m/bin/openssl s_time -connect localhost:443 
No CIPHER specified
Collecting connection statistics for 30 seconds
**********************************************************************(以下略)

520 connections in 5.35s; 97.20 connections/user sec, bytes read 0
520 connections in 31 real seconds, 0 bytes read per connection


Now timing with session id reuse.
starting
rrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrr(以下略)

11044 connections in 6.34s; 1741.96 connections/user sec, bytes read 0
11044 connections in 31 real seconds, 0 bytes read per connection
```

- 新規ハンドシェイクの場合だけテストする
```
$ openssl s_time -connect localhost:443 -new
No CIPHER specified
Collecting connection statistics for 30 seconds
**********************************************************************

521 connections in 5.32s; 97.93 connections/user sec, bytes read 0
521 connections in 31 real seconds, 0 bytes read per connection
```

- 再ハンドシェイクの場合だけテストする
```
$ openssl s_time -connect localhost:443  -reuse
No CIPHER specified


Now timing with session id reuse.
starting
rrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrr

9213 connections in 5.81s; 1585.71 connections/user sec, bytes read 0
9213 connections in 31 real seconds, 0 bytes read per connection
```

TODO: No CIPHERということはCiphe使っていない?

### HTTP接続でのテストを実施する
- 新規ハンドシェイク、再ハンドシェイク双方でテストを実施する
```
$ openssl s_time -connect localhost:443  -www /test.html 
No CIPHER specified
Collecting connection statistics for 30 seconds
**********************************************************************

641 connections in 0.82s; 781.71 connections/user sec, bytes read 175634
641 connections in 31 real seconds, 274 bytes read per connection


Now timing with session id reuse.
starting
rrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrr

712 connections in 0.21s; 3390.48 connections/user sec, bytes read 195088
712 connections in 31 real seconds, 274 bytes read per connection
```
- 新規ハンドシェイク
```
$ openssl s_time -connect localhost:443  -www /test.html -new
No CIPHER specified
Collecting connection statistics for 30 seconds
**********************************************************************

603 connections in 0.88s; 685.23 connections/user sec, bytes read 165222
603 connections in 31 real seconds, 274 bytes read per connection
```
- 再ハンドシェイクでテストをする
```
$ openssl s_time -connect localhost:443  -www /test.html -reuse
No CIPHER specified


Now timing with session id reuse.
starting
rrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrr

689 connections in 0.20s; 3445.00 connections/user sec, bytes read 188786
689 connections in 31 real seconds, 274 bytes read per connection
```

### テストする時間を変更する
何も指定しない30秒から変更したい場合にはtimeオプションで指定することができます。
``` 
$ openssl s_time -connect localhost:443  -www /test.html -new -time 10
No CIPHER specified
Collecting connection statistics for 10 seconds
**********************************************************************

222 connections in 0.31s; 716.13 connections/user sec, bytes read 60828
222 connections in 11 real seconds, 274 bytes read per connection
```

### ヘルプを確認する
```
$  /opt/openssl-1.0.2m/bin/openssl s_time -connect localhost:443  help
unknown option help
usage: s_time <args>

-connect host:port - host:port to connect to (default is localhost:4433)
-nbio         - Run with non-blocking IO
-ssl2         - Just use SSLv2
-ssl3         - Just use SSLv3
-bugs         - Turn on SSL bug compatibility
-new          - Just time new connections
-reuse        - Just time connection reuse
-www page     - Retrieve 'page' from the site
-time arg     - max number of seconds to collect data, default 30
-verify arg   - turn on peer certificate verification, arg == depth
-cert arg     - certificate file to use, PEM format assumed
-key arg      - RSA file to use, PEM format assumed, key is in cert file
                file if not specified by this option
-CApath arg   - PEM format directory of CA's
-CAfile arg   - PEM format file of CA's
-cipher       - preferred cipher to use, play with 'openssl ciphers'
```

