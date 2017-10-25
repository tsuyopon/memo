# 概要
コマンドラインに関するTIPS

# 詳細
### dateコマンド関連
- 現在のunixtime
```
$ date +%s
1508860937
```
- 特定の日時のunixtimeを取得する
```
$ date +%s --date "2005-01-01 00:00"
1104505200
```
- unixtimeから日付への変換
```
$ date -d@1104505200
Sat Jan  1 00:00:00 JST 2005
```
- 明日の時刻を取得する(dはdateと同じ)
```
$ date -d tomorrow +%s
1508888328
```
- 30日後の日付を取得する
```
$ date "+%Y/%m/%d %H:%M:%S" -d "30days"
2017/11/23 08:40:25
```

- 参考
  - 以下にdateコマンドについて色々まとまっています。
  - http://hydrocul.github.io/wiki/commands/date.html

### 特定の文字数以下・以上の行を取得したい
例えば特定のファイルの各行が100文字以下のものだけを表示するには次のようにします。
tail -fなどと組み合わせて使うことができそうです。
```
$ cat gist.md | awk 'length($0) < 100'
```

- 参考
  - https://stackoverflow.com/questions/12815519/finding-lines-which-are-greater-than-120-characters-length-using-sed

### sudoでリダイレクトしたい場合
cオプションあとは囲めばOK
```
$ sudo sh -c "echo 'redirect' >> /var/test/hoge.txt"
```

teeを使っても同様のことをできます
```
$ echo "redirect" | tee -a /var/test/hoge.txt
```


### ファイルのサイズを0にする。
たとえば、何かのプロセスがログを吐き出していてrmやmvなどを実行したくないような場合にはtruncateが利用できます。
```
$ ls -alt /var/log/messages-20161020 
-rw------- 1 root root 231267 Oct 20 07:10 /var/log/messages-20161020
$ sudo truncate -s 0 /var/log/messages-20161020 
$ ls -alt /var/log/messages-20161020 
-rw------- 1 root root 0 Nov 30 09:55 /var/log/messages-20161020
```

ファイルサイズを0にするのであれば以下のコマンドでも可能です。
```
$ : > /var/log/messages-20161020
or
$ echo -n > /var/log/messages-20161020
or
$ sudo cp /dev/null /var/log/messages-20161020
```

### コマンドラインからファイルを生成する
次を実行するだけでコマンドラインからファイルを生成することが可能です。
```
$ cat > hello.c << "EOF"
#include <stdio.h>

int main(int argc, char* argv[])
{
printf("hello\n");

return 0;
}
EOF
$ cc -O0 -g hello.c
```

### 特定のプロセス名のpidを取得する。
例えばhttpdのpidを取得する場合

```
$ pidof httpd
6924 6923 6922 6921 6920 6919 6918 6917 2050
```

### lessコマンド終了時の画面クリアを避けたい
lessコマンド終了時にqを押したらlessで見ていた画面が全てクリアされる。 これを防ぐには次のように起動すれば良い
```
$ less -X
```

もしくは、環境変数に入れてしまうのも手かもしれない。
```
export LESS="-X" 
```

### 複数の言語や文字コードに対応したファイルビュアー  
```
$ lv <file>
```

### 特定のバイナリの関数スタックを調査する(pstack)

たとえば、特定のバイナリのスタックを見たい場合pidをまずは調べる
```
root     15985  0.0  0.5 402228  5924 ?        Sl   16:26   0:00 /usr/libexec/packagekitd
```

sudo権限でpidを引数としてpstackコマンドを実行する。
バックトレースを取得することができる。stripされている箇所は??と表示されるようだ。
```
$ sudo pstack 15985
Thread 3 (Thread 0x7fdd1b59b700 (LWP 15986)):
#0  0x0000003897ae8bdf in poll () from /lib64/libc.so.6
#1  0x0000003899a47984 in ?? () from /lib64/libglib-2.0.so.0
#2  0x0000003899a47aa4 in g_main_context_iteration () from /lib64/libglib-2.0.so.0
#3  0x0000003899a47af1 in ?? () from /lib64/libglib-2.0.so.0
#4  0x0000003899a6a315 in ?? () from /lib64/libglib-2.0.so.0
#5  0x0000003897e07d14 in start_thread () from /lib64/libpthread.so.0
#6  0x0000003897af168d in clone () from /lib64/libc.so.6
Thread 2 (Thread 0x7fdd1a599700 (LWP 15988)):
#0  0x0000003897ae8bdf in poll () from /lib64/libc.so.6
#1  0x0000003899a47984 in ?? () from /lib64/libglib-2.0.so.0
#2  0x0000003899a47de2 in g_main_loop_run () from /lib64/libglib-2.0.so.0
#3  0x000000389b6c9126 in ?? () from /lib64/libgio-2.0.so.0
#4  0x0000003899a6a315 in ?? () from /lib64/libglib-2.0.so.0
#5  0x0000003897e07d14 in start_thread () from /lib64/libpthread.so.0
#6  0x0000003897af168d in clone () from /lib64/libc.so.6
Thread 1 (Thread 0x7fdd1b59c800 (LWP 15985)):
#0  0x0000003897ae8bdf in poll () from /lib64/libc.so.6
#1  0x0000003899a47984 in ?? () from /lib64/libglib-2.0.so.0
#2  0x0000003899a47de2 in g_main_loop_run () from /lib64/libglib-2.0.so.0
#3  0x000000000040d2df in main ()
```

### 特定のプロセスのファイルディスクリプタ利用数を確認する
xargsでIオプションを利用すると以前のPIDを引き継ぐことができる。そして"sh -c"などに引き渡して実行するのが肝となる。  
/proc配下はsudoが必要なのでsudoを付与しています。
```
$ ps auxww | grep -i udevd | grep -v grep | awk -F' ' '{print $2}' | xargs -I{} sh -c 'sudo ls -1 /proc/{}/fd | wc -l'
12
9
9
```

- 参考
  - https://qiita.com/soymsk/items/7c1621ffca4d0f7ad678



