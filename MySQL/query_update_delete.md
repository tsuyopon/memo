# 概要
UPDATE文やDELETE文について

# 詳細

### UPDATEする際にテーブルを結合した情報をSETへの変更情報として渡したい
書式は次の通り
```
UPDATE テーブルA
LEFT JOIN テーブルB ON 結合条件
SET カラム名 = 値
WHERE 更新条件
```

以下は上記書式に則ったサンプル
```
UPDATE user_main a
LEFT JOIN user_sub b
ON a.user_id = b.user_id
SET a.name = "new name"
WHERE b.type = 2;
```

- http://blog.higty.xyz/archives/466/

### 

```
DELETE entries FROM entries 
JOIN authors ON entries.author_id = authors.id
WHERE authors.name = 'labocho';
```


- 参考
  - https://dev.mysql.com/doc/refman/5.6/ja/delete.html#idm140513790680208
