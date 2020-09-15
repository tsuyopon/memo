# 概要
git subtreeは、外部のレポジトリの取り込みを行なうことができます。
git submoduleでは、外部レポジトリをハッシュ値から参照しているだけでしたが、git subtreeは自身のプロジェクトに取り込んでしまうといった点で異なります。

# 利用方法
最初はaddをする必要があります。それ以降の取り込みを更新したい場合には、pullを利用します
あらかじめ、git statusで修正されていないことを確認してから以下のコマンドを実行しないと失敗してしまいます。

- prefixには取りみたいレポジトリをどのレポジトリに配置するかを指定します。
- squashを付与すると取り込んだファイルが履歴を持たなくなります。
```
書式:
	git subtree add --prefix=<任意のディレクトリ名> --suquash <1.で登録した任意の名前> <任意のブランチ名>

利用例
	$ git remote add --prefix=pullrepo --squash git@gitlab.subtree.co.jp:subtree-test.git master
```

一度、addしてからはpullを利用することができます。
```
$ git remote add --prefix=pullrepo --squash git@gitlab.subtree.co.jp:subtree-test.git master
```
