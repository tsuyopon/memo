# 概要

### ユーザーのcommit履歴を参照したい場合
- https://github.com/rails/rails/commits/master?author=azarashi

### gitの検索画面からユーザーやその他を指定したい
以下の公式サイトでgithubの検索方法のヘルプがあります。
- https://help.github.com/articles/searching-issues-and-pull-requests/

たとえば、次のような感じで指定可能です。
```
is:pr is:merged author:tsuyopon
```

ラベルの指定も可能
```
label:xxx
```

レポジトリ横断検索で特定のユーザとレポジトリ範囲を限定することも可能
```
user:tsuyopon/memo
```

ハッシュ値の指定が可能だが識別子みたいなものは付与しなくても、7文字以上の16進数文字列がcommit hashと解釈される
```
(例) e1109ab
```

まとめると、次のようなオプションがあるようです。
```
is:pr       is:issue
is:open     is:closed
is:public   is:private
is:merged   is:unmerged
in:title    in:body        in:comments
type:pr     type:issue
author:xxx  assignee:xxx   mentions:xxx   commenter:xxx  involves:xxx   (xxxはusername)
state:open  state:closed   
label:xxx (xxxはlabel)  -label:bug(-を付与すると持たないという意味)
milestone:xxx (xxxはmilestone)
no:label    no:milestone   no:assignee    no:project
status:pending   status:success   status:failure
org:xxx (xxxはorg)

以下は例
language:ruby
repo:tsuyopon/memo
created:<2012-03-01
updated:<=2012-03-01T18:00:00+09:00
merged:2011-01-01..2015-05-01
closed:>2014-06-11 
omments:>100         comments:500..1000 
```

上記オプションにはsort関連のオプションも存在します。
- https://help.github.com/articles/sorting-search-results/ 

```
created-asc
created-desc
updated-asc
updated-desc
commented-desc
commented-asc
```

- 参考
  - http://qiita.com/shunjikonishi/items/c5024e70b0878817725f
