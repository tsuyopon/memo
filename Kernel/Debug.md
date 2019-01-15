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
$ qemu-system-x86_64 --kernel ./vmlinuz-3.10.0-693.el7.x86_64 -initrd initramfs-3.10.0-693.el7.x86_64.img -nographic -append "console=ttyS0"
```

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


# トラブルシューティング

### qemu: could not load PC BIOS 'bios-256k.bin'のエラーが出る
qemu-system-x86_64を実行したときに上記のエラーメッセージが出力された。
以下をインストールすることで問題は解消した。

```
$ yum install seabios
```

- 参考
  - Cannot Start KVM VM Because Missing BIOS
  - https://unix.stackexchange.com/questions/134893/cannot-start-kvm-vm-because-missing-bios/413725

# 参考URL
- QEMU上のLinuxカーネルをGDBでデバッグする
  - https://www.hiroom2.com/2014/01/15/qemu%E4%B8%8A%E3%81%AElinux%E3%82%AB%E3%83%BC%E3%83%8D%E3%83%AB%E3%82%92gdb%E3%81%A7%E3%83%87%E3%83%90%E3%83%83%E3%82%B0%E3%81%99%E3%82%8B/
- StackOverflow: How to debug the Linux kernel with GDB and QEMU?
  - https://stackoverflow.com/questions/11408041/how-to-debug-the-linux-kernel-with-gdb-and-qemu

