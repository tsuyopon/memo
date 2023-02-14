# 概要
PostgreSQLの使い方についてまとめます

# インストール

### psqlクライアントのインストール (Mac)
下記をbrewから入れるだけでpsqlクライアントが入ります。ただし、サーバは入りません。
```
$ brew install libpq
```

# 利用
### 接続方法
Uにはロール名、dにはデータベース名を指定します。
```
$ psql -h localhost -p 5432 -U postgres -d testdb
```

localhostで、デフォルト5432の場合には省略できます。
```
psql -U postgres -d testdb
```

バージョンを確認してみます。
```
traffic_ops=> SELECT version();
                                                version                                                
-------------------------------------------------------------------------------------------------------
 PostgreSQL 13.2 on x86_64-pc-linux-musl, compiled by gcc (Alpine 10.2.1_pre1) 10.2.1 20201203, 64-bit
(1 row)
```

### 環境変数を利用する
postgresqlでは以下の環境変数を解釈してくれます。
```
export PGDATABASE=DB名
export PGHOST=ホスト
export PGPORT=ポート番号
export PGUSER=ユーザー名
export PGPASSWORD=パスワード
```

### 接続終了時
```
\q
or
exit
```

### ヘルプを表示する
```
traffic_ops=> \h
Available help:
  ABORT                            ALTER TEXT SEARCH TEMPLATE       CREATE PUBLICATION               DROP FUNCTION                    IMPORT FOREIGN SCHEMA
  ALTER AGGREGATE                  ALTER TRIGGER                    CREATE ROLE                      DROP GROUP                       INSERT
  ALTER COLLATION                  ALTER TYPE                       CREATE RULE                      DROP INDEX                       LISTEN
  ALTER CONVERSION                 ALTER USER                       CREATE SCHEMA                    DROP LANGUAGE                    LOAD
  ALTER DATABASE                   ALTER USER MAPPING               CREATE SEQUENCE                  DROP MATERIALIZED VIEW           LOCK
  ALTER DEFAULT PRIVILEGES         ALTER VIEW                       CREATE SERVER                    DROP OPERATOR                    MOVE
  ALTER DOMAIN                     ANALYZE                          CREATE STATISTICS                DROP OPERATOR CLASS              NOTIFY
  ALTER EVENT TRIGGER              BEGIN                            CREATE SUBSCRIPTION              DROP OPERATOR FAMILY             PREPARE
  ALTER EXTENSION                  CALL                             CREATE TABLE                     DROP OWNED                       PREPARE TRANSACTION
  ALTER FOREIGN DATA WRAPPER       CHECKPOINT                       CREATE TABLE AS                  DROP POLICY                      REASSIGN OWNED
  ALTER FOREIGN TABLE              CLOSE                            CREATE TABLESPACE                DROP PROCEDURE                   REFRESH MATERIALIZED VIEW
  ALTER FUNCTION                   CLUSTER                          CREATE TEXT SEARCH CONFIGURATION DROP PUBLICATION                 REINDEX
  ALTER GROUP                      COMMENT                          CREATE TEXT SEARCH DICTIONARY    DROP ROLE                        RELEASE SAVEPOINT
  ALTER INDEX                      COMMIT                           CREATE TEXT SEARCH PARSER        DROP ROUTINE                     RESET
  ALTER LANGUAGE                   COMMIT PREPARED                  CREATE TEXT SEARCH TEMPLATE      DROP RULE                        REVOKE
  ALTER LARGE OBJECT               COPY                             CREATE TRANSFORM                 DROP SCHEMA                      ROLLBACK
  ALTER MATERIALIZED VIEW          CREATE ACCESS METHOD             CREATE TRIGGER                   DROP SEQUENCE                    ROLLBACK PREPARED
  ALTER OPERATOR                   CREATE AGGREGATE                 CREATE TYPE                      DROP SERVER                      ROLLBACK TO SAVEPOINT
  ALTER OPERATOR CLASS             CREATE CAST                      CREATE USER                      DROP STATISTICS                  SAVEPOINT
  ALTER OPERATOR FAMILY            CREATE COLLATION                 CREATE USER MAPPING              DROP SUBSCRIPTION                SECURITY LABEL
  ALTER POLICY                     CREATE CONVERSION                CREATE VIEW                      DROP TABLE                       SELECT
  ALTER PROCEDURE                  CREATE DATABASE                  DEALLOCATE                       DROP TABLESPACE                  SELECT INTO
  ALTER PUBLICATION                CREATE DOMAIN                    DECLARE                          DROP TEXT SEARCH CONFIGURATION   SET
  ALTER ROLE                       CREATE EVENT TRIGGER             DELETE                           DROP TEXT SEARCH DICTIONARY      SET CONSTRAINTS
  ALTER ROUTINE                    CREATE EXTENSION                 DISCARD                          DROP TEXT SEARCH PARSER          SET ROLE
  ALTER RULE                       CREATE FOREIGN DATA WRAPPER      DO                               DROP TEXT SEARCH TEMPLATE        SET SESSION AUTHORIZATION
  ALTER SCHEMA                     CREATE FOREIGN TABLE             DROP ACCESS METHOD               DROP TRANSFORM                   SET TRANSACTION
  ALTER SEQUENCE                   CREATE FUNCTION                  DROP AGGREGATE                   DROP TRIGGER                     SHOW
  ALTER SERVER                     CREATE GROUP                     DROP CAST                        DROP TYPE                        START TRANSACTION
  ALTER STATISTICS                 CREATE INDEX                     DROP COLLATION                   DROP USER                        TABLE
  ALTER SUBSCRIPTION               CREATE LANGUAGE                  DROP CONVERSION                  DROP USER MAPPING                TRUNCATE
  ALTER SYSTEM                     CREATE MATERIALIZED VIEW         DROP DATABASE                    DROP VIEW                        UNLISTEN
  ALTER TABLE                      CREATE OPERATOR                  DROP DOMAIN                      END                              UPDATE
  ALTER TABLESPACE                 CREATE OPERATOR CLASS            DROP EVENT TRIGGER               EXECUTE                          VACUUM
  ALTER TEXT SEARCH CONFIGURATION  CREATE OPERATOR FAMILY           DROP EXTENSION                   EXPLAIN                          VALUES
  ALTER TEXT SEARCH DICTIONARY     CREATE POLICY                    DROP FOREIGN DATA WRAPPER        FETCH                            WITH
  ALTER TEXT SEARCH PARSER         CREATE PROCEDURE                 DROP FOREIGN TABLE               GRANT                            
```

### データベース一覧の表示
```
traffic_ops=> \l
                                     List of databases
     Name      |     Owner     | Encoding |  Collate   |   Ctype    |   Access privileges   
---------------+---------------+----------+------------+------------+-----------------------
 postgres      | postgres      | UTF8     | en_US.utf8 | en_US.utf8 | 
 template0     | postgres      | UTF8     | en_US.utf8 | en_US.utf8 | =c/postgres          +
               |               |          |            |            | postgres=CTc/postgres
 template1     | postgres      | UTF8     | en_US.utf8 | en_US.utf8 | =c/postgres          +
               |               |          |            |            | postgres=CTc/postgres
 traffic_ops   | traffic_ops   | UTF8     | en_US.utf8 | en_US.utf8 | 
 traffic_vault | traffic_vault | UTF8     | en_US.utf8 | en_US.utf8 | 
(5 rows)
```

### データベースの切り替え
```
traffic_ops=> \c traffic_ops
Password: 
You are now connected to database "xxxxx" as user "traffic_ops".
```

### データベース中のテーブル一覧の表示
```
traffic_ops=> \d
                               List of relations
 Schema |                    Name                     |   Type   |    Owner    
--------+---------------------------------------------+----------+-------------
 public | acme_account                                | table    | traffic_ops
 public | api_capability                              | table    | traffic_ops
 public | api_capability_id_seq                       | sequence | traffic_ops
 public | asn                                         | table    | traffic_ops
 public | asn_id_seq                                  | sequence | traffic_ops
(snip)
(107 rows)
```

### テーブルのスキーマ情報の表示
テーブル情報の詳細を取得する
```
traffic_ops=>  \d acme_account
             Table "public.acme_account"
   Column    | Type | Collation | Nullable | Default 
-------------+------+-----------+----------+---------
 email       | text |           | not null | 
 private_key | text |           | not null | 
 provider    | text |           | not null | 
 uri         | text |           | not null | 
Indexes:
    "acme_account_pkey" PRIMARY KEY, btree (email, provider)
```

### レコードの表示
```
traffic_ops=> SELECT * FROM region;
 id |      name       | division |         last_updated          
----+-----------------+----------+-------------------------------
  1 | Montreal        |        1 | 2023-02-13 11:48:25.827093+00
  2 | Washington, D.C |        2 | 2023-02-13 11:48:25.953833+00
(2 rows)
```

項目ごとに行として表示したい場合には\gxを付与します。
```
traffic_ops=> SELECT * FROM region \gx
-[ RECORD 1 ]+------------------------------
id           | 1
name         | Montreal
division     | 1
last_updated | 2023-02-13 11:48:25.827093+00
-[ RECORD 2 ]+------------------------------
id           | 2
name         | Washington, D.C
division     | 2
last_updated | 2023-02-13 11:48:25.953833+00
```

### クエリにかかった時間を表示する
\timing onの後にクエリにかかった時間を表示します。\timing off以降はクエリにかかった時間を表示しません。
以下に例を示します。
```
traffic_ops=> \timing on
Timing is on.
traffic_ops=> SELECT current_date;
 current_date 
--------------
 2023-02-14
(1 row)

Time: 1.482 ms
traffic_ops=> \timing off
Timing is off.
traffic_ops=> SELECT current_date;
 current_date 
--------------
 2023-02-14
(1 row)
```

### 出力結果をログとしてファイルに落とす。
\oの後に引数を指定するとそのファイルに書き出しを行い、\oで書き出しが終了します。
```
traffic_ops=> \o log.txt
traffic_ops=> SELECT current_date;
traffic_ops=> \o
```

ファイルの内容を確認してみます。
```
# cat log.txt 
 current_date 
--------------
 2023-02-14
(1 row)
```

# 管理

### ユーザー一覧を表示する
```
traffic_ops=> \du
                                     List of roles
   Role name   |                         Attributes                         | Member of 
---------------+------------------------------------------------------------+-----------
 grafana       |                                                            | {}
 postgres      | Superuser, Create role, Create DB, Replication, Bypass RLS | {}
 telegraf      |                                                            | {}
 traffic_ops   |                                                            | {}
 traffic_vault |                                                            | {}
```

### PostgreSQLへの接続を確認する
```
traffic_ops=> select * from pg_stat_activity \gx
(snip)
-[ RECORD 4 ]----+----------------------------------------------------------------------------------------------
datid            | 16387
datname          | traffic_ops
pid              | 157
leader_pid       | 
usesysid         | 16384
usename          | traffic_ops
application_name | trafficops
client_addr      | 172.27.0.16
client_hostname  | 
client_port      | 53826
backend_start    | 2023-02-13 11:48:23.296154+00
xact_start       | 
query_start      | 2023-02-13 11:48:46.327938+00
state_change     | 2023-02-13 11:48:46.328023+00
wait_event_type  | Client
wait_event       | ClientRead
state            | idle
backend_xid      | 
backend_xmin     | 
query            | COMMIT
backend_type     | client backend
```

# コマンドライン

### テーブル一覧の表示
```
# psql -h localhost -p 5432 -U traffic_ops -W -l
Password: 
                                     List of databases
     Name      |     Owner     | Encoding |  Collate   |   Ctype    |   Access privileges   
---------------+---------------+----------+------------+------------+-----------------------
 postgres      | postgres      | UTF8     | en_US.utf8 | en_US.utf8 | 
 template0     | postgres      | UTF8     | en_US.utf8 | en_US.utf8 | =c/postgres          +
               |               |          |            |            | postgres=CTc/postgres
 template1     | postgres      | UTF8     | en_US.utf8 | en_US.utf8 | =c/postgres          +
               |               |          |            |            | postgres=CTc/postgres
 traffic_ops   | traffic_ops   | UTF8     | en_US.utf8 | en_US.utf8 | 
 traffic_vault | traffic_vault | UTF8     | en_US.utf8 | en_US.utf8 | 
(5 rows)
```

# 便利ツール

### データベースのテーブル情報からER図を自動生成する
下記コマンドでhtmlやer図などの情報を自動生成してくれます。以下はciabデフォルト時のサンプルです。パスワードは適宜変更するのが良いでしょう。
```
$ docker run -v "$PWD/schema:/output" --net="host" schemaspy/schemaspy:6.1.0 -t pgsql -host localhost:5432 -db traffic_ops -u traffic_ops -p twelve -debug

// 実行完了するとschemaというディレクトリに生成します。
$ ls schema
$ cd schema

// webサーバを起動する
$ python3 -m http.server 8888
```

あとは以下にアクセスして確認できます。
- http://localhost:8888/

詳細については下記資料を参考のこと
- https://zenn.dev/ucwork/articles/a42121e85451be
