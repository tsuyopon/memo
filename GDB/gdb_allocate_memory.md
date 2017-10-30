# 概要
例えば、次のようなプログラムにおいてmyprintの出力結果を変更したい事があるとする。
```
$ cat test.c 
#include<stdio.h>

void myprint(char* args){
	printf("%s\n", args);
}

int main(){
	char test[11] = "test.co.jp";    // ちょうどサイズを確保する
	myprint(test);
}
```

しかし、大元ではそのサイズ分しかchar要素が確保されていないので、元々確保した要素数よりも大きい場合に死んでしまう(以下、その出力例)
```
$ gcc -g ./test.cc 
tsuyoshi@tsuyoshi:~/git/memo/GDB:$ gdb ./a.out 
(gdb) b myprint
Breakpoint 1 at 0x4005b2: file ./test.cc, line 4.
(gdb) run
Starting program: /home/tsuyoshi/git/memo/GDB/a.out 

Breakpoint 1, myprint (args=0x7fffffffe930 "test.co.jp") at ./test.cc:4
4		printf("%s\n", args);
(gdb) set {char [32]} 0x7fffffffe930 = "test.co.jp:hogehogehoge"
(gdb) c
Continuing.
test.co.jp:hogehogehoge
*** stack smashing detected ***: /home/tsuyoshi/git/memo/GDB/a.out terminated

Program received signal SIGABRT, Aborted.
0x00007ffff7a44267 in __GI_raise (sig=sig@entry=6) at ../sysdeps/unix/sysv/linux/raise.c:55
55	../sysdeps/unix/sysv/linux/raise.c: No such file or directory.
```

ここではgdb上で動的にmallocで必要な要素数を確保してポインタの取り付けを行う方法を示す。

### 解決法
mallocで確保した要素をargsの値へのポインタとして取替を行っている
```
$ gcc -g ./test.cc 
tsuyoshi@tsuyoshi:~/git/memo/GDB:$ gdb ./a.out 
(gdb) b myprint
Breakpoint 1 at 0x4005b2: file ./test.cc, line 4.
(gdb) run
Starting program: /home/tsuyoshi/git/memo/GDB/a.out 

Breakpoint 1, myprint (args=0x7fffffffe930 "test.co.jp") at ./test.cc:4
4		printf("%s\n", args);
(gdb) call/x malloc(32)                                   # /xしているのはアドレスをわかりやすくするため
$1 = 0x602010
(gdb) set *0x602010 = "hogehogehogehogehogehogehoge"
(gdb) p &args
$1 = (char **) 0x7fffffffe918
(gdb) set *((char **) 0x7fffffffe918) = *0x602010
(gdb) p args
$6 = 0x602070 "hogehogehogehogehogehogehoge"
(gdb) run
```

# 参考URL
- gdb内で文字列バッファを動的に扱う(基礎)
  - http://www.hogetan.net/note/c/gdb.html
- 
