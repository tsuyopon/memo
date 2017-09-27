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

### TODO
- http://qiita.com/chihiro/items/e178e45a7fd5a2fb4599
  - 以下のコマンドをまとめたい
```
git branch -u <upstream>
git branch --unset-upstream
```
