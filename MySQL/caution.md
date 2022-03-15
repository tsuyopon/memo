# 概要
MySQLを操作する上での注意点について


# 詳細

### NULLはイコールで判定してはならない
以下のSQLをみると一目瞭然です。
```
mysql> SELECT COUNT(*) FROM rental WHERE return_date = NULL;
+----------+
| COUNT(*) |
+----------+
|        0 |
+----------+
1 row in set (0.01 sec)

mysql> SELECT COUNT(*) FROM rental WHERE return_date IS NULL;
+----------+
| COUNT(*) |
+----------+
|      183 |
+----------+
1 row in set (0.01 sec)
```

### NULLが含まれるフィールドはWHEREの際に集計数に明示的に指定する必要がある
sakilaのaddressテーブルのaddress2フィールドにはNULLか空しか値が存在しない。このテーブルを使って動作確認を行う。

addressテーブル全体では603件存在する。なお、address.address2フィールドにはNULLか空しか値が存在しない
```
mysql> SELECT COUNT(*) FROM address;
+----------+
| COUNT(*) |
+----------+
|      603 |
+----------+
1 row in set (0.00 sec)

mysql> SELECT COUNT(*) FROM address WHERE address2 = "" OR address2 IS NULL;
+----------+
| COUNT(*) |
+----------+
|      603 |
+----------+
1 row in set (0.01 sec)
```

空の値は599件となる。つまり、NULLは4件含まれることが期待されている。
```
mysql> SELECT COUNT(*) FROM address WHERE address2 = "";
+----------+
| COUNT(*) |
+----------+
|      599 |
+----------+
1 row in set (0.01 sec)
```

空でないパターンを除外するが0件と表示される。
フィールドを指定してしまうとNULLは集計対象に含まれなくなる。
```
mysql> SELECT COUNT(*) FROM address WHERE address2 != "";
+----------+
| COUNT(*) |
+----------+
|        0 |
+----------+
1 row in set (0.01 sec)
```

なお、IS NULLで明示的に指定すれば4件あることが確認できる。
```
mysql> SELECT COUNT(*) FROM address WHERE address2 IS NULL;
+----------+
| COUNT(*) |
+----------+
|        4 |
+----------+
1 row in set (0.01 sec)
```

COUNTの引数の指定方法でもNULLの場合には正しく集計値が取得できなくなるケースが存在する
```
mysql> SELECT COUNT(*),address2 FROM address GROUP BY address2;
+----------+----------+
| COUNT(*) | address2 |
+----------+----------+
|        4 | NULL     |
|      599 |          |
+----------+----------+
2 rows in set (0.01 sec)

mysql> SELECT COUNT(address2),address2 FROM address GROUP BY address2;
+-----------------+----------+
| COUNT(address2) | address2 |
+-----------------+----------+
|               0 | NULL     |
|             599 |          |
+-----------------+----------+
2 rows in set (0.00 sec)
```


### COUNT時もNULLは要注意
rentalテーブルのreturn_dateには日付が入っていますが、年度だけ取得するようにしています。
この場合、COUNT(\*)をしていないとNULLの値が正しく取得できていないことがわかります。
```
mysql> SELECT COUNT(DATE_FORMAT(return_date,'%Y')), DATE_FORMAT(return_date,'%Y') FROM rental GROUP BY DATE_FORMAT(return_date,'%Y');
+--------------------------------------+-------------------------------+
| COUNT(DATE_FORMAT(return_date,'%Y')) | DATE_FORMAT(return_date,'%Y') |
+--------------------------------------+-------------------------------+
|                                    0 | NULL                          |
|                                15861 | 2005                          |
+--------------------------------------+-------------------------------+
2 rows in set (0.02 sec)

mysql> SELECT COUNT(*), DATE_FORMAT(return_date,'%Y') FROM rental GROUP BY DATE_FORMAT(return_date,'%Y');
+----------+-------------------------------+
| COUNT(*) | DATE_FORMAT(return_date,'%Y') |
+----------+-------------------------------+
|      183 | NULL                          |
|    15861 | 2005                          |
+----------+-------------------------------+
2 rows in set (0.02 sec)
```
