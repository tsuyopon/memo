# 概要
vagrantはVirtualBoxを操作するためのフロントエンドツールですので、事前にVirtualBoxのインストールが必要となります。
chefで使われるtest-kitchenでもデフォルトで利用されるようになっています。

このツールを使うとVagrantfileというファイルを用意するだけで、コマンド一発で仮想OS環境が作成できるようになります。

# 詳細

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

### Vagrantfileに記述できる内容
実際に試したわけではないので、参考URLだけ載せておく。
- https://qiita.com/ryurock/items/91df14537512c03488ac
- https://qiita.com/centipede/items/64e8f7360d2086f4764f

# 公式資料
- Vagrant公式ドキュメント
  - https://www.vagrantup.com/docs/index
