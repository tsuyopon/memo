# 概要
dexはCoreOSにより作られたOpen SourceのIdentity Providerです。
OpenID Connectに対応しており、多くの3rd party製のコネクタにも対応しています。

# 詳細

### 起動プロセス
dex serveに与えるyamlにより起動プロセスを制御できる。
設定ファイルに明示的に記載しないとプロセスとして起動しない。
- dex (http, https)
  - Identity Providerメインエンドポイント提供
- grpc api
  - ClientID, Secret発行などのAPIをGRPCで提供する
- telemetry
  - /metrics
  - /healthz
  - /healthz/live
  - /healthz/ready

### dexとサンプルアプリケーションのビルド
基本的には以下の手順に準ずる。
- https://dexidp.io/docs/getting-started/

dexは以下でビルドする
```
$ git clone https://github.com/dexidp/dex.git
$ cd dex/
$ make build
```

実行はサンプルのyamlがあります。
```
$ ./bin/dex serve examples/config-dev.yaml
```

続いて、上記dexをIdPとして利用するサービスアプリケーションの実行は以下の通りです。
```
$ make examples
$ ./bin/example-app
```

ブラウザから http://localhost:5555/ にアクセスし、Loginを押下する。
Login With Emailから
- admin@example.com
- password
でログインすることでデフォルトで設定されたIDとパスワードで認可を行うことができます。


### 設定ファイル
設定できる値などは以下を参照にすること
- https://github.com/dexidp/dex/blob/v2.31.1/cmd/dex/config.go

### エンドポイント起点
エンドポイントの定義は以下
- https://github.com/dexidp/dex/blob/v2.31.1/server/server.go#L346-L389

# 参考資料
- レポジトリ 
  - https://github.com/dexidp/dex
- 公式ホームページ
  - https://dexidp.io/
- 公式ドキュメント
  - https://dexidp.io/docs/
