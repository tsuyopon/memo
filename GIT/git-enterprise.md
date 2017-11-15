# 概要
2つのgheサーバ間における操作などについて

# 詳細
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


### ghe1からghe2に最新情報が更新された。ghe2をforkする特定のブランチ(testbranch)に対して更新された内容のPRを発行したい場合
ghe2をforkしたブランチをghe3と仮定する。


ghe3をcloneして、testbranchからブランチを派生させて作成する。
```
$ git clone git@ghe3:foo/bar.git
$ cd bar.git
$ git checkout testbranch
$ git branch UPDATE_testbranch
$ git checkout UPDATE_testbranch
```

upstreamにghe2を登録します。そして、UPDATE_testbranchにupstream/testbranchの更新を適用します。
```
$ git remote add upstream git@ghe2:foo/bar.git
$ git fetch upstream
$ git merge upstream/testbranch
```

あとは必要あればコンフリクトを解消させて、testbranchから派生したUPDATE_testbranchブランチにpushすればUI上からPRを発行できます。
```
$ git push -u origin UPDATE_testbranch
```
