# 概要
ディスク関連に関するコマンドについて

# 詳細


### ディスクやパーティションの情報を調べる
```
$ sudo fdisk -l

Disk /dev/sda: 15.2 GB, 15156117504 bytes, 29601792 sectors
Units = sectors of 1 * 512 = 512 bytes
Sector size (logical/physical): 512 bytes / 512 bytes
I/O サイズ (最小 / 推奨): 512 バイト / 512 バイト
Disk label type: dos
ディスク識別子: 0x000d9614

デバイス ブート      始点        終点     ブロック   Id  システム
/dev/sda1   *        2048     2099199     1048576   83  Linux
/dev/sda2         2099200    29601791    13751296   8e  Linux LVM

Disk /dev/mapper/centos-root: 12.6 GB, 12561940480 bytes, 24535040 sectors
Units = sectors of 1 * 512 = 512 bytes
Sector size (logical/physical): 512 bytes / 512 bytes
I/O サイズ (最小 / 推奨): 512 バイト / 512 バイト


Disk /dev/mapper/centos-swap: 1518 MB, 1518338048 bytes, 2965504 sectors
Units = sectors of 1 * 512 = 512 bytes
Sector size (logical/physical): 512 bytes / 512 bytes
I/O サイズ (最小 / 推奨): 512 バイト / 512 バイト
```

### ファイルシステムを識別する
fileコマンドにsオプションを付与するとデバイスのファイルシステムを確認することができます。
```
$ sudo file /dev/sda1 
/dev/sda1: block special
$ sudo file -s /dev/sda1 
/dev/sda1: SGI XFS filesystem data (blksz 4096, inosz 512, v2 dirs)
```
