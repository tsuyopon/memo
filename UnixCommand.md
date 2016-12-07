# 概要
コマンドラインに関するTIPS

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

