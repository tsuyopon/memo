# 概要
smartはハードディスクの温度を調べるためのソフトウェアです。

# 詳細

### ハードディスクの温度を調べる(実験環境:fedora5)
ハードディスクのS.M.A.R.T情報を取得するにはsmartctlで様々なHD情報を取得 できる。以下はsmartctlで温度だけを調べた例です。
```
# /usr/sbin/smartctl -a /dev/hda | grep Temp
194 Temperature_Celsius     0x0022   050   056   000    Old_age   Always
- 50
```
以下にsmartctlコマンドのオプションを示す。

オプション 意味 
```
-a     すべての情報を表示する 
-i     ハードディスクのS.M.A.R.T.サポート状況を表示する 
-l     エラーのログを表示する 
-v     温度やシークエラーなどの状況を表示する 
```
