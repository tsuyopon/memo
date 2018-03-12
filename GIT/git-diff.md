# 概要
gitのdiffを見る方法について

# 比較方法(ブラウザ)

### ブラウザで比較する
以下はサンプルです。sha1を記載したりブランチ名を記載することが可能です。３点リーダーではさみます。
指定できるのはブランチ、タグ、コミットIDです。
- https://github.com/fastladder/fastladder/compare/2.3.5...711ae09c3de07532c4ee86d7a8ffb08bfa6d369e
- https://github.com/fastladder/fastladder/compare/2.3.5...master

### forkされたブランチと比較する
- https://github.com/rails/rails/compare/byroot:master...master

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

- 参考
  - https://qiita.com/sotayamashita/items/1cf05f2a2be3d6fb3388

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

### 特定のディレクトリのファイル名の差分のみを抽出したい場合
path/to/dir配下の差分の名前のみを抽出したい場合には次のようにします。
```
$ git diff <hash1> <hash2> --name-only --relative=path/to/dir
```

### 1ファイルの変更点だけを見たい
```
$ git diff -- <filename>
```

### git addしたあとの変更点を見たい
git add した後にインデックスと最新のコミットとの変更点を見たいときgit diffだともう見ることができません。
この場合には次のcachedオプションを付与します。
```
$ git diff --cached
```

上記だけだと、renameなどの場合にファイルが削除されて、新しいファイルが作成されたことしかわからないので、Mオプションを付与すると良い
```
$ git diff --cached -M
```

### commitによる比較やブランチによる比較
レポジトリ全体を比較したい場合には次のようにします。
```
$ git diff 変更後のSHA..変更前のSHA
```

また、ブランチを比較する場合も同じ
```
$ git diff ブランチA..ブランチB
```

### 特定のコミット間やブランチ間で、特定のファイルだけを比較対象としたい。
特定のファイルでコミット間の比較をしたい場合には次のようにします。
```
$ git diff commit1 commit2 -- /home/xxx/hoge.txt
```

それぞれのcommitにおいてパスやファイルを指定することにより比較することもできます。
```
$ git diff <コミット名>:<ファイル名> <コミット名>:<ファイル名>
```

### 変更点以外の前後の行も表示したい
たとえば、次のようにすると変更した前後10行が表示されるようになります。
```
$ git diff -U10
```

### 空白コードなどを無視する場合
```
$ git diff -w
or
$ git diff --ignore-all-space
```

### ファイル内のスペース数の違いを無視する場合
```
$ git diff -b
or
$ git diff --ignore-space-changes
```

### 空行を無視する場合
```
$ git diff --ignore-blank-lines
```

### コミット間の差分を色で表示する
```
$ git diff --color-words
```

### 文字レベルで違いを表示する
```
// 差分を文字レベルで表示する
$ git diff --word-diff
 
// 差分を文字レベルで表示する。色と＋、ーだけで、差分を表現する
$ git diff --word-diff=color
  
// git diff HEAD --word-diff　と同じ効果
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

# TIPS

### git diffで行末に^Mが表示される
改行コードがCRLFだと^Mと表示されるようです。対策としては改行コードをLFにすれいいようです。
次のようにします。
```
[core]
    whitespace = cr-at-eol
```

- SeeAlso
  - http://amano41.hatenablog.jp/entry/git-diff-treats-cr-at-eol-as-error
