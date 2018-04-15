# 概要
MacでAppleSuperDriveを操作する場合にはdrutilコマンドを利用します。
drutilは光学ドライブに対してファイルの書き込みや情報表示・消去などを実行するコマンド。

# 詳細

### ディスクを排出する
```
$ drutil eject
```

### 接続されている全てのドライブ情報を表示する
```
$ drutil list
   Vendor   Product           Rev   Bus       SupportLevel
1  HL-DT-ST DVDRW  GX50N      RR06  USB       Unsupported
```

### 接続している光学ドライブの情報を表示する
```
$ drutil info
 Vendor   Product           Rev 
 HL-DT-ST DVDRW  GX50N      RR06

   Interconnect: USB
   SupportLevel: Unsupported
   Profile Path: None
          Cache: 768k
       CD-Write: -R, -RW, BUFE, CDText, Test, IndexPts, ISRC
      DVD-Write: -R, -R DL, -RW, +R, +R DL, +RW, BUFE, Test
     Strategies: CD-TAO, CD-SAO, CD-Raw, DVD-DAO
```

### 光学ドライブに挿入されているメディア情報を表示する
```
$ drutil status
 Vendor   Product           Rev 
 HL-DT-ST DVDRW  GX50N      RR06

           Type: CD-ROM               Name: /dev/disk2
       Sessions: 1                  Tracks: 60
   Overwritable:   00:00:00         blocks:        0 /   0.00MB /   0.00MiB
     Space Free:   00:00:00         blocks:        0 /   0.00MB /   0.00MiB
     Space Used:   69:07:24         blocks:   311049 / 637.03MB / 607.52MiB
    Writability: 
```

### CD/R/RWメディアのATIP情報を表示する
```
$ drutil atip
 Vendor   Product           Rev 
 HL-DT-ST DVDRW  GX50N      RR06

    ATIP information can only be read from CD-R/RW media.
```

# SeeAlso
- drutils: OS X Man Pages
  - https://developer.apple.com/legacy/library/documentation/Darwin/Reference/ManPages/man1/drutil.1.html

### TODO
以下についてはまだ使ったことがないのでまとめていない
- burn: 指定したファイル内容をCD/DVDに書き込む。イメージファイル（.iso）を書き込むことも可能。
- erase: 書き換えメディアを消する。消去方法は、「quick」「full」の２種類。
- tray: 光学ドライブのトレイを操作。「open」「close」「eject」が行える。

