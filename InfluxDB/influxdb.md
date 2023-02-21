# 概要
InfluxDBのコマンドラインやWebAPIの使い方メモです
このコマンドはInfluxDB1.7.3で試した際のメモです。

# コマンドライン
### influxdbのCLIから使えるコマンド
ヘルプでどのようなコマンドが利用できるか確認できます。
```
> help
Usage:
        connect <host:port>   connects to another node specified by host:port
        auth                  prompts for username and password
        pretty                toggles pretty print for the json format
        chunked               turns on chunked responses from server
        chunk size <size>     sets the size of the chunked responses.  Set to 0 to reset to the default chunked size
        use <db_name>         sets current database
        format <format>       specifies the format of the server responses: json, csv, or column
        precision <format>    specifies the format of the timestamp: rfc3339, h, m, s, ms, u or ns
        consistency <level>   sets write consistency level: any, one, quorum, or all
        history               displays command history
        settings              outputs the current settings for the shell
        clear                 clears settings such as database or retention policy.  run 'clear' for help
        exit/quit/ctrl+d      quits the influx shell

        show databases        show database names
        show series           show series information
        show measurements     show measurement information
        show tag keys         show tag key information
        show field keys       show field key information

        A full list of influxql commands can be found at:
        https://docs.influxdata.com/influxdb/latest/query_language/spec/
```

### InfluxDBに接続する・終了する(influxコマンド 1系)
下記コマンドで接続する
```
$ influx
```

RFC3339準拠の日付表示を行う
```
$ influx -precision rfc3339
```

なお、終了するにはEXITを使ってください。
```
> EXIT
```

### InfluxDBに接続する(influx 2系以降)
influxコマンドが2系以上の場合には少し接続方法が異なります
```
$ influx v1 shell --host http://localhost:8086
```

### influxコマンドに指定できる引数
コマンドラインに指定できる引数は下記を参照のこと
- https://docs.influxdata.com/influxdb/v1.7/tools/influx-cli/

以下、抜粋
```
-version     Display the version and exit
-host        HTTP address of InfluxDB (default: http://localhost:8086)
-port        Port to connect to
-socket      Unix socket to connect to
-database    Database to connect to the server
-password    Password to connect to the server. Leaving blank will prompt for password.
-username    Username to connect to the server
-ssl         Use https for requests
-unsafessl   Set this when connecting to the cluster using https
-execute     Execute command and quit
-type        Specify the query language for executing commands or when invoking the REPL.
-format      Specify the format of the server responses: json, csv, or column
-precision   Specify the format of the timestamp: rfc3339, h, m, s, ms, u or ns
-consistency Set write consistency level: any, one, quorum, or all
-pretty      Turns on pretty print for JSON format
-import      Import a previous database export from file
-pps         Points per second the import will allow. The default is 0 and will not throttle importing.
-path        Path to file to import
-compressed  Set to true if the import file is compressed
```

### データベース一覧を表示する
```
> SHOW DATABASES
name: databases
name
----
cache_stats
daily_stats
deliveryservice_stats
_internal
```

### データベースを作成する
```
> CREATE DATABASE mydb1
> SHOW DATABASES
name: databases
name
----
cache_stats
daily_stats
deliveryservice_stats
_internal
mydb1
```

### 利用するデータベースを切り替える
```
> USE mydb1
Using database mydb1
```

### measurements(RDBのテーブルに相当)を表示する
データベースを切り替えたら下記でどのようなデータがあるかを確認できます。
```
> show measurements
name: measurements
name
----
kbps
kbps.cg.1min
kbps.ds.1min
status_4xx
status_5xx
tps_2xx
tps_2xx.ds.1min
tps_3xx
tps_3xx.ds.1min
(snip)
```

### データを登録する
insertでmeasurementsに登録できます。
以下でcpuやcpu2を作成していますが、特段にmeasurementsの定義をしていませんが表示されていることが確認できます。
同一名称のmeasurementsに登録することもできます。
```
> INSERT cpu,host=serverA,region=us_west value=0.64
> show measurements
name: measurements
name
----
cpu
> INSERT cpu2,host=serverA,region=us_west value=0.64
> show measurements
name: measurements
name
----
cpu
cpu2
```

以下の書式で設定を行なっています。
```
INSERT <measurement>[,<tag-key>=<tag-value>...] <field-key>=<field-value>[,<field2-key>=<field2-value>...] [unix-nano-timestamp]
```

今回のinsertの例では設定値は下記のようになっています。
- measurement: cpuやcpu2
- 任意であるtag-keyとtag-value: 「host=serverA,region=us_west」
- 必須であるfield-keyとfield-value: 「value=0.64」

### measurementsに設定されたタグ情報を表示する
データベース毎にこの値は変わります。
```
> show tag keys
name: cpu
tagKey
------
host
region

name: cpu2
tagKey
------
host
region
```

### タグ名を指定して、そのタグに紐づく値にはどのような値が入っているのかを確認する
以下の例では先で表示された「region」をtagのキーとして指定している例です。
```
> show tag values with key = "region"
name: cpu
key    value
---    -----
region jp
region us_west

name: cpu2
key    value
---    -----
region us_west
```

### データを参照する

下記の書式となっています。
```
SELECT <field名> FROM <measurement名>
```

以下のようにinsertした場合
```
INSERT cpu,host=serverA,region=us_west value=0.64
```

fieldには「value」を指定して下記のように取得します。filed名はカンマ区切りで複数指定することも可能です。
```
> SELECT value FROM cpu
name: cpu
time                         value
----                         -----
2015-08-23T08:38:50Z         0.64
2023-02-18T22:35:10.6888221Z 0.64
```

### 複数のmeasurementsを指定する
```
> SELECT value FROM cpu,cpu2
name: cpu
time                         value
----                         -----
2015-08-23T08:38:50Z         0.64
2023-02-18T22:35:10.6888221Z 0.64

name: cpu2
time                         value
----                         -----
2023-02-18T22:35:20.5033051Z 0.64
```

### 表示時にfield値の加工をする
以下の例では100倍している例です。0.64が100倍されて64になっていることがわかります。
```
> SELECT value*100 FROM cpu
name: cpu
time                         value
----                         -----
2015-08-23T08:38:50Z         64
2023-02-18T22:35:10.6888221Z 64
```

### 件数を絞って参照する
```
> SELECT value FROM cpu LIMIT 1
name: cpu
time                 value
----                 -----
2015-08-23T08:38:50Z 0.64
```

### シリーズを参照する
シリーズとは「リテンションポリシー」、「measurement」、「タグのセット(複数含む)」が同一のデータ群です。
以下の値をみるとイメージしやすいかもしれません。
```
> show series
key
---
cpu,host=serverA,region=jp
cpu,host=serverA,region=us_west
cpu2,host=serverA,region=us_west
```

### measurementsを削除する
以下は「meas」のmeasurementsを作成して、すぐに削除している例です。
```
> insert meas,key=1 value=2
> show measurements
name: measurements
name
----
cpu
cpu2
meas
> drop measurement meas
> show measurements
name: measurements
name
----
cpu
cpu2
```


### 保持期限を表示する
リテンションポリシーといいます。influxDBがどの程度の期間を保持(DURATION)するかを規定するものです。データのコピーを幾つ保存するかもREPLICATIONで指定することができます。
データベース毎に異なります。以下ではデータベース毎に切り替えてその時の表示の違いを確認しています。
```
> show retention policies
name    duration shardGroupDuration replicaN default
----    -------- ------------------ -------- -------
autogen 0s       168h0m0s           1        true
> use daily_stats
Using database daily_stats
> show retention policies
name       duration shardGroupDuration replicaN default
----       -------- ------------------ -------- -------
autogen    0s       168h0m0s           1        false
indefinite 0s       168h0m0s           1        true
> use daily_stats
Using database daily_stats
> show retention policies
name       duration shardGroupDuration replicaN default
----       -------- ------------------ -------- -------
autogen    0s       168h0m0s           1        false
indefinite 0s       168h0m0s           1        true
> use deliveryservice_stats
Using database deliveryservice_stats
> show retention policies
name       duration shardGroupDuration replicaN default
----       -------- ------------------ -------- -------
autogen    0s       168h0m0s           1        false
daily      26h0m0s  1h0m0s             1        true
monthly    720h0m0s 24h0m0s            1        false
indefinite 0s       168h0m0s           1        false
```


# WebAPIの利用

### データベースを表示する
```
$ curl -G http://localhost:8086/query --data-urlencode "q=show databases"
{"results":[{"statement_id":0,"series":[{"name":"databases","columns":["name"],"values":[["cache_stats"],["daily_stats"],["deliveryservice_stats"],["_internal"],["mydb1"]]}]}]}
```

出力を整形して表示したい場合には「?pretty=true」を付与すればよい。
```
$  curl -G 'http://localhost:8086/query?pretty=true' --data-urlencode "q=show databases"
{
    "results": [
        {
            "statement_id": 0,
            "series": [
                {
                    "name": "databases",
                    "columns": [
                        "name"
                    ],
                    "values": [
                        [
                            "cache_stats"
                        ],
                        [
                            "daily_stats"
                        ],
                        [
                            "deliveryservice_stats"
                        ],
                        [
                            "_internal"
                        ],
                        [
                            "mydb1"
                        ]
                    ]
                }
            ]
        }
    ]
}
```

### データの抽出にWHEREを使う
上記の例とあまり大差ありませんが、一応WHERE句を使ったリクエスト例を記載しておきます。
```
$ curl -G 'http://localhost:8086/query?pretty=true' --data-urlencode "db=mydb1" --data-urlencode "q=SELECT value FROM cpu WHERE region='jp'"
{
    "results": [
        {
            "statement_id": 0,
            "series": [
                {
                    "name": "cpu",
                    "columns": [
                        "time",
                        "value"
                    ],
                    "values": [
                        [
                            "2015-08-23T08:38:50Z",
                            0.64
                        ]
                    ]
                }
            ]
        }
    ]
}
```

### データを入れてみる
```
[~/git/memo]$ curl -G 'http://localhost:8086/query' --data-urlencode "db=mydb1" --data-urlencode "q=SELECT value FROM cpu"
{"results":[{"statement_id":0,"series":[{"name":"cpu","columns":["time","value"],"values":[["2023-02-18T22:35:10.6888221Z",0.64]]}]}]}
[~/git/memo]$ curl -i -XPOST 'http://localhost:8086/write?db=mydb1&precision=s' --data-binary 'cpu,host=serverA,region=jp value=0.64 1440319130'
HTTP/1.1 204 No Content
Content-Type: application/json
Request-Id: 0c73ab51-afde-11ed-9227-0242ac1f000a
X-Influxdb-Build: OSS
X-Influxdb-Version: 1.7.3
X-Request-Id: 0c73ab51-afde-11ed-9227-0242ac1f000a
Date: Sat, 18 Feb 2023 22:46:14 GMT

[~/git/memo]$ curl -G 'http://localhost:8086/query' --data-urlencode "db=mydb1" --data-urlencode "q=SELECT value FROM cpu"
{"results":[{"statement_id":0,"series":[{"name":"cpu","columns":["time","value"],"values":[["2015-08-23T08:38:50Z",0.64],["2023-02-18T22:35:10.6888221Z",0.64]]}]}]}
```
