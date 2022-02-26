# 概要
MySQLのデバッグ方法について

# 詳細

### サーバサイドによるデバッグ方法

MySQLサーバに投げられてきたSQL文をログに出力する設定があります。

```
mysql> show variables like 'general_log%';
+------------------+---------------------------------+
| Variable_name    | Value                           |
+------------------+---------------------------------+
| general_log      | OFF                             |
| general_log_file | /var/lib/mysql/0794c3377bf9.log |
+------------------+---------------------------------+
2 rows in set (0.00 sec)
```

下記のように変更することで設定が有効になります。
```
mysql> set global general_log = on;
Query OK, 0 rows affected (0.03 sec)

mysql> show variables like 'general_log%';
+------------------+---------------------------------+
| Variable_name    | Value                           |
+------------------+---------------------------------+
| general_log      | ON                              |
| general_log_file | /var/lib/mysql/0794c3377bf9.log |
+------------------+---------------------------------+
2 rows in set (0.04 sec)
```

適当に以下のクエリを投げて
```
mysql> select 1;
```

出力されたログの中にSQL文が存在することを確認します。
```
# ls -alh /var/lib/mysql/0794c3377bf9.log 
-rw-r----- 1 mysql mysql 449 Feb 26 01:39 /var/lib/mysql/0794c3377bf9.log
# cat /var/lib/mysql/0794c3377bf9.log 
/usr/sbin/mysqld, Version: 5.7.17-0ubuntu0.16.04.1 ((Ubuntu)). started with:
Tcp port: 3306  Unix socket: /var/run/mysqld/mysqld.sock
Time                 Id Command    Argument
2022-02-26T01:39:05.514313Z	    5 Query	show variables like 'general_log%'
2022-02-26T01:39:53.349702Z	    5 Query	select 1
```

これでMySQLのデバッグが捗ります。


### クライアントサイドによるデバッグ方法(PHP)

この機能(mysqli_debug)を使うためにはMySQLクライアントライブラリのデバッグ機能を有効にしてコンパイルする必要があるようです(-DWITH_DEBUG=1)。
```
mysqli_debug("d:t:o,/tmp/client.trace");
```

- 参考
  - https://dev.mysql.com/doc/refman/8.0/ja/debugging-client.html
  - https://www.php.net/manual/ja/mysqli.debug.php




