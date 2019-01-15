# push関連
主にgit push関連についてまとめています。
tagやbranchをpushしての追加や削除については、別の資料などに記載されている可能性があります。

forceプッシュを使う可能性がある場合には個人レポジトリにforkしたものでやりましょう。

# 詳細

### git pushの意味をちゃんと理解する
よくpushする際には次のように記載していますが、、、
```
$ git push origin master
```

これは省略しないと次のような意味となります。
```
$ git push <リモート名>  <今いるブランチ>:<push先リモートブランチ>
```

リモート名がorigin、今いるブランチがtestbranch、プッシュしたいリモートブランチがmasterだとすると次のようになります。
つまり、現在いるブランチは省略できます。
```
$ git push origin testbranch:master

or

$ git push origin master
```

### git push -u の意味について

git push -u origin master とすると次回から git push だけで勝手に origin master で push してくれるらしい。
つまり、引数なしの「git push」は超危険。。。使わないようにする。

オプションについては次のようにしてgit-xxxxでmanpageを開くと良いらしい。
```
man git-push
```

以下のリンクも参考のこと
- https://qiita.com/ironsand/items/6c301fef730d53f35bc3

### git push引数なしは危険なのでちゃんと理解する
uオプションなどを指定してしまうと、以降ではgit pushで引数を省略できてしまいます。
対処方法としては次の通り
- 1. ブランチ名を指定する
```
$ git push origin master
```
- 2. デフォルトの挙動をupstreamモードに変更する
  - カレントブランチとリモートブランチの間に「追跡関係」がある場合のみ、カレントブランチのpushが行われます。
```
$ git config --global push.default upstream
$ git push
```
- 3. デフォルトの挙動をcurrentモードに変更する
  - カレントブランチのpushのみが行われます
```
$ git config --global push.default current
$ git push
```
- 4. デフォルトの挙動をsimpleモードに変更する(Git1.7.11以降のみ)
  - 「カレントブランチと同名のリモートブランチが存在する場合のみ、カレントブランチのpushが行われる」モード
```
$ git config --global push.default simple
$ git push
```





- 参考
  - http://dqn.sakusakutto.jp/2012/10/git_push.html

### 直前のコミット内容を変更してremoteにプッシュする
```
$ git commit --amend
$ git push -f origin XXXX
```

### 特定のコミットをなかったことにする
```
$ git rebase -i HEAD~2        // 不要な行を削除する
$ git push -f origin XXXX
```

### upstreamからブランチを派生させる
```
$ git remote add upstream https://github.com/apache/trafficserver.git
$ git fetch upstream
$ git checkout upstream/7.1.x
$ git checkout -b 7.1.x_branch
```
