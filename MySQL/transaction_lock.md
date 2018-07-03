# 概要
トランザクションとロック機能について。ここではInnodbと仮定して説明します。

トランザクションとロックの違いは次のとおりです。(参考: https://stackoverflow.com/questions/4226766/mysql-transactions-vs-locking-tables )
- データの一貫性を保ちたい場合にはトランザクションを利用します。tx_isolation によりトランザクション一貫性でどこまでを保証するか違ってくるのでその辺については意識しておく必要があります。
- 特定のテーブルを同時に読み書きを避けたい場合にはLockの仕組みを利用します。Lockはconcurrentなトランザクションを避けるための仕組みです。


# Start Transactionについて

### トランザクション分離レベルについて
トランザクション分離レベルの設定によって、次の問題をどこまでを担保できるかが決定します。
これらは、データベースのACID特性のうちのIsolation（独立性）に関わる設定が違うため発生します。
- 1. ダーティーリード(dirty)
  - 他のトランザクションのコミットされていない変更が見えること
- 2. ノンリピータブルリード/ファジーリード(non-repeatable)
  - 他のトランザクションのコミットされた変更が見えること
- 3. ファントムリード(phantom)
  - 他のトランザクションで挿入されたレコードが見えること

mysql設定についてはtx_isolationで設定変更できますが、次の4種類が存在します。 InnoDBのデフォルトがREPEATABLE READです。
- READ UNCOMMITTED
  - dirty, non-repeatable, phantomすべての問題が発生する
- READ COMMITTED
  - non-repeatable, phantomの問題が発生する
- REPEATABLE READ
  - phantomの問題が発生する
- SERIALIZABLE
  - すべての問題が発生しない
  - 厳密には影響あるテーブルの操作の場合には、他のトランザクションの操作を待たせています。

と同時に更に意識しなければならないのはisolationレベルによってデッドロックが発生するということです。
デッドロックについては
- https://qiita.com/saki7/items/87c471f71cca4a542ef7

上記の要点としては次の２点を抑えておく必要がある。
- InnoDBはデッドロック検知機構が搭載されているので、デッドロックが発生した場合は どれかのトランザクション(=victim) が 安全にROLLBACKされるので、アプリケーションで検知されることができる。
- 次のTIPSを理解しておくこと
  - https://dev.mysql.com/doc/refman/5.5/en/innodb-deadlocks.html


- 参考URL
  - https://qiita.com/noonworks/items/bb232cc13d5c2da55f29

### Start Transactionのネストはできるのか?
以下のstack overflowによると
- https://stackoverflow.com/questions/1306869/are-nested-transactions-allowed-in-mysql

公式資料にも記載されている通りネストすることはできない。
- (公式資料) https://dev.mysql.com/doc/refman/5.7/en/implicit-commit.html
```
Transactions cannot be nested. This is a consequence of the implicit commit performed for any current transaction when you issue a START TRANSACTION statement or one of its synonyms.
```

これはストアドプロシージャの中でストアドプロシージャや関数などを呼び出す場合にネックとなる。


# Lockについて

InnoDBにおけるロックの種類について
- レコードロック
- ギャップロック
- ネクストキーロック

- 参考
  - https://dev.mysql.com/doc/refman/5.6/ja/innodb-lock-modes.html
  - https://dev.mysql.com/doc/refman/5.6/ja/innodb-record-level-locks.html


# トランザクション・ロックで重要な設定値

### トランザクション分離レベル
トランザクション分離レベルによりDBの整合性が変わってきますので、この項目によってDBの整合性が変化してくることは非常に重要です。
```
mysql> select @@global.tx_isolation, @@session.tx_isolation;
+-----------------------+------------------------+
| @@global.tx_isolation | @@session.tx_isolation |
+-----------------------+------------------------+
| REPEATABLE-READ       | REPEATABLE-READ        |
+-----------------------+------------------------+
1 row in set (0.00 sec)
```

### autocommitをオンにするかどうか
COMMITを明示的に実行しなくても、COMMITするかどうかを表す変数です。
```
mysql>  select @@global.autocommit, @@session.autocommit;
+---------------------+----------------------+
| @@global.autocommit | @@session.autocommit |
+---------------------+----------------------+
|                   1 |                    1 |
+---------------------+----------------------+
1 row in set (0.00 sec)
```

### ロックで待つ最大時間
```
mysql>  select @@global.innodb_lock_wait_timeout, @@session.innodb_lock_wait_timeout;
+-----------------------------------+------------------------------------+
| @@global.innodb_lock_wait_timeout | @@session.innodb_lock_wait_timeout |
+-----------------------------------+------------------------------------+
|                                50 |                                 50 |
+-----------------------------------+------------------------------------+
1 row in set (0.00 sec)
```

### トランザクションタイムアウト時のロールバック動作を指定する
MySQL 5.6 では、InnoDB はデフォルトで、トランザクションタイムアウト時に最後のステートメントのみをロールバックします。--innodb_rollback_on_timeout を指定すると、トランザクションタイムアウトによって、InnoDB はトランザクション全体を中止してロールバックします
```
mysql> select @@global.innodb_rollback_on_timeout;
+-------------------------------------+
| @@global.innodb_rollback_on_timeout |
+-------------------------------------+
|                                   0 |
+-------------------------------------+
1 row in set (0.00 sec)
```

# 記述すること(TODO)
- トランザクションとロックは相性がよくない
- ロックのネスト
- START TRANSACTION WITH CONSISTENT SNAPSHOT
- SELECT ... FOR UPDATE or SELECT ... LOCK IN SHARE MODE
- ギャップロックについて

