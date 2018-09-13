# 概要
git resetについて

# 詳細

### 誤ってコミットしたので、コミットする前の状態に戻したい(修正内容はそのままとする)
```
$ git reset --soft HEAD^
```

### 誤ってコミットしたので、コミットする前の状態に戻したい(修正内容もコミット時に戻すものとする)
```
$ git reset --hard HEAD^
```

特定の状態にまで戻したい場合にはcommit値を指定する。
```
$ git reset --hard <commit>
```

# 参考URL
- http://www-creators.com/archives/1116
