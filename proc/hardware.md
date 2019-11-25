
### 割り込み発生数を確認する(/proc/interrupts)
/proc/interruptsを参照することにより現在までの割り込み発生数を確認することができます。  
以下の例ではCPU0しか表示されていないが、複数のCPUが認識されていればCPU1なども表示される。

特定のCPUだけ割り込み回数が多いような場合には偏っている可能性がある。smp_affinityの設定をしてあげると良いようだ。
- http://tsuchinoko.dmmlabs.com/?p=627

一番左側はIRQ番号を表示している。CPUが複数ある場合にはCPU0, CPU1といったように複数行表示されることになります。
```
$ cat /proc/interrupts 
           CPU0       
  0:        155   IO-APIC-edge      timer
  1:         29   IO-APIC-edge      i8042
  8:          0   IO-APIC-edge      rtc0
  9:          0   IO-APIC-fasteoi   acpi
 12:        133   IO-APIC-edge      i8042
 14:          0   IO-APIC-edge      ata_piix
 15:     114966   IO-APIC-edge      ata_piix
 19:     961245   IO-APIC-fasteoi   p2p1
 21:     673030   IO-APIC-fasteoi   ahci, snd_intel8x0
 22:        780   IO-APIC-fasteoi   ohci_hcd:usb1
NMI:          0   Non-maskable interrupts
LOC:    5517233   Local timer interrupts
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
MCP:        393   Machine check polls
ERR:          0
MIS:      96135
```

**TBD** NMI,LOC,SPUなどが記述されている意味は??
**TBD** 割り込み回数はどこで測っているのか??
