# 概要
コマンドラインに関するTIPS

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
