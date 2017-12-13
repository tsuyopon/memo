# 概要
CPU周りに関するtipsについて
procファイルシステムに関してはproc/cpu.mdあたりの資料も参考にしてください。

# 詳細
### CPU情報を表示します
```
$ lscpu 
アーキテクチャ: x86_64
CPU op-mode(s):        32-bit, 64-bit
Byte Order:            Little Endian
CPU(s):                1
On-line CPU(s) list:   0
コアあたりのスレッド数:1
ソケットあたりのコア数:1
Socket(s):             1
NUMAノード:         1
ベンダーID:        GenuineIntel
CPUファミリー:    6
モデル:             58
Model name:            Intel(R) Core(TM) i5-3427U CPU @ 1.80GHz
ステッピング:    9
CPU MHz:               2294.770
BogoMIPS:              4589.54
ハイパーバイザーベンダー:KVM
仮想化タイプ:    完全仮想化
L1d キャッシュ:   32K
L1i キャッシュ:   32K
L2 キャッシュ:    256K
L3 キャッシュ:    3072K
NUMAノード 0 CPU:   0
Flags:                 fpu vme de pse tsc msr pae mce cx8 apic sep mtrr pge mca cmov pat pse36 clflush mmx fxsr sse sse2 syscall nx rdtscp lm constant_tsc rep_good nopl xtopology nonstop_tsc pni pclmulqdq monitor ssse3 cx16 sse4_1 sse4_2 x2apic popcnt aes xsave avx rdrand hypervisor lahf_lm
```

### CPUの温度や回転数などのモニタリングを行う

以下でインストールします。
```
$ yum install lm_sensors
```

以下のURLなどを参考にして初期設定をしたら
- http://www.atmarkit.co.jp/flinux/rensai/linuxtips/743hwmonitor.html

sensorsコマンドでデータを取得することができるようです。
```
$ sensors
coretemp-isa-0000
Adapter: ISA adapter
Core 0:      +47.0℃  (high = +80.0℃, crit = +100.0℃)  

coretemp-isa-0001
Adapter: ISA adapter
Core 1:      +48.0℃  (high = +80.0℃, crit = +100.0℃)  

coretemp-isa-0002
Adapter: ISA adapter
Core 2:      +48.0℃  (high = +80.0℃, crit = +100.0℃)  

coretemp-isa-0003
Adapter: ISA adapter
Core 3:      +49.0℃  (high = +80.0℃, crit = +100.0℃)  

it8720-isa-0290
Adapter: ISA adapter
in0:         +0.91 V  (min =  +0.00 V, max =  +4.08 V)   
in1:         +1.52 V  (min =  +0.00 V, max =  +4.08 V)   
in2:         +3.31 V  (min =  +0.00 V, max =  +4.08 V)   
+5V:         +2.99 V  (min =  +0.00 V, max =  +4.08 V)   
in4:         +0.35 V  (min =  +0.00 V, max =  +4.08 V)   
in5:         +3.18 V  (min =  +0.00 V, max =  +4.08 V)   
in6:         +0.40 V  (min =  +0.00 V, max =  +4.08 V)   
5VSB:        +3.06 V  (min =  +0.00 V, max =  +4.08 V)   
Vbat:        +3.25 V
fan1:       1360 RPM  (min =   10 RPM)
fan2:       1278 RPM  (min =    0 RPM)
fan3:       1061 RPM  (min =    0 RPM)
fan4:          0 RPM  (min =    0 RPM)
temp1:       +40.0℃  (low  = +127.0℃, high = +127.0℃)  sensor = thermistor
temp2:       +43.0℃  (low  = +127.0℃, high = +70.0℃)  sensor = thermal diode
temp3:       +50.0℃  (low  = +127.0℃, high = +127.0℃)  sensor = thermistor
```
