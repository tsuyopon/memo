# 概要
mysqlコマンドについて

# 詳細

### サーバやポートを指定する
```
$ mysql -u ユーザ名 -D 操作したDB名 -p -h example.com -P 3306
```

### mysqlのファイル(.sql)を読み込む
```
$ mysql -u ユーザ名 -D 操作したDB名 -p < xxxxx.sql
```

### SSLによりmysqlに接続する
```
$ mysql -h <サーバ> -u <ユーザ> -p --ssl
```

### SSL暗号化通信を使用しない接続を明示的に行う
```
$ mysql -h <サーバ> -u <ユーザ> -p --skip-ssl
```

### コマンドライン経由でTSV出力を取得する
以下の2つのコマンドは出力が異なりますので注意してください。

以下の場合には、通常のコマンドラインからSQL文を入力した内容と同様の出力を返します。
```
$ mysql -u root -p sakila -e "SELECT * FROM rental;"
```

出力内容をTSV形式として出力します。
```
$ mysql -u root -p sakila -e "SELECT * FROM rental;" > test.tsv
```

### コマンドライン経由でTSV出力を取得した際にヘッダ情報を付与しない
ファイルへ出力すると基本的には1行目にヘッダ情報が付与されます。
```
$ mysql -u root -p --protocol=tcp sakila -e "SELECT * FROM rental LIMIT 1;" > log
$ cat log 
rental_id	rental_date	inventory_id	customer_id	return_date	staff_id	last_update
1	2005-05-24 22:53:30	367	130	2005-05-26 22:04:30	1	2006-02-16 06:30:53
```

この情報が不要な場合にはNオプションを付与することでヘッダ情報を除外することができます。
```
$ mysql -u root -p --protocol=tcp -N sakila -e "SELECT * FROM rental LIMIT 1;" > log2
$ cat log2
1	2005-05-24 22:53:30	367	130	2005-05-26 22:04:30	1	2006-02-16 06:30:53
```
