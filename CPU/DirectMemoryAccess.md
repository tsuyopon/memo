ダイレクトメモリーアクセス(DMA)

多くのデバイスは、バスを一時的に制御できます。
これらのデバイスは、メインメモリーなどのデバイスを必要とするデータ転送を行うことができます。
デバイスは CPU の助けを借りずにその処理を行なっているためDMAと呼ばれます。

コンピュータでデータを転送する方法についておさらいをします。以下の３つの方法があります。
 1) pollingによるデータ転送(CPUが主にIN命令・OUT命令を発行します。)
 2) 割り込みを受けてからのデータ転送
 3) DMAによるデータ転送

DMAはもちろん3)で、特徴としては
- DMAはCPUの代わりにデバイスとメモリ間のデータ転送を行う
- DMAは直接（Direct）メモリ（Memory）にアクセスできる
- デバイスからメモリへのデータ転送ができる
- メモリからデバイスへのデータ転送ができる



- DMA詳細
-- http://softwaretechnique.jp/OS_Development/kernel_development13.html