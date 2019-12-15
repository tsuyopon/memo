# 概要
CPU関連の/procについて

# 詳細
### /proc/loadavg
最初の３つは1分、５分、15分のロードアベレージとなりuptimeコマンドで表示されているものと同じ。
4つめの1/248は２つの数値がスラッシュで区切られていて、1の部分は現在カーネルで稼働しているプロセスやスレッドを表す。後半の数値248というのはシステム上で現在存在するカーネルスケジューリングされるべき数を表す。
5つめのフィールドはPIDを表す。
```
$ sudo cat /proc/loadavg 
0.00 0.01 0.05 1/248 27781
```

### /proc/cpuinfo
CPUに関する情報を表示します。
```
$ cat /proc/cpuinfo 
processor	: 0
vendor_id	: GenuineIntel
cpu family	: 6
model		: 58
model name	: Intel(R) Core(TM) i5-3427U CPU @ 1.80GHz
stepping	: 9
microcode	: 0x19
cpu MHz		: 2294.507
cache size	: 3072 KB
fpu		: yes
fpu_exception	: yes
cpuid level	: 13
wp		: yes
flags		: fpu vme de pse tsc msr pae mce cx8 apic sep mtrr pge mca cmov pat pse36 clflush mmx fxsr sse sse2 syscall nx rdtscp lm constant_tsc up rep_good nopl xtopology nonstop_tsc pni pclmulqdq monitor ssse3 cx16 sse4_1 sse4_2 popcnt aes xsave avx rdrand lahf_lm
bogomips	: 4589.01
clflush size	: 64
cache_alignment	: 64
address sizes	: 36 bits physical, 48 bits virtual
power management:
```

- fpu: 浮動小数点演算ができるか
- bogomips: Linuxカーネルのブート時にCPU速度をビジーループを使って測定した値をさす。もともとはBogo(インチキの) MIPSという意味らしい。
 - 参考: https://ja.wikipedia.org/wiki/BogoMips
- address sizes: アドレス空間がどのくらいあるかの話のようで、40-48だと64bitCPUになる
 

