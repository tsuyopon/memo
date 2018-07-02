# 概要
ステータス変数には次の２つが存在します。普段から意識しておく必要があります。
- グローバルスコープ
  - mysqld全体に影響を及ぼす
- セッションスコープ
  - 各セッション毎に影響を及ぼす



# 詳細

### ステータスで参照できるカテゴリ
```
Com_                   MySQLサーバ内でのコマンド実行回数
Create_tmp_            テンポラリテーブル作成
Handler_               Handlerインターフェースに対するコマンド実行回数
Innodb_                InnoDBストレージエンジン
Key_                   MyISAMのインデックスキャッシュ
Performance_schema_    パフォーマンススキーマ
Qcache_                クエリキャッシュ
Select_                問題となり得るSELECT文
Slave_                 レプリケーションスレーブ
Sort_                  ソート
Ssl_                   SSL
Table_                 テーブルレベルロックおよびテーブルキャッシュ
Thread_                MySQLサーバの内部スレッド
Uptime_                稼働時間
```

### 変数を参照する
- セッション変数
```
mysql> SHOW LOCAL VARIABLES;
```
- グローバル変数
```
mysql> SHOW GLOBAL VARIABLES;
```

### SELECTでグローバル変数とセッション変数の値を参照したい
グローバル変数の参照方法とセッション変数の参照方法を以下に記します。
```
mysql> SET SESSION max_join_size=10000;   -- セッション変数の値を予め変更しておきます(セッション接続時だとグローバル変数のコピーなので)
Query OK, 0 rows affected (0.00 sec)

mysql> SELECT @@global.max_join_size;     -- グローバル変数を参照する
+------------------------+
| @@global.max_join_size |
+------------------------+
|   18446744073709551615 |
+------------------------+
1 row in set (0.00 sec)

mysql> SELECT @@session.max_join_size;    -- セッション変数を参照する(@@localでも参照可能)
+-------------------------+
| @@session.max_join_size |
+-------------------------+
|                   10000 |
+-------------------------+
1 row in set (0.00 sec)

mysql> SELECT @@max_join_size;            -- @@globalや@@sessionを付与しない場合には@@sesionと同じ
+-----------------+
| @@max_join_size |
+-----------------+
|           10000 |
+-----------------+
1 row in set (0.00 sec)
```


sql_modeはmysqlのバージョンでデフォルト値がコロコロと変わっているので、設定しておくことが重要です。

### 変数を変更する
- グローバル変数の変更
```
SET GLOBAL max_join_size = 18446744073709551615;
```
- セッション変数の変更
```
SET SESSION max_join_size = 100000;
or
SET max_join_size = 100000;
```

サーバシステム変数については次の資料で規定されているので参照のこと
- https://dev.mysql.com/doc/refman/5.6/ja/server-system-variables.html

### GLOBAL値をコンパイル時のMySQLの値に設定する。
DEFAULTというキーワードを利用することができるようです。
```
SET max_join_size=DEFAULT;
```

### ステータス変数を参照する

以下はCom_selectに絞った例ですが、セッションスコープとグローバルスコープで参照方法が異なります。
- セッションスコープ
```
mysql> SHOW SESSION STATUS LIKE 'Com_select';
+---------------+-------+
| Variable_name | Value |
+---------------+-------+
| Com_select    | 1     |
+---------------+-------+
1 row in set (0.00 sec)
```
- グローバルスコープ
```
mysql> SHOW GLOBAL STATUS LIKE 'Com_select';
+---------------+-------+
| Variable_name | Value |
+---------------+-------+
| Com_select    | 2     |
+---------------+-------+
1 row in set (0.00 sec)
```

セッション変数・クローバル変数として分離して扱われるか、同一で扱われるかは次のページで確認することができます。
- http://download.nust.na/pub6/mysql/doc/refman/5.1/en/server-status-variables.html

例えば、次の変数を例として示す。
- innodb_buffer_pool_size
  - これはグローバルしか存在しない
- max_allowed_packet
  - グローバル変数はセッションでのデフォルト値を定義していて、接続時にセッション変数としてコピーされる。
- 独自定義
  - 

### セッションスコープとグローバルスコープで差異があるものを知りたい

先程のSTATUSコマンドは、以下のSQLテーブル参照が発行されているのと同じです。
```
-- SHOW GLOBAL STATUSと等価
mysql> SELECT * FROM INFORMATION_SCHEMA.GLOBAL_STATUS;

-- SHOW SESSION STATUSと等価
mysql> SELECT * FROM INFORMATION_SCHEMA.SESSION_STATUS;
```

つまり、セッションスコープとグローバルスコープで差異がある値は次のようにして抽出することができます。
```
mysql> SELECT G.variable_name, G.variable_value, S.variable_value FROM information_schema.global_status G INNER join information_schema.session_status S USING (variable_name) WHERE G.variable_value <> S.variable_value;
+--------------------------+----------------+----------------+
| variable_name            | variable_value | variable_value |
+--------------------------+----------------+----------------+
| BYTES_RECEIVED           | 2519           | 2054           |
| BYTES_SENT               | 269271         | 259385         |
| COM_ADMIN_COMMANDS       | 1              | 0              |
| COM_FLUSH                | 1              | 0              |
| COM_SELECT               | 7              | 6              |
| COM_SHOW_DATABASES       | 1              | 0              |
| COM_SHOW_STATUS          | 37             | 36             |
| CREATED_TMP_TABLES       | 51             | 13             |
| HANDLER_EXTERNAL_LOCK    | 140            | 0              |
| HANDLER_READ_FIRST       | 3              | 0              |
| HANDLER_READ_RND_NEXT    | 10711          | 3629           |
| HANDLER_WRITE            | 10647          | 4142           |
| LAST_QUERY_COST          | 0.000000       | 21.650822      |
| LAST_QUERY_PARTIAL_PLANS | 0              | 3              |
| OPENED_TABLE_DEFINITIONS | 67             | 0              |
| OPENED_TABLES            | 67             | 0              |
| QUESTIONS                | 54             | 48             |
| SELECT_SCAN              | 47             | 9              |
| TABLE_OPEN_CACHE_HITS    | 3              | 0              |
| TABLE_OPEN_CACHE_MISSES  | 67             | 0              |
+--------------------------+----------------+----------------+
20 rows in set (0.02 sec)
```


### ステータス変数をリセットしたい
セッションスコープかグローバルスコープかで方法が異なります。

- セッションスコープの場合
```
FLUSH STATUS;
```
- グローバルスコープの場合
  - mysqldの再起動しか方法はありません。

参考資料
- https://dev.mysql.com/doc/refman/5.6/ja/flush.html

# 参考URL
- MySQL 5.6 リファレンスマニュアル(13.7.5.40 SHOW VARIABLES 構文)
  - https://dev.mysql.com/doc/refman/5.6/ja/show-variables.html
- MySQL 5.6 リファレンスマニュアル(13.7.4 SET 構文)
  - https://dev.mysql.com/doc/refman/5.6/ja/set-statement.html
