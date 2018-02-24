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
