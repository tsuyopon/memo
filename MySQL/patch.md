# 概要
mysqlのパッチファイルの作り方に関するTIPSなど


# 詳細

### パッチファイル書式
DBに対して操作する場合には、あらかじめ何が起こるのかわからないのでロールバック可能なようにmysqldumpコマンドを取得しておくのが一般的である。  
これはパッチファイルには含めなくても良い
```
mysqldump -umyuser -h localhost --set-gtid-purged=OFF --single-transaction -p mydatabase > mytable`date +%Y%m%d`.sql
```

上記オプションで指定されるgtidについてはMySQL5.6移行で追加された機能とのこと
- http://d.hatena.ne.jp/hiroi10/20130308/1362765495

xxxx.sqlといった名前で次のようなものを準備する。コメントはハイフン2つの後にスペースが必要
```
USE mydatabase

-- -------------------------------------------
-- 1. XXXXの確認
-- -------------------------------------------
\! echo "適用前のXXXX確認"
SELECT * FROM XXXX;

\! echo "適用"
UPDATE mydatabase.XXXX SET hoge=1;

\! echo "適用後のXXXX確認"
SELECT ROW_COUNT();
SELECT * FROM XXXX;

-- -------------------------------------------
-- 2. YYYYの確認
-- -------------------------------------------
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

