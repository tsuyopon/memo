### ghe1側のレポジトリをghe2側の同名レポジトリにミラーする

あらかじめghe2側で新しく同名のレポジトリbarを作成しておきます。この際にREADME.mdを作成しないようにします。

事前準備を行います。
```
git clone --bare git@ghe1:foo/bar.git
cd bar.git
git remote add ghe2 git@ghe2:foo/bar.git
```

同期方法はgit-fetchでoriginのghe1の変更を取り込みます。次にgit-pushでghe2へ向けてpushします.
```
git fetch --prune origin 'refs/heads/*:refs/heads/*'
git push ghe2 --mirror
```

- 参考
  - http://qiita.com/satoruk/items/186af9d095d744d15c76
