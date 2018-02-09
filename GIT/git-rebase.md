# 概要
git rebase関連の処理について

# 詳細
### 直近のログをまとめる
ログを確認します。
```
$ git log --oneline
ee0ffcb added new (git-grep.md)
1b29715 add trivial(TS/Debugging.md, TS/DocumentLink.md)
7ee8da8 add(rpm_spec.md)
6412ac4 new added(rpm_spec.md)
3ceeefb added new(Cache.md, Debugging.md, DocumentLink.md)
9e35a8e add trivial(BGP.md)
```

次のコマンドで最新１０件のログをまとめようとします。次のコマンドはgit logとは時刻として逆順で表示されるので注意が必要です。
pickからsquashに修正して保存することによりログをまとめることができます。squashとした箇所はその直前のコミットにまとめられます。
```
$ git rebase -i HEAD~10       // 最初から10個分のコミットをまとめる
pick 36cfced added(Crash.md)
pick e1f830d added new document(git-enterprise.md)
pick 13e5f84 mod(BGP.md)
pick 9e35a8e add trivial(BGP.md)
pick 3ceeefb added new(Cache.md, Debugging.md, DocumentLink.md)
pick 6412ac4 new added(rpm_spec.md)
pick 7ee8da8 add(rpm_spec.md)
pick 1b29715 add trivial(TS/Debugging.md, TS/DocumentLink.md)
pick ee0ffcb added new (git-grep.md)
pick 38288a7 mod about git(git-diff.md, git-ui.md, git.md)

# Rebase 6455324..38288a7 onto 6455324
#
# Commands:
#  p, pick = use commit
#  r, reword = use commit, but edit the commit message
#  e, edit = use commit, but stop for amending
#  s, squash = use commit, but meld into previous commit
#  f, fixup = like "squash", but discard this commit's log message
#  x, exec = run command (the rest of the line) using shell
#
# These lines can be re-ordered; they are executed from top to bottom.
#
# If you remove a line here THAT COMMIT WILL BE LOST.
#
# However, if you remove everything, the rebase will be aborted.
#
# Note that empty commits are commented out
```

あとはプッシュします。
```
$ git push -u origin <branch>
```

このgit rebaseのiオプションを使うと
- コミットメッセージを編集する
- コミットをまとめる
- コミットを分割する
- コミットの順番を移動させる
- コミットを削除する

コマンドについて載せておく
- pick:   何もしない
- reword: コミットメッセージを修正する
- squash: コミットをまとめる
- fixed:  squashと似ているが、違いはコメントは変更せずにコミットをまとめる
- edit:   rebaseを一旦止める

### masterからrebaseする
次のようにします。git fetchとgit rebaseの２つはgit mergeしたことと等価となる。
```
$ git checkout xxx     // xxxはrebaseしたい対象ブランチ
$ git fetch upstream
$ git rebase upstream/master
```

conflictが存在する場合には、conflictを解消します。エラーが表示され、git branchを実行するとどのブランチにも属しません
```
$ git branch
* (no branch)
  xxx
```

conflictの行を解消してあげて、git statusを実行すると対象ファイルに「both modified: 〜」と表示されますので、
表示されたファイル全てに対してgit addすることによって追加して、git statusすると
```
$ git add xxx
$ git status     // 「both modified:」の行が消える
```

解消したら次の「git rebase --continue」を実行します。解消するまでなんどもこれを繰り返します。
```
$ git rebase --continue
Applying: xxxxの対応
$ git branch
xxx
```

pushするときにはfオプションを付与しないとプッシュすることができません
```
$ git push -f origin xxx
```

### 特定のハッシュ値からN個分のコミットをまとめたい
以下は特定のハッシュ値から5個分のコミットをまとめている例です。
```
$ git rebase cce24c9~5
```

### 開発中に他の人がコミットしたソースを自分のブランチに反映させる(コミットIDを進める)
次の手順はレポジトリがrebaseされている場合などに必要と思われます。
```
// 自分の修正を退避する
$ git stash

// マスターレポジトリ(upstream)の最新ソースを自分のレポジトリに持ってくる
$ git checkout master
$ git pull upstream master

//ブランチにリモートレポジトリのソースを反映する
$ git checkout  <branch>
$ git rebase master

// 自分の修正を元に戻す
$ git stash pop
```

# 参考URL
- https://git-scm.com/book/ja/v2/Git-%E3%81%AE%E3%81%95%E3%81%BE%E3%81%96%E3%81%BE%E3%81%AA%E3%83%84%E3%83%BC%E3%83%AB-%E6%AD%B4%E5%8F%B2%E3%81%AE%E6%9B%B8%E3%81%8D%E6%8F%9B%E3%81%88
