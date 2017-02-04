# cscopeについて
cscopeはC, C++, JAVAなどのソースコードを読んでいく際のタグジャンプなどに非常に役立つツールです。  
上記以外の言語の場合にはctags, globalなどの別のツールの方が適しているかもしれません。自分はPHPはGLOBALで、perl, Javascript, python, rubyなどはctagsを使っています。

# 内容

### セットアップ

デフォルトだとvimでタグジャンプしないので設定ファイルを配置します。

デフォルトだとvimからcscope設定が有効にならないので以下から$HOME/.vim/plugin/cscope_map.vimなどに以下のダウンロードしたものを配置します。
- http://cscope.sourceforge.net/cscope_maps.vim

上記が取得できなければ、$HOME/.vimrcに以下を追記します。
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

### cscopeを使ってみる

cscopeを利用するためにはまずはインデックスを生成する必要があります。
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

```
c 	その関数を呼んでいる関数の検索
d 	その関数によって呼ばれている関数の検索
e 	egrepパターンの検索
f 	ファイルの検索
g 	定義の検索
i 	そのファイルをインクルードしているファイルの検索
s 	そのCシンボルの検索
t 	そのテキスト文字列の検索
```

先ほどのコマンドは以下のように短縮可能である。
```
:cs f g FILE
```

これらのコマンドは以下のcscope_map.vimを導入することでコマンド入力を短縮化することができる。

##############################################################
### cscopeとvimを連携させる
##############################################################
~/.vim/plugin/にcscope_map.vimを配置する。   
cscope_map.vimは下記に存在する。
```
	http://cscope.sourceforge.net/cscope_maps.vim
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


(参考) http://sios-oss.blogspot.jp/2012/01/cscope-vim.html

### JAVAやC++でcscopeを利用する。
デフォルトではC, lex, and yacc files (.c, .h, .l, .y)のファイルしかパースしてくれない。
つまりC++でcppを利用している場合やJAVAの拡張子.javaなどはパースしてくれません。
まずはcscope.filesを作成してから「cscope -R -b」などのデータベース生成コマンドを実行する必要があります。

- C++の場合の例
```
$ find . -name '*.cpp' -o -name '*.c' -o -name '*.h' -o -name '*.hpp' > cscope.files
$ cscope -R -b
```
- JAVAの場合の例
```
$find . -name '*.java' > cscope.files
$ cscope -R -b
```

- 参考
 - http://cscope.sourceforge.net/cscope_vim_tutorial.html


### Linux Kernelなどで利用する。
以下のドキュメントを参考にするとよい。
- Using Cscope on large projects (example: the Linux kernel)
 - http://cscope.sourceforge.net/large_projects.html

一言で表すとcscope.filesの対象を絞ってからデータベースを生成しろよということ。

### CSCOPEのデータベースの場所をカレントディレクトリ以外の場所に設定する。
CSCOPE_DBという環境変数に設定するとカレントディレクトリ以外の場所に設定することができるようだ。
```
$ cd /foo
$ cscope -R -b
$ CSCOPE_DB=/foo/cscope.out; export CSCOPE_DB   
```

### cscopeをインタラクティブモードで開く
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

### vimのプラグイン
- 現在のファイルから即座に探す仕組みを提供してくれるようだ
- - https://github.com/vim-scripts/cscope.vim

# 参考
- The Vim/Cscope tutorial
 - http://cscope.sourceforge.net/cscope_vim_tutorial.html
- cscope Manpage
 - http://cscope.sourceforge.net/cscope_man_page.html
- How to use cscope?
 - http://stackoverflow.com/questions/3828157/how-to-use-cscope
- if_cscop - Vim日本語ドキュメント(Vimバージョン8.0)
 - http://vim-jp.org/vimdoc-ja/if_cscop.html
