# 概要
2つのgheサーバ間における操作などについて

# 詳細
### ghe1側のレポジトリをghe2側の同名レポジトリにミラーする

あらかじめghe2側で新しく同名のレポジトリbarを作成しておきます。この際にREADME.mdを作成しないようにします。

事前準備を行います。
```
$ git clone --bare git@ghe1:foo/bar.git
$ cd bar.git
$ git remote add ghe2 git@ghe2:foo/bar.git
```

同期方法はgit-fetchでoriginのghe1の変更を取り込みます。次にgit-pushでghe2へ向けてpushします.
refsなどの記法についてはgit-refspec.mdを参照のこと
```
$ git fetch --prune origin 'refs/heads/*:refs/heads/*'
$ git push ghe2 --mirror
```

--pruneオプションをつけると、fetchやpullする際に自動的にリモートで削除されているリモートブランチを削除してくれる。
mirrorとbareオプションについては後で説明しているのでそちらを参照のこと

- 参考
  - http://qiita.com/satoruk/items/186af9d095d744d15c76

### ghe1側のレポジトリに同期されたghe2側の同名レポジトリの差分を更新したい
これは「ghe1側のレポジトリをghe2側の同名レポジトリにミラーする」と全くすべて同じ手順を実施すれば良い。
ghe1のbareを落として、ghe2をremote addして、originからfetchして、ghe2にmirrorとして適用するといった流れだ。

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

### bareレポジトリとは
1台のサーバで複数人が作業する場合のローカルレポジトリとして利用できる。

以下の資料でgit initとgit init --bareの違いを説明している
- http://www.saintsjd.com/2011/01/what-is-a-bare-git-repository/

git initは"working"のためのレポジトリを作成する。そこでは追加、削除、修正などを行う。
git init --bareは"sharing"のためのレポジトリを作成する。その中には.gitディレクトリで履歴などが含まれている。

### bareオプションとmirrorオプションの違いについて

bareオプションと比較して、mirrorはローカルにのみ存在するブランチとすべてのrefsをマッピングするとのこと。
- https://stackoverflow.com/questions/3959924/whats-the-difference-between-git-clone-mirror-and-git-clone-bare

### mirrorの内容を更新したい
```
$ git remote update
```

### githubのウェブサイトを利用せずに、チーム内でgitレポジトリを共有する方法について
ローカルのみでgitレポジトリを作成するには次のようにする。  
bareは管理のみを行うレポジトリで、sharedはグループアクセス可能なパーミッションを追加するオプションである。
```
$ git init --bare --shared /path/to/hogehoge.git
```

なお、リモート用のベアレポジトリは.gitという拡張子を入れるのが一般的です。

- 参考
  - https://qiita.com/shuntaro_tamura/items/d04fb892c9a6b7e1ab42

