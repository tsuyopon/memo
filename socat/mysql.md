# 概要
socatを利用したMySQLのデバッグ方法について

# 詳細
mysqlコマンドは接続時に/tmp/mysql.sockを使います。
```
$ mysql -utest -ppassword
mysql: [Warning] Using a password on the command line interface can be insecure.
ERROR 2002 (HY000): Can't connect to local MySQL server through socket '/tmp/mysql.sock' (2)
```

よって、単純なTCPのlocalhost:3306からMySQLサーバ:3306へのトンネルではなくて、Unixドメインソケットを利用したListenを定義して、そこからリモートサーバ(ubuntu:3306)にプロキシが必要です。
```
$ socat -v UNIX-LISTEN:/tmp/mysql.sock,fork,reuseaddr TCP:ubuntu:3306
```

上記コマンドでも出力されますが、出力がごちゃごちゃしているのでtsharkを利用するのが良いでしょう。
別の端末で以下のコマンドで3306ポートのキャプチャーを実行しておきます。
```
$ sudo tshark  -O mysql -Y 'tcp.dstport==3306' -V
```

例えば、MySQLで接続して「SELECT COUNT(\*) FROM city;」と実行した場合、tsharkは次のような出力となります。
```
Frame 541: 98 bytes on wire (784 bits), 98 bytes captured (784 bits) on interface en0, id 0
Ethernet II, Src: Apple_7d:82:4a (a4:83:e7:7d:82:4a), Dst: Buffalo_42:fb:fe (4c:e6:76:42:fb:fe)
Internet Protocol Version 4, Src: 192.168.3.7, Dst: 192.168.3.19
Transmission Control Protocol, Src Port: 50420, Dst Port: 3306, Seq: 61, Ack: 24483, Len: 32
MySQL Protocol
    Packet Length: 28
    Packet Number: 0
    Request Command Query
        Command: Query (3)
        Statement: 
    Payload: 0153454c45435420434f554e54282a292046524f4d2063697479
        [Expert Info (Warning/Undecoded): FIXME - dissector is incomplete]
            [FIXME - dissector is incomplete]
            [Severity level: Warning]
            [Group: Undecoded]
```

上記の「Payload:」以降に出力されている16進数を文字列に戻すとSQL文になります。
これによって、socatでローカルで3306で起動し、tsharkでmysqlとして解釈させることでどのようなSQL文が発行されているのかの調査に捗ります。
```
$ echo 0153454c45435420434f554e54282a292046524f4d2063697479 | xxd -r -p
SELECT COUNT(*) FROM city
```

また、localhostの3306で起動しているような場合には、wiresharkを起動してMySQLで発行された調査に捗ります。

- cf. https://troushoo.blog.fc2.com/blog-entry-511.html




