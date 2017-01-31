# 概要
zookeeperについてまとめておくこと

# 詳細

### スタンドアロンでzookeeperを稼働させる。
以下にも記載していますが、再掲する。
- https://github.com/tsuyopon/cpp/tree/master/zookeeper

ほとんどはZooKeeper Getting Started Guideを参考にしています。
- https://zookeeper.apache.org/doc/r3.1.2/zookeeperStarted.html

```
$ wget http://ftp.jaist.ac.jp/pub/apache/zookeeper/zookeeper-3.4.9/zookeeper-3.4.9.tar.gz
$ tar zxvf zookeeper-3.4.9.tar.gz
$ cd zookeeper-3.4.9
$ vim conf/zoo.cfg
tickTime=2000
dataDir=/var/zookeeper
clientPort=2181
$
$ sudo ./bin/zkServer.sh start
/usr/bin/java
ZooKeeper JMX enabled by default
Using config: /Users/tsuyoshi/SOURCE/zookeeper/bin/../conf/zoo.cfg
Starting zookeeper ... STARTED
$
$ ps auxww | grep -i zookeeper
root            4353   0.0  0.6  3735684  25976 s006  S    12:31PM   0:00.33 /usr/bin/java -Dzookeeper.log.dir=/Users/tsuyoshi/SOURCE/zookeeper/bin/../logs -Dzookeeper.log.file=zookeeper-root-server-tsuyoshi.local.log -Dzookeeper.root.logger=INFO,CONSOLE -XX:+HeapDumpOnOutOfMemoryError -XX:OnOutOfMemoryError=kill -9 %p -cp /Users/tsuyoshi/SOURCE/zookeeper/bin/../build/classes:/Users/tsuyoshi/SOURCE/zookeeper/bin/../build/lib/*.jar:/Users/tsuyoshi/SOURCE/zookeeper/bin/../lib/*.jar:/Users/tsuyoshi/SOURCE/zookeeper/bin/../zookeeper-*.jar:/Users/tsuyoshi/SOURCE/zookeeper/bin/../src/java/lib/*.jar:/Users/tsuyoshi/SOURCE/zookeeper/bin/../conf: -Xmx1000m -Dcom.sun.management.jmxremote -Dcom.sun.management.jmxremote.local.only=false org.apache.zookeeper.server.quorum.QuorumPeerMain /Users/tsuyoshi/SOURCE/zookeeper/bin/../conf/zoo.cfg
```

### zookeeperサーバを稼働する
次のコマンドでzookeeperサーバを稼働させることができる。
```
$ zkServer.sh start
```

設定ファイルも指定したい場合には引数としてstartのあとに設定ファイルへのパスを指定すれば良い。
```
$ zkServer.sh start /path/to/zoo.cnf
```

zkServer.shにはいくつかのオプションがある。
```
$ bin/zkServer.sh -h
ZooKeeper JMX enabled by default
Using config: /home/tsuyoshi/zookeeper-3.4.9/bin/../conf/zoo.cfg
Usage: bin/zkServer.sh {start|start-foreground|stop|restart|status|upgrade|print-cmd}
```

### 利用できるコマンドを確認する
zookeeperソースコード中のbinディレクトリの中を見てみる。実態はシェルスクリプトだったりするので時間があるときにでも中を覗いてみるとよさそう。
```
$ file bin/*
bin/README.txt:   ASCII text
bin/zkCleanup.sh: a /usr/bin/env bash script, ASCII text executable
bin/zkCli.cmd:    DOS batch file, ASCII text
bin/zkCli.sh:     a /usr/bin/env bash script, ASCII text executable
bin/zkEnv.cmd:    DOS batch file, ASCII text
bin/zkEnv.sh:     a /usr/bin/env bash script, ASCII text executable
bin/zkServer.cmd: DOS batch file, ASCII text
bin/zkServer.sh:  a /usr/bin/env bash script, ASCII text executable
```

- zkCleanup.sh
 - confのdataDirで設定したディレクトリやトランザクションログなどにある不要なものを削除し、不要なファイルを削減する
- zkCli.sh
 - zookeeper上のデータを操作するためのcliインターフェース
- zkEnv.sh
 - zookeeper用の環境変数を設定しているだけ(100行弱しか行数がないので中を覗いた方が理解が早いかも)
 - CLASSPATH, LIBPATH, ZOO_LOG_DIR, ZOOCFGDIR, ZOOCFGなどの環境変数を設定しているだけです
- zkServer.sh
 - zookeeperサーバを起動するためのシェルスクリプト


### zkCli.shを使う
zkCli.shを使ってみることにする。
とりあえず使ってみるということで以下の入門記事を元にコマンドを実行してみることにする。CとJAVAのInterfaceが以下の記事で紹介されているが、今回はJAVAのInterfaceであるzkCli.shを利用してみることにする。
- http://oss.infoscience.co.jp/hadoop/zookeeper/docs/r3.3.1/zookeeperStarted.html

以下はzookeeperの初回起動時にアクセスして/zk_testにmy_dataを入れたり、その値を取得したり、入っている値を変更、削除するサンプルです。
127.0.0.1:2181に接続する場合には「bin/zkCli.sh」と引数なしの実行でも問題ありません。
```
$ bin/zkCli.sh -server 127.0.0.1:2181
Connecting to 127.0.0.1:2181
(中略)
WATCHER::

WatchedEvent state:SyncConnected type:None path:null
[zk: 127.0.0.1:2181(CONNECTED) 0] ls /
[isr_change_notification, zookeeper, admin, consumers, cluster, config, controller, brokers, controller_epoch]
[zk: 127.0.0.1:2181(CONNECTED) 1] create /zk_test my_data
Created /zk_test
[zk: 127.0.0.1:2181(CONNECTED) 2] ls /
[isr_change_notification, zookeeper, admin, zk_test, consumers, cluster, config, controller, brokers, controller_epoch]
[zk: 127.0.0.1:2181(CONNECTED) 3] get /zk_test
my_data
cZxid = 0x124
ctime = Wed Feb 01 08:28:29 JST 2017
mZxid = 0x124
mtime = Wed Feb 01 08:28:29 JST 2017
pZxid = 0x124
cversion = 0
dataVersion = 0
aclVersion = 0
ephemeralOwner = 0x0
dataLength = 7
numChildren = 0
[zk: 127.0.0.1:2181(CONNECTED) 4] set /zk_test junk
cZxid = 0x124
ctime = Wed Feb 01 08:28:29 JST 2017
mZxid = 0x125
mtime = Wed Feb 01 08:28:51 JST 2017
pZxid = 0x124
cversion = 0
dataVersion = 1
aclVersion = 0
ephemeralOwner = 0x0
dataLength = 4
numChildren = 0
[zk: 127.0.0.1:2181(CONNECTED) 5] get /zk_test     
junk
cZxid = 0x124
ctime = Wed Feb 01 08:28:29 JST 2017
mZxid = 0x125
mtime = Wed Feb 01 08:28:51 JST 2017
pZxid = 0x124
cversion = 0
dataVersion = 1
aclVersion = 0
ephemeralOwner = 0x0
dataLength = 4
numChildren = 0
[zk: 127.0.0.1:2181(CONNECTED) 6] delete /zk_test
[zk: 127.0.0.1:2181(CONNECTED) 7] ls /           
[isr_change_notification, zookeeper, admin, consumers, cluster, config, controller, brokers, controller_epoch]
```

上記が簡単な使い方となります。どのようなコマンドがあるのかを知るにはhelpにより表示することができます。
```
[zk: 127.0.0.1:2181(CONNECTED) 8] help
ZooKeeper -server host:port cmd args
	connect host:port
	get path [watch]
	ls path [watch]
	set path data [version]
	rmr path
	delquota [-n|-b] path
	quit 
	printwatches on|off
	create [-s] [-e] path data acl
	stat path [watch]
	close 
	ls2 path [watch]
	history 
	listquota path
	setAcl path acl
	getAcl path
	sync path
	redo cmdno
	addauth scheme auth
	delete path [version]
	setquota -n|-b val path
```


