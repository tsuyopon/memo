
### 単純なプロシージャ
mysqlのプロンプト上で次を実行してみる(先頭の"mysql>"はコピーしやすいように除去している)
```
DELIMITER //
CREATE PROCEDURE procedure_sqrt(IN input INT)
BEGIN
    DECLARE counter INT DEFAULT 2;
    SELECT SQRT(counter), input;
END;
//
DELIMITER ;
```

実行してみると次ようになります。
```
mysql> CALL procedure_sqrt(10);
+--------------------+-------+
| SQRT(counter)      | input |
+--------------------+-------+
| 1.4142135623730951 |    10 |
+--------------------+-------+
1 row in set (0.00 sec)

Query OK, 0 rows affected (0.00 sec)

mysql> DROP PROCEDURE procedure_sqrt;
Query OK, 0 rows affected (0.00 sec)
```

### 変数スコープの理解
- システム変数(例: @@version)
  - グローバルスコープ
  - 宣言:なし、 型:なし、設定:SET GLOBAL/SET SESSION、SELECT INTO不可、EXECUTE USING不可
- ユーザー変数(例: @var_name)
  - セッションスコープ
  - 宣言:なし、 型:なし、設定:SET、SELECT INTO可能、EXECUTE USING可能
- ローカル変数(例: DECLARE var_name INT: ストアドプロシージャ内で使う事ができる)
  - ローカルスコープ
  - 宣言:あり、 型:あり、設定:SET、SELECT INTO可能、EXECUTE USING不可
  

下記の資料がわかりやすい
- https://zigorou.hatenablog.com/entry/20110802/1312302137


### 変数宣言する
DECLARE分はすべてBEGINの直後に記述しなければならず、ルーチンの途中に書くことはできません。
```
#DECLARE 変数名 データ型;
DECLARE created_date DATETIME;
```

### ストアドプロシージャ一覧を表示する
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
3 rows in set (0.00 sec)
```

### ストアドプロシージャの定義を確認する
以下はストアドプロシージャのサンプルにもなる。
```
mysql> SHOW CREATE PROCEDURE sakila.rewards_report \G
*************************** 1. row ***************************
           Procedure: rewards_report
            sql_mode: STRICT_TRANS_TABLES,STRICT_ALL_TABLES,NO_ZERO_IN_DATE,NO_ZERO_DATE,ERROR_FOR_DIVISION_BY_ZERO,TRADITIONAL,NO_AUTO_CREATE_USER,NO_ENGINE_SUBSTITUTION
    Create Procedure: CREATE DEFINER=`root`@`localhost` PROCEDURE `rewards_report`(
    IN min_monthly_purchases TINYINT UNSIGNED
    , IN min_dollar_amount_purchased DECIMAL(10,2) UNSIGNED
    , OUT count_rewardees INT
)
    READS SQL DATA
    COMMENT 'Provides a customizable report on best customers'
proc: BEGIN

    DECLARE last_month_start DATE;
    DECLARE last_month_end DATE;

    
    IF min_monthly_purchases = 0 THEN
        SELECT 'Minimum monthly purchases parameter must be > 0';
        LEAVE proc;
    END IF;
    IF min_dollar_amount_purchased = 0.00 THEN
        SELECT 'Minimum monthly dollar amount purchased parameter must be > $0.00';
        LEAVE proc;
    END IF;

    
    SET last_month_start = DATE_SUB(CURRENT_DATE(), INTERVAL 1 MONTH);
    SET last_month_start = STR_TO_DATE(CONCAT(YEAR(last_month_start),'-',MONTH(last_month_start),'-01'),'%Y-%m-%d');
    SET last_month_end = LAST_DAY(last_month_start);

    
    CREATE TEMPORARY TABLE tmpCustomer (customer_id SMALLINT UNSIGNED NOT NULL PRIMARY KEY);

    
    INSERT INTO tmpCustomer (customer_id)
    SELECT p.customer_id
    FROM payment AS p
    WHERE DATE(p.payment_date) BETWEEN last_month_start AND last_month_end
    GROUP BY customer_id
    HAVING SUM(p.amount) > min_dollar_amount_purchased
    AND COUNT(customer_id) > min_monthly_purchases;

    
    SELECT COUNT(*) FROM tmpCustomer INTO count_rewardees;

    
    SELECT c.*
    FROM tmpCustomer AS t
    INNER JOIN customer AS c ON t.customer_id = c.customer_id;

    
    DROP TABLE tmpCustomer;
END
character_set_client: utf8
collation_connection: utf8_general_ci
  Database Collation: utf8_general_ci
1 row in set (0.00 sec)
```

確認方法としては次のようにinformation_schema.ROUTINESテーブルを参照する方法がある(上記とは別のルーチンだが参考までに載せておく)
```
mysql> SELECT ROUTINE_DEFINITION FROM information_schema.ROUTINES WHERE ROUTINE_NAME = 'film_in_stock' AND ROUTINE_TYPE = 'PROCEDURE';
+--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
| ROUTINE_DEFINITION                                                                                                                                                                                           |
+--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
| BEGIN
     SELECT inventory_id
     FROM inventory
     WHERE film_id = p_film_id
     AND store_id = p_store_id
     AND inventory_in_stock(inventory_id);

     SELECT FOUND_ROWS() INTO p_film_count;
END |
+--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
1 row in set (0.01 sec)
```

上記のテーブルではcollateや文字コードなどの全体的な設定もあるので一度覗いてみるとよい。
```
mysql> SELECT * FROM information_schema.ROUTINES WHERE ROUTINE_NAME = 'rewards_report' AND ROUTINE_TYPE = 'PROCEDURE';
```


### プロシージャーコールを呼び出す
例えば、次のプロシージャの定義を確認してみます。
```
mysql> SHOW CREATE PROCEDURE sakila.film_in_stock \G
*************************** 1. row ***************************
           Procedure: film_in_stock
            sql_mode: STRICT_TRANS_TABLES,STRICT_ALL_TABLES,NO_ZERO_IN_DATE,NO_ZERO_DATE,ERROR_FOR_DIVISION_BY_ZERO,TRADITIONAL,NO_AUTO_CREATE_USER,NO_ENGINE_SUBSTITUTION
    Create Procedure: CREATE DEFINER=`root`@`localhost` PROCEDURE `film_in_stock`(IN p_film_id INT, IN p_store_id INT, OUT p_film_count INT)
    READS SQL DATA
BEGIN
     SELECT inventory_id
     FROM inventory
     WHERE film_id = p_film_id
     AND store_id = p_store_id
     AND inventory_in_stock(inventory_id);

     SELECT FOUND_ROWS() INTO p_film_count;
END
character_set_client: utf8
collation_connection: utf8_general_ci
  Database Collation: utf8_general_ci
1 row in set (0.00 sec)

```

上記の定義により1番目、２番目はINで、３番目はOUTとなります。
```
mysql> CALL sakila.film_in_stock(1, 1, @out);
+--------------+
| inventory_id |
+--------------+
|            1 |
|            2 |
|            3 |
|            4 |
+--------------+
4 rows in set (0.09 sec)

Query OK, 1 row affected (0.09 sec)
```

なお、outにインサートされた結果を確認するにはSELECTを使うだけです。
```
mysql> SELECT @out;
+------+
| @out |
+------+
|    4 |
+------+
1 row in set (0.00 sec)
```

### ストアドプロシージャの削除
```
mysql> DROP PROCEDURE procedure_name;
```

### プロシージャのデバッグする

SHOW PROCEDURE CODEというものが存在するようだ。実行された動作がわかるらしい
- https://dev.mysql.com/doc/refman/5.6/ja/show-procedure-code.html

自分の環境ではビルドオプション(--with-debug)が指定されておらずうまく動作しなかった。
```
mysql> SHOW PROCEDURE CODE sakila.film_in_stock;
ERROR 1289 (HY000): The 'SHOW PROCEDURE|FUNCTION CODE' feature is disabled; you need MySQL built with '--with-debug' to have it working
```
