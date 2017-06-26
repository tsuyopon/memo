# 概要
副問い合わせについて

# 詳細

### レコードが存在するかどうかをチェックする
存在するかどうかをチェックする場合にはEXISTSが使える。存在しない場合には「NOT EXISTS」にすればよい。
```
mysql> SELECT EXISTS (SELECT * FROM address ORDER BY postal_code, last_update DESC);
+-----------------------------------------------------------------------+
| EXISTS (SELECT * FROM address ORDER BY postal_code, last_update DESC) |
+-----------------------------------------------------------------------+
|                                                                     1 |
+-----------------------------------------------------------------------+
1 row in set (0.00 sec)
```

### FROMの後に副問い合わせした結果を指定する。
以下のサンプルは意味が無いが、FROMの後にSELECTしたものを指定する場合の例である。
そのまますると次のようにエラーがでる。
```
mysql> SELECT * FROM (SELECT * FROM address WHERE address2 IS NULL);
ERROR 1248 (42000): Every derived table must have its own alias
```

この場合には「AS T1」などとエイリアスを明示的に必要とする。
```
mysql> SELECT * FROM (SELECT * FROM address WHERE address2 IS NULL) AS T1;
+------------+----------------------+----------+----------+---------+-------------+-------------+---------------------+
| address_id | address              | address2 | district | city_id | postal_code | phone       | last_update         |
+------------+----------------------+----------+----------+---------+-------------+-------------+---------------------+
|          1 | 47 MySakila Drive    | NULL     | Alberta  |     300 |             |             | 2014-09-25 22:30:27 |
|          2 | 28 MySQL Boulevard   | NULL     | QLD      |     576 |             |             | 2014-09-25 22:30:09 |
|          3 | 23 Workhaven Lane    | NULL     | Alberta  |     300 |             | 14033335568 | 2014-09-25 22:30:27 |
|          4 | 1411 Lillydale Drive | NULL     | QLD      |     576 |             | 6172235589  | 2014-09-25 22:30:09 |
+------------+----------------------+----------+----------+---------+-------------+-------------+---------------------+
4 rows in set (0.00 sec)
```

### 副問い合わせで複数レコードが帰ってきたのでマッチさせたい
addressテーブルは600件ほどあるが、そのうち重複するcity_idは4件ある。
```
mysql> SELECT * FROM (SELECT city_id FROM address GROUP BY city_id HAVING COUNT(*) >= 2) AS T1;
+---------+
| city_id |
+---------+
|      42 |
|     300 |
|     312 |
|     576 |
+---------+
4 rows in set (0.00 sec)
```

複数件が返却される副問い合わせでは"="ではエラーとなる
```
mysql> SELECT * FROM address AS a1 INNER JOIN address AS a2 ON  a1.city_id = a2.city_id WHERE a1.city_id = (SELECT * FROM (SELECT city_id FROM address GROUP BY city_id HAVING COUNT(*) >= 2) AS T1);
ERROR 1242 (21000): Subquery returns more than 1 row
```

この場合にはINを使うと良い
```
mysql> SELECT COUNT(*) FROM address AS a1 INNER JOIN address AS a2 ON  a1.city_id = a2.city_id WHERE a1.city_id IN (SELECT * FROM (SELECT city_id FROM address GROUP BY city_id HAVING COUNT(*) >= 2) AS T1);
+----------+
| COUNT(*) |
+----------+
|       16 |
+----------+
1 row in set (0.00 sec)

``


