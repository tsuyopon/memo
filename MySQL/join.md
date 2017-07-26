# 概要
queryの主にjoin関連についてまとめる

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

次のstackflowがすごいわかりやすい
- https://stackoverflow.com/questions/38549/what-is-the-difference-between-inner-join-and-outer-join?rq=1

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

# 参考URL
- http://stackoverflow.com/questions/5706437/whats-the-difference-between-inner-join-left-join-right-join-and-full-join
- https://www.codeproject.com/kb/database/visual_sql_joins.aspx
