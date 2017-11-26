# 概要
nmコマンドは与えられたオブジェクトファイル中に存在するシンボルをリストします。
シンボルリストの意味やその理解についても言及しています。

# 詳細

### 共有ライブラリの作成方法と確認方法
- 共有ライブラリの作成方法
  - 次のようにすると、test1.oとtest2.oの静的共有ライブラリ(libcustomize.so)が作成される。
```
$ gcc -shared -o libcustomize.so  test1.o test2.o
※一般的には、拡張子がso(shared object)ファイルは慣用的にlibname.so.x.yと書かれる。xは共有ライブラリのmajor番号、yはminor番号表す。
soファイルはcygwinなどにおけるdllと同じ働きをする。
```

- 共有ライブラリの確認方法
次のようにすればよい
```
$ nm libname.so
```

なお、C++の場合にはマングリングされていて読みにくいのでdemangleオプションを付与するとよい。
```
$ nm --demangle libname.so
```

または以下のようにc++filtコマンドを利用することも可能
```
$ nm -o libname.so | c++filt
```

シンボルがあるかどうかはfileコマンドで確認することができる「not stripped」や「stripped」といった情報が表示される。

### オブジェクトファイルのシンボルを確認する
以下のようなhello.cをオブジェクトファイルにします。
```
#include
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

