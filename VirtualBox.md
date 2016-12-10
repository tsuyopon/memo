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

### ゲストOS側のapacheにアクセスする
- http://www.karakaram.com/virtualbox-port-foawarding
でポートフォワーディング設定を行います。
ホストOSから8080でリクエストすると、ゲストOS側には80でリクエストされるように設定します。

このようにすると
```
http://<hostname>:8080/
```
としてアクセスすることができるようになります。
