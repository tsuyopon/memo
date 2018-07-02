# 概要
MySQLのトリガー処理について


# 詳細

### 設定されているトリガー一覧を取得する
```
mysql> SHOW TRIGGERS \G
*************************** 1. row ***************************
             Trigger: customer_create_date
               Event: INSERT
               Table: customer
           Statement: SET NEW.create_date = NOW()
              Timing: BEFORE
             Created: NULL
            sql_mode: STRICT_TRANS_TABLES,STRICT_ALL_TABLES,NO_ZERO_IN_DATE,NO_ZERO_DATE,ERROR_FOR_DIVISION_BY_ZERO,TRADITIONAL,NO_AUTO_CREATE_USER,NO_ENGINE_SUBSTITUTION
             Definer: root@localhost
character_set_client: utf8
collation_connection: utf8_general_ci
  Database Collation: latin1_swedish_ci
*************************** 2. row ***************************
             Trigger: ins_film
               Event: INSERT
               Table: film
           Statement: BEGIN
    INSERT INTO film_text (film_id, title, description)
        VALUES (new.film_id, new.title, new.description);
  END
              Timing: AFTER
             Created: NULL
            sql_mode: STRICT_TRANS_TABLES,STRICT_ALL_TABLES,NO_ZERO_IN_DATE,NO_ZERO_DATE,ERROR_FOR_DIVISION_BY_ZERO,TRADITIONAL,NO_AUTO_CREATE_USER,NO_ENGINE_SUBSTITUTION
             Definer: root@localhost
character_set_client: utf8
collation_connection: utf8_general_ci
  Database Collation: latin1_swedish_ci
```

### サンプルでトリガーを使ってみる
以下はコピペしてトリガー作成まで
```
USE trigger_test
CREATE TABLE user(id int, name varchar(20));
CREATE TABLE log(logtext varchar(20), t timestamp);

delimiter $$

create trigger trigger_insert after insert on user for each row 
begin
insert into log (logtext) values ('INSERT');
end;
$$

delimiter ;
```

トリガーを確認するためにINSERTを1件入れて、logテーブルを確認してINSERTされていることを確認する。
```
mysql> insert into user values(1, 'Hoge');
Query OK, 1 row affected (0.01 sec)

mysql> SELECT * FROM log;
+---------+---------------------+
| logtext | t                   |
+---------+---------------------+
| INSERT  | 2018-06-19 13:12:08 |
+---------+---------------------+
1 row in set (0.00 sec)
```

続いて、2件一気に入れてみると、for each rowなので今度はlogテーブルに2件格納されていることを確認する。
```
mysql> insert into user values (2, 'Fuga'), (3, 'Piyo');
Query OK, 2 rows affected (0.01 sec)
Records: 2  Duplicates: 0  Warnings: 0

mysql> SELECT * FROM log;
+---------+---------------------+
| logtext | t                   |
+---------+---------------------+
| INSERT  | 2018-06-19 13:12:08 |
| INSERT  | 2018-06-19 13:14:50 |
| INSERT  | 2018-06-19 13:14:50 |
+---------+---------------------+
3 rows in set (0.01 sec)
```

終わったら削除しておくこと
```
mysql> DROP TRIGGER IF EXISTS trigger_test;
```

### 古い情報と新しい情報を参照する(NEW.xxx, OLD.xxx)

たとえば、UPDATEのトリガーを設定する際に古いカラム情報(更新前の値)と新しい登録カラム情報(更新後の値)をそれぞれで参照したい場合がある。

次のサンプルはそのままコピペで使えるUPDATEのトリガーサンプルです。
```
CREATE DATABASE trigger_test2;
USE trigger_test2;
CREATE TABLE user(id int, name varchar(20));
CREATE TABLE address(name varchar(20), oldname varchar(20));

DELIMITER $$

CREATE TRIGGER trigger_update AFTER UPDATE ON user FOR EACH ROW
BEGIN
INSERT INTO address VALUES (NEW.name, OLD.name);
END;
$$

DELIMITER ;
```

UPDATEのトリガーの確認なのであらかじめデータを1件入れておく。
```
mysql> INSERT INTO user VALUES(1, 'Hoge');
Query OK, 1 row affected (0.01 sec)
```

トリガーの挙動を確認しておく。NEW.nameには新しい名前、OLD.nameには古い値となっていることを確認しておく。
```
mysql> UPDATE user SET name = 'BrandnewHoge' where name = 'Hoge';
Query OK, 1 row affected (0.01 sec)
Rows matched: 1  Changed: 1  Warnings: 0

mysql> SELECT * FROM user;
+------+--------------+
| id   | name         |
+------+--------------+
|    1 | BrandnewHoge |
+------+--------------+
1 row in set (0.00 sec)

mysql> SELECT * FROM address;
+--------------+---------+
| name         | oldname |
+--------------+---------+
| BrandnewHoge | Hoge    |
+--------------+---------+
1 row in set (0.00 sec)``
```

- https://www.dbonline.jp/mysql/trigger/index3.html

### sakilaデータベースのtriggerについて
こちらを参考のこと
- https://dev.mysql.com/doc/sakila/en/sakila-structure-triggers.html


# 参考
- triggerに関するFAQ
  - https://dev.mysql.com/doc/refman/5.6/ja/faqs-triggers.html
