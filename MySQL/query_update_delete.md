# 概要
INSERT分、UPDATE文やDELETE文について

# 詳細

### 特定の取得したフィールドをインクリメントする
次のような感じで簡単にインクリメントすることができる。
```
UPDATE mytable SET logins = logins + 1 WHERE id = 12
```
- https://stackoverflow.com/questions/2762851/increment-a-database-field-by-1

### 古いテーブルのレコードを新しいテーブルにコピーする
```
mysql> SELECT * INTO oldtable FROM newtable;
```

### UPDATEする際にテーブルを結合した情報をSETへの変更条件として渡したい
たとえば、AテーブルとBテーブルを結合して、Bテーブルの値がxxxの時だけAテーブルの特定の値を更新したいなどの際に利用します。

書式は次の通りです。「LEFT JOIN」の箇所は適宜「INNER JOIN」等に変更して問題ありません。
```
UPDATE テーブルA
LEFT JOIN テーブルB ON 結合条件
SET カラム名 = 値
WHERE 更新条件
```

以下は上記書式に則ったサンプルです。
```
UPDATE user_main a
LEFT JOIN user_sub b
ON a.user_id = b.user_id
SET a.name = "new name"
WHERE b.type = 2;
```

- http://blog.higty.xyz/archives/466/


### DELETEする際にテーブルを結合した情報を削除条件としたい
以下はサンプルです
```
DELETE entries FROM entries 
JOIN authors ON entries.author_id = authors.id
WHERE authors.name = 'labocho';
```

### IGNOREキーワード
挿入、更新、削除が1件もできないと通常はエラーとなりますが、IGNOREを指定すると対象が存在しなくても処理が成功するようになります。
```
INSERT IGNORE 〜
UPDATE IGNORE 〜
DELETE IGNORE 〜
```

# 参考URL
- 参考
  - https://dev.mysql.com/doc/refman/5.6/ja/delete.html#idm140513790680208
