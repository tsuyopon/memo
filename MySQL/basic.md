# 概要
mysqlの情報取得やシェル操作などの基本的な情報についてまとめる

# 詳細

### 入力中に間違えてしまった場合
入力途中で間違ったことに気づいた場合には無理やり改行を入れていましたが「\c」ではキャンセルすることが可能です。
```
mysql> SELECT HOGE  \c    # "\cで途中で間違えた場合にキャンセルすることが可能です。
mysql>
```

### mysqlに再接続を行う
connectコマンドで
```
mysql> connect
Connection id:    44
Current database: mysql

mysql> connect
Connection id:    45
Current database: mysql
```
### サーバの情報を表示したい
```
mysql> \s
--------------
mysql  Ver 14.14 Distrib 5.6.40, for Linux (x86_64) using  EditLine wrapper

Connection id:		38
Current database:	
Current user:		root@localhost
SSL:			Not in use
Current pager:		stdout
Using outfile:		''
Using delimiter:	;
Server version:		5.6.40 MySQL Community Server (GPL)
Protocol version:	10
Connection:		Localhost via UNIX socket
Server characterset:	latin1
Db     characterset:	latin1
Client characterset:	utf8
Conn.  characterset:	utf8
UNIX socket:		/var/lib/mysql/mysql.sock
Uptime:			13 days 20 hours 2 min 58 sec

Threads: 1  Questions: 2079  Slow queries: 0  Opens: 139  Flush tables: 3  Open tables: 46  Queries per second avg: 0.001
--------------
```


### 実行中のプロセスリストを表示して、不要なプロセスを削除する
```
mysql> SHOW PROCESSLIST;
+----+------+-----------+------+---------+------+-------+------------------+
| Id | User | Host      | db   | Command | Time | State | Info             |
+----+------+-----------+------+---------+------+-------+------------------+
| 34 | root | localhost | NULL | Query   |    0 | init  | SHOW PROCESSLIST |
+----+------+-----------+------+---------+------+-------+------------------+
1 row in set (0.00 sec)
```

削除するにはkillコマンドの後にIdを指定します。
```
mysql> KILL 34
```
