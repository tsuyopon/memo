# 概要
git revertについて

# 詳細

### 直前のcommitを打ち消す場合
```
$ git revert HEAD
```

### 特定のcommitのみを打ち消す方法
そのコミットがなかったときの状態に戻ります。コンフリクトが発生する場合にはそれを解消する必要があります。
```
$ git revert <commit_id>
```

### 過去２つのcommitを打ち消す場合
```
$ git revert HEAD~2
```

### revertする範囲を指定する場合
```
$ git revert master~5..masetr~2
```

# 参考URL
- https://git-scm.com/docs/git-revert

