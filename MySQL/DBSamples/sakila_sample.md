# 概要
MySQLのサンプルデータベースとして
worldデータベースの後継として新しい機能などもテストできるようにしているのがSakilaデータベースとのことです。

# セットアップ
以下のページからダウンロードすることができるようです。
- https://dev.mysql.com/doc/index-other.html

tar.gzを取得して展開します。
```
$ wget http://downloads.mysql.com/docs/sakila-db.tar.gz
$ tar zxvf sakila-db.tar.gz 
$ cd sakila-db/
$ ls -1
sakila-data.sql
sakila-schema.sql
sakila.mwb
```

schemaを流し込んで、データを流し込めばもう利用できる状態となります。
mysql5.5でschemaを流したらFULLTEXTサポートしていないみたいなエラーがでましたが、mysql5.6に変更したらエラーが出なくなりましたので最新にしか対応していないと思われます。  
いい感じにテーブルがたくさんあるのでサンプルデータやテストとして非常に有用活用できそう。
```
$ mysql -u root -p < sakila-schema.sql
$ mysql -u root -p < sakila-data.sql
mysql> use sakila
mysql> show tables;
+----------------------------+
| Tables_in_sakila           |
+----------------------------+
| actor                      |
| actor_info                 |
| address                    |
| category                   |
| city                       |
| country                    |
| customer                   |
| customer_list              |
| film                       |
| film_actor                 |
| film_category              |
| film_list                  |
| film_text                  |
| inventory                  |
| language                   |
| nicer_but_slower_film_list |
| payment                    |
| rental                     |
| sales_by_film_category     |
| sales_by_store             |
| staff                      |
| staff_list                 |
| store                      |
+----------------------------+
23 rows in set (0.00 sec)
```


### ビューのテーブル一覧
```
mysql> select TABLE_SCHEMA,TABLE_NAME from information_schema.tables where TABLE_TYPE = 'VIEW' and  TABLE_SCHEMA = 'sakila';
+--------------+----------------------------+
| TABLE_SCHEMA | TABLE_NAME                 |
+--------------+----------------------------+
| sakila       | actor_info                 |
| sakila       | customer_list              |
| sakila       | film_list                  |
| sakila       | nicer_but_slower_film_list |
| sakila       | sales_by_film_category     |
| sakila       | sales_by_store             |
| sakila       | staff_list                 |
+--------------+----------------------------+
7 rows in set (0.01 sec)
```

### 設定されているINDEX一覧
```
mysql> select TABLE_NAME,INDEX_NAME from  information_schema.statistics where TABLE_SCHEMA='sakila';
+---------------+-----------------------------+
| TABLE_NAME    | INDEX_NAME                  |
+---------------+-----------------------------+
| actor         | PRIMARY                     |
| actor         | idx_actor_last_name         |
| address       | PRIMARY                     |
| address       | idx_fk_city_id              |
| category      | PRIMARY                     |
| city          | PRIMARY                     |
| city          | idx_fk_country_id           |
| country       | PRIMARY                     |
| customer      | PRIMARY                     |
| customer      | idx_fk_store_id             |
| customer      | idx_fk_address_id           |
| customer      | idx_last_name               |
| film          | PRIMARY                     |
| film          | idx_title                   |
| film          | idx_fk_language_id          |
| film          | idx_fk_original_language_id |
| film_actor    | PRIMARY                     |
| film_actor    | PRIMARY                     |
| film_actor    | idx_fk_film_id              |
| film_category | PRIMARY                     |
| film_category | PRIMARY                     |
| film_category | fk_film_category_category   |
| film_text     | PRIMARY                     |
| film_text     | idx_title_description       |
| film_text     | idx_title_description       |
| inventory     | PRIMARY                     |
| inventory     | idx_fk_film_id              |
| inventory     | idx_store_id_film_id        |
| inventory     | idx_store_id_film_id        |
| language      | PRIMARY                     |
| payment       | PRIMARY                     |
| payment       | idx_fk_staff_id             |
| payment       | idx_fk_customer_id          |
| payment       | fk_payment_rental           |
| rental        | PRIMARY                     |
| rental        | rental_date                 |
| rental        | rental_date                 |
| rental        | rental_date                 |
| rental        | idx_fk_inventory_id         |
| rental        | idx_fk_customer_id          |
| rental        | idx_fk_staff_id             |
| staff         | PRIMARY                     |
| staff         | idx_fk_store_id             |
| staff         | idx_fk_address_id           |
| store         | PRIMARY                     |
| store         | idx_unique_manager          |
| store         | idx_fk_address_id           |
+---------------+-----------------------------+
47 rows in set (0.00 sec)
```

### 関数一覧
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

### ストアドプロシージャ一覧
```
mysql> SHOW PROCEDURE STATUS \G
*************************** 1. row ***************************
                  Db: sakila
                Name: film_in_stock
                Type: PROCEDURE
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
                Name: film_not_in_stock
                Type: PROCEDURE
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
                Name: rewards_report
                Type: PROCEDURE
             Definer: root@localhost
            Modified: 2016-12-22 08:46:36
             Created: 2016-12-22 08:46:36
       Security_type: DEFINER
             Comment: Provides a customizable report on best customers
character_set_client: utf8
collation_connection: utf8_general_ci
  Database Collation: utf8_general_ci
3 rows in set (0.01 sec)
```

### トリガー一覧
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
*************************** 3. row ***************************
             Trigger: upd_film
               Event: UPDATE
               Table: film
           Statement: BEGIN
    IF (old.title != new.title) OR (old.description != new.description) OR (old.film_id != new.film_id)
    THEN
        UPDATE film_text
            SET title=new.title,
                description=new.description,
                film_id=new.film_id
        WHERE film_id=old.film_id;
    END IF;
  END
              Timing: AFTER
             Created: NULL
            sql_mode: STRICT_TRANS_TABLES,STRICT_ALL_TABLES,NO_ZERO_IN_DATE,NO_ZERO_DATE,ERROR_FOR_DIVISION_BY_ZERO,TRADITIONAL,NO_AUTO_CREATE_USER,NO_ENGINE_SUBSTITUTION
             Definer: root@localhost
character_set_client: utf8
collation_connection: utf8_general_ci
  Database Collation: latin1_swedish_ci
*************************** 4. row ***************************
             Trigger: del_film
               Event: DELETE
               Table: film
           Statement: BEGIN
    DELETE FROM film_text WHERE film_id = old.film_id;
  END
              Timing: AFTER
             Created: NULL
            sql_mode: STRICT_TRANS_TABLES,STRICT_ALL_TABLES,NO_ZERO_IN_DATE,NO_ZERO_DATE,ERROR_FOR_DIVISION_BY_ZERO,TRADITIONAL,NO_AUTO_CREATE_USER,NO_ENGINE_SUBSTITUTION
             Definer: root@localhost
character_set_client: utf8
collation_connection: utf8_general_ci
  Database Collation: latin1_swedish_ci
*************************** 5. row ***************************
             Trigger: payment_date
               Event: INSERT
               Table: payment
           Statement: SET NEW.payment_date = NOW()
              Timing: BEFORE
             Created: NULL
            sql_mode: STRICT_TRANS_TABLES,STRICT_ALL_TABLES,NO_ZERO_IN_DATE,NO_ZERO_DATE,ERROR_FOR_DIVISION_BY_ZERO,TRADITIONAL,NO_AUTO_CREATE_USER,NO_ENGINE_SUBSTITUTION
             Definer: root@localhost
character_set_client: utf8
collation_connection: utf8_general_ci
  Database Collation: latin1_swedish_ci
*************************** 6. row ***************************
             Trigger: rental_date
               Event: INSERT
               Table: rental
           Statement: SET NEW.rental_date = NOW()
              Timing: BEFORE
             Created: NULL
            sql_mode: STRICT_TRANS_TABLES,STRICT_ALL_TABLES,NO_ZERO_IN_DATE,NO_ZERO_DATE,ERROR_FOR_DIVISION_BY_ZERO,TRADITIONAL,NO_AUTO_CREATE_USER,NO_ENGINE_SUBSTITUTION
             Definer: root@localhost
character_set_client: utf8
collation_connection: utf8_general_ci
  Database Collation: latin1_swedish_ci
6 rows in set (0.00 sec)
```


# 参考URL
- MySQL公式ドキュメント(Sakila Sample Database)
 - https://dev.mysql.com/doc/sakila/en/
- Sakila Sample Database
 - しっかりと書かれているPDFドキュメント
 - http://downloads.mysql.com/docs/sakila-en.pdf

