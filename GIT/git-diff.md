# 概要
gitのdiffを見る方法について

# 比較方法(ブラウザ)

### ブラウザで比較する

以下はサンプルです。sha1を記載したりブランチ名を記載することが可能です。３点リーダーではさみます。
指定できるのはブランチ、タグ、コミットIDです。
- https://github.com/fastladder/fastladder/compare/2.3.5...711ae09c3de07532c4ee86d7a8ffb08bfa6d369e
- https://github.com/fastladder/fastladder/compare/2.3.5...master

### 空白を無視したい場合
URLの最後に「?w=1」を付与する
- 参考
  - https://github.com/tiimgreen/github-cheat-sheet

### UI表示上のタブ幅を変更したい場合
URLに「?ts=4」などとすると良い

### いついつから変更されたmaster情報を確認したい
```
https://github.com/rails/rails/compare/master@{1.day.ago}...master
https://github.com/rails/rails/compare/master@{2014-10-04}...master
```

# 比較方法(コマンド)

### どれくらいを変更したかだけを知りたい場合
```
$ git diff --stat
 git-diff.md | 15 ++++++++++++++-
 git.md      | 64 ++++++++++++++++------------------------------------------------
 2 files changed, 30 insertions(+), 49 deletions(-)
```

### ブランチ間を比較したい場合
名前だけ表示したければ、--name-onlyを付与すればよい。
```
$ git diff --name-only branch1 branch2
```

### 1ファイルの変更点だけを見たい
```
$ git diff -- <filename>
```

### git addしたあとの変更点を見たい
git add した後にインデックスと最新のコミットとの変更点を見たいときには次のようにします。
```
$ git diff --cached
```

### コミットしたファイル同士の変更点の比較
```
$ git diff 変更後のSHA..変更前のSHA
```

または次のようにしても可能らしい
```
$ git diff commit1 commit2 -- path/to/file
```

また、ブランチを比較する場合も同じ
```
$ git diff ブランチA..ブランチB
```

### コミットしたSHAの比較を行う場合
```
$ git diff 確認したいコミットのSHA^..確認したいコミットのSHA
```

### 変更点以外の前後の行も表示したい
たとえば、次のようにすると変更した前後10行が表示されるようになります。
```
$ git diff -U10
```

### 空白コードなどを無視する場合
```
$ git diff -w
```

### 空行を無視する場合
```
$ git diff --ignore-blank-lines
```

### コミット間の差分を色で表示する
```
$ git diff --color-words
```

### git pull, git pushする前にあらかじめにリモート側とのファイル変更点を確認しておきたい場合
pullする前
```
$ git diff HEAD..リモート名/ブランチ名
```

pushする前
```
$ git diff リモート名/ブランチ名..HEAD
```

### コミットした変更点を見る
コミットした直後に、そのコミットとその直前のコミットを比較したい場合に利用する
```
$ git diff HEAD^
or 
$ git diff HEAD^..HEAD
```

### git logやgit uiのツール上で取得したハッシュ値同しで比較する

```
$ git log
$ git diff <hash1>  <hash2>
```


