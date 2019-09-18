# 概要
gitに関する設定などについてのメモ

詳細は以下のコマンドなどで確認すること
```
$ man git-config
```

### 初期設定
以下はユーザ設定のglobalを指定しているが、システム全体(system)とレポジトリのみ(local)といったものも存在する。
```
$ git config --global color.ui true
$ git config --global user.name "tsuyopon"
$ git config --global user.email "hoge@example.com"
$ cat ~/.gitconfig
```

### git用設定ファイルについて
~/.gitconfigや.git/configなどにgit用設定ファイルとして配置されことがある。
ただし、前者の方が優先度が高く設定される。

### originを確認する
```
$ git remote -v 
origin  https://github.com/tsuyopon/memo.git (fetch)
origin  https://github.com/tsuyopon/memo.git (push)
```

### upstreamを追加する
```
$ git remote add upstream git:://github.com/tsuyopon/memo.git
```

### git設定ファイルについて
次の３種類の設定ファイルがある。Linuxの場合には次のファイルパスとなる。
- (1) システム全体(--system)
  - /etc/gitconfig
- (2) ユーザ全体(--global)
  - $HOME/.gitconfig
- (3) レポジトリのみ(--local)
  - 対象レポジトリ内の.git/config

次のようにeditをすると、指定したsystem, global, localなどの設定ファイルを直接開いてくれる。以下の例ではglobalが指定されているので$HOME/.gitconfigが開かれることになります。
```
$ git config --global --edit
```

### 設定ファイルの内容を出力する
```
$ git config --list            // (1)〜(3)すべての出力
$ git config --system --list   // (1)のみ
$ git config --global --list   // (2)のみ
$ git config --local --list    // (3)のみ
```

### 設定ファイルの内容を正規表現で検索する
```
$ git config --get-regexp "^color"
```


### 設定した値を削除する
```
$ git config --list                 // 削除するプロパティ名を確認する
$ git config --unset プロパティ名
```

### git statusすると日本語名のファイルが文字化けする場合
```
$ git config --global core.quotepath false
```

### git diffすると日本語名のファイルが文字化けする場合
```
$ git config --global core.pager "LESSCHARSET=utf-8 less"
```

また以下の設定を~/.bash_profileなどにいれておきましょう。
```
export GIT_PAGER="LESSCHARSET=utf-8 less"
```

# 参考
- 他の人のgithub
  - https://github.com/yuroyoro/dotfiles/blob/master/.gitconfig
