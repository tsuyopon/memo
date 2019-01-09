# docker-machineとは何か?
手元のMACでdocker-machineというコマンドが存在してるのだが、dockerコマンドとは何が違うんだろうか?

もともとDocker Engineは64bit上のLinuxでしか動作しない。つまり、MacやWindowsはDocker Engineでは動かすことができないです。  
MacやWindowsでは、VirtualBoxなどの仮想マシン上でDockerデーモンがインストールされたLinux環境を構築する必要があります。これをやってくれる仕組みがDocker Machineです。

これによって、Mac OSの仮想マシン上でLinuxが起動され、その中でdockerコンテナを動かすためのdockerデーモンが起動され、dockerを動かすことができるという仕組みになっています。
概念図などは以下の資料を参考にすると良いでしょう。
- https://knowledge.sakura.ad.jp/3990/

今回、手元で確認したVirtualBoxのバージョンは「5.1.30 r118389 (Qt5.6.3)」です。

# 詳細
## セットアップ (Docker Machineを使ってDockerコンテナを利用するための環境構築)

以下の資料を参考にして
- http://docs.docker.jp/machine/get-started.html

以下のコマンドでは、Docker デーモンをインストールする軽量 Linux ディストリビューション（ boot2docker ）をダウンロードし、Docker を動かすための VirtualBox 仮想マシンを作成・起動します。  
defaultの部分は適宜、個人の環境に合わせて変更できます。
```
$ docker-machine create --driver virtualbox default
Running pre-create checks...
(default) Unable to get the local Boot2Docker ISO version:  Did not find prefix "-v" in version string
(default) Default Boot2Docker ISO is out-of-date, downloading the latest release...
(default) Latest release for github.com/boot2docker/boot2docker is v18.09.0
(default) Downloading /Users/tsuyoshi/.docker/machine/cache/boot2docker.iso from https://github.com/boot2docker/boot2docker/releases/download/v18.09.0/boot2docker.iso...
(default) 0%....10%....20%....30%....40%....50%....60%....70%....80%....90%....100%
Error with pre-create check: "VirtualBox is configured with multiple host-only adapters with the same IP \"192.168.99.1\". Please remove one."
tsuyoshi:gomi tsuyoshi$ docker-machine create --driver virtualbox default
Running pre-create checks...
(default) Unable to get the local Boot2Docker ISO version:  Did not find prefix "-v" in version string
(default) Default Boot2Docker ISO is out-of-date, downloading the latest release...
(default) Latest release for github.com/boot2docker/boot2docker is v18.09.0
(default) Downloading /Users/tsuyoshi/.docker/machine/cache/boot2docker.iso from https://github.com/boot2docker/boot2docker/releases/download/v18.09.0/boot2docker.iso...
(default) 0%....10%....20%....30%....40%....50%....60%....70%....80%....90%....100%
Creating machine...
(default) Unable to get the local Boot2Docker ISO version:  Did not find prefix "-v" in version string
(default) Default Boot2Docker ISO is out-of-date, downloading the latest release...
(default) Latest release for github.com/boot2docker/boot2docker is v18.09.0
(default) Downloading /Users/tsuyoshi/.docker/machine/cache/boot2docker.iso from https://github.com/boot2docker/boot2docker/releases/download/v18.09.0/boot2docker.iso...
(default) 0%....10%....20%....30%....40%....50%....60%....70%....80%....90%....100%
(default) Copying /Users/tsuyoshi/.docker/machine/cache/boot2docker.iso to /Users/tsuyoshi/.docker/machine/machines/default/boot2docker.iso...
(default) Creating VirtualBox VM...
(default) Creating SSH key...
(default) Starting the VM...
(default) Check network to re-create if needed...
(default) Waiting for an IP...
Waiting for machine to be running, this may take a few minutes...
Detecting operating system of created instance...
Waiting for SSH to be available...
Detecting the provisioner...
Provisioning with boot2docker...
Copying certs to the local machine directory...
Copying certs to the remote machine...
Setting Docker configuration on the remote daemon...
Checking connection to Docker...
Docker is up and running!
To see how to connect your Docker Client to the Docker Engine running on this virtual machine, run: docker-machine env default
```

確認してみるとRunningとなりました。
```
$ docker-machine ls
NAME      ACTIVE   DRIVER       STATE     URL                         SWARM   DOCKER     ERRORS
default   *        virtualbox   Running   tcp://192.168.99.100:2376           v18.09.0   
```

新しく作成したtest1マシンを操作するには、「docker-machine env」を実行します。
```
$ docker-machine env default
export DOCKER_TLS_VERIFY="1"
export DOCKER_HOST="tcp://192.168.99.100:2376"
export DOCKER_CERT_PATH="/Users/tsuyoshi/.docker/machine/machines/default"
export DOCKER_MACHINE_NAME="default"
# Run this command to configure your shell: 
# eval $(docker-machine env default)
```

上記で出力された環境変数が設定されていることが確認できます。これでdockerが使えます。
```
$ env | grep -i docker
DOCKER_HOST=tcp://192.168.99.100:2376
DOCKER_MACHINE_NAME=test1
DOCKER_TLS_VERIFY=1
DOCKER_CERT_PATH=/Users/tsuyoshi/.docker/machine/machines/test1
```


起動時に上記環境変数を有効にしたければ、.bashrcなどに以下を入れておくと良いです。
```
eval $(docker-machine env default)
```

dockerコマンドが使えるようになっているはずなので
```
$ docker version
Client:
 Version:      1.11.0
 API version:  1.23
 Go version:   go1.5.4
 Git commit:   4dc5990
 Built:        Wed Apr 13 18:13:28 2016
 OS/Arch:      darwin/amd64

Server:
 Version:      18.09.0
 API version:  1.39
 Go version:   go1.10.4
 Git commit:   4d60db4
 Built:        Wed Nov  7 00:52:55 2018
 OS/Arch:      linux/amd64
```

単純なbusyboxを使ってみます。
```
$ docker run busybox echo hello world
Unable to find image 'busybox:latest' locally
latest: Pulling from library/busybox

57c14dd66db0: Pull complete 
Digest: sha256:7964ad52e396a6e045c39b5a44438424ac52e12e4d5a25d94895f2058cb863a0
Status: Downloaded newer image for busybox:latest
hello world
```

イメージとしても取得できています。
```
$ docker images
REPOSITORY          TAG                 IMAGE ID            CREATED             SIZE
busybox             latest              3a093384ac30        8 days ago          1.199 MB
busybox             <none>              3a093384ac30        8 days ago          1.199 MB
```

## 各種コマンド
以下ではマシンを指定する際には「default」を引数と指定していますので、適宜読み替えてください。

### 使用可能なマシンを確認する
以下ではdefaultしか存在していません。
```
$ docker-machine ls
NAME      ACTIVE   DRIVER       STATE     URL                         SWARM   DOCKER     ERRORS
default   *        virtualbox   Running   tcp://192.168.99.100:2376           v18.09.0   
```

### docker-machineを作成する
```
$ docker-machine create --driver virtualbox default
```

上記は本当に単純な例です。例えば、次のようなコマンドでcreateオプション指定時にどのようなオプションが指定できるかわかります(ドライバごとにことなるので注意)
```
// サンプル
$ docker-machine create -d virtualbox
$ docker-machine create -d amazonec2
```

driverなどについては以下のページを参照すること
- https://docs.docker.com/machine/#openstack
- https://qiita.com/zembutsu/items/9d189da5d2c7708717a3



### 不要になったdocker-machineを削除する
以下ではdefaultという名前のdocker-machineを削除している例です。
```
$ docker-machine rm default
machine does not exist, assuming it has been removed already
Successfully removed dev
```

rmを行ったあとに、再度createしようとすると自分は次のエラーにひっかかりました。
- 「VirtualBox is configured with multiple host-only adapters with the same IP」
  - https://qiita.com/niiyz/items/70580164551c710a75d3

### 起動・停止・再起動・強制終了


- 起動
  - startをしたあとはメッセージに出力されているように「docker-machine env」コマンドの再実行が必要です。
```
$ docker-machine start default
Starting "default"...
(default) Check network to re-create if needed...
(default) Waiting for an IP...
Machine "default" was started.
Waiting for SSH to be available...
Detecting the provisioner...
Started machines may have new IP addresses. You may need to re-run the `docker-machine env` command.
$ docker-machine ls
NAME      ACTIVE   DRIVER       STATE     URL                         SWARM   DOCKER     ERRORS
default   *        virtualbox   Running   tcp://192.168.99.100:2376           v18.09.0  
```
- 停止
```
$ docker-machine stop default
Stopping "default"...
Machine "default" was stopped.
$ docker-machine ls
NAME      ACTIVE   DRIVER       STATE     URL   SWARM   DOCKER    ERRORS
default   -        virtualbox   Stopped                 Unknown 
```
- 再起動
```
$ docker-machine restart default
Restarting "default"...
(default) Check network to re-create if needed...
(default) Waiting for an IP...
Waiting for SSH to be available...
Detecting the provisioner...
Restarted machines may have new IP addresses. You may need to re-run the `docker-machine env` command.
$ docker-machine ls
NAME      ACTIVE   DRIVER       STATE     URL                         SWARM   DOCKER     ERRORS
default   *        virtualbox   Running   tcp://192.168.99.100:2376           v18.09.0   
```
- 強制終了
```
$  docker-machine kill default
Killing "default"...
Machine "default" was killed.
$ docker-machine ls
NAME      ACTIVE   DRIVER       STATE     URL   SWARM   DOCKER    ERRORS
default   -        virtualbox   Stopped                 Unknown  
```

### 起動状態を確認する
```
$ docker-machine status default
Running
```

### 起動設定を確認する
```
$ docker-machine config default
--tlsverify
--tlscacert="/Users/tsuyoshi/.docker/machine/certs/ca.pem"
--tlscert="/Users/tsuyoshi/.docker/machine/certs/cert.pem"
--tlskey="/Users/tsuyoshi/.docker/machine/certs/key.pem"
-H=tcp://192.168.99.100:2376
```

### 作成したDockerマシンにSSHする

以下はdefaultのマシンに対して/proc/versionを確認するだけのsshコマンドを発行しています。
```
$ docker-machine ssh default cat /proc/version
Linux version 4.14.79-boot2docker (root@5ce219ef6d66) (gcc version 6.3.0 20170516 (Debian 6.3.0-18+deb9u1)) #1 SMP Thu Nov 8 01:56:42 UTC 2018
```

ログインする場合は次のようなコマンドで入れます。
```
$ docker-machine ssh default
```

### SCPする

ローカル・ホストからマシーン上へ、マシーンからマシーンへ、あるいはマシーンからローカルホストへのファイルのコピーに scp を使います。  
引数での記法は マシン名:/ファイル/への/パス 形式で、ホストマシン上の場合はホスト名を指定せず、パスだけ記述します。
```
$ docker-machine scp default:/home/docker/foo.txt .
```
デフォルトでは再帰的(-r)にコピーされるようです。

### activeなdocker-machineを切り替える
たとえば、testという別のdocker-machineに切り替えたい場合には次のようにします。
```
$ docker-machine active test
```

### docker-machineの詳細な情報を表示する。
```
$ docker-machine inspect default
{
    "ConfigVersion": 3,
    "Driver": {
        "IPAddress": "192.168.99.100",
        "MachineName": "default",
        "SSHUser": "docker",
        "SSHPort": 53770,
        "SSHKeyPath": "/Users/tsuyoshi/.docker/machine/machines/default/id_rsa",
        "StorePath": "/Users/tsuyoshi/.docker/machine",
        "SwarmMaster": false,
        "SwarmHost": "tcp://0.0.0.0:3376",
        "SwarmDiscovery": "",
        "VBoxManager": {},
        "HostInterfaces": {},
        "CPU": 1,
        "Memory": 1024,
        "DiskSize": 20000,
        "NatNicType": "82540EM",
        "Boot2DockerURL": "",
        "Boot2DockerImportVM": "",
        "HostDNSResolver": false,
        "HostOnlyCIDR": "192.168.99.1/24",
        "HostOnlyNicType": "82540EM",
        "HostOnlyPromiscMode": "deny",
        "NoShare": false,
        "DNSProxy": true,
        "NoVTXCheck": false
    },
    "DriverName": "virtualbox",
    "HostOptions": {
        "Driver": "",
        "Memory": 0,
        "Disk": 0,
        "EngineOptions": {
            "ArbitraryFlags": [],
            "Dns": null,
            "GraphDir": "",
            "Env": [],
            "Ipv6": false,
            "InsecureRegistry": [],
            "Labels": [],
            "LogLevel": "",
            "StorageDriver": "",
            "SelinuxEnabled": false,
            "TlsVerify": true,
            "RegistryMirror": [],
            "InstallURL": "https://get.docker.com"
        },
        "SwarmOptions": {
            "IsSwarm": false,
            "Address": "",
            "Discovery": "",
            "Master": false,
            "Host": "tcp://0.0.0.0:3376",
            "Image": "swarm:latest",
            "Strategy": "spread",
            "Heartbeat": 0,
            "Overcommit": 0,
            "ArbitraryFlags": [],
            "Env": null,
            "IsExperimental": false
        },
        "AuthOptions": {
            "CertDir": "/Users/tsuyoshi/.docker/machine/certs",
            "CaCertPath": "/Users/tsuyoshi/.docker/machine/certs/ca.pem",
            "CaPrivateKeyPath": "/Users/tsuyoshi/.docker/machine/certs/ca-key.pem",
            "CaCertRemotePath": "",
            "ServerCertPath": "/Users/tsuyoshi/.docker/machine/machines/default/server.pem",
            "ServerKeyPath": "/Users/tsuyoshi/.docker/machine/machines/default/server-key.pem",
            "ClientKeyPath": "/Users/tsuyoshi/.docker/machine/certs/key.pem",
            "ServerCertRemotePath": "",
            "ServerKeyRemotePath": "",
            "ClientCertPath": "/Users/tsuyoshi/.docker/machine/certs/cert.pem",
            "ServerCertSANs": [],
            "StorePath": "/Users/tsuyoshi/.docker/machine/machines/default"
        }
    },
    "Name": "default"
}
```

### docker-machineへの接続先を確認する
```
$ docker-machine url
tcp://192.168.99.100:2376
```

### TLS証明書を再生成
```
$ docker-machine regenerate-certs default
Regenerate TLS machine certs?  Warning: this is irreversible. (y/n): y
Regenerating TLS certificates
```

### Dockerの最新バージョンにマシンをアップグレードする
```
$ docker-machine upgrade default
Waiting for SSH to be available...
Detecting the provisioner...
Upgrading docker...
Stopping machine to do the upgrade...
Upgrading machine "default"...
Unable to get the local Boot2Docker ISO version:  Did not find prefix "-v" in version string
Default Boot2Docker ISO is out-of-date, downloading the latest release...
Latest release for github.com/boot2docker/boot2docker is v18.09.0
Downloading /Users/tsuyoshi/.docker/machine/cache/boot2docker.iso from https://github.com/boot2docker/boot2docker/releases/download/v18.09.0/boot2docker.iso...
0%....10%....20%....30%....40%....50%....60%....70%....80%....90%....100%
Copying /Users/tsuyoshi/.docker/machine/cache/boot2docker.iso to /Users/tsuyoshi/.docker/machine/machines/default/boot2docker.iso...
Starting machine back up...
(default) Check network to re-create if needed...
(default) Waiting for an IP...
Restarting docker...
```

### docker-machineのバージョンを表示する
```
$ docker-machine version
docker-machine version 0.7.0, build a650a40
```

### provisionで初期化する??? (TODO: よくわからん)
```
$ docker-machine provision default
Waiting for SSH to be available...
Detecting the provisioner...
Copying certs to the local machine directory...
Copying certs to the remote machine...
Setting Docker configuration on the remote daemon...
```

- 公式ドキュメントにprovision実行時の処理が記載されている
  - https://docs.docker.com/machine/reference/provision/

### ヘルプを表示する
```
$ docker-machine -h
Usage: docker-machine [OPTIONS] COMMAND [arg...]

Create and manage machines running Docker.

Version: 0.7.0, build a650a40

Author:
  Docker Machine Contributors - <https://github.com/docker/machine>

Options:
  --debug, -D						Enable debug mode
  -s, --storage-path "/Users/tsuyoshi/.docker/machine"	Configures storage path [$MACHINE_STORAGE_PATH]
  --tls-ca-cert 					CA to verify remotes against [$MACHINE_TLS_CA_CERT]
  --tls-ca-key 						Private key to generate certificates [$MACHINE_TLS_CA_KEY]
  --tls-client-cert 					Client cert to use for TLS [$MACHINE_TLS_CLIENT_CERT]
  --tls-client-key 					Private key used in client TLS auth [$MACHINE_TLS_CLIENT_KEY]
  --github-api-token 					Token to use for requests to the Github API [$MACHINE_GITHUB_API_TOKEN]
  --native-ssh						Use the native (Go-based) SSH implementation. [$MACHINE_NATIVE_SSH]
  --bugsnag-api-token 					BugSnag API token for crash reporting [$MACHINE_BUGSNAG_API_TOKEN]
  --help, -h						show help
  --version, -v						print the version
  
Commands:
  active		Print which machine is active
  config		Print the connection config for machine
  create		Create a machine
  env			Display the commands to set up the environment for the Docker client
  inspect		Inspect information about a machine
  ip			Get the IP address of a machine
  kill			Kill a machine
  ls			List machines
  provision		Re-provision existing machines
  regenerate-certs	Regenerate TLS Certificates for a machine
  restart		Restart a machine
  rm			Remove a machine
  ssh			Log into or run a command on a machine with SSH.
  scp			Copy files between machines
  start			Start a machine
  status		Get the status of a machine
  stop			Stop a machine
  upgrade		Upgrade a machine to the latest version of Docker
  url			Get the URL of a machine
  version		Show the Docker Machine version or a machine docker version
  help			Shows a list of commands or help for one command
  
Run 'docker-machine COMMAND --help' for more information on a command.
```
provision, 


# 参考URL
- docker公式資料(Docker Machine)
  - https://docs.docker.com/machine/
- docker.jp 公式資料
  - http://docs.docker.jp/machine/index.html
- docker/machine github
  - https://github.com/docker/machine
- Docker Machine をローカル VM で始めるには
  - 環境構築はこれを参考にしました。
  - http://docs.docker.jp/machine/get-started.html
- qiita: docker-machineコマンド
  - docker-machine関連のコマンドが一通りまとまっています。
  - https://qiita.com/maemori/items/e7318b088b9e4bf22310

