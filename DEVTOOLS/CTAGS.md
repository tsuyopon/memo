# ctagsについて
ctagsはデフォルトでインストールされていることが多く、非常に便利なタグジャンプの仕組みです。
C, C++, JavaなどはCscopeの方を自分は好みますが、それ以外のJavascript, Perl, Ruby, Go, PHP, Scala, Markdown, CSSなどはこのctagsで十分です。
なお、PHPやC++ではGLOBALも利用されるようですが、呼び出し元まで辿れるというのが利点となっているようです。

.ctagsファイルについてはdotfilesレポジトリに置いてあるので参考にすること

# 詳細

## セットアップ
### ソースコードからのインストール
```
$ mkdir -p $HOME/local
$ wget http://prdownloads.sourceforge.net/ctags/ctags-5.8.tar.gz
$ tar zxf ctags-5.8.tar.gz
$ cd ctags-5.8
$ ./configure --prefix=$HOME/local
$ make
$ sudo make install
```

あとはindex生成したいディレクトリに移動して-Rオプションを付与すれば良い。
```
$ ctags -R
```

以下のように含める・含めないの指定もできる
```
$ ctags -R --exclude=.git --exclude=log *
```

### 複数のディレクトリを指定してインデックスを作る場合
単純に後ろに複数指定すれば良いだけです。
```
$ ctags -R  path/dir1   path2/dir2
```

### MACの場合のセットアップ方法
MACの場合のセットアップは次を参照すること。ctagsは入っているが「ctags -R」のRオプションが解釈されない場合などは以下を参照すべし。
これはたいていのLinuxにインストールされる ctags は etags(Exuberant Ctags)で、多くの言語に対応している。しかし、Mac OSXに付属している ctags はBSD由来のもので、-Rオプションが使えなかったりする。
- https://gist.github.com/nazgob/1570678

基本的にはbrew install ctagsでインストールしてログインしなおせばOKです。

## キーバインドやコマンドなど
### キーバインドについて
以下のキーバインドは重要です。
```
Ctrl + ]    定義位置に移動する。
Ctrl + O    移動前の位置に戻る
Ctrl + I    Ctrl+Oを実行して移動前の位置に戻った後に、再度戻る
```

定義元も合わせてvimの水平タブで表示するには次のキーバインドを実行します。
```
Ctrl + W, Ctrl + ]      定義元を水平タブで合わせて開く
```

なお、標準ではありませんが、次を.vimrcに追加することによって
```
map <C-\> :tab split<CR>:exec("tag ".expand("<cword>"))<CR>
map <C-^> :vsp <CR>:exec("tag ".expand("<cword>"))<CR>
```

次のキーバインドが利用できるようになります。
```
Ctrl + \         新しいタブで定義を開く
Ctrl + ^         定義元を垂直タブで合わせて開く
```

- 参考
  - https://stackoverflow.com/questions/563616/vim-and-ctags-tips-and-tricks?rq=1

### vimのコマンド
```
:tselect 	現在のタグの一覧を表示
:tfirst 	（タグが重複している場合）最初のタグへ
:tn 	    （タグが重複している場合）次のタグへ
:tp 	    （タグが重複している場合）前のタグへ
:tlast 	    （タグが重複している場合） 最後のタグへ
:tags 	    移動経路を確認
:tag 	    タグリストの前方にジャンプ。(:3tagなども可)
:tag        [タグ名] 	指定したタグにジャンプ。(:taと同じ)
:ptag       [タグ名] 	[タグ名]の定義をプレビューウィンドウで開く。
```

### vimでtagsファイルを登録しておきたい場合
$HOME/.vimrcに次のような行を追加することでvimを開いた時にどのtagsファイルを使うのかを指定することができます。
```
set tags+=$HOME/tags
set tags+=$HOME/tags2
```

## .ctagsファイルについて
$HOME/.ctagsに配置するとindexを生成する際に参照するファイルが指定できる。
- https://github.com/grassdog/dotfiles/blob/6bd36bcb59b57eac28d618f76f21e83d4fc487a8/ctags
- https://gist.github.com/tim-smart/199338

javascriptの場合だとこの辺の説明が.ctags生成の理解に役立つ
- http://dance.computer.dance/posts/2015/04/using-ctags-on-modern-javascript.html

### JavaScript用の.ctags
先ほども示したこの辺の例が役に立ちそうだ。
- http://cortyuming.hateblo.jp/entry/2016/01/01/171216

上記サイトからの抜粋
```
--exclude=.git
--exclude=.hg
--exclude=log
--exclude=tmp
--exclude=node_modules

--languages=-javascript
--langdef=js
--langmap=js:.js
--langmap=js:+.jsx

--regex-js=/[ \t.]([A-Z][A-Z0-9._$]+)[ \t]*[=:][ \t]*([0-9"'\[\{]|null)/\1/n,constant/

--regex-js=/\.([A-Za-z0-9._$]+)[ \t]*=[ \t]*\{/\1/o,object/
--regex-js=/['"]*([A-Za-z0-9_$]+)['"]*[ \t]*:[ \t]*\{/\1/o,object/
--regex-js=/([A-Za-z0-9._$]+)\[["']([A-Za-z0-9_$]+)["']\][ \t]*=[ \t]*\{/\1\.\2/o,object/

--regex-js=/([A-Za-z0-9._$]+)[ \t]*=[ \t]*\(function\(\)/\1/c,class/
--regex-js=/['"]*([A-Za-z0-9_$]+)['"]*:[ \t]*\(function\(\)/\1/c,class/
--regex-js=/class[ \t]+([A-Za-z0-9._$]+)[ \t]*/\1/c,class/
--regex-js=/([A-Za-z$][A-Za-z0-9_$()]+)[ \t]*=[ \t]*[Rr]eact.createClass[ \t]*\(/\1/c,class/
--regex-js=/([A-Z][A-Za-z0-9_$]+)[ \t]*=[ \t]*[A-Za-z0-9_$]*[ \t]*[{(]/\1/c,class/
--regex-js=/([A-Z][A-Za-z0-9_$]+)[ \t]*:[ \t]*[A-Za-z0-9_$]*[ \t]*[{(]/\1/c,class/

--regex-js=/([A-Za-z$][A-Za-z0-9_$]+)[ \t]*=[ \t]*function[ \t]*\(/\1/f,function/

--regex-js=/(function)*[ \t]*([A-Za-z$_][A-Za-z0-9_$]+)[ \t]*\([^)]*\)[ \t]*\{/\2/f,function/
--regex-js=/['"]*([A-Za-z$][A-Za-z0-9_$]+)['"]*:[ \t]*function[ \t]*\(/\1/m,method/
--regex-js=/([A-Za-z0-9_$]+)\[["']([A-Za-z0-9_$]+)["']\][ \t]*=[ \t]*function[ \t]*\(/\2/m,method/
```

### go言語用の.ctags
.ctagsは以下を参考のこと
```
--langdef=Go
--langmap=Go:.go
--regex-Go=/func([ \t]+\([^)]+\))?[ \t]+([a-zA-Z0-9_]+)/\2/d,func/
--regex-Go=/var[ \t]+([a-zA-Z_][a-zA-Z0-9_]+)/\1/d,var/
--regex-Go=/type[ \t]+([a-zA-Z_][a-zA-Z0-9_]+)/\1/d,type/
```

goだとデフォルトでsyntax onじゃないっぽいので、vimrc設定も載せておく
- https://www.seeds-std.co.jp/seedsblog/2494.html

### Perl用の.ctags
```
--regex-perl=/with\s+([^;]+)\s*?;/\1/w,role,roles/
--regex-perl=/extends\s+['"]([^'"]+)['"]\s*?;/\1/e,extends/
--regex-perl=/use\s+base\s+['"]([^'"]+)['"]\s*?;/\1/e,extends/
--regex-perl=/use\s+parent\s+['"]([^'"]+)['"]\s*?;/\1/e,extends/
--regex-perl=/Mojo::Base\s+['"]([^'"]+)['"]\s*?;/\1/e,extends/
--regex-perl=/^\s*?use\s+([^;]+)\s*?;/\1/u,use,uses/
--regex-perl=/^\s*?require\s+((\w|\:)+)/\1/r,require,requires/
--regex-perl=/^\s*?has\s+['"]?(\w+)['"]?/\1/a,attribute,attributes/
--regex-perl=/^\s*?\*(\w+)\s*?=/\1/a,alias,aliases/
--regex-perl=/->helper\(\s?['"]?(\w+)['"]?/\1/h,helper,helpers/
--regex-perl=/^\s*?our\s*?[\$@%](\w+)/\1/o,our,ours/
--regex-perl=/^\=head1\s+(.+)/\1/p,pod,Plain Old Documentation/
--regex-perl=/^\=head2\s+(.+)/-- \1/p,pod,Plain Old Documentation/
--regex-perl=/^\=head[3-5]\s+(.+)/---- \1/p,pod,Plain Old Documentation/
--recurse=yes
--langmap=perl:+.pod
```


### 対応言語について
対応言語の表示
```
$ ctags --list-languages
Ant
Asm
Asp
Awk
Basic
BETA
C
C++
C#
Cobol
CSS
DosBatch
Eiffel
Erlang
Flex
Fortran
HTML
Java
JavaScript
Lisp
Lua
Make
MatLab
OCaml
Pascal
Perl
PHP
Python
REXX
Ruby
Scheme
Sh
SLang
SML
SQL
Tcl
Tex
Vera
Verilog
VHDL
Vim
YACC
```

種別の表示
```
$ ctags --list-kinds=JavaScript
f  functions
c  classes
m  methods
p  properties
v  global variables
```

タグを生成する言語を指定する
```
$ ctags --languages=PHP,JavaScript
```

### .ctags設定ファイルの読み込み順序
以下のサイトによると
- http://ctags.sourceforge.net/ctags.html

次の順番で読み込まれるらしい。つまりレポジトリ直下におくことによって、$HOME直下よりも優先されるようになるらしい
- /ctags.cnf (on MSDOS, MSWindows only)
- /etc/ctags.conf
- /usr/local/etc/ctags.conf
- $HOME/.ctags
- $HOME/ctags.cnf (on MSDOS, MSWindows only)
- .ctags
- ctags.cnf (on MSDOS, MSWindows only)

### ctags関連でよく使う設定について
- append=yes:    tagsがすでにあれば上書きではなく追加する
- recurse=yes:   配下ディレクトリを再帰的にタグ作成するかどうか。これがあればctagsコマンドに-Rが不要
- tags-relative: 作成されるtagsファイル内のキーワードのパスが相対パスになる。
- sort=yes:      作成されたキーワードをsortする

# 参考
- 公式ドキュメント
  - http://ctags.sourceforge.net/ctags.html
- vimを使っている人はみんなctagsで幸せになれる権利を持っている
  - http://wknar.hatenablog.com/entry/vim-ctags
- Exuberant Ctags and JavaScript
  - https://weblogs.asp.net/george_v_reilly/exuberant-ctags-and-javascript
- Recommended Vim plugins for JavaScript coding?
  - http://stackoverflow.com/questions/4777366/recommended-vim-plugins-for-javascript-coding?noredirect=1&lq=1
- exuberant ctags 日本語対応版
  - http://hp.vector.co.jp/authors/VA025040/ctags/
- Manpage of ctags
  - http://hp.vector.co.jp/authors/VA025040/ctags/ctags_j.html
- Stack Overflow: Vim and Ctags tips and tricks [closed]
  - https://stackoverflow.com/questions/563616/vim-and-ctags-tips-and-tricks?rq=1
