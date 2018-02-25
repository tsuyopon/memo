# 概要
mysqladminコマンドについて

# 詳細

### mysqlサーバが起動しているかどうか確認する
mysqladmin pingによりaliveが帰ってくれば起動しています。
```
$ mysqladmin ping
mysqld is alive
```

### コマンドラインで/etc/my.cnfなどで設定したリストを表示させる
```
$ mysqladmin variables
```
出力はshow variablesと同じである。

### コマンドラインで動作しているmysqlプロセスを表示する
```
$ mysqladmin processlist -uroot -p
+----+------+-----------+----+---------+------+-------+------------------+
| Id | User | Host      | db | Command | Time | State | Info             |
+----+------+-----------+----+---------+------+-------+------------------+
| 11 | root | localhost |    | Query   | 0    |       | show processlist |
+----+------+-----------+----+---------+------+-------+------------------+
```

コマンドライン版SHOW STATUS
```
$ mysqladmin extended-status
+--------------------------+-------+
| Variable_name            | Value |
+--------------------------+-------+
| Aborted_clients          | 0     |
| Aborted_connects         | 0     |
| Bytes_received           | 2183  |
| Bytes_sent               | 28146 |
| Com_admin_commands       | 3     |
      (以下略)
```

### データベースの作成、削除
- DB作成
```
$ mysqladmin -u ユーザ名前 -p create データベース名
```
- DB削除
```
$ mysqladmin -u ユーザ名 -p drop データベース名
```

### rootのパスワード設定をコマンドラインから行う
```
# mysqladmin -u root password <パスワード>
```
