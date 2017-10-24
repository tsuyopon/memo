# 概要
ttyをに付け替えることができる仕組みです。
長時間のビルドなどを途中で止めるのを避けたい場合などに利用できます。

# 詳細
### インストール
ソースコードからインストールするのも非常に簡単
```
$ git clone https://github.com/nelhage/reptyr.git
$ cd reptyr
$ make            // インストールも含めてしたければこの後にmake installを実行します。
$ ls ./reptyr     // 出来上がり
```

またはubuntuだと次のようにしてインストールすることも可能
```
$ sudo aptitude install reptyr
```

### 使い方
hogeというプロセスのpidを取得して
```
$ ps auxww | grep hoge
$ tmux
$ reptyr <pid>
```

# 参考URL
- https://github.com/nelhage/reptyr
- https://qiita.com/__cooper/items/c0d21cf24436621052c3
