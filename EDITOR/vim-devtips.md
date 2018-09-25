# 概要
vimで開発での役立ちそうなtipsについてまとめる

# 詳細

### 現在カーソル位置に存在するAPIのmanを表示する。
たとえば、malloc等にカーソルを載せて次を打てばmanが表示される。
```
Shift + K
```

### 現在カーソルにあるワードをそのファイルから検出する
そのワードを検索する。カーソルに載せて「*」(アスタリスク)を押下するだけでOK

### 最後に保存してから、どのくらい編集したのかの差分を表示したい
```
:DiffOrig
```
とすればよい。  

万が一、DiffOrigが使えない場合には以下を疑う。
```
vimエディタのバージョンが足りていない 
「$VIMRUNTIME/vimrc_example.vim」を読み込んでいない 
```

自分は以下の定義を.vimrcに追加することで利用することができるようになりました。
```
command DiffOrig vert new | set bt=nofile | r # | 0d_ | diffthis | wincmd p | diffthis
```

### vimのPHPの辞書を作成する
```
$ mkdir -p ~/.vim/dict/
$ php -r '$f=get_defined_functions();echo join("\n",$f["internal"]);' | sort > ~/.vim/dict/php_functions.dict
```

上記により辞書の作成を行う。  
次に.vimrcに以下の2行を追加する。
```
autocmd FileType php :set dictionary+=~/.vim/dict/php_functions.dict
set complete+=k
```

こうすると、たとえばhtmlspecialcharsとか長いのを打つときにhtmlまで打って
```
Ctrl + N or Ctrl + P 
```

を打つと候補が出現する。 複数ある場合には
```
Ctrl + N(Ctrl + P)
```
を打てばNext,Prevで選択できる。

### PHPで.incファイルもphpファイルとみなしたい
ctagsによりtagファイルを作成して、vimrcに以下の行を追加するといいらしい。
```
autocmd FileType php :set tags+=~/.vim/tags/pear.tags
```
- http://www.asahi-net.or.jp/~wv7y-kmr/memo/vim_php.html

### 特定の拡張子のファイルに対して特定のセッティングにしたい
例えば、c, c++, perlに対しては特有のセッティングにしたい場合には以下の様にして 設定することができる。
```
au FileType c,cpp,perl set fdm=syntax et sw=4 ts=4 cindent
```

### syntax等の入っているvimのランタイムライブラリの場所を定義したい
通常では/usr/local/share/vim/vim70の用に設定されているがVIMRUNTIME環境変数を 利用することにより、場所を設定することができる。  
自分のホームディレクトリ中の/home/tsuyoshi/lib/vim70に設定するのであれば
```
export VIMRUNTIME="/home/tsuyoshi/lib/vim70"
```

### 2つのファイルの違いを表示する
現在開いているファイルとあるファイルの違いを知りたい場合には以下の様にします。
```
:diffsplit file             横分割の場合
:vertical diffsplit file    縦分割の場合      
```

尚、コマンドラインから実行する場合には 以下の2つの方法があります。
```
vimdiff fileA fileB
vim -d file A fileB
```

なお、左右に差分を表示してでのvimdiffではなく、上下に差分を表示するvimdiffの場合にはoオプションを付与すると良い。
```
vimdiff -o fileA fileB
```

### 色づけして、splitによりファイルの差分の確認をしたい
今のファイルと、他のファイルとの差分を取る時に非常に便利です。 以下のコマンドを実行すると、差分が確認できます。色鮮やかでわかりやすいです。 一度試してみてください。
```
:vert diffsplit [他のファイル]
```

上記を実行してみて鮮やかすぎて逆にわかりにくいという場合には以下を.vimrcに追加します。
```
set diffexpr=IgnoreSpaceDiff()
function IgnoreSpaceDiff()
  let opt = ""
  if &diffopt =~ "icase"
  let opt = opt . "-i "
  endif
  if &diffopt =~ "iwhite"
  let opt = opt . "-b "
  endif
  silent execute "!diff --ignore-all-space -a " . opt .
  \  v:fname_in . " " . v:fname_new .
  \  " > " . v:fname_out
endfunction
```

### vimの文字コードの自動認識
```
" ステータス行に文字コードや改行コードを表示
set statusline=%<%f\ %m%r%h%w%{'['.(&fenc!=''?&fenc:&enc).']['.&ff.']'}%=%l,%c%V%8P

" 日本語を扱うために必要
"---------------------------------
" auto encoding (japanese)
"---------------------------------
if &encoding !=# 'utf-8'
        set encoding=japan
endif
set fileencoding=japan
if has('iconv')
        let s:enc_euc = 'euc-jp'
        let s:enc_jis = 'iso-2022-jp'
        " iconvがJISX0213に対応しているかをチェック
        if iconv("\x87\x64\x87\x6a", 'cp932', 'euc-jisx0213') ==# "\xad\xc5\xad\xcb"
                let s:enc_euc = 'euc-jisx0213'
                let s:enc_jis = 'iso-2022-jp-3'
        endif
        " fileencodingsを構築
        if &encoding ==# 'utf-8'
                let s:fileencodings_default = &fileencodings
                let &fileencodings = s:enc_jis .','. s:enc_euc .',cp932'
                let &fileencodings = &fileencodings .','. s:fileencodings_default
                unlet s:fileencodings_default
        else
                let &fileencodings = &fileencodings .','. s:enc_jis
                set fileencodings+=utf-8,ucs-2le,ucs-2
                if &encoding =~# '^euc-\%(jp\|jisx0213\)$'
                        set fileencodings+=cp932
                        set fileencodings-=euc-jp
                        set fileencodings-=euc-jisx0213
                        let &encoding = s:enc_euc
                else
                        let &fileencodings = &fileencodings .','. s:enc_euc
                endif
        endif
        " 定数を処分
        unlet s:enc_euc
        unlet s:enc_jis
endif
```
- 参考
 - http://www.ksknet.net/vi/vim_1.html
