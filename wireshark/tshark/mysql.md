# 概要
tsharkのMySQLコマンドについて

Oオプションの後にmysqlを指定しているが、これはアプリケーションレイヤーとしてmysqlの結果だけ出力してくれて便利です。
Vオプションを付与してOオプションを付与しないとデフォルトで全レイヤの情報が全て出力されるので必要な出力結果のみフィルタしたい場合に非常に便利です。

# 詳細

### ローカルサーバから発行しているSQLクエリを確認する
たとえば、ローカルサーバから発行している
```
$ sudo tshark -i lo -O mysql -Y 'tcp.dstport==3306' -V
Running as user "root" and group "root". This could be dangerous.
Capturing on 'Loopback'
Frame 21: 86 bytes on wire (688 bits), 86 bytes captured (688 bits) on interface 0
Ethernet II, Src: 00:00:00_00:00:00 (00:00:00:00:00:00), Dst: 00:00:00_00:00:00 (00:00:00:00:00:00)
Internet Protocol Version 4, Src: 127.0.0.1 (127.0.0.1), Dst: 127.0.0.1 (127.0.0.1)
Transmission Control Protocol, Src Port: 37360 (37360), Dst Port: mysql (3306), Seq: 1, Ack: 1, Len: 20
MySQL Protocol
    Packet Length: 16
    Packet Number: 0
    Request Command Query
        Command: Query (3)
        Statement: show PROCEDURES

Frame 23: 66 bytes on wire (528 bits), 66 bytes captured (528 bits) on interface 0
Ethernet II, Src: 00:00:00_00:00:00 (00:00:00:00:00:00), Dst: 00:00:00_00:00:00 (00:00:00:00:00:00)
Internet Protocol Version 4, Src: 127.0.0.1 (127.0.0.1), Dst: 127.0.0.1 (127.0.0.1)
Transmission Control Protocol, Src Port: 37360 (37360), Dst Port: mysql (3306), Seq: 21, Ack: 170, Len: 0

Frame 44: 89 bytes on wire (712 bits), 89 bytes captured (712 bits) on interface 0
Ethernet II, Src: 00:00:00_00:00:00 (00:00:00:00:00:00), Dst: 00:00:00_00:00:00 (00:00:00:00:00:00)
Internet Protocol Version 4, Src: 127.0.0.1 (127.0.0.1), Dst: 127.0.0.1 (127.0.0.1)
Transmission Control Protocol, Src Port: 37360 (37360), Dst Port: mysql (3306), Seq: 21, Ack: 170, Len: 23
MySQL Protocol
    Packet Length: 19
    Packet Number: 0
    Request Command Query
        Command: Query (3)
        Statement: SELECT * FROM city
```


### ローカルサーバで発行しているSQLクエリとその応答を確認する
sakilaデータベースを使って
```
mysql> SELECT * FROM city LIMIT 1;
+---------+--------------------+------------+---------------------+
| city_id | city               | country_id | last_update         |
+---------+--------------------+------------+---------------------+
|       1 | A Corua (La Corua) |         87 | 2006-02-15 04:45:25 |
+---------+--------------------+------------+---------------------+
1 row in set (0.00 sec)
```

ローカルサーバが発行しているクエリを確認するにはtcp.dstportでフィルタリングしたが、ここではtcp.dstport, tcp.srcportで3306を検知させるようにtcp.portを3306をフィルタ条件として設定した。
たった1行のクエリ応答だがこんなにもたくさんのmysqlパケットが流れる。

```
$ sudo tshark -i lo -O mysql -Y 'tcp.port==3306' -V
(snip)
Frame 610: 97 bytes on wire (776 bits), 97 bytes captured (776 bits) on interface 0
Ethernet II, Src: 00:00:00_00:00:00 (00:00:00:00:00:00), Dst: 00:00:00_00:00:00 (00:00:00:00:00:00)
Internet Protocol Version 4, Src: 127.0.0.1 (127.0.0.1), Dst: 127.0.0.1 (127.0.0.1)
Transmission Control Protocol, Src Port: 37360 (37360), Dst Port: mysql (3306), Seq: 77, Ack: 714, Len: 31
MySQL Protocol
    Packet Length: 27
    Packet Number: 0
    Request Command Query
        Command: Query (3)
        Statement: SELECT * FROM city LIMIT 1

Frame 611: 361 bytes on wire (2888 bits), 361 bytes captured (2888 bits) on interface 0
Ethernet II, Src: 00:00:00_00:00:00 (00:00:00:00:00:00), Dst: 00:00:00_00:00:00 (00:00:00:00:00:00)
Internet Protocol Version 4, Src: 127.0.0.1 (127.0.0.1), Dst: 127.0.0.1 (127.0.0.1)
Transmission Control Protocol, Src Port: mysql (3306), Dst Port: 37360 (37360), Seq: 714, Ack: 108, Len: 295
MySQL Protocol
    Packet Length: 1
    Packet Number: 1
    Number of fields: 4
MySQL Protocol
    Packet Length: 50
    Packet Number: 2
    Catalog: def
    Database: sakila
    Table: city
    Original table: city
    Name: city_id
    Original name: city_id
    Charset number: binary COLLATE binary (63)
    Length: 5
    Type: FIELD_TYPE_SHORT (2)
    Flags: 0x4223
        .... .... .... ...1 = Not null: Set
        .... .... .... ..1. = Primary key: Set
        .... .... .... .0.. = Unique key: Not set
        .... .... .... 0... = Multiple key: Not set
        .... .... ...0 .... = Blob: Not set
        .... .... ..1. .... = Unsigned: Set
        .... .... .0.. .... = Zero fill: Not set
        .... .... 0... .... = Binary: Not set
        .... ...0 .... .... = Enum: Not set
        .... ..1. .... .... = Auto increment: Set
        .... .0.. .... .... = Timestamp: Not set
        .... 0... .... .... = Set: Not set
    Decimals: 0
MySQL Protocol
    Packet Length: 44
    Packet Number: 3
    Catalog: def
    Database: sakila
    Table: city
    Original table: city
    Name: city
    Original name: city
    Charset number: utf8 COLLATE utf8_general_ci (33)
    Length: 150
    Type: FIELD_TYPE_VAR_STRING (253)
    Flags: 0x1001
        .... .... .... ...1 = Not null: Set
        .... .... .... ..0. = Primary key: Not set
        .... .... .... .0.. = Unique key: Not set
        .... .... .... 0... = Multiple key: Not set
        .... .... ...0 .... = Blob: Not set
        .... .... ..0. .... = Unsigned: Not set
        .... .... .0.. .... = Zero fill: Not set
        .... .... 0... .... = Binary: Not set
        .... ...0 .... .... = Enum: Not set
        .... ..0. .... .... = Auto increment: Not set
        .... .0.. .... .... = Timestamp: Not set
        .... 0... .... .... = Set: Not set
    Decimals: 0
MySQL Protocol
    Packet Length: 56
    Packet Number: 4
    Catalog: def
    Database: sakila
    Table: city
    Original table: city
    Name: country_id
    Original name: country_id
    Charset number: binary COLLATE binary (63)
    Length: 5
    Type: FIELD_TYPE_SHORT (2)
    Flags: 0x5029
        .... .... .... ...1 = Not null: Set
        .... .... .... ..0. = Primary key: Not set
        .... .... .... .0.. = Unique key: Not set
        .... .... .... 1... = Multiple key: Set
        .... .... ...0 .... = Blob: Not set
        .... .... ..1. .... = Unsigned: Set
        .... .... .0.. .... = Zero fill: Not set
        .... .... 0... .... = Binary: Not set
        .... ...0 .... .... = Enum: Not set
        .... ..0. .... .... = Auto increment: Not set
        .... .0.. .... .... = Timestamp: Not set
        .... 0... .... .... = Set: Not set
    Decimals: 0
MySQL Protocol
    Packet Length: 58
    Packet Number: 5
    Catalog: def
    Database: sakila
    Table: city
    Original table: city
    Name: last_update
    Original name: last_update
    Charset number: binary COLLATE binary (63)
    Length: 19
    Type: FIELD_TYPE_TIMESTAMP (7)
    Flags: 0x2481
        .... .... .... ...1 = Not null: Set
        .... .... .... ..0. = Primary key: Not set
        .... .... .... .0.. = Unique key: Not set
        .... .... .... 0... = Multiple key: Not set
        .... .... ...0 .... = Blob: Not set
        .... .... ..0. .... = Unsigned: Not set
        .... .... .0.. .... = Zero fill: Not set
        .... .... 1... .... = Binary: Set
        .... ...0 .... .... = Enum: Not set
        .... ..0. .... .... = Auto increment: Not set
        .... .1.. .... .... = Timestamp: Set
        .... 0... .... .... = Set: Not set
    Decimals: 0
MySQL Protocol
    Packet Length: 5
    Packet Number: 6
    EOF marker: 254
    Warnings: 0
    Server Status: 0x0022
        .... .... .... ...0 = In transaction: Not set
        .... .... .... ..1. = AUTO_COMMIT: Set
        .... .... .... .0.. = More results: Not set
        .... .... .... 0... = Multi query - more resultsets: Not set
        .... .... ...0 .... = Bad index used: Not set
        .... .... ..1. .... = No index used: Set
        .... .... .0.. .... = Cursor exists: Not set
        .... .... 0... .... = Last row sebd: Not set
        .... ...0 .... .... = database dropped: Not set
        .... ..0. .... .... = No backslash escapes: Not set
MySQL Protocol
    Packet Length: 44
    Packet Number: 7
    text: 1
    text: A Corua (La Corua)
    text: 87
    text: 2006-02-15 04:45:25
MySQL Protocol
    Packet Length: 5
    Packet Number: 8
    EOF marker: 254
    Warnings: 0
    Server Status: 0x0022
        .... .... .... ...0 = In transaction: Not set
        .... .... .... ..1. = AUTO_COMMIT: Set
        .... .... .... .0.. = More results: Not set
        .... .... .... 0... = Multi query - more resultsets: Not set
        .... .... ...0 .... = Bad index used: Not set
        .... .... ..1. .... = No index used: Set
        .... .... .0.. .... = Cursor exists: Not set
        .... .... 0... .... = Last row sebd: Not set
        .... ...0 .... .... = database dropped: Not set
        .... ..0. .... .... = No backslash escapes: Not set
```


### Prepared Statementの場合
次のプログラムを使ってアクセスする
- https://github.com/tsuyopon/php/blob/master/mysql/mysqli/sample.php

Prepared Statementの場合にはたくさんのフレームから成り立っているので、すぐに判断はできない。
以下ではたくさんのフレームを省略しているが、リクエストは次のあたりで成り立っていることが確認できます。
```
Frame 147: 144 bytes on wire (1152 bits), 144 bytes captured (1152 bits) on interface 0
Ethernet II, Src: 00:00:00_00:00:00 (00:00:00:00:00:00), Dst: 00:00:00_00:00:00 (00:00:00:00:00:00)
Internet Protocol Version 4, Src: 127.0.0.1 (127.0.0.1), Dst: 127.0.0.1 (127.0.0.1)
Transmission Control Protocol, Src Port: 39472 (39472), Dst Port: mysql (3306), Seq: 72, Ack: 90, Len: 78
MySQL Protocol
    Packet Length: 74
    Packet Number: 0
    Request Command Prepare Statement
        Command: Prepare Statement (22)
        Statement: SELECT city_id, city FROM city WHERE country_id=? AND city LIKE ? LIMIT 1

(snip)

Frame 150: 98 bytes on wire (784 bits), 98 bytes captured (784 bits) on interface 0
Ethernet II, Src: 00:00:00_00:00:00 (00:00:00:00:00:00), Dst: 00:00:00_00:00:00 (00:00:00:00:00:00)
Internet Protocol Version 4, Src: 127.0.0.1 (127.0.0.1), Dst: 127.0.0.1 (127.0.0.1)
Transmission Control Protocol, Src Port: 39472 (39472), Dst Port: mysql (3306), Seq: 150, Ack: 280, Len: 32
MySQL Protocol
    Packet Length: 28
    Packet Number: 0
    Request Command Execute Statement
        Command: Execute Statement (23)
        Statement ID: 1
        Flags: Defaults (0)
        Iterations (unused): 1
        New parameter bound flag: First call or rebound (1)
        Parameter
            Type: FIELD_TYPE_LONGLONG (8)
            Unsigned: 0
            Value: 75
        Parameter
            Type: FIELD_TYPE_VAR_STRING (253)
            Unsigned: 0
            Value: Ta%

```


# TODO
- prepared statementも
