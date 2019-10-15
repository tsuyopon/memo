# 概要
PCI関連の情報を取得するためのコマンドについて
pciutilsパッケージをインストールすることでlspciのPCI情報を出力するコマンドを得ることができます。

# 詳細

### ベンダーIDを確認する
PCIコンフィグレーション空間に含まれるベンダーIDはOS中にデータファイルが存在するので、確認することができます。
```
$ cat /usr/share/hwdata/pci.ids  | grep "Intel Corporation" -A 10 -B 10
7470  TP-LINK Technologies Co., Ltd.
7604  O.N. Electronic Co Ltd.
7bde  MIDAC Corporation
7fed  PowerTV
8008  Quancom Electronic GmbH
	0010  WDOG1 [PCI-Watchdog 1]
	0011  PWDOG2 [PCI-Watchdog 2]
	0015  Clock77/PCI & Clock77/PCIe (DCF-77 receiver)
# Wrong ID used in subsystem ID of AsusTek PCI-USB2 PCI card.
807d  Asustek Computer, Inc.
8086  Intel Corporation
	0007  82379AB
	0008  Extended Express System Support Controller
	0039  21145 Fast Ethernet
	0040  Core Processor DRAM Controller
	0041  Core Processor PCI Express x16 Root Port
	0042  Core Processor Integrated Graphics Controller
	0043  Core Processor Secondary PCI Express Root Port
	0044  Core Processor DRAM Controller
		1025 0347  Aspire 7740G
		1025 0487  TravelMate 5742
```

### 現在のPCIデバイスを出力する
```
$ lspci 
00:00.0 Host bridge: Intel Corporation 440FX - 82441FX PMC [Natoma] (rev 02)
00:01.0 ISA bridge: Intel Corporation 82371SB PIIX3 ISA [Natoma/Triton II]
00:01.1 IDE interface: Intel Corporation 82371AB/EB/MB PIIX4 IDE (rev 01)
00:02.0 VGA compatible controller: VMware SVGA II Adapter
00:03.0 Ethernet controller: Intel Corporation 82540EM Gigabit Ethernet Controller (rev 02)
00:04.0 System peripheral: InnoTek Systemberatung GmbH VirtualBox Guest Service
00:05.0 Multimedia audio controller: Intel Corporation 82801AA AC'97 Audio Controller (rev 01)
00:06.0 USB controller: Apple Inc. KeyLargo/Intrepid USB
00:07.0 Bridge: Intel Corporation 82371AB/EB/MB PIIX4 ACPI (rev 08)
00:0d.0 SATA controller: Intel Corporation 82801HM/HEM (ICH8M/ICH8M-E) SATA Controller [AHCI mode] (rev 02)
```

構成としてはprocと同じはず
```
$ tree /proc/bus/pci/
/proc/bus/pci/
|-- 00
|   |-- 00.0
|   |-- 01.0
|   |-- 01.1
|   |-- 02.0
|   |-- 03.0
|   |-- 04.0
|   |-- 05.0
|   |-- 06.0
|   |-- 07.0
|   `-- 0d.0
`-- devices

1 directory, 11 files
```

hexdumpでPCIコンフィグレーション空間を確認できます。これは後で説明するlspciのxオプションでも同様のことを確認できます。
```
$ hexdump -C -n 64 /proc/bus/pci/00/07.0 
00000000  86 80 13 71 01 00 80 02  08 00 80 06 00 00 80 00  |...q............|
00000010  00 00 00 00 00 00 00 00  00 00 00 00 00 00 00 00  |................|
*
00000030  00 00 00 00 00 00 00 00  00 00 00 00 09 01 00 00  |................|
00000040
```

### PICコンフィグレーション空間を出力する

```
$ lspci -x
00:00.0 Host bridge: Intel Corporation 440FX - 82441FX PMC [Natoma] (rev 02)
00: 86 80 37 12 00 00 00 00 02 00 00 06 00 00 00 00
10: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
20: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
30: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00

(snip)

00:07.0 Bridge: Intel Corporation 82371AB/EB/MB PIIX4 ACPI (rev 08)
00: 86 80 13 71 01 00 80 02 08 00 80 06 00 00 80 00
10: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
20: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
30: 00 00 00 00 00 00 00 00 00 00 00 00 09 01 00 00

00:0d.0 SATA controller: Intel Corporation 82801HM/HEM (ICH8M/ICH8M-E) SATA Controller [AHCI mode] (rev 02)
00: 86 80 29 28 07 00 10 00 02 01 06 01 00 40 00 00
10: 41 d2 00 00 49 d2 00 00 51 d2 00 00 59 d2 00 00
20: 61 d2 00 00 00 60 80 f1 00 00 00 00 00 00 00 00
30: 00 00 00 00 70 00 00 00 00 00 00 00 0b 01 00 00
```



### デバイスの詳細を表示する
```
$ lspci -v -s 00:03.0
00:03.0 Ethernet controller: Intel Corporation 82540EM Gigabit Ethernet Controller (rev 02)
	Subsystem: Intel Corporation PRO/1000 MT Desktop Adapter
	Flags: bus master, 66MHz, medium devsel, latency 64, IRQ 19
	Memory at f1200000 (32-bit, non-prefetchable) [size=128K]
	I/O ports at d020 [size=8]
	Capabilities: <access denied>
	Kernel driver in use: e1000
	Kernel modules: e1000
```

### デバイスのモジュールを合わせて表示する
```
$ lspci -k
00:00.0 Host bridge: Intel Corporation 440FX - 82441FX PMC [Natoma] (rev 02)
00:01.0 ISA bridge: Intel Corporation 82371SB PIIX3 ISA [Natoma/Triton II]
00:01.1 IDE interface: Intel Corporation 82371AB/EB/MB PIIX4 IDE (rev 01)
	Kernel driver in use: ata_piix
	Kernel modules: ata_piix, pata_acpi, ata_generic
00:02.0 VGA compatible controller: VMware SVGA II Adapter
	Subsystem: VMware SVGA II Adapter
	Kernel driver in use: vmwgfx
	Kernel modules: vmwgfx
00:03.0 Ethernet controller: Intel Corporation 82540EM Gigabit Ethernet Controller (rev 02)
	Subsystem: Intel Corporation PRO/1000 MT Desktop Adapter
	Kernel driver in use: e1000
	Kernel modules: e1000
00:04.0 System peripheral: InnoTek Systemberatung GmbH VirtualBox Guest Service
00:05.0 Multimedia audio controller: Intel Corporation 82801AA AC'97 Audio Controller (rev 01)
	Subsystem: Dell Device 0177
	Kernel driver in use: snd_intel8x0
	Kernel modules: snd_intel8x0
00:06.0 USB controller: Apple Inc. KeyLargo/Intrepid USB
	Kernel driver in use: ohci-pci
00:07.0 Bridge: Intel Corporation 82371AB/EB/MB PIIX4 ACPI (rev 08)
	Kernel driver in use: piix4_smbus
	Kernel modules: i2c_piix4
00:0d.0 SATA controller: Intel Corporation 82801HM/HEM (ICH8M/ICH8M-E) SATA Controller [AHCI mode] (rev 02)
	Kernel driver in use: ahci
	Kernel modules: ahci
```



### I/Oポートの割り当て表を確認する
```
$ cat /proc/ioports | head -10
0000-0cf7 : PCI Bus 0000:00
  0000-001f : dma1
  0020-0021 : pic1
  0040-0043 : timer0
  0050-0053 : timer1
  0060-0060 : keyboard
  0064-0064 : keyboard
  0070-0071 : rtc_cmos
    0070-0071 : rtc0
  0080-008f : dma page reg
```


### メモリポートの割り当て表を確認する

```
$ cat /proc/iomem 
00000000-00000fff : reserved
00001000-0009fbff : System RAM
0009fc00-0009ffff : reserved
000a0000-000bffff : PCI Bus 0000:00
000c0000-000c7fff : Video ROM
000e2000-000ef3ff : Adapter ROM
000f0000-000fffff : reserved
  000f0000-000fffff : System ROM
00100000-dffeffff : System RAM
  2b000000-350fffff : Crash kernel
  68000000-6877c25e : Kernel code
  6877c25f-68d661ff : Kernel data
  68f45000-69250fff : Kernel bss
dfff0000-dfffffff : ACPI Tables
e0000000-fdffffff : PCI Bus 0000:00
  f0000000-f0ffffff : 0000:00:02.0
    f0000000-f0ffffff : vmwgfx probe
  f1000000-f11fffff : 0000:00:02.0
    f1000000-f11fffff : vmwgfx probe
  f1200000-f121ffff : 0000:00:03.0
    f1200000-f121ffff : e1000
  f1400000-f17fffff : 0000:00:04.0
  f1800000-f1803fff : 0000:00:04.0
  f1804000-f1804fff : 0000:00:06.0
    f1804000-f1804fff : ohci_hcd
  f1806000-f1807fff : 0000:00:0d.0
    f1806000-f1807fff : ahci
fec00000-fec00fff : reserved
  fec00000-fec003ff : IOAPIC 0
fee00000-fee00fff : Local APIC
  fee00000-fee00fff : reserved
fffc0000-ffffffff : reserved
100000000-11fffffff : System RAM
```


