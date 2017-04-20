# git
git関連についてまとめておきます

# 設定関連
リモートブランチの設定などを確認する場合
```
$ git remote -v
```

リモートブランチの設定を変更する場合
```
$ git remote set-url origin git://github.com/hoge/fuga.git
```

# 取得

### 再帰的に取得する
git submoduleを使っていてそれらも再帰的に取得したい場合には次のようにします。
```
$ git clone git://github.com/hoge/fuga.git --recursive
```

ダウンロードしたレポジトリのサブモジュールを後からアップデートしたい場合には次のようにすれば良い
```
$ git submodule update --init --recursive
```

# ブランチ関連

### ブランチを削除する
```
$ git branch -d issue1
```
以下のコマンドでリモート側も削除します。
```
$ git push origin :issue1
または
$ git push origin --delete issue1
```

このほかにもHEADにマージしてあるブランチだけ削除したければ--delete、マージに無条件で削除する場合には-Dオプションを利用する。

- 参考
 - http://chaika.hatenablog.com/entry/2016/03/01/080000

### ローカルブランチの一覧を表示する
```
$ git branch
```

### リモートブランチの一覧を表示する
```
$ git branch --remote
```

### リモートブランチとローカルブランチの一覧を表示する。
```
$ git branch --all
```

### ローカルでマージ済みブランチ一覧を表示する。
```
$ git branch --merged
```

# 復旧など
### 誤って消してしまったファイルを復活させる
```
$ rm Makefile.md
$ git checkout HEAD Makefile.md
```

# git tag

### tag一覧や情報を取得する
tag一覧を取得するには次の通り
```
$ git tag
```

タグの詳細情報を見るにはshowを利用する。
```
$ git show <タグ名>
tag <タグ名>
Tagger: Author Name <mail@address.com>
Date:   Sun Jan 1 11:11:11 2012 +0900

Annotation Message
commit 102495885ae6aaf8d3c3576a1b3007bf8993bc9
Author: Author Name <mail@address.com>
Date:   Sun Jan 11 11:11:11 2012 +0900

    Commit Message
```

### タグの状態をチェックアウトする
```
$ git checkout <タグ名>
```

ローカルで行った変更を全て破棄してcheckoutするには-f(force)を付与する
```
$ git checkout -f <タグ名>
```

### 現在のgit状態にタグを付与する
```
$ git tag -a <タグ名>                 // エディタが表示されメッセージを付けることができる
$ git tag -a <タグ名> -m <メッセージ>  // メッセージもコマンド内で付けられる
```

tagをリモートに登録する場合には
```
$ git push origin <タグ名>
```

ローカルでつけたtagをリモートに反映するというコマンドもある。(怖いのであまり使わない方がいいかもしれない)
```
$ git push origin --tags
```

### tagを削除する
リモートのタグを削除する場合
```
$ git tag -d [タグの名前]
$ git push origin :[タグの名前]
```

### tagをリネームする(tagをコピーする)
実際にはリネームは存在しないのでコピーして、古いのを削除するということになる。
```
$ git tag newTag oldTag  // oldTagと同じコミットにnewTagというタグが新しくできる
$ git tag -d oldTag      // もともと存在したタグを削除する
```

### 過去のコミットにtagを付与する。
以前の状態にtagを残しておきたいという場合もあるかもしれない。
```
$ git log --pretty=oneline

hogehoge1 dev
fugafuga1 pre
fufufufu1 prod

$ git tag pre_v1.0.0 fugafuga1
```

### リモートに存在するタグを確認する
```
$ git ls-remote --tags
```

### リモートタグの情報をローカルに反映する
```
$ git pull --tags
```

# サブモジュール

### manを見る
どうやらsubmoduleにはmanがあるようです。
```
$ man git-submodule
```

### サブモジュールを追加する
```
$ git submodule add https://gist.github.com/hoge.git WordPress
$  git status
On branch master
Your branch is up-to-date with 'origin/master'.

Changes to be committed:
  (use "git reset HEAD <file>..." to unstage)

      new file:   .gitmodules
	      new file:   WordPress
```

登録したサブモジュールを更新するには次のようにします。
```
$ git submodule update

以下はsubmodule内部のsubmoduleも更新したい場合
$ git submodule update --recursive
```

# その他

### 誤って登録してしまったコミットメッセージを変更する
amendオプションを使います。
```
$ git commit -m '修正版コメント' --amend
```

### トラッキングされていないファイルを削除したい。
次のコマンドでgitでトラッキングされないファイルを削除する場合、
```
$ git status
```

nオプションでドライランするので削除されるファイルの確認をして、fオプションで削除することができます。
```
$ git clean -n    # dry-runで確認
$ git clean -f    # 削除実行
```

ディレクトリも再帰的に削除するにはdオプションも付加します。
```
$ git clean -dn    # dry-runで確認
$ git clean -df    # 削除実行
```

### .gitsubmoduleのハッシュ値に"-dirty"というのが付与されてしまう場合

たとえば、更新しようとしているレポジトリの中で呼ばれているレポジトリも次のコマンドで更新した場合すべてがアタrしくなる
```
$ git submodule update --recursive
```

この状態で次のhogeレポジトリを落としてその直下にrepoaがあり、repoaは別のgitsubmodule repobを使っている場合
```
hoge/repoa
      /repob
```

通常は、hogeレポジトリに入ったあとにrepoaにcdして、git checkout xxxxでブランチを切り替えてhogeに戻ってからgit diffなどして確認する。
このときにxxxxxx-dirtyとなった場合、repobの方も更新されていることがある。


