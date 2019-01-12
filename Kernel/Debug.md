# LinuxKernelデバッグ方法について

まだまだ未完成ですがとりあえずLinux Kernelデバッグ方法についてのメモです。

自身の環境MAC OS上でのVirtual Boxで動かしてみたところのメモ
```
[tsuyoshi@localhost ~]$ uname -a
Linux localhost.localdomain 3.10.0-693.el7.x86_64 #1 SMP Tue Aug 22 21:09:27 UTC 2017 x86_64 x86_64 x86_64 GNU/Linux
[tsuyoshi@localhost ~]$ cat /proc/version 
Linux version 3.10.0-693.el7.x86_64 (builder@kbuilder.dev.centos.org) (gcc version 4.8.5 20150623 (Red Hat 4.8.5-16) (GCC) ) #1 SMP Tue Aug 22 21:09:27 UTC 2017
```

# 詳細
### qemu上で起動させてみる
```
$ qemu-system-x86_64 --kernel /boot/vmlinuz-3.10.0-693.el7.x86_64  -nographic -append "console=ttyS0"
[    0.000000] Initializing cgroup subsys cpuset
[    0.000000] Initializing cgroup subsys cpu
[    0.000000] Initializing cgroup subsys cpuacct
[    0.000000] Linux version 3.10.0-693.el7.x86_64 (builder@kbuilder.dev.centos.org) (gcc version 4.8.5 20150623 (Red Hat 4.8.5-16) (GCC) ) #1 SMP Tue Aug 22 
[    0.000000] Command line: console=ttyS0
[    0.000000] e820: BIOS-provided physical RAM map:
[    0.000000] BIOS-e820: [mem 0x0000000000000000-0x000000000009fbff] usable
[    0.000000] BIOS-e820: [mem 0x000000000009fc00-0x000000000009ffff] reserved
[    0.000000] BIOS-e820: [mem 0x00000000000f0000-0x00000000000fffff] reserved
[    0.000000] BIOS-e820: [mem 0x0000000000100000-0x0000000007ffdfff] usable
[    0.000000] BIOS-e820: [mem 0x0000000007ffe000-0x0000000007ffffff] reserved
[    0.000000] BIOS-e820: [mem 0x00000000fffc0000-0x00000000ffffffff] reserved
[    0.000000] NX (Execute Disable) protection: active
[    0.000000] SMBIOS 2.4 present.
[    0.000000] e820: last_pfn = 0x7ffe max_arch_pfn = 0x400000000
[    0.000000] x86 PAT enabled: cpu 0, old 0x7040600070406, new 0x7010600070106
[    0.000000] found SMP MP-table at [mem 0x000f63c0-0x000f63cf] mapped at [ffff8800000f63c0]
[    0.000000] Early table checksum verification disabled
....
[  110.721000] Code: 00 00 49 ff cc 74 0c bf 58 89 41 00 e8 45 29 c9 ff eb ef 48 83 c3 64 eb b1 83 3d 16 7f 6e 00 00 74 05 e8 ff 24 a0 ff fb 66 66 90 <66> 66 
[  110.721000] RIP  [<ffffffff8169dd35>] panic+0x1c9/0x20d
[  110.721000]  RSP <ffff880007c039d8>
[  110.721000] ---[ end trace a30981859e8f046b ]---
[  110.721000] Kernel panic - not syncing: Fatal exception in interrupt
```

しかし、kernel panicになっているのでまだうまくいっていない。

### gdbでのカーネル起動の開始を制御する

まず1つのターミナル上から先ほどのコマンドに加えて「-gdb tcp::10000 -S」を付与します。
-Sを指定すると、gdbでcコマンドを入力するまでCPU起動直後に停止します。
```
$ qemu-system-x86_64 --kernel /boot/vmlinuz-3.10.0-693.el7.x86_64  -gdb tcp::10000 -S -nographic -append "console=ttyS0"
```

引き続き、同一ホスト上で別のターミナルから次のように接続することで、上記のターミナルの起動処理が開始されるようになります。
```
$ gdb -p `pidof qemu-system-x86_64`
(gdb) target remote localhost:10000
(gdb) b start_kernel
(gdb) c
```

cを入力すると処理が開始されるようになります。


# 参考URL
- QEMU上のLinuxカーネルをGDBでデバッグする
  - https://www.hiroom2.com/2014/01/15/qemu%E4%B8%8A%E3%81%AElinux%E3%82%AB%E3%83%BC%E3%83%8D%E3%83%AB%E3%82%92gdb%E3%81%A7%E3%83%87%E3%83%90%E3%83%83%E3%82%B0%E3%81%99%E3%82%8B/

