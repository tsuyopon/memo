# 概要
起動時周りの処理について


# 詳細
### 起動時のパラメータを確認する
カーネルの起動時の引数を参照することができます。
```
$ cat /proc/cmdline 
BOOT_IMAGE=/vmlinuz-3.10.0-957.el7.x86_64 root=/dev/mapper/centos-root ro crashkernel=auto rd.lvm.lv=centos/root rd.lvm.lv=centos/swap rhgb quiet LANG=ja_JP.UTF-8
```

### /proc/uptime
1つめのフィールドがOSが起動してからの合計時間(秒)、２つめのフィールドがアイドルだった際の合計時間(秒)
```
$ cat /proc/uptime 
114900.22 112903.48
```

1番目のフィールドをわかりやすい形式に次のようにして変換することができる。
```
$ cat /proc/uptime | awk '{print $1 / 60 /60 /24 "days (" $1 "sec)"}'
1.3068days (114904.66sec)
```

