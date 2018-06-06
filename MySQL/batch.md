# 概要
シェルスクリプトからmysqlを実行する方法などについて

# 詳細

### シェルスクリプトから実行するサンプル

例として次のように引数を1つ受け取るシェルスクリプトを作成します。
```
$ cat test.sh 
#!/bin/sh
SCHEMA=$1
sql="SELECT table_name, column_name FROM information_schema.columns WHERE table_schema = '$SCHEMA' LIMIT 3;"
mysql -uroot information_schema -e "$sql"
```

引数に$SCHEMAの情報を与えてあげることでテーブルを表示します。
```
$ ./test.sh information_schema
+----------------+----------------------+
| table_name     | column_name          |
+----------------+----------------------+
| CHARACTER_SETS | CHARACTER_SET_NAME   |
| CHARACTER_SETS | DEFAULT_COLLATE_NAME |
| CHARACTER_SETS | DESCRIPTION          |
+----------------+----------------------+
```

### ヒアドキュメントやSOURCEコマンドを使ったsqlの外部読み込み
ヒアドキュメント及びSOURCEを使った外部のsql読み込みのサンプルを示します。
```
$ cat test.sh 
#!/bin/sh
SCHEMA=$1
sql="SELECT table_name, column_name FROM information_schema.columns WHERE table_schema = '$SCHEMA' LIMIT 3;"
mysql -uroot information_schema <<EOF

BEGIN;

\! echo "### STEP1: Execute from inside shellscript";
$sql

\! echo "";
\! echo "### STEP2: Execute from outside file using SOURCE COMMAND";
SOURCE display.sql 

ROLLBACK;
-- COMMIT;
EOF
```

引数を指定して実行してみましょう。
```
$ ./test.sh information_schema
### STEP1: Execute from inside shellscript
table_name	column_name
CHARACTER_SETS	CHARACTER_SET_NAME
CHARACTER_SETS	DEFAULT_COLLATE_NAME
CHARACTER_SETS	DESCRIPTION

### STEP2: Execute from outside file using source
table_name	column_name
CHARACTER_SETS	CHARACTER_SET_NAME
```


