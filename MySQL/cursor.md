# 概要
MySQLのカーソルについてまとめたメモ

# 詳細

### 簡単なカーソルのサンプル
カーソルは変数宣言、カーソル宣言、ハンドラ宣言の順に記述しないとエラーになるようなので注意が必要です。
次のSQL文はsakilaデータベースで簡単に使えるサンプルです。
```
use sakila;
DROP PROCEDURE IF EXSITS curdemo;

delimiter //
CREATE PROCEDURE curdemo()
BEGIN
  DECLARE done INT DEFAULT 1;
  DECLARE get_city_id INT;
  DECLARE get_city VARCHAR(40);

  DECLARE cur1 CURSOR FOR SELECT city_id, city FROM city WHERE country_id=82;

  -- 02000はカーソルでループして処理する対象レコードが存在しなくなったらという意味。その時にdoneは0にセットされる。
  DECLARE CONTINUE HANDLER FOR SQLSTATE '02000' SET done = 0;

  OPEN cur1;

  WHILE done DO
    FETCH cur1 INTO get_city_id, get_city;
    IF done THEN
      SELECT get_city_id, get_city;
    END IF;
  END WHILE;

  CLOSE cur1;
END
//
delimiter ;

CALL curdemo();
DROP PROCEDURE curdemo;
```

### ハンドラの定義について
ハンドラ宣言は次の書式となっている。
```
DECLARE <handler_type> HANDLER FOR <condition_value>[,...]  <statement>
```

- handler_type
  - CONTINUE: ハンドラを実行した後に実行制御を元の場所に戻す。
  - EXIT: ハンドラを実行してプログラムを終了する

- condition_value
  - condition_name: DECLARE ... CONDITIONで宣言したコンディション名を指定します。
  - SQLWARNING: 01で始まるSQLSTATEをキャッチします。
  - NOT FOUND: 02 で始まるSQLStateをキャッチします。
  - SQLEXCEPTION: 01, 02 以外で始まるSQLStateをキャッチします。
  - mysql_error_code: 特定のMySQL固有エラーコードをキャッチします。
  - SQLSTATE [value] sqlstate_value: 特定のSQLSTATEをキャッチします。(valueには'02000'などが指定される)


### SQLSTATEの番号について

- https://dev.mysql.com/doc/refman/5.6/ja/signal.html#signal-condition-information-items


### エラーを扱う
たとえば、エラー時などにはIF,THENなどに次のようなSQL文を埋め込むことで異常なシグナル発行させることができる。
```
SIGNAL SQLSTATE '45001' SET MESSAGE_TEXT = 'ERROR OCCURED';
```
シグナル番号については次を参考にすること


### シグナルを発行する場合

シグナルは先頭２桁で次のような意味をもちます。
- クラス = '00' (成功)
- クラス = '01' (警告)
- クラス = '02' (見つからない)
- クラス > '02' (例外)
- クラス = '40'

詳細は以下の公式資料を確認してください。
- https://dev.mysql.com/doc/refman/5.6/ja/signal.html#signal-effects

### 各種エラーコード(02000, 45000など)の意味が知りたい
各種エラーコード(02000, 45000など)については以下の資料を参考にすること
- https://dev.mysql.com/doc/refman/5.6/ja/error-messages-server.html
