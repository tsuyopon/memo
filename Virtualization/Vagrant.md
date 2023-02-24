# 概要
vagrantは仮想環境上に仮想マシンを作るツールです。

VirtualBoxを操作するためのフロントエンドツールとして使われたりします。 chefで使われるtest-kitchenでもデフォルトで利用されるようになっています。
このツールを使うとVagrantfileというファイルを用意するだけで、コマンド一発で仮想OS環境が作成できるようになります。

# 詳細

### インストール
手元のMacOS(12.6)からの場合下記でインストール可能です。
```
$ brew install --cask virtualbox vagrant
```

### バージョン
下記でインストールされているバージョンと利用可能な最新バージョンを共に情報として出力します。
```
$ vagrant version
Installed Version: 2.3.4
Latest Version: 2.3.4
 
You're running an up-to-date version of Vagrant!
```

### vagrantを使ってみる

利用可能なOSを表示します。
```
$ vagrant box list
bento/centos-7     (virtualbox, 202008.16.0)
bento/ubuntu-18.04 (virtualbox, 202008.16.0)
```

上記のリストから指定してVagrantfileを生成します。
```
$ vagrant init --minimal bento/centos-7
A `Vagrantfile` has been placed in this directory. You are now
ready to `vagrant up` your first virtual environment! Please read
the comments in the Vagrantfile as well as documentation on
`vagrantup.com` for more information on using Vagrant.
```

Vagrantfileが生成されたことを確認します。
```
$ ls Vagrantfile 
Vagrantfile
```

中をのぞいてみます。たった３行のファイルです。必要に応じてこのファイルをカスタマイズしますが、今回はとりあえず使ってみるのでこのまま進めます。
```
$ cat Vagrantfile 
Vagrant.configure("2") do |config|
  config.vm.box = "bento/centos-7"
end
```

では、インスタンスを起動してみます。
```
$ vagrant up
Bringing machine 'default' up with 'virtualbox' provider...
==> default: Importing base box 'bento/centos-7'...
==> default: Matching MAC address for NAT networking...
==> default: Checking if box 'bento/centos-7' version '202008.16.0' is up to date...
==> default: Setting the name of the VM: vagrant_default_1598115897613_40821
==> default: Fixed port collision for 22 => 2222. Now on port 2200.
==> default: Clearing any previously set network interfaces...
==> default: Preparing network interfaces based on configuration...
    default: Adapter 1: nat
==> default: Forwarding ports...
    default: 22 (guest) => 2200 (host) (adapter 1)
==> default: Booting VM...
==> default: Waiting for machine to boot. This may take a few minutes...
    default: SSH address: 127.0.0.1:2200
    default: SSH username: vagrant
    default: SSH auth method: private key
    default: Warning: Connection reset. Retrying...
    default: 
    default: Vagrant insecure key detected. Vagrant will automatically replace
    default: this with a newly generated keypair for better security.
    default: 
    default: Inserting generated public key within guest...
    default: Removing insecure key from the guest if it's present...
    default: Key inserted! Disconnecting and reconnecting using new SSH key...
==> default: Machine booted and ready!
==> default: Checking for guest additions in VM...
==> default: Mounting shared folders...
    default: /vagrant => /Users/tsuyoshi/vagrant
```

この状態でVMWareのGUIを確認すると、デフォルトのVMが起動していることを確認できます。

では、作成したインスタンスにログインします。
```
$ vagrant ssh

This system is built by the Bento project by Chef Software
More information can be found at https://github.com/chef/bento
[vagrant@localhost ~]$ hostname
localhost.localdomain
[vagrant@localhost ~]$ pwd
/home/vagrant
```   

必要なくなったらインスタンスを破棄するので以下のコマンドを実行します。
```
$ vagrant destroy
```

### 存在しているboxのリストを取得する
```
$ vagrant box list
bento/centos-7     (virtualbox, 202008.16.0)
bento/centos-7     (virtualbox, 202212.11.0)
bento/ubuntu-18.04 (virtualbox, 202008.16.0)
ubuntu/bionic64    (virtualbox, 20230222.0.0)
```

### vagrant sshでログインする際のSSH接続情報を確認する
以下を見るとデフォルトでは ホストOSのport 2200に、VMのport 22がフォワードされています
```
$ vagrant ssh-config
Host default
  HostName 127.0.0.1
  User vagrant
  Port 2200
  UserKnownHostsFile /dev/null
  StrictHostKeyChecking no
  PasswordAuthentication no
  IdentityFile /Users/tsuyoshi/vagrant/.vagrant/machines/default/virtualbox/private_key
  IdentitiesOnly yes
  LogLevel FATAL
```

### IPアドレスを変更する
起動する仮想OSのIPアドレスを192.168.3.10としたい場合には、Vagrantfileに次のようにconfig.vm.networkを追加します。
```
$ cat Vagrantfile
Vagrant.configure("2") do |config|
  config.vm.box = "bento/centos-7"
  config.vm.network "private_network", ip: "192.168.3.10"
end
$ vagrant up
```

ssh設定にはhostとして192.168.3.10を指定して.ssh/configに保存します。
```
$ vagrant ssh-config --host 192.168.3.10 >> ~/.ssh/config
$ vim ~/.ssh/config
Host 192.168.3.10
  HostName 127.0.0.1
  User vagrant
  Port 2200
  UserKnownHostsFile /dev/null
  StrictHostKeyChecking no
  PasswordAuthentication no
  IdentityFile /Users/xxxx/.vagrant/machines/default/virtualbox/private_key
  IdentitiesOnly yes
  LogLevel FATAL
```

無事IPアドレスでログインできるようになりました。
```
$ ssh 192.168.3.10
Last login: Tue Feb 17 09:08:54 2019 from 10.0.1.2
[vagrant@vagrant-centos-7 ~]$
```

### Boxを追加する
```
$ vagrant box add ubuntu/xenial64
```

### ダウンロード済みのBoxの更新版の有無を確認する
```
$ vagrant box outdated
Checking if box 'ubuntu/focal64' version '20211006.0.0' is up to date...
A newer version of the box 'ubuntu/focal64' for provider 'virtualbox' is
available! You currently have version '20211006.0.0'. The latest is version
'20220302.0.0'. Run `vagrant box update` to update.
```

### 追加したBoxを更新する
```
$ vagrant box update
==> default: Checking for updates to 'bento/centos-7'
    default: Latest installed version: 202008.16.0
    default: Version constraints: 
    default: Provider: virtualbox
==> default: Updating 'bento/centos-7' with provider 'virtualbox' from version
==> default: '202008.16.0' to '202212.11.0'...
==> default: Loading metadata for box 'https://vagrantcloud.com/bento/centos-7'
==> default: Adding box 'bento/centos-7' (v202212.11.0) for provider: virtualbox
    default: Downloading: https://vagrantcloud.com/bento/boxes/centos-7/versions/202212.11.0/providers/virtualbox.box
==> default: Successfully added box 'bento/centos-7' (v202212.11.0) for 'virtualbox'!
$ 
```

特定のboxを指定してアップデートすることも可能です。
```
$ vagrant box update --box ubuntu/trusty64
```

### バージョン違いの Box が複数存在する場合、古いバージョンの Box を削除します。
まずはリストを確認すると下記の例ではcentos-7が複数バージョン存在しています。
```
[~]$ vagrant box list
bento/centos-7     (virtualbox, 202008.16.0)
bento/centos-7     (virtualbox, 202212.11.0)
bento/ubuntu-18.04 (virtualbox, 202008.16.0)
ubuntu/bionic64    (virtualbox, 20230222.0.0)
```

dry-runオプションを指定して何が削除されるのかを事前に確認できます。まずはこれを実行します。
```
[~]$ vagrant box prune --dry-run
The following boxes will be kept...
bento/centos-7     (virtualbox, 202212.11.0)
bento/ubuntu-18.04 (virtualbox, 202008.16.0)
ubuntu/bionic64    (virtualbox, 20230222.0.0)
Checking for older boxes...
Would remove bento/centos-7 virtualbox 202008.16.0
```

古いバージョンのBoxを削除します。 途中でインタラクティブにboxを削除しても良いかどうかの確認があります。
```
[~]$ vagrant box prune 
The following boxes will be kept...
bento/centos-7     (virtualbox, 202212.11.0)
bento/ubuntu-18.04 (virtualbox, 202008.16.0)
ubuntu/bionic64    (virtualbox, 20230222.0.0)

Checking for older boxes...
Box 'bento/centos-7' (v202008.16.0) with provider 'virtualbox' appears
to still be in use by at least one Vagrant environment. Removing
the box could corrupt the environment. We recommend destroying
these environments first:

default (ID: 1b6d6f1c94bd42beb4c2235d53e2174c)
default (ID: 22a5a531a1e040f98e7c78256c3d15f8)
default (ID: fda1d95797234d06b24ac191ca89bca7)

Are you sure you want to remove this box? [y/N] y
Removing box 'bento/centos-7' (v202008.16.0) with provider 'virtualbox'...
```

再度リストを確認するとcentos-7の重複したバージョンで古いバージョンが削除されています。
```
[~]$ vagrant box list
bento/centos-7     (virtualbox, 202212.11.0)
bento/ubuntu-18.04 (virtualbox, 202008.16.0)
ubuntu/bionic64    (virtualbox, 20230222.0.0)
```

### Boxを削除する
```
$ vagrant box remove ubuntu/trusty64
```

また以下の例のように複数のバージョンが存在していて、通常だと存在する全てが削除されるので、ターゲットバージョンを指定したい場合には、
```
$ vagrant box list
centos/7        (virtualbox, 1708.01)
centos/7        (virtualbox, 1801.02)
```

バージョンを指定して削除することができます。
```
$ vagrant box remove centos/7 --box-version 1708.01
Removing box 'centos/7' (v1708.01) with provider 'virtualbox'...
```

### ヘルプオプションを確認する
```
$ vagrant -h
Usage: vagrant [options] <command> [<args>]

    -h, --help                       Print this help.

Common commands:
     autocomplete    manages autocomplete installation on host
     box             manages boxes: installation, removal, etc.
     cloud           manages everything related to Vagrant Cloud
     destroy         stops and deletes all traces of the vagrant machine
     global-status   outputs status Vagrant environments for this user
     halt            stops the vagrant machine
     help            shows the help for a subcommand
     init            initializes a new Vagrant environment by creating a Vagrantfile
     login           
     package         packages a running vagrant environment into a box
     plugin          manages plugins: install, uninstall, update, etc.
     port            displays information about guest port mappings
     powershell      connects to machine via powershell remoting
     provision       provisions the vagrant machine
     push            deploys code in this environment to a configured destination
     rdp             connects to machine via RDP
     reload          restarts vagrant machine, loads new Vagrantfile configuration
     resume          resume a suspended vagrant machine
     serve           start Vagrant server
     snapshot        manages snapshots: saving, restoring, etc.
     ssh             connects to machine via SSH
     ssh-config      outputs OpenSSH valid configuration to connect to the machine
     status          outputs status of the vagrant machine
     suspend         suspends the machine
     up              starts and provisions the vagrant environment
     upload          upload to machine via communicator
     validate        validates the Vagrantfile
     version         prints current and latest Vagrant version
     winrm           executes commands on a machine via WinRM
     winrm-config    outputs WinRM configuration to connect to the machine

For help on any individual command run `vagrant COMMAND -h`

Additional subcommands are available, but are either more advanced
or not commonly used. To see all subcommands, run the command
`vagrant list-commands`.
        --[no-]color                 Enable or disable color output
        --machine-readable           Enable machine readable output
    -v, --version                    Display Vagrant version
        --debug                      Enable debug output
        --timestamp                  Enable timestamps on log output
        --debug-timestamp            Enable debug output with timestamps
        --no-tty                     Enable non-interactive output
```

### Vagrantfileに記述できる内容
実際に試したわけではないので、参考URLだけ載せておく。
- https://qiita.com/ryurock/items/91df14537512c03488ac
- https://qiita.com/centipede/items/64e8f7360d2086f4764f
- https://qiita.com/pugiemonn/items/bcd95a35c3ec7624cd61

# 公式資料
- Vagrant公式ドキュメント
  - https://www.vagrantup.com/docs/index

