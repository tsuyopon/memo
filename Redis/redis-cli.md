# 概要
redis-cliコマンドを使うと対話的にredisとの接続操作を行うことができます。

redisがサポートするコマンド一覧を参照するには以下のページが参考になります。
- https://redis.io/commands

# 詳細

## コマンドラインオプション

### redis-cliから操作をする
redis-cliへの最後の引数にコマンドを与えることで、redis-cliへの命令を実行を与えることができます。
```
$ redis-cli -h localhost GET mykey
"myvalue"
$ redis-cli -h localhost SET mykey myvalu_from_cmd
OK
$ redis-cli -h localhost GET mykey
"myvalu_from_cmd"
```

リダイレクトで実行させるサンプル
```
$ echo "SET hoge bar" | redis-cli
OK
```

SET, GETを一括で処理させるサンプル
```
$ echo -e "SET hoge bar \r\n GET hoge" | redis-cli
OK
"bar"
```

### 正規表現で検索する
以下の例ではmykeyで始まるキーを全て探索しています。
```
$ redis-cli --scan --pattern "mykey*"
mykey3
mykey2
mykey
```

### 指定したkeyの値を定期的に確認する
以下の例ではmykeyのkeyの値を2秒間隔で3回確認して出力しています。
```
$ redis-cli -r 3 -i 2 get mykey
"myvalu_from_cmd"
"myvalu_from_cmd"
"myvalu_from_cmd"
```


## 使い方

### 基本操作
```
$ redis-cli 
127.0.0.1:6379> SET mykey myvalue
OK
127.0.0.1:6379> GET mykey
"myvalue"
127.0.0.1:6379> EXISTS mykey
(integer) 1
127.0.0.1:6379> EXISTS mykey2
(integer) 0
```


### PUB/SUBを試してみる
以下の例ではredis-cliで「PSUBSCRIBE」で正規表現の特定のチャンネルを指定しています。
```
$ redis-cli
127.0.0.1:6379> PSUBSCRIBE hoge.*                    // このコマンド以降は他でPUBLISHされたチャンネル内容が出力される。
Reading messages... (press Ctrl-C to quit)
1) "psubscribe"
2) "hoge.*"
3) (integer) 1
```

別のターミナルなどから次の様にPUBLISHを発行します。
```
$ redis-cli 
127.0.0.1:6379> PUBLISH test mytest                  // これはhoge.で始まっていないチャンネルなので補足されない(戻り値も0となっている)
(integer) 0
127.0.0.1:6379> PUBLISH hoge.test mytest             // これはhoge.で始まっているチャンネルなので補足される
(integer) 1
127.0.0.1:6379> PUBLISH hoge.fuga myfuga             // これはhoge.で始まっているチャンネルなので補足される
(integer) 1
```

先ほどPSUBSCRIBEしたときのターミナルは次の様に上記で受け取ったチャンネル内容hoge.testとhoge.fugaの値を表示しています。
```
$ redis-cli
127.0.0.1:6379> PSUBSCRIBE hoge.*                    // このコマンド以降は他でPUBLISHされたチャンネル内容が出力される。
Reading messages... (press Ctrl-C to quit)
1) "psubscribe"
2) "hoge.*"
3) (integer) 1
1) "pmessage"
2) "hoge.*"
3) "hoge.test"
4) "mytest"
1) "pmessage"
2) "hoge.*"
3) "hoge.fuga"
4) "myfuga"
```

- 参考資料
  - https://redis.io/topics/rediscli

### 登録されたデータの全削除を実施する
FLUSHALLコマンドを使うことでredisに登録された全データを削除することができます。
```
127.0.0.1:6379> SET hoge fuga
127.0.0.1:6379> FLUSHALL
OK
127.0.0.1:6379> GET hoge
(nil)
```

### 実行されたコマンドを監視する
MONITORコマンドを実行します。
```
127.0.0.1:6379> MONITOR
OK
```

redisに対して操作された内容がコンソールに出力され続けます。tail -fで出力されるredisモニタツールのような感じです。
```
127.0.0.1:6379> MONITOR
OK
1574709810.887287 [0 127.0.0.1:41626] "COMMAND"
1574709820.124245 [0 127.0.0.1:41626] "flushall"
1574709826.644897 [0 127.0.0.1:41626] "SET" "hoge" "fuga"
```

### 統計情報を出力する

```
$ redis-cli --stat
------- data ------ --------------------- load -------------------- - child -
keys       mem      clients blocked requests            connections          
1          793.48K  1       0       29 (+0)             12          
1          793.48K  1       0       30 (+1)             12          
1          793.48K  1       0       31 (+1)             12          
1          793.48K  1       0       32 (+1)             12          
```

### redisが生きているかどうかを確認する
```
127.0.0.1:6379> ping
PONG
```

# 参考URL
- redis公式ドキュメント
  - https://redis.io/documentation
- rediscli
  - https://redis.io/topics/rediscli
- redisドキュメント日本語訳
  - http://redis.shibu.jp/
- redisのコマンド一覧
  - https://redis.io/commands
