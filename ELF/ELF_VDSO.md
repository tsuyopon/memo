# VDSO(Virtual Dynamic Shared Object)とは
VDSOとはカーネル側で.soを生成し、.incbin命令でバイナリを取り込むようになっている。VDSOは完全なELF形式です。
この仕組みを利用して頻繁に呼び出すような関数(gettimeofdayなど)はカーネルモードに切り替えることなく、高速にアクセスできる仕組みです。

VDSOの特徴
- ユーザープロセスのメモリ空間の一部にカーネルのメモリを読み取り専用でマップしている
- 頻繁に利用するような関数をカーネルモードに切り替えることなく、高速にアクセス仕組み。
- 共有ライブラリと同じELF形式である。
- vsyscallよりもセキュアな方式である。
  - vsyscallはVDSOと同機能を提供するが、固定アドレスに配置されている仕組みである。

# 詳細
procのmapsを確認するとvdsoで表示されます。同時にvsyscallも出力されることが確認できます。
vdsoとvsyscallは同じ機能を提供しますが、vdsoの方はセキュリティのためのランダムなアドレスに配置されます。(この仕組みはASLRと呼びます。)

ASLRの仕組みの1つとしてVDSOが存在します。
ASLR(Address Space Layout Randomization)はプロセス実行時のメモリ空間の配置をランダマイズすることで，例えば攻撃者が配置したコードのアドレスへのJMP等を防ぐことができる仕組みです。
ASLRはデフォルトで有効です。ASLRを無効化するにはsysctlのkernel.randomize_va_spaceに0を指定します(有効なときは2です。)
なお、ASLRが無効の場合にはvsyscallというVDSOと同機能であるが固定アドレスに配置されている仕組みが利用されるはず(ちゃんとは追えていない。)

通常のアプリケーションは絶対アドレスを用いて記述されているため，ASLRによるランダマイズが適用できませんが、
セキュリティ向上のために相対アドレスを用いたPIE(position-independent executable)と呼ばれる形式が通常のアプリケーションにおいても使用されている。

では、vdsoについてのプロセスをみていくことにします。

以下のコマンドを実行して、他のプロセスのmapsを比較して見てみるとvdsoはプロセス毎にアドレスが異なっているのに対して、vsyscallは他のプロセスでも常に固定値となっています。
```
$ sudo cat /proc/1720/maps 
...
7f753c9b4000-7f753c9b5000 r--p 00021000 fd:00 75800                      /usr/lib64/ld-2.17.so;5c305ca2 (deleted)
7f753c9b5000-7f753c9b6000 rw-p 00022000 fd:00 75800                      /usr/lib64/ld-2.17.so;5c305ca2 (deleted)
7f753c9b6000-7f753c9b7000 rw-p 00000000 00:00 0 
7ffecb6d3000-7ffecb6f4000 rw-p 00000000 00:00 0                          [stack]
7ffecb72a000-7ffecb72c000 r-xp 00000000 00:00 0                          [vdso]
ffffffffff600000-ffffffffff601000 r-xp 00000000 00:00 0                  [vsyscall]
```

vdsoの場合にはlddで出力してもライブラリ先が存在していません。
```
$ ldd /usr/bin/true
	linux-vdso.so.1 =>  (0x00007ffeb0a49000)
	libc.so.6 => /lib64/libc.so.6 (0x00007f2946c3c000)
	/lib64/ld-linux-x86-64.so.2 (0x000055bbaf108000)
```	

VDSO(i386)だと、すべてのシステムコールが利用する。
また、VDSO(x86_64)だと、gettimeofday、time、getcpu、clock_gettimeだけが利用する。
vdsoとして呼び出すことができる関数はアーキテクチャごとに異なる。詳しくは以下に記載されているので参照のこと。
- https://linuxjm.osdn.jp/html/LDP_man-pages/man7/vdso.7.html

なお、上記資料からx86_64のみを抜粋するとVDSOとして呼び出せる関数は次の４つのみである。
```
シンボル                 バージョン
__vdso_clock_gettime    LINUX_2.6
__vdso_getcpu           LINUX_2.6
__vdso_gettimeofday     LINUX_2.6
__vdso_time             LINUX_2.6
```

実は内部の処理は次のようになっています。
- Linuxカーネル側でsoファイルが生成され、.incbinでカーネルに取り込まれます。(arch/x86/vdso/を参照のこと)
- glibc側ではVDSOのアドレスを特定して、__vdso_gettimeofdayを呼び出すラッパーをgettimeofday関数として実装しています。

どのようにVDSO側のアドレスを特定しているのかというと、次のサンプルプログラムを参考にすると具体的な処理が想像できます。
- https://github.com/torvalds/linux/blob/v3.13/Documentation/vDSO/
  - vdso_test.cにmainが定義されていて、parse_vdso.cで定義されている関数を使っている
  - 上記では__vdso_gettimeofdayへのVDSOのアドレスを特定しているが
    - https://github.com/torvalds/linux/blob/v3.13/Documentation/vDSO/parse_vdso.c#L238
    - 次のような流れとなっている
      - stackに格納されるタイプがAT_SYSINFO_EHDRの値と一致しているかどうかのチェック
    - PT_LOADの場合には、「AT_SYSINFO_EHDRの値 + プログラムヘッダに存在するp_offset - プログラムヘッダのp_vaddr + symtabセクションに含まれるst_value」の値からVDSOの位置を特定する。symtabセクションに含まれるst_valueの値は関数名(今回だと__vdso_gettimeofday)から決定される。

# 参考URL
- LWN.net
  - vdsoとvsyscallの違いについて説明している
  - https://lwn.net/Articles/446528/
- https://linuxjm.osdn.jp/html/LDP_man-pages/man3/getauxval.3.html
```
$ LD_SHOW_AUXV=1 /bin/true
$ cat /proc/PID/auxv
```

