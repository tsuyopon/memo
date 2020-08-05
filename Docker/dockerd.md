# 概要
dockerデーモンについて

# 詳細

### デーモン起動関連オプション
```
-D, --debug=false: デバッグモードにする
-H, --host=[]: デーモンモードでソケットをバインドする先。&br; tcp://host:port, unix:///path/to/socket, fd://* , fd://socketfd を必要な回数繰り返して指定する。デフォルトは（もしあれば）DOCKER_HOST 環境変数の内容に従う。
-G, --group="docker": デーモンモードで起動された時に -H 指定のUNIXソケットを割り当てるグループ。グループを設定しない場合は ''（空文字列）を指定する。
--api-enable-cors=false: リモート APIで CORS ヘッダーを有効にする
-b, --bridge="": コンテナを既存のブリッジに接続する。コンテナのネットワークを無効にする場合は 'none' を指定する。
-bip="": この CIDR 表現のアドレスをネットワーク・ブリッジのIPとして指定する。-b との互換性はありません。
-d, --daemon=false: デーモンモードを有効にする
--dns=[]: docker にこれらの DNS サーバ指定を強制する。
--dns-search=[]: docker にこれらの DNS 検索ドメイン指定を強制する。
--enable-selinux=false: 実行するコンテナで sulinux を有効にする。
-g, --graph="/var/lib/docker": docker ランタイムの root パスを指定する
--icc=true: コンテナ間の相互通信を有効にする
--ip="0.0.0.0": コンテナのポートにバインドする際のデフォルトの IP アドレス
--ip-forward=true: net.ipv4.ip_forward（IP転送）を有効にする
--iptables=true: docker における追加の iptables ルールを有効にする
-p, --pidfile="/var/run/docker.pid": デーモンが使用する PID ファイルのパス
-r, --restart=true: 直前に動いていたコンテナを再起動する
-s, --storage-driver="": docker ランタイムに特定のストレージドライバの利用を強制する
-e, --exec-driver="native": docker ランタイムに特定の exec ドライバの利用を強制する
-v, --version=false: バージョン情報を表示して終了する
--tls=false: TLS を使う。tls-verify フラグにより暗黙に指定される。
--tlscacert="~/.docker/ca.pem": ここで指定された CA によって署名された証明書を提供するリモート環境のみを信頼する
--tlscert="~/.docker/cert.pem": TLS 証明書ファイルへのパス
--tlskey="~/.docker/key.pem": TLS キーファイルへのパス
--tlsverify=false: TLS を使用してリモート環境を検証する（デーモン：クライアントを検証、クライアント：デーモンを検証）
--mtu=0: コンテナのネットワーク MTU を指定する。値を指定しない場合、デフォルトルートがあればその MTU、なければ 1500 を使う。
```

- 参考: https://gist.github.com/hotta/69b476ae6662c5ff67f0/#events
