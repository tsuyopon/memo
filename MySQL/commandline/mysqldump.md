# 概要
mysqldumpコマンドについて

# 詳細

### mysqlのダンプファイルの作成
MySQL上のデータをダンプするには下記に示すようなコマンドを実行する。
- あるDBのダンプ
```
$mysqldump -uユーザ名 -p -x -F --databases <DB> >  backup.`date +%Y%m%d.%H%M`.dump
```
- 複数のデータベース(以下の例ではDB1, DB2)をダンプしたい場合は以下の様にします。
```
$mysqldump -uユーザ名 -p -x -F --databases DB1 DB2 >  backup.`date +%Y%m%d.%H%M`.dump
```

#### 全データベースのダンプを行う
```
$mysqldump -uユーザ名 -p -x -F --all-databases >  allbackup.`date +%Y%m%d.%H%M`.dump
```

以下にオプションについて記す。
-x」は，テーブルのロックの指定である。 「-F」は，ログの切替(Flash)の実施である。 「--all-databases」は，データベース全体のバックアップの指定である。


### mysqlのダンプファイルからのリストア
ダンプされたファイルからリストアするには下記の様なコマンドを実行する。
```
$mysqldump -uユーザ名 -pパスワード < allbackup.dump
```
