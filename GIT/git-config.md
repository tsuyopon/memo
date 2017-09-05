# 概要
gitに関する設定など

### 初期設定
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
