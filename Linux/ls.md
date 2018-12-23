# 概要
lsに関連するコマンドについて

# 詳細

### Linuxファイルシステムでロックされているファイル情報を表示する

```
$ lslocks 
COMMAND           PID  TYPE SIZE MODE  M START END PATH
lvmetad           487 POSIX   0B WRITE 0     0   0 /run
(unknown)         752 FLOCK   0B WRITE 0     0   0 /run
abrtd             753 POSIX   0B WRITE 0     0   0 /run
crond            1196 FLOCK   0B WRITE 0     0   0 /run
libvirtd         1190 POSIX   0B WRITE 0     0   0 /run
master           1642 FLOCK   0B WRITE 0     0   0 /
master           1642 FLOCK   0B WRITE 0     0   0 /
mysqld           1659 POSIX   0B WRITE 0     0   0 /
mysqld           1659 POSIX   0B WRITE 0     0   0 /
mysqld           1659 POSIX   0B WRITE 0     0   0 /
mysqld           1659 POSIX   0B WRITE 0     0   0 /
mysqld           1659 POSIX   0B WRITE 0     0   0 /
mysqld           1659 POSIX   0B WRITE 0     0   0 /
mysqld           1659 POSIX   0B WRITE 0     0   0 /
mysqld           1659 POSIX   0B WRITE 0     0   0 /
mysqld           1659 POSIX   0B WRITE 0     0   0 /
```


### lspci

この辺がすごい役に立つ
- https://eng-entrance.com/linux-command-lspci

```
$ lspci 
00:00.0 Host bridge: Intel Corporation 440FX - 82441FX PMC [Natoma] (rev 02)
00:01.0 ISA bridge: Intel Corporation 82371SB PIIX3 ISA [Natoma/Triton II]
00:01.1 IDE interface: Intel Corporation 82371AB/EB/MB PIIX4 IDE (rev 01)
00:02.0 VGA compatible controller: InnoTek Systemberatung GmbH VirtualBox Graphics Adapter
00:03.0 Ethernet controller: Intel Corporation 82540EM Gigabit Ethernet Controller (rev 02)
00:04.0 System peripheral: InnoTek Systemberatung GmbH VirtualBox Guest Service
00:05.0 Multimedia audio controller: Intel Corporation 82801AA AC'97 Audio Controller (rev 01)
00:06.0 USB controller: Apple Inc. KeyLargo/Intrepid USB
00:07.0 Bridge: Intel Corporation 82371AB/EB/MB PIIX4 ACPI (rev 08)
00:0d.0 SATA controller: Intel Corporation 82801HM/HEM (ICH8M/ICH8M-E) SATA Controller [AHCI mode] (rev 02)
```


PCIデバイスの全詳細情報を出力する(v, vv, vvvオプションがあります)
```
$ lspci -vvv
00:00.0 Host bridge: Intel Corporation 440FX - 82441FX PMC [Natoma] (rev 02)
	Control: I/O- Mem- BusMaster- SpecCycle- MemWINV- VGASnoop- ParErr- Stepping- SERR- FastB2B- DisINTx-
	Status: Cap- 66MHz- UDF- FastB2B- ParErr- DEVSEL=fast >TAbort- <TAbort- <MAbort- >SERR- <PERR- INTx-

00:01.0 ISA bridge: Intel Corporation 82371SB PIIX3 ISA [Natoma/Triton II]
	Control: I/O+ Mem+ BusMaster+ SpecCycle- MemWINV- VGASnoop- ParErr- Stepping- SERR- FastB2B- DisINTx-
	Status: Cap- 66MHz- UDF- FastB2B- ParErr- DEVSEL=medium >TAbort- <TAbort- <MAbort- >SERR- <PERR- INTx-
	Latency: 0

00:01.1 IDE interface: Intel Corporation 82371AB/EB/MB PIIX4 IDE (rev 01) (prog-if 8a [Master SecP PriP])
	Control: I/O+ Mem+ BusMaster+ SpecCycle- MemWINV- VGASnoop- ParErr- Stepping- SERR- FastB2B- DisINTx-
	Status: Cap- 66MHz- UDF- FastB2B- ParErr- DEVSEL=fast >TAbort- <TAbort- <MAbort- >SERR- <PERR- INTx-
	Latency: 64
	Region 0: [virtual] Memory at 000001f0 (32-bit, non-prefetchable) [size=8]
	Region 1: [virtual] Memory at 000003f0 (type 3, non-prefetchable)
	Region 2: [virtual] Memory at 00000170 (32-bit, non-prefetchable) [size=8]
	Region 3: [virtual] Memory at 00000370 (type 3, non-prefetchable)
	Region 4: I/O ports at d000 [size=16]
	Kernel driver in use: ata_piix
	Kernel modules: ata_piix, pata_acpi, ata_generic

00:02.0 VGA compatible controller: InnoTek Systemberatung GmbH VirtualBox Graphics Adapter (prog-if 00 [VGA controller])
	Control: I/O+ Mem+ BusMaster+ SpecCycle- MemWINV- VGASnoop- ParErr- Stepping- SERR- FastB2B- DisINTx-
	Status: Cap- 66MHz- UDF- FastB2B- ParErr- DEVSEL=fast >TAbort- <TAbort- <MAbort- >SERR- <PERR- INTx-
	Latency: 0
	Interrupt: pin A routed to IRQ 11
	Region 0: Memory at e0000000 (32-bit, prefetchable) [size=16M]
	Expansion ROM at <unassigned> [disabled]

00:03.0 Ethernet controller: Intel Corporation 82540EM Gigabit Ethernet Controller (rev 02)
	Subsystem: Intel Corporation PRO/1000 MT Desktop Adapter
	Control: I/O+ Mem+ BusMaster+ SpecCycle- MemWINV- VGASnoop- ParErr- Stepping- SERR- FastB2B- DisINTx-
	Status: Cap+ 66MHz+ UDF- FastB2B- ParErr- DEVSEL=medium >TAbort- <TAbort- <MAbort- >SERR- <PERR- INTx-
	Latency: 64 (63750ns min)
	Interrupt: pin A routed to IRQ 19
	Region 0: Memory at f0000000 (32-bit, non-prefetchable) [size=128K]
	Region 2: I/O ports at d010 [size=8]
	Capabilities: <access denied>
	Kernel driver in use: e1000
	Kernel modules: e1000
...
```

PCI Configuration Spaceに関する情報を出力する
```
$ lspci -xxx
00:00.0 Host bridge: Intel Corporation 440FX - 82441FX PMC [Natoma] (rev 02)
00: 86 80 37 12 00 00 00 00 02 00 00 06 00 00 00 00
10: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
20: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
30: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00

00:01.0 ISA bridge: Intel Corporation 82371SB PIIX3 ISA [Natoma/Triton II]
00: 86 80 00 70 07 00 00 02 00 00 01 06 00 00 80 00
10: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
20: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
30: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
...
```

###
```
$ lsblk 
NAME            MAJ:MIN RM  SIZE RO TYPE MOUNTPOINT
sda               8:0    0 14.1G  0 disk 
├─sda1            8:1    0    1G  0 part /boot
└─sda2            8:2    0 13.1G  0 part 
  ├─centos-root 253:0    0 11.7G  0 lvm  /
  └─centos-swap 253:1    0  1.4G  0 lvm  [SWAP]
sr0              11:0    1 1024M  0 rom  
```

### scsiデバイスに関する情報を表示する。
```
$ lsscsi 
[1:0:0:0]    cd/dvd  VBOX     CD-ROM           1.0   /dev/sr0 
[2:0:0:0]    disk    ATA      VBOX HARDDISK    1.0   /dev/sda 
```

```
$ lsscsi -l
[1:0:0:0]    cd/dvd  VBOX     CD-ROM           1.0   /dev/sr0 
  state=running queue_depth=1 scsi_level=6 type=5 device_blocked=0 timeout=30
[2:0:0:0]    disk    ATA      VBOX HARDDISK    1.0   /dev/sda 
  state=running queue_depth=31 scsi_level=6 type=0 device_blocked=0 timeout=30
```

```
$ lsscsi -c
Attached devices: 
Host: scsi1 Channel: 00 Target: 00 Lun: 00
  Vendor: VBOX     Model: CD-ROM           Rev: 1.0 
  Type:   CD-ROM                           ANSI SCSI revision: 05
Host: scsi2 Channel: 00 Target: 00 Lun: 00
  Vendor: ATA      Model: VBOX HARDDISK    Rev: 1.0 
  Type:   Direct-Access                    ANSI SCSI revision: 05
```

```
$ lsscsi -g
[1:0:0:0]    cd/dvd  VBOX     CD-ROM           1.0   /dev/sr0   /dev/sg0 
[2:0:0:0]    disk    ATA      VBOX HARDDISK    1.0   /dev/sda   /dev/sg1 
```

```
$ lsscsi -d
[1:0:0:0]    cd/dvd  VBOX     CD-ROM           1.0   /dev/sr0 [11:0]
[2:0:0:0]    disk    ATA      VBOX HARDDISK    1.0   /dev/sda [8:0]
```

### lshw
```
$ lshw -numeric
WARNING: you should run this program as super-user.
localhost.localdomain       
    description: Computer
    width: 64 bits
    capabilities: vsyscall32
  *-core
       description: Motherboard
       physical id: 0
     *-memory
          description: System memory
          physical id: 0
          size: 1GiB
     *-cpu
          product: Intel(R) Core(TM) i5-3427U CPU @ 1.80GHz
          vendor: Intel Corp.
          vendor_id: GenuineIntel
          physical id: 1
          bus info: cpu@0
          width: 64 bits
          capabilities: fpu fpu_exception wp vme de pse tsc msr pae mce cx8 apic sep mtrr pge mca cmov pat pse36 clflush mmx fxsr sse sse2 syscall nx rdtscp x86-64 constant_tsc rep_good nopl xtopology nonstop_tsc pni pclmulqdq monitor ssse3 cx16 sse4_1 sse4_2 x2apic popcnt aes xsave avx rdrand hypervisor lahf_lm
     *-pci
          description: Host bridge
          product: 440FX - 82441FX PMC [Natoma] [8086:1237]
          vendor: Intel Corporation [8086]
          physical id: 100
          bus info: pci@0000:00:00.0
          version: 02
          width: 32 bits
          clock: 33MHz
        *-isa
             description: ISA bridge
             product: 82371SB PIIX3 ISA [Natoma/Triton II] [8086:7000]
             vendor: Intel Corporation [8086]
             physical id: 1
             bus info: pci@0000:00:01.0
             version: 00
             width: 32 bits
             clock: 33MHz
             capabilities: isa bus_master
             configuration: latency=0
        *-ide
             description: IDE interface
             product: 82371AB/EB/MB PIIX4 IDE [8086:7111]
             vendor: Intel Corporation [8086]
             physical id: 1.1
             bus info: pci@0000:00:01.1
             version: 01
             width: 32 bits
             clock: 33MHz
             capabilities: ide bus_master
             configuration: driver=ata_piix latency=64
             resources: irq:0 ioport:1f0(size=8) ioport:3f6 ioport:170(size=8) ioport:376 ioport:d000(size=16)
        *-display UNCLAIMED
             description: VGA compatible controller
             product: VirtualBox Graphics Adapter [80EE:BEEF]
             vendor: InnoTek Systemberatung GmbH [80EE]
             physical id: 2
             bus info: pci@0000:00:02.0
             version: 00
             width: 32 bits
             clock: 33MHz
             capabilities: vga_controller bus_master
             configuration: latency=0
             resources: memory:e0000000-e0ffffff
        *-network
             description: Ethernet interface
             product: 82540EM Gigabit Ethernet Controller [8086:100E]
             vendor: Intel Corporation [8086]
             physical id: 3
             bus info: pci@0000:00:03.0
             logical name: enp0s3
             version: 02
             serial: 08:00:27:af:c9:96
             size: 1Gbit/s
             capacity: 1Gbit/s
             width: 32 bits
             clock: 66MHz
             capabilities: bus_master cap_list ethernet physical tp 10bt 10bt-fd 100bt 100bt-fd 1000bt-fd autonegotiation
             configuration: autonegotiation=on broadcast=yes driver=e1000 driverversion=7.3.21-k8-NAPI duplex=full ip=10.0.2.15 latency=64 link=yes mingnt=255 multicast=yes port=twisted pair speed=1Gbit/s
             resources: irq:19 memory:f0000000-f001ffff ioport:d010(size=8)
        *-generic UNCLAIMED
             description: System peripheral
             product: VirtualBox Guest Service [80EE:CAFE]
             vendor: InnoTek Systemberatung GmbH [80EE]
             physical id: 4
             bus info: pci@0000:00:04.0
             version: 00
             width: 32 bits
             clock: 33MHz
             capabilities: bus_master
             configuration: latency=0
             resources: ioport:d020(size=32) memory:f0400000-f07fffff memory:f0800000-f0803fff
        *-multimedia
             description: Multimedia audio controller
             product: 82801AA AC'97 Audio Controller [8086:2415]
             vendor: Intel Corporation [8086]
             physical id: 5
             bus info: pci@0000:00:05.0
             version: 01
             width: 32 bits
             clock: 33MHz
             capabilities: bus_master
             configuration: driver=snd_intel8x0 latency=64
             resources: irq:21 ioport:d100(size=256) ioport:d200(size=64)
        *-usb
             description: USB controller
             product: KeyLargo/Intrepid USB [106B:3F]
             vendor: Apple Inc. [106B]
             physical id: 6
             bus info: pci@0000:00:06.0
             version: 00
             width: 32 bits
             clock: 33MHz
             capabilities: ohci bus_master cap_list
             configuration: driver=ohci-pci latency=64
             resources: irq:22 memory:f0804000-f0804fff
        *-bridge
             description: Bridge
             product: 82371AB/EB/MB PIIX4 ACPI [8086:7113]
             vendor: Intel Corporation [8086]
             physical id: 7
             bus info: pci@0000:00:07.0
             version: 08
             width: 32 bits
             clock: 33MHz
             capabilities: bridge bus_master
             configuration: driver=piix4_smbus latency=0
             resources: irq:9
        *-sata
             description: SATA controller
             product: 82801HM/HEM (ICH8M/ICH8M-E) SATA Controller [AHCI mode] [8086:2829]
             vendor: Intel Corporation [8086]
             physical id: d
             bus info: pci@0000:00:0d.0
             version: 02
             width: 32 bits
             clock: 33MHz
             capabilities: sata ahci_1.0 bus_master cap_list
             configuration: driver=ahci latency=64
             resources: irq:21 ioport:d240(size=8) ioport:d250(size=8) ioport:d260(size=16) memory:f0806000-f0807fff
     *-pnp00:00
          product: PnP device PNP0303
          physical id: 2
          capabilities: pnp
          configuration: driver=i8042 kbd
     *-pnp00:01
          product: PnP device PNP0f03
          physical id: 3
          capabilities: pnp
          configuration: driver=i8042 aux
  *-network:0 DISABLED
       description: Ethernet interface
       physical id: 1
       logical name: virbr0-nic
       serial: 52:54:00:59:fc:8f
       size: 10Mbit/s
       capabilities: ethernet physical
       configuration: autonegotiation=off broadcast=yes driver=tun driverversion=1.6 duplex=full link=no multicast=yes port=twisted pair speed=10Mbit/s
  *-network:1
       description: Ethernet interface
       physical id: 2
       logical name: virbr0
       serial: 52:54:00:59:fc:8f
       capabilities: ethernet physical
       configuration: broadcast=yes driver=bridge driverversion=2.3 firmware=N/A ip=192.168.122.1 link=no multicast=yes
WARNING: output may be incomplete or inaccurate, you should run this program as super-user.
```

### lsinitrd

```
$ sudo lsinitrd 
Image: /boot/initramfs-3.10.0-693.el7.x86_64.img: 20M
========================================================================
Early CPIO image
========================================================================
drwxr-xr-x   3 root     root            0 Nov 23  2017 .
-rw-r--r--   1 root     root            2 Nov 23  2017 early_cpio
drwxr-xr-x   3 root     root            0 Nov 23  2017 kernel
drwxr-xr-x   3 root     root            0 Nov 23  2017 kernel/x86
drwxr-xr-x   2 root     root            0 Nov 23  2017 kernel/x86/microcode
-rw-r--r--   1 root     root        12288 Nov 23  2017 kernel/x86/microcode/GenuineIntel.bin
========================================================================
Version: dracut-033-502.el7

Arguments: -f

dracut modules:
bash
nss-softokn
i18n
network
ifcfg
drm
plymouth
dm
kernel-modules
lvm
qemu
resume
rootfs-block
terminfo
udev-rules
biosdevname
systemd
usrmount
base
fs-lib
shutdown
========================================================================
crw-r--r--   1 root     root       5,   1 Nov 23  2017 dev/console
crw-r--r--   1 root     root       1,  11 Nov 23  2017 dev/kmsg
crw-r--r--   1 root     root       1,   3 Nov 23  2017 dev/null
drwxr-xr-x  12 root     root            0 Nov 23  2017 .
lrwxrwxrwx   1 root     root            7 Nov 23  2017 bin -> usr/bin
drwxr-xr-x   2 root     root            0 Nov 23  2017 dev
drwxr-xr-x  12 root     root            0 Nov 23  2017 etc
drwxr-xr-x   2 root     root            0 Nov 23  2017 etc/cmdline.d
drwxr-xr-x   2 root     root            0 Nov 23  2017 etc/conf.d
-rw-r--r--   1 root     root          124 Nov 23  2017 etc/conf.d/systemd.conf
...
```
```
$ lshw -short
WARNING: you should run this program as super-user.
H/W path    Device      Class       Description
===============================================
                        system      Computer
/0                      bus         Motherboard
/0/0                    memory      1GiB System memory
/0/1                    processor   Intel(R) Core(TM) i5-3427U CPU @ 1.80GHz
/0/100                  bridge      440FX - 82441FX PMC [Natoma]
/0/100/1                bridge      82371SB PIIX3 ISA [Natoma/Triton II]
/0/100/1.1              storage     82371AB/EB/MB PIIX4 IDE
/0/100/2                display     VirtualBox Graphics Adapter
/0/100/3    enp0s3      network     82540EM Gigabit Ethernet Controller
/0/100/4                generic     VirtualBox Guest Service
/0/100/5                multimedia  82801AA AC'97 Audio Controller
/0/100/6                bus         KeyLargo/Intrepid USB
/0/100/7                bridge      82371AB/EB/MB PIIX4 ACPI
/0/100/d                storage     82801HM/HEM (ICH8M/ICH8M-E) SATA Controller [AHCI mode]
/0/2                    input       PnP device PNP0303
/0/3                    input       PnP device PNP0f03
/1          virbr0-nic  network     Ethernet interface
/2          virbr0      network     Ethernet interface
WARNING: output may be incomplete or inaccurate, you should run this program as super-user.
```

```
$ lshw -businfo
WARNING: you should run this program as super-user.
Bus info          Device      Class       Description
=====================================================
                              system      Computer
                              bus         Motherboard
                              memory      1GiB System memory
cpu@0                         processor   Intel(R) Core(TM) i5-3427U CPU @ 1.80GHz
pci@0000:00:00.0              bridge      440FX - 82441FX PMC [Natoma]
pci@0000:00:01.0              bridge      82371SB PIIX3 ISA [Natoma/Triton II]
pci@0000:00:01.1              storage     82371AB/EB/MB PIIX4 IDE
pci@0000:00:02.0              display     VirtualBox Graphics Adapter
pci@0000:00:03.0  enp0s3      network     82540EM Gigabit Ethernet Controller
pci@0000:00:04.0              generic     VirtualBox Guest Service
pci@0000:00:05.0              multimedia  82801AA AC'97 Audio Controller
pci@0000:00:06.0              bus         KeyLargo/Intrepid USB
pci@0000:00:07.0              bridge      82371AB/EB/MB PIIX4 ACPI
pci@0000:00:0d.0              storage     82801HM/HEM (ICH8M/ICH8M-E) SATA Controller [AHCI mode]
                              input       PnP device PNP0303
                              input       PnP device PNP0f03
                  virbr0-nic  network     Ethernet interface
                  virbr0      network     Ethernet interface
WARNING: output may be incomplete or inaccurate, you should run this program as super-user.
```


### lsns
```
$ lsns 
        NS TYPE  NPROCS   PID USER     COMMAND
4026531836 pid        7  1740 tsuyoshi -bash
4026531837 user       7  1740 tsuyoshi -bash
4026531838 uts        7  1740 tsuyoshi -bash
4026531839 ipc        7  1740 tsuyoshi -bash
4026531840 mnt        7  1740 tsuyoshi -bash
4026531956 net        7  1740 tsuyoshi -bash
```


### 利用可能なIPCについての情報を表示する(lsipc)
```
$ lsipc 
RESOURCE DESCRIPTION                                              LIMIT USED  USE%
MSGMNI   Number of message queues                                  1984    0 0.00%
MSGMAX   Max size of message (bytes)                               8192    -     -
MSGMNB   Default max size of queue (bytes)                        16384    -     -
SHMMNI   Shared memory segments                                    4096    0 0.00%
SHMALL   Shared memory pages                       18446744073692774399    0 0.00%
SHMMAX   Max size of shared memory segment (bytes) 18446744073692774399    -     -
SHMMIN   Min size of shared memory segment (bytes)                    1    -     -
SEMMNI   Number of semaphore identifiers                            128    0 0.00%
SEMMNS   Total number of semaphores                               32000    0 0.00%
SEMMSL   Max semaphores per semaphore set.                          250    -     -
SEMOPM   Max number of operations per semop(2)                       32    -     -
SEMVMX   Semaphore max value                                      32767    -     -
```


### wtmpやbtmpログをチェックしてシステムのログイン情報を表示する
```
$ lslogins
  UID USER            PROC PWD-LOCK PWD-DENY LAST-LOGIN GECOS
    0 root             103                   2017-Nov23 root
    1 bin                0                              bin
    2 daemon             0                              daemon
    3 adm                0                              adm
    4 lp                 0                              lp
    5 sync               0                              sync
    6 shutdown           0                              shutdown
    7 halt               0                              halt
    8 mail               0                              mail
   11 operator           0                              operator
   12 games              0                              games
   14 ftp                0                              FTP User
   27 mysql              0                              MySQL Server
   29 rpcuser            0                              RPC Service User
   32 rpc                0                              Rpcbind Daemon
   38 ntp                0                              
   48 apache             0                              Apache
   59 tss                0                              Account used by the trousers package to sandbox the tcsd daemon
   72 tcpdump            0                              
   74 sshd               0                              Privilege-separated SSH
   75 radvd              0                              radvd user
   81 dbus               0                              System message bus
   89 postfix            0                              
   99 nobody             0                              Nobody
  107 qemu               0                              qemu user
  173 abrt               0                              
  192 systemd-network    0                              systemd Network Management
  995 saslauth           0                              Saslauthd user
  996 unbound            0                              Unbound DNS resolver
  997 gluster            0                              GlusterFS daemons
  998 chrony             0                              
  999 polkitd            0                              User for polkitd
 1000 tsuyoshi           7                     14:35:15 tsuyoshi
65534 nfsnobody          0                              Anonymous NFS User
```
