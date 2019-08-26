# cscopeについて
cscopeはC, C++, JAVA, PHP4のソースコードを読んでいく際のタグジャンプなどに非常に役立つツールです。  
上記以外の言語の場合にはctags, globalなどの別のツールの方が適しているかもしれません。自分はPHPはGLOBALで、perl, Javascript, python, rubyなどはctagsを使っています。

迷った場合のドキュメントとしてはこちらを参照すると良いでしょう。
- http://vimdoc.sourceforge.net/htmldoc/if_cscop.html

# 内容

## セットアップ

デフォルトだとvimでタグジャンプしないので設定ファイルを配置します。

デフォルトだとvimからcscope設定が有効にならないので以下から$HOME/.vim/plugin/cscope_map.vimなどに以下のダウンロードしたものを配置します。
```
$ cd $HOME/.vim/plugin/
$ wget http://cscope.sourceforge.net/cscope_maps.vim
```

上記が取得できなかったり面倒であれば、$HOME/.vimrcに以下を追記でも大丈夫です。
```
if has("cscope")
    set cscopetag
    set csto=0
"    if filereadable("cscope.out")
"        cs add cscope.out  
"    elseif $CSCOPE_DB != ""
"        cs add $CSCOPE_DB
"    endif
    set cscopeverbose  

    nmap <C-\>s :cs find s <C-R>=expand("<cword>")<CR><CR>  
    nmap <C-\>g :cs find g <C-R>=expand("<cword>")<CR><CR>  
    nmap <C-\>c :cs find c <C-R>=expand("<cword>")<CR><CR>  
    nmap <C-\>t :cs find t <C-R>=expand("<cword>")<CR><CR>  
    nmap <C-\>e :cs find e <C-R>=expand("<cword>")<CR><CR>  
    nmap <C-\>f :cs find f <C-R>=expand("<cfile>")<CR><CR>  
    nmap <C-\>i :cs find i ^<C-R>=expand("<cfile>")<CR>$<CR>
    nmap <C-\>d :cs find d <C-R>=expand("<cword>")<CR><CR>  

    nmap <C-@>s :scs find s <C-R>=expand("<cword>")<CR><CR> 
    nmap <C-@>g :scs find g <C-R>=expand("<cword>")<CR><CR> 
    nmap <C-@>c :scs find c <C-R>=expand("<cword>")<CR><CR> 
    nmap <C-@>t :scs find t <C-R>=expand("<cword>")<CR><CR> 
    nmap <C-@>e :scs find e <C-R>=expand("<cword>")<CR><CR> 
    nmap <C-@>f :scs find f <C-R>=expand("<cfile>")<CR><CR>
    nmap <C-@>i :scs find i ^<C-R>=expand("<cfile>")<CR>$<CR>
    nmap <C-@>d :scs find d <C-R>=expand("<cword>")<CR><CR>

    nmap <C-@><C-@>s :vert scs find s <C-R>=expand("<cword>")<CR><CR>
    nmap <C-@><C-@>g :vert scs find g <C-R>=expand("<cword>")<CR><CR>
    nmap <C-@><C-@>c :vert scs find c <C-R>=expand("<cword>")<CR><CR>
    nmap <C-@><C-@>t :vert scs find t <C-R>=expand("<cword>")<CR><CR>
    nmap <C-@><C-@>e :vert scs find e <C-R>=expand("<cword>")<CR><CR>
    nmap <C-@><C-@>f :vert scs find f <C-R>=expand("<cfile>")<CR><CR>
    nmap <C-@><C-@>i :vert scs find i ^<C-R>=expand("<cfile>")<CR>$<CR>
    nmap <C-@><C-@>d :vert scs find d <C-R>=expand("<cword>")<CR><CR>
endif
```
これでvimからcscopeが簡単に利用できるようになりました。

## cscopeを使ってみる

cscopeを利用するためにはまずはインデックスを生成する必要があります。
Rは再帰的に生成して、bはcscope db(cscope.out)を作成したらインタラクティブモードとせずに即時終了させることを意味する。
```
$ cd <インデックスを作成したいディレクトリ>
$ cscope -R -b
```

vimを開いたら以下のようにしてインデックスを利用できるようになる。
```
:cscope add /usr/src/cscope.out
```

 例えば、FILEの定義を調べるには以下のコマンドを実行する
```
:cscope find global FILE
```

それぞれの意味は次の通りです。
```
s 	そのCシンボルの検索
g 	定義の検索
c 	その関数を呼んでいる関数の検索
t 	そのテキスト文字列の検索
e 	egrepパターンの検索
f 	ファイルの検索
i 	そのファイルをインクルードしているファイルの検索
d 	その関数によって呼ばれている関数の検索
```

先ほどのコマンドは以下のように短縮可能です。
```
:cs f g FILE
```

これらのコマンドはセットアップで説明したcscope_map.vimを導入することでコマンド入力を短縮化することができます。

## cscopeとvimを連携させる
~/.vim/plugin/にcscope_map.vimを配置する。cscope_map.vimは下記に存在する。
```
$ wget http://cscope.sourceforge.net/cscope_maps.vim
```

データベースが重複するみたいなエラーが万が一表示されたら cs add の行をコメントアウトすれば良い。

あとは以下のキーバインドで連携することができます。   
例えば、下記の記述で CTRL+\ s はコントロールキーと "\" を同時にタイプし、続けて "s" をタイプすることを示します。

```
CTRL+\ s : C シンボルの検索
CTRL+\ g : グローバルな定義の検索
CTRL+\ c : 呼び出す関数を検索
CTRL+\ t : この文字列を検索
CTRL+\ e : egrep パターンを検索
CTRL+\ f : ファイルを検索
CTRL+\ i : include しているファイルを検索
CTRL+\ d : 呼ばれる関数を検索 
```

なお、別画面遷移後に元の画面に戻りたい場合には
```
CTRL + t
```
を押下すればよい。

また、このCtrl + Tで戻って来た後に先ほどの場所に戻りたい場合には
```
Ctrl + i
```
を押下すればよい
この辺の移動方法は重要なので覚えておくこと


(参考) http://sios-oss.blogspot.jp/2012/01/cscope-vim.html


## JAVAやC++でcscopeを利用する。
デフォルトではC, lex, and yacc files (.c, .h, .l, .y)のファイルしかパースしてくれないという問題があります。
つまり、C++でcppを利用している場合やJAVAの拡張子.javaなどはパースしてくれません。
まずはcscope.filesを作成してから「cscope -R -b」などのデータベース生成コマンドを実行する必要があります。

- C++の場合の例
```
$ find -L . -name '*.cpp' -o -name '*.c' -o -name '*.cc' -o -name '*.cxx' -o -name '*.cp' -o -name '*.c++' -o -name '*.h' -o -name '*.hpp' -o -name '*.hxx' -o -name '*.hh' -o -name '*.hp' -o -name '*.h++' > cscope.files
$ cscope -R -b
```
- JAVAの場合の例
```
$find -L . -name '*.java' > cscope.files
$ cscope -R -b
```

- 参考
  - http://cscope.sourceforge.net/cscope_vim_tutorial.html


## Linux Kernelなどで利用する。
以下のドキュメントを参考にするとよい。
- Using Cscope on large projects (example: the Linux kernel)
  - http://cscope.sourceforge.net/large_projects.html

一言で表すとcscope.filesの対象を絞ってからデータベースを生成しろよということ。

## CSCOPEのデータベースの場所をカレントディレクトリ以外の場所に設定する。
CSCOPE_DBという環境変数に設定するとカレントディレクトリ以外の場所に設定することができるようだ。
```
$ cd /foo
$ cscope -R -b
$ CSCOPE_DB=/foo/cscope.out; export CSCOPE_DB   
```

## cscopeデータベース、tagsデータベースの優先について
```
:set csto=0          // 先にcscopeデータベースが検索され、見つからなければtagsが読まれる。デフォルトはこれ。
:set csto=1          // cscopeデータベースの前にtagsが検索される
```

## cscopeプログラムの場所を設定する
自身でコンパイルしたcscopeを使いたい場合などに設定します。
```
:set csprg=/usr/local/bin/cscope
```

## vimで現在使われているcscope.outを表示する。
vimで「:cs show」と入力すると次の情報を画面下部に表示する。
```
 # pid    データベース名                      prepend パス
 0 3522   /home/tsuyoshi/trafficserver_tsuyopon/cscope.out  <none>
```

## cscopeをインタラクティブモードで開く
cscopeを引数なしで実行すると次の画面が開きます。
```
$ cscope
Find this C symbol:  <- (1)
Find this global definition: <- (2)
Find functions called by this function: <- (3)
Find functions calling this function: <- (4)
Find this text string: <- (5)
Change this text string: <- (6)
Find this egrep pattern: <- (7)
Find this file: <- (8)
Find files #including this file: <- (9)
Find assignments to this symbol: <- (10)
```

cscopeのインテラクティブモードを中止する場合には「Ctrl-d」を押下します。(重要なので覚えておく)


vim上から「:cs」と入力すると次のようにfindのヘルプを表示してくれます。上記の英語は下記と照らし合わせると良いでしょう。
```
cscopeコマンド:                                                                                                                                    
add  : 新データベースを追加           (使用法: add file|dir [pre-path] [flags])
find : パターンのクエリーを追加       (使用法: find c|d|e|f|g|i|s|t name)
       c: この関数を呼んでいる関数を探す
       d: この関数から呼んでいる関数を探す
       e: このegrepパターンを探す
       f: このファイルを探す
       g: この定義を探す
       i: このファイルを#includeしているファイルを探す
       s: このCシンボルを探す
       t: このテキスト文字列を探す
help : このメッセージを表示する       (使用法: help)
kill : 接続を終了する                 (使用法: kill #)
reset: 全ての接続を再初期化する       (使用法: reset)
show : 接続を表示する                 (使用法: show)
```


いろいろ使ってみる事にします。
trafficserverのソースコードを使って試してみる。

** TBD **


- (1)
PluginRegInfoというメソッドがあるので「PluginRegInfo」を入れてみると
```
C symbol: PluginRegInfo

  File     Function Line
  0 Plugin.h <global> 38 struct PluginRegInfo {
  1 Plugin.h <global> 39 PluginRegInfo();
  2 Plugin.h <global> 40 ~PluginRegInfo();
  3 Plugin.h <global> 50 LINK(PluginRegInfo, link);
  4 Plugin.h <global> 54 extern DLL<PluginRegInfo> plugin_reg_list;
  5 Plugin.h <global> 55 extern PluginRegInfo *plugin_reg_current;
```

- (2)
"PluginRegInfo"という文字列で検索してみると次のL38にカーソルがあたります(候補が１つしかないので一気に移動する)
```
// proxy/Plugin.h
     38 struct PluginRegInfo {
     39   PluginRegInfo();
     40   ~PluginRegInfo();
     41 
     42   bool plugin_registered;
     43   char *plugin_path;
     44 
     45   PluginSDKVersion sdk_version;
     46   char *plugin_name;
     47   char *vendor_name;
     48   char *support_email;
     49 
```

** TBD **


- (7)
```
Egrep pattern: PluginRegInfo

  File     Line
  0 Plugin.h 38 struct PluginRegInfo {
  1 Plugin.h 39 PluginRegInfo();
  2 Plugin.h 40 ~PluginRegInfo();
  3 Plugin.h 50 LINK(PluginRegInfo, link);
  4 Plugin.h 54 extern DLL<PluginRegInfo> plugin_reg_list;
  5 Plugin.h 55 extern PluginRegInfo *plugin_reg_current;
```

- (8)
"Proxy"と入れてエンターを押下するとProxyが含まれるファイル名を表示する。
```
File: Proxy

  File
0 iocore/eventsystem/I_ProxyAllocator.h
1 mgmt/ProxyConfig.h
2 proxy/ProxyClientSession.h
3 proxy/ReverseProxy.h
4 proxy/http/HttpProxyAPIEnums.h
5 proxy/http/HttpProxyServerMain.h
```

- (9)
"Proxy"と入れてエンターを押下すると「*Proxy*」というファイル名をincludeしている全ての候補が見つかる
```
Files #including this file: Proxy

  File                  Line
  0 P_SplitDNSProcessor.h 41 #include "ProxyConfig.h"
  1 I_Thread.h            68 #include "I_ProxyAllocator.h"
  2 P_SSLCertLookup.h     27 #include "ProxyConfig.h"
  3 P_SSLConfig.h         34 #include "ProxyConfig.h"
  4 IPAllow.h             38 #include "ProxyConfig.h"
  5 InkAPIInternal.h	36 #include "ProxyConfig.h"
  6 ParentSelection.h     35 #include "ProxyConfig.h"
  7 HttpCacheSM.h         38 #include "ProxyConfig.h"
  8 HttpClientSession.h   41 #include "ProxyClientSession.h"
  9 HttpConfig.h          46 #include "HttpProxyAPIEnums.h"
  a HttpConfig.h          47 #include "ProxyConfig.h"
  b HttpServerSession.h   50 #include "HttpProxyAPIEnums.h"
  c HttpTransact.h        38 #include "ProxyConfig.h"
  d RemapPlugins.h        38 #include "ReverseProxy.h"
  e RemapProcessor.h	33 #include "ReverseProxy.h"
  f Http2ClientSession.h  28 #include "ProxyClientSession.h"
  g LogConfig.h           30 #include "ProxyConfig.h"
```

### cscopeとvimとのマッピングのヘルプをみる
マッピング情報を見るためにはvimを開いて次のコマンドを入力します。
```
:help cscope-suggestions
```

cscopeのヘルプをみるだけなら次のようにすればいいみたいです。
```
:help cscope
```

## vimのプラグイン
- 現在のファイルから即座に探す仕組みを提供してくれるようだ
- - https://github.com/vim-scripts/cscope.vim

## 各種コマンドの使い方についての説明

### CTRL+\ g: 定義元を表示する。
最もよく使われるやつ。
使っている関数やマクロ、変数などにカーソルをあててCtrl+\ gを実行すると定義元に移動する。
あとでCTRL+\ s, CTRL+\ e,CTRL+\ tとの比較で比較して説明する。

### CTRL+\ c: 呼び出している関数を検索する
たとえば、次の関数のL2988のap_abort_on_oomの関数名にカーソルをあててCtrl+\ cを呼び出すと、
```
2988 AP_DECLARE(void) ap_abort_on_oom()            
2989 {                                             
2990     int written, count = strlen(oom_message); 
...
```

その関数を呼び出している箇所を表示します。
```
Cscope tag: ap_abort_on_oom
   #   line  filename / context / line
   1    272  httpd-2.4.23/server/main.c <<abort_on_oom>>
             ap_abort_on_oom();
   2    283  httpd-2.4.23/server/util.c <<AP_DECLARE>>
             ap_abort_on_oom();
   3    283  httpd-2.4.23/server/util.c <<ap_pregcomp>>
             ap_abort_on_oom();
   4   3008  httpd-2.4.23/server/util.c <<AP_DECLARE>>
             ap_abort_on_oom();
```

### CTRL+\ f: ファイルの検索を行う
たとえば、次のような行で「httpd.h」にカーソルを載せてCtrl+\ f を押下すると、
```
#include "httpd.h"
```

次のように引っかかったファイルを表示する。対象が１つしかなければそのファイルに直接移動する。
たとえば、httpd.hでは、次のようにphp_phttpd.hと部分マッチしたものも対象となっているようなので複数表示されるようだ。
```
Cscope tag: httpd.h
   #   line  filename / context / line
   1      1  httpd-2.4.23/include/httpd.h <<<unknown>>>
   2      1  php-5.6.25/sapi/phttpd/php_phttpd.h <<<unknown>>>
   3      1  php-5.6.25/sapi/thttpd/php_thttpd.h <<<unknown>>>
```

### CTRL+\ i: そのヘッダファイルを読み込んでいる箇所を探す。

たとえば、次のようなincludeの箇所の「ap_config.h」にカーソルを載せて、そこでCtrl+\ iを実行すると
```
#include "ap_config.h"
```

次のように他にもそのヘッダファイルを読み込んでいる箇所を表示してくれます。
```
Cscope tag: ^ap_config.h$
   #   line  filename / context / line
   1     29  httpd-2.4.23/include/ap_provider.h <<GLOBAL>>
             #include "ap_config.h"
   2     29  httpd-2.4.23/include/ap_regkey.h <<GLOBAL>>
             #include "ap_config.h"
   3     30  httpd-2.4.23/include/http_config.h <<GLOBAL>>
             #include "ap_config.h"
  (省略)
```

### CTRL+\ d: ある関数から呼ばれる関数を検索
これは、関数の中で呼び出している関数を検索するためのコマンドです。  
たとえば、次の関数がある場合「destroy_and_exit_process」の上にカーソルを載せてCtrl+\ dを押すと、
```
252 static void destroy_and_exit_process(process_rec *process,
253                                      int process_exit_value)
254 {
255     /*
256      * Sleep for TASK_SWITCH_SLEEP micro seconds to cause a task switch on
257      * OS layer and thus give possibly started piped loggers a chance to
258      * process their input. Otherwise it is possible that they get killed
259      * by us before they can do so. In this case maybe valueable log messages
260      * might get lost.
261      */
262     apr_sleep(TASK_SWITCH_SLEEP);
263     ap_main_state = AP_SQ_MS_EXITING;
264     apr_pool_destroy(process->pool); /* and destroy all descendent pools */
265     apr_terminate();
266     exit(process_exit_value);
267 }
```

その関数の中で呼び出している関数の一覧が表示される。つまり、上記でL262, L264, L265, L266にジャンプすることができます。
```
Cscope tag: destroy_and_exit_process
   #   line  filename / context / line
   1    262  httpd-2.4.23/server/main.c <<apr_sleep>>
             apr_sleep(TASK_SWITCH_SLEEP);
   2    264  httpd-2.4.23/server/main.c <<apr_pool_destroy>>
             apr_pool_destroy(process->pool);
   3    265  httpd-2.4.23/server/main.c <<apr_terminate>>
             apr_terminate();
   4    266  httpd-2.4.23/server/main.c <<exit>>
             exit(process_exit_value);
```

### Ctrl + g, Ctrl / + s, Ctrl / + e, Ctrl / + tの違い
g, s, e, tはわかりにくいので比較して確認することにする。

以下のapacheのコードのap_prelinked_modulesにカーソルを当ててコマンドを実行する。
```
 22 module *ap_prelinked_modules[] = {
 23   &core_module,
 24   &so_module,
 25   &http_module,
 26   &mpm_prefork_module,
 27   NULL
 28 };
```

gは定義元を表示する。定義元の候補は３箇所であることがわかる。
```
Cscope tag: ap_prelinked_modules
   #   line  filename / context / line
   1     22  httpd-2.4.23/modules.c <<ap_prelinked_modules>>
             module *ap_prelinked_modules[] = {
   2     47  httpd-2.4.23/os/netware/modules.c <<ap_prelinked_modules>>
             module *ap_prelinked_modules[] = {
   3     31  httpd-2.4.23/os/win32/modules.c <<ap_prelinked_modules>>
             AP_DECLARE_DATA module *ap_prelinked_modules[] = {
```

続いて、sはシンボルを表示する。  
後で説明するがeやtなどと異なってコメントは表示されないようだ。
```
Cscope tag: ap_prelinked_modules
   #   line  filename / context / line
   1    931  httpd-2.4.23/include/http_config.h <<GLOBAL>>
             AP_DECLARE_DATA extern module *ap_prelinked_modules[];
   2     22  httpd-2.4.23/modules.c <<GLOBAL>>
             module *ap_prelinked_modules[] = {
   3     47  httpd-2.4.23/os/netware/modules.c <<GLOBAL>>
             module *ap_prelinked_modules[] = {
   4     31  httpd-2.4.23/os/win32/modules.c <<GLOBAL>>
             AP_DECLARE_DATA module *ap_prelinked_modules[] = {
   5      5  httpd-2.4.23/server/export_vars.h <<GLOBAL>>
             ap_prelinked_modules
   6    511  httpd-2.4.23/server/config.c <<rebuild_conf_hash>>
             for (m = ap_prelinked_modules; *m != NULL; m++) {
   7    797  httpd-2.4.23/server/config.c <<ap_setup_prelinked_modules>>
             for (m = ap_prelinked_modules; *m != NULL; m++) {
   8    718  httpd-2.4.23/server/main.c <<main>>
             for (mod = ap_prelinked_modules; *mod != NULL; mod++) {
```

続いて、eやtは次のようになる。(いろいろためしたがeとtは候補が同じだった。おそらく対話モードでeのegrepはtよりもより高度な検索ができると思われる。)
eやtは単なるテキスト検索なので先ほどの場合と比べて1番のコメントまで候補に追加されていることが確認できる。
```
Cscope tag: ap_prelinked_modules
   #   line  filename / context / line
   1    929  httpd-2.4.23/include/http_config.h <<<unknown>>>
              * @var module *ap_prelinked_modules[]
   2    931  httpd-2.4.23/include/http_config.h <<<unknown>>>
             AP_DECLARE_DATA extern module *ap_prelinked_modules[];
   3     22  httpd-2.4.23/modules.c <<<unknown>>>
             module *ap_prelinked_modules[] = {
   4     47  httpd-2.4.23/os/netware/modules.c <<<unknown>>>
             module *ap_prelinked_modules[] = {
   5     31  httpd-2.4.23/os/win32/modules.c <<<unknown>>>
             AP_DECLARE_DATA module *ap_prelinked_modules[] = {
   6    511  httpd-2.4.23/server/config.c <<<unknown>>>
                     for (m = ap_prelinked_modules; *m != NULL; m++) {
   7    797  httpd-2.4.23/server/config.c <<<unknown>>>
                 for (m = ap_prelinked_modules; *m != NULL; m++) {
   8      5  httpd-2.4.23/server/export_vars.h <<<unknown>>>
             ap_prelinked_modules
   9    718  httpd-2.4.23/server/main.c <<<unknown>>>
                     for (mod = ap_prelinked_modules; *mod != NULL; mod++) {
```


## cscopeのオプションについて
cscopeのデータベースを生成するときのオプションはhelpで確認できる。
```
$ cscope --help
Usage: cscope [-bcCdehklLqRTuUvV] [-f file] [-F file] [-i file] [-I dir] [-s dir]
              [-p number] [-P path] [-[0-8] pattern] [source files]

-b            Build the cross-reference only.
-C            Ignore letter case when searching.
-c            Use only ASCII characters in the cross-ref file (don't compress).
-d            Do not update the cross-reference.
-e            Suppress the <Ctrl>-e command prompt between files.
-F symfile    Read symbol reference lines from symfile.
-f reffile    Use reffile as cross-ref file name instead of cscope.out.
-h            This help screen.
-I incdir     Look in incdir for any #include files.
-i namefile   Browse through files listed in namefile, instead of cscope.files
-k            Kernel Mode - don't use /usr/include for #include files.
-L            Do a single search with line-oriented output.
-l            Line-oriented interface.
-num pattern  Go to input field num (counting from 0) and find pattern.
-P path       Prepend path to relative file names in pre-built cross-ref file.
-p n          Display the last n file path components.
-q            Build an inverted index for quick symbol searching.
-R            Recurse directories for files.
-s dir        Look in dir for additional source  files.
-T            Use only the first eight characters to match against C symbols.
-U            Check file time stamps.
-u            Unconditionally build the cross-reference file.
-v            Be more verbose in line mode.
-V            Print the version number.

Please see the manpage for more information.
```

合わせてmanpageも参考のこと
- http://cscope.sourceforge.net/cscope_man_page.html


## Linuxでcsopeを使う
トップディレクトリで次のようにcscopeターゲットを実行すると良いらしい
```
$ ARCH=x86 make cscope
```
- https://stackoverflow.com/questions/22938266/linux-kernel-makefile-cscope-target?noredirect=1&lq=1

# 参考
- The Vim/Cscope tutorial
  - http://cscope.sourceforge.net/cscope_vim_tutorial.html
- cscope Manpage
  - http://cscope.sourceforge.net/cscope_man_page.html
- How to use cscope?
  - http://stackoverflow.com/questions/3828157/how-to-use-cscope
- if_cscop - Vim日本語ドキュメント(Vimバージョン8.0)
  - http://vim-jp.org/vimdoc-ja/if_cscop.html
  - https://github.com/vim-jp/vimdoc-ja-working/blob/master/doc/if_cscop.jax


# 確認したいこと
- リスト一覧からの検索
- autoを自動判別して、その定義に飛ぶ方法
- 同一ファイルの定義に飛ぶ方法
- ヘッダファイルの宣言から定義に移動する方法
