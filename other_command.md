# 概要
便利なコマンドなど


# 詳細

### tailコマンドのfオプションとFオプションの違い
fオプションは元々オープンしていたファイルをtailします。
Fオプションはファイルがrenameされた場合にファイルをオープンし直します。
ということで、実利用ではFオプションの方が便利です。

- 参考
  - https://qiita.com/sakito/items/7f65e16f10b3d754f307

### 指定されたプロセスIDのプロセスにリンクされている動的共有オブジェクトのリストを表示する
```
$ pldd 3895
3895:	/usr/bin/cscope
linux-vdso.so.1
/lib64/libncurses.so.5
/lib64/libtinfo.so.5
/lib64/libc.so.6
/lib64/libdl.so.2
/lib64/ld-linux-x86-64.so.2
```

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

- 指定したdelimiterで区切って、特定のフィールドを指定した出力delimiterを使って表示する
```
$ cat access | cut -d $'\x1A' -f 1,2,3 --output-delimiter $'\t'

or 

$ cat access | cut -d ^Z -f 1,2,3             // ^Zは制御文字で入力すること
```
制御文字の0x1Aについては^Zの制御文字を表しています。詳細は以下を参考のこと
- https://ja.wikipedia.org/wiki/%E5%88%B6%E5%BE%A1%E6%96%87%E5%AD%97




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


### 文字列のsha256を取得する
いくつかの出力方法がある。
```
$ echo -n "Sample Message" | sha256sum 
94288261ce666acc2cb2d0992d0decbdcf2b952abc75a650f88323800a13793d  -
$ echo -n "Sample Message" | shasum -a 256
94288261ce666acc2cb2d0992d0decbdcf2b952abc75a650f88323800a13793d  -
$ echo -n "Sample Message" | openssl dgst -sha256
(stdin)= 94288261ce666acc2cb2d0992d0decbdcf2b952abc75a650f88323800a13793d
