### 簡単なデータを生成する
```
$ sqlite test.db
sqlite> CREATE TABLE test(id integer, name text);
sqlite> .import import.sql test
sqlite> select * from test;
1|taro
2|jiro
3|saburo
4|siro
5|goro
```