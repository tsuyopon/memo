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



# 参考URL

- Sakila Sample Database
 - しっかりと書かれているPDFドキュメント
 - http://downloads.mysql.com/docs/sakila-en.pdf
