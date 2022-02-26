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

### コマンドライン経由で出力を取得する
以下の2つのコマンドは出力が異なりますので注意してください。

以下の場合には、通常のコマンドラインからSQL文を入力した内容と同様の出力を返します。
```
$ mysql -u root -p sakila -e "SELECT * FROM rental;"
```

出力内容をTSV形式として出力します。
```
$ mysql -u root -p sakila -e "SELECT * FROM rental;" > test.tsv
```
