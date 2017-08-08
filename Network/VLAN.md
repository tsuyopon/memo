# 概要
VLANについて、ここではCisco Catalyst設定方法のコマンドについて載せています。
VLANには次の２つの種類があります。
- アクセスポート
  - １つのVLANに所属するポートです
  - アクセスポートを設定するためにはスタティックVLANとダイナミックVLANの２種類があります。
    - スタティックVLANは、ポートにより所属するVLANを指定する方法です。
    - ダイナミックVLANは、接続されたホストのMACアドレスなどにより、そのポートが所属するVLANを指定する方法です。
- トランクポート
  - 複数のVLANに所属するポートです。主にswitch同士を接続する際に利用されます。
  - トランクポートで接続したリンクのことをトランクリンクと言います。

トランクポートはどのような場合に必要となるかというと、２台のスイッチにまたがってVLANが設定されている場合、
例えば、スイッチAからスイッチBにvlan10, vlan20, vlan30を送る場合には次の２つの方法があります

- スイッチAとスイッチBでアクセスポート３つを作成し、vlan10, vlan20, vlan30と設定する。
- スイッチAとスイッチBでトランクポート１つを作成し、vlan10〜vlan30を送る。トランクポートでは送付するときにVLANを識別するタグを付与、受信するときにタグを除去する。(CiscoではTagging接続と呼ばれるが、メーカーでまちまち)現在は、IEEE802標準である「IEEE802.1Q」が一般的に使用されています。

トランクポートを使うことによってポート数の使いすぎを防いでくれます。


# 設定方法

### VLANの作成
次のような書式となります。
```
(config)# vlan <vlan-id>
(config-vlan)# name <vlan-name>
```

設定例
```
# config t
(config)# vlan 10
(config-vlan)# name TestVLAN10
(config-vlan)# exit
(config)# vlan 20
(config-vlan)# name TestVLAN20
(config-vlan)# exit
```

### VLANの削除
作成時のコマンドにnoを付与します。
```
(config)# no vlan <vlan-id>
```

### 物理ポートにvlanを割り当てる
以下ではGigabitEthernetXを指定していますが、だったりfastEthernetXだったりするのでそこは適宜仕様や設定を確認してください。
```
(config)# inteface GigabitEthernet1/0/1
(config-if)# switchport access vlan TestVLAN10
(config-if)# switchport mode access

(config)# inteface GigabitEthernet1/0/2
(config-if)# switchport access vlan TestVLAN20
(config-if)# switchport mode access

(config)# inteface GigabitEthernet1/0/3
(config-if)# switchport access vlan TestVLAN30
(config-if)# switchport mode access
```

設定したら次のコマンドで確認します。
```
# show vlan

VLAN Name                             Status    Ports
10   TestVLAN10                       active    Gi1/0/1
20   TestVLAN20                       active    Gi1/0/2
30   TestVLAN30                       active    Gi1/0/3
```


### VLANにIPアドレスの割当を行なう
L3スイッチであれば作成したVLANにIPアドレスを割り当て、VLAN間ルーティングを実施することが可能です。
L2スイッチでも複数のVLANにIPを割り当てることも可能ですが、IPの無駄使いであり特に意味はないかと思われます。
```
(config)# interface TestVLAN10
(config-if)# ip address 192.168.10.1 255.255.255.0
(config-if)# no shutdown

(config)# interface TestVLAN20
(config-if)# ip address 192.168.20.1 255.255.255.0
(config-if)# no shutdown

(config)# interface TestVLAN30
(config-if)# ip address 192.168.30.1 255.255.255.0
(config-if)# no shutdown
```

### トランクポートの設定
スイッチA(fastEthernet0/5ポート)とスイッチB(fastEthernet0/1)ポートをトランクリンクすることを仮定します。
```
Switch-A# config t
Switch-A(config)# interface fastEthernet0/5
Switch-A(config-if)# switchport mode trunk
```

```
Switch-B# config t
Switch-B(config)# interface fastEthernet0/1
Switch-B(config-if)# switchport mode trunk
```

設定されたかどうかは次のコマンドで確認できます。
```
#show interfaces fastEthernet 0/3 switchport
```


### VLAN IDの範囲について
VLAN-IDに使用できる範囲は決まっています。
```
0, 4095       システム内部で使用するVLAN
1             イーサネットのデフォルトVLAN
2 - 1001      イーサネットの標準VLAN
1002 - 1005   トークンリング / FDDI のデフォルトVLAN
1006 - 4094   イーサネットの拡張VLAN
```

Ciscoでは1002から10024まではすでに予約されているVLANであり、ユーザー側では使用することができません。


# 参考URL
- http://www.ccna-navi.com/archives/267

