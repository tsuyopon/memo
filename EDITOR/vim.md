vimについて

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
```
:set hlsearch
```
