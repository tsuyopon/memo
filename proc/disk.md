

### スワップ情報を表示する(/proc/swaps)
```
$ cat /proc/swaps 
Filename				Type		Size	Used	Priority
/dev/dm-0                               partition	1015804	131176	0
```

### ブロックデバイスとキャラクタデバイスを表示する(/proc/devices)
メジャー番号のデバイスグループ(blockとcharacter)を表示する。
```
$ cat /proc/devices 
Character devices:
  1 mem
  4 /dev/vc/0
  4 tty
  4 ttyS
  5 /dev/tty
  5 /dev/console
  5 /dev/ptmx
  7 vcs
 10 misc
 13 input
 14 sound
 21 sg
 29 fb
116 alsa
128 ptm
136 pts
162 raw
180 usb
188 ttyUSB
189 usb_device
202 cpu/msr
203 cpu/cpuid
251 hidraw
252 usbmon
253 bsg
254 rtc

Block devices:
259 blkext
  7 loop
  8 sd
  9 md
 11 sr
 65 sd
 66 sd
 67 sd
 68 sd
 69 sd
 70 sd
 71 sd
128 sd
129 sd
130 sd
131 sd
132 sd
133 sd
134 sd
135 sd
253 device-mapper
254 mdp
```
