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


## .ctagsファイルについて
$HOME/.ctagsに配置するとindexを生成する際に参照するファイルが指定できる。
- https://github.com/grassdog/dotfiles/blob/6bd36bcb59b57eac28d618f76f21e83d4fc487a8/ctags
- https://gist.github.com/tim-smart/199338

javascriptの場合だとこの辺の説明が.ctags生成の理解に役立つ
- http://dance.computer.dance/posts/2015/04/using-ctags-on-modern-javascript.html

