
########################################################################
基本操作
########################################################################
■コアが生成されない場合
ulimitコマンド設定を見直す必要があります。
$ ulimit -c              // 確認コマンド
$ ulimit -c unlimited    // 無制限に変更

■コンパイルオプションについて
-gオプションを付与してコンパイルすること。
これをしないとgdbからブレークポイントを設定しても認識されないようです。
＄gcc -g <source>

■起動中プロセスのコアを取得する。
gcoreコマンドにプロセスIDを指定すれば生成することができる
$ sudo gcore 2567
[sudo] password for tsuyoshi: 
[Thread debugging using libthread_db enabled]
Using host libthread_db library "/lib64/libthread_db.so.1".
0x00007f3325b03e47 in accept4 () from /lib64/libc.so.6
Saved corefile core.2567
$ ls core.2567
$ sudo gdb /usr/local/bin/httpd core.2567

■テキストユーザインターフェースモード
あまりよくわかっていないが
$ gdb -tui
とするとテキストユーザーインターフェースを表示してくれるようです。

■プログラムを進める
continue: 
next:     次の関数を実行する
step:     関数の中を1行ずつ実行する
stepi:    アセンブリレベルで１つずつ実行を行う

nextやstepを一気に100回実行したいと行った場合には
n 100
s 100
とすればよい

■いじっている周辺のソースコードを取得
(gdb) list
109	        core_dir_config *d;
110	        d = ap_get_module_config(r->per_dir_config, &core_module);
111	        if (d->allow_encoded_slashes) {
112	            access_status = ap_unescape_url_keep2f_ex(r->parsed_uri.path, d->decode_encoded_slashes);
113	        }
114	        else {
115	            access_status = ap_unescape_url(r->parsed_uri.path);
116	        }
117	        if (access_status) {
118	            if (access_status == HTTP_NOT_FOUND) {

■起動中のプロセスにgdbからアタッチする
$ ps auxww | grep -i httpd
$ sudo gdb /usr/local/apache2/bin/httpd
(gdb) attach <pid>
// 何かをする
(gdb) detach          // デバッグ終了したらデタッチします。

attachした状態にてrunやquitを実行するとプロセスが停止してしまうらしいので注意が必要とのことです。

(参考)実行中のmemcachedプロセスをGDBでdebugする方法 
http://kotakanbe.blogspot.jp/2011/02/memcachedgdbdebug.html

■変数の型を取得する
(gdb) whatis *d
type = int

■print書式
(gdb) p 変数           // (例): p str
(gdb) p *ポインタ変数   // (例): p *r
(gdb) p &アドレス変数   // (例): p &r

■変数の値を調べる
(gdb) p counter        // 10進数
$1 = 1024
(gdb) p/o counter      // 8進数
$2 = 02000
(gdb) p/x counter      // 16進数
$3 = 0x400
(gdb) p/t counter      // 2進数
$4 = 10000000000
(gdb) p/a counter      // アドレス
$5 = 0x400
(gdb) p/c counter      // 文字表示
$6 = 0 '¥000'
(gdb) p/d counter      // 符号付き10進数
$7 = 1024
(gdb) p/u counter      // 符号無し10真数
$8 = 1024
(gdb) p &counter
$9 = (int *) 0x7fffffffe218
(gdb) p *counter
Cannot access memory at address 0x400

■ブレークポイントを設定する
(gdb) b 行番号             // 例: b 16
(gdb) b 関数名             // 例: b log4cpp::StringUtil::vform
(gdb) b ファイル名:行番号   // 例: b test.cc:207
(gdb) b ファイル名:関数名   // 例: b http_request.c:ap_internal_request
(gdb) b +オフセット
(gdb) b -オフセット
(gdb) b *アドレス         // 例:  b *0x00007ffff7dc0a0e

■環境変数を設定する
(gdb) set environment LD_LIBRARY_PATH=/usr/lib/debug

########################################################################
マニアック操作
########################################################################
■逆アセンブラを行う
(gdb) disassemble
Dump of assembler code for function main:
   0x00000000004255de <+0>:	push   %rbp
   0x00000000004255df <+1>:	mov    %rsp,%rbp
   0x00000000004255e2 <+4>:	sub    $0xc0,%rsp
   0x00000000004255e9 <+11>:	mov    %edi,-0xa4(%rbp)
   0x00000000004255ef <+17>:	mov    %rsi,-0xb0(%rbp)
   0x00000000004255f6 <+24>:	movl   $0x0,-0x4(%rbp)
   0x00000000004255fd <+31>:	movq   $0x489da3,-0x10(%rbp)
   0x0000000000425605 <+39>:	movq   $0x489db3,-0x18(%rbp)
   0x000000000042560d <+47>:	movq   $0x0,-0x20(%rbp)
   0x0000000000425615 <+55>:	lea    -0xb0(%rbp),%rdx
   0x000000000042561c <+62>:	lea    -0xa4(%rbp),%rax
   0x0000000000425623 <+69>:	mov    %rdx,%rsi
   0x0000000000425626 <+72>:	mov    %rax,%rdi
   0x0000000000425629 <+75>:	callq  0x425038 <init_process>
   0x000000000042562e <+80>:	mov    %rax,-0x30(%rbp)

以下のように特定の場所でブレークポイントを設定などもできます。
   break *0x0000000000425629

########################################################################
info関連
########################################################################
■info
引数無しでinfoを実行すればOKです。
(gdb) info
List of info subcommands:

info address -- Describe where symbol SYM is stored
info all-registers -- List of all registers and their contents
info args -- Argument variables of current stack frame
info auto-load -- Print current status of auto-loaded files
info auto-load-scripts -- Print the list of automatically loaded Python scripts
info auxv -- Display the inferior's auxiliary vector
-- snip --

■設定してあるブレークポイントを取得する
(gdb) info breakpoints
Num     Type           Disp Enb Address            What
1       breakpoint     keep y   0x000000000043989d in ap_process_request_internal at request.c:104
	breakpoint already hit 1 time


■プロセス情報を取得する
(gdb) info proc
process 18060
cmdline = '/usr/local/apache2.2/bin/httpd'
cwd = '/usr/local/apache2.2/bin'
exe = '/usr/local/apache2.2/bin/httpd'

■共有ライブラリ一覧を取得する
(gdb) info sharedlibrary
From                To                  Syms Read   Shared Object Library
0x0000003d54200b20  0x0000003d5421a2e9  Yes (*)     /lib64/ld-linux-x86-64.so.2
0x0000003d556055f0  0x0000003d5566ca0c  Yes (*)     /lib64/libm.so.6
0x00007ffff7dcf820  0x00007ffff7de31bc  Yes (*)     /lib64/libaprutil-1.so.0
0x0000003a1f200dc0  0x0000003a1f205cac  Yes (*)     /lib64/libcrypt.so.1
0x0000003a1ce03dd0  0x0000003a1ce1cccc  Yes (*)     /lib64/libexpat.so.1
0x0000003d5fe23ae0  0x0000003d5ff45db8  Yes (*)     /lib64/libdb-4.8.so
0x00007ffff7ba0340  0x00007ffff7bba1ac  Yes (*)     /lib64/libapr-1.so.0
0x0000003d54a05790  0x0000003d54a10494  Yes (*)     /lib64/libpthread.so.0
0x0000003d54e00ea0  0x0000003d54e019e0  Yes (*)     /lib64/libdl.so.2
0x0000003d5461ef60  0x0000003d5475f7a0  Yes (*)     /lib64/libc.so.6
0x0000003d5fa016d0  0x0000003d5fa02d58  Yes (*)     /lib64/libuuid.so.1
0x0000003a1f603740  0x0000003a1f64a530  Yes (*)     /lib64/libfreebl3.so
0x00007ffff79841b0  0x00007ffff798b67c  Yes (*)     /lib64/libnss_files.so.2
(*): Shared library is missing debugging information.

■関数一覧を取得する
ファイルごとに出力してくれるみたいです。
All defined functions:

File /home/tsuyoshi/httpd/httpd-2.2.27/server/buildmark.c:
const char *ap_get_server_built(void);

File vhost.c:
void ap_fini_vhost_config(apr_pool_t *, server_rec *);
void ap_init_vhost_config(apr_pool_t *);
int ap_matches_request_vhost(request_rec *, const char *, apr_port_t);
const char *ap_parse_vhost_addrs(apr_pool_t *, const char *, server_rec *);
const char *ap_set_name_virtual_host(cmd_parms *, void *, const char *);
void ap_update_vhost_from_headers(request_rec *);
void ap_update_vhost_given_ip(conn_rec *);
int ap_vhost_iterate_given_conn(conn_rec *, ap_vhost_iterate_conn_cb, void *);
static int add_name_vhost_config(apr_pool_t *, server_rec *, server_rec *, server_addr_rec *, ipaddr_chain *);
static void check_hostalias(request_rec *);
static void check_serverpath(request_rec *);
static void dump_a_vhost(apr_file_t *, ipaddr_chain *);
static void dump_vhost_config(apr_file_t *);
static ipaddr_chain *find_default_server(apr_port_t);
static ipaddr_chain *find_ipaddr(apr_sockaddr_t *);
static void fix_hostname(request_rec *);
static const char *get_addresses(apr_pool_t *, const char *, server_addr_rec ***, apr_port_t);
static unsigned int hash_addr(struct apr_sockaddr_t *);
static unsigned int hash_inaddr(unsigned int);
static int matches_aliases(server_rec *, const char *);
static ipaddr_chain *new_ipaddr_chain(apr_pool_t *, server_rec *, server_addr_rec *);
static name_chain *new_name_chain(apr_pool_t *, server_rec *, server_addr_rec *);
static void remove_unused_name_vhosts(server_rec *, ipaddr_chain **);

File util_pcre.c:
int ap_regcomp(ap_regex_t *, const char *, int);
apr_size_t ap_regerror(int, const ap_regex_t *, char *, apr_size_t);
int ap_regexec(const ap_regex_t *, const char *, apr_size_t, ap_regmatch_t *, int);
-- snip --


■バックとレースを取得する
btとbt fullがあります。btの方が簡易版です。
(gdb) bt
#0  ap_process_request_internal (r=0x7afbf0) at request.c:104
#1  0x00000000004620d6 in ap_process_request (r=0x7afbf0) at http_request.c:280
#2  0x000000000045efd3 in ap_process_http_connection (c=0x7abdc0) at http_core.c:190
#3  0x0000000000449395 in ap_run_process_connection (c=0x7abdc0) at connection.c:43
#4  0x000000000044982b in ap_process_connection (c=0x7abdc0, csd=0x7abbd0) at connection.c:190
#5  0x000000000047d13e in child_main (child_num_arg=0) at prefork.c:667
#6  0x000000000047d235 in make_child (s=0x6be148, slot=0) at prefork.c:712
#7  0x000000000047d7ed in ap_mpm_run (_pconf=0x6b9138, plog=0x6fb348, s=0x6be148) at prefork.c:988
#8  0x00000000004260bf in main (argc=2, argv=0x7fffffffe4e8) at main.c:753

もっと詳細を取得したい場合にはfullを付加します。
(gdb) bt full
#0  ap_process_request_internal (r=0x7afbf0) at request.c:104
        file_req = -1
        access_status = 32767
#1  0x00000000004620d6 in ap_process_request (r=0x7afbf0) at http_request.c:280
        access_status = -1
#2  0x000000000045efd3 in ap_process_http_connection (c=0x7abdc0) at http_core.c:190
        r = 0x7afbf0
        csd = 0x0
#3  0x0000000000449395 in ap_run_process_connection (c=0x7abdc0) at connection.c:43
        pHook = 0x6e6f08
        n = 0
        rv = -1
#4  0x000000000044982b in ap_process_connection (c=0x7abdc0, csd=0x7abbd0) at connection.c:190
        rc = -2
#5  0x000000000047d13e in child_main (child_num_arg=0) at prefork.c:667
        current_conn = 0x7abdc0
        csd = 0x7abbd0
        ptrans = 0x7abb58
        allocator = 0x7a9a50
        status = 0
        i = -1
        lr = 0x6b7b70
        pollset = 0x7a9bc8
        sbh = 0x7a9bc0
        bucket_alloc = 0x7adb68
        last_poll_idx = 0
#6  0x000000000047d235 in make_child (s=0x6be148, slot=0) at prefork.c:712
        pid = 0
#7  0x000000000047d7ed in ap_mpm_run (_pconf=0x6b9138, plog=0x6fb348, s=0x6be148) at prefork.c:988
        index = 0
        remaining_children_to_start = 0
        rv = 0
#8  0x00000000004260bf in main (argc=2, argv=0x7fffffffe4e8) at main.c:753
        c = 88 'X'
        configtestonly = 0

■レジスタ情報を取得する
(gdb) info registers
rax            0x7afbf0	8059888
rbx            0x0	0
rcx            0x0	0
rdx            0x0	0
rsi            0x0	0
rdi            0x7afbf0	8059888
rbp            0x7fffffffe400	0x7fffffffe400
rsp            0x7fffffffe340	0x7fffffffe340
r8             0x7afe70	8060528
r9             0x7afe80	8060544
r10            0x7afbf0	8059888
r11            0x7ffff7ba40f0	140737349566704
r12            0x424c90	4344976
r13            0x7fffffffe4e0	140737488348384
r14            0x0	0
r15            0x0	0
rip            0x4260bf	0x4260bf <main+2785>
eflags         0x202	[ IF ]
cs             0x33	51
ss             0x2b	43
ds             0x0	0
es             0x0	0
fs             0x0	0
gs             0x0	0

各レジスタの値は$を付加することでprintで閲覧することができるようです。
(gdb) print $rax
$1 = 140737488347680



