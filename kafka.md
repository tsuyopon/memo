# 概要
kafka関連のメモについて

# 詳細

### zookeeper, producer, broker, consumerの関係性について
以下の図が非常に理解に役立つ
- http://inokara.hateblo.jp/entry/2016/05/01/113254

要点だけ記述しておくと
- producerとconsumerはzookeeperからbroker情報を取得する
- brokerはzookeeperにtopicなどの情報を登録する
- producerはbrokerにメッセージの送信を行う
- consumerはbrokerからメッセージの取得を行う

### スタンドアロンで動かす
tgzパッケージをdownloadしてスタンドアロンですぐに動作確認することができます。

次の資料を元にして確認を行った。
- https://kafka.apache.org/quickstart

パッケージ取得後、次のようにして展開してディレクトリに移動する。
```
$ tar xzvf kafka_2.11-0.10.1.0.tgz
$ cd kafka_2.11-0.10.1.0
```

余談だが、このディレクトリの中からbin/中のコマンドを何度も呼び出すのでscreenやtmuxなどを動かして実行したほうがいいかもしれない。

まずはzookeeperを動かす。
```
$ bin/zookeeper-server-start.sh config/zookeeper.properties
```

続いて、kafkaサーバを立ち上げます。
```
$ bin/kafka-server-start.sh config/server.properties
```

topicを作成してみます。ここでは例として３つほど作成してみます。
```
$ bin/kafka-topics.sh --create --zookeeper localhost:2181 --replication-factor 1 --partitions 1 --topic test
Created topic "test".
$ bin/kafka-topics.sh --create --zookeeper localhost:2181 --replication-factor 1 --partitions 1 --topic test2
Created topic "test2".
$ bin/kafka-topics.sh --create --zookeeper localhost:2181 --replication-factor 1 --partitions 1 --topic test3
Created topic "test3".
```

上記のオプションについて簡単に説明します。
- replication-factor
 - kafkaクラスタ内に存在するkafkaブローカーの何台にトピックを作成するか指定できます、なのでkafkaブローカーが1つしかない場合は1以上は指定できません
- partitions
 - topicをいくつのパーティションに分割するかを指定します。

続いて、登録されているすべてのトピックを確認します。
```
$ bin/kafka-topics.sh --list --zookeeper localhost:2181
test
test2
test3
```

作成したトピックtestに対してメッセージを送信してみます。
「Hello world! This is test message of test」というのはここで入力するメッセージとなる。
```
$ bin/kafka-console-producer.sh --broker-list localhost:9092 --topic test
Hello world!
This is test message of test
(ここで Ctrl + Dを押すと終了する)
```

続いて、consumerを立ち上げてみることにする。少し待つと先ほど送信したデータが表示されるようになる。  
「–from-beginning」を指定するとトピックに送信されたメッセージを最初からすべて取得することができます。  
なお、接続した時点からのメッセージのみを取得したい場合は「–from-beginning」オプションを指定しないことにより取得できます。  
```
$ bin/kafka-console-consumer.sh --bootstrap-server localhost:9092 --topic test --from-beginning
Hello world!
This is test message of test
```

### topicを削除したい

ややわかりにくいのでメモしておくことにする。testというトピックを削除することを想定としている。

```
$ kafka-topics.sh --delete --zookeeper localhost:2181 --topic test
$ bin/kafka-topics.sh --list --zookeeper localhost:2181
test - marked for deletion
test2
test3
```

実は「- marked for deletion」はマークが付けられただけで全く削除されていない。

この場合にはまずkafkaの設定ファイル/usr/local/etc/kafka/server.propertiesに次の1行が入っていることで削除が有効になっているかどうかを確認します。
```
delete.topic.enable=true
```

そして、設定を有効にさせるためにkafkaを再起動します。これでtopicが削除できるようになります。(多分、zookeeperの再起動は不要なはず...)
```
$ kafka-server-stop.sh /usr/local/etc/kafka/server.properties
```

先ほど実行したtestトピック削除してlistで確認します。
```
$ kafka-topics.sh --delete --zookeeper localhost:2181 --topic test
$ kafka-topics.sh --list --zookeeper localhost:2181
```

listでの表示は少し(10秒程度!?)待たないと反映されないことがあります。
消えない場合には、kafkaのconsumerが接続されている可能性が高いのですべてのconsumerを停止してください。

- 参考
 - http://stackoverflow.com/questions/33537950/how-to-delete-a-topic-in-apache-kafka/33538299

### describeでtopicの詳細を確認する

例えば、testというトピックの詳細を確認して次の出力となった場合
```
$ bin/kafka-topics.sh --describe --zookeeper localhost:2181 --topic test
Topic:test    PartitionCount:1 ReplicationFactor:3 Configs:
   Topic:test Partition:0 Leader:0 Replicas:0,2,1 Isr:0,2,1
```
- PartitionCountはこのトピックを何台で保持しているかを表す。


### パーティションカウントを変更する
```
$ bin/kafka-topics.sh —zookeeper localhost:2181 --alter --topic topic_name --parti-tions count
```























