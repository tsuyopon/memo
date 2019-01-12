# virtualBox on MACについて
MacでのVirtual Boxの扱いについてまとめておく

### ネットワーク構成について
- VirtualBoxで実現可能なネットワーク構成について
  - http://c-through.blogto.jp/archives/14539119.html

- NAT + ホストオンリーモード設定については以下を参照した
  - http://manchan-pc.blogspot.jp/2012/09/virtualboxpcnw.html

### ホストOSからゲストOSにssh できるようにしたい。

NAT + ホストオンリーモードの初期状態であるとする。

以下を参考にしてゲストOS側に/etc/sysconfig/network-scripts/ifcfg-eth0のstatic IPアドレス設定を行わせます。
- http://www.workabroad.jp/tech/622

続いて、
- http://d.hatena.ne.jp/bojovs/20090325/1237985409
を参考にして実施ポート設定を行います。

ここでFedoraTest1というのは仮想環境の名称となります
```
$ VBoxManage setextradata "FedoraTest1" "VBoxInternal/Devices/pcnet/0/LUN#0/Config/guestssh/Protocol" TCP
$ VBoxManage setextradata "FedoraTest1" "VBoxInternal/Devices/pcnet/0/LUN#0/Config/guestssh/GuestPort" 22
$ VBoxManage setextradata "FedoraTest1" "VBoxInternal/Devices/pcnet/0/LUN#0/Config/guestssh/HostPort" 50022
```

以下のエラーが出ました。
- http://murayama.hatenablog.com/entry/20100801/1280628489

以下で設定を確認することができます。
```
$ VBoxManage getextradata "FedoraTest1" enumerate
Key: GUI/LastCloseAction, Value: PowerOff
Key: GUI/LastGuestSizeHint, Value: 720,400
Key: GUI/LastNormalWindowPosition, Value: 400,46,640,501
Key: GUI/LastScaleWindowPosition, Value: 400,189,640,480
Key: GUI/RestrictedRuntimeDevicesMenuActions, Value: HardDrives
Key: GUI/RestrictedRuntimeMachineMenuActions, Value: SaveState,PowerOff
Key: GUI/StatusBar/IndicatorOrder, Value: HardDisks,OpticalDisks,FloppyDisks,Network,USB,SharedFolders,Display,VideoCapture,Features,Mouse,Keyboard
Key: VBoxInternal/Devices/pcnet/0/LUN#0/Config/guestssh/GuestPort, Value: 22
Key: VBoxInternal/Devices/pcnet/0/LUN#0/Config/guestssh/HostPort, Value: 50022
Key: VBoxInternal/Devices/pcnet/0/LUN#0/Config/guestssh/Protocol, Value: TCP
```

あやまった設定を解除します。
```
$ VBoxManage setextradata "FedoraTest1" "VBoxInternal/Devices/pcnet/0/LUN#0/Config/guestssh/Protocol"
$ VBoxManage setextradata "FedoraTest1" "VBoxInternal/Devices/pcnet/0/LUN#0/Config/guestssh/GuestPort"
$ VBoxManage setextradata "FedoraTest1" "VBoxInternal/Devices/pcnet/0/LUN#0/Config/guestssh/HostPort"
```

新しい設定を追加(e1000になっていることに注意)します。
```
$ VBoxManage setextradata "FedoraTest1" "VBoxInternal/Devices/e1000/0/LUN#0/Config/guestssh/Protocol" TCP
$ VBoxManage setextradata "FedoraTest1" "VBoxInternal/Devices/e1000/0/LUN#0/Config/guestssh/GuestPort" 22
$ VBoxManage setextradata "FedoraTest1" "VBoxInternal/Devices/e1000/0/LUN#0/Config/guestssh/HostPort" 50022
```

以下のコマンドで入ることができます。
```
$ ssh localhost -p 50022
```

### ゲストOS側の80番ブラウザにアクセスする(centOS7)
ブラウザからアクセスしても、ずっと接続しているような状態になっていて応答が返ってきませんでした。
行ったことをすべて記述しているのですべてが必要かどうかは不明ですが、VirtualBoxのUIからの設定とfirewalldを停止するのはCentOS7には必ず必要と思われます。

- VirtualBoxのUI上から該当のVMを選択して以下の作業を行う。
  - Virtualboxの"設定" -> "ネットワーク"で"高度"を展開 -> 「ポートフォワーディング」 -> 名前"www"、プロトコル"TCP"、ホストポート"50080"、ゲストポート"80"
  - (参考) http://zorinos.seesaa.net/article/450523806.html

- ホストOS上から次の設定を追加しておきます(本当に必要かは不明)
```
$ VBoxManage setextradata "FedoraTest1" "VBoxInternal/Devices/e1000/0/LUN#0/Config/guestwww/Protocol" TCP
$ VBoxManage setextradata "FedoraTest1" "VBoxInternal/Devices/e1000/0/LUN#0/Config/guestwww/GuestPort" 80
$ VBoxManage setextradata "FedoraTest1" "VBoxInternal/Devices/e1000/0/LUN#0/Config/guestwww/HostPort" 50080
```

- ゲストOS側では50080が起動、ホストOS側では80が起動しているのを確認しておきます
```
$ netstat -an | grep -iw listen
```

- 念のためにSELinuxをoffにしておきます。offにしたらOSを再起動しておいてもいいかもしれません。(本当に必要かは不明)
```
# vi /etc/selinux/config
SELINUX=disabled
```

CentOS7からはiptabblesではなくfirewalld
```
$ systemctl stop firewalld
==== AUTHENTICATING FOR org.freedesktop.systemd1.manage-units ===
Authentication is required to manage system services or units.
Authenticating as: root
Password: 
==== AUTHENTICATION COMPLETE ===
```

このようにすると
```
http://<hostname>:50080/
```
としてアクセスすることができるようになります。


### サイズを拡張する

```
$ VBoxManage list hdds
UUID:           8906af61-f2b4-4596-8bfb-6d32d4e92829
Parent UUID:    base
State:          created
Type:           normal (base)
Location:       /Users/tsuyoshi/VirtualBox VMs/FedoraTest1/FedoraTest1.vdi
Storage format: VDI
Capacity:       20480 MBytes
Encryption:     disabled

UUID:           24c1c950-b8c9-4216-98d1-b8e502c973ec
Parent UUID:    base
State:          created
Type:           normal (base)
Location:       /Users/tsuyoshi/VirtualBox VMs/LinuxStudy/LinuxStudy.vdi
Storage format: VDI
Capacity:       8192 MBytes
Encryption:     disabled

UUID:           14dc76ed-f735-452c-94e9-88ab1e05c2e2
Parent UUID:    base
State:          created
Type:           normal (base)
Location:       /Users/tsuyoshi/.docker/machine/machines/default/disk.vmdk
Storage format: VMDK
Capacity:       204800 MBytes
Encryption:     disabled

UUID:           1c79ce4a-5543-4323-b36a-ea570df6f45d
Parent UUID:    base
State:          created
Type:           normal (base)
Location:       /Users/tsuyoshi/VirtualBox VMs/LinuxNew/LinuxNew.vdi
Storage format: VDI
Capacity:       8192 MBytes
Encryption:     disabled

UUID:           f2882217-7967-4db0-8750-494b5b8b40ec
Parent UUID:    base
State:          created
Type:           normal (base)
Location:       /Users/tsuyoshi/VirtualBox VMs/NewOSUbuntu/NewOSUbuntu.vdi
Storage format: VDI
Capacity:       8192 MBytes
Encryption:     disabled

UUID:           755d2096-7e3d-4a6e-af04-db7feff6185c
Parent UUID:    base
State:          created
Type:           normal (base)
Location:       /Users/tsuyoshi/VirtualBox VMs/NewOSUbuntu/NewUbuntu.vdi
Storage format: VDI
Capacity:       32768 MBytes
Encryption:     disabled
```

```
tsuyoshi:VirtualBox VMs tsuyoshi$ VBoxManage modifyhd f2882217-7967-4db0-8750-494b5b8b40ec --resize 32768
0%...10%...20%...30%...40%...50%...60%...70%...80%...90%...100%
tsuyoshi:VirtualBox VMs tsuyoshi$ VBoxManage showhdinfo f2882217-7967-4db0-8750-494b5b8b40ec
UUID:           f2882217-7967-4db0-8750-494b5b8b40ec
Parent UUID:    base
State:          created
Type:           normal (base)
Location:       /Users/tsuyoshi/VirtualBox VMs/NewOSUbuntu/NewOSUbuntu.vdi
Storage format: VDI
Format variant: dynamic default
Capacity:       32768 MBytes
Size on disk:   7400 MBytes
Encryption:     disabled
In use by VMs:  NewOSUbuntu (UUID: abc81f5c-d5c3-4e4b-8a70-e15861d3117b)
```

### CentOSのイメージを取得する
- http://www.osboxes.org/centos/

# 参考URL
- ソースコードは無料で閲覧可能
  - http://download.virtualbox.org/virtualbox/5.1.28/VirtualBox-5.1.28.tar.bz2
  - https://www.virtualbox.org/browser/vbox/trunk
  - checkout

```
$ svn co http://www.virtualbox.org/svn/vbox/trunk vbox
```
