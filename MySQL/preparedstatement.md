# 概要
プリペアドステートメントについて

# 詳細

### SQLコマンドからプリペアドステートメントを実行する

```
mysql> SET @mysql = 'SELECT * FROM actor WHERE first_name=? AND last_name=?';
Query OK, 0 rows affected (0.00 sec)

mysql> PREPARE mystmt FROM @mysql;
Query OK, 0 rows affected (0.00 sec)
Statement prepared

mysql> SET @first = 'PENELOPE';
Query OK, 0 rows affected (0.00 sec)

mysql> SET @last = 'GUINESS';
Query OK, 0 rows affected (0.00 sec)

mysql> EXECUTE mystmt USING @first, @last;
+----------+------------+-----------+---------------------+
| actor_id | first_name | last_name | last_update         |
+----------+------------+-----------+---------------------+
|        1 | PENELOPE   | GUINESS   | 2006-02-15 04:34:33 |
+----------+------------+-----------+---------------------+
1 row in set (0.01 sec)

mysql> DEALLOCATE PREPARE mystmt;
Query OK, 0 rows affected (0.00 sec)
```

### prepared statementでハテナの数を少なくしたい
FIND_IN_SETを使うとINを使わずに対象を抽出できる。
何がいいかというと、prepared statementでハテナの数を1つに減らすことができるという利点がある。
```
mysql> SELECT * from actor where FIND_IN_SET(actor_id, '1,3,4') ;
+----------+------------+-----------+---------------------+
| actor_id | first_name | last_name | last_update         |
+----------+------------+-----------+---------------------+
|        1 | PENELOPE   | GUINESS   | 2006-02-15 04:34:33 |
|        3 | ED         | CHASE     | 2006-02-15 04:34:33 |
|        4 | JENNIFER   | DAVIS     | 2006-02-15 04:34:33 |
+----------+------------+-----------+---------------------+
3 rows in set (0.00 sec)
```

### デバッグ方法について
prepared statementはMySQLサーバ側で解釈しているので、tcpdumpで表示できないし、stack overflowにもこれといった回答はない。
- https://stackoverflow.com/questions/30094724/php-mysql-prepared-statements-debugging

PDOの場合にはPDOStatement::debugDumpParamsというメソッドが存在する
- https://www.php.net/manual/ja/pdostatement.debugdumpparams.php

なお、MySQLサーバ側でgeneral_logをonにすればリクエストがあったSQLを見ることは確認することは可能であると思われる。


# 参考URL
- https://dev.mysql.com/doc/refman/5.6/ja/sql-syntax-prepared-statements.html
