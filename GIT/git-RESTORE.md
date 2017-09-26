# 概要
gitでやらかしてしまった場合に元に戻す方法などについて

# 概要

### 別のブランチへのコミットを現在のブランチに対してコピーしたい場合
```
$ git cherry-pick [commit id]
```

### worktreeの修正をなかったことにしたい
```
$ git checkout .
```

### 直前のコミットを変更したい
```
$ git commit --amend -m "新しいコメント"
```

### 特定のコミットのみを取り消したい場合
```
$ git revert <commit_id>
```

### コミット済のファイルをレポジトリから消したい場合
```
$ git rm --cached hoge.txt
```

### 特定のファイルをHEAD状態に戻すには
```
$ git checkout HEAD -- test_file.txt
```

### mergeして、conflictが発生し、解消しようと努力したが、こんがらがって中止したくなった
```
$ git reset --hard HEAD
```

