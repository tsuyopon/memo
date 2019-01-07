# 概要
便利なコマンドなど


# 詳細

### IPアドレスを取得する
簡単にIFのIPアドレスを取得できるコマンドがあった。 ただし、ipconfig(ifconfigではない)ことに注意
```
$ ipconfig getifaddr en0
192.168.3.10
```

### N秒ごとにコマンドを確認する
たとえば、時刻を表示する場合など
```
$ watch -n 1 date
```

複数の引数がある場合などは次のようにダブルクォートで囲みます
```
$ watch -n 1 "cat /proc/cpuinfo| grep -i mhz"
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
- 2番目以降のフィールドを取得する
```
$ echo "field1,123456789,field3,field4,field5" | cut -d , -f2- 
123456789,field3,field4,field5
```

- 2番目と4番目のフィールドを取得する
```
$ echo "field1,123456789,field3,field4,field5" | cut -d , -f2,4
123456789,field4
```

- unixtimeを変換して出力する
```
$ echo "field1,123456789,field3,field4,field5" | cut -d , -f2- | awk -F',' '{print strftime("%c", $1), $0}'
1973年11月30日 06時33分09秒 123456789,field3,field4,field5
```

### 制御文字を表示する
vオプションで制御オプションもターミナル上に見えるように出力することができます(通常はlessなどをすると制御文字も見れる)
```
$ cat -v test
hoge^Afuga^Bpiyo^Cfoo^Dbar
```

抽出するには以下の通り
```
$ cat a | cut -d ^Z -f 2
fuga
```

次のような形式で取得することも可能です。
```
$ cat -v test 
1^A2^A3^A4^A5
1^A2^A3^A4^A5
$ cat test | cut -f 3- -d $'\x01' | cat -v
3^A4^A5
3^A4^A5
```

- SeeAlso
  - https://stackoverflow.com/questions/25243763/cut-command-with-delimiter-control-a

### 適当にN文字を生成する
以下の例では適当に100文字を生成した際の例です
```
$ cat /dev/urandom | tr -dc 'a-zA-Z0-9' | fold -w 100 | head -1
aoqFRhJkNAi5ZBKXM9JSL7EyLhL7o4xxKELuS60CYAEky6UWX9A2g2xtINKlayAMgsRcsmrxVeufFuhOiJRJN67e7wE7poCfQpHf
```

- 参考
  - https://qiita.com/Vit-Symty/items/5be5326c9db9de755184
