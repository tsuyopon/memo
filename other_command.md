# 概要
便利なコマンドなど


# 詳細

### N秒ごとにコマンドを確認する
たとえば、時刻を表示する場合など
```
$ watch -n 1 date
```

複数の引数がある場合などは次のようにダブルクォートで囲みます
```
$ watch -n 1 "cat /proc/cpuinfo| grep -i mhz"
```

### 制御文字を表示する
vオプションで制御オプションもターミナル上に見えるように出力することができます(通常はlessなどをすると制御文字も見れる)
```
$ cat -v test
hoge^Afuga^Bpiyo^Cfoo^Dbar
```

### 空行の重複行を排除する
```
$ cat test 
hoge


fuga



piyo
```

sオプションで重複を排除することができます。
```
$ cat -s test 
hoge

fuga

piyo
```

### 特定のフィールド列でソートを行う
例えば、/etc/passwdで４番目の列でソートをするばあいには次のようにします
```
$ cat /etc/passwd | sort -t: -nk4 
```

### 特定のフィールドを以降を取り出して、一部のunixtimeなどはわかりやすい時刻に変換する
```
$ echo "field1,123456789,field3,field4,field5" | cut -d , -f2- 
123456789,field3,field4,field5
$ echo "field1,123456789,field3,field4,field5" | cut -d , -f2- | awk -F',' '{print strftime("%c", $1), $0}'
1973年11月30日 06時33分09秒 123456789,field3,field4,field5
```
