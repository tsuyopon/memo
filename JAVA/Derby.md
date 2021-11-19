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
CONNECT時に/tmp/testDerbyを指定していますが、このディレクトリが1個のデータベースになりいくつかのファイルやディレクトリが作られます。「create=true」が存在するとデータベースが存在しない場合には新しく作ってくれるようです。
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
