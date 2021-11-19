# 概要
Apache DerbyはJAVAで実装されたRDBMSです。

# 環境構築(MAC OS)
予めJDKをダウンロードしておく必要があります。

JAVAバージョンに応じて適切なリリースバージョンを選択してください。
- https://db.apache.org/derby/derby_downloads.html

今回はJAVA11を使っていたので以下のバージョンからダウンロードを行います。
- https://db.apache.org/derby/releases/release-10_15_2_0.cgi

4種類のdistributionが存在しますが、
- bin distribution - contains the documentation, javadoc, and jar files for Derby.
- lib distribution - contains only the jar files for Derby.
- lib-debug distribution - contains jar files for Derby with source line numbers.
- src distribution - contains the Derby source tree at the point which the binaries were built.

稼働させるためにはjarがあればよいのですが、今回は以下よりbin distributionのderbyのzipファイルをダウンロードして、手元で展開します。
- https://dlcdn.apache.org//db/derby/db-derby-10.15.2.0/db-derby-10.15.2.0-bin.zip

環境変数DERBY_HOMEに上記zipを展開したフォルダを設定します。
```
$ export DERBY_HOME=~/Desktop/db-derby-10.15.2.0-bin/
```

RDBMSを起動します。
```
$ java -jar /Users/tsuyoshi/Desktop/db-derby-10.15.2.0-bin/lib/derbyrun.jar server start&
```

コマンドライン上から使ってみます。

JDBCというRDBにアクセスするための標準Java APIを利用します。
CONNECT時に[現在のディレクトリ]/tmp/testDerbyを指定していますが、このディレクトリが1個のデータベースになりいくつかのファイルやディレクトリが作られます。「create=true」が存在するとデータベースが存在しない場合には新しく作ってくれるようです。
```
$ java -jar /Users/tsuyoshi/Desktop/db-derby-10.15.2.0-bin/lib/derbyrun.jar ij
ijバージョン10.15
ij> CONNECT 'jdbc:derby://localhost:1527/tmp/testDerby;create=true';
ij> CREATE TABLE my_schema.Emp ( Id INT NOT NULL GENERATED ALWAYS AS IDENTITY,
   Name VARCHAR(255),
   Salary INT NOT NULL,
   Location VARCHAR(255),
   Phone_Number BIGINT
);
> > > > > 0行が挿入/更新/削除されました
ij> SHOW SCHEMAS;
TABLE_SCHEM                   
------------------------------
APP                           
MY_SCHEMA                     
NULLID                        
SQLJ                          
SYS                           
SYSCAT                        
SYSCS_DIAG                    
SYSCS_UTIL                    
SYSFUN                        
SYSIBM                        
SYSPROC                       
SYSSTAT                       

12行が選択されました
```

テーブルを表示してみます。
```
ij> SHOW TABLES;
TABLE_SCHEM         |TABLE_NAME                    |REMARKS             
------------------------------------------------------------------------
SYS                 |SYSALIASES                    |                    
SYS                 |SYSCHECKS                     |                    
SYS                 |SYSCOLPERMS                   |                    
SYS                 |SYSCOLUMNS                    |                    
SYS                 |SYSCONGLOMERATES              |                    
SYS                 |SYSCONSTRAINTS                |                    
SYS                 |SYSDEPENDS                    |                    
SYS                 |SYSFILES                      |                    
SYS                 |SYSFOREIGNKEYS                |                    
SYS                 |SYSKEYS                       |                    
SYS                 |SYSPERMS                      |                    
SYS                 |SYSROLES                      |                    
SYS                 |SYSROUTINEPERMS               |                    
SYS                 |SYSSCHEMAS                    |                    
SYS                 |SYSSEQUENCES                  |                    
SYS                 |SYSSTATEMENTS                 |                    
SYS                 |SYSSTATISTICS                 |                    
SYS                 |SYSTABLEPERMS                 |                    
SYS                 |SYSTABLES                     |                    
SYS                 |SYSTRIGGERS                   |                    
SYS                 |SYSUSERS                      |                    
SYS                 |SYSVIEWS                      |                    
SYSIBM              |SYSDUMMY1                     |                    
MY_SCHEMA           |EMP                           |                    

24行が選択されました
ij> SHOW TABLES IN MY_SCHEMA;
TABLE_SCHEM         |TABLE_NAME                    |REMARKS             
------------------------------------------------------------------------
MY_SCHEMA           |EMP                           |                    

1行が選択されました
```

先ほど作成したテーブルをみてみます。
```
ij> DESCRIBE MY_SCHEMA.EMP;
COLUMN_NAME         |TYPE_NAME|DEC&|NUM&|COLUM&|COLUMN_DEF|CHAR_OCTE&|IS_NULL&
------------------------------------------------------------------------------
ID                  |INTEGER  |0   |10  |10    |AUTOINCRE&|NULL      |NO      
NAME                |VARCHAR  |NULL|NULL|255   |NULL      |510       |YES     
SALARY              |INTEGER  |0   |10  |10    |NULL      |NULL      |NO      
LOCATION            |VARCHAR  |NULL|NULL|255   |NULL      |510       |YES     
PHONE_NUMBER        |BIGINT   |0   |10  |19    |NULL      |NULL      |YES     

5行が選択されました
```

テーブルの中身を参照してみます。
```
ij> SELECT * FROM MY_SCHEMA.EMP;
ID         |NAME                                                                                                                            |SALARY     |LOCATION                                                                                                                        |PHONE_NUMBER        
--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

0行が選択されました
```

作成後に、接続を終了する場合には以下のようにします。
```
ij> disconnect;
ij> quit;
$
```

# コマンド
代表的なコマンドを以下に示す。
```
コマンド      説明
connect       DBに接続する
disconnect    DBから切断する
autocommit    自動コミットの有無を切り替える。デフォルトは自動コミットされる。
commit        コミットする
rollback      ロールバックする
describe      テーブルの定義を表示する。
show schemas  スキーマ一覧を表示する
show tables   テーブル一覧を表示する。「show tables in APP;」でAPPスキーマのテーブルのみ表示する。
show views    ビュー一覧を表示する
show indexes  インデックス一覧を表示する。 項目名も表示。   「show indexes from TEST;」でTESTテーブルのインデックスが表示される。
```

利用可能なコマンドはhelpコマンドで確認することができます。
```
ij> help;
 
 次のようなコマンドがサポートされます:
 
  PROTOCOL 'JDBCプロトコル' [ AS ident ];
                               -- デフォルトまたは指定されたプロトコルを設定
  DRIVER 'ドライバのクラス';   -- 指定されたクラスをロード
  CONNECT 'データベースのURL' [ PROTOCOL namedProtocol ] [ AS connectionName ];
                               -- データベースURLに接続し
                               -- 識別子を割り当て
  SET CONNECTION connectionName; -- 指定された接続に切り替え
  SHOW CONNECTIONS;            -- すべての接続をリスト
  AUTOCOMMIT [ ON | OFF ];     -- 接続に自動コミットを設定
  DISCONNECT [ CURRENT | connectionName | ALL ];
                               -- 現在の、指定された、またはすべての接続を削除;
                               -- デフォルトはCURRENT
 
  SHOW SCHEMAS;                -- 現在のデータベースのスキーマをすべてリスト
  SHOW [ TABLES | VIEWS | PROCEDURES | FUNCTIONS | SYNONYMS ] { IN schema };
                               -- 表、ビュー、プロシージャ、ファンクション、シノニムをリスト
  SHOW INDEXES { IN schema | FROM table };
                               -- スキーマまたは表の索引をリスト
  SHOW ROLES;                  -- データベースで定義されているすべてのロールをソートしてリスト
  SHOW ENABLED_ROLES;          -- 現在の接続で有効なロールを
                               -- ソートしてリスト(現在のロールを
                               -- 確認するにはVALUES CURRENT_ROLEを使用)
  SHOW SETTABLE_ROLES;         -- 現在の接続に設定できる
                               -- ロールをソートしてリスト
  DESCRIBE name;               -- 指定された表の列をリスト
 
  COMMIT;                      -- 現在のトランザクションをコミット
  ROLLBACK;                    -- 現在のトランザクションをロールバック
 
  PREPARE name AS 'SQL-J text'; -- SQL-Jテキストを準備
  EXECUTE { name | 'SQL-J text' } [ USING { name | 'SQL-J text' } ] ;
                               -- パラメータ付きで文を実行
                               -- USING結果セット行の値
  REMOVE name;                 -- 指定された既存のプリペアド文を削除
 
  RUN 'filename';              -- 指定されたファイルからコマンドを実行
 
  ELAPSEDTIME [ ON | OFF ];    -- ijに経過時間モードを設定
  MAXIMUMDISPLAYWIDTH integerValue;
                               -- 各列の最大表示幅を
                               -- integerValueに設定
 
  ASYNC name 'SQL-J text';     -- 別のスレッドでコマンドを実行
  WAIT FOR name;               -- ASYNC'dコマンドの結果を待機
 
  GET [SCROLL INSENSITIVE] [WITH  { HOLD | NOHOLD }] CURSOR name AS 'SQL-J query';
                               -- 問合せでカーソル(JDBC結果セット)を取得
                               -- デフォルトは保持機能を持つ前方スクロール専用カーソル
  NEXT name;                   -- 指定されたカーソルから次の行を取得
  FIRST name;                  -- 指定されたスクロール・カーソルから最初の行を取得
  LAST name;                   -- 指定されたスクロール・カーソルから最後の行を取得
  PREVIOUS name;               -- 指定されたスクロール・カーソルから前の行を取得
  ABSOLUTE integer name;       -- 指定されたスクロール・カーソルを、絶対行番号の位置に配置
                               -- (負の数は最後の行から数えた位置を示す。) 
  RELATIVE integer name;       -- 指定されたスクロール・カーソルを、現在の行との相対位置に配置
                               -- (integerは行の番号)
  AFTER LAST name;             -- 指定されたスクロール・カーソルを最終行の次に配置
  BEFORE FIRST name;           -- 指定されたスクロール・カーソルを最初の行の前に配置
  GETCURRENTROWNUMBER name;    -- 指定されたスクロール・カーソルの現在位置に対する行番号を返す
                               -- (カーソルが行の上に置かれていない場合には0が返される。) 
  CLOSE name;                  -- 指定されたカーソルをクローズ
  LOCALIZEDDISPLAY [ ON | OFF ];
                               -- ロケールによって異なるデータの表記を制御
 
  EXIT;                        -- ijを終了
  HELP;                        -- このメッセージを表示
 
 認識されないコマンドがあれば、SQL-Jコマンドの候補として扱われ、直接実行されます。
```

# TIPS

### メモリ上にDBを作成したい
CONNECT時に以下のように指定すれば良いらしい。これでメモリ上にTestDBというDBが作成できます。
```
CONNECT 'jdbc:derby:memory:TestDB;create=true';
```
