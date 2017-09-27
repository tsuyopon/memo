# 概要
git remoteやそのセットアップについて

# 詳細

### リモートレポジトリ情報を見る
```
$ git remote -v
origin	https://github.com/tsuyopon/memo.git (fetch)
origin	https://github.com/tsuyopon/memo.git (push)
```
### リモートレポジトリの詳細情報を確認する
```
$ git remote show origin
* remote origin
  Fetch URL: https://github.com/tsuyopon/memo.git
  Push  URL: https://github.com/tsuyopon/memo.git
  HEAD branch: master
  Remote branches:
    gh-pages tracked
    master   tracked
  Local branch configured for 'git pull':
    master merges with remote master
  Local ref configured for 'git push':
    master pushes to master (up to date)
```

### リモートレポジトリ情報を削除する
```
$ git remote rm origin
```

### リモートレポジトリ情報を追加する
```
$ git remote add upstream git@github.com:tsuyopon/memo.git
```

### 登録済のリモートレポジトリのアドレスを変更する
```
$ git remote set-url origin git@github.com:tsuyopon/memo.git
```

### リモートレポジトリに登録されている名前を変更したい場合
upstreamをupstream2としておきたい場合には次のようにします。
```
$ git remote rename upstream upstream2
```

# 参考URL
- https://git-scm.com/book/ja/v1/Git-%E3%81%AE%E5%9F%BA%E6%9C%AC-%E3%83%AA%E3%83%A2%E3%83%BC%E3%83%88%E3%81%A7%E3%81%AE%E4%BD%9C%E6%A5%AD
