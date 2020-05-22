# 概要
Linuxのケーパビリティ機能について
ケーパビリティ機能はコンテナ技術の要素の1つであるので理解しておいた方がよい。

# 詳細

### ケーパビリティの操作をできるシステムコール・コマンドについて
ケーパビリティを操作するシステムコールとコマンドを以下に記載します。
- prctl, capget, capsetシステムコール: 
  - プロセスのCapability Setを操作します。
- setxattr, getxattrシステムコール: 
  - ファイルの拡張属性を操作してCapability Setを扱います。
- attrパッケージ
  - attrコマンド: ファイルの拡張属性を扱います。
  - getfattrコマンド: ファイルの拡張属性を表示します。
  - setfattrコマンド: ファイルの拡張属性を設定します。
- libcapパッケージ
  - capshコマンド: Capability設定をサポートした /bin/bash のラッパーです。
  - getcapコマンド: ファイルのCapability Setを表示します。
  - setcapコマンド: ファイルのCapability Setを設定します。
  - getpcapコマンド: 指定されたプロセスのCapability Setを表示します。

### ケーパビリティ機能を使ってみる
ケーパビリティを与える。CAP_NET_RAWでrawソケットを扱う権限を与えます。
setcapで与えているep の e は effective、p は permitted となっています(後述)
```
$ ls -l /bin/ping
-rwxr-xr-x. 1 root root 66176 Aug  4  2017 /bin/ping
$ cp /bin/ping .
$ ./ping -c1 -q 127.0.0.1
ping: socket: Operation not permitted
$  sudo setcap CAP_NET_RAW+ep ./ping
$ ./ping -c1 -q 127.0.0.1
PING 127.0.0.1 (127.0.0.1) 56(84) bytes of data.

--- 127.0.0.1 ping statistics ---
1 packets transmitted, 1 received, 0% packet loss, time 0ms
rtt min/avg/max/mdev = 0.042/0.042/0.042/0.000 ms
```

上記でセットされたケーパビリティはgetcapコマンドで確認することができます。
```
$ getcap ./ping 
./ping = cap_net_raw+ep
```


CAP_NET_RAWについては以下のmanpageを参照のこと
- https://linuxjm.osdn.jp/html/LDP_man-pages/man7/capabilities.7.html
- https://github.com/torvalds/linux/blob/master/include/uapi/linux/capability.h#L105-L368


### プロセスのケーパビリティを確認する

ケーパビリティセットはビット列で保持しています。
```
$ cat /proc/self/status | grep ^Cap
CapInh:	0000000000000000
CapPrm:	0000000000000000
CapEff:	0000000000000000
CapBnd:	0000001fffffffff
CapAmb:	0000000000000000
```

プロセスは以下の種類のケーパビリティセットを持っています。
実際にカーネルがプロセスが持つ権限をチェックする時は，Effectiveケーパビリティをチェックします。つまりEffectiveで許可されていない操作はできません。

- Inheritable
  - execve(2)した際に継承できるケーパビリティセット。このプロセスから新たにプロセスを作成する場合に継承されるセキュリティビットのようです。
- Permitted
  - EffectiveとInheritableで持つことを許されるケーパビリティセット。つまり、このプロセスに許可されたセキュリティビットです。
- Effective
  - 実際にカーネルがスレッドの実行権限を判定するのに使うケーパビリティセット。
- Bounding
  - CapInhとCapEffで設定されたセキュリティビットに対してマスクをかけるセキュリティビットのです。
- Ambient
  - 特権のない（setuid/setgidされていない）プログラムをexecve(2)した際に子プロセスに継承されるケーパビリティセット（Linux 4.3以降で使用可能）

上記のケーパビリティを変更する機会は次の３つがあります。
- capset(2)
- execve(2)
- prctl(2)


上記の説明については以下の資料に記載されています。
- https://gihyo.jp/admin/serial/01/linux_containers/0042


# 参考URL
- manpage: capability
  - https://linuxjm.osdn.jp/html/LDP_man-pages/man7/capabilities.7.html
- 第42回　Linuxカーネルのケーパビリティ［1］
  - https://gihyo.jp/admin/serial/01/linux_containers/0042
