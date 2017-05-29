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

続いて、kafkaサーバを立ち上げます。これはbrokerを指しています。
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
- "Leader" is the node responsible for all reads and writes for the given partition. Each node will be the leader for a randomly selected portion of the partitions.
- "Replicas" is the list of nodes that replicate the log for this partition regardless of whether they are the leader or even if they are currently alive.
- "Isr" is the set of "in-sync" replicas. This is the subset of the replicas list that is currently alive and caught-up to the leader.
  - https://ishiis.net/2016/07/31/kafka-cluster-and-zookeeper-ensemble/

### パーティションカウントを変更する
```
$ bin/kafka-topics.sh —zookeeper localhost:2181 --alter --topic topic_name --parti-tions count
```

### kafka-topics.shのその他のオプション
```
$ bin/kafka-topics.sh
Create, delete, describe, or change a topic.
Option                                   Description                            
------                                   -----------                            
--alter                                  Alter the number of partitions,        
                                           replica assignment, and/or           
                                           configuration for the topic.         
--config <name=value>                    A topic configuration override for the 
                                           topic being created or altered.The   
                                           following is a list of valid         
                                           configurations:                      
                                         	cleanup.policy                        
                                         	compression.type                      
                                         	delete.retention.ms                   
                                         	file.delete.delay.ms                  
                                         	flush.messages                        
                                         	flush.ms                              
                                         	follower.replication.throttled.       
                                           replicas                             
                                         	index.interval.bytes                  
                                         	leader.replication.throttled.replicas 
                                         	max.message.bytes                     
                                         	message.format.version                
                                         	message.timestamp.difference.max.ms   
                                         	message.timestamp.type                
                                         	min.cleanable.dirty.ratio             
                                         	min.compaction.lag.ms                 
                                         	min.insync.replicas                   
                                         	preallocate                           
                                         	retention.bytes                       
                                         	retention.ms                          
                                         	segment.bytes                         
                                         	segment.index.bytes                   
                                         	segment.jitter.ms                     
                                         	segment.ms                            
                                         	unclean.leader.election.enable        
                                         See the Kafka documentation for full   
                                           details on the topic configs.        
--create                                 Create a new topic.                    
--delete                                 Delete a topic                         
--delete-config <name>                   A topic configuration override to be   
                                           removed for an existing topic (see   
                                           the list of configurations under the 
                                           --config option).                    
--describe                               List details for the given topics.     
--disable-rack-aware                     Disable rack aware replica assignment  
--force                                  Suppress console prompts               
--help                                   Print usage information.               
--if-exists                              if set when altering or deleting       
                                           topics, the action will only execute 
                                           if the topic exists                  
--if-not-exists                          if set when creating topics, the       
                                           action will only execute if the      
                                           topic does not already exist         
--list                                   List all available topics.             
--partitions <Integer: # of partitions>  The number of partitions for the topic 
                                           being created or altered (WARNING:   
                                           If partitions are increased for a    
                                           topic that has a key, the partition  
                                           logic or ordering of the messages    
                                           will be affected                     
--replica-assignment                     A list of manual partition-to-broker   
  <broker_id_for_part1_replica1 :          assignments for the topic being      
  broker_id_for_part1_replica2 ,           created or altered.                  
  broker_id_for_part2_replica1 :                                                
  broker_id_for_part2_replica2 , ...>                                           
--replication-factor <Integer:           The replication factor for each        
  replication factor>                      partition in the topic being created.
--topic <topic>                          The topic to be create, alter or       
                                           describe. Can also accept a regular  
                                           expression except for --create option
--topics-with-overrides                  if set when describing topics, only    
                                           show topics that have overridden     
                                           configs                              
--unavailable-partitions                 if set when describing topics, only    
                                           show partitions whose leader is not  
                                           available                            
--under-replicated-partitions            if set when describing topics, only    
                                           show under replicated partitions     
--zookeeper <urls>                       REQUIRED: The connection string for    
                                           the zookeeper connection in the form 
                                           host:port. Multiple URLS can be      
                                           given to allow fail-over.  
```

### kafka-console-consumer.shのその他のオプション
実際に試せていないが有用そうなオプションを確認しておくことにする。(確認したkafkaのバージョンはkafka_2.11-0.10.1.0)
```
$ bin/kafka-console-consumer.sh
The console consumer is a tool that reads data from Kafka and outputs it to standard output.
Option                                  Description                            
------                                  -----------                            
--blacklist <blacklist>                 Blacklist of topics to exclude from    
                                          consumption.                         
--bootstrap-server <server to connect   REQUIRED (unless old consumer is       
  to>                                     used): The server to connect to.     
--consumer-property <consumer_prop>     A mechanism to pass user-defined       
                                          properties in the form key=value to  
                                          the consumer.                        
--consumer.config <config file>         Consumer config properties file. Note  
                                          that [consumer-property] takes       
                                          precedence over this config.         
--csv-reporter-enabled                  If set, the CSV metrics reporter will  
                                          be enabled                           
--delete-consumer-offsets               If specified, the consumer path in     
                                          zookeeper is deleted when starting up
--enable-systest-events                 Log lifecycle events of the consumer   
                                          in addition to logging consumed      
                                          messages. (This is specific for      
                                          system tests.)                       
--formatter <class>                     The name of a class to use for         
                                          formatting kafka messages for        
                                          display. (default: kafka.tools.      
                                          DefaultMessageFormatter)             
--from-beginning                        If the consumer does not already have  
                                          an established offset to consume     
                                          from, start with the earliest        
                                          message present in the log rather    
                                          than the latest message.             
--key-deserializer <deserializer for                                           
  key>                                                                         
--max-messages <Integer: num_messages>  The maximum number of messages to      
                                          consume before exiting. If not set,  
                                          consumption is continual.            
--metrics-dir <metrics directory>       If csv-reporter-enable is set, and     
                                          this parameter isset, the csv        
                                          metrics will be outputed here        
--new-consumer                          Use the new consumer implementation.   
                                          This is the default.                 
--offset <consume offset>               The offset id to consume from (a non-  
                                          negative number), or 'earliest'      
                                          which means from beginning, or       
                                          'latest' which means from end        
                                          (default: latest)                    
--partition <Integer: partition>        The partition to consume from.         
--property <prop>                       The properties to initialize the       
                                          message formatter.                   
--skip-message-on-error                 If there is an error when processing a 
                                          message, skip it instead of halt.    
--timeout-ms <Integer: timeout_ms>      If specified, exit if no message is    
                                          available for consumption for the    
                                          specified interval.                  
--topic <topic>                         The topic id to consume on.            
--value-deserializer <deserializer for                                         
  values>                                                                      
--whitelist <whitelist>                 Whitelist of topics to include for     
                                          consumption.                         
--zookeeper <urls>                      REQUIRED (only when using old          
                                          consumer): The connection string for 
                                          the zookeeper connection in the form 
                                          host:port. Multiple URLS can be      
                                          given to allow fail-over.      
```

特に次のオプションが使えそうだ(topicやzookeeperなどの基本的なものを除く)
- blacklist 
- whitelist

### kafka-console-producer.shのその他のオプション
```
$ bin/kafka-console-producer.sh
Read data from standard input and publish it to Kafka.
Option                                   Description                            
------                                   -----------                            
--batch-size <Integer: size>             Number of messages to send in a single 
                                           batch if they are not being sent     
                                           synchronously. (default: 200)        
--broker-list <broker-list>              REQUIRED: The broker list string in    
                                           the form HOST1:PORT1,HOST2:PORT2.    
--compression-codec [compression-codec]  The compression codec: either 'none',  
                                           'gzip', 'snappy', or 'lz4'.If        
                                           specified without value, then it     
                                           defaults to 'gzip'                   
--key-serializer <encoder_class>         The class name of the message encoder  
                                           implementation to use for            
                                           serializing keys. (default: kafka.   
                                           serializer.DefaultEncoder)           
--line-reader <reader_class>             The class name of the class to use for 
                                           reading lines from standard in. By   
                                           default each line is read as a       
                                           separate message. (default: kafka.   
                                           tools.                               
                                           ConsoleProducer$LineMessageReader)   
--max-block-ms <Long: max block on       The max time that the producer will    
  send>                                    block for during a send request      
                                           (default: 60000)                     
--max-memory-bytes <Long: total memory   The total memory used by the producer  
  in bytes>                                to buffer records waiting to be sent 
                                           to the server. (default: 33554432)   
--max-partition-memory-bytes <Long:      The buffer size allocated for a        
  memory in bytes per partition>           partition. When records are received 
                                           which are smaller than this size the 
                                           producer will attempt to             
                                           optimistically group them together   
                                           until this size is reached.          
                                           (default: 16384)                     
--message-send-max-retries <Integer>     Brokers can fail receiving the message 
                                           for multiple reasons, and being      
                                           unavailable transiently is just one  
                                           of them. This property specifies the 
                                           number of retires before the         
                                           producer give up and drop this       
                                           message. (default: 3)                
--metadata-expiry-ms <Long: metadata     The period of time in milliseconds     
  expiration interval>                     after which we force a refresh of    
                                           metadata even if we haven't seen any 
                                           leadership changes. (default: 300000)
--old-producer                           Use the old producer implementation.   
--producer-property <producer_prop>      A mechanism to pass user-defined       
                                           properties in the form key=value to  
                                           the producer.                        
--producer.config <config file>          Producer config properties file. Note  
                                           that [producer-property] takes       
                                           precedence over this config.         
--property <prop>                        A mechanism to pass user-defined       
                                           properties in the form key=value to  
                                           the message reader. This allows      
                                           custom configuration for a user-     
                                           defined message reader.              
--queue-enqueuetimeout-ms <Integer:      Timeout for event enqueue (default:    
  queue enqueuetimeout ms>                 2147483647)                          
--queue-size <Integer: queue_size>       If set and the producer is running in  
                                           asynchronous mode, this gives the    
                                           maximum amount of  messages will     
                                           queue awaiting sufficient batch      
                                           size. (default: 10000)               
--request-required-acks <request         The required acks of the producer      
  required acks>                           requests (default: 1)                
--request-timeout-ms <Integer: request   The ack timeout of the producer        
  timeout ms>                              requests. Value must be non-negative 
                                           and non-zero (default: 1500)         
--retry-backoff-ms <Integer>             Before each retry, the producer        
                                           refreshes the metadata of relevant   
                                           topics. Since leader election takes  
                                           a bit of time, this property         
                                           specifies the amount of time that    
                                           the producer waits before refreshing 
                                           the metadata. (default: 100)         
--socket-buffer-size <Integer: size>     The size of the tcp RECV size.         
                                           (default: 102400)                    
--sync                                   If set message send requests to the    
                                           brokers are synchronously, one at a  
                                           time as they arrive.                 
--timeout <Integer: timeout_ms>          If set and the producer is running in  
                                           asynchronous mode, this gives the    
                                           maximum amount of time a message     
                                           will queue awaiting sufficient batch 
                                           size. The value is given in ms.      
                                           (default: 1000)                      
--topic <topic>                          REQUIRED: The topic id to produce      
                                           messages to.                         
--value-serializer <encoder_class>       The class name of the message encoder  
                                           implementation to use for            
                                           serializing values. (default: kafka. 
                                           serializer.DefaultEncoder)        
```


# TODO
- この辺をひとめぐり
  - https://kafka.apache.org/08/documentation.html
- kafka-console-producer.sh, kafka-topics.sh, kafka-console-consumer.shコマンドのオプションをざっと使ってみるといいかもしれない

# 参考URL
- kafka公式ドキュメント
  - http://kafka.apache.org/documentation.html
- kafka Release Note
  - https://kafka.apache.org/downloads
- http://www.w3ii.com/en-US/apache_kafka/apache_kafka_cluster_architecture.html


