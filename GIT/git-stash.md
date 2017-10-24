# 概要
git stash周りについて

# 詳細

### 現在の状態を退避しておき、修正をなかったものとして扱う
```
$ git stash save
or
$ git stash
```

デフォルトでは新規ファイルまでは退避されません。新規ファイルも含める場合には次のようにuオプションを付与します。
```
$ git stash -u 
```

### git stashで保存した最新の状態を現在の状態に反映する
```
$ git stash pop
```

このコマンドは実は適用(git stash apply)と削除(git stash drop)を同時に行っていることに注意しておいてください。

### git stashで退避した状態一覧を確認し、それを元にして復元する
```
$ git stash list
stash@{0}: WIP on master: 049d078 added the index file
stash@{1}: WIP on master: c264051 Revert "added file_size"
```

以下はstash@{0}の例となります。  

変更されたファイル一覧を確認する。
```
$ git stash show stash@{0}
 GIT/git-log.md       |  15 +++++++++++++++
 GIT/git-merge.md     | 123 +--------------------------------------------------------------------------------------------------------------------------
 TLS/TLSResumption.md |   2 +-
 3 files changed, 17 insertions(+), 123 deletions(-)
```

変更されたファイルの詳細(diff)を確認する。
```
$ git stash show stash@{0} -p
```

適用したい場合(適用されるが、stash listからは削除されない)
```
$ git stash apply stash@{0}
```

なお適用したので該当のstashが不要となる場合にはリストからも削除させる
```
$ git stash drop stash@{0}
```

git stash popを利用するとapplyとdropを同時に行うことができます。引数を省略した場合にはstash@{0}が指定されたものとみなされます。
```
$ git stash pop stash@{0}
```

### git stash listで表示されるstashをクリアしたい
```
$ git stash clear
```

### applyで適用したdiffを取り消したい
applyで適用したあとに削除したい場合には次のようなコマンドで可能なようです。
```
$ git stash show -p stash@{0} | git apply -R
```

### stashで退避された状態をすべて削除する場合
```
$ git stash clean
```

# 参考URL
- https://git-scm.com/book/ja/v1/Git-%E3%81%AE%E3%81%95%E3%81%BE%E3%81%96%E3%81%BE%E3%81%AA%E3%83%84%E3%83%BC%E3%83%AB-%E4%BD%9C%E6%A5%AD%E3%82%92%E9%9A%A0%E3%81%99
