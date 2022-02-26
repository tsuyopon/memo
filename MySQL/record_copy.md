# 概要
MySQLのレコードをコピーする方法について

# 詳細

### 違うテーブルに行を複製する
以下の例では、レコードのprimary keyをduplicatieしないよう場合で、test, test2のテーブル構造が同じ場合のみ利用できる。
```
INSERT INTO test SELECT * FROM test2 WHERE id= $id;
```

### 同一テーブルから要素を抽出して複製する。
レコードを追加する際に他の要素がauto incrementや自動的な時刻更新を行う場合には、特定の要素だけINSERTします。
その場合の例を以下に示します。
```
INSERT INTO tbl (name,age) (SELECT name,age FROM tbl WHERE id = 2);
```

上記の例では、複数のレコード結果があると、全て挿入されます。

### 同じテーブルにレコードを複製する
データを加工してからデータをINSERTする場合にはCREATE TEMPORARY TABLEで一時的なテーブルを作成します。
```
CREATE TEMPORARY TABLE tmp_test LIKE test;
INSERT INTO tmp_test SELECT * FROM test WHERE id= id ;
UPDATE tmp_test set id = (SELECT MAX(id) FROM test)+1;
INSERT INTO test SELECT * FROM tmp_test;
DROP TABLE tmp_test;
```

CREATE TEMPORARY TABLEは利用しているセッション内だけで有効なテーブルを作成し、セッションが閉じた際に自動的にテーブルが削除されます。

### テンポラリテーブルを作成して、プライマリキーのカラム(id)を削除してINSERTする。idは0を指定する。
テンポラリテーブルからidフィールドをdropして、idを0として、それ以外をテンポラリテーブルからINSERTするようにすればプライマリキーであるidも生成される。
```
CREATE TEMPORARY TABLE tmp SELECT * FROM tablename WHERE id=273;
ALTER TABLE tmp drop id;
INSERT INTO tablename SELECT 0,tmp.* FROM tmp;
DROP TABLE tmp;
```
