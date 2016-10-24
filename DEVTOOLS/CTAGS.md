# ctagsについて
rubyやjavascriptなどはcscope, globalなどではうまい具合に動かなったので、ctagsについてもまとめておく


# 詳細

## ソースコードからのインストール
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

以下のように含める・含めないの指定もできる
$ ctags -R --exclude=.git --exclude=log *
```

## MACの場合のセットアップ方法
MACの場合のセットアップは次を参照すること。ctagsは入っているが「ctags -R」のRオプションが解釈されない場合などは以下を参照すべし。
- https://gist.github.com/nazgob/1570678

## .ctagsファイルについて
$HOME/.ctagsに配置するとindexを生成する際に参照するファイルが指定できる。
- https://github.com/grassdog/dotfiles/blob/6bd36bcb59b57eac28d618f76f21e83d4fc487a8/ctags
- https://gist.github.com/tim-smart/199338

javascriptの場合だとこの辺の説明が.ctags生成の理解に役立つ
- http://dance.computer.dance/posts/2015/04/using-ctags-on-modern-javascript.html

# .ctags生成方法
先ほども示したこの辺の例が役に立ちそうだ。
- http://dance.computer.dance/posts/2015/04/using-ctags-on-modern-javascript.html

上記サイトからの抜粋
```
--languages=-javascript
--langdef=js
--langmap=js:.js
--langmap=js:+.jsx

//
// Constants
//

// A constant: AAA0_123 = { or AAA0_123: {
--regex-js=/[ \t.]([A-Z][A-Z0-9._$]+)[ \t]*[=:][ \t]*([0-9"'\[\{]|null)/\1/n,constant/

//
// Properties
//

// .name = {
--regex-js=/\.([A-Za-z0-9._$]+)[ \t]*=[ \t]*\{/\1/o,object/

// "name": {
--regex-js=/['"]*([A-Za-z0-9_$]+)['"]*[ \t]*:[ \t]*\{/\1/o,object/

// parent["name"] = {
--regex-js=/([A-Za-z0-9._$]+)\[["']([A-Za-z0-9_$]+)["']\][ \t]*=[ \t]*\{/\1\.\2/o,object/

//
// Classes
//

// name = (function()
--regex-js=/([A-Za-z0-9._$]+)[ \t]*=[ \t]*\(function\(\)/\1/c,class/

// "name": (function()
--regex-js=/['"]*([A-Za-z0-9_$]+)['"]*:[ \t]*\(function\(\)/\1/c,class/

// class ClassName
--regex-js=/class[ \t]+([A-Za-z0-9._$]+)[ \t]*/\1/c,class/

// ClassName = React.createClass
--regex-js=/([A-Za-z$][A-Za-z0-9_$()]+)[ \t]*=[ \t]*[Rr]eact.createClass[ \t]*\(/\1/c,class/

// Capitalised object: Name = whatever({
--regex-js=/([A-Z][A-Za-z0-9_$]+)[ \t]*=[ \t]*[A-Za-z0-9_$]*[ \t]*[{(]/\1/c,class/

// Capitalised object: Name: whatever({
--regex-js=/([A-Z][A-Za-z0-9_$]+)[ \t]*:[ \t]*[A-Za-z0-9_$]*[ \t]*[{(]/\1/c,class/

//
// Functions
//

// name = function(
--regex-js=/([A-Za-z$][A-Za-z0-9_$]+)[ \t]*=[ \t]*function[ \t]*\(/\1/f,function/

//
// Methods
//

// Class method or function (this matches too many things which I filter out separtely)
// name() {
--regex-js=/(function)*[ \t]*([A-Za-z$_][A-Za-z0-9_$]+)[ \t]*\([^)]*\)[ \t]*\{/\2/f,function/

// "name": function(
--regex-js=/['"]*([A-Za-z$][A-Za-z0-9_$]+)['"]*:[ \t]*function[ \t]*\(/\1/m,method/

// parent["name"] = function(
--regex-js=/([A-Za-z0-9_$]+)\[["']([A-Za-z0-9_$]+)["']\][ \t]*=[ \t]*function[ \t]*\(/\2/m,method/
```



## 対応言語について
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

# 参考
- 公式ドキュメント
 - http://ctags.sourceforge.net/ctags.html
- vimを使っている人はみんなctagsで幸せになれる権利を持っている
 - http://wknar.hatenablog.com/entry/vim-ctags
- Exuberant Ctags and JavaScript
 - https://weblogs.asp.net/george_v_reilly/exuberant-ctags-and-javascript
- Recommended Vim plugins for JavaScript coding?
 - http://stackoverflow.com/questions/4777366/recommended-vim-plugins-for-javascript-coding?noredirect=1&lq=1
