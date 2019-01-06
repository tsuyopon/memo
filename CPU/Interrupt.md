# 割り込みとは
割り込みコントローラは次のような全体像となっている(PIC, APIC, xAPICなど種類があるが、以下ではAPICとして記載している)
以下の図でLocal APICとIO APICの場所については押さえておくと良い。
```
     +------------------+                +------------------+
     |                  |                |                  |
     | プロセッサ・コア |                | プロセッサ・コア |
     |                  |                |                  |
     +------------------+                +------------------+
     | Local APIC       |                | Local APIC       |
     +------------------+                +------------------+
       ^              ^                    ^              ^  
       |              |                    |              |  
   IPI |              | 割り込み       IPI |              | 割り込み
       |              | メッセージ         |              | メッセージ
       v              v                    v              v     
    ---------------------------------------------------------
                         システムバス                       
    ---------------------------------------------------------
                              ^                             
    +------------------------ | ----------------------------+
    |                         v                             |
    |         +--------------------------------+            |
    |         |          PCI ブリッジ          |            |
    |         +--------------------------------+            |
    |                         ^                             |
    |                         |                             |
    |                         v                             |
    |    -----------------------------------------------    |
    |                        PCI バス                       |
    |    -----------------------------------------------    |
    |                         ^                             |
    |                         |                             |
    |                         v                             |
    |         +--------------------------------+            |
    |         |                                |            |
    |         |            IO APIC             |            |
    |         |                                |            |
    |         +--------------------------------+            |
    |           ^             ^              ^              |
    |           |             |              |              |
    +-------------------------------------------------------+
                |             |              |
            外部割込み    外部割込み      外部割込み
```

- 参考: http://d.hatena.ne.jp/think_carefully/20090811

# CPUへの割り込み処理について
プロセッサには次の２つの割り込みを受信するピンが実装されています
- INTRピン
  - プロセッサの「FLAGS」レジスタの「IF」フラグを操作することでマスクできます。
- NMIピン
  - NMI(Non Maskable Interrupt)ピンを通す割り込みは、マスクできない割り込みとなる。FLAGSの「IF」フラグを操作しても割り込みは報告されます。
  - デバッグやハードウェアエラーなどの報告で利用される特殊な割り込みです。

余談ですが、プログラムからINTRを制御するためのIFフラグをクリア/セットするには、CLI 命令/STI 命令を使用します。

INTRやNMIの回数については次のように/proc/interruptsで確認することができます。
```
$ cat /proc/interrupts  
           CPU0       
  0:        156   IO-APIC-edge      timer
  1:          9   IO-APIC-edge      i8042
  8:          0   IO-APIC-edge      rtc0
  9:          0   IO-APIC-fasteoi   acpi
 12:        133   IO-APIC-edge      i8042
 14:          0   IO-APIC-edge      ata_piix
 15:      23910   IO-APIC-edge      ata_piix
 19:      44481   IO-APIC-fasteoi   p2p1
 21:      48142   IO-APIC-fasteoi   ahci, snd_intel8x0
 22:         64   IO-APIC-fasteoi   ohci_hcd:usb1
NMI:          0   Non-maskable interrupts
LOC:     501563   Local timer interrupts
SPU:          0   Spurious interrupts
PMI:          0   Performance monitoring interrupts
IWI:          0   IRQ work interrupts
RTR:          0   APIC ICR read retries
RES:          0   Rescheduling interrupts
CAL:          0   Function call interrupts
TLB:          0   TLB shootdowns
TRM:          0   Thermal event interrupts
THR:          0   Threshold APIC interrupts
MCE:          0   Machine check exceptions
MCP:         82   Machine check polls
ERR:          0
MIS:          0
```

# 割り込みコントローラ
割り込みコントローラには次のようにいくつか種類があります。
- 8259 PIC
  - レガシーな割込みコントローラ
- APIC(Advanced Programmable Interrupt Controller)
  - 8259PICにとって変わるPICである。最近のx86ではこれが主流となっている。
  - PICと比較して、マルチプロセッサ対応(SMP)、プライオリティ制御などの機能が追加されている。
- xAPIC / x2APIC
  - 最新版

# APICについて
APICについては以下のIntelの資料「Chapter10: ADVANCED PROGRAMMABLE INTERRUPT CONTROLLER(APIC)」にLocal APIC, IOAPICや詳細が記載されています。
- https://www.intel.com/content/dam/www/public/us/en/documents/manuals/64-ia-32-architectures-software-developer-vol-3a-part-1-manual.pdf

割り込みコントローラとして紹介したAPICでは次の２つは分けて理解しておく必要があります。
SMPシステムにおいて周辺装置からの割り込みをI/O APICが受け付けた後にCPUのLocal APICへ転送します。

- Local APIC
  - CPU内部に実装され、外部からの割り込み全てを管理する
- I/O APIC(IOAPIC)
  - I/Oデバイスから受け取った割り込みは処理は全て一旦IOAPICを経由する。IOAPICはOSやBIOSによって設定されたリダイレクション・テーブルを参照してそれに従ってCPUへの割り込み処理を行う。　

# ローカルAPIC詳細
- http://d.hatena.ne.jp/think_carefully/20090811/1249975469

TODO: レジスタ周りについてはまたこんど時間がある際に

# 参考URL
- VA LINUX技術文章: 
  - Linux / x86_64の割り込み処理 第1回 割り込みコントローラ
  - https://www.valinux.co.jp/technologylibrary/document/linux/interrupts0001/
- パソコンのレガシィI/O活用大全
  - http://www.cqpub.co.jp/column/books/2001a/34331PC_Legacy/default.htm
- wikipedia: Intel_8259
  - https://ja.wikipedia.org/wiki/Intel_8259
- wikipedia: APIC
  - https://ja.wikipedia.org/wiki/APIC

# 公式資料
- APIC仕様書
  - http://www.acpi.info/spec.htm
- 8259A 仕様書
  - https://pdos.csail.mit.edu/6.828/2005/readings/hardware/8259A.pdf
- Intel64 Architecture x2APIC Specification
  - https://www.naic.edu/~phil/software/intel/318148.pdf
- Intel64 and IA-32 Architectures Software Developer’s Manual
  - https://www.intel.com/content/dam/www/public/us/en/documents/manuals/64-ia-32-architectures-software-developer-vol-3a-part-1-manual.pdf

# TODO
- 設定方法も記載する
- エッジトリガー、レベルトリガー
