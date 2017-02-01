# 概要
zookeeperとはもともとはHadoopのサブプロジェクトとして稼働していたが、後にApacheのトッププロジェクトとなった。
HadoopやHBaseなどの分散データのステータス管理などに利用されている。

zookeeperは、クラスタの中での調整や共有データを強固な同期メカニズムを使って保っている仕組みです。  
次のようなものがzookeeperによって提供されています。
- 名前サービス(名前によるノードの識別)
- 設定管理
- クラスタ管理
- リーダー選択
- ロックと同期サービス
- 高信頼性のデータレジストリの提供

以下の用語を押さえておく
- Leader
 - もしleaderへの接続がfailedになったとしてもatomicに復旧をさせる
- Follower
 - Leaderの指示に従うzookeeperサーバ
- Ensemble
 - zookeeperサーバのグループ。最小ノード数は3つ必要である
- znode
 - /から始まる木構造のディレクトリツリーを表す。Unixのディレクトリツリーの概念と似ている
 - 各znodeには1MBまでのデータを格納することができる。

znodeのステータスとして重要なのは次のデータである。
- version number
- ACL
- Timestamp
- Data Length

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



# zkCli.shについて
zookeeperの操作に重要なzkCli.shコマンドについては一通りの機能が知っておいたほうが今後も重宝すると思うので載せておく。

### zkCli.shを使ってみる
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

接続を閉じるにはcloseというのもあります。これは、別のzookeeperに再度connectを使って接続しなおしたい場合などに利用するので普段はつかわないかもしれません。
```
[zk: localhost:2181(CONNECTED) 9] close
2017-02-01 09:46:13,479 [myid:] - INFO  [main:ZooKeeper@684] - Session: 0x159f03881bf0014 closed
[zk: localhost:2181(CLOSED) 10] 2017-02-01 09:46:13,481 [myid:] - INFO  [main-EventThread:ClientCnxn$EventThread@519] - EventThread shut down for session: 0x159f03881bf0014

[zk: localhost:2181(CLOSED) 10] 
```

### シーケンシャルなznodeを作成する
sオプションを与えるとシーケンシャルに番号を振ってくれます。以下の礼をみるとすぐにわかります。
```
[zk: localhost:2181(CONNECTED) 3] create -s /FirstZnode second-data
Created /FirstZnode0000000017
[zk: localhost:2181(CONNECTED) 4] create -s /FirstZnode second-data
Created /FirstZnode0000000018
[zk: localhost:2181(CONNECTED) 5] create -s /FirstZnode second-data
Created /FirstZnode0000000019
```

シーケンシャルな仕組みはロックや同期で重要な意味を持つようです。

### 接続を解除したら消える一時的なデータ(エフェメラルznode)を作成する
eオプションでephemeralなznodeを作成できる。  

これは接続が解除されるとそのznodeがなくなってしまうデータである。以下にcreateとcreate -eの比較例を載せる。

```
[zk: localhost:2181(CONNECTED) 39] create /hoge
[zk: localhost:2181(CONNECTED) 40] create /hoge hoge
Created /hoge
[zk: localhost:2181(CONNECTED) 41] create -e /fuga fuga
Created /fuga
[zk: localhost:2181(CONNECTED) 42] get /hoge
hoge
cZxid = 0x17a
ctime = Wed Feb 01 10:15:39 JST 2017
mZxid = 0x17a
mtime = Wed Feb 01 10:15:39 JST 2017
pZxid = 0x17a
cversion = 0
dataVersion = 0
aclVersion = 0
ephemeralOwner = 0x0
dataLength = 4
numChildren = 0
[zk: localhost:2181(CONNECTED) 43] get /fuga
fuga
cZxid = 0x17b
ctime = Wed Feb 01 10:15:44 JST 2017
mZxid = 0x17b
mtime = Wed Feb 01 10:15:44 JST 2017
pZxid = 0x17b
cversion = 0
dataVersion = 0
aclVersion = 0
ephemeralOwner = 0x159f03881bf0017
dataLength = 4
numChildren = 0
```

上記で作成したので、ここで一度切断(close)して、再接続(connect)します。
```
[zk: localhost:2181(CONNECTED) 44] close
(省略)
[zk: localhost:2181(CLOSED) 45] connect
(省略)
```

先ほど作成した値を取得すると/hogeは取れて、/fugaは取れないことが確認できました。/fugaのznodeはもう存在していません。
```
[zk: localhost:2181(CONNECTED) 46] get /hoge
hoge
cZxid = 0x17a
ctime = Wed Feb 01 10:15:39 JST 2017
mZxid = 0x17a
mtime = Wed Feb 01 10:15:39 JST 2017
pZxid = 0x17a
cversion = 0
dataVersion = 0
aclVersion = 0
ephemeralOwner = 0x0
dataLength = 4
numChildren = 0
[zk: localhost:2181(CONNECTED) 47] get /fuga
Node does not exist: /fuga
```

このエフェメラルznodeはリーダー選出の際に重要な役割を持つようです。

### znodeの統計情報を表示する(stat, get, ls2)
stat, get, ls2の違いを理解しておく。ほとんど同じだが出力結果をみるとわかりやすい。

statの場合
```
[zk: localhost:2181(CONNECTED) 20] stat /zktest2
cZxid = 0x144
ctime = Wed Feb 01 09:21:38 JST 2017
mZxid = 0x153
mtime = Wed Feb 01 09:33:36 JST 2017
pZxid = 0x144
cversion = 0
dataVersion = 10
aclVersion = 1
ephemeralOwner = 0x0
dataLength = 6
numChildren = 0
```

getの場合
```
[zk: localhost:2181(CONNECTED) 21] get /zktest2 
fuga11
cZxid = 0x144
ctime = Wed Feb 01 09:21:38 JST 2017
mZxid = 0x153
mtime = Wed Feb 01 09:33:36 JST 2017
pZxid = 0x144
cversion = 0
dataVersion = 10
aclVersion = 1
ephemeralOwner = 0x0
dataLength = 6
numChildren = 0
```

ls2の場合
```
[zk: localhost:2181(CONNECTED) 22] ls2 /zktest2
[]
cZxid = 0x144
ctime = Wed Feb 01 09:21:38 JST 2017
mZxid = 0x153
mtime = Wed Feb 01 09:33:36 JST 2017
pZxid = 0x144
cversion = 0
dataVersion = 10
aclVersion = 1
ephemeralOwner = 0x0
dataLength = 6
numChildren = 0
```

getとstatの違いとしては、statはgetからznodeの値を表示しなくなった版であることがわかる。
また、ls2というのはlsの結果と、statの結果両方を出力してくれることがわかる。ls2にはwatch機能がある。

### znodeを削除する
znode単体を削除するにはdeleteを利用します。
```
delete /path/to_delete
```

znodeをディレクトリとして削除する場合、rmrを利用して削除することができます。
```
rmr /path/to_delete
```

### コマンド実行履歴をみて実行する
zkCli.shの対話モードでは実行したコマンドの履歴を見ることができます。
```
[zk: 127.0.0.1:2181(CONNECTED) 4] history
0 - history
1 - ls /
2 - ls /zookeeper
3 - get /zookeeper
4 - history
```

履歴番号1番のコマンドを実行したければredoのあとに番号を指定すれば良い。
```
[zk: 127.0.0.1:2181(CONNECTED) 4] redo 1
[isr_change_notification, test, zookeeper, admin, consumers, cluster, config, controller, zktest1, brokers, zktest2, controller_epoch]
```

### コマンドラインから呼び出す
対話モードでなくコマンドラインから直接呼び出すといったことも実は可能です。
```
$ bin/zkCli.sh -server 127.0.0.1:2181 get /zookeeper/quota
(中略)
cZxid = 0x0
ctime = Thu Jan 01 09:00:00 JST 1970
mZxid = 0x0
mtime = Thu Jan 01 09:00:00 JST 1970
pZxid = 0x0
cversion = 0
dataVersion = 0
aclVersion = 0
ephemeralOwner = 0x0
dataLength = 0
numChildren = 0
```

上記の意味
- https://zookeeper.apache.org/doc/trunk/zookeeperProgrammers.html

上記から抜粋した。
- czxid
 - The zxid of the change that caused this znode to be created.
- mzxid
 - The zxid of the change that last modified this znode.
- pzxid
 - The zxid of the change that last modified children of this znode.
- ctime
 - The time in milliseconds from epoch when this znode was created.
- mtime
 - The time in milliseconds from epoch when this znode was last modified.
- version
 - The number of changes to the data of this znode.
- cversion
 - The number of changes to the children of this znode.
- aversion
 - The number of changes to the ACL of this znode.
- ephemeralOwner
 - The session id of the owner of this znode if the znode is an ephemeral node. If it is not an ephemeral node, it will be zero.
- dataLength
 - The length of the data field of this znode.
- numChildren
 - The number of children of this znode.


### 認証モード
この辺のコンフルが非常に役立ちそう
- https://ihong5.wordpress.com/2014/07/24/apache-zookeeper-setting-acl-in-zookeeper-client/

認証方式には次のschemeが存在するようだ
- world
- addauth
- digest
- host
- ip

以下のサンプルのようにgetAclしたときに表示されるcdrwaについて何を表しているのかというと権限を表している。  
```
[zk: 127.0.0.1:2181(CONNECTED) 31] getAcl /zktest                 
'world,'anyone
: cdrwa
```

zkCli.shのソースコードZooKeeperMain.javaをみると次の説明があった。
```
private static String getPermString(int perms) {
    StringBuilder p = new StringBuilder();
    if ((perms & ZooDefs.Perms.CREATE) != 0) {
        p.append('c');
    }
    if ((perms & ZooDefs.Perms.DELETE) != 0) {
        p.append('d');
    }
    if ((perms & ZooDefs.Perms.READ) != 0) {
        p.append('r');
    }
    if ((perms & ZooDefs.Perms.WRITE) != 0) {
        p.append('w');
    }
    if ((perms & ZooDefs.Perms.ADMIN) != 0) {
        p.append('a');
    }
    return p.toString();
}
```

### アクセス制限をかけてみる。
```
[zk: 127.0.0.1:2181(CONNECTED) 30] create /zktest "hoge"          
Created /zktest
[zk: 127.0.0.1:2181(CONNECTED) 31] getAcl /zktest                 
'world,'anyone
: cdrwa
```

権限をrとwだけにセットして変更する。
```
[zk: 127.0.0.1:2181(CONNECTED) 32] setAcl /zktest world:anyone:rw
cZxid = 0x13b
ctime = Wed Feb 01 09:15:56 JST 2017
mZxid = 0x13b
mtime = Wed Feb 01 09:15:56 JST 2017
pZxid = 0x13b
cversion = 0
dataVersion = 0
aclVersion = 1
ephemeralOwner = 0x0
dataLength = 4
numChildren = 0
[zk: 127.0.0.1:2181(CONNECTED) 34] getAcl /zktest                
'world,'anyone
: rw
```

### IPアドレス認証する

特定のIPアドレスに設定するにはip:<IPv4-address>:<permission-set>の形式を設定すると良い。
/zktest1と/zktest2の２つを作ってIPアドレス認証が効くことを確認する。127.0.0.1のローカルホストに接続して作業すると仮定する。
```
$ bin/zkCli.sh -server 127.0.0.1:2181
...
[zk: 127.0.0.1:2181(CONNECTED) 42] create /zktest1 hoge1
Created /zktest1
[zk: 127.0.0.1:2181(CONNECTED) 43] create /zktest2 hoge2
Created /zktest2
```

/zktest1はIPアドレス認証を許可しないアドレスを、/zktest2には許可する127.0.0.1をセットする
```
[zk: 127.0.0.1:2181(CONNECTED) 44] setAcl /zktest1 ip:1.0.0.1:rw   
cZxid = 0x143
ctime = Wed Feb 01 09:21:33 JST 2017
mZxid = 0x143
mtime = Wed Feb 01 09:21:33 JST 2017
pZxid = 0x143
cversion = 0
dataVersion = 0
aclVersion = 1
ephemeralOwner = 0x0
dataLength = 5
numChildren = 0
[zk: 127.0.0.1:2181(CONNECTED) 45] setAcl /zktest2 ip:127.0.0.1:rw
cZxid = 0x144
ctime = Wed Feb 01 09:21:38 JST 2017
mZxid = 0x144
mtime = Wed Feb 01 09:21:38 JST 2017
pZxid = 0x144
cversion = 0
dataVersion = 0
aclVersion = 1
ephemeralOwner = 0x0
dataLength = 5
numChildren = 0
[zk: 127.0.0.1:2181(CONNECTED) 46] getAcl /zktest1
'ip,'1.0.0.1
: rw
[zk: 127.0.0.1:2181(CONNECTED) 47] getAcl /zktest2
'ip,'127.0.0.1
: rw
```

接続して確認してみると/zktest1は拒否しているが、/zktest2は取得できることが確認できる。
```
[zk: 127.0.0.1:2181(CONNECTED) 48] get /zktest1
Authentication is not valid : /zktest1
[zk: 127.0.0.1:2181(CONNECTED) 49] get /zktest2
hoge2
cZxid = 0x144
ctime = Wed Feb 01 09:21:38 JST 2017
mZxid = 0x144
mtime = Wed Feb 01 09:21:38 JST 2017
pZxid = 0x144
cversion = 0
dataVersion = 0
aclVersion = 1
ephemeralOwner = 0x0
dataLength = 5
numChildren = 0
```

### 特定のznodeに別のznodeが追加・削除などされたことを検知する
次のようにls <path> watchとしてコマンドを実行する
```
[zk: localhost:2181(CONNECTED) 6] ls /zktest watch
[]
```

例えば、別のターミナルなどで次のように/zktest配下に作成すると、
```
[zk: localhost:2181(CONNECTED) 9] create /zktest/aaa bbb
Created /zktest/aaa
```

watchしていた方に次のように検知したことを表示してくれるようだ。
```
[zk: localhost:2181(CONNECTED) 7] 
WATCHER::

WatchedEvent state:SyncConnected type:NodeChildrenChanged path:/zktest
```

watchは一度しか検知されないようなので、再度検知させる場合にはもう一度実行する必要がある。
なお、今度は作成した次のznodeを削除した場合にも画面上に変化したことを知らせてくれるようである。
```
delete /zktest/aaa
```

１点注意点としては、/zktestに対してsetして値を設定しようとした場合はlsのwatchには検知されない。
この場合にはget <path> watchを使うことを覚えておくと良い。

### 特定のznodeの値が変更されたことを検知する。

```
[zk: localhost:2181(CONNECTED) 5] get /zktest watch
hoge
cZxid = 0x155
ctime = Wed Feb 01 09:34:23 JST 2017
mZxid = 0x15d
mtime = Wed Feb 01 09:49:41 JST 2017
pZxid = 0x158
cversion = 2
dataVersion = 4
aclVersion = 0
ephemeralOwner = 0x0
dataLength = 5
numChildren = 0
```

別のターミナルなどから次のように値を変更すると
```
[zk: localhost:2181(CONNECTED) 15] set /zktest fuga
```

先ほどwatchした画面に変更通知が表示される。
```
[zk: localhost:2181(CONNECTED) 6] 
WATCHER::

WatchedEvent state:SyncConnected type:NodeDataChanged path:/zktest
```

この変更通知もlsの場合と同様で一度しか検知してくれないようだ。

### printwatchesについて
lsやgetでも一度しかwatchで変更があった場合に表示されないので、これがある意味がわからないがデフォルトは「printwatches on」となっているようだ。
つまり、ls <path> watchなどとすると必ず変更がwatchできるようになっている。

watchが一度切りではなく常に検知できるのであればこのオプションがあるのが意味がわかるが不明(自分がよくわかっていない機能があるのかもしれない)

### クォータについて
割り当てられたクォータをユーザーが超過した場合、ZooKeeper は WARN メッセージを出力します。メッセージは、ZooKeeper のログに記録されます。

listquota, setquota, delquotaなどはここで利用するようです。

詳しくはまだ調べていないので以下を参考にしてください。
- http://oss.infoscience.co.jp/hadoop/zookeeper/docs/r3.3.1/zookeeperQuotas.html

# 動作仕様について
### どのようにしてclientはserverへの接続を保っているのか?
TODO


# TODO
- zkCli.shについてもっと調べる
 - helpで表示されるsync, listquota, setquota, delquotaなどについてまとめておく
 - quotaについては http://oss.infoscience.co.jp/hadoop/zookeeper/docs/r3.3.1/zookeeperQuotas.html あたり?
- https://www.tutorialspoint.com/zookeeper/zookeeper_quick_guide.htm
 - この辺もっと読む
- https://ihong5.wordpress.com/2014/07/24/apache-zookeeper-setting-acl-in-zookeeper-client/
 - 認証も読む

