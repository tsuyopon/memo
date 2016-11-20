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



# 比較

### コミットしたファイル同士の変更点の比較
```
$ git diff 変更後のSHA..変更前のSHA
```

または次のようにしても可能らしい
```
$ git diff commit1 commit2 -- path/to/file
```

### コミットしたSHAの比較を行う場合
```
$ git diff 確認したいコミットのSHA^..確認したいコミットのSHA
```

### 空白コードなどを無視する場合
```
$ git diff -w
```

### 空行を無視する場合
```
$ git diff --ignore-blank-lines
```

### コミット間の差分を色で表示する
```
$ git diff --color-words
```



# git pull

### pullする前にあらかじめファイルの変更点を確認しておきたい場合
```
$ git diff HEAD..リモート名/ブランチ名
```

# 復旧など
### 誤って消してしまったファイルを復活させる
```
$ rm Makefile.md
$ git checkout HEAD Makefile.md
```
