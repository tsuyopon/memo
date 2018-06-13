# 概要
queryについてまとめる

# 詳細
### IFなどを試して見る
次のようにして簡単に試すことができる。
```
mysql> SELECT 'INPUT 0' AS 'TEST', IF(0 = 0, 1, 0), IF(0 <> 0, 1, 0), IF(100 = 0, 1, 0), IF(100 <> 0, 1, 0), IF(null <> 0, 1, 0);
+---------+-----------------+------------------+-------------------+--------------------+---------------------+
| TEST    | IF(0 = 0, 1, 0) | IF(0 <> 0, 1, 0) | IF(100 = 0, 1, 0) | IF(100 <> 0, 1, 0) | IF(null <> 0, 1, 0) |
+---------+-----------------+------------------+-------------------+--------------------+---------------------+
| INPUT 0 |               1 |                0 |                 0 |                  1 |                   0 |
+---------+-----------------+------------------+-------------------+--------------------+---------------------+
1 row in set (0.00 sec)
```

### 通常SELECTで表示される逆順から３件取得したい
DESCしてLIMITで件数制限して取得すればOK
```
mysql> SELECT * FROM country ORDER BY country_id DESC LIMIT 0, 3;
+------------+------------+---------------------+
| country_id | country    | last_update         |
+------------+------------+---------------------+
|        109 | Zambia     | 2006-02-15 04:44:00 |
|        108 | Yugoslavia | 2006-02-15 04:44:00 |
|        107 | Yemen      | 2006-02-15 04:44:00 |
+------------+------------+---------------------+
3 rows in set (0.01 sec)
```

### 最大値を持つレコードでdistinctする
次のテーブルがあったとして(idは重複している)
```
mysql> SELECT * FROM table1;
+------+--------+
|   id | num    |
+---------------+
|  101 | 1      |
|  101 | 2      |
|  102 | 5      |
|  102 | 3      |
|  102 | 1      |
|  103 | 3      |
|  103 | 7      |
|  103 | 5      |
+---------------+
```

重複する各種idで最大のnumを取得するSQL文は次のようになります。
```
mysql> SELECT DISTINCT id, MAX( num ) FROM table1 GROUP BY id;
+------+----------+
|   id | MAX(num) |
+-----------------+
|  101 | 2        |
|  102 | 5        |
|  103 | 7        |
+-----------------+
```

### ある列で並べて、さらに別の列で並べる
ORDER BYの後にカラムを順番に記述します。  
postal_codeやlast_updateは桁違いの場合8000,900,9000のように意図しない順番になります。
```
mysql> SELECT * FROM address ORDER BY postal_code, last_update DESC;
```

次のように+0などを入れると数値と解釈して意図した結果となります。
```
mysql> SELECT * FROM address ORDER BY postal_code+0, last_update+0 DESC;
```

### 特定のカテゴリで足しあわせを行う
actor_idは複数のfilm_idを持つ。以下の例ではactor_id毎にfilm_idのSUM, AVG, MIN, MAX, COUNT表示している。  
ただし、件数が200件と多いので180番目のactor_id以降を表示した例です。
```
mysql> SELECT actor_id, SUM(film_id), AVG(film_id), MIN(film_id), MAX(film_id), COUNT(film_id) FROM film_actor GROUP BY actor_id HAVING(actor_id) > 180;
+----------+--------------+--------------+--------------+--------------+----------------+
| actor_id | SUM(film_id) | AVG(film_id) | MIN(film_id) | MAX(film_id) | COUNT(film_id) |
+----------+--------------+--------------+--------------+--------------+----------------+
|      181 |        19950 |     511.5385 |            5 |          991 |             39 |
|      182 |        13856 |     577.3333 |           33 |          990 |             24 |
|      183 |        10177 |     535.6316 |           32 |          983 |             19 |
|      184 |        16955 |     584.6552 |           35 |          985 |             29 |
|      185 |        17348 |     578.2667 |            7 |          973 |             30 |
|      186 |         8143 |     508.9375 |           95 |          994 |             16 |
|      187 |        14006 |     424.4242 |           17 |          976 |             33 |
|      188 |        13794 |     459.8000 |            1 |          989 |             30 |
|      189 |        13388 |     557.8333 |           43 |          940 |             24 |
|      190 |        13115 |     485.7407 |           38 |          959 |             27 |
|      191 |        17888 |     596.2667 |           16 |          993 |             30 |
|      192 |        13991 |     482.4483 |           16 |          819 |             29 |
|      193 |        11324 |     492.3478 |           44 |          960 |             23 |
|      194 |         8571 |     389.5909 |            9 |          940 |             22 |
|      195 |        15031 |     556.7037 |          129 |          962 |             27 |
|      196 |        16814 |     560.4667 |           64 |          972 |             30 |
|      197 |        16990 |     514.8485 |            6 |          995 |             33 |
|      198 |        21894 |     547.3500 |            1 |          997 |             40 |
|      199 |         7715 |     514.3333 |           67 |          953 |             15 |
|      200 |         9706 |     485.3000 |            5 |          993 |             20 |
+----------+--------------+--------------+--------------+--------------+----------------+
20 rows in set (0.01 sec)
```

### 特定のカラムが重複している行を取得する
重複排除はDISTINCで簡単に可能だが、重複する場合にはGROUP BYして特定の件数以上のもののみを出力させるようにする。
```
mysql> SELECT * FROM customer GROUP BY first_name HAVING COUNT(*) >= 2;
+-------------+----------+------------+-----------+----------------------------------+------------+--------+---------------------+---------------------+
| customer_id | store_id | first_name | last_name | email                            | address_id | active | create_date         | last_update         |
+-------------+----------+------------+-----------+----------------------------------+------------+--------+---------------------+---------------------+
|         146 |        1 | JAMIE      | RICE      | JAMIE.RICE@sakilacustomer.org    |        150 |      1 | 2006-02-14 22:04:36 | 2006-02-15 04:57:20 |
|         215 |        2 | JESSIE     | BANKS     | JESSIE.BANKS@sakilacustomer.org  |        219 |      1 | 2006-02-14 22:04:36 | 2006-02-15 04:57:20 |
|          67 |        1 | KELLY      | TORRES    | KELLY.TORRES@sakilacustomer.org  |         71 |      1 | 2006-02-14 22:04:36 | 2006-02-15 04:57:20 |
|         143 |        1 | LESLIE     | GORDON    | LESLIE.GORDON@sakilacustomer.org |        147 |      1 | 2006-02-14 22:04:36 | 2006-02-15 04:57:20 |
|         178 |        2 | MARION     | SNYDER    | MARION.SNYDER@sakilacustomer.org |        182 |      1 | 2006-02-14 22:04:36 | 2006-02-15 04:57:20 |
|         253 |        1 | TERRY      | CARLSON   | TERRY.CARLSON@sakilacustomer.org |        258 |      1 | 2006-02-14 22:04:36 | 2006-02-15 04:57:20 |
|         108 |        1 | TRACY      | COLE      | TRACY.COLE@sakilacustomer.org    |        112 |      1 | 2006-02-14 22:04:36 | 2006-02-15 04:57:20 |
|         219 |        2 | WILLIE     | HOWELL    | WILLIE.HOWELL@sakilacustomer.org |        223 |      1 | 2006-02-14 22:04:36 | 2006-02-15 04:57:20 |
+-------------+----------+------------+-----------+----------------------------------+------------+--------+---------------------+---------------------+
8 rows in set (0.00 sec)
```


### DATETIMEを日付順でレコード数集計をする
次のようなDATETIMEレコードがカラムに存在していて、日付毎にレコードを集計したいような場合
```
YYYY-MM-DD hh:mm:ss
```

mysqlは次のようになる。
```
mysql> SELECT DATE_FORMAT(create_time, '%Y-%m-%d') AS time, COUNT(*) AS count FROM MyTable GROUP BY DATE_FORMAT(create_time, '%Y%m%d');
```

### UNIONを使って重複レコードを排除する。
上の例では左側(3日前)と右側(2日前)のSELECTが異なるので２行表示されるが、下の出力例では左側と右側が同じなので1行だけで重複排除されている。
```
mysql> select date_add(now(), interval 3 day) UNION select date_add(now(), interval 2 day);
+---------------------------------+
| date_add(now(), interval 3 day) |
+---------------------------------+
| 2017-06-02 08:26:20             |
| 2017-06-01 08:26:20             |
+---------------------------------+
2 rows in set (0.00 sec)

mysql> select date_add(now(), interval 3 day) UNION select date_add(now(), interval 3 day);
+---------------------------------+
| date_add(now(), interval 3 day) |
+---------------------------------+
| 2017-06-02 08:26:22             |
+---------------------------------+
1 row in set (0.00 sec)
```

### UNION ALLを使って重複レコードも表示する
UNIONだけだと重複レコードを排除していたが、UNION ALLだと重複レコードを表示する。
```
mysql> select date_add(now(), interval 3 day) UNION ALL select date_add(now(), interval 3 day);
+---------------------------------+
| date_add(now(), interval 3 day) |
+---------------------------------+
| 2017-06-02 08:28:15             |
| 2017-06-02 08:28:15             |
+---------------------------------+
2 rows in set (0.00 sec)
```

### CASE WHENを使ってみる
```
mysql> SELECT name, SID FROM staff_list;
+--------------+-----+
| name         | SID |
+--------------+-----+
| Mike Hillyer |   1 |
| Jon Stephens |   2 |
+--------------+-----+
2 rows in set (0.00 sec)

mysql> SELECT name, SID, CASE 
         WHEN SID = 1 THEN 'TOKYO' 
		 WHEN SID = 2 THEN 'OSAKA' 
		 ELSE 'OTHER' 
	  END AS storeName FROM staff_list;
+--------------+-----+-----------+
| name         | SID | storeName |
+--------------+-----+-----------+
| Mike Hillyer |   1 | TOKYO     |
| Jon Stephens |   2 | OSAKA     |
+--------------+-----+-----------+
2 rows in set (0.00 sec)
```

## 件数取得
FOUND_ROWS()を実行すると取得したレコード件数を取得できます。
```
mysql> SELECT * FROM actor LIMIT 3;
+----------+------------+-----------+---------------------+
| actor_id | first_name | last_name | last_update         |
+----------+------------+-----------+---------------------+
|        1 | PENELOPE   | GUINESS   | 2006-02-15 04:34:33 |
|        2 | NICK       | WAHLBERG  | 2006-02-15 04:34:33 |
|        3 | ED         | CHASE     | 2006-02-15 04:34:33 |
+----------+------------+-----------+---------------------+
3 rows in set (0.00 sec)

mysql> SELECT FOUND_ROWS();
+--------------+
| FOUND_ROWS() |
+--------------+
|            3 |
+--------------+
1 row in set (0.00 sec)
```

OFFSETを使うと直感に反した件数が帰ってきます。
```
mysql> SELECT * FROM actor LIMIT 3 OFFSET 100;
+----------+------------+-----------+---------------------+
| actor_id | first_name | last_name | last_update         |
+----------+------------+-----------+---------------------+
|      101 | SUSAN      | DAVIS     | 2006-02-15 04:34:33 |
|      102 | WALTER     | TORN      | 2006-02-15 04:34:33 |
|      103 | MATTHEW    | LEIGH     | 2006-02-15 04:34:33 |
+----------+------------+-----------+---------------------+
3 rows in set (0.00 sec)

mysql> SELECT FOUND_ROWS();
+--------------+
| FOUND_ROWS() |
+--------------+
|          103 |
+--------------+
1 row in set (0.00 sec)
```

テーブルの全体件数を取得したい場合にはSQL_CALC_FOUND_ROWSを指定するとFOUND_ROWS()で取得することができます。
```
mysql> SELECT SQL_CALC_FOUND_ROWS * FROM actor LIMIT 3 OFFSET 100;
+----------+------------+-----------+---------------------+
| actor_id | first_name | last_name | last_update         |
+----------+------------+-----------+---------------------+
|      101 | SUSAN      | DAVIS     | 2006-02-15 04:34:33 |
|      102 | WALTER     | TORN      | 2006-02-15 04:34:33 |
|      103 | MATTHEW    | LEIGH     | 2006-02-15 04:34:33 |
+----------+------------+-----------+---------------------+
3 rows in set (0.00 sec)

mysql> SELECT FOUND_ROWS();
+--------------+
| FOUND_ROWS() |
+--------------+
|          200 |
+--------------+
1 row in set (0.00 sec)
```

## 更新系

### 古いテーブルのレコードを新しいテーブルにコピーする
```
mysql> SELECT * INTO oldtable FROM newtable;
```

### 変数に取得した値を格納する
例えば次のようなレコードが存在していて特定のactor_idのフィールドを取得する場合、
```
mysql> select * from actor LIMIT 3;
+----------+------------+-----------+---------------------+
| actor_id | first_name | last_name | last_update         |
+----------+------------+-----------+---------------------+
|        1 | PENELOPE   | GUINESS   | 2006-02-15 04:34:33 |
|        2 | NICK       | WAHLBERG  | 2006-02-15 04:34:33 |
|        3 | ED         | CHASE     | 2006-02-15 04:34:33 |
+----------+------------+-----------+---------------------+
3 rows in set (0.00 sec)
```

次の様な感じで変数に格納できます。なお、条件で複数レコードに合致した場合にはエラーとなります。
```
mysql> SELECT first_name, last_name INTO @first_value, @last_value FROM actor WHERE actor_id = 3;
Query OK, 1 row affected (0.00 sec)

mysql> SELECT @first_value, @last_value;
+--------------+-------------+
| @first_value | @last_value |
+--------------+-------------+
| ED           | CHASE       |
+--------------+-------------+
1 row in set (0.00 sec)
```

# 参考URL 
- http://blog.livedoor.jp/sasata299/archives/51106595.html
