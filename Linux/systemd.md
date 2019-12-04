# 概要
systemd関連のコマンドについてはRHEL7、Cent7、Fedora15から採用されています。
systemdではこれまでサービス起動スクリプトで定義されていたものがUnitという形で定義されるので、サービスの管理=Unitの管理となる。

なお、今までのランレベルの関係は次の様にサービスに置き換えられています。
```
runlevel0 -> poweroff
runlevel1 -> rescue
runlevel2 -> multi-user
runlevel3 -> multi-user
runlevel4 -> multi-user
runlevel5 -> graphical
runlevel6 -> reboot
```


# 詳細

## unit管理
### サービスとして登録されている一覧が存在する設定ファイルを確認する
今までサービス起動スクリプトとして定義されていたものがunitとして扱われることになります。

各種unitは以下のパスに存在しています。
```
$ ls /usr/lib/systemd/system/
```

例えばredisでは次の場所にunitが存在します。
```
$ ls /usr/lib/systemd/system/redis.service 
/usr/lib/systemd/system/redis.service
```

### unit定義ファイル変更後の読み込み
上記に配置されているsystemdが読み込むunit定義ファイルは修正した後に読み込ませなければなりません。
```
$ sudo systemctl daemon-reload
```

### unit定義ファイルの記述方法
以下を参照のこと
- https://access.redhat.com/documentation/ja-jp/red_hat_enterprise_linux/7/html/system_administrators_guide/sect-managing_services_with_systemd-unit_files


### unit定義ファイルを確認する
```
$ systemctl cat redis.service
# /usr/lib/systemd/system/redis.service
[Unit]
Description=Redis persistent key-value database
After=network.target
After=network-online.target
Wants=network-online.target

[Service]
ExecStart=/usr/bin/redis-server /etc/redis.conf --supervised systemd
ExecStop=/usr/libexec/redis-shutdown
Type=notify
User=redis
Group=redis
RuntimeDirectory=redis
RuntimeDirectoryMode=0755

[Install]
WantedBy=multi-user.target


# /etc/systemd/system/redis.service.d/limit.conf
# If you need to change max open file limit
# for example, when you change maxclient in configuration
# you can change the LimitNOFILE value below
# see "man systemd.exec" for information

[Service]
LimitNOFILE=10240
```


## サービス状態変更
### サービスの起動・停止・再起動
```
$ systemctl start xxx.service
$ systemctl stop xxx.service
$ systemctl restart xxx.service
```

### サービスの設定の再読み込みを行う
```
$ systemctl reload xxx.service
```

### サービスの強制停止
stopで停止できなくなってしまうような場合には
```
$ ps auxww | grep -i redis
redis     3902  0.3  0.1 142956  5804 ?        Ssl  08:39   0:00 /usr/bin/redis-server 127.0.0.1:6379
tsuyoshi  3906  0.0  0.0   9088   668 pts/0    R+   08:39   0:00 grep --color=auto -i redis
```

killを使って強制停止することができます。
```
$ sudo systemctl kill redis
$ ps auxww | grep -i redis
tsuyoshi  3937  0.0  0.0   9088   664 pts/0    S+   08:40   0:00 grep --color=auto -i redis
$
```


### サービスとして登録されている一覧を確認する
```
$ systemctl list-unit-files
UNIT FILE                                     STATE   
proc-sys-fs-binfmt_misc.automount             static  
dev-hugepages.mount                           static  
dev-mqueue.mount                              static  
proc-sys-fs-binfmt_misc.mount                 static  
sys-fs-fuse-connections.mount                 static  
sys-kernel-config.mount                       static  
sys-kernel-debug.mount                        static  
tmp.mount                                     disabled
brandbot.path                                 disabled
systemd-ask-password-console.path             static  
systemd-ask-password-plymouth.path            static  
systemd-ask-password-wall.path                static  
session-1.scope                               static  
arp-ethers.service                            disabled
auditd.service                                enabled 
autovt@.service                               enabled 
blk-availability.service                      disabled
brandbot.service                              static  
chrony-dnssrv@.service                        static  
chrony-wait.service                           disabled
chronyd.service                               enabled 
console-getty.service                         disabled
console-shell.service                         disabled
container-getty@.service                      static  
cpupower.service                              disabled
crond.service                                 enabled 
...
```

サービス単体で確認するにはis-enabledで確認することができます。
```
$ systemctl is-enabled cpupower.service
disabled
```

上記出力からサービスのステータスには次の３つの状態が存在することがわかります。
- static
- enabled
- disabled

### サービスの有効化・無効化
有効化は次の様にします。
```
$ systemctl enable xxx.service 
```

無効化は次の様にします。
```
$ systemctl disable xxx.service 
```

### サービスのマスキングを行う
Unitが無効化されていたとしてもサービスを起動することは可能です。
このため、maskという仕組みを使うことでサービスの起動自体を防ぐことを可能にします。
```
$ sudo systemctl mask redis.service
Created symlink from /etc/systemd/system/redis.service to /dev/null.
$ sudo systemctl start redis.service
Failed to start redis.service: Unit is masked.
```

unitの状態を確認するとmaskされています。
```
$ sudo systemctl is-enabled redis.service
masked
```

maskを解除するにはunmaskを利用します。
```
$ sudo systemctl unmask redis.service
Removed symlink /etc/systemd/system/redis.service.
$ sudo systemctl start redis.service
$ ps auxww | grep -i redis
redis     4072  0.5  0.1 142956  5804 ?        Ssl  08:52   0:00 /usr/bin/redis-server 127.0.0.1:6379
tsuyoshi  4076  0.0  0.0   9088   668 pts/0    R+   08:52   0:00 grep --color=auto -i redis
```


### サービスのステータス情報を確認する
```
$ systemctl status crond.service 
* crond.service - Command Scheduler
   Loaded: loaded (/usr/lib/systemd/system/crond.service; enabled; vendor preset: enabled)
   Active: active (running) since Wed 2019-12-04 08:20:31 JST; 4min 20s ago
 Main PID: 2779 (crond)
   CGroup: /system.slice/crond.service
           `-2779 /usr/sbin/crond -n

Dec 04 08:20:31 localhost.localdomain systemd[1]: Started Command Scheduler.
Dec 04 08:20:31 localhost.localdomain crond[2779]: (CRON) INFO (RANDOM_DELAY will be scaled with factor 55% if used.)
Dec 04 08:20:31 localhost.localdomain crond[2779]: (CRON) INFO (running with inotify support)
```

### サービスの情報を取得する
目視ではstatusの方が便利ですが、プログラムからサービス情報を取得する際にはshowコマンドが便利です。
no-pagerオプションを付与しているのはlessでの表示を防ぐためなので外しても問題ありません。

```
$ sudo systemctl show redis.service --no-pager
Type=notify
Restart=no
NotifyAccess=main
RestartUSec=100ms
TimeoutStartUSec=1min 30s
TimeoutStopUSec=1min 30s
WatchdogUSec=0
WatchdogTimestampMonotonic=0
StartLimitInterval=10000000
StartLimitBurst=5
StartLimitAction=none
FailureAction=none
PermissionsStartOnly=no
RootDirectoryStartOnly=no
RemainAfterExit=no
GuessMainPID=yes
MainPID=0
ControlPID=0
FileDescriptorStoreMax=0
StatusErrno=0
Result=exit-code
ExecMainStartTimestamp=Wed 2019-12-04 08:39:56 JST
ExecMainStartTimestampMonotonic=1170218767
ExecMainExitTimestamp=Wed 2019-12-04 08:40:05 JST
ExecMainExitTimestampMonotonic=1179721711
ExecMainPID=3902
ExecMainCode=1
ExecMainStatus=0
ExecStart={ path=/usr/bin/redis-server ; argv[]=/usr/bin/redis-server /etc/redis.conf --supervised systemd ; ignore_errors=no ; start_time=[Wed 2019-12-04 08:39:56 JST] ; stop_time=[Wed 2019-12-04 08:40:05 JST] ; pid=3902 ; code=exited ; status=0 }
ExecStop={ path=/usr/libexec/redis-shutdown ; argv[]=/usr/libexec/redis-shutdown ; ignore_errors=no ; start_time=[Wed 2019-12-04 08:40:05 JST] ; stop_time=[Wed 2019-12-04 08:40:05 JST] ; pid=3922 ; code=exited ; status=1 }
Slice=system.slice
MemoryCurrent=18446744073709551615
TasksCurrent=18446744073709551615
Delegate=no
CPUAccounting=no
CPUShares=18446744073709551615
StartupCPUShares=18446744073709551615
CPUQuotaPerSecUSec=infinity
BlockIOAccounting=no
BlockIOWeight=18446744073709551615
StartupBlockIOWeight=18446744073709551615
MemoryAccounting=no
MemoryLimit=18446744073709551615
DevicePolicy=auto
TasksAccounting=no
TasksMax=18446744073709551615
UMask=0022
LimitCPU=18446744073709551615
LimitFSIZE=18446744073709551615
LimitDATA=18446744073709551615
LimitSTACK=18446744073709551615
LimitCORE=18446744073709551615
LimitRSS=18446744073709551615
LimitNOFILE=10240
LimitAS=18446744073709551615
LimitNPROC=15063
LimitMEMLOCK=65536
LimitLOCKS=18446744073709551615
LimitSIGPENDING=15063
LimitMSGQUEUE=819200
LimitNICE=0
LimitRTPRIO=0
LimitRTTIME=18446744073709551615
OOMScoreAdjust=0
Nice=0
IOScheduling=0
CPUSchedulingPolicy=0
CPUSchedulingPriority=0
TimerSlackNSec=50000
CPUSchedulingResetOnFork=no
NonBlocking=no
StandardInput=null
StandardOutput=journal
StandardError=inherit
TTYReset=no
TTYVHangup=no
TTYVTDisallocate=no
SyslogPriority=30
SyslogLevelPrefix=yes
SecureBits=0
CapabilityBoundingSet=18446744073709551615
AmbientCapabilities=0
User=redis
Group=redis
MountFlags=0
PrivateTmp=no
PrivateNetwork=no
PrivateDevices=no
ProtectHome=no
ProtectSystem=no
SameProcessGroup=no
IgnoreSIGPIPE=yes
NoNewPrivileges=no
SystemCallErrorNumber=0
RuntimeDirectoryMode=0755
RuntimeDirectory=redis
KillMode=control-group
KillSignal=15
SendSIGKILL=yes
SendSIGHUP=no
Id=redis.service
Names=redis.service
Requires=basic.target
Wants=system.slice network-online.target
Conflicts=shutdown.target
Before=shutdown.target
After=systemd-journald.socket network-online.target system.slice basic.target network.target
Description=Redis persistent key-value database
LoadState=loaded
ActiveState=failed
SubState=failed
FragmentPath=/usr/lib/systemd/system/redis.service
DropInPaths=/etc/systemd/system/redis.service.d/limit.conf
UnitFileState=disabled
UnitFilePreset=disabled
InactiveExitTimestamp=Wed 2019-12-04 08:39:56 JST
InactiveExitTimestampMonotonic=1170219915
ActiveEnterTimestamp=Wed 2019-12-04 08:39:56 JST
ActiveEnterTimestampMonotonic=1170240076
ActiveExitTimestamp=Wed 2019-12-04 08:40:05 JST
ActiveExitTimestampMonotonic=1179722082
InactiveEnterTimestamp=Wed 2019-12-04 08:40:05 JST
InactiveEnterTimestampMonotonic=1179756654
CanStart=yes
CanStop=yes
CanReload=no
CanIsolate=no
StopWhenUnneeded=no
RefuseManualStart=no
RefuseManualStop=no
AllowIsolate=no
DefaultDependencies=yes
OnFailureJobMode=replace
IgnoreOnIsolate=no
IgnoreOnSnapshot=no
NeedDaemonReload=no
JobTimeoutUSec=0
JobTimeoutAction=none
ConditionResult=yes
AssertResult=yes
ConditionTimestamp=Wed 2019-12-04 08:39:56 JST
ConditionTimestampMonotonic=1170217674
AssertTimestamp=Wed 2019-12-04 08:39:56 JST
AssertTimestampMonotonic=1170217674
Transient=no
```

### サービスの起動状態を確認する

### サービスの異常状態を確認する


### 依存関係を表示する
```
$ sudo systemctl list-dependencies redis.service
redis.service
* |-system.slice
* |-basic.target
* | |-microcode.service
* | |-rhel-dmesg.service
* | |-selinux-policy-migrate-local-changes@targeted.service
* | |-paths.target
* | |-slices.target
* | | |--.slice
* | | `-system.slice
* | |-sockets.target
* | | |-dbus.socket
* | | |-dm-event.socket
* | | |-systemd-initctl.socket
* | | |-systemd-journald.socket
* | | |-systemd-shutdownd.socket
* | | |-systemd-udevd-control.socket
* | | `-systemd-udevd-kernel.socket
* | |-sysinit.target
* | | |-dev-hugepages.mount
* | | |-dev-mqueue.mount
* | | |-kmod-static-nodes.service
* | | |-lvm2-lvmetad.socket
* | | |-lvm2-lvmpolld.socket
* | | |-lvm2-monitor.service
* | | |-plymouth-read-write.service
* | | |-plymouth-start.service
* | | |-proc-sys-fs-binfmt_misc.automount
* | | |-rhel-autorelabel.service
* | | |-rhel-domainname.service
* | | |-rhel-import-state.service
* | | |-rhel-loadmodules.service
* | | |-sys-fs-fuse-connections.mount
* | | |-sys-kernel-config.mount
* | | |-sys-kernel-debug.mount
* | | |-systemd-ask-password-console.path
* | | |-systemd-binfmt.service
* | | |-systemd-firstboot.service
* | | |-systemd-hwdb-update.service
* | | |-systemd-journal-catalog-update.service
* | | |-systemd-journal-flush.service
* | | |-systemd-journald.service
* | | |-systemd-machine-id-commit.service
* | | |-systemd-modules-load.service
* | | |-systemd-random-seed.service
* | | |-systemd-sysctl.service
* | | |-systemd-tmpfiles-setup-dev.service
* | | |-systemd-tmpfiles-setup.service
* | | |-systemd-udev-trigger.service
* | | |-systemd-udevd.service
* | | |-systemd-update-done.service
* | | |-systemd-update-utmp.service
* | | |-systemd-vconsole-setup.service
* | | |-cryptsetup.target
* | | |-local-fs.target
* | | | |--.mount
* | | | |-boot.mount
* | | | |-rhel-readonly.service
* | | | `-systemd-remount-fs.service
* | | `-swap.target
* | |   `-dev-mapper-centos\x2dswap.swap
* | `-timers.target
* |   `-systemd-tmpfiles-clean.timer
* `-network-online.target
*   `-NetworkManager-wait-online.service
```

## ログ周り





# 参考資料
- Linux女子部　systemd徹底入門
  - https://www.slideshare.net/enakai/linux-27872553
- はじめてのsystemdサービス管理ガイド
  - https://dev.classmethod.jp/cloud/aws/service-control-use-systemd/


