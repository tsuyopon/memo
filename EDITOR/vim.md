# 概要
vimについて


# ディレクトリ構成
```
├─ _vimrc もしくは .vimrc       vimエディタ設定ファイル（共通）
├─ _gvimrc もしくは .gvimrc     vimエディタ設定ファイル（GUI用）
├─ _viminfo                     履歴情報などがvimエディタによって格納される。環境移行時などには消してもほぼ問題ないファイル。
└─ vimfiles/                    vimエディタの設定ファイルディレクトリ
     ├─ filetype.vim            ファイル名パターンごとに、ファイルタイプを設定したい場合に用意する。
     ├─ scripts.vim             ファイルのデータによって、ファイルタイプを設定したい場合に用意する。
     ├─ colors/                 カラースキーマ用のファイルは、このディレクトリに入れる。
     ├─ doc/                    ドキュメント用のディレクトリ。
     ├─ ftplugin/               ファイルタイププラグイン用のディレクトリ。
     ├─ indent/                 インデントスクリプト用のディレクトリ。
     ├─ plugin/                 プラグイン用のディレクトリ。このサイトで紹介しているプラグインは、大抵このディレクトリに入れると動作する。
     ├─ syntax/                 シンタックスファイル用のディレクトリ。
     └─ after/                  このディレクトリ以下のスクリプトは、システムのスクリプトが読み込まれた後、読み込まれる。
          ├─ftplugin/
          ├─indent/
          └─ ....
```

# 操作
### 起動について
```
vi testfile          viでtestfileを開く
vi -R testfile       viでtestfileを読み出し専用で開く
vi + file            起動時にfileの最終行から開く
vi +/pattern file    起動時にfileのpatternの位置から開く
```

### コマンドについて
```
Esc,Ctrl+[       テキストモードからコマンドモードへ切り替える
```

### 基本操作(自分が覚えているような動作)
```
[Esc]、Ctrl-[     コマンドモードの中断
q!        保存せずに終了
q         (編集していなければ)終了
w         保存を行う
wq(ZZ)    保存して終了する
i         テキストモードへ移行(カーソルの文字から挿入できる)
a         テキストモードへ移動(カーソルの次の文字から挿入できる)
o         カーソル位置の下に1行追加し挿入モードに入る
h         右へ移動
j         下へ移動
k         上へ移動
l         左へ移動
w         右に1単語分移動する
b         左に1単語分移動する
^         行の最初のノンブランクワードに移動する
x         カーソルの位置にある文字を削除する
4x        カーソルの位置から右4つの文字を削除する
yy,Y      現在行をバッファにコピーする
dd        行の削除を行う
D         カーソル位置から行末までを削除する
p         カーソル位置の後ろにバッファ内容を貼り付ける
:u        アンドゥ(コマンドの取り消し)
J         カーソルのある行とその下の行を連結する
/文字列   順方向検索(nで次にマッチした文字へ移動、Nで1つ前に戻る)
?文字列   逆方向検索
.         リドゥ(redo),コマンドの再実行(例：ddをした後に.を実行すると最後ddを実行する)
:数字     数字の行へ移動する(例えば:10とすると10行目に移動する)
```

### 一般的な操作
```
gg,H      現在のページの先頭行へ移動
L         現在のページの末尾行へ移動
A         現在の行の末尾にテキストを追加する
I         テキストモードへ移行(カーソルのある行の先頭から挿入できる)
O         カーソル位置の上に1行追加し挿入モードに入る
P         カーソル位置の前にバッファ内容を貼り付ける
f         現在のファイル名と行番号を表示する
10G       左のは例で10行目に移動するつまり(数字)Gで移動できる
G         最後の行へ移動する。
$         カーソルのある行の最後へ移動する
0         カーソルのある行の先頭へ移動する
yl        1文字のコピー(3文字のコピーはy3lか3ylとする)
yw        1単語のコピー(3単語のコピーはy3wか3ywとする)
y$        カーソル位置からその行の最後までをコピーする
y0        カーソル位置からその行の先頭までをコピーする
r         次に入力する1文字と置き換え
R         以降に入力する文字と置き換え(上書き編集モード)
w ファイル名   ファイル名を付けて保存
r ファイル名   ファイルを読み込む
! コマンド     コマンドを実行して表示する
r! コマンド    コマンドの実行結果を読み込む
9dd       カーソル位置から9行削除
10l       10文字分カーソルを右に移動
3b        3単語前に移動
5H        画面の上から5行目に移動する
:%s/apple/orange/     1行内、1度だけ文字列appleをorangeに置き換える。
:%s/apple/orange/g    1行内、全てのappleをorangeに置き換える
:%s/apple/orange/gc   文書全体、全該当分のappleをorangeに置き換える(確認あり)
:%s/apple/orange/c    appleをorangeに確認しながら置き換える。
```

### 中級操作
```
<<        カーソルのある行をインデントする
>>        カーソルのある行をアンインデントする
zz        カーソルの位置の行を画面中央にする。
x,yd      x行からy行目までを削除する。(x,yは数字)
+         次の行の先頭に移動する
-         前の行の先頭に移動する
cw        単語を変更する。
C         行末まで変更する。
e         現在の単語の終わりに移動する
U         カーソル行に対して行った変更を全て消す
(         現在の文の先頭に飛ぶ
)         現在の文の文末に飛ぶ(.や。など)
%         カーソルのある括弧の対括弧に移動する。
d^        カーソル位置から行の先頭までを全て削除
d$        カーソル位置から行の後方までを全て削除
e!        前回保存時まで復旧する
```

### 応用操作
```
W         次のノンブランクワードの先頭に移動する
B         前のノンブランクワードの先頭に移動する
E         現在のノンブランクワードの終りに移動する
z.        現在行が画面の中央になるようにスクロール
z-        現在行が画面の下端になるようにスクロール
```

### 高度な移動など
```
Ctrl-F    次の頁へ移動
Ctrl-B    前の頁へ移動
Ctrl-D    半画面だけ次の頁へ移動
Ctrl-U    半画面だけ前の頁へ移動
Ctrl-E    1行次へ移動
Ctrl-Y    1行前へ移動
Ctrl-R    uコマンドの取消(リドゥredo)
Ctrl-L    画面の再描画を行う
Ctrl-G    カーソルのある位置の行番号などの情報をメッセージ行に出力する。
Ctrl-H    バックスペース(set backspace=2)があれば行をさかのぼって削除可能)
          ファイル全体の上からn％の位置に飛ぶ
```

# ファイル関連操作について
### リドゥしたい
アンドゥを取り消すリドゥがしたい場合 Ctrl + R でできる。

### 複数行の先頭に#を付与したい
これはCtrl+Vで選択範囲を絞って、I(カーソルのある行頭から挿入)を実行し、その後#(シャープ)を入力すればよい。

### ^Aや^Bなどのセパレータの入力方法について
Ctrl + Vの後にCtrl + AやCtrl + Bを押下すればよい。

### 10単語分の文字を削除したい。
カーソルの位置から10単語分削除したい場合にはコマンドモードで
```
10dw
```
とすればよい。

### ある文字まで削除したい。
カーソル位置からある文字まで削除したい場合には
```
df<1文字>
```
とする。 例えば、以下の行があったとする。 
- http://itpro.nikkeibp.co.jp/article/COLUMN/20060228/231169/

カーソル位置がhttp:のコロン(:)の位置にあると仮定して、
```
df2
```
とすると以下の部分が削除されることになる。
```
://itpro.nikkeibp.co.jp/article/COLUMN/2
```

つまり、以下の様な行になる。
```
http0060228/231169/
```

これは非常に便利なので覚えておくと良い。

### レジスタ管理(register)
レジスタはa〜zの26種類が格納できるクリップボードです。
```
"ay    選択範囲をレジスタ a に保存
"ayy   今いる行をレジスタ a に保存
"ap    レジスタ a の内容をカーソル位置にペースト
```

### 記録操作(recording)を行いたい。 
```
[操作開始]
:qa   操作の記録を開始し、レジスタ a に保存する 
```

```
[操作終了]
:q    操作の記録を終了する。
```

```
[記録の再生]
:@a   レジスタ a に保存された操作を再生する 
:5@a  レジスタ a に保存された操作を5回再生する 
```

記録しているレジスタ一覧が知りたい場合には:regとすれば確認できる。 以下に例を示す。
```
:reg
--- Registers ---
""   --------------------------------------------------------------------^J
"0   --------------------------------------------------------------------^J
```

### カーソル上の文字の大文字小文字を切り替えたい
カーソル上で~(ニョロ)を押せば切り替えることができる。

### コマンドの実行結果を現在のviの編集画面に埋め込みたい
```
:r!ls -al
```
とすると、カーソル位置に「ls -al」のコマンド実行結果が埋め込まれます。


# 設定について
設定は.exrcか.vimrcに記述する。 ダブルクォーテーション以降がコメントとして扱われる。

```
利用した方がいい設定>

    :set title         タイトルに現在開いているファイル名を表示する
    :set list          タブや改行を表示する
    :set number        行番号の表示をする
    :set nonumber      行番号の表示をしない(default)
    :set showmode      挿入モードの表示
    :set noshowmode    文字列挿入モードかどうかを表示しない(default)
    :set showmatch     カッコを閉じたときに対応するカッコにカーソルを移動する
    :set tabstop=2     タブ幅をスペース2文字分にする。
    :set shiftwidth=2  インデントでスペースを2文字挿入する
    :set softtabstop=2 入力したタブをスペース2文字で表す。
    (上記3つの省略系は1行で記述できる。 :set ts=2 sw=2 sts=2)
    :set showmode      文字列挿入モードの表示を行う
    :set autoindent    自動的にインデントを行う
    :set noautoindent  自動的にインデントは行わない
    :set cindent       C言語のコードを自動的にインデントする   
    :set showmatch     プログラムでのカッコを確認できる。
    :set ruler         いま現在の行番号、列番号を常に表示する
    :set backup        .bak拡張子を付けてファイル作成前にバックアップファイルを作成
    :set patchmode=.back  左の例では.backという名前を付加しbackupファイルを作成する。
    :set backupdir=>/tmp  /tmpにファイル名~を作成を行う(set backupが必要) 
    :set encoding=euc-jp   内部エンコードをEUC-JPに固定する。(utf-8,iso-2022-jpも可)
    :syntax on        色によりシンタックスチェックが可能になる。
    :set compatible
    :set fileenconding=japan
    :set modeline
    :set exrc

基本的な設定>

    :set fexrc         拡張子ごとに設定ファイルを読み込む(例えばphpでは.vimrc.phpファイル)
    :set nohlsearch    あらかじめ強調表示しないように設定する
    :set hlsearch      強調表示機能をONにする
    :set ignorecase    大文字、小文字を区別なく検索する
    :set noignorecase  大文字、小文字は別文字として区別して検索します
    :set smartcase     大文字、小文字を区別して検索する
    :nohlsearch        (検索時に現れる)強調されている文字をクリアする
    :shell(shのみも可) シェルモードへ移行(exitでもとのviの画面に戻る)
    :set softtabstop=2 入力したタブをスペース2文字で表す。
    :set expandtab     タブを入力した時、タブの代わりにスペースを挿入する。
    :set iminsert=0    挿入モードでインプットメソッドをオフにする。
    :set laststatus=2  (2は)ステータスラインを常に表示する
    :set backspace=?   ?にはindent,eol,startが入る。
                       <BS>時の挙動を示す。
                                 indent:インデントの削除を許可
                                 eol:   EndOfLine。改行の削除を許可
                                 start: 挿入モード直後の文字削除を許可
    :set hid           編集中の内容を保ったまま別の画面に切り替えられる。
                       (デフォルトだと一度保存しないと切り替えられない)
    :set incsearch     インクリメンタルサーチを行う(単語を入力した時点で一致しているものを表示)
    :h                 ヘルプの表示
    :!cmd              シェルコマンドの実行を行う
    !!cmd              コマンドを実行してその結果を挿入する
    :e <ファイル名>    <ファイル名>を読み込む
    :r <ファイル名>    カーソル行の下に<ファイル名>の内容を挿入する
    :w <ファイル名>    編集中のデータを<ファイル名>のファイルに保存する

中級的な設定>

    :set fileencoding=cp932        cp932(Shift-JIS)にする。
    :set fileformats=unix,dos,mac  改行コードの自動認識を行う。
    :set fileformat=改行コード種類 dos,mac,unixが指定できる。

ウィンドウの分割に関する操作>
    :split             画面を上下に分割する
    :vsplit            画面を左右に分割する
    :split <file>      <file>を開く(上下)
    :vsplit <file>     <file>を開く(左右)
    Ctrl+W,+           現在のウィンドウを1つ増やす(+にはShiftを押す必要がある)
    Ctrl+W,-           現在のウィンドウを1つ減らす
    :close             現在カーソルのある画面をcloseする
    :only              現在カーソルのある行以外を全て閉じる
    :new               画面を上下に分割して新しいバッファを開く
    :vnew              画面を左右に分割して新しいバッファを開く
    :Ctrl-w(h,j,k,l)   カーソルを左右上下に移動する(h,j,k,lは通常と同じ移動操作)
```

### Bundleを使う
以下のコマンドでインストールする
```
$ git clone http://github.com/gmarik/vundle.git ~/.vim/bundle/vundle
```

以下を$HOME/.vimrcに追加する
```
set nocompatible               " be iMproved
filetype off                   " required!
set rtp+=~/.vim/bundle/vundle/
call vundle#rc()
" let Vundle manage Vundle
" required!
Bundle 'gmarik/vundle'
" My Bundles here:
"
" original repos on github
Bundle 'tpope/vim-fugitive'
Bundle 'Lokaltog/vim-easymotion'
Bundle 'rstacruz/sparkup', {'rtp': 'vim/'}
Bundle 'tpope/vim-rails.git'
" vim-scripts repos
Bundle 'L9'
Bundle 'FuzzyFinder'
" non github repos
Bundle 'git://git.wincent.com/command-t.git'
" ...
filetype plugin indent on     " required!
"
" Brief help
" :BundleList          - list configured bundles
" :BundleInstall(!)    - install(update) bundles
" :BundleSearch(!) foo - search(or refresh cache first) for foo
" :BundleClean(!)      - confirm(or auto-approve) removal of unused bundles
"
" see :h vundle for more details or wiki for FAQ
" NOTE: comments after Bundle command are not allowed..
```

たとえば、faith/vim-goの以下のvimプラグインをインストールしたい場合には
- https://github.com/fatih/vim-go

.vimrcの最下行に以下を追加して保存します。
```
Bundle 'fatih/vim-go'
```

vimを引数なしで実行して、以下を実行するとインストールが始まります。
```
:BundleInstall
```

### UTF-8を開こうとするとバイナリファイルとなって開けない場合
```
$ vim ~/.virmc
set fileencoding=japan
set fileencodings=iso-2022-jp,utf-8,euc-jp,ucs-2le,ucs-2,cp932p
```

### vimの検索結果をハイライトする

:set hlsearch
```

# syntax関連

### syntax関連の設定について
```
:set highlight ハイライトを設定する
:set nohighlight ハイライトを解除する
:syn on 構文ハイライトを有効にする
:syn off 構文ハイライトを無効にする
:set filetype=c cのシンタックスでハイライトする
:set filetype=html htmlのシンタックスでハイライトする 
```

### ある拡張子を特定の拡張子のsyntaxファイルと認識させたい。
たとえば、.testという拡張子のファイルをhtmlファイルと認識させたいような 場合には.vimrcに以下の記述をすればよい。
```
augroup filetypedetect
au BufRead,BufNewFile *.test setfiletype html
augroup END
```

### 個人用のsyntaxファイルを利用したい
```
~/.vim/colors
```
のディレクトリ中にsyntaxファイル(拡張子:.vim)を設置すれば、
```
:colorscheme  testsyntax
```
とすれば、~/.vim/colors/testsyntax.vimのファイルの読み込みを 行います。

### 色の指定について
```
:colorscheme [targetcolor]
```
でよい。以下にtargetcolorを示す。 これは[TAB]により、引数候補が出るので覚える必要はない。 blue, darkblue, default, elford, evening, koehler morning, murphy, pablo, peachpuff, ron, shinetorte, zellner
↑

### カラースキームファイルで何が利用できるか知りたい。
```
/usr/share/vim/vim63/colors/
```
上記の場所に様々なカラースキームが存在します。

# ヘルプページ

### ヘルプの参照方法
```
:help
```

### ヘルプページへの移動方法 と 「:help」トップページへの戻り方
「:help」実行後に下記画面が表示されたら
```
Getting Started ~
|usr_01.txt|  About the manuals
|usr_02.txt|  The first steps in Vim
```
「user_01.txt」や「user_02.txt」の上にカーソルを持って「Ctrl + ]」と押下することによって、閲覧したいヘルプドキュメントに遷移できます。 「:help」実行時の画面に戻る際には、「Ctrl + T」によって戻ることができるようになります。

以下ははvimヘルプページの日本語版です。
- http://www.ac.cyberhome.ne.jp/~yakahaira/vimdoc/


# 参考URL
- VIMドキュメント 日本語訳
 - http://sites.google.com/site/vimdocja/
- vim様々なリンク集 by 2ch
 - http://www.bookshelf.jp/2ch/unix/1284344926.html
- サイト更新停滞ちゅう
 - http://advweb.seesaa.net/
- Vim日本語ドキュメント
 - http://www.kaoriya.net/vimdoc_j/
- JVim3非公式ガイド 目次
 - http://homepage1.nifty.com/niwatori/vi/index.html
- Vim documentation: syntax
 - http://www.ac.cyberhome.ne.jp/~yakahaira/vimdoc/syntax.html
- vim - 文字コードの自動認識
 - http://www.ksknet.net/vi/vim_1.html
- vim設定コマンド リファレンス
 - http://www15.ocn.ne.jp/~tusr/vim/options.html
 - http://www15.ocn.ne.jp/~tusr/vim/options_help.html
- vimの小技
 - http://d.hatena.ne.jp/bonar/20070415/1176651778
http://www.not-enough.org/abe/manual/comm/tips.html


