# タイマーについて

TODO: ウェブ上からの(よく理解していない)雑なまとめなのでちゃんと整理したい

### PIT(Programmable Interval Timer)

特徴
- プロセッサに内蔵されない外部タイマー回路

### HPET(High Precision Event Timer)
日本語に直訳すると高精度イベントタイマーです。
古いオペレーティングシステムではHPETをサポートしておらず、リアルタイムクロック(RTC)といった以前からの古いタイマー設備を使用します。

特徴としては、
- プロセッサに内蔵されない外部タイマー回路で、仕様上最大256個のタイマーブロックを構成可能
- HPETはRTCに比べて高い解像度でより多くの定期的な割り込みを生成することができる
- 周期タイマだけでなくワンショットタイマ（指定時間後割込みを起こすアラーム）としての用途としても使える 


HPET仕様書
- https://www.intel.com/content/dam/www/public/us/en/documents/technical-specifications/software-developers-hpet-spec-1-0a.pdf

### TSC(Time Stamp Counter)

特徴
- プロセッサに内蔵された64ビットカウンタで、プロセッサの入力クロック単位でカウントアップする
- RDTSC命令で現在のカウント値を取得する
- カーネル起動後にはこの時間が読み込まれるらしい
- タイマーチップの電源はバッテリによって供給されるので、システムの電源が落ちていても時計の計測は行われる

### APCI PM-Timer(ACPI Power Management Timer)

特徴
- ACPIを実装しているマザーボードならば必ず搭載しているハードウェアである。
- ACPI Power management Timerのクロック周波数は規格により固定されていて3.58 MHzのクロック信号(約280ナノ秒)の精度となっている
- I/Oポートに対してカウンタ値をアクセスできる。


### Local APIC Timer
特徴
- 各プロセッサ内部APICに内蔵されるタイマーで、該当プロセッサに対して割り込みを発生する。



# Linuxにおけるタイマーの取り扱い
Linuxではタイマーを次の２種類に分類していて、カーネルに提供しています。
- (1). clocksource
  - 時間の読み取りを行ないます。
  - xtime更新時、カーネルAPIのktime_get_xxxx、gettimeofday実行時などに参照されます。
- (2). clockevents
  - 指定時刻に割り込む

### (1) clocksource
カーネルで現在利用可能なハードウェアは次の情報を確認することで取得できます。
```
$ cat /sys/devices/system/clocksource/clocksource0/available_clocksource
kvm-clock tsc acpi_pm 
```

### (2) clockevents
通常はclockeventX(XはCPU番号)の方に指定されたデバイスが利用されます。
しかし、CPUデバイスが省電力モードに入ってしまっているような場合にはbroadcast側が使われるようです。
```
$ cat /sys/devices/system/clockevents/clockevent0/current_device 
lapic
$ cat /sys/devices/system/clockevents/broadcast/current_device 
pit
```

IAサーバにおけるclockeventsのデバイスは次の通り
- lapic
  - Local APIC タイマー
- hpet
  - HPET
- pit
  - i8254 PIT

上記の値を変更したい場合には、/boot/grob/menu.lstを弄れば良いです。

### 参考資料
- https://www.valinux.co.jp/technologylibrary/document/linuxkernel/timer0004/
