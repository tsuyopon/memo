# 概要
主にgit周りで他のブランチなどの取り込み・更新などの処理についてはこちらにまとめます。

# 詳細

### git pullは
git fetchとgit mergeしたことと等価らしいので覚えておく

### forkしたレポジトリの内容が古くなったので、親レポジトリに追従させる

オリジナルレポジトリをupstream
```
$ git remote add upstream git://github.com/tsuyopon/xxxx.git
$ git remote -v
```

あとはマージしたいレポジトリに移動してから
```
$ git fetch upstream
$ git merge upstream/master
```

### マージしたけどやっぱり元に戻したい時
mergeしてしまって、やっぱりmergeをやめたいと思った場合の対処方法
```
# マージする。
$ git checkout <マージ先ブランチ>
$ git merge <マージ元ブランチ>

# マージしたあと、やっぱやめよって思ったらこれをやる
# ORIG_HEADを指定すればマージ前に戻る
$ git reset --hard ORIG_HEAD
```


# 参考URL
- 参考
  - https://www.iana.org/assignments/tls-parameters/tls-parameters.xhtml
