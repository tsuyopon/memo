# 概要
hdparamはハードディスクのパフォーアンスを計測するソフトウェアです。

# 詳細

### ハードディスクパラメータを取得、設定する
この場合にはhdparmコマンドを利用する。 一般的にhdparmは以下のようにベンチマークとして利用される。
```
#/sbin/hdparm -Tt /dev/hda
Timing buffer-cache reads 128MB in 0.90 seconds=144.22MB/sec
Timing buffered disk reads 64MB in 3.31 seconds=19.34MB/sec
```
- Tオプションはbuffer-cache
- tオプションはbuffered diskに関する読み込みテストを行う。
よくhdparmで利用されるのがIDE DMA(Direct Memory Access)モードの変更である。 一般的にDMAは16bitモードで利用されているので、32bitモードにした方が高速化が望めるらしい。 以下のように設定を行う。

```
#/sbin/hdparm -d 1 /dev/hda
```

IDE DMA転送モードの確認は以下のようにして行う。
```
#/sbin/hdparm -d /dev/hda
```
