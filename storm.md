# 概要
Apache Stormに関する概要について
- 分散リアルタイム処理のOSSです。
- Hadoopがバッチプロセスとして実行していますが、Stormはリアルタイムプロセスとして実行しています。
- 利用用途としては、
  - リアルタイム分析
  - オンライン機械学習
  - 継続的な計算処理
  - 分散PRC
- スケーラブル、フォールトトレラント、データ保証、No SPOF
- データ入力
  - MQからデータを取り込むのが定番
  - スケールアウト可能な製品が望ましい(kestrel, kafka, RabbitMQ)
- データ出力
  - ストリームとして下流に流す。KVSやRDBMSなど

### 用語
- Topology
  - stormによるストリームを定義するものであり、SpoutとBoltの組み合わせを表します。
  - ユーザーはSpoutとBoltを実装する必要があります。
- Spout
  - 無限ループで呼ばれ続ける。Tupleを流す
- Bolt
  - Tupleを受け取ったらexecuteを呼び出す
- Tuple
  - タプルと呼ばれるデータ構造で扱う

# Tutorialメモ
- hadoopだとMapReduce jobs, Stormだとtopologiesを稼働させるが、違いはhadoopは終了するが、stormは終了しない
- stormにはmasterノードとworkerノードの２つが存在する
  - masterはhadoopeのJobTrackerに似たNimbusを稼働させる。Nimbusはクラスタにコードを分配する責任を持ち、タスクを割り当て、失敗を監視する
  - どちらのworkerもSupervisorというデーモンを起動する

# 参考URL
- 公式ドキュメント
  - http://storm.apache.org/index.html
- tutorial
  - http://storm.apache.org/releases/current/Tutorial.html
- slide share
  - https://www.slideshare.net/hadoopxnttdata/storm-19536843

