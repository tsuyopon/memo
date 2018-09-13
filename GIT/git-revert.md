# 概要
git revertについて

# 詳細

### 直前のcommitを打ち消す場合
```
$ git revert HEAD
```

またはgit logなどで画面に表示された最上部のハッシュ値を指定すると良い

### 特定のcommitのみを打ち消す方法
そのコミットがなかったときの状態に戻ります。コンフリクトが発生する場合にはそれを解消する必要があります。
```
$ git revert <commit_id>
```

### 特定のPRをrevertする方法
特定のPRをrevertする方法はありませんので、最新のcommitから順番に古いcommit値を指定して順番で以下のコマンドを打ちます。
なお、PRにmasterから取り込んだ場合、そのコミット値が記載されていますが、これはgit revertで指定しなくても大丈夫です。
```
$ git revert <commit_id>
```

もし、このコミットよりもあとで更新処理などが入っている場合にはrevert処理はそれより前のコミットも遡及してrevertしない限りエラーとはできません。

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

