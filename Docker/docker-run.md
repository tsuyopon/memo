# 概要
docker runコマンドについてまとめておきます。

docker runのオプションは以下の資料でも確認することができます。
- https://docs.docker.jp/engine/reference/run.html

# 詳細

### 主要オプション
docker runにはオプションが多いので主要オプションを覚えておきます。

```
-d: コンテナをdetachedモードでデーモンとして利用する。設計上、コンテナが実行するプロセスが終了したら、このモードで起動したコンテナも終了します。このモードではコンテナ停止時に自動的に削除できないので--rmオプションは同時に指定できません。

-it: インタラクティブなプロセスでは、コンテナのプロセスに対して tty を割り当てるためにiとtオプションを一緒に使います。 iは「Keep STDIN open even if not attached」、tは「Allocate a pseudo-tty」の意味があります。

-p: 外部ポートとコンテナ内部のポートを接続します。
    例えば「-p 8080:80」とするとローカルホストのport8080にアクセスすると、dockerコンテナの内部でport80で稼働しているアプリケーションに接続できるようになります。

-v: ボリューム(v)を指定する。一般的な指定は「-v ローカルマウント元:コンテナマウント先」となる。

-h: コンテナのホスト名

--name: 指定した名前をつけることができます。これを付与しないとdockerが勝手にnameをつけてくれます。docker ps -aなどのコマンドで確認することができます。
```

### ドキュメントからの引用
17.0.6ドキュメントからの引用
- https://docs.docker.jp/engine/reference/commandline/run.html

```
使い方: docker run [オプション] イメージ [コマンド] [引数...]

新しいコンテナを実行する命令

  -a, --attach=[]               STDIN、STDOUT、STDERR にアタッチする
  --add-host=[]                 ホストから IP アドレスのマッピングをカスタマイズして追加 (host:ip)
  --blkio-weight=0              ブロック IO ウエイト (相対ウエイト)
  --blkio-weight-device=[]      ブロック IO ウエイト (相対デバイス・ウエイト。書式： `デバイス名:ウエイト`)
  --cpu-shares=0                CPU 共有 (相対ウエイト)
  --cap-add=[]                  Linux ケーパビリティの追加
  --cap-drop=[]                 Linux ケーパビリティの削除
  --cgroup-parent=""            コンテナ用のオプション親 cgroup を指定
  --cidfile=""                  コンテナ ID をファイルに書き出し
  --cpu-percent=0               コンテナが実行可能な CPU 使用率のパーセントを制限。Windowsのみ
  --cpu-period=0                CPU CFS (Completely Fair Scheduler) ペイロードの制限
  --cpu-quota=0                 CPU CFS (Completely Fair Scheduler) クォータの制限
  --cpuset-cpus=""              実行を許可する CPU (0-3, 0,1)
  --cpuset-mems=""              実行を許可するメモリ必要量 (0-3, 0,1)
  -d, --detach                  コンテナをバックグラウンドで実行し、コンテナ ID を表示
  --detach-keys                 コンテナのデタッチに使うエスケープ・キー・シーケンスを設定
  --device=[]                   ホスト・デバイスをコンテナに追加
  --device-read-bps=[]          デバイスからの読み込みレート (バイト/秒) を制限 (例: --device-read-bps=/dev/sda:1mb)
  --device-read-iops=[]         デバイスからの読み込みレート (IO/秒) を制限 (例: --device-read-iops=/dev/sda:1000)
  --device-write-bps=[]         デバイスへの書き込みレート (バイト/秒) を制限  (例: --device-write-bps=/dev/sda:1mb)
  --device-write-iops=[]        デバイスへの書き込みレート (IO/秒) を制限 (例: --device-write-bps=/dev/sda:1000)
  --disable-content-trust=true  イメージの認証をスキップ
  --dns=[]                      カスタム DNS サーバの指定
  --dns-opt=[]                  カスタム DNS オプションの指定
  --dns-search=[]               カスタム DNS 検索ドメインの指定
  -e, --env=[]                  環境変数を指定
  --entrypoint=""               イメージのデフォルト ENTRYPOINT を上書き
  --env-file=[]                 ファイルから環境変数を読み込み
  --expose=[]                   ポートまたはポート範囲を露出
  --group-add=[]                参加するグループを追加
  -h, --hostname=""             コンテナのホスト名
  --help                        使い方の表示
  -i, --interactive             コンテナの STDIN にアタッチ
  --ip=""                       コンテナの IPv4 アドレス (例: 172.30.100.104)
  --ip6=""                      コンテナの IPv6 アドレス (例: 2001:db8::33)
  --ipc=""                      使用する IPC 名前空間
  --isolation=""                コンテナの分離（独立）技術
  --kernel-memory=""            Kernel メモリ上限
  -l, --label=[]                コンテナにメタデータを指定 (例: --label=com.example.key=value)
  --label-file=[]               行ごとにラベルを記述したファイルを読み込み
  --link=[]                     他のコンテナへのリンクを追加
  --link-local-ip=[]            コンテナとリンクするローカルの IPv4/IPv6 アドレス (例: 169.254.0.77, fe80::77)
  --log-driver=""               コンテナ用のログ記録ドライバを追加
  --log-opt=[]                  ログドライバのオプションを指定
  -m, --memory=""               メモリ上限
  --mac-address=""              コンテナの MAC アドレス (例： 92:d0:c6:0a:29:33)
  --io-maxbandwidth=""          システム・デバイスの IO 帯域に対する上限を指定（Windowsのみ）。
                                書式は `<数値><単位>`。単位はオプションで `b` (バイト/秒)、
                                `k` (キロバイト/秒)、 `m` (メガバイト/秒)、 `g` (ギガバイト/秒)。
                                単位を指定しなければ、システムはバイト/秒とみなす。
                                --io-maxbandwidth と --io-maxiops は相互排他オプション
  --io-maxiops=0                システム・ドライブの最大 IO/秒に対する上限を指定 *Windowsのみ)
                                --io-maxbandwidth と --io-maxiops は相互排他オプション
  --memory-reservation=""       メモリのソフト上限
  --memory-swap=""              整数値の指定はメモリにスワップ値を追加。-1は無制限スワップを有効化
  --memory-swappiness=""        コンテナ用メモリのスワップ程度を調整。整数値の 0 から 100 で指定
  --name=""                     コンテナに名前を割り当て
  --net="bridge"   : コンテナをネットワークに接続
                                'bridge': docker ブリッジ上でコンテナ用に新しいネットワーク・スタックを作成
                                'none': コンテナにネットワーク機能を付けない
                                'container:<name|id>': 他のコンテナ用ネットワーク・スタックを再利用
                                'host': コンテナ内でホスト側ネットワーク・スタックを使用
                                'NETWORK': 「docker network create」コマンドでユーザ作成したネットワークを使用
  --net-alias=[]                コンテナにネットワーク内部用のエイリアスを追加
  --oom-kill-disable            コンテナの OOM Killer を無効化するかどうか指定
  --oom-score-adj=0             コンテナに対してホスト側の OOM 優先度を設定 ( -1000 ～ 1000 を指定)
  -P, --publish-all             全ての露出ポートをランダムならポートに公開
  -p, --publish=[]              コンテナのポートをホスト側に公開
  --pid=""                      使用する PID 名前空間
  --pids-limit=-1                コンテナの pids 制限を調整 (kernel 4.3 以上は -1 で無制限に設定)
  --privileged                  このコンテナに対して拡張権限を与える
  --read-only                   コンテナのルート・ファイルシステムを読み込み専用としてマウント
  --restart="no"                再起動ポリシー (no, on-failure[:max-retry], always, unless-stopped)
  --rm                          コンテナ終了時、自動的に削除
  --runtime=""                  コンテナで使うランタイム名を指定
  --shm-size=[]                 `/dev/shm` のサイズ。書式は `<数値><単位>`. `数値` は必ず `0` より大きい。単位はオプションで `b` (bytes)、 `k` (kilobytes)、 `m` (megabytes)、 `g` (gigabytes) を指定可能。単位を指定しなければ、システムは bytes を使う。数値を指定しなければ、システムは `64m` を使う
  --security-opt=[]             セキュリティ・オプション
  --sig-proxy=true              受信したシグナルをプロセスにプロキシ
  --stop-signal="SIGTERM"       コンテナの停止シグナル
  --storage-opt=[]              コンテナごとにストレージ・ドライバのオプションを指定
  --sysctl[=*[]*]]              実行時に名前空間カーネル・パラメータを調整
  -t, --tty                     疑似ターミナル (pseudo-TTY) を割り当て
  -u, --user=""                 ユーザ名または UID
  --userns=""                   コンテナのユーザ名前空間
                                'host': Docker ホストで使うユーザ名前空間
                                '': Docker デーモンのユーザ名前空間を指定するには `--userns-remap` オプションを使う
  --ulimit=[]                   Ulimit オプション
  --uts=""                      使用する UTS 名前空間
  -v, --volume=[ホスト側ソース:]コンテナ側送信先[:<オプション>]
                                ボリュームを拘束マウント。カンマ区切りで指定
                                `オプション` は [rw|ro], [z|Z], [[r]shared|[r]slave|[r]private], [nocopy]
                                'ホスト側ソース' は絶対パスまたは名前の値
  --volume-driver=""            コンテナのボリューム・ドライバ
  --volumes-from=[]             指定したコンテナからボリュームをマウント
  -w, --workdir=""              コンテナ内の作業用ディレクトリを指定
```

### コンテナを停止させずにコンテナから抜けたい場合
重要なので覚えておくとよい。
```
Ctrl+P, Ctrl+Q
```

### 80ポートでデーモンとして起動し、親からは8081として接続できるようにする
以下の例では
```
$ docker run -d -p 8081:80 --name {コンテナ名} nginx
```

終わったら後片付けをしておきましょう。以下の例ではwebserverというコンテナ名にしています。
```
$ docker container stop webserver
$ docker container rm webserver
```

### dockerを起動する
次のようにしてdockerを起動します。オプションは省略できるものもあります。
- hオプションは名前を付与します。以下では適当に「spam」という名称を付与します。指定しないとdockerが適当に決定します。
- iオプションはそのdocker内でシェルを続行したい場合に付与します。
- tにはイメージを指定します。「docer images」などで指定した「<REPOSITORY>:<IMAGE ID>」を指定します。
- dオプション(daemon)をつけなければ、フォアグランドの実行となる。コンテナを抜けるとコンテナは停止する。
```
$ sudo docker run -h spam -i -t ubuntu:b44ce450cb60 /bin/bash 
```

起動時に環境変数を指定するeオプションもある。実行時の初期ディレクトリを変更するにはwオプションがある。詳しくは以下を参照のこと
- https://qiita.com/shimo_yama/items/d0c42394689132fcb4b6

### dockerをコンテナバックグラウンドで起動する
dオプションによってバックグラウンドで起動させることができます。
```
$ docker run -i -t -d ubuntu /bin/bash
```

### ホスト名を指定する
hostnameを指定することで自動的にコンテナ名を作成することを防ぐことができます。
このとき指定した名前は「docker ps」で確認することができます。
```
$ docker run --hostname kaeru -i -t ubuntu /bin/bash
```

### dockerの停止後に破棄する
rmオプションを付与するとコンテナ停止後にコンテナが破棄されます。
```
$ docker run --rm -t -i tsuyopon/hello /bin/bash
```

### 起動時に環境変数を与える
eオプションを引き渡すことで外部から環境変数を指定することができます。
複数の-eオプションを引き渡すことも可能です。
```
$ docker run -p 8080:80 -e HOGE_ENV=10485760  ubuntu

// 複数引き渡す場合
$ docker run -p 8080:80 -e HOGE_ENV=10485760 FUGA_ENV=1024  ubuntu
```

なお、--env-fileオプションを使うことでファイルから環境変数を渡すことができる。

### ボリュームを指定する
vオプションで指定することができます。
以下の例ではカレントディレクトリのmydirを/mydirとして参照できるようになります。
```
$ docker run -d -p 8080:8080 -v `pwd`/mydir:/mydir ubuntu
```
