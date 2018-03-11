# git
git関連の基礎知識についてまとめておきます

一般的にはgitは以下の構造となっていることを意識しておくこと
```
ワーキングツリー  --add-->  インデックス  --commit--> ローカルレポジトリ  --push--> リモートレポジトリ --PRandマージ--> コアレポジトリ 
```

# ファイルやディレクトリ名を変更する
deleteして、addしてなんてことをやっているのが面倒であるので、git mvコマンドが存在します。
```
$ git mv oldname newname
```

すでに存在するファイル名に変更するにはfオプションが必要となるようです。
```
$ git mv -f oldname newname
```

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

### ブランチ作成と同時にそのブランチに移動する
ブランチ作成と同時にはよく使うので１行でできるようにしておくとよさそうです。
```
$ git checkout -b testbranch
```

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

### ブランチ名を変更する
```
$ git branch -m issue1 newissue
$ git branch
```

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

### 全てのブランチの情報を取り込む
デフォルトのブランチ以外のブランチがあればそちらに切り替えたいたいような場合、全てのブランチ情報を取得するには次のようにします。
以下を実行することで他のブランチにも切り替えを行うことができます。
```
$ git pull --all
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

# 復元

### 消したファイルやディレクトリを復元させたい場合
次のコマンドを実行する。ただし、変更点も一緒に戻るので注意すること。
```
$ git checkout -f
```

一部のファイルやディレクトリだけ戻す場合にはパス名を指定すること
```
$ git checkout -f path/to/xxxx
```

### ブランチの状態を修正してしまったので、最新のコミットの状態に戻す
```
$ git reset --hard HEAD
```

### 誤って登録してしまった直前のコミットメッセージを変更する
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

ディレクトリも再帰的に削除するにはdオプションも付加します。次のコマンドは現在いるカレントディレクトリを起点として捜査します。
```
$ git clean -d -n    # dry-runで確認
$ git clean -d -f    # 削除実行
```

次のgitで意図的に無視しているファイルを削除する次のオプションもあります
- x: .gitignoreや$GIT_DIR/info/excludeで指定されているファイルを除外せずに削除対象に含めたい場合
- X: gitがignoreしているファイルのみを削除対象とする


### ブランチを作るのを忘れてmasterにコミットしてしまった場合に、そのブランチを作成してコミットを移す方法
まずは誤ってmasterにコミットしたことに気づいた時点でブランチを作成します。
```
$ git branch testbranch
```

masterからブランチを切り替えます
```
$ git checkout testbranch
```

masterのコミット番号を確認する。m000001からm000003までの3コミットがtestbranchに移すためのコミットとする。
```
$ git log --oneline --decorate --graph master
* m000003 (master) mod3
* m000002 mod2
* m000001 mod1
* m000000 (origin/master, origin/HEAD) 作業開始地点
```

testbranchに古い順でチェリーピックでコミットをコピーします。
```
$ git cherry-pick m000001 
$ git cherry-pick m000002
$ git cherry-pick m000003 
```

masterとtestbranchの関係を確認します。コミット番号は新しく振られます。
```
$ git log --oneline --decorate --graph master testbranch
* b000003 (HEAD, branch01) なんか修正3
* b000002 なんか修正2
* b000001 なんか修正1
| * m000003 (master) mod3
| * m000002 mod2
| * m000001 mod1
|/  
* m000000 (origin/master, origin/HEAD) 作業開始地点
```

以上で完成です。後は、必要に応じてmasterのコミットを削除します。
たとえば、今回はmasterからtestbranchに3件のcommitを移動したので次のようにします。
```
$ git reset --hard HEAD~3
```

### キャレットとチルダの違いについて
- キャレット
  - 指定したコミットの親を指す
- チルダ
  - 指定したコミットの前世代を指す
- http://chulip.org/entry/20121006/1349406906

# その他
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

- 参考
  - http://qiita.com/atskimura/items/a90dfa8bfc72e3657ef9


# 参考URL
- Pro Git
  - https://git-scm.com/book/en/v2
