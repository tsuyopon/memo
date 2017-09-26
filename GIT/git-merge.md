# 概要
主にgit周りで他のブランチなどの取り込み・更新などの処理についてはこちらにまとめます。

# 詳細
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

- 参考
  - https://www.iana.org/assignments/tls-parameters/tls-parameters.xhtml
