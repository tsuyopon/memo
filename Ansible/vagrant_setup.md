# 概要
ansibleはManagedNodeが複数必要です。
仮想環境を立てることでansibleによる動作検証をスムーズに進めるために、ここではvagrantで環境を整備します。

# 詳細

vagrantのインストール手順は割愛します。

下記のようなVagrantfileを用意します。指定できるIPアドレスレンジは制限があるので注意してください。
```
$ cat Vagrantfile
# -*- mode: ruby -*-
# vi: set ft=ruby :


Vagrant.configure("2") do |config|

  config.vm.box = "generic/rocky9"
  # config.vm.network "private_network", type: "dhcp"

  config.vm.define "machine_a" do |machine|
    machine.vm.network "private_network", ip: "192.168.56.101"
  end

  config.vm.define "machine_b" do |machine|
    machine.vm.network "private_network", ip: "192.168.56.102"
  end

  config.vm.provider "virtualbox" do |vb|
    # Display the VirtualBox GUI when booting the machine
    vb.gui = false

    # Customize the amount of memory on the VM:
#    vb.memory = "2048"
#    vb.cpus = "1"
  end
end
```

上記Vagrantfileが存在するディレクトリで下記コマンドを実行してVMを起動します。
```
$ vagrant up
Bringing machine 'machine_a' up with 'virtualbox' provider...
Bringing machine 'machine_b' up with 'virtualbox' provider...
==> machine_a: Checking if box 'generic/rocky9' version '4.2.16' is up to date...
==> machine_a: Fixed port collision for 22 => 2222. Now on port 2200.
==> machine_a: Clearing any previously set network interfaces...
==> machine_a: Preparing network interfaces based on configuration...
    machine_a: Adapter 1: nat
    machine_a: Adapter 2: hostonly
==> machine_a: Forwarding ports...
    machine_a: 22 (guest) => 2200 (host) (adapter 1)
==> machine_a: Running 'pre-boot' VM customizations...
==> machine_a: Booting VM...
==> machine_a: Waiting for machine to boot. This may take a few minutes...
    machine_a: SSH address: 127.0.0.1:2200
    machine_a: SSH username: vagrant
    machine_a: SSH auth method: private key
    machine_a: 
    machine_a: Vagrant insecure key detected. Vagrant will automatically replace
    machine_a: this with a newly generated keypair for better security.
    machine_a: 
    machine_a: Inserting generated public key within guest...
    machine_a: Removing insecure key from the guest if it's present...
    machine_a: Key inserted! Disconnecting and reconnecting using new SSH key...
==> machine_a: Machine booted and ready!
==> machine_a: Checking for guest additions in VM...
==> machine_a: Configuring and enabling network interfaces...
==> machine_b: Importing base box 'generic/rocky9'...
==> machine_b: Matching MAC address for NAT networking...
==> machine_b: Checking if box 'generic/rocky9' version '4.2.16' is up to date...
==> machine_b: Setting the name of the VM: ansible_machine_b_1692830674798_23195
==> machine_b: Fixed port collision for 22 => 2222. Now on port 2201.
==> machine_b: Clearing any previously set network interfaces...
==> machine_b: Preparing network interfaces based on configuration...
    machine_b: Adapter 1: nat
    machine_b: Adapter 2: hostonly
==> machine_b: Forwarding ports...
    machine_b: 22 (guest) => 2201 (host) (adapter 1)
==> machine_b: Running 'pre-boot' VM customizations...
==> machine_b: Booting VM...
==> machine_b: Waiting for machine to boot. This may take a few minutes...
    machine_b: SSH address: 127.0.0.1:2201
    machine_b: SSH username: vagrant
    machine_b: SSH auth method: private key
    machine_b: 
    machine_b: Vagrant insecure key detected. Vagrant will automatically replace
    machine_b: this with a newly generated keypair for better security.
    machine_b: 
    machine_b: Inserting generated public key within guest...
    machine_b: Removing insecure key from the guest if it's present...
    machine_b: Key inserted! Disconnecting and reconnecting using new SSH key...
==> machine_b: Machine booted and ready!
==> machine_b: Checking for guest additions in VM...
==> machine_b: Configuring and enabling network interfaces...
```

起動を確認します。
```
$ vagrant status
Current machine states:

machine_a                 running (virtualbox)
machine_b                 running (virtualbox)

This environment represents multiple VMs. The VMs are all listed
above with their current state. For more information about a specific
VM, run `vagrant status NAME`.
```

vagrant ssh machine_aのようにしてログインできますが、ansibleの場合には直接sshとなります。
このため、sshの設定情報は~/.ssh/configに入れておく必要があります。
```
$ vagrant ssh-config >> ~/.ssh/config
```

下記の情報が書き込まれます。machine_a、machine_b共に127.0.0.1ではありますので、ansibleのhostファイルにはIPではなくホスト名で記載します。
```
$ cat ~/.ssh/config 
Host machine_a
  HostName 127.0.0.1
  User vagrant
  Port 2001
  UserKnownHostsFile /dev/null
  StrictHostKeyChecking no
  PasswordAuthentication no
  IdentityFile /home/tsuyoshi/ansible/.vagrant/machines/machine_a/virtualbox/private_key
  IdentitiesOnly yes
  LogLevel FATAL

Host machine_b
  HostName 127.0.0.1
  User vagrant
  Port 2002
  UserKnownHostsFile /dev/null
  StrictHostKeyChecking no
  PasswordAuthentication no
  IdentityFile /home/tsuyoshi/ansible/.vagrant/machines/machine_b/virtualbox/private_key
  IdentitiesOnly yes
  LogLevel FATAL
```

このようにIPアドレスではなく、ホスト名でhostsを記載することで.ssh/configを適切に識別してくれるようになります。
```
$ cat inventory/hosts 
[alpha]
machine_a
machine_b
```

下記のようにして上記のhostsを指定すると適切に出しわけして来れます。
```
$ ansible alpha -i inventory/hosts -m ping 
machine_a | SUCCESS => {
    "ansible_facts": {
        "discovered_interpreter_python": "/usr/bin/python3"
    },
    "changed": false,
    "ping": "pong"
}
machine_b | SUCCESS => {
    "ansible_facts": {
        "discovered_interpreter_python": "/usr/bin/python3"
    },
    "changed": false,
    "ping": "pong"
}
```
