# 概要
SQLiteはサーバとしてではなくアプリケーションに組み込んで利用される軽量データベースです。 以下に主な特徴を示します。
- Linux, FreeBSD, Windowsでも動作するマルチプラットフォームである
- サーバとしては動作しない
- 中小規模のサイトに適している
- 導入、設定が容易
- DBへの複数書き込みをするとエラーになる

メリットについては以下の記事を見るといいかもしれません。
- SQLiteを使うべき10の理由と5つのデメリット
  - http://www.cpa-lab.com/tech/046

# 詳細

## インストール
aptitudeが使える環境であれば次のコマンドで一発です。
```
$ aptitude insgtall sqlite3
```

## 基本データ型について
以下の5つのデータ型のみが存在します。
- NULL, INTEGER, REAL, TEXT, BLOB
VARCHAR(10)などの有効桁数制限は無い。CREATE TABLE時に指定可能だが、意味を成さない。VARCHARなどの型はSQLite側で自動的にTEXT等のデータ型に変換されることになります。


以下はサンプルスキーマですが問題ないことを確認しています。
```
CREATE TABLE ddd (
  id INTEGER PRIMARY KEY,
  starttime INTEGER NOT NULL,
  rundist INTEGER NOT NULL,
  runtime INTEGER NOT NULL,
  member TEXT,
  others TEXT
);
```

- SeeAlso
  - SQLiteで利用可能なデータ型
    - http://www.dbonline.jp/sqlite/type/
  - Datatypes In SQLite Version 3
    - http://www.sqlite.org/datatype3.html

## sqlite3コマンドで接続してみる
以下の様にしてsqliteで生成したDBに対してコマンドラインからインタラクティブに操作を行うことができるようになります。
```
$ sqlite3 /home/tsuyoshi/work/data.db
SQLite version 3.5.9
Enter ".help" for instructions
sqlite> 
```
尚、上記で指定されたパスにdbが存在しない場合には新規で作られることになります。

SQLiteのDBの拡張子には一般的に.dbや.sqlite3などが多いですが、特に決まりはありません。

とりあえず試してみたければ次のようにサンプルスキーマ作成及びinsertなどを行ってみるといいかもしれません。
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

接続しているデータベースを切断するにはexitを実行します。
```
sqlite> .exit
```

## 接続中のデータベースを確認する
「.databases」により接続中のデータベースを確認することができます。
```
sqlite> .databases
seq  name             file
---  ---------------  ----------------------------------------------------------
0    main             /home/tsuyoshi/work/aaa.db
```
上記の項目は以下の意味があります。

```
項目	意味	備考
seq	    単なる番号	
name	単なるデータベース名	接続した時点で常にmainになります
file	データベースが格納されているファイル名	
```


## sqliteのドットコマンドについて
sqliteはドットコマンドを使ってインタラクティブに制御します。ここでは様々なドットコマンドについてまとめます

### .help: ヘルプを出力したい
```
sqlite> .help
.help
.bail ON|OFF           Stop after hitting an error.  Default OFF
.databases             List names and files of attached databases
.dump ?TABLE? ...      Dump the database in an SQL text format
.echo ON|OFF           Turn command echo on or off
.exit                  Exit this program
.explain ON|OFF        Turn output mode suitable for EXPLAIN on or off.
.header(s) ON|OFF      Turn display of headers on or off
.help                  Show this message
.import FILE TABLE     Import data from FILE into TABLE
.indices TABLE         Show names of all indices on TABLE
.load FILE ?ENTRY?     Load an extension library
.mode MODE ?TABLE?     Set output mode where MODE is one of:
csv      Comma-separated values
column   Left-aligned columns.  (See .width)
html     HTML <table> code
insert   SQL insert statements for TABLE
line     One value per line
list     Values delimited by .separator string
tabs     Tab-separated values
tcl      TCL list elements
.nullvalue STRING      Print STRING in place of NULL values
.output FILENAME       Send output to FILENAME
.output stdout         Send output to the screen
.prompt MAIN CONTINUE  Replace the standard prompts
.quit                  Exit this program
.read FILENAME         Execute SQL in FILENAME
.schema ?TABLE?        Show the CREATE statements
.separator STRING      Change separator used by output mode and .import
.show                  Show the current values for various settings
.tables ?PATTERN?      List names of tables matching a LIKE pattern
.timeout MS            Try opening locked tables for MS milliseconds
.timer ON|OFF          Turn the CPU timer measurement on or off
.width NUM NUM ...     Set column widths for "column" mode
```

### .show: sqliteに関する設定を表示する。
```
.showコマンドを使ってみる
sqlite> .show
     echo: off
  explain: off
  headers: off
     mode: list
nullvalue: ""
   output: stdout
separator: "|"
    width:
```

### .mode: selectした際などの出力方法を変更してくれます。
次の8種類が存在します。

- list(デフォルト)
- line
- column
- csv
- html
- insert
- tabs
- tcl

それぞれ出力サンプルを載せます。
- list(デフォルトのモード)
```
sqlite> .mode list
sqlite> select * from test;
AAAA|BBBB
100|BBBB
```
- line
```
sqlite> .mode line
sqlite> select * from test;
   id = AAAA
 name = BBBB

   id = 100
 name = BBBB
```
- column
```
sqlite> .mode column
sqlite> select * from test;
AAAA        BBBB
100         BBBB
```
- csv
```
sqlite> .mode csv
sqlite> select * from test;
AAAA,BBBB
100,BBBB
```
- html
```
sqlite> .mode html
sqlite> select * from test;
<TR><TD>AAAA</TD>
<TD>BBBB</TD>
</TR>
<TR><TD>100</TD>
<TD>BBBB</TD>
</TR>
```
- insert
```
sqlite> select * from test;
INSERT INTO table VALUES('AAAA','BBBB');
INSERT INTO table VALUES(100,'BBBB');
```
- tabs
```
sqlite> .mode tabs
sqlite> select * from test;
AAAA    BBBB
100     BBBB
```
- tcl
```
sqlite> .mode tcl
sqlite> select * from test;
"AAAA"  "BBBB"
"100"   "BBBB"
```

### .databases: データベースの場所を表示します
```
sqlite> .databases
seq  name             file
---  ---------------  ----------------------------------------------------------
0    main             /home/tsuyoshi/test.db
```

### .dump: データベースやテーブル情報をダンプする
- データベースを指定してdumpする
```
sqlite> .dump main
BEGIN TRANSACTION;
COMMIT;
```
- テーブルを指定してdumpする
```
sqlite> .dump test
BEGIN TRANSACTION;
CREATE TABLE test(id integer(8), name varchar(255));
INSERT INTO "test" VALUES('AAAA','BBBB');
INSERT INTO "test" VALUES(100,'BBBB');
COMMIT;
sqlite> .dump personal
BEGIN TRANSACTION;
CREATE TABLE personal (id, name);
COMMIT;
```

### .echo: 実行したSQL文を画面上に表示する
- 実行したSQLを復唱しない(デフォルト) 
```
sqlite> .echo OFF
.echo OFF                        // 元々復唱設定となっている例なので、ここでは復唱されるが、これ以降はSQL文を実行しても復唱されない
sqlite> select * from test;
AAAA|BBBB
100|BBBB
```
- 実行したSQLを復唱する
```
sqlite> .echo ON
sqlite> select * from test;
select * from test;              // 実行したSQL文が復唱される。
AAAA|BBBB
100|BBBB
```

### .explain: field名称を出力する
- .explain: OFF
```
sqlite> .explain OFF
sqlite> select * from test;
AAAA|BBBB
100|BBBB
```
- .explain: ON
```
sqlite> .explain ON
sqlite> select * from test;
id    name                            // field名が表示されるようになった
----  -------------
AAAA  BBBB
100   BBBB
```

### .import: ファイル中からデータをインポートする
```
$ cat aaa.txt
1|text1
2|text2
3|text3
$ sqlite3 test.db
sqlite> select * from test;
AAAA|BBBB
100|BBBB
sqlite> .import aaa.txt test
sqlite> select * from test;
AAAA|BBBB
100|BBBB
1|text1                       // これ以降の3行がaaa.txtよりtestテーブルにインポートされた
2|text2
3|text3
```

### .output: SQLの実行結果を指定したファイルに出力する
```
sqlite> .output output.txt
sqlite> select * from test;
sqlite> .quit
$ cat output.txt
AAAA|BBBB
100|BBBB
1|text1
2|text2
3|text3
10|
```

### .prompt:自分が好きなpromptに変更する
```
sqlite> .prompt "mysqlite>"
mysqlite>                             // 「mysqlite>」に変更された
```

### .header: カラム名を出力するようになる
```
sqlite> .header ON
sqlite> select * from test;
id|name                          // この行はカラム名
AAAA|BBBB
100|BBBB
1|text1
2|text2
3|text3
```

## データベースを新規作成する
以下のコマンドを実行すると、DBが存在しない場合には新規作成します。
尚、新規で上記ファイルが作成されると「main」という名前のDBが作成されます。 1つのファイルには、複数のDBを作成することも可能です。
```
$ sqlite3 /path/to/<DB名>
```

## データベースを削除する
ファイルベースなので、そのファイルに含まれる"全ての"DBを削除する場合にはrmを利用しても問題ありません。
```
$ rm <DB名>
```

## 他のデータベースにアタッチする
test.dbとtest2.dbというDBが存在し、予めtest.dbにアタッチしているものとして、他のデータベースtest2.dbにもアタッチしたい場合には以下の様にします。
```
sqlite> attach database './test2.db' as 'sample';
sqlite> .database
seq  name             file
---  ---------------  ----------------------------------------------------------
0    main             /home/tsuyoshi/test.db
2    sample           /home/tsuyoshi/./test2.db
```
test2.dbのnameをsampleと指定しているのはtest.db、test2.db共に名称がmainというデータベース名だからです。
また、attachされたデータベースはseqが2から順番に割り当てられます。

## テーブルを作成する例
以下はテーブル作成〜データ挿入・参照の簡単な例です。 SQLiteではデータ型を指定する、指定しないのは使用者が自由に選択できます。

- データ型指定の例
```
sqlite> create table test(one varchar(10), two smallint);
sqlite> insert into test values('Hello', 10);
sqlite> select * from test;
```
- データ型未指定の例
```
sqlite> create table test(one, two);
sqlite> insert into test values('Hello', 10);
sqlite> select * from test;
```

## テーブルの内容を更新する
以下に例を示します。mysql構文と変わりません。
```
sqlite> update mytable set name="tomato" where id=3;
```

## 作成済みテーブル一覧が知りたい
```
sqlite> .schema
CREATE TABLE personal (id, name);
CREATE TABLE test(id integer(8), name varchar(255));
```

## 一部名称から存在するテーブルを探したい
例えば、テーブル名称に「ers」と含まれるのが予めわかっている場合には、以下の様にしてテーブル名称を探すことができます。
```
sqlite> .tables ers
personal
```

## テーブルのスキーマ情報が知りたい
以下では2つのテーブル「test」、「test2」が存在することがわかります。
```
sqlite> .schema
.schema
CREATE TABLE test(one varchar(10), two smallint);
CREATE TABLE test2(one varchar(10), two smallint);
```

## テーブルのスナップショットを作成する
```
sqlite> .dump <テーブル名>
```

## SQLiteが利用出来る関数
- https://www.dbonline.jp/sqlite/function/

## 現在のデータベースの文字エンコーディングを確認する 
次の例ではUTF-8であることが確認できます
```
sqlite3> PRAGMA encoding;
PRAGMA encoding:
UTF-8
```

## 時間関連
- http://www.sqlite.org/cvstrac/wiki?p=DateAndTimeFunctions

# 参考URL
- SQLite公式サイト(英語)
  - http://www.sqlite.org/
- SQLite入門
  - http://www.dbonline.jp/sqlite/
- SQLiteコマンドの使い方
  - http://www.dbonline.jp/sqlite/sqlite_command/index.html
- SQLite が認識できる SQL
  - https://net-newbie.com/sqlite/lang.html
- rktSQLite2
  - SQLiteのSQLコマンドの全体俯瞰に便利なページです。
  - http://rktsqlite.sourceforge.jp/sqlite/command.html

