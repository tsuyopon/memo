# 概要
git cloneについて

# 詳細

### レポジトリをcloneする 
```
$ git clone git://github.com/schacon/grit.git
```

### レポジトリをcloneして特定のレポジトリにチェックアウトする
```
$ git clone -b mybranch git://github.com/schacon/grit.git
```

### レポジトリをディレクトリ名を指定してcloneする
引数の最後に名前を指定するとその名前がディレクトリ名となります。
```
$ git clone git://github.com/schacon/grit.git mygrit
```

### レポジトリ内に登録されているsubmoduleも再帰的に取得する
```
$ git clone https://github.com/unconed/TermKit.git --recursive
```

recursiveを忘れてcloneしてしまったら次のようなコマンドを実行する必要があります。
```
$ git submodule update --init --recursive
```

### 最新版のみcloneできれば履歴がいらない場合
githubではこれをshallow cloneとよんでいるようです。取得時間も早いです。
```
$ git clone --depth 1 https://github.com/git/git
```

depthに1を指定しているのは取得する履歴の数です。git logを実行すると履歴は1つしかないことが確認できます。

- 参考
  - https://qiita.com/usamik26/items/7bfa61b31344206077fb

# 参考URL
- https://git-scm.com/book/ja/v1/Git-%E3%81%AE%E5%9F%BA%E6%9C%AC-Git-%E3%83%AA%E3%83%9D%E3%82%B8%E3%83%88%E3%83%AA%E3%81%AE%E5%8F%96%E5%BE%97
