# 概要
mysqlのパッチファイルの作り方に関するTIPSなど

# 詳細

### 安全にパッチの適用を行う
START TRANSACTIONを最初に実行して確認します。
最初はCOMMITは実行せずに、期待通りの結果かを確認するSELECT文などを表示するようにするのが良いでしょう。

問題ないことを確認出来次第、最後のROLLBACKを外して実行します。
```
USE mydatabase

START TRANSACTION;

SELECT * FROM XXXX;
UPDATE mydatabase.XXXX SET hoge=1;
SELECT * FROM XXXX;

ROLLBACK;

-- 問題なければROLLBACKをコメントにして、次のCOMMITを有効にする
-- COMMIT;
```

### パッチファイル書式
DBに対して操作する場合には、あらかじめ何が起こるのかわからないのでロールバック可能なようにmysqldumpコマンドを取得しておくのが一般的である。  
これはパッチファイルには含めなくても良い
```
mysqldump -umyuser -h localhost --set-gtid-purged=OFF --single-transaction -p mydatabase > mytable`date +%Y%m%d`.sql
```

上記オプションで指定されるgtidについてはMySQL5.6移行で追加された機能とのこと
- http://d.hatena.ne.jp/hiroi10/20130308/1362765495

xxxx.sqlといった名前で次のようなものを準備する。コメントはハイフン2つの後にスペースが必要です。
「\!」はsystemコマンドに相当して、mysqlシェル上でコマンドを実行することができます。
```
USE mydatabase

-- -------------------------------------------
-- 1. XXXXの確認
-- -------------------------------------------
\! echo ""
\! echo "適用前のXXXX確認"
SELECT * FROM XXXX;

\! echo ""
\! echo "適用"
UPDATE mydatabase.XXXX SET hoge=1;

\! echo ""
\! echo "適用後のXXXX確認"
SELECT ROW_COUNT();
SELECT * FROM XXXX;

-- -------------------------------------------
-- 2. YYYYの確認
-- -------------------------------------------
\! echo ""
\! echo "YYYYの確認"
SELECT * FROM YYYY;
```

sqlファイルの適用方法は次のように流し込みをするだけです。
```
$ mysql -u root -p < xxxx.sql
```

mysqlプロンプトからも流し込むことができます。どっとの前に\が必要であることに注意。
```
mysql> \. test.sql
```

### UPDATEやDELETEなどで更新適用された件数を知りたい場合

```
SELECT ROW_COUNT();
```

なお、ROW_COUNT()はあくまでも適用結果なので、SELECTで表示されたレコード件数は知ることはできない。SELECTの場合には-1などがクエリ結果として帰って来る模様。


### 値を一時変数に格納したい場合
次のように「@xxx:=」を使うと良い。ただし、一時変数はmysql接続が切れると初期化されるので
```
mysql> SELECT @id:=city_id FROM city WHERE city LIKE "Kabul";
+--------------+
| @id:=city_id |
+--------------+
|          251 |
+--------------+
1 row in set (0.00 sec)

mysql> SELECT @id;
+------+
| @id  |
+------+
|  251 |
+------+
1 row in set (0.00 sec)

mysql> SELECT * FROM city WHERE city_id=@id;
+---------+-------+------------+---------------------+
| city_id | city  | country_id | last_update         |
+---------+-------+------------+---------------------+
|     251 | Kabul |          1 | 2006-02-15 04:45:25 |
+---------+-------+------------+---------------------+
1 row in set (0.00 sec)
```

なお、複数のレコードが取得できる場合には最後の値が格納されるので注意が必要です。うまい方法ないのかな?
```
mysql> SELECT @id:=city_id FROM city WHERE city LIKE "Kam%";
+--------------+
| @id:=city_id |
+--------------+
|          256 |
|          257 |
|          258 |
|          259 |
+--------------+
4 rows in set (0.00 sec)

mysql> SELECT @id;
+------+
| @id  |
+------+
|  259 |
+------+
1 row in set (0.00 sec)	
```


