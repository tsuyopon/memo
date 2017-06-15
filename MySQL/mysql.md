# 概要
MySQLに関する基本的な事柄について

# 詳細

### pagerを変更する
pagerをlessに変更する例
```
mysql> pager less -n -i -S -F -X
```

以下はlessのオプション
- "-n": 行表示抑制
- "-i": 検索時の大文字小文字無視
- "-S": 折り返し抑制
- "-F": 一画面内に表示が収まる場合は表示して終了
- "-X": less終了時に画面クリアさせない

### 現在のステータスを表示する
以外と知られていないがstatusだけで実行するとその時のmysqlのステータスを表示してくれるらしい
```
mysql> status
--------------
mysql  Ver 14.14 Distrib 5.6.22, for osx10.10 (x86_64) using  EditLine wrapper

Connection id:		10
Current database:	
Current user:		root@localhost
SSL:			Not in use
Current pager:		stdout
Using outfile:		''
Using delimiter:	;
Server version:		5.6.22 Homebrew
Protocol version:	10
Connection:		Localhost via UNIX socket
Server characterset:	utf8
Db     characterset:	utf8
Client characterset:	utf8
Conn.  characterset:	utf8
UNIX socket:		/tmp/mysql.sock
Uptime:			16 days 8 hours 4 min 6 sec

Threads: 1  Questions: 794  Slow queries: 0  Opens: 834  Flush tables: 1  Open tables: 113  Queries per second avg: 0.000
--------------
```

### 数値・整数型, 数値・浮動小数点型, 日付・時刻型
- http://mysql.javarou.com/dat/000831.html

### 比較演算子

```
a = b     a と b は等しい
a <=> b   a と b は等しい(NULL対応)
a <> b    a と b は等しくない
a != b    a と b は等しくない
a < b     a は b よりも小さい
a <= b    a は b よりも小さいか等しい
a > b     a は b よりも大きい
a >= b    a は b よりも大きいか等しい
```

### 文字列の完全一致、前方部分一致、後方部分一致
```
WHERE　フィールド名　LIKE　'%文字列'    /* 後方一致検索 */
WHERE　フィールド名　LIKE　'文字列%'    /* 前方一致検索 */
WHERE　フィールド名　LIKE　'%文字列%'   /* 部分一致検索 */
WHERE　フィールド名　LIKE　'文字列'     /* 完全一致。LIKEの部分は=に置換してもOK */
```

### テーブル定義を確認する
以下の３つどれを実行しても同じ
```
mysql> DESC actor;
mysql> SHOW COLUMNS FROM actor;
mysql> SHOW FIELDS FROM actor;
```

以下に例を示す。
```
mysql> SHOW COLUMNS FROM actor;
+-------------+----------------------+------+-----+-------------------+-----------------------------+
| Field       | Type                 | Null | Key | Default           | Extra                       |
+-------------+----------------------+------+-----+-------------------+-----------------------------+
| actor_id    | smallint(5) unsigned | NO   | PRI | NULL              | auto_increment              |
| first_name  | varchar(45)          | NO   |     | NULL              |                             |
| last_name   | varchar(45)          | NO   | MUL | NULL              |                             |
| last_update | timestamp            | NO   |     | CURRENT_TIMESTAMP | on update CURRENT_TIMESTAMP |
+-------------+----------------------+------+-----+-------------------+-----------------------------+
4 rows in set (0.00 sec)
```

もっとたくさん情報を表示する
```
mysql> SHOW FULL COLUMNS FROM actor;
+-------------+----------------------+-----------------+------+-----+-------------------+-----------------------------+---------------------------------+---------+
| Field       | Type                 | Collation       | Null | Key | Default           | Extra                       | Privileges                      | Comment |
+-------------+----------------------+-----------------+------+-----+-------------------+-----------------------------+---------------------------------+---------+
| actor_id    | smallint(5) unsigned | NULL            | NO   | PRI | NULL              | auto_increment              | select,insert,update,references |         |
| first_name  | varchar(45)          | utf8_general_ci | NO   |     | NULL              |                             | select,insert,update,references |         |
| last_name   | varchar(45)          | utf8_general_ci | NO   | MUL | NULL              |                             | select,insert,update,references |         |
| last_update | timestamp            | NULL            | NO   |     | CURRENT_TIMESTAMP | on update CURRENT_TIMESTAMP | select,insert,update,references |         |
+-------------+----------------------+-----------------+------+-----+-------------------+-----------------------------+---------------------------------+---------+
4 rows in set (0.00 sec)
```

### テーブル作成の実行文を確認する
```
mysql> SHOW CREATE TABLE actor \G
*************************** 1. row ***************************
       Table: actor
Create Table: CREATE TABLE `actor` (
  `actor_id` smallint(5) unsigned NOT NULL AUTO_INCREMENT,
  `first_name` varchar(45) NOT NULL,
  `last_name` varchar(45) NOT NULL,
  `last_update` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP,
  PRIMARY KEY (`actor_id`),
  KEY `idx_actor_last_name` (`last_name`)
) ENGINE=InnoDB AUTO_INCREMENT=201 DEFAULT CHARSET=utf8
1 row in set (0.00 sec)
```

### VIEW一覧を見る
以下をそのまま変更せずに実行すれば、ビュー
```
mysql> SELECT table_name FROM information_schema.tables WHERE table_type = 'VIEW';
+----------------------------+
| table_name                 |
+----------------------------+
| current_dept_emp           |
| dept_emp_latest_date       |
| actor_info                 |
| customer_list              |
| film_list                  |
| nicer_but_slower_film_list |
| sales_by_film_category     |
| sales_by_store             |
| staff_list                 |
+----------------------------+
9 rows in set (0.02 sec)
```

逆にBASE TABLEを見るには次のようにします。
```
mysql> SELECT table_name FROM information_schema.tables WHERE table_type = 'BASE TABLE';
```

システムに関するテーブルは次のようにして見れます。
```
mysql> SELECT table_name FROM information_schema.tables WHERE table_type = 'SYSTEM VIEW';
```

### VIEWのCreate定義を見る
```
mysql> SHOW CREATE VIEW nicer_but_slower_film_list \G
*************************** 1. row ***************************
                View: nicer_but_slower_film_list
         Create View: CREATE ALGORITHM=UNDEFINED DEFINER=`root`@`localhost` SQL SECURITY DEFINER VIEW `nicer_but_slower_film_list` AS select `film`.`film_id` AS `FID`,`film`.`title` AS `title`,`film`.`description` AS `description`,`category`.`name` AS `category`,`film`.`rental_rate` AS `price`,`film`.`length` AS `length`,`film`.`rating` AS `rating`,group_concat(concat(concat(ucase(substr(`actor`.`first_name`,1,1)),lcase(substr(`actor`.`first_name`,2,length(`actor`.`first_name`))),_utf8' ',concat(ucase(substr(`actor`.`last_name`,1,1)),lcase(substr(`actor`.`last_name`,2,length(`actor`.`last_name`)))))) separator ', ') AS `actors` from ((((`category` left join `film_category` on((`category`.`category_id` = `film_category`.`category_id`))) left join `film` on((`film_category`.`film_id` = `film`.`film_id`))) join `film_actor` on((`film`.`film_id` = `film_actor`.`film_id`))) join `actor` on((`film_actor`.`actor_id` = `actor`.`actor_id`))) group by `film`.`film_id`,`category`.`name`
character_set_client: utf8
collation_connection: utf8_general_ci
1 row in set (0.00 sec)
```

### 関数一覧を見る
```
mysql> SHOW FUNCTION STATUS \G
*************************** 1. row ***************************
                  Db: sakila
                Name: get_customer_balance
                Type: FUNCTION
             Definer: root@localhost
            Modified: 2016-12-22 08:46:36
             Created: 2016-12-22 08:46:36
       Security_type: DEFINER
             Comment: 
character_set_client: utf8
collation_connection: utf8_general_ci
  Database Collation: utf8_general_ci
*************************** 2. row ***************************
                  Db: sakila
                Name: inventory_held_by_customer
                Type: FUNCTION
             Definer: root@localhost
            Modified: 2016-12-22 08:46:36
             Created: 2016-12-22 08:46:36
       Security_type: DEFINER
             Comment: 
character_set_client: utf8
collation_connection: utf8_general_ci
  Database Collation: utf8_general_ci
*************************** 3. row ***************************
                  Db: sakila
                Name: inventory_in_stock
                Type: FUNCTION
             Definer: root@localhost
            Modified: 2016-12-22 08:46:36
             Created: 2016-12-22 08:46:36
       Security_type: DEFINER
             Comment: 
character_set_client: utf8
collation_connection: utf8_general_ci
  Database Collation: utf8_general_ci
3 rows in set (0.01 sec)
```

### 関数定義を見る
```
mysql> SHOW CREATE FUNCTION get_customer_balance \G
```

### 外部キー制約

更新時の挙動を示す場合にはON UPDATEを使います。
```
CREATE TABLE 子テーブル名(子カラム名 データ型,
  FOREIGN KEY (子カラム名)
  REFERENCES 親テーブル名(親カラム名)
  ON UPDATE <reference_option>
) ENGINE=InnoDB;
```

削除時の挙動を示す場合にはON DELETEを使います。
```
CREATE TABLE 子テーブル名(子カラム名 データ型,
  FOREIGN KEY (子カラム名)
  REFERENCES 親テーブル名(親カラム名)
  ON DELETE <reference_option>
) ENGINE=InnoDB;
```

<reference_option>に指定できるのは次のものが指定できる
- RESTRICT:     テーブルに対して更新や削除を行うとエラーが発生
- CASCADE:      親テーブルに対して更新を行うと子テーブルで同じ値を持つカラムの値も合わせて更新されます。削除の場合には削除される。
- SET NULL:     親テーブルに対して更新を行うと子テーブルで同じ値を持つカラムの値がNULLに更新される
- NO ACTION:    親テーブルに対して更新や削除を行うとエラーが発生します(MySQLだとNO ACTIONとRESTRICTは同じ)

なお、ON UPDATE, ON DELETEの句が存在しない場合には、参照している子テーブルの該当行がある場合、親テーブルの行を削除できない。

- http://qiita.com/suin/items/21fe6c5a78c1505b19cb

### そのほかの参考資料
- viewとstored procedureの違いについて
 - http://stackoverflow.com/questions/3773277/stored-procedures-vs-views


### テーブルの作成時刻、更新時刻、参照時刻を表示する
Check_timeについてはすべてのエンジンが入るとは限らないので注意すること。その場合にはNULLになるらしい。  
以下の各カラムの意味については以下の資料を参考のこと
- https://dev.mysql.com/doc/refman/5.6/ja/show-table-status.html
```
mysql> SHOW TABLE STATUS FROM sakila \G
*************************** 1. row ***************************
           Name: actor
         Engine: InnoDB
        Version: 10
     Row_format: Compact
           Rows: 200
 Avg_row_length: 81
    Data_length: 16384
Max_data_length: 0
   Index_length: 16384
      Data_free: 0
 Auto_increment: 201
    Create_time: 2016-12-22 08:46:35
    Update_time: NULL
     Check_time: NULL
      Collation: utf8_general_ci
       Checksum: NULL
 Create_options: 
        Comment: 
```

上記コマンドの時刻は次のinformation_schema.tablesテーブル参照でも確認することができる。  
```
mysql> SELECT * FROM information_schema.tables WHERE table_schema = DATABASE() LIMIT 2 \G
*************************** 1. row ***************************
  TABLE_CATALOG: def
   TABLE_SCHEMA: sakila
     TABLE_NAME: actor
     TABLE_TYPE: BASE TABLE
         ENGINE: InnoDB
        VERSION: 10
     ROW_FORMAT: Compact
     TABLE_ROWS: 200
 AVG_ROW_LENGTH: 81
    DATA_LENGTH: 16384
MAX_DATA_LENGTH: 0
   INDEX_LENGTH: 16384
      DATA_FREE: 0
 AUTO_INCREMENT: 201
    CREATE_TIME: 2016-12-22 08:46:35
    UPDATE_TIME: NULL
     CHECK_TIME: NULL
TABLE_COLLATION: utf8_general_ci
       CHECKSUM: NULL
 CREATE_OPTIONS: 
  TABLE_COMMENT: 
```


