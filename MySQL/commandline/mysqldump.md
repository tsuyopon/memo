# 概要
mysqldumpコマンドについてよく使うコマンドをまとめておくページです。
コマンドのサンプルではユーザーはrootと指定している。

# 詳細

#### 全データベースのダンプを行う
```
$mysqldump -u root -p -x --all-databases >  allbackup.`date +%Y%m%d.%H%M`.dump
```

以下にオプションについて記す。
- 「-x」は，テーブルのロックの指定であり参照系のクエリは発行できるが、更新系のクエリは発行できない。
- 「-F」は，ログの切替(Flash)の実施である。 
- 「--all-databases」は，データベース全体のバックアップの指定である。

### 特定のデータベースのダンプを行う
MySQL上のデータをダンプするには下記に示すようなコマンドを実行する。
- あるDB(database1	)のダンプを行う場合
```
$mysqldump -u root -p -x --databases database1 >  backup.`date +%Y%m%d.%H%M`.dump
```
- 複数のデータベース(以下の例ではdatabase1, database2)をダンプしたい場合は以下の様にします。
```
$mysqldump -u root -p -x --databases database1 database2 >  backup.`date +%Y%m%d.%H%M`.dump
```

### 特定のテーブルのダンプを行う
特定のデータベース(database1)の中のtable1とtable2をバックアップしたい場合
```
$mysqldump -u root -p -x --databases database1 table1 table2 >  backup.`date +%Y%m%d.%H%M`.dump
```

### データ定義のみ欲しい場合
no-dataオプションを付与するとデータの入っていない空のデータベースをダンプします。
```
$mysqldump -u root -p --all-databases -–no-data >  backup.`date +%Y%m%d.%H%M`.dump
```

### mysqlのダンプファイルからのリストア
ダンプされたファイルからリストアするには下記の様なコマンドでダンプから流し込み処理を行う
```
$mysqldump -u root -ppassword < allbackup.dump
```

### ストアドプロシージャやFUNCTIONを含めてmysqldumpを行う
mysqldumpはtriggerなどはデフォルトで含むようだが、ストアドプロシージャやfunctionは含まれないらしい。
--routinesオプションを付与することでこれらを含めることが可能となる。

### Innodbテーブルのバックアップの場合
データベース中が全てInnodbのテーブルしか存在しない場合に限り、single-transactionを指定すると一貫性を保持したバックアップを取得することができます。
次のオプションを付与することで、ダンプを1トランザクション内で行うことによってテーブルをロックせずとも整合性を保つことができるようになります。
```
--single-transaction
```
lock-all-tablesとsingle-transactionは同時に利用する事が出来ません

### ダンプを開始する前にMySQLサーバのログファイルをフラッシュします
ダンプを始める前にバイナリログをフラッシュして新しいファイルを作ります。
```
--flush-logs
```

### バイナリログファイルの名前と場所を出力に書き込む 
バイナリログファイルの名前と場所を出力に書き込む
master-dataの値が2の場合、CHANGE MASTER TOステートメントはSQLコメントとして書き込まれます。
```
--master-data=2
```

- https://dev.mysql.com/doc/refman/5.6/ja/mysqldump.html#option_mysqldump_master-data

### mysqldumpの実行結果にdrop databaseを含めておきたい場合
次のオプションを付加しておくと良いらしい
```
--add-drop-database
```

# 参考URL
- mysqldump公式リファレンス
  - https://dev.mysql.com/doc/refman/5.6/ja/mysqldump.html
- DBAのためのmysqldumpのtips 25選
  - https://yakst.com/ja/posts/1355
