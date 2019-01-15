# 仮想化について

- 完全仮想化
- 準仮想化
- VirtualBox
- QEMU
- OpenVZ
- Hyper-V
- VMWare
- KVM
- XEN
- virt-manager
- virsh
- libvirt
- libvim
- Docker
- UEFI
- SeaBios



# 詳細





### ホストOS型とハイパーバイザー型について
ホストOS型とハイパーバイザー型の違い
- http://ascii.jp/elem/000/000/414/414625/index-4.html


- ホスト型
  - Windows, Mac OS X, LinuxといったOSの上で仮想化ソフトを実行して、そこで仮想マシンを実行するタイプである。
  - 実行時のオーバーヘッドがハイパーバイザーよりも大きい
- ハイパーバイザー型
  - ハードウェアのBIOSから直接仮想化ソフトを起動して、その上で仮想マシンを実行するタイプである。


ハイパーバイザー型の場合、仮想マシンの実現方法には「完全仮想化」と「準仮想化」の２つの実装方法が存在します。
これについては次に説明します。

### 準仮想化と完全仮想化について

- 完全仮想化
  - 実ハードウェア向けのOSに付属しているデバイスドライバをそのまま使用できる。
  - ゲストOSを修正する必要がない
- 準仮想化
  - 実ハードウェア向けのOSに付属しているデバイスドライバをそのまま使用できず、ゲスト環境向けに準仮想化用のデバイスドライバをインストールする必要がある。
  - ゲストOSを修正する必要がある
    - 完全仮想化のハードウェアの完全エミュレーションは十分な性能が出ないのでゲストOSを修正する。


### Nested Virtualization

```
// Intel
$ cat /sys/module/kvm_intel/parameters/nested
Y

// AMD
/sys/module/kvm_amd/parameters/nested
```

- 参考
  - https://docs.fedoraproject.org/en-US/quick-docs/using-nested-virtualization-in-kvm/

### TODO
- SeaBiosについて整理する
  - http://d.hatena.ne.jp/kvm/20110522/1306064742
- KVM ディスク操作(qcow2, rawなど)
  - http://d.hatena.ne.jp/kt_hiro/20120819/1345351773
- How to enable nested virtualization in KVM
  - https://docs.fedoraproject.org/en-US/quick-docs/using-nested-virtualization-in-kvm/
- 基本問題
  - http://icttoracon.net/tech-blog/2018/08/27/ictsc2018-prep01-xen-w/
- QEMUについてまとまっている
  - https://wiki.archlinux.jp/index.php/QEMU
- 参考
  - What are the differences between QEMU and VirtualBox?
    - https://stackoverflow.com/questions/43704856/what-are-the-differences-between-qemu-and-virtualbox
  - What's the differences between Xen, QEMU and KVM?
    - https://stackoverflow.com/questions/10307323/whats-the-differences-between-xen-qemu-and-kvm?noredirect=1&lq=1
  - Difference between bare metal (hypervisor based) and host virtualization types
    - https://stackoverflow.com/questions/38130453/difference-between-bare-metal-hypervisor-based-and-host-virtualization-types?noredirect=1&lq=1
- QEMU をつかって仮想マシンを作成する
  - https://qiita.com/seijimomoto/items/b7e2a2b28f91c4cb5cec

Linux debug
- How to debug the Linux kernel with GDB and QEMU?
  - https://stackoverflow.com/questions/11408041/how-to-debug-the-linux-kernel-with-gdb-and-qemu
- QEMU on Vagrant on Mac の環境構築メモ
  - http://akouryy.hatenablog.jp/entry/setup/qemu-vagrant?utm_source=feed
- Linux kernelのQEMU+GDBデバッグ環境を整える(Ubuntu)
  - https://kaki-no-tane.hatenablog.com/entry/2018/12/03/135302
- QEMU上のLinuxカーネルをGDBでデバッグする
  - https://www.hiroom2.com/2014/01/15/qemu%E4%B8%8A%E3%81%AElinux%E3%82%AB%E3%83%BC%E3%83%8D%E3%83%AB%E3%82%92gdb%E3%81%A7%E3%83%87%E3%83%90%E3%83%83%E3%82%B0%E3%81%99%E3%82%8B/
- http://proc-cpuinfo.fixstars.com/2017/08/test-and-debug-linux-kernel-with-gdb/
- http://d.hatena.ne.jp/fixme/20101120/1290242209
- Linux kernelをgdbでリモートデバッグするときはKASLRをoffにするのを忘れずに(´・ω・`)
  - https://kernhack.hatenablog.com/entry/2018/02/15/223027




