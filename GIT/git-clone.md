# 概要
git cloneについて

# 詳細

### レポジトリをcloneする 
```
$ git clone git://github.com/schacon/grit.git
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

# 参考URL
- https://git-scm.com/book/ja/v1/Git-%E3%81%AE%E5%9F%BA%E6%9C%AC-Git-%E3%83%AA%E3%83%9D%E3%82%B8%E3%83%88%E3%83%AA%E3%81%AE%E5%8F%96%E5%BE%97
