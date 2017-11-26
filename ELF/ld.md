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

### 順番を気にせずにうまくリンクする

関数が main() ->　foo() -> bar() のようにコールしているならば、 リンク時にも main.c -lfoo -lbar の順に並べないと、リンク解決できないようです。
このような場合にはno-as-neededを付与すればlfooとlbarの順番を気にせずに以下のどちらでもリンク解決できるようになるようです。
```
$ gcc -Wl,-no-as-needed -L. -lfoo -lbar main.c
or
$ gcc -Wl,-no-as-needed -L. -lbar -lfoo main.c
```

- 参考
  - http://masahir0y.blogspot.jp/2013/01/shared-object.html
