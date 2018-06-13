# 概要
queryの主にjoin関連についてまとめる

### JOINのパターン
joinは同じ意味であるがいろいろな書き方があるので混乱しやすいが主要なものをまとめると次の通り。
inner join, left joinあたりを覚えておけば通常はあまり困ることはない
- inner join(= join)
  - 1:1の関係で結合する
  - inner joinの場合には双方で結合できなければ、そのレコードは削除されることに注意する
- left join (= left outer join)
  - 左にあるテーブルを元に結合する。右側に一致するレコードが存在しなくてもnullとしてレコードを表示する
- right join (= right outer join)
  - 右にあるテーブルを元に結合する。左側に一致するレコードが存在しなくてもnullとしてレコードを表示する
- full join (= full outer join)
  - 左右にあるテーブルを結合する。右側、左側どちらのテーブルでレコードが一致しなかったとしてもそのレコードを表示する。
- cross join
  - 左右のレコードの直積を求める。ON, USING を指定しない場合、左右のテーブルの直積を返します
  - 右テーブルにN列、左テーブルにM列だと、cross joinするとMxNレコードが表示される。

次のstackflowがすごいわかりやすい
- https://stackoverflow.com/questions/38549/what-is-the-difference-between-inner-join-and-outer-join?rq=1

上記内容から引用すると、下記のようなテーブルが存在する場合
```
A    B
-    -
1    3
2    4
3    5
4    6
```

- inner join
```
select * from a INNER JOIN b on a.a = b.b;
select a.*,b.*  from a,b where a.a = b.b;

a | b
--+--
3 | 3
4 | 4
```
- left outer join
```
select * from a LEFT OUTER JOIN b on a.a = b.b;
select a.*,b.*  from a,b where a.a = b.b(+);

a |  b
--+-----
1 | null
2 | null
3 |    3
4 |    4
```
- right outer join
```
select * from a RIGHT OUTER JOIN b on a.a = b.b;
select a.*,b.*  from a,b where a.a(+) = b.b;

a    |  b
-----+----
3    |  3
4    |  4
null |  5
null |  6
```
- full outer join
```
select * from a FULL OUTER JOIN b on a.a = b.b;

 a   |  b
-----+-----
   1 | null
   2 | null
   3 |    3
   4 |    4
null |    6
null |    5
```
- cross join
```
select * from a CROSS JOIN b;

A    B
-    -
1    3
1    4
1    5
1    6
2    3
2    4
2    5
2    6
3    3
3    4
3    5
3    6
4    3
4    4
4    5
4    6
```

### joinを使って見る
とりあえず今回はLEFT JOINの例です。
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

### あるテーブルを２度参照させるようなSQL文を書く
たとえば、次のようなAとBというテーブルが存在して
```
A

<myid>   <name>
1      hoge
2      fuga
3      piyo
4      hoge2
```

```
B
<id>   <left_myid>   <right_myid>
1      2             3
2      2             4
3      3             1
4      3             4
5      1             3
```


AのmyidとBのleft_myidを一致するright_myidを探索して、right_myidと一致するA.myidのnameを取得したい場合、 Aテーブルは２度参照されることになる。
この場合には次のように記述する
```
SELECT A2.name FROM A AS A1
INNER JOIN B AS B1 ON A1.myid = B1.left_myid
INNER JOIN (SELECT * FROM A) AS A2 ON B1.right_myid = A2.name;
```

INNER JOINの後にテーブルではなく「(SELECT * FROM A) AS A2」などと記述できる点がポイントとなる

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
