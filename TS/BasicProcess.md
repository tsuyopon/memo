# 概要
trafficserverのプロセス概要についての説明です

# 詳細

## trafficserverで稼働している主要３プロセスについて
- traffic_cop
  - プロセス監視
- traffic_server
  - キャッシュサービス・プロキシサービスなどの主要サービスの提供
- traffic_manager
  - サービスレベルの管理や監視を行う

traffic_managerとtraffic_serverが同一の共有メモリを参照している。

### traffic_managerプロセス動作概要
- traffic_serverプロセスの起動、停止、再起動を行う
- traffic_serverプロセスの監視
- Web管理コンソールGUI
- traffic_serverプロセスと連携して統計情報を表示する
- クラスタ管理
- 仮想IPフェイルオーバー
- プロキシ自動設定
- traffic_server再起動時のコネクションキュー

### traffic_copプロセス動作概要
traffic_serverプロセスとtraffic_managerプロセスに対してヘルスチェックを行う。syntheticへのリクエストを行う事によってheartbeatを確認する。
１分間に何度か実行して、応答がない場合にはtraffic_serverプロセスとtraffic_managerプロセスをrestartする。

# TODO
- もう少し精度を高める

# SeeAlso
- https://docs.trafficserver.apache.org/en/latest/admin-guide/introduction.en.html#traffic-server-processes
