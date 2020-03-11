# 概要
nmコマンドは与えられたオブジェクトファイル中に存在するシンボルをリストします。
シンボルリストの意味やその理解についても言及しています。

# 詳細

### オブジェクトファイルのシンボルを確認する
以下のようなhello.cをオブジェクトファイルにします。
```
#include<stdio.h>
int main(){ printf("Hello World\n"); }
```
上記を保存してオブジェクトファイルにします。
```
$ gcc -c hello.c
$ ls 
 hello.c    hello.o
```
上記の様にgccに-cオプションを行うと.o(オブジェクトファイル)が作成される  

上記のシンボルを以下のようにして確認する。
```
$ nm hello.o
00000000 T main
         U printf
```

### 先頭にファイル名を表示する
Aオプションを付与すると先頭にファイル名を表示します。用途としては複数のELFを指定した場合のため?
```
$ nm -A a.out 
a.out:0000000000600e28 d _DYNAMIC
a.out:0000000000601000 d _GLOBAL_OFFSET_TABLE_
a.out:00000000004005c0 R _IO_stdin_used
a.out:0000000000400720 r __FRAME_END__
a.out:00000000004005d4 r __GNU_EH_FRAME_HDR
a.out:0000000000600e20 d __JCR_END__
a.out:0000000000600e20 d __JCR_LIST__
a.out:0000000000601030 D __TMC_END__
a.out:000000000060102c B __bss_start
a.out:0000000000601028 D __data_start
a.out:00000000004004d0 t __do_global_dtors_aux
a.out:0000000000600e18 t __do_global_dtors_aux_fini_array_entry
a.out:00000000004005c8 R __dso_handle
a.out:0000000000600e10 t __frame_dummy_init_array_entry
a.out:                 w __gmon_start__
a.out:0000000000600e18 t __init_array_end
a.out:0000000000600e10 t __init_array_start
a.out:00000000004005b0 T __libc_csu_fini
a.out:0000000000400540 T __libc_csu_init
a.out:                 U __libc_start_main@@GLIBC_2.2.5
a.out:000000000060102c D _edata
a.out:0000000000601030 B _end
a.out:00000000004005b4 T _fini
a.out:00000000004003c8 T _init
a.out:0000000000400430 T _start
a.out:000000000060102c b completed.6355
a.out:0000000000601028 W data_start
a.out:0000000000400460 t deregister_tm_clones
a.out:000000000040051d W f
a.out:00000000004004f0 t frame_dummy
a.out:000000000040052d T main
a.out:                 U puts@@GLIBC_2.2.5
a.out:0000000000400490 t register_tm_clones
```

### 出力フォーマットを指定する。
fオプションの後に指定することができる。bsd, sysv, posixのいずれかを指定することができ、デフォルトはbsdである。

- bsd
```
$ nm -f bsd a.out 
0000000000600e28 d _DYNAMIC
0000000000601000 d _GLOBAL_OFFSET_TABLE_
00000000004005c0 R _IO_stdin_used
0000000000400720 r __FRAME_END__
00000000004005d4 r __GNU_EH_FRAME_HDR
0000000000600e20 d __JCR_END__
0000000000600e20 d __JCR_LIST__
0000000000601030 D __TMC_END__
000000000060102c B __bss_start
0000000000601028 D __data_start
00000000004004d0 t __do_global_dtors_aux
0000000000600e18 t __do_global_dtors_aux_fini_array_entry
00000000004005c8 R __dso_handle
0000000000600e10 t __frame_dummy_init_array_entry
                 w __gmon_start__
0000000000600e18 t __init_array_end
0000000000600e10 t __init_array_start
00000000004005b0 T __libc_csu_fini
0000000000400540 T __libc_csu_init
                 U __libc_start_main@@GLIBC_2.2.5
000000000060102c D _edata
0000000000601030 B _end
00000000004005b4 T _fini
00000000004003c8 T _init
0000000000400430 T _start
000000000060102c b completed.6355
0000000000601028 W data_start
0000000000400460 t deregister_tm_clones
000000000040051d W f
00000000004004f0 t frame_dummy
000000000040052d T main
                 U puts@@GLIBC_2.2.5
0000000000400490 t register_tm_clones
```

- sysm
```
$ nm -f sysv a.out 


Symbols from a.out:

Name                  Value           Class        Type         Size             Line  Section

_DYNAMIC            |0000000000600e28|   d  |            OBJECT|                |     |.dynamic
_GLOBAL_OFFSET_TABLE_|0000000000601000|   d  |            OBJECT|                |     |.got.plt
_IO_stdin_used      |00000000004005c0|   R  |            OBJECT|0000000000000004|     |.rodata
__FRAME_END__       |0000000000400720|   r  |            OBJECT|                |     |.eh_frame
__GNU_EH_FRAME_HDR  |00000000004005d4|   r  |            NOTYPE|                |     |.eh_frame_hdr
__JCR_END__         |0000000000600e20|   d  |            OBJECT|                |     |.jcr
__JCR_LIST__        |0000000000600e20|   d  |            OBJECT|                |     |.jcr
__TMC_END__         |0000000000601030|   D  |            OBJECT|                |     |.data
__bss_start         |000000000060102c|   B  |            NOTYPE|                |     |.bss
__data_start        |0000000000601028|   D  |            NOTYPE|                |     |.data
__do_global_dtors_aux|00000000004004d0|   t  |              FUNC|                |     |.text
__do_global_dtors_aux_fini_array_entry|0000000000600e18|   t  |            OBJECT|                |     |.fini_array
__dso_handle        |00000000004005c8|   R  |            OBJECT|                |     |.rodata
__frame_dummy_init_array_entry|0000000000600e10|   t  |            OBJECT|                |     |.init_array
__gmon_start__      |                |   w  |            NOTYPE|                |     |*UND*
__init_array_end    |0000000000600e18|   t  |            NOTYPE|                |     |.init_array
__init_array_start  |0000000000600e10|   t  |            NOTYPE|                |     |.init_array
__libc_csu_fini     |00000000004005b0|   T  |              FUNC|0000000000000002|     |.text
__libc_csu_init     |0000000000400540|   T  |              FUNC|0000000000000065|     |.text
__libc_start_main@@GLIBC_2.2.5|                |   U  |              FUNC|                |     |*UND*
_edata              |000000000060102c|   D  |            NOTYPE|                |     |.data
_end                |0000000000601030|   B  |            NOTYPE|                |     |.bss
_fini               |00000000004005b4|   T  |              FUNC|                |     |.fini
_init               |00000000004003c8|   T  |              FUNC|                |     |.init
_start              |0000000000400430|   T  |              FUNC|                |     |.text
completed.6355      |000000000060102c|   b  |            OBJECT|0000000000000001|     |.bss
data_start          |0000000000601028|   W  |            NOTYPE|                |     |.data
deregister_tm_clones|0000000000400460|   t  |              FUNC|                |     |.text
f                   |000000000040051d|   W  |              FUNC|0000000000000010|     |.text
frame_dummy         |00000000004004f0|   t  |              FUNC|                |     |.text
main                |000000000040052d|   T  |              FUNC|000000000000000c|     |.text
puts@@GLIBC_2.2.5   |                |   U  |              FUNC|                |     |*UND*
register_tm_clones  |0000000000400490|   t  |              FUNC|                |     |.text
```

- posix
```
$ nm -f posix a.out 
_DYNAMIC d 0000000000600e28 
_GLOBAL_OFFSET_TABLE_ d 0000000000601000 
_IO_stdin_used R 00000000004005c0 0000000000000004
__FRAME_END__ r 0000000000400720 
__GNU_EH_FRAME_HDR r 00000000004005d4 
__JCR_END__ d 0000000000600e20 
__JCR_LIST__ d 0000000000600e20 
__TMC_END__ D 0000000000601030 
__bss_start B 000000000060102c 
__data_start D 0000000000601028 
__do_global_dtors_aux t 00000000004004d0 
__do_global_dtors_aux_fini_array_entry t 0000000000600e18 
__dso_handle R 00000000004005c8 
__frame_dummy_init_array_entry t 0000000000600e10 
__gmon_start__ w         
__init_array_end t 0000000000600e18 
__init_array_start t 0000000000600e10 
__libc_csu_fini T 00000000004005b0 0000000000000002
__libc_csu_init T 0000000000400540 0000000000000065
__libc_start_main@@GLIBC_2.2.5 U         
_edata D 000000000060102c 
_end B 0000000000601030 
_fini T 00000000004005b4 
_init T 00000000004003c8 
_start T 0000000000400430 
completed.6355 b 000000000060102c 0000000000000001
data_start W 0000000000601028 
deregister_tm_clones t 0000000000400460 
f W 000000000040051d 0000000000000010
frame_dummy t 00000000004004f0 
main T 000000000040052d 000000000000000c
puts@@GLIBC_2.2.5 U         
register_tm_clones t 0000000000400490 
```

### それぞれのシンボルを用いてデバッグ情報を見つけようとする
次のプログラムを使って考えます。これをgオプション付きでデバッグビルドします。
```
$ cat test.c 
#include<stdio.h>

int globalvar;

void testfunc1(){
	printf("testfunc1");
}

int main(){
	globalvar = 100;
	printf("Hello World\n");
}
$ gcc -g test.c
```

lオプションを用いることで、gオプションでコンパイルされているバイナリの場合に、
定義されているシンボルに対してはシンボルアドレスの行番号を探して表示し、
未定義なシンボルに対しては、シンボルを参照しているリロケーションエントリの行番号を探します。

行番号に関する情報を見つけることができたら、他のシンボル情報に続いて表示されます。

lオプションを用いて先ほどのプログラムを確認しています。
```
$ nm -l a.out 
0000000000600e28 d _DYNAMIC
0000000000601000 d _GLOBAL_OFFSET_TABLE_
0000000000400610 R _IO_stdin_used
0000000000400788 r __FRAME_END__
0000000000400638 r __GNU_EH_FRAME_HDR
0000000000600e20 d __JCR_END__
0000000000600e20 d __JCR_LIST__
0000000000601038 D __TMC_END__
0000000000601034 B __bss_start
0000000000601030 D __data_start
0000000000400510 t __do_global_dtors_aux
0000000000600e18 t __do_global_dtors_aux_fini_array_entry
0000000000400618 R __dso_handle
0000000000600e10 t __frame_dummy_init_array_entry
                 w __gmon_start__
0000000000600e18 t __init_array_end
0000000000600e10 t __init_array_start
0000000000400600 T __libc_csu_fini
0000000000400590 T __libc_csu_init
                 U __libc_start_main@@GLIBC_2.2.5
0000000000601034 D _edata
0000000000601040 B _end
0000000000400604 T _fini
0000000000400400 T _init
0000000000400470 T _start
0000000000601034 b completed.6355
0000000000601030 W data_start
00000000004004a0 t deregister_tm_clones
0000000000400530 t frame_dummy
0000000000601038 B globalvar	/home/tsuyoshi/test10/test.c:3
0000000000400572 T main	/home/tsuyoshi/test10/test.c:9
                 U printf@@GLIBC_2.2.5
                 U puts@@GLIBC_2.2.5
00000000004004d0 t register_tm_clones
000000000040055d T testfunc1	/home/tsuyoshi/test10/test.c:5
```

通常時との違いを確認するためにdiffで確認してみます。
```
$ nm a.out  > normal
$ nm -l a.out > l_option
$ diff normal l_option 
30,31c30,31
< 0000000000601038 B globalvar
< 0000000000400572 T main
---
> 0000000000601038 B globalvar	/home/tsuyoshi/test10/test.c:3
> 0000000000400572 T main	/home/tsuyoshi/test10/test.c:9
35c35
< 000000000040055d T testfunc1
---
> 000000000040055d T testfunc1	/home/tsuyoshi/test10/test.c:5
```

### 未定義のシンボルのみを表示する

```
$ nm -u /opt/openssl-1.1.1c/lib/libcrypto.so | tail -10
                 U strtol@@GLIBC_2.2.5
                 U strtoul@@GLIBC_2.2.5
                 U syscall@@GLIBC_2.2.5
                 U sysconf@@GLIBC_2.2.5
                 U syslog@@GLIBC_2.2.5
                 U tcgetattr@@GLIBC_2.2.5
                 U tcsetattr@@GLIBC_2.2.5
                 U time@@GLIBC_2.2.5
                 U vfprintf@@GLIBC_2.2.5
                 U write@@GLIBC_2.2.5
```

### C++でのマングリング表記をデマングルして表示する
Cオプションは--demangleを指定したものと同じです。
以下の例ではC++のstd::が確認できます。
```
$ nm -C cppsample
0000000000600df8 d _DYNAMIC
0000000000601000 d _GLOBAL_OFFSET_TABLE_
0000000000400821 t _GLOBAL__sub_I_main
00000000004008c0 R _IO_stdin_used
00000000004007e4 t __static_initialization_and_destruction_0(int, int)
                 U std::ostream::operator<<(std::ostream& (*)(std::ostream&))@@GLIBCXX_3.4
                 U std::ios_base::Init::Init()@@GLIBCXX_3.4
                 U std::ios_base::Init::~Init()@@GLIBCXX_3.4
0000000000601060 B std::cout@@GLIBCXX_3.4
                 U std::basic_ostream<char, std::char_traits<char> >& std::endl<char, std::char_traits<char> >(std::basic_ostream<char, std::char_traits<char> >&)@@GLIBCXX_3.4
0000000000601171 b std::__ioinit
                 U std::basic_ostream<char, std::char_traits<char> >& std::operator<< <std::char_traits<char> >(std::basic_ostream<char, std::char_traits<char> >&, char const*)@@GLIBCXX_3.4
0000000000400a50 r __FRAME_END__
00000000004008d8 r __GNU_EH_FRAME_HDR
0000000000600df0 d __JCR_END__
0000000000600df0 d __JCR_LIST__
0000000000601058 D __TMC_END__
0000000000601054 B __bss_start
                 U __cxa_atexit@@GLIBC_2.2.5
0000000000601050 D __data_start
0000000000400770 t __do_global_dtors_aux
0000000000600de8 t __do_global_dtors_aux_fini_array_entry
00000000004008c8 R __dso_handle
0000000000600dd8 t __frame_dummy_init_array_entry
                 w __gmon_start__
0000000000600de8 t __init_array_end
0000000000600dd8 t __init_array_start
00000000004008b0 T __libc_csu_fini
0000000000400840 T __libc_csu_init
                 U __libc_start_main@@GLIBC_2.2.5
0000000000601054 D _edata
0000000000601178 B _end
00000000004008b4 T _fini
0000000000400620 T _init
00000000004006d0 T _start
0000000000601170 b completed.6355
0000000000601050 W data_start
0000000000400700 t deregister_tm_clones
0000000000400790 t frame_dummy
00000000004007bd T main
0000000000400730 t register_tm_clones
```

### 動的なシンボルのみを表示する。
Dオプションを付与することによって通常のシンボルではなく、動的なシンボルを表示します。
```
$ nm -D a.out 
                 w __gmon_start__
                 U __libc_start_main
                 U printf
                 U puts
```

### 外部シンボルのみを表示する
外部シンボル、つまり大文字のシンボルのみを表示します。これにはgオプションを利用します。
```
$ nm -g a.out 
0000000000400610 R _IO_stdin_used
0000000000601038 D __TMC_END__
0000000000601034 B __bss_start
0000000000601030 D __data_start
0000000000400618 R __dso_handle
                 w __gmon_start__
0000000000400600 T __libc_csu_fini
0000000000400590 T __libc_csu_init
                 U __libc_start_main@@GLIBC_2.2.5
0000000000601034 D _edata
0000000000601040 B _end
0000000000400604 T _fini
0000000000400400 T _init
0000000000400470 T _start
0000000000601030 W data_start
0000000000601038 B globalvar
0000000000400572 T main
                 U printf@@GLIBC_2.2.5
                 U puts@@GLIBC_2.2.5
000000000040055d T testfunc1
```

これをdiffで通常時と比較してみると、小文字のシンボルが表示されていないことがわかります。
```
$ nm a.out > normal
$ nm -g a.out > g_option
$ diff normal g_option 
1,2d0
< 0000000000600e28 d _DYNAMIC
< 0000000000601000 d _GLOBAL_OFFSET_TABLE_
4,7d1
< 0000000000400788 r __FRAME_END__
< 0000000000400638 r __GNU_EH_FRAME_HDR
< 0000000000600e20 d __JCR_END__
< 0000000000600e20 d __JCR_LIST__
11,12d4
< 0000000000400510 t __do_global_dtors_aux
< 0000000000600e18 t __do_global_dtors_aux_fini_array_entry
14d5
< 0000000000600e10 t __frame_dummy_init_array_entry
16,17d6
< 0000000000600e18 t __init_array_end
< 0000000000600e10 t __init_array_start
26d14
< 0000000000601034 b completed.6355
28,29d15
< 00000000004004a0 t deregister_tm_clones
< 0000000000400530 t frame_dummy
34d19
< 00000000004004d0 t register_tm_clones
```

### シンボルの数値によってソートする
通常はアルファベット順に指定されているが、nオプションを付与することでアドレスの数値によってソートします。
```
$ nm -n a.out 
                 w __gmon_start__
                 U __libc_start_main@@GLIBC_2.2.5
                 U printf@@GLIBC_2.2.5
                 U puts@@GLIBC_2.2.5
0000000000400400 T _init
0000000000400470 T _start
00000000004004a0 t deregister_tm_clones
00000000004004d0 t register_tm_clones
0000000000400510 t __do_global_dtors_aux
0000000000400530 t frame_dummy
000000000040055d T testfunc1
0000000000400572 T main
0000000000400590 T __libc_csu_init
0000000000400600 T __libc_csu_fini
0000000000400604 T _fini
0000000000400610 R _IO_stdin_used
0000000000400618 R __dso_handle
0000000000400638 r __GNU_EH_FRAME_HDR
0000000000400788 r __FRAME_END__
0000000000600e10 t __frame_dummy_init_array_entry
0000000000600e10 t __init_array_start
0000000000600e18 t __do_global_dtors_aux_fini_array_entry
0000000000600e18 t __init_array_end
0000000000600e20 d __JCR_END__
0000000000600e20 d __JCR_LIST__
0000000000600e28 d _DYNAMIC
0000000000601000 d _GLOBAL_OFFSET_TABLE_
0000000000601030 D __data_start
0000000000601030 W data_start
0000000000601034 B __bss_start
0000000000601034 D _edata
0000000000601034 b completed.6355
0000000000601038 D __TMC_END__
0000000000601038 B globalvar
0000000000601040 B _end
```

### シンボルをまったくソートさせない
何も指定しないとアルファベット順に表示しますが、pオプションを付与すると全くソートしません
```
$ nm -p a.out 
0000000000600e20 d __JCR_LIST__
00000000004004a0 t deregister_tm_clones
00000000004004d0 t register_tm_clones
0000000000400510 t __do_global_dtors_aux
0000000000601034 b completed.6355
0000000000600e18 t __do_global_dtors_aux_fini_array_entry
0000000000400530 t frame_dummy
0000000000600e10 t __frame_dummy_init_array_entry
0000000000400788 r __FRAME_END__
0000000000600e20 d __JCR_END__
0000000000600e18 t __init_array_end
0000000000600e28 d _DYNAMIC
0000000000600e10 t __init_array_start
0000000000400638 r __GNU_EH_FRAME_HDR
0000000000601000 d _GLOBAL_OFFSET_TABLE_
0000000000400600 T __libc_csu_fini
0000000000601030 W data_start
                 U puts@@GLIBC_2.2.5
0000000000601038 B globalvar
0000000000601034 D _edata
000000000040055d T testfunc1
0000000000400604 T _fini
                 U printf@@GLIBC_2.2.5
                 U __libc_start_main@@GLIBC_2.2.5
0000000000601030 D __data_start
                 w __gmon_start__
0000000000400618 R __dso_handle
0000000000400610 R _IO_stdin_used
0000000000400590 T __libc_csu_init
0000000000601040 B _end
0000000000400470 T _start
0000000000601034 B __bss_start
0000000000400572 T main
0000000000601038 D __TMC_END__
0000000000400400 T _init
```

### ソート順を逆にする
```
$ nm -r a.out 
000000000040055d T testfunc1
00000000004004d0 t register_tm_clones
                 U puts@@GLIBC_2.2.5
                 U printf@@GLIBC_2.2.5
0000000000400572 T main
0000000000601038 B globalvar
0000000000400530 t frame_dummy
00000000004004a0 t deregister_tm_clones
0000000000601030 W data_start
0000000000601034 b completed.6355
0000000000400470 T _start
0000000000400400 T _init
0000000000400604 T _fini
0000000000601040 B _end
0000000000601034 D _edata
                 U __libc_start_main@@GLIBC_2.2.5
0000000000400590 T __libc_csu_init
0000000000400600 T __libc_csu_fini
0000000000600e10 t __init_array_start
0000000000600e18 t __init_array_end
                 w __gmon_start__
0000000000600e10 t __frame_dummy_init_array_entry
0000000000400618 R __dso_handle
0000000000600e18 t __do_global_dtors_aux_fini_array_entry
0000000000400510 t __do_global_dtors_aux
0000000000601030 D __data_start
0000000000601034 B __bss_start
0000000000601038 D __TMC_END__
0000000000600e20 d __JCR_LIST__
0000000000600e20 d __JCR_END__
0000000000400638 r __GNU_EH_FRAME_HDR
0000000000400788 r __FRAME_END__
0000000000400610 R _IO_stdin_used
0000000000601000 d _GLOBAL_OFFSET_TABLE_
0000000000600e28 d _DYNAMIC
```

### アドレスの表記方法を8進数、10進数、16進数で表示する

基数はtオプションの後に文字を指定することで、8進数(o)、10進数(t)、16進数(x)を指定する。
```
// 10進数の場合にはdを指定する
$ nm -t d a.out | tail -5
0000000004195698 T main
                 U printf@@GLIBC_2.2.5
                 U puts@@GLIBC_2.2.5
0000000004195536 t register_tm_clones
0000000004195677 T testfunc1

// 8進数の場合にはoを指定する
$ nm -t o a.out | tail -5
0000000020002562 T main
                 U printf@@GLIBC_2.2.5
                 U puts@@GLIBC_2.2.5
0000000020002320 t register_tm_clones
0000000020002535 T testfunc1

// 16進数の場合にはxを指定する
$ nm -t x a.out | tail -5
0000000000400572 T main
                 U printf@@GLIBC_2.2.5
                 U puts@@GLIBC_2.2.5
00000000004004d0 t register_tm_clones
000000000040055d T testfunc1
```

### シンボルサイズ順で表示する
サイズが昇順は単順にsize-sortオプションを付与するだけです。
```
$ nm --demangle --size-sort a.out
0000000000000001 b completed.6344
0000000000000002 T __libc_csu_fini
0000000000000004 R _IO_stdin_used
0000000000000004 B a
0000000000000004 b b
0000000000000004 b c.2181
0000000000000024 T main
0000000000000044 T hello
0000000000000065 T __libc_csu_init
```

サイズが降順は次のようにreverse-sortオプションも合わせて付加します
```
$ nm --demangle --size-sort --reverse-sort a.out
0000000000000065 T __libc_csu_init
0000000000000044 T hello
0000000000000024 T main
0000000000000004 b c.2181
0000000000000004 b b
0000000000000004 B a
0000000000000004 R _IO_stdin_used
0000000000000002 T __libc_csu_fini
0000000000000001 b completed.6344
```

### 記号(シンボル)の意味について
小文字はそのシンボルがローカルであることを意味し、大文字はそのシンボルがグローバル (外部定義) であることを意味します。  
典型的なシンボルタイプについては以下のとおりです
- A シンボルの値は絶対値であり、さらにリンクによって変更することはないようです。
- B 初期化されないデータセクション(BSS)
- C CはCommonシンボルを表します。Commonシンボルは初期化されていないデータです。
- D 初期化されたデータセクション
- G 小さなオブジェクトのための初期化されたデータセクションにあります。
- I 別のシンボルへの間接的な参照です。これは、めったに使用されない a.out オブジェクトファイル形式への GNU の拡張です。
- N シンボルはデバッグシンボルであることを表す
- p The symbols is in a stack unwind section.
- R 読み込み専用データセクションにあります。
- S 小さなオブジェクトのための初期化されていないデータセクションにあります。
- T テキストコードセクション内の定義
- U 未定義。シンボルはライブラリによって使われているが、ライブラリ内では定義されていない
- V weak. ウィークに定義された
- W weak. 他のライブラリも同じシンボルを定義している場合、その定義によりオーバーライドされる
- ? 未知であるか、特有のオブジェクトファイルの形式であることを表します
- - ハイフン記号はa.outオブジェクトファイルのスタブです。


上記シンボルについては以下のコマンドで表示されるようだ
```
$ man nm
```

- 上記意味については以下を参考のこと
  - http://www.yosbits.com/opensonar/rest/man/freebsd/man/ja/man1/nm.1.html


### シンボルの意味をライブラリなどから理解する

- A
  - Aシンボルは自分が確認した限りではlibc.so以外では確認できませんでした。
```
$ nm /lib64/libc.so.6 | grep " A "
0000000000000000 A GLIBC_2.10
0000000000000000 A GLIBC_2.11
0000000000000000 A GLIBC_2.12
0000000000000000 A GLIBC_2.13
0000000000000000 A GLIBC_2.14
0000000000000000 A GLIBC_2.15
0000000000000000 A GLIBC_2.16
0000000000000000 A GLIBC_2.17
0000000000000000 A GLIBC_2.2.5
0000000000000000 A GLIBC_2.2.6
0000000000000000 A GLIBC_2.3
0000000000000000 A GLIBC_2.3.2
0000000000000000 A GLIBC_2.3.3
0000000000000000 A GLIBC_2.3.4
0000000000000000 A GLIBC_2.4
0000000000000000 A GLIBC_2.5
0000000000000000 A GLIBC_2.6
0000000000000000 A GLIBC_2.7
0000000000000000 A GLIBC_2.8
0000000000000000 A GLIBC_2.9
0000000000000000 A GLIBC_PRIVATE
```

- B
```
$ nm --debug-syms /opt/openssl-1.0.2m/lib/libcrypto.so | grep " B "
000000000042a3c8 B OPENSSL_NONPIC_relocated
000000000042db40 B OPENSSL_ia32cap_P
000000000042a3a1 B __bss_start
000000000042db60 B _end
000000000042a6a0 B _shadow_DES_check_key
000000000042c658 B app_pkey_methods
000000000042a498 B obj_cleanup_defer
000000000042a840 B rand_predictable
000000000042db58 B sig_app
000000000042db50 B sigx_app
```

- C
  - 次のようなコードを実行するとオブジェクトコード上ではCシンボルがあることを確認した。
  - ただし、一般的なlibやgccで生成された実行コードからはCシンボルが存在することを確認できなかった。
  - (参考) https://www.linuxquestions.org/questions/programming-9/using-nm-command-to-get-symbol-information-571162/
```
$ cat test2.c 
#include <stdio.h>

int a;
int b = 10;
int *c;
int *d = NULL;

extern short e;
extern short *f;

char g[5];
char h[7] = "Piyush";
extern char i[2];

static int p;
static int q = 40;
static int r[4];
static int s[4] = {1, 2, 3};

int main()
{
        int j;
        int k = 30;
        int *l;
        int *m = NULL;
        int n[3];
        int o[3] = {4, 0};
}
$ gcc -c test2.c 
$ nm test2.o                // 生成されたオブジェクトファイルを確認するとCシンボルがある
0000000000000004 C a
0000000000000000 D b
0000000000000008 C c
0000000000000000 B d
0000000000000005 C g
0000000000000004 D h
0000000000000000 T main
0000000000000008 b p
000000000000000c d q
0000000000000010 b r
0000000000000010 d s
$ gcc test2.c
$ nm a.out                 // バイナリで生成されるとCシンボルがなくなる
(snip)
0000000000400400 T _start
00000000006010a0 B a
0000000000601040 D b
0000000000601098 B c
0000000000601060 b completed.6344
0000000000601070 B d
0000000000601030 W data_start
0000000000400430 t deregister_tm_clones
00000000004004c0 t frame_dummy
0000000000601090 B g
0000000000601044 D h
00000000004004ed T main
0000000000601078 b p
000000000060104c d q
0000000000601080 b r
0000000000400460 t register_tm_clones
0000000000601050 d s
```

- D
  - 以下に示されるような構造体の定義が入っている。
  - https://github.com/openssl/openssl/blob/master/crypto/x509/by_dir.c#L49-L60
  - https://github.com/openssl/openssl/blob/master/crypto/x509/by_file.c#L22-L33
```
$ nm --debug-syms /opt/openssl-1.0.2m/lib/libcrypto.so | grep " D " | grep -ie x509_dir_lookup -ie x509_file_lookup
0000000000425cc0 D x509_dir_lookup
0000000000425c60 D x509_file_lookup
```

- G
  - 未確認

- I
  - libc.soでiシンボル(小文字)は利用されているようだ
```
$ nm --debug-syms /lib64/libc.so.6 | grep -i " i "
00000000000af140 i __GI___gettimeofday
0000000000089f80 i __GI___strcasecmp
000000000008c250 i __GI___strncasecmp
00000000000af140 i __GI_gettimeofday
0000000000089f40 i __GI_strcasecmp_l
000000000008c210 i __GI_strncasecmp_l
00000000000af0f0 i __GI_time
00000000000af140 i __gettimeofday
0000000000089710 i __libc_memmove
0000000000089760 i __libc_memset
000000000009fbc0 i __libc_strstr
(snip)
```
  - 例えば、__GI_gettimeofdayの場合には次の箇所でしか利用されていない
    - https://github.com/lattera/glibc/blob/a2f34833b1042d5d8eeb263b4cf4caaea138c4ad/sysdeps/unix/sysv/linux/x86_64/gettimeofday.c#L42-L43

- N
  - gオプションを付与した際に付与されるシンボルのようです。 (TODO: 入っているシンボルの意味については今後確認する)
```
$ cat test.c 
#include<stdio.h>
int main(){ printf("Hello World\n"); }
$ gcc test.c 
$ nm --debug-syms a.out | grep " N "
$ gcc -g test.c 
$ nm --debug-syms a.out | grep " N "
0000000000000000 N .debug_abbrev
0000000000000000 N .debug_aranges
0000000000000000 N .debug_info
0000000000000000 N .debug_line
0000000000000000 N .debug_str
```

- R
```
$ nm --debug-syms /opt/openssl-1.0.2m/lib/libcrypto.so | grep " R " | grep -ie TXT_DB_version -ie X509_version
00000000001cd5a0 R TXT_DB_version
00000000001ca140 R X509_version
```
次のようにconst charで定義されている箇所のようです
```
const char TXT_DB_version[]="TXT_DB" OPENSSL_VERSION_PTEXT;
const char X509_version[] = "X.509" OPENSSL_VERSION_PTEXT;
```

- S
  - 未確認

- T
  - 関数などが含まれていることがわかります。
```
$ nm --debug-syms /opt/openssl-1.0.2m/lib/libssl.so | grep " T " | grep -ie SSL_accept -ie SSL_write
00000000000504c0 T SSL_accept
0000000000050658 T SSL_write
```

- U
  - 以下はただのhello worldのa.outから未定義シンボルを抽出したり、opensslから一部抜粋した例です。
  - 出力される@@の意味については以下のリンクを参照のこと
    - StackOverflow: What does the '@@' symbol mean in the output of nm command?
      - https://stackoverflow.com/questions/39507830/what-does-the-symbol-mean-in-the-output-of-nm-command
    - 公式サイト
      - https://sourceware.org/binutils/docs/ld/VERSION.html
```
$ nm a.out  | grep -i " U "
                 U __libc_start_main@@GLIBC_2.2.5
                 U puts@@GLIBC_2.2.5

$ nm --debug-syms /opt/openssl-1.0.2m/lib/libcrypto.so | grep " U " | tail -5
                 U tcsetattr@@GLIBC_2.2.5
                 U time@@GLIBC_2.2.5
                 U tolower@@GLIBC_2.2.5
                 U vfprintf@@GLIBC_2.2.5
                 U write@@GLIBC_2.2.5
```

- V
  - 自分が確認した限りだとlibc.soしかこのシンボルが発見されなかった
```
$ nm --debug-syms /lib64/libc.so.6 | grep -i " V "
00000000003bea20 V __after_morecore_hook
00000000003bea30 V __free_hook
00000000003bc740 V __malloc_hook
00000000003bea40 V __malloc_initialize_hook
00000000003bc720 V __memalign_hook
00000000003bc730 V __realloc_hook
                 v _dl_starting_up@@GLIBC_PRIVATE
00000000003bf4a8 V _environ
00000000003bee10 V daylight
00000000003bf4a8 V environ
00000000003bd018 V program_invocation_name
00000000003bd010 V program_invocation_short_name
00000000003bee00 V timezone
00000000003bd000 V tzname
```
上記でglibc/stdlib/errno.hには以下のように定義されている
```
// glibc/stdlib/errno.h
extern char *program_invocation_name;
extern char *program_invocation_short_name;
```

- W
  - opensslをデバッグオプション付きでビルドしたときのsoでw(小文字)が次のように表示された
```
$ nm --debug-syms /opt/openssl-1.0.2m/lib/libssl.so | grep -i " W "
                 w _ITM_deregisterTMCloneTable
                 w _ITM_registerTMCloneTable
                 w _Jv_RegisterClasses
                 w __cxa_finalize@@GLIBC_2.2.5
                 w __gmon_start__
```
  - W(大文字)シンボルはlibc.soを見ると多く使われているようだ。
    - 例えば、__ctype_get_mb_cur_maxの定義を見ると次の通り
    - https://github.com/lattera/glibc/blob/a2f34833b1042d5d8eeb263b4cf4caaea138c4ad/locale/mb_cur_max.c#L27-L32
```
$ nm --debug-syms /lib64/libc.so.6 | grep -i " W "
00000000000bf4f0 W _Exit
00000000000517a0 W _IO_fprintf
00000000000e9e80 W __close
00000000000f9060 W __connect
000000000002d640 W __ctype_get_mb_cur_max
00000000000e9c20 W __fcntl
000000000006c130 W __getdelim
000000000002e5c0 W __isascii_l
0000000000038970 W __libc_secure_getenv
00000000000f8370 W __lseek
00000000000bf180 W __nanosleep
00000000000e9590 W __open
00000000000e9590 W __open64
00000000000eda10 W __poll
00000000000e7f90 W __pread64
00000000000e7ff0 W __pwrite64
00000000000e97d0 W __read
0000000000038970 W __secure_getenv@GLIBC_2.2.5
```

- ?やハイフンのシンボルについても未確認

