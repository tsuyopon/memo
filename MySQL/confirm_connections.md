# 概要
MySQLの接続関連の確認コマンドについて


# 詳細

### 現在接続しているスレッド数を表示する
```
mysql> show status like 'Threads_connected';
+-------------------+-------+
| Variable_name     | Value |
+-------------------+-------+
| Threads_connected | 2     |
+-------------------+-------+
1 row in set (0.00 sec)
```


### プロセスリスト（処理中の接続）を表示する
```
mysql>  show processlist;
+----+-----------------+--------------------+------+---------+---------+------------------------+------------------+
| Id | User            | Host               | db   | Command | Time    | State                  | Info             |
+----+-----------------+--------------------+------+---------+---------+------------------------+------------------+
|  5 | event_scheduler | localhost          | NULL | Daemon  | 1562448 | Waiting on empty queue | NULL             |
| 67 | test            | 192.168.3.19:35390 | NULL | Sleep   |      60 |                        | NULL             |
| 68 | test            | 192.168.3.19:35392 | NULL | Query   |       0 | init                   | show processlist |
+----+-----------------+--------------------+------+---------+---------+------------------------+------------------+
3 rows in set (0.00 sec)
```

### 不要なコネクションをkillする
「show processlist」で表示されるIdを指定してプロセスをkillできる
```
mysql> kill 69;
Query OK, 0 rows affected (0.00 sec)
```

### 60秒以上経過しているコネクションを抽出する
```
mysql> SELECT * FROM information_schema.PROCESSLIST WHERE time >= 60 and user != 'rdsadmin';
+----+-----------------+-----------+------+---------+---------+------------------------+------+
| ID | USER            | HOST      | DB   | COMMAND | TIME    | STATE                  | INFO |
+----+-----------------+-----------+------+---------+---------+------------------------+------+
|  5 | event_scheduler | localhost | NULL | Daemon  | 1562594 | Waiting on empty queue | NULL |
+----+-----------------+-----------+------+---------+---------+------------------------+------+
1 row in set (0.02 sec)
```

### プライマリ/レプリカの判別
プライマリはOFF、レプリカはONとなる
```
mysql> SHOW GLOBAL VARIABLES LIKE 'innodb_read_only';
+------------------+-------+
| Variable_name    | Value |
+------------------+-------+
| innodb_read_only | OFF   |
+------------------+-------+
1 row in set (0.00 sec)
```
