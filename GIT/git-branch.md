# 概要
git branchについて

# 詳細

### ブランチ切り替え
```
$ git branch <branch>
```

### ブランチ名を変更したい
```
$ git branch -m <oldbranch> <newbranch>
```

上記でoldnameを省略すると、現在いるブランチとなる
```
$ git branch -m <newbranch>
```

### ブランチを確認する
- ローカルブランチを確認する
```
$ git branch
```
- リモートブランチを確認する
```
$ git branch -r
```
- ローカル・リモートブランチ双方を一度に確認する
```
$ git branch -a
```

万が一、上記で表示されないような場合には次を実行しておくとリモートからブランチ情報を取得してくれる。
```
$ git fetch
```

その他にも次のようなオプションが存在する
- HEADにマージ済みのブランチの一覧を表示する
```
$ git branch --merged
```
- HEADにマージされていないブランチの一覧を表示する
```
$ git branch --no-merged
```

### ブランチを削除する
```
$ git branch -d testbranch
```

HEADにマージされていないコミットがあるブランチを強制的に削除するにはDを利用する必要があるようです。
```
$ git branch -D testbranch
```

### 現在の作業ブランチに指定ブランチをマージする
```
$ git merge mergeOrigBranch
```

### 現在いるブランチを表示する
たとえば、master_derivedというブランチを作成して、そのブランチの中にいるのであれば次のコマンドでそのブランチを取得できる。
```
$ git rev-parse --abbrev-ref HEAD
master_derived
```

### 現在のハッシュ値や直前のコミットメッセージを表示する
vやvvオプションでブランチの現在のハッシュ値や直前のコミットメッセージが表示されます。
```
$ git branch -v
* master 4d71925 added .DEFAULT_GOAL
$ git branch -vv
* master 4d71925 [origin/master] added .DEFAULT_GOAL
```

### TODO
- http://qiita.com/chihiro/items/e178e45a7fd5a2fb4599
  - 以下のコマンドをまとめたい
```
git branch -u <upstream>
git branch --unset-upstream
```

# 参考URL
- https://git-scm.com/book/ja/v1/Git-%E3%81%AE%E3%83%96%E3%83%A9%E3%83%B3%E3%83%81%E6%A9%9F%E8%83%BD-%E3%83%96%E3%83%A9%E3%83%B3%E3%83%81%E3%81%AE%E7%AE%A1%E7%90%86
