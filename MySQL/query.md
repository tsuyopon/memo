# 概要
sakilaデータベースを使ってjoinに使えそうなことをまとめる

### JOINのパターン
たった、3つのパターンだけのようだ
- inner join
  - 1:1の関係で結合する
  - inner joinの場合には双方で結合できなければ、そのレコードは削除されることに注意する
- left join
  - 左にあるテーブルを元に結合する
- right join
  - 右にあるテーブルを元に結合する

この他にも次のように煩わしいのがあるがきほんは上記の３つらしい
- outer join
- cross join
- left outer join
- right outer join

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

### joinしてみる
```
mysql> SELECT * FROM city AS ci LEFT JOIN country AS co ON ci.country_id = co.country_id LIMIT 10;
+---------+--------------------+------------+---------------------+------------+----------------------+---------------------+
| city_id | city               | country_id | last_update         | country_id | country              | last_update         |
+---------+--------------------+------------+---------------------+------------+----------------------+---------------------+
|       1 | A Corua (La Corua) |         87 | 2006-02-15 04:45:25 |         87 | Spain                | 2006-02-15 04:44:00 |
|       2 | Abha               |         82 | 2006-02-15 04:45:25 |         82 | Saudi Arabia         | 2006-02-15 04:44:00 |
|       3 | Abu Dhabi          |        101 | 2006-02-15 04:45:25 |        101 | United Arab Emirates | 2006-02-15 04:44:00 |
|       4 | Acua               |         60 | 2006-02-15 04:45:25 |         60 | Mexico               | 2006-02-15 04:44:00 |
|       5 | Adana              |         97 | 2006-02-15 04:45:25 |         97 | Turkey               | 2006-02-15 04:44:00 |
|       6 | Addis Abeba        |         31 | 2006-02-15 04:45:25 |         31 | Ethiopia             | 2006-02-15 04:44:00 |
|       7 | Aden               |        107 | 2006-02-15 04:45:25 |        107 | Yemen                | 2006-02-15 04:44:00 |
|       8 | Adoni              |         44 | 2006-02-15 04:45:25 |         44 | India                | 2006-02-15 04:44:00 |
|       9 | Ahmadnagar         |         44 | 2006-02-15 04:45:25 |         44 | India                | 2006-02-15 04:44:00 |
|      10 | Akishima           |         50 | 2006-02-15 04:45:25 |         50 | Japan                | 2006-02-15 04:44:00 |
+---------+--------------------+------------+---------------------+------------+----------------------+---------------------+
10 rows in set (0.00 sec)
```

上記の例ではcountry_idの列が重複しているが、この列を重複せずに表示するにはUSINGを指定して結合したいカラムを指定する。
```
mysql> SELECT * FROM city LEFT JOIN country USING(country_id) LIMIT 3;
+------------+---------+--------------------+---------------------+----------------------+---------------------+
| country_id | city_id | city               | last_update         | country              | last_update         |
+------------+---------+--------------------+---------------------+----------------------+---------------------+
|         87 |       1 | A Corua (La Corua) | 2006-02-15 04:45:25 | Spain                | 2006-02-15 04:44:00 |
|         82 |       2 | Abha               | 2006-02-15 04:45:25 | Saudi Arabia         | 2006-02-15 04:44:00 |
|        101 |       3 | Abu Dhabi          | 2006-02-15 04:45:25 | United Arab Emirates | 2006-02-15 04:44:00 |
+------------+---------+--------------------+---------------------+----------------------+---------------------+
3 rows in set (0.00 sec)
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

### UPDATEを使ってJOINして、結合した複数のテーブルを一気に更新する
次の例ではuser_mainとuser_subの両方を更新する例です。
```
参考)
mysql> UPDATE user_main a
LEFT JOIN user_sub b
ON a.user_id = b.user_id
SET a.name = "name2a new!", b.name = "name2b new!"
WHERE b.type = 2;
```

複数テーブルが更新されるとレコード数も1ではなく更新されたテーブル数になる。

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

# 更新系

### 古いテーブルのレコードを新しいテーブルにコピーする
```
mysql> SELECT * INTO oldtable FROM newtable;
```


# 参考URL 
- http://blog.livedoor.jp/sasata299/archives/51106595.html
- http://stackoverflow.com/questions/5706437/whats-the-difference-between-inner-join-left-join-right-join-and-full-join
- https://www.codeproject.com/kb/database/visual_sql_joins.aspx
