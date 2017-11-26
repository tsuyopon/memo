# 概要
### ld(GNUのリンカ)を使用する
例えば次の例を見てみることとする。
```
$ld -o output /lib/crt0.o hello.o -lc  <=一番良く使用される例
```
この例では、ldにoutputという名前のファイルを作成するように命令している。  
リンクするファイルは/lib/crt0.oとhello.o及び標準的な検索ディレクトリ(/usr/lib,/libなど)にあるライブラリlibc.aであるという亊を意味している。

### rpathをバイナリに設定して、それが設定されていることを確認する
Wlオプションでリンカに対してオプションを渡すことができるようになります。
```
$ cat test.c 
#include<stdio.h>
int main(){ printf("Hello World\n"); }
$ gcc -Wl,-rpath /usr/local/lib64 test.c 
$ objdump -p a.out  | grep -i rpath
  RPATH                /usr/local/lib64
```

複数パスを指定したい場合にはCSV形式で指定できるようだ。
- https://stackoverflow.com/questions/6562403/i-dont-understand-wl-rpath-wl
```
$ gcc -Wl,aaa,bbb,ccc
```
