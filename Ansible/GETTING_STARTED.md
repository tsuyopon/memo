# 概要
Ansibleをとりあえず使ってみる
Ansibleは設定構成ツールのために仮想環境を構築するVagrantと合わせて試されることが多いみたいので、その手順で記載します。

下記のAnsibleのドキュメントを参考にして記載しています。
- https://docs.ansible.com/ansible/2.9_ja/scenario_guides/guide_vagrant.html
- https://docs.ansible.com/ansible/latest/getting_started/index.html


# セットアップ(MacOS)
下記でパッケージインストールを行います。
```
$ brew install --cask virtualbox vagrant
$ brew install ansible
```

# 詳細

今回は以下を作業ディレクトリとします。
```
$ mkdir ansible-test
$ cd ansible-test/
```

vagrantでAnsibleから今回練習台として操作するためにあらかじめ対象のノードを2つ起動しておきます。
```
$ vim Vagrantfile 
# -*- mode: ruby -*- 
# vi: set ft=ruby :

Vagrant.configure("2") do |config|

  config.vm.define :node1 do |node|
    node.vm.box = "bento/centos-7"
    node.vm.network :forwarded_port, guest: 22, host: 2001, id: "ssh"
    node.vm.network :private_network, ip: "192.168.33.11"
  end 

  config.vm.define :node2 do |node|
    node.vm.box = "bento/centos-7"
    node.vm.network :forwarded_port, guest: 22, host: 2002, id: "ssh"
    node.vm.network :forwarded_port, guest: 80, host: 8000, id: "http"
    node.vm.network :private_network, ip: "192.168.33.12"
  end 
  config.vm.provision "shell",
    inline: "echo Hello, World!"

end
$ vagrant up
```

~/.ssh/configに設定情報を入れておきます。
```
$ vagrant ssh-config
Host node1
  HostName 127.0.0.1
  User vagrant
  Port 2001
  UserKnownHostsFile /dev/null
  StrictHostKeyChecking no
  PasswordAuthentication no
  IdentityFile /Users/tsuyoshi/.vagrant/machines/node1/virtualbox/private_key
  IdentitiesOnly yes
  LogLevel FATAL

Host node2
  HostName 127.0.0.1
  User vagrant
  Port 2002
  UserKnownHostsFile /dev/null
  StrictHostKeyChecking no
  PasswordAuthentication no
  IdentityFile /Users/tsuyoshi/.vagrant/machines/node2/virtualbox/private_key
  IdentitiesOnly yes
  LogLevel FATAL

[~/ansible-test]$ vagrant ssh-config >> ~/.ssh/config 
```

上記のssh-configの出力結果に合わせてhostsファイルを整形します。これがInventoryファイルと呼ばれるものです。
```
[testgroup]
node1 ansible_host=node1 ansible_port=2001 ansible_user=vagrant ansible_ssh_private_key_file=/Users/tsuyoshi/.vagrant/machines/node1/virtualbox/private_key
node2 ansible_host=node2 ansible_port=2002 ansible_user=vagrant ansible_ssh_private_key_file=/Users/tsuyoshi/.vagrant/machines/node1/virtualbox/private_key
```

続いて、ansible.cfgを下記内容で用意します。これにより~/.ssh/known_hostsの設定を無効化できます。
```
$ vim ansible.cfg 
[defaults]
host_key_checking = False
```

対象のnodeの2台に対して成功するかを確認します。
```
$ ansible all -i hosts -m ping -v
Using /Users/tsuyoshi/ansible-test/ansible.cfg as config file
node1 | SUCCESS => {
    "ansible_facts": {
        "discovered_interpreter_python": "/usr/bin/python"
    },
    "changed": false,
    "ping": "pong"
}
node2 | SUCCESS => {
    "ansible_facts": {
        "discovered_interpreter_python": "/usr/bin/python"
    },
    "changed": false,
    "ping": "pong"
}
```

では続いてPlaybookであるsite.ymlを用意します。まずは何もしないPlaybookを新規作成します。
```
$ vi site.yml 
---
- name: Playbookチュートリアル
  hosts: all
  tasks:
```

実行してみます。下記のような出力になれば成功です。
```
$ ansible-playbook -i hosts site.yml 

PLAY [Playbookチュートリアル] *************************************************************************************************************************************************************************

TASK [Gathering Facts] ********************************************************************************************************************************************************************************
ok: [vagrant-machine]

PLAY RECAP ********************************************************************************************************************************************************************************************
vagrant-machine            : ok=1    changed=0    unreachable=0    failed=0    skipped=0    rescued=0    ignored=0  
```

これだけだと何もしておらず非常に味気ないのでnginxを入れてみることにします。先ほど作成したsite.ymlを書き換えてください。
```
$ rm site.yml
$ vi site.yml
---
- name: Playbook Sample
  hosts: all
  become: true
  tasks:
    - name: install libselinux-python
      yum:
        name: libselinux-python
        state: present

    - name: install EPEL Repository
      yum:
        name: epel-release
        state: present

    - name: install Nginx
      yum:
        name: nginx
        state: present

    - name: start nginx & auto start setting
      service:
        name: nginx
        state: started
        enabled: true
```

では実行してみます。
```
$ ansible-playbook -i hosts site.yml 

PLAY [Playbook Sample] ********************************************************************************************************************************************************************************

TASK [Gathering Facts] ********************************************************************************************************************************************************************************
ok: [vagrant-machine]

TASK [install libselinux-python] **********************************************************************************************************************************************************************
ok: [vagrant-machine]

TASK [install EPEL Repository] ************************************************************************************************************************************************************************
changed: [vagrant-machine]

TASK [install Nginx] **********************************************************************************************************************************************************************************
changed: [vagrant-machine]

TASK [start nginx & auto start setting] ***************************************************************************************************************************************************************
changed: [vagrant-machine]

PLAY RECAP ********************************************************************************************************************************************************************************************
vagrant-machine            : ok=5    changed=3    unreachable=0    failed=0    skipped=0    rescued=0    ignored=0 
```

最初からvオプションを付与した方がデバッグに必要な情報を表示してくれます。
```
$ ansible-playbook -i hosts site.yml -v
Using /Users/tsuyoshi/ansible-test/ansible.cfg as config file

PLAY [Playbook Sample] ********************************************************************************************************************************************************************************

TASK [Gathering Facts] ********************************************************************************************************************************************************************************
ok: [node2]
ok: [node1]

TASK [install libselinux-python] **********************************************************************************************************************************************************************
ok: [node2] => {"changed": false, "msg": "", "rc": 0, "results": ["libselinux-python-2.5-15.el7.x86_64 providing libselinux-python is already installed"]}
ok: [node1] => {"changed": false, "msg": "", "rc": 0, "results": ["libselinux-python-2.5-15.el7.x86_64 providing libselinux-python is already installed"]}

TASK [install EPEL Repository] ************************************************************************************************************************************************************************
ok: [node2] => {"changed": false, "msg": "", "rc": 0, "results": ["epel-release-7-11.noarch providing epel-release is already installed"]}
changed: [node1] => {"changed": true, "changes": {"installed": ["epel-release"]}, "msg": "", "rc": 0, "results": ["Loaded plugins: fastestmirror\nLoading mirror speeds from cached hostfile\n * base: ftp.riken.jp\n * extras: ftp.riken.jp\n * updates: ftp.riken.jp\nResolving Dependencies\n--> Running transaction check\n---> Package epel-release.noarch 0:7-11 will be installed\n--> Finished Dependency Resolution\n\nDependencies Resolved\n\n================================================================================\n Package                Arch             Version         Repository        Size\n================================================================================\nInstalling:\n epel-release           noarch           7-11            extras            15 k\n\nTransaction Summary\n================================================================================\nInstall  1 Package\n\nTotal download size: 15 k\nInstalled size: 24 k\nDownloading packages:\nRunning transaction check\nRunning transaction test\nTransaction test succeeded\nRunning transaction\n  Installing : epel-release-7-11.noarch                                     1/1 \n  Verifying  : epel-release-7-11.noarch                                     1/1 \n\nInstalled:\n  epel-release.noarch 0:7-11                                                    \n\nComplete!\n"]}

TASK [install Nginx] **********************************************************************************************************************************************************************************
ok: [node2] => {"changed": false, "msg": "", "rc": 0, "results": ["1:nginx-1.20.1-10.el7.x86_64 providing nginx is already installed"]}
changed: [node1] => {"changed": true, "changes": {"installed": ["nginx"]}, "msg": "warning: /var/cache/yum/x86_64/7/epel/packages/nginx-1.20.1-10.el7.x86_64.rpm: Header V4 RSA/SHA256 Signature, key ID 352c64e5: NOKEY\nImporting GPG key 0x352C64E5:\n Userid     : \"Fedora EPEL (7) <epel@fedoraproject.org>\"\n Fingerprint: 91e9 7d7c 4a5e 96f1 7f3e 888f 6a2f aea2 352c 64e5\n Package    : epel-release-7-11.noarch (@extras)\n From       : /etc/pki/rpm-gpg/RPM-GPG-KEY-EPEL-7\n", "rc": 0, "results": ["Loaded plugins: fastestmirror\nLoading mirror speeds from cached hostfile\n * base: ftp.riken.jp\n * epel: ftp.riken.jp\n * extras: ftp.riken.jp\n * updates: ftp.riken.jp\nResolving Dependencies\n--> Running transaction check\n---> Package nginx.x86_64 1:1.20.1-10.el7 will be installed\n--> Processing Dependency: nginx-filesystem = 1:1.20.1-10.el7 for package: 1:nginx-1.20.1-10.el7.x86_64\n--> Processing Dependency: libcrypto.so.1.1(OPENSSL_1_1_0)(64bit) for package: 1:nginx-1.20.1-10.el7.x86_64\n--> Processing Dependency: libssl.so.1.1(OPENSSL_1_1_0)(64bit) for package: 1:nginx-1.20.1-10.el7.x86_64\n--> Processing Dependency: libssl.so.1.1(OPENSSL_1_1_1)(64bit) for package: 1:nginx-1.20.1-10.el7.x86_64\n--> Processing Dependency: nginx-filesystem for package: 1:nginx-1.20.1-10.el7.x86_64\n--> Processing Dependency: redhat-indexhtml for package: 1:nginx-1.20.1-10.el7.x86_64\n--> Processing Dependency: libcrypto.so.1.1()(64bit) for package: 1:nginx-1.20.1-10.el7.x86_64\n--> Processing Dependency: libprofiler.so.0()(64bit) for package: 1:nginx-1.20.1-10.el7.x86_64\n--> Processing Dependency: libssl.so.1.1()(64bit) for package: 1:nginx-1.20.1-10.el7.x86_64\n--> Running transaction check\n---> Package centos-indexhtml.noarch 0:7-9.el7.centos will be installed\n---> Package gperftools-libs.x86_64 0:2.6.1-1.el7 will be installed\n---> Package nginx-filesystem.noarch 1:1.20.1-10.el7 will be installed\n---> Package openssl11-libs.x86_64 1:1.1.1k-4.el7 will be installed\n--> Finished Dependency Resolution\n\nDependencies Resolved\n\n================================================================================\n Package                 Arch          Version                Repository   Size\n================================================================================\nInstalling:\n nginx                   x86_64        1:1.20.1-10.el7        epel        588 k\nInstalling for dependencies:\n centos-indexhtml        noarch        7-9.el7.centos         base         92 k\n gperftools-libs         x86_64        2.6.1-1.el7            base        272 k\n nginx-filesystem        noarch        1:1.20.1-10.el7        epel         24 k\n openssl11-libs          x86_64        1:1.1.1k-4.el7         epel        1.5 M\n\nTransaction Summary\n================================================================================\nInstall  1 Package (+4 Dependent packages)\n\nTotal download size: 2.4 M\nInstalled size: 6.7 M\nDownloading packages:\nPublic key for nginx-1.20.1-10.el7.x86_64.rpm is not installed\n--------------------------------------------------------------------------------\nTotal                                              2.8 MB/s | 2.4 MB  00:00     \nRetrieving key from file:///etc/pki/rpm-gpg/RPM-GPG-KEY-EPEL-7\nRunning transaction check\nRunning transaction test\nTransaction test succeeded\nRunning transaction\n  Installing : 1:nginx-filesystem-1.20.1-10.el7.noarch                      1/5 \n  Installing : centos-indexhtml-7-9.el7.centos.noarch                       2/5 \n  Installing : gperftools-libs-2.6.1-1.el7.x86_64                           3/5 \n  Installing : 1:openssl11-libs-1.1.1k-4.el7.x86_64                         4/5 \n  Installing : 1:nginx-1.20.1-10.el7.x86_64                                 5/5 \n  Verifying  : 1:openssl11-libs-1.1.1k-4.el7.x86_64                         1/5 \n  Verifying  : gperftools-libs-2.6.1-1.el7.x86_64                           2/5 \n  Verifying  : centos-indexhtml-7-9.el7.centos.noarch                       3/5 \n  Verifying  : 1:nginx-filesystem-1.20.1-10.el7.noarch                      4/5 \n  Verifying  : 1:nginx-1.20.1-10.el7.x86_64                                 5/5 \n\nInstalled:\n  nginx.x86_64 1:1.20.1-10.el7                                                  \n\nDependency Installed:\n  centos-indexhtml.noarch 0:7-9.el7.centos gperftools-libs.x86_64 0:2.6.1-1.el7\n  nginx-filesystem.noarch 1:1.20.1-10.el7  openssl11-libs.x86_64 1:1.1.1k-4.el7\n\nComplete!\n"]}

TASK [start nginx & auto start setting] ***************************************************************************************************************************************************************
ok: [node2] => {"changed": false, "enabled": true, "name": "nginx", "state": "started", "status": {"ActiveEnterTimestamp": "金 2023-02-24 03:48:32 UTC", "ActiveEnterTimestampMonotonic": "2073849345", "ActiveExitTimestampMonotonic": "0", "ActiveState": "active", "After": "-.mount systemd-journald.socket basic.target tmp.mount remote-fs.target network-online.target nss-lookup.target system.slice", "AllowIsolate": "no", "AmbientCapabilities": "0", "AssertResult": "yes", "AssertTimestamp": "金 2023-02-24 03:48:32 UTC", "AssertTimestampMonotonic": "2073805442", "Before": "multi-user.target shutdown.target", "BlockIOAccounting": "no", "BlockIOWeight": "18446744073709551615", "CPUAccounting": "no", "CPUQuotaPerSecUSec": "infinity", "CPUSchedulingPolicy": "0", "CPUSchedulingPriority": "0", "CPUSchedulingResetOnFork": "no", "CPUShares": "18446744073709551615", "CanIsolate": "no", "CanReload": "yes", "CanStart": "yes", "CanStop": "yes", "CapabilityBoundingSet": "18446744073709551615", "CollectMode": "inactive", "ConditionResult": "yes", "ConditionTimestamp": "金 2023-02-24 03:48:32 UTC", "ConditionTimestampMonotonic": "2073805442", "Conflicts": "shutdown.target", "ControlGroup": "/system.slice/nginx.service", "ControlPID": "0", "DefaultDependencies": "yes", "Delegate": "no", "Description": "The nginx HTTP and reverse proxy server", "DevicePolicy": "auto", "ExecMainCode": "0", "ExecMainExitTimestampMonotonic": "0", "ExecMainPID": "3909", "ExecMainStartTimestamp": "金 2023-02-24 03:48:32 UTC", "ExecMainStartTimestampMonotonic": "2073849288", "ExecMainStatus": "0", "ExecReload": "{ path=/usr/sbin/nginx ; argv[]=/usr/sbin/nginx -s reload ; ignore_errors=no ; start_time=[n/a] ; stop_time=[n/a] ; pid=0 ; code=(null) ; status=0/0 }", "ExecStart": "{ path=/usr/sbin/nginx ; argv[]=/usr/sbin/nginx ; ignore_errors=no ; start_time=[金 2023-02-24 03:48:32 UTC] ; stop_time=[金 2023-02-24 03:48:32 UTC] ; pid=3908 ; code=exited ; status=0 }", "ExecStartPre": "{ path=/usr/sbin/nginx ; argv[]=/usr/sbin/nginx -t ; ignore_errors=no ; start_time=[金 2023-02-24 03:48:32 UTC] ; stop_time=[金 2023-02-24 03:48:32 UTC] ; pid=3903 ; code=exited ; status=0 }", "FailureAction": "none", "FileDescriptorStoreMax": "0", "FragmentPath": "/usr/lib/systemd/system/nginx.service", "GuessMainPID": "yes", "IOScheduling": "0", "Id": "nginx.service", "IgnoreOnIsolate": "no", "IgnoreOnSnapshot": "no", "IgnoreSIGPIPE": "yes", "InactiveEnterTimestampMonotonic": "0", "InactiveExitTimestamp": "金 2023-02-24 03:48:32 UTC", "InactiveExitTimestampMonotonic": "2073807509", "JobTimeoutAction": "none", "JobTimeoutUSec": "0", "KillMode": "process", "KillSignal": "3", "LimitAS": "18446744073709551615", "LimitCORE": "18446744073709551615", "LimitCPU": "18446744073709551615", "LimitDATA": "18446744073709551615", "LimitFSIZE": "18446744073709551615", "LimitLOCKS": "18446744073709551615", "LimitMEMLOCK": "65536", "LimitMSGQUEUE": "819200", "LimitNICE": "0", "LimitNOFILE": "4096", "LimitNPROC": "3880", "LimitRSS": "18446744073709551615", "LimitRTPRIO": "0", "LimitRTTIME": "18446744073709551615", "LimitSIGPENDING": "3880", "LimitSTACK": "18446744073709551615", "LoadState": "loaded", "MainPID": "3909", "MemoryAccounting": "no", "MemoryCurrent": "18446744073709551615", "MemoryLimit": "18446744073709551615", "MountFlags": "0", "Names": "nginx.service", "NeedDaemonReload": "no", "Nice": "0", "NoNewPrivileges": "no", "NonBlocking": "no", "NotifyAccess": "none", "OOMScoreAdjust": "0", "OnFailureJobMode": "replace", "PIDFile": "/run/nginx.pid", "PermissionsStartOnly": "no", "PrivateDevices": "no", "PrivateNetwork": "no", "PrivateTmp": "yes", "ProtectHome": "no", "ProtectSystem": "no", "RefuseManualStart": "no", "RefuseManualStop": "no", "RemainAfterExit": "no", "Requires": "basic.target -.mount system.slice", "RequiresMountsFor": "/var/tmp", "Restart": "no", "RestartUSec": "100ms", "Result": "success", "RootDirectoryStartOnly": "no", "RuntimeDirectoryMode": "0755", "SameProcessGroup": "no", "SecureBits": "0", "SendSIGHUP": "no", "SendSIGKILL": "yes", "Slice": "system.slice", "StandardError": "inherit", "StandardInput": "null", "StandardOutput": "journal", "StartLimitAction": "none", "StartLimitBurst": "5", "StartLimitInterval": "10000000", "StartupBlockIOWeight": "18446744073709551615", "StartupCPUShares": "18446744073709551615", "StatusErrno": "0", "StopWhenUnneeded": "no", "SubState": "running", "SyslogLevelPrefix": "yes", "SyslogPriority": "30", "SystemCallErrorNumber": "0", "TTYReset": "no", "TTYVHangup": "no", "TTYVTDisallocate": "no", "TasksAccounting": "no", "TasksCurrent": "18446744073709551615", "TasksMax": "18446744073709551615", "TimeoutStartUSec": "1min 30s", "TimeoutStopUSec": "5s", "TimerSlackNSec": "50000", "Transient": "no", "Type": "forking", "UMask": "0022", "UnitFilePreset": "disabled", "UnitFileState": "enabled", "WantedBy": "multi-user.target", "Wants": "network-online.target", "WatchdogTimestamp": "金 2023-02-24 03:48:32 UTC", "WatchdogTimestampMonotonic": "2073849312", "WatchdogUSec": "0"}}
changed: [node1] => {"changed": true, "enabled": true, "name": "nginx", "state": "started", "status": {"ActiveEnterTimestampMonotonic": "0", "ActiveExitTimestampMonotonic": "0", "ActiveState": "inactive", "After": "tmp.mount network-online.target remote-fs.target system.slice systemd-journald.socket basic.target -.mount nss-lookup.target", "AllowIsolate": "no", "AmbientCapabilities": "0", "AssertResult": "no", "AssertTimestampMonotonic": "0", "Before": "shutdown.target", "BlockIOAccounting": "no", "BlockIOWeight": "18446744073709551615", "CPUAccounting": "no", "CPUQuotaPerSecUSec": "infinity", "CPUSchedulingPolicy": "0", "CPUSchedulingPriority": "0", "CPUSchedulingResetOnFork": "no", "CPUShares": "18446744073709551615", "CanIsolate": "no", "CanReload": "yes", "CanStart": "yes", "CanStop": "yes", "CapabilityBoundingSet": "18446744073709551615", "CollectMode": "inactive", "ConditionResult": "no", "ConditionTimestampMonotonic": "0", "Conflicts": "shutdown.target", "ControlPID": "0", "DefaultDependencies": "yes", "Delegate": "no", "Description": "The nginx HTTP and reverse proxy server", "DevicePolicy": "auto", "ExecMainCode": "0", "ExecMainExitTimestampMonotonic": "0", "ExecMainPID": "0", "ExecMainStartTimestampMonotonic": "0", "ExecMainStatus": "0", "ExecReload": "{ path=/usr/sbin/nginx ; argv[]=/usr/sbin/nginx -s reload ; ignore_errors=no ; start_time=[n/a] ; stop_time=[n/a] ; pid=0 ; code=(null) ; status=0/0 }", "ExecStart": "{ path=/usr/sbin/nginx ; argv[]=/usr/sbin/nginx ; ignore_errors=no ; start_time=[n/a] ; stop_time=[n/a] ; pid=0 ; code=(null) ; status=0/0 }", "ExecStartPre": "{ path=/usr/sbin/nginx ; argv[]=/usr/sbin/nginx -t ; ignore_errors=no ; start_time=[n/a] ; stop_time=[n/a] ; pid=0 ; code=(null) ; status=0/0 }", "FailureAction": "none", "FileDescriptorStoreMax": "0", "FragmentPath": "/usr/lib/systemd/system/nginx.service", "GuessMainPID": "yes", "IOScheduling": "0", "Id": "nginx.service", "IgnoreOnIsolate": "no", "IgnoreOnSnapshot": "no", "IgnoreSIGPIPE": "yes", "InactiveEnterTimestampMonotonic": "0", "InactiveExitTimestampMonotonic": "0", "JobTimeoutAction": "none", "JobTimeoutUSec": "0", "KillMode": "process", "KillSignal": "3", "LimitAS": "18446744073709551615", "LimitCORE": "18446744073709551615", "LimitCPU": "18446744073709551615", "LimitDATA": "18446744073709551615", "LimitFSIZE": "18446744073709551615", "LimitLOCKS": "18446744073709551615", "LimitMEMLOCK": "65536", "LimitMSGQUEUE": "819200", "LimitNICE": "0", "LimitNOFILE": "4096", "LimitNPROC": "3880", "LimitRSS": "18446744073709551615", "LimitRTPRIO": "0", "LimitRTTIME": "18446744073709551615", "LimitSIGPENDING": "3880", "LimitSTACK": "18446744073709551615", "LoadState": "loaded", "MainPID": "0", "MemoryAccounting": "no", "MemoryCurrent": "18446744073709551615", "MemoryLimit": "18446744073709551615", "MountFlags": "0", "Names": "nginx.service", "NeedDaemonReload": "no", "Nice": "0", "NoNewPrivileges": "no", "NonBlocking": "no", "NotifyAccess": "none", "OOMScoreAdjust": "0", "OnFailureJobMode": "replace", "PIDFile": "/run/nginx.pid", "PermissionsStartOnly": "no", "PrivateDevices": "no", "PrivateNetwork": "no", "PrivateTmp": "yes", "ProtectHome": "no", "ProtectSystem": "no", "RefuseManualStart": "no", "RefuseManualStop": "no", "RemainAfterExit": "no", "Requires": "-.mount basic.target system.slice", "RequiresMountsFor": "/var/tmp", "Restart": "no", "RestartUSec": "100ms", "Result": "success", "RootDirectoryStartOnly": "no", "RuntimeDirectoryMode": "0755", "SameProcessGroup": "no", "SecureBits": "0", "SendSIGHUP": "no", "SendSIGKILL": "yes", "Slice": "system.slice", "StandardError": "inherit", "StandardInput": "null", "StandardOutput": "journal", "StartLimitAction": "none", "StartLimitBurst": "5", "StartLimitInterval": "10000000", "StartupBlockIOWeight": "18446744073709551615", "StartupCPUShares": "18446744073709551615", "StatusErrno": "0", "StopWhenUnneeded": "no", "SubState": "dead", "SyslogLevelPrefix": "yes", "SyslogPriority": "30", "SystemCallErrorNumber": "0", "TTYReset": "no", "TTYVHangup": "no", "TTYVTDisallocate": "no", "TasksAccounting": "no", "TasksCurrent": "18446744073709551615", "TasksMax": "18446744073709551615", "TimeoutStartUSec": "1min 30s", "TimeoutStopUSec": "5s", "TimerSlackNSec": "50000", "Transient": "no", "Type": "forking", "UMask": "0022", "UnitFilePreset": "disabled", "UnitFileState": "disabled", "Wants": "network-online.target", "WatchdogTimestampMonotonic": "0", "WatchdogUSec": "0"}}

PLAY RECAP ********************************************************************************************************************************************************************************************
node1                      : ok=5    changed=3    unreachable=0    failed=0    skipped=0    rescued=0    ignored=0   
node2                      : ok=5    changed=0    unreachable=0    failed=0    skipped=0    rescued=0    ignored=0 
```

なおvvvにするとデバッグに重要な大量な出力情報を出力してくれます(sshコマンドの実行詳細までを表示します)
```
$ ansible-playbook -i hosts site.yml -vvv
```

# 参考資料
- https://qiita.com/reflet/items/b297aad557a8a426c32d

