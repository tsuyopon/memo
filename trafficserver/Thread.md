# 概要
各種スレッドについて

# 詳細

### 動的解析したときのスレッド
動的に調査した際に次のようにスレッドが利用されていた。これは設定値などによってスレッドの種類やその数の変更があると思われる。
- LOG_PREPROCが1つ
- LOG_FLUSHが1つ
- ET_AIOが8つ
- ACCEPT(0:8080)が2つ
- ACCEPT(0:8084)が1つ
- traffic_serverが1つ
- ET_TASKが2つ
- ET_NETが１つ
- TS_MAINが1つ

### 主要スレッドについて
mainの中でほとんどのスレッドが呼び出されることを確認できた。
```
main
    eventProcessor.start
    remapProcessor.start
    netProcessor.start
    dnsProcessor.start
    hostDBProcessor.start
    sslNetProcessor.start
    cacheProcessor.start
    udpNet.start
    transformProcessor.start
    (start_HttpProxyServer)
    tasksProcessor.start
```

上記のスレッド処理についてまとめると以下の通り(詳細についてはOVERVIEW_THREAD_ET_XXX.mdを参照のこと)
- main (TS_MAIN)
  - メインスレッドの処理。ClusterProcessor以外の基盤となるスレッドはここから呼び出される(ここで生成されるスレッドから別のスレッドを生成することもあるがそこは>割愛) 
- EventProcessor (ET_NET)
  - イベント処理を検出し続ける
- RemapProcessor (ET_REMAP)
  - HttpSM::set_next_state()の中でHttpTransact::SM_ACTION_REMAP_REQUESTの場合にのみschedule_immとして呼び出される
- UnixNetProcessor
  - net関連処理で呼ばれる
  - UnixNet.cc, UnixNetPages.cc, InkAPI.cc, Transform.cc, ClusterHandlerBase.cc, CongestionDB.cc, Http2ConnectionState.ccのnet処理に関連する部分などで使われていると思われる。
- DnsProcessor (ET_DNS)
- HostDBProcessor
  - スレッドは作らずに、ET_DNSを利用する。1秒ごとにHostDBContinuation::backgroundEventを実行して前回実行後から特定の時間が経過していたら処理する。
- SslNetProcessor
- CacheProcessor
- UdpNet
- TransformProcessor
  - (参考) https://github.com/apache/trafficserver/blob/7.0.x/proxy/Transform.cc#L23-L58
- TasksProcessor (ET_TASK)
  - DiagsLogContinuation, MemoryLimit, Prefetch, HostDB, CachePageなど様々な箇所で呼びされているようだ

# SeeAlso
スレッドに関する説明は以下のドキュメントが詳しい
- https://docs.trafficserver.apache.org/en/latest/developer-guide/threads-and-events.en.html
